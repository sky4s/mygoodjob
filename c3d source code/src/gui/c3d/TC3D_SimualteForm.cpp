//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "TC3D_SimualteForm.h"

//C系統文件
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件

//本項目內gui頭文件
#include "THSVStepSimForm.h"
#include <gui/c3d/TC3DForm.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TC3DSimualteForm *C3DSimualteForm;
//---------------------------------------------------------------------------
int x_site, y_site;
__fastcall TC3DSimualteForm::TC3DSimualteForm(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------

void rgb2hsv1(double r, double g, double b, double *h, double *s, double *i, double *v)
{
    r = (int) r;
    g = (int) g;
    b = (int) b;
    *i = (r + g + b) / 3;
    double max = (r > g ? r : g);
    max = (b > max ? b : max);
    *v = max;
    double min = (r < g ? r : g);
    min = (min < b ? min : b);
    double d = max - min;
    *s = d;
    d = (d == 0 ? d + 256 : d);

    if (s == 0)
	*h = 0;
    else if (max == r)
	*h = 60 * (g - b) / d;
    else if (max == g)
	*h = 60 * (b - r) / d + 120;
    else if (max == b)
	*h = 60 * (r - g) / d + 240;
    *h = fmod(*h + 360, 360);
    if (max == 0)
	*s = 0;
    else
	*s = *s / max;
}

//----------------------------------------------------------------------------

void __fastcall TC3DSimualteForm::Image1MouseMove(TObject * Sender, TShiftState Shift, int X, int Y)
{
    int color;
    double h, s, v, i, r, g, b;
    color = Image1->Canvas->Pixels[X][Y];
    if (color == -1)
	color = 0;

    b = color / 65536;
    g = color / 256 % 256;
    r = color % 256;
    rgb2hsv1(r, g, b, &h, &s, &i, &v);

    i = (double (int (i * 10))) /10.0;
    h = (double (int (h * 10))) /10.0;
    s = (double (int (s * 1000))) /1000.0;
    lb_c3d_showX->Caption = "X: " + IntToStr((int) X);
    lb_c3d_showY->Caption = "Y: " + IntToStr((int) Y);
    lb_c3d_showR->Caption = "R: " + IntToStr((int) r);
    lb_c3d_showG->Caption = "G: " + IntToStr((int) g);
    lb_c3d_showB->Caption = "B: " + IntToStr((int) b);
    lb_c3d_showH->Caption = "H: " + FloatToStr(h);
    lb_c3d_showS->Caption = "S: " + FloatToStr((float) s);
    lb_c3d_showI->Caption = "I: " + FloatToStr(i);
    lb_c3d_showV->Caption = "V: " + FloatToStr(v);
}

//---------------------------------------------------------------------------

void __fastcall TC3DSimualteForm::btn_img_saveClick(TObject * Sender)
{
    if (!SaveDialog_Img->Execute()) {
	return;
    }

    String Fpath = SaveDialog_Img->FileName;
    if (Fpath == NULL)
	return;

    Image1->Picture->SaveToFile(Fpath);
}

//---------------------------------------------------------------------------


void __fastcall TC3DSimualteForm::Image1MouseDown(TObject * Sender,
						  TMouseButton Button, TShiftState Shift, int X,
						  int Y)
{
    int color = C3DForm1->colorPicker->image->Canvas->Pixels[X][Y];
    double r1, g1, b1;
    if (color == -1)
	color = 0;

    b1 = color / 65536;
    g1 = color / 256 % 256;
    r1 = color % 256;
    String Fpath = "point.txt";
    FILE *fptr = fopen(Fpath.c_str(), "a");
    fprintf(fptr, "%d\t%d\t%d\n", (int) r1, (int) g1, (int) b1);
    fclose(fptr);
    x_site = X;
    y_site = Y;
}

//---------------------------------------------------------------------------

void __fastcall TC3DSimualteForm::cb_record_u_wantClick(TObject * Sender)
{
    int color;
    double r_new, g_new, b_new;

    String Fpath = "sim_grid_point(224-255,160-192,64-96).txt";
    FILE *fptr = fopen(Fpath.c_str(), "w");
    for (int x = 224; x < 256; x++)
	for (int y = 160; y < 192; y++)
	    for (int z = 64; z < 96; z++) {
		C3DForm1->C3Dsim(x, y, z, &r_new, &g_new, &b_new);
		fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", (int) x, (int) y, (int) z, r_new,
			g_new, b_new);
	    }
    fclose(fptr);

    /*
       int color;
       double r1,g1,b1,r_new, g_new, b_new;

       String Fpath = "sim_error_point_vert.txt";
       FILE* fptr = fopen (Fpath.c_str(),"w");
       for(int y = 0; y < 300; y++){
       color = C3DForm1->Img_3DLUT->Canvas->Pixels[285][y];
       //color = Image1->Canvas->Pixels[285][y];
       if(color==-1)
       color = 0;
       b1 = color/65536;
       g1 = color/256%256;
       r1 = color%256;
       C3DForm1->C3Dsim(r1,g1,b1,&r_new,&g_new,&b_new);
       fprintf(fptr,"%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n",(int)r1,(int)g1,(int)b1,r_new,g_new, b_new);
       }
       fclose(fptr);
     */
    /*
       String Fpath = "sim_error_point1.txt";
       FILE* fptr = fopen (Fpath.c_str(),"a");
       for(int x = 260; x < 305; x++){
       //color = C3DForm1->Img_3DLUT->Canvas->Pixels[x][245];
       color = Image1->Canvas->Pixels[x][207];
       if(color==-1)
       color = 0;
       b1 = color/65536;
       g1 = color/256%256;
       r1 = color%256;
       fprintf(fptr,"%d\t%d\t%d\n",(int)r1,(int)g1,(int)b1);
       }

       fclose(fptr);  */

}

