//---------------------------------------------------------------------------
#include <includeall.h>
//#include <vcl.h>
#pragma hdrstop

#include "TStabilityForm.h"
#include "TMainForm.h"


//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TStabilityForm *StabilityForm;
//---------------------------------------------------------------------------
__fastcall TStabilityForm::TStabilityForm(TComponent * Owner)
:TForm(Owner), mm(MainForm->mm)
{
}

//---------------------------------------------------------------------------
void __fastcall TStabilityForm::Button1Click(TObject * Sender)
{
    /*
       要可以量測出以下幾種條件
       1. idle time的影響 400~1000
       2. insert blank的影響
     */
    using namespace cms::colorformat;
    //bptr < cms::measure::MeasureTool > mt(new cms::measure::MeasureTool(mm));
    bptr < DGLutFile > dglutFile(new DGLutFile("stability.xls", Create));
    Patch_vector_ptr measurePatchVector = mm->MeasurePatchVector;
    if (null != measurePatchVector && measurePatchVector->size() != 0) {
	dglutFile->setMeasure(measurePatchVector);
    }
    dgLutFile.reset();
}

//---------------------------------------------------------------------------

