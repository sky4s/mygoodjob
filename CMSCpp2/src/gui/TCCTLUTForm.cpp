//---------------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop

#include "TCCTLUTForm.h"
#include <FileCtrl.hpp>
#include "TMainForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCCTLUTForm *CCTLUTForm;
//---------------------------------------------------------------------------
__fastcall TCCTLUTForm::TCCTLUTForm(TComponent * Owner)
:TForm(Owner), serialid(0)
{
}

//---------------------------------------------------------------------------



void __fastcall TCCTLUTForm::Button_BrowseDirClick(TObject * Sender)
{
    //this->OpenDialog1->Execute();
    AnsiString Dir = this->Edit_Directory->Text;
    //AnsiString Dir = "C:\\Program Files\\";
    SelectDirectory("選擇目錄", "", Dir);
    this->Edit_Directory->Text = Dir;
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
    bool tconInput = MainForm->RadioButton_TCON->Checked;

    this->CheckBox_Gamma256->Checked = true;
    this->RadioButton_Lut12->Checked = true;
    this->RadioButton_Out8->Checked = true;
    setBitDepthEnable(false, true, false, true, true);

    if (false == tconInput) {
	this->Edit_StartLevel->Text = "255";
	this->ComboBox_LevelStep->Text = "1";
    } else {
	this->Edit_StartLevel->Text = "1023";
	this->ComboBox_LevelStep->Text = "4";
    }

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
    using namespace std;
    using namespace Dep;
    using namespace cms::lcd::calibrate;

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
    bool gamma256 = this->CheckBox_Gamma256->Checked;
    bitDepth =
	bptr < BitDepthProcessor >
	(new BitDepthProcessor(in, lut, out, gamma256, false));
    /*const MaxValue & inbit = MaxValue::getByBit(in);
       const MaxValue & lutbit = MaxValue::getByBit(lut);
       const MaxValue & outbit = MaxValue::getByBit(out); */
    //==========================================================================

    cms::lcd::calibrate::LCDCalibrator calibrator(MainForm->analyzer,
						  bitDepth);

    //==========================================================================
    // P1P2和RBInterp的選擇
    //==========================================================================
    if (this->RadioButton_P1P2->Checked) {
	//選了P1P2
	int p1 = this->Edit_P1->Text.ToInt();
	int p2 = this->Edit_P2->Text.ToInt();
	calibrator.setP1P2(p1, p2);
    } else if (this->RadioButton_RBInterp->Checked) {
	//選了RBInterp
	int rbunder = this->Edit_RBInterpUnder->Text.ToInt();
	calibrator.setRBInterpolation(rbunder);
    } else {
	calibrator.setNoneDimCorrect();
    }

    //==========================================================================

    //==========================================================================
    // gamma的處理
    //==========================================================================
    if (this->RadioButton_Gamma->Checked) {
	double gamma = this->ComboBox_Gamma->Text.ToDouble();
	calibrator.setGamma(gamma);
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
    //calibrator.setGamma256(this->CheckBox_Gamma256->Checked);
    calibrator.setAvoidFRCNoise(this->CheckBox_AvoidNoise->Checked);

    int start = this->Edit_StartLevel->Text.ToInt();
    int end = this->Edit_EndLevel->Text.ToInt();
    int step = this->ComboBox_LevelStep->Text.ToInt();

    int waitTimes = MainForm->getInterval();
    MainForm->mm->setWaitTimes(waitTimes);

    RGB_vector_ptr dglut = calibrator.getDGLut(start, end, step);

    AnsiString dir = this->Edit_Directory->Text;
    if (!DirectoryExists(dir)) {
	CreateDir(dir);
    }
    AnsiString sid = FormatFloat("00", serialid);
    AnsiString astr = dir + "\\" + this->Edit_Prefix->Text + sid + ".xls";
    string filename = astr.c_str();

    calibrator.storeDGLut(filename, dglut);
    ShowMessage("Ok!");
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::FormKeyPress(TObject * Sender, char &Key)
{
    if (Key == 27) {
	//int x = 1;
    }
}

//---------------------------------------------------------------------------




void __fastcall TCCTLUTForm::FormCreate(TObject * Sender)
{
    bool debug = !MainForm->linkCA210;
    this->Button_Debug->Visible = debug;
    this->Button_Reset->Visible = debug;
    this->RadioButton_None->Visible = debug;
}

//---------------------------------------------------------------------------



void __fastcall TCCTLUTForm::Button_DebugClick(TObject * Sender)
{
    using namespace std;
    if (OpenDialog1->Execute()) {
	const AnsiString & filename = OpenDialog1->FileName;
	MainForm->setDummyMeterFilename(string(filename.c_str()));
	ShowMessage("Dummy meter setting Ok!");
    };

}

//---------------------------------------------------------------------------


void __fastcall TCCTLUTForm::Button_ResetClick(TObject * Sender)
{
    MainForm->resetDummyMeter();
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_Out6Click(TObject * Sender)
{
    this->Edit_StartLevel->Text = "252";
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_Out8Click(TObject * Sender)
{
    this->Edit_StartLevel->Text = "255";
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::Button_LoadGammaCurveClick(TObject * Sender)
{
    this->CheckBox_GByPass->Visible = true;
}

//---------------------------------------------------------------------------

