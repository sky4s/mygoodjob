
//---------------------------------------------------------------------------

#include <vcl.h>
#include <lib/CMSCpp2.1/includeall.h>
#pragma hdrstop
#include "Sharpness1.h"
#include <math.h>
#include "include.h"
#include <fpga/11307/ImageProcess/ImgProc_11307.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TSharpnessForm1 *SharpnessForm;       //使用動態宣告,不需作實體宣告
bool SP_IsChkSum = 0;
//---------------------------------------------------------------------------
__fastcall TSharpnessForm1::TSharpnessForm1(TComponent * Owner)
:TForm(Owner)
{
    SP_Chg = 0;
    gain_flag = false;
}

//---------------------------------------------------------------------------
void __fastcall TSharpnessForm1::FormClose(TObject * Sender, TCloseAction & Action)
{
    delete[]OSP;
    delete[]cb;
    delete[]ChkB;

    delete[]lble2;		//Add by Michelle 20100702
    delete[]LblE2;

    delete[]scrlb;
    delete[]ScrlB;
    Action = caFree;
    MainForm->SharpnessFormNULL();
}

//---------------------------------------------------------------------------


void __fastcall TSharpnessForm1::ScrollBar_Change(TObject * Sender)
{
    if (SP_Chg == 0)
	return;
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    if (ScrlB[idx]->Addr.Name().AnsiCompare("GLT_STR") == 0) {
	int set_val = (ScrlB[idx]->ScrlB->Position);
	float tmp_val = (double) set_val / 4;
	int t_val = (float) ((int) (tmp_val * 10)) / 10;
	ScrlB[idx]->StTxt->Caption = t_val;
	EngineerForm->SetWrite_Byte(ScrlB[idx]->Addr, set_val);
    } else {
	int set_val = (ScrlB[idx]->ScrlB->Position);
	ScrlB[idx]->StTxt->Caption = set_val;
	EngineerForm->SetWrite_Byte(ScrlB[idx]->Addr, set_val);
    }
}

