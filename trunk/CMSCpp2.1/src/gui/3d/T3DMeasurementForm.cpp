//---------------------------------------------------------------------------

#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件


//其他庫頭文件
#include <math.hpp>

//本項目內頭文件
#include "T3DMeasurementForm.h"
#include "T3DMeasureWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TOutputFileFrame"
#pragma resource "*.dfm"
TThreeDMeasurementForm *ThreeDMeasurementForm;
//---------------------------------------------------------------------------
__fastcall TThreeDMeasurementForm::TThreeDMeasurementForm(TComponent * Owner)
:TForm(Owner), linkCA210(!FileExists(DEBUG_FILE)), stop(false), dynamicMode(false),
whiteFont(false), talkABreak(false)
{
    using namespace cms::util;
    fieldNames =
	StringVector::fromCString(18, "Target", "0", "16", "32", "48",
				  "64", "80", "96", "112", "128", "144",
				  "160", "176", "192", "208", "224", "240", "255");
}

//---------------------------------------------------------------------------



void __fastcall TThreeDMeasurementForm::Button_MeasureClick(TObject * Sender)
{
    using namespace Dep;
    using namespace cms::util;
    using namespace cms::colorformat;
    using namespace ca210api;



    bool_vector_ptr rgbw(new bool_vector(7));
    (*rgbw)[0] = this->CheckBox_R->Checked;
    (*rgbw)[1] = this->CheckBox_G->Checked;
    (*rgbw)[2] = this->CheckBox_B->Checked;
    (*rgbw)[3] = false;
    (*rgbw)[4] = false;
    (*rgbw)[5] = false;
    (*rgbw)[6] = this->CheckBox_W->Checked;

    if (false == (*rgbw)[0] && false == (*rgbw)[1] && false == (*rgbw)[2]
	&& false == (*rgbw)[6]) {
	ShowMessage("Select at least one color.");
	return;
    }

    bool leftrightChange = this->CheckBox_LeftRightChange->Checked;
    int idleTime = this->Edit_IdleTime->Text.ToInt();
    int aveTimes = this->Edit_AveTimes->Text.ToInt();
    bool stableTest = this->CheckBox_StableTest->Checked;


    if (true == stableTest && true == linkCA210) {
	int index = this->ComboBox_MeasureMode->ItemIndex;
	bptr < ca210api::CA210API > ca210api = ca210->getCA210API();
	switch (index) {
	case 0:
	    ca210api->setAveragingMode(Auto);
	    break;
	case 1:
	    ca210api->setAveragingMode(Fast);
	    break;
	}
    }

    string filename = this->OutputFileFrame1->getOutputFilename()->c_str();
    Util::deleteExist(filename);
    bptr < ExcelAccessBase > excel(new ExcelAccessBase(filename, Create));

    foreach(const Channel & ch, *Channel::RGBWChannel) {
	if (true == (*rgbw)[ch.getArrayIndex()]) {
	    double2D_ptr result = ODMeasure(ch, idleTime, aveTimes, leftrightChange,
					    stableTest);
	    if (null == result) {
		return;
	    }
	    string measureSheet = *ch.toString() + "_Measure";
	    excel->initSheet(measureSheet, fieldNames);
	    storeResult(measureSheet, result, excel);

	    string xtalkSheet = *ch.toString() + "_Xtalk";
	    excel->initSheet(xtalkSheet, fieldNames);
	    double2D_ptr xtalkresult = crosstalk(result);
	    storeResult(xtalkSheet, xtalkresult, excel);
	}
    }
    ShowMessage("Measure complete.");
    excel.reset();		//釋放掉excel, 就可以釋放掉檔案的控制權
    Util::shellExecute(filename);
}

//---------------------------------------------------------------------------
double TThreeDMeasurementForm::patternMeasure(RGB_ptr left, RGB_ptr right,
					      int idleTime, int aveTimes, bool leftrightChange)
{
    double_vector_ptr result = patternMeasure0(left, right, idleTime, aveTimes, leftrightChange);
    if (null != result) {
	return getMeanLuminance(result);
    } else {
	return -1;
    }
};

