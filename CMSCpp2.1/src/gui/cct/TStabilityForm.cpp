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
    using namespace cms::util;
    //bptr < cms::measure::MeasureTool > mt(new cms::measure::MeasureTool(mm));
    Button1->Enabled = false;

    //mm->WaitTimes = 0;
    mm->BlankTimes = Edit_Blank->Text.ToInt();
    //mm->BlankTimes = 17;
    //mm->BlankRGB =Dep::RGBColor::Black;
    //mm->BlankRGB = RGBColor::White;
    //int AGGrayLevel[] = { 0, 32, 64, 96, 128, 160, 192, 224 };
    MeasureWindow->setVisible(true);
    /*for (int grayLevel = 0; grayLevel <=255; grayLevel+=16) {
       //int grayLevel = AGGrayLevel[x];

       MeasureWindow->setRGB(4080,4080,4080);
       Util::sleep(34);
       for (int t = 0; t < 20; t++) {
       mm->measure(grayLevel, grayLevel, grayLevel, nil_string_ptr);
       Util::sleep(100);
       }
       } */
    run = true;
    int grayLevel = Edit_Start->Text.ToInt();
    int step = Edit_Step->Text.ToInt();
    int count = Edit_Count->Text.ToInt();
    int waitTimes = Edit_WaitTime->Text.ToInt();
    mm->WaitTimes = waitTimes;
    for (; grayLevel > 0; grayLevel -= step) {
	//int grayLevel = AGGrayLevel[x];
	for (int t = 0; t < count; t++) {
	    if (null != dgcodeTable) {
		RGB_ptr rgb = (*dgcodeTable)[grayLevel];
		mm->measure(rgb, nil_string_ptr);
	    } else {
		mm->measure(grayLevel, grayLevel, grayLevel, nil_string_ptr);
	    }


	    //Util::sleep(sleep);
	    if (false == run) {
		break;
	    }
	}
	if (false == run) {
	    break;
	}
    }
    run = false;


    storeMeasurePatchVector();
    mm->setMeasureWindowsVisible(false);

    Button1->Enabled = true;
}


void TStabilityForm::storeMeasurePatchVector()
{
    using namespace cms::colorformat;
    using namespace cms::util;
    Patch_vector_ptr measurePatchVector = mm->MeasurePatchVector;
    if (null != measurePatchVector && measurePatchVector->size() != 0) {
	Util::deleteExist("stability.xls");
	bptr < DGLutFile > dglutFile(new DGLutFile("stability.xls", Create));
	dglutFile->setMeasure(measurePatchVector);
	dglutFile.reset();
	mm->resetMeasurePatchVector();
    }
};

//---------------------------------------------------------------------------

void __fastcall TStabilityForm::FormKeyPress(TObject * Sender, char &Key)
{
    if (27 == Key) {
	run = false;
    }
}

//---------------------------------------------------------------------------


void __fastcall TStabilityForm::Button3Click(TObject * Sender)
{
    using namespace cms::colorformat;
    using namespace cms::util;
    using namespace Dep;
    OpenDialog1->Filter = "Gamma Table Files(*.xls)|*.xls";
    string currDir = Util::getCurrentDirectory();

    //OpenDialog1->InitialDir = currDir;
    if (OpenDialog1->Execute()) {
	const AnsiString & filename = OpenDialog1->FileName;

	DGLutFile dgcode(filename.c_str(), ReadOnly, MaxValue::Int12Bit);
	//dgcodeTable = RGBVector::reverse(dgcode.getGammaTable());
	dgcodeTable = dgcode.getGammaTable();

    }
}

//---------------------------------------------------------------------------
bptr < cms::colorformat::DGLutFile > stabilityDGLutFile;
void __fastcall TStabilityForm::Button_ContinueMeasureClick(TObject * Sender)
{
    using namespace cms::colorformat;
    using namespace cms::util;
    using namespace cms::measure;
    if (false == run) {
	Button_ContinueMeasure->Caption = "Stop Measure";
	run = true;
	mm->WaitTimes = 0;
	int waitTimes = Edit_WaitTime->Text.ToInt();;
	bool flicker = CheckBox_Flicker->Checked;
	bool jeita = CheckBox_JEITA->Checked;
	mm->Flicker = jeita ? FlickerMode::JEITA : FlickerMode::FMA;

	Util::deleteExist("stability.xls");
	stabilityDGLutFile = bptr < DGLutFile > (new DGLutFile("stability.xls", Create));

	while (true) {
	    Util::sleep(waitTimes);
	    Patch_ptr XYZPatch = mm->measure(nil_string_ptr);
	    stabilityDGLutFile->addMeasure(XYZPatch);
	    if (flicker) {
		Patch_ptr flickerPatch = mm->measureFlicker(nil_string_ptr);
		stabilityDGLutFile->addMeasure(flickerPatch);
	    }
	    Application->ProcessMessages();
	    if (false == run) {
		break;
	    }
	    Application->ProcessMessages();
	}


    } else {
	Button_ContinueMeasure->Caption = "Continue Measure";
	run = false;
	mm->WaitTimes = Edit_WaitTime->Text.ToInt();

	stabilityDGLutFile.reset();
	stabilityDGLutFile = bptr < DGLutFile > ((DGLutFile *) null);

	/*Patch_vector_ptr measurePatchVector = mm->MeasurePatchVector;
	   if (null != measurePatchVector && measurePatchVector->size() != 0) {
	   Util::deleteExist("stability.xls");
	   bptr < DGLutFile > dglutFile(new DGLutFile("stability.xls", Create));
	   dglutFile->setMeasure(measurePatchVector);
	   dglutFile.reset();
	   } */
    }
}

//---------------------------------------------------------------------------

void __fastcall TStabilityForm::Button4Click(TObject * Sender)
{
    if (null == dgcodeTable) {
	return;
    }
    Button4->Enabled = false;
    MeasureWindow->setVisible(true);
    run = true;
    int grayLevel = 255;
    int step = 1;
    int waitTimes = Edit_WaitTime->Text.ToInt();
    mm->WaitTimes = waitTimes;
    for (; grayLevel > 0; grayLevel -= step) {
	if (null != dgcodeTable) {
	    RGB_ptr rgb = (*dgcodeTable)[grayLevel];
	    mm->measure(rgb, nil_string_ptr);
	    RGB_ptr rgb1 = rgb->clone();

	    rgb1->changeMaxValue(Dep::MaxValue::Int11Bit);
	    rgb1->R += 1;
	    mm->measure(rgb1, nil_string_ptr);

	    rgb1 = rgb->clone();
	    rgb1->changeMaxValue(Dep::MaxValue::Int11Bit);
	    rgb1->G += 1;
	    mm->measure(rgb1, nil_string_ptr);

	    rgb1 = rgb->clone();
	    rgb1->changeMaxValue(Dep::MaxValue::Int11Bit);
	    rgb1->B += 1;
	    mm->measure(rgb1, nil_string_ptr);


	}


	if (false == run) {
	    break;
	}
    }
    run = false;


    storeMeasurePatchVector();
    mm->setMeasureWindowsVisible(false);

    Button4->Enabled = true;
}

//---------------------------------------------------------------------------

