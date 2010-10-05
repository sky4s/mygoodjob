//---------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////
//        20100608
//     table Hue 10 bit/ Saturation 7 bit/ Value 7 bit
//     Total 24 bit, 24 set of HSV
//     hue: 0=>0, 768 => 360; Saturation: 0=>0, 32=>1, 64=>2, 96=>3, 128=>4
//     value: -64~+63, use 2's complement
//////////////////////////////////////////////////////////////////////////////

#include <vcl.h>
#include <includeall.h>
#pragma hdrstop

#include "THSVForm3.h"
#include <fpga/11307/ImageProcess/ImgProc_11307.h>
#include "Engineering.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TColorPickerFrame"
#pragma link "THSVAdjustFrame"
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall THSVForm3::THSVForm3(TComponent * Owner)
:TForm(Owner), HSV_IsChkSum(0), tbl_step(360. / 24)
{
    HSV_Chg = 0;
    HSVEN_idx = -1;
}

//---------------------------------------------------------------------------
void __fastcall THSVForm3::CheckBox_Click(TObject * Sender)
{
    if (HSV_Chg == 0)
	return;
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (ChkB[idx]->Chkb->Checked ? 1 : 0);
    EngineerForm->SetWrite_Byte(ChkB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::FormCreate(TObject * Sender)
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

    this->initStringGrid_HSV();
    //hsvAdjust->setHSV(0, 1, 0);

}


void THSVForm3::initGroupBoxBase(TGroupBox * groupBox_base)
{
    int count = groupBox_base->ControlCount;
    for (int x = 0; x < count; x++) {
	TRadioButton *b =
	    dynamic_cast < TRadioButton * >(groupBox_base->Controls[x]);
	if (null != b) {
	    int row = hintToRow(b->Hint.ToInt()) - 1;
	    b->Color = getHueRGB(row)->getColor();
	}
    }
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::FormClose(TObject * Sender,
				     TCloseAction & Action)
{
    delete[]OHSV;
    delete[]cb;
    delete[]ChkB;
    delete[]lut_addr;

    Action = caFree;
    MainForm->HSVFormNULL();
}

//---------------------------------------------------------------------------

void THSVForm3::Initial_HSV_table()
{
    //initial table setting
    for (int i = 0; i < HUE_COUNT; i++) {
	Hue_table[i] = i * 768 / HUE_COUNT;
	Sat_table[i] = 32;
	Val_table[i] = 0;
	Hue_table_t[i] = i * 768 / HUE_COUNT;
	Sat_table_t[i] = 32;
	Val_table_t[i] = 0;
    }

    hsvAdjust->sb_Hue_gain->Position = 0;
    hsvAdjust->sb_Sat_gain->Position = 32;
    hsvAdjust->sb_Val_gain->Position = 0;
}


//---------------------------------------------------------------------------

void THSVForm3::Reset_HSVshow()
{				// Set gain value relative to color choose
    //int tbl_idx = Get_select_idx(StrToInt(le_ChAangle->Text));
    //int tbl_idx = stringGrid_HSV->Selection.Top - 1;
    int tbl_idx = stringGrid_HSV->Selection.Top;

    //Hue gain
    hsvAdjust->sb_Hue_gain->Position = 0;
    hsvAdjust->lb_Hue_gain->Caption = 0;
    // Saturation gain
    hsvAdjust->sb_Sat_gain->Position =
	(int) floor(StrToFloat(stringGrid_HSV->Cells[2][tbl_idx]) * 32);
    hsvAdjust->lb_Sat_gain->Caption = stringGrid_HSV->Cells[2][tbl_idx];
    // Value gain
    hsvAdjust->sb_Val_gain->Position =
	StrToInt(stringGrid_HSV->Cells[3][tbl_idx]);
    hsvAdjust->lb_Val_gain->Caption = stringGrid_HSV->Cells[3][tbl_idx];

}

//---------------------------------------------------------------------------
void __fastcall THSVForm3::cb_Hue_RedClick(TObject * Sender)
{				// 6 Color Adjust : Red
    if (cb_Hue_Red->Checked == true) {
	cb_Hue_Green->Checked = false;
	cb_Hue_Blue->Checked = false;
	cb_Hue_Cyan->Checked = false;
	cb_Hue_Mag->Checked = false;
	cb_Hue_Yellow->Checked = false;
	//le_ChAangle->Text = 0;
	ed_Hue_Custom->Text = 0;
    }
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::cb_Hue_YellowClick(TObject * Sender)
{				// 6 Color Adjust : Yellow
    if (cb_Hue_Yellow->Checked == true) {
	cb_Hue_Red->Checked = false;
	cb_Hue_Green->Checked = false;
	cb_Hue_Blue->Checked = false;
	cb_Hue_Cyan->Checked = false;
	cb_Hue_Mag->Checked = false;
	//le_ChAangle->Text = 60;
	ed_Hue_Custom->Text = 60;
    }
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::cb_Hue_GreenClick(TObject * Sender)
{				// 6 Color Adjust : Green
    if (cb_Hue_Green->Checked == true) {
	cb_Hue_Red->Checked = false;
	cb_Hue_Blue->Checked = false;
	cb_Hue_Cyan->Checked = false;
	cb_Hue_Mag->Checked = false;
	cb_Hue_Yellow->Checked = false;
	//le_ChAangle->Text = 120;
	ed_Hue_Custom->Text = 120;
    }
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::cb_Hue_BlueClick(TObject * Sender)
{				// 6 Color Adjust : Blue
    if (cb_Hue_Blue->Checked == true) {
	cb_Hue_Red->Checked = false;
	cb_Hue_Green->Checked = false;
	cb_Hue_Cyan->Checked = false;
	cb_Hue_Mag->Checked = false;
	cb_Hue_Yellow->Checked = false;
	//le_ChAangle->Text = 240;
	ed_Hue_Custom->Text = 240;
    }
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::cb_Hue_CyanClick(TObject * Sender)
{				// 6 Color Adjust : Cyan
    if (cb_Hue_Cyan->Checked == true) {
	cb_Hue_Red->Checked = false;
	cb_Hue_Green->Checked = false;
	cb_Hue_Blue->Checked = false;
	cb_Hue_Mag->Checked = false;
	cb_Hue_Yellow->Checked = false;
	//le_ChAangle->Text = 180;
	ed_Hue_Custom->Text = 180;
    }
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::cb_Hue_MagClick(TObject * Sender)
{				// 6 Color Adjust : Magenta
    if (cb_Hue_Mag->Checked == true) {
	cb_Hue_Red->Checked = false;
	cb_Hue_Green->Checked = false;
	cb_Hue_Blue->Checked = false;
	cb_Hue_Cyan->Checked = false;
	cb_Hue_Yellow->Checked = false;
	//le_ChAangle->Text = 300;      //移動的角度為300
	ed_Hue_Custom->Text = 300;
    }
}



//---------------------------------------------------------------------------

void THSVForm3::Hue_LUTWrite()
{
    HSV_LUT_FuncEnable(0);	// Table operation button disable
    bool ok = HSV_LUT_RW_start();	// Record the state of HSV enable
    if (ok == 0) {		// Fail to record the state
	HSV_LUT_FuncEnable(1);	// Table operation button enable
	return;
    }

    for (int i = 0; i < 24; i++) {
	Hue_table[i] =
	    (int) (StrToFloat(stringGrid_HSV->Cells[1][i + 1]) / 360 *
		   768 + 0.5);
	Sat_table[i] =
	    (int) (StrToFloat(stringGrid_HSV->Cells[2][i + 1]) * 32);
	Val_table[i] = StrToInt(stringGrid_HSV->Cells[3][i + 1]);
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

    }
    EngineerForm->SetWrite_PG(lut_addr[0], HSV_lut, HSV_IsChkSum);
    delete[]HSV_lut;

    HSV_LUT_RW_over();		// Recover HSV enable
    HSV_LUT_FuncEnable(1);	// Table operation button enable
}


//--------------------------------------------------------------------------

void __fastcall THSVForm3::btn_resetClick(TObject * Sender)
{
    Initial_HSV_table();
}

void THSVForm3::show_gain(int h, int s, int v)
{
    double h_show = ((double) h / 768) * 360;
    hsvAdjust->lb_Hue_gain->Caption =
	hsvAdjust->lb_Hue_gain->Caption.sprintf("%.2f", h_show);

    double s_show = (double) s / 32;
    hsvAdjust->lb_Sat_gain->Caption =
	hsvAdjust->lb_Sat_gain->Caption.sprintf("%.2f", s_show);

    hsvAdjust->lb_Val_gain->Caption = IntToStr(v);
}
void THSVForm3::Get_Adj_tbl(int *tmp_H, int *tmp_S, int *tmp_V,
			    int tbl_idx)
{
    for (int i = -4; i <= 4; i++) {
	tmp_H[i + 4] = Hue_table[(tbl_idx + i + 24) % 24];
	if (i > (-4) && (tmp_H[i + 4] < tmp_H[i + 3]))
	    tmp_H[i + 4] += 768;
	tmp_S[i + 4] = Sat_table[(tbl_idx + i + 24) % 24];
	tmp_V[i + 4] = Val_table[(tbl_idx + i + 24) % 24];
    }
}
void THSVForm3::Set_Adj_tbl(int *tmp_H, int *tmp_S, int *tmp_V,
			    int tbl_idx)
{
    for (int i = -4; i <= 4; i++) {
	Hue_table_t[(tbl_idx + i + 24) % 24] = tmp_H[i + 4] % 768;
	Sat_table_t[(tbl_idx + i + 24) % 24] = tmp_S[i + 4];
	Val_table_t[(tbl_idx + i + 24) % 24] = tmp_V[i + 4];
    }
}

bool THSVForm3::CheckDif(int &high, int &low, int *tmp_H, int gain)
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

    return 1;
}

bool THSVForm3::CheckHueIncrease(int high, int low, int *tmp_H)
{
    bool ok = true;
    for (int i = ((-1) * low + 4) + 2; i < high + 4 - 1; i++) {
	if (tmp_H[i - 1] - tmp_H[i] >= 0
	    && tmp_H[i - 1] - tmp_H[i] < 768 / 2) {
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
void __fastcall THSVForm3::sb_Hue_gainScroll(TObject * Sender,
					     TScrollCode ScrollCode,
					     int &ScrollPos)
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
    //le_ChAangle看不見, 就是目前選的角度
    int tbl_idx = Get_select_idx(StrToFloat(le_ChAangle->Text));

    //更新
    show_gain(sb_Hue_gain->Position, sb_Sat_gain->Position,
	      sb_Val_gain->Position);
    int gain_h = sb_Hue_gain->Position;	// Hue值為Gain
    int gain_s = sb_Sat_gain->Position - Sat_table[tbl_idx];	// 調整值與table數值的差異為gain
    int gain_v = sb_Val_gain->Position - Val_table[tbl_idx];
    if (gain_h > 768 / 2) {
	gain_h -= 768;
    } else if (gain_h < (-1) * 768 / 2) {
	gain_h += 768;
    }
    //可以做set
    btn_set->Enabled = true;
    if (cb_Hue_rotation->Checked == false) {
	//非全域調整
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
	    ratio =
		pow(double (high - i) / high,
		    2) + (double) i / high * Gauss(i, sigma);
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
	    ratio =
		pow(double (low - i) / low,
		    2) + (double) i / low * Gauss(i, sigma);
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
	//全域調整
	for (int i = 0; i < tbl_n; i++) {
	    Hue_table_t[i] = (Hue_table[i] + gain_h + 768) % 768;
	    Sat_table_t[i] = Sat_table[i] + gain_s;
	    Val_table_t[i] = Val_table[i] + gain_v;
	}
    }

    //同步到grid
    for (int i = 0; i < tbl_n; i++) {
	stringGrid_HSV->Cells[1][i + 1] =
	    FloatToStr((double) Hue_table_t[i] / 768 * 360);
	stringGrid_HSV->Cells[2][i + 1] =
	    FloatToStr((double) (Sat_table_t[i]) / 32);
	stringGrid_HSV->Cells[3][i + 1] = Val_table_t[i];
    }

}

//---------------------------------------------------------------------------


void __fastcall THSVForm3::btn_hsv_loadClick(TObject * Sender)
{
    if (!OpenDialog1->Execute())
	return;
    String Fpath;
    Fpath = OpenDialog1->FileName;

    Load_HSV(Fpath);
}

//---------------------------------------------------------------------------

bool THSVForm3::Load_HSV(String Fpath)
{
    if (Fpath == NULL)
	return 0;
    char *buffer = Load_File(Fpath);
    if (buffer == NULL)
	return 0;
    for (int i = 0; i < HUE_COUNT; i++) {
	Hue_table[i] = -1;
	Sat_table[i] = -1;
	Val_table[i] = 0;
    }



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
	stringGrid_HSV->Cells[1][i + 1] =
	    FloatToStr((double) Hue_table[i] / 768 * 360);
	stringGrid_HSV->Cells[2][i + 1] =
	    FloatToStr((double) (Sat_table[i]) / 32);
	stringGrid_HSV->Cells[3][i + 1] = IntToStr(Val_table[i]);
    }

    //Hue_LUTWrite();
    return 1;
}


//---------------------------------------------------------------------------

void __fastcall THSVForm3::btn_hsv_saveClick(TObject * Sender)
{
    if (!SaveDialog1->Execute())
	return;
    String Fpath = SaveDialog1->FileName /*+".txt" */ ;
    FILE *fptr = fopen(Fpath.c_str(), "w");

    //fprintf(fptr,"Hue_LUT\tSat_LUT\tBri_LUT\n");
    for (int i = 0; i < 24; i++) {
	fprintf(fptr, "%d\t%d\t%d\n", Hue_table[i], Sat_table[i],
		Val_table[i]);
    }

    fclose(fptr);
}

//---------------------------------------------------------------------------


void __fastcall THSVForm3::Hue_ImgMouseMove(TObject * Sender,
					    TShiftState Shift, int X,
					    int Y)
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
	"B:" + IntToStr((int) b) + " G:" + IntToStr((int) g) + " R:" +
	IntToStr((int) r) + " H:" + FloatToStr(h) + " S:" + FloatToStr(s) +
	" V:" + FloatToStr(v) + " I:" + FloatToStr(i);
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::btn_Hue_Img_loadClick(TObject * Sender)
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

void __fastcall THSVForm3::rg_HSV_ModeClick(TObject * Sender)
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

void __fastcall THSVForm3::Btn_HSV_reloadClick(TObject * Sender)
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
		ShowMessage("HSV CheckBox read error:" +
			    IntToStr(read_val));
	}
    }
    btn_hsv_readClick(Sender);
    HSV_LUT_FuncEnable(1);
    Btn_HSV_reload->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::FormKeyDown(TObject * Sender, WORD & Key,
				       TShiftState Shift)
{
    if (Key == 0x40) {
	Btn_HSV_reloadClick(Sender);
    }
}

//---------------------------------------------------------------------------





//---------------------------------------------------------------------------


void __fastcall THSVForm3::sb_dif_nChange(TObject * Sender)
{
    lb_dif_n->Caption = (4 - sb_dif_n->Position) * 15;
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::sb_dif_pChange(TObject * Sender)
{
    lb_dif_p->Caption = sb_dif_p->Position * 15;
}

//---------------------------------------------------------------------------



void __fastcall THSVForm3::btn_setClick(TObject * Sender)
{
    for (int i = 0; i < 24; i++) {
	Hue_table[i] = Hue_table_t[i];
	Sat_table[i] = Sat_table_t[i];
	Val_table[i] = Val_table_t[i];

	stringGrid_HSV->Cells[1][i + 1] =
	    FloatToStr((double) Hue_table_t[i] / 768 * 360);
	stringGrid_HSV->Cells[2][i + 1] =
	    FloatToStr((double) (Sat_table_t[i]) / 32);
	stringGrid_HSV->Cells[3][i + 1] = Val_table_t[i];
    }
    btn_set->Enabled = false;
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::btn_hsv_writeClick(TObject * Sender)
{
    Hue_LUTWrite();
}

//---------------------------------------------------------------------------
// Recover the state of HSV enable
bool THSVForm3::HSV_LUT_RW_start()
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
void THSVForm3::HSV_LUT_RW_over()
{
    // reload en state
    int set_val = (HSV_EN_State == false ? 0 : 1);
    ChkB[HSVEN_idx]->Chkb->Checked = HSV_EN_State;
    EngineerForm->SetWrite_Byte(ChkB[HSVEN_idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void THSVForm3::HSV_LUT_FuncEnable(bool flag_en)
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

void __fastcall THSVForm3::btn_hsv_readClick(TObject * Sender)
{
    HSV_LUT_FuncEnable(0);	// Table operation button disable
    bool ok = HSV_LUT_RW_start();	// Record the state of HSV enable
    if (ok == 0) {		// Fail to record the state
	HSV_LUT_FuncEnable(1);	// Table operation button enable
	return;
    }

    int HSV_lut[24 * 3];
    if (!EngineerForm->SetRead_PG(lut_addr[0], HSV_lut, HSV_IsChkSum)) {
	ShowMessage("Hue page read fail.");
	return;
    }
    EngineerForm->SetWrite_Byte(en.Addr, HSV_EN_State);

    int val_r;
    for (int i = 0; i < 24; i++) {
	Hue_table[i] = HSV_lut[i * 3] * 4 + (HSV_lut[i * 3 + 1] / 64) % 4;
	Sat_table[i] =
	    (HSV_lut[i * 3 + 1] % 64) * 2 + (HSV_lut[i * 3 + 2] / 128) % 2;
	val_r = HSV_lut[i * 3 + 2] % 128;
	// Modified only for AUO11307
	//Hue_table[i] = HSV_lut[i*3+2]*4 + (HSV_lut[i*3+1]/64)%4;
	//Sat_table[i] = (HSV_lut[i*3+1]%64)*2 + (HSV_lut[i*3]/128)%2;
	//val_r = HSV_lut[i*3]%128;

	Val_table[i] = Cmplmnt2sToSign(val_r, 128);

	stringGrid_HSV->Cells[1][i + 1] =
	    FloatToStr((double) Hue_table[i] / 768 * 360);
	stringGrid_HSV->Cells[2][i + 1] =
	    FloatToStr((double) (Sat_table[i]) / 32);
	stringGrid_HSV->Cells[3][i + 1] = IntToStr(Val_table[i]);
    }
    HSV_LUT_RW_over();		// Recover HSV enable
    HSV_LUT_FuncEnable(1);	// Table operation button enable
}

//---------------------------------------------------------------------------



void __fastcall THSVForm3::Hue_ImgMouseDown(TObject * Sender,
					    TMouseButton Button,
					    TShiftState Shift, int X,
					    int Y)
{
    int color;
    double h, s, v, i, r, g, b;
    color = Hue_Img->Canvas->Pixels[X][Y];

    b = color / 65536;
    g = color / 256 % 256;
    r = color % 256;

    rgb2hsv(r, g, b, &h, &s, &i, &v);
    ed_Hue_Custom->Text = FloatToStr(h);
}

//---------------------------------------------------------------------------
void THSVForm3::initStringGrid_HSV()
{

    //initial table setting
    for (int i = 0; i < HUE_COUNT; i++) {
	stringGrid_HSV->Cells[0][i + 1] = IntToStr(360 / 24 * i) + "°";	// Index as hue
	stringGrid_HSV->Cells[1][i + 1] = IntToStr(360 / 24 * i);	// Hue default value
	stringGrid_HSV->Cells[2][i + 1] = 1;	// Saturation default value
	stringGrid_HSV->Cells[3][i + 1] = 0;	// Luminance default value
    }

    stringGrid_HSV->Cells[1][0] = "H";
    stringGrid_HSV->Cells[2][0] = "S";
    stringGrid_HSV->Cells[3][0] = "V";
};

const int THSVForm3::HueRGBValues[24][3] = {
    {255, 0, 0}, {255, 64, 0}, {255, 128, 0}, {255, 191, 0}, {255, 255, 0},
    {191, 255, 0}, {128, 255, 0}, {64, 255, 0}, {0, 255, 0}, {0, 255, 64},
    {0, 255, 128}, {0, 255, 191}, {0, 255, 255}, {0, 191, 255}, {0, 128,
								 255},
    {0, 64, 255}, {0, 0, 255}, {64, 0, 255}, {128, 0, 255}, {191, 0, 255},
    {255, 0, 255}, {255, 0, 191}, {255, 0, 128}, {255, 0, 64}
};


RGB_ptr THSVForm3::getHueRGB(int index)
{
    using namespace Dep;
    RGB_ptr rgb(new
		RGBColor(HueRGBValues[index][0], HueRGBValues[index][1],
			 HueRGBValues[index][2]));
    return rgb;
}

void __fastcall THSVForm3::stringGrid_HSVDrawCell(TObject * Sender,
						  int ACol, int ARow,
						  TRect & Rect,
						  TGridDrawState State)
{
    using namespace Dep;

    //int row = ARow;
    if (ARow >= 1 && ARow <= 24 && ACol == 1) {
	RGB_ptr rgb = getHueRGB(ARow - 1);
	stringGrid_HSV->Canvas->Brush->Color = rgb->getColor();
	int height = stringGrid_HSV->DefaultRowHeight + 1;
	int width = stringGrid_HSV->ColWidths[0];
	stringGrid_HSV->Canvas->Rectangle(0, height * ARow, width,
					  height * (ARow + 1));
	stringGrid_HSV->Canvas->Font->Color = clBlack;
	int hueAngle = (ARow - 1) * 15;
	stringGrid_HSV->Canvas->TextOut(0 + 4, height * ARow + 1,
					hueAngle);
    }
}

//---------------------------------------------------------------------------

double_array THSVForm3::getHSVAdjustValue(int row)
{
    double_array adjustValue(new double[3]);
    adjustValue[0] = stringGrid_HSV->Cells[1][row].ToDouble();
    adjustValue[1] = stringGrid_HSV->Cells[2][row].ToDouble();
    adjustValue[2] = stringGrid_HSV->Cells[3][row].ToDouble();
    return adjustValue;
}

void __fastcall THSVForm3::stringGrid_HSVSelectCell(TObject * Sender,
						    int ACol, int ARow,
						    bool & CanSelect)
{
    //this->Reset_HSVshow();
    RGB_ptr rgb = getHueRGB(ARow - 1);
    //設定colorpicker
    colorPicker->setOriginalColor(rgb->R, rgb->G, rgb->B);
    //設定hsvadjust
    double_array hsvAdjustValue = getHSVAdjustValue(ARow);
    Reset_HSVshow();
}

//---------------------------------------------------------------------------


void __fastcall THSVForm3::hsvAdjustsb_c3d_Manual39_hChange(TObject *
							    Sender)
{

    for (int i = 0; i < HUE_COUNT; i++) {
	Hue_table_t[i] = Hue_table[i];
	Sat_table_t[i] = Sat_table[i];
	Val_table_t[i] = Val_table[i];
    }

    int tbl_idx = stringGrid_HSV->Selection.Top - 1;

    //更新
    //int h = sb_Hue_gain->Position;
    //int s = sb_Sat_gain->Position;
    //int v = sb_Val_gain->Position;
    int h = hsvAdjust->sb_Hue_gain->Position;
    int s = hsvAdjust->sb_Sat_gain->Position;
    int v = hsvAdjust->sb_Val_gain->Position;
    show_gain(h, s, v);
    int gain_h = h;		// Hue值為Gain
    int gain_s = s - Sat_table[tbl_idx];	// 調整值與table數值的差異為gain
    int gain_v = v - Val_table[tbl_idx];
    if (gain_h > 768 / 2) {
	gain_h -= 768;
    } else if (gain_h < (-1) * 768 / 2) {
	gain_h += 768;
    }
    //可以做set
    btn_set->Enabled = true;
    if (cb_Hue_rotation->Checked == false) {
	//非全域調整
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

	Set_Adj_tbl(tmp_H, tmp_S, tmp_V, tbl_idx);
	if (!CheckHueIncrease(high, low, tmp_H)) {
	    ShowMessage("Hue value has inverse.");
	    btn_set->Enabled = false;
	    return;
	}
    } else {			//rotation
	//全域調整
	for (int i = 0; i < HUE_COUNT; i++) {
	    Hue_table_t[i] = (Hue_table[i] + gain_h + 768) % 768;
	    Sat_table_t[i] = Sat_table[i] + gain_s;
	    Val_table_t[i] = Val_table[i] + gain_v;
	}
    }

    //同步到grid
    for (int i = 0; i < HUE_COUNT; i++) {
	stringGrid_HSV->Cells[1][i + 1] =
	    FloatToStr((double) Hue_table_t[i] / 768 * 360);
	stringGrid_HSV->Cells[2][i + 1] =
	    FloatToStr((double) (Sat_table_t[i]) / 32);
	stringGrid_HSV->Cells[3][i + 1] = Val_table_t[i];
    }
}

//---------------------------------------------------------------------------






void __fastcall THSVForm3::RadioButton_deg60baseClick(TObject * Sender)
{
    TRadioButton *button = dynamic_cast < TRadioButton * >(Sender);
    if (null != button) {
	setGridSelectRow(hintToRow(button->Hint.ToInt()));
    }
}

int THSVForm3::hintToRow(int hint)
{
    return hint / 15 + 1;
}

void THSVForm3::setGridSelectRow(int row)
{
    TGridRect select = stringGrid_HSV->Selection;
    select.Top = row;
    select.Bottom = row;
    stringGrid_HSV->Selection = select;
    stringGrid_HSVSelectCell(null, -1, row, true);
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall THSVForm3::RadioButton_deg30baseClick(TObject * Sender)
{
    TRadioButton *button = dynamic_cast < TRadioButton * >(Sender);
    if (null != button) {
	setGridSelectRow(hintToRow(button->Hint.ToInt()));
    }

}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::FormShow(TObject * Sender)
{
    initGroupBoxBase(GroupBox_30base);
    initGroupBoxBase(GroupBox_60base);
}

//---------------------------------------------------------------------------

