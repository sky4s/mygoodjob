//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TCEForm.h"
#include "include.h"
#include <colorip/11307/ImgProc_11307.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TContrastEnhanceForm1 *ContrastEnhanceForm1;

//---------------------------------------------------------------------------
__fastcall TCEForm::TCEForm(TComponent * Owner)
:TForm(Owner)
{
    CE_Chg = 0;
}

//---------------------------------------------------------------------------
void __fastcall TCEForm::CheckBox_Click(TObject * Sender)
{
    if (CE_Chg == 0) {
	ShowMessage("Previous write is not over yet.");
	return;
    }
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (ChkB[idx]->Chkb->Checked ? 1 : 0);
    EngineerForm->SetWrite_Byte(ChkB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void __fastcall TCEForm::ComboBox_Change(TObject * Sender)
{
    if (CE_Chg == 0) {
	ShowMessage("Previous write is not over yet.");
	return;
    }
    TComboBox *c = (TComboBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (CboB[idx]->Cbob->ItemIndex);
    EngineerForm->SetWrite_Byte(CboB[idx]->Addr, set_val);
}

//--------------------------------------------------------------------------
void __fastcall TCEForm::ScrollBar_Change(TObject * Sender)
{
    if (CE_Chg == 0) {
	ShowMessage("Previous write is not over yet.");
	return;
    }
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (ScrlB[idx]->ScrlB->Position);
    ScrlB[idx]->StTxt->Caption = set_val;
    EngineerForm->SetWrite_Byte(ScrlB[idx]->Addr, set_val);

}

//---------------------------------------------------------------------------
void __fastcall TCEForm::FormCreate(TObject * Sender)
{
    CE_Chg = 0;
    /*int ic_choice;
    if (MainForm->TCON_DEV == "11307")
	ic_choice = 0;

    switch (ic_choice) {
    case 0:*/
	OCE = new CE_11307;
	/*break;
    }     */

	/********************************************************************/
    //                                                                  //
    //  Image Process CE has CheckBox*8 & ComboBox*5 & ScrollBar*14     //
    //                                                                  //
    //******************************************************************//

    //CheckBox
    cb = OCE->SetChkBx();

    ChkB = new _CHKB *[OCE->CEChkBox_Nbr];
    for (int i = 0; i < OCE->CEChkBox_Nbr; i++)
	ChkB[i] = new _CHKB;

    ChkB[0]->Chkb = CheckBox1;
    ChkB[1]->Chkb = CheckBox2;
    ChkB[2]->Chkb = CheckBox3;
    ChkB[3]->Chkb = CheckBox4;
    ChkB[4]->Chkb = CheckBox5;
    ChkB[5]->Chkb = CheckBox6;
    ChkB[6]->Chkb = CheckBox7;
    ChkB[7]->Chkb = CheckBox8;
    ChkB[8]->Chkb = CheckBox9;

    for (int i = 0; i < OCE->CEChkBox_Nbr; i++) {
	ChkB[i]->Addr = cb[i];
	ChkB[i]->Chkb->Visible = ChkB[i]->Addr.FuncEn();
	ChkB[i]->Chkb->OnClick = CheckBox_Click;
	ChkB[i]->Chkb->Hint = i;
	ChkB[i]->Chkb->Caption = ChkB[i]->Addr.Name();
    }

    //Combobox
    cbo = OCE->SetCboBx();

    CboB = new _CBOB *[OCE->CECboBox_Nbr];
    for (int i = 0; i < OCE->CECboBox_Nbr; i++)
	CboB[i] = new _CBOB;

    CboB[0]->Cbob = ComboBox1;
    CboB[0]->CbobL = Label1;

    CboB[1]->Cbob = ComboBox2;
    CboB[1]->CbobL = Label2;

    CboB[2]->Cbob = ComboBox3;
    CboB[2]->CbobL = Label3;

    CboB[3]->Cbob = ComboBox4;
    CboB[3]->CbobL = Label4;

    CboB[4]->Cbob = ComboBox5;
    CboB[4]->CbobL = Label5;

    for (int i = 0; i < OCE->CECboBox_Nbr; i++) {
	CboB[i]->Addr = cbo[i];
	CboB[i]->Cbob->Visible = CboB[i]->Addr.FuncEn();
	CboB[i]->CbobL->Visible = CboB[i]->Addr.FuncEn();
	CboB[i]->Cbob->OnChange = ComboBox_Change;
	CboB[i]->Cbob->Hint = i;
	CboB[i]->CbobL->Caption = CboB[i]->Addr.Name();
	CboB[i]->Cbob->Text = "";
	if (CboB[i]->Addr.FuncEn())
	    for (int j = 0; j < CboB[i]->Addr.choice_nbr; j++)	//ComboBox choice
		CboB[i]->Cbob->Items->Add(CboB[i]->Addr.choice[j]);
    }

    //ScrollBar
    scrlb = OCE->SetScrollBar();

    ScrlB = new _ScrollBar *[OCE->CEScrollBar_Nbr];
    for (int i = 0; i < OCE->CEScrollBar_Nbr; i++)
	ScrlB[i] = new _ScrollBar;

    ScrlB[0]->Lbl = Label6;
    ScrlB[0]->StTxt = StaticText1;
    ScrlB[0]->ScrlB = ScrollBar1;

    ScrlB[1]->Lbl = Label7;
    ScrlB[1]->StTxt = StaticText2;
    ScrlB[1]->ScrlB = ScrollBar2;

    ScrlB[2]->Lbl = Label8;
    ScrlB[2]->StTxt = StaticText3;
    ScrlB[2]->ScrlB = ScrollBar3;

    ScrlB[3]->Lbl = Label9;
    ScrlB[3]->StTxt = StaticText4;
    ScrlB[3]->ScrlB = ScrollBar4;

    ScrlB[4]->Lbl = Label10;
    ScrlB[4]->StTxt = StaticText5;
    ScrlB[4]->ScrlB = ScrollBar5;

    ScrlB[5]->Lbl = Label11;
    ScrlB[5]->StTxt = StaticText6;
    ScrlB[5]->ScrlB = ScrollBar6;

    ScrlB[6]->Lbl = Label12;
    ScrlB[6]->StTxt = StaticText7;
    ScrlB[6]->ScrlB = ScrollBar7;

    ScrlB[7]->Lbl = Label13;
    ScrlB[7]->StTxt = StaticText8;
    ScrlB[7]->ScrlB = ScrollBar8;

    ScrlB[8]->Lbl = Label14;
    ScrlB[8]->StTxt = StaticText9;
    ScrlB[8]->ScrlB = ScrollBar9;

    ScrlB[9]->Lbl = Label15;
    ScrlB[9]->StTxt = StaticText10;
    ScrlB[9]->ScrlB = ScrollBar10;

    ScrlB[10]->Lbl = Label16;
    ScrlB[10]->StTxt = StaticText11;
    ScrlB[10]->ScrlB = ScrollBar11;

    ScrlB[11]->Lbl = Label17;
    ScrlB[11]->StTxt = StaticText12;
    ScrlB[11]->ScrlB = ScrollBar12;

    ScrlB[12]->Lbl = Label18;
    ScrlB[12]->StTxt = StaticText13;
    ScrlB[12]->ScrlB = ScrollBar13;

    ScrlB[13]->Lbl = Label19;
    ScrlB[13]->StTxt = StaticText14;
    ScrlB[13]->ScrlB = ScrollBar14;

    for (int i = 0; i < OCE->CEScrollBar_Nbr; i++) {
	ScrlB[i]->Addr = scrlb[i];
	ScrlB[i]->Lbl->Visible = ScrlB[i]->Addr.FuncEn();
	ScrlB[i]->StTxt->Visible = ScrlB[i]->Addr.FuncEn();
	ScrlB[i]->ScrlB->Visible = ScrlB[i]->Addr.FuncEn();
	ScrlB[i]->ScrlB->Min = 0;
	ScrlB[i]->ScrlB->Max = (int) pow(2, ScrlB[i]->Addr.BitNum()) - 1;
	ScrlB[i]->ScrlB->OnChange = ScrollBar_Change;
	ScrlB[i]->ScrlB->Hint = i;
	ScrlB[i]->StTxt->Caption = 0;
	ScrlB[i]->Lbl->Caption = ScrlB[i]->Addr.Name();
    }
    JND_addr = OCE->SetJNDlut();
    ST_addr = OCE->SetSTlut();
    MAX_addr = OCE->SetMAXlut();
    MIN_addr = OCE->SetMINlut();

    Clear_JND_LUT(true);
    Clear_ST_LUT(true);
    Clear_MAX_LUT(true);
    Clear_MIN_LUT(true);
    CE_Chg = 1;
}

//---------------------------------------------------------------------------
int JND_lut[16];
int ST_lut[16];
int MAX_lut[16];
int MIN_lut[16];
void TCEForm::Clear_JND_LUT(bool type)
{
    if (type == true) {
	for (int i = 0; i < 16; i++)
	    JND_lut[i] = -1;
    }
    Graphics::TBitmap * LUT_Graph;
    LUT_Graph = new Graphics::TBitmap();
    LUT_Graph->Height = JND_LUT->Height;
    LUT_Graph->Width = JND_LUT->Width;
    JND_LUT->Canvas->Draw(0, 0, LUT_Graph);
    delete LUT_Graph;

    JND_LUT->Canvas->Pen->Color = clSilver;
    JND_LUT->Canvas->Brush->Color = clMoneyGreen;

    /*
       for(int b = 230; b > 0;  b=b-50, i++)
       for(int a = (i%2?40:140); a < 360;a+=200){
       JND_LUT->Canvas->Rectangle(a,(b<30?30:b),(a+100>360?360:a+100),b+50);
       } */
    JND_LUT->Canvas->Pen->Color = clBlack;
    JND_LUT->Canvas->Pen->Style = psSolid;
    JND_LUT->Canvas->Brush->Color = clWhite;
    JND_LUT->Canvas->TextOutA(20, 400, "0");
    JND_LUT->Canvas->TextOutA(135, 400, "5");
    JND_LUT->Canvas->TextOutA(230, 400, "10");
    JND_LUT->Canvas->TextOutA(330, 400, "15");


    JND_LUT->Canvas->TextOutA(20, 360, "20");
    JND_LUT->Canvas->TextOutA(20, 330, "40");
    JND_LUT->Canvas->TextOutA(20, 300, "60");
    JND_LUT->Canvas->TextOutA(20, 270, "80");
    JND_LUT->Canvas->TextOutA(20, 240, "100");
    JND_LUT->Canvas->TextOutA(20, 210, "120");
    JND_LUT->Canvas->TextOutA(20, 180, "140");
    JND_LUT->Canvas->TextOutA(20, 150, "160");
    JND_LUT->Canvas->TextOutA(20, 120, "180");
    JND_LUT->Canvas->TextOutA(20, 90, "200");
    JND_LUT->Canvas->TextOutA(20, 60, "220");
    JND_LUT->Canvas->TextOutA(20, 30, "240");
    JND_LUT->Canvas->TextOutA(20, 6, "256");

    JND_LUT->Canvas->MoveTo(40, 10);
    JND_LUT->Canvas->LineTo(40, 394);
    JND_LUT->Canvas->LineTo(380, 394);

    JND_LUT->Canvas->Pen->Color = clSilver;
    for (int i = 1; i <= 64; i++) {
	JND_LUT->Canvas->MoveTo(40, 394 - 6 * i);
	JND_LUT->Canvas->LineTo(360, 394 - 6 * i);
    }

    for (int i = 1; i <= 16; i++) {
	JND_LUT->Canvas->MoveTo(40 + 20 * i, 394);
	JND_LUT->Canvas->LineTo(40 + 20 * i, 10);
    }

    //黑線
    JND_LUT->Canvas->Pen->Color = clBlack;
    for (int i = 5; i <= 64; i += 5) {
	JND_LUT->Canvas->MoveTo(40, 394 - 6 * i);
	JND_LUT->Canvas->LineTo(360, 394 - 6 * i);
    }
    for (int i = 5; i <= 16; i += 5) {
	JND_LUT->Canvas->MoveTo(40 + 20 * i, 394);
	JND_LUT->Canvas->LineTo(40 + 20 * i, 10);
    }

    if (type == false) {
	for (int i = 0; i < 16; i++) {
	    if (JND_lut[i] != -1) {
		int x = i * 20 + 40 + 20;
		int y = 384 - JND_lut[i] / 2 * 3;
		JND_LUT->Canvas->Brush->Color = clMaroon;
		JND_LUT->Canvas->Ellipse(x - 5, y - 3 + 10, x + 5, y + 3 + 10);
	    }
	}
    }
    //Fill in JND StringGrid
    for (int i = 0; i < 16; i++)
	sg_JND_LUT->Cells[i][0] = JND_lut[i];

}

//---------------------------------------------------------------------------
void __fastcall TCEForm::JND_LUTMouseDown(TObject * Sender,
							TMouseButton Button, TShiftState Shift,
							int X, int Y)
{
    if (X >= (60 - 5) && X <= (360 + 5) && Y <= (394 + 3) && Y >= (10 - 3)) {
	int tmp_y;
	if (Y % 6 >= 3)
	    tmp_y = (floor((double) (Y - 10) / 6) + 1) * 6;	//上方預留空間10
	else
	    tmp_y = (floor((double) (Y - 10) / 6)) * 6;
	int tmp_x;
	if (X % 20 >= 10)
	    tmp_x = (floor((double) X / 20) + 1) * 20;
	else
	    tmp_x = (floor((double) X / 20)) * 20;

	int J_idx = 16 - (360 - (tmp_x - 20)) / 20;
	int J_var = (384 - tmp_y) / 3 * 2;	//原本的0~256=>0~384

	if (JND_lut[J_idx] == -1) {	//沒被點過的值
	    JND_lut[J_idx] = J_var;
	    JND_LUT->Canvas->Brush->Color = clMaroon;
	    JND_LUT->Canvas->Ellipse(tmp_x - 5, tmp_y - 3 + 10, tmp_x + 5, tmp_y + 3 + 10);
	    //Fill in JND StringGrid
	    sg_JND_LUT->Cells[J_idx][0] = JND_lut[J_idx];
	} else {		//被點過的值,重繪圖形
	    JND_lut[J_idx] = J_var;
	    Clear_JND_LUT(false);
	}
    }
}

//---------------------------------------------------------------------------
void __fastcall TCEForm::JND_WriteClick(TObject * Sender)
{
    if (JND_addr[0].LutNum() != 16) {
	ShowMessage("JND LUT number defined in AddressCE.cpp is wrong.");
	return;
    }

    for (int i = 0; i < 16; i++)
	JND_lut[i] = StrToInt(sg_JND_LUT->Cells[i][0]);
    EngineerForm->SetWrite_PG(JND_addr[0], JND_lut, 0);
}

//---------------------------------------------------------------------------
void __fastcall TCEForm::ST_WriteClick(TObject * Sender)
{
    if (ST_addr[0].LutNum() != 16) {
	ShowMessage("ST LUT number defined in AddressCE.cpp is wrong.");
	return;
    }

    for (int i = 0; i < 16; i++)
	ST_lut[i] = StrToInt(sg_ST_LUT->Cells[i][0]);
    EngineerForm->SetWrite_PG(ST_addr[0], ST_lut, 0);
}

//---------------------------------------------------------------------------
void __fastcall TCEForm::MAX_WriteClick(TObject * Sender)
{
    if (MAX_addr[0].LutNum() != 16) {
	ShowMessage("MAX LUT number defined in AddressCE.cpp is wrong.");
	return;
    }

    for (int i = 0; i < 16; i++)
	MAX_lut[i] = StrToInt(sg_MAX_LUT->Cells[i][0]);
    EngineerForm->SetWrite_PG(MAX_addr[0], MAX_lut, 0);
}

//---------------------------------------------------------------------------

void __fastcall TCEForm::MIN_WriteClick(TObject * Sender)
{
    if (MIN_addr[0].LutNum() != 16) {
	ShowMessage("MIN LUT number defined in AddressCE.cpp is wrong.");
	return;
    }

    for (int i = 0; i < 16; i++)
	MIN_lut[i] = StrToInt(sg_MIN_LUT->Cells[i][0]);
    EngineerForm->SetWrite_PG(MIN_addr[0], MIN_lut, 0);
}

//---------------------------------------------------------------------------

void __fastcall TCEForm::ST_LUTMouseDown(TObject * Sender,
						       TMouseButton Button, TShiftState Shift,
						       int X, int Y)
{
    if (X >= (60 - 5) && X <= (360 + 5) && Y <= (394 + 3) && Y >= (10 - 3)) {
	int tmp_y;
	if (Y % 6 >= 3)
	    tmp_y = (floor((double) (Y - 10) / 6) + 1) * 6;	//上方預留空間10
	else
	    tmp_y = (floor((double) (Y - 10) / 6)) * 6;
	int tmp_x;
	if (X % 20 >= 10)
	    tmp_x = (floor((double) X / 20) + 1) * 20;
	else
	    tmp_x = (floor((double) X / 20)) * 20;

	int S_idx = 16 - (360 - (tmp_x - 20)) / 20;
	int S_var = (384 - tmp_y) / 3 * 2;	//原本的0~256=>0~384

	if (ST_lut[S_idx] == -1) {	//沒被點過的值
	    ST_lut[S_idx] = S_var;
	    ST_LUT->Canvas->Brush->Color = clMaroon;
	    ST_LUT->Canvas->Ellipse(tmp_x - 5, tmp_y - 3 + 10, tmp_x + 5, tmp_y + 3 + 10);
	    //Fill in JND StringGrid
	    sg_ST_LUT->Cells[S_idx][0] = ST_lut[S_idx];
	} else {		//被點過的值,重繪圖形
	    ST_lut[S_idx] = S_var;
	    Clear_ST_LUT(false);
	}
    }
}

//---------------------------------------------------------------------------
void TCEForm::Clear_ST_LUT(bool type)
{
    if (type == true) {
	for (int i = 0; i < 16; i++)
	    ST_lut[i] = -1;
    }
    Graphics::TBitmap * LUT_Graph;
    LUT_Graph = new Graphics::TBitmap();
    LUT_Graph->Height = ST_LUT->Height;
    LUT_Graph->Width = ST_LUT->Width;
    ST_LUT->Canvas->Draw(0, 0, LUT_Graph);
    delete LUT_Graph;

    ST_LUT->Canvas->Pen->Color = clSilver;
    ST_LUT->Canvas->Brush->Color = clMoneyGreen;

    /*
       for(int b = 230; b > 0;  b=b-50, i++)
       for(int a = (i%2?40:140); a < 360;a+=200){
       JND_LUT->Canvas->Rectangle(a,(b<30?30:b),(a+100>360?360:a+100),b+50);
       } */
    ST_LUT->Canvas->Pen->Color = clBlack;
    ST_LUT->Canvas->Pen->Style = psSolid;
    ST_LUT->Canvas->Brush->Color = clWhite;
    ST_LUT->Canvas->TextOutA(20, 400, "0");
    ST_LUT->Canvas->TextOutA(135, 400, "5");
    ST_LUT->Canvas->TextOutA(230, 400, "10");
    ST_LUT->Canvas->TextOutA(330, 400, "15");

    ST_LUT->Canvas->TextOutA(20, 360, "20");
    ST_LUT->Canvas->TextOutA(20, 330, "40");
    ST_LUT->Canvas->TextOutA(20, 300, "60");
    ST_LUT->Canvas->TextOutA(20, 270, "80");
    ST_LUT->Canvas->TextOutA(20, 240, "100");
    ST_LUT->Canvas->TextOutA(20, 210, "120");
    ST_LUT->Canvas->TextOutA(20, 180, "140");
    ST_LUT->Canvas->TextOutA(20, 150, "160");
    ST_LUT->Canvas->TextOutA(20, 120, "180");
    ST_LUT->Canvas->TextOutA(20, 90, "200");
    ST_LUT->Canvas->TextOutA(20, 60, "220");
    ST_LUT->Canvas->TextOutA(20, 30, "240");
    ST_LUT->Canvas->TextOutA(20, 6, "256");

    ST_LUT->Canvas->MoveTo(40, 10);
    ST_LUT->Canvas->LineTo(40, 394);
    ST_LUT->Canvas->LineTo(380, 394);

    ST_LUT->Canvas->Pen->Color = clSilver;
    for (int i = 1; i <= 64; i++) {
	ST_LUT->Canvas->MoveTo(40, 394 - 6 * i);
	ST_LUT->Canvas->LineTo(360, 394 - 6 * i);
    }

    for (int i = 1; i <= 16; i++) {
	ST_LUT->Canvas->MoveTo(40 + 20 * i, 394);
	ST_LUT->Canvas->LineTo(40 + 20 * i, 10);
    }

    //黑線
    ST_LUT->Canvas->Pen->Color = clBlack;
    for (int i = 5; i <= 64; i += 5) {
	ST_LUT->Canvas->MoveTo(40, 394 - 6 * i);
	ST_LUT->Canvas->LineTo(360, 394 - 6 * i);
    }
    for (int i = 5; i <= 16; i += 5) {
	ST_LUT->Canvas->MoveTo(40 + 20 * i, 394);
	ST_LUT->Canvas->LineTo(40 + 20 * i, 10);
    }

    if (type == false) {
	for (int i = 0; i < 16; i++) {
	    if (ST_lut[i] != -1) {
		int x = i * 20 + 40 + 20;
		int y = 384 - ST_lut[i] / 2 * 3;
		ST_LUT->Canvas->Brush->Color = clMaroon;
		ST_LUT->Canvas->Ellipse(x - 5, y - 3 + 10, x + 5, y + 3 + 10);
	    }
	}
    }
    //Fill in ST StringGrid
    for (int i = 0; i < 16; i++)
	sg_ST_LUT->Cells[i][0] = ST_lut[i];
}

//--------------------------------------------------------------------------
void __fastcall TCEForm::MAX_LUTMouseDown(TObject * Sender,
							TMouseButton Button, TShiftState Shift,
							int X, int Y)
{
    if (X >= (60 - 5) && X <= (360 + 5) && Y <= (394 + 3) && Y >= (10 - 3)) {
	int tmp_y;
	if (Y % 6 >= 3)
	    tmp_y = (floor((double) (Y - 10) / 6) + 1) * 6;	//上方預留空間10
	else
	    tmp_y = (floor((double) (Y - 10) / 6)) * 6;
	int tmp_x;
	if (X % 20 >= 10)
	    tmp_x = (floor((double) X / 20) + 1) * 20;
	else
	    tmp_x = (floor((double) X / 20)) * 20;

	int M_idx = 16 - (360 - (tmp_x - 20)) / 20;
	int M_var = (384 - tmp_y) / 3 * 2;	//原本的0~256=>0~384

	if (MAX_lut[M_idx] == -1) {	//沒被點過的值
	    MAX_lut[M_idx] = M_var;
	    MAX_LUT->Canvas->Brush->Color = clMaroon;
	    MAX_LUT->Canvas->Ellipse(tmp_x - 5, tmp_y - 3 + 10, tmp_x + 5, tmp_y + 3 + 10);
	    //Fill in JND StringGrid
	    sg_MAX_LUT->Cells[M_idx][0] = MAX_lut[M_idx];
	} else {		//被點過的值,重繪圖形
	    MAX_lut[M_idx] = M_var;
	    Clear_MAX_LUT(false);
	}
    }
}

//---------------------------------------------------------------------------
void __fastcall TCEForm::MIN_LUTMouseDown(TObject * Sender,
							TMouseButton Button, TShiftState Shift,
							int X, int Y)
{
    if (X >= (60 - 5) && X <= (360 + 5) && Y <= (394 + 3) && Y >= (10 - 3)) {
	int tmp_y;
	if (Y % 6 >= 3)
	    tmp_y = (floor((double) (Y - 10) / 6) + 1) * 6;	//上方預留空間10
	else
	    tmp_y = (floor((double) (Y - 10) / 6)) * 6;
	int tmp_x;
	if (X % 20 >= 10)
	    tmp_x = (floor((double) X / 20) + 1) * 20;
	else
	    tmp_x = (floor((double) X / 20)) * 20;

	int M_idx = 16 - (360 - (tmp_x - 20)) / 20;
	int M_var = (384 - tmp_y) / 3 * 2;	//原本的0~256=>0~384

	if (MIN_lut[M_idx] == -1) {	//沒被點過的值
	    MIN_lut[M_idx] = M_var;
	    MIN_LUT->Canvas->Brush->Color = clMaroon;
	    MIN_LUT->Canvas->Ellipse(tmp_x - 5, tmp_y - 3 + 10, tmp_x + 5, tmp_y + 3 + 10);
	    //Fill in JND StringGrid
	    sg_MIN_LUT->Cells[M_idx][0] = MIN_lut[M_idx];
	} else {		//被點過的值,重繪圖形
	    MIN_lut[M_idx] = M_var;
	    Clear_MIN_LUT(false);
	}
    }
}

//---------------------------------------------------------------------------
void TCEForm::Clear_MAX_LUT(bool type)
{
    if (type == true) {
	for (int i = 0; i < 16; i++)
	    MAX_lut[i] = -1;
    }
    Graphics::TBitmap * LUT_Graph;
    LUT_Graph = new Graphics::TBitmap();
    LUT_Graph->Height = MAX_LUT->Height;
    LUT_Graph->Width = MAX_LUT->Width;
    MAX_LUT->Canvas->Draw(0, 0, LUT_Graph);
    delete LUT_Graph;

    MAX_LUT->Canvas->Pen->Color = clSilver;
    MAX_LUT->Canvas->Brush->Color = clMoneyGreen;

    /*
       for(int b = 230; b > 0;  b=b-50, i++)
       for(int a = (i%2?40:140); a < 360;a+=200){
       JND_LUT->Canvas->Rectangle(a,(b<30?30:b),(a+100>360?360:a+100),b+50);
       } */
    MAX_LUT->Canvas->Pen->Color = clBlack;
    MAX_LUT->Canvas->Pen->Style = psSolid;
    MAX_LUT->Canvas->Brush->Color = clWhite;
    MAX_LUT->Canvas->TextOutA(20, 400, "0");
    MAX_LUT->Canvas->TextOutA(135, 400, "5");
    MAX_LUT->Canvas->TextOutA(230, 400, "10");
    MAX_LUT->Canvas->TextOutA(330, 400, "15");

    MAX_LUT->Canvas->TextOutA(20, 360, "20");
    MAX_LUT->Canvas->TextOutA(20, 330, "40");
    MAX_LUT->Canvas->TextOutA(20, 300, "60");
    MAX_LUT->Canvas->TextOutA(20, 270, "80");
    MAX_LUT->Canvas->TextOutA(20, 240, "100");
    MAX_LUT->Canvas->TextOutA(20, 210, "120");
    MAX_LUT->Canvas->TextOutA(20, 180, "140");
    MAX_LUT->Canvas->TextOutA(20, 150, "160");
    MAX_LUT->Canvas->TextOutA(20, 120, "180");
    MAX_LUT->Canvas->TextOutA(20, 90, "200");
    MAX_LUT->Canvas->TextOutA(20, 60, "220");
    MAX_LUT->Canvas->TextOutA(20, 30, "240");
    MAX_LUT->Canvas->TextOutA(20, 6, "256");

    MAX_LUT->Canvas->MoveTo(40, 10);
    MAX_LUT->Canvas->LineTo(40, 394);
    MAX_LUT->Canvas->LineTo(380, 394);

    MAX_LUT->Canvas->Pen->Color = clSilver;
    for (int i = 1; i <= 64; i++) {
	MAX_LUT->Canvas->MoveTo(40, 394 - 6 * i);
	MAX_LUT->Canvas->LineTo(360, 394 - 6 * i);
    }

    for (int i = 1; i <= 16; i++) {
	MAX_LUT->Canvas->MoveTo(40 + 20 * i, 394);
	MAX_LUT->Canvas->LineTo(40 + 20 * i, 10);
    }

    //黑線
    MAX_LUT->Canvas->Pen->Color = clBlack;
    for (int i = 5; i <= 64; i += 5) {
	MAX_LUT->Canvas->MoveTo(40, 394 - 6 * i);
	MAX_LUT->Canvas->LineTo(360, 394 - 6 * i);
    }
    for (int i = 5; i <= 16; i += 5) {
	MAX_LUT->Canvas->MoveTo(40 + 20 * i, 394);
	MAX_LUT->Canvas->LineTo(40 + 20 * i, 10);
    }

    if (type == false) {
	for (int i = 0; i < 16; i++) {
	    if (MAX_lut[i] != -1) {
		int x = i * 20 + 40 + 20;
		int y = 384 - MAX_lut[i] / 2 * 3;
		MAX_LUT->Canvas->Brush->Color = clMaroon;
		MAX_LUT->Canvas->Ellipse(x - 5, y - 3 + 10, x + 5, y + 3 + 10);
	    }
	}
    }
    //Fill in MAX StringGrid
    for (int i = 0; i < 16; i++)
	sg_MAX_LUT->Cells[i][0] = MAX_lut[i];
}

//--------------------------------------------------------------------------

void TCEForm::Clear_MIN_LUT(bool type)
{
    if (type == true) {
	for (int i = 0; i < 16; i++)
	    MIN_lut[i] = -1;
    }
    Graphics::TBitmap * LUT_Graph;
    LUT_Graph = new Graphics::TBitmap();
    LUT_Graph->Height = MIN_LUT->Height;
    LUT_Graph->Width = MIN_LUT->Width;
    MIN_LUT->Canvas->Draw(0, 0, LUT_Graph);
    delete LUT_Graph;

    MIN_LUT->Canvas->Pen->Color = clSilver;
    MIN_LUT->Canvas->Brush->Color = clMoneyGreen;

    /*
       for(int b = 230; b > 0;  b=b-50, i++)
       for(int a = (i%2?40:140); a < 360;a+=200){
       JND_LUT->Canvas->Rectangle(a,(b<30?30:b),(a+100>360?360:a+100),b+50);
       } */
    MIN_LUT->Canvas->Pen->Color = clBlack;
    MIN_LUT->Canvas->Pen->Style = psSolid;
    MIN_LUT->Canvas->Brush->Color = clWhite;
    MIN_LUT->Canvas->TextOutA(20, 400, "0");
    MIN_LUT->Canvas->TextOutA(135, 400, "5");
    MIN_LUT->Canvas->TextOutA(230, 400, "10");
    MIN_LUT->Canvas->TextOutA(330, 400, "15");

    MIN_LUT->Canvas->TextOutA(20, 360, "20");
    MIN_LUT->Canvas->TextOutA(20, 330, "40");
    MIN_LUT->Canvas->TextOutA(20, 300, "60");
    MIN_LUT->Canvas->TextOutA(20, 270, "80");
    MIN_LUT->Canvas->TextOutA(20, 240, "100");
    MIN_LUT->Canvas->TextOutA(20, 210, "120");
    MIN_LUT->Canvas->TextOutA(20, 180, "140");
    MIN_LUT->Canvas->TextOutA(20, 150, "160");
    MIN_LUT->Canvas->TextOutA(20, 120, "180");
    MIN_LUT->Canvas->TextOutA(20, 90, "200");
    MIN_LUT->Canvas->TextOutA(20, 60, "220");
    MIN_LUT->Canvas->TextOutA(20, 30, "240");
    MIN_LUT->Canvas->TextOutA(20, 6, "256");

    MIN_LUT->Canvas->MoveTo(40, 10);
    MIN_LUT->Canvas->LineTo(40, 394);
    MIN_LUT->Canvas->LineTo(380, 394);

    MIN_LUT->Canvas->Pen->Color = clSilver;
    for (int i = 1; i <= 64; i++) {
	MIN_LUT->Canvas->MoveTo(40, 394 - 6 * i);
	MIN_LUT->Canvas->LineTo(360, 394 - 6 * i);
    }

    for (int i = 1; i <= 16; i++) {
	MIN_LUT->Canvas->MoveTo(40 + 20 * i, 394);
	MIN_LUT->Canvas->LineTo(40 + 20 * i, 10);
    }

    //黑線
    MIN_LUT->Canvas->Pen->Color = clBlack;
    for (int i = 5; i <= 64; i += 5) {
	MIN_LUT->Canvas->MoveTo(40, 394 - 6 * i);
	MIN_LUT->Canvas->LineTo(360, 394 - 6 * i);
    }
    for (int i = 5; i <= 16; i += 5) {
	MIN_LUT->Canvas->MoveTo(40 + 20 * i, 394);
	MIN_LUT->Canvas->LineTo(40 + 20 * i, 10);
    }

    if (type == false) {
	for (int i = 0; i < 16; i++) {
	    if (MIN_lut[i] != -1) {
		int x = i * 20 + 40 + 20;
		int y = 384 - MIN_lut[i] / 2 * 3;
		MIN_LUT->Canvas->Brush->Color = clMaroon;
		MIN_LUT->Canvas->Ellipse(x - 5, y - 3 + 10, x + 5, y + 3 + 10);
	    }
	}
    }
    //Fill in MIN StringGrid
    for (int i = 0; i < 16; i++)
	sg_MIN_LUT->Cells[i][0] = MIN_lut[i];
}

//---------------------------------------------------------------------------


void __fastcall TCEForm::btn_CE_loadClick(TObject * Sender)
{
    btn_CE_load->Enabled = false;
    if (!OpenDialog1->Execute())
	return;
    String Fpath;
    Fpath = OpenDialog1->FileName;
    btn_CE_load->Enabled = false;
    btn_CE_save->Enabled = false;
    rg_ce_mode->Enabled = false;
    Load_CEini(Fpath);
    btn_CE_load->Enabled = true;
    btn_CE_save->Enabled = true;
    rg_ce_mode->Enabled = true;
    btn_wrt_allClick(Sender);
    btn_CE_load->Enabled = true;
}

//---------------------------------------------------------------------------
bool TCEForm::Load_CEini(String Fpath)
{
    long lSize;
    char *Buffer;
    FILE *fptr;
    if ((fptr = fopen(Fpath.c_str(), "r")) == NULL)
	return 0;

    // obtain file size:
    fseek(fptr, 0, SEEK_END);
    lSize = ftell(fptr);
    rewind(fptr);

    // allocate memory to contain the whole file:
    Buffer = (char *) malloc(sizeof(char) * lSize);
    if (Buffer == NULL)
	return 0;
    // copy the file into the buffer:
    fread(Buffer, 1, lSize, fptr);
    fclose(fptr);

    //------------Load CE value to interface-----------------------------

    AnsiString Str[29];
    //CheckBox
    Str[0] = "SPRS_BLK1";
    Str[1] = "SPRS_BLK0";
    Str[2] = "PURITYWT_EN";
    Str[3] = "GRAD_EN";
    Str[4] = "FASTCHG_EN";
    Str[5] = "MLC_EN";
    //ComboBox
    Str[6] = "MAXLIMT_SEL";
    Str[7] = "PIXHIST_SEL";
    Str[8] = "LOWST_SEL";
    Str[9] = "JND_SEL";
    Str[10] = "ST_SEL";
    //ScrollBar
    Str[11] = "GRAD_GMA_STEP";
    Str[12] = "GRAD_FRM_STEP";
    Str[13] = "GRAD_PIXDIFF_THR";
    Str[14] = "STRENGTH_K";
    Str[15] = "MIN_EDGE";
    Str[16] = "PIX_DIFF_THR";
    Str[17] = "EDG_DIFF_THR";
    Str[18] = "MLC_THR";
    Str[19] = "PATDET_FRM_NUM";
    Str[20] = "PATDET_LINE_NUM";
    Str[21] = "JND_MAX";
    Str[22] = "JND_MIN";
    Str[23] = "ST_MAX";
    Str[24] = "ST_MIN";
    //Table
    Str[25] = "JND_LUT";
    Str[26] = "ST_LUT";
    Str[27] = "MAX_LUT";
    Str[28] = "MIN_LUT";

    char *buffer;
    char *pch;
    bool match = false;
    //CheckBox
    for (int i = 0; i < 25; i++) {
	match = false;
	buffer = (char *) malloc(sizeof(char) * lSize);
	strncpy(buffer, Buffer, lSize);
	pch = strtok(buffer, "\n\t");
	while (!SameText((AnsiString) pch, Str[i])) {
	    if (pch == NULL) {
		ShowMessage("Can't Find" + Str[i]);
		return 0;	//資料中沒有
	    }
	    pch = strtok(NULL, "\n\t");
	}
	pch = strtok(NULL, "\n\t");
	for (int j = 0; j < OCE->CEChkBox_Nbr; j++) {
	    if (SameText(Str[i], ChkB[j]->Addr.Name())) {
		ChkB[j]->Chkb->Checked = (StrToInt(pch) == 1 ? 1 : 0);
		match = true;
		break;
	    }
	}
	if (!match) {
	    for (int j = 0; j < OCE->CECboBox_Nbr; j++) {
		if (SameText(Str[i], CboB[j]->Addr.Name())) {
		    CboB[j]->Cbob->ItemIndex = StrToInt(pch);
		    match = true;
		    break;
		}
	    }
	}
	if (!match) {
	    for (int j = 0; j < OCE->CEScrollBar_Nbr; j++) {
		if (SameText(Str[i], ScrlB[j]->Addr.Name())) {
		    ScrlB[j]->ScrlB->Position = StrToInt(pch);
		    break;
		}
	    }
	}
	delete[]buffer;
    }

    //-----------------LUT------------------------------
    for (int i = 0; i < 16; i++) {
	JND_lut[i] = 0;
	ST_lut[i] = 0;
	MAX_lut[i] = 0;
	MIN_lut[i] = 0;
    }

    char *str[4];
    str[0] = "JND_LUT";
    str[1] = "ST__LUT";
    str[2] = "MAX_LUT";
    str[3] = "MIN_LUT";

    for (int i = 0; i < 4; i++) {
	buffer = (char *) malloc(sizeof(char) * lSize);
	strncpy(buffer, Buffer, lSize);
	pch = strtok(buffer, "\n\t");
	while (SameText((AnsiString) pch, str[i]) != 1) {
	    if (pch == NULL)
		return 0;
	    pch = strtok(NULL, "\n\t");
	}

	int c = 0;
	pch = strtok(NULL, "\n\t");
	while (c < 16 && pch != NULL) {
	    if (pch == NULL)
		return 0;	//資料中的data缺少
	    if (i == 0)
		JND_lut[c] = StrToInt((AnsiString) pch);
	    else if (i == 1)
		ST_lut[c] = StrToInt((AnsiString) pch);
	    else if (i == 2)
		MAX_lut[c] = StrToInt((AnsiString) pch);
	    else
		MIN_lut[c] = StrToInt((AnsiString) pch);

	    pch = strtok(NULL, "\n\t");
	    c++;
	}
	delete[]buffer;
    }
    delete[]Buffer;

    for (int i = 0; i < 16; i++) {
	sg_JND_LUT->Cells[i][0] = JND_lut[i];
	sg_ST_LUT->Cells[i][0] = ST_lut[i];
	sg_MAX_LUT->Cells[i][0] = MAX_lut[i];
	sg_MIN_LUT->Cells[i][0] = MIN_lut[i];
    }
    return 1;
}

//--------------------------------------------------------------------------
void __fastcall TCEForm::btn_wrt_allClick(TObject * Sender)
{
    if (CE_Chg == 0) {
	ShowMessage("Previous write is not over yet.");
	return;
    }
    btn_wrt_all->Enabled = false;
    for (int i = 0; i < OCE->CEChkBox_Nbr; i++) {
	ChkB[i]->Chkb->OnClick;
    }
    for (int i = 0; i < OCE->CECboBox_Nbr; i++) {
	CboB[i]->Cbob->OnChange;
    }
    for (int i = 0; i < OCE->CEScrollBar_Nbr; i++) {
	ScrlB[i]->ScrlB->OnChange;
    }
    JND_WriteClick(Sender);
    ST_WriteClick(Sender);
    MAX_WriteClick(Sender);
    MIN_WriteClick(Sender);
    Clear_JND_LUT(false);
    Clear_ST_LUT(false);
    Clear_MAX_LUT(false);
    Clear_MIN_LUT(false);
    btn_wrt_all->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TCEForm::btn_CE_saveClick(TObject * Sender)
{
    btn_CE_save->Enabled = false;
    FILE *fptr;
    if (!SaveDialog1->Execute())
	return;
    String Fpath = SaveDialog1->FileName;
    if ((fptr = fopen(Fpath.c_str(), "w")) == NULL)
	return;

    for (int i = 0; i < OCE->CEChkBox_Nbr; i++) {
	fprintf(fptr, "%s\t%d\n", ChkB[i]->Addr.Name(), (ChkB[i]->Chkb->Checked ? 1 : 0));
    }
    for (int i = 0; i < OCE->CECboBox_Nbr; i++) {
	fprintf(fptr, "%s\t%d\n", CboB[i]->Addr.Name(), CboB[i]->Cbob->ItemIndex);
    }
    for (int i = 0; i < OCE->CEScrollBar_Nbr; i++) {
	fprintf(fptr, "%s\t%d\n", ScrlB[i]->Addr.Name(), ScrlB[i]->ScrlB->Position);
    }
    fprintf(fptr, "JND_LUT\n");
    for (int i = 0; i < 16; i++) {
	fprintf(fptr, "%s\t", sg_JND_LUT->Cells[i][0]);
	if (i % 4 == 3)
	    fprintf(fptr, "\n");
    }

    fprintf(fptr, "ST__LUT\n");
    for (int i = 0; i < 16; i++) {
	fprintf(fptr, "%s\t", sg_ST_LUT->Cells[i][0]);
	if (i % 4 == 3)
	    fprintf(fptr, "\n");
    }

    fprintf(fptr, "MAX_LUT\n");
    for (int i = 0; i < 16; i++) {
	fprintf(fptr, "%s\t", sg_MAX_LUT->Cells[i][0]);
	if (i % 4 == 3)
	    fprintf(fptr, "\n");
    }

    fprintf(fptr, "MIN_LUT\n");
    for (int i = 0; i < 16; i++) {
	fprintf(fptr, "%s\t", sg_MIN_LUT->Cells[i][0]);
	if (i % 4 == 3)
	    fprintf(fptr, "\n");
    }
    btn_CE_save->Enabled = true;
    fclose(fptr);
}

//---------------------------------------------------------------------------

void __fastcall TCEForm::btn_JND_ClearClick(TObject * Sender)
{
    Clear_JND_LUT(true);
}

//---------------------------------------------------------------------------

void __fastcall TCEForm::btn_ST_ClearClick(TObject * Sender)
{
    Clear_ST_LUT(true);
}

//---------------------------------------------------------------------------

void __fastcall TCEForm::btn_MAX_ClearClick(TObject * Sender)
{
    Clear_MAX_LUT(true);
}

//---------------------------------------------------------------------------

void __fastcall TCEForm::btn_MIN_ClearClick(TObject * Sender)
{
    Clear_MIN_LUT(true);
}

//---------------------------------------------------------------------------

void __fastcall TCEForm::rg_ce_modeClick(TObject * Sender)
{
    String Fpath;

    if (rg_ce_mode->ItemIndex == 0)
	Fpath = "\CE_default1.txt";
    else if (rg_ce_mode->ItemIndex == 1)
	Fpath = "\CE_default2.txt";
    else if (rg_ce_mode->ItemIndex == 2)
	Fpath = "\CE_default3.txt";

    btn_CE_load->Enabled = false;
    btn_CE_save->Enabled = false;
    rg_ce_mode->Enabled = false;
    if (Load_CEini(Fpath))
	btn_wrt_allClick(Sender);
    btn_CE_load->Enabled = true;
    btn_CE_save->Enabled = true;
    rg_ce_mode->Enabled = true;
}

//---------------------------------------------------------------------------



void __fastcall TCEForm::JND_ReadClick(TObject * Sender)
{
    EngineerForm->SetRead_PG(JND_addr[0], JND_lut, 0);
    for (int i = 0; i < 16; i++)
	sg_JND_LUT->Cells[i][0] = IntToStr(JND_lut[i]);
    Clear_JND_LUT(false);
}

//---------------------------------------------------------------------------


void __fastcall TCEForm::ST_ReadClick(TObject * Sender)
{
    EngineerForm->SetRead_PG(ST_addr[0], ST_lut, 0);
    for (int i = 0; i < 16; i++)
	sg_ST_LUT->Cells[i][0] = IntToStr(ST_lut[i]);
    Clear_ST_LUT(false);
}

//---------------------------------------------------------------------------

void __fastcall TCEForm::MAX_ReadClick(TObject * Sender)
{
    EngineerForm->SetRead_PG(MAX_addr[0], MAX_lut, 0);
    for (int i = 0; i < 16; i++)
	sg_MAX_LUT->Cells[i][0] = IntToStr(MAX_lut[i]);
    Clear_MAX_LUT(false);
}

//---------------------------------------------------------------------------

void __fastcall TCEForm::MIN_ReadClick(TObject * Sender)
{
    EngineerForm->SetRead_PG(MIN_addr[0], MIN_lut, 0);
    for (int i = 0; i < 16; i++)
	sg_MIN_LUT->Cells[i][0] = IntToStr(MIN_lut[i]);
    Clear_MIN_LUT(false);
}

//---------------------------------------------------------------------------

void __fastcall TCEForm::Btn_CE_reloadClick(TObject * Sender)
{
    Btn_CE_reload->Enabled = false;
    unsigned char read_val;
    for (int i = 0; i < OCE->CEChkBox_Nbr; i++) {
	if (ChkB[i]->Chkb->Visible == true) {
	    EngineerForm->SetRead_Byte(ChkB[i]->Addr, &read_val);
	    if (read_val == 1)
		ChkB[i]->Chkb->Checked = 1;
	    else if (read_val == 0)
		ChkB[i]->Chkb->Checked = 0;
	    else
		ShowMessage("CE CheckBox read error:" + IntToStr(read_val));
	}
    }
    for (int i = 0; i < OCE->CECboBox_Nbr; i++) {
	if (CboB[i]->Cbob->Visible == true) {
	    EngineerForm->SetRead_Byte(CboB[i]->Addr, &read_val);
	    CboB[i]->Cbob->ItemIndex = read_val;
	}
    }

    for (int i = 0; i < OCE->CEScrollBar_Nbr; i++) {
	if (ScrlB[i]->ScrlB->Visible == true) {
	    EngineerForm->SetRead_Byte(ScrlB[i]->Addr, &read_val);
	    ScrlB[i]->ScrlB->Position = read_val;
	    ScrlB[i]->StTxt->Caption = read_val;
	}
    }
    JND_ReadClick(Sender);
    ST_ReadClick(Sender);
    MAX_ReadClick(Sender);
    MIN_ReadClick(Sender);
    Btn_CE_reload->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TCEForm::FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift)
{
    if (Key == 0x40) {
	Btn_CE_reloadClick(Sender);
    }
}

//---------------------------------------------------------------------------

void __fastcall TCEForm::FormClose(TObject * Sender, TCloseAction & Action)
{
    delete[]OCE;
    Action = caFree;
    //MainForm->CEFormNULL();
}

//---------------------------------------------------------------------------