double_vector_ptr TThreeDMeasurementForm::patternMeasure0(RGB_ptr left,
							  RGB_ptr right,
							  int idleTime,
							  int aveTimes, bool leftrightChange)
{
    if (!leftrightChange) {
	ThreeDMeasureWindow->setLeftRGB(left);
	ThreeDMeasureWindow->setRightRGB(right);
    } else {
	ThreeDMeasureWindow->setLeftRGB(right);
	ThreeDMeasureWindow->setRightRGB(left);
    }

    ThreeDMeasureWindow->Visible = true;
    Application->ProcessMessages();

    Sleep(idleTime);
    try {
	if (true == stop) {
	    return double_vector_ptr((double_vector *) null);
	}

	double_vector_ptr result(new double_vector());
	for (int x = 0; x < aveTimes; x++) {
	    if (true == stop) {
		return double_vector_ptr((double_vector *) null);
	    }
	    double Y = 0;
	    if (true == linkCA210) {
		Y = ca210->triggerMeasurementInXYZ()[1];
	    } else {
		Y = 1;
	    }
	    result->push_back(Y);
	}
	return result;

    }
    __finally {
	stop = false;
    }
    return nil_double_vector_ptr;
};

double2D_ptr TThreeDMeasurementForm::ODMeasure(const Dep::Channel & ch,
					       int idleTime,
					       int aveTimes, bool leftrightChange, bool stableTest)
{
    using namespace Dep;
    using namespace math;
    using namespace cms::colorformat;
    using namespace cms::util;

    double2D_ptr result(new double2D(17, 17));
    bptr < ExcelAccessBase > excel;
    string_vector_ptr fieldNames = StringVector::fromCString(18, "number", "0", "16", "32", "48",
							     "64", "80", "96", "112", "128", "144",
							     "160", "176", "192", "208", "224",
							     "240",
							     "255");

    if (true == stableTest) {
	string filename = *ch.toString() + "_stableTest.xls";
	Util::deleteExist(filename);
	excel = bptr < ExcelAccessBase > (new ExcelAccessBase(filename, Create));
    }
    stop = false;
    try {
	for (int x = 0; x < 17; x++) {
	  std:vector < double_vector_ptr > vec;
	    for (int y = 0; y < 17; y++) {
		//==================================================================
		// rgb prepare
		//==================================================================
		int l = 16 * x;
		int r = 16 * y;
		l = l > 255 ? 255 : l;
		r = r > 255 ? 255 : r;
		RGB_ptr rrgb(new RGBColor(MaxValue::Double255));
		RGB_ptr lrgb(new RGBColor(MaxValue::Double255));
		rrgb->setValue(ch, r);
		lrgb->setValue(ch, l);
		//==================================================================
		double_vector_ptr measureResult = patternMeasure0(lrgb, rrgb, idleTime, aveTimes,
								  leftrightChange);
		if (true == stableTest) {
		    vec.push_back(measureResult);
		}
		double meanY = getMeanLuminance(measureResult);
		if (true == stop) {
		    return double2D_ptr((double2D *) null);
		}
		(*result)[x][y] = meanY;
	    }

	    if (true == stableTest) {
		int sheetNum = x * 16;
		sheetNum = sheetNum >= 255 ? 255 : sheetNum;
		string sheetName = _toString(sheetNum);
		excel->initSheet(sheetName, fieldNames);

		for (int m = 0; m < aveTimes; m++) {
		    string_vector_ptr values(new string_vector());
		    values->push_back(_toString(m + 1));
		    for (int n = 0; n < 17; n++) {
			double v = (*vec[n])[m];
			values->push_back(_toString(v));
		    }
		    excel->insertData(sheetName, values, false);
		}
	    }
	}

	result = DoubleArray::transpose(result);
	return result;
    }

    __finally {
	stop = false;
	ThreeDMeasureWindow->Visible = false;
    }

    return double2D_ptr((double2D *) null);
};

double TThreeDMeasurementForm::getMeanLuminance(double_vector_ptr result)
{
    int size = result->size();
    double total = 0;
    for (int x = 0; x != size; x++) {
	total += (*result)[x];
    }
    return total / size;
};
void TThreeDMeasurementForm::
storeResult(const string & sheetName,
	    double2D_ptr result, bptr < cms::colorformat::ExcelAccessBase > excel)
{
    using namespace cms::util;
    int height = result->dim1();
    int weight = result->dim2();
    if (height != 17 || weight != 17) {
	ShowMessage("Measure result isn't 17x17 format.");
	return;
    }

    for (int y = 0; y < height; y++) {
	int v = y * 16;
	v = v > 255 ? 255 : v;
	string_vector_ptr measure = StringVector::fromDoubleArray(result, y);
	string_vector_ptr data(new string_vector());
	data->push_back(_toString(v));
	data->insert(data->end(), measure->begin(), measure->end());
	excel->insertData(sheetName, data, false);
    }
}

