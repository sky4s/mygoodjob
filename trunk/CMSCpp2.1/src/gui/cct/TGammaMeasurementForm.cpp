//---------------------------------------------------------------------------

#include <includeall.h>
#pragma hdrstop

//C系統文件
#include <dir.h>
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
    run = false;
}

//---------------------------------------------------------------------------
void __fastcall TGammaMeasurementForm::Button_MeasureClick(TObject * Sender)
{
    using namespace std;
    using namespace cms::util;

    MainForm->setMeterMeasurementWaitTimes();

    bool_vector_ptr rgbw(new bool_vector(4));
    (*rgbw)[0] = this->CheckBox_R->Checked;
    (*rgbw)[1] = this->CheckBox_G->Checked;
    (*rgbw)[2] = this->CheckBox_B->Checked;
    (*rgbw)[3] = this->CheckBox_W->Checked;
    bool flicker = this->CheckBox_FlickerFMA->Checked;

    if (false == (*rgbw)[0] && false == (*rgbw)[1] && false == (*rgbw)[2]
	&& false == (*rgbw)[3]) {
	ShowMessage("Select at least one color.");
	return;
    }

    String_ptr filename = this->TOutputFileFrame1->getOutputFilename();
    string stlfilename = filename->c_str();
    Util::deleteExist(stlfilename);


    try {
	MainForm->showProgress(ProgressBar1);
	if (measure(rgbw, getMeasureCondition(), flicker, stlfilename)) {
	    MainForm->stopProgress(ProgressBar1);
	    ShowMessage("Ok!");
	    Util::shellExecute(stlfilename);
	}
    }
    __finally {
	MainForm->stopProgress(ProgressBar1);
    }
}

bptr < cms::lcd::calibrate::MeasureCondition > TGammaMeasurementForm::getMeasureCondition()
{
    using namespace cms::lcd::calibrate;
    using namespace Dep;

    int start = this->Edit_StartLevel->Text.ToInt();
    int end = this->Edit_EndLevel->Text.ToInt();
    int step = this->ComboBox_LevelStep->Text.ToInt();


    bptr < MeasureCondition > condition;
    if (null == dgcodeTable) {
	if (bitDepth->isTCONInput()) {
	    start = bitDepth->getMeasureStart();
	    end = bitDepth->getMeasureEnd();
	    step = bitDepth->getMeasureStep();
	}

	condition =
	    bptr < MeasureCondition >
	    (new MeasureCondition(start, end, step, step, bitDepth->getMeasureMaxValue()));
    } else {
	int start = this->Edit_StartLevelT->Text.ToInt();
	int end = this->Edit_EndLevelT->Text.ToInt();
	RGB_vector_ptr measureTable(new RGB_vector());
	for (int x = start; x <= end; x++) {
	    measureTable->push_back((*dgcodeTable)[x]);
	}

	measureTable = RGBVector::reverse(measureTable);
	condition = bptr < MeasureCondition > (new MeasureCondition(measureTable));
    }
    return condition;
};


//---------------------------------------------------------------------------
void TGammaMeasurementForm::setBitDepthProcessor(bptr <
						 cms::lcd::calibrate::BitDepthProcessor > bitDepth)
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
bool TGammaMeasurementForm::measure(bool_vector_ptr rgbw,
				    bptr <
				    cms::lcd::calibrate::MeasureCondition >
				    measureCondition, bool flicker, const std::string & filename)
{
    using namespace Dep;
    using namespace std;
    using namespace cms::colorformat;
    using namespace cms::measure;
    using namespace cms::util;

    RampMeasureFile measureFile(filename, Create);
    Patch_vector_ptr vectors[4];
    mt = bptr < MeasureTool > (new MeasureTool(mm));
    MeasureWindow->addWindowListener(mt);

    run = true;
    try {

	foreach(const Channel & ch, *Channel::RGBWChannel) {
	    int index = ch.getArrayIndex();
	    index = (Channel::W == ch) ? 3 : index;
	    if (true == (*rgbw)[index]) {
		vectors[index] = mt->rampMeasure(ch, measureCondition);
		if (null == vectors[index]) {
		    return false;
		}
	    } else {
		vectors[index] = nil_Patch_vector_ptr;
	    }
	}
    }
    __finally {
	run = false;
    }

    measureFile.setMeasureData(vectors[3], vectors[0], vectors[1], vectors[2], false);
    measureFile.setMeasureData(vectors[3], vectors[0], vectors[1], vectors[2], true);
    measureFile.setDeltaData(vectors[3]);
    return true;
};

