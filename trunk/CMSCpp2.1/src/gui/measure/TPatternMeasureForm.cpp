//---------------------------------------------------------------------------

#include <includeall.h>
#pragma hdrstop

#include "TPatternMeasureForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TOutputFileFrame"
#pragma resource "*.dfm"
TPatternMeasureForm *PatternMeasureForm;
//---------------------------------------------------------------------------
__fastcall TPatternMeasureForm::TPatternMeasureForm(TComponent * Owner)
:TForm(Owner), linkCA210(!FileExists(DEBUG_FILE))
{
    using namespace cms::measure::meter;
    if (linkCA210) {
	meter = bptr < Meter > (new CA210());
    }
    MeasureWindow->Image1->Visible=true;
    MeasureWindow->Visible=true;
}

//---------------------------------------------------------------------------
void __fastcall TPatternMeasureForm::Button_MeasureClick(TObject * Sender)
{
    using namespace cms::util;
    using namespace cms::colorformat;

    this->TOutputFileFrame1->createDir();



    String_ptr astr = this->TOutputFileFrame1->getOutputFilename();
    string filename = astr->c_str();
    ShowMessage("Ok!");
    Util::shellExecute(filename);
}

//---------------------------------------------------------------------------

