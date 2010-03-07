//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TCCTLUTForm.h"
#include <FileCtrl.hpp>
#include "TMainForm.h"

#include <cms/lcd/calibrate/lcdcalibrator.h>
#include <cms/measure/MeterMeasurement.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCCTLUTForm *CCTLUTForm;
//---------------------------------------------------------------------------
__fastcall TCCTLUTForm::TCCTLUTForm(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------



void __fastcall TCCTLUTForm::Button_BrowseDirClick(TObject * Sender)
{
    //this->OpenDialog1->Execute();
    AnsiString Dir = "C:\\Program Files\\";
    SelectDirectory("選擇目錄", "", Dir);
}

//---------------------------------------------------------------------------

void TCCTLUTForm::resetBitDepth()
{
    //this->RadioButton_In8->Checked = true;
    this->CheckBox_Gamma256->Checked = false;
    setBitDepthEnable(true, true, true, true, false);
};

void TCCTLUTForm::setBitDepthEnable(bool lut10, bool lut12, bool out6,
				    bool out8, bool out10)
{
    this->RadioButton_Lut10->Enabled = lut10;
    this->RadioButton_Lut12->Enabled = lut12;
    this->RadioButton_Out6->Enabled = out6;
    this->RadioButton_Out8->Enabled = out8;
    this->RadioButton_Out10->Enabled = out10;
};

void __fastcall TCCTLUTForm::RadioButton_In6Click(TObject * Sender)
{
    resetBitDepth();
    this->RadioButton_Lut10->Checked = true;
    this->RadioButton_Out6->Checked = true;
    setBitDepthEnable(true, false, true, false, false);
    this->Edit_StartLevel->Text = "252";
    this->ComboBox_LevelStep->Text = "4";
    this->CheckBox_AvoidNoise->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_In8Click(TObject * Sender)
{
    resetBitDepth();
    this->RadioButton_Out8->Checked = true;
    setBitDepthEnable(true, true, true, true, false);
    this->Edit_StartLevel->Text = "255";
    this->ComboBox_LevelStep->Text = "1";
    this->CheckBox_AvoidNoise->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_In10Click(TObject * Sender)
{
    this->CheckBox_Gamma256->Checked = true;
    this->RadioButton_Lut12->Checked = true;
    this->RadioButton_Out8->Checked = true;
    setBitDepthEnable(false, true, false, true, true);
    this->Edit_StartLevel->Text = "255";
    this->ComboBox_LevelStep->Text = "1";
    this->CheckBox_AvoidNoise->Checked = false;
    this->CheckBox_AvoidNoise->Enabled = false;
    this->CheckBox_Gamma256->Enabled = true;
}

//---------------------------------------------------------------------------



void __fastcall TCCTLUTForm::RadioButton_RBInterpClick(TObject * Sender)
{
    this->Edit_RBInterpUnder->Enabled = true;
    this->Edit_P1->Enabled = false;
    this->Edit_P2->Enabled = false;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_P1P2Click(TObject * Sender)
{
    this->Edit_RBInterpUnder->Enabled = false;
    this->Edit_P1->Enabled = true;
    this->Edit_P2->Enabled = true;
}

//---------------------------------------------------------------------------



void __fastcall TCCTLUTForm::Button_RunClick(TObject * Sender)
{
    cms::lcd::calibrate::LCDCalibrator calibrator(MainForm->analyzer);

    //==========================================================================
    // P1P2和RBInterp的選擇
    //==========================================================================
    if (this->RadioButton_P1P2->Checked) {
	//選了P1P2
	int p1 = this->Edit_P1->Text.ToInt();
	int p2 = this->Edit_P2->Text.ToInt();
	calibrator.setP1P2(p1, p2);
    } else {
	//選了RBInterp
	int rbunder = this->Edit_RBInterpUnder->Text.ToInt();
	calibrator.setRBInterpolation(rbunder);
    }
    //==========================================================================

    //==========================================================================
    // in/lut/out的處理
    //==========================================================================
    int in =
	RadioButton_In6->Checked ? 6 : 0 +
	RadioButton_In8->Checked ? 8 : 0 +
	RadioButton_In10->Checked ? 10 : 0;
    int lut =
	RadioButton_Lut10->Checked ? 10 : 0 +
	RadioButton_Lut12->Checked ? 12 : 0;
    int out =
	RadioButton_Out6->Checked ? 6 : 0 +
	RadioButton_Out8->Checked ? 8 : 0 +
	RadioButton_Out10->Checked ? 10 : 0;
    calibrator.setBitDepth(in, lut, out);
    //==========================================================================

    //==========================================================================
    // gamma的處理
    //==========================================================================
    if (this->RadioButton_Gamma->Checked) {
	double gamma = this->ComboBox_Gamma->Text.ToDouble();
	calibrator.setGamma(gamma, 256);
    } else {

    }
    calibrator.setGByPass(this->CheckBox_GByPass->Checked);
    //==========================================================================

    //==========================================================================
    // blue correction
    //==========================================================================
    if (this->CheckBox_BGain->Checked) {
	double gain = this->Edit_BGain->Text.ToDouble();
	calibrator.setBIntensityGain(gain);
    }
    calibrator.setBMax(this->CheckBox_BMax->Checked);
    //==========================================================================
    calibrator.setGamma256(this->CheckBox_Gamma256->Checked);
    calibrator.setAvoidFRCNoise(this->CheckBox_AvoidNoise->Checked);

    int start = this->Edit_StartLevel->Text.ToInt();
    int end = this->Edit_EndLevel->Text.ToInt();
    int step = this->ComboBox_LevelStep->Text.ToInt();

    int waitTimes = MainForm->getInterval();
    MainForm->mm->setWaitTimes(waitTimes);

    RGB_vector_ptr dgcode = calibrator.getDGCode(start, end, step);
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::FormKeyPress(TObject * Sender, char &Key)
{
    if (Key == 27) {
	int x = 1;
    }
}

//---------------------------------------------------------------------------


