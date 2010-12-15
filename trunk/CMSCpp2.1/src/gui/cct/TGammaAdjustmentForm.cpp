//---------------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop

//C╰参ゅン

//C++╰参ゅン

//ㄤ畐繷ゅン

//セ兜ヘず繷ゅン
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
						cms::lcd::calibrate::BitDepthProcessor > bitDepth)
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
	} else {
	    ShowMessage("Desired Gamma File Format is wrong!");
	    this->CheckBox_LoadingGamma->Checked = false;
	    this->CheckBox_LoadingGamma->Enabled = false;
	}
    }
}

//---------------------------------------------------------------------------

void __fastcall TGammaAdjustmentForm::CheckBox_LoadingGammaClick(TObject * Sender)
{
    using namespace cms::util;
    if (false == this->CheckBox_LoadingGamma->Checked) {
	this->CheckBox_LoadingGamma->Enabled = false;
	rgbGamma = RGBGamma_ptr((RGBGamma *) null);
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
    //int step = this->ComboBox_LevelStep->Text.ToInt();
    //==========================================================================
    // gamma矪瞶
    //==========================================================================
    if (rgbGammaAdjust) {
	if (this->CheckBox_LoadingGamma->Checked) {
	    //更gamma
	    double_vector_ptr rgammaCurve = rgbGamma->r;
	    double_vector_ptr ggammaCurve = rgbGamma->g;
	    double_vector_ptr bgammaCurve = rgbGamma->b;
	    calibrator->setGammaCurve(rgammaCurve, ggammaCurve, bgammaCurve);
	} else {
	    //rgb gammaだ秨砞﹚
	    double rgamma = this->ComboBox_RGamma->Text.ToDouble();
	    double ggamma = this->ComboBox_GGamma->Text.ToDouble();
	    double bgamma = this->ComboBox_BGamma->Text.ToDouble();
	    calibrator->setGamma(rgamma, ggamma, bgamma);
	}

    } else {
	if (this->CheckBox_LoadingGamma->Checked) {
	    //更gamma
	    double_vector_ptr gammaCurve = rgbGamma->w;
	    calibrator->setGammaCurve(gammaCurve);
	} else {
	    double gamma = this->ComboBox_GrayGamma->Text.ToDouble();
	    calibrator->setGamma(gamma);
	}
    }
    //==========================================================================
    calibrator->setAvoidFRCNoise(this->CheckBox_AvoidNoise->Checked);
    calibrator->setKeepMaxLuminance(this->CheckBox_KeepMax->Checked);

    if (this->TOutputFileFrame1->createDir() == false) {
	return;
    }
    RGB_vector_ptr dglut = calibrator->getGammaDGLut(getMeasureCondition());
    if (dglut == null) {
	return;
    }
    String_ptr astr = this->TOutputFileFrame1->getOutputFilename();
    string filename = astr->c_str();
    calibrator->storeDGLutFile(filename, dglut);
    ShowMessage("Ok!");
    Util::shellExecute(filename);
};


bptr < cms::lcd::calibrate::MeasureCondition > TGammaAdjustmentForm::getMeasureCondition()
{
    using namespace cms::lcd::calibrate;
    int start = bitDepth->getMeasureStart();
    int end = bitDepth->getMeasureEnd();
    int step = this->ComboBox_LevelStep->Text.ToInt();

    //箇砞材顶
    int firstStep = (bitDepth->getMeasureStep() != step) ? step : bitDepth->getMeasureFirstStep();

    return bptr < MeasureCondition >
	(new MeasureCondition(start, end, firstStep, step, bitDepth->getMeasureMaxValue()));
};

//---------------------------------------------------------------------------

