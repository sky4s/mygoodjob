//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TTargetWhiteForm2.h"
#include <cms/core.h>
#include <cms/colorspace/ciexyz.h>

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
void __fastcall TTargetWhiteForm2::RadioButton3Click(TObject * Sender)
{
    this->Edit_R->SetTextBuf("255");
    this->Edit_G->SetTextBuf("255");
    this->Edit_B->SetTextBuf("255");
    //this->ScrollBar_R->Position = 255;
    //this->ScrollBar_G->Position = 255;
    //this->ScrollBar_B->Position = 255;
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
    catch(IllegalArgumentException ex) {
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