double2D_ptr TThreeDMeasurementForm::crosstalk(double2D_ptr meaureResult)
{
    using namespace java::lang;
    int height = meaureResult->dim1();
    int weight = meaureResult->dim2();
    if (height != 17 || weight != 17) {
	throw IllegalArgumentException("meaureResult->dim1() != 17 || meaureResult->dim1() != 17");
    }

    double2D_ptr result(new double2D(17, 17));
    for (int h = 0; h < 17; h++) {
	for (int w = 0; w < 17; w++) {

	    if (h == w) {
		(*result)[h][w] = -1;
	    } else if (w > h) {
		double BB = (*meaureResult)[h][h];
		double BW = (*meaureResult)[h][w];
		double WW = (*meaureResult)[w][w];
		double v = whiteXTalk(BB, BW, WW);
		(*result)[h][w] = IsNan(v) ? 0 : v;
		//(*result)[h][w] =  std::isnan(v) ? 0 : v;
	    } else {
		double BB = (*meaureResult)[w][w];
		double WB = (*meaureResult)[h][w];
		double WW = (*meaureResult)[h][h];
		double v = blackXTalk(BB, WB, WW);
		(*result)[h][w] = IsNan(v) ? 0 : v;
	    }

	}
    }
    return result;
};
double TThreeDMeasurementForm::whiteXTalk(double BB, double BW, double WW)
{
    double denominator = WW - BB;
    if (denominator == 0) {
	return 0;
    } else {
	return (BW - BB) / denominator * 100;
    }
};
double TThreeDMeasurementForm::blackXTalk(double BB, double WB, double WW)
{
    double denominator = WW - BB;
    if (denominator == 0) {
	return 0;
    } else {
	return (WW - WB) / denominator * 100;
    }
};
void __fastcall TThreeDMeasurementForm::FormCreate(TObject * Sender)
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    if (true == linkCA210) {
	try {
	    ca210 = bptr < CA210 > (new CA210());
	}
	catch(EOleException & ex) {
	    ShowMessage("CA210 cannot be linked.");
	}
    }
}

//---------------------------------------------------------------------------


void __fastcall TThreeDMeasurementForm::Button_SpotMeasureClick(TObject * Sender)
{
    using namespace Dep;
    int start = this->Edit_Start->Text.ToInt();
    int target = this->Edit_Target->Text.ToInt();
    this->Edit5->Text = start;
    this->Edit6->Text = target;
    this->Edit7->Text = start;
    this->Edit8->Text = start;
    this->Edit9->Text = target;
    this->Edit10->Text = target;
    this->Edit2->Text = target;
    this->Edit3->Text = start;

    bool extend = this->CheckBox_Extend->Checked;
    stop = false;
    try {
	double v0 = measure(start, target);
	double v1 = measure(start, start);
	double v2 = measure(target, target);
	double v3 = 0;
	if (extend) {
	    v3 = measure(target, start);
	    this->Edit4->Text = v3;
	}

	this->Edit11->Text = v0;
	this->Edit12->Text = v1;
	this->Edit13->Text = v2;
	double v = 0, vv = 0;
	if (start > target) {
	    //lrgb > rrgb
	    v = whiteXTalk(v2, v0, v1);
	    if (extend) {
		vv = blackXTalk(v2, v3, v1);
	    }
	} else {
	    //lrgb < rrgb
	    v = blackXTalk(v1, v0, v2);
	    if (extend) {
		vv = whiteXTalk(v1, v3, v2);
	    }
	}
	this->Edit1->Text = v;
	if (extend) {
	    this->Edit14->Text = vv;
	}
    }
    __finally {
	stop = false;
	ThreeDMeasureWindow->Visible = false;
    }
}

//---------------------------------------------------------------------------

