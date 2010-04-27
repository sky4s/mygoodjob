//---------------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop

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



