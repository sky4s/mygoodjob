//---------------------------------------------------------------------------

#include <vcl.h>
#include <lib/CMSCpp2.1/src/includeall.h>
#pragma hdrstop

#include "Offset_11307.h"
#include "TOffsetForm.h"
#include "include.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOffsetForm *offsetForm;
//---------------------------------------------------------------------------
__fastcall TOffsetForm::TOffsetForm(TComponent * Owner)
:TForm(Owner)
{
    IsChg = 0;
}

//---------------------------------------------------------------------------
void __fastcall TOffsetForm::ScrollBar_Scroll(TObject * Sender, TScrollCode ScrollCode,
					      int &ScrollPos)
{
    TCheckBox *c = (TCheckBox *) Sender;
    //從check box找到index
    int idx = StrToInt(c->Hint);
    //從check找到scrollbar, 還有pos
    int set_val = (ScrlB[idx]->ScrlB->Position);
    //把pos指到label
    ScrlB[idx]->StTxt->Caption = set_val;
    if (ScrollCode == scEndScroll) {
	//滑鼠放開, 或鍵盤操作放開
	if (IsChg == 0) {
	    return;
	}
	EngineerForm->SetWrite_Byte(ScrlB[idx]->Addr, set_val);
    }
}

//---------------------------------------------------------------------------
void __fastcall TOffsetForm::ScrollBar2_Scroll(TObject * Sender, TScrollCode ScrollCode,
					       int &ScrollPos)
{
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (ScrlB2[idx]->ScrlB->Position);
    ScrlB2[idx]->StTxt->Caption = set_val;

    if (ScrollCode == scEndScroll) {
	//滑鼠放開, 或鍵盤操作放開
	if (IsChg == 0)
	    return;
	int val1 = set_val / ScrlB2[idx]->Addr.Divide();
	int val2 = set_val % ScrlB2[idx]->Addr.Divide();
	EngineerForm->SetWrite_Byte(ScrlB2[idx]->Addr.Byte1, val1);
	EngineerForm->SetWrite_Byte(ScrlB2[idx]->Addr.Byte2, val2);
    }
}