void __fastcall TThreeDMeasurementForm::CheckBox_StableTestClick(TObject * Sender)
{
    bool test = this->CheckBox_StableTest->Checked;
    ComboBox_MeasureMode->Enabled = test;
    if (test) {
	Edit_IdleTime->Text = 0;
	Edit_AveTimes->Text = 200;
    }

}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TThreeDMeasurementForm::CheckBox_ExtendClick(TObject * Sender)
{
    bool extend = this->CheckBox_Extend->Checked;
    Edit2->Visible = extend;
    Edit3->Visible = extend;
    Edit4->Visible = extend;
    Edit14->Visible = extend;
    Label8->Visible = extend;
}

//---------------------------------------------------------------------------

void TThreeDMeasurementForm::patternGenerate()
{
    using namespace Dep;
    int idleTime = this->Edit_IdleTime->Text.ToInt();


    ThreeDMeasureWindow->Visible = true;
    stop = false;
    while (!stop) {
	if (talkABreak) {
	    Application->ProcessMessages();
	    continue;
	}
	RGB_ptr lrgb(new
		     RGBColor(patGenR ? startAdj : 0, patGenG ? startAdj : 0,
			      patGenB ? startAdj : 0));
	RGB_ptr rrgb(new
		     RGBColor(patGenR ? targetAdj : 0, patGenG ? targetAdj : 0,
			      patGenB ? targetAdj : 0));

	ThreeDMeasureWindow->setLeftRGB(lrgb);
	ThreeDMeasureWindow->setRightRGB(lrgb);
	Application->ProcessMessages();
	Sleep(idleTime);
	ThreeDMeasureWindow->setLeftRGB(rrgb);
	ThreeDMeasureWindow->setRightRGB(rrgb);
	Application->ProcessMessages();
	Sleep(idleTime);
    }
}

void TThreeDMeasurementForm::dynamicMeasure(int start, int target,
					    int adjustStart, int adjustTarget)
{
    //=========================================================================
    // for gino
    //=========================================================================
    if (this->CheckBox_PatternGenOnly->Checked) {
	patGenR = this->CheckBox_PatternGenR->Checked;
	patGenG = this->CheckBox_PatternGenG->Checked;
	patGenB = this->CheckBox_PatternGenB->Checked;
	ThreeDMeasureWindow->patternGenMode = true;
	ThreeDMeasureWindow->FormPaint(this);
	patternGenerate();
	this->CheckBox_PatternGenR->Checked = patGenR;
	this->CheckBox_PatternGenG->Checked = patGenG;
	this->CheckBox_PatternGenB->Checked = patGenB;
	return;
    }
    //=========================================================================

    //=========================================================================
    // 訊息設定
    //=========================================================================
    ThreeDMeasureWindow->patternGenMode = false;
    ThreeDMeasureWindow->FormPaint(this);
    ThreeDMeasureWindow->Label_StartBase->Caption =
	(_toString(start) + "->" + _toString(start) + " measuring...").c_str();
    ThreeDMeasureWindow->Label_TargetBase->Caption =
	(_toString(target) + "->" + _toString(target) + " measuring...").c_str();
    ThreeDMeasureWindow->Label_StartTarget->Caption =
	(_toString(adjustStart) + "->" + _toString(adjustTarget) + " measuring...").c_str();
    ThreeDMeasureWindow->Label_TargetStart->Caption =
	(_toString(adjustTarget) + "->" + _toString(adjustStart) + " measuring...").c_str();

    ThreeDMeasureWindow->Label_WXtalk->Caption = "w xtalk measuring...";
    ThreeDMeasureWindow->Label_BXtalk->Caption = "b xtalk measuring...";
    //=========================================================================

    //=========================================================================
    // 設定CA210
    //=========================================================================
    bool release = CheckBox_AutoReleaseCA210->Checked;
    if (true == linkCA210 && release) {
	ca210->getCA210API()->setRemoteMode(ca210api::Locked);
    }
    //=========================================================================


    //=========================================================================
    // 量測
    //=========================================================================
    stop = false;
    double v1 = measure(start, start);
    double v2 = measure(target, target);
    double v3 = measure(adjustTarget, adjustStart);
    double v0 = measure(adjustStart, adjustTarget);
    //=========================================================================

    if (true == linkCA210 && release) {
	ca210->getCA210API()->setRemoteMode(ca210api::Off);
    }
    //=========================================================================
    // 訊息設定
    //=========================================================================
    ThreeDMeasureWindow->Label_StartBase->Caption =
	(_toString(start) + "->" + _toString(start) + " " + _toString(v1)).c_str();
    ThreeDMeasureWindow->Label_TargetBase->Caption =
	(_toString(target) + "->" + _toString(target) + " " + _toString(v2)).c_str();
    ThreeDMeasureWindow->Label_StartTarget->Caption =
	(_toString(adjustStart) + "->" + _toString(adjustTarget) + " " + _toString(v0)).c_str();
    ThreeDMeasureWindow->Label_TargetStart->Caption =
	(_toString(adjustTarget) + "->" + _toString(adjustStart) + " " + _toString(v3)).c_str();
    //=========================================================================

    //=========================================================================
    // xtalk計算
    //=========================================================================
    double bb = start > target ? v2 : v1;
    double ww = start > target ? v1 : v2;
    double bw = start > target ? v3 : v0;
    double wb = start > target ? v0 : v3;

    double wxtalk = whiteXTalk(bb, bw, ww);
    double bxtalk = whiteXTalk(bb, wb, ww);
    //=========================================================================
    ThreeDMeasureWindow->Label_WXtalk->Caption = ("w xtalk " + _toString(wxtalk)).c_str();
    ThreeDMeasureWindow->Label_BXtalk->Caption = ("b xtalk " + _toString(bxtalk)).c_str();

    updateAdjust();
}