//---------------------------------------------------------------------------
void __fastcall TSharpnessForm1::CheckBox_Click(TObject * Sender)
{
    if (SP_Chg == 0)
	return;
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (ChkB[idx]->Chkb->Checked ? 1 : 0);
    EngineerForm->SetWrite_Byte(ChkB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void __fastcall TSharpnessForm1::LblEdit2_KeyPress(TObject * Sender, char &Key)	//Add by Michelle 20100702
{
    TLabeledEdit *c = (TLabeledEdit *) Sender;
    int idx = StrToInt(c->Hint);
    if (Key != 13) {
	LblE2[idx]->Lble->Font->Color = cl3DDkShadow;
	return;
    }

    if (SP_Chg == 0)
	return;

    String tmp_v = LblE2[idx]->Lble->Text;
    if (tmp_v == "") {
	tmp_v = "0";
    }
    int set_val = StrToInt(tmp_v);

    unsigned char val1, val2;
    //add Max hint
    if (set_val >= pow(2, LblE2[idx]->Addr.BitNum())) {
	AnsiString max = "Max value:" + IntToStr((int) pow(2, LblE2[idx]->Addr.BitNum()) - 1);
	ShowMessage(max);
	//read value
	EngineerForm->SetRead_Byte(LblE2[idx]->Addr.Byte1, &val1);
	EngineerForm->SetRead_Byte(LblE2[idx]->Addr.Byte2, &val2);
	LblE2[idx]->Lble->Text = (int) val1 *LblE2[idx]->Addr.Divide() + val2;
	LblE2[idx]->Lble->Font->Color = clWindowText;
    } else {
	val1 = set_val / LblE2[idx]->Addr.Divide();
	val2 = set_val % LblE2[idx]->Addr.Divide();
	EngineerForm->SetWrite_Byte(LblE2[idx]->Addr.Byte1, val1);
	if (LblE2[idx]->Addr.Byte2.BitNum() != 0)
	    EngineerForm->SetWrite_Byte(LblE2[idx]->Addr.Byte2, val2);
	LblE2[idx]->Lble->Font->Color = clWindowText;
    }
}

//---------------------------------------------------------------------------
void __fastcall TSharpnessForm1::FormCreate(TObject * Sender)
{
    SP_Chg = 0;
    int ic_choice;
    if (MainForm->TCON_DEV == "11307")
	ic_choice = 0;

    switch (ic_choice) {
    case 0:
	OSP = new SP_11307;
	break;
    }

    /********************************************************************///
    //  Image Process SP has CheckBox*6 & ScrollBar*4  & table idx 32   //
    //                                  & LblEdit2*1                    //
    //******************************************************************//

    //CheckBox
    cb = OSP->SetChkBx();

    ChkB = new _CHKB *[OSP->SPChkBox_Nbr];
    for (int i = 0; i < OSP->SPChkBox_Nbr; i++)
	ChkB[i] = new _CHKB;

    ChkB[0]->Chkb = CheckBox1;
    ChkB[1]->Chkb = CheckBox2;
    ChkB[2]->Chkb = CheckBox3;
    ChkB[3]->Chkb = CheckBox4;
    ChkB[4]->Chkb = CheckBox5;
    ChkB[5]->Chkb = CheckBox6;

    for (int i = 0; i < OSP->SPChkBox_Nbr; i++) {
	ChkB[i]->Addr = cb[i];
	ChkB[i]->Chkb->Visible = ChkB[i]->Addr.FuncEn();
	ChkB[i]->Chkb->OnClick = CheckBox_Click;
	ChkB[i]->Chkb->Hint = i;
	ChkB[i]->Chkb->Caption = ChkB[i]->Addr.Name();
    }

    //ScrollBar
    scrlb = OSP->SetScrollBar();

    ScrlB = new _ScrollBar *[OSP->SPScrollBar_Nbr];
    for (int i = 0; i < OSP->SPScrollBar_Nbr; i++)
	ScrlB[i] = new _ScrollBar;

    ScrlB[0]->Lbl = Label1;
    ScrlB[0]->StTxt = StaticText1;
    ScrlB[0]->ScrlB = ScrollBar1;

    ScrlB[1]->Lbl = Label2;
    ScrlB[1]->StTxt = StaticText2;
    ScrlB[1]->ScrlB = ScrollBar2;

    ScrlB[2]->Lbl = Label3;
    ScrlB[2]->StTxt = StaticText3;
    ScrlB[2]->ScrlB = ScrollBar3;

    ScrlB[3]->Lbl = Label4;
    ScrlB[3]->StTxt = StaticText4;
    ScrlB[3]->ScrlB = ScrollBar4;

    for (int i = 0; i < OSP->SPScrollBar_Nbr; i++) {
	ScrlB[i]->Addr = scrlb[i];
	ScrlB[i]->Lbl->Visible = ScrlB[i]->Addr.FuncEn();
	ScrlB[i]->StTxt->Visible = ScrlB[i]->Addr.FuncEn();
	ScrlB[i]->ScrlB->Visible = ScrlB[i]->Addr.FuncEn();
	if (ScrlB[i]->Addr.FuncEn()) {
	    ScrlB[i]->ScrlB->Min = 0;
	    ScrlB[i]->ScrlB->Max = (int) pow(2, ScrlB[i]->Addr.BitNum()) - 1;
	    ScrlB[i]->ScrlB->OnChange = ScrollBar_Change;
	    ScrlB[i]->ScrlB->Hint = i;
	    ScrlB[i]->StTxt->Caption = 0;
	    ScrlB[i]->Lbl->Caption = ScrlB[i]->Addr.Name();
	}
    }
    //LabeledEdit2   //Add by Michelle 20100702
    lble2 = OSP->SetLblE2();
    LblE2 = new _LBLE2 *[OSP->SPLblE2_Nbr];
    for (int i = 0; i < OSP->SPLblE2_Nbr; i++)
	LblE2[i] = new _LBLE2;

    //LblE2[0]->Lble = LabeledEdit1;


    for (int i = 0; i < OSP->SPLblE2_Nbr; i++) {
	LblE2[i]->Addr = lble2[i];
	LblE2[i]->Lble->Visible = LblE2[i]->Addr.FuncEn();
	LblE2[i]->Lble->OnKeyPress = LblEdit2_KeyPress;
	LblE2[i]->Lble->Hint = i;
	LblE2[i]->Lble->EditLabel->Caption = LblE2[i]->Addr.Name();
	LblE2[i]->Lble->Text = 0;
    }

    Clear_LUT(true);
    SP_addr = OSP->SetSPLUT();
    SP_Chg = 1;
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void TSharpnessForm1::SP_LUT_FuncEnable(bool flag_en)
{
    if (flag_en == true) {
	btn_sp_lut_write->Enabled = true;
	btn_sp_lut_read->Enabled = true;
	btn_sp_lut_Set->Enabled = true;
    } else {
	btn_sp_lut_write->Enabled = false;
	btn_sp_lut_read->Enabled = false;
	btn_sp_lut_Set->Enabled = false;
    }
}

//----------------------------------------------------------------------------
void TSharpnessForm1::Clear_LUT(bool type)
{
    if (type == true) {
	for (int i = 0; i < 32; i++)
	    SP_lut[i] = -1;
    }
    Graphics::TBitmap * LUT_Graph;
    LUT_Graph = new Graphics::TBitmap();
    LUT_Graph->Height = SP_LUT->Height;
    LUT_Graph->Width = SP_LUT->Width;
    SP_LUT->Canvas->Draw(0, 0, LUT_Graph);
    delete LUT_Graph;

    SP_LUT->Canvas->Pen->Color = clBlack;
    SP_LUT->Canvas->Pen->Style = psSolid;
    SP_LUT->Canvas->MoveTo(30, 10);
    SP_LUT->Canvas->LineTo(30, 266);
    SP_LUT->Canvas->LineTo(350, 266);
    SP_LUT->Canvas->Pen->Style = psSolid;
    SP_LUT->Canvas->Brush->Color = clWhite;
    SP_LUT->Canvas->Pen->Color = clSilver;
    //SP_LUT->Canvas->Pen->Style = psDashDot;
    for (int i = 1; i <= 63; i++) {
	SP_LUT->Canvas->MoveTo(30, 266 - 4 * i);
	SP_LUT->Canvas->LineTo(340, 266 - 4 * i);
    }
    SP_LUT->Canvas->Pen->Color = clGray;
    //SP_LUT->Canvas->Pen->Style = psDashDot;
    for (int i = 5; i <= 63; i += 5) {
	SP_LUT->Canvas->MoveTo(30, 266 - 4 * i);
	SP_LUT->Canvas->LineTo(340, 266 - 4 * i);
    }

    for (int i = 1; i <= 31; i++) {
	SP_LUT->Canvas->MoveTo(30 + 10 * i, 266);
	SP_LUT->Canvas->LineTo(30 + 10 * i, 14);
    }

    //10刻度線
    SP_LUT->Canvas->Pen->Color = clBlack;
    //SP_LUT->Canvas->Pen->Style = psDashDot;
    for (int i = 10; i <= 63; i += 10) {
	SP_LUT->Canvas->MoveTo(30, 266 - 4 * i);
	SP_LUT->Canvas->LineTo(340, 266 - 4 * i);
	SP_LUT->Canvas->TextOutA(10, 266 - 4 * i - 5, IntToStr(i));
    }

    for (int i = 5; i <= 31; i += 5) {
	SP_LUT->Canvas->MoveTo(30 + 10 * i, 266);
	SP_LUT->Canvas->LineTo(30 + 10 * i, 14);
	SP_LUT->Canvas->TextOutA(30 + 10 * i - 5, 270, IntToStr(i));
    }

    SP_LUT->Canvas->Pen->Color = clBlack;
    SP_LUT->Canvas->Pen->Style = psSolid;
    SP_LUT->Canvas->Brush->Color = clWhite;
    SP_LUT->Canvas->TextOutA(310, 285, "Difference");
    SP_LUT->Canvas->TextOutA(10, 0, "Weight");
    SP_LUT->Canvas->TextOutA(30 - 5, 270, "0");
}

//--------------------------------------------------------------------------

void __fastcall TSharpnessForm1::SP_LUTMouseDown(TObject * Sender,
						 TMouseButton Button, TShiftState Shift, int X,
						 int Y)
{
    if (X >= (30 - 5) && X <= (340 + 5) && Y <= (264) && Y >= (12)) {
	int tmp_y;
	if (Y % 4 >= 2)
	    tmp_y = (floor((double) Y / 4) + 1) * 4;
	else
	    tmp_y = (floor((double) Y / 4)) * 4;
	int tmp_x;
	if (X % 10 >= 5)
	    tmp_x = (floor((double) X / 10) + 1) * 10;
	else
	    tmp_x = (floor((double) X / 10)) * 10;

	int dif = 31 - (340 - tmp_x) / 10;
	int weight = (266 - tmp_y) / 4;
	if (SP_lut[dif] == -1) {	//沒被點過的值
	    SP_lut[dif] = weight;
	    SP_LUT->Canvas->Brush->Color = clMaroon;
	    SP_LUT->Canvas->Ellipse(tmp_x - 5, tmp_y, tmp_x + 5, tmp_y + 4);
	} else {		//被點過的值,重繪圖形
	    Clear_LUT(false);
	    SP_lut[dif] = weight;
	    for (int i = 0; i < 32; i++) {
		if (SP_lut[i] != -1) {
		    int x = i * 10 + 30;
		    int y = 266 - SP_lut[i] * 4;
		    SP_LUT->Canvas->Brush->Color = clMaroon;
		    SP_LUT->Canvas->Ellipse(x - 5, y - 2, x + 5, y + 2);
		}
	    }
	}
	LUT_type->ItemIndex = -1;
    }
}

//---------------------------------------------------------------------------

void __fastcall TSharpnessForm1::SP_LUTDblClick(TObject * Sender)
{
    int t;
    for (int i = 0; i < 32; i++) {
	if (SP_lut[i] == -1) {
	    if (i == 0) {
		int j = 0;
		while (SP_lut[j] == -1) {
		    if (j == 31) {
			SP_lut[j] = 0;
			break;
		    }
		    j++;
		}

		for (t = j; t > 0; t--)
		    SP_lut[t - 1] = SP_lut[t];
		i = j;
	    } else {
		bool no_last = false;
		int a = i - 1;
		int s = 0;
		while (SP_lut[i + s] == -1) {
		    s++;
		    if (i + s > 31) {
			no_last = true;
			break;
		    }
		}
		if (no_last) {
		    for (t = a + 1; t <= 31; t++)
			SP_lut[t] = SP_lut[t - 1];
		} else {
		    int b = i + s;
		    for (t = i; t < i + s; t++) {
			SP_lut[t] = SP_lut[a] + (SP_lut[b] - SP_lut[a]) * (t - i + 1) / s;
		    }
		}
		i = t;
	    }

	}
    }
    Clear_LUT(false);
    int x, y, x_1, y_1;
    x = 30;
    y = 266 - SP_lut[0] * 4;
    SP_LUT->Canvas->Brush->Color = clMaroon;
    SP_LUT->Canvas->Ellipse(x - 5, y - 2, x + 5, y + 2);

    for (int i = 1; i < 32; i++) {
	x = i * 10 + 30;
	y = 266 - SP_lut[i] * 4;
	x_1 = (i - 1) * 10 + 30;
	y_1 = 266 - SP_lut[i - 1] * 4;
	SP_LUT->Canvas->Brush->Color = clMaroon;
	SP_LUT->Canvas->Ellipse(x - 5, y - 2, x + 5, y + 2);
	SP_LUT->Canvas->Pen->Color = clRed;
	SP_LUT->Canvas->MoveTo(x_1, y_1);
	SP_LUT->Canvas->LineTo(x, y);
    }
}

//---------------------------------------------------------------------------

void __fastcall TSharpnessForm1::sb_softgainChange(TObject * Sender)
{
    if (SP_lut[0] != -1) {
	gain_flag = true;
	float gain = (float) sb_softgain->Position / 10;

	char buf[4];
	sprintf(buf, "%2.1f", gain);
	st_softgain->Caption = (AnsiString) buf;

	for (int i = 0; i < 32; i++)
	    LUT_g[i] = (SP_lut[i] * gain > 64 ? 63 : SP_lut[i] * gain);
	SP_LUTDblClick(Sender);

	int x, y, x_1, y_1;
	x = 30;
	y = 266 - LUT_g[0] * 4;
	SP_LUT->Canvas->Pen->Color = (TColor) RGB(180, 128, 128);
	SP_LUT->Canvas->Brush->Color = (TColor) RGB(180, 128, 128);
	SP_LUT->Canvas->Ellipse(x - 5, y - 2, x + 5, y + 2);

	for (int i = 1; i < 32; i++) {
	    x = i * 10 + 30;
	    y = 266 - LUT_g[i] * 4;
	    x_1 = (i - 1) * 10 + 30;
	    y_1 = 266 - LUT_g[i - 1] * 4;
	    SP_LUT->Canvas->Brush->Color = (TColor) RGB(220, 128, 128);
	    SP_LUT->Canvas->Ellipse(x - 5, y - 2, x + 5, y + 2);
	    SP_LUT->Canvas->MoveTo(x_1, y_1);
	    SP_LUT->Canvas->LineTo(x, y);
	}

    } else
	sb_softgain->Position = 10;

}

//---------------------------------------------------------------------------

void __fastcall TSharpnessForm1::btn_sp_lut_SetClick(TObject * Sender)
{
    SP_LUT_FuncEnable(0);
    SP_LUT->Canvas->Refresh();
    Clear_LUT(true);
    LUT_type->ItemIndex = -1;
    sb_softgain->Position = 10;
    st_softgain->Caption = "1";
    SP_LUT_FuncEnable(1);
}

//---------------------------------------------------------------------------

void __fastcall TSharpnessForm1::btn_GainSetClick(TObject * Sender)
{
    if (SP_lut[0] != -1) {
	gain_flag = false;
	for (int i = 0; i < 32; i++)
	    SP_lut[i] = LUT_g[i];
	sb_softgain->Position = 10;
	st_softgain->Caption = 1;
	SP_LUTDblClick(Sender);
    }
}

//---------------------------------------------------------------------------

void __fastcall TSharpnessForm1::btn_sp_lut_writeClick(TObject * Sender)
{
    SP_Chg = 0;
    if (SP_addr[0].LutNum() != 32) {
	ShowMessage("SP LUT number defined in AddressSP.cpp is wrong.");
	return;
    }
    btn_sp_lut_write->Enabled = false;
    EngineerForm->SetWrite_PG(SP_addr[0], SP_lut, SP_IsChkSum);
    btn_sp_lut_write->Enabled = true;
    SP_Chg = 1;
}

//---------------------------------------------------------------------------
void __fastcall TSharpnessForm1::btn_sp_lut_readClick(TObject * Sender)
{
    SP_Chg = 0;
    if (SP_addr[0].LutNum() != 32) {
	ShowMessage("SP LUT number defined in AddressSP.cpp is wrong.");
	return;
    }
    btn_sp_lut_read->Enabled = false;
    EngineerForm->SetRead_PG(SP_addr[0], SP_lut, 0);
    SP_LUTDblClick(Sender);
    btn_sp_lut_read->Enabled = true;
    SP_Chg = 1;
}

//---------------------------------------------------------------------------

void __fastcall TSharpnessForm1::Btn_SP_reloadClick(TObject * Sender)
{
    Btn_SP_reload->Enabled = false;
    SP_LUT_FuncEnable(0);
    SP_Chg = 0;
    unsigned char read_val;
    for (int i = 0; i < OSP->SPChkBox_Nbr; i++) {
	if (ChkB[i]->Chkb->Visible == true) {
	    EngineerForm->SetRead_Byte(ChkB[i]->Addr, &read_val);
	    if (read_val == 1)
		ChkB[i]->Chkb->Checked = 1;
	    else if (read_val == 0)
		ChkB[i]->Chkb->Checked = 0;
	    else
		ShowMessage("SP CheckBox read error:" + IntToStr(read_val));
	}
    }
    for (int i = 0; i < OSP->SPScrollBar_Nbr; i++) {
	if (ScrlB[i]->ScrlB->Visible == true) {
	    EngineerForm->SetRead_Byte(ScrlB[i]->Addr, &read_val);
	    ScrlB[i]->ScrlB->Position = read_val;
	    ScrlB[i]->StTxt->Caption = read_val;
	}
    }

    unsigned char read_val1, read_val2;
    for (int i = 0; i < OSP->SPLblE2_Nbr; i++) {
	if (LblE2[i]->Lble->Visible == true) {
	    EngineerForm->SetRead_Byte(LblE2[i]->Addr.Byte1, &read_val1);
	    EngineerForm->SetRead_Byte(LblE2[i]->Addr.Byte2, &read_val2);
	    LblE2[i]->Lble->Text = (int) read_val1 *LblE2[i]->Addr.Divide() + read_val2;
	    LblE2[i]->Lble->Font->Color = clWindowText;
	}
    }
    btn_sp_lut_readClick(Sender);
    SP_Chg = 1;
    Btn_SP_reload->Enabled = true;
    SP_LUT_FuncEnable(1);
}

//---------------------------------------------------------------------------

void __fastcall TSharpnessForm1::btn_sp_LoadClick(TObject * Sender)
{
    Clear_LUT(true);

    if (!OpenDialog1->Execute())
	return;
    SP_LUT_FuncEnable(0);
    String Fpath = OpenDialog1->FileName;
    if (!Load_SP(Fpath))
	Application->MessageBox("Open Sharpness File Failed.", "Error Message", 0);

    sb_softgainChange(Sender);
    SP_LUTDblClick(Sender);
    btn_GainSetClick(Sender);
    SP_LUT_FuncEnable(1);
    btn_sp_lut_writeClick(Sender);
}

//---------------------------------------------------------------------------
bool TSharpnessForm1::Load_SP(String Fpath)
{
    char *buffer = Load_File(Fpath);
    char *pch;
    pch = strtok(buffer, "\n\t");
    int c = 0;

    AnsiString str[5];
    str[0] = "TEXT_DET";
    str[1] = "HORZ_THR";
    str[2] = "VERT_THR";
    str[3] = "EDGE_THR";
    str[4] = "GLT_STR";		//hardwre gain
    while (c < 38 && pch != NULL) {
	if (pch == NULL) {
	    ShowMessage("Data Missing.");
	    delete[]buffer;
	    return 0;
	    //資料中的data缺少
	}

	if (c == 0) {		//TD
	    for (int i = 0; i < OSP->SPChkBox_Nbr; i++) {
		if (SameText(ChkB[i]->Addr.Name(), str[0])) {
		    ChkB[i]->Chkb->Checked = (StrToInt((AnsiString) pch) > 0 ? 1 : 0);
		    ChkB[i]->Chkb->OnClick;
		    break;
		}
	    }
	} else if (c >= 1 && c <= 3) {	//HORZ_THR, VERT_THR, EDGE_THR
	    for (int i = 0; i < OSP->SPScrollBar_Nbr; i++) {
		if (SameText(ScrlB[i]->Addr.Name(), str[c])) {
		    ScrlB[i]->ScrlB->Position = (StrToInt((AnsiString) pch));
		    ScrlB[i]->ScrlB->OnChange;
		    break;
		}
	    }
	} else if (c == 4) {	//hardware gain
	    for (int i = 0; i < OSP->SPScrollBar_Nbr; i++) {
		if (SameText(ScrlB[i]->Addr.Name(), str[c])) {
		    float tmp = (StrToFloat((AnsiString) pch));
		    ScrlB[i]->ScrlB->Position = int (tmp * 4);
		    ScrlB[i]->ScrlB->OnChange;
		    break;
		}
	    }
	} else if (c == 5) {	//swg
	    sb_softgain->Position = StrToFloat((AnsiString) pch) * 10;

	} else {		//tbl
	    SP_lut[c - 6] = StrToInt((AnsiString) pch);
	}
	pch = strtok(NULL, "\n\t");
	c++;
	if (c >= 38)
	    break;
    }
    delete[]buffer;
    return 1;
}

void __fastcall TSharpnessForm1::btn_sp_SaveClick(TObject * Sender)
{
    if (!SaveDialog1->Execute())
	return;
    SP_LUT_FuncEnable(0);
    String Fpath = SaveDialog1->FileName;
    FILE *fptr = fopen(Fpath.c_str(), "w");

    AnsiString str[5];
    str[0] = "TEXT_DET";
    str[1] = "HORZ_THR";
    str[2] = "VERT_THR";
    str[3] = "EDGE_THR";
    str[4] = "GLT_STR";		//hardwre gain

    AnsiString input_str[5];
    for (int i = 0; i <= 3; i++)
	input_str[i] = "0";
    input_str[4] = "1";

    for (int i = 0; i < OSP->SPChkBox_Nbr; i++) {
	if (SameText(ChkB[i]->Addr.Name(), str[0])) {
	    input_str[0] = (ChkB[i]->Chkb->Checked ? "1" : "0");
	    break;
	}
    }
    for (int j = 0; j <= 3; j++)
	for (int i = 0; i < OSP->SPScrollBar_Nbr; i++) {
	    if (SameText(ScrlB[i]->Addr.Name(), str[j])) {
		input_str[j] = ScrlB[i]->ScrlB->Position;
		break;
	    }
	}
    for (int i = 0; i < OSP->SPScrollBar_Nbr; i++) {
	if (SameText(ScrlB[i]->Addr.Name(), str[4])) {
	    float val = (float) ScrlB[i]->ScrlB->Position * 4;
	    input_str[4] = FloatToStr(val);
	    break;
	}
    }
    float input_str5 = StrToFloat(sb_softgain->Position) / 10;

    fprintf(fptr, "%s\t%s\t%s\t%s\t%s\t%f\n", input_str[0], input_str[1], input_str[2],
	    input_str[3], input_str[4], input_str5);

    for (int i = 0; i < 32; i++) {
	fprintf(fptr, "%d\n", SP_lut[i]);
    }
    fclose(fptr);
    SP_LUT_FuncEnable(1);
}

//---------------------------------------------------------------------------

void __fastcall TSharpnessForm1::LUT_typeClick(TObject * Sender)
{
    String Fpath;
    if (LUT_type->ItemIndex == 0) {
	Fpath = "SP_default1.txt";
    } else if (LUT_type->ItemIndex == 1) {
	Fpath = "SP_default2.txt";
    } else if (LUT_type->ItemIndex == 2) {
	Fpath = "SP_default3.txt";
    }
    Clear_LUT(true);
    Load_SP(Fpath);

    sb_softgainChange(Sender);
    SP_LUTDblClick(Sender);
    btn_GainSetClick(Sender);
    btn_sp_lut_writeClick(Sender);

}

//---------------------------------------------------------------------------




void __fastcall TSharpnessForm1::FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift)
{
    if (Key == 0x40)
	Btn_SP_reloadClick(Sender);
}

//---------------------------------------------------------------------------

