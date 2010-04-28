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

    bool usexy = this->RadioButton_Targetxy->Checked;
    bool moreAccurate = this->CheckBox_MoreAccurate->Checked;
    //已知rgb
    int rvalue = this->Edit_R->Text.ToInt();
    int gvalue = this->Edit_G->Text.ToInt();
    int bvalue = this->Edit_B->Text.ToInt();
    //已知rgb
    RGB_ptr rgb(new RGBColor(rvalue, gvalue, bvalue));

    bptr < IntensityAnalyzerIF > analyzer = MainForm->getAnalyzer();

    MainForm->setMeterMeasurementWaitTimes();
    MainForm->setAnalyzerToSourceChannel();

    if (true == usexy) {
	double targetx = this->Edit_targetx->Text.ToDouble();
	double targety = this->Edit_targety->Text.ToDouble();
	xyY_ptr xyY(new CIExyY(targetx, targety, 1));
	bptr < WhitePointFinder > finder;
	double maxCount = bitDepth->getMaxDigitalCount();
	//已知xy, 求rgb
	if (true == moreAccurate) {
	    finder.reset(new WhitePointFinder(MainForm->mm, maxCount));
	    MeasureWindow->addWindowListener(finder);
	    rgb = finder->findRGB(xyY);
	} else {

	    finder.reset(new StocktonWhitePointFinder(MainForm->mm, rgb,
						      maxCount));
	    MeasureWindow->addWindowListener(finder);
	    rgb = finder->findRGB(xyY);
	}

	if (null == rgb) {
	    return;
	}
    }
    RGB_ptr r(new RGBColor());
    RGB_ptr g(new RGBColor());
    RGB_ptr b(new RGBColor());
    r->R = rgb->R;
    g->G = rgb->G;
    b->B = rgb->B;

    //==========================================================================
    // 設定到ca-210去
    //==========================================================================
    try {
	analyzer->setWaitTimes(5000);
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
	MainForm->setAnalyzerToTargetChannel();
	analyzer->enter();
	MainForm->setMeterMeasurementWaitTimes();
	//==========================================================================

	setRGBRatio(r->R, g->G, b->B);
    }
    __finally {
	stopMeasure = false;
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

