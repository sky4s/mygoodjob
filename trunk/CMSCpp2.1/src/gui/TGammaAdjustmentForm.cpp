//---------------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
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
void TGammaAdjustmentForm::setBitDepthProcessor(bptr <
						cms::lcd::calibrate::
						BitDepthProcessor >
						bitDepth)
{
    this->bitDepth = bitDepth;
}

//---------------------------------------------------------------------------


void __fastcall TGammaAdjustmentForm::FormShow(TObject * Sender)
{
    using namespace cms::util;
    using namespace Dep;
    int step = bitDepth->getMeasureStep();
    this->ComboBox_LevelStep->Text = Util::toString(step).c_str();

    const MaxValue & input = bitDepth->getInputMaxValue();
    bool avoidNoise = (input == MaxValue::Int6Bit
		       || input == MaxValue::Int8Bit);
    this->CheckBox_AvoidNoise->Enabled = avoidNoise;
}

//---------------------------------------------------------------------------




void __fastcall TGammaAdjustmentForm::Button3Click(TObject * Sender)
{
    using namespace cms::util;
    OpenDialog1->Filter = "Desired Gamma Files(*.xls)|*.xls";
    if (OpenDialog1->Execute()) {
	const AnsiString & filename = OpenDialog1->FileName;
	rgbGamma = RGBGamma::loadFromDesiredGamma(filename.c_str());
	unsigned int n = bitDepth->getLevel();
	if (rgbGamma != null && rgbGamma->w->size() == n) {
	    this->CheckBox_LoadingGamma->Checked = true;
	    this->CheckBox_LoadingGamma->Enabled = true;
	    return;
	} else {
	    ShowMessage("Desired Gamma File Format is wrong!");
	}
    }
}

//---------------------------------------------------------------------------

void __fastcall TGammaAdjustmentForm::CheckBox_LoadingGammaClick(TObject *
								 Sender)
{
    using namespace cms::util;
    if (false == this->CheckBox_LoadingGamma->Checked) {
	this->CheckBox_LoadingGamma->Enabled = false;
	rgbGamma = RGBGamma_ptr((RGBGamma *) null);
    }
}

//---------------------------------------------------------------------------


void __fastcall TGammaAdjustmentForm::Button_GrayGammaClick(TObject *
							    Sender)
{
    gammaAdjust(false);
}

//---------------------------------------------------------------------------

void __fastcall TGammaAdjustmentForm::Button_RGBGammaClick(TObject *
							   Sender)
{
    gammaAdjust(true);
}

//---------------------------------------------------------------------------

void TGammaAdjustmentForm::gammaAdjust(bool rgbGammaAdjust)
{
    using namespace std;
    int step = this->ComboBox_LevelStep->Text.ToInt();
    //==========================================================================
    // gamma的處理
    //==========================================================================
    if (this->CheckBox_LoadingGamma->Checked) {
	double_vector_ptr gammaCurve = rgbGamma->w;
	calibrator->setGammaCurve(gammaCurve);
    } else if (rgbGammaAdjust) {
	double rgamma = this->ComboBox_RGamma->Text.ToDouble();
	double ggamma = this->ComboBox_GGamma->Text.ToDouble();
	double bgamma = this->ComboBox_BGamma->Text.ToDouble();
	calibrator->setGamma(rgamma, ggamma, bgamma);
    } else {
	double gamma = this->ComboBox_GrayGamma->Text.ToDouble();
	calibrator->setGamma(gamma);
    }
    //==========================================================================
    calibrator->setAvoidFRCNoise(this->CheckBox_AvoidNoise->Checked);
    calibrator->setKeepMaxLuminance(this->CheckBox_KeepMax->Checked);

    this->TOutputFileFrame1->createDir();
    RGB_vector_ptr dglut = calibrator->getGammaDGLut(step);
    if (dglut == null) {
	return;
    }
    String_ptr astr = this->TOutputFileFrame1->getOutputFilename();
    string filename = astr->c_str();
    calibrator->storeDGLut(filename, dglut);
    ShowMessage("Ok!");
};

//---------------------------------------------------------------------------

void __fastcall TGammaAdjustmentForm::FormCreate(TObject * Sender)
{
    using namespace cms::lcd::calibrate;

    calibrator = bptr < LCDCalibrator > (new
					 LCDCalibrator(MainForm->
						       getComponentFetcher
						       (), bitDepth));
}

//---------------------------------------------------------------------------