void TThreeDMeasurementForm::updateAdjust()
{
    using namespace Dep;
    startAdj = startAdj > 255 ? 255 : startAdj < 0 ? 0 : startAdj;
    targetAdj = targetAdj > 255 ? 255 : targetAdj < 0 ? 0 : targetAdj;
    ThreeDMeasureWindow->Label_StartAdj->Caption = ("(Left) start: " + _toString(startAdj)).c_str();
    ThreeDMeasureWindow->Label_TargetAdj2->Caption =
	("(Right) target: " + _toString(targetAdj)).c_str();
    ThreeDMeasureWindow->Label_TargetAdj->Caption = ThreeDMeasureWindow->Label_TargetAdj2->Caption;

    if (!ThreeDMeasureWindow->patternGenMode) {
	RGB_ptr lrgb(new RGBColor(startAdj, startAdj, startAdj));
	RGB_ptr rrgb(new RGBColor(targetAdj, targetAdj, targetAdj));
	ThreeDMeasureWindow->setLeftRGB(lrgb);
	ThreeDMeasureWindow->setRightRGB(rrgb);
    }
}

void __fastcall TThreeDMeasurementForm::Button_DynamicMeasureClick(TObject * Sender)
{

    dynamicMode = true;
    start = this->Edit_DStart->Text.ToInt();
    target = this->Edit_DTarget->Text.ToInt();
    startAdj = start;
    targetAdj = target;
    stop = false;

    try {
	updateAdjust();
	dynamicMeasure(start, target, startAdj, targetAdj);

    }
    __finally {
    }
}

double TThreeDMeasurementForm::measure(int start, int target)
{
    using namespace Dep;
    bool leftrightChange = this->CheckBox_LeftRightChange->Checked;
    int idleTime = this->Edit_IdleTime->Text.ToInt();
    int aveTimes = this->Edit_AveTimes->Text.ToInt();

    RGB_ptr lrgb(new RGBColor(start, start, start));
    RGB_ptr rrgb(new RGBColor(target, target, target));
    double v0 = patternMeasure(lrgb, rrgb, idleTime, aveTimes,
			       leftrightChange);
    return v0;
}

//---------------------------------------------------------------------------

void TThreeDMeasurementForm::keyPress(TObject * Sender, char &Key)
{
    FormKeyPress(Sender, Key);
};


