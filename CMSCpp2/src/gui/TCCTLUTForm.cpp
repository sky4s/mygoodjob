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
:TForm(Owner), serialid(0), in(8), lut(10), out(8)
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

void TCCTLUTForm::setBitDepthEnable(bool lut10, bool lut12, bool out6,
				    bool out8, bool out10)
{
    this->RadioButton_Lut10->Enabled = lut10;
    this->RadioButton_Lut12->Enabled = lut12;
    this->RadioButton_Out6->Enabled = out6;
    this->RadioButton_Out8->Enabled = out8;
    this->RadioButton_Out10->Enabled = out10;
};

void TCCTLUTForm::setBitDepthChecked(int lutSelect, int outSelect)
{

    switch (lutSelect) {
    case 0:
	this->RadioButton_Lut10->Checked = true;
	break;
    case 1:
	this->RadioButton_Lut12->Checked = true;
	break;
    };
    switch (outSelect) {
    case 0:
	this->RadioButton_Out6->Checked = true;
	break;
    case 1:
	this->RadioButton_Out8->Checked = true;
	break;
    case 2:
	this->RadioButton_Out10->Checked = true;
	break;
    };
};

void TCCTLUTForm::setMeasureInfo()
{
    using namespace util;
    int start = bitDepth->getMeasureStart();
    int step = bitDepth->getMeasureStep();
    this->Edit_StartLevel->Text = Util::toString(start).c_str();
    this->ComboBox_LevelStep->Text = Util::toString(step).c_str();
};

void __fastcall TCCTLUTForm::RadioButton_In6Click(TObject * Sender)
{
    using namespace boost;
    bitDepth->setInBit(in = 6);
    // 設定lut/out bit depth checked
    setBitDepthChecked(0, 0);
    // 設定enable
    setBitDepthEnable(true, false, true, false, false);
    // 設定量測step
    //setMeasureInfo();
    // 設定Avoid Noise
    this->CheckBox_AvoidNoise->Enabled = true;
    //設定Gamma256
    this->CheckBox_Gamma256->Checked = false;

}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_In8Click(TObject * Sender)
{
    using namespace util;
    bitDepth->setInBit(in = 8);
    // 設定lut/out bit depth checked
    setBitDepthChecked(0, 1);
    // 設定enable
    setBitDepthEnable(true, true, true, true, false);
    // 設定量測step
    //setMeasureInfo();
    // 設定Avoid Noise
    this->CheckBox_AvoidNoise->Enabled = true;
    //設定Gamma256
    this->CheckBox_Gamma256->Checked = false;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_In10Click(TObject * Sender)
{
    using namespace util;
    bitDepth->setInBit(in = 10);
    // 設定lut/out bit depth checked
    setBitDepthChecked(1, 1);
    // 設定enable
    setBitDepthEnable(false, true, false, true, true);
    // 設定量測step
    //setMeasureInfo();
    // 設定Avoid Noise
    this->CheckBox_AvoidNoise->Enabled = false;
    //設定Gamma256
    this->CheckBox_Gamma256->Checked = true;
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
    calibrator.setAvoidFRCNoise(this->CheckBox_AvoidNoise->Checked);
    calibrator.setKeepMaxLuminance(this->CheckBox_KeepMax->Checked);

    int start = this->Edit_StartLevel->Text.ToInt();
    int end = this->Edit_EndLevel->Text.ToInt();
    int step = this->ComboBox_LevelStep->Text.ToInt();

    int waitTimes = MainForm->getInterval();
    MainForm->mm->setWaitTimes(waitTimes);
    try {
	RGB_vector_ptr dglut = calibrator.getDGLut(start, end, step);

	AnsiString dir = this->Edit_Directory->Text;
	if (!DirectoryExists(dir)) {
	    CreateDir(dir);
	}
	AnsiString sid = FormatFloat("00", serialid);
	AnsiString astr =
	    dir + "\\" + this->Edit_Prefix->Text + sid + ".xls";
	string filename = astr.c_str();

	calibrator.storeDGLut(filename, dglut);
	ShowMessage("Ok!");
    }
    catch(java::lang::IllegalStateException ex) {
	ShowMessage(ex.toString().c_str());
    }

}

//---------------------------------------------------------------------------




void __fastcall TCCTLUTForm::FormCreate(TObject * Sender)
{
    using namespace cms::lcd::calibrate;

    bool debug = !MainForm->linkCA210;
    this->Button_Debug->Visible = debug;
    this->Button_Reset->Visible = debug;
    this->RadioButton_None->Visible = debug;

    //bool tconInput = MainForm->RadioButton_TCON->Checked;
    bitDepth.reset(new BitDepthProcessor(in, lut, out, false, false));
    setMeasureInfo();
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
    bitDepth->setOutBit(6);
    setMeasureInfo();
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_Out8Click(TObject * Sender)
{
    bitDepth->setOutBit(8);
    setMeasureInfo();
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::Button_LoadGammaCurveClick(TObject * Sender)
{
    this->CheckBox_GByPass->Visible = true;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::CheckBox_Gamma256Click(TObject * Sender)
{
    bool gamma256 = this->CheckBox_Gamma256->Checked;
    bitDepth->setGamma256(gamma256);
}

//---------------------------------------------------------------------------

void TCCTLUTForm::setTCONInput(bool tconInput)
{
    bitDepth->setTCONInput(tconInput);
}

void __fastcall TCCTLUTForm::RadioButton_Out10Click(TObject * Sender)
{
    if (!bitDepth->isTCONInput()) {
	ShowMessage("Recommend using T-CON Input.");
    };
    bitDepth->setOutBit(10);
    setMeasureInfo();
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::FormShow(TObject * Sender)
{
    setMeasureInfo();
}

//---------------------------------------------------------------------------

