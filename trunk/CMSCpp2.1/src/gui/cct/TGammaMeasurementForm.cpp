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
    if (MainForm->isCA210Analyzer()) {
	MainForm->setAnalyzerToTargetChannel();
    }
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

    String_ptr filename = this->TOutputFileFrame1->getOutputFilename();
    string stlfilename = filename->c_str();
    Util::deleteExist(stlfilename);

    measure(rgbw, getMeasureCondition(), stlfilename);
    Util::shellExecute(stlfilename);
}

bptr < cms::lcd::calibrate::MeasureCondition >
    TGammaMeasurementForm::getMeasureCondition()
{
    using namespace cms::lcd::calibrate;

    int start = this->Edit_StartLevel->Text.ToInt();
    int end = this->Edit_EndLevel->Text.ToInt();
    int step = this->ComboBox_LevelStep->Text.ToInt();

    if (bitDepth->isTCONInput()) {
	start = bitDepth->getMeasureStart();
	end = 0;
	step = bitDepth->getMeasureStep();
    }
    bptr < MeasureCondition > condition;
    if (null == dgcodeTable) {
	condition = bptr < MeasureCondition > (new
					       MeasureCondition(start, end,
								step,
								step));
    } else {
	condition = bptr < MeasureCondition > (new
					       MeasureCondition
					       (dgcodeTable));
    }
    return condition;
};


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
void TGammaMeasurementForm::measure(bool_vector_ptr rgbw,
				    bptr <
				    cms::lcd::calibrate::MeasureCondition >
				    measureCondition,
				    const std::string & filename)
{
    using namespace Dep;
    using namespace std;
    using namespace cms::colorformat;
    using namespace cms::measure;
    using namespace cms::util;

    Patch_vector_ptr vectors[3];

    Component_vector_ptr componentVector =
	(true == (*rgbw)[3]) ?
	fetcher->fetchComponent(measureCondition) :
	Component_vector_ptr((Component_vector *) null);
    if (true == (*rgbw)[3] && null == componentVector) {
	//代表被阻斷量測
	return;
    }

    bptr < MeasureTool > mt(new MeasureTool(mm));
    MeasureWindow->addWindowListener(mt);
    foreach(const Channel & ch, *Channel::RGBChannel) {
	int index = ch.getArrayIndex();
	if (true == (*rgbw)[index]) {
	    vectors[index] = mt->rampMeasure(ch, measureCondition);
	    if (null == vectors[index]) {
		return;
	    }
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
    //int size = channels->size();
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


void __fastcall TGammaMeasurementForm::
TOutputFileFrame1Button_BrowseDirClick(TObject * Sender)
{
    TOutputFileFrame1->Button_BrowseDirClick(Sender);

}

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::Button2Click(TObject * Sender)
{
    using namespace cms::colorformat;
    using namespace cms::util;
    OpenDialog1->Filter = "Gamma Table Files(*.xls)|*.xls";
    if (OpenDialog1->Execute()) {
	const AnsiString & filename = OpenDialog1->FileName;
	DGLutFile dgcode(filename.c_str(), ReadOnly);
	dgcodeTable = RGBVector::reverse(dgcode.getGammaTable());
	this->CheckBox_Loaded->Checked = true;
	this->CheckBox_Loaded->Enabled = true;
    }
}

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::FormKeyPress(TObject * Sender,
						    char &Key)
{
    if (Key == 27) {		//esc
	this->Close();
    }
}

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::CheckBox_LoadedClick(TObject *
							    Sender)
{
    if (false == CheckBox_Loaded->Checked) {
	this->CheckBox_Loaded->Enabled = false;
	dgcodeTable.reset();
    }
}

//---------------------------------------------------------------------------