//---------------------------------------------------------------------------



void __fastcall TC3DSimualteForm::Image1DblClick(TObject * Sender)
{
    int X = x_site - 35;
    int Y = y_site - 35;

    double r, g, b, h, s, in, v;
    double H_step = StrToFloat(HSVStepSimForm->EditH->Text);
    double S_step = StrToFloat(HSVStepSimForm->EditS->Text);
    double V_step = StrToFloat(HSVStepSimForm->EditV->Text);
    int color;
    TCanvas *pCanvas = HSVStepSimForm->Image1->Canvas;
    TCanvas *pCanvas2 = HSVStepSimForm->Image2->Canvas;
    TCanvas *pCanvas3 = HSVStepSimForm->Image3->Canvas;
    for (int x = 0; x < 70; x++) {
	for (int y = 0; y < 70; y++) {
	    color = Image1->Canvas->Pixels[X + x][Y + y];
	    if (color == -1)
		color = 0;
	    b = color / 65536;
	    g = color / 256 % 256;
	    r = color % 256;
	    rgb2hsv(r, g, b, &h, &s, &in, &v);
	    for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
		    hsv2rgb(h + (i - 2) * H_step, s + (j - 2) * S_step, v, &r, &g, &b);
		    pCanvas->Brush->Color = (TColor) (int) (r + 256 * g + 65536 * b);
		    pCanvas->Brush->Style = bsSolid;
		    pCanvas->
			FillRect(Rect
				 (i * 140 + 0 + x * 2, j * 140 + 0 + y * 2, i * 140 + x * 2 + 2,
				  j * 140 + y * 2 + 2));

		    hsv2rgb(h + (i - 2) * H_step, s, v + (j - 2) * V_step, &r, &g, &b);
		    pCanvas2->Brush->Color = (TColor) (int) (r + 256 * g + 65536 * b);
		    pCanvas2->Brush->Style = bsSolid;
		    pCanvas2->
			FillRect(Rect
				 (i * 140 + 0 + x * 2, j * 140 + 0 + y * 2, i * 140 + x * 2 + 2,
				  j * 140 + y * 2 + 2));

		    hsv2rgb(h, s + (i - 2) * S_step, v + (j - 2) * V_step, &r, &g, &b);
		    pCanvas3->Brush->Color = (TColor) (int) (r + 256 * g + 65536 * b);
		    pCanvas3->Brush->Style = bsSolid;
		    pCanvas3->
			FillRect(Rect
				 (i * 140 + 0 + x * 2, j * 140 + 0 + y * 2, i * 140 + x * 2 + 2,
				  j * 140 + y * 2 + 2));
		}
	    }
	}
    }
    pCanvas->Pen->Width = 3;
    pCanvas2->Pen->Width = 3;
    pCanvas3->Pen->Width = 3;
    for (int i = 1; i <= 4; i++) {
	pCanvas->MoveTo(i * 140, 0);	//vertical
	pCanvas->LineTo(i * 140, 700);
	pCanvas->MoveTo(0, i * 140);	//horizontal
	pCanvas->LineTo(700, i * 140);

	pCanvas2->MoveTo(i * 140, 0);	//vertical
	pCanvas2->LineTo(i * 140, 700);
	pCanvas2->MoveTo(0, i * 140);	//horizontal
	pCanvas2->LineTo(700, i * 140);

	pCanvas3->MoveTo(i * 140, 0);	//vertical
	pCanvas3->LineTo(i * 140, 700);
	pCanvas3->MoveTo(0, i * 140);	//horizontal
	pCanvas3->LineTo(700, i * 140);
    }
}

//---------------------------------------------------------------------------

void __fastcall TC3DSimualteForm::btn_dif_saveClick(TObject * Sender)
{
    if (!SaveDialog_Img->Execute()) {
	return;
    }

    String Fpath = SaveDialog_Img->FileName;
    if (Fpath == NULL)
	return;

    Img_diff->Picture->SaveToFile(Fpath);
}

//---------------------------------------------------------------------------

void __fastcall TC3DSimualteForm::btn_saveHSVClick(TObject * Sender)
{
    if (!SaveDialog_Img->Execute()) {
	return;
    }

    String Fpath = SaveDialog_Img->FileName;
    if (Fpath == NULL)
	return;

    if (pc_hsv_dif->TabIndex == 0)
	Image_h->Picture->SaveToFile(Fpath);
    else if (pc_hsv_dif->TabIndex == 1)
	Image_s->Picture->SaveToFile(Fpath);
    else if (pc_hsv_dif->TabIndex == 2)
	Image_v->Picture->SaveToFile(Fpath);
}

//---------------------------------------------------------------------------


void __fastcall TC3DSimualteForm::SaveDialog_ImgTypeChange(TObject * Sender)
{
    if (SaveDialog_Img->FilterIndex == 1)
	SaveDialog_Img->FileName = ".bmp";
    else if (SaveDialog_Img->FilterIndex == 2)
	SaveDialog_Img->FileName = ".jpg";
}

//---------------------------------------------------------------------------

