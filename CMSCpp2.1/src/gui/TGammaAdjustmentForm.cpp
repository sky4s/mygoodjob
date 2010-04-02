//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TGammaAdjustmentForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TOptionsFrame"
#pragma link "TOutputFileFrame"
#pragma resource "*.dfm"
TGammaAdjustmentForm *GammaAdjustmentForm;
//---------------------------------------------------------------------------
__fastcall TGammaAdjustmentForm::TGammaAdjustmentForm(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
