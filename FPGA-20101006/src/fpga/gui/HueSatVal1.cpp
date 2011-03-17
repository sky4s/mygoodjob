//---------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////
//        20100608
//     table Hue 10 bit/ Saturation 7 bit/ Value 7 bit
//     Total 24 bit, 24 set of HSV
//     hue: 0=>0, 768 => 360; Saturation: 0=>0, 32=>1, 64=>2, 96=>3, 128=>4
//     value: -64~+63, use 2's complement
//////////////////////////////////////////////////////////////////////////////

#include <vcl.h>
#include <lib/CMSCpp2.1/src/includeall.h>
#pragma hdrstop

#include "HueSatVal1.h"
#include "include.h"
#include <fpga/11307/ImageProcess/ImgProc_11307.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//THSVForm1 *HSVForm1;
bool HSV_IsChkSum = 0;
int tbl_step = 360 / 24;
//---------------------------------------------------------------------------
__fastcall THSVFormOrg::THSVFormOrg(TComponent * Owner)
:TForm(Owner)
{
    HSV_Chg = 0;
    HSVEN_idx = -1;
}

//---------------------------------------------------------------------------
void __fastcall THSVFormOrg::CheckBox_Click(TObject * Sender)
{
    if (HSV_Chg == 0)
	return;
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (ChkB[idx]->Chkb->Checked ? 1 : 0);
    EngineerForm->SetWrite_Byte(ChkB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------

void __fastcall THSVFormOrg::FormCreate(TObject * Sender)
{
    HSV_Chg = 0;
    int ic_choice;
    if (MainForm->TCON_DEV == "11307")
	ic_choice = 0;

    switch (ic_choice) {
    case 0:
	OHSV = new HSV_11307;
	break;
    }

    lut_addr = OHSV->SetLUT();

    cb = OHSV->SetChkBx();
    ChkB = new _CHKB *[OHSV->HSVChkBox_Nbr];
    for (int i = 0; i < OHSV->HSVChkBox_Nbr; i++)
	ChkB[i] = new _CHKB;

    ChkB[0]->Chkb = CheckBox1;
    ChkB[1]->Chkb = CheckBox2;
    ChkB[2]->Chkb = CheckBox3;
    ChkB[3]->Chkb = CheckBox4;

    for (int i = 0; i < OHSV->HSVChkBox_Nbr; i++) {
	ChkB[i]->Addr = cb[i];
	ChkB[i]->Chkb->Visible = ChkB[i]->Addr.FuncEn();
	ChkB[i]->Chkb->OnClick = CheckBox_Click;
	ChkB[i]->Chkb->Hint = i;
	ChkB[i]->Chkb->Caption = ChkB[i]->Addr.Name();
	// find index for HSV enable
	if (ChkB[i]->Addr.Name() == OHSV->HSV_EN_Name())	// 20100608 Find HSV enable index
	    HSVEN_idx = i;
    }
    // 20100608 check HSV enable index
    if (HSVEN_idx == -1)
	ShowMessage("Can't Get HSV enable index.");
    Initial_HSV_table();	// initial HSV table
    HSV_Chg = 1;
}

//---------------------------------------------------------------------------

void __fastcall THSVFormOrg::FormClose(TObject * Sender, TCloseAction & Action)
{
    delete[]OHSV;
    delete[]cb;
    delete[]ChkB;
    delete[]lut_addr;

    Action = caFree;
    MainForm->HSVFormNULL();
}

//---------------------------------------------------------------------------

void THSVFormOrg::Initial_HSV_table()
{
    //initial table setting
    for (int i = 0; i < 24; i++) {
	Hue_table[i] = i * 768 / 24;
	Sat_table[i] = 32;
	Val_table[i] = 0;
	Hue_table_t[i] = i * 768 / 24;
	Sat_table_t[i] = 32;
	Val_table_t[i] = 0;

	sg_HSV->Cells[0][i + 1] = IntToStr(360 / 24 * i) + "°";	// Index as hue
	sg_HSV->Cells[1][i + 1] = IntToStr(360 / 24 * i);	// Hue default value
	sg_HSV->Cells[2][i + 1] = 1;	// Saturation default value
	sg_HSV->Cells[3][i + 1] = 0;	// Luminance default value
    }

    sg_HSV->Cells[1][0] = "Hue";
    sg_HSV->Cells[2][0] = "Sat";
    sg_HSV->Cells[3][0] = "Val";
    sg_HSV->Cells[0][1] = "R 0°";
    sg_HSV->Cells[0][5] = "Y 60°";
    sg_HSV->Cells[0][9] = "G120°";
    sg_HSV->Cells[0][13] = "C180°";
    sg_HSV->Cells[0][17] = "B240°";
    sg_HSV->Cells[0][21] = "M300°";

    for (int i = 0; i < 6; i++) {
	sg_6HSV->Cells[0][i] = 360 / 6 * i;
	sg_6HSV->Cells[1][i] = 1;
	sg_6HSV->Cells[2][i] = 0;
    }
    sg_6HSV->Cells[0][6] = 0;
    sg_6HSV->Cells[1][6] = 1;
    sg_6HSV->Cells[2][6] = 0;

    sb_Hue_gain->Position = 0;
    sb_Sat_gain->Position = 32;
    sb_Val_gain->Position = 0;
}

//---------------------------------------------------------------------------
/*
  從角度換算成grid裡的index
*/
int Get_select_idx(double angle)
{
    angle = fabs(angle);	//取絕對值, 型態為float

    if (angle > 360) {
	double frac_tmp, int_tmp;
	frac_tmp = modf(angle, &int_tmp);	//將tmp分成整數"int_tmp"與小數"frac_tmp"
	angle = (int) int_tmp % 360 + frac_tmp;
    }
    int tbl_idx = (int) floor((angle / tbl_step) + 0.5);	//取變動的Table值
    return tbl_idx;
}

//---------------------------------------------------------------------------

void THSVFormOrg::Reset_HSVshow()
{				// Set gain value relative to color choose
    int tbl_idx = Get_select_idx(StrToInt(le_ChAangle->Text));

    //Hue gain
    sb_Hue_gain->Position = 0;
    lb_Hue_gain->Caption = 0;
    // Saturation gain
    sb_Sat_gain->Position = (int) floor(StrToFloat(sg_HSV->Cells[2][tbl_idx + 1]) * 32);
    lb_Sat_gain->Caption = sg_HSV->Cells[2][tbl_idx + 1];
    // Value gain
    sb_Val_gain->Position = StrToInt(sg_HSV->Cells[3][tbl_idx + 1]);
    lb_Val_gain->Caption = sg_HSV->Cells[3][tbl_idx + 1];

    for (int i = 0; i < 3; i++) {
	sg_6HSV->Cells[i][0] = sg_HSV->Cells[i + 1][1];	//Red
	sg_6HSV->Cells[i][1] = sg_HSV->Cells[i + 1][5];	//Yellow
	sg_6HSV->Cells[i][2] = sg_HSV->Cells[i + 1][9];	//Green
	sg_6HSV->Cells[i][3] = sg_HSV->Cells[i + 1][13];	//Cyan
	sg_6HSV->Cells[i][4] = sg_HSV->Cells[i + 1][17];	//Blue
	sg_6HSV->Cells[i][5] = sg_HSV->Cells[i + 1][21];	//Magenta
	sg_6HSV->Cells[i][6] = sg_HSV->Cells[i + 1][tbl_idx + 1];
    }
}

//---------------------------------------------------------------------------
void __fastcall THSVFormOrg::cb_Hue_RedClick(TObject * Sender)
{				// 6 Color Adjust : Red
    if (cb_Hue_Red->Checked == true) {
	cb_Hue_Green->Checked = false;
	cb_Hue_Blue->Checked = false;
	cb_Hue_Cyan->Checked = false;
	cb_Hue_Mag->Checked = false;
	cb_Hue_Yellow->Checked = false;
	le_ChAangle->Text = 0;
	ed_Hue_Custom->Text = 0;
	Set_6HSV_grid();
    }
}

//---------------------------------------------------------------------------

void __fastcall THSVFormOrg::cb_Hue_YellowClick(TObject * Sender)
{				// 6 Color Adjust : Yellow
    if (cb_Hue_Yellow->Checked == true) {
	cb_Hue_Red->Checked = false;
	cb_Hue_Green->Checked = false;
	cb_Hue_Blue->Checked = false;
	cb_Hue_Cyan->Checked = false;
	cb_Hue_Mag->Checked = false;
	le_ChAangle->Text = 60;
	ed_Hue_Custom->Text = 60;
	Set_6HSV_grid();
    }
}

//---------------------------------------------------------------------------

void __fastcall THSVFormOrg::cb_Hue_GreenClick(TObject * Sender)
{				// 6 Color Adjust : Green
    if (cb_Hue_Green->Checked == true) {
	cb_Hue_Red->Checked = false;
	cb_Hue_Blue->Checked = false;
	cb_Hue_Cyan->Checked = false;
	cb_Hue_Mag->Checked = false;
	cb_Hue_Yellow->Checked = false;
	le_ChAangle->Text = 120;
	ed_Hue_Custom->Text = 120;
	Set_6HSV_grid();
    }
}

//---------------------------------------------------------------------------

void __fastcall THSVFormOrg::cb_Hue_BlueClick(TObject * Sender)
{				// 6 Color Adjust : Blue
    if (cb_Hue_Blue->Checked == true) {
	cb_Hue_Red->Checked = false;
	cb_Hue_Green->Checked = false;
	cb_Hue_Cyan->Checked = false;
	cb_Hue_Mag->Checked = false;
	cb_Hue_Yellow->Checked = false;
	le_ChAangle->Text = 240;
	ed_Hue_Custom->Text = 240;
	Set_6HSV_grid();
    }
}

//---------------------------------------------------------------------------

void __fastcall THSVFormOrg::cb_Hue_CyanClick(TObject * Sender)
{				// 6 Color Adjust : Cyan
    if (cb_Hue_Cyan->Checked == true) {
	cb_Hue_Red->Checked = false;
	cb_Hue_Green->Checked = false;
	cb_Hue_Blue->Checked = false;
	cb_Hue_Mag->Checked = false;
	cb_Hue_Yellow->Checked = false;
	le_ChAangle->Text = 180;
	ed_Hue_Custom->Text = 180;
	Set_6HSV_grid();
    }
}

//---------------------------------------------------------------------------

void __fastcall THSVFormOrg::cb_Hue_MagClick(TObject * Sender)
{				// 6 Color Adjust : Magenta
    if (cb_Hue_Mag->Checked == true) {
	cb_Hue_Red->Checked = false;
	cb_Hue_Green->Checked = false;
	cb_Hue_Blue->Checked = false;
	cb_Hue_Cyan->Checked = false;
	cb_Hue_Yellow->Checked = false;
	le_ChAangle->Text = 300;	//移動的角度為300
	ed_Hue_Custom->Text = 300;
	Set_6HSV_grid();
    }
}

//---------------------------------------------------------------------------
void THSVFormOrg::Set_6HSV_grid()
{
    le_ChAangle->Text = ed_Hue_Custom->Text;	//移動的角度
    String str = ed_Hue_Custom->Text;

    //判斷輸入的角度是否合法, type_ok = true(合法,皆為數字), type_ok = false(不合法)
    bool type_ok = true;
    if (str == "") {
	type_ok = false;
    } else {
	for (int i = 0; i < le_ChAangle->Text.Length(); i++) {
	    //逐字元比對, 是否為數字
	    if (!isdigit(*(le_ChAangle->Text.c_str() + i))) {
		type_ok = false;
		break;
	    }
	}
    }

    if (type_ok == false) {	//輸入角度不合法
	sg_6HSV->Cells[0][6] = "";
	sg_6HSV->Cells[1][6] = "";
	sg_6HSV->Cells[2][6] = "";
	return;
    }
    //輸入角度合法

    int tbl_idx = Get_select_idx(StrToFloat(le_ChAangle->Text));
    //選擇變動的HSV值
    sg_6HSV->Cells[0][6] = sg_HSV->Cells[1][tbl_idx + 1];
    sg_6HSV->Cells[1][6] = sg_HSV->Cells[2][tbl_idx + 1];
    sg_6HSV->Cells[2][6] = sg_HSV->Cells[3][tbl_idx + 1];
    Reset_HSVshow();
}

void __fastcall THSVFormOrg::ed_Hue_CustomChange(TObject * Sender)
{
    Set_6HSV_grid();
}

//---------------------------------------------------------------------------

void THSVFormOrg::Hue_LUTWrite()
{
    HSV_LUT_FuncEnable(0);	// Table operation button disable
    bool ok = HSV_LUT_RW_start();	// Record the state of HSV enable
    if (ok == 0) {		// Fail to record the state
	HSV_LUT_FuncEnable(1);	// Table operation button enable
	return;
    }

    for (int i = 0; i < 24; i++) {
	Hue_table[i] = (int) (StrToFloat(sg_HSV->Cells[1][i + 1]) / 360 * 768 + 0.5);
	Sat_table[i] = (int) (StrToFloat(sg_HSV->Cells[2][i + 1]) * 32);
	Val_table[i] = StrToInt(sg_HSV->Cells[3][i + 1]);
    }

    int *HSV_lut = new int[24 * 3];
    int val_w;
    for (int i = 0; i < 24; i++) {
	Hue_table[i] = Hue_table[i] % 1024;	// 10 bit
	Sat_table[i] = Sat_table[i] % 128;	// 7 bit
	val_w = SignToCmplmnt2s(Val_table[i], 128);
	val_w = val_w % 128;	// 7 bit

	HSV_lut[i * 3] = Hue_table[i] / 4;
	HSV_lut[i * 3 + 1] = Hue_table[i] % 4 * 64 + Sat_table[i] / 2;
	HSV_lut[i * 3 + 2] = Sat_table[i] % 2 * 128 + val_w;
	// Modified only for AUO11307
	//HSV_lut[i*3+2] = Hue_table[i]/4;
	//HSV_lut[i*3+1] = Hue_table[i]%4*64 + Sat_table[i]/2;
	//HSV_lut[i*3] = Sat_table[i]%2*128 + val_w;
    }
    EngineerForm->SetWrite_PG(lut_addr[0], HSV_lut, HSV_IsChkSum);
    delete[]HSV_lut;

    HSV_LUT_RW_over();		// Recover HSV enable
    HSV_LUT_FuncEnable(1);	// Table operation button enable
}


//--------------------------------------------------------------------------

void __fastcall THSVFormOrg::btn_resetClick(TObject * Sender)
{
    Initial_HSV_table();
}

void THSVFormOrg::show_gain(int h, int s, int v)
{
    double h_show = ((double) h / 768) * 360;
    char str[6];
    sprintf(str, "%.2f", h_show);
    lb_Hue_gain->Caption = str;

    double s_show = (double) s / 32;
    sprintf(str, "%.2f", s_show);
    lb_Sat_gain->Caption = str;

    lb_Val_gain->Caption = IntToStr(v);
}
void THSVFormOrg::Get_Adj_tbl(int *tmp_H, int *tmp_S, int *tmp_V, int tbl_idx)
{
    for (int i = -4; i <= 4; i++) {
	tmp_H[i + 4] = Hue_table[(tbl_idx + i + 24) % 24];
	if (i > (-4) && (tmp_H[i + 4] < tmp_H[i + 3]))
	    tmp_H[i + 4] += 768;
	tmp_S[i + 4] = Sat_table[(tbl_idx + i + 24) % 24];
	tmp_V[i + 4] = Val_table[(tbl_idx + i + 24) % 24];
    }
}
void THSVFormOrg::Set_Adj_tbl(int *tmp_H, int *tmp_S, int *tmp_V, int tbl_idx)
{
    for (int i = -4; i <= 4; i++) {
	Hue_table_t[(tbl_idx + i + 24) % 24] = tmp_H[i + 4] % 768;
	Sat_table_t[(tbl_idx + i + 24) % 24] = tmp_S[i + 4];
	Val_table_t[(tbl_idx + i + 24) % 24] = tmp_V[i + 4];
    }
}

bool THSVFormOrg::CheckDif(int &high, int &low, int *tmp_H, int gain)
{
    //據給予的gain值找出適合的diffusion邊界值
    tmp_H[4] += gain;		// 調整值在index = 3
    while (tmp_H[4] > tmp_H[high + 4]) {
	if (high < 4)
	    high++;
	else {
	    ShowMessage("Hue increase too much!");
	    return 0;
	}
    }
    while (tmp_H[4] < tmp_H[4 - low]) {
	if (low < 4)
	    low++;
	else {
	    ShowMessage("Hue decrease too much!");
	    return 0;
	}
    }
    //low = (low > 3)?3:low;
    //high = (high > 3)?3:high;
    return 1;
}

bool THSVFormOrg::CheckHueIncrease(int high, int low, int *tmp_H)
{
    bool ok = true;
    for (int i = ((-1) * low + 4) + 2; i < high + 4 - 1; i++) {
	if (tmp_H[i - 1] - tmp_H[i] >= 0 && tmp_H[i - 1] - tmp_H[i] < 768 / 2) {
	    ok = false;
	}
    }
    return ok;
}
double Gauss(int x, double sigma)
{
    double ratio = exp(((-1) * x * x) / (2 * sigma * sigma));
    return ratio;
}

//---------------------------------------------------------------------------
void __fastcall THSVFormOrg::sb_Hue_gainScroll(TObject * Sender,
					       TScrollCode ScrollCode, int &ScrollPos)
{
    double sigma;
    if (ScrollCode != scEndScroll) {
	return;
    }
    int tbl_n = 24;
    for (int i = 0; i < tbl_n; i++) {
	Hue_table_t[i] = Hue_table[i];
	Sat_table_t[i] = Sat_table[i];
	Val_table_t[i] = Val_table[i];
    }

    //將使用者輸入的角度換成table表中的index
    int tbl_idx = Get_select_idx(StrToFloat(le_ChAangle->Text));

    show_gain(sb_Hue_gain->Position, sb_Sat_gain->Position, sb_Val_gain->Position);
    int gain_h = sb_Hue_gain->Position;	// Hue值為Gain
    int gain_s = sb_Sat_gain->Position - Sat_table[tbl_idx];	// 調整值與table數值的差異為gain
    int gain_v = sb_Val_gain->Position - Val_table[tbl_idx];
    if (gain_h > 768 / 2) {
	gain_h -= 768;
    } else if (gain_h < (-1) * 768 / 2) {
	gain_h += 768;
    }
    btn_set->Enabled = true;
    if (cb_Hue_rotation->Checked == false) {
	int tmp_H[9], tmp_S[9], tmp_V[9];
	Get_Adj_tbl(tmp_H, tmp_S, tmp_V, tbl_idx);

	int low = (4 - sb_dif_n->Position);
	int high = sb_dif_p->Position;

	bool dif_ok = CheckDif(high, low, tmp_H, gain_h);
	if (dif_ok == 0)
	    return;
	sb_dif_p->Position = high;
	sb_dif_n->Position = 4 - low;

	tmp_S[4] += gain_s;
	tmp_V[4] += gain_v;
	double ratio;

	if (high == 4)
	    sigma = 0.4;
	else if (high == 3)
	    sigma = 0.5;
	else if (high == 2)
	    sigma = 0.6;

	for (int i = 1; i < high; i++) {
	    ratio = pow(double (high - i) / high, 2) + (double) i / high * Gauss(i, sigma);
	    tmp_H[i + 4] = tmp_H[i + 4] + gain_h * ratio;
	    tmp_S[i + 4] = tmp_S[i + 4] + gain_s * ratio;
	    tmp_V[i + 4] = tmp_V[i + 4] + gain_v * ratio;
	}

	if (low == 4)
	    sigma = 0.4;
	else if (low == 3)
	    sigma = 0.5;
	else if (low == 2)
	    sigma = 0.6;

	for (int i = 1; i < low; i++) {
	    ratio = pow(double (low - i) / low, 2) + (double) i / low * Gauss(i, sigma);
	    tmp_H[4 - i] = tmp_H[4 - i] + gain_h * ratio;
	    tmp_S[4 - i] = tmp_S[4 - i] + gain_s * ratio;
	    tmp_V[4 - i] = tmp_V[4 - i] + gain_v * ratio;
	}
	Set_Adj_tbl(tmp_H, tmp_S, tmp_V, tbl_idx);
	if (!CheckHueIncrease(high, low, tmp_H)) {
	    ShowMessage("Hue value has inverse.");
	    btn_set->Enabled = false;
	    return;
	}
    } else {			//rotation
	for (int i = 0; i < tbl_n; i++) {
	    Hue_table_t[i] = (Hue_table[i] + gain_h + 768) % 768;
	    Sat_table_t[i] = Sat_table[i] + gain_s;
	    Val_table_t[i] = Val_table[i] + gain_v;
	}
    }

    for (int i = 0; i < tbl_n; i++) {
	sg_HSV->Cells[1][i + 1] = FloatToStr((double) Hue_table_t[i] / 768 * 360);
	sg_HSV->Cells[2][i + 1] = FloatToStr((double) (Sat_table_t[i]) / 32);
	sg_HSV->Cells[3][i + 1] = Val_table_t[i];
    }
    for (int i = 0; i < 3; i++) {
	sg_6HSV->Cells[i][0] = sg_HSV->Cells[i + 1][1];	//Red
	sg_6HSV->Cells[i][1] = sg_HSV->Cells[i + 1][5];	//Yellow
	sg_6HSV->Cells[i][2] = sg_HSV->Cells[i + 1][9];	//Green
	sg_6HSV->Cells[i][3] = sg_HSV->Cells[i + 1][13];	//Cyan
	sg_6HSV->Cells[i][4] = sg_HSV->Cells[i + 1][17];	//Blue
	sg_6HSV->Cells[i][5] = sg_HSV->Cells[i + 1][21];	//Magenta
	sg_6HSV->Cells[i][6] = sg_HSV->Cells[i + 1][tbl_idx + 1];
    }
}

//---------------------------------------------------------------------------


void __fastcall THSVFormOrg::btn_hsv_loadClick(TObject * Sender)
{
    if (!OpenDialog1->Execute())
	return;
    String Fpath;
    Fpath = OpenDialog1->FileName;

    Load_HSV(Fpath);
}

//---------------------------------------------------------------------------

bool THSVFormOrg::Load_HSV(String Fpath)
{
    if (Fpath == NULL)
	return 0;
    char *buffer = Load_File(Fpath);
    if (buffer == NULL)
	return 0;
    for (int i = 0; i < 96; i++) {
	Hue_table[i] = -1;
	Sat_table[i] = -1;
	Val_table[i] = 0;
    }

    //比對檔案中的Hue_LUT, Sat_LUT, Bri_LUT字串
    /*char* str[3];
       char* pch;
       str[0]="Hue_LUT";
       str[1]="Sat_LUT";
       str[2]="Bri_LUT";
       pch = strtok (buffer,"\n\t");
       for(int i = 0; i < 3; i++){
       while (memcmp(pch,str[i],7)!=0){
       if(pch == NULL){
       ShowMessage("Can't open Hue table file.");
       return 0;
       }
       pch = strtok (NULL,"\n\t");
       }
       } */

    //取出檔案中的數值
    int c = 0;
    char *pch;
    pch = strtok(buffer, "\n\t");
    int Length = lut_addr[0].LutNum();
    while (c < Length && pch != NULL) {
	if (pch == NULL) {
	    ShowMessage("Can't open Hue table file.");
	    return 0;		//資料中的data缺少
	}
	if (c % 3 == 0)
	    Hue_table[c / 3] = StrToInt((AnsiString) pch);
	else if (c % 3 == 1)
	    Sat_table[c / 3] = StrToInt((AnsiString) pch);
	else
	    Val_table[c / 3] = StrToInt((AnsiString) pch);
	pch = strtok(NULL, "\n\t");
	c++;
    }
    delete[]buffer;

    for (int i = 0; i < 24; i++) {
	sg_HSV->Cells[1][i + 1] = FloatToStr((double) Hue_table[i] / 768 * 360);
	sg_HSV->Cells[2][i + 1] = FloatToStr((double) (Sat_table[i]) / 32);
	sg_HSV->Cells[3][i + 1] = IntToStr(Val_table[i]);
    }

    Set_6HSV_grid();
    //Hue_LUTWrite();
    return 1;
}


//---------------------------------------------------------------------------

void __fastcall THSVFormOrg::btn_hsv_saveClick(TObject * Sender)
{
    if (!SaveDialog1->Execute())
	return;
    String Fpath = SaveDialog1->FileName /*+".txt" */ ;
    FILE *fptr = fopen(Fpath.c_str(), "w");

    //fprintf(fptr,"Hue_LUT\tSat_LUT\tBri_LUT\n");
    for (int i = 0; i < 24; i++) {
	fprintf(fptr, "%d\t%d\t%d\n", Hue_table[i], Sat_table[i], Val_table[i]);
    }

    fclose(fptr);
}

//---------------------------------------------------------------------------


void __fastcall THSVFormOrg::Hue_ImgMouseMove(TObject * Sender, TShiftState Shift, int X, int Y)
{
    int color;
    double h, s, v, i, r, g, b;
    color = Hue_Img->Canvas->Pixels[X][Y];

    b = color / 65536;
    g = color / 256 % 256;
    r = color % 256;

    rgb2hsv(r, g, b, &h, &s, &i, &v);
    i = (double) (int (i * 10)) /10.0;
    h = (double) (int (h * 10)) /10.0;
    s = (double) (int (s * 100)) /100.0;
    Hue_Img_Infor->Caption =
	"B:" + IntToStr((int) b) + " G:" + IntToStr((int) g) + " R:" + IntToStr((int) r) + " H:" +
	FloatToStr(h) + " S:" + FloatToStr(s) + " V:" + FloatToStr(v) + " I:" + FloatToStr(i);
}

//---------------------------------------------------------------------------

void __fastcall THSVFormOrg::btn_Hue_Img_loadClick(TObject * Sender)
{
    if (!OpenDialog1->Execute())
	return;
    String Fpath;
    //Hue_Img->Picture->LoadFromFile(Fpath);

    Fpath = OpenDialog1->FileName;
    Graphics::TBitmap * Bitmap;

    Graphics::TBitmap * RefGraph;
    RefGraph = new Graphics::TBitmap();
    RefGraph->Height = Hue_Img->Height;
    RefGraph->Width = Hue_Img->Width;
    RefGraph->LoadFromFile(Fpath);
    Hue_Img->Picture->Graphic = RefGraph;
//        Hue_Img->Canvas->Draw(0,0,RefGraph);
    delete RefGraph;

}

//---------------------------------------------------------------------------

void __fastcall THSVFormOrg::rg_HSV_ModeClick(TObject * Sender)
{
    String Fpath;

    if (rg_HSV_Mode->ItemIndex == 0)
	Fpath = "\HSV_default1.txt";
    else if (rg_HSV_Mode->ItemIndex == 1)
	Fpath = "\HSV_default2.txt";
    else if (rg_HSV_Mode->ItemIndex == 2)
	Fpath = "\HSV_default3.txt";

    btn_hsv_load->Enabled = false;
    btn_hsv_save->Enabled = false;
    rg_HSV_Mode->Enabled = false;
    if (!Load_HSV(Fpath)) {
	ShowMessage("Load File fail.");
    }
    btn_hsv_load->Enabled = true;
    btn_hsv_save->Enabled = true;
    rg_HSV_Mode->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall THSVFormOrg::Btn_HSV_reloadClick(TObject * Sender)
{
    Btn_HSV_reload->Enabled = false;
    HSV_LUT_FuncEnable(0);
    unsigned char read_val;
    for (int i = 0; i < OHSV->HSVChkBox_Nbr; i++) {
	if (ChkB[i]->Chkb->Visible == true) {
	    EngineerForm->SetRead_Byte(ChkB[i]->Addr, &read_val);
	    if (read_val == 1)
		ChkB[i]->Chkb->Checked = 1;
	    else if (read_val == 0)
		ChkB[i]->Chkb->Checked = 0;
	    else
		ShowMessage("HSV CheckBox read error:" + IntToStr(read_val));
	}
    }
    btn_hsv_readClick(Sender);
    HSV_LUT_FuncEnable(1);
    Btn_HSV_reload->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall THSVFormOrg::FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift)
{
    if (Key == 0x40) {
	Btn_HSV_reloadClick(Sender);
    }
}

//---------------------------------------------------------------------------





//---------------------------------------------------------------------------


void __fastcall THSVFormOrg::sb_dif_nChange(TObject * Sender)
{
    lb_dif_n->Caption = (4 - sb_dif_n->Position) * 15;
}

//---------------------------------------------------------------------------

void __fastcall THSVFormOrg::sb_dif_pChange(TObject * Sender)
{
    lb_dif_p->Caption = sb_dif_p->Position * 15;
}

//---------------------------------------------------------------------------



void __fastcall THSVFormOrg::btn_setClick(TObject * Sender)
{
    for (int i = 0; i < 24; i++) {
	Hue_table[i] = Hue_table_t[i];
	Sat_table[i] = Sat_table_t[i];
	Val_table[i] = Val_table_t[i];

	sg_HSV->Cells[1][i + 1] = FloatToStr((double) Hue_table_t[i] / 768 * 360);
	sg_HSV->Cells[2][i + 1] = FloatToStr((double) (Sat_table_t[i]) / 32);
	sg_HSV->Cells[3][i + 1] = Val_table_t[i];
    }
    btn_set->Enabled = false;
}

//---------------------------------------------------------------------------

void __fastcall THSVFormOrg::btn_hsv_writeClick(TObject * Sender)
{
    Hue_LUTWrite();
}

//---------------------------------------------------------------------------
// Recover the state of HSV enable
bool THSVFormOrg::HSV_LUT_RW_start()
{
    if (HSVEN_idx == -1) {
	ShowMessage("Unknown HSV enabled index.");
	return 0;
    }

    unsigned char set_val;
    bool ok = EngineerForm->SetRead_Byte(ChkB[HSVEN_idx]->Addr, &set_val);
    if (ok == 0) {
	ShowMessage("read enable fail.");
	return 0;
    }
    HSV_EN_State = (set_val > 0 ? 1 : 0);
    ChkB[HSVEN_idx]->Chkb->Checked = false;
    EngineerForm->SetWrite_Byte(ChkB[HSVEN_idx]->Addr, 0);
    return 1;
}

//---------------------------------------------------------------------------

// Recover the state of HSV disable
void THSVFormOrg::HSV_LUT_RW_over()
{
    // reload en state
    int set_val = (HSV_EN_State == false ? 0 : 1);
    ChkB[HSVEN_idx]->Chkb->Checked = HSV_EN_State;
    EngineerForm->SetWrite_Byte(ChkB[HSVEN_idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void THSVFormOrg::HSV_LUT_FuncEnable(bool flag_en)
{
    if (flag_en == true) {	// Table operation button enable
	btn_hsv_read->Enabled = true;
	btn_hsv_write->Enabled = true;
	btn_hsv_save->Enabled = true;
	btn_hsv_load->Enabled = true;
    } else {			// Table operation button disable
	btn_hsv_read->Enabled = false;
	btn_hsv_write->Enabled = false;
	btn_hsv_save->Enabled = false;
	btn_hsv_load->Enabled = false;
    }
}

void __fastcall THSVFormOrg::btn_hsv_readClick(TObject * Sender)
{

    bool ok = HSV_LUT_RW_start();	// Record the state of HSV enable
    if (ok == 0) {		// Fail to record the state
	HSV_LUT_FuncEnable(1);	// Table operation button enable
	return;
    }
    HSV_LUT_FuncEnable(0);	// Table operation button disable

    int HSV_lut_tmp[24 * 3 + 2];	//add
    int HSV_lut[24 * 3];

    if (!EngineerForm->SetRead_PG(lut_addr[0], HSV_lut_tmp, HSV_IsChkSum)) {
	ShowMessage("Hue page read fail.");
	return;
    }

    for (int i = 0; i < 24 * 3; i++) {	//add
	HSV_lut[i] = HSV_lut_tmp[i];	//add
    }

    EngineerForm->SetWrite_Byte(en.Addr, HSV_EN_State);

    int val_r;
    for (int i = 0; i < 24; i++) {
	Hue_table[i] = HSV_lut[i * 3] * 4 + (HSV_lut[i * 3 + 1] / 64) % 4;
	Sat_table[i] = (HSV_lut[i * 3 + 1] % 64) * 2 + (HSV_lut[i * 3 + 2] / 128) % 2;
	val_r = HSV_lut[i * 3 + 2] % 128;
	// Modified only for AUO11307
	//Hue_table[i] = HSV_lut[i*3+2]*4 + (HSV_lut[i*3+1]/64)%4;
	//Sat_table[i] = (HSV_lut[i*3+1]%64)*2 + (HSV_lut[i*3]/128)%2;
	//val_r = HSV_lut[i*3]%128;

	Val_table[i] = Cmplmnt2sToSign(val_r, 128);

	sg_HSV->Cells[1][i + 1] = FloatToStr((double) Hue_table[i] / 768 * 360);
	sg_HSV->Cells[2][i + 1] = FloatToStr((double) (Sat_table[i]) / 32);
	sg_HSV->Cells[3][i + 1] = IntToStr(Val_table[i]);
    }
    Set_6HSV_grid();
    HSV_LUT_RW_over();		// Recover HSV enable
    HSV_LUT_FuncEnable(1);	// Table operation button enable
}

//---------------------------------------------------------------------------



void __fastcall THSVFormOrg::Hue_ImgMouseDown(TObject * Sender,
					      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    int color;
    double h, s, v, i, r, g, b;
    color = Hue_Img->Canvas->Pixels[X][Y];

    b = color / 65536;
    g = color / 256 % 256;
    r = color % 256;

    rgb2hsv(r, g, b, &h, &s, &i, &v);
    ed_Hue_Custom->Text = FloatToStr(h);
    Set_6HSV_grid();
}

//---------------------------------------------------------------------------

