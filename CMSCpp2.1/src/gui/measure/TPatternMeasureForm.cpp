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
    /*MeasureWindow->Image1->Visible = true;
       MeasureWindow->Visible = true; */
}

//---------------------------------------------------------------------------
void __fastcall TPatternMeasureForm::Button_MeasureClick(TObject * Sender)
{
    using namespace cms::util;
    using namespace cms::colorformat;
    using namespace Indep;

    this->TOutputFileFrame1->createDir();
    XYZ_vector_ptr XYZVector(new XYZ_vector());
    AnsiString s;
    int waitTimes = Edit_Interval->Text.ToInt();
    MeasureWindow->Visible = true;

    for (int x = 0; x < 999; x++) {
	AnsiString filename =
	    s.sprintf("%03d.", x) + ComboBox_FileFormat->Text;
	bool fileExist = FileExists(filename);
	if (fileExist) {
	    MeasureWindow->setImageFilename(filename.c_str());
	    Application->ProcessMessages();
	    Sleep(waitTimes);
	    if (linkCA210) {
		double_array XYZValues = meter->triggerMeasurementInXYZ();
		XYZ_ptr XYZ(new Indep::CIEXYZ(XYZValues));
		XYZVector->push_back(XYZ);
	    } else {
		XYZ_ptr XYZ(new Indep::CIEXYZ(1, 2, 3));
		XYZVector->push_back(XYZ);
	    }
	} else {
	    break;
	}
    }
    MeasureWindow->Visible = false;


    String_ptr astr = this->TOutputFileFrame1->getOutputFilename();
    string filename = astr->c_str();
    Util::storeXYZxyVector(filename, XYZVector, "no");
    ShowMessage("Ok!");
    Util::shellExecute(filename);
}

//---------------------------------------------------------------------------

