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

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTargetWhiteForm2 *TargetWhiteForm2;
//---------------------------------------------------------------------------
__fastcall TTargetWhiteForm2::TTargetWhiteForm2(TComponent * Owner)
:TForm(Owner), stopMeasure(false)
{
}

//---------------------------------------------------------------------------
void __fastcall TTargetWhiteForm2::RadioButton_MaxRGBClick(TObject *
							   Sender)
{
    setRGBRatio(255, 255, 255);
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::ScrollBar_RChange(TObject * Sender)
{
    Edit_R->Text = AnsiString(ScrollBar_R->Position);
    Edit_ScrollR->Text = AnsiString(ScrollBar_R->Position);
    scrollBar_Change();
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::ScrollBar_GChange(TObject * Sender)
{
    Edit_G->Text = AnsiString(ScrollBar_G->Position);
    Edit_ScrollG->Text = AnsiString(ScrollBar_G->Position);
    scrollBar_Change();
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::ScrollBar_BChange(TObject * Sender)
{
    Edit_B->Text = AnsiString(ScrollBar_B->Position);
    Edit_ScrollB->Text = AnsiString(ScrollBar_B->Position);
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
	bptr < CIExyY > xyY =
	    CorrelatedColorTemperature::CCT2DIlluminantxyY(ct);
	double_array uvpValues = xyY->getuvPrimeValues();
	setColorimetricValues(xyY->x, xyY->y, uvpValues[0], uvpValues[1]);
    }
    catch(IllegalArgumentException & ex) {
	setColorimetricValues(-1, -1, -1, -1);
    }
}

//---------------------------------------------------------------------------

void TTargetWhiteForm2::setColorimetricValues(double x, double y,
					      double up, double vp)
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
    int cct =
	static_cast <
	int >(CorrelatedColorTemperature::xy2CCTByMcCamyFloat(xyY));
    return cct;
}




void __fastcall TTargetWhiteForm2::Button2Click(TObject * Sender)
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
    RGB_ptr rgb(new RGBColor(rvalue, gvalue, bvalue));

    bptr < IntensityAnalyzerIF > analyzer = MainForm->getAnalyzer();

    MainForm->setMeterMeasurementWaitTimes();
    MainForm->setAnalyzerToSourceChannel();

    bool usemaxRGB = this->RadioButton_MaxRGB->Checked;
    bool useRGBRatio = this->RadioButton_RGBRatio->Checked;
    bool usexy = this->RadioButton_Targetxy->Checked;
    bool moreAccurate = this->CheckBox_MoreAccurate->Checked;

    if (usemaxRGB) {
	analyzer->setReferenceColorComment("Max RGB");
    } else if (useRGBRatio) {
	analyzer->setReferenceColorComment("RGB Ratio");
    } else if (usexy) {
	string comment =
	    "Target x,y(" + string(Edit_CT->Text.c_str()) + "k)";
	analyzer->setReferenceColorComment(comment);
	double targetx = this->Edit_targetx->Text.ToDouble();
	double targety = this->Edit_targety->Text.ToDouble();
	xyY_ptr xyY(new CIExyY(targetx, targety, 1));
	bptr < WhitePointFinder > finder;
	double maxCount = bitDepth->getMaxDigitalCount();
	//已知xy, 求rgb
	if (true == moreAccurate) {
	    finder =
		bptr < WhitePointFinder >
		(new WhitePointFinder(MainForm->mm, bitDepth, maxCount));
	    MeasureWindow->addWindowListener(finder);
	    rgb = finder->findRGB(xyY);
	} else {
	    finder =
		bptr < StocktonWhitePointFinder > (new
						   StocktonWhitePointFinder
						   (MainForm->mm, bitDepth,
						    rgb, maxCount));
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
    RGB_ptr r(new RGBColor());
    RGB_ptr g(new RGBColor());
    RGB_ptr b(new RGBColor());
    if (this->CheckBox_MaxRGB->Checked) {
	r->R = g->G = b->B = 255;
    } else {
	r->R = rgb->R;
	g->G = rgb->G;
	b->B = rgb->B;
    }
    //==========================================================================

    //==========================================================================
    // 設定到ca-210去
    //==========================================================================
    try {
	analyzer->setWaitTimes(5000);
	stopMeasure = false;
	//analyzer->beginSetup();
	analyzer->setupComponent(Channel::R, r);
	if (true == stopMeasure) {
	    return;
	}
	analyzer->setupComponent(Channel::G, g);
	if (true == stopMeasure) {
	    return;
	}
	analyzer->setupComponent(Channel::B, b);
	if (true == stopMeasure) {
	    return;
	}
	analyzer->setupComponent(Channel::W, rgb);
	if (true == stopMeasure) {
	    return;
	}
	if (MainForm->isCA210Analyzer()) {
	    MainForm->setAnalyzerToTargetChannel();
	}
	analyzer->enter();
	//MainForm->setMeterMeasurementWaitTimes();
	//==========================================================================

	//==========================================================================
	// 將info設定到UI
	//==========================================================================
	setRGBRatio(rgb->R, rgb->G, rgb->B);
	xyY_ptr refWhite = analyzer->getReferenceColor();
	this->Edit_refLuminance->Text = refWhite->Y;
	this->Edit_refx->Text = refWhite->x;
	this->Edit_refy->Text = refWhite->y;
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
    ScrollBar_R->Position = this->Edit_R->Text.ToInt();
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::Edit_GChange(TObject * Sender)
{
    ScrollBar_G->Position = this->Edit_G->Text.ToInt();
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::Edit_BChange(TObject * Sender)
{
    ScrollBar_B->Position = this->Edit_B->Text.ToInt();
}

//---------------------------------------------------------------------------

void TTargetWhiteForm2::windowClosing()
{
    stopMeasure = true;
}
void __fastcall TTargetWhiteForm2::FormCreate(TObject * Sender)
{
    using namespace cms::util;
    bptr < WindowListener > formPtr(dynamic_cast <
				    WindowListener * >(this));
    MeasureWindow->addWindowListener(formPtr);
#ifdef DEBUG_TARGETWHITE
    this->CheckBox_MoreAccurate->Visible = true;
    this->CheckBox_MaxRGB->Visible = true;
#endif

}

//---------------------------------------------------------------------------

void TTargetWhiteForm2::setBitDepthProcessor(bptr <
					     cms::lcd::calibrate::
					     BitDepthProcessor > bitDepth)
{
    this->bitDepth = bitDepth;
    double maxCount = bitDepth->getMaxDigitalCount();
    setRGBRatio(maxCount, maxCount, maxCount);
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
    this->Button1->Enabled = maxMatrix;
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::Button1Click(TObject * Sender)
{
    using namespace cms::measure;
    using namespace Dep;
    bptr < IntensityAnalyzerIF > analyzer = MainForm->getAnalyzer();
    bptr < MaxMatrixIntensityAnayzer >
	maxmatrix(dynamic_cast <
		  MaxMatrixIntensityAnayzer * >(analyzer.get()));

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

    XYZ_ptr r(new Indep::CIEXYZ(rX, rY, rZ));
    XYZ_ptr g(new Indep::CIEXYZ(gX, gY, gZ));
    XYZ_ptr b(new Indep::CIEXYZ(bX, bY, bZ));
    XYZ_ptr w(new Indep::CIEXYZ(wX, wY, wZ));

    maxmatrix->setupComponent(Channel::R, r);
    maxmatrix->setupComponent(Channel::G, g);
    maxmatrix->setupComponent(Channel::B, b);
    maxmatrix->setupComponent(Channel::W, w);
    //maxmatrix->setupComponent()

    maxmatrix->enter();
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::FormKeyPress(TObject * Sender,
						char &Key)
{
    if (Key == 27) {		//esc
	this->Close();
    }
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::Button3Click(TObject * Sender)
{
    //if (MainForm->isCA210Analyzer()) {
	MainForm->connectMeter();
    //}
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::Button4Click(TObject * Sender)
{
    //if (MainForm->isCA210Analyzer()) {
	MainForm->disconnectMeter();
    //}
}

//---------------------------------------------------------------------------

