//---------------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TTargetWhiteForm2.h"
#include "TMainForm.h"
#include <cms/util/util.h>
#include <gui/event/listener.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTargetWhiteForm2 *TargetWhiteForm2;
//---------------------------------------------------------------------------
__fastcall TTargetWhiteForm2::TTargetWhiteForm2(TComponent * Owner)
:TForm(Owner), stopMeasure(false), maxZDGCode(-1), measuring(false)
{
}

//---------------------------------------------------------------------------
void __fastcall TTargetWhiteForm2::RadioButton_MaxRGBClick(TObject * Sender)
{
    int max = bitDepth->getMaxDigitalCount();
    setRGBRatio(max, max, max);
    this->RadioButton_MaxRGB->Checked = true;
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::ScrollBar_RChange(TObject * Sender)
{
    binder->active(Sender);

    if (CheckBox_Lock->Checked) {
	ScrollBar_G->Position = ScrollBar_R->Position;
	ScrollBar_B->Position = ScrollBar_R->Position;
    }
    scrollBar_Change();
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::ScrollBar_GChange(TObject * Sender)
{
    binder->active(Sender);

    if (CheckBox_Lock->Checked) {
	ScrollBar_R->Position = ScrollBar_G->Position;
	ScrollBar_B->Position = ScrollBar_G->Position;
    }
    scrollBar_Change();
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::ScrollBar_BChange(TObject * Sender)
{
    binder->active(Sender);

    if (CheckBox_Lock->Checked) {
	ScrollBar_R->Position = ScrollBar_B->Position;
	ScrollBar_G->Position = ScrollBar_B->Position;
    }
    scrollBar_Change();
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::Edit_CTChange(TObject * Sender)
{
    if (true == colorimetricChanging) {
	return;
    }

    this->RadioButton_Targetxy->Checked = true;

    using cms::CorrelatedColorTemperature;
    using Indep::CIExyY;
    using java::lang::IllegalArgumentException;
    using namespace boost;

    AnsiString ctText = this->Edit_CT->Text;
    if (ctText.Length() == 0) {
	setColorimetricValues(-1, -1, -1, -1);
	return;
    }

    int ct = ctText.ToInt();

    try {
	bptr < CIExyY > xyY = CorrelatedColorTemperature::CCT2DIlluminantxyY(ct);
	double_array uvpValues = xyY->getuvPrimeValues();
	setColorimetricValues(xyY->x, xyY->y, uvpValues[0], uvpValues[1]);
    }
    catch(IllegalArgumentException & ex) {
	setColorimetricValues(-1, -1, -1, -1);
    }
}

//---------------------------------------------------------------------------

void TTargetWhiteForm2::setColorimetricValues(double x, double y, double up, double vp)
{

    AnsiString xStr = AnsiString().sprintf("%1.4g", x);
    AnsiString yStr = AnsiString().sprintf("%1.4g", y);
    colorimetricChanging = true;
    this->Edit_targetx->Text = xStr;
    this->Edit_targety->Text = yStr;
    this->Edit_up->Text = AnsiString().sprintf("%1.4g", up);
    this->Edit_vp->Text = AnsiString().sprintf("%1.4g", vp);
    colorimetricChanging = false;
}


void TTargetWhiteForm2::scrollBar_Change()
{
    this->RadioButton_RGBRatio->Checked = true;
    Panel1->Color =
	(TColor) ScrollBar_R->Position + ((ScrollBar_G->Position) << 8) +
	((ScrollBar_B->Position) << 16);
}

void __fastcall TTargetWhiteForm2::Edit_targetxChange(TObject * Sender)
{
    if (true == colorimetricChanging) {
	return;
    }

    using cms::CorrelatedColorTemperature;
    using Indep::CIExyY;
    double x = this->Edit_targetx->Text.ToDouble();
    double y = this->Edit_targety->Text.ToDouble();
    colorimetricChanging = true;
    this->Edit_CT->Text = AnsiString(calculateCCT(x, y));
    colorimetricChanging = false;
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::Edit_targetyChange(TObject * Sender)
{
    if (true == colorimetricChanging) {
	return;
    }

    double x = this->Edit_targetx->Text.ToDouble();
    double y = this->Edit_targety->Text.ToDouble();
    colorimetricChanging = true;
    this->Edit_CT->Text = AnsiString(calculateCCT(x, y));
    colorimetricChanging = false;
}

//---------------------------------------------------------------------------


int TTargetWhiteForm2::calculateCCT(double x, double y)
{
    using cms::CorrelatedColorTemperature;
    using Indep::CIExyY;
    bptr < CIExyY > xyY(new CIExyY(x, y));
    int cct = static_cast < int >(CorrelatedColorTemperature::xy2CCTByMcCamyFloat(xyY));
    return cct;
}




void __fastcall TTargetWhiteForm2::Button_RunClick(TObject * Sender)
{
    using namespace boost;
    using namespace Dep;
    using namespace Indep;
    using namespace std;
    using namespace cms::lcd::calibrate;
    using namespace cms::measure::meter;
    using namespace cms::measure;

    if (false == MainForm->linkCA210) {
	ShowMessage("CA210 cannot be linked.");
	return;
    }
    //已知rgb
    int rvalue = this->Edit_R->Text.ToInt();
    int gvalue = this->Edit_G->Text.ToInt();
    int bvalue = this->Edit_B->Text.ToInt();
    //已知rgb
    RGB_ptr rgb(new RGBColor(rvalue, gvalue, bvalue, MaxValue::Int8Bit));

    bptr < IntensityAnalyzerIF > analyzer = MainForm->getAnalyzer();

    MainForm->setMeterMeasurementWaitTimes();
    MainForm->setAnalyzerToSourceChannel();

    bool usemaxRGB = this->RadioButton_MaxRGB->Checked;
    bool useRGBRatio = this->RadioButton_RGBRatio->Checked;
    bool usexy = this->RadioButton_Targetxy->Checked;
    bool moreAccurate = this->CheckBox_MoreAccurate->Checked;
    bool avoidHookTV = true == usexy && this->CheckBox_AvoidHookTV->Checked;

    if (avoidHookTV) {
	//tv下的avoid hook
	//1. 量測最大亮度點色度座標
	//2. 找到反轉點
	//3. 設定B為反轉點, 且保持不變
	//4. 找到對應色度的RGB
	if (maxZDGCode == -1) {
	    //this->maxZDGCode = MeasureTool::getMaxZDGCode(MainForm->mm, bitDepth);
	    Button_FindInverseB->Click();
	}
	rgb->B = maxZDGCode;
    }

    if (usemaxRGB) {
	analyzer->setReferenceColorComment("Max RGB");
    } else if (useRGBRatio) {
	analyzer->setReferenceColorComment("RGB Ratio");
    } else if (usexy) {
	string comment = "Target x,y(" + string(Edit_CT->Text.c_str()) + "k)";
	/*if (avoidHookTV) {
	   comment = "Target x,y(Max RGB) with avoid Hook TV";
	   } else {
	   comment = "Target x,y(" + string(Edit_CT->Text.c_str()) + "k)";
	   } */

	analyzer->setReferenceColorComment(comment);
	double targetx = this->Edit_targetx->Text.ToDouble();
	double targety = this->Edit_targety->Text.ToDouble();
	xyY_ptr xyY(new CIExyY(targetx, targety, 1));
	bptr < WhitePointFinder > finder;
	double maxCount = bitDepth->getMaxDigitalCount();
	//已知xy, 求rgb
	if (true == moreAccurate) {
	    finder =
		bptr < WhitePointFinder > (new WhitePointFinder(MainForm->mm, bitDepth, maxCount));
	    MeasureWindow->addWindowListener(finder);
	    rgb = finder->findRGB(xyY);
	} else {
	    finder =
		bptr < StocktonWhitePointFinder > (new
						   StocktonWhitePointFinder
						   (MainForm->mm, bitDepth, rgb, maxCount, false));
	    MeasureWindow->addWindowListener(finder);
	    rgb = finder->findRGB(xyY);
	}

	if (null == rgb) {
	    return;
	}
    }
    //==========================================================================
    // primary color的設定
    //==========================================================================
    RGB_ptr r(new RGBColor(MaxValue::Int8Bit));
    RGB_ptr g(new RGBColor(MaxValue::Int8Bit));
    RGB_ptr b(new RGBColor(MaxValue::Int8Bit));
    r->R = rgb->R;
    g->G = rgb->G;
    b->B = rgb->B;
    //==========================================================================

    //==========================================================================
    // 設定到ca-210去
    //==========================================================================

    bool tconinput = MainForm->RadioButton_TCON->Checked;
    try {
	analyzer->setWaitTimes(5000);
	stopMeasure = false;
	measuring = true;
	analyzer->beginAnalyze();
	//當在Direct Gamma下, false == MeasureWindow->Visibl會一直成立
	//如此將無法進行量測
	if (true == stopMeasure || (!tconinput && false == MeasureWindow->Visible)) {
	    measuring = false;
	    analyzer->endAnalyze();
	    return;
	}
	analyzer->setupComponent(Channel::R, r);
	if (true == stopMeasure || (!tconinput && false == MeasureWindow->Visible)) {
	    measuring = false;
	    analyzer->endAnalyze();
	    return;
	}
	analyzer->setupComponent(Channel::G, g);
	if (true == stopMeasure || (!tconinput && false == MeasureWindow->Visible)) {
	    measuring = false;
	    analyzer->endAnalyze();
	    return;
	}
	analyzer->setupComponent(Channel::B, b);
	if (true == stopMeasure || (!tconinput && false == MeasureWindow->Visible)) {
	    measuring = false;
	    analyzer->endAnalyze();
	    return;
	}
	analyzer->setupComponent(Channel::W, rgb);
	if (true == stopMeasure || (!tconinput && false == MeasureWindow->Visible)) {
	    measuring = false;
	    analyzer->endAnalyze();
	    return;
	}

	if (MainForm->isCA210Analyzer()) {
	    MainForm->setAnalyzerToTargetChannel();
	}
	analyzer->enter();
	MainForm->StatusBar1->Panels->Items[0]->Text = "Target White: Set";

	//==========================================================================

	//==========================================================================
	// 將info設定到UI
	//==========================================================================
	setRGBRatio(rgb->R, rgb->G, rgb->B);
	xyY_ptr refWhite = analyzer->getReferenceColor();
	String str;

	this->Edit_refLuminance->Text = str.sprintf("%.4f", refWhite->Y);
	this->Edit_refx->Text = str.sprintf("%.4f", refWhite->x);
	this->Edit_refy->Text = str.sprintf("%.4f", refWhite->y);


	XYZ_ptr rXYZ = analyzer->getPrimaryColor(Channel::R)->toXYZ();
	XYZ_ptr gXYZ = analyzer->getPrimaryColor(Channel::G)->toXYZ();
	XYZ_ptr bXYZ = analyzer->getPrimaryColor(Channel::B)->toXYZ();
	XYZ_ptr wXYZ = refWhite->toXYZ();

	this->Edit_RX->Text = str.sprintf("%.4f", rXYZ->X);
	this->Edit_RY->Text = str.sprintf("%.4f", rXYZ->Y);
	this->Edit_RZ->Text = str.sprintf("%.4f", rXYZ->Z);
	this->Edit_GX->Text = str.sprintf("%.4f", gXYZ->X);
	this->Edit_GY->Text = str.sprintf("%.4f", gXYZ->Y);
	this->Edit_GZ->Text = str.sprintf("%.4f", gXYZ->Z);
	this->Edit_BX->Text = str.sprintf("%.4f", bXYZ->X);
	this->Edit_BY->Text = str.sprintf("%.4f", bXYZ->Y);
	this->Edit_BZ->Text = str.sprintf("%.4f", bXYZ->Z);
	this->Edit_WX->Text = str.sprintf("%.4f", wXYZ->X);
	this->Edit_WY->Text = str.sprintf("%.4f", wXYZ->Y);
	this->Edit_WZ->Text = str.sprintf("%.4f", wXYZ->Z);
	//==========================================================================
    }
    __finally {
	stopMeasure = false;
	MainForm->setMeterMeasurementWaitTimes();
    }
}

//---------------------------------------------------------------------------



void __fastcall TTargetWhiteForm2::Edit_RChange(TObject * Sender)
{
    binder->active(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::Edit_BChange(TObject * Sender)
{
    binder->active(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::Edit_GChange(TObject * Sender)
{
    binder->active(Sender);
}

//----------------------------------------

//---------------------------------------------------------------------------

void TTargetWhiteForm2::windowClosing()
{
    stopMeasure = true;
}
void __fastcall TTargetWhiteForm2::FormCreate(TObject * Sender)
{
    using namespace cms::util;
    using namespace gui::util;
    using namespace gui::event;
    bptr < WindowListener > formPtr(dynamic_cast < WindowListener * >(this));
    MeasureWindow->addWindowListener(formPtr);
    if (MainForm->newFunction) {
	//CheckBox_AvoidHookTV->Visible = true;
    }
#ifdef DEBUG_TARGETWHITE
    this->CheckBox_MoreAccurate->Visible = true;
    this->CheckBox_MaxRGB->Visible = true;
#endif

    binder = bptr < MultiUIBinder > (new MultiUIBinder());
    binder->bind(Edit_ScrollR, ScrollBar_R);
    binder->bind(Edit_ScrollG, ScrollBar_G);
    binder->bind(Edit_ScrollB, ScrollBar_B);
    binder->bind(Edit_R, ScrollBar_R);
    binder->bind(Edit_G, ScrollBar_G);
    binder->bind(Edit_B, ScrollBar_B);
    binder->bind(Edit_InverseB, Edit_B);
}

//---------------------------------------------------------------------------

void TTargetWhiteForm2::setBitDepthProcessor(bptr <
					     cms::lcd::calibrate::BitDepthProcessor > bitDepth)
{
    this->bitDepth = bitDepth;
    if (Edit_R->Text.ToInt() == 0) {
	int maxCount = (int) bitDepth->getMaxDigitalCount();
	setRGBRatio(maxCount, maxCount, maxCount);
	this->RadioButton_MaxRGB->Checked = true;
	ScrollBar_R->Max = maxCount;
	ScrollBar_G->Max = maxCount;
	ScrollBar_B->Max = maxCount;
    }
}

//---------------------------------------------------------------------------
void TTargetWhiteForm2::setRGBRatio(int r, int g, int b)
{
    this->Edit_R->Text = r;
    this->Edit_G->Text = g;
    this->Edit_B->Text = b;
};


void __fastcall TTargetWhiteForm2::Edit_BZChange(TObject * Sender)
{
    double rX = this->Edit_RX->Text.ToDouble();
    double rY = this->Edit_RY->Text.ToDouble();
    double rZ = this->Edit_RZ->Text.ToDouble();

    double gX = this->Edit_GX->Text.ToDouble();
    double gY = this->Edit_GY->Text.ToDouble();
    double gZ = this->Edit_GZ->Text.ToDouble();

    double bX = this->Edit_BX->Text.ToDouble();
    double bY = this->Edit_BY->Text.ToDouble();
    double bZ = this->Edit_BZ->Text.ToDouble();

    double wX = rX + gX + bX;
    double wY = rY + gY + bY;
    double wZ = rZ + gZ + bZ;
    this->Edit_WX->Text = wX;
    this->Edit_WY->Text = wY;
    this->Edit_WZ->Text = wZ;
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::FormShow(TObject * Sender)
{
    bool maxMatrix = MainForm->RadioButton_AnalyzerMaxMatrix->Checked;
    this->Button_setMaxMatrix->Enabled = maxMatrix;
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::Button_setMaxMatrixClick(TObject * Sender)
{
    using namespace cms::measure;
    using namespace Dep;
    bptr < IntensityAnalyzerIF > analyzer = MainForm->getAnalyzer();
    bptr < MaxMatrixIntensityAnalyzer >
	maxmatrix(dynamic_cast < MaxMatrixIntensityAnalyzer * >(analyzer.get()));

    double rX = this->Edit_RX->Text.ToDouble();
    double rY = this->Edit_RY->Text.ToDouble();
    double rZ = this->Edit_RZ->Text.ToDouble();

    double gX = this->Edit_GX->Text.ToDouble();
    double gY = this->Edit_GY->Text.ToDouble();
    double gZ = this->Edit_GZ->Text.ToDouble();

    double bX = this->Edit_BX->Text.ToDouble();
    double bY = this->Edit_BY->Text.ToDouble();
    double bZ = this->Edit_BZ->Text.ToDouble();

    double wX = this->Edit_WX->Text.ToDouble();
    double wY = this->Edit_WY->Text.ToDouble();
    double wZ = this->Edit_WZ->Text.ToDouble();

    XYZ_ptr rXYZ(new Indep::CIEXYZ(rX, rY, rZ));
    XYZ_ptr gXYZ(new Indep::CIEXYZ(gX, gY, gZ));
    XYZ_ptr bXYZ(new Indep::CIEXYZ(bX, bY, bZ));
    XYZ_ptr wXYZ(new Indep::CIEXYZ(wX, wY, wZ));

    maxmatrix->setupComponent(Channel::R, rXYZ);
    maxmatrix->setupComponent(Channel::G, gXYZ);
    maxmatrix->setupComponent(Channel::B, bXYZ);
    maxmatrix->setupComponent(Channel::W, wXYZ);

    maxmatrix->enter();
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::FormKeyPress(TObject * Sender, char &Key)
{
    if (Key == 27) {		//esc
	if (true == measuring) {
	    stopMeasure = true;
	} else {
	    this->Close();
	}
    }
}

//---------------------------------------------------------------------------
void __fastcall TTargetWhiteForm2::Button3Click(TObject * Sender)
{
    if (MainForm->linkCA210) {
	MainForm->connectMeter();
	this->Button4->Enabled = true;
	this->Button3->Enabled = false;
	this->Button_Run->Enabled = true;
	Button_ContinueMeasure->Enabled = true;
    }
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::Button4Click(TObject * Sender)
{
    //MainForm->getAnalyzer();
    if (MainForm->linkCA210) {

	MainForm->disconnectMeter();
	this->Button4->Enabled = false;
	this->Button3->Enabled = true;
	this->Button_Run->Enabled = false;
	Button_ContinueMeasure->Enabled = false;

    }
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::Button_FindInverseBClick(TObject * Sender)
{
    using namespace cms::measure;
    using namespace cms::lcd::calibrate;
    this->maxZDGCode = MeasureTool::getMaxZDGCode(MainForm->mm, bitDepth);
    Edit_InverseB->Text = maxZDGCode;
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::Edit_InverseBClick(TObject * Sender)
{
    if (Edit_InverseB->Text.Length() != 0) {
	binder->active(Sender);
    }
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::Button_ContinueMeasureClick(TObject * Sender)
{

    if (true == continueMeasure) {
	continueMeasure = false;
	GroupBox7->Caption = "Reference Color";
	Button_ContinueMeasure->Caption = "Continue Measure";
    } else {
	GroupBox7->Caption = "Measure Color";
	Button_ContinueMeasure->Caption = "Stop Measure";

	using namespace cms::measure;
	using namespace Indep;
	bptr < IntensityAnalyzerIF > analyzer = MainForm->getAnalyzer();
	bptr < MeterMeasurement > mm = analyzer->getMeterMeasurement();
	bptr < cms::measure::meter::Meter > meter = mm->getMeter();

	String str;
	continueMeasure = true;

	while (continueMeasure) {
	    Application->ProcessMessages();
	    double_array XYZValues = meter->triggerMeasurementInXYZ();
	    Application->ProcessMessages();
	    XYZ_ptr XYZ(new Indep::CIEXYZ(XYZValues));
	    xyY_ptr xyY(new CIExyY(XYZ));

	    this->Edit_refLuminance->Text = str.sprintf("%.4f", xyY->Y);
	    this->Edit_refx->Text = str.sprintf("%.4f", xyY->x);
	    this->Edit_refy->Text = str.sprintf("%.4f", xyY->y);
	}
    }
}

//---------------------------------------------------------------------------

