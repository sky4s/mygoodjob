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
    run = false;
}

//---------------------------------------------------------------------------
void __fastcall TGammaMeasurementForm::Button_MeasureClick(TObject * Sender)
{
    using namespace std;
    using namespace cms::util;
    /*bptr < cms::measure::IntensityAnalyzerIF > analyzer = MainForm->getAnalyzer();
       if (MainForm->isCA210Analyzer()) {
       MainForm->setAnalyzerToTargetChannel();
       } else {
       if (null == analyzer->getReferenceColor()) {
       ShowMessage("Set \"Target White\" first or use CA-210 Intensity Analyzer");
       return;
       }
       } */
    if (false == checkMeasureable()) {
	return;
    }
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

    if (measure(rgbw, getMeasureCondition(), flicker, stlfilename)) {
	ShowMessage("Ok!");
	Util::shellExecute(stlfilename);
    }
}

bptr < cms::lcd::calibrate::MeasureCondition > TGammaMeasurementForm::getMeasureCondition()
{
    using namespace cms::lcd::calibrate;
    using namespace Dep;

    int start = this->Edit_StartLevel->Text.ToInt();
    int end = this->Edit_EndLevel->Text.ToInt();
    int step = this->ComboBox_LevelStep->Text.ToInt();

    if (bitDepth->isTCONInput()) {
	start = bitDepth->getMeasureStart();
	end = bitDepth->getMeasureEnd();
	step = bitDepth->getMeasureStep();
    }
    bptr < MeasureCondition > condition;
    if (null == dgcodeTable) {
	condition =
	    bptr < MeasureCondition >
	    (new MeasureCondition(start, end, step, step, bitDepth->getMeasureMaxValue()));
    } else {
	condition = bptr < MeasureCondition > (new MeasureCondition(dgcodeTable));
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
    Patch_vector_ptr vectors[3];
    mt = bptr < MeasureTool > (new MeasureTool(mm));
    MeasureWindow->addWindowListener(mt);
    Component_vector_ptr componentVector;

    run = true;
    try {
	componentVector =
	    (true == (*rgbw)[3]) ?
	    (flicker ? mt->flickerMeasure(measureCondition) : fetcher->
	     fetchComponent(measureCondition)) : nil_Component_vector_ptr;
	if (true == (*rgbw)[3] && null == componentVector) {
	    //代表被阻斷量測
	    return false;
	}

	foreach(const Channel & ch, *Channel::RGBChannel) {
	    int index = ch.getArrayIndex();
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

    measureFile.setMeasureData(componentVector, vectors[0], vectors[1], vectors[2], false);
    measureFile.setMeasureData(componentVector, vectors[0], vectors[1], vectors[2], true);
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
    if (false == checkMeasureable()) {
	return;
    }


    bool tconInput = bitDepth->isTCONInput();
    this->Panel2->Visible = tconInput;
    setMeasureInfo();
    fetcher = MainForm->getComponentFetcher();
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
	    }
	}
    }
    return false;
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
    if (OpenDialog1->Execute()) {
	const AnsiString & filename = OpenDialog1->FileName;
	const MaxValue & maxValue =
	    RadioButton_12Bit->Checked ? MaxValue::Int12Bit : MaxValue::Int10Bit;
	DGLutFile dgcode(filename.c_str(), ReadOnly, maxValue);
	dgcodeTable = RGBVector::reverse(dgcode.getGammaTable());
	this->CheckBox_Loaded->Checked = true;
	this->CheckBox_Loaded->Enabled = true;
    }
}

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::FormKeyPress(TObject * Sender, char &Key)
{
    if (27 == Key) {
	if (true == run) {
	    ShowMessage("Interrupt!");
	    if (false == MeasureWindow->Visible) {
		MainForm->getComponentFetcher()->windowClosing();
	    }
	    if (null != mt) {
		mt->windowClosing();
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

