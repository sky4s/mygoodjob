//---------------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TTargetWhiteForm2.h"
#include "TMainForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTargetWhiteForm2 *TargetWhiteForm2;
//---------------------------------------------------------------------------
__fastcall TTargetWhiteForm2::TTargetWhiteForm2(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TTargetWhiteForm2::RadioButton_MaxRGBClick(TObject *
							   Sender)
{
    this->Edit_R->SetTextBuf("255");
    this->Edit_G->SetTextBuf("255");
    this->Edit_B->SetTextBuf("255");
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
    if (true == changing) {
	return;
    }

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
    changing = true;
    this->Edit_targetx->Text = xStr;
    this->Edit_targety->Text = yStr;
    this->Edit_up->Text = AnsiString().sprintf("%1.4g", up);
    this->Edit_vp->Text = AnsiString().sprintf("%1.4g", vp);
    changing = false;
}


void TTargetWhiteForm2::scrollBar_Change()
{
    Panel1->Color =
	(TColor) ScrollBar_R->Position + ((ScrollBar_G->Position) << 8) +
	((ScrollBar_B->Position) << 16);
}

void __fastcall TTargetWhiteForm2::Edit_targetxChange(TObject * Sender)
{
    if (true == changing) {
	return;
    }

    using cms::CorrelatedColorTemperature;
    using Indep::CIExyY;
    double x = this->Edit_targetx->Text.ToDouble();
    double y = this->Edit_targety->Text.ToDouble();
    changing = true;
    this->Edit_CT->Text = AnsiString(calculateCCT(x, y));
    changing = false;
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm2::Edit_targetyChange(TObject * Sender)
{
    if (true == changing) {
	return;
    }

    double x = this->Edit_targetx->Text.ToDouble();
    double y = this->Edit_targety->Text.ToDouble();
    changing = true;
    this->Edit_CT->Text = AnsiString(calculateCCT(x, y));
    changing = false;
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
    RGB_ptr rgb;

    if (true == usexy) {
	double targetx = this->Edit_targetx->Text.ToDouble();
	double targety = this->Edit_targety->Text.ToDouble();
	xyY_ptr xyY(new CIExyY(targetx, targety, 1));
	//已知xy, 求rgb
	WhitePointFinder finder(MainForm->mm);
	rgb = finder.findRGB(xyY);
    } else {
	//已知rgb
	int r = this->Edit_R->Text.ToInt();
	int g = this->Edit_G->Text.ToInt();
	int b = this->Edit_B->Text.ToInt();
	rgb.reset(new RGBColor(r, g, b));
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
    //利用ca210做成分分析器, 並且設定回MainForm
    bptr < IntensityAnalyzerIF > analyzer = MainForm->analyzer;
    /*CA210IntensityAnalyzer *ca210Analyzer =
	dynamic_cast < CA210IntensityAnalyzer * >(analyzer.get());*/

    MainForm->setToTargetChannel();
    analyzer->setupComponent(Channel::R, r);
    analyzer->setupComponent(Channel::G, g);
    analyzer->setupComponent(Channel::B, b);
    analyzer->setupComponent(Channel::W, rgb);
    analyzer->enter();
    //==========================================================================
    this->Close();
}

//---------------------------------------------------------------------------

