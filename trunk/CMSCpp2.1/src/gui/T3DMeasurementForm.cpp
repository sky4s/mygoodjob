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
__fastcall TThreeDMeasurementForm::TThreeDMeasurementForm(TComponent *
							  Owner)
:TForm(Owner), linkCA210(!FileExists(DEBUG_FILE)), stop(false),
dynamicMode(false)
{
    using namespace cms::util;
    fieldNames =
	StringVector::fromCString(18, "Target", "0", "16", "32", "48",
				  "64", "80", "96", "112", "128", "144",
				  "160", "176", "192", "208", "224", "240",
				  "255");
}

//---------------------------------------------------------------------------



void __fastcall TThreeDMeasurementForm::Button_MeasureClick(TObject *
							    Sender)
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

    bool leftrightChange = this->CheckBox_LeftRightChange->Checked;


    if (false == (*rgbw)[0] && false == (*rgbw)[1] && false == (*rgbw)[2]
	&& false == (*rgbw)[6]) {
	ShowMessage("Select at least one color.");
	return;
    }

    int idleTime = this->Edit_IdleTime->Text.ToInt();
    int aveTimes = this->Edit_AveTimes->Text.ToInt();

    /*if (true == this->CheckBox_StableTest->Checked) {
       stableTest(idleTime, aveTimes);
       return;
       } */
    bool stableTest = this->CheckBox_StableTest->Checked;
    if (true == stableTest) {
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
	    double2D_ptr result =
		ODMeasure(ch, idleTime, aveTimes, leftrightChange,
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
					      int idleTime, int aveTimes,
					      bool leftrightChange)
{
    double_vector_ptr result =
	patternMeasure0(left, right, idleTime, aveTimes, leftrightChange);
    return getMeanLuminance(result);
};

double_vector_ptr TThreeDMeasurementForm::patternMeasure0(RGB_ptr left,
							  RGB_ptr right,
							  int idleTime,
							  int aveTimes,
							  bool
							  leftrightChange)
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
};

double2D_ptr TThreeDMeasurementForm::ODMeasure(const Dep::Channel & ch,
					       int idleTime,
					       int aveTimes,
					       bool leftrightChange,
					       bool stableTest)
{
    using namespace Dep;
    using namespace math;
    using namespace cms::colorformat;
    using namespace cms::util;

    double2D_ptr result(new double2D(17, 17));
    bptr < ExcelAccessBase > excel;
    string_vector_ptr fieldNames =
	StringVector::fromCString(18, "number", "0", "16", "32", "48",
				  "64", "80", "96", "112", "128", "144",
				  "160", "176", "192", "208", "224", "240",
				  "255");

    if (true == stableTest) {
	string filename = *ch.toString() + "_stableTest.xls";
	Util::deleteExist(filename);
	excel =
	    bptr < ExcelAccessBase >
	    (new ExcelAccessBase(filename, Create));
    }

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
		double_vector_ptr measureResult =
		    patternMeasure0(lrgb, rrgb, idleTime, aveTimes,
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
	    double2D_ptr result,
	    bptr < cms::colorformat::ExcelAccessBase > excel)
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
	string_vector_ptr measure =
	    StringVector::fromDoubleArray(result, y);
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
	throw
	    IllegalArgumentException
	    ("meaureResult->dim1() != 17 || meaureResult->dim1() != 17");
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


void __fastcall TThreeDMeasurementForm::
Button_SpotMeasureClick(TObject * Sender)
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

    /*bool leftrightChange = this->CheckBox_LeftRightChange->Checked;
       bool extend = this->CheckBox_Extend->Checked;
       int idleTime = this->Edit_IdleTime->Text.ToInt();
       int aveTimes = this->Edit_AveTimes->Text.ToInt();

       RGB_ptr lrgb(new RGBColor(start, start, start));
       RGB_ptr rrgb(new RGBColor(target, target, target)); */
    bool extend = this->CheckBox_Extend->Checked;
    try {
	double v0 = measure(start, target);
	double v1 = measure(start, start);
	double v2 = measure(target, target);
	/*double v0 = patternMeasure(lrgb, rrgb, idleTime, aveTimes,
	   leftrightChange);
	   double v1 = patternMeasure(lrgb, lrgb, idleTime, aveTimes,
	   leftrightChange);
	   double v2 = patternMeasure(rrgb, rrgb, idleTime, aveTimes,
	   leftrightChange); */
	double v3 = 0;
	if (extend) {
	    /*v3 = patternMeasure(rrgb, lrgb, idleTime, aveTimes,
	       leftrightChange); */
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

void __fastcall TThreeDMeasurementForm::
CheckBox_StableTestClick(TObject * Sender)
{
    bool test = this->CheckBox_StableTest->Checked;
    ComboBox_MeasureMode->Enabled = test;
    if (test) {
	Edit_IdleTime->Text = 0;
	Edit_AveTimes->Text = 66;
    }

}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TThreeDMeasurementForm::CheckBox_ExtendClick(TObject *
							     Sender)
{
    bool extend = this->CheckBox_Extend->Checked;
    Edit2->Visible = extend;
    Edit3->Visible = extend;
    Edit4->Visible = extend;
    Edit14->Visible = extend;
    Label8->Visible = extend;
}

//---------------------------------------------------------------------------


void __fastcall TThreeDMeasurementForm::
Button_DynamicMeasureClick(TObject * Sender)
{

    dynamicMode = true;
    int start = this->Edit_DStart->Text.ToInt();
    int target = this->Edit_DTarget->Text.ToInt();
    /*bool leftrightChange = this->CheckBox_LeftRightChange->Checked;
       int idleTime = this->Edit_IdleTime->Text.ToInt();
       int aveTimes = this->Edit_AveTimes->Text.ToInt();

       RGB_ptr lrgb(new RGBColor(start, start, start));
       RGB_ptr rrgb(new RGBColor(target, target, target)); */

    try {
	double v0 = measure(start, target);
	double v1 = measure(start, start);
	double v2 = measure(target, target);
	/*double v0 = patternMeasure(lrgb, rrgb, idleTime, aveTimes,
	   leftrightChange);
	   double v1 = patternMeasure(lrgb, lrgb, idleTime, aveTimes,
	   leftrightChange);    //start
	   double v2 = patternMeasure(rrgb, rrgb, idleTime, aveTimes,
	   leftrightChange);    //target */
	ThreeDMeasureWindow->Label_StartBase->Caption =
	    (_toString(start) + "->" + _toString(start) + " " +
	     _toString(v1)).c_str();
	ThreeDMeasureWindow->Label_TargetBase->Caption =
	    (_toString(target) + "->" + _toString(target) + " " +
	     _toString(v2)).c_str();



    }
    __finally {
	//stop = false;
	//ThreeDMeasureWindow->Visible = false;
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


void __fastcall TThreeDMeasurementForm::FormKeyPress(TObject * Sender,
						     char &Key)
{
    switch (Key) {
    case 27:			//esc
	//this->stop = true;
	ThreeDMeasureWindow->Visible = false;

	break;
    case 72:			//up
	break;
    case 80:			//dw
	break;
    case 75:			//lt
	break;
    case 77:			//rt
	break;
    }
}

//---------------------------------------------------------------------------

