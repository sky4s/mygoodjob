//---------------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include "TMainForm.h"
#include "TGammaAdjustmentForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TOptionsFrame"
#pragma link "TOutputFileFrame"
#pragma resource "*.dfm"
TGammaAdjustmentForm *GammaAdjustmentForm;
//---------------------------------------------------------------------------
__fastcall TGammaAdjustmentForm::TGammaAdjustmentForm(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------
void TGammaAdjustmentForm::setBitDepthProcessor(bptr < cms::lcd::BitDepthProcessor > bitDepth)
{
    this->bitDepth = bitDepth;
}

//---------------------------------------------------------------------------


void __fastcall TGammaAdjustmentForm::FormShow(TObject * Sender)
{
    using namespace cms::util;
    using namespace Dep;
    using namespace cms::lcd::calibrate;

    int step = bitDepth->getMeasureStep();
    this->ComboBox_LevelStep->Text = Util::toString(step).c_str();

    const MaxValue & input = bitDepth->getInputMaxValue();
    bool avoidNoise = (input == MaxValue::Int6Bit || input == MaxValue::Int8Bit);
    this->CheckBox_AvoidNoise->Enabled = avoidNoise;

    calibrator = bptr < LCDCalibrator > (new
					 LCDCalibrator(MainForm->getComponentFetcher(), bitDepth));
}

//---------------------------------------------------------------------------




void __fastcall TGammaAdjustmentForm::Button_LoadGammaClick(TObject * Sender)
{
    using namespace cms::util;
    OpenDialog1->Filter = "Desired Gamma Files(*.xls)|*.xls";
    if (OpenDialog1->Execute()) {
	const AnsiString & filename = OpenDialog1->FileName;
	rgbGamma = RGBGamma::loadFromDesiredGamma(filename.c_str());


	if (rgbGamma != null) {
	    unsigned int n = bitDepth->getLevel();
	    if (rgbGamma->w->size() == n) {
		ComboBox_GrayGamma->Text = "Load";
	    }
	    if (rgbGamma->r->size() == n) {
		ComboBox_RGamma->Text = "Load";
	    }
	    if (rgbGamma->g->size() == n) {
		ComboBox_GGamma->Text = "Load";
	    }
	    if (rgbGamma->b->size() == n) {
		ComboBox_BGamma->Text = "Load";
	    }
	    this->CheckBox_LoadGamma->Checked = true;
	    this->CheckBox_LoadGamma->Enabled = true;
	} else {
	    ShowMessage("Desired Gamma File Format is wrong!");
	    this->CheckBox_LoadGamma->Checked = false;
	    this->CheckBox_LoadGamma->Enabled = false;
	}

    }
}

//---------------------------------------------------------------------------

void __fastcall TGammaAdjustmentForm::CheckBox_LoadGammaClick(TObject * Sender)
{
    using namespace cms::util;
    if (false == this->CheckBox_LoadGamma->Checked) {
	this->CheckBox_LoadGamma->Enabled = false;
	rgbGamma = RGBGamma_ptr((RGBGamma *) null);
	ComboBox_GrayGamma->Text = "2.2";
	ComboBox_RGamma->Text = "2.2";
	ComboBox_GGamma->Text = "2.2";
	ComboBox_BGamma->Text = "2.2";
    }
}

//---------------------------------------------------------------------------


void __fastcall TGammaAdjustmentForm::Button_GrayGammaClick(TObject * Sender)
{
    gammaAdjust(false);
}

//---------------------------------------------------------------------------

void __fastcall TGammaAdjustmentForm::Button_RGBGammaClick(TObject * Sender)
{
    gammaAdjust(true);
}

//---------------------------------------------------------------------------

void TGammaAdjustmentForm::gammaAdjust(bool rgbGammaAdjust)
{
    using namespace std;
    using namespace cms::util;
    try {
	run = true;
	MainForm->showProgress(ProgressBar1);
	//==========================================================================
	// gamma���B�z
	//==========================================================================
	if (rgbGammaAdjust) {
	    if (this->CheckBox_LoadGamma->Checked) {
		//���Jgamma
		double_vector_ptr rgammaCurve = rgbGamma->r;
		double_vector_ptr ggammaCurve = rgbGamma->g;
		double_vector_ptr bgammaCurve = rgbGamma->b;
		calibrator->setGammaCurve(rgammaCurve, ggammaCurve, bgammaCurve);
	    } else {
		//rgb gamma���}�]�w
		double rgamma = this->ComboBox_RGamma->Text.ToDouble();
		double ggamma = this->ComboBox_GGamma->Text.ToDouble();
		double bgamma = this->ComboBox_BGamma->Text.ToDouble();
		calibrator->setGamma(rgamma, ggamma, bgamma);
	    }

	} else {
	    if (this->CheckBox_LoadGamma->Checked) {
		//���Jgamma
		double_vector_ptr gammaCurve = rgbGamma->w;
		calibrator->setGammaCurve(gammaCurve);
	    } else {
		double gamma = this->ComboBox_GrayGamma->Text.ToDouble();
		calibrator->setGamma(gamma);
	    }
	}
	//==========================================================================
	calibrator->AvoidFRCNoise = this->CheckBox_AvoidNoise->Checked;
	calibrator->setKeepMaxLuminance(this->CheckBox_KeepMax->Checked);
	calibrator->FineLuminanceCalibrate = this->CheckBox_FineCalibrate->Checked;

	if (this->TOutputFileFrame1->createDir() == false) {
	    return;
	}
	RGB_vector_ptr dglut = calibrator->getGammaDGLut(getMeasureCondition());
	if (dglut == null) {
	    ShowMessage("Internal Error!");
	    return;
	}
	String_ptr astr = this->TOutputFileFrame1->getOutputFilename();
	string filename = astr->c_str();
	calibrator->storeDGLutFile(filename, dglut);
	ShowMessage("Ok!");
	Util::shellExecute(filename);
    }
    __finally {
	MainForm->stopProgress(ProgressBar1);
	run = false;

    }

};


bptr < cms::lcd::calibrate::MeasureCondition > TGammaAdjustmentForm::getMeasureCondition()
{
    using namespace cms::lcd::calibrate;
    int start = bitDepth->getMeasureStart();
    int end = bitDepth->getMeasureEnd();
    int step = this->ComboBox_LevelStep->Text.ToInt();

    //�w�]���Ĥ@��
    int firstStep = (bitDepth->getMeasureStep() != step) ? step : bitDepth->getMeasureFirstStep();

    return bptr < MeasureCondition >
	(new MeasureCondition(start, end, firstStep, step, bitDepth->getMeasureMaxValue()));
};

//---------------------------------------------------------------------------

void __fastcall TGammaAdjustmentForm::TOutputFileFrame1Button_BrowseDirClick(TObject * Sender)
{
    TOutputFileFrame1->Button_BrowseDirClick(Sender);

}

//---------------------------------------------------------------------------

void __fastcall TGammaAdjustmentForm::FormMouseMove(TObject * Sender,
						    TShiftState Shift, int X, int Y)
{
    TOutputFileFrame1->updateWarning();
}

//---------------------------------------------------------------------------

void __fastcall TGammaAdjustmentForm::FormKeyPress(TObject * Sender, char &Key)
{
    if (27 == Key) {
	//for direct gamma��, �����|����o��
	if (true == run) {
	    ShowMessage("Interrupt!");
	    if (false == MeasureWindow->Visible) {
		//Ĳ�ofetcher��window closing, �i�H����q��
		TCloseAction action = caNone;
		MainForm->getComponentFetcher()->windowClosing(Sender, action);
		MainForm->mm->setMeasureWindowsVisible(false);
	    }
	    //Button_MeaRun->Enabled = true;
	    run = false;
	} else {
	    this->Close();
	}
    }
}

//---------------------------------------------------------------------------

