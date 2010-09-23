//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <java/lang.h>
#include <cms/colorformat/excelfile.h>
#include <cms/util/util.h>
#include <iostream>
#include "c3d_sim.h"
#include "c3d_12401.h"
#include "Engineering.h"
#include "Unit3.h"
#include "Unit2.h"
#include "c3d1_dis_new.h"
#include "GetCursorColor.h"
#include "color_converter.h"

//#include "Table_Step_Form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma warn -pck
#define PointColor_D 2		//RGB diffusion 最大的調整量為50, 即移動的漸層範圍不超過32*2, 所以設為2

TC3DForm1 *C3DForm1;
AbstC3D *OC3D;
double Color_move[150][3];
int Color_move_Nbr = 4;
int TBL_SIZE = 9;
int cube_dis = 256 / (TBL_SIZE - 1);	// steps for non-uniform table
int bit_num = 12;		// lookup table 的 bit 數
double Ratio = pow(2, bit_num - 8);	// 因bit數為10或12所放大的倍數
double scrl_ratio = 1;
bool c3d_detailadjust = false;
int tbl_s;

int tbl_val[4][33] = {
    {0, 32, 64, 96, 128, 160, 192, 224, (256 - 1.0 / Ratio)},	//9x9x9 uniform table, first index is 0
    {0, 32, 64, 128, 192, 224, (256 - 1.0 / Ratio), 0, 0},	//7x7x7 table, first index is 1
    {0, 16, 32, 48, 64, 80, 96, 112, 128, 144, 160, 176, 192, 208, 224, 240, 255},	//17x17x17 table, first index is 2
    {0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120, 128, 136, 144,	//33x33x33 table, first index is 3
     152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248, 255}
//Following is some sets of non-uniform table
//{0,16,48,112,176,208,224,240,255},      //table 3
//{0,16,80,144,184,216,232,248,255}, //table 10
//{0,16,96,144,168,200,224,240,255},      //table a
//{0,16,96,144,176,200,224,240,255},      //table b
};

int sim_val[72] = { 8.1, 4.1, 0.2, -1.1, -0.8, -1.7, -2.3, -3.4, -4.9, -4.3, -4.4,
    -4.8, -3.3, -3.4, -3.2, -3.1, -3.3, -2.8, -0.5, 3.0, 4.8, 12.0, 14.9, 14.8,
    14.9, 13.0, 11.8, 10.4, 9.7, 10.0, 9.4, 8.2, 6.7, 5.8, 4.6, 2.8, 2.3, 1.6, 0.7,
    -0.2, -0.5, -1.3, -1.4, -1.9, -1.4, -1.3, -2.6, -4.4, -4.4, -5.5, -8.2, -6.2,
    -3.8, -2.0, -0.1, 1.5, 1.7, 2.4, 4.1, 4.0, 3.5, 4.1, 3.4, 3.6, 3.6, 3.3, 2.9,
    4.5, 3.7, 6.0, 8.9, 10.8
};

int total_len = TBL_SIZE * TBL_SIZE * TBL_SIZE;	// the number of points in table
int **c3d_r, **c3d_g, **c3d_b;

TC3D_SimualteForm *C3D_SimualteForm;
TPColorThread1 *PColorThread1;
int X_site, Y_site;

double pi = 3.1415926;

// sigma_lgt is a value for Modulate Saturation value from 0.666 to 0
// The value is for Gaussian distribution, used in function "Manual39_mid","Manual39_light","Manual39_dark"
double sigma_lgt = 0.35;	//Saturation smooth 高飽和區的Gaussian參數, 參數越小越快趨近bypass curve
double sigma_st = 0.45;
bool Cell_move = true;		//避免在selectcell時, 發生manual39的hue label當中的值優先寫到grid裡, 而不是點選的Cell值

//---------------------------------------------------------------------------
__fastcall TC3DForm1::TC3DForm1(TComponent * Owner)
:TForm(Owner)
{
    new_array();
    interpol = true;
    if (TBL_SIZE == 9)
	tbl_s = 0;
    else if (TBL_SIZE == 7)
	tbl_s = 1;
    else if (TBL_SIZE == 17)
	tbl_s = 2;
    else if (TBL_SIZE == 33)
	tbl_s = 3;

    C3Dini();
    sg_rgb_input->Cells[0][0] = "R";
    sg_rgb_input->Cells[1][0] = "G";
    sg_rgb_input->Cells[2][0] = "B";
}

__fastcall TC3DForm1::~TC3DForm1()
{
    delete_array();
}

//---------------------------------------------------------------------------
void TC3DForm1::new_array()
{
    // simulate時使用的lookup table 值
    c3d_lutR = new double **[TBL_SIZE];
    c3d_lutG = new double **[TBL_SIZE];
    c3d_lutB = new double **[TBL_SIZE];
    c3d_lutH = new double **[TBL_SIZE];
    c3d_lutS = new double **[TBL_SIZE];
    c3d_lutI = new double **[TBL_SIZE];
    c3d_lutV = new double **[TBL_SIZE];
    for (int i = 0; i < TBL_SIZE; i++) {
	c3d_lutR[i] = new double *[TBL_SIZE];
	c3d_lutG[i] = new double *[TBL_SIZE];
	c3d_lutB[i] = new double *[TBL_SIZE];
	c3d_lutH[i] = new double *[TBL_SIZE];
	c3d_lutS[i] = new double *[TBL_SIZE];
	c3d_lutI[i] = new double *[TBL_SIZE];
	c3d_lutV[i] = new double *[TBL_SIZE];
	for (int j = 0; j < TBL_SIZE; j++) {
	    c3d_lutR[i][j] = new double[TBL_SIZE];
	    c3d_lutG[i][j] = new double[TBL_SIZE];
	    c3d_lutB[i][j] = new double[TBL_SIZE];
	    c3d_lutH[i][j] = new double[TBL_SIZE];
	    c3d_lutS[i][j] = new double[TBL_SIZE];
	    c3d_lutI[i][j] = new double[TBL_SIZE];
	    c3d_lutV[i][j] = new double[TBL_SIZE];
	}
    }

    //===================================================================/
    //排列lookup table 成儲存格式時使用的陣列
    c3d_r = new int *[2];
    c3d_g = new int *[2];
    c3d_b = new int *[2];
    for (int i = 0; i < 2; i++) {
	c3d_r[i] = new int[total_len];
	c3d_g[i] = new int[total_len];
	c3d_b[i] = new int[total_len];
    }

    //===================================================================/

    //計算時使用的暫存lookup table
    tmp_c3d_lutR = new double **[TBL_SIZE];
    tmp_c3d_lutG = new double **[TBL_SIZE];
    tmp_c3d_lutB = new double **[TBL_SIZE];
    tmp_c3d_lutH = new double **[TBL_SIZE];
    tmp_c3d_lutS = new double **[TBL_SIZE];
    tmp_c3d_lutV = new double **[TBL_SIZE];
    for (int i = 0; i < TBL_SIZE; i++) {
	tmp_c3d_lutR[i] = new double *[TBL_SIZE];
	tmp_c3d_lutG[i] = new double *[TBL_SIZE];
	tmp_c3d_lutB[i] = new double *[TBL_SIZE];
	tmp_c3d_lutH[i] = new double *[TBL_SIZE];
	tmp_c3d_lutS[i] = new double *[TBL_SIZE];
	tmp_c3d_lutV[i] = new double *[TBL_SIZE];
	for (int j = 0; j < TBL_SIZE; j++) {
	    tmp_c3d_lutR[i][j] = new double[TBL_SIZE];
	    tmp_c3d_lutG[i][j] = new double[TBL_SIZE];
	    tmp_c3d_lutB[i][j] = new double[TBL_SIZE];
	    tmp_c3d_lutH[i][j] = new double[TBL_SIZE];
	    tmp_c3d_lutS[i][j] = new double[TBL_SIZE];
	    tmp_c3d_lutV[i][j] = new double[TBL_SIZE];
	}
    }

    // Temperary record PointColor (the values in adjust)
    int range = 1 + PointColor_D * 2;
    range = pow(range, 3);
    PointColor_array = new double *[range];
    for (int i = 0; i < range; i++)
	PointColor_array[i] = new double[6];
}

//---------------------------------------------------------------------------
void TC3DForm1::delete_array()
{
    for (int i = 0; i < TBL_SIZE; i++) {
	for (int j = 0; j < TBL_SIZE; j++) {
	    delete[]c3d_lutR[i][j];
	    delete[]c3d_lutG[i][j];
	    delete[]c3d_lutB[i][j];
	    delete[]c3d_lutH[i][j];
	    delete[]c3d_lutS[i][j];
	    delete[]c3d_lutI[i][j];
	    delete[]c3d_lutV[i][j];
	}
	delete[]c3d_lutR[i];
	delete[]c3d_lutG[i];
	delete[]c3d_lutB[i];
	delete[]c3d_lutH[i];
	delete[]c3d_lutS[i];
	delete[]c3d_lutI[i];
	delete[]c3d_lutV[i];
    }
    delete[]c3d_lutR;
    delete[]c3d_lutG;
    delete[]c3d_lutB;
    delete[]c3d_lutH;
    delete[]c3d_lutS;
    delete[]c3d_lutI;
    delete[]c3d_lutV;

    //================================================================//

    for (int i = 0; i < 2; i++) {
	delete[]c3d_r[i];
	delete[]c3d_g[i];
	delete[]c3d_b[i];
    }
    delete[]c3d_r;
    delete[]c3d_g;
    delete[]c3d_b;

    //================================================================//

    for (int i = 0; i < TBL_SIZE; i++) {
	for (int j = 0; j < TBL_SIZE; j++) {
	    delete[]tmp_c3d_lutR[i][j];
	    delete[]tmp_c3d_lutG[i][j];
	    delete[]tmp_c3d_lutB[i][j];
	    delete[]tmp_c3d_lutH[i][j];
	    delete[]tmp_c3d_lutS[i][j];
	    delete[]tmp_c3d_lutV[i][j];

	}
	delete[]tmp_c3d_lutR[i];
	delete[]tmp_c3d_lutG[i];
	delete[]tmp_c3d_lutB[i];
	delete[]tmp_c3d_lutH[i];
	delete[]tmp_c3d_lutS[i];
	delete[]tmp_c3d_lutV[i];
    }
    delete[]tmp_c3d_lutR;
    delete[]tmp_c3d_lutG;
    delete[]tmp_c3d_lutB;
    delete[]tmp_c3d_lutH;
    delete[]tmp_c3d_lutS;
    delete[]tmp_c3d_lutV;

    //====================================================================
    int range = 1 + PointColor_D * 2;
    range = pow(range, 3);
    for (int i = 0; i < range; i++)
	delete[]PointColor_array[i];
    delete[]PointColor_array;
}

//---------------------------------------------------------------------------
void TC3DForm1::Ini_c3d_table()
{
    for (int i = 0; i < TBL_SIZE; i++) {
	for (int j = 0; j < TBL_SIZE; j++) {
	    for (int k = 0; k < TBL_SIZE; k++) {
		c3d_lutR[i][j][k] = tbl_val[tbl_s][i];
		c3d_lutG[i][j][k] = tbl_val[tbl_s][j];
		c3d_lutB[i][j][k] = tbl_val[tbl_s][k];
		rgb2hsv(c3d_lutR[i][j][k], c3d_lutG[i][j][k], c3d_lutB[i][j][k],
			&c3d_lutH[i][j][k], &c3d_lutS[i][j][k], &c3d_lutI[i][j][k],
			&c3d_lutV[i][j][k]);

		tmp_c3d_lutR[i][j][k] = tbl_val[tbl_s][i];
		tmp_c3d_lutG[i][j][k] = tbl_val[tbl_s][j];
		tmp_c3d_lutB[i][j][k] = tbl_val[tbl_s][k];
		tmp_c3d_lutH[i][j][k] = c3d_lutH[i][j][k];
		tmp_c3d_lutS[i][j][k] = c3d_lutS[i][j][k];
		tmp_c3d_lutV[i][j][k] = c3d_lutV[i][j][k];
	    }
	}
    }
    double r = StrToFloat(lb_c3d_selR->Caption);
    double g = StrToFloat(lb_c3d_selG->Caption);
    double b = StrToFloat(lb_c3d_selB->Caption);
    Show_c3d_SelImg(r, g, b);
}

//---------------------------------------------------------------------------
//initianl 3D lookup table or initial table value from file
void TC3DForm1::C3Dini()
{
    Ini_c3d_table();
    ShowImageColor(img_color, 255, 255, 255);
    Show_c3d_Img_sim();
    Show_c3d_SelImg(255, 255, 255);
    Show_c3d_CorImg(255, 255, 255);
    Show_c3d_TblImg(255, 255, 255);
    Show_c3d_SimImg(255, 255, 255);
    refresh_6axis_grid(255, 255, 255);

    PointColor_array_nbr = 0;
}

//---------------------------------------------------------------------------
void TC3DForm1::Show_c3d_TblImg(double tbl_r, double tbl_g, double tbl_b)
{
    if (tbl_r == 256)
	tbl_r = 256 - 1.0 / Ratio;
    if (tbl_g == 256)
	tbl_g = 256 - 1.0 / Ratio;
    if (tbl_b == 256)
	tbl_b = 256 - 1.0 / Ratio;

    double tbl_h, tbl_s, tbl_i, tbl_v;
    rgb2hsv(tbl_r, tbl_g, tbl_b, &tbl_h, &tbl_s, &tbl_i, &tbl_v);
    tbl_i = (double (int (tbl_i * 10))) /10.0;
    tbl_h = (double (int (tbl_h * 100))) /100.0;
    tbl_s = (double (int (tbl_s * 1000))) /1000.0;
    tbl_v = (double (int (tbl_v * 10))) /10.0;
    lb_c3d_tblR->Caption = IntToStr((int) tbl_r);
    lb_c3d_tblG->Caption = IntToStr((int) tbl_g);
    lb_c3d_tblB->Caption = IntToStr((int) tbl_b);
    lb_c3d_tblH->Caption = FloatToStr(tbl_h);
    lb_c3d_tblS->Caption = FloatToStr(tbl_s);
    lb_c3d_tblI->Caption = FloatToStr(tbl_i);
    lb_c3d_tblV->Caption = FloatToStr(tbl_v);

    ShowImageColor(Img_c3d_tbl, tbl_r, tbl_g, tbl_b);
}

//---------------------------------------------------------------------------
void c3d_find_point(int tbl_l, int tbl_n, double r, double g, double b, int *idx_r, int *idx_g,
		    int *idx_b)
{
    //找最接近的點
    double t_r = fmod(r, cube_dis);
    if (t_r > cube_dis / 2) {
	*idx_r = (r - t_r) / cube_dis + 1;
    } else {
	*idx_r = (r - t_r) / cube_dis;
    }

    double t_g = fmod(g, cube_dis);
    if (t_g > cube_dis / 2)
	*idx_g = (g - t_g) / cube_dis + 1;
    else
	*idx_g = (g - t_g) / cube_dis;

    double t_b = fmod(b, cube_dis);
    if (t_b > cube_dis / 2)
	*idx_b = (b - t_b) / cube_dis + 1;
    else
	*idx_b = (b - t_b) / cube_dis;
}

void TC3DForm1::Show_c3d_SelImg(double sel_r, double sel_g, double sel_b)
{
    if (sel_r == 256)
	sel_r = 256 - 1.0 / Ratio;
    if (sel_g == 256)
	sel_g = 256 - 1.0 / Ratio;
    if (sel_b == 256)
	sel_b = 256 - 1.0 / Ratio;

    double sel_h, sel_s, sel_i, sel_v;
    rgb2hsv(sel_r, sel_g, sel_b, &sel_h, &sel_s, &sel_i, &sel_v);
    sel_i = (double (int (sel_i * 10))) /10.0;
    sel_h = (double (int (sel_h * 100))) /100.0;
    sel_s = (double (int (sel_s * 1000))) /1000.0;
    sel_v = (double (int (sel_v * 10))) /10.0;
    lb_c3d_selR->Caption = FloatToStr(double ((int) sel_r * 100) / 100);
    lb_c3d_selG->Caption = FloatToStr(double ((int) sel_g * 100) / 100);
    lb_c3d_selB->Caption = FloatToStr(double ((int) sel_b * 100) / 100);
    lb_c3d_selH->Caption = FloatToStr(sel_h);
    lb_c3d_selS->Caption = FloatToStr(sel_s);
    lb_c3d_selI->Caption = FloatToStr(sel_i);
    lb_c3d_selV->Caption = FloatToStr(sel_v);

    ShowImageColor(Img_c3d_sel, sel_r, sel_g, sel_b);
}
void TC3DForm1::Show_c3d_CorImg(double cor_r, double cor_g, double cor_b)
{
    if (cor_r >= 256)
	cor_r = 256 - 1.0 / Ratio;
    if (cor_g >= 256)
	cor_g = 256 - 1.0 / Ratio;
    if (cor_b >= 256)
	cor_b = 256 - 1.0 / Ratio;

    double cor_h, cor_s, cor_i, cor_v;
    rgb2hsv(cor_r, cor_g, cor_b, &cor_h, &cor_s, &cor_i, &cor_v);
    cor_i = (double (int (cor_i * 10))) /10.0;
    cor_h = (double (int (cor_h * 100))) /100.0;
    cor_s = (double (int (cor_s * 100))) /100.0;
    cor_v = (double (int (cor_v * 10))) /10.0;
    lb_c3d_corR->Caption = IntToStr((int) cor_r);
    lb_c3d_corG->Caption = IntToStr((int) cor_g);
    lb_c3d_corB->Caption = IntToStr((int) cor_b);
    lb_c3d_corH->Caption = FloatToStr(cor_h);
    lb_c3d_corS->Caption = FloatToStr(cor_s);
    lb_c3d_corI->Caption = FloatToStr(cor_i);
    lb_c3d_corV->Caption = FloatToStr(cor_v);

    ShowImageColor(Img_c3d_cor, cor_r, cor_g, cor_b);
}

//---------------------------------------------------------------------------
void TC3DForm1::Show_c3d_SimImg(double sim_r, double sim_g, double sim_b)
{
    if (sim_r == 256)
	sim_r = 256 - 1.0 / Ratio;
    if (sim_g == 256)
	sim_g = 256 - 1.0 / Ratio;
    if (sim_b == 256)
	sim_b = 256 - 1.0 / Ratio;

    double sim_h, sim_s, sim_i, sim_v;
    rgb2hsv(sim_r, sim_g, sim_b, &sim_h, &sim_s, &sim_i, &sim_v);
    sim_i = (double (int (sim_i * 10))) /10.0;
    sim_h = (double (int (sim_h * 100))) /100.0;
    sim_s = (double (int (sim_s * 1000))) /1000.0;
    sim_v = (double (int (sim_v * 10))) /10.0;
    lb_c3d_simR->Caption = FloatToStr(double (int (sim_r * 100)) / 100);
    lb_c3d_simG->Caption = FloatToStr(double (int (sim_g * 100)) / 100);
    lb_c3d_simB->Caption = FloatToStr(double (int (sim_b * 100)) / 100);
    lb_c3d_simH->Caption = FloatToStr(sim_h);
    lb_c3d_simS->Caption = FloatToStr(sim_s);
    lb_c3d_simI->Caption = FloatToStr(sim_i);
    lb_c3d_simV->Caption = FloatToStr(sim_v);

    ShowImageColor(Img_c3d_sim, sim_r, sim_g, sim_b);

    if (pc_Adjust->TabIndex == 0 && pc_global_adj->TabIndex == 1) {
	Edit_c3d_Manual39_h_adj->Text = FloatToStr(sim_h);
	Edit_c3d_Manual39_s_adj->Text = FloatToStr(sim_s);
	Edit_c3d_Manual39_v_adj->Text = FloatToStr(sim_v);
    } else if (pc_Adjust->TabIndex == 1 && pc_point_color_adj->TabIndex == 1) {
	Edit_c3d_Point_HSV_h_adj->Text = FloatToStr(sim_h);
	Edit_c3d_Point_HSV_s_adj->Text = FloatToStr(sim_s);
	Edit_c3d_Point_HSV_v_adj->Text = FloatToStr(sim_v);
    }
}

// 將單一顏色r,g,b畫到img上
void TC3DForm1::ShowImageColor(TImage * img, double r, double g, double b)
{
    Graphics::TBitmap * TmpBitmap;
    TmpBitmap = new Graphics::TBitmap();
    TmpBitmap->Width = img->Width;
    TmpBitmap->Height = img->Height;

    TmpBitmap->Canvas->Brush->Color = (TColor) RGB(r, g, b);
    TmpBitmap->Canvas->Rectangle(0, 0, TmpBitmap->Width, TmpBitmap->Height);
    img->Canvas->Draw(0, 0, TmpBitmap);
    delete TmpBitmap;
}

void TC3DForm1::Show_c3d_Img_sim()
{
    double r, g, b, r_new, g_new, b_new;
    int color[4];
    int x = img_sim->Width / 2;
    int y = img_sim->Height / 2;
    color[0] = img_color->Canvas->Pixels[10][10];
    color[1] = img_color->Canvas->Pixels[x + 10][10];
    color[2] = img_color->Canvas->Pixels[10][y + 10];
    color[3] = img_color->Canvas->Pixels[x + 10][y + 10];

    Graphics::TBitmap * TmpBitmap = new Graphics::TBitmap();
    if ((color[0] == color[1]) && (color[0] == color[2]) && (color[0] == color[3])) {
	//Simulate Color
	TmpBitmap->Width = img_sim->Width;
	TmpBitmap->Height = img_sim->Height;

	double r, g, b, r_new, g_new, b_new;
	int color = img_color->Canvas->Pixels[10][10];
	b = color / 65536;
	g = color / 256 % 256;
	r = color % 256;

	C3Dsim_t(r, g, b, &r_new, &g_new, &b_new);
	TmpBitmap->Canvas->Brush->Color = (TColor) RGB(r_new, g_new, b_new);
	TmpBitmap->Canvas->Rectangle(0, 0, TmpBitmap->Width, TmpBitmap->Height);
	img_sim->Canvas->Draw(0, 0, TmpBitmap);
    } else {			// Simulate 影像
	TmpBitmap->Width = img_color->Width / 2;
	TmpBitmap->Height = img_color->Height / 2;

	for (int i = 0; i < 4; i++) {
	    if (color[i] == -1)
		color[i] = 0;

	    b = color[i] / 65536;
	    g = color[i] / 256 % 256;
	    r = color[i] % 256;
	    C3Dsim_t(r, g, b, &r_new, &g_new, &b_new);
	    TmpBitmap->Canvas->Brush->Color = (TColor) RGB(r_new, g_new, b_new);
	    TmpBitmap->Canvas->Rectangle(0, 0, TmpBitmap->Width, TmpBitmap->Height);
	    if (i == 0)
		img_sim->Canvas->Draw(0, 0, TmpBitmap);
	    else if (i == 1)
		img_sim->Canvas->Draw(x, 0, TmpBitmap);
	    else if (i == 2)
		img_sim->Canvas->Draw(0, y, TmpBitmap);
	    else
		img_sim->Canvas->Draw(x, y, TmpBitmap);
	}
    }

    delete TmpBitmap;
}

//--------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_c3d_load_imgClick(TObject * Sender)
{
    AnsiString S1;
    Graphics::TBitmap * OrgBitmap = new Graphics::TBitmap();

    if (OpenDialog_img->Execute()) {
	S1 = OpenDialog_img->FileName;

	AnsiString curExt = LowerCase(ExtractFileExt(S1));
	TJPEGImage *JPEG = new TJPEGImage;
	Graphics::TBitmap * bitmap = new Graphics::TBitmap();

	if (curExt == ".jpg" || curExt == ".jpeg" || curExt == ".JPG") {
	    JPEG->Performance = jpBestQuality;
	    JPEG->LoadFromFile(S1);
	    JPEG->CompressionQuality = 100;

	    // bitmap->Width = JPEG->Width;     //放到bitmap裡, 自己寫resize
	    // bitmap->Height = JPEG->Height;
	    // bitmap->Assign(JPEG);

	    if (JPEG->Width > Img_3DLUT->Width * 4 + Img_3DLUT->Width * 2) {
		JPEG->Scale = jsEighth;
	    } else if (JPEG->Width > Img_3DLUT->Width * 2 + Img_3DLUT->Width) {
		JPEG->Scale = jsQuarter;
	    } else if (JPEG->Width > Img_3DLUT->Width + Img_3DLUT->Width) {
		JPEG->Scale = jsHalf;
	    } else {
		JPEG->Scale = jsFullSize;
	    }
	    Img_3DLUT->Width = JPEG->Width;
	    Img_3DLUT->Height = JPEG->Height;
	    Img_3DLUT->Picture->Bitmap->Assign(JPEG);

	} else if (curExt == ".bmp" || curExt == ".BMP" || curExt == ".Bitmap") {
	    Img_3DLUT->Picture->LoadFromFile(S1);
	    /* Graphics::TBitmap *pi = new Graphics::TBitmap();
	       try{
	       pi->LoadFromFile(S1);
	       Img_3DLUT->Width = pi->Width;
	       Img_3DLUT->Height = pi->Height;
	       Img_3DLUT->Canvas->Draw(0,0,pi);

	       }
	       __finally{
	       delete pi;
	       } */
	}
	delete bitmap;
	delete JPEG;
	OrgBitmap->Assign(Img_3DLUT->Picture->Bitmap);
	if (pc_img->TabIndex == 0)
	    Form_in_target->img_in_target->Picture->Bitmap->Assign(Img_3DLUT->Picture->Bitmap);
    }
    delete OrgBitmap;

    edt_show_h->Visible = false;
}

//---------------------------------------------------------------------------
void TC3DForm1::calculate_disc()
{				//Measure discontinue by caculate difference at r+/-1,g+/-1, b+/-1, idea by NCTU
    //C3D_SimualteForm = new TC3D_SimualteForm(this);
    btn_c3d_sim->Enabled = false;
    int x = Img_3DLUT->Picture->Width;
    int y = Img_3DLUT->Picture->Height;

    //c3d_tmp_tbl_save();
    if (pc_Adjust->TabIndex == 1 && pc_point_color_adj->TabIndex == 1) {	//Point Color-HSV Domain
	if (rg_c3d_hsv_mode->ItemIndex == 0)	//method 1 (三種HSV漸層法, 一為單純的hsv, 二為...)
	    c3d_hsvBase_adj(true);
    }
    double r, g, b, r_new, g_new, b_new;
    double r_new_dis, g_new_dis, b_new_dis, r_new_tol, g_new_tol, b_new_tol;
    double r_new_d, g_new_d, b_new_d, tol, disc;
    double r_new_tol1, g_new_tol1, b_new_tol1;
    BYTE *p_Img, *p_Sim_Img1, *p_Sim_Img_Dif;
    C3D_SimualteForm->Image1->Picture->Bitmap = Img_3DLUT->Picture->Bitmap;
    C3D_SimualteForm->Img_diff->Picture->Bitmap = Img_3DLUT->Picture->Bitmap;
    for (int i = 0; i < y; i++) {
	p_Img = (BYTE *) Img_3DLUT->Picture->Bitmap->ScanLine[i];
	p_Sim_Img1 = (BYTE *) C3D_SimualteForm->Image1->Picture->Bitmap->ScanLine[i];
	p_Sim_Img_Dif = (BYTE *) C3D_SimualteForm->Img_diff->Picture->Bitmap->ScanLine[i];
	for (int j = 0; j < x * 3; j += 3) {
	    b = p_Img[j];
	    g = p_Img[j + 1];
	    r = p_Img[j + 2];

	    r_new_tol = 0;
	    g_new_tol = 0;
	    b_new_tol = 0;
	    r_new_tol1 = 0;
	    g_new_tol1 = 0;
	    b_new_tol1 = 0;

	    C3Dsim(r, g, b, &r_new, &g_new, &b_new);
	    p_Sim_Img1[j] = (BYTE) b_new;
	    p_Sim_Img1[j + 1] = (BYTE) g_new;
	    p_Sim_Img1[j + 2] = (BYTE) r_new;

	    C3Dsim((r + 1 > 255 ? 255 : r + 1), g, b, &r_new_dis, &g_new_dis, &b_new_dis);
	    r_new_tol += r_new_dis;
	    g_new_tol += g_new_dis;
	    b_new_tol += b_new_dis;
	    r_new_tol1 += fabs(r_new_dis - r_new);
	    g_new_tol1 += fabs(g_new_dis - g_new);
	    b_new_tol1 += fabs(b_new_dis - b_new);

	    C3Dsim((r - 1 < 0 ? 0 : r - 1), g, b, &r_new_dis, &g_new_dis, &b_new_dis);
	    r_new_tol += r_new_dis;
	    g_new_tol += g_new_dis;
	    b_new_tol += b_new_dis;

	    r_new_tol1 += fabs(r_new_dis - r_new);
	    g_new_tol1 += fabs(g_new_dis - g_new);
	    b_new_tol1 += fabs(b_new_dis - b_new);

	    C3Dsim(r, (g + 1 > 255 ? 255 : g + 1), b, &r_new_dis, &g_new_dis, &b_new_dis);
	    r_new_tol += r_new_dis;
	    g_new_tol += g_new_dis;
	    b_new_tol += b_new_dis;

	    r_new_tol1 += fabs(r_new_dis - r_new);
	    g_new_tol1 += fabs(g_new_dis - g_new);
	    b_new_tol1 += fabs(b_new_dis - b_new);

	    C3Dsim(r, (g - 1 < 0 ? 0 : g - 1), b, &r_new_dis, &g_new_dis, &b_new_dis);
	    r_new_tol += r_new_dis;
	    g_new_tol += g_new_dis;
	    b_new_tol += b_new_dis;

	    r_new_tol1 += fabs(r_new_dis - r_new);
	    g_new_tol1 += fabs(g_new_dis - g_new);
	    b_new_tol1 += fabs(b_new_dis - b_new);

	    C3Dsim(r, g, (b + 1 > 255 ? 255 : b + 1), &r_new_dis, &g_new_dis, &b_new_dis);
	    r_new_tol += r_new_dis;
	    g_new_tol += g_new_dis;
	    b_new_tol += b_new_dis;

	    r_new_tol1 += fabs(r_new_dis - r_new);
	    g_new_tol1 += fabs(g_new_dis - g_new);
	    b_new_tol1 += fabs(b_new_dis - b_new);

	    C3Dsim(r, g, (b - 1 < 0 ? 0 : b - 1), &r_new_dis, &g_new_dis, &b_new_dis);
	    r_new_tol += r_new_dis;
	    g_new_tol += g_new_dis;
	    b_new_tol += b_new_dis;

	    r_new_tol1 += fabs(r_new_dis - r_new);
	    g_new_tol1 += fabs(g_new_dis - g_new);
	    b_new_tol1 += fabs(b_new_dis - b_new);

	    r_new_d = fabs(r_new_tol1 / 6);
	    g_new_d = fabs(g_new_tol1 / 6);
	    b_new_d = fabs(b_new_tol1 / 6);

	    if (cb_sim_type->ItemIndex == 1) {
		//C3D_SimualteForm->Img_diff->Canvas->Pixels[i][j] = (TColor)RGB(r_new_d*10,g_new_d*10,b_new_d*10);
		p_Sim_Img_Dif[j] = (BYTE) (b_new_d * 20);
		p_Sim_Img_Dif[j + 1] = (BYTE) (g_new_d * 20);
		p_Sim_Img_Dif[j + 2] = (BYTE) (r_new_d * 20);

	    } else if (cb_sim_type->ItemIndex == 2) {
		//C3D_SimualteForm->Img_diff->Canvas->Pixels[i][j] = (TColor)RGB(r_new_d*28/10,g_new_d*151/10,b_new_d*77/10);
		p_Sim_Img_Dif[j] = (BYTE) (b_new_d * 77 / 10);
		p_Sim_Img_Dif[j + 1] = (BYTE) (g_new_d * 151 / 10);
		p_Sim_Img_Dif[j + 2] = (BYTE) (r_new_d * 28 / 10);

	    } else if (cb_sim_type->ItemIndex == 3) {
		//tol = (r_new_d+g_new_d+b_new_d)*60;
		disc = pow(pow(r_new_tol / 6 - r_new, 2) + pow(g_new_tol / 6 - g_new, 2)
			   + pow(b_new_tol / 6 - b_new, 2), 0.5);
		tol = disc * 60;
		p_Sim_Img_Dif[j] = (BYTE) tol;
		p_Sim_Img_Dif[j + 1] = (BYTE) tol;
		p_Sim_Img_Dif[j + 2] = (BYTE) tol;
		//C3D_SimualteForm->Img_diff->Canvas->Pixels[i][j] = (TColor)RGB(tol,tol,tol);

	    } else if (cb_sim_type->ItemIndex == 4) {
		tol = (r_new_d * 28 + g_new_d * 151 + b_new_d * 77) / 17 * 12;
		p_Sim_Img_Dif[j] = (BYTE) tol;
		p_Sim_Img_Dif[j + 1] = (BYTE) tol;
		p_Sim_Img_Dif[j + 2] = (BYTE) tol;
		//C3D_SimualteForm->Img_diff->Canvas->Pixels[i][j] = (TColor)RGB(tol,tol,tol);
	    }
	}
    }
    C3D_SimualteForm->lb_hsv_adj_h->Caption = FloatToStr(GetPointH_val());
    C3D_SimualteForm->lb_hsv_adj_s->Caption = IntToStr(GetPointS_val());
    C3D_SimualteForm->lb_hsv_adj_v->Caption = IntToStr(GetPointV_val());
    c3d_scrollbar_reset();
    btn_c3d_sim->Enabled = true;
    C3D_SimualteForm->Show();
}

void TC3DForm1::calculate_HSV_disc()
{
    //C3D_SimualteForm = new TC3D_SimualteForm(this);
    btn_c3d_sim->Enabled = false;
    int x = Img_3DLUT->Picture->Width;
    int y = Img_3DLUT->Picture->Height;
    int color;

    if (pc_Adjust->TabIndex == 1 && pc_point_color_adj->TabIndex == 1) {	//Point Color - HSV Domain
	if (rg_c3d_hsv_mode->ItemIndex == 0)	//method 1
	    c3d_hsvBase_adj(true);
    }
    double col[3], col_vn[3], col_hn[3];	//col(current): 0:R, 1:G, 2:B,
    //col_vn: Vertical next, col_hn: Horizontal next
    double col_sim[3], col_vn_sim[3], col_hn_sim[3];
    double col_h_dis[3], col_v_dis[3];	//col_h_dis: Horizontal distance,
    //col_v_dis: Vertical distance
    double h[2], s[2], v[2], intance[2];
    double max_h_dis = 0.0, max_s_dis = 0.0, max_v_dis = 0.0;

    BYTE *p_Img, *p_Img_n_row, *p_Sim_Img, *p_diff_img_h, *p_diff_img_s, *p_diff_img_v;
    C3D_SimualteForm->Image1->Picture->Bitmap = Img_3DLUT->Picture->Bitmap;
    C3D_SimualteForm->Image_h->Picture->Bitmap = Img_3DLUT->Picture->Bitmap;
    C3D_SimualteForm->Image_s->Picture->Bitmap = Img_3DLUT->Picture->Bitmap;
    C3D_SimualteForm->Image_v->Picture->Bitmap = Img_3DLUT->Picture->Bitmap;
    //C3D_SimualteForm->Image_v->Picture->Bitmap = Img_3DLUT->Picture->Bitmap;
    double tmp, tmp_s, tmp_v;
    int next_i, next_j;

    for (int i = 0; i < y; i++) {
	p_Img = (BYTE *) Img_3DLUT->Picture->Bitmap->ScanLine[i];
	next_i = (i + 1 >= y ? i : i + 1);
	p_Img_n_row = (BYTE *) Img_3DLUT->Picture->Bitmap->ScanLine[next_i];
	p_Sim_Img = (BYTE *) C3D_SimualteForm->Image1->Picture->Bitmap->ScanLine[i];
	p_diff_img_h = (BYTE *) C3D_SimualteForm->Image_h->Picture->Bitmap->ScanLine[i];
	p_diff_img_s = (BYTE *) C3D_SimualteForm->Image_s->Picture->Bitmap->ScanLine[i];
	p_diff_img_v = (BYTE *) C3D_SimualteForm->Image_v->Picture->Bitmap->ScanLine[i];

	for (int j = 0; j < x * 3; j += 3) {
	    next_j = (j + 3 >= x * 3 ? j : j + 3);
	    for (int c = 0; c < 3; c++) {
		col[2 - c] = p_Img[j + c];
		col_vn[2 - c] = p_Img_n_row[j + c];
		col_hn[2 - c] = p_Img[next_j + c];
	    }
	    //Simulate current color to adjust
	    C3Dsim(col[0], col[1], col[2], &col_sim[0], &col_sim[1], &col_sim[2]);
	    for (int c = 0; c < 3; c++) {
		p_Sim_Img[j + (2 - c)] = (BYTE) floor(col_sim[c]);
	    }
	    // h[0], s[0], v[0], intance[0] is current adjust color (hue, saturation, value, intensity)
	    rgb2hsv(col_sim[0], col_sim[1], col_sim[2], &h[0], &s[0], &intance[0], &v[0]);

	    C3Dsim(col_vn[0], col_vn[1], col_vn[2], &col_vn_sim[0], &col_vn_sim[1], &col_vn_sim[2]);	//vertical
	    // h[1], s[1], v[1], intance[1] is adjust color of next vertical (hue, saturation, value, intensity)
	    rgb2hsv(col_vn_sim[0], col_vn_sim[1], col_vn_sim[2], &h[1], &s[1], &intance[1], &v[1]);

	    tmp_s = fabs(s[0] - s[1]);
	    tmp_v = fabs(v[0] - v[1]) / (v[0] + v[1]);
	    for (int c = 0; c < 3; c++) {
		p_diff_img_s[j + c] = (BYTE) (tmp_s * 4096);	//Saturation
		p_diff_img_v[j + c] = (BYTE) (tmp_v * 20000);	//Value
	    }
	    if (tmp_s > max_s_dis)
		max_s_dis = tmp_s;
	    if (tmp_v > max_v_dis)
		max_v_dis = tmp_v;

	    C3Dsim(col_hn[0], col_hn[1], col_hn[2], &col_hn_sim[0], &col_hn_sim[1], &col_hn_sim[2]);	//horizontal
	    // h[1], s[1], v[1], intance[1] is adjust color of next horizontal (hue, saturation, value, intensity)
	    rgb2hsv(col_hn_sim[0], col_hn_sim[1], col_hn_sim[2], &h[1], &s[1], &intance[1], &v[1]);
	    tmp = fabs(h[0] - h[1]);	//Hue
	    tmp = fabs(tmp > 300 ? 360 - tmp : tmp);
	    if (tmp > max_h_dis)
		max_h_dis = tmp;

	    tmp = (tmp * 14 > 255 ? 255 : tmp * 14);
	    for (int c = 0; c < 3; c++) {
		p_diff_img_h[j + c] = (BYTE) tmp;
	    }
	}
    }

    C3D_SimualteForm->lb_hsv_adj_h->Caption = FloatToStr(GetPointH_val());
    C3D_SimualteForm->lb_hsv_adj_s->Caption = IntToStr(GetPointS_val());
    C3D_SimualteForm->lb_hsv_adj_v->Caption = IntToStr(GetPointV_val());
    c3d_scrollbar_reset();
    btn_c3d_sim->Enabled = true;
    C3D_SimualteForm->Show();
    String str;
/*
        double Array_hsv[3];
        Array_hsv[0]=max_h_dis;
        Array_hsv[0]=max_s_dis*/

    sprintf(str.c_str(), "Max dif---H:%2.6f, S:%2.6f, V:%2.6f", max_h_dis, max_s_dis, max_v_dis);
    C3D_SimualteForm->lb_hsv_dis_max->Caption = (AnsiString) str.c_str();
    String H_gain = sb_c3d_Point_HSV_hdp->Position;
    AnsiString FilePath = "Sim_" + H_gain + ".bmp";
    C3D_SimualteForm->Image1->Picture->SaveToFile(FilePath);
    FilePath = "Sim_dif_h" + H_gain + ".bmp";
    C3D_SimualteForm->Image_h->Picture->SaveToFile(FilePath);
    FilePath = "Sim_dif_s" + H_gain + ".bmp";
    C3D_SimualteForm->Image_s->Picture->SaveToFile(FilePath);
    FilePath = "Sim_dif_v" + H_gain + ".bmp";
    C3D_SimualteForm->Image_v->Picture->SaveToFile(FilePath);
}

void TC3DForm1::Caculate_dif_table(double ***c3d_dif_lutR, double ***c3d_dif_lutG,
				   double ***c3d_dif_lutB, double ***c3d_dif, int modif)
{
    for (int i = 1; i < TBL_SIZE; i++)
	for (int j = 1; j < TBL_SIZE; j++) {
	    c3d_dif_lutR[i][j][0] = 0;
	    c3d_dif_lutR[i][j][TBL_SIZE - 1] = 0;
	    c3d_dif_lutG[i][j][0] = 0;
	    c3d_dif_lutG[i][j][TBL_SIZE - 1] = 0;
	    c3d_dif_lutB[i][j][0] = 0;
	    c3d_dif_lutB[i][j][TBL_SIZE - 1] = 0;
	}
    for (int i = 1; i < TBL_SIZE; i++)
	for (int k = 1; k < TBL_SIZE; k++) {
	    c3d_dif_lutR[i][0][k] = 0;
	    c3d_dif_lutR[i][TBL_SIZE - 1][k] = 0;
	    c3d_dif_lutG[i][0][k] = 0;
	    c3d_dif_lutG[i][TBL_SIZE - 1][k] = 0;
	    c3d_dif_lutB[i][0][k] = 0;
	    c3d_dif_lutB[i][TBL_SIZE - 1][k] = 0;
	}
    for (int j = 1; j < TBL_SIZE; j++)
	for (int k = 1; k < TBL_SIZE; k++) {
	    c3d_dif_lutR[0][j][k] = 0;
	    c3d_dif_lutR[TBL_SIZE - 1][j][k] = 0;
	    c3d_dif_lutG[0][j][k] = 0;
	    c3d_dif_lutG[TBL_SIZE - 1][j][k] = 0;
	    c3d_dif_lutB[0][j][k] = 0;
	    c3d_dif_lutB[TBL_SIZE - 1][j][k] = 0;
	}

    if (modif == 1) {
	for (int i = 1; i < TBL_SIZE - 1; i++)
	    for (int j = 1; j < TBL_SIZE - 1; j++)
		for (int k = 1; k < TBL_SIZE - 1; k++) {
		    c3d_lutR[i][j][k] =
			(c3d_lutR[i - 1][j][k] + c3d_lutR[i + 1][j][k] + c3d_lutR[i][j - 1][k]
			 + c3d_lutR[i][j + 1][k] + c3d_lutR[i][j][k - 1] + c3d_lutR[i][j][k +
											  1]) / 6;

		    c3d_lutG[i][j][k] =
			(c3d_lutG[i - 1][j][k] + c3d_lutG[i + 1][j][k] + c3d_lutG[i][j - 1][k]
			 + c3d_lutG[i][j + 1][k] + c3d_lutG[i][j][k - 1] + c3d_lutG[i][j][k +
											  1]) / 6;

		    c3d_lutB[i][j][k] =
			(c3d_lutB[i - 1][j][k] + c3d_lutB[i + 1][j][k] + c3d_lutB[i][j - 1][k]
			 + c3d_lutB[i][j + 1][k] + c3d_lutB[i][j][k - 1] + c3d_lutB[i][j][k +
											  1]) / 6;
		}
    }
    for (int i = 1; i < TBL_SIZE - 1; i++)
	for (int j = 1; j < TBL_SIZE - 1; j++)
	    for (int k = 1; k < TBL_SIZE - 1; k++) {
		c3d_dif_lutR[i][j][k] =
		    (c3d_lutR[i - 1][j][k] + c3d_lutR[i + 1][j][k] + c3d_lutR[i][j - 1][k]
		     + c3d_lutR[i][j + 1][k] + c3d_lutR[i][j][k - 1] + c3d_lutR[i][j][k + 1]) / 6;
		c3d_dif_lutR[i][j][k] = c3d_lutR[i][j][k] - c3d_dif_lutR[i][j][k];

		c3d_dif_lutG[i][j][k] =
		    (c3d_lutG[i - 1][j][k] + c3d_lutG[i + 1][j][k] + c3d_lutG[i][j - 1][k]
		     + c3d_lutG[i][j + 1][k] + c3d_lutG[i][j][k - 1] + c3d_lutG[i][j][k + 1]) / 6;
		c3d_dif_lutG[i][j][k] = c3d_lutG[i][j][k] - c3d_dif_lutG[i][j][k];

		c3d_dif_lutB[i][j][k] =
		    (c3d_lutB[i - 1][j][k] + c3d_lutB[i + 1][j][k] + c3d_lutB[i][j - 1][k]
		     + c3d_lutB[i][j + 1][k] + c3d_lutB[i][j][k - 1] + c3d_lutB[i][j][k + 1]) / 6;
		c3d_dif_lutB[i][j][k] = c3d_lutB[i][j][k] - c3d_dif_lutB[i][j][k];

		c3d_dif[i][j][k] =
		    pow(pow(c3d_dif_lutR[i][j][k], 2) + pow(c3d_dif_lutG[i][j][k], 2) +
			pow(c3d_dif_lutB[i][j][k], 2), 0.5);
	    }

}
void TC3DForm1::C3Dsim_dif(double r, double g, double b, double *r_new, double *g_new,
			   double *b_new, double ***c3d_dif)
{
    //techehedral
    int idx_r, idx_g, idx_b;
    double v_r[2], v_g[2], v_b[2];

    for (int i = 0; i <= TBL_SIZE - 2; i++) {
	if (r >= tbl_val[tbl_s][i] && r <= tbl_val[tbl_s][i + 1]) {
	    v_r[0] = tbl_val[tbl_s][i];
	    v_r[1] = tbl_val[tbl_s][i + 1];
	    idx_r = i;
	    break;
	}
    }
    for (int i = 0; i <= TBL_SIZE - 2; i++) {
	if (g >= tbl_val[tbl_s][i] && g <= tbl_val[tbl_s][i + 1]) {
	    v_g[0] = tbl_val[tbl_s][i];
	    v_g[1] = tbl_val[tbl_s][i + 1];
	    idx_g = i;
	    break;
	}
    }
    for (int i = 0; i <= TBL_SIZE - 2; i++) {
	if (b >= tbl_val[tbl_s][i] && b <= tbl_val[tbl_s][i + 1]) {
	    v_b[0] = tbl_val[tbl_s][i];
	    v_b[1] = tbl_val[tbl_s][i + 1];
	    idx_b = i;
	    break;
	}
    }

    double P[2][2][2][3];
    // p[][][][0]=> red  p[][][][1]=> green  p[][][][2]=> blue
    for (int i = 0; i < 2; i++)
	for (int j = 0; j < 2; j++)
	    for (int k = 0; k < 2; k++) {
		P[i][j][k][0] = c3d_dif[idx_r + i][idx_g + j][idx_b + k];
		P[i][j][k][1] = c3d_dif[idx_r + i][idx_g + j][idx_b + k];
		P[i][j][k][2] = c3d_dif[idx_r + i][idx_g + j][idx_b + k];
	    }

    double dlt_x = (r - v_r[0]) / (v_r[1] - v_r[0]);
    double dlt_y = (g - v_g[0]) / (v_g[1] - v_g[0]);
    double dlt_z = (b - v_b[0]) / (v_b[1] - v_b[0]);

    if (interpol == true) {
	double C1[3], C2[3], C3[3];

	if (dlt_x >= dlt_y && dlt_y > dlt_z) {	//T1
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][0][0][c] - P[0][0][0][c];
		C2[c] = P[1][1][0][c] - P[1][0][0][c];
		C3[c] = P[1][1][1][c] - P[1][1][0][c];
	    }
	} else if (dlt_x > dlt_z && dlt_z >= dlt_y) {	//T2
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][0][0][c] - P[0][0][0][c];
		C2[c] = P[1][1][1][c] - P[1][0][1][c];
		C3[c] = P[1][0][1][c] - P[1][0][0][c];
	    }
	} else if (dlt_z >= dlt_x && dlt_x >= dlt_y) {	//T3
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][0][1][c] - P[0][0][1][c];
		C2[c] = P[1][1][1][c] - P[1][0][1][c];
		C3[c] = P[0][0][1][c] - P[0][0][0][c];
	    }
	} else if (dlt_y > dlt_x && dlt_x > dlt_z) {	//T4
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][1][0][c] - P[0][1][0][c];
		C2[c] = P[0][1][0][c] - P[0][0][0][c];
		C3[c] = P[1][1][1][c] - P[1][1][0][c];
	    }
	} else if (dlt_y > dlt_z && dlt_z >= dlt_x) {	//T5
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][1][1][c] - P[0][1][1][c];
		C2[c] = P[0][1][0][c] - P[0][0][0][c];
		C3[c] = P[0][1][1][c] - P[0][1][0][c];
	    }
	} else if (dlt_z >= dlt_y && dlt_y > dlt_x) {	//T6
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][1][1][c] - P[0][1][1][c];
		C2[c] = P[0][1][1][c] - P[0][0][1][c];
		C3[c] = P[0][0][1][c] - P[0][0][0][c];
	    }
	}

	double P_[3];
	for (int c = 0; c < 3; c++) {
	    P_[c] = P[0][0][0][c] + C1[c] * dlt_x + C2[c] * dlt_y + C3[c] * dlt_z;
	}

	*r_new = P_[0];
	*g_new = P_[1];
	*b_new = P_[2];
    } else {			//trilinear
	double i[2][3], j[2][3], w[2][3];

	for (int c = 0; c < 3; c++) {
	    i[0][c] = P[0][0][0][c] * (1 - dlt_x) + P[1][0][0][c] * dlt_x;
	    i[1][c] = P[0][1][0][c] * (1 - dlt_x) + P[1][1][0][c] * dlt_x;
	    j[0][c] = P[0][0][1][c] * (1 - dlt_x) + P[1][0][1][c] * dlt_x;
	    j[1][c] = P[0][1][1][c] * (1 - dlt_x) + P[1][1][1][c] * dlt_x;
	}
	for (int c = 0; c < 3; c++) {
	    w[0][c] = i[0][c] * (1 - dlt_y) + i[1][c] * dlt_y;
	    w[1][c] = j[0][c] * (1 - dlt_y) + j[1][c] * dlt_y;
	}
	*r_new = w[0][0] * (1 - dlt_z) + w[1][0] * dlt_z;
	*g_new = w[0][1] * (1 - dlt_z) + w[1][1] * dlt_z;
	*b_new = w[0][2] * (1 - dlt_z) + w[1][2] * dlt_z;
    }
}
void TC3DForm1::calculate_NCTU_dif()
{
    btn_c3d_sim->Enabled = false;

    if (pc_Adjust->TabIndex == 1 && pc_point_color_adj->TabIndex == 1) {	//Point Color - HSV Domain
	if (rg_c3d_hsv_mode->ItemIndex == 0)	//method 1
	    c3d_hsvBase_adj(true);
    }
    //Caculate Difference table
    //define table
    double ***c3d_dif_lutR = new double **[TBL_SIZE];
    double ***c3d_dif_lutG = new double **[TBL_SIZE];
    double ***c3d_dif_lutB = new double **[TBL_SIZE];
    double ***c3d_dif = new double **[TBL_SIZE];
    for (int i = 0; i < TBL_SIZE; i++) {
	c3d_dif_lutR[i] = new double *[TBL_SIZE];
	c3d_dif_lutG[i] = new double *[TBL_SIZE];
	c3d_dif_lutB[i] = new double *[TBL_SIZE];
	c3d_dif[i] = new double *[TBL_SIZE];
	for (int j = 0; j < TBL_SIZE; j++) {
	    c3d_dif_lutR[i][j] = new double[TBL_SIZE];
	    c3d_dif_lutG[i][j] = new double[TBL_SIZE];
	    c3d_dif_lutB[i][j] = new double[TBL_SIZE];
	    c3d_dif[i][j] = new double[TBL_SIZE];
	}
    }
    int modif = 0;		// modif = 1, do Consistensity modification function
    if (cb_sim_type->ItemIndex == 7)
	modif = 1;
    Caculate_dif_table(c3d_dif_lutR, c3d_dif_lutG, c3d_dif_lutB, c3d_dif, modif);

    //Simulate the difference in test image
    //C3D_SimualteForm = new TC3D_SimualteForm(this);
    int x = Img_3DLUT->Picture->Width;
    int y = Img_3DLUT->Picture->Height;
    //int color;
    double r, g, b, r_new, g_new, b_new;
    int max_dif = 0;

    BYTE *p_Img, *p_Sim_Img1, *p_Sim_Img_Dif;
    C3D_SimualteForm->Image1->Picture->Bitmap = Img_3DLUT->Picture->Bitmap;
    C3D_SimualteForm->Img_diff->Picture->Bitmap = Img_3DLUT->Picture->Bitmap;
    for (int i = 0; i < y; i++) {
	p_Img = (BYTE *) Img_3DLUT->Picture->Bitmap->ScanLine[i];
	p_Sim_Img1 = (BYTE *) C3D_SimualteForm->Image1->Picture->Bitmap->ScanLine[i];
	p_Sim_Img_Dif = (BYTE *) C3D_SimualteForm->Img_diff->Picture->Bitmap->ScanLine[i];
	for (int j = 0; j < x * 3; j += 3) {
	    r = p_Img[j + 2];
	    g = p_Img[j + 1];
	    b = p_Img[j + 0];

	    //According R,G,B value to find a different value
	    C3Dsim(r, g, b, &r_new, &g_new, &b_new);
	    p_Sim_Img1[j + 2] = r_new;
	    p_Sim_Img1[j + 1] = g_new;
	    p_Sim_Img1[j] = b_new;

	    C3Dsim_dif(r, g, b, &r_new, &g_new, &b_new, c3d_dif);
	    p_Sim_Img_Dif[j + 2] = r_new * 2;
	    p_Sim_Img_Dif[j + 1] = g_new * 2;
	    p_Sim_Img_Dif[j] = b_new * 2;

	    if ((int) r_new > max_dif)
		max_dif = (int) r_new;
	}
    }
    C3D_SimualteForm->lb_hsv_adj_h->Caption = FloatToStr(GetPointH_val());
    C3D_SimualteForm->lb_hsv_adj_s->Caption = IntToStr(GetPointS_val());
    C3D_SimualteForm->lb_hsv_adj_v->Caption = IntToStr(GetPointV_val());
    c3d_scrollbar_reset();
    btn_c3d_sim->Enabled = true;
    C3D_SimualteForm->Show();
    char str[20];
    sprintf(str, "max_dif: %3d", max_dif);
    C3D_SimualteForm->lb_hsv_dis_max->Caption = (AnsiString) str;
}


void __fastcall TC3DForm1::btn_c3d_simClick(TObject * Sender)
{
    // 計算差值
    if (cb_sim_type->ItemIndex == 1 || cb_sim_type->ItemIndex == 2
	|| cb_sim_type->ItemIndex == 3 || cb_sim_type->ItemIndex == 4) {
	//rgb diff(1), w diff(1), g diff(1), gw diff(1)
	calculate_disc();
	return;
    } else if (cb_sim_type->ItemIndex == 5) {
	// dH/dS/dV
	calculate_HSV_disc();
	return;
    } else if (cb_sim_type->ItemIndex == 6 || cb_sim_type->ItemIndex == 7) {
	// NCHU diff, NCTU modified
	calculate_NCTU_dif();
	return;
    }
    //=================================================================//

    //根據目前分頁, 決定simulate的影像
    TImage *tmp_img = new TImage(this);
    tmp_img = Img_3DLUT;
    pc_img->TabIndex = 0;
    ts_image->Show();
    /*
       if(pc_img->TabIndex == 0)
       //當simulate影像為讀入的圖片(image 分頁)
       tmp_img = Img_3DLUT;
       else if(pc_img->TabIndex == 1)
       //當Simulate影像為單一顏色(image分頁)
       tmp_img = img_color;
       else if(pc_img->TabIndex == 2){
       //當Simulate影像為單一顏色(Sim_color分頁)
       tmp_img = img_color;
       pc_img->TabIndex = 1;
       ts_color->Show();
       }else
       return;
     */

    //C3D_SimualteForm = new TC3D_SimualteForm(this);
    btn_c3d_sim->Enabled = false;
    int x = Img_3DLUT->Picture->Width;
    int y = Img_3DLUT->Picture->Height;
    C3D_SimualteForm->Image1->Width = Img_3DLUT->Picture->Width;
    C3D_SimualteForm->Image1->Height = Img_3DLUT->Picture->Height;

    int color;
    c3d_tmp_tbl_save();

    //根據目前分頁狀況決定diffusion的方法
    if (pc_Adjust->TabIndex == 1 && pc_point_color_adj->TabIndex == 0) {
	//Point Color RGB Diffusion
	cal_c3d_rgb(true);
	Reset_c3d_Point_RGB_Scroll();

    } else if (pc_Adjust->TabIndex == 0 && pc_global_adj->TabIndex == 1) {
	//Global manual 39 Point (HSV Diffusion)
	if (TBL_SIZE == 9)
	    Manual39_color_adj(true);
	else
	    ShowMessage("table size is not 9x9x9, do nothing.");

    } else if (pc_Adjust->TabIndex == 1 && pc_point_color_adj->TabIndex == 1) {
	if (rg_c3d_hsv_mode->ItemIndex == 0) {
	    // Point Color && HSV diffusion, method 1
	    c3d_hsvBase_adj(true);	//hsv adjust
	    Reset_c3d_Point_HSV_Scroll();
	    //}else if(rg_c3d_hsv_mode->ItemIndex==1){
	    //method 2, RGB 6 axis
	    //c3d_6axisAdj_h(true);
	    //c3d_6axisAdj_s(true);
	    //c3d_6axisAdj_v(true);*/
	} else if (rg_c3d_hsv_mode->ItemIndex == 2) {
	    //method 3, RGB+hsv diffusion
	    c3d_MixAdj_h(true);
	    //c3d_MixAdj_s(true);
	    //c3d_MixAdj_v(true);
	} else if (rg_c3d_hsv_mode->ItemIndex == 3) {
	    //method 4, HSV+fix
	    c3d_hsv_FixGain(true);
	}
    }
    // Simulate 影像
    double r, g, b, r_new, g_new, b_new;
    for (int i = 0; i < x; i++)
	for (int j = 0; j < y; j++) {
	    color = tmp_img->Canvas->Pixels[i][j];
	    if (color == -1)
		color = 0;

	    b = color / 65536;
	    g = color / 256 % 256;
	    r = color % 256;
	    C3Dsim(r, g, b, &r_new, &g_new, &b_new);
	    C3D_SimualteForm->Image1->Canvas->Pixels[i][j] = (TColor) RGB(r_new, g_new, b_new);
	}

    // simulate的hsv結果標示在simalate form
    C3D_SimualteForm->lb_hsv_adj_h->Caption = lb_c3d_simH->Caption;
    C3D_SimualteForm->lb_hsv_adj_s->Caption = lb_c3d_simS->Caption;
    C3D_SimualteForm->lb_hsv_adj_v->Caption = lb_c3d_simV->Caption;

    btn_c3d_sim->Enabled = true;
    BitBtn_c3d_undo->Enabled = true;
    C3D_SimualteForm->Show();
    C3D_SimualteForm->WindowState = wsNormal;
    cb_en->Checked = false;
    cb_enClick(Sender);
    /*
       if(!SaveDialog1->Execute()){
       return;
       }

       String Fpath = SaveDialog1->FileName;
       if(Fpath==NULL)
       return;

       FILE* fptr = fopen (Fpath.c_str(),"w");
       for(int i = 0; i < 15; i++)
       fprintf(fptr,"%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
       Y[i][0],Y[i][1],Y[i][2],Y[i][3],Y[i][4],Y[i][5],Y[i][6],Y[i][7],Y[i][8],Y[i][9],Y[i][10]);
       fclose(fptr);  */
    //C3D_SimualteForm->Image2->Picture->SaveToFile("dif_r.bmp");
    //C3D_SimualteForm->Image3->Picture->SaveToFile("dif_g.bmp");
    //C3D_SimualteForm->Image4->Picture->SaveToFile("dif_b.bmp");
}

//----------------------------------------------------------------------------
bool TC3DForm1::c3d_lutArrange()
{
    int idx = 0;

    // 1
    for (int k = 0; k < TBL_SIZE; k += 2)
	for (int j = 0; j < TBL_SIZE; j += 2)
	    for (int i = 0; i < TBL_SIZE; i += 2) {
		c3d_r[1][idx] = c3d_lutR[i][j][k] * Ratio;
		c3d_g[1][idx] = c3d_lutG[i][j][k] * Ratio;
		c3d_b[1][idx] = c3d_lutB[i][j][k] * Ratio;
		c3d_r[0][idx] = tbl_val[tbl_s][i];
		c3d_g[0][idx] = tbl_val[tbl_s][j];
		c3d_b[0][idx] = tbl_val[tbl_s][k];
		idx++;
	    }

    //2
    if (TBL_SIZE == 7) {
	for (int k = 0; k < TBL_SIZE; k += 2)
	    for (int i = 1; i < TBL_SIZE - 1; i += 2)
		for (int j = 0; j < TBL_SIZE; j += 2) {
		    c3d_r[1][idx] = c3d_lutR[i][j][k] * Ratio;
		    c3d_g[1][idx] = c3d_lutG[i][j][k] * Ratio;
		    c3d_b[1][idx] = c3d_lutB[i][j][k] * Ratio;
		    c3d_r[0][idx] = tbl_val[tbl_s][i];
		    c3d_g[0][idx] = tbl_val[tbl_s][j];
		    c3d_b[0][idx] = tbl_val[tbl_s][k];
		    idx++;
		}
    } else if (TBL_SIZE == 9 || TBL_SIZE == 17) {
	for (int k = 0; k < TBL_SIZE; k += 2)
	    for (int j = 0; j < TBL_SIZE; j += 2)
		for (int i = 1; i < TBL_SIZE - 1; i += 2) {
		    c3d_r[1][idx] = c3d_lutR[i][j][k] * Ratio;
		    c3d_g[1][idx] = c3d_lutG[i][j][k] * Ratio;
		    c3d_b[1][idx] = c3d_lutB[i][j][k] * Ratio;
		    c3d_r[0][idx] = tbl_val[tbl_s][i];
		    c3d_g[0][idx] = tbl_val[tbl_s][j];
		    c3d_b[0][idx] = tbl_val[tbl_s][k];
		    idx++;
		}
    }
    //3
    for (int k = 0; k < TBL_SIZE; k += 2)
	for (int j = 1; j < TBL_SIZE - 1; j += 2)
	    for (int i = 0; i < TBL_SIZE; i += 2) {
		c3d_r[1][idx] = c3d_lutR[i][j][k] * Ratio;
		c3d_g[1][idx] = c3d_lutG[i][j][k] * Ratio;
		c3d_b[1][idx] = c3d_lutB[i][j][k] * Ratio;
		c3d_r[0][idx] = tbl_val[tbl_s][i];
		c3d_g[0][idx] = tbl_val[tbl_s][j];
		c3d_b[0][idx] = tbl_val[tbl_s][k];
		idx++;
	    }
    //4
    for (int k = 0; k < TBL_SIZE; k += 2)
	for (int j = 1; j < TBL_SIZE - 1; j += 2)
	    for (int i = 1; i < TBL_SIZE - 1; i += 2) {
		c3d_r[1][idx] = c3d_lutR[i][j][k] * Ratio;
		c3d_g[1][idx] = c3d_lutG[i][j][k] * Ratio;
		c3d_b[1][idx] = c3d_lutB[i][j][k] * Ratio;
		c3d_r[0][idx] = tbl_val[tbl_s][i];
		c3d_g[0][idx] = tbl_val[tbl_s][j];
		c3d_b[0][idx] = tbl_val[tbl_s][k];
		idx++;
	    }
    //5
    for (int k = 1; k < TBL_SIZE - 1; k += 2)
	for (int j = 0; j < TBL_SIZE; j += 2)
	    for (int i = 0; i < TBL_SIZE; i += 2) {
		c3d_r[1][idx] = c3d_lutR[i][j][k] * Ratio;
		c3d_g[1][idx] = c3d_lutG[i][j][k] * Ratio;
		c3d_b[1][idx] = c3d_lutB[i][j][k] * Ratio;
		c3d_r[0][idx] = tbl_val[tbl_s][i];
		c3d_g[0][idx] = tbl_val[tbl_s][j];
		c3d_b[0][idx] = tbl_val[tbl_s][k];
		idx++;
	    }
    //6
    if (TBL_SIZE == 7) {
	for (int k = 1; k < TBL_SIZE - 1; k += 2)
	    for (int i = 1; i < TBL_SIZE - 1; i += 2)
		for (int j = 0; j < TBL_SIZE; j += 2) {
		    c3d_r[1][idx] = c3d_lutR[i][j][k] * Ratio;
		    c3d_g[1][idx] = c3d_lutG[i][j][k] * Ratio;
		    c3d_b[1][idx] = c3d_lutB[i][j][k] * Ratio;
		    c3d_r[0][idx] = tbl_val[tbl_s][i];
		    c3d_g[0][idx] = tbl_val[tbl_s][j];
		    c3d_b[0][idx] = tbl_val[tbl_s][k];
		    idx++;
		}
    } else if (TBL_SIZE == 9 || TBL_SIZE == 17) {
	for (int k = 1; k < TBL_SIZE - 1; k += 2)
	    for (int j = 0; j < TBL_SIZE; j += 2)
		for (int i = 1; i < TBL_SIZE - 1; i += 2) {
		    c3d_r[1][idx] = c3d_lutR[i][j][k] * Ratio;
		    c3d_g[1][idx] = c3d_lutG[i][j][k] * Ratio;
		    c3d_b[1][idx] = c3d_lutB[i][j][k] * Ratio;
		    c3d_r[0][idx] = tbl_val[tbl_s][i];
		    c3d_g[0][idx] = tbl_val[tbl_s][j];
		    c3d_b[0][idx] = tbl_val[tbl_s][k];
		    idx++;
		}
    }
    //7
    for (int k = 1; k < TBL_SIZE - 1; k += 2)
	for (int j = 1; j < TBL_SIZE - 1; j += 2)
	    for (int i = 0; i < TBL_SIZE; i += 2) {
		c3d_r[1][idx] = c3d_lutR[i][j][k] * Ratio;
		c3d_g[1][idx] = c3d_lutG[i][j][k] * Ratio;
		c3d_b[1][idx] = c3d_lutB[i][j][k] * Ratio;
		c3d_r[0][idx] = tbl_val[tbl_s][i];
		c3d_g[0][idx] = tbl_val[tbl_s][j];
		c3d_b[0][idx] = tbl_val[tbl_s][k];
		idx++;
	    }
    //8
    for (int k = 1; k < TBL_SIZE - 1; k += 2)
	for (int j = 1; j < TBL_SIZE - 1; j += 2)
	    for (int i = 1; i < TBL_SIZE - 0; i += 2) {
		c3d_r[1][idx] = c3d_lutR[i][j][k] * Ratio;
		c3d_g[1][idx] = c3d_lutG[i][j][k] * Ratio;
		c3d_b[1][idx] = c3d_lutB[i][j][k] * Ratio;
		c3d_r[0][idx] = tbl_val[tbl_s][i];
		c3d_g[0][idx] = tbl_val[tbl_s][j];
		c3d_b[0][idx] = tbl_val[tbl_s][k];
		idx++;
	    }
    return 1;
}

//---------------------------------------------------------------------------
void TC3DForm1::c3d_tmp_tbl_save()
{
    String Fpath = "tmp_tbl.txt";
    Save_c3d_table(Fpath);
    BitBtn_c3d_undo->Enabled = true;

    /*
       fprintf(fptr,"C3D_LUT\nRin\tGin\tBin\tRout\tGout\tBout\tH\tS\tV\tI\n");
       double h,s, in, v;
       for(int i = 0; i < total_len; i++){
       fprintf(fptr,"%d\t%d\t%d\t%d\t%d\t%d\t",c3d_r[0][i],c3d_g[0][i],
       c3d_b[0][i], c3d_r[1][i],c3d_g[1][i],c3d_b[1][i]);
       rgb2hsv(c3d_r[1][i],c3d_g[1][i],c3d_b[1][i],&h,&s,&in,&v);
       fprintf(fptr,"%2.2f\t%2.2f\t%2.2f\t%2.2f\n",h,s,v,in);
       } */
}

//----------------------------------------------------------------------------
void TC3DForm1::PointAdjust_1(int idx_r, int idx_g, int idx_b)
{
    int d = (sb_c3d_rgb_dis->Position);
    double r_gain = double (sb_c3d_rgb_r->Position - sb_c3d_rgb_r->Max / 2) / scrl_ratio;
    double g_gain = double (sb_c3d_rgb_g->Position - sb_c3d_rgb_g->Max / 2) / scrl_ratio;
    double b_gain = double (sb_c3d_rgb_b->Position - sb_c3d_rgb_b->Max / 2) / scrl_ratio;
    double ratio;

    int tmp_i, tmp_j, tmp_k;
    if (d == 0) {
	tmp_c3d_lutR[idx_r][idx_g][idx_b] += r_gain;
	tmp_c3d_lutG[idx_r][idx_g][idx_b] += g_gain;
	tmp_c3d_lutB[idx_r][idx_g][idx_b] += b_gain;
	if (tmp_c3d_lutR[idx_r][idx_g][idx_b] > 256 - 1.0 / Ratio)
	    tmp_c3d_lutR[idx_r][idx_g][idx_b] = 256 - 1.0 / Ratio;
	if (tmp_c3d_lutG[idx_r][idx_g][idx_b] > 256 - 1.0 / Ratio)
	    tmp_c3d_lutG[idx_r][idx_g][idx_b] = 256 - 1.0 / Ratio;
	if (tmp_c3d_lutB[idx_r][idx_g][idx_b] > 256 - 1.0 / Ratio)
	    tmp_c3d_lutB[idx_r][idx_g][idx_b] = 256 - 1.0 / Ratio;
	//Record_Move(idx_r,idx_g,idx_b,tmp_c3d_lutR[idx_r][idx_g][idx_b],
	//  tmp_c3d_lutG[idx_r][idx_g][idx_b],tmp_c3d_lutB[idx_r][idx_g][idx_b]);
    } else if (d == 1) {	//choose distance = 1
	for (int i_r = (idx_r - 1) > 0 ? (idx_r - 1) : 0; i_r <= (idx_r + 1 < 8 ? idx_r + 1 : 8);
	     i_r++) {
	    for (int i_g = (idx_g - 1) > 0 ? (idx_g - 1) : 0;
		 i_g <= (idx_g + 1 < 8 ? idx_g + 1 : 8); i_g++) {
		for (int i_b = (idx_b - 1) > 0 ? (idx_b - 1) : 0;
		     i_b <= (idx_b + 1 < 8 ? idx_b + 1 : 8); i_b++) {
		    tmp_c3d_lutR[i_r][i_g][i_b] += r_gain;
		    tmp_c3d_lutG[i_r][i_g][i_b] += g_gain;
		    tmp_c3d_lutB[i_r][i_g][i_b] += b_gain;

		    if (tmp_c3d_lutR[i_r][i_g][i_b] > 256 - 1.0 / Ratio)
			tmp_c3d_lutR[i_r][i_g][i_b] = 256 - 1.0 / Ratio;
		    else if (tmp_c3d_lutR[i_r][i_g][i_b] < 0)
			tmp_c3d_lutR[i_r][i_g][i_b] = 0;

		    if (tmp_c3d_lutG[i_r][i_g][i_b] > 256 - 1.0 / Ratio)
			tmp_c3d_lutG[i_r][i_g][i_b] = 256 - 1.0 / Ratio;
		    else if (tmp_c3d_lutG[i_r][i_g][i_b] < 0)
			tmp_c3d_lutG[i_r][i_g][i_b] = 0;

		    if (tmp_c3d_lutB[i_r][i_g][i_b] > 256 - 1.0 / Ratio)
			tmp_c3d_lutB[i_r][i_g][i_b] = 256 - 1.0 / Ratio;
		    else if (tmp_c3d_lutB[i_r][i_g][i_b] < 0)
			tmp_c3d_lutB[i_r][i_g][i_b] = 0;

		    //Record_Move(i_r,i_g,i_b,tmp_c3d_lutR[i_r][i_g][i_b],
		    //tmp_c3d_lutG[i_r][i_g][i_b],tmp_c3d_lutB[i_r][i_g][i_b]);
		}
	    }
	}
    } else if (d >= 2) {	//choose distance more than 2
	double rat;
	for (int i = (d) * (-1); i <= d; i++) {
	    tmp_i = idx_r + i;
	    if (tmp_i >= 0 & tmp_i <= TBL_SIZE - 1) {
		for (int j = (d) * (-1); j <= d; j++) {
		    tmp_j = idx_g + j;
		    if (tmp_j >= 0 & tmp_j <= TBL_SIZE - 1) {
			for (int k = (d) * (-1); k <= d; k++) {
			    tmp_k = idx_b + k;
			    if (tmp_k >= 0 & tmp_k <= TBL_SIZE - 1) {
				//c3d_Aratio(i,j,k,&rat,d);
				ratio = 1 - sqrt(double (i * i + j * j + k * k) / 3) / d;
				//ratio = 1-rat/d;
				if (ratio > 0) {
				    tmp_c3d_lutR[tmp_i][tmp_j][tmp_k] += ratio * r_gain;
				    tmp_c3d_lutG[tmp_i][tmp_j][tmp_k] += ratio * g_gain;
				    tmp_c3d_lutB[tmp_i][tmp_j][tmp_k] += ratio * b_gain;

				    if (tmp_c3d_lutR[tmp_i][tmp_j][tmp_k] > 256 - 1.0 / Ratio)
					tmp_c3d_lutR[tmp_i][tmp_j][tmp_k] = 256 - 1.0 / Ratio;
				    else if (tmp_c3d_lutR[tmp_i][tmp_j][tmp_k] < 0)
					tmp_c3d_lutR[tmp_i][tmp_j][tmp_k] = 0;
				    if (tmp_c3d_lutG[tmp_i][tmp_j][tmp_k] > 256 - 1.0 / Ratio)
					tmp_c3d_lutG[tmp_i][tmp_j][tmp_k] = 256 - 1.0 / Ratio;
				    else if (tmp_c3d_lutG[tmp_i][tmp_j][tmp_k] < 0)
					tmp_c3d_lutG[tmp_i][tmp_j][tmp_k] = 0;
				    if (tmp_c3d_lutB[tmp_i][tmp_j][tmp_k] > 256 - 1.0 / Ratio)
					tmp_c3d_lutB[tmp_i][tmp_j][tmp_k] = 256 - 1.0 / Ratio;
				    else if (tmp_c3d_lutB[tmp_i][tmp_j][tmp_k] < 0)
					tmp_c3d_lutB[tmp_i][tmp_j][tmp_k] = 0;

				    //Record_Move(tmp_i,tmp_j,tmp_k,tmp_c3d_lutR[tmp_i][tmp_j][tmp_k],
				    //tmp_c3d_lutG[tmp_i][tmp_j][tmp_k],tmp_c3d_lutB[tmp_i][tmp_j][tmp_k]);
				}
			    }
			}
		    }
		}
	    }
	}
    }
}

//------------------------------------------------------------------------
void TC3DForm1::Modif_Point(int color, double gain1, double gain2, double gain3, bool fl_ranh)
{				//Point Color adjust (fl_rah=0 is rgb, fl_rah=1 is hsv)
    if (color == -1)
	color = 0;
    double b = color / 65536;
    double g = color / 256 % 256;
    double r = color % 256;
    int idx_r = (r == 255 ? 8 : r / cube_dis);
    int idx_g = (g == 255 ? 8 : g / cube_dis);
    int idx_b = (b == 255 ? 8 : b / cube_dis);
    if (fl_ranh == 0) {		//rgb adjust
	tmp_c3d_lutR[idx_r][idx_g][idx_b] = c3d_lutR[idx_r][idx_g][idx_b] + gain1;
	tmp_c3d_lutG[idx_r][idx_g][idx_b] = c3d_lutG[idx_r][idx_g][idx_b] + gain2;
	tmp_c3d_lutB[idx_r][idx_g][idx_b] = c3d_lutB[idx_r][idx_g][idx_b] + gain3;
    } else {			//hsv adjust
	double h, s, in, v;
	rgb2hsv(c3d_lutR[idx_r][idx_g][idx_b], c3d_lutG[idx_r][idx_g][idx_b],
		c3d_lutB[idx_r][idx_g][idx_b], &h, &s, &in, &v);
	h = fmod((h + gain1 + 360), 360);
	s *= (1 + gain2);
	s = (s >= 1 ? 1 : s);
	v *= (1 + gain3);
	v = (v >= 256 ? 256 - 1 / Ratio : v);
	hsv2rgb(h, s, v, &tmp_c3d_lutR[idx_r][idx_g][idx_b], &tmp_c3d_lutG[idx_r][idx_g][idx_b],
		&tmp_c3d_lutB[idx_r][idx_g][idx_b]);
    }
    tmp_c3d_lutR[idx_r][idx_g][idx_b] =
	(tmp_c3d_lutR[idx_r][idx_g][idx_b] < 0 ? 0 : tmp_c3d_lutR[idx_r][idx_g][idx_b]);
    tmp_c3d_lutG[idx_r][idx_g][idx_b] =
	(tmp_c3d_lutG[idx_r][idx_g][idx_b] < 0 ? 0 : tmp_c3d_lutG[idx_r][idx_g][idx_b]);
    tmp_c3d_lutB[idx_r][idx_g][idx_b] =
	(tmp_c3d_lutB[idx_r][idx_g][idx_b] < 0 ? 0 : tmp_c3d_lutB[idx_r][idx_g][idx_b]);

    tmp_c3d_lutR[idx_r][idx_g][idx_b] =
	(tmp_c3d_lutR[idx_r][idx_g][idx_b] >=
	 256 ? 255 - 1 / Ratio : tmp_c3d_lutR[idx_r][idx_g][idx_b]);
    tmp_c3d_lutG[idx_r][idx_g][idx_b] =
	(tmp_c3d_lutG[idx_r][idx_g][idx_b] >=
	 256 ? 255 - 1 / Ratio : tmp_c3d_lutG[idx_r][idx_g][idx_b]);
    tmp_c3d_lutB[idx_r][idx_g][idx_b] =
	(tmp_c3d_lutB[idx_r][idx_g][idx_b] >=
	 256 ? 255 - 1 / Ratio : tmp_c3d_lutB[idx_r][idx_g][idx_b]);
    //Record_Move(idx_r,idx_g,idx_b,tmp_c3d_lutR[idx_r][idx_g][idx_b],tmp_c3d_lutG[idx_r][idx_g][idx_b],tmp_c3d_lutB[idx_r][idx_g][idx_b]);
}

//------------------------------------------------------------------------
void TC3DForm1::PointAdjust_4()
{
    int color;
    double r, g, b;
    int width = Img_3DLUT->Width;
    int height = Img_3DLUT->Height;
    if (rg_PCrgb_choose->ItemIndex == 0) {	// gain in rgb
	double r_gain = double (sb_c3d_rgb_r->Position - sb_c3d_rgb_r->Max / 2) / scrl_ratio;
	double g_gain = double (sb_c3d_rgb_g->Position - sb_c3d_rgb_g->Max / 2) / scrl_ratio;
	double b_gain = double (sb_c3d_rgb_b->Position - sb_c3d_rgb_b->Max / 2) / scrl_ratio;

	color = img_color->Canvas->Pixels[10][10];
	Modif_Point(color, r_gain, g_gain, b_gain, 0);

	color = img_color->Canvas->Pixels[10 + width / 2][10];
	Modif_Point(color, r_gain, g_gain, b_gain, 0);

	color = img_color->Canvas->Pixels[10][10 + height / 2];
	Modif_Point(color, r_gain, g_gain, b_gain, 0);

	color = img_color->Canvas->Pixels[10 + width / 2][10 + height / 2];
	Modif_Point(color, r_gain, g_gain, b_gain, 0);

    } else if (rg_PCrgb_choose->ItemIndex == 1) {	// gain in hsv
	double h_gain = ((double) sb_c3d_hsv_h->Position - sb_c3d_hsv_h->Max / 2) / 2;
	double c = StrToFloat(edt_c3d_satC->Text);
	double s_gain = ((double) sb_c3d_hsv_s->Position - sb_c3d_hsv_s->Max / 2) / 100 / c;
	c = StrToFloat(edt_c3d_valC->Text);
	double v_gain = ((double) sb_c3d_hsv_v->Position - sb_c3d_hsv_v->Max / 2) / 100 / c;

	color = img_color->Canvas->Pixels[10][10];
	Modif_Point(color, h_gain, s_gain, v_gain, 1);

	color = img_color->Canvas->Pixels[10 + width / 2][10];
	Modif_Point(color, h_gain, s_gain, v_gain, 1);

	color = img_color->Canvas->Pixels[10][10 + height / 2];
	Modif_Point(color, h_gain, s_gain, v_gain, 1);

	color = img_color->Canvas->Pixels[10 + width / 2][10 + height / 2];
	Modif_Point(color, h_gain, s_gain, v_gain, 1);
    }
}

//--------------------------------------------------------------------------
void TC3DForm1::PointAdjust_m()
{
    if (rg_PCrgb_choose->ItemIndex == 0) {	//gain in rgb
	double r_gain = double (sb_c3d_rgb_r->Position - sb_c3d_rgb_r->Max / 2) / scrl_ratio;
	double g_gain = double (sb_c3d_rgb_g->Position - sb_c3d_rgb_g->Max / 2) / scrl_ratio;
	double b_gain = double (sb_c3d_rgb_b->Position - sb_c3d_rgb_b->Max / 2) / scrl_ratio;
	for (int i = 0; i < Color_move_Nbr; i++)
	    Modif_Point(RGB(Color_move[i][0], Color_move[i][1], Color_move[i][2]), r_gain, g_gain,
			b_gain, 0);
    } else if (rg_PCrgb_choose->ItemIndex == 1) {	//gain in hsv
	double h_gain = ((double) sb_c3d_hsv_h->Position - sb_c3d_hsv_h->Max / 2) / 2;
	double c = StrToFloat(edt_c3d_satC->Text);
	double s_gain = ((double) sb_c3d_hsv_s->Position - sb_c3d_hsv_s->Max / 2) / 100 / c;
	c = StrToFloat(edt_c3d_valC->Text);
	double v_gain = ((double) sb_c3d_hsv_v->Position - sb_c3d_hsv_v->Max / 2) / 100 / c;
	for (int i = 0; i < Color_move_Nbr; i++)
	    Modif_Point(RGB(Color_move[i][0], Color_move[i][1], Color_move[i][2]), h_gain, s_gain,
			v_gain, 1);
    }
}

//------------------------------------------------------------------------
void TC3DForm1::Record_Move(int i_r, int i_g, int i_b, double r, double g, double b)
{				// 去除重複的點...(先不作)   紀錄點調整所移動的部份
    PointColor_array[PointColor_array_nbr][0] = i_r * cube_dis;
    PointColor_array[PointColor_array_nbr][1] = i_g * cube_dis;
    PointColor_array[PointColor_array_nbr][2] = i_b * cube_dis;
    PointColor_array[PointColor_array_nbr][3] = r;
    PointColor_array[PointColor_array_nbr][4] = g;
    PointColor_array[PointColor_array_nbr][5] = b;
    PointColor_array_nbr++;
}

//------------------------------------------------------------------------

void TC3DForm1::cal_c3d_rgb(bool flg_wri)
{				//RGB diffusion (include: 1 point, 4 points, many points move)
    PointColor_array_nbr = 0;
    int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
    int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
    int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);

    for (int i = 0; i < TBL_SIZE; i++) {
	for (int j = 0; j < TBL_SIZE; j++) {
	    for (int k = 0; k < TBL_SIZE; k++) {
		tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
		tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
		tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
	    }
	}
    }
    double r, g, b, cor_r, cor_g, cor_b;

    if (rg_PointNum->ItemIndex == 1) {	// 4 color move
	PointAdjust_4();
	r = StrToFloat(sg_rgb_input->Cells[0][1]);
	g = StrToFloat(sg_rgb_input->Cells[1][1]);
	b = StrToFloat(sg_rgb_input->Cells[2][1]);
	Show_c3d_SelImg(r, g, b);
    } else if (rg_PointNum->ItemIndex == 0) {	// 1 color move
	PointAdjust_1(idx_r, idx_g, idx_b);
	cor_r = (double) tmp_c3d_lutR[idx_r][idx_g][idx_b];
	cor_g = (double) tmp_c3d_lutG[idx_r][idx_g][idx_b];
	cor_b = (double) tmp_c3d_lutB[idx_r][idx_g][idx_b];
	Show_c3d_CorImg(cor_r, cor_g, cor_b);
	r = StrToFloat(lb_c3d_selR->Caption);
	g = StrToFloat(lb_c3d_selG->Caption);
	b = StrToFloat(lb_c3d_selB->Caption);
    } else if (rg_PointNum->ItemIndex == 2) {	// many color move
	PointAdjust_m();
	r = StrToFloat(sg_rgb_input->Cells[0][1]);
	g = StrToFloat(sg_rgb_input->Cells[1][1]);
	b = StrToFloat(sg_rgb_input->Cells[2][1]);
	Show_c3d_SelImg(r, g, b);
    }
    if (flg_wri == true) {
	for (int i = 0; i < TBL_SIZE; i++)
	    for (int j = 0; j < TBL_SIZE; j++)
		for (int k = 0; k < TBL_SIZE; k++) {
		    c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
		    c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
		    c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
		}
    }
    double sim_r, sim_g, sim_b;
    C3Dsim_t(r, g, b, &sim_r, &sim_g, &sim_b);
    Show_c3d_SimImg(sim_r, sim_g, sim_b);
    Show_c3d_Img_sim();
    //refresh_6axis_grid_t(sim_r,sim_g,sim_b);
}

//---------------------------------------------------------------------------

void TC3DForm1::C3Dsim_t(double r, double g, double b, double *r_new, double *g_new, double *b_new)
{				//techehedral
    int idx_r, idx_g, idx_b;
    double v_r[2], v_g[2], v_b[2];

    for (int i = 0; i <= TBL_SIZE - 2; i++) {
	if (r >= tbl_val[tbl_s][i] && r <= tbl_val[tbl_s][i + 1]) {
	    v_r[0] = tbl_val[tbl_s][i];
	    v_r[1] = tbl_val[tbl_s][i + 1];
	    idx_r = i;
	    break;
	}
    }
    for (int i = 0; i <= TBL_SIZE - 2; i++) {
	if (g >= tbl_val[tbl_s][i] && g <= tbl_val[tbl_s][i + 1]) {
	    v_g[0] = tbl_val[tbl_s][i];
	    v_g[1] = tbl_val[tbl_s][i + 1];
	    idx_g = i;
	    break;
	}
    }
    for (int i = 0; i <= TBL_SIZE - 2; i++) {
	if (b >= tbl_val[tbl_s][i] && b <= tbl_val[tbl_s][i + 1]) {
	    v_b[0] = tbl_val[tbl_s][i];
	    v_b[1] = tbl_val[tbl_s][i + 1];
	    idx_b = i;
	    break;
	}
    }

    double P[2][2][2][3];
    // p[][][][0]=> red  p[][][][1]=> green  p[][][][2]=> blue
    for (int i = 0; i < 2; i++)
	for (int j = 0; j < 2; j++)
	    for (int k = 0; k < 2; k++) {
		P[i][j][k][0] = tmp_c3d_lutR[idx_r + i][idx_g + j][idx_b + k];
		P[i][j][k][1] = tmp_c3d_lutG[idx_r + i][idx_g + j][idx_b + k];
		P[i][j][k][2] = tmp_c3d_lutB[idx_r + i][idx_g + j][idx_b + k];
	    }

    double dlt_x = (r - v_r[0]) / (v_r[1] - v_r[0]);
    double dlt_y = (g - v_g[0]) / (v_g[1] - v_g[0]);
    double dlt_z = (b - v_b[0]) / (v_b[1] - v_b[0]);

    if (interpol == true) {
	double C1[3], C2[3], C3[3];

	if (dlt_x >= dlt_y && dlt_y > dlt_z) {	//T1
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][0][0][c] - P[0][0][0][c];
		C2[c] = P[1][1][0][c] - P[1][0][0][c];
		C3[c] = P[1][1][1][c] - P[1][1][0][c];
	    }
	} else if (dlt_x > dlt_z && dlt_z >= dlt_y) {	//T2
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][0][0][c] - P[0][0][0][c];
		C2[c] = P[1][1][1][c] - P[1][0][1][c];
		C3[c] = P[1][0][1][c] - P[1][0][0][c];
	    }
	} else if (dlt_z >= dlt_x && dlt_x >= dlt_y) {	//T3
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][0][1][c] - P[0][0][1][c];
		C2[c] = P[1][1][1][c] - P[1][0][1][c];
		C3[c] = P[0][0][1][c] - P[0][0][0][c];
	    }
	} else if (dlt_y > dlt_x && dlt_x > dlt_z) {	//T4
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][1][0][c] - P[0][1][0][c];
		C2[c] = P[0][1][0][c] - P[0][0][0][c];
		C3[c] = P[1][1][1][c] - P[1][1][0][c];
	    }
	} else if (dlt_y > dlt_z && dlt_z >= dlt_x) {	//T5
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][1][1][c] - P[0][1][1][c];
		C2[c] = P[0][1][0][c] - P[0][0][0][c];
		C3[c] = P[0][1][1][c] - P[0][1][0][c];
	    }
	} else if (dlt_z >= dlt_y && dlt_y > dlt_x) {	//T6
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][1][1][c] - P[0][1][1][c];
		C2[c] = P[0][1][1][c] - P[0][0][1][c];
		C3[c] = P[0][0][1][c] - P[0][0][0][c];
	    }
	}

	double P_[3];
	for (int c = 0; c < 3; c++) {
	    P_[c] = P[0][0][0][c] + C1[c] * dlt_x + C2[c] * dlt_y + C3[c] * dlt_z;
	}

	*r_new = P_[0];
	*g_new = P_[1];
	*b_new = P_[2];
    } else {			//trilinear
	double i[2][3], j[2][3], w[2][3];

	for (int c = 0; c < 3; c++) {
	    i[0][c] = P[0][0][0][c] * (1 - dlt_x) + P[1][0][0][c] * dlt_x;
	    i[1][c] = P[0][1][0][c] * (1 - dlt_x) + P[1][1][0][c] * dlt_x;
	    j[0][c] = P[0][0][1][c] * (1 - dlt_x) + P[1][0][1][c] * dlt_x;
	    j[1][c] = P[0][1][1][c] * (1 - dlt_x) + P[1][1][1][c] * dlt_x;
	}
	for (int c = 0; c < 3; c++) {
	    w[0][c] = i[0][c] * (1 - dlt_y) + i[1][c] * dlt_y;
	    w[1][c] = j[0][c] * (1 - dlt_y) + j[1][c] * dlt_y;
	}
	*r_new = w[0][0] * (1 - dlt_z) + w[1][0] * dlt_z;
	*g_new = w[0][1] * (1 - dlt_z) + w[1][1] * dlt_z;
	*b_new = w[0][2] * (1 - dlt_z) + w[1][2] * dlt_z;
    }
}

//---------------------------------------------------------------------------
void TC3DForm1::C3Dsim(double r, double g, double b, double *r_new, double *g_new, double *b_new)
{
    int idx_r, idx_g, idx_b;
    double v_r[2], v_g[2], v_b[2];
    for (int i = 0; i <= TBL_SIZE - 2; i++) {
	if (r >= tbl_val[tbl_s][i] && r <= tbl_val[tbl_s][i + 1]) {
	    v_r[0] = tbl_val[tbl_s][i];
	    v_r[1] = tbl_val[tbl_s][i + 1];
	    idx_r = i;
	    break;
	}
    }
    for (int i = 0; i <= TBL_SIZE - 2; i++) {
	if (g >= tbl_val[tbl_s][i] && g <= tbl_val[tbl_s][i + 1]) {
	    v_g[0] = tbl_val[tbl_s][i];
	    v_g[1] = tbl_val[tbl_s][i + 1];
	    idx_g = i;
	    break;
	}
    }
    for (int i = 0; i <= TBL_SIZE - 2; i++) {
	if (b >= tbl_val[tbl_s][i] && b <= tbl_val[tbl_s][i + 1]) {
	    v_b[0] = tbl_val[tbl_s][i];
	    v_b[1] = tbl_val[tbl_s][i + 1];
	    idx_b = i;
	    break;
	}
    }

    double P[2][2][2][3];
    // p000[0]=> red  p000[0]=> green  p000[0]=> blue
    for (int i = 0; i < 2; i++)
	for (int j = 0; j < 2; j++)
	    for (int k = 0; k < 2; k++) {
		P[i][j][k][0] = c3d_lutR[idx_r + i][idx_g + j][idx_b + k];
		P[i][j][k][1] = c3d_lutG[idx_r + i][idx_g + j][idx_b + k];
		P[i][j][k][2] = c3d_lutB[idx_r + i][idx_g + j][idx_b + k];
	    }

    double dlt_x = (r - v_r[0]) / (v_r[1] - v_r[0]);
    double dlt_y = (g - v_g[0]) / (v_g[1] - v_g[0]);
    double dlt_z = (b - v_b[0]) / (v_b[1] - v_b[0]);

    if (interpol == true) {	//techehedral
	double C1[3], C2[3], C3[3];

	if (dlt_x >= dlt_y && dlt_y > dlt_z) {	//T1
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][0][0][c] - P[0][0][0][c];
		C2[c] = P[1][1][0][c] - P[1][0][0][c];
		C3[c] = P[1][1][1][c] - P[1][1][0][c];
	    }
	} else if (dlt_x > dlt_z && dlt_z >= dlt_y) {	//T2
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][0][0][c] - P[0][0][0][c];
		C2[c] = P[1][1][1][c] - P[1][0][1][c];
		C3[c] = P[1][0][1][c] - P[1][0][0][c];
	    }
	} else if (dlt_z >= dlt_x && dlt_x >= dlt_y) {	//T3
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][0][1][c] - P[0][0][1][c];
		C2[c] = P[1][1][1][c] - P[1][0][1][c];
		C3[c] = P[0][0][1][c] - P[0][0][0][c];
	    }
	} else if (dlt_y > dlt_x && dlt_x > dlt_z) {	//T4
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][1][0][c] - P[0][1][0][c];
		C2[c] = P[0][1][0][c] - P[0][0][0][c];
		C3[c] = P[1][1][1][c] - P[1][1][0][c];
	    }
	} else if (dlt_y > dlt_z && dlt_z >= dlt_x) {	//T5
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][1][1][c] - P[0][1][1][c];
		C2[c] = P[0][1][0][c] - P[0][0][0][c];
		C3[c] = P[0][1][1][c] - P[0][1][0][c];
	    }
	} else if (dlt_z >= dlt_y && dlt_y > dlt_x) {	//T6
	    for (int c = 0; c < 3; c++) {
		C1[c] = P[1][1][1][c] - P[0][1][1][c];
		C2[c] = P[0][1][1][c] - P[0][0][1][c];
		C3[c] = P[0][0][1][c] - P[0][0][0][c];
	    }
	}

	double P_[3];
	for (int c = 0; c < 3; c++) {
	    P_[c] = P[0][0][0][c] + C1[c] * dlt_x + C2[c] * dlt_y + C3[c] * dlt_z;
	}

	*r_new = P_[0];
	*g_new = P_[1];
	*b_new = P_[2];
    } else {			//trilinear
	double i[2][3], j[2][3], w[2][3];

	for (int c = 0; c < 3; c++) {
	    i[0][c] = P[0][0][0][c] * (1 - dlt_x) + P[1][0][0][c] * dlt_x;
	    i[1][c] = P[0][1][0][c] * (1 - dlt_x) + P[1][1][0][c] * dlt_x;
	    j[0][c] = P[0][0][1][c] * (1 - dlt_x) + P[1][0][1][c] * dlt_x;
	    j[1][c] = P[0][1][1][c] * (1 - dlt_x) + P[1][1][1][c] * dlt_x;
	}
	for (int c = 0; c < 3; c++) {
	    w[0][c] = i[0][c] * (1 - dlt_y) + i[1][c] * dlt_y;
	    w[1][c] = j[0][c] * (1 - dlt_y) + j[1][c] * dlt_y;
	}
	*r_new = w[0][0] * (1 - dlt_z) + w[1][0] * dlt_z;
	*g_new = w[0][1] * (1 - dlt_z) + w[1][1] * dlt_z;
	*b_new = w[0][2] * (1 - dlt_z) + w[1][2] * dlt_z;
    }
}

//------------------------------------------------------------------------------

//---------------------------------------------------------------------------
// 更新六軸調整Grid的顯示數值, 數值來源c3d_lutR,c3d_lutG,c3d_lutB
void TC3DForm1::refresh_6axis_grid(double r, double g, double b)
{
    if (r == 256)
	r = 256 - 1.0 / Ratio;
    if (g == 256)
	g = 256 - 1.0 / Ratio;
    if (b == 256)
	b = 256 - 1.0 / Ratio;

    int idx = TBL_SIZE - 1;
    c3d_grid(0, r, g, b);
    c3d_grid(1, c3d_lutR[idx][0][0], c3d_lutG[idx][0][0], c3d_lutB[idx][0][0]);
    c3d_grid(2, c3d_lutR[idx][idx][0], c3d_lutG[idx][idx][0], c3d_lutB[idx][idx][0]);
    c3d_grid(3, c3d_lutR[0][idx][0], c3d_lutG[0][idx][0], c3d_lutB[0][idx][0]);
    c3d_grid(4, c3d_lutR[0][idx][idx], c3d_lutG[0][idx][idx], c3d_lutB[0][idx][idx]);
    c3d_grid(5, c3d_lutR[0][0][idx], c3d_lutG[0][0][idx], c3d_lutB[0][0][idx]);
    c3d_grid(6, c3d_lutR[idx][0][idx], c3d_lutG[idx][0][idx], c3d_lutB[idx][0][idx]);
}

//----------------------------------------------------------------------------
// 更新六軸調整Grid的顯示數值, 數值來源tmp_c3d_lutR,tmp_c3d_lutG,tmp_c3d_lutB
void TC3DForm1::refresh_6axis_grid_t(double r, double g, double b)
{
    if (r == 256)
	r = 256 - 1.0 / Ratio;
    if (g == 256)
	g = 256 - 1.0 / Ratio;
    if (b == 256)
	b = 256 - 1.0 / Ratio;

    int idx = TBL_SIZE - 1;
    c3d_grid(0, r, g, b);
    c3d_grid(1, tmp_c3d_lutR[idx][0][0], tmp_c3d_lutG[idx][0][0], tmp_c3d_lutB[idx][0][0]);
    c3d_grid(2, tmp_c3d_lutR[idx][idx][0], tmp_c3d_lutG[idx][idx][0], tmp_c3d_lutB[idx][idx][0]);
    c3d_grid(3, tmp_c3d_lutR[0][idx][0], tmp_c3d_lutG[0][idx][0], tmp_c3d_lutB[0][idx][0]);
    c3d_grid(4, tmp_c3d_lutR[0][idx][idx], tmp_c3d_lutG[0][idx][idx], tmp_c3d_lutB[0][idx][idx]);
    c3d_grid(5, tmp_c3d_lutR[0][0][idx], tmp_c3d_lutG[0][0][idx], tmp_c3d_lutB[0][0][idx]);
    c3d_grid(6, tmp_c3d_lutR[idx][0][idx], tmp_c3d_lutG[idx][0][idx], tmp_c3d_lutB[idx][0][idx]);
}

//------------------------------------------------------------------------------
void TC3DForm1::c3d_grid(int c, int r, int g, int b)
{
    double h, s, v, in;
    rgb2hsv(r, g, b, &h, &s, &in, &v);
    sg_c3d_hsvi->Cells[0][c] = h;
    sg_c3d_hsvi->Cells[1][c] = s;
    sg_c3d_hsvi->Cells[2][c] = v;
}

//------------------------------------------------------------------------------

void TC3DForm1::refresh_c3d_color_grid()
{
    int rgb1[12][3] = { {192, 64, 64}, {192, 128, 64}, {192, 192, 64}, {128, 192, 64},
    {64, 192, 64}, {64, 192, 128}, {64, 192, 192}, {64, 128, 192}, {64, 64, 192},
    {128, 64, 192}, {192, 64, 192}, {192, 64, 128}
    };

    int rgb2[12][3] = { {96, 32, 32}, {96, 64, 32}, {96, 96, 32}, {64, 96, 32}, {32, 96, 32},
    {32, 96, 64}, {32, 96, 96}, {32, 64, 96}, {32, 32, 96}, {64, 32, 96}, {96, 32, 96}, {96, 32, 64}
    };

    int rgb_d[6][3] = { {32, 0, 0}, {32, 32, 0}, {0, 32, 0}, {0, 32, 32}, {0, 0, 32}, {32, 0, 32} };

    int rgb_g[9][3] = { {0, 0, 0}, {32, 32, 32}, {64, 64, 64}, {96, 96, 96}, {128, 128, 128},
    {160, 160, 160}, {192, 192, 192}, {224, 224, 224}, {255, 255, 255}
    };

    for (int i = 1; i <= 12; i++) {
	set_c3d_color_grid(1, i, rgb1[i - 1][0], rgb1[i - 1][1], rgb1[i - 1][2]);
	set_c3d_color_grid(2, i, rgb2[i - 1][0], rgb2[i - 1][1], rgb2[i - 1][2]);
    }
    for (int i = 1; i <= 6; i++) {
	set_c3d_color_grid(3, i, rgb_d[i - 1][0], rgb_d[i - 1][1], rgb_d[i - 1][2]);
    }
    for (int i = 1; i <= 9; i++) {
	set_c3d_color_grid(4, i, rgb_g[i - 1][0], rgb_g[i - 1][1], rgb_g[i - 1][2]);
    }
}

//------------------------------------------------------------------------------
void TC3DForm1::set_c3d_color_grid(int grid_num, int c, int r, int g, int b)
{
    double h, s, v, in;
    rgb2hsv(r, g, b, &h, &s, &in, &v);
    if (grid_num == 1) {
	sg_12color1->Cells[1][c] = h;
	sg_12color1->Cells[2][c] = s;
	sg_12color1->Cells[3][c] = v;
    } else if (grid_num == 2) {
	sg_12color2->Cells[1][c] = h;
	sg_12color2->Cells[2][c] = s;
	sg_12color2->Cells[3][c] = v;
    } else if (grid_num == 3) {
	sg_Dark->Cells[1][c] = h;
	sg_Dark->Cells[2][c] = s;
	sg_Dark->Cells[3][c] = v;
    } else if (grid_num == 4) {
	sg_Gray->Cells[1][c] = h;
	sg_Gray->Cells[2][c] = s;
	sg_Gray->Cells[3][c] = v;
    }
}

//------------------------------------------------------------------------------

void __fastcall TC3DForm1::rg_c3d_interplClick(TObject * Sender)
{
    if (rg_c3d_interpl->ItemIndex == 0)
	interpol = true;
    else
	interpol = false;
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::rg_c3d_TblSizeClick(TObject * Sender)
{
    c3d_scrollbar_reset();
    pc_Adjust->TabIndex = 1;
    TabSheet22->Visible = true;
    tbl_s = rg_c3d_TblSize->ItemIndex;
    delete_array();
    if (tbl_s == 0)
	TBL_SIZE = 9;
    else if (tbl_s == 1)
	TBL_SIZE = 7;
    else if (tbl_s == 2)
	TBL_SIZE = 17;
    else if (tbl_s == 3)
	TBL_SIZE = 33;
    cube_dis = 256 / (TBL_SIZE - 1);
    if (TBL_SIZE == 7) {
	cube_dis = 32;

    }
    total_len = TBL_SIZE * TBL_SIZE * TBL_SIZE;
    new_array();
    Ini_c3d_table();
    // btn_c3d_resetClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::rb_c3d_pointClick(TObject * Sender)
{
    //point color mode to adjust color
    if (c3d_detailadjust == true)
	for (int i = 0; i < TBL_SIZE; i++)
	    for (int j = 0; j < TBL_SIZE; j++)
		for (int k = 0; k < TBL_SIZE; k++) {
		    hsv2rgb(c3d_lutH[i][j][k], c3d_lutS[i][j][k], c3d_lutV[i][j][k],
			    &c3d_lutR[i][j][k], &c3d_lutG[i][j][k], &c3d_lutB[i][j][k]);
		}
    c3d_detailadjust = false;
    c3d_scrollbar_reset();
}

//---------------------------------------------------------------------------
void __fastcall TC3DForm1::rb_c3d_colorClick(TObject * Sender)
{
    c3d_scrollbar_reset();
    //HSI mode to adjust color
    double in;
    if (c3d_detailadjust == false)
	for (int i = 0; i < TBL_SIZE; i++)
	    for (int j = 0; j < TBL_SIZE; j++)
		for (int k = 0; k < TBL_SIZE; k++) {
		    rgb2hsv(c3d_lutR[i][j][k], c3d_lutG[i][j][k], c3d_lutB[i][j][k],
			    &c3d_lutH[i][j][k], &c3d_lutS[i][j][k], &in, &c3d_lutV[i][j][k]);
		}
    c3d_detailadjust = true;
    int idx_r, idx_g, idx_b;
    if (rb_c3d_r->Checked == true) {
	idx_r = TBL_SIZE - 1;
	idx_g = 0;
	idx_b = 0;
    } else if (rb_c3d_y->Checked == true) {
	idx_r = TBL_SIZE - 1;
	idx_g = TBL_SIZE - 1;
	idx_b = 0;
    } else if (rb_c3d_g->Checked == true) {
	idx_r = 0;
	idx_g = TBL_SIZE - 1;
	idx_b = 0;
    } else if (rb_c3d_c->Checked == true) {
	idx_r = 0;
	idx_g = TBL_SIZE - 1;
	idx_b = TBL_SIZE - 1;
    } else if (rb_c3d_b->Checked == true) {
	idx_r = 0;
	idx_g = 0;
	idx_b = TBL_SIZE - 1;
    } else if (rb_c3d_m->Checked == true) {
	idx_r = TBL_SIZE - 1;
	idx_g = 0;
	idx_b = TBL_SIZE - 1;
    }

    lb_c3d_tbl_ir->Caption = idx_r;
    lb_c3d_tbl_ig->Caption = idx_g;
    lb_c3d_tbl_ib->Caption = idx_b;

    double r = c3d_lutR[idx_r][idx_g][idx_b];
    double g = c3d_lutG[idx_r][idx_g][idx_b];
    double b = c3d_lutB[idx_r][idx_g][idx_b];

    Show_c3d_SelImg(r, g, b);
    Show_c3d_CorImg(r, g, b);
    Show_c3d_TblImg(r, g, b);
    Show_c3d_SimImg(r, g, b);
    Show_c3d_Img_sim();
}

//---------------------------------------------------------------------------
void __fastcall TC3DForm1::btn_c3d_resetClick(TObject * Sender)
{
    c3d_tmp_tbl_save();
    BitBtn_c3d_undo->Enabled = true;
    sb_c3d_rgb_dis->Position = 0;

    sb_c3d_Manual39_h->Position = sb_c3d_Manual39_h->Max / 2;
    sb_c3d_Manual39_s->Position = sb_c3d_Manual39_s->Max / 2;
    sb_c3d_Manual39_v->Position = sb_c3d_Manual39_v->Max / 2;
    c3d_scrollbar_reset();

    Ini_c3d_table();
    rb_c3d_point->Checked = false;
    rb_c3d_r->Checked = false;
    rb_c3d_g->Checked = false;
    rb_c3d_b->Checked = false;
    rb_c3d_c->Checked = false;
    rb_c3d_y->Checked = false;
    rb_c3d_m->Checked = false;
    //cal_c3d_rgb(false);
    if (TBL_SIZE == 9)
	Refresh_Manual39_Point();
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_c3d_loadClick(TObject * Sender)
{
    if (!OpenDialog1->Execute())
	return;
    String Fpath = OpenDialog1->FileName;
    char *buffer = Load_File(Fpath);

    int tbl_tl = pow(TBL_SIZE, 3);

    int idx_r, idx_g, idx_b;
    char *str[11];
    int str_l[11];
    str[0] = "C3D_LUT";
    str_l[0] = 7;
    str[1] = "Rin";
    str_l[1] = 4;
    str[2] = "Gin";
    str_l[2] = 4;
    str[3] = "Bin";
    str_l[3] = 4;
    str[4] = "Rout";
    str_l[4] = 4;
    str[5] = "Gout";
    str_l[5] = 4;
    str[6] = "Bout";
    str_l[6] = 4;
    str[7] = "H";
    str_l[7] = 1;
    str[8] = "S";
    str_l[8] = 1;
    str[9] = "V";
    str_l[9] = 1;
    str[10] = "I";
    str_l[10] = 1;

    char *pch = strtok(buffer, "\n\t");
    for (int i = 0; i < 11; i++) {
	while (memcmp(pch, str[i], str_l[i]) != 0) {
	    if (pch == NULL) {
		ShowMessage("Can't open c3d table file.");
		return;
	    }
	    pch = strtok(NULL, "\n\t");
	}
    }
    int c = 0;
    pch = strtok(NULL, "\n\t");
    while (c < tbl_tl * 10 && pch != NULL) {
	if (pch == NULL) {
	    ShowMessage("Can't open c3d table file.");
	    return;		//資料中的data缺少
	}
	if (c % 10 == 0)
	    idx_r = (int) ceil((double) StrToInt((AnsiString) pch) / cube_dis);
	else if (c % 10 == 1)
	    idx_g = (int) ceil((double) StrToInt((AnsiString) pch) / cube_dis);
	else if (c % 10 == 2)
	    idx_b = (int) ceil((double) StrToInt((AnsiString) pch) / cube_dis);
	else if (c % 10 == 3)
	    c3d_lutR[idx_r][idx_g][idx_b] = StrToFloat((AnsiString) pch) / scrl_ratio;
	else if (c % 10 == 4)
	    c3d_lutG[idx_r][idx_g][idx_b] = StrToFloat((AnsiString) pch) / scrl_ratio;
	else if (c % 10 == 5)
	    c3d_lutB[idx_r][idx_g][idx_b] = StrToFloat((AnsiString) pch) / scrl_ratio;
	else if (c % 10 == 6)
	    c3d_lutH[idx_r][idx_g][idx_b] = StrToFloat((AnsiString) pch);
	else if (c % 10 == 7)
	    c3d_lutS[idx_r][idx_g][idx_b] = StrToFloat((AnsiString) pch);
	else if (c % 10 == 8)
	    c3d_lutV[idx_r][idx_g][idx_b] = StrToFloat((AnsiString) pch);
	else if (c % 10 == 9)
	    c3d_lutI[idx_r][idx_g][idx_b] = StrToFloat((AnsiString) pch);

	pch = strtok(NULL, "\n\t");
	c++;
    }
    delete[]buffer;
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_c3d_save_hClick(TObject * Sender)
{
    if (!SaveDialog1->Execute()) {
	return;
    }

    String Fpath = SaveDialog1->FileName /*+".txt" */ ;
    if (Fpath == NULL)
	return;
    btn_c3d_save_h->Enabled = false;
    FILE *fptr = fopen(Fpath.c_str(), "w");

    c3d_lutArrange();
    fprintf(fptr, "C3D_LUT\nRin\tGin\tBin\tRout\tGout\tBout\tH\tS\tV\tI\n");
    int tbl_tl = pow(TBL_SIZE, 3);
    double h, s, in, v;
    for (int i = 0; i < tbl_tl; i++) {
	fprintf(fptr, "%d\t%d\t%d\t%d\t%d\t%d\t", c3d_r[0][i], c3d_g[0][i],
		c3d_b[0][i], c3d_r[1][i], c3d_g[1][i], c3d_b[1][i]);
	rgb2hsv(c3d_r[1][i] / Ratio, c3d_g[1][i] / Ratio, c3d_b[1][i] / Ratio, &h, &s, &in, &v);
	fprintf(fptr, "%2.2f\t%2.3f\t%2.2f\t%2.2f\n", h, s, v, in);
    }
    fclose(fptr);

    sb_c3d_rgb_dis->Position = 0;
    c3d_scrollbar_reset();

    btn_c3d_save_h->Enabled = true;
}

//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//    HSV adjust method 2
//    c3d_6axisAdj_h(bool flag), c3d_6axisAdj_s(bool flag), c3d_6axisAdj_v(bool flag)
//-----------------------------------------------------------------------------------
/*
void c3d_6axisAdj_r(int type, double dif_p, double dif_n, double gain, double tmp_c3d_lutR[9][9][9], double tmp_c3d_lutG[9][9][9], double tmp_c3d_lutB[9][9][9])
{
        double r_gain[9][9] = {0}, g_gain[9][9] = {0}, b_gain[9][9] = {0};
        double h, s, v, in;
        double tmp_r, tmp_g, tmp_b;
        double ratio;

        if(type == 1){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                rgb2hsv(c3d_lutR[i][j][j],c3d_lutG[i][j][j],c3d_lutB[i][j][j],&h, &s, &in, &v);
                                h += gain;
                                h = fmod(h+360, 360);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[i][j][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[i][j][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[i][j][j];
                        }
                }
        }else if(type == 2){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                rgb2hsv(c3d_lutR[i][j][j],c3d_lutG[i][j][j], c3d_lutB[i][j][j],&h, &s, &in, &v);
                                s += s*gain;
                                s = (s<0?0:s);
                                s = (s>1?1:s);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[i][j][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[i][j][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[i][j][j];
                        }
                }
        }else if(type == 3){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                //hsv
                                rgb2hsv(c3d_lutR[i][j][j],c3d_lutG[i][j][j],c3d_lutB[i][j][j],&h,&s,&in,&v);
                                v += v*gain*s;
                                v = (v<0?0:v);
                                v = (v>=256?256-1.0/Ratio:v);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[i][j][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[i][j][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[i][j][j];
                        }
                }
        }
        double avg;

        for(int i = 0; i < 9; i++){
                for(int j =0; j < 9; j++){
                        for(int k =0; k < 9; k++){
                                if(i==j && j==k)
                                        break;
                                rgb2hsv(i*32,j*32,k*32,&h,&s,&in,&v);
                                if(h<dif_p || h>360+dif_n){
                                        avg = double(j+k)/2;
                                        ratio = (h<180?1-h/dif_p:1-(360-h)/dif_n*(-1));
                                        double intpart, fractpart;
                                        fractpart = modf (avg , &intpart);
                                        int intval = (int)intpart;
                                        tmp_c3d_lutR[i][j][k] += ratio*(r_gain[i][intval]*(1-fractpart)+r_gain[i][intval+1]*fractpart);
                                        tmp_c3d_lutG[i][j][k] += ratio*(g_gain[i][intval]*(1-fractpart)+g_gain[i][intval+1]*fractpart);
                                        tmp_c3d_lutB[i][j][k] += ratio*(b_gain[i][intval]*(1-fractpart)+b_gain[i][intval+1]*fractpart);
                                        fix_val(&tmp_c3d_lutR[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutG[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutB[i][j][k],256-1.0/Ratio);
                                }
                        }
                }
        }

}

//------------------------------------------------------------------------
void c3d_6axisAdj_g(int type, double dif_p, double dif_n,double gain, double tmp_c3d_lutR[9][9][9], double tmp_c3d_lutG[9][9][9], double tmp_c3d_lutB[9][9][9])
{
        double r_gain[9][9] = {0}, g_gain[9][9] = {0}, b_gain[9][9] = {0};
        double h, s, v, in;
        double tmp_r, tmp_g, tmp_b;
        double ratio;

        if(type == 1){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                rgb2hsv(c3d_lutR[j][i][j],c3d_lutG[j][i][j],c3d_lutB[j][i][j],&h,&s,&in,&v);
                                h += gain;
                                h = fmod(h+360, 360);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][i][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][i][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][i][j];
                        }
                }
        }else if(type == 2){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                rgb2hsv(c3d_lutR[j][i][j],c3d_lutG[j][i][j], c3d_lutB[j][i][j],&h,&s,&in,&v);
                                s += s*gain;
                                s = (s<0?0:s);
                                s = (s>1?1:s);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][i][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][i][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][i][j];
                        }
                }
        }else if(type == 3){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                //hsv
                                rgb2hsv(c3d_lutR[j][i][j],c3d_lutG[j][i][j],c3d_lutB[j][i][j],&h,&s,&in,&v);
                                v += v*gain*s;
                                v = (v<0?0:v);
                                v = (v>=256?256-1.0/Ratio:v);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][i][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][i][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][i][j];
                        }
                }
        }
        double avg;
        for(int i = 0; i < 9; i++){
                for(int j =0; j < 9; j++){
                        for(int k =0; k < 9; k++){
                                rgb2hsv(i*32,j*32,k*32,&h,&s,&in,&v);
                                if(h>120+dif_n && h<120+dif_p){
                                        avg = double(i+k)/2;
                                        ratio = (h>120?1-(h-120)/dif_p:1-(120-h)/dif_n*(-1));
                                        double intpart, fractpart;
                                        fractpart = modf (avg , &intpart);
                                        int intval = (int)intpart;
                                        tmp_c3d_lutR[i][j][k] += ratio*(r_gain[j][intval]*(1-fractpart)+r_gain[j][intval+1]*fractpart);
                                        tmp_c3d_lutG[i][j][k] += ratio*(g_gain[j][intval]*(1-fractpart)+g_gain[j][intval+1]*fractpart);
                                        tmp_c3d_lutB[i][j][k] += ratio*(b_gain[j][intval]*(1-fractpart)+b_gain[j][intval+1]*fractpart);
                                        fix_val(&tmp_c3d_lutR[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutG[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutB[i][j][k],256-1.0/Ratio);
                                }
                        }
                }
        }
}
//---------------------------------------------------------------------

void c3d_6axisAdj_b(int type, double dif_p, double dif_n,double gain, double tmp_c3d_lutR[9][9][9], double tmp_c3d_lutG[9][9][9], double tmp_c3d_lutB[9][9][9])
{
        double r_gain[9][9] = {0}, g_gain[9][9] = {0}, b_gain[9][9] = {0};
        double h, s, v, in;
        double tmp_r, tmp_g, tmp_b;
        double ratio;

        if(type == 1){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                rgb2hsv(c3d_lutR[j][j][i],c3d_lutG[j][j][i],c3d_lutB[j][j][i],&h,&s,&in,&v);
                                h += gain;
                                h = fmod(h+360, 360);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][j][i];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][j][i];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][j][i];
                        }
                }
        }else if(type == 2){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                rgb2hsv(c3d_lutR[j][j][i],c3d_lutG[j][j][i],c3d_lutB[j][j][i],&h,&s,&in,&v);
                                s += s*gain;
                                s = (s<0?0:s);
                                s = (s>1?1:s);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][j][i];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][j][i];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][j][i];
                        }
                }
        }else if(type == 3){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                //hsv
                                rgb2hsv(c3d_lutR[j][j][i],c3d_lutG[j][j][i],c3d_lutB[j][j][i],&h,&s,&in,&v);
                                v += v*gain*s;
                                v = (v<0?0:v);
                                v = (v>=256?256-1.0/Ratio:v);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][j][i];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][j][i];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][j][i];
                        }
                }
        }
        double avg;
        for(int i = 0; i < 9; i++){
                for(int j =0; j < 9; j++){
                        for(int k =0; k < 9; k++){
                                rgb2hsv(i*32,j*32,k*32,&h,&s,&in,&v);
                                if(h>240+dif_n && h<240+dif_p){
                                        ratio = (h>240?1-(h-240)/dif_p:1-(240-h)/dif_n*(-1));
                                        avg = double(i+j)/2;
                                        double intpart, fractpart;
                                        fractpart = modf (avg , &intpart);
                                        int intval = (int)intpart;
                                        tmp_c3d_lutR[i][j][k] += ratio*(r_gain[k][intval]*(1-fractpart)+r_gain[k][intval+1]*fractpart);
                                        tmp_c3d_lutG[i][j][k] += ratio*(g_gain[k][intval]*(1-fractpart)+g_gain[k][intval+1]*fractpart);
                                        tmp_c3d_lutB[i][j][k] += ratio*(b_gain[k][intval]*(1-fractpart)+b_gain[k][intval+1]*fractpart);
                                        fix_val(&tmp_c3d_lutR[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutG[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutB[i][j][k],256-1.0/Ratio);
                                }
                        }
                }
        }
}

//------------------------------------------------------------------------
void c3d_6axisAdj_c(int type, double dif_p, double dif_n,double gain, double tmp_c3d_lutR[9][9][9], double tmp_c3d_lutG[9][9][9], double tmp_c3d_lutB[9][9][9])
{
        double r_gain[9][9] = {0}, g_gain[9][9] = {0}, b_gain[9][9] = {0};
        double h, s, v, in;
        double tmp_r, tmp_g, tmp_b;
        double ratio;

        if(type == 1){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                rgb2hsv(c3d_lutR[i][j][j],c3d_lutG[i][j][j],c3d_lutB[i][j][j],&h,&s,&in,&v);
                                h += gain;
                                h = fmod(h+360, 360);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[i][j][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[i][j][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[i][j][j];
                        }
                }
        }else if(type == 2){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                rgb2hsv(c3d_lutR[i][j][j],c3d_lutG[i][j][j],c3d_lutB[i][j][j],&h,&s,&in,&v);
                                s += s*gain;
                                s = (s<0?0:s);
                                s = (s>1?1:s);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[i][j][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[i][j][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[i][j][j];
                        }
                }
        }else if(type == 3){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                //hsv
                                rgb2hsv(c3d_lutR[i][j][j],c3d_lutG[i][j][j],c3d_lutB[i][j][j],&h,&s,&in,&v);
                                v += v*gain*s;
                                v = (v<0?0:v);
                                v = (v>=256?256-1.0/Ratio:v);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[i][j][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[i][j][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[i][j][j];
                        }
                }
        }

        double avg;
        for(int i = 0; i < 9; i++){
                for(int j =0; j < 9; j++){
                        for(int k =0; k < 9; k++){
                                rgb2hsv(i*32,j*32,k*32,&h,&s,&in,&v);
                                if(h>180+dif_n && h< 180+dif_p){
                                        ratio = (h>180?1-(h-180)/dif_p:1-(180-h)/dif_n*(-1));
                                        avg = double(j+k)/2;
                                        double intpart, fractpart;
                                        fractpart = modf (avg , &intpart);
                                        int intval = (int)intpart;
                                        tmp_c3d_lutR[i][j][k] += ratio*(r_gain[i][intval]*(1-fractpart)+r_gain[i][intval+1]*fractpart);
                                        tmp_c3d_lutG[i][j][k] += ratio*(g_gain[i][intval]*(1-fractpart)+g_gain[i][intval+1]*fractpart);
                                        tmp_c3d_lutB[i][j][k] += ratio*(b_gain[i][intval]*(1-fractpart)+b_gain[i][intval+1]*fractpart);
                                        fix_val(&tmp_c3d_lutR[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutG[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutB[i][j][k],256-1.0/Ratio);
                                }
                        }
                }
        }
}
//------------------------------------------------------------------------

void c3d_6axisAdj_m(int type, double dif_p, double dif_n, double gain, double tmp_c3d_lutR[9][9][9], double tmp_c3d_lutG[9][9][9], double tmp_c3d_lutB[9][9][9])
{
        double r_gain[9][9] = {0}, g_gain[9][9] = {0}, b_gain[9][9] = {0};
        double h, s, v, in;
        double tmp_r, tmp_g, tmp_b;
        double ratio;

        if(type == 1){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                rgb2hsv(c3d_lutR[j][i][j],c3d_lutG[j][i][j],c3d_lutB[j][i][j],&h,&s,&in,&v);
                                h += gain;
                                h = fmod(h+360, 360);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][i][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][i][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][i][j];
                        }
                }
        }else if(type == 2){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                rgb2hsv(c3d_lutR[j][i][j],c3d_lutG[j][i][j],c3d_lutB[j][i][j],&h,&s,&in,&v);
                                s += s*gain;
                                s = (s<0?0:s);
                                s = (s>1?1:s);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][i][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][i][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][i][j];
                        }
                }
        }else if(type == 3){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                //hsv
                                rgb2hsv(c3d_lutR[j][i][j],c3d_lutG[j][i][j],c3d_lutB[j][i][j],&h,&s,&in,&v);
                                v += v*gain*s;
                                v = (v<0?0:v);
                                v = (v>=256?256-1.0/Ratio:v);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][i][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][i][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][i][j];
                        }
                }
        }
        double avg;
        for(int i = 0; i < 9; i++){
                for(int j =0; j < 9; j++){
                        for(int k =0; k < 9; k++){
                                rgb2hsv(i*32,j*32,k*32,&h,&s,&in,&v);
                                if(h>300+dif_n && h< 300+dif_p){
                                        ratio = (h>300?1-(h-300)/dif_p:1-(300-h)/dif_n*(-1));
                                        avg = double(i+k)/2;
                                        double intpart, fractpart;
                                        fractpart = modf (avg , &intpart);
                                        int intval = (int)intpart;
                                        tmp_c3d_lutR[i][j][k] += ratio*(r_gain[j][intval]*(1-fractpart)+r_gain[j][intval+1]*fractpart);
                                        tmp_c3d_lutG[i][j][k] += ratio*(g_gain[j][intval]*(1-fractpart)+g_gain[j][intval+1]*fractpart);
                                        tmp_c3d_lutB[i][j][k] += ratio*(b_gain[j][intval]*(1-fractpart)+b_gain[j][intval+1]*fractpart);
                                        fix_val(&tmp_c3d_lutR[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutG[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutB[i][j][k],256-1.0/Ratio);
                                }
                        }
                }
        }
}
//------------------------------------------------------------------------
void c3d_6axisAdj_y(int type,double dif_p, double dif_n,double gain, double tmp_c3d_lutR[9][9][9], double tmp_c3d_lutG[9][9][9], double tmp_c3d_lutB[9][9][9])
{
        double r_gain[9][9] = {0}, g_gain[9][9] = {0}, b_gain[9][9] = {0};
        double h, s, v, in;
        double tmp_r, tmp_g, tmp_b;
        double ratio;

        if(type == 1){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                rgb2hsv(c3d_lutR[j][j][i],c3d_lutG[j][j][i],c3d_lutB[j][j][i],&h,&s,&in,&v);
                                h += gain;
                                h = fmod(h+360, 360);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][j][i];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][j][i];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][j][i];
                        }
                }
        }else if(type == 2){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                //rgb2hsi(c3d_lutR[j][j][i]/power_dump,c3d_lutG[j][j][i]/power_dump,
                                //c3d_lutB[j][j][i]/power_dump,&h,&s,&in);
                                rgb2hsv(c3d_lutR[j][j][i],c3d_lutG[j][j][i],c3d_lutB[j][j][i],&h,&s,&in,&v);
                                s += s*gain;
                                s = (s<0?0:s);
                                s = (s>1?1:s);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                //hsi2rgb(h, s, in, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][j][i];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][j][i];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][j][i];
                        }
                }
        }else if(type == 3){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                //hsv
                                rgb2hsv(c3d_lutR[j][j][i],c3d_lutG[j][j][i],c3d_lutB[j][j][i],&h,&s,&in,&v);
                                v += v*gain*s;
                                v = (v<0?0:v);
                                v = (v>=256?256-1.0/Ratio:v);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][j][i];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][j][i];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][j][i];
                        }
                }
        }
        double avg;
        for(int i = 0; i < 9; i++){
                for(int j =0; j < 9; j++){
                        for(int k =0; k < 9; k++){
                                rgb2hsv(i*32,j*32,k*32,&h,&s,&in,&v);
                                //rgb2h(i*32,j*32,k*32,&h);
                                if(h>60+dif_n && h<60+dif_p){
                                        ratio = (h>60?1-(h-60)/dif_p:1-(60-h)/dif_n*(-1));
                                        avg = double(i+j)/2;
                                        double intpart, fractpart;
                                        fractpart = modf (avg , &intpart);
                                        int intval = (int)intpart;
                                        tmp_c3d_lutR[i][j][k] += ratio*(r_gain[k][intval]*(1-fractpart)+r_gain[k][intval+1]*fractpart);
                                        tmp_c3d_lutG[i][j][k] += ratio*(g_gain[k][intval]*(1-fractpart)+g_gain[k][intval+1]*fractpart);
                                        tmp_c3d_lutB[i][j][k] += ratio*(b_gain[k][intval]*(1-fractpart)+b_gain[k][intval+1]*fractpart);
                                        fix_val(&tmp_c3d_lutR[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutG[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutB[i][j][k],256-1.0/Ratio);
                                }
                        }
                }
        }
}
//----------------------------------------------------------------------------
void TC3DForm1::c3d_6axisAdj_h(bool flag)
{
        double h_gain = double(sb_c3d_Manual39_h->Position-sb_c3d_Manual39_h->Max/2)/10;
        double dif_n = (double)Get_Point_H_NegDif();
        double dif_p = (double)Get_Point_H_PosDif();

        double tmp_c3d_lutR[9][9][9],tmp_c3d_lutG[9][9][9],tmp_c3d_lutB[9][9][9];

        for(int i = 0; i < 9; i ++)
                for(int j = 0; j < 9; j ++)
                        for(int k = 0; k < 9; k ++){
                                tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
                                tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
                                tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
                        }
        double h, s, in, v;
        double r=0, g=0, b=0;
        if(sb_c3d_Point_HSV_h_g->Checked == true){    //global color rotate
                for(int i = 0; i < 9; i ++)
                        for(int j = 0; j < 9; j ++)
                                for(int k = 0; k < 9; k ++){
                                        rgb2hsv(tmp_c3d_lutR[i][j][k],tmp_c3d_lutG[i][j][k],tmp_c3d_lutB[i][j][k],&h,&s,&in,&v);
                                        h+=h_gain;
                                        h=fmod(h+360,360);
                                        hsv2rgb(h,s,v,&tmp_c3d_lutR[i][j][k],&tmp_c3d_lutG[i][j][k],&tmp_c3d_lutB[i][j][k]);
                                }
        }else{      //six color adjust
                if(rb_c3d_r->Checked == true){  //red
                        c3d_6axisAdj_r(1,dif_p,dif_n,h_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_g->Checked == true){    //green
                        c3d_6axisAdj_g(1,dif_p,dif_n,h_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_b->Checked == true){    //blue
                        c3d_6axisAdj_b(1,dif_p,dif_n,h_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_c->Checked == true){    //cyan
                        c3d_6axisAdj_c(1,dif_p,dif_n,h_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_y->Checked == true){    //yellow
                        c3d_6axisAdj_y(1,dif_p,dif_n,h_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_m->Checked == true){    //magenta
                        c3d_6axisAdj_m(1,dif_p,dif_n,h_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }
        }

        if(rb_c3d_r->Checked == true){
                r = tmp_c3d_lutR[8][0][0];
                g = tmp_c3d_lutG[8][0][0];
                b = tmp_c3d_lutB[8][0][0];
        }else if(rb_c3d_g->Checked == true){
                r = tmp_c3d_lutR[0][8][0];
                g = tmp_c3d_lutG[0][8][0];
                b = tmp_c3d_lutB[0][8][0];
        }else if(rb_c3d_b->Checked == true){
                r = tmp_c3d_lutR[0][0][8];
                g = tmp_c3d_lutG[0][0][8];
                b = tmp_c3d_lutB[0][0][8];
        }else if(rb_c3d_c->Checked == true){
                r = tmp_c3d_lutR[0][8][8];
                g = tmp_c3d_lutG[0][8][8];
                b = tmp_c3d_lutB[0][8][8];
        }else if(rb_c3d_y->Checked == true){
                r = tmp_c3d_lutR[8][8][0];
                g = tmp_c3d_lutG[8][8][0];
                b = tmp_c3d_lutB[8][8][0];
        }else if(rb_c3d_m->Checked == true){
                r = tmp_c3d_lutR[8][0][8];
                g = tmp_c3d_lutG[8][0][8];
                b = tmp_c3d_lutB[8][0][8];
        }
        Show_c3d_SimImg(r,g,b);
        Show_c3d_Img_sim();
        refresh_6axis_grid(r,g,b,tmp_c3d_lutR,tmp_c3d_lutG,tmp_c3d_lutB);

        if(flag==true){
                for(int i = 0; i < 9; i++)
                        for(int j = 0; j < 9; j++)
                                for(int k = 0; k < 9; k++){
                                        c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
                                        c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
                                        c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
                                }
        }
}
//---------------------------------------------------------------------------
void TC3DForm1::c3d_6axisAdj_s(bool flag)
{
        double c = StrToFloat(edt_c3d_satC->Text);
        double s_gain = (double)GetPointS_val()/100/c;
        double dif_n = double(sb_c3d_Manual39_hdn->Position-500)/10;
        double dif_p = double(sb_c3d_Manual39_hdp->Position)/10;

        double tmp_c3d_lutR[9][9][9],tmp_c3d_lutG[9][9][9],tmp_c3d_lutB[9][9][9];

        for(int i = 0; i < 9; i ++)
                for(int j = 0; j < 9; j ++)
                        for(int k = 0; k < 9; k ++){
                                tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
                                tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
                                tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
                        }
        double h, s, in, v;
        double r=0, g=0, b=0;
        if(sb_c3d_Point_HSV_s_g->Checked == true){
                for(int i = 0; i < 9; i ++)
                        for(int j = 0; j < 9; j ++)
                                for(int k = 0; k < 9; k ++){
                                        rgb2hsv(tmp_c3d_lutR[i][j][k],tmp_c3d_lutG[i][j][k],tmp_c3d_lutB[i][j][k],&h,&s,&in,&v);
                                        s+=s_gain*s;
                                        s = (s<0?0:s);
                                        s = (s>1?1:s);
                                        hsv2rgb(h,s,v,&tmp_c3d_lutR[i][j][k],&tmp_c3d_lutG[i][j][k],&tmp_c3d_lutB[i][j][k]);
                                }
        }else{
                if(rb_c3d_r->Checked == true){
                        c3d_6axisAdj_r(2,dif_p,dif_n,s_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_g->Checked == true){
                        c3d_6axisAdj_g(2,dif_p,dif_n,s_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_b->Checked == true){
                        c3d_6axisAdj_b(2,dif_p,dif_n,s_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_c->Checked == true){
                        c3d_6axisAdj_c(2,dif_p,dif_n,s_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_y->Checked == true){
                        c3d_6axisAdj_y(2,dif_p,dif_n,s_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_m->Checked == true){
                        c3d_6axisAdj_m(2,dif_p,dif_n,s_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }
                Show_c3d_SimImg(r,g,b);
                Show_c3d_Img_sim();
        }
        if(rb_c3d_r->Checked == true){
                r = tmp_c3d_lutR[8][0][0];
                g = tmp_c3d_lutG[8][0][0];
                b = tmp_c3d_lutB[8][0][0];
        }else if(rb_c3d_g->Checked == true){
                r = tmp_c3d_lutR[0][8][0];
                g = tmp_c3d_lutG[0][8][0];
                b = tmp_c3d_lutB[0][8][0];
        }else if(rb_c3d_b->Checked == true){
                r = tmp_c3d_lutR[0][0][8];
                g = tmp_c3d_lutG[0][0][8];
                b = tmp_c3d_lutB[0][0][8];
        }else if(rb_c3d_c->Checked == true){
                r = tmp_c3d_lutR[0][8][8];
                g = tmp_c3d_lutG[0][8][8];
                b = tmp_c3d_lutB[0][8][8];
        }else if(rb_c3d_y->Checked == true){
                r = tmp_c3d_lutR[8][8][0];
                g = tmp_c3d_lutG[8][8][0];
                b = tmp_c3d_lutB[8][8][0];
        }else if(rb_c3d_m->Checked == true){
                r = tmp_c3d_lutR[8][0][8];
                g = tmp_c3d_lutG[8][0][8];
                b = tmp_c3d_lutB[8][0][8];
        }
        Show_c3d_SimImg(r,g,b);
        Show_c3d_Img_sim();
        refresh_6axis_grid(r,g,b,tmp_c3d_lutR,tmp_c3d_lutG,tmp_c3d_lutB);
        if(flag==true){
                for(int i = 0; i < 9; i++)
                        for(int j = 0; j < 9; j++)
                                for(int k = 0; k < 9; k++){
                                        c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
                                        c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
                                        c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
                                }
        }
}
//------------------------------------------------------------------------
void TC3DForm1::c3d_6axisAdj_v(bool flag)
{
        double c = StrToFloat(edt_c3d_valC->Text);
        double v_gain = double(sb_c3d_Manual39_v->Position-1000)/1000/c;
        double dif_n = (double)Get_Point_H_NegDif();
        double dif_p = (double)Get_Point_H_PosDif();
        double tmp_c3d_lutR[9][9][9],tmp_c3d_lutG[9][9][9],tmp_c3d_lutB[9][9][9];

        for(int i = 0; i < 9; i ++)
                for(int j = 0; j < 9; j ++)
                        for(int k = 0; k < 9; k ++){
                                tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
                                tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
                                tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
                        }
        double h, s, in, v;
        double r=0, g=0, b=0;
        if(sb_c3d_Point_HSV_v_g->Checked == true){
                for(int i = 0; i < 9; i ++)
                        for(int j = 0; j < 9; j ++)
                                for(int k = 0; k < 9; k ++){
                                        rgb2hsv(tmp_c3d_lutR[i][j][k],tmp_c3d_lutG[i][j][k],tmp_c3d_lutB[i][j][k],&h,&s,&in,&v);
                                        v+=v*v_gain*s;
                                        v = (v<0?0:v);
                                        v = (v>=256?256-1.0/Ratio:v);
                                        hsv2rgb(h,s,v,&tmp_c3d_lutR[i][j][k],&tmp_c3d_lutG[i][j][k],&tmp_c3d_lutB[i][j][k]);
                                }
        }else{
                if(rb_c3d_r->Checked == true){
                        c3d_6axisAdj_r(3,dif_p,dif_n,v_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_g->Checked == true){
                        c3d_6axisAdj_g(3,dif_p,dif_n,v_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_b->Checked == true){
                        c3d_6axisAdj_b(3,dif_p,dif_n,v_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_c->Checked == true){
                        c3d_6axisAdj_c(3,dif_p,dif_n,v_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_y->Checked == true){
                        c3d_6axisAdj_y(3,dif_p,dif_n,v_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_m->Checked == true){
                        c3d_6axisAdj_m(3,dif_p,dif_n,v_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }
                Show_c3d_SimImg(r,g,b);
                Show_c3d_Img_sim();
        }
        if(rb_c3d_r->Checked == true){
                r = tmp_c3d_lutR[8][0][0];
                g = tmp_c3d_lutG[8][0][0];
                b = tmp_c3d_lutB[8][0][0];
        }else if(rb_c3d_g->Checked == true){
                r = tmp_c3d_lutR[0][8][0];
                g = tmp_c3d_lutG[0][8][0];
                b = tmp_c3d_lutB[0][8][0];
        }else if(rb_c3d_b->Checked == true){
                r = tmp_c3d_lutR[0][0][8];
                g = tmp_c3d_lutG[0][0][8];
                b = tmp_c3d_lutB[0][0][8];
        }else if(rb_c3d_c->Checked == true){
                r = tmp_c3d_lutR[0][8][8];
                g = tmp_c3d_lutG[0][8][8];
                b = tmp_c3d_lutB[0][8][8];
        }else if(rb_c3d_y->Checked == true){
                r = tmp_c3d_lutR[8][8][0];
                g = tmp_c3d_lutG[8][8][0];
                b = tmp_c3d_lutB[8][8][0];
        }else if(rb_c3d_m->Checked == true){
                r = tmp_c3d_lutR[8][0][8];
                g = tmp_c3d_lutG[8][0][8];
                b = tmp_c3d_lutB[8][0][8];
        }
        Show_c3d_SimImg(r,g,b);
        Show_c3d_Img_sim();
        refresh_6axis_grid(r,g,b,tmp_c3d_lutR,tmp_c3d_lutG,tmp_c3d_lutB);

        if(flag==true){
                for(int i = 0; i < 9; i++)
                        for(int j = 0; j < 9; j++)
                                for(int k = 0; k < 9; k++){
                                        c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
                                        c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
                                        c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
                                }
        }
}
*/
/***********************************************
//      method 1                              //
***********************************************/

void TC3DForm1::c3d_hsv_FixGain_h(double tmp_c3d_lutH[9][9][9])
{
    if (cb_c3d_Point_HSV_h_g->Checked == true) {
	double h_gain = double (sb_c3d_Manual39_h->Position - sb_c3d_Manual39_h->Max / 2) / 10;
	for (int i = 0; i < 9; i++)
	    for (int j = 0; j < 9; j++)
		for (int k = 0; k < 9; k++) {
		    if (c3d_lutH[i][j][k] != 0 || c3d_lutS[i][j][k] != 0)	//固定灰階
			tmp_c3d_lutH[i][j][k] = fmod((c3d_lutH[i][j][k] + h_gain) + 360, 360);
		}
	return;
    }

    int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
    int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
    int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);

    double h_gain = double (sb_c3d_Manual39_h->Position - sb_c3d_Manual39_h->Max / 2) / 10;
    if (h_gain == 0) {
	for (int i = 0; i < TBL_SIZE; i++)
	    for (int j = 0; j < TBL_SIZE; j++)
		for (int k = 0; k < TBL_SIZE; k++)
		    tmp_c3d_lutH[i][j][k] = c3d_lutH[i][j][k];
	return;
    }
    double h1, h2;
    double dif_n = (double) Get_Point_H_NegDif();
    double dif_p = (double) Get_Point_H_PosDif();
    double low = c3d_lutH[idx_r][idx_g][idx_b] + dif_n;	//負向的diffusion邊界
    double high = c3d_lutH[idx_r][idx_g][idx_b] + dif_p;	//正向的diffusion邊界
    double new_pos_rng, new_neg_rng;
    if (h_gain > 0) {
	h1 = c3d_lutH[idx_r][idx_g][idx_b];	//使用者調整的h 上界
	h2 = c3d_lutH[idx_r][idx_g][idx_b] - h_gain;	//使用者調整的h 下界
	new_pos_rng = dif_p - h_gain;	//原本做正向diffusion的範圍所要對應到的新範圍
	new_neg_rng = dif_n * (-1);	//原本做負向diffusion的範圍所要對應到的新範圍
	dif_n = dif_n + h_gain;
    } else {
	h1 = c3d_lutH[idx_r][idx_g][idx_b] - h_gain;	//使用者調整的h 上界
	h2 = c3d_lutH[idx_r][idx_g][idx_b];	//使用者調整的h 下界
	new_pos_rng = dif_p;	//原本做正向diffusion的範圍所要對應到的新範圍
	new_neg_rng = dif_n * (-1) + h_gain;	//原本做負向diffusion的範圍所要對應到的新範圍
	dif_p = dif_p + h_gain;
    }

    double tmp_h;		//對每個hue值(tmp_h)計算diffusion量

    bool Is_dif = false;	//flag recording tmp_h to do diffusion or not
    double ratio, rslt;

    for (int i = 0; i < TBL_SIZE; i++)
	for (int j = 0; j < TBL_SIZE; j++)
	    for (int k = 0; k < TBL_SIZE; k++) {
		Is_dif = false;
		tmp_h = c3d_lutH[i][j][k];

		if (low < 0 && tmp_h > low + 360) {
		    tmp_h -= 360;
		    Is_dif = true;
		} else if (high >= 360 && tmp_h < fmod(high, 360)) {
		    tmp_h += 360;
		    Is_dif = true;
		} else if (tmp_h >= low && tmp_h < high) {
		    Is_dif = true;
		}
		if (Is_dif == true) {
		    if (tmp_h <= h1 && tmp_h >= h2) {
			rslt = tmp_h + h_gain;
		    } else if (tmp_h < h2) {
			ratio = (tmp_h - low) / dif_n * (-1);
			rslt = ratio * new_neg_rng + low;
		    } else if (tmp_h > h1) {
			ratio = (tmp_h - high) / dif_p;
			rslt = ratio * new_pos_rng + high;
		    }
		    tmp_c3d_lutH[i][j][k] = fmod(rslt + 360, 360);
		} else {
		    tmp_c3d_lutH[i][j][k] = c3d_lutH[i][j][k];
		}
	    }
}

void TC3DForm1::c3d_hsv_FixGain(bool flg_wri)
{
/*       //ouble tmp_c3d_lutH[9][9][9],tmp_c3d_lutS[9][9][9],tmp_c3d_lutV[9][9][9];

        c3d_hsv_FixGain_h(tmp_c3d_lutH);

        //Sat & Value值不動
        for(int i = 0; i < 9; i++)
                for(int j = 0; j < 9; j++)
                        for(int k = 0; k < 9; k++){
                                tmp_c3d_lutS[i][j][k] = c3d_lutS[i][j][k];
                                tmp_c3d_lutV[i][j][k] = c3d_lutV[i][j][k];
                        }
        //Grey level remain original value
        for(int c = 0; c < TBL_SIZE; c++){
                tmp_c3d_lutH[c][c][c] = c3d_lutH[c][c][c];
                tmp_c3d_lutS[c][c][c] = c3d_lutS[c][c][c];
                tmp_c3d_lutV[c][c][c] = c3d_lutV[c][c][c];
        }

        for(int i = 0; i < TBL_SIZE; i++)
                for(int j = 0; j < TBL_SIZE; j++)
                        for(int k = 0; k < TBL_SIZE; k++){
                                hsv2rgb(tmp_c3d_lutH[i][j][k],tmp_c3d_lutS[i][j][k],tmp_c3d_lutV[i][j][k],
                                &tmp_c3d_lutR[i][j][k], &tmp_c3d_lutG[i][j][k], &tmp_c3d_lutB[i][j][k]);
                        }

        if(flg_wri==true){
                for(int i = 0; i < TBL_SIZE; i++)
                        for(int j = 0; j < TBL_SIZE; j++)
                                for(int k = 0; k < TBL_SIZE; k++){
                                        c3d_lutH[i][j][k] = tmp_c3d_lutH[i][j][k];
                                        c3d_lutS[i][j][k] = tmp_c3d_lutS[i][j][k];
                                        c3d_lutV[i][j][k] = tmp_c3d_lutV[i][j][k];
                                        c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
                                        c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
                                        c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
                                }
        }
        int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
        int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
        int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);

        Show_c3d_CorImg(tmp_c3d_lutR[idx_r][idx_g][idx_b], tmp_c3d_lutG[idx_r][idx_g][idx_b],
        tmp_c3d_lutB[idx_r][idx_g][idx_b]);

        double r = StrToFloat(lb_c3d_selR->Caption);
        double g = StrToFloat(lb_c3d_selG->Caption);
        double b = StrToFloat(lb_c3d_selB->Caption);
        double sim_r, sim_g, sim_b;
        C3Dsim_t(r, g, b, &sim_r, &sim_g, &sim_b);
        Show_c3d_SimImg(sim_r, sim_g, sim_b);
        Show_c3d_Img_sim();
        refresh_6axis_grid_t(r,g,b);             */
}


double reset_dh_range(double h)
{
    h = (h > 150 ? h - 360 : h);
    h = (h < -150 ? h + 360 : h);
    return h;
}
void TC3DForm1::SmoothValue_2Gray(double s, double v, double *col)
{
    if (rg_v_smooth2gray->ItemIndex == 1) {
	if (s < 0.666) {
	    int v_idx = floor(v / 32);
	    double value_g = StrToFloat(sg_Gray->Cells[3][v_idx + 1]);
	    *col = *col * s / 0.666 + value_g * (1 - s / 0.666);
	    /*
	       int v_l = floor(v/32);
	       int v_h = v_l+1;
	       double value_g;
	       if(v_l>=8){
	       value_g = StrToFloat(sg_Gray->Cells[3][v_l+1]);
	       }else
	       value_g = (StrToFloat(sg_Gray->Cells[3][v_l+1])*(v_h*32-v)/32+
	       StrToFloat(sg_Gray->Cells[3][v_h+1])*(v-v_l*32)/32);
	       *col = *col*s/0.666+value_g*(1-s/0.666); */
	}
    }
}
void TC3DForm1::SmoothSaturation(double s, double gain, double *col)
{
    double Sat_smpl = gain * 0.666;
    double tmp_sat;
    if (rg_Sat_smooth->ItemIndex == 2) {
	// Gaussian curve
	if (s < 0.666) {
	    double x = 1 - s / 0.666;
	    double Gauss_distr = exp((-1) * (x * x) / (2 * sigma_lgt * sigma_lgt));
	    tmp_sat = Gauss_distr * Sat_smpl;
	    if (Sat_smpl > 0.666 && tmp_sat < *col)
		*col = tmp_sat;
	} else {
	    double x = (s - 0.666) / 0.334;
	    double Gauss_distr = exp((-1) * (x * x) / (2 * sigma_st * sigma_st));
	    *col = (1 - Gauss_distr) * (1 - Sat_smpl) + Sat_smpl;
	}
    } else if (rg_Sat_smooth->ItemIndex == 1) {
	// Linear Gain
	if (s < 0.666) {
	    *col = s * ((Sat_smpl / 0.666) * (s / 0.666));
	} else {
	    *col = s * (Sat_smpl / 0.666 * (1 - (s - 0.666) / 0.333) + 1 * (s - 0.666) / 0.333);
	}
    } else if (rg_Sat_smooth->ItemIndex == 3) {
	// Gaussian distribution with Gauss, by pass
	if (s < 0.666) {
	    double x = 1 - s / 0.666;
	    double Gauss_distr = exp((-1) * (x * x) / (2 * sigma_lgt * sigma_lgt));
	    if (Sat_smpl > 0.666)
		*col = s * (Gauss_distr * gain + (1 - Gauss_distr) * 1);
	} else {
	    *col = (s - 0.666) / 0.334 * (1 - Sat_smpl) + Sat_smpl;
	    //*col= s*(gain*(1-((s-0.666)/0.334))+1*(s-0.666)/0.334);
	}
    }
}

void TC3DForm1::Manual39_light(double h, double s, double v, double col[3])
{				//value >= 192
    if (h == 0 && s == 0) {	//Gray level, do not Adjust
	col[0] = 0;
	col[1] = 0;
	col[2] = v;
	return;
    }

    double col_v = 192;		// Sample point V, S
    double col_s = 0.666;

    int h_l = floor(h / 30) * 30;	// lower bound Hue
    int h_h = (h_l + 30 >= 360 ? 0 : h_l + 30);	//upper bound Hue
    // H difference (h_gain) with Hue lower bound
    double dh_l = sg_12color1->Cells[1][h_l / 30 + 1] - h_l;
    dh_l = reset_dh_range(dh_l);
    // H difference with Hue upper bound
    double dh_h = sg_12color1->Cells[1][h_h / 30 + 1] - (h_l + 30);
    dh_h = reset_dh_range(dh_h);

    // rs_l is s_gain at lower bound Hue
    // rs_h is s_gain at upper bound Hue
    double rs_l = StrToFloat(sg_12color1->Cells[2][h_l / 30 + 1]) / col_s;
    double rs_h = StrToFloat(sg_12color1->Cells[2][h_h / 30 + 1]) / col_s;

    // rv_l is v_gain at lower bound Hue
    // rv_h is v_gain at upper bound Hue
    double rv_l = StrToFloat(sg_12color1->Cells[3][h_l / 30 + 1]) / col_v;
    double rv_h = StrToFloat(sg_12color1->Cells[3][h_h / 30 + 1]) / col_v;

    // Hue distance to lower bound hue, 30 for normalize to 0~1
    double l_ratio = (h - h_l) / 30;
    col[0] = l_ratio * dh_h + (1 - l_ratio) * dh_l + h;	// Adjust Hue
    col[1] = (l_ratio * rs_h + (1 - l_ratio) * rs_l) * s;	// Adjust Saturation
    col[2] = (l_ratio * rv_h + (1 - l_ratio) * rv_l) * v;	// Adjust Value

    SmoothValue_2Gray(s, v, &col[2]);

    double s_gain = (l_ratio * rs_h + (1 - l_ratio) * rs_l);
    SmoothSaturation(s, s_gain, &col[1]);
}

void TC3DForm1::Manual39_dark(double h, double s, double v, double col[3])
{
    //value <= 96
    if (h == 0 && s == 0) {
	col[0] = 0;
	col[1] = 0;
	col[2] = v;
	return;
    }
    double col_v = 96;
    double col_s = 0.666;

    int h_l = floor(h / 30) * 30;
    int h_h = (h_l + 30 >= 360 ? 0 : h_l + 30);
    double dh_l = sg_12color2->Cells[1][h_l / 30 + 1] - h_l;
    double dh_h = sg_12color2->Cells[1][h_h / 30 + 1] - (h_l + 30);
    dh_l = reset_dh_range(dh_l);
    dh_h = reset_dh_range(dh_h);
    double rs_l = StrToFloat(sg_12color2->Cells[2][h_l / 30 + 1]) / col_s;
    double rs_h = StrToFloat(sg_12color2->Cells[2][h_h / 30 + 1]) / col_s;

    double l_ratio = (h - h_l) / 30;
    col[0] = l_ratio * dh_h + (1 - l_ratio) * dh_l + h;
    col[1] = (l_ratio * rs_h + (1 - l_ratio) * rs_l) * s;

    double rv_l_96 = StrToFloat(sg_12color2->Cells[3][h_l / 30 + 1]) / col_v;
    double rv_h_96 = StrToFloat(sg_12color2->Cells[3][h_h / 30 + 1]) / col_v;
    double rv_96 = (l_ratio * rv_h_96 + (1 - l_ratio) * rv_l_96);

    /////////v32////////////
    col_v = 32;
    h_l = floor(h / 60) * 60;
    h_h = (h_l + 60 >= 360 ? 0 : h_l + 60);
    dh_l = sg_Dark->Cells[1][h_l / 60 + 1] - h_l;
    dh_h = sg_Dark->Cells[1][h_h / 60 + 1] - (h_l + 60);
    double rv_l_32 = StrToFloat(sg_Dark->Cells[3][h_l / 60 + 1]) / col_v;
    double rv_h_32 = StrToFloat(sg_Dark->Cells[3][h_h / 60 + 1]) / col_v;
    l_ratio = (h - h_l) / 60;
    double v_32 = (l_ratio * rv_h_32 + (1 - l_ratio) * rv_l_32) * col_v;

    if (v > 96) {
	col[2] = rv_96 * v;
    } else if (v == 96) {
	col[2] = rv_96 * 96;
    } else if (v == 32) {
	col[2] = v_32;
    } else if (v == 64) {
	col[2] = (rv_96 * 96 + v_32) / 2;
    } else {
	col[2] = v;		//value == 0
    }

    SmoothValue_2Gray(s, v, &col[2]);

    double s_gain = (l_ratio * rs_h + (1 - l_ratio) * rs_l);
    SmoothSaturation(s, s_gain, &col[1]);
}
void TC3DForm1::Manual39_mid(double h, double s, double v, double col[3])
{
    // 96 <= value <= 192
    if (h == 0 && s == 0) {
	col[0] = 0;
	col[1] = 0;
	col[2] = v;
	return;
    }

    double col_192[3], col_96[3];
    Manual39_light(h, s, 192, col_192);
    Manual39_dark(h, s, 96, col_96);

    double l_v_ratio = (v - 96) / (192 - 96);

    double dh_l = col_96[0] - h;
    dh_l = reset_dh_range(dh_l);	// h_gain, when v=96
    double dh_h = col_192[0] - h;
    dh_h = reset_dh_range(dh_h);	// h_gain, when v=192

    double rs_l = StrToFloat(col_96[1]) / s;	// s_gain, when v=96
    double rs_h = StrToFloat(col_192[1]) / s;	// s_gain, when v=192

    double rv_l = col_96[2] / 96;	// v_gain, when v=96
    double rv_h = col_192[2] / 192;	// v_gain, when v=192

    col[0] = l_v_ratio * dh_h + (1 - l_v_ratio) * dh_l + h;
    col[1] = (l_v_ratio * rs_h + (1 - l_v_ratio) * rs_l) * s;
    col[2] = (l_v_ratio * rv_h + (1 - l_v_ratio) * rv_l) * v;

    SmoothValue_2Gray(s, v, &col[2]);
    double s_gain = l_v_ratio * rs_h + (1 - l_v_ratio) * rs_l;
    SmoothSaturation(s, s_gain, &col[1]);
}

// 套用Hue page調整的數值計算table值
// 用原始9x9x9 rgb table轉到HSV數值來計算, 與記憶體內的table無關
void TC3DForm1::Manual39_color_adj(bool flg_wri)
{
    double h, s, v, in;
    double col[3];

    /* for(int i = 0; i < TBL_SIZE; i++)
       for(int j = 0; j < TBL_SIZE; j++)
       for(int k = 0; k < TBL_SIZE; k++){
       rgb2hsv(tmp_c3d_lutR[i][j][k], tmp_c3d_lutG[i][j][k], tmp_c3d_lutB[i][j][k],
       &tmp_c3d_lutH[i][j][k],&tmp_c3d_lutS[i][j][k],&in,&tmp_c3d_lutV[i][j][k]);
       }
     */
    ////////////////////////////////////////////////////////
    int v_gray;
    double r, g, b;
    for (int i = 0; i < TBL_SIZE; i++)
	for (int j = 0; j < TBL_SIZE; j++)
	    for (int k = 0; k < TBL_SIZE; k++) {
		r = (i * 32 >= 256 ? 256 - 1 / Ratio : i * 32);
		g = (j * 32 >= 256 ? 256 - 1 / Ratio : j * 32);
		b = (k * 32 >= 256 ? 256 - 1 / Ratio : k * 32);
		rgb2hsv(r, g, b, &h, &s, &in, &v);
		//rgb2hsv(c3d_lutR[i][j][k], c3d_lutG[i][j][k],
		//c3d_lutB[i][j][k], &h,&s,&in,&v);
		if (h == 0 && s == 0) {
		    v_gray = (int) floor(v / 32 + 0.5) + 1;
		    col[0] = h;
		    col[1] = s;
		    col[2] = StrToFloat(sg_Gray->Cells[3][v_gray]);
		} else {
		    if (v >= 192) {
			Manual39_light(h, s, v, col);
		    } else if (v <= 96) {
			Manual39_dark(h, s, v, col);
		    } else {
			Manual39_mid(h, s, v, col);
		    }
		}
		if (col[2] >= 256)
		    col[2] = 256 - 1 / Ratio;
		if (col[1] >= 1)
		    col[1] = 1;
		if (col[0] < 0)
		    col[0] += 360;
		if (col[0] >= 360)
		    col[0] -= 360;
		tmp_c3d_lutH[i][j][k] = col[0];
		tmp_c3d_lutS[i][j][k] = col[1];
		tmp_c3d_lutV[i][j][k] = col[2];
		hsv2rgb(tmp_c3d_lutH[i][j][k], tmp_c3d_lutS[i][j][k], tmp_c3d_lutV[i][j][k],
			&tmp_c3d_lutR[i][j][k], &tmp_c3d_lutG[i][j][k], &tmp_c3d_lutB[i][j][k]);

	    }
    ////////////////////////////////////////////////////////

    if (flg_wri == true) {
	for (int i = 0; i < TBL_SIZE; i++)
	    for (int j = 0; j < TBL_SIZE; j++)
		for (int k = 0; k < TBL_SIZE; k++) {
		    c3d_lutH[i][j][k] = tmp_c3d_lutH[i][j][k];
		    c3d_lutS[i][j][k] = tmp_c3d_lutS[i][j][k];
		    c3d_lutV[i][j][k] = tmp_c3d_lutV[i][j][k];
		    c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
		    c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
		    c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
		}
    }
}

// HSV的Hue page 調整
void TC3DForm1::c3d_hsvBase_adj(bool flg_wri)
{

    /*if(pc_HuePage_Grid->TabIndex == 2){
       double h_gain = ((double)sb_c3d_Manual39_h->Position-sb_c3d_Manual39_h->Max/2)/2;
       double c = StrToFloat(edt_c3d_satC->Text);
       double s_gain = ((double)sb_c3d_Manual39_s->Position-sb_c3d_Manual39_s->Max/2)/100/c;
       c = StrToFloat(edt_c3d_valC->Text);
       double v_gain = ((double)sb_c3d_Manual39_v->Position-sb_c3d_Manual39_v->Max/2)/100/c;
       for(int i = 0; i < Color_move_Nbr; i++)
       Modif_Point(RGB(Color_move[i][0],Color_move[i][1],Color_move[i][2]), h_gain, s_gain, v_gain,1);
       for(int i = 0; i < TBL_SIZE; i++)
       for(int j = 0; j < TBL_SIZE; j++)
       for(int k = 0; k < TBL_SIZE; k++){
       rgb2hsv(tmp_c3d_lutR[i][j][k], tmp_c3d_lutG[i][j][k], tmp_c3d_lutB[i][j][k],
       &tmp_c3d_lutH[i][j][k],&tmp_c3d_lutS[i][j][k],&in,&tmp_c3d_lutV[i][j][k]);
       }
       }else{ */

    for (int i = 0; i < TBL_SIZE; i++)
	for (int j = 0; j < TBL_SIZE; j++)
	    for (int k = 0; k < TBL_SIZE; k++) {
		tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
		tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
		tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
	    }
    double in;
    for (int i = 0; i < TBL_SIZE; i++)	//RGB table 轉到 hsv table 以做調整
	for (int j = 0; j < TBL_SIZE; j++)
	    for (int k = 0; k < TBL_SIZE; k++) {
		rgb2hsv(tmp_c3d_lutR[i][j][k], tmp_c3d_lutG[i][j][k], tmp_c3d_lutB[i][j][k],
			&tmp_c3d_lutH[i][j][k], &tmp_c3d_lutS[i][j][k], &in,
			&tmp_c3d_lutV[i][j][k]);
	    }

    c3d_HSVBase_h_adj();
    c3d_HSVBase_s_adj();
    c3d_HSVBase_v_adj();

    /*
       //Grey level remain original value
       for(int s = 0; s < TBL_SIZE; s++){
       tmp_c3d_lutH[s][s][s] = c3d_lutH[s][s][s];
       tmp_c3d_lutS[s][s][s] = c3d_lutS[s][s][s];
       tmp_c3d_lutV[s][s][s] = c3d_lutV[s][s][s];
       } */

    for (int i = 0; i < TBL_SIZE; i++)	//調整後的HSV table 轉到RGB
	for (int j = 0; j < TBL_SIZE; j++)
	    for (int k = 0; k < TBL_SIZE; k++) {
		hsv2rgb(tmp_c3d_lutH[i][j][k], tmp_c3d_lutS[i][j][k], tmp_c3d_lutV[i][j][k],
			&tmp_c3d_lutR[i][j][k], &tmp_c3d_lutG[i][j][k], &tmp_c3d_lutB[i][j][k]);
	    }

    if (flg_wri == true) {	//調整值從暫存的table(tmp_c3d_lutR...)更新到紀錄的table(c3d_lutR...)
	for (int i = 0; i < TBL_SIZE; i++)
	    for (int j = 0; j < TBL_SIZE; j++)
		for (int k = 0; k < TBL_SIZE; k++) {
		    c3d_lutH[i][j][k] = tmp_c3d_lutH[i][j][k];
		    c3d_lutS[i][j][k] = tmp_c3d_lutS[i][j][k];
		    c3d_lutV[i][j][k] = tmp_c3d_lutV[i][j][k];
		    c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
		    c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
		    c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
		}
    }
    //取調整的目標
    int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
    int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
    int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);

    //顯示到user interface
    Show_c3d_CorImg(tmp_c3d_lutR[idx_r][idx_g][idx_b], tmp_c3d_lutG[idx_r][idx_g][idx_b],
		    tmp_c3d_lutB[idx_r][idx_g][idx_b]);

    double r = StrToFloat(lb_c3d_selR->Caption);
    double g = StrToFloat(lb_c3d_selG->Caption);
    double b = StrToFloat(lb_c3d_selB->Caption);
    double sim_r, sim_g, sim_b;
    C3Dsim_t(r, g, b, &sim_r, &sim_g, &sim_b);
    Show_c3d_SimImg(sim_r, sim_g, sim_b);
    Show_c3d_Img_sim();
    //refresh_6axis_grid_t(r,g,b);
    if (TBL_SIZE == 9)
	Refresh_Manual39_Point();
    //refresh_c3d_color_grid();
}

//----------------------------------------------------------------------------



void TC3DForm1::c3d_HSVBase_h_adj()
{
    if (cb_c3d_Point_HSV_h_g->Checked == true) {
	double h_gain = (double) GetPointH_val();
	for (int i = 0; i < TBL_SIZE; i++)
	    for (int j = 0; j < TBL_SIZE; j++)
		for (int k = 0; k < TBL_SIZE; k++) {
		    if (c3d_lutH[i][j][k] != 0 || c3d_lutS[i][j][k] != 0)	//固定灰階
			tmp_c3d_lutH[i][j][k] = fmod((tmp_c3d_lutH[i][j][k] + h_gain) + 360, 360);
		}
	return;
    }

    int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
    int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
    int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);

    double h_gain = (double) GetPointH_val();
    /*
       if(h_gain==0){
       for(int i = 0; i < TBL_SIZE; i++)
       for(int j = 0; j < TBL_SIZE; j++)
       for(int k = 0; k < TBL_SIZE; k++)
       tmp_c3d_lutH[i][j][k] = c3d_lutH[i][j][k];
       return;
       } */
    double h = c3d_lutH[idx_r][idx_g][idx_b];	//使用者調整的h
    double s = c3d_lutS[idx_r][idx_g][idx_b];	//使用者調整的s
    double v = c3d_lutV[idx_r][idx_g][idx_b];	//使用者調整的v
    double dif_sv = StrToFloat(sb_c3d_Point_HSV_svd->Position);	// Saturaion 與Value的Diffusion 範圍
    //double h,s,in,v;   //table原本的hue value
    //rgb2hsv(idx_r*cube_dis,idx_g*cube_dis,idx_b*cube_dis,&h,&s,&in,&v);
    double dif_n = (double) Get_Point_H_NegDif();
    double dif_p = (double) Get_Point_H_PosDif();

    double tmp_h, tmp_s, tmp_v;	//對每個hue值(tmp_h), Saturation, value計算diffusion量
    double low = h + dif_n;	//負向的diffusion邊界
    double high = h + dif_p;	//正向的diffusion邊界
    //double new_pos_rng = dif_p-h_gain;      //原本做正向diffusion的範圍所要對應到的新範圍
    //double new_neg_rng = dif_n*(-1)+h_gain; //原本做負向diffusion的範圍所要對應到的新範圍
    bool Is_dif = false;	//flag recording tmp_h to do diffusion or not
    double ratio, ratio1, ratio2, ratio3, rslt;

    for (int i = 0; i < TBL_SIZE; i++)
	for (int j = 0; j < TBL_SIZE; j++)
	    for (int k = 0; k < TBL_SIZE; k++) {
		Is_dif = false;
		//rgb2hsv(i*cube_dis, j*cube_dis, k*cube_dis, &tmp_h, &s, &in, &v);
		tmp_h = c3d_lutH[i][j][k];
		tmp_s = c3d_lutS[i][j][k];
		tmp_v = c3d_lutV[i][j][k];

		if (low < 0 && tmp_h > low + 360) {
		    tmp_h -= 360;
		    Is_dif = true;
		} else if (high >= 360 && tmp_h < fmod(high, 360)) {
		    tmp_h += 360;
		    Is_dif = true;
		} else if (tmp_h > low && tmp_h < high) {
		    Is_dif = true;
		}

		if (Is_dif == true && (tmp_h != 0 || s != 0)) {	//灰階為H=0且s=0, 固定不動
		    if (tmp_h < h) {
			ratio1 = (h - tmp_h) / dif_n * (-1);
		    } else if (tmp_h >= h) {
			ratio1 = (tmp_h - h) / dif_p;
		    }
		    if (dif_sv == 10)	//整個Hue page 一起動, diffusion在Hue方向作
			ratio = 1 - ratio1;
		    else {	//考慮Hue與Saturation與Value方向的diffusion
			if (tmp_s < s + dif_sv / 10 && tmp_s > s - dif_sv / 10
			    && tmp_v < v + dif_sv / 10 * 255 && tmp_v > v - dif_sv / 10 * 255) {
			    ratio2 = fabs((tmp_s - s) / (dif_sv / 10));	//Saturation方向的diffusion ratio
			    ratio3 = fabs((tmp_v - v) / (dif_sv / 10 * 255));	//value方向的diffusion ratio
			    ratio =
				1 - pow((pow(ratio1, 2) + pow(ratio2, 2) + pow(ratio3, 2)) / 3,
					0.5);
			} else	//not gain
			    ratio = 0;
		    }
		    rslt = ratio * h_gain + tmp_h;
		    tmp_c3d_lutH[i][j][k] = fmod(rslt + 360, 360);
		} else {
		    tmp_c3d_lutH[i][j][k] = tmp_h;
		}

		/* 原本的方法, 平均分配在上界與下界之間
		   if(Is_dif == true && (tmp_h!=0 || s!=0)){  //灰階為H=0且s=0, 固定不動
		   if(tmp_h < h){
		   ratio = (tmp_h-low)/dif_n*(-1);
		   rslt = ratio * new_neg_rng + low;
		   }else if(tmp_h >= h){
		   ratio = (tmp_h-high)/dif_p;
		   rslt = ratio * new_pos_rng + high;
		   }
		   tmp_c3d_lutH[i][j][k] = fmod(rslt + 360, 360);
		   }
		   else{
		   tmp_c3d_lutH[i][j][k] = c3d_lutH[i][j][k];
		   } */
	    }
}

//---------------------------------------------------------------------------
void TC3DForm1::c3d_HSVBase_s_adj()
{
    if (cb_c3d_Point_HSV_s_g->Checked == true) {
	double c = StrToFloat(edt_c3d_satC->Text);
	double s_gain = (double) GetPointS_val() / 100 / c;
	double tmp;
	for (int i = 0; i < TBL_SIZE; i++)
	    for (int j = 0; j < TBL_SIZE; j++)
		for (int k = 0; k < TBL_SIZE; k++) {
		    if (c3d_lutH[i][j][k] != 0 || c3d_lutS[i][j][k] != 0) {	//固定灰階
			tmp = c3d_lutS[i][j][k] * (s_gain + 1);
			tmp = (tmp < 0 ? 0 : tmp);
			tmp = (tmp > 1 ? 1 : tmp);
			tmp_c3d_lutS[i][j][k] = tmp;
		    }
		}
	return;
    }

    int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
    int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
    int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);

    double c = StrToFloat(edt_c3d_satC->Text);
    double s_gain = (double) GetPointS_val() / 100 / c;

    double h = c3d_lutH[idx_r][idx_g][idx_b];	//使用者調整的h
    double s = c3d_lutS[idx_r][idx_g][idx_b];	//使用者調整的s
    double v = c3d_lutV[idx_r][idx_g][idx_b];	//使用者調整的v
    double dif_sv = StrToFloat(sb_c3d_Point_HSV_svd->Position);	// Saturaion 與Value的Diffusion 範圍
    //double h,s,in,v;   //table原本的hue value
    //rgb2hsv(idx_r*cube_dis,idx_g*cube_dis,idx_b*cube_dis,&h,&s,&in,&v);

    double dif_n = (double) Get_Point_H_NegDif();
    double dif_p = (double) Get_Point_H_PosDif();

    /*FILE* fptr = fopen ("change_S.txt","w");
       if(fptr==NULL){
       ShowMessage("can't open sat record file.");
       return;
       } */

    double tmp_h, tmp_s, tmp_v;	//對每個hue值(tmp_h)計算diffusion量
    double low = h + dif_n;	//負向的diffusion邊界
    double high = h + dif_p;	//正向的diffusion邊界
    bool Is_dif = false;	//flag recording tmp_h to do diffusion or not
    double ratio, ratio1, ratio2, ratio3;
    for (int i = 0; i < TBL_SIZE; i++)
	for (int j = 0; j < TBL_SIZE; j++)
	    for (int k = 0; k < TBL_SIZE; k++) {
		Is_dif = false;

		tmp_h = c3d_lutH[i][j][k];
		tmp_s = c3d_lutS[i][j][k];
		tmp_v = c3d_lutV[i][j][k];
		//rgb2hsv(i*cube_dis, j*cube_dis, k*cube_dis, &tmp_h, &s, &in, &v);

		if (low < 0 && tmp_h > low + 360) {
		    tmp_h -= 360;
		    Is_dif = true;
		} else if (high >= 360 && tmp_h < fmod(high, 360)) {
		    tmp_h += 360;
		    Is_dif = true;
		} else if (tmp_h > low && tmp_h < high) {
		    Is_dif = true;
		}
		if (Is_dif == true && (tmp_h != 0 || s != 0)) {	//灰階為H=0且s=0, 固定不動
		    if (tmp_h < h) {
			ratio1 = (h - tmp_h) / dif_n * (-1);
		    } else if (tmp_h >= h) {
			ratio1 = (tmp_h - h) / dif_p;
		    }
		    if (dif_sv == 10)	//整個Hue page 一起動, diffusion在Hue方向作
			ratio = 1 - ratio1;
		    else {	//考慮Hue與Saturation與Value方向的diffusion
			if (tmp_s < s + dif_sv / 10 && tmp_s > s - dif_sv / 10
			    && tmp_v < v + dif_sv / 10 * 255 && tmp_v > v - dif_sv / 10 * 255) {
			    ratio2 = fabs((tmp_s - s) / (dif_sv / 10));	//Saturation方向的diffusion ratio
			    ratio3 = fabs((tmp_v - v) / (dif_sv / 10 * 255));	//value方向的diffusion ratio
			    ratio =
				1 - pow((pow(ratio1, 2) + pow(ratio2, 2) + pow(ratio3, 2)) / 3,
					0.5);
			} else	//not gain
			    ratio = 0;
		    }

		    if (ratio > 1) {
			ShowMessage("S ratio >1");
			return;
		    }
		    tmp_c3d_lutS[i][j][k] = (ratio * s_gain + 1) * c3d_lutS[i][j][k];
		    if (tmp_c3d_lutS[i][j][k] > 1)
			tmp_c3d_lutS[i][j][k] = 1;
		    else if (tmp_c3d_lutS[i][j][k] < 0)
			tmp_c3d_lutS[i][j][k] = 0;
		} else
		    tmp_c3d_lutS[i][j][k] = c3d_lutS[i][j][k];
		//if(tmp_h>260 && tmp_h<280)
		//        ShowMessage("h="+FloatToStr(tmp_h)+"ratio"+FloatToStr(ratio)+"");
		//fprintf(fptr, "%.2f\t%.2f\n", c3d_lutS[i][j][k],tmp_c3d_lutS[i][j][k]);
	    }
    //fclose(fptr);
}

//------------------------------------------------------------------------
// Adjust Value to a moving direction in Hue Page
// The Adjust Point is record in "lb_c3d_tbl_ir->Caption" as value dir_r
// The Hue Page is decided by "diffusion" in user interface
void TC3DForm1::c3d_HSVBase_v_adj()
{
    if (cb_c3d_Point_HSV_v_g->Checked == true) {
	double c = StrToFloat(edt_c3d_valC->Text);
	double v_gain = (double) GetPointV_val() / 100 / c;
	double tmp;
	for (int i = 0; i < TBL_SIZE; i++)
	    for (int j = 0; j < TBL_SIZE; j++)
		for (int k = 0; k < TBL_SIZE; k++) {
		    tmp = c3d_lutV[i][j][k] * (v_gain + 1);
		    tmp = (tmp < 0 ? 0 : tmp);
		    tmp = (tmp >= 256 ? 256 - 1.0 / Ratio : tmp);
		    tmp_c3d_lutV[i][j][k] = tmp;
		}
	return;
    }

    int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
    int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
    int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);

    double c = StrToFloat(edt_c3d_valC->Text);
    double v_gain = (double) GetPointV_val() / 100 / c;

    double h = c3d_lutH[idx_r][idx_g][idx_b];	//使用者調整的h
    double s = c3d_lutS[idx_r][idx_g][idx_b];	//使用者調整的s
    double v = c3d_lutV[idx_r][idx_g][idx_b];	//使用者調整的v
    double dif_sv = StrToFloat(sb_c3d_Point_HSV_svd->Position);	// Saturaion 與Value的Diffusion 範圍
    //double h,s,in,v;   //table原本的hue value
    //rgb2hsv(idx_r*cube_dis,idx_g*cube_dis,idx_b*cube_dis,&h,&s,&in,&v);

    double dif_n = (double) Get_Point_H_NegDif();
    double dif_p = (double) Get_Point_H_PosDif();

    FILE *fptr = fopen("change_V.txt", "w");
    if (fptr == NULL) {
	ShowMessage("can't open value record file.");
	return;
    }

    double tmp_h, tmp_s, tmp_v;	//對每個hue值(tmp_h)計算diffusion量
    double low = h + dif_n;	//負向的diffusion邊界
    double high = h + dif_p;	//正向的diffusion邊界
    bool Is_dif = false;	//flag recording tmp_h to do diffusion or not
    double ratio, ratio1, ratio2, ratio3;
    for (int i = 0; i < TBL_SIZE; i++)
	for (int j = 0; j < TBL_SIZE; j++)
	    for (int k = 0; k < TBL_SIZE; k++) {
		Is_dif = false;

		tmp_h = c3d_lutH[i][j][k];
		tmp_s = c3d_lutS[i][j][k];
		tmp_v = c3d_lutV[i][j][k];
		//rgb2hsv(i*cube_dis, j*cube_dis, k*cube_dis, &tmp_h, &s, &in, &v);

		if (low < 0 && tmp_h > low + 360) {
		    tmp_h -= 360;
		    Is_dif = true;
		} else if (high >= 360 && tmp_h < fmod(high, 360)) {
		    tmp_h += 360;
		    Is_dif = true;
		} else if (tmp_h > low && tmp_h < high) {
		    Is_dif = true;
		}
		if (Is_dif == true && (tmp_h != 0 || s != 0)) {	//灰階為H=0且s=0, 固定不動
		    if (tmp_h < h) {
			ratio1 = (h - tmp_h) / dif_n * (-1);
		    } else if (tmp_h >= h) {
			ratio1 = (tmp_h - h) / dif_p;
		    }
		    if (dif_sv == 10)	//整個Hue page 一起動, diffusion在Hue方向作
			ratio = 1 - ratio1;
		    else {	//考慮Hue與Saturation與Value方向的diffusion
			if (tmp_s < s + dif_sv / 10 && tmp_s > s - dif_sv / 10
			    && tmp_v < v + dif_sv / 10 * 255 && tmp_v > v - dif_sv / 10 * 255) {
			    ratio2 = fabs((tmp_s - s) / (dif_sv / 10));	//Saturation方向的diffusion ratio
			    ratio3 = fabs((tmp_v - v) / (dif_sv / 10 * 255));	//value方向的diffusion ratio
			    ratio =
				1 - pow(((pow(ratio1, 2) + pow(ratio2, 2) + pow(ratio3, 2)) / 3),
					0.5);
			} else	//not gain
			    ratio = 0;
		    }

		    tmp_c3d_lutV[i][j][k] = (ratio * v_gain + 1) * c3d_lutV[i][j][k];
		    if (tmp_c3d_lutV[i][j][k] >= 256)
			tmp_c3d_lutV[i][j][k] = 256 - 1.0 / Ratio;
		    else if (tmp_c3d_lutV[i][j][k] < 0)
			tmp_c3d_lutV[i][j][k] = 0;
		    if (ratio > 1) {
			ShowMessage("V ratio >1");
			return;
		    }
		} else
		    tmp_c3d_lutV[i][j][k] = c3d_lutV[i][j][k];
		fprintf(fptr, "%.2f\t%.2f\n", c3d_lutV[i][j][k], tmp_c3d_lutV[i][j][k]);
	    }
    fclose(fptr);
}

//----------------------------------------------------------------------------
void __fastcall TC3DForm1::btn_c3d_writeClick(TObject * Sender)
{
    //cb_en->Checked = false;
    //cb_enClick(Sender);
    btn_c3d_write->Enabled = false;
    c3d_tmp_tbl_save();
    /*
       if(pc_Manual_Adjust->TabIndex == 0){
       cal_c3d_rgb(true);
       }else if(pc_Manual_Adjust->TabIndex == 1){
       if(rg_c3d_hsv_mode->ItemIndex==1){
       //        c3d_6axisAdj_h(true);
       //        c3d_6axisAdj_s(true);
       //        c3d_6axisAdj_v(true);
       }else if(rg_c3d_hsv_mode->ItemIndex==0)
       c3d_hsvBase_adj(true);
       else if(rg_c3d_hsv_mode->ItemIndex==2)
       c3d_MixAdj_h(true);
       }
     */
    c3d_lutArrange();
    /*
       FILE* fptr = fopen("1.txt","w");

       int tbl_tl = pow(TBL_SIZE,3);
       for(int i = 0; i < tbl_tl; i++){
       fprintf(fptr,"%d\t%d\t%d\t%d\t%d\t%d\n",c3d_r[0][i],c3d_g[0][i],
       c3d_b[0][i],c3d_r[1][i],c3d_g[1][i],c3d_b[1][i]);
       }
       fclose(fptr);         */

    if (EngineerForm->btn_connect_card->Enabled == false) {
	EngineerForm->SetWrite_PG(lut[0], c3d_r[1], total_len);	//red  LUT
	EngineerForm->SetWrite_PG(lut[1], c3d_g[1], total_len);	//green  LUT
	EngineerForm->SetWrite_PG(lut[2], c3d_b[1], total_len);	//blue  LUT
    }

    if (pc_Adjust->TabIndex == 1 && pc_point_color_adj->TabIndex == 0) {
	//Point Color - RGB
	sb_c3d_rgb_dis->Position = 0;
	Reset_c3d_Point_RGB_Scroll();
    } else if (pc_Adjust->TabIndex == 0 && pc_point_color_adj->TabIndex == 1)
	// Point Color - HSV Domain
	Reset_c3d_Point_HSV_Scroll();
    btn_c3d_write->Enabled = true;
    cb_en->Checked = true;
    cb_enClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::sb_c3d_rgb_disChange(TObject * Sender)
{
    lb_c3d_rgb_dis->Caption = sb_c3d_rgb_dis->Position;
    cal_c3d_rgb(false);
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::sb_c3d_rgb_rChange(TObject * Sender)
{
//sb_c3d_rgb_r為做3D LUT的Point Color adjust時, 對選擇的顏色做紅色值的增減量
    double r = floor((sb_c3d_rgb_r->Position - sb_c3d_rgb_r->Max / 2) / scrl_ratio);
    lb_c3d_rgb_r->Caption = r;
    double d = (sb_c3d_rgb_dis->Position) * cube_dis;	//實際的pixel數值差距為32

    if (r > 0 && d < r) {
	d += cube_dis;
	while (d - 5 < r) {
	    d += cube_dis;
	}
	sb_c3d_rgb_dis->Position = int (d / cube_dis) - 1;
    } else if (r < 0 && d < r * (-1)) {
	d += cube_dis;
	while (d - 5 < r * (-1)) {
	    d += cube_dis;
	}
	sb_c3d_rgb_dis->Position = int (d / cube_dis) - 1;
    }
    cal_c3d_rgb(false);
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::sb_c3d_rgb_gChange(TObject * Sender)
{
    //sb_c3d_rgb_g為做3D LUT的Point Color adjust時, 對選擇的顏色做綠色值的增減量
    double g = double (sb_c3d_rgb_g->Position - sb_c3d_rgb_g->Max / 2) / scrl_ratio;
    lb_c3d_rgb_g->Caption = g;
    double d = (sb_c3d_rgb_dis->Position) * cube_dis;

    if (g > 0 && d < g) {
	d += cube_dis;
	while (d - 5 < g) {
	    d += cube_dis;
	}
	sb_c3d_rgb_dis->Position = int (d / cube_dis) - 1;
    } else if (g < 0 && d < g * (-1)) {
	d += cube_dis;
	while (d - 5 < g * (-1)) {
	    d += cube_dis;
	}
	sb_c3d_rgb_dis->Position = int (d / cube_dis) - 1;
    }
    cal_c3d_rgb(false);
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::sb_c3d_rgb_bChange(TObject * Sender)
{
    //sb_c3d_rgb_b為做3D LUT的Point Color adjust時, 對選擇的顏色做藍色值的增減量
    double b = double (sb_c3d_rgb_b->Position - sb_c3d_rgb_b->Max / 2) / scrl_ratio;
    lb_c3d_rgb_b->Caption = b;
    double d = (sb_c3d_rgb_dis->Position) * cube_dis;

    if (b > 0 && d < b) {
	d += cube_dis;
	while (d - 5 < b) {
	    d += cube_dis;
	}
	sb_c3d_rgb_dis->Position = int (d / cube_dis) - 1;
    } else if (b < 0 && d < b * (-1)) {
	d += cube_dis;
	while (d - 5 < b * (-1)) {
	    d += cube_dis;
	}
	sb_c3d_rgb_dis->Position = int (d / cube_dis) - 1;
    }
    cal_c3d_rgb(false);
}

//---------------------------------------------------------------------------


void __fastcall TC3DForm1::sb_c3d_hsv_Change(TObject * Sender)
{
    double r, g, b, h, s, v, i, o_r, o_g, o_b;
    int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
    int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
    int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);
    double Tbl_r, Tbl_g, Tbl_b;
    if (rg_PointNum->ItemIndex == 1) {
	o_r = StrToFloat(lb_c3d_selR->Caption);
	o_g = StrToFloat(lb_c3d_selG->Caption);
	o_b = StrToFloat(lb_c3d_selB->Caption);
	C3Dsim(o_r, o_g, o_b, &Tbl_r, &Tbl_g, &Tbl_b);
    } else {
	Tbl_r = c3d_lutR[idx_r][idx_g][idx_b];
	Tbl_g = c3d_lutG[idx_r][idx_g][idx_b];
	Tbl_b = c3d_lutB[idx_r][idx_g][idx_b];
    }

    rgb2hsv(Tbl_r, Tbl_g, Tbl_b, &h, &s, &i, &v);

    double h_gain = ((double) sb_c3d_hsv_h->Position - sb_c3d_hsv_h->Max / 2) / 2;
    double c = StrToFloat(edt_c3d_satC->Text);
    double s_gain = ((double) sb_c3d_hsv_s->Position - sb_c3d_hsv_s->Max / 2) / 100 / c;
    c = StrToFloat(edt_c3d_valC->Text);
    double v_gain = ((double) sb_c3d_hsv_v->Position - sb_c3d_hsv_v->Max / 2) / 100 / c;
    lb_c3d_hsv_h->Caption = h_gain;
    lb_c3d_hsv_s->Caption = floor(FloatToStr(s_gain * s) * 1000) / 1000;
    lb_c3d_hsv_v->Caption = v_gain * v;

    h += h_gain;
    s *= (1 + s_gain);
    v *= (1 + v_gain);
    h = fmod(h + 360, 360);

    if (s > 1)
	s = 1;
    else if (s < 0)
	s = 0;
    if (v > 255)
	v = 255;
    else if (v < 0)
	v = 0;
    hsv2rgb(h, s, v, &r, &g, &b);


    if (r > 256 || g > 256 || b > 256 || r < 0 || g < 0 || b < 0)
	return;

    sb_c3d_rgb_r->Position = (r - Tbl_r) + sb_c3d_rgb_r->Max / 2;
    sb_c3d_rgb_g->Position = (g - Tbl_g) + sb_c3d_rgb_g->Max / 2;
    sb_c3d_rgb_b->Position = (b - Tbl_b) + sb_c3d_rgb_b->Max / 2;

    sb_c3d_rgb_rChange(Sender);
    sb_c3d_rgb_gChange(Sender);
    sb_c3d_rgb_bChange(Sender);

    Show_c3d_CorImg(r, g, b);

    //cal_c3d_rgb(false);
}


void TC3DForm1::Manual39_HSV_Bar_Move()
{
    double r = StrToFloat(lb_c3d_selR->Caption);
    double g = StrToFloat(lb_c3d_selG->Caption);
    double b = StrToFloat(lb_c3d_selB->Caption);

    double h_gain = (double) GetH_val();
    double c = StrToFloat(edt_c3d_satC->Text);
    double s_gain = (double) GetS_val() / 100 / c;
    c = StrToFloat(edt_c3d_valC->Text);
    double v_gain = (double) GetV_val() / 100 / c;
    double h, s, v, in;
    rgb2hsv(r, g, b, &h, &s, &in, &v);
    h += h_gain;
    s *= (1 + s_gain);
    v *= (1 + v_gain);

    hsv2rgb(h, s, v, &r, &g, &b);
    Show_c3d_SimImg(r, g, b);
    ShowImageColor(img_sim, r, g, b);
    //Show_c3d_Img_sim();  //因為不會更改tmp_C3DLUT, 所以直接以上面的方式顯示Simulate Color
}

double TC3DForm1::GetH_val()
{
    double H = sb_c3d_Manual39_h->Position - sb_c3d_Manual39_h->Max / 2;
    return H;
}

void TC3DForm1::SetH_caption(double H)
{
    lb_c3d_Manual39_h->Caption = FloatToStr(H) + "°";
}
void __fastcall TC3DForm1::sb_c3d_Manual39_hChange(TObject * Sender)
{
    double H = GetH_val();
    //if(pc_HuePage_Grid->TabIndex==2 || pc_HuePage_Grid->TabIndex==3)
    //        H = 0;
    SetH_caption(H);

    //HSV Diffusion page
    Manual39_HSV_Bar_Move();	//改變SimImg顯示的色彩, 並不改變table值

    if (Cell_move == true)
	//避免在selectcell時, 發生manual39的hue label當中的值優先寫到grid裡, 而不是點選的Cell值
	ColorSet();
}

//---------------------------------------------------------------------------

int TC3DForm1::GetS_val()
{
    int S = sb_c3d_Manual39_s->Position - sb_c3d_Manual39_s->Max / 2;
    return S;
}

void TC3DForm1::SetS_Caption()
{
    double c = StrToFloat(edt_c3d_satC->Text);
    double s_gain = (double) GetS_val() / 100 / c;
    double S = StrToFloat(lb_c3d_selS->Caption);
    S = double (floor(S * s_gain * 1000)) / 1000;
    lb_c3d_Manual39_s->Caption = FloatToStr(S);
}

void __fastcall TC3DForm1::sb_c3d_Manual39_sChange(TObject * Sender)
{
    SetS_Caption();

    Manual39_HSV_Bar_Move();	//改變SimImg顯示的色彩, 並不改變table值
    if (Cell_move == true)
	//避免在selectcell時, 發生manual39的hue label當中的值優先寫到grid裡, 而不是點選的Cell值
	ColorSet();

    /*if(rg_c3d_hsv_mode->ItemIndex==1)
       c3d_6axisAdj_s(false);
       else if(rg_c3d_hsv_mode->ItemIndex==0)
       c3d_hsvBase_adj(false);
       else if(rg_c3d_hsv_mode->ItemIndex==2)
       c3d_MixAdj_s(false);       */
}

//---------------------------------------------------------------------------


int TC3DForm1::GetV_val()
{
    int V = sb_c3d_Manual39_v->Position - sb_c3d_Manual39_v->Max / 2;
    return V;
}

void TC3DForm1::SetV_Caption()
{
    double c = StrToFloat(edt_c3d_valC->Text);
    double v_gain = (double) GetV_val() / 100 / c;
    double V = StrToFloat(lb_c3d_selV->Caption);
    lb_c3d_Manual39_v->Caption = FloatToStr(V * v_gain);
}

void __fastcall TC3DForm1::sb_c3d_Manual39_vChange(TObject * Sender)
{
    SetV_Caption();

    Manual39_HSV_Bar_Move();	//改變SimImg顯示的色彩, 並不改變table值

    if (Cell_move == true)
	//避免在selectcell時, 發生manual39的hue label當中的值優先寫到grid裡, 而不是點選的Cell值
	ColorSet();

    /*if(rg_c3d_hsv_mode->ItemIndex==1)
       c3d_6axisAdj_v(false);
       else if(rg_c3d_hsv_mode->ItemIndex==0)
       c3d_hsvBase_adj(false);
       else if(rg_c3d_hsv_mode->ItemIndex==2)
       c3d_MixAdj_v(false);      */
}

//---------------------------------------------------------------------------
/*****************************************************
//      Method 3                                    //
*****************************************************/
//----------------------------------------------------------------------------

struct Color_Val {
    double d_r, d_g, d_b;	//移動後的r,g,b差值
    double h, s, v;		//原始的移動軸的hsv值
};

void TC3DForm1::c3d_MixAdj_r(int type, double dif_p, double dif_n, double gain)
{
    double h, s, v, in;
    double tmp_r, tmp_g, tmp_b;
    Color_Val *color_val;
    color_val = new Color_Val[32770];
    int idx = 0;
    if (type == 1) {
	for (int i = 0; i < 256; i++) {
	    for (int j = 0; j < i; j++) {
		//for(int  k = 0; k < i; k++){
		//rgb2hsv(i,j,k,&h, &s, &in, &v);
		rgb2h(i, j, j, &h);
		if (h == 0) {
		    rgb2hsv(i, j, j, &h, &s, &in, &v);
		    color_val[idx].h = h;
		    color_val[idx].s = s;
		    color_val[idx].v = v;
		    h += gain;
		    h = fmod(h + 360, 360);
		    hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
		    color_val[idx].d_r = tmp_r - i;
		    color_val[idx].d_g = tmp_g - j;
		    color_val[idx].d_b = tmp_b - j;
		    idx++;
		}
		//}
	    }
	}
    } else if (type == 2) {
	for (int i = 0; i < 256; i++) {
	    for (int j = 0; j < i; j++) {
		//for(int  k = 0; k < 256; k++){
		rgb2h(i, j, j, &h);
		h = floor(h * 100 + 0.5) / 100;	//4捨5入2位小數
		s = floor(s * 1000 + 0.5) / 1000;	//4捨5入3位小數
		if (h == 0) {
		    color_val[idx].h = h;
		    color_val[idx].s = s;
		    color_val[idx].v = v;
		    s += s * gain;
		    hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
		    color_val[idx].d_r = tmp_r - i;
		    color_val[idx].d_g = tmp_g - j;
		    color_val[idx].d_b = tmp_b - j;
		    idx++;
		}
		//}
	    }
	}
    } else if (type == 3) {
	for (int i = 0; i < 256; i++) {
	    for (int j = 0; j < i; j++) {
		//for(int  k = 0; k < 256; k++){
		rgb2hsv(i, j, j, &h, &s, &in, &v);
		h = floor(h * 100 + 0.5) / 100;
		s = floor(s * 1000 + 0.5) / 1000;
		if (h == 0) {
		    color_val[idx].h = h;
		    color_val[idx].s = s;
		    color_val[idx].v = v;
		    v += s * v * gain;
		    hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
		    color_val[idx].d_r = tmp_r - i;
		    color_val[idx].d_g = tmp_g - j;
		    color_val[idx].d_b = tmp_b - j;
		    idx++;
		}
		//}
	    }
	}
    }

    double r, g, b;
    double ratio;
    for (int i = 0; i < 9; i++) {
	for (int j = 0; j < 9; j++) {
	    for (int k = 0; k < 9; k++) {
		if (i == j && j == k)
		    break;
		rgb2hsv(i * 32, j * 32, k * 32, &h, &s, &in, &v);
		if (h < dif_p || h > 360 + dif_n) {
		    ratio = (h < 180 ? 1 - h / dif_p : 1 - (360 - h) / dif_n * (-1));
		    //ratio = (h<180?h/dif_p:(h-360)/dif_n);
		    if (h == 0)
			ratio = 1;
		    r = 0;
		    g = 0;
		    b = 0;
		    int t = 0;
		    for (int c = 0; c < idx; c++) {
			if (v == 256)
			    v--;
			if (color_val[c].v < v + 1 && color_val[c].v > v - 1 &&
			    (color_val[c].s < s + 0.01 && color_val[c].s >= s - 0.01
			     && color_val[c].s != 0)) {
			    r += color_val[c].d_r;
			    g += color_val[c].d_g;
			    b += color_val[c].d_b;
			    t++;
			}
		    }
		    tmp_c3d_lutR[i][j][k] += ratio * r / t;
		    tmp_c3d_lutG[i][j][k] += ratio * g / t;
		    tmp_c3d_lutB[i][j][k] += ratio * b / t;
		    fix_val(&tmp_c3d_lutR[i][j][k], 256 - 1.0 / Ratio);
		    fix_val(&tmp_c3d_lutG[i][j][k], 256 - 1.0 / Ratio);
		    fix_val(&tmp_c3d_lutB[i][j][k], 256 - 1.0 / Ratio);
		}
	    }
	}
    }
    delete[]color_val;
}

//---------------------------------------------------------------------------
void TC3DForm1::c3d_MixAdj_v(bool flag)	//can't use
{
    double c = StrToFloat(edt_c3d_valC->Text);
    double v_gain = double (sb_c3d_Manual39_v->Position - 1000) / 1000 / c;
    double dif_n = (double) Get_Point_H_NegDif();
    double dif_p = (double) Get_Point_H_PosDif();

    for (int i = 0; i < 9; i++)
	for (int j = 0; j < 9; j++)
	    for (int k = 0; k < 9; k++) {
		tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
		tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
		tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
	    }
    double h, s, in, v;
    if (cb_c3d_Point_HSV_v_g->Checked == true) {
	for (int i = 0; i < 9; i++)
	    for (int j = 0; j < 9; j++)
		for (int k = 0; k < 9; k++) {
		    rgb2hsv(tmp_c3d_lutR[i][j][k], tmp_c3d_lutG[i][j][k], tmp_c3d_lutB[i][j][k], &h,
			    &s, &in, &v);
		    v += v * v_gain * s;
		    v = (v < 0 ? 0 : v);
		    v = (v >= 256 ? 256 - 1.0 / Ratio : v);
		    hsv2rgb(h, s, v, &tmp_c3d_lutR[i][j][k], &tmp_c3d_lutG[i][j][k],
			    &tmp_c3d_lutB[i][j][k]);
		}
    } else {
	if (rb_c3d_r->Checked == true) {
	    c3d_MixAdj_r(3, dif_p, dif_n, v_gain);
	}
    }

    if (flag == true) {
	for (int i = 0; i < 9; i++)
	    for (int j = 0; j < 9; j++)
		for (int k = 0; k < 9; k++) {
		    c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
		    c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
		    c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
		}
    }
    int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
    int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
    int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);
    Show_c3d_CorImg(tmp_c3d_lutR[idx_r][idx_g][idx_b], tmp_c3d_lutG[idx_r][idx_g][idx_b],
		    tmp_c3d_lutB[idx_r][idx_g][idx_b]);

    double r = StrToFloat(lb_c3d_selR->Caption);
    double g = StrToFloat(lb_c3d_selG->Caption);
    double b = StrToFloat(lb_c3d_selB->Caption);
    double sim_r, sim_g, sim_b;
    C3Dsim_t(r, g, b, &sim_r, &sim_g, &sim_b);
    Show_c3d_SimImg(sim_r, sim_g, sim_b);
    Show_c3d_Img_sim();
}

//----------------------------------------------------------------------------
void TC3DForm1::c3d_MixAdj_s(bool flag)	//can't use
{
    double s_gain = double (sb_c3d_Manual39_s->Position - 500) / 10;
    double dif_n = (double) Get_Point_H_NegDif();
    double dif_p = (double) Get_Point_H_PosDif();

    double tmp_c3d_lutR[9][9][9], tmp_c3d_lutG[9][9][9], tmp_c3d_lutB[9][9][9];

    for (int i = 0; i < 9; i++)
	for (int j = 0; j < 9; j++)
	    for (int k = 0; k < 9; k++) {
		tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
		tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
		tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
	    }
    double h, s, in, v;
    if (cb_c3d_Point_HSV_s_g->Checked == true) {
	for (int i = 0; i < 9; i++)
	    for (int j = 0; j < 9; j++)
		for (int k = 0; k < 9; k++) {
		    rgb2hsv(tmp_c3d_lutR[i][j][k], tmp_c3d_lutG[i][j][k], tmp_c3d_lutB[i][j][k], &h,
			    &s, &in, &v);
		    s += s_gain * s;
		    s = (s < 0 ? 0 : s);
		    s = (s > 1 ? 1 : s);
		    hsv2rgb(h, s, v, &tmp_c3d_lutR[i][j][k], &tmp_c3d_lutG[i][j][k],
			    &tmp_c3d_lutB[i][j][k]);
		}
    } else {
	if (rb_c3d_r->Checked == true) {
	    c3d_MixAdj_r(2, dif_p, dif_n, s_gain);
	}
    }

    if (flag == true) {
	for (int i = 0; i < 9; i++)
	    for (int j = 0; j < 9; j++)
		for (int k = 0; k < 9; k++) {
		    c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
		    c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
		    c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
		}
    }
    int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
    int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
    int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);
    Show_c3d_CorImg(tmp_c3d_lutR[idx_r][idx_g][idx_b], tmp_c3d_lutG[idx_r][idx_g][idx_b],
		    tmp_c3d_lutB[idx_r][idx_g][idx_b]);

    double r = StrToFloat(lb_c3d_selR->Caption);
    double g = StrToFloat(lb_c3d_selG->Caption);
    double b = StrToFloat(lb_c3d_selB->Caption);
    double sim_r, sim_g, sim_b;
    C3Dsim_t(r, g, b, &sim_r, &sim_g, &sim_b);
    Show_c3d_SimImg(sim_r, sim_g, sim_b);
    Show_c3d_Img_sim();
}

//----------------------------------------------------------------------------
void TC3DForm1::c3d_MixAdj_h(bool flag)
{
    double h_gain = double (sb_c3d_Manual39_h->Position - sb_c3d_Manual39_h->Max / 2) / 10;
    double dif_n = double (sb_c3d_Point_HSV_hdn->Position - sb_c3d_Point_HSV_hdn->Max);
    double dif_p = double (sb_c3d_Point_HSV_hdp->Position);

    for (int i = 0; i < 9; i++)
	for (int j = 0; j < 9; j++)
	    for (int k = 0; k < 9; k++) {
		tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
		tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
		tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
	    }
    double h, s, in, v;
    if (cb_c3d_Point_HSV_h_g->Checked == true) {
	for (int i = 0; i < 9; i++)
	    for (int j = 0; j < 9; j++)
		for (int k = 0; k < 9; k++) {
		    rgb2hsv(tmp_c3d_lutR[i][j][k], tmp_c3d_lutG[i][j][k],
			    tmp_c3d_lutB[i][j][k], &h, &s, &in, &v);
		    h += h_gain;
		    h = fmod(h + 360, 360);
		    hsv2rgb(h, s, v, &tmp_c3d_lutR[i][j][k], &tmp_c3d_lutG[i][j][k],
			    &tmp_c3d_lutB[i][j][k]);
		}
    } else {
	if (rb_c3d_r->Checked == true) {
	    c3d_MixAdj_r(1, dif_p, dif_n, h_gain);
	}
    }

    if (flag == true) {
	for (int i = 0; i < 9; i++)
	    for (int j = 0; j < 9; j++)
		for (int k = 0; k < 9; k++) {
		    c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
		    c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
		    c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
		}
    }
    int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
    int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
    int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);
    Show_c3d_CorImg(tmp_c3d_lutR[idx_r][idx_g][idx_b], tmp_c3d_lutG[idx_r][idx_g][idx_b],
		    tmp_c3d_lutB[idx_r][idx_g][idx_b]);

    double r = StrToFloat(lb_c3d_selR->Caption);
    double g = StrToFloat(lb_c3d_selG->Caption);
    double b = StrToFloat(lb_c3d_selB->Caption);
    double sim_r, sim_g, sim_b;
    C3Dsim(r, g, b, &sim_r, &sim_g, &sim_b);
    Show_c3d_SimImg(sim_r, sim_g, sim_b);
    Show_c3d_Img_sim();
}

//----------------------------------------------------------------------------
void __fastcall TC3DForm1::Img_3DLUTMouseMove(TObject * Sender, TShiftState Shift, int X, int Y)
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

    //Graphics *TempBitmap, *TheBitmap;
    //TempBitmap=new Graphics::TBitmap()Picture ->;
    //TheBitmap=Hue_Img->Picture->Bitmap;
    //TempBitmap->Assign(TheBitmap);
    //delete TempBitmap;
    //  const String s = /* something */;
    //mages[i]->Picture->LoadFromFile(sl);
}

//---------------------------------------------------------------------------




//----------------------------------------------------------------------------
void c3d_find_smallpoint(int tbl_l, int tbl_n, double r, double g, double b, int *idx_r, int *idx_g,
			 int *idx_b)
{
    //找存在的那個block中最小的點
    for (int i = 0; i <= tbl_l - 2; i++) {
	if (r >= tbl_val[tbl_n][i] && r <= tbl_val[tbl_n][i + 1]) {	//找出r值在那一個區間,
	    *idx_r = i;
	    break;
	}
    }
    for (int i = 0; i <= tbl_l - 2; i++) {
	if (g >= tbl_val[tbl_n][i] && g <= tbl_val[tbl_n][i + 1]) {	//找出g值在那一個區間,
	    *idx_g = i;
	    break;
	}
    }
    for (int i = 0; i <= tbl_l - 2; i++) {
	if (b >= tbl_val[tbl_n][i] && b <= tbl_val[tbl_n][i + 1]) {	//找出b值在那一個區間,
	    *idx_b = i;
	    break;
	}
    }
}

void __fastcall TC3DForm1::Img_3DLUTMouseDown(TObject * Sender,
					      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (pc_Adjust->TabIndex == 0 && pc_global_adj->TabIndex == 1)
	return;

    rb_c3d_point->Checked = true;
    c3d_scrollbar_reset();
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

    /*
       if(pc_Adjust->TabIndex==1){
       double h_t, h_s;
       rgb2hsv(idx_r*cube_dis, idx_g*cube_dis, idx_b*cube_dis, &h_t, &s, &i, &v);
       rgb2hsv(sim_r, sim_g, sim_b, &h_s, &s, &i, &v);
       double h_move = h_s-h_t;
       if(h_move > 180)
       h_move = 360 - h_move;
       int int_part;
       if(h_move-floor(h_move) > 0.5)
       h_move = floor(h_move)+1;
       sb_c3d_Point_HSV_h->Position = h_move+sb_c3d_Point_HSV_h->Max/2;
       }             */
}

//---------------------------------------------------------------------------
bool IsC3Dshow = false;
void __fastcall TC3DForm1::FormCreate(TObject * Sender)
{
    // Create the thread objects
    PColorThread1 = new TPColorThread1(true);

    if (IsC3Dshow == false) {
	C3Dini();
	IsC3Dshow = true;
    }
    C3D_Chg = 0;
    OC3D = new C3D_12401;

    en.Addr = OC3D->SetEn();
    cb_en->Visible = en.Addr.FuncEn();
    cb_en->Caption = en.Addr.Name();

    lut = OC3D->SetLUT();
    cb = OC3D->SetChkBx();
    ChkB = new _CHKB *[C3DChkBox_Nbr];
    for (int i = 0; i < C3DChkBox_Nbr; i++)
	ChkB[i] = new _CHKB;

    ChkB[0]->Chkb = cb_demo;
    ChkB[1]->Chkb = CheckBox1;
    for (int i = 0; i < C3DChkBox_Nbr; i++) {
	ChkB[i]->Addr = cb[i];
	ChkB[i]->Chkb->Visible = ChkB[i]->Addr.FuncEn();
	ChkB[i]->Chkb->OnClick = CheckBox_Click;
	ChkB[i]->Chkb->Hint = i;
	ChkB[i]->Chkb->Caption = ChkB[i]->Addr.Name();
    }

    C3D_Chg = 1;

    for (int i = 0; i < 9; i++) {
	sg_table_step->Cells[i][0] = i + 1;
	sg_table_step->Cells[i][1] = tbl_val[0][i];
    }

    sg_12color1->Canvas->Brush->Color = clRed;
    sg_12color1->Cells[0][0] = "Tbl H";
    sg_12color1->Cells[1][0] = "H";
    sg_12color1->Canvas->Brush->Color = clWhite;
    sg_12color1->Cells[2][0] = "S";
    sg_12color1->Cells[3][0] = "V";

    sg_12color2->Cells[0][0] = "Tbl H";
    sg_12color2->Cells[1][0] = "H";
    sg_12color2->Cells[2][0] = "S";
    sg_12color2->Cells[3][0] = "V";

    sg_Dark->Cells[0][0] = "Tbl H";
    sg_Dark->Cells[1][0] = "H";
    sg_Dark->Cells[2][0] = "S";
    sg_Dark->Cells[3][0] = "V";

    sg_Gray->Cells[0][0] = "Gray";
    sg_Gray->Cells[1][0] = "H";
    sg_Gray->Cells[2][0] = "S";
    sg_Gray->Cells[3][0] = "V";
    if (TBL_SIZE == 9)
	Refresh_Manual39_Point();

    // Initial setup for threads, Cursor Point 
    PColorThread1->Resume();

    // reference HSV adjust with image(0) or color(1)
    fl_ref_HSV_img_col = 1;

    //refresh_c3d_color_grid();
    /*
       for(int i = 0; i < sg_12color1->RowCount; i++){
       sg_12color1->Cells[0][i+1]=i*30;
       sg_12color1->Cells[1][i+1]=i*30;
       sg_12color1->Cells[2][i+1]=0.6666;
       sg_12color1->Cells[3][i+1]=192;
       sg_12color2->Cells[0][i+1]=(i)*30;
       sg_12color2->Cells[1][i+1]=(i)*30;
       sg_12color2->Cells[2][i+1]=0.6666;
       sg_12color2->Cells[3][i+1]=96;
       } */
    /*
       Graphics ::TBitmap *TmpBitmap;
       TmpBitmap=new Graphics::TBitmap();
       TmpBitmap->Width = Img_3DLUT->Width;
       TmpBitmap->Height = Img_3DLUT->Height;
       TmpBitmap->Canvas->Brush->Color = (TColor)RGB(192, 192, 192);
       TmpBitmap->Canvas->Rectangle(0,0,TmpBitmap->Width,TmpBitmap->Height);
       Img_3DLUT->Canvas->Draw(0,0,TmpBitmap);
       delete TmpBitmap;
     */
    /*
       sg_12color1->Canvas->Brush->Color = clRed;
       sg_12color1->Canvas->Brush->Style = bsSolid;
       sg_12color1->Canvas->Rectangle(0, 0, 30, 22);
       Canvas->FillRect(Rect);

       TRect TheRect;
       TheRect = Rect(10,10,100,100);
       //sg_12color1->Canvas->TextRect(TheRect, 10, 10, "Hello World");
       sg_12color1->Canvas->Brush->Color = clBlack;
       sg_12color1->Canvas->FrameRect(TheRect);
     */
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::BitBtn_c3d_undoClick(TObject * Sender)
{
    BitBtn_c3d_undo->Enabled = false;
    String Fpath = "tmp_tbl.txt";
    Load_c3d_table(Fpath);

    //refresh_6axis_grid(255,255,255);
    //refresh_c3d_color_grid();
    if (TBL_SIZE == 9)
	Refresh_Manual39_Point();

    double r, g, b;
    r = StrToFloat(lb_c3d_selR->Caption);
    g = StrToFloat(lb_c3d_selG->Caption);
    b = StrToFloat(lb_c3d_selB->Caption);
    double sim_r, sim_g, sim_b;
    C3Dsim(r, g, b, &sim_r, &sim_g, &sim_b);
    Show_c3d_SimImg(sim_r, sim_g, sim_b);
    Show_c3d_Img_sim();
    c3d_scrollbar_reset();
    //BitBtn_c3d_undo->Enabled = true;
}

//--------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_c3d_checkClick(TObject * Sender)
{
    /*
       //AddrC3D.R_LUT[ASIC_num].LutNum()
       if(AddrC3D.R_LUT[ASIC_num].LutNum()!=729){
       ShowMessage("Address Naming wrong!(c3d lookup table number)");
       return;
       }

       int buff_length = ceil(double(729)*3/2);
       unsigned char* data_buff = new unsigned char [buff_length];
       i2c_read_byte_seq(dev_addr, AddrC3D.R_LUT[ASIC_num].Addr(),data_buff, buff_length, 0);

       int tmp_lut[729];
       int tbl_idx = 0;
       for(int i = 0; i < buff_length; i+=3){
       tmp_lut[tbl_idx] = (unsigned int)data_buff[i]+ (unsigned int)data_buff[i+1]%16*256;
       tmp_lut[tbl_idx+1] = (unsigned int)data_buff[i+1]/16;
       if(i+2< buff_length)
       tmp_lut[tbl_idx+1] += (unsigned int)data_buff[i+2]*16;
       tbl_idx += 2;
       }
       SaveDialog1->Execute();
       String Fpath = SaveDialog1->FileName;
       FILE* fptr;
       if((fptr = fopen(Fpath.c_str(),"w"))==NULL)
       return;
       for(int i = 0; i<buff_length; i++)
       fprintf(fptr,"%d:\t%d\n",i,data_buff[i]);
       fclose(fptr);

       int c3d_r[2][729],c3d_g[2][729],c3d_b[2][729];
       c3d_lutArrange(c3d_r, c3d_g, c3d_b);

       int t = 0;
       for(int i = 0; i < 729; i ++){
       if(tmp_lut[i]!=c3d_r[1][i]){
       ShowMessage("c3d r value r["+IntToStr(i)+"] not match!");
       t++;
       if(t>=5)
       break;
       }
       }

       tbl_idx = 0;
       i2c_read_byte_seq(dev_addr, AddrC3D.G_LUT[ASIC_num].Addr(),data_buff, buff_length, 0);
       for(int i = buff_length; i < buff_length*2; i+=3){
       tmp_lut[tbl_idx] = (unsigned int)data_buff[i]+ (unsigned int)data_buff[i+1]%16*256;
       tmp_lut[tbl_idx+1] = (unsigned int)data_buff[i+1]/16;
       if(i+2< buff_length)
       tmp_lut[tbl_idx+1] += (unsigned int)data_buff[i+2]*16;
       tbl_idx += 2;
       }
       t = 0;
       for(int i = 0; i < 729; i ++){
       if(tmp_lut[i]!=c3d_g[1][i]){
       ShowMessage("c3d g value g["+IntToStr(i)+"] not match!");
       t++;
       if(t>=5)
       break;
       }
       }

       tbl_idx = 0;
       i2c_read_byte_seq(dev_addr, AddrC3D.B_LUT[ASIC_num].Addr(),data_buff, buff_length, 0);
       SaveDialog1->Execute();
       Fpath = SaveDialog1->FileName;
       if((fptr = fopen(Fpath.c_str(),"w"))==NULL)
       return;
       for(int i = 0; i<buff_length; i++)
       fprintf(fptr,"%d:\t%d\n",i,data_buff[i]);
       fclose(fptr);
       for(int i = buff_length*2; i < buff_length*3; i+=3){
       tmp_lut[tbl_idx] = (unsigned int)data_buff[i]+ (unsigned int)data_buff[i+1]%16*256;
       tmp_lut[tbl_idx+1] = (unsigned int)data_buff[i+1]/16;
       if(i+2< buff_length)
       tmp_lut[tbl_idx+1] += (unsigned int)data_buff[i+2]*16;
       tbl_idx += 2;
       }
       SaveDialog1->Execute();
       Fpath = SaveDialog1->FileName;
       if((fptr = fopen(Fpath.c_str(),"w"))==NULL)
       return;
       for(int i = 0; i<buff_length; i++)
       fprintf(fptr,"%d:\t%d\n",i,data_buff[i]);
       fclose(fptr);

       for(int i = 0; i < 729; i ++){
       if(tmp_lut[i]!=c3d_b[1][i]){
       ShowMessage("c3d b value b["+IntToStr(i)+"] not match!");
       t++;
       if(t>=5)
       break;
       }
       }
       delete [] data_buff;
       ShowMessage("3DLUT Tcon value check ok!");        */
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::cb_enClick(TObject * Sender)
{
    if (C3D_Chg == 0)
	return;
    int set_val = (cb_en->Checked ? 1 : 0);
    if (EngineerForm->btn_connect_card->Enabled == false)
	EngineerForm->SetWrite_Byte(en.Addr, set_val);
}

//---------------------------------------------------------------------------
void __fastcall TC3DForm1::CheckBox_Click(TObject * Sender)
{
    if (C3D_Chg == 0)
	return;
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (ChkB[idx]->Chkb->Checked ? 1 : 0);
    EngineerForm->SetWrite_Byte(ChkB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void TC3DForm1::Refresh_Manual39_Point()
{
    //Light 12
    int rgb1[12][3] = { {192, 64, 64}, {192, 128, 64}, {192, 192, 64}, {128, 192, 64},
    {64, 192, 64}, {64, 192, 128}, {64, 192, 192}, {64, 128, 192}, {64, 64, 192},
    {128, 64, 192}, {192, 64, 192}, {192, 64, 128}
    };
    //Dark 12
    int rgb2[12][3] = { {96, 32, 32}, {96, 64, 32}, {96, 96, 32}, {64, 96, 32}, {32, 96, 32},
    {32, 96, 64}, {32, 96, 96}, {32, 64, 96}, {32, 32, 96}, {64, 32, 96}, {96, 32, 96}, {96, 32, 64}
    };
    //Dark
    int rgb3[6][3] = { {32, 0, 0}, {32, 32, 0}, {0, 32, 0}, {0, 32, 32}, {0, 0, 32}, {32, 0, 32} };
    //Gray
    int rgb4[9][3] = { {0, 0, 0}, {32, 32, 32}, {64, 64, 64}, {96, 96, 96}, {128, 128, 128},
    {160, 160, 160}, {192, 192, 192}, {224, 224, 224}, {256, 256, 256}
    };

    double h_st, h, s, in, v, v_st;
    int x, y, z;
    // sg_12 color1 (light 12)
    for (int i = 0; i < 12; i++) {
	rgb2hsv(rgb1[i][0], rgb1[i][1], rgb1[i][2], &h_st, &s, &in, &v);
	x = rgb1[i][0] / cube_dis;
	y = rgb1[i][1] / cube_dis;
	z = rgb1[i][2] / cube_dis;
	rgb2hsv(c3d_lutR[x][y][z], c3d_lutG[x][y][z], c3d_lutB[x][y][z], &h, &s, &in, &v);
	sg_12color1->Cells[1][h_st / 30 + 1] = h;
	sg_12color1->Cells[2][h_st / 30 + 1] = s;
	sg_12color1->Cells[3][h_st / 30 + 1] = v;
    }
    // sg_12 color2 (Dark 12)
    for (int i = 0; i < 12; i++) {
	rgb2hsv(rgb2[i][0], rgb2[i][1], rgb2[i][2], &h_st, &s, &in, &v);
	x = rgb2[i][0] / cube_dis;
	y = rgb2[i][1] / cube_dis;
	z = rgb2[i][2] / cube_dis;
	rgb2hsv(c3d_lutR[x][y][z], c3d_lutG[x][y][z], c3d_lutB[x][y][z], &h, &s, &in, &v);
	sg_12color2->Cells[1][h_st / 30 + 1] = h;
	sg_12color2->Cells[2][h_st / 30 + 1] = s;
	sg_12color2->Cells[3][h_st / 30 + 1] = v;
    }
    // sg_Dark
    for (int i = 0; i < 6; i++) {
	rgb2hsv(rgb3[i][0], rgb3[i][1], rgb3[i][2], &h_st, &s, &in, &v);
	x = rgb3[i][0] / cube_dis;
	y = rgb3[i][1] / cube_dis;
	z = rgb3[i][2] / cube_dis;
	rgb2hsv(c3d_lutR[x][y][z], c3d_lutG[x][y][z], c3d_lutB[x][y][z], &h, &s, &in, &v);
	sg_Dark->Cells[1][h_st / 60 + 1] = h;
	sg_Dark->Cells[2][h_st / 60 + 1] = s;
	sg_Dark->Cells[3][h_st / 60 + 1] = v;
    }
    // sg_Gray
    for (int i = 0; i < 9; i++) {
	rgb2hsv(rgb4[i][0], rgb4[i][1], rgb4[i][2], &h, &s, &in, &v_st);
	x = rgb4[i][0] / cube_dis;
	y = rgb4[i][1] / cube_dis;
	z = rgb4[i][2] / cube_dis;
	rgb2hsv(c3d_lutR[x][y][z], c3d_lutG[x][y][z], c3d_lutB[x][y][z], &h, &s, &in, &v);
	sg_Gray->Cells[1][v_st / 32 + 1] = h;
	sg_Gray->Cells[2][v_st / 32 + 1] = s;
	sg_Gray->Cells[3][v_st / 32 + 1] = v;
    }
}


void TC3DForm1::Load_c3d_table(String Fpath)
{
    char *buffer = Load_File(Fpath);

    int tbl_tl = pow(TBL_SIZE, 3);

    int idx_r, idx_g, idx_b;
    char *str[7];
    int str_l[7];
    str[0] = "C3D_LUT";
    str_l[0] = 7;
    str[1] = "Rin";
    str_l[1] = 4;
    str[2] = "Gin";
    str_l[2] = 4;
    str[3] = "Bin";
    str_l[3] = 4;
    str[4] = "Rout";
    str_l[4] = 4;
    str[5] = "Gout";
    str_l[5] = 4;
    str[6] = "Bout";
    str_l[6] = 4;

    char *pch = strtok(buffer, "\n\t");
    for (int i = 0; i < 7; i++) {
	while (memcmp(pch, str[i], str_l[i]) != 0) {
	    if (pch == NULL) {
		ShowMessage("Can't open c3d table file.");
		return;
	    }
	    pch = strtok(NULL, "\n\t");
	}
    }
    int c = 0;
    int tbl7[9] = { 0, 1, 2, -1, 3, -1, 4, 5, 6 };
    //AnsiString str1 = "4011";
    pch = strtok(NULL, "\n\t ");
    while (c < tbl_tl * 6 && pch != NULL) {

	// if(memcmp(pch,str1,4)!=0)
	//        int a = 0;
	if (pch == NULL) {
	    ShowMessage("Can't open c3d table file.");
	    return;		//資料中的data缺少
	}

	if (c % 6 == 0) {
	    idx_r = (int) ceil((double) StrToInt((AnsiString) pch) / cube_dis);
	    if (TBL_SIZE == 7) {
		idx_r = tbl7[idx_r];
		if (idx_r == -1) {
		    ShowMessage("Rin value has 96 or 160.");
		    return;
		}
	    }
	} else if (c % 6 == 1) {
	    idx_g = (int) ceil((double) StrToInt((AnsiString) pch) / cube_dis);
	    if (TBL_SIZE == 7) {
		idx_g = tbl7[idx_g];
		if (idx_g == -1) {
		    ShowMessage("Gin value has 96 or 160.");
		    return;
		}
	    }
	} else if (c % 6 == 2) {
	    idx_b = (int) ceil((double) StrToInt((AnsiString) pch) / cube_dis);
	    if (TBL_SIZE == 7) {
		idx_b = tbl7[idx_b];
		if (idx_b == -1) {
		    ShowMessage("Bin value has 96 or 160.");
		    return;
		}
	    }
	} else if (c % 6 == 3) {
	    c3d_lutR[idx_r][idx_g][idx_b] = (double) StrToInt((AnsiString) pch) / Ratio;
	} else if (c % 6 == 4) {
	    c3d_lutG[idx_r][idx_g][idx_b] = (double) StrToInt((AnsiString) pch) / Ratio;
	} else if (c % 6 == 5) {
	    c3d_lutB[idx_r][idx_g][idx_b] = (double) StrToInt((AnsiString) pch) / Ratio;
	}
	pch = strtok(NULL, "\n\t ");
	c++;
    }
    delete[]buffer;
}

/*  Load RGB&HSIV
        char* buffer = Load_File(Fpath);
        int tbl_tl = pow(TBL_SIZE,3);
        int idx_r, idx_g, idx_b;
        char* str[11];          int str_l[11];
        str[0]="C3D_LUT";       str_l[0]=7;
        str[1]="Rin";           str_l[1]=4;
        str[2]="Gin";           str_l[2]=4;
        str[3]="Bin";           str_l[3]=4;
        str[4]="Rout";          str_l[4]=4;
        str[5]="Gout";          str_l[5]=4;
        str[6]="Bout";          str_l[6]=4;
        str[7]="H";             str_l[7]=1;
        str[8]="S";             str_l[8]=1;
        str[9]="V";             str_l[9]=1;
        str[10]="I";            str_l[10]=1;

        char* pch = strtok (buffer,"\n\t");
        for(int i = 0; i < 11; i++){
                while (memcmp(pch,str[i],str_l[i])!=0){
                        if(pch == NULL){
                                ShowMessage("Can't open c3d table file.");
                                return;
                        }
                        pch = strtok (NULL,"\n\t");
                }
        }
        int c = 0;
        pch = strtok (NULL,"\n\t");
        while (c < tbl_tl*10 && pch!=NULL){
                if(pch == NULL){
                        ShowMessage("Can't open c3d table file.");
                        return;        //資料中的data缺少
                }
                if(c%10 == 0)
                        idx_r = (int)ceil((double)StrToInt((AnsiString)pch)/32);
                else if(c%10 == 1)
                        idx_g = (int)ceil((double)StrToInt((AnsiString)pch)/32);
                else if(c%10 == 2)
                        idx_b = (int)ceil((double)StrToInt((AnsiString)pch)/32);
                else if(c%10 == 3){
                        c3d_lutR[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch)/Ratio;
                }else if(c%10 == 4){
                        c3d_lutG[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch)/Ratio;
                }else if(c%10 == 5){
                        c3d_lutB[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch)/Ratio;
                }else if(c%10 == 6)
                        c3d_lutH[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch);
                else if(c%10 == 7)
                        c3d_lutS[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch);
                else if(c%10 == 8)
                        c3d_lutV[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch)/Ratio;
                else if(c%10 == 9)
                        c3d_lutI[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch)/Ratio;

                pch = strtok (NULL,"\n\t");
                c++;
       }
       delete [] buffer;  */
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_tbl_searchClick(TObject * Sender)
{
    SaveDialog1->Title = "Enter File Name of the cross & plane";
    if (!SaveDialog1->Execute())
	return;
    String Fpath = SaveDialog1->FileName;
    FILE *fptr;
    if ((fptr = fopen(Fpath.c_str(), "w")) == NULL)
	return;
    double r_new, g_new, b_new;

    //對角線
    fprintf(fptr, "cross1\n");
    for (int i = 0; i < 32; i++) {
	C3Dsim((double) (192 + i), (double) (64 - i), (double) 0, &r_new, &g_new, &b_new);
	fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", (int) (192 + i), (int) (64 - i), 0, r_new,
		g_new, b_new);
    }

    fprintf(fptr, "cross2\n");
    for (int i = 0; i < 16; i++) {
	C3Dsim((double) (192 + i), (double) (48 - i), (double) 0, &r_new, &g_new, &b_new);
	fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", (int) (192 + i), (int) (48 - i), 0, r_new,
		g_new, b_new);
    }
    fprintf(fptr, "cross3\n");
    for (int i = 0; i < 16; i++) {
	C3Dsim((double) (208 + i), (double) (64 - i), (double) 0, &r_new, &g_new, &b_new);
	fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", (int) (208 + i), (int) (64 - i), 0, r_new,
		g_new, b_new);
    }

    fprintf(fptr, "cross4\n");
    for (int i = 0; i < 8; i++) {
	C3Dsim((double) (200 - i), (double) (32 + i), (double) 0, &r_new, &g_new, &b_new);
	fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", (int) (200 - i), (int) (32 + i), 0, r_new,
		g_new, b_new);
    }

    fprintf(fptr, "cross5\n");
    for (int i = 0; i < 24; i++) {
	C3Dsim((double) (216 - i), (double) (32 + i), (double) 0, &r_new, &g_new, &b_new);
	fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", (int) (216 - i), (int) (32 + i), 0, r_new,
		g_new, b_new);
    }
    fprintf(fptr, "cross6\n");
    for (int i = 0; i < 24; i++) {
	C3Dsim((double) (224 - i), (double) (40 + i), (double) 0, &r_new, &g_new, &b_new);
	fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", (int) (224 - i), (int) (40 + i), 0, r_new,
		g_new, b_new);
    }
    fprintf(fptr, "cross7\n");
    for (int i = 0; i < 8; i++) {
	C3Dsim((double) (224 - i), (double) (56 + i), (double) 0, &r_new, &g_new, &b_new);
	fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", (int) (224 - i), (int) (56 + i), 0, r_new,
		g_new, b_new);
    }

    /*
       fprintf(fptr,"cross2\n");
       for(int i = 0; i <= 32; i++){
       C3Dsim((double)255.0, (double)(64+i),(double)(160-i), &r_new, &g_new, &b_new);
       fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n",255, (int)(64+i),(int)(160-i),r_new,g_new,b_new);
       }
     */
    // 4 disc cube plane
    fprintf(fptr, "plane_incube\n");
    int b = 0;
    for (int r = 192; r <= 224; r++)
	for (int g = 32; g <= 64; g++) {
	    //for(int b = 32; b <= 64; b++){
	    C3Dsim((double) r, (double) g, (double) b, &r_new, &g_new, &b_new);
	    fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", r, g, b, r_new, g_new, b_new);
	}
    fclose(fptr);
    /*
       SaveDialog1->Title = "Enter File Name of the 2nd Plane";
       if(!SaveDialog1->Execute())
       return;
       Fpath = SaveDialog1->FileName;
       if((fptr = fopen(Fpath.c_str(),"w"))==NULL)
       return ;
       fprintf(fptr,"plane_incube\n");
       g=255;
       for(int r = 192; r <= 255; r++)
       //for(int g = 96; g <= 224; g++)
       for(int b = 32; b <= 64; b++){
       C3Dsim((double)r,(double)g, (double)b, &r_new, &g_new, &b_new);
       fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", r,g,b,r_new,g_new,b_new);
       }

       SaveDialog1->Title = "Enter File Name of the 3rd Plane";

       if(!SaveDialog1->Execute())
       return;
       Fpath = SaveDialog1->FileName;
       if((fptr = fopen(Fpath.c_str(),"w"))==NULL)
       return ;
       fprintf(fptr,"plane_incube\n");
       g=255;
       for(int r = 192; r <= 255; r++)
       //for(int g = 96; g <= 224; g++)
       for(int b = 96; b <= 128; b++){
       C3Dsim((double)r,(double)g, (double)b, &r_new, &g_new, &b_new);
       fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", r,g,b,r_new,g_new,b_new);
       } */
    //fclose(fptr);
    /*
       fprintf(fptr,"acme*4cube");

       int table [24][3]={{128,224,64},{128,224,96},{128,255,64},{128,255,96},
       {160,224,64},{160,224,96},{160,255,64},{160,255,96},
       {160,224,64},{160,224,96},{160,255,64},{160,255,96},{192,224,64},{192,224,96},
       {192,255,64},{192,255,96},
       {160,224,32},{160,224,64},{160,255,32},{160,255,64},{192,224,32},{192,224,64},
       {192,255,32},{192,255,64}};

       for(int i=0; i < 24;i++){
       C3Dsim((double)table[i][0], (double)table[i][1], (double)table[i][2]+32, &r_new, &g_new, &b_new);
       fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", table[i][0], table[i][1], table[i][2]+32,r_new,g_new,b_new);
       if((i+1)%8==0)
       fprintf(fptr,"\n");
       }
     */
    /*
       //輸入8個頂點, 找出轉換後的table值
       OpenDialog1->Title = "Choose acme point file";
       if(!OpenDialog1->Execute())
       return;
       Fpath = OpenDialog1->FileName;
       //Fpath = OpenDialog1->FileName;
       char* buffer = Load_File(Fpath);

       //write file
       SaveDialog1->Title = "Enter acme point result file name";
       if(!SaveDialog1->Execute())
       return;
       Fpath = SaveDialog1->FileName;

       FILE* fptr1;
       if((fptr1 = fopen(Fpath.c_str(),"w"))==NULL)
       return ;

       int tbl_R,tbl_G,tbl_B;
       double tbl_H;
       int idxR,idxG,idxB;
       char* pch = strtok (buffer,"\n\t");
       tbl_R = StrToInt((AnsiString)pch);
       pch = strtok (NULL,"\n\t");
       tbl_G = StrToInt((AnsiString)pch);
       pch = strtok (NULL,"\n\t");
       tbl_B = StrToInt((AnsiString)pch);
       rgb2h((double)tbl_R,(double)tbl_G,(double)tbl_B,&tbl_H);
       idxR=tbl_R/cube_dis;
       idxG=tbl_G/cube_dis;
       idxB=tbl_B/cube_dis;
       fprintf(fptr1, "%d\t%d\t%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",(int)tbl_R,(int)tbl_G,(int)tbl_B,tbl_H,c3d_lutR[idxR][idxG][idxB],
       c3d_lutG[idxR][idxG][idxB],c3d_lutB[idxR][idxG][idxB],c3d_lutH[idxR][idxG][idxB]);

       int idx=1;
       while(idx<128){
       for(int i = 0; i < 3; i++){
       if(pch == NULL){
       ShowMessage("Table items missing.");
       return;
       }
       pch = strtok (NULL,"\n\t");
       if(i==0)
       tbl_R = StrToInt((AnsiString)pch);
       else if(i==1)
       tbl_G = StrToInt((AnsiString)pch);
       else if(i==2)
       tbl_B = StrToInt((AnsiString)pch);
       }
       rgb2h(tbl_R,tbl_G,tbl_B,&tbl_H);
       idxR=tbl_R/cube_dis;
       idxG=tbl_G/cube_dis;
       idxB=tbl_B/cube_dis;
       fprintf(fptr1, "%d\t%d\t%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",(int)tbl_R,(int)tbl_G,(int)tbl_B,tbl_H,c3d_lutR[idxR][idxG][idxB],
       c3d_lutG[idxR][idxG][idxB],c3d_lutB[idxR][idxG][idxB],c3d_lutH[idxR][idxG][idxB]);
       idx++;
       //if(idx%8==0)
       //        fprintf(fptr1,"\n");
       }
       fclose(fptr1); */
}

//---------------------------------------------------------------------------
void TC3DForm1::Direct_sim(double r, double g, double b, double *r_new, double *g_new,
			   double *b_new)
{
    //h_adj --- start
    double h, s, i, v;
    rgb2hsv(r, g, b, &h, &s, &i, &v);
    if (s == 0) {		//固定灰階
	*r_new = r;
	*g_new = g;
	*b_new = b;
	return;
    }
    double h_gain = (double) GetPointH_val();
    double trans_h = StrToFloat(lb_c3d_selH->Caption);
    if (cb_c3d_Point_HSV_h_g->Checked == true) {
	h = fmod((h + h_gain) + 360, 360);
	hsv2rgb(h, s, v, &r, &g, &b);
	*r_new = r;
	*g_new = g;
	*b_new = b;
    } else {
	if (h_gain == 0) {
	    *r_new = r;
	    *g_new = g;
	    *b_new = b;
	    return;
	} else {
	    double dif_n = (double) Get_Point_H_NegDif();
	    double dif_p = (double) Get_Point_H_PosDif();
	    double low = trans_h + dif_n;	//負向的diffusion邊界
	    double high = trans_h + dif_p;	//正向的diffusion邊界
	    double new_pos_rng = dif_p - h_gain;	//原本做正向diffusion的範圍所要對應到的新範圍
	    double new_neg_rng = dif_n * (-1) + h_gain;	//原本做負向diffusion的範圍所要對應到的新範圍
	    bool Is_dif = false;	//flag recording tmp_h to do diffusion or not
	    double ratio, rslt;

	    if (low < 0 && h > low + 360) {
		h -= 360;
		Is_dif = true;
	    } else if (high >= 360 && h < fmod(high, 360)) {
		h += 360;
		Is_dif = true;
	    } else if (h >= low && h < high) {
		Is_dif = true;
	    }
	    if (Is_dif == true) {
		if (h < trans_h) {
		    ratio = (h - low) / dif_n * (-1);
		    rslt = ratio * new_neg_rng + low;
		} else if (h >= trans_h) {
		    ratio = (h - high) / dif_p;
		    rslt = ratio * new_pos_rng + high;
		}
		h = fmod(rslt + 360, 360);
	    }
	    hsv2rgb(h, s, v, &r, &g, &b);
	    *r_new = r;
	    *g_new = g;
	    *b_new = b;
	}
    }

    //S adj
    double c = StrToFloat(edt_c3d_satC->Text);
    double s_gain = (double) GetPointS_val() / 100 / c;
    if (cb_c3d_Point_HSV_s_g->Checked == true) {
	double tmp;
	for (int i = 0; i < TBL_SIZE; i++)
	    for (int j = 0; j < TBL_SIZE; j++)
		for (int k = 0; k < TBL_SIZE; k++) {
		    if (h != 0 || s != 0) {	//固定灰階
			tmp = s * (s_gain + 1);
			tmp = (tmp < 0 ? 0 : tmp);
			tmp = (tmp > 1 ? 1 : tmp);
			s = tmp;
		    }
		}
	return;
    }

    double dif_n = (double) Get_Point_H_NegDif();
    double dif_p = (double) Get_Point_H_PosDif();

    double low = h + dif_n;	//負向的diffusion邊界
    double high = h + dif_p;	//正向的diffusion邊界
    bool Is_dif = false;	//flag recording tmp_h to do diffusion or not
    double ratio;
    Is_dif = false;

    if (low < 0 && h > low + 360) {
	h -= 360;
	Is_dif = true;
    } else if (high >= 360 && h < fmod(high, 360)) {
	h += 360;
	Is_dif = true;
    } else if (h > low && h < high) {
	Is_dif = true;
    }
    if (Is_dif == true) {
	if (h < trans_h) {
	    ratio = 1 - (trans_h - h) / dif_n * (-1);
	} else if (h >= trans_h) {
	    ratio = 1 - (h - trans_h) / dif_p;
	}
	if (ratio > 1)
	    ShowMessage("S ratio >1");
	s = (ratio * s_gain / c + 1) * s;
	if (s > 1)
	    s = 1;
	else if (s < 0)
	    s = 0;

    }
}

void __fastcall TC3DForm1::btn_directly_simClick(TObject * Sender)
{
    btn_directly_sim->Enabled = false;
    // TC3D_SimualteForm *C3D_SimualteForm;
    //C3D_SimualteForm = new TC3D_SimualteForm(this);

    int x = Img_3DLUT->Picture->Width;
    int y = Img_3DLUT->Picture->Height;

    int color;
    Graphics::TBitmap * TmpBitmap;
    TmpBitmap = new Graphics::TBitmap();
    TmpBitmap->Width = x;
    TmpBitmap->Height = y;

    //double Y[15][11] ;
    for (int i = 0; i < x; i++)
	for (int j = 0; j < y; j++) {
	    color = Img_3DLUT->Canvas->Pixels[i][j];
	    if (color == -1)
		color = 0;

	    double r, g, b, r_new, g_new, b_new;
	    b = color / 65536;
	    g = color / 256 % 256;
	    r = color % 256;
	    Direct_sim(r, g, b, &r_new, &g_new, &b_new);
	    /* if(r>=123 && r<=137 && g==255 && b>=27 && b<=37){
	       Y[(int)r-123][(int)b-27] = 0.299 * r_new + 0.587 * g_new + 0.114 * b_new;
	       }

	       if((r==123 || r==137) && g==255 && (b==27 || b==37)){
	       r_new = 0;
	       g_new = 0;
	       b_new = 0;
	       } */
	    //Img_3DLUT->Canvas->Pixels[i][j] = (TColor)RGB(r_new,g_new,b_new);
	    C3D_SimualteForm->Image1->Canvas->Pixels[i][j] = (TColor) RGB(r_new, g_new, b_new);
	    //C3D_SimualteForm->Image2->Canvas->Pixels[i][j] = (TColor)RGB(((r-r_new)>0?(r-r_new)+20:0),0,0);
	    //C3D_SimualteForm->Image3->Canvas->Pixels[i][j] = (TColor)RGB(0,((g-g_new)>0?(g-g_new)+20:0),0);
	    //C3D_SimualteForm->Image4->Canvas->Pixels[i][j] = (TColor)RGB(0,0,((b_new-b)>0?(b_new-b)+20:0));
	}
    C3D_SimualteForm->Image1->Picture->SaveToFile("sim_tmp.bmp");
    Img_3DLUT->Picture->LoadFromFile("sim_tmp.bmp");

    delete TmpBitmap;
    /*
       if(!SaveDialog1->Execute()){
       return;
       }

       String Fpath = SaveDialog1->FileName;
       if(Fpath==NULL)
       return;

       FILE* fptr = fopen (Fpath.c_str(),"w");
       for(int i = 0; i < 15; i++)
       fprintf(fptr,"%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
       Y[i][0],Y[i][1],Y[i][2],Y[i][3],Y[i][4],Y[i][5],Y[i][6],Y[i][7],Y[i][8],Y[i][9],Y[i][10]);
       fclose(fptr); */
    c3d_scrollbar_reset();
    btn_directly_sim->Enabled = true;
    C3D_SimualteForm->Show();

}

//---------------------------------------------------------------------------





void __fastcall TC3DForm1::sg_table_stepKeyDown(TObject * Sender, WORD & Key, TShiftState Shift)
{
    for (int i = 0; i < 9; i++) {
	tbl_val[0][i] = StrToInt(sg_table_step->Cells[i][1]);
    }
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::BitBtn1Click(TObject * Sender)
{
    C3Dini();
}

//---------------------------------------------------------------------------


void __fastcall TC3DForm1::BitBtn2Click(TObject * Sender)
{
    int x = Img_3DLUT->Picture->Width;
    int y = Img_3DLUT->Picture->Height;

    double r, g, b;
    double h = StrToFloat(LabeledEdit1->Text);
    double s = StrToFloat(sg_rgb_input->Cells[1][1]);
    double v = StrToFloat(sg_rgb_input->Cells[2][1]);

    if (s > 1 || v > 255) {
	ShowMessage("S or V range fault.");
	return;
    }
    hsv2rgb(h, s, v, &r, &g, &b);
    for (int i = 0; i < x; i++)
	for (int j = 0; j < y; j++)
	    Img_3DLUT->Canvas->Pixels[i][j] = (TColor) (r + 256 * g + 65536 * b);

    edt_show_h->Visible = false;
}

//---------------------------------------------------------------------------


void __fastcall TC3DForm1::LabeledEdit1SubLabelClick(TObject * Sender)
{
    double h = StrToFloat(LabeledEdit1->Text);
    h += 30;
    LabeledEdit1->Text = FloatToStr(h);
    BitBtn2Click(Sender);
    TMouseButton Button;
    TShiftState Shift;
    Img_3DLUTMouseDown(Sender, Button, Shift, 100, 100);
}

//---------------------------------------------------------------------------

/*
  未曾出現在UI上?
*/
void __fastcall TC3DForm1::btn_sim_by_valClick(TObject * Sender)
{
    // sb_c3d_Point_HSV_hdn->Position = 950;
    // sb_c3d_Point_HSV_hdp->Position = 50;
    int tbl_n;
    if (rg_c3d_TblSize->ItemIndex == 0) {
	tbl_n = 0;
    } else if (rg_c3d_TblSize->ItemIndex == 1) {
	tbl_n = 1;
    } else if (rg_c3d_TblSize->ItemIndex == 2) {
	tbl_n = 2;
    } else if (rg_c3d_TblSize->ItemIndex == 3) {
	tbl_n = 3;
    }

    int idx_r, idx_g, idx_b;
    double r, g, b, h, s = 0.6, v = 0.6 * 255;

    for (int i = 0; i < 72; i++) {
	h = i * 5;
	hsv2rgb(h, s, v, &r, &g, &b);
	c3d_find_point(TBL_SIZE, tbl_n, r, g, b, &idx_r, &idx_g, &idx_b);	//取block裡的最小點
	lb_c3d_tbl_ir->Caption = IntToStr(idx_r);
	lb_c3d_tbl_ig->Caption = IntToStr(idx_g);
	lb_c3d_tbl_ib->Caption = IntToStr(idx_b);
	sb_c3d_Manual39_h->Position = 500 + sim_val[i] * 10;
	c3d_hsvBase_adj(true);
    }
    btn_c3d_simClick(Sender);
}

//---------------------------------------------------------------------------



void __fastcall TC3DForm1::btn_dirSim_by_valClick(TObject * Sender)
{
    btn_c3d_simClick(Sender);
}

//---------------------------------------------------------------------------



double max(double x, double y, double z)
{
    double big = (x > y ? x : y);
    big = (big > z ? big : z);
    return big;
}

double max(double x, double y)
{
    double big = (x > y ? x : y);
    return big;
}
void TC3DForm1::Set_Adj_Color(double r, double g, double b)
{
    int tbl_n;
    if (rg_c3d_TblSize->ItemIndex == 0) {
	tbl_n = 0;
    } else if (rg_c3d_TblSize->ItemIndex == 1) {
	tbl_n = 1;
    } else if (rg_c3d_TblSize->ItemIndex == 2) {
	tbl_n = 2;
    } else if (rg_c3d_TblSize->ItemIndex == 3) {
	tbl_n = 3;
    }

    int idx_r, idx_g, idx_b;
    //c3d_find_smallpoint(tbl_l,tbl_n,r,g,b,&idx_r,&idx_g,&idx_b); //取block裡的最小點
    c3d_find_point(TBL_SIZE, tbl_n, r, g, b, &idx_r, &idx_g, &idx_b);	//取最近點

    lb_c3d_tbl_ir->Caption = idx_r;
    lb_c3d_tbl_ig->Caption = idx_g;
    lb_c3d_tbl_ib->Caption = idx_b;
    lb_c3d_tbl_ir->Caption = idx_r;
    lb_c3d_tbl_ig->Caption = idx_g;
    lb_c3d_tbl_ib->Caption = idx_b;

//----------------table r, g, b, h, s, i, v 即Matrix rgb---------------------------

    double tbl_r, tbl_g, tbl_b, tbl_h, tbl_s, tbl_i, tbl_v;

    tbl_r = c3d_lutR[idx_r][idx_g][idx_b];
    tbl_g = c3d_lutG[idx_r][idx_g][idx_b];
    tbl_b = c3d_lutB[idx_r][idx_g][idx_b];

    Show_c3d_TblImg(tbl_r, tbl_g, tbl_b);
    Show_c3d_CorImg(tbl_r, tbl_g, tbl_b);
}

void __fastcall TC3DForm1::btn_key_in_RGBClick(TObject * Sender)
{
    int x = img_color->Width;
    int y = img_color->Height;

    double r = StrToFloat(sg_rgb_input->Cells[0][1]);
    double g = StrToFloat(sg_rgb_input->Cells[1][1]);
    double b = StrToFloat(sg_rgb_input->Cells[2][1]);
    double r_new, g_new, b_new;
    if (rg_PointNum->ItemIndex == 0) {	//1 color
	ShowImageColor(img_color, r, g, b);
	Set_Adj_Color(r, g, b);
	Show_c3d_SelImg(r, g, b);
	C3Dsim_t(r, g, b, &r_new, &g_new, &b_new);
	Show_c3d_SimImg(r_new, g_new, b_new);
	Show_c3d_Img_sim();
    } else if (rg_PointNum->ItemIndex == 1) {	//4 color
	if ((fmod(r, 32) == 0 || r == 255) && (fmod(g, 32) == 0 || g == 255)
	    && (fmod(b, 32) == 0 || b == 255)) {
	    Set_Adj_Color(r, g, b);
	    C3Dsim_t(r, g, b, &r_new, &g_new, &b_new);
	    Show_c3d_SimImg(r_new, g_new, b_new);
	    Show_c3d_Img_sim();
	    return;
	}

	int r_t = floor(r / cube_dis) * cube_dis, g_t = floor(g / cube_dis) * cube_dis, b_t =
	    floor(b / cube_dis) * cube_dis;
	int r_t1 = (r_t + cube_dis > 255 ? 255 : r_t + cube_dis);
	int g_t1 = (g_t + cube_dis > 255 ? 255 : g_t + cube_dis);
	int b_t1 = (b_t + cube_dis > 255 ? 255 : b_t + cube_dis);

	Graphics::TBitmap * TmpBitmap;
	TmpBitmap = new Graphics::TBitmap();
	TmpBitmap->Width = img_color->Width / 2;
	TmpBitmap->Height = img_color->Height / 2;

	//small
	TmpBitmap->Canvas->Brush->Color = (TColor) RGB(r_t, g_t, b_t);
	TmpBitmap->Canvas->Rectangle(0, 0, TmpBitmap->Width, TmpBitmap->Height);
	img_color->Canvas->Draw(0, 0, TmpBitmap);

	//rgb
	TmpBitmap->Canvas->Brush->Color = (TColor) RGB(r_t1, g_t1, b_t1);
	TmpBitmap->Canvas->Rectangle(0, 0, TmpBitmap->Width, TmpBitmap->Height);
	img_color->Canvas->Draw(x / 2, y / 2, TmpBitmap);

	double d_x = fmod(r, cube_dis);
	double d_y = fmod(g, cube_dis);
	double d_z = fmod(b, cube_dis);

	double d_max = max(d_x, d_y, d_z);
	double d_mid;

	double r_u = r_t;
	double g_u = g_t;
	double b_u = b_t;
	if (d_max == d_x) {
	    r_u = r_t1;
	    d_mid = max(d_y, d_z);
	    d_x = 300;
	} else if (d_max == d_y) {
	    g_u = g_t1;
	    d_mid = max(d_x, d_z);
	    d_y = 300;
	} else if (d_max == d_z) {
	    b_u = b_t1;
	    d_mid = max(d_x, d_y);
	    d_z = 300;
	}

	TmpBitmap->Canvas->Brush->Color = (TColor) RGB(r_u, g_u, b_u);
	TmpBitmap->Canvas->Rectangle(0, 0, TmpBitmap->Width, TmpBitmap->Height);
	img_color->Canvas->Draw(x / 2, 0, TmpBitmap);

	if (d_mid == d_x)
	    r_u = r_t1;
	else if (d_mid == d_y)
	    g_u = g_t1;
	else if (d_mid == d_z)
	    b_u = b_t1;

	TmpBitmap->Canvas->Brush->Color = (TColor) RGB(r_u, g_u, b_u);
	TmpBitmap->Canvas->Rectangle(0, 0, TmpBitmap->Width, TmpBitmap->Height);
	img_color->Canvas->Draw(0, y / 2, TmpBitmap);
	delete TmpBitmap;
	Set_Adj_Color(r_t, g_t, b_t);

	double sim_r, sim_g, sim_b, sim_h, sim_s, sim_i, sim_v;
	C3Dsim_t(r, g, b, &sim_r, &sim_g, &sim_b);
	Show_c3d_SimImg(sim_r, sim_g, sim_b);
	Show_c3d_Img_sim();
	C3Dsim_t(r, g, b, &r_new, &g_new, &b_new);
	Show_c3d_SimImg(r_new, g_new, b_new);
	Show_c3d_Img_sim();
    } else
	return;

    pc_img->TabIndex = 1;
    ts_color->Show();

    if (pc_img->TabIndex == 0)
	Form_in_target->img_in_target->Picture->Bitmap->Assign(Img_3DLUT->Picture->Bitmap);
    else
	Form_in_target->img_in_target->Picture->Bitmap->Assign(img_color->Picture->Bitmap);
}

//---------------------------------------------------------------------------


void __fastcall TC3DForm1::btn_key_in_HSVClick(TObject * Sender)
{
    double h = StrToFloat(sg_rgb_input->Cells[0][1]);
    double s = StrToFloat(sg_rgb_input->Cells[1][1]);
    double v = StrToFloat(sg_rgb_input->Cells[2][1]);

    double r, g, b;
    hsv2rgb(h, s, v, &r, &g, &b);
    int x = Img_3DLUT->Width;
    int y = Img_3DLUT->Height;

    int r_t = floor(r / cube_dis) * cube_dis, g_t = floor(g / cube_dis) * cube_dis, b_t =
	floor(b / cube_dis) * cube_dis;
    int r_t1 = (r_t + cube_dis > 255 ? 255 : r_t + cube_dis);
    int g_t1 = (g_t + cube_dis > 255 ? 255 : g_t + cube_dis);
    int b_t1 = (b_t + cube_dis > 255 ? 255 : b_t + cube_dis);

    Graphics::TBitmap * TmpBitmap;
    TmpBitmap = new Graphics::TBitmap();
    TmpBitmap->Width = Img_3DLUT->Width / 4;
    TmpBitmap->Height = Img_3DLUT->Height / 2;

    //small
    TmpBitmap->Canvas->Brush->Color = (TColor) RGB(r_t, g_t, b_t);
    TmpBitmap->Canvas->Rectangle(0, 0, TmpBitmap->Width, TmpBitmap->Height);
    Img_3DLUT->Canvas->Draw(0, 0, TmpBitmap);

    //rgb
    TmpBitmap->Canvas->Brush->Color = (TColor) RGB(r_t1, g_t1, b_t1);
    TmpBitmap->Canvas->Rectangle(0, 0, TmpBitmap->Width, TmpBitmap->Height);
    Img_3DLUT->Canvas->Draw(x / 4 * 3, y / 2, TmpBitmap);
    double d_x = fmod(r, cube_dis);
    double d_y = fmod(g, cube_dis);
    double d_z = fmod(b, cube_dis);

    double d_max = max(d_x, d_y, d_z);
    double d_mid;

    double r_u = r_t;
    double g_u = g_t;
    double b_u = b_t;
    if (d_max == d_x) {
	r_u = r_t1;
	d_mid = max(d_y, d_z);
    } else if (d_max == d_y) {
	g_u = g_t1;
	d_mid = max(d_x, d_z);
    } else if (d_max == d_z) {
	b_u = b_t1;
	d_mid = max(d_x, d_y);
    }

    TmpBitmap->Canvas->Brush->Color = (TColor) RGB(r_u, g_u, b_u);
    TmpBitmap->Canvas->Rectangle(0, 0, TmpBitmap->Width, TmpBitmap->Height);
    Img_3DLUT->Canvas->Draw(x / 2, 0, TmpBitmap);

    if (d_mid == d_x)
	r_u = r_t1;
    else if (d_mid == d_y)
	g_u = g_t1;
    else if (d_mid == d_z)
	b_u = b_t1;

    TmpBitmap->Canvas->Brush->Color = (TColor) RGB(r_u, g_u, b_u);
    TmpBitmap->Canvas->Rectangle(0, 0, TmpBitmap->Width, TmpBitmap->Height);
    Img_3DLUT->Canvas->Draw(0, y / 2, TmpBitmap);

    /*
       //r
       TmpBitmap->Canvas->Brush->Color = (TColor)RGB(r_t1, g_t, b_t);
       TmpBitmap->Canvas->Rectangle(0,0,TmpBitmap->Width,TmpBitmap->Height);
       Img_3DLUT->Canvas->Draw(x/4,0,TmpBitmap);
       //g
       TmpBitmap->Canvas->Brush->Color = (TColor)RGB(r_t, g_t1, b_t);
       TmpBitmap->Canvas->Rectangle(0,0,TmpBitmap->Width,TmpBitmap->Height);
       Img_3DLUT->Canvas->Draw(x/4*2,0,TmpBitmap);
       //b
       TmpBitmap->Canvas->Brush->Color = (TColor)RGB(r_t, g_t, b_t1);
       TmpBitmap->Canvas->Rectangle(0,0,TmpBitmap->Width,TmpBitmap->Height);
       Img_3DLUT->Canvas->Draw(x/4*3,0,TmpBitmap);
       //y
       TmpBitmap->Canvas->Brush->Color = (TColor)RGB(r_t1, g_t1, b_t);
       TmpBitmap->Canvas->Rectangle(0,0,TmpBitmap->Width,TmpBitmap->Height);
       Img_3DLUT->Canvas->Draw(0,y/2,TmpBitmap);
       //c
       TmpBitmap->Canvas->Brush->Color = (TColor)RGB(r_t, g_t1, b_t1);
       TmpBitmap->Canvas->Rectangle(0,0,TmpBitmap->Width,TmpBitmap->Height);
       Img_3DLUT->Canvas->Draw(x/4,y/2,TmpBitmap);
       //m
       TmpBitmap->Canvas->Brush->Color = (TColor)RGB(r_t1, g_t, b_t1);
       TmpBitmap->Canvas->Rectangle(0,0,TmpBitmap->Width,TmpBitmap->Height);
       Img_3DLUT->Canvas->Draw(x/4*2,y/2,TmpBitmap);
     */

    delete TmpBitmap;
    //C3D_SimualteForm = new TC3D_SimualteForm(this);
    C3D_SimualteForm->Image1->Canvas->Draw(0, 0, Img_3DLUT->Picture->Bitmap);
    C3D_SimualteForm->Label4->Caption = "Figure";
    C3D_SimualteForm->Label4->Visible = true;
    C3D_SimualteForm->Show();
}

//---------------------------------------------------------------------------


void __fastcall TC3DForm1::FormClose(TObject * Sender, TCloseAction & Action)
{
    PColorThread1->Terminate();

}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::sg_12color1MouseDown(TObject * Sender,
						TMouseButton Button, TShiftState Shift, int X,
						int Y)
{
/*        int Column, Row;//the coordinates of StirngGrid
        sg_12color1->MouseToCell(X, Y, Column, Row);//to get the corrdinates of MouseDown
        if(Row == 0)
                return;

        int rgb[12][3]={{192,64,64},{192,128,64},{192,192,64},{128,192,64},
        {64,192,64},{64,192,128},{64, 192, 192},{64,128,192},{64, 64, 192},
        {128,64,192},{192, 64, 192},{192,64,128}};

        double r = rgb[Row-1][0];
        double g = rgb[Row-1][1];
        double b = rgb[Row-1][2];

        ShowSelectCell(Row, r, g, b, sg_12color1);*/
}

//---------------------------------------------------------------------------
void TC3DForm1::Refresh_PointColor_rgb(double r, double g, double b)
{
    sg_rgb_input->Cells[0][1] = FloatToStr(r);
    sg_rgb_input->Cells[1][1] = FloatToStr(g);
    sg_rgb_input->Cells[2][1] = FloatToStr(b);
}

//---------------------------------------------------------------------------
// 點選HuePage的顏色, 顯示在介面上(Select RGB 與 Simulate RGB 與 Colors頁面上的影像)
void TC3DForm1::ShowSelectCell(int ARow, double r, double g, double b, TStringGrid * sg)
{
    Show_c3d_SelImg(r, g, b);
    ShowImageColor(img_color, r, g, b);
    // 更新到點調整(RGB)的介面上
    Refresh_PointColor_rgb(r, g, b);

    // 以調整後的H,S,V值, 作為Simulate後的值 (直接從介面的grid上取出)
    double adj_r, adj_g, adj_b;
    double h_use = StrToFloat(sg->Cells[1][ARow]);
    double s_use = StrToFloat(sg->Cells[2][ARow]);
    double v_use = StrToFloat(sg->Cells[3][ARow]);
    hsv2rgb(h_use, s_use, v_use, &adj_r, &adj_g, &adj_b);

    Show_c3d_SimImg(adj_r, adj_g, adj_b);
    Show_c3d_Img_sim();
    ts_color->Show();
    pc_img->TabIndex = 1;
    Form_in_target->img_in_target->Picture->Bitmap->Assign(img_color->Picture->Bitmap);

    double h, s, v, in;
    rgb2hsv(r, g, b, &h, &s, &in, &v);
    double h_gain = h_use - h;
    double c = StrToFloat(edt_c3d_satC->Text);
    double s_gain = ((s_use / s) - 1) * 100 * c;
    c = StrToFloat(edt_c3d_valC->Text);
    double v_gain = ((v_use / v) - 1) * 100 * c;

    sb_c3d_Manual39_h->Position = sb_c3d_Manual39_h->Max / 2 + (int) floor(h_gain + 0.5);
    sb_c3d_Manual39_s->Position = sb_c3d_Manual39_s->Max / 2 + (int) floor(s_gain + 0.5);
    sb_c3d_Manual39_v->Position = sb_c3d_Manual39_v->Max / 2 + (int) floor(v_gain + 0.5);

    /*
       double H = sb_c3d_Manual39_h->Position-sb_c3d_Manual39_h->Max/2;
       int S = sb_c3d_Manual39_s->Position-sb_c3d_Manual39_s->Max/2;
       int V = sb_c3d_Manual39_v->Position-sb_c3d_Manual39_v->Max/2;

       double h_gain = (double)GetH_val();
       double c = StrToFloat(edt_c3d_satC->Text);
       double s_gain = (double)GetS_val()/100/c;
       c = StrToFloat(edt_c3d_valC->Text);
       double v_gain = (double)GetV_val()/100/c;

       h += h_gain;
       s *= (1+s_gain);
       v *= (1+v_gain);   */
}

void __fastcall TC3DForm1::sg_GraySelectCell(TObject * Sender, int ACol, int ARow, bool & CanSelect)
{
    Cell_move = false;
    if (ARow == 0)
	return;

    int rgb[9][3] = { {0, 0, 0}, {32, 32, 32}, {64, 64, 64}, {96, 96, 96}, {128, 128, 128},
    {160, 160, 160}, {192, 192, 192}, {224, 224, 224}, {255, 255, 255}
    };
    double r = rgb[ARow - 1][0];
    double g = rgb[ARow - 1][1];
    double b = rgb[ARow - 1][2];
    ShowSelectCell(ARow, r, g, b, sg_Gray);
    Cell_move = true;
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::sg_DarkSelectCell(TObject * Sender, int ACol, int ARow, bool & CanSelect)
{
    Cell_move = false;
    if (ARow == 0)
	return;

    int rgb[6][3] = { {32, 0, 0}, {32, 32, 0}, {0, 32, 0}, {0, 32, 32}, {0, 0, 32}, {32, 0, 32} };
    double r = rgb[ARow - 1][0];
    double g = rgb[ARow - 1][1];
    double b = rgb[ARow - 1][2];

    ShowSelectCell(ARow, r, g, b, sg_Dark);
    Cell_move = true;
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::sg_12color2MouseDown(TObject * Sender,
						TMouseButton Button, TShiftState Shift, int X,
						int Y)
{
    Cell_move = false;
    int Column, Row;		//the coordinates of StirngGrid
    sg_12color2->MouseToCell(X, Y, Column, Row);	//to get the corrdinates of MouseDown
    if (Row == 0)
	return;

    int rgb[12][3] = { {96, 32, 32}, {96, 64, 32}, {96, 96, 32}, {64, 96, 32}, {32, 96, 32},
    {32, 96, 64}, {32, 96, 96}, {32, 64, 96}, {32, 32, 96}, {64, 32, 96}, {96, 32, 96}, {96, 32, 64}
    };

    double r = rgb[Row - 1][0];
    double g = rgb[Row - 1][1];
    double b = rgb[Row - 1][2];

    ShowSelectCell(Row, r, g, b, sg_12color2);
    Cell_move = true;
}

//---------------------------------------------------------------------------

void TC3DForm1::Save_c3d_table(String Fpath)
{
    FILE *fptr = fopen(Fpath.c_str(), "w");

    c3d_lutArrange();
    fprintf(fptr, "C3D_LUT\nRin\tGin\tBin\tRout\tGout\tBout\n");
    int tbl_tl = pow(TBL_SIZE, 3);
    double h, s, in, v;
    for (int i = 0; i < tbl_tl; i++) {
	fprintf(fptr, "%d\t%d\t%d\t%d\t%d\t%d\n", c3d_r[0][i], c3d_g[0][i],
		c3d_b[0][i], c3d_r[1][i], c3d_g[1][i], c3d_b[1][i]);
    }
    /*
       fprintf(fptr,"C3D_LUT\nRin\tGin\tBin\tRout\tGout\tBout\tH\tS\tV\n");
       int tbl_tl = pow(TBL_SIZE,3);
       double h,s, in, v;
       for(int i = 0; i < tbl_tl; i++){
       fprintf(fptr,"%d\t%d\t%d\t%d\t%d\t%d\t",c3d_r[0][i],c3d_g[0][i],
       c3d_b[0][i],c3d_r[1][i],c3d_g[1][i],c3d_b[1][i]);
       rgb2hsv(c3d_r[1][i]/16,c3d_g[1][i]/16,c3d_b[1][i]/16,&h,&s,&in,&v);
       fprintf(fptr,"%2f\t%2f\t%2f\n",h,s,v);
       }
     */
    fclose(fptr);
}

bool Save_c3dXlsFile(String Fpath)
{
    using namespace cms::colorformat;
    using namespace std;
    using namespace cms::util;

    const string & filename = (string &) Fpath;
    ExcelFileDB db(filename, Create);

    string_vector_ptr fieldsNames = StringVector::fromCString(7, "LutNum", "Rin", "Gin", "Bin",
							      "Rout", "Gout", "Bout");

    db.createTable("9x9x9", fieldsNames);
    for (int i = 0; i < total_len; i++) {
	db.insert(fieldsNames,
		  StringVector::fromCString(7, IntToStr(i + 1), IntToStr(c3d_r[0][i]),
					    IntToStr(c3d_g[0][i]), IntToStr(c3d_b[0][i]),
					    IntToStr(c3d_r[1][i]), IntToStr(c3d_g[1][i]),
					    IntToStr(c3d_b[1][i])));
    }
    db.createTable("7x7x7", fieldsNames);
    int idx = 1;
    for (int i = 0; i < 9 * 9 * 9; i++) {
	if (c3d_r[0][i] != 96 && c3d_r[0][i] != 160 && c3d_g[0][i] != 96 && c3d_g[0][i] != 160
	    && c3d_b[0][i] != 96 && c3d_b[0][i] != 160) {
	    db.insert(fieldsNames,
		      StringVector::fromCString(7, IntToStr(idx), IntToStr(c3d_r[0][i]),
						IntToStr(c3d_g[0][i]), IntToStr(c3d_b[0][i]),
						IntToStr(c3d_r[1][i]), IntToStr(c3d_g[1][i]),
						IntToStr(c3d_b[1][i])));
	    idx++;
	}
    }

    return 1;
}

void __fastcall TC3DForm1::btn_c3d_save_rgbClick(TObject * Sender)
{
    if (!SaveDialog1->Execute()) {
	return;
    }

    String Fpath = SaveDialog1->FileName /*+".txt" */ ;
    if (Fpath == NULL)
	return;

    btn_c3d_save_rgb->Enabled = false;
    if (SaveDialog1->FilterIndex == 1) {	//xls
	c3d_lutArrange();
	Save_c3dXlsFile(Fpath);
    } else if (SaveDialog1->FilterIndex == 2)	//txt
	Save_c3d_table(Fpath);

    if (pc_Adjust->TabIndex == 1 && pc_point_color_adj->TabIndex == 0) {
	//Point Color - RGB Diffusion
	sb_c3d_rgb_dis->Position = 0;
	Reset_c3d_Point_RGB_Scroll();
    } else if (pc_Adjust->TabIndex == 1 && pc_point_color_adj->TabIndex == 1)
	//Point Color - HSV Diffusion
	Reset_c3d_Point_HSV_Scroll();

    btn_c3d_save_rgb->Enabled = true;
}

//---------------------------------------------------------------------------
// Draw "Light 12" Color , H=n+30, S=0.6666, V=192
void __fastcall TC3DForm1::sg_12color1DrawCell(TObject * Sender, int ACol,
					       int ARow, TRect & Rect, TGridDrawState State)
{
    int rgb[12][3] = { {192, 64, 64}, {192, 128, 64}, {192, 192, 64}, {128, 192, 64},
    {64, 192, 64}, {64, 192, 128}, {64, 192, 192}, {64, 128, 192}, {64, 64, 192},
    {128, 64, 192}, {192, 64, 192}, {192, 64, 128}
    };
    for (int row = 1; row <= 12; row++) {
	sg_12color1->Canvas->Brush->Color = (TColor) rgb[row - 1][2] * 65536 +
	    rgb[row - 1][1] * 256 + rgb[row - 1][0];
	sg_12color1->Canvas->Rectangle(0, 19 * row, 34, 19 * (row + 1));
	sg_12color1->Canvas->Font->Color = clBlack;
	sg_12color1->Canvas->TextOut(0 + 4, 19 * row + 4, (row - 1) * 30);
    }
}

//---------------------------------------------------------------------------

// Draw "Dark 12" Color , H=n+30, S=0.6666, V=96
void __fastcall TC3DForm1::sg_12color2DrawCell(TObject * Sender, int ACol,
					       int ARow, TRect & Rect, TGridDrawState State)
{
    int rgb[12][3] = { {96, 32, 32}, {96, 64, 32}, {96, 96, 32}, {64, 96, 32}, {32, 96, 32},
    {32, 96, 64}, {32, 96, 96}, {32, 64, 96}, {32, 32, 96}, {64, 32, 96}, {96, 32, 96}, {96, 32, 64}
    };
    for (int row = 1; row <= 12; row++) {
	sg_12color2->Canvas->Brush->Color = (TColor) rgb[row - 1][2] * 65536 +
	    rgb[row - 1][1] * 256 + rgb[row - 1][0];
	sg_12color2->Canvas->Rectangle(0, 19 * row, 34, 19 * (row + 1));
	sg_12color2->Canvas->Font->Color = clBlack;
	sg_12color2->Canvas->TextOut(0 + 4, 19 * row + 4, (row - 1) * 30);
    }
}

//---------------------------------------------------------------------------

//Draw "Dark" color , value = 32
void __fastcall TC3DForm1::sg_DarkDrawCell(TObject * Sender, int ACol,
					   int ARow, TRect & Rect, TGridDrawState State)
{
    int rgb[6][3] = { {32, 0, 0}, {32, 32, 0}, {0, 32, 0}, {0, 32, 32}, {0, 0, 32}, {32, 0, 32} };
    for (int row = 1; row <= 6; row++) {
	sg_Dark->Canvas->Brush->Color = (TColor) rgb[row - 1][2] * 65536 +
	    rgb[row - 1][1] * 256 + rgb[row - 1][0];
	sg_Dark->Canvas->Rectangle(0, 19 * row, 34, 19 * (row + 1));
	sg_Dark->Canvas->Font->Color = clWhite;
	sg_Dark->Canvas->TextOut(0 + 4, 19 * row + 4, (row - 1) * 60);
    }
}

//---------------------------------------------------------------------------
// Draw "Gray" Color , 9 Gray Level (0,32,64,96,128,160,192,224,255)
void __fastcall TC3DForm1::sg_GrayDrawCell(TObject * Sender, int ACol,
					   int ARow, TRect & Rect, TGridDrawState State)
{
    int rgb[9][3] = { {0, 0, 0}, {32, 32, 32}, {64, 64, 64}, {96, 96, 96}, {128, 128, 128},
    {160, 160, 160}, {192, 192, 192}, {224, 224, 224}, {255, 255, 255}
    };
    for (int row = 1; row <= 9; row++) {
	sg_Gray->Canvas->Brush->Color = (TColor) rgb[row - 1][2] * 65536 +
	    rgb[row - 1][1] * 256 + rgb[row - 1][0];
	sg_Gray->Canvas->Rectangle(0, 19 * row, 34, 19 * (row + 1));
	if (row <= 5)
	    sg_Gray->Canvas->Font->Color = clWhite;
	else
	    sg_Gray->Canvas->Font->Color = clBlack;
	int text = (row - 1) * 32;
	if (row == 9)
	    text = 255;
	sg_Gray->Canvas->TextOut(0 + 4, 19 * row + 4, text);
    }
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::img_colorMouseDown(TObject * Sender,
					      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    rb_c3d_point->Checked = true;
    c3d_scrollbar_reset();

    int color;
    double h, s, i, v, r, g, b;
    X_site = X;
    Y_site = Y;
    color = img_color->Canvas->Pixels[X][Y];
    if (color == -1)
	color = 0;
    b = color / 65536;
    g = color / 256 % 256;
    r = color % 256;
    //ShowImageColor(img_color,r,g,b);
    Show_c3d_SelImg(r, g, b);
    Set_Adj_Color(r, g, b);
    sg_rgb_input->Cells[0][1] = FloatToStr(r);
    sg_rgb_input->Cells[1][1] = FloatToStr(g);
    sg_rgb_input->Cells[2][1] = FloatToStr(b);

    if (pc_Adjust->TabIndex == 1) {
	if (Button == mbRight) {
	    c3d_Sim_Image_HSV_Step->Enabled = true;
	    TPoint pt = C3DForm1->ClientToScreen(Point(X, Y));
	    PopupMenu_HSV_ref_img->Popup(pt.x, pt.y);
	}
	double sim_r, sim_g, sim_b, sim_h, sim_s, sim_i, sim_v;
	C3Dsim_t(r, g, b, &sim_r, &sim_g, &sim_b);
	Show_c3d_SimImg(sim_r, sim_g, sim_b);
	Show_c3d_Img_sim();
	refresh_6axis_grid(sim_r, sim_g, sim_b);
    } else if (pc_Adjust->TabIndex == 0 && pc_global_adj->TabIndex == 1) {
	if (Button == mbRight) {
	    c3d_Sim_Image_HSV_Step->Enabled = false;
	    TPoint pt = C3DForm1->ClientToScreen(Point(X, Y));
	    PopupMenu_HSV_ref_img->Popup(pt.x, pt.y);
	}
	Manual39_HSV_Bar_Move();
    }
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::img_colorMouseMove(TObject * Sender, TShiftState Shift, int X, int Y)
{
    int color;
    double h, s, v, i, r, g, b;
    if (pc_img->TabIndex == 1)
	color = img_color->Canvas->Pixels[X][Y];
    else if (pc_img->TabIndex == 2)
	color = img_sim->Canvas->Pixels[X][Y];

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
void swap(double *sw1, double *sw2, int idx)
{
    double *tmp = new double[idx];
    for (int i = 0; i < idx; i++) {
	tmp[i] = sw1[i];
	sw1[i] = sw2[i];
	sw2[i] = tmp[i];
    }
    delete[]tmp;
}

//---------------------------------------------------------------------------
void Sort_Color_64(void)
{
    double Sort[3][20][3];
    double Sort_pack[3] = { 0 };
    double h, s, in, v;

    int idx = 0;
    for (int i = 0; i < Color_move_Nbr; i++) {
	rgb2hsv(Color_move[i][0], Color_move[i][1], Color_move[i][2], &h, &s, &in, &v);
	if (v == 0) {
	    idx = Sort_pack[0];
	    Sort[0][idx][0] = Color_move[i][0];
	    Sort[0][idx][1] = Color_move[i][1];
	    Sort[0][idx][2] = Color_move[i][2];
	    Sort_pack[0]++;
	} else if (v == 32) {
	    idx = Sort_pack[1];
	    Sort[1][idx][0] = Color_move[i][0];
	    Sort[1][idx][1] = Color_move[i][1];
	    Sort[1][idx][2] = Color_move[i][2];
	    Sort_pack[1]++;
	} else if (v == 64) {
	    idx = Sort_pack[2];
	    Sort[2][idx][0] = Color_move[i][0];
	    Sort[2][idx][1] = Color_move[i][1];
	    Sort[2][idx][2] = Color_move[i][2];
	    Sort_pack[2]++;
	}
    }
    double h1, h2;
    int color_m_idx = 0;
    for (int c = 0; c < 3; c++)
	Color_move[color_m_idx][c] = Sort[0][0][c];
    color_m_idx++;
    for (int i = 1; i < 3; i++) {
	for (int t1 = Sort_pack[i]; t1 > 0; t1--) {
	    for (int t2 = 0; t2 < t1 - 1; t2++) {
		rgb2hsv(Sort[i][t2][0], Sort[i][t2][1], Sort[i][t2][2], &h1, &s, &in, &v);
		rgb2hsv(Sort[i][t2 + 1][0], Sort[i][t2 + 1][1], Sort[i][t2 + 1][2], &h2, &s, &in,
			&v);
		if (h1 > h2)
		    swap(Sort[i][t2], Sort[i][t2 + 1], 3);
	    }
	}
	for (int j = 0; j < Sort_pack[i]; j++) {
	    for (int c = 0; c < 3; c++) {
		Color_move[color_m_idx][c] = Sort[i][j][c];
	    }
	    color_m_idx++;
	}
    }
}

//-------------------------------------------------------------------------
int img_idx = 0;
void __fastcall TC3DForm1::rg_PointNumClick(TObject * Sender)
{
    if (rg_PointNum->ItemIndex == 1) {
	btn_key_in_RGBClick(Sender);
	rg_PointNum->ItemIndex = 0;
    }
/*        if(rg_PointNum->ItemIndex == 2){
                double in_l, in_h, hue_l, hue_h;
                if(img_idx<=0){
                        in_l=0; in_h=64;
                        hue_l=0;
                        hue_h=360;   //***
                }else if(img_idx>=1 && img_idx<=12){  //sat 切
                        in_l=64; in_h = 160;
                        hue_l=(345+(img_idx-1)*30)%360;
                        hue_h=(15+(img_idx-1)*30)%360;    //***
                }else if(img_idx>=13 && img_idx<=17 ){//hue在切
                        in_l=160; in_h = 224;
                        hue_l=(330+(img_idx-13)*60)%360;
                        hue_h=(30+(img_idx-13)*60)%360;     //**
                }else if(img_idx>=18 && img_idx<=23 ){
                        in_l=224; in_h = 255;
                        hue_l=(330+(img_idx-18)*60)%360;
                        hue_h=(30+(img_idx-18)*60)%360;     //**
                }else
                        return;

                double h,s,v,in;
                int idx = 0;
                if( hue_l<hue_h){
                for(int i = 0; i < TBL_SIZE; i++){
                        for(int j = 0; j < TBL_SIZE; j++){
                                for(int k = 0; k < TBL_SIZE; k++){
                                        rgb2hsv(c3d_lutR[i][j][k],c3d_lutG[i][j][k],c3d_lutB[i][j][k],&h,&s,&in,&v);    //不適合用c3d_lutR的值
                                        if(v<=in_h && v>=in_l && h>=hue_l && h<=hue_h){
                                                Color_move[idx][0] = c3d_lutR[i][j][k];
                                                Color_move[idx][1] = c3d_lutG[i][j][k];
                                                Color_move[idx][2] = c3d_lutB[i][j][k];
                                                idx++;
                                        }
                                }
                        }
                }
                }else{
                for(int i = 0; i < TBL_SIZE; i++){
                        for(int j = 0; j < TBL_SIZE; j++){
                                for(int k = 0; k < TBL_SIZE; k++){
                                        rgb2hsv(c3d_lutR[i][j][k],c3d_lutG[i][j][k],c3d_lutB[i][j][k],&h,&s,&in,&v);   //不適合用c3d_lutR的值
                                        if(v<=in_h && v>in_l && (h>hue_l || h<=hue_h)){
                                                Color_move[idx][0] = c3d_lutR[i][j][k];
                                                Color_move[idx][1] = c3d_lutG[i][j][k];
                                                Color_move[idx][2] = c3d_lutB[i][j][k];
                                                idx++;
                                        }
                                }
                        }
                }
                }

                Color_move_Nbr = idx;
                Sort_Color_64();

                // ShowColor
                Graphics ::TBitmap *TmpBitmap;
                TmpBitmap=new Graphics::TBitmap();
                TmpBitmap->Width = 433;
                TmpBitmap->Height = 301;
                TmpBitmap->Canvas->Brush->Color = (TColor)RGB(0,0,0);
                TmpBitmap->Canvas->Rectangle(0,0,TmpBitmap->Width,TmpBitmap->Height);

                img_color->Canvas->Draw(0,0,TmpBitmap);

                for(int i = 0; i < 7; i++){
                        for(int j = 0; j < 5; j++){
                                if(i*5+j >= Color_move_Nbr)
                                        break;
                                TmpBitmap->Canvas->Brush->Color = (TColor)RGB(Color_move[i*5+j][0], Color_move[i*5+j][1],Color_move[i*5+j][2]);
                                TmpBitmap->Canvas->Rectangle(0,0,60,60);
                                img_color->Canvas->Draw(i*60,j*60,TmpBitmap);
                        }
                }
                img_color->Canvas->Font->Color = clBlack;
                img_color->Canvas->Font->Size = 8;
                AnsiString str = "value:"+FloatToStr(in_l)+"~"+FloatToStr(in_h)+
                "  hue:"+FloatToStr(hue_l)+"~"+FloatToStr(hue_h);
                img_color->Canvas->TextOut( 0, 0,str);
               delete TmpBitmap;

               int color = (int)img_color->Canvas->Pixels[5][5];
               double b = color/65536;
               double g = color/256%256;
               double r = color%256;
               Show_c3d_SelImg(r, g, b);
               double sim_r, sim_g, sim_b;
               C3Dsim_t(r, g, b, &sim_r, &sim_g, &sim_b);
               Show_c3d_SimImg(sim_r, sim_g, sim_b);
               Show_c3d_Img_sim();
               refresh_6axis_grid_t(sim_r,sim_g,sim_b);
        }    */
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_img_nextClick(TObject * Sender)
{
    img_idx++;
    rg_PointNumClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_img_prevClick(TObject * Sender)
{
    img_idx--;
    rg_PointNumClick(Sender);
}

//---------------------------------------------------------------------------
void TC3DForm1::Set_HuePageStringGrid(TStringGrid * sg)
{
    int sel_idx = 0;
    sel_idx = sg->Row;
    if (sel_idx == 0)
	return;

    sg->Cells[1][sel_idx] = lb_c3d_simH->Caption;
    sg->Cells[2][sel_idx] = lb_c3d_simS->Caption;
    sg->Cells[3][sel_idx] = lb_c3d_simV->Caption;
}

//---------------------------------------------------------------------------
// "Color Set" button in hue page clicks
// According to the Hue of Select color, Set H,S,V Adjusting value to
// "Light 12" or "Dark 12" StringGrid
void TC3DForm1::ColorSet()
{
    if (pc_HuePage_Grid->TabIndex == 0) {
	Set_HuePageStringGrid(sg_12color1);
    } else if (pc_HuePage_Grid->TabIndex == 1) {
	Set_HuePageStringGrid(sg_12color2);
    } else if (pc_HuePage_Grid->TabIndex == 2) {
	Set_HuePageStringGrid(sg_Dark);
    } else if (pc_HuePage_Grid->TabIndex == 3) {
	Set_HuePageStringGrid(sg_Gray);
    }
}

//---------------------------------------------------------------------------
//
void __fastcall TC3DForm1::btn_darkClick(TObject * Sender)
{
    double in_l, in_h, hue_l, hue_h;
    //in_l=0; in_h=64;
    //hue_l=0;
    //hue_h=360;   //***
    double h, s, v, in;
    int idx = 0;
    int u_r, u_g, u_b;
    for (int i = 0; i < TBL_SIZE; i++) {
	for (int j = 0; j < TBL_SIZE; j++) {
	    for (int k = 0; k < TBL_SIZE; k++) {
		if (i <= 2 && j <= 2 && k <= 2) {
		    Color_move[idx][0] = i * 32;
		    Color_move[idx][1] = j * 32;
		    Color_move[idx][2] = k * 32;
		    idx++;
		}
	    }
	}
    }
    Color_move_Nbr = idx;
    Sort_Color_64();

    // ShowColor
    Graphics::TBitmap * TmpBitmap;
    TmpBitmap = new Graphics::TBitmap();
    TmpBitmap->Width = 433;
    TmpBitmap->Height = 301;
    TmpBitmap->Canvas->Brush->Color = (TColor) RGB(0, 0, 0);
    TmpBitmap->Canvas->Rectangle(0, 0, TmpBitmap->Width, TmpBitmap->Height);

    img_color->Canvas->Draw(0, 0, TmpBitmap);

    for (int i = 0; i < 7; i++) {
	for (int j = 0; j < 5; j++) {
	    if (i * 5 + j >= Color_move_Nbr)
		break;
	    TmpBitmap->Canvas->Brush->Color =
		(TColor) RGB(Color_move[i * 5 + j][0], Color_move[i * 5 + j][1],
			     Color_move[i * 5 + j][2]);
	    TmpBitmap->Canvas->Rectangle(0, 0, 60, 60);
	    img_color->Canvas->Draw(i * 60, j * 60, TmpBitmap);
	}
    }
    delete TmpBitmap;

    double r = Color_move[Color_move_Nbr - 1][0];
    double g = Color_move[Color_move_Nbr - 1][1];
    double b = Color_move[Color_move_Nbr - 1][2];
    Show_c3d_SelImg(r, g, b);
    ShowImageColor(img_color, r, g, b);
    double sim_r, sim_g, sim_b;
    C3Dsim_t(r, g, b, &sim_r, &sim_g, &sim_b);
    Show_c3d_SimImg(sim_r, sim_g, sim_b);
    Show_c3d_Img_sim();
    refresh_6axis_grid_t(sim_r, sim_g, sim_b);
}

//---------------------------------------------------------------------------
// Set parameter "sigma_lgt", sigma_lgt is a value for Modulate Saturation value from 0.666 to 0
// The value is for Gaussian distribution, used in function "Manual39_mid",
//"Manual39_light","Manual39_dark"
void __fastcall TC3DForm1::lbe_sat_sigma_lightChange(TObject * Sender)
{
    sigma_lgt = StrToFloat(lbe_sat_sigma_light->Text);
}

//---------------------------------------------------------------------------
// When StringGrid "sg_12color1" Select Change,
// call function "sg_12color1MouseDown" to change select color
void __fastcall TC3DForm1::sg_12color1SelectCell(TObject * Sender, int ACol,
						 int ARow, bool & CanSelect)
{
    Cell_move = false;
    if (ARow == 0)
	return;
    int rgb[12][3] = { {192, 64, 64}, {192, 128, 64}, {192, 192, 64}, {128, 192, 64},
    {64, 192, 64}, {64, 192, 128}, {64, 192, 192}, {64, 128, 192}, {64, 64, 192},
    {128, 64, 192}, {192, 64, 192}, {192, 64, 128}
    };

    double r = rgb[ARow - 1][0];
    double g = rgb[ARow - 1][1];
    double b = rgb[ARow - 1][2];

    ShowSelectCell(ARow, r, g, b, sg_12color1);
    Cell_move = true;
}

//---------------------------------------------------------------------------
// When StringGrid "sg_12color2" Select Change,
// call function "sg_12color2MouseDown" to change select color
void __fastcall TC3DForm1::sg_12color2SelectCell(TObject * Sender, int ACol,
						 int ARow, bool & CanSelect)
{
    int X = ACol * sg_12color2->DefaultColWidth;
    int Y = ARow * (sg_12color2->DefaultRowHeight + 1);

    TShiftState Shift;
    TMouseButton Button;
    sg_12color2MouseDown(Sender, Button, Shift, X, Y);
}

//---------------------------------------------------------------------------

// 切換HuePage的分頁時, 同步更換顯示顏色

void __fastcall TC3DForm1::btn_AddPointClick(TObject * Sender)
{
    AnsiString str;
    AnsiString Rin, Gin, Bin, Rout, Gout, Bout;
    for (int i = 0; i < PointColor_array_nbr; i++) {
	Rin = FloatToStr(PointColor_array[i][0]);
	Gin = FloatToStr(PointColor_array[i][1]);
	Bin = FloatToStr(PointColor_array[i][2]);
	Rout = FloatToStr(PointColor_array[i][3]);
	Gout = FloatToStr(PointColor_array[i][4]);
	Bout = FloatToStr(PointColor_array[i][5]);
	str = Rin + "," + Gin + "," + Bin + "   " + Rout + "," + Gout + "," + Bout;
	ListBox_PointColor->Items->Add(str);	//加入資料
    }
    PointColor_array_nbr = 0;
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_DeletePointClick(TObject * Sender)
{
    int index = ListBox_PointColor->ItemIndex;

    if (index != -1)
	ListBox_PointColor->Items->Delete(index);
    else {
	index = ListBox_PointColor->Items->Count - 1;
	ListBox_PointColor->Items->Delete(index);
    }
}

//---------------------------------------------------------------------------






void __fastcall TC3DForm1::btn_SaveRecordClick(TObject * Sender)
{
    int index = ListBox_PointColor->Items->Count;
    AnsiString Str_Record;
    if (!SaveDialog1->Execute()) {
	return;
    }
    String Fpath = SaveDialog1->FileName /*+".txt" */ ;
    FILE *fptr = fopen(Fpath.c_str(), "w");
    fprintf(fptr, "%d\n", index);
    for (int i = 0; i < index; i++) {
	Str_Record = ListBox_PointColor->Items->Strings[i];
	fprintf(fptr, "%s\n", Str_Record.c_str());
    }
    fprintf(fptr, "\0");
    fclose(fptr);
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_LoadRecordClick(TObject * Sender)
{
    int ok = Application->MessageBox("Replace Colors?", "Warning", MB_OKCANCEL);
    if (ok != 1)
	return;			// do nothing

    if (!OpenDialog1->Execute())
	return;
    String Fpath = OpenDialog1->FileName;
    char *buffer = Load_File(Fpath);

    // Calculate number of lines
    int line_nbr = 0;
    /*
       char* pch=strchr(buffer,'\n');
       while (pch!=NULL){
       line_nbr++;
       pch=strchr(pch+1,'\n');
       } */

    // Get each lines of String

    //加入資料
    int idx = 0;
    char *pch = strtok(buffer, "\n");
    if (isdigit(pch[0]))
	line_nbr = StrToInt(pch);
    else
	return;

    char **str = new char *[line_nbr + 1];
    for (int i = 0; i < line_nbr + 1; i++)
	str[i] = "";

    pch = strtok(NULL, "\n\0");
    while (idx < line_nbr) {
	str[idx] = pch;
	ListBox_PointColor->Items->Add(str[idx]);
	pch = strtok(NULL, "\n\0");
	idx++;
    }
    int *Rin = new int[line_nbr];
    int *Gin = new int[line_nbr];
    int *Bin = new int[line_nbr];
    double *Rout = new double[line_nbr];
    double *Gout = new double[line_nbr];
    double *Bout = new double[line_nbr];

    // Get Rin, Gin, Bin, Rout, Gout, Bout in Each Point
    for (int i = 0; i < line_nbr; i++) {
	pch = strtok(str[i], ", \t\0");
	idx = 0;
	while (pch != NULL) {
	    if (idx % 6 == 0)
		Rin[i] = StrToFloat(pch) / cube_dis;
	    else if (idx % 6 == 1)
		Gin[i] = StrToFloat(pch) / cube_dis;
	    else if (idx % 6 == 2)
		Bin[i] = StrToFloat(pch) / cube_dis;
	    else if (idx % 6 == 3)
		Rout[i] = StrToFloat(pch);
	    else if (idx % 6 == 4)
		Gout[i] = StrToFloat(pch);
	    else if (idx % 6 == 5)
		Bout[i] = StrToFloat(pch);
	    idx++;
	    pch = strtok(NULL, ", \t\0");
	}
	c3d_lutR[Rin[i]][Gin[i]][Bin[i]] = Rout[i];
	c3d_lutG[Rin[i]][Gin[i]][Bin[i]] = Gout[i];
	c3d_lutB[Rin[i]][Gin[i]][Bin[i]] = Bout[i];
	rgb2hsv(Rout[i], Gout[i], Bout[i], &c3d_lutH[Rin[i]][Gin[i]][Bin[i]],
		&c3d_lutS[Rin[i]][Gin[i]][Bin[i]], &c3d_lutI[Rin[i]][Gin[i]][Bin[i]],
		&c3d_lutV[Rin[i]][Gin[i]][Bin[i]]);
    }
    for (int i = 0; i < line_nbr + 1; i++)
	delete[]str[i];
    delete[]str;
    delete[]buffer;

    if (line_nbr > 0) {
	sg_rgb_input->Cells[0][1] = Rin[0];
	sg_rgb_input->Cells[1][1] = Gin[0];
	sg_rgb_input->Cells[2][1] = Bin[0];
    }

    delete[]Rin;
    delete[]Gin;
    delete[]Bin;
    delete[]Rout;
    delete[]Gout;
    delete[]Bout;
}

//---------------------------------------------------------------------------


void __fastcall TC3DForm1::ListBox_PointColorClick(TObject * Sender)
{
    int index = ListBox_PointColor->ItemIndex;

    double Rin, Gin, Bin;
    if (index != -1) {
	AnsiString str = ListBox_PointColor->Items->Strings[index];

	char *pch = strtok(str.c_str(), ", ");
	int idx = 0;
	while (pch != NULL) {
	    if (idx % 6 == 0)
		Rin = StrToFloat(pch);
	    else if (idx % 6 == 1)
		Gin = StrToFloat(pch);
	    else if (idx % 6 == 2)
		Bin = StrToFloat(pch);
	    idx++;
	    pch = strtok(NULL, ", ");
	}
	sg_rgb_input->Cells[0][1] = Rin;
	sg_rgb_input->Cells[1][1] = Gin;
	sg_rgb_input->Cells[2][1] = Bin;
	btn_key_in_RGBClick(Sender);
    } else {
	return;
    }
}

//---------------------------------------------------------------------------





void __fastcall TC3DForm1::pc_AdjustChange(TObject * Sender)
{
    if (pc_Adjust->TabIndex == 0 && pc_global_adj->TabIndex == 1)
	//Manual 39 Colors   //更換顯示顏色
	rg_manual_39_choiceClick(Sender);
}

//---------------------------------------------------------------------------


void __fastcall TC3DForm1::btn_show_4_colorClick(TObject * Sender)
{
    rg_PointNum->ItemIndex = 1;
}

//---------------------------------------------------------------------------


void __fastcall TC3DForm1::rg_PCrgb_chooseClick(TObject * Sender)
{
    if (rg_PCrgb_choose->ItemIndex == 0) {
	gb_PCrgb_rgb->Visible = true;
	gb_PCrgb_hsv->Visible = false;
    } else if (rg_PCrgb_choose->ItemIndex == 1) {
	gb_PCrgb_rgb->Visible = false;
	gb_PCrgb_hsv->Visible = true;
    }
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::rg_manual_39_choiceClick(TObject * Sender)
{
    bool a;
    bool & CanS = &a;

    int ACol = 1;
    if (rg_manual_39_choice->ItemIndex == 0) {
	//切換到Light 12
	pc_HuePage_Grid->TabIndex = 0;
	ts_light12->Show();
	int ARow = sg_12color1->Row;
	sg_12color1SelectCell(Sender, ACol, ARow, CanS);
	sb_c3d_Manual39_h->Enabled = true;
	sb_c3d_Manual39_s->Enabled = true;
    } else if (rg_manual_39_choice->ItemIndex == 1) {
	//切換到Middle 12
	pc_HuePage_Grid->TabIndex = 1;
	ts_middle12->Show();
	int ARow = sg_12color2->Row;
	sg_12color2SelectCell(Sender, ACol, ARow, CanS);
	sb_c3d_Manual39_h->Enabled = true;
	sb_c3d_Manual39_s->Enabled = true;
    } else if (rg_manual_39_choice->ItemIndex == 2) {
	//切換到Dark 6
	pc_HuePage_Grid->TabIndex = 2;
	ts_dark6->Show();
	int ARow = sg_Dark->Row;
	sg_DarkSelectCell(Sender, ACol, ARow, CanS);
	sb_c3d_Manual39_h->Enabled = false;
	sb_c3d_Manual39_s->Enabled = false;
    } else if (rg_manual_39_choice->ItemIndex == 3) {
	//切換到Gray
	pc_HuePage_Grid->TabIndex = 3;
	ts_gray9->Show();
	int ARow = sg_Gray->Row;
	sg_GraySelectCell(Sender, ACol, ARow, CanS);
	sb_c3d_Manual39_h->Enabled = false;
	sb_c3d_Manual39_s->Enabled = false;
    }
}

//---------------------------------------------------------------------------


void __fastcall TC3DForm1::pc_global_adjChange(TObject * Sender)
{
    if (pc_global_adj->TabIndex == 1) {
	//Manual 39 Colors   //更換顯示顏色
	rg_manual_39_choiceClick(Sender);
    }
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::c3d_Sim_Image_HSV_StepClick(TObject * Sender)
{
    // reference HSV adjust with image(0) or color(1)
    fl_ref_HSV_img_col = 0;

    int X = X_site - 40;
    int Y = Y_site - 40;

    double r, g, b, sim_r, sim_g, sim_b, h, s, in, v;
    double H_step = StrToFloat(Form3->lb_c3d_sim_H_step->Caption);
    double S_step = StrToFloat(Form3->lb_c3d_sim_S_step->Caption);
    double V_step = StrToFloat(Form3->lb_c3d_sim_V_step->Caption) / 255;
    int color;
    TCanvas *pCanvas = Form3->Image1->Canvas;
    TCanvas *pCanvas2 = Form3->Image2->Canvas;
    TCanvas *pCanvas3 = Form3->Image3->Canvas;
    TImage *Img;
    if (pc_img->TabIndex == 0)
	Img = Img_3DLUT;
    else if (pc_img->TabIndex == 1)
	Img = img_color;

    BYTE *p_Img1, *p_Img2, *p_Img3;

    for (int y = 0; y < 80; y++) {	//截取80x80的圖片做處理
	for (int x = 0; x < 80; x++) {
	    color = Img->Canvas->Pixels[X + x][Y + y];
	    if (color == -1)
		color = 0;
	    b = color / 65536;
	    g = color / 256 % 256;
	    r = color % 256;
	    C3Dsim_t(r, g, b, &sim_r, &sim_g, &sim_b);
	    rgb2hsv(sim_r, sim_g, sim_b, &h, &s, &in, &v);
	    for (int j = 0; j < 5; j++) {
		p_Img1 = (BYTE *) Form3->Image1->Picture->Bitmap->ScanLine[y + j * 80];
		p_Img2 = (BYTE *) Form3->Image2->Picture->Bitmap->ScanLine[y + j * 80];
		p_Img3 = (BYTE *) Form3->Image3->Picture->Bitmap->ScanLine[y + j * 80];
		for (int i = 0; i < 5; i++) {
		    hsv2rgb(h + (i - 2) * H_step, s * (1 + (j - 2) * (-1) * S_step), v, &r, &g, &b);
		    p_Img1[(x + i * 80) * 3 + 2] = r;
		    p_Img1[(x + i * 80) * 3 + 1] = g;
		    p_Img1[(x + i * 80) * 3] = b;

		    hsv2rgb(h + (i - 2) * H_step, s, v * (1 + (j - 2) * (-1) * V_step), &r, &g, &b);
		    p_Img2[(x + i * 80) * 3 + 2] = r;
		    p_Img2[(x + i * 80) * 3 + 1] = g;
		    p_Img2[(x + i * 80) * 3] = b;

		    hsv2rgb(h, s * (1 + (i - 2) * S_step), v * (1 + (j - 2) * (-1) * V_step), &r,
			    &g, &b);
		    p_Img3[(x + i * 80) * 3 + 2] = r;
		    p_Img3[(x + i * 80) * 3 + 1] = g;
		    p_Img3[(x + i * 80) * 3] = b;
		}
	    }
	}
    }
    pCanvas->Pen->Width = 3;
    pCanvas2->Pen->Width = 3;
    pCanvas3->Pen->Width = 3;
    for (int i = 1; i <= 4; i++) {
	pCanvas->MoveTo(i * 80, 0);	//vertical
	pCanvas->LineTo(i * 80, 400);
	pCanvas->MoveTo(0, i * 80);	//horizontal
	pCanvas->LineTo(400, i * 80);

	pCanvas2->MoveTo(i * 80, 0);	//vertical
	pCanvas2->LineTo(i * 80, 400);
	pCanvas2->MoveTo(0, i * 80);	//horizontal
	pCanvas2->LineTo(400, i * 80);

	pCanvas3->MoveTo(i * 80, 0);	//vertical
	pCanvas3->LineTo(i * 80, 400);
	pCanvas3->MoveTo(0, i * 80);	//horizontal
	pCanvas3->LineTo(400, i * 80);
    }
    if (pc_Adjust->TabIndex == 0 && pc_global_adj->TabIndex == 1) {
	//Manual 39, 紀錄目前移動量
	Form3->Text_H_move->Caption = sb_c3d_Manual39_h->Position - sb_c3d_Manual39_h->Max / 2;
	Form3->Text_S_move->Caption = sb_c3d_Manual39_s->Position - sb_c3d_Manual39_s->Max / 2;
	Form3->Text_V_move->Caption = sb_c3d_Manual39_v->Position - sb_c3d_Manual39_v->Max / 2;
    }
    Form3->WindowState = wsNormal;
    Form3->Show();
    /* 黑框
       int X = X_site-35;
       int Y = Y_site-35;
       Img_3DLUT->Canvas->MoveTo(X, Y);
       Img_3DLUT->Canvas->LineTo(X+70, Y);
       Img_3DLUT->Canvas->LineTo(X+70, Y+70);
       Img_3DLUT->Canvas->LineTo(X, Y+70);
       Img_3DLUT->Canvas->LineTo(X, Y);
     */
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::c3d_Sim_Color_HSV_StepClick(TObject * Sender)
{
    // reference HSV adjust with image(0) or color(1)
    fl_ref_HSV_img_col = 1;

    double H_step = StrToFloat(Form3->lb_c3d_sim_H_step->Caption);
    double S_step = StrToFloat(Form3->lb_c3d_sim_S_step->Caption);
    double V_step = StrToFloat(Form3->lb_c3d_sim_V_step->Caption) / 255;
    double r, g, b, h, s, v;
    h = StrToFloat(lb_c3d_simH->Caption);
    s = StrToFloat(lb_c3d_simS->Caption);
    v = StrToFloat(lb_c3d_simV->Caption);
    r = StrToFloat(lb_c3d_simR->Caption);
    g = StrToFloat(lb_c3d_simG->Caption);
    b = StrToFloat(lb_c3d_simB->Caption);

    TCanvas *pCanvas = Form3->Image1->Canvas;
    for (int i = 0; i < 5; i++)
	for (int j = 0; j < 5; j++) {
	    hsv2rgb(h + (i - 2) * H_step, s * (1 + (j - 2) * (-1) * S_step), v, &r, &g, &b);
	    pCanvas->Brush->Color = (TColor) (r + 256 * g + 65536 * b);
	    pCanvas->Brush->Style = bsSolid;
	    pCanvas->Rectangle(i * 80 + 0, j * 80 + 0, i * 80 + 80, j * 80 + 80);
	}
    TCanvas *pCanvas2 = Form3->Image2->Canvas;
    for (int i = 0; i < 5; i++) {
	for (int j = 0; j < 5; j++) {
	    hsv2rgb(h + (i - 2) * H_step, s, v * (1 + (j - 2) * (-1) * V_step), &r, &g, &b);
	    pCanvas2->Brush->Color = (TColor) (r + 256 * g + 65536 * b);
	    pCanvas2->Brush->Style = bsSolid;
	    pCanvas2->Rectangle(i * 80 + 0, j * 80 + 0, i * 80 + 80, j * 80 + 80);
	}
    }
    TCanvas *pCanvas3 = Form3->Image3->Canvas;
    for (int i = 0; i < 5; i++) {
	for (int j = 0; j < 5; j++) {
	    hsv2rgb(h, s * (1 + (i - 2) * S_step), v * (1 + (j - 2) * (-1) * V_step), &r, &g, &b);
	    pCanvas3->Brush->Color = (TColor) (r + 256 * g + 65536 * b);
	    pCanvas3->Brush->Style = bsSolid;
	    pCanvas3->Rectangle(i * 80 + 0, j * 80 + 0, i * 80 + 80, j * 80 + 80);
	}
    }
    if (pc_Adjust->TabIndex == 0 && pc_global_adj->TabIndex == 1) {
	//Manual 39, 紀錄目前移動量
	Form3->Text_H_move->Caption = sb_c3d_Manual39_h->Position - sb_c3d_Manual39_h->Max / 2;
	Form3->Text_S_move->Caption = sb_c3d_Manual39_s->Position - sb_c3d_Manual39_s->Max / 2;
	Form3->Text_V_move->Caption = sb_c3d_Manual39_v->Position - sb_c3d_Manual39_v->Max / 2;
    }
    Form3->WindowState = wsNormal;
    Form3->Show();
}

//---------------------------------------------------------------------------
double TC3DForm1::GetPointH_val()
{
    double H = sb_c3d_Point_HSV_h->Position - sb_c3d_Point_HSV_h->Max / 2;
    return H;
}

void TC3DForm1::SetPointH_caption(double H)
{
    lb_c3d_Point_HSV_h->Caption = FloatToStr(H) + "°";
}

void __fastcall TC3DForm1::sb_c3d_Point_HSV_hChange(TObject * Sender)
{
    double H = GetPointH_val();
    //if(pc_HuePage_Grid->TabIndex==2 || pc_HuePage_Grid->TabIndex==3)
    //        H = 0;
    SetPointH_caption(H);
    Adjust_H_diffusion(H);

    //HSV Diffusion page
    Point_HSV_Bar_Move();	//改變SimImg顯示的色彩, 並不改變table值
}

void TC3DForm1::Point_HSV_Bar_Move()
{


    c3d_hsvBase_adj(false);

    /* double r = StrToFloat(lb_c3d_selR->Caption);
       double g = StrToFloat(lb_c3d_selG->Caption);
       double b = StrToFloat(lb_c3d_selB->Caption);
       if(rg_c3d_hsv_mode->ItemIndex==1)
       c3d_6axisAdj_h(false);
       else if(rg_c3d_hsv_mode->ItemIndex==0)
       c3d_hsvBase_adj(false);
       else if(rg_c3d_hsv_mode->ItemIndex==2)
       c3d_MixAdj_h(false);
       else if(rg_c3d_hsv_mode->ItemIndex==3)
       c3d_hsv_FixGain(false);
     */
}

//---------------------------------------------------------------------------


void __fastcall TC3DForm1::sb_c3d_Point_HSV_hdnChange(TObject * Sender)
{
    int neg = Get_Point_H_NegDif();
    lb_c3d_Point_HSV_hdn->Caption = IntToStr(neg) + "°";	//position 1000 means 0
}

void __fastcall TC3DForm1::sb_c3d_Point_HSV_hdpChange(TObject * Sender)
{
    int pos = Get_Point_H_PosDif();
    lb_c3d_Point_HSV_hdp->Caption = IntToStr(pos) + "°";
}

//---------------------------------------------------------------------------
void __fastcall TC3DForm1::sb_c3d_Point_HSV_svdChange(TObject * Sender)
{
    double sv = sb_c3d_Point_HSV_svd->Position;
    lb_c3d_Point_HSV_svd->Caption = FloatToStr(sv / 10);
}

//---------------------------------------------------------------------------

int TC3DForm1::Get_Point_H_NegDif()
{
    int neg = sb_c3d_Point_HSV_hdn->Position - sb_c3d_Point_HSV_hdn->Max;
    return neg;
}

//--------------------------------------------------------------------------
int TC3DForm1::Get_Point_H_PosDif()
{
    int pos = sb_c3d_Point_HSV_hdp->Position;
    return pos;
}

//--------------------------------------------------------------------------
void TC3DForm1::Adjust_H_diffusion(double H)
{
    if (H > 0) {
	if (sb_c3d_Point_HSV_hdp->Position < H)
	    sb_c3d_Point_HSV_hdp->Position = H;
    } else if (H < 0) {
	if (sb_c3d_Point_HSV_hdn->Position - sb_c3d_Point_HSV_hdn->Max > H)
	    sb_c3d_Point_HSV_hdn->Position = H + sb_c3d_Point_HSV_hdn->Max;
    }
}

//--------------------------------------------------------------------------

void __fastcall TC3DForm1::sb_c3d_Point_HSV_sChange(TObject * Sender)
{
    SetPointS_Caption();

    //HSV Diffusion page
    Point_HSV_Bar_Move();	//改變SimImg顯示的色彩, 並不改變table值

    /*if(rg_c3d_hsv_mode->ItemIndex==1)
       c3d_6axisAdj_s(false);
       else if(rg_c3d_hsv_mode->ItemIndex==0)
       c3d_hsvBase_adj(false);
       else if(rg_c3d_hsv_mode->ItemIndex==2)
       c3d_MixAdj_s(false);
     */
}

//---------------------------------------------------------------------------
int TC3DForm1::GetPointS_val()
{
    int S = sb_c3d_Point_HSV_s->Position - sb_c3d_Point_HSV_s->Max / 2;
    return S;
}

void TC3DForm1::SetPointS_Caption()
{
    double c = StrToFloat(edt_c3d_satC->Text);
    double s_gain = (double) GetPointS_val() / 100 / c;
    double S = StrToFloat(lb_c3d_selS->Caption);
    S = double (floor(S * s_gain * 1000)) / 1000;
    lb_c3d_Point_HSV_s->Caption = FloatToStr(S);
}

//--------------------------------------------------------------------------
void __fastcall TC3DForm1::sb_c3d_Point_HSV_vChange(TObject * Sender)
{
    SetPointV_Caption();

    //HSV Diffusion page
    Point_HSV_Bar_Move();	//改變SimImg顯示的色彩, 並不改變table值

    /*if(rg_c3d_hsv_mode->ItemIndex==1)
       c3d_6axisAdj_s(false);
       else if(rg_c3d_hsv_mode->ItemIndex==0)
       c3d_hsvBase_adj(false);
       else if(rg_c3d_hsv_mode->ItemIndex==2)
       c3d_MixAdj_s(false);
     */
}

//---------------------------------------------------------------------------

int TC3DForm1::GetPointV_val()
{
    int V = sb_c3d_Point_HSV_v->Position - sb_c3d_Point_HSV_v->Max / 2;
    return V;
}

void TC3DForm1::SetPointV_Caption()
{
    double c = StrToFloat(edt_c3d_valC->Text);
    double v_gain = (double) GetPointV_val() / 100 / c;
    double V = StrToFloat(lb_c3d_selV->Caption);
    lb_c3d_Point_HSV_v->Caption = FloatToStr(V * v_gain);
}

void __fastcall TC3DForm1::cb_show_ref_imgClick(TObject * Sender)
{
    if (cb_show_ref_img->Checked == true)
	Form_in_target->WindowState = wsNormal;
    else
	Form_in_target->WindowState = wsMinimized;
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::pc_imgChange(TObject * Sender)
{
    if (pc_img->TabIndex == 0)
	Form_in_target->img_in_target->Picture->Bitmap->Assign(Img_3DLUT->Picture->Bitmap);
    else
	Form_in_target->img_in_target->Picture->Bitmap->Assign(img_color->Picture->Bitmap);
}

//---------------------------------------------------------------------------


bool Load_XlsFile(String fpath, String Sheet_N, double **Data, int W_max, int H_max)
{
    using namespace cms::colorformat;
    using namespace std;

    const string & filename = fpath.c_str();
    ExcelFileDB db(filename, ReadOnly);
    //db.setTableName((string&)Sheet_N);

    db.setTableName(Sheet_N.c_str());
    bptr < DBQuery > query = db.selectAll();

    int i = 0;
    int j = 0;
    while (query->hasNext()) {
	string_vector_ptr result = query->nextResult();
	double_vector_ptr doubleresult = query->toDoubleVector(result);
	i = 0;
	foreach(const double d, *doubleresult) {
	    if (i > W_max || j > H_max)
		return 0;
	    Data[j][i] = d;
	    i++;
	}
	if (i < W_max)
	    return 0;
	j++;
    };
    if (i != W_max || j != H_max)
	return 0;
    else
	return 1;
}

double R255_xyY[3], G255_xyY[3], B255_xyY[3], W255_xyY[3], W0_xyY[3];	// Source量測數值
double SR0_255_Y[256], SG0_255_Y[256], SB0_255_Y[256];	// Source量測數值
double R255_XYZ[3], G255_XYZ[3], B255_XYZ[3], W255_XYZ[3], W0_XYZ[3];

void __fastcall TC3DForm1::btn_Auto_Src_LoadClick(TObject * Sender)
{
    if (!OpenDialog_xls->Execute())
	return;
    String Fpath = OpenDialog_xls->FileName;
    //String* Column_name = {"Gray Level","W_x","W_y","W_Y (nit)","W_C.T.","ΔUV","W_R","W_G",
    //"W_B","R_x","R_y","R_Y (nit)","G_x","G_y","G_Y (nit)","B_x","B_y","B_Y (nit)"};

    int WRGB_h = 256, WRGB_w = 18;
    double **WRGB_meas = new double *[WRGB_h];
    for (int i = 0; i < WRGB_h; i++)
	WRGB_meas[i] = new double[WRGB_w];

    bool Load_ok = Load_XlsFile(Fpath, "Sheet1", WRGB_meas, WRGB_w, WRGB_h);
    if (!Load_ok) {
	ShowMessage("Fail to Load Source WRGB file.");
	return;
    }
    //Load Source table
    for (int i = 0; i < 3; i++) {
	W0_xyY[i] = WRGB_meas[255][1 + i];
	W255_xyY[i] = WRGB_meas[0][1 + i];
	R255_xyY[i] = WRGB_meas[0][9 + i];
	G255_xyY[i] = WRGB_meas[0][12 + i];
	B255_xyY[i] = WRGB_meas[0][15 + i];
    }
    for (int i = 0; i < 256; i++) {
	SR0_255_Y[i] = WRGB_meas[255 - i][11];
	SG0_255_Y[i] = WRGB_meas[255 - i][14];
	SB0_255_Y[i] = WRGB_meas[255 - i][17];
    }
    for (int i = 0; i < WRGB_h; i++)
	delete[]WRGB_meas[i];
    delete[]WRGB_meas;
    btn_Auto_Src_Calc->Enabled = true;
}

//---------------------------------------------------------------------------
void xyY2XYZ(double C_xyY[3], double C_XYZ[3])
{
    double x = C_xyY[0];
    double y = C_xyY[1];
    double Y = C_xyY[2];

    if (y == 0)
	y = 1.0 / 65535;
    C_XYZ[0] = x / y * Y;	// X = x/y*Y
    C_XYZ[1] = Y;		// Y = Y
    C_XYZ[2] = (1 - x - y) / y * Y;	// Z = (1-x-y)/y*Y
}

void Normal_XYZ(double C_XYZ[3], double W255_Y, double W0_XYZ[3], double NC_XYZ[3])
{
    for (int i = 0; i < 3; i++)
	NC_XYZ[i] = (C_XYZ[i] - W0_XYZ[i]) / W255_Y;
}

void Inverse_3matrix(double A[3][3], double B[3][3])
{
    // A^(-1) = (1/det(A))*(cofactor(A))^T;
    // det(A)

    double det;
    det = A[0][0] * A[1][1] * A[2][2];
    det += A[0][1] * A[1][2] * A[2][0];
    det += A[1][0] * A[2][1] * A[0][2];
    det -= A[0][2] * A[1][1] * A[2][0];
    det -= A[0][1] * A[1][0] * A[2][2];
    det -= A[1][2] * A[2][1] * A[0][0];

    // Cofactor of A
    double C[3][3];
    C[0][0] = A[1][1] * A[2][2] - (A[2][1] * A[1][2]);
    C[0][1] = (-1) * (A[1][0] * A[2][2] - (B[2][0] * B[1][2]));
    C[0][2] = A[1][0] * A[2][1] - (A[2][0] * A[1][1]);

    C[1][0] = (-1) * (A[0][1] * A[2][2] - A[2][1] * A[0][2]);
    C[1][1] = A[0][0] * A[2][2] - A[2][0] * A[0][2];
    C[1][2] = (-1) * (A[0][0] * A[2][1] - A[2][0] * A[0][1]);

    C[2][0] = A[0][1] * A[1][2] - A[1][1] * A[0][2];
    C[2][1] = (-1) * (A[0][0] * A[1][2] - A[1][0] * A[0][2]);
    C[2][2] = A[0][0] * A[1][1] - A[1][0] * A[0][1];

    // Transform Cofactor matrix
    for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
	    B[j][i] = C[i][j] / det;
}

//---------------------------------------------------------------------------
void Mtrx3_multiple(double multi1[3][3], double multi2[3][3], double result[3][3])
{
    for (int i = 0; i < 3; i++)
	for (int j = 0; j < 3; j++)
	    for (int s = 0; s < 3; s++) {
		result[i][j] += multi1[i][s] * multi2[s][j];
	    }
}
void xyY2xyz(double *xyY, double *xyz)
{
    xyz[0] = xyY[0];
    xyz[1] = xyY[1];
    xyz[2] = 1 - xyz[0] - xyz[1];
}

//---------------------------------------------------------------------------


void __fastcall TC3DForm1::btn_Auto_Src_CalcClick(TObject * Sender)
{
    double Gamma_R, Gamma_G, Gamma_B;
    double Mtrx_rgb2xyz[3][3] = { 0 };
    double R255_xyz[3], G255_xyz[3], B255_xyz[3];
    double P[256];		// 計算Gamma用的參數
    double *SR0_255_YN, *SG0_255_YN, *SB0_255_YN;
    SR0_255_YN = new double[256];	// Red 0 ~ Red255 的 Y
    SG0_255_YN = new double[256];
    SB0_255_YN = new double[256];
    // Normalize SR0_255_Y, SG0_255_Y, SB0_255_Y;
    for (int i = 0; i < 256; i++) {
	// Use W0 & (R255 or G255 or B255) to Normalize R0~255, G0~255, B0~255
	SR0_255_YN[i] = (SR0_255_Y[i] - W0_xyY[2]) / (R255_xyY[2] - W0_xyY[2]);
	SG0_255_YN[i] = (SG0_255_Y[i] - W0_xyY[2]) / (G255_xyY[2] - W0_xyY[2]);
	SB0_255_YN[i] = (SB0_255_Y[i] - W0_xyY[2]) / (B255_xyY[2] - W0_xyY[2]);
	if (i != 0)
	    P[i] = log10((double) i / 255);
	if (SR0_255_YN[i] < 0.000001)
	    SR0_255_YN[i] = 0.000001;
	if (SG0_255_YN[i] < 0.000001)
	    SG0_255_YN[i] = 0.000001;
	if (SB0_255_YN[i] < 0.000001)
	    SB0_255_YN[i] = 0.000001;
    }
    P[0] = log10(0.000001);

    // 計算Gamma, 參考"http://www.brucelindbloom.com/Eqn_BestGamma.html"
    double tmp_r = 0.0, tmp_g = 0.0, tmp_b = 0.0, tmp_p = 0.0;

    for (int i = 1; i < 256; i++) {	//discard 0 Point
	tmp_r += log10(SR0_255_YN[i]) * P[i];
	tmp_g += log10(SG0_255_YN[i]) * P[i];
	tmp_b += log10(SB0_255_YN[i]) * P[i];
	tmp_p += P[i] * P[i];
    }
    Gamma_R = tmp_r / tmp_p;
    Gamma_G = tmp_g / tmp_p;
    Gamma_B = tmp_b / tmp_p;

    // to interface
    lble_auto_Gm_R->Text = Gamma_R;
    lble_auto_Gm_G->Text = Gamma_G;
    lble_auto_Gm_B->Text = Gamma_B;

    delete[]SR0_255_YN;
    delete[]SG0_255_YN;
    delete[]SB0_255_YN;

    //===============  計算RGB2XYZ矩陣  ===============================//

    xyY2XYZ(R255_xyY, R255_XYZ);
    xyY2XYZ(G255_xyY, G255_XYZ);
    xyY2XYZ(B255_xyY, B255_XYZ);
    xyY2XYZ(W255_xyY, W255_XYZ);
    xyY2XYZ(W0_xyY, W0_XYZ);

    double R255m0_XYZ[3], G255m0_XYZ[3], B255m0_XYZ[3], W255m0_XYZ[3], W0m0_XYZ[3];
    Normal_XYZ(R255_XYZ, W255_xyY[2], W0_XYZ, R255m0_XYZ);
    Normal_XYZ(G255_XYZ, W255_xyY[2], W0_XYZ, G255m0_XYZ);
    Normal_XYZ(B255_XYZ, W255_xyY[2], W0_XYZ, B255m0_XYZ);
    Normal_XYZ(W255_XYZ, W255_xyY[2], W0_XYZ, W255m0_XYZ);
    Normal_XYZ(W0_XYZ, W255_xyY[2], W0_XYZ, W0m0_XYZ);

    if (rg_Color_Model->ItemIndex == 1) {
	//Suppose YR255+YG255+YB255=YW255 Linear
	//                | xr xg xb |
	// Mtrx_rgb2xyz = | yr yg yb |
	//                | zr zg zb |
	for (int i = 0; i < 3; i++) {
	    Mtrx_rgb2xyz[i][0] = R255m0_XYZ[i];
	    Mtrx_rgb2xyz[i][1] = G255m0_XYZ[i];
	    Mtrx_rgb2xyz[i][2] = B255m0_XYZ[i];
	}
    } else if (rg_Color_Model->ItemIndex == 0) {
	// Consider R,G,B ratio as SR*YR255+SG*YG255+SB*YB255=YW255
	double Mtrx_xyz[3][3], InvMtrx_xyz[3][3];
	double R255_xyz[3], G255_xyz[3], B255_xyz[3];
	double Sr = 0, Sg = 0, Sb = 0;
	xyY2xyz(R255_xyY, R255_xyz);
	xyY2xyz(G255_xyY, G255_xyz);
	xyY2xyz(B255_xyY, B255_xyz);
	for (int i = 0; i < 3; i++) {
	    Mtrx_xyz[i][0] = R255_xyz[i];
	    Mtrx_xyz[i][1] = G255_xyz[i];
	    Mtrx_xyz[i][2] = B255_xyz[i];
	}
	Inverse_3matrix(Mtrx_xyz, InvMtrx_xyz);
	for (int i = 0; i < 3; i++) {
	    Sr += InvMtrx_xyz[0][i] * (W255m0_XYZ[i] - W0m0_XYZ[i]);
	    Sg += InvMtrx_xyz[1][i] * (W255m0_XYZ[i] - W0m0_XYZ[i]);
	    Sb += InvMtrx_xyz[2][i] * (W255m0_XYZ[i] - W0m0_XYZ[i]);
	}
	double Mtrx_SrSgSb[3][3] = { 0 };
	Mtrx_SrSgSb[0][0] = Sr;
	Mtrx_SrSgSb[1][1] = Sg;
	Mtrx_SrSgSb[2][2] = Sb;

	Mtrx3_multiple(Mtrx_xyz, Mtrx_SrSgSb, Mtrx_rgb2xyz);
    }
    // RGB2XYZ
    edt_auto_rgb2xyz11->Text = Mtrx_rgb2xyz[0][0];
    edt_auto_rgb2xyz12->Text = Mtrx_rgb2xyz[0][1];
    edt_auto_rgb2xyz13->Text = Mtrx_rgb2xyz[0][2];
    edt_auto_rgb2xyz21->Text = Mtrx_rgb2xyz[1][0];
    edt_auto_rgb2xyz22->Text = Mtrx_rgb2xyz[1][1];
    edt_auto_rgb2xyz23->Text = Mtrx_rgb2xyz[1][2];
    edt_auto_rgb2xyz31->Text = Mtrx_rgb2xyz[2][0];
    edt_auto_rgb2xyz32->Text = Mtrx_rgb2xyz[2][1];
    edt_auto_rgb2xyz33->Text = Mtrx_rgb2xyz[2][2];

    btn_Auto_Src_Calc->Enabled = false;
}

//---------------------------------------------------------------------------
double **T_tbl_xyY;
double **Tbl_RGB;
void __fastcall TC3DForm1::btn_Auto_Trg_LoadClick(TObject * Sender)
{
    // Target_xyY
    T_tbl_xyY = new double *[total_len];
    for (int i = 0; i < total_len; i++)
	T_tbl_xyY[i] = new double[3];

    if (!OpenDialog_xls->Execute())
	return;
    String Fpath = OpenDialog_xls->FileName;

    int T_tbl_col_h = total_len, T_tbl_col_w = 7;
    double **T_tbl_col = new double *[T_tbl_col_h];
    for (int i = 0; i < T_tbl_col_h; i++)
	T_tbl_col[i] = new double[T_tbl_col_w];

    bool Load_ok = Load_XlsFile(Fpath, "Sheet1", T_tbl_col, T_tbl_col_w, T_tbl_col_h);
    if (!Load_ok) {
	ShowMessage("Load target data fail!");
	return;
    }
    for (int i = 0; i < total_len; i++)
	for (int j = 0; j < 3; j++) {
	    T_tbl_xyY[i][j] = T_tbl_col[i][j + 4];
	}
    for (int i = 0; i < T_tbl_col_h; i++)
	delete[]T_tbl_col[i];
    delete[]T_tbl_col;

    btn_Auto_Trg_BuildTbl->Enabled = true;
}

//---------------------------------------------------------------------------

void TC3DForm1::c3d_lutAssign()
{
    int idx = 0;
    for (int k = 0; k < TBL_SIZE; k += 2)
	for (int j = 0; j < TBL_SIZE; j += 2)
	    for (int i = 0; i < TBL_SIZE; i += 2) {
		c3d_lutR[i][j][k] = Tbl_RGB[idx][0];
		c3d_lutG[i][j][k] = Tbl_RGB[idx][1];
		c3d_lutB[i][j][k] = Tbl_RGB[idx][2];
		idx++;
	    }

    for (int k = 0; k < TBL_SIZE; k += 2)
	for (int j = 0; j < TBL_SIZE; j += 2)
	    for (int i = 1; i < TBL_SIZE - 1; i += 2) {
		c3d_lutR[i][j][k] = Tbl_RGB[idx][0];
		c3d_lutG[i][j][k] = Tbl_RGB[idx][1];
		c3d_lutB[i][j][k] = Tbl_RGB[idx][2];
		idx++;
	    }

    for (int k = 0; k < TBL_SIZE; k += 2)
	for (int j = 1; j < TBL_SIZE - 1; j += 2)
	    for (int i = 0; i < TBL_SIZE; i += 2) {
		c3d_lutR[i][j][k] = Tbl_RGB[idx][0];
		c3d_lutG[i][j][k] = Tbl_RGB[idx][1];
		c3d_lutB[i][j][k] = Tbl_RGB[idx][2];
		idx++;
	    }

    for (int k = 0; k < TBL_SIZE; k += 2)
	for (int j = 1; j < TBL_SIZE - 1; j += 2)
	    for (int i = 1; i < TBL_SIZE - 1; i += 2) {
		c3d_lutR[i][j][k] = Tbl_RGB[idx][0];
		c3d_lutG[i][j][k] = Tbl_RGB[idx][1];
		c3d_lutB[i][j][k] = Tbl_RGB[idx][2];
		idx++;
	    }

    for (int k = 1; k < TBL_SIZE - 1; k += 2)
	for (int j = 0; j < TBL_SIZE; j += 2)
	    for (int i = 0; i < TBL_SIZE; i += 2) {
		c3d_lutR[i][j][k] = Tbl_RGB[idx][0];
		c3d_lutG[i][j][k] = Tbl_RGB[idx][1];
		c3d_lutB[i][j][k] = Tbl_RGB[idx][2];
		idx++;
	    }

    for (int k = 1; k < TBL_SIZE - 1; k += 2)
	for (int j = 0; j < TBL_SIZE; j += 2)
	    for (int i = 1; i < TBL_SIZE - 1; i += 2) {
		c3d_lutR[i][j][k] = Tbl_RGB[idx][0];
		c3d_lutG[i][j][k] = Tbl_RGB[idx][1];
		c3d_lutB[i][j][k] = Tbl_RGB[idx][2];
		idx++;
	    }

    for (int k = 1; k < TBL_SIZE - 1; k += 2)
	for (int j = 1; j < TBL_SIZE - 1; j += 2)
	    for (int i = 0; i < TBL_SIZE; i += 2) {
		c3d_lutR[i][j][k] = Tbl_RGB[idx][0];
		c3d_lutG[i][j][k] = Tbl_RGB[idx][1];
		c3d_lutB[i][j][k] = Tbl_RGB[idx][2];
		idx++;
	    }

    for (int k = 1; k < TBL_SIZE - 1; k += 2)
	for (int j = 1; j < TBL_SIZE - 1; j += 2)
	    for (int i = 1; i < TBL_SIZE - 0; i += 2) {
		c3d_lutR[i][j][k] = Tbl_RGB[idx][0];
		c3d_lutG[i][j][k] = Tbl_RGB[idx][1];
		c3d_lutB[i][j][k] = Tbl_RGB[idx][2];
		idx++;
	    }
}

void Load_c3d_xls_table(String Fpath)
{
    int xls_f_w = 7, xls_f_h;
    int Tbl_RGB_w = 3, Tbl_RGB_h;
    if (TBL_SIZE == 9) {
	xls_f_h = 729;
	Tbl_RGB_h = 729;
    } else if (TBL_SIZE == 7) {
	xls_f_h = 343;
	Tbl_RGB_h = 343;
    }
    double **xls_f = new double *[xls_f_h];
    for (int i = 0; i < xls_f_h; i++)
	xls_f[i] = new double[xls_f_w];

    bool Load_ok;
    if (TBL_SIZE == 9)
	Load_ok = Load_XlsFile(Fpath, "9x9x9", xls_f, xls_f_w, xls_f_h);
    else if (TBL_SIZE == 7)
	Load_ok = Load_XlsFile(Fpath, "7x7x7", xls_f, xls_f_w, xls_f_h);
    if (!Load_ok) {
	ShowMessage("Load target data fail!");
	return;
    }

    Tbl_RGB = new double *[Tbl_RGB_h];
    for (int i = 0; i < Tbl_RGB_h; i++)
	Tbl_RGB[i] = new double[Tbl_RGB_w];

    for (int i = 0; i < Tbl_RGB_h; i++)
	for (int j = 0; j < 3; j++)
	    Tbl_RGB[i][j] = xls_f[i][j + 4] / Ratio;
    C3DForm1->c3d_lutAssign();

    for (int i = 0; i < Tbl_RGB_h; i++) {
	delete[]Tbl_RGB[i];
	delete[]xls_f[i];
    }
    delete[]Tbl_RGB;
    delete[]xls_f;
}


void __fastcall TC3DForm1::btn_c3d_load_rgbClick(TObject * Sender)
{
    if (!OpenDialog1->Execute())
	return;
    String Fpath = OpenDialog1->FileName;
    AnsiString curExt = LowerCase(ExtractFileExt(Fpath));

    if (curExt == ".txt") {
	Load_c3d_table(Fpath);
    } else if (curExt == ".xls") {
	Load_c3d_xls_table(Fpath);	// only 9*9*9
    }

    for (int i = 0; i < TBL_SIZE; i++)
	for (int j = 0; j < TBL_SIZE; j++)
	    for (int k = 0; k < TBL_SIZE; k++) {
		rgb2hsv(c3d_lutR[i][j][k], c3d_lutG[i][j][k], c3d_lutB[i][j][k],
			&c3d_lutH[i][j][k], &c3d_lutS[i][j][k], &c3d_lutI[i][j][k],
			&c3d_lutV[i][j][k]);

		tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
		tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
		tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
	    }

    if (TBL_SIZE == 9)
	Refresh_Manual39_Point();
}
void __fastcall TC3DForm1::btn_Auto_Trg_BuildTblClick(TObject * Sender)
{
    double **T_tbl_XYZ, **T_tblm0_XYZ;

    Tbl_RGB = new double *[total_len];
    T_tbl_XYZ = new double *[total_len];
    T_tblm0_XYZ = new double *[total_len];

    for (int i = 0; i < total_len; i++) {
	T_tbl_XYZ[i] = new double[3];
	T_tblm0_XYZ[i] = new double[3];
	Tbl_RGB[i] = new double[3];
    }

    double Nrml_W255_Y, Nrml_W0_XYZ[3];

    if (rg_normal_target->ItemIndex == 1) {	//Use Source data to Normalize Target
	Nrml_W255_Y = W255_xyY[2];
	Nrml_W0_XYZ[0] = W0_XYZ[0];
	Nrml_W0_XYZ[1] = W0_XYZ[1];
	Nrml_W0_XYZ[2] = W0_XYZ[2];
    } else if (rg_normal_target->ItemIndex == 0) {	//Use Target data to Normalize Target
	xyY2XYZ(T_tbl_xyY[0], Nrml_W0_XYZ);
	if (TBL_SIZE == 9 || TBL_SIZE == 7)
	    Nrml_W255_Y = T_tbl_xyY[124][2];	//Target W255 Y
	else if (TBL_SIZE == 17)
	    Nrml_W255_Y = T_tbl_xyY[728][2];	//Target W255 Y
	// For table 7 or table 9, W0 is at index 0, W255 at index 124
    }

    double Mtrx_rgb2xyz[3][3] = { 0 }, Mtrx_xyz2rgb[3][3] = {
    0};
    double Gamma_R = StrToFloat(lble_auto_Gm_R->Text);
    double Gamma_G = StrToFloat(lble_auto_Gm_G->Text);
    double Gamma_B = StrToFloat(lble_auto_Gm_B->Text);

    // 提取介面上的Color Model數值(M)
    Mtrx_rgb2xyz[0][0] = StrToFloat(edt_auto_rgb2xyz11->Text);
    Mtrx_rgb2xyz[0][1] = StrToFloat(edt_auto_rgb2xyz12->Text);
    Mtrx_rgb2xyz[0][2] = StrToFloat(edt_auto_rgb2xyz13->Text);

    Mtrx_rgb2xyz[1][0] = StrToFloat(edt_auto_rgb2xyz21->Text);
    Mtrx_rgb2xyz[1][1] = StrToFloat(edt_auto_rgb2xyz22->Text);
    Mtrx_rgb2xyz[1][2] = StrToFloat(edt_auto_rgb2xyz23->Text);

    Mtrx_rgb2xyz[2][0] = StrToFloat(edt_auto_rgb2xyz31->Text);
    Mtrx_rgb2xyz[2][1] = StrToFloat(edt_auto_rgb2xyz32->Text);
    Mtrx_rgb2xyz[2][2] = StrToFloat(edt_auto_rgb2xyz33->Text);

    Inverse_3matrix(Mtrx_rgb2xyz, Mtrx_xyz2rgb);

    for (int i = 0; i < total_len; i++) {
	//*縮減色域的地方*//
	xyY2XYZ(T_tbl_xyY[i], T_tbl_XYZ[i]);
	Normal_XYZ(T_tbl_XYZ[i], Nrml_W255_Y, Nrml_W0_XYZ, T_tblm0_XYZ[i]);

	//T_tbl_XYZ[i] - W0_XYZ
	// Normalize 的結果可能小於零(量測誤差or兩片最暗色不同) !!
	if (T_tblm0_XYZ[i][0] < 0)
	    T_tblm0_XYZ[i][0] = 0.0;
	if (T_tblm0_XYZ[i][1] < 0)
	    T_tblm0_XYZ[i][1] = 0.0;
	if (T_tblm0_XYZ[i][2] < 0)
	    T_tblm0_XYZ[i][2] = 0.0;

	for (int j = 0; j < 3; j++) {
	    Tbl_RGB[i][j] =
		Mtrx_xyz2rgb[j][0] * T_tblm0_XYZ[i][0] + Mtrx_xyz2rgb[j][1] * T_tblm0_XYZ[i][1]
		+ Mtrx_xyz2rgb[j][2] * T_tblm0_XYZ[i][2];

	    if (Tbl_RGB[i][j] < 0)
		Tbl_RGB[i][j] = 0;
	    else if (Tbl_RGB[i][j] > 1)
		Tbl_RGB[i][j] = 1;
	}

	Tbl_RGB[i][0] = pow(Tbl_RGB[i][0], 1.0 / Gamma_R) * 255;
	Tbl_RGB[i][1] = pow(Tbl_RGB[i][1], 1.0 / Gamma_G) * 255;
	Tbl_RGB[i][2] = pow(Tbl_RGB[i][2], 1.0 / Gamma_B) * 255;
    }
    // 整理到c3d_lutR
    c3d_lutAssign();

    for (int i = 0; i < TBL_SIZE; i++)
	for (int j = 0; j < TBL_SIZE; j++)
	    for (int k = 0; k < TBL_SIZE; k++) {
		tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
		tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
		tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
	    }
    for (int i = 0; i < total_len; i++) {
	delete[]Tbl_RGB[i];
	delete[]T_tbl_xyY[i];
	delete[]T_tbl_XYZ[i];
	delete[]T_tblm0_XYZ[i];
    }
    delete[]T_tbl_xyY;
    delete[]Tbl_RGB;
    delete[]T_tbl_XYZ;
    delete[]T_tblm0_XYZ;

    btn_Auto_Trg_BuildTbl->Enabled = false;
}

//---------------------------------------------------------------------------


void __fastcall TC3DForm1::SaveDialog1TypeChange(TObject * Sender)
{
    if (SaveDialog1->FilterIndex == 1)
	SaveDialog1->FileName = ".xls";
    else if (SaveDialog1->FilterIndex == 2)
	SaveDialog1->FileName = ".txt";
}

//---------------------------------------------------------------------------

