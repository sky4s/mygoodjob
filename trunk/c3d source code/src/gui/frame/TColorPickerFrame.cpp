//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "TColorPickerFrame.h"

//C系統文件

//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件
#include <c3d/core.h>

//本項目內gui頭文件

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TColorPickerFrame *ColorPickerFrame;
//---------------------------------------------------------------------------
__fastcall TColorPickerFrame::TColorPickerFrame(TComponent * Owner)
:TFrame(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TColorPickerFrame::Img_3DLUTMouseMove(TObject * Sender,
						      TShiftState Shift, int X, int Y)
{
    int color;
    double h, s, v, i, r, g, b;
    color = Img_3DLUT->Canvas->Pixels[X][Y];
    if (color == -1)
	color = 0;

    b = color / 65536;
    g = color / 256 % 256;
    r = color % 256;
    rgb2hsv(r, g, b, &h, &s, &i, &v);

    i = (double (int (i * 10))) /10.0;
    h = (double (int (h * 10))) /10.0;
    s = (double (int (s * 1000))) /1000.0;

    lb_c3d_showX->Caption = "X: " + IntToStr((int) X);
    lb_c3d_showY->Caption = "Y: " + IntToStr((int) Y);
    lb_c3d_showR->Caption = "R: " + IntToStr((int) r);
    lb_c3d_showG->Caption = "G: " + IntToStr((int) g);
    lb_c3d_showB->Caption = "B: " + IntToStr((int) b);
    lb_c3d_showH->Caption = "H: " + IntToStr((int) h);
    lb_c3d_showS->Caption = "S: " + FloatToStr((float) s);
    lb_c3d_showV->Caption = "V: " + IntToStr((int) v);
}

//---------------------------------------------------------------------------

void __fastcall TColorPickerFrame::Img_3DLUTMouseDown(TObject * Sender,
						      TMouseButton Button, TShiftState Shift, int X,
						      int Y)
{
    /*if (pc_Adjust->TabIndex == 0 && pc_global_adj->TabIndex == 1)
	return;*/

    //rb_c3d_point->Checked = true; //看不到
    //c3d_scrollbar_reset();  //color adjust
    int color;
    double h, s, i, v, r, g, b, r_new, g_new, b_new;
    X_site = X;
    Y_site = Y;
    color = Img_3DLUT->Canvas->Pixels[X][Y];
    if (color == -1)
	color = 0;
    b = color / 65536;
    g = color / 256 % 256;
    r = color % 256;

    ShowImageColor(img_color, r, g, b);
    Set_Adj_Color(r, g, b);
    Show_c3d_SelImg(r, g, b);
    C3Dsim_t(r, g, b, &r_new, &g_new, &b_new);
    Show_c3d_SimImg(r_new, g_new, b_new);
    Show_c3d_Img_sim();
    sg_rgb_input->Cells[0][1] = FloatToStr(r);
    sg_rgb_input->Cells[1][1] = FloatToStr(g);
    sg_rgb_input->Cells[2][1] = FloatToStr(b);

    if (pc_Adjust->TabIndex == 1 && Button == mbRight) {
	TPoint pt = C3DForm1->ClientToScreen(Point(X, Y));
	PopupMenu_HSV_ref_img->Popup(pt.x, pt.y);
    }

}

//---------------------------------------------------------------------------