void __fastcall TThreeDMeasurementForm::FormKeyPress(TObject * Sender, char &Key)
{

    switch (Key) {
    case 27:			//esc
	this->stop = true;
	ThreeDMeasureWindow->Visible = false;
	//this->stop = false;
	break;
    case 'w':			//W
    case 'W':
	talkABreak = true;
	startAdj++;
	updateAdjust();
	talkABreak = false;
	break;
    case 's':			//s
    case 'S':
	talkABreak = true;
	startAdj--;
	updateAdjust();
	talkABreak = false;
	break;
    case 'a':
    case 'A':
	talkABreak = true;
	targetAdj--;
	updateAdjust();
	talkABreak = false;
	break;
    case 'd':			//d
    case 'D':
	talkABreak = true;
	targetAdj++;
	updateAdjust();
	talkABreak = false;
	break;

    case 'r':
    case 'R':
	patGenR = !patGenR;
	break;
    case 'g':
	patGenG = !patGenG;
	break;
    case 'b':
    case 'B':
	patGenB = !patGenB;
	break;
    case 88:			//x for swap
    case 120:
	{
	    int startTemp = startAdj;
	    startAdj = targetAdj;
	    targetAdj = startTemp;
	    updateAdjust();
	}
	break;
    case 67:			//c for measure
    case 99:
	updateAdjust();
	dynamicMeasure(start, target, startAdj, targetAdj);
	break;
    case 32:			//space
	{
	    whiteFont = !whiteFont;
	    TColor c = whiteFont ? clWhite : clBlack;
	    ThreeDMeasureWindow->Label_StartBase->Font->Color = c;
	    ThreeDMeasureWindow->Label_TargetBase->Font->Color = c;
	    ThreeDMeasureWindow->Label_StartAdj->Font->Color = c;
	    ThreeDMeasureWindow->Label_TargetAdj2->Font->Color = c;
	    ThreeDMeasureWindow->Label_StartTarget->Font->Color = c;
	    ThreeDMeasureWindow->Label_TargetStart->Font->Color = c;
	    ThreeDMeasureWindow->Label_WXtalk->Font->Color = c;
	    ThreeDMeasureWindow->Label_BXtalk->Font->Color = c;
	    ThreeDMeasureWindow->Label_TargetAdj->Font->Color = c;
	    break;
	}

    }
}

//---------------------------------------------------------------------------

void __fastcall TThreeDMeasurementForm::Button1Click(TObject * Sender)
{
    using namespace Dep;
    using namespace cms::util;
    using namespace cms::colorformat;
    using namespace ca210api;

    bool stableTest = this->CheckBox_StableTest->Checked;
    if (true == stableTest) {

	if (true == linkCA210) {
	    int index = this->ComboBox_MeasureMode->ItemIndex;
	    bptr < ca210api::CA210API > ca210api = ca210->getCA210API();
	    switch (index) {
	    case 0:
		ca210api->setAveragingMode(Auto);
		break;
	    case 1:
		ca210api->setAveragingMode(Fast);
		break;
	    case 2:
		ca210api->setAveragingMode(Slow);
		break;
	    }
	}

	string filename = "W_stableTest.xls";
	Util::deleteExist(filename);
	bptr < ExcelAccessBase > excel =
	    bptr < ExcelAccessBase > (new ExcelAccessBase(filename, Create));

	int idleTime = this->Edit_IdleTime->Text.ToInt();
	int aveTimes = this->Edit_AveTimes->Text.ToInt();
	bool leftrightChange = this->CheckBox_LeftRightChange->Checked;

      std:vector < double_vector_ptr > vec;
	try {
	    for (int y = 0; y < 17; y++) {
		//==================================================================
		// rgb prepare
		//==================================================================
		int r = 16 * y;
		r = r > 255 ? 255 : r;
		RGB_ptr rrgb(new RGBColor(MaxValue::Double255));
		rrgb->setValue(Channel::W, r);
		//==================================================================
		double_vector_ptr measureResult = patternMeasure0(rrgb, rrgb, idleTime, aveTimes,
								  leftrightChange);
		if (true == stableTest) {
		    vec.push_back(measureResult);
		}
		if (true == stop) {
		    break;
		}
	    }
	}
	__finally {
	    stop = false;
	}

	string sheetName = "Sheet1";
	excel->initSheet(sheetName, fieldNames);

	for (int m = 0; m < aveTimes; m++) {
	    string_vector_ptr values(new string_vector());
	    values->push_back(_toString(m + 1));
	    for (int n = 0; n < 17; n++) {
		double v = (*vec[n])[m];
		values->push_back(_toString(v));
	    }
	    excel->insertData(sheetName, values, false);
	}
	ThreeDMeasureWindow->Visible = false;
    }
}

//---------------------------------------------------------------------------



void __fastcall TThreeDMeasurementForm::CheckBox_TopBottomModeClick(TObject * Sender)
{
    bool topBottomMode = this->CheckBox_TopBottomMode->Checked;
    ThreeDMeasureWindow->topBottomMode = topBottomMode;
}

//---------------------------------------------------------------------------

