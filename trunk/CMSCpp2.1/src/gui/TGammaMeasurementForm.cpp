//---------------------------------------------------------------------------

#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TGammaMeasurementForm.h"
#include "TMainForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TOutputFileFrame"
#pragma resource "*.dfm"
TGammaMeasurementForm *GammaMeasurementForm;
//---------------------------------------------------------------------------
__fastcall TGammaMeasurementForm::TGammaMeasurementForm(TComponent * Owner)
:TForm(Owner), mm(MainForm->mm), fetcher(MainForm->getComponentFetcher())
{
}

//---------------------------------------------------------------------------
void __fastcall TGammaMeasurementForm::Button_MeasureClick(TObject *
							   Sender)
{
    using namespace std;
    using namespace cms::util;
    MainForm->getAnalyzer();
    MainForm->setAnalyzerToTargetChannel();
    MainForm->setMeterMeasurementWaitTimes();

    bool_vector_ptr rgbw(new bool_vector(4));
    (*rgbw)[0] = this->CheckBox_R->Checked;
    (*rgbw)[1] = this->CheckBox_G->Checked;
    (*rgbw)[2] = this->CheckBox_B->Checked;
    (*rgbw)[3] = this->CheckBox_W->Checked;

    if (false == (*rgbw)[0] && false == (*rgbw)[1] && false == (*rgbw)[2]
	&& false == (*rgbw)[3]) {
	ShowMessage("Select at least one color.");
	return;
    }


    int start = this->Edit_StartLevel->Text.ToInt();
    int end = this->Edit_EndLevel->Text.ToInt();
    int step = this->ComboBox_LevelStep->Text.ToInt();
    String_ptr filename = this->TOutputFileFrame1->getOutputFilename();
    string stlstring = filename->c_str();
    Util::deleteExist(stlstring);

    if (bitDepth->isTCONInput()) {
	//tconMeasure(rgbw, start, end, step);

    } else {
	pcMeasure(rgbw, start, end, step, stlstring);
    }
}


//---------------------------------------------------------------------------
void TGammaMeasurementForm::setBitDepthProcessor(bptr <
						 cms::lcd::calibrate::
						 BitDepthProcessor >
						 bitDepth)
{
    this->bitDepth = bitDepth;
}

//---------------------------------------------------------------------------


void TGammaMeasurementForm::setMeasureInfo()
{
    using namespace cms::util;
    int start = bitDepth->getMeasureStart();
    int step = bitDepth->getMeasureStep();
    this->Edit_StartLevel->Text = Util::toString(start).c_str();
    this->ComboBox_LevelStep->Text = Util::toString(step).c_str();
};

//---------------------------------------------------------------------------
void TGammaMeasurementForm::pcMeasure(bool_vector_ptr rgbw, int start,
				      int end, int step,
				      const std::string & filename)
{
    using namespace Dep;
    using namespace std;
    using namespace cms::colorformat;
    using namespace cms::measure;
    Channel_vector_ptr channels = Channel::RGBChannel;
    Patch_vector_ptr vectors[3];

    Component_vector_ptr componentVector =
	(true == (*rgbw)[3]) ?
	fetcher->fetchComponent(start, end, step, step) :
	Component_vector_ptr((Component_vector *) null);

    MeasureTool mt(mm);

    foreach(const Channel & ch, *channels) {
	int index = ch.getArrayIndex();
	if (true == (*rgbw)[index]) {
	    vectors[index] = mt.rampMeasure(ch, start, end, step);
	} else {
	    vectors[index] = nil_Patch_vector_ptr;
	}
    }

    RampMeasureFile measureFile(filename, Create);
    measureFile.setMeasureData(componentVector, vectors[0], vectors[1],
			       vectors[2]);
};

//---------------------------------------------------------------------------
void TGammaMeasurementForm::tconMeasure(bool_vector_ptr rgbw, int start,
					int end, int step,
					const std::string & filename)
{
    using namespace Dep;
    Channel_vector_ptr channels = Channel::RGBWChannel;
    int size = channels->size();
};

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::FormShow(TObject * Sender)
{
//bitDepth->
    bool tconInput = bitDepth->isTCONInput();
    this->Panel2->Visible = tconInput;
    setMeasureInfo();
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