//---------------------------------------------------------------------------
void TGammaMeasurementForm::tconMeasure(bool_vector_ptr rgbw, int start,
					int end, int step, const std::string & filename)
{
    using namespace Dep;
    Channel_vector_ptr channels = Channel::RGBWChannel;
    //int size = channels->size();
};

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::FormShow(TObject * Sender)
{
    /*if (false == checkMeasureable()) {
       return;
       } */


    bool tconInput = bitDepth->isTCONInput();
    this->Panel2->Visible = tconInput;
    setMeasureInfo();
    fetcher = MainForm->getComponentFetcher();

#ifdef EXPERIMENT_FUNC
    CheckBox_FlickerFMA->Visible = true;
#endif
}

//---------------------------------------------------------------------------
bool TGammaMeasurementForm::checkMeasureable()
{
    bptr < cms::measure::IntensityAnalyzerIF > analyzer = MainForm->getAnalyzer();
    if (null != analyzer) {
	if (MainForm->isCA210Analyzer()) {
	    MainForm->setAnalyzerToTargetChannel();
	    return true;
	} else {
	    if (null == analyzer->getReferenceColor()) {
		ShowMessage("Set \"Target White\" first or use CA-210 Intensity Analyzer");
		return false;
	    } else {
		return true;
	    }
	}
    } else {
	return false;
    }
}

//---------------------------------------------------------------------------


void __fastcall TGammaMeasurementForm::TOutputFileFrame1Button_BrowseDirClick(TObject * Sender)
{
    TOutputFileFrame1->Button_BrowseDirClick(Sender);

}

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::Button2Click(TObject * Sender)
{
    using namespace cms::colorformat;
    using namespace cms::util;
    using namespace Dep;
    OpenDialog1->Filter = "Gamma Table Files(*.xls)|*.xls";
    string currDir = Util::getCurrentDirectory();

    //OpenDialog1->InitialDir = currDir;
    if (OpenDialog1->Execute()) {
	const AnsiString & filename = OpenDialog1->FileName;
	const MaxValue & maxValue =
	    RadioButton_12Bit->Checked ? MaxValue::Int12Bit : MaxValue::Int10Bit;
	DGLutFile dgcode(filename.c_str(), ReadOnly, maxValue);
	//dgcodeTable = RGBVector::reverse(dgcode.getGammaTable());
	dgcodeTable = dgcode.getGammaTable();
	this->CheckBox_Loaded->Checked = true;
	this->CheckBox_Loaded->Enabled = true;

	int size = dgcodeTable->size();
	Edit_Count->Text = size;
	Edit_EndLevelT->Text = size - 1;

	chdir(currDir.c_str());
    }
}

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::FormKeyPress(TObject * Sender, char &Key)
{
    if (27 == Key) {
	if (true == run) {
	    ShowMessage("Interrupt!");
	    if (false == MeasureWindow->Visible) {
		MainForm->getComponentFetcher()->windowClosing(Sender, caNone);
	    }
	    if (null != mt) {
		mt->windowClosing(Sender, caNone);
	    }
	    run = false;
	} else {
	    this->Close();
	}
    }
}

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::CheckBox_LoadedClick(TObject * Sender)
{
    if (false == CheckBox_Loaded->Checked) {
	this->CheckBox_Loaded->Enabled = false;
	dgcodeTable.reset();
    }
}

//---------------------------------------------------------------------------

