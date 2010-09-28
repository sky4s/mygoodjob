//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TColorFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TColorFrame *ColorFrame;
//---------------------------------------------------------------------------
__fastcall TColorFrame::TColorFrame(TComponent * Owner)
:TFrame(Owner)
{
}

//---------------------------------------------------------------------------
double_array TColorFrame::getRGBArray()
{
    double_array result(new double[3]);
    result[0] = StrToFloat(lb_c3d_selR->Caption);
    result[1] = StrToFloat(lb_c3d_selG->Caption);
    result[2] = StrToFloat(lb_c3d_selB->Caption);
    return result;
};
double_array TColorFrame::getHSIVArray()
{
    double_array result(new double[4]);
    result[0] = StrToFloat(lb_c3d_selH->Caption);
    result[1] = StrToFloat(lb_c3d_selS->Caption);
    result[2] = StrToFloat(lb_c3d_selI->Caption);
    result[3] = StrToFloat(lb_c3d_selV->Caption);
    return result;
};
void TColorFrame::setRGBHSIV(double r, double g, double b, double h, double s, double i, double v)
{
    lb_c3d_selR->Caption = r;
    lb_c3d_selG->Caption = g;
    lb_c3d_selB->Caption = b;
    lb_c3d_selH->Caption = h;
    lb_c3d_selS->Caption = s;
    lb_c3d_selI->Caption = i;
    lb_c3d_selV->Caption = v;
};