//---------------------------------------------------------------------------
void __fastcall TOffsetForm::CheckBox_Click(TObject * Sender)
{
    if (IsChg == 0)
	return;
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (ChkB[idx]->Chkb->Checked ? 1 : 0);

    EngineerForm->SetWrite_Byte(ChkB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void __fastcall TOffsetForm::ComboBox_Click(TObject * Sender)
{
    if (IsChg == 0)
	return;
    TComboBox *c = (TComboBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (CboB[idx]->Cbob->ItemIndex);
    EngineerForm->SetWrite_Byte(CboB[idx]->Addr, set_val);
}

//----------------------------------------------------------------------------

void __fastcall TOffsetForm::LblE3_KeyPress(TObject * Sender, char &Key)
{
    TLabeledEdit *c = (TLabeledEdit *) Sender;
    int idx = StrToInt(c->Hint);

    if (Key != 13) {
	LblE3[idx]->Lble->Font->Color = cl3DDkShadow;
	return;
    }
    //Key = 13, 按下Enter
    String tmp_v = LblE3[idx]->Lble->Text;
    if (tmp_v == "") {
	tmp_v = "0";
    }
    int set_val = StrToInt(tmp_v);

    if (IsChg == 0)
	return;

    unsigned char val1, val2, val3;
    //add for Max hint
    if (set_val >= pow(2, LblE3[idx]->Addr.BitNum())) {
	AnsiString max = "Max value:" + IntToStr((int) pow(2, LblE3[idx]->Addr.BitNum()) - 1);
	ShowMessage(max);
	//read value
	EngineerForm->SetRead_Byte(LblE3[idx]->Addr.Byte1, &val1);
	EngineerForm->SetRead_Byte(LblE3[idx]->Addr.Byte2, &val2);
	EngineerForm->SetRead_Byte(LblE3[idx]->Addr.Byte3, &val3);
	LblE3[idx]->Lble->Text = (int) val1 *LblE3[idx]->Addr.Divide1()
	+ (int) val2 *LblE3[idx]->Addr.Divide2() + (int) val3;
    } else {
	val1 = set_val / LblE3[idx]->Addr.Divide1();
	val2 =
	    (set_val / LblE3[idx]->Addr.Divide2()) % (int) pow(2, LblE3[idx]->Addr.Byte2.BitNum());
	val3 = set_val % LblE3[idx]->Addr.Divide2();
	EngineerForm->SetWrite_Byte(LblE3[idx]->Addr.Byte1, val1);
	if (LblE3[idx]->Addr.Byte2.BitNum() != 0)
	    EngineerForm->SetWrite_Byte(LblE3[idx]->Addr.Byte2, val2);
	if (LblE3[idx]->Addr.Byte3.BitNum() != 0)
	    EngineerForm->SetWrite_Byte(LblE3[idx]->Addr.Byte3, val3);
	LblE3[idx]->Lble->Font->Color = clWindowText;
    }
}

//---------------------------------------------------------------------------
void __fastcall TOffsetForm::LblE4_KeyPress(TObject * Sender, char &Key)
{
    TLabeledEdit *c = (TLabeledEdit *) Sender;
    int idx = StrToInt(c->Hint);

    if (Key != 13) {
	LblE4[idx]->Lble->Font->Color = cl3DDkShadow;
	return;
    }
    //Key = 13, 按下Enter
    String tmp_v = LblE4[idx]->Lble->Text;
    if (tmp_v == "") {
	tmp_v = "0";
    }
    int set_val = StrToInt(tmp_v);

    if (IsChg == 0)
	return;

    unsigned char val1, val2, val3, val4;
    //add for Max hint
    if (set_val >= pow(2, LblE4[idx]->Addr.BitNum())) {
	AnsiString max = "Max value:" + IntToStr((int) pow(2, LblE4[idx]->Addr.BitNum()) - 1);
	ShowMessage(max);
	//read value
	EngineerForm->SetRead_Byte(LblE4[idx]->Addr.Byte1, &val1);
	EngineerForm->SetRead_Byte(LblE4[idx]->Addr.Byte2, &val2);
	EngineerForm->SetRead_Byte(LblE4[idx]->Addr.Byte3, &val3);
	EngineerForm->SetRead_Byte(LblE4[idx]->Addr.Byte4, &val4);
	LblE4[idx]->Lble->Text = (int) val1 *LblE4[idx]->Addr.Divide1()
	+ (int) val2 *LblE4[idx]->Addr.Divide2()
	+ (int) val3 *LblE4[idx]->Addr.Divide3() + (int) val4;
    } else {
	val1 = set_val / LblE4[idx]->Addr.Divide1();
	set_val -= val1 * LblE4[idx]->Addr.Divide1();

	val2 = set_val / LblE4[idx]->Addr.Divide2();
	set_val -= val2 * LblE4[idx]->Addr.Divide2();

	val3 = set_val / LblE4[idx]->Addr.Divide3();
	set_val -= val3 * LblE4[idx]->Addr.Divide3();

	val4 = set_val % LblE4[idx]->Addr.Divide3();

	EngineerForm->SetWrite_Byte(LblE4[idx]->Addr.Byte1, val1);
	if (LblE4[idx]->Addr.Byte2.BitNum() != 0)
	    EngineerForm->SetWrite_Byte(LblE4[idx]->Addr.Byte2, val2);
	if (LblE4[idx]->Addr.Byte3.BitNum() != 0)
	    EngineerForm->SetWrite_Byte(LblE4[idx]->Addr.Byte3, val3);
	if (LblE4[idx]->Addr.Byte4.BitNum() != 0)
	    EngineerForm->SetWrite_Byte(LblE4[idx]->Addr.Byte4, val4);

	LblE4[idx]->Lble->Font->Color = clWindowText;
    }
}

void __fastcall TOffsetForm::FormCreate(TObject * Sender)
{
    /*int ic_choice;
       if (MainForm->TCON_DEV == "11307")
       ic_choice = 0;

       switch (ic_choice) {
       case 0: */
    OoffsetForm = new OffsetForm_11307;
    /*break;

       }     */

	/****************************************************************
        //      CheckBox: ChkBox_Nbr=3                                   //
        //                                                              //
        *****************************************************************/

    cb = OoffsetForm->SetChkBx();
    ChkB = new _CHKB *[OoffsetForm->ChkBox_Nbr];
    for (int i = 0; i < OoffsetForm->ChkBox_Nbr; i++)
	ChkB[i] = new _CHKB;

    ChkB[0]->Chkb = CheckBox1;
    ChkB[1]->Chkb = CheckBox2;
    ChkB[2]->Chkb = CheckBox3;

    for (int i = 0; i < OoffsetForm->ChkBox_Nbr; i++) {
	ChkB[i]->Addr = cb[i];
	ChkB[i]->Chkb->Visible = ChkB[i]->Addr.FuncEn();
	ChkB[i]->Chkb->OnClick = CheckBox_Click;
	ChkB[i]->Chkb->Hint = i;
	ChkB[i]->Chkb->Caption = ChkB[i]->Addr.Name();
    }

	/*****************************************************************
        //      ComboBox: CboBox_Nbr=0                                   //
        //                                                              //
        *****************************************************************/

    cbo = OoffsetForm->SetCboBx();

    CboB = new _CBOB *[OoffsetForm->CboBox_Nbr];
    for (int i = 0; i < OoffsetForm->CboBox_Nbr; i++)
	CboB[i] = new _CBOB;

    // CboB[0]->Cbob = ComboBox1;
    // CboB[0]->CbobL= Label2;

    for (int i = 0; i < OoffsetForm->CboBox_Nbr; i++) {
	CboB[i]->Addr = cbo[i];
	CboB[i]->Cbob->Visible = CboB[i]->Addr.FuncEn();
	CboB[i]->CbobL->Visible = CboB[i]->Addr.FuncEn();
	CboB[i]->Cbob->OnClick = ComboBox_Click;
	CboB[i]->Cbob->Hint = i;
	CboB[i]->CbobL->Caption = CboB[i]->Addr.Name();
	CboB[i]->Cbob->Text = "";
	if (CboB[i]->Addr.FuncEn() == true)
	    for (int j = 0; j < CboB[i]->Addr.choice_nbr; j++)	//ComboBox choice
		CboB[i]->Cbob->Items->Add(CboB[i]->Addr.choice[j]);
    }

	/*****************************************************************
        //      ScrollBar: ScrollBar_Nbr=1                               //
        //                                                              //
        *****************************************************************/

    scrlb = OoffsetForm->SetScrollBar();

    ScrlB = new _ScrollBar *[OoffsetForm->ScrollBar_Nbr];
    for (int i = 0; i < OoffsetForm->ScrollBar_Nbr; i++)
	ScrlB[i] = new _ScrollBar;

    ScrlB[0]->Lbl = Label1;
    ScrlB[0]->StTxt = StaticText1;
    ScrlB[0]->ScrlB = ScrollBar1;

    for (int i = 0; i < OoffsetForm->ScrollBar_Nbr; i++) {
	ScrlB[i]->Addr = scrlb[i];
	ScrlB[i]->Lbl->Visible = ScrlB[i]->Addr.FuncEn();
	ScrlB[i]->StTxt->Visible = ScrlB[i]->Addr.FuncEn();
	ScrlB[i]->ScrlB->Visible = ScrlB[i]->Addr.FuncEn();
	ScrlB[i]->ScrlB->Min = 0;
	ScrlB[i]->ScrlB->Max = (int) pow(2, ScrlB[i]->Addr.BitNum()) - 1;
	ScrlB[i]->ScrlB->OnScroll = ScrollBar_Scroll;
	ScrlB[i]->ScrlB->Hint = i;
	ScrlB[i]->StTxt->Caption = 0;
	ScrlB[i]->Lbl->Caption = ScrlB[i]->Addr.Name();
    }

	/*****************************************************************
        //      ScrollBar2: ScrollBar2_Nbr=                             //
        //                                                              //
        *****************************************************************/

    scrlb2 = OoffsetForm->SetScrollBar2();

    ScrlB2 = new _ScrollBar2 *[OoffsetForm->ScrollBar2_Nbr];
    for (int i = 0; i < OoffsetForm->ScrollBar2_Nbr; i++) {
	ScrlB2[i] = new _ScrollBar2;
    }

    //ScrlB2[0]->Lbl = Label3;
    //ScrlB2[0]->StTxt = StaticText12;
    //ScrlB2[0]->ScrlB = ScrollBar12;

    for (int i = 0; i < OoffsetForm->ScrollBar2_Nbr; i++) {
	ScrlB2[i]->Addr = scrlb2[i];
	ScrlB2[i]->Lbl->Visible = ScrlB2[i]->Addr.FuncEn();
	ScrlB2[i]->StTxt->Visible = ScrlB2[i]->Addr.FuncEn();
	ScrlB2[i]->ScrlB->Visible = ScrlB2[i]->Addr.FuncEn();
	ScrlB2[i]->ScrlB->Min = 0;
	ScrlB2[i]->ScrlB->Max = (int) pow(2, ScrlB2[i]->Addr.BitNum()) - 1;
	ScrlB2[i]->ScrlB->OnScroll = ScrollBar2_Scroll;
	ScrlB2[i]->StTxt->Caption = 0;
	ScrlB2[i]->ScrlB->Hint = i;
	ScrlB2[i]->Lbl->Caption = ScrlB2[i]->Addr.Name();
    }

    //LabeledEdit3
    lble3 = OoffsetForm->SetLblE3();

    LblE3 = new _LBLE3 *[OoffsetForm->LblE3_Nbr];
    for (int i = 0; i < OoffsetForm->LblE3_Nbr; i++)
	LblE3[i] = new _LBLE3;

    //LblE3[0]->Lble = LabeledEdit1;
    for (int i = 0; i < OoffsetForm->LblE3_Nbr; i++) {
	LblE3[i]->Addr = lble3[i];
	LblE3[i]->Lble->Visible = LblE3[i]->Addr.FuncEn();
	LblE3[i]->Lble->Hint = i;
	LblE3[i]->Lble->EditLabel->Caption = LblE3[i]->Addr.Name();
	LblE3[i]->Lble->OnKeyPress = LblE3_KeyPress;
	LblE3[i]->Lble->Text = 0;
    }

    // LblE4
    lble4 = OoffsetForm->SetLblE4();

    LblE4 = new _LBLE4 *[OoffsetForm->LblE4_Nbr];
    for (int i = 0; i < OoffsetForm->LblE4_Nbr; i++)
	LblE4[i] = new _LBLE4;

    //LblE4[0]->Lble = LabeledEdit1;
    for (int i = 0; i < OoffsetForm->LblE4_Nbr; i++) {
	LblE4[i]->Addr = lble4[i];
	LblE4[i]->Lble->Visible = LblE4[i]->Addr.FuncEn();
	LblE4[i]->Lble->Hint = i;
	LblE4[i]->Lble->EditLabel->Caption = LblE4[i]->Addr.Name();
	LblE4[i]->Lble->OnKeyPress = LblE4_KeyPress;
	LblE4[i]->Lble->Text = 0;
    }

    IsChg = 1;
}

//---------------------------------------------------------------------------
void __fastcall TOffsetForm::FormClose(TObject * Sender, TCloseAction & Action)
{
    delete[]OoffsetForm;
    delete[]cb;
    delete[]ChkB;

    delete[]cbo;
    delete[]CboB;

    delete[]scrlb;
    delete[]scrlb;

    delete[]scrlb2;
    delete[]ScrlB2;

    Action = caFree;
    //MainForm->offsetFormNULL();
}

//---------------------------------------------------------------------------
void __fastcall TOffsetForm::btn_reloadClick(TObject * Sender)
{
    btn_reload->Enabled = false;
    IsChg = 0;
    unsigned char read_val;
    for (int i = 0; i < OoffsetForm->ChkBox_Nbr; i++) {
	if (ChkB[i]->Chkb->Visible == true) {
	    EngineerForm->SetRead_Byte(ChkB[i]->Addr, &read_val);
	    if (read_val == 1)
		ChkB[i]->Chkb->Checked = 1;
	    else if (read_val == 0)
		ChkB[i]->Chkb->Checked = 0;
	    else
		ShowMessage("CheckBox read error:" + IntToStr(read_val));
	}
    }
    for (int i = 0; i < OoffsetForm->CboBox_Nbr; i++) {
	if (CboB[i]->Cbob->Visible == true) {
	    EngineerForm->SetRead_Byte(CboB[i]->Addr, &read_val);
	    CboB[i]->Cbob->ItemIndex = read_val;
	}
    }

    for (int i = 0; i < OoffsetForm->ScrollBar_Nbr; i++) {
	if (ScrlB[i]->ScrlB->Visible == true) {
	    EngineerForm->SetRead_Byte(ScrlB[i]->Addr, &read_val);
	    ScrlB[i]->ScrlB->Position = read_val;
	    ScrlB[i]->StTxt->Caption = read_val;
	}
    }
    unsigned char read_val1, read_val2, read_val3, read_val4;
    for (int i = 0; i < OoffsetForm->ScrollBar2_Nbr; i++) {
	if (ScrlB2[i]->ScrlB->Visible == true) {
	    EngineerForm->SetRead_Byte(ScrlB2[i]->Addr.Byte1, &read_val1);
	    EngineerForm->SetRead_Byte(ScrlB2[i]->Addr.Byte2, &read_val2);
	    ScrlB2[i]->ScrlB->Position = (int) read_val1 *ScrlB2[i]->Addr.Divide() + read_val2;
	    ScrlB2[i]->StTxt->Caption = (int) read_val1 *ScrlB2[i]->Addr.Divide() + read_val2;
	}
    }

    for (int i = 0; i < OoffsetForm->LblE3_Nbr; i++) {
	if (LblE3[i]->Lble->Visible == true) {
	    EngineerForm->SetRead_Byte(LblE3[i]->Addr.Byte1, &read_val1);
	    EngineerForm->SetRead_Byte(LblE3[i]->Addr.Byte2, &read_val2);
	    EngineerForm->SetRead_Byte(LblE3[i]->Addr.Byte3, &read_val3);
	    LblE3[i]->Lble->Text = (int) read_val1 *LblE3[i]->Addr.Divide1()
	    + (int) read_val2 *LblE3[i]->Addr.Divide2() + (int) read_val3;
	}
    }
    // LblE4
    for (int i = 0; i < OoffsetForm->LblE4_Nbr; i++) {
	if (LblE4[i]->Lble->Visible == true) {
	    EngineerForm->SetRead_Byte(LblE4[i]->Addr.Byte1, &read_val1);
	    EngineerForm->SetRead_Byte(LblE4[i]->Addr.Byte2, &read_val2);
	    EngineerForm->SetRead_Byte(LblE4[i]->Addr.Byte3, &read_val3);
	    EngineerForm->SetRead_Byte(LblE4[i]->Addr.Byte4, &read_val4);
	    LblE4[i]->Lble->Text = (int) read_val1 *LblE4[i]->Addr.Divide1()
	    + (int) read_val2 *LblE4[i]->Addr.Divide2()
	    + (int) read_val3 *LblE4[i]->Addr.Divide3() + (int) read_val4;
	}
    }

    IsChg = 1;
    btn_reload->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TOffsetForm::FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift)
{
    if (Key == 0x40)
	btn_reloadClick(Sender);
}

//---------------------------------------------------------------------------

