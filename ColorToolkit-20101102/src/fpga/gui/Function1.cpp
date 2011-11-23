//---------------------------------------------------------------------------

#include <vcl.h>
#include <lib/CMSCpp2.1/src/includeall.h>
#pragma hdrstop

#include "Unit1.h"
#include "Function1.h"
#include "include.h"
#include  <fpga/11307/Function/Func_11307.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
static bool DG_IsChkSum = true;
static bool OD_IsChkSum = true;
//extern String TCON_DEV;
//---------------------------------------------------------------------------
__fastcall TFunctionForm1::TFunctionForm1(TComponent * Owner)
:TForm(Owner)
{
    Func_Chg = 0;
    DGEN_idx = -1;
    ODEN_idx = -1;
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::FormClose(TObject * Sender, TCloseAction & Action)
{
    delete[]OFunc;
    //Pstate
    delete[]Pstate_cb;
    delete[]PstateChkB;
    delete[]Pstate_cbo;
    delete[]PstateCboB;
    delete[]Pstate_lble2;	//Add by Michelle 20100702
    delete[]PstateLblE2;

    //AGBS
    delete[]AGBS_cb;
    delete[]AGBSChkB;
    delete[]AGBS_cbo;
    delete[]AGBSCboB;
    delete[]AGBS_lble2;
    delete[]AGBSLblE2;

    // FRC DG
    delete[]FrcDg_cb;
    delete[]FrcDgChkB;
    delete[]FrcDg_cbo;
    delete[]FrcDgCboB;
    delete[]FrcDg_lble;
    delete[]FrcDgLblE;

    //OD
    delete[]OD_cb;
    delete[]ODChkB;
    delete[]OD_cbo;
    delete[]ODCboB;
    delete[]OD_cbo2;
    delete[]ODCboB2;
    delete[]OD_ScrlB;
    delete[]ODScrlB;
    delete[]Addr_DgLUT;

    Action = caFree;
    MainForm->FunctionFormNULL();
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::Pstate_CheckBox_Click(TObject * Sender)
{
    if (Func_Chg == 0)
	return;
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (PstateChkB[idx]->Chkb->Checked ? 1 : 0);
    EngineerForm->SetWrite_Byte(PstateChkB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::Pstate_ComboBox_Click(TObject * Sender)
{
    if (Func_Chg == 0)
	return;
    TComboBox *c = (TComboBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (PstateCboB[idx]->Cbob->ItemIndex);
    EngineerForm->SetWrite_Byte(PstateCboB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::Pstate_LblEdit2_KeyPress(TObject * Sender, char &Key)
{
    TLabeledEdit *c = (TLabeledEdit *) Sender;
    int idx = StrToInt(c->Hint);
    if (Key != 13) {
	PstateLblE2[idx]->Lble->Font->Color = cl3DDkShadow;
	return;
    }

    if (Func_Chg == 0)
	return;

    String tmp_v = PstateLblE2[idx]->Lble->Text;
    if (tmp_v == "") {
	tmp_v = "0";
    }
    int set_val = StrToInt(tmp_v);

    unsigned char val1, val2;
    //add Max hint
    if (set_val >= pow(2, PstateLblE2[idx]->Addr.BitNum())) {
	AnsiString max = "Max value:" + IntToStr((int) pow(2, PstateLblE2[idx]->Addr.BitNum()) - 1);
	ShowMessage(max);
	//read value
	EngineerForm->SetRead_Byte(PstateLblE2[idx]->Addr.Byte1, &val1);
	EngineerForm->SetRead_Byte(PstateLblE2[idx]->Addr.Byte2, &val2);
	PstateLblE2[idx]->Lble->Text = (int) val1 *PstateLblE2[idx]->Addr.Divide() + val2;
	PstateLblE2[idx]->Lble->Font->Color = clWindowText;
    } else {
	val1 = set_val / PstateLblE2[idx]->Addr.Divide();
	val2 = set_val % PstateLblE2[idx]->Addr.Divide();
	EngineerForm->SetWrite_Byte(PstateLblE2[idx]->Addr.Byte1, val1);
	if (PstateLblE2[idx]->Addr.Byte2.BitNum() != 0)
	    EngineerForm->SetWrite_Byte(PstateLblE2[idx]->Addr.Byte2, val2);
	PstateLblE2[idx]->Lble->Font->Color = clWindowText;
    }
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::AGBS_CheckBox_Click(TObject * Sender)
{
    if (Func_Chg == 0)
	return;
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (AGBSChkB[idx]->Chkb->Checked ? 1 : 0);
    EngineerForm->SetWrite_Byte(AGBSChkB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::AGBS_ComboBox_Click(TObject * Sender)
{
    if (Func_Chg == 0)
	return;
    TComboBox *c = (TComboBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (AGBSCboB[idx]->Cbob->ItemIndex);
    EngineerForm->SetWrite_Byte(AGBSCboB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::AGBS_LblEdit2_KeyPress(TObject * Sender, char &Key)
{
    TLabeledEdit *c = (TLabeledEdit *) Sender;
    int idx = StrToInt(c->Hint);

    if (Key != 13) {
	AGBSLblE2[idx]->Lble->Font->Color = cl3DDkShadow;
	return;
    }

    if (Func_Chg == 0)
	return;
    String tmp_v = AGBSLblE2[idx]->Lble->Text;
    if (tmp_v == "") {
	tmp_v = "0";
    }
    int set_val = StrToInt(tmp_v);
    unsigned char val1, val2;
    //add Max hint
    if (set_val >= pow(2, AGBSLblE2[idx]->Addr.BitNum())) {
	AnsiString max = "Max value:" + IntToStr((int) pow(2, AGBSLblE2[idx]->Addr.BitNum()) - 1);
	ShowMessage(max);
	//read value
	EngineerForm->SetRead_Byte(AGBSLblE2[idx]->Addr.Byte1, &val1);
	EngineerForm->SetRead_Byte(AGBSLblE2[idx]->Addr.Byte2, &val2);
	AGBSLblE2[idx]->Lble->Text = (int) val1 *AGBSLblE2[idx]->Addr.Divide() + val2;
	AGBSLblE2[idx]->Lble->Font->Color = clWindowText;
    } else {
	val1 = set_val / AGBSLblE2[idx]->Addr.Divide();
	val2 = set_val % AGBSLblE2[idx]->Addr.Divide();
	EngineerForm->SetWrite_Byte(AGBSLblE2[idx]->Addr.Byte1, val1);
	if (AGBSLblE2[idx]->Addr.Byte2.BitNum() != 0)
	    EngineerForm->SetWrite_Byte(AGBSLblE2[idx]->Addr.Byte2, val2);
	AGBSLblE2[idx]->Lble->Font->Color = clWindowText;
    }
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::FrcDg_CheckBox_Click(TObject * Sender)
{
    if (Func_Chg == 0)
	return;
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (FrcDgChkB[idx]->Chkb->Checked ? 1 : 0);
    EngineerForm->SetWrite_Byte(FrcDgChkB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::FrcDg_ComboBox_Click(TObject * Sender)
{
    if (Func_Chg == 0)
	return;
    TComboBox *c = (TComboBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (FrcDgCboB[idx]->Cbob->ItemIndex);
    EngineerForm->SetWrite_Byte(FrcDgCboB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::FrcDg_LblEdit_KeyPress(TObject * Sender, char &Key)
{
    TLabeledEdit *c = (TLabeledEdit *) Sender;
    int idx = StrToInt(c->Hint);
    if (Key != 13) {
	FrcDgLblE[idx]->Lble->Font->Color = cl3DDkShadow;
	return;
    }
    if (Func_Chg == 0)
	return;

    String tmp_v = FrcDgLblE[idx]->Lble->Text;
    if (tmp_v == "") {
	tmp_v = "0";
    }
    int set_val = StrToInt(tmp_v);

    unsigned char read_val;
    //add Max hint
    if (set_val >= pow(2, FrcDgLblE[idx]->Addr.BitNum())) {
	AnsiString max = "Max value:" + IntToStr((int) pow(2, FrcDgLblE[idx]->Addr.BitNum()) - 1);
	ShowMessage(max);
	//read value
	EngineerForm->SetRead_Byte(FrcDgLblE[idx]->Addr, &read_val);
	FrcDgLblE[idx]->Lble->Text = read_val;
	FrcDgLblE[idx]->Lble->Font->Color = clWindowText;
    } else {
	EngineerForm->SetWrite_Byte(FrcDgLblE[idx]->Addr, set_val);
	FrcDgLblE[idx]->Lble->Font->Color = clWindowText;
    }
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::OD_CheckBox_Click(TObject * Sender)
{
    if (Func_Chg == 0)
	return;
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (ODChkB[idx]->Chkb->Checked ? 1 : 0);
    EngineerForm->SetWrite_Byte(ODChkB[idx]->Addr, set_val);
}

//--------------------------------------------------------------------------
void __fastcall TFunctionForm1::OD_ComboBox_Click(TObject * Sender)
{
    if (Func_Chg == 0)
	return;
    TComboBox *c = (TComboBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (ODCboB[idx]->Cbob->ItemIndex);
    EngineerForm->SetWrite_Byte(ODCboB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::OD_ComboBox2_Click(TObject * Sender)
{
    if (Func_Chg == 0)
	return;
    TComboBox *c = (TComboBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = StrToInt(ODCboB2[idx]->Cbob->ItemIndex);
    int val1 = set_val / ODCboB2[idx]->Addr.Divide();
    int val2 = set_val % ODCboB2[idx]->Addr.Divide();
    EngineerForm->SetWrite_Byte(ODCboB2[idx]->Addr.Byte1, val1);
    Sleep(10);
    EngineerForm->SetWrite_Byte(ODCboB2[idx]->Addr.Byte2, val2);
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::OD_ScrollBar_Scroll(TObject * Sender,
						    TScrollCode ScrollCode, int &ScrollPos)
{
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (ODScrlB[idx]->ScrlB->Position);
    ODScrlB[idx]->StTxt->Caption = set_val;

    if (ScrollCode == scEndScroll) {
	//滑鼠放開, 或鍵盤操作放開
	if (Func_Chg == 0)
	    return;
	EngineerForm->SetWrite_Byte(ODScrlB[idx]->Addr, set_val);
    }
}

//---------------------------------------------------------------------------
void TFunctionForm1::Initial_DG_table()
{
    sg_dg->Cells[1][0] = "R";	//RGB top row
    sg_dg->Cells[2][0] = "G";
    sg_dg->Cells[3][0] = "B";

    if (OFunc->DGLUT_Nbr == 4) {
	//額外的一欄for white
	sg_dg->ColCount = 5;
	sg_dg->Width = 273;
	sg_dg->Cells[3][0] = "W";
    }
    int max_val = pow(2, Addr_DgLUT[0].BitNum());
    for (int j = 1; j <= 256; j++) {
	sg_dg->Cells[0][j] = IntToStr(j - 1);	//index on the left of table
	for (int i = 1; i <= OFunc->DGLUT_Nbr; i++) {
	    sg_dg->Cells[i][j] = IntToStr(max_val / 256 * (j - 1));	//給予預設值
	}
    }
    if (Addr_DgLUT[0].LutNum() == 257) {
	sg_dg->RowCount = 258;
	sg_dg->Cells[0][257] = 256;
	for (int i = 0; i <= OFunc->DGLUT_Nbr; i++) {
	    sg_dg->Cells[i + 1][257] = max_val - 1;
	}
    }
}

void __fastcall TFunctionForm1::FormCreate(TObject * Sender)
{
    int ic_choice;
    if (MainForm->TCON_DEV == "11307") {
	ic_choice = 0;
    }

    switch (ic_choice) {
    case 0:
	OFunc = new Func_11307;
	break;

	/* case 1:
	   OFunc = new Func_1240x;
	   break; */

    }

	/****************************************************************/
    //                                                              //
    //   P-state page CheckBox*2 & ComboBox*1 & LabeledEdit*4       //
    //                                                              //
	/****************************************************************/

    //CheckBox
    Pstate_cb = OFunc->SetPstateChkBx();

    PstateChkB = new _CHKB *[OFunc->PstateChkBox_Nbr];
    for (int i = 0; i < OFunc->PstateChkBox_Nbr; i++)
	PstateChkB[i] = new _CHKB;

    PstateChkB[0]->Chkb = CheckBox1;
    PstateChkB[1]->Chkb = CheckBox2;

    for (int i = 0; i < OFunc->PstateChkBox_Nbr; i++) {
	PstateChkB[i]->Addr = Pstate_cb[i];
	PstateChkB[i]->Chkb->Visible = PstateChkB[i]->Addr.FuncEn();
	PstateChkB[i]->Chkb->OnClick = Pstate_CheckBox_Click;
	PstateChkB[i]->Chkb->Hint = i;
	PstateChkB[i]->Chkb->Caption = PstateChkB[i]->Addr.Name();
    }

    //ComboBox
    Pstate_cbo = OFunc->SetPstateCboBx();
    PstateCboB = new _CBOB *[OFunc->PstateCboBox_Nbr];
    for (int i = 0; i < OFunc->PstateCboBox_Nbr; i++)
	PstateCboB[i] = new _CBOB;

    PstateCboB[0]->Cbob = ComboBox1;
    PstateCboB[0]->CbobL = Label1;
    for (int i = 0; i < OFunc->PstateCboBox_Nbr; i++) {
	PstateCboB[i]->Addr = Pstate_cbo[i];
	PstateCboB[i]->Cbob->Visible = PstateCboB[i]->Addr.FuncEn();
	PstateCboB[i]->Cbob->OnClick = Pstate_ComboBox_Click;
	PstateCboB[i]->Cbob->Hint = i;
	PstateCboB[i]->CbobL->Caption = PstateCboB[i]->Addr.Name();
	PstateCboB[i]->Cbob->Text = "";
	if (PstateCboB[i]->Addr.FuncEn())
	    for (int j = 0; j < PstateCboB[i]->Addr.choice_nbr; j++)	//ComboBox choice
		PstateCboB[i]->Cbob->Items->Add(PstateCboB[i]->Addr.choice[j]);
    }

    //LabeledEdit2
    Pstate_lble2 = OFunc->SetPstateLblE2();
    PstateLblE2 = new _LBLE2 *[OFunc->PstateLblE2_Nbr];
    for (int i = 0; i < OFunc->PstateLblE2_Nbr; i++)
	PstateLblE2[i] = new _LBLE2;

    PstateLblE2[0]->Lble = LabeledEdit1;
    PstateLblE2[1]->Lble = LabeledEdit2;
    PstateLblE2[2]->Lble = LabeledEdit3;
    PstateLblE2[3]->Lble = LabeledEdit4;

    for (int i = 0; i < OFunc->PstateLblE2_Nbr; i++) {
	PstateLblE2[i]->Addr = Pstate_lble2[i];
	PstateLblE2[i]->Lble->Visible = PstateLblE2[i]->Addr.FuncEn();
	PstateLblE2[i]->Lble->OnKeyPress = Pstate_LblEdit2_KeyPress;
	PstateLblE2[i]->Lble->Hint = i;
	PstateLblE2[i]->Lble->EditLabel->Caption = PstateLblE2[i]->Addr.Name();
	PstateLblE2[i]->Lble->Text = 0;
    }

	/*********************************************************************/
    //                                                                   //
    //   Aging Bist Page CheckBox*3 & ComboBox*0 & 2byte LabeledEdit*3   //
    //                                                                   //
	/*********************************************************************/
    //CheckBox
    AGBS_cb = OFunc->SetAGBSChkBx();

    AGBSChkB = new _CHKB *[OFunc->AGBSChkBox_Nbr];
    for (int i = 0; i < OFunc->AGBSChkBox_Nbr; i++)
	AGBSChkB[i] = new _CHKB;

    AGBSChkB[0]->Chkb = CheckBox3;
    AGBSChkB[1]->Chkb = CheckBox4;
    AGBSChkB[2]->Chkb = CheckBox13;
    for (int i = 0; i < OFunc->AGBSChkBox_Nbr; i++) {
	AGBSChkB[i]->Addr = AGBS_cb[i];
	AGBSChkB[i]->Chkb->Visible = AGBSChkB[i]->Addr.FuncEn();
	AGBSChkB[i]->Chkb->OnClick = AGBS_CheckBox_Click;
	AGBSChkB[i]->Chkb->Hint = i;
	AGBSChkB[i]->Chkb->Caption = AGBSChkB[i]->Addr.Name();
    }

    //ComboBox
    AGBS_cbo = OFunc->SetAGBSCboBx();
    AGBSCboB = new _CBOB *[OFunc->AGBSCboBox_Nbr];
    for (int i = 0; i < OFunc->AGBSCboBox_Nbr; i++)
	AGBSCboB[i] = new _CBOB;

    for (int i = 0; i < OFunc->AGBSCboBox_Nbr; i++) {
	AGBSCboB[i]->Addr = AGBS_cbo[i];
	AGBSCboB[i]->Cbob->Visible = AGBSCboB[i]->Addr.FuncEn();
	AGBSCboB[i]->Cbob->OnClick = AGBS_ComboBox_Click;
	AGBSCboB[i]->Cbob->Hint = i;
	AGBSCboB[i]->CbobL->Caption = AGBSCboB[i]->Addr.Name();
	AGBSCboB[i]->Cbob->Text = "";
	if (AGBSCboB[i]->Addr.FuncEn())
	    for (int j = 0; j < AGBSCboB[i]->Addr.choice_nbr; j++)	//ComboBox choice
		AGBSCboB[i]->Cbob->Items->Add(AGBSCboB[i]->Addr.choice[j]);
    }

    //LabeledEdit 2 byte size
    AGBS_lble2 = OFunc->SetAGBSLblE2();
    AGBSLblE2 = new _LBLE2 *[OFunc->AGBSLblE2_Nbr];
    for (int i = 0; i < OFunc->AGBSLblE2_Nbr; i++)
	AGBSLblE2[i] = new _LBLE2;

    AGBSLblE2[0]->Lble = LabeledEdit5;
    AGBSLblE2[1]->Lble = LabeledEdit6;
    AGBSLblE2[2]->Lble = LabeledEdit7;

    for (int i = 0; i < OFunc->AGBSLblE2_Nbr; i++) {
	AGBSLblE2[i]->Addr = AGBS_lble2[i];
	AGBSLblE2[i]->Lble->Visible = AGBSLblE2[i]->Addr.FuncEn();
	AGBSLblE2[i]->Lble->OnKeyPress = AGBS_LblEdit2_KeyPress;
	AGBSLblE2[i]->Lble->Hint = i;
	AGBSLblE2[i]->Lble->EditLabel->Caption = AGBSLblE2[i]->Addr.Name();
	AGBSLblE2[i]->Lble->Text = 0;
    }

	/*******************************************************************/
    //                                                                 //
    //   FRC DG page CheckBox*6 & ComboBox*1 & LabeledEdit*0           //
    //                                                                 //
	/*******************************************************************/
    //Set DG address
    Addr_DgLUT = OFunc->SetDGLUT();
    Initial_DG_table();		// 20100608 DG table(RGB/RGBW) initial

    //CheckBox
    FrcDg_cb = OFunc->SetFrcDgChkBx();
    FrcDgChkB = new _CHKB *[OFunc->FrcDgChkBox_Nbr];
    for (int i = 0; i < OFunc->FrcDgChkBox_Nbr; i++)
	FrcDgChkB[i] = new _CHKB;

    FrcDgChkB[0]->Chkb = CheckBox5;
    FrcDgChkB[1]->Chkb = CheckBox6;
    FrcDgChkB[2]->Chkb = CheckBox7;
    FrcDgChkB[3]->Chkb = CheckBox8;
    FrcDgChkB[4]->Chkb = CheckBox9;
    FrcDgChkB[5]->Chkb = CheckBox14;

    for (int i = 0; i < OFunc->FrcDgChkBox_Nbr; i++) {
	FrcDgChkB[i]->Addr = FrcDg_cb[i];
	FrcDgChkB[i]->Chkb->Visible = FrcDgChkB[i]->Addr.FuncEn();
	FrcDgChkB[i]->Chkb->OnClick = FrcDg_CheckBox_Click;
	FrcDgChkB[i]->Chkb->Hint = i;
	FrcDgChkB[i]->Chkb->Caption = FrcDgChkB[i]->Addr.Name();
	if (FrcDgChkB[i]->Addr.Name() == OFunc->DG_EN_Name())	// 20100608 find DG enable index
	    DGEN_idx = i;
    }
    if (DGEN_idx == -1)		// 20100608 Check DG enable index
	ShowMessage("Can't Get DG enable index.");

    //ComboBox
    FrcDg_cbo = OFunc->SetFrcDgCboBx();
    FrcDgCboB = new _CBOB *[OFunc->FrcDgCboBox_Nbr];
    for (int i = 0; i < OFunc->FrcDgCboBox_Nbr; i++)
	FrcDgCboB[i] = new _CBOB;


    ComboBox3->Hide();
    Label3->Hide();
    FrcDgCboB[0]->Cbob = ComboBox3;
    FrcDgCboB[0]->CbobL = Label3;

    for (int i = 0; i < OFunc->FrcDgCboBox_Nbr; i++) {
	FrcDgCboB[i]->Addr = FrcDg_cbo[i];
	FrcDgCboB[i]->Cbob->Visible = FrcDgCboB[i]->Addr.FuncEn();
	FrcDgCboB[i]->Cbob->OnClick = FrcDg_ComboBox_Click;
	FrcDgCboB[i]->Cbob->Hint = i;
	FrcDgCboB[i]->CbobL->Caption = FrcDgCboB[i]->Addr.Name();
	FrcDgCboB[i]->Cbob->Text = "";
	if (FrcDgCboB[i]->Addr.FuncEn())
	    for (int j = 0; j < FrcDgCboB[i]->Addr.choice_nbr; j++)	//ComboBox choice
		FrcDgCboB[i]->Cbob->Items->Add(FrcDgCboB[i]->Addr.choice[j]);
    }
    //LabeledEdit
    FrcDg_lble = OFunc->SetFrcDgLblE();
    FrcDgLblE = new _LBLE *[OFunc->FrcDgLblE_Nbr];
    for (int i = 0; i < OFunc->FrcDgLblE_Nbr; i++)
	FrcDgLblE[i] = new _LBLE;

    for (int i = 0; i < OFunc->FrcDgLblE_Nbr; i++) {
	FrcDgLblE[i]->Addr = FrcDg_lble[i];
	FrcDgLblE[i]->Lble->Visible = FrcDgLblE[i]->Addr.FuncEn();
	FrcDgLblE[i]->Lble->OnKeyPress = FrcDg_LblEdit_KeyPress;
	FrcDgLblE[i]->Lble->Hint = i;
	FrcDgLblE[i]->Lble->EditLabel->Caption = FrcDgLblE[i]->Addr.Name();
	FrcDgLblE[i]->Lble->Text = 0;
    }

	/*******************************************************************/
    //                                                                 //
    //      OD page CheckBox*3   ComboBox*3  ComboBox2*1  ScrollBar*3  //
    //                                                                 //
	/*******************************************************************/

    Func_Chg = 1;
}

//---------------------------------------------------------------------------

// 20100608 Record the state of DG enable
bool TFunctionForm1::DG_LUT_RW_start()
{
    if (DGEN_idx == -1) {
	ShowMessage("Unknown DG enabled index.");
	return 0;
    }
    unsigned char set_val;
    bool ok = EngineerForm->SetRead_Byte(FrcDgChkB[DGEN_idx]->Addr, &set_val);
    if (ok == 0) {
	ShowMessage("read enable fail.");
	return 0;
    }
    DG_EN_State = (set_val > 0 ? 1 : 0);
    FrcDgChkB[DGEN_idx]->Chkb->Checked = false;
    EngineerForm->SetWrite_Byte(FrcDgChkB[DGEN_idx]->Addr, 0);
    return 1;
}

// 20100608 Recover the state of DG enable
void TFunctionForm1::DG_LUT_RW_over()
{
    // reload en state
    int set_val = (DG_EN_State == false ? 0 : 1);
    FrcDgChkB[DGEN_idx]->Chkb->Checked = DG_EN_State;
    EngineerForm->SetWrite_Byte(FrcDgChkB[DGEN_idx]->Addr, set_val);
}

// 20100608 DG table operation enable/disable
void TFunctionForm1::DG_LUT_FuncEnable(bool en_flag)
{
    if (en_flag == true) {	// Table operation button enable
	btn_dg_wrt->Enabled = true;
	btn_dg_read->Enabled = true;
	btn_dg_save->Enabled = true;
	btn_dg_load->Enabled = true;
    } else {			// Table operation button disable
	btn_dg_wrt->Enabled = false;
	btn_dg_read->Enabled = false;
	btn_dg_save->Enabled = false;
	btn_dg_load->Enabled = false;
    }
}

// DG table write
// 20100608 add enable record and revise EngineerForm->SetWrite_DG(...)
void __fastcall TFunctionForm1::btn_dg_wrtClick(TObject * Sender)
{
    DG_LUT_FuncEnable(0);	// Table operation button disable
    bool ok = DG_LUT_RW_start();	// Record the state of DG enable
    if (ok == 0) {		// Fail to record the state
	DG_LUT_FuncEnable(1);	// Table operation button enable
	return;
    }

    int **lut = new int *[OFunc->DGLUT_Nbr];

    for (int i = 0; i < OFunc->DGLUT_Nbr; i++) {
	lut[i] = new int[Addr_DgLUT[i].LutNum()];
	for (int j = 0; j < Addr_DgLUT[i].LutNum(); j++) {
	    //從UI撈回資料
	    lut[i][j] = StrToInt(sg_dg->Cells[i + 1][j + 1]);
	}
    }

    EngineerForm->SetWrite_DG(Addr_DgLUT, lut, OFunc->DGLUT_Nbr, DG_IsChkSum, 0);	//Add by Michelle : checksum type 20100716 
    for (int i = 0; i < OFunc->DGLUT_Nbr; i++) {
	delete[]lut[i];
    }
    delete[]lut;
    DG_LUT_RW_over();		// Recover DG enable
    DG_LUT_FuncEnable(1);	// Table operation button enable
}

//---------------------------------------------------------------------------
// DG table read
// 20100608 add enable record and revise EngineerForm->SetRead_DG(...)
void __fastcall TFunctionForm1::btn_dg_readClick(TObject * Sender)
{
    DG_LUT_FuncEnable(0);	// Table operation button disable
    bool ok = DG_LUT_RW_start();	// Record the state of DG enable
    if (ok == 0) {		// Fail to record the state
	DG_LUT_FuncEnable(1);	// Table operation button enable
	return;
    }

    int **DG_table = new int *[OFunc->DGLUT_Nbr];
    int read_len = Addr_DgLUT[0].Addr();

    for (int i = 0; i < OFunc->DGLUT_Nbr; i++) {
	DG_table[i] = new int[read_len];
    }
    EngineerForm->SetRead_DG(Addr_DgLUT, DG_table, OFunc->DGLUT_Nbr, DG_IsChkSum);

    for (int i = 0; i < OFunc->DGLUT_Nbr; i++) {
	for (int j = 0; j < Addr_DgLUT[i].LutNum(); j++) {	//To GUI
	    sg_dg->Cells[i + 1][j + 1] = IntToStr(DG_table[i][j]);
	}
    }
    for (int i = 0; i < OFunc->DGLUT_Nbr; i++) {
	delete[]DG_table[i];
    }
    delete[]DG_table;
    DG_LUT_RW_over();		// Recover DG enable
    DG_LUT_FuncEnable(1);	// Table operation button enable
}

//---------------------------------------------------------------------------

// DG table, Load from text file
// 20100608 Add table operation Enable/ Disable
void __fastcall TFunctionForm1::btn_dg_loadClick(TObject * Sender)
{
    DG_LUT_FuncEnable(0);
    String Fpath;
    if (LoadDialog->Execute()) {
	Fpath = LoadDialog->FileName;
	String *DG_LUT = NULL;
        //從檔案讀進來, 跟EngineerForm何關?
	DG_LUT = EngineerForm->Load_file(Fpath, Addr_DgLUT[0].LutNum() * OFunc->DGLUT_Nbr);
	if (DG_LUT == NULL) {
	    ShowMessage("Load file fail!");
	    return;
	}

	for (int c = 0; c < OFunc->DGLUT_Nbr; c++) {
	    for (int r = 0; r < Addr_DgLUT[0].LutNum(); r++) {
            //轉到UI去
		sg_dg->Cells[c + 1][r + 1] = StrToInt(DG_LUT[r * OFunc->DGLUT_Nbr + c]);
	    }
	}
	delete[]DG_LUT;
    }
    DG_LUT_FuncEnable(1);

}

//---------------------------------------------------------------------------
// DG table, Save to text file
// 20100608 add table operation enable/ disble
void __fastcall TFunctionForm1::btn_dg_saveClick(TObject * Sender)
{
    DG_LUT_FuncEnable(0);
    if (!SaveDialog->Execute())
	return;
    String Fpath = SaveDialog->FileName /*+".txt" */ ;
    FILE *fptr = fopen(Fpath.c_str(), "w");
    //fprintf(fptr,"R\tG\tB\n");

    for (int i = 1; i <= Addr_DgLUT[0].LutNum(); i++) {
	for (int j = 1; j <= OFunc->DGLUT_Nbr; j++) {
	    fprintf(fptr, "%d\t", StrToInt(sg_dg->Cells[j][i]));
	}
	fprintf(fptr, "\n");
    }

    fclose(fptr);
    DG_LUT_FuncEnable(1);
}

//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::Btn_FRC_DG_reloadClick(TObject * Sender)
{
    Btn_FRC_DG_reload->Enabled = false;
    DG_LUT_FuncEnable(0);
    Func_Chg = 0;
    unsigned char read_val;
    for (int i = 0; i < OFunc->FrcDgChkBox_Nbr; i++) {
	if (FrcDgChkB[i]->Chkb->Visible == true) {
	    EngineerForm->SetRead_Byte(FrcDgChkB[i]->Addr, &read_val);
	    if (read_val == 1)
		FrcDgChkB[i]->Chkb->Checked = 1;
	    else if (read_val == 0)
		FrcDgChkB[i]->Chkb->Checked = 0;
	    else
		ShowMessage("FRC/DG CheckBox read error:" + IntToStr(read_val));
	}
    }
    for (int i = 0; i < OFunc->FrcDgCboBox_Nbr; i++) {
	if (FrcDgCboB[i]->Cbob->Visible == true) {
	    EngineerForm->SetRead_Byte(FrcDgCboB[i]->Addr, &read_val);
	    FrcDgCboB[i]->Cbob->ItemIndex = read_val;
	}
    }
    for (int i = 0; i < OFunc->FrcDgLblE_Nbr; i++) {
	if (FrcDgLblE[i]->Lble->Visible == true) {
	    EngineerForm->SetRead_Byte(FrcDgLblE[i]->Addr, &read_val);
	    FrcDgLblE[i]->Lble->Text = read_val;
	    FrcDgLblE[i]->Lble->Font->Color = clWindowText;
	}
    }
    btn_dg_readClick(Sender);
    Func_Chg = 1;
    Btn_FRC_DG_reload->Enabled = true;
    DG_LUT_FuncEnable(1);
}

//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::Btn_Pstate_reloadClick(TObject * Sender)
{
    Btn_Pstate_reload->Enabled = false;
    Func_Chg = 0;
    unsigned char read_val;
    for (int i = 0; i < OFunc->PstateChkBox_Nbr; i++) {
	if (PstateChkB[i]->Chkb->Visible == true) {
	    EngineerForm->SetRead_Byte(PstateChkB[i]->Addr, &read_val);
	    if (read_val == 1)
		PstateChkB[i]->Chkb->Checked = 1;
	    else if (read_val == 0)
		PstateChkB[i]->Chkb->Checked = 0;
	    else
		ShowMessage("FRC/DG CheckBox read error:" + IntToStr(read_val));
	}
    }
    for (int i = 0; i < OFunc->PstateCboBox_Nbr; i++) {
	if (PstateCboB[i]->Cbob->Visible == true) {
	    EngineerForm->SetRead_Byte(PstateCboB[i]->Addr, &read_val);
	    PstateCboB[i]->Cbob->ItemIndex = read_val;
	}
    }

    unsigned char read_val1, read_val2;
    for (int i = 0; i < OFunc->PstateLblE2_Nbr; i++) {
	if (PstateLblE2[i]->Lble->Visible == true) {
	    EngineerForm->SetRead_Byte(PstateLblE2[i]->Addr.Byte1, &read_val1);
	    EngineerForm->SetRead_Byte(PstateLblE2[i]->Addr.Byte2, &read_val2);
	    PstateLblE2[i]->Lble->Text = (int) read_val1 *PstateLblE2[i]->Addr.Divide() + read_val2;
	    PstateLblE2[i]->Lble->Font->Color = clWindowText;
	}
    }
    Func_Chg = 1;
    Btn_Pstate_reload->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::Btn_AGBS_reloadClick(TObject * Sender)
{
    Btn_AGBS_reload->Enabled = false;
    Func_Chg = 0;
    unsigned char read_val;
    for (int i = 0; i < OFunc->AGBSChkBox_Nbr; i++) {
	if (AGBSChkB[i]->Chkb->Visible == true) {
	    EngineerForm->SetRead_Byte(AGBSChkB[i]->Addr, &read_val);
	    if (read_val == 1)
		AGBSChkB[i]->Chkb->Checked = 1;
	    else if (read_val == 0)
		AGBSChkB[i]->Chkb->Checked = 0;
	    else
		ShowMessage("FRC/DG CheckBox read error:" + IntToStr(read_val));
	}
    }
    for (int i = 0; i < OFunc->AGBSCboBox_Nbr; i++) {
	if (AGBSCboB[i]->Cbob->Visible == true) {
	    EngineerForm->SetRead_Byte(AGBSCboB[i]->Addr, &read_val);
	    AGBSCboB[i]->Cbob->ItemIndex = read_val;
	}
    }
    unsigned char read_val1, read_val2;
    for (int i = 0; i < OFunc->AGBSLblE2_Nbr; i++) {
	if (AGBSLblE2[i]->Lble->Visible == true) {
	    EngineerForm->SetRead_Byte(AGBSLblE2[i]->Addr.Byte1, &read_val1);
	    EngineerForm->SetRead_Byte(AGBSLblE2[i]->Addr.Byte2, &read_val2);
	    AGBSLblE2[i]->Lble->Text = (int) read_val1 *AGBSLblE2[i]->Addr.Divide() + read_val2;
	    AGBSLblE2[i]->Lble->Font->Color = clWindowText;
	}
    }
    Func_Chg = 1;
    Btn_AGBS_reload->Enabled = true;
}

//---------------------------------------------------------------------------

// 20100608 Record the state of OD enable
bool TFunctionForm1::OD_LUT_RW_start()
{
    if (ODEN_idx == -1) {
	ShowMessage("Unknown OD enabled index.");
	return 0;
    }

    unsigned char set_val;
    bool ok = EngineerForm->SetRead_Byte(ODChkB[ODEN_idx]->Addr, &set_val);
    if (ok == 0) {
	ShowMessage("read enable fail.");
	return 0;
    }
    OD_EN_State = (set_val > 0 ? 1 : 0);
    ODChkB[ODEN_idx]->Chkb->Checked = false;
    EngineerForm->SetWrite_Byte(ODChkB[ODEN_idx]->Addr, 0);
    return 1;
}

//---------------------------------------------------------------------------
// 20100608 Recover the state of OD enable
void TFunctionForm1::OD_LUT_RW_over()
{
    // reload en state
    int set_val = (OD_EN_State == false ? 0 : 1);
    ODChkB[ODEN_idx]->Chkb->Checked = OD_EN_State;
    EngineerForm->SetWrite_Byte(ODChkB[ODEN_idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
// 20100608 OD table operation enable/disable
void TFunctionForm1::OD_LUT_FuncEnable(bool flag_en)
{
    if (flag_en == true) {	// Table operation button enable
	btn_od_read->Enabled = true;
	btn_od_write->Enabled = true;
	btn_od_save->Enabled = true;
	btn_od_load->Enabled = true;
    } else {			// Table operation button disable
	btn_od_read->Enabled = false;
	btn_od_write->Enabled = false;
	btn_od_save->Enabled = false;
	btn_od_load->Enabled = false;
    }
}

//---------------------------------------------------------------------------
// OD table reload
// 20100608 Add operation Disable befor reload and Enable after reload
void __fastcall TFunctionForm1::Btn_OD_reloadClick(TObject * Sender)
{
    Btn_OD_reload->Enabled = false;
    OD_LUT_FuncEnable(0);
    Func_Chg = 0;
    unsigned char read_val;
    for (int i = 0; i < OFunc->ODChkBox_Nbr; i++) {
	if (ODChkB[i]->Chkb->Visible == true) {
	    EngineerForm->SetRead_Byte(ODChkB[i]->Addr, &read_val);
	    if (read_val == 1)
		ODChkB[i]->Chkb->Checked = 1;
	    else if (read_val == 0)
		ODChkB[i]->Chkb->Checked = 0;
	    else
		ShowMessage("OD CheckBox read error:" + IntToStr(read_val));
	}
    }
    for (int i = 0; i < OFunc->ODCboBox_Nbr; i++) {
	if (ODCboB[i]->Cbob->Visible == true) {
	    EngineerForm->SetRead_Byte(ODCboB[i]->Addr, &read_val);
	    ODCboB[i]->Cbob->ItemIndex = read_val;
	}
    }
    unsigned char read_val1, read_val2;
    for (int i = 0; i < OFunc->ODCboBox2_Nbr; i++) {
	if (ODCboB2[i]->Cbob->Visible == true) {
	    EngineerForm->SetRead_Byte(ODCboB2[i]->Addr.Byte1, &read_val1);
	    EngineerForm->SetRead_Byte(ODCboB2[i]->Addr.Byte2, &read_val2);
	    ODCboB2[i]->Cbob->Text = (int) read_val1 *ODCboB2[i]->Addr.Divide() + read_val2;
	}
    }
    for (int i = 0; i < OFunc->ODScrollBar_Nbr; i++) {
	if (ODScrlB[i]->ScrlB->Visible == true) {
	    EngineerForm->SetRead_Byte(ODScrlB[i]->Addr, &read_val);
	    ODScrlB[i]->ScrlB->Position = read_val;
	    ODScrlB[i]->StTxt->Caption = read_val;
	}
    }

    btn_od_readClick(Sender);
    Func_Chg = 1;
    OD_LUT_FuncEnable(1);
    Btn_OD_reload->Enabled = true;
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift)
{
    if (Key == 0x40) {
	Btn_FRC_DG_reloadClick(Sender);
	Btn_Pstate_reloadClick(Sender);
	Btn_AGBS_reloadClick(Sender);
	//Btn_OD_reloadClick(Sender);  // remove by Michelle 20100716
    }
}

//---------------------------------------------------------------------------

// OD table read
// 20100608 Add Table Enable record and revise EngineerForm->SetRead_PG(...)
// for 2 types of IP (AUO 18x18 & vender 17x17)
void __fastcall TFunctionForm1::btn_od_readClick(TObject * Sender)
{
    OD_LUT_FuncEnable(0);	// Table operation button disable
    bool ok = OD_LUT_RW_start();	// Record the state of OD enable
    if (ok == 0) {		// Fail to record the state
	OD_LUT_FuncEnable(1);	// Table operation button enable
	return;
    }
    int *OD_table;
    OD_table = new int[Addr_ODLUT[0].LutNum()];

    EngineerForm->SetRead_PG(Addr_ODLUT[0], OD_table, OD_IsChkSum);

    // 2's Complement => sign
    for (int i = 0; i < Addr_ODLUT[0].LutNum(); i++) {
	if (OD_table[i] > 256 / 2)
	    OD_table[i] -= 256;
    }

    // Set to interface
    if (ODLUT_ip_type == 1) {	// AUO IP, 18x18 table
	int od1_len = 18 * 18;
	int idx = 0;
	int bas_1, bas_2;	// 加到差值的start數值
	for (int j = 0; j < 18; j += 2) {
	    if (rg_od_table_type->ItemIndex == 1) {	// od table顯示Target值
		bas_1 = (16 * j) >= 256 ? 255 : (16 * j);
		bas_2 = (16 * (j + 1)) >= 256 ? 255 : (j + 1) * 16;
	    } else if (rg_od_table_type->ItemIndex == 0) {
		bas_1 = 0;
		bas_2 = 0;
	    }
	    for (int i = 0; i < 18; i += 2) {
		sg_od_1->Cells[i + 1][j + 1] = IntToStr((bas_1 + OD_table[idx]) % 256);
		sg_od_1->Cells[i + 2][j + 1] = IntToStr((bas_1 + OD_table[81 + idx]) % 256);
		sg_od_1->Cells[i + 1][j + 2] = IntToStr((bas_2 + OD_table[81 * 2 + idx]) % 256);
		sg_od_1->Cells[i + 2][j + 2] = IntToStr((bas_2 + OD_table[81 * 3 + idx]) % 256);

		sg_od_2->Cells[i + 1][j + 1] = IntToStr((bas_1 + OD_table[od1_len + idx]) % 256);
		sg_od_2->Cells[i + 2][j + 1] =
		    IntToStr((bas_1 + OD_table[od1_len + 81 + idx]) % 256);
		sg_od_2->Cells[i + 1][j + 2] =
		    IntToStr((bas_2 + OD_table[od1_len + 81 * 2 + idx]) % 256);
		sg_od_2->Cells[i + 2][j + 2] =
		    IntToStr((bas_2 + OD_table[od1_len + 81 * 3 + idx]) % 256);
		idx++;
	    }
	}
    } else if (ODLUT_ip_type == 2) {	// Vender IP
	int od1_len = 17 * 17;
	int idx = 0;
	int bas_1;		// 加到差值的start數值
	// if(rg_od_table_type->ItemIndex==1){  // od table顯示Target值
	for (int j = 0; j < 17; j++) {
	    if (rg_od_table_type->ItemIndex == 1) {	// od table顯示Target值
		bas_1 = (16 * j) >= 256 ? 255 : (16 * j);
	    } else if (rg_od_table_type->ItemIndex == 0) {	// od table顯示Difference值
		bas_1 = 0;
	    }
	    for (int i = 0; i < 17; i++) {
		sg_od_1->Cells[i + 1][j + 1] = IntToStr((bas_1 + OD_table[idx]) % 256);
		sg_od_2->Cells[i + 1][j + 1] = IntToStr((bas_1 + OD_table[od1_len + idx]) % 256);
		idx++;
	    }
	}
    }
    delete[]OD_table;

    OD_LUT_RW_over();		// Recover OD enable
    OD_LUT_FuncEnable(1);	// Table operation button enable
}

//---------------------------------------------------------------------------
// OD table write
// 20100608 Add Table Enable record and revise EngineerForm->SetWrite_PG(...)
// for 2 types of IP (AUO 18x18 & vender 17x17)
void __fastcall TFunctionForm1::btn_od_writeClick(TObject * Sender)
{
    OD_LUT_FuncEnable(0);	// Table operation button disable
    bool ok = OD_LUT_RW_start();	// Record the state of OD enable
    if (ok == 0) {		// Fail to record the state
	OD_LUT_FuncEnable(1);	// Table operation button enable
	return;
    }

    if (ODLUT_ip_type == 1) {	//1: AUO IP  //顯示17x17 table, 實際寫入18x18 table
	int *od1 = new int[18 * 18];
	int *od2 = new int[18 * 18];
	int idx = 0;

	// 第18行與第17行相同,第18列與第17列相同
	for (int i = 1; i <= 17; i++) {
	    sg_od_1->Cells[18][i] = sg_od_1->Cells[17][i];
	    sg_od_1->Cells[i][18] = sg_od_1->Cells[i][17];

	    sg_od_2->Cells[18][i] = sg_od_2->Cells[17][i];
	    sg_od_2->Cells[i][18] = sg_od_2->Cells[i][17];
	}
	sg_od_1->Cells[18][18] = sg_od_1->Cells[17][17];
	sg_od_2->Cells[18][18] = sg_od_2->Cells[17][17];

	int bas_1, bas_2;	// Target轉到difference所減去的start數值
	//取出欲寫入的table
	for (int j = 0; j <= 17; j += 2) {
	    if (rg_od_table_type->ItemIndex == 1) {	// od table顯示Target值
		bas_1 = (j * 16) >= 256 ? 255 : (j * 16);
		bas_2 = ((j + 1) * 16) >= 256 ? 255 : (j + 1) * 16;
	    } else if (rg_od_table_type->ItemIndex == 0) {	// od table顯示Difference值
		bas_1 = 0;
		bas_2 = 0;
	    }
	    for (int i = 0; i <= 17; i += 2) {
		od1[idx] = StrToInt(sg_od_1->Cells[i + 1][j + 1]) - bas_1;
		od1[81 + idx] = StrToInt(sg_od_1->Cells[i + 2][j + 1]) - bas_1;
		od1[81 * 2 + idx] = StrToInt(sg_od_1->Cells[i + 1][j + 2]) - bas_2;
		od1[81 * 3 + idx] = StrToInt(sg_od_1->Cells[i + 2][j + 2]) - bas_2;

		od2[idx] = StrToInt(sg_od_2->Cells[i + 1][j + 1]) - bas_1;
		od2[81 + idx] = StrToInt(sg_od_2->Cells[i + 2][j + 1]) - bas_1;
		od2[81 * 2 + idx] = StrToInt(sg_od_2->Cells[i + 1][j + 2]) - bas_2;
		od2[81 * 3 + idx] = StrToInt(sg_od_2->Cells[i + 2][j + 2]) - bas_2;
		idx++;
	    }
	}
	int *od_w = new int[18 * 18 * 2];
	for (int i = 0; i < 18 * 18; i++) {	// signed => 2's Complement
	    od_w[i] = (od1[i] + 256) % 256;
	    od_w[18 * 18 + i] = (od2[i] + 256) % 256;
	}

	EngineerForm->SetWrite_PG(Addr_ODLUT[0], od_w, OD_IsChkSum);

	delete[]od1;
	delete[]od2;
	delete[]od_w;
    } else if (ODLUT_ip_type == 2) {	//2: Vender IP
	int *od1 = new int[17 * 17];
	int *od2 = new int[17 * 17];
	int idx = 0;
	int bas_1;
	for (int j = 0; j < 17; j++) {
	    if (rg_od_table_type->ItemIndex == 1) {	// 取介面的Target 值轉為Difference
		bas_1 = (j * 16) >= 256 ? 255 : (j * 16);
	    } else if (rg_od_table_type->ItemIndex == 0) {	// 取介面的difference
		bas_1 = 0;
	    }
	    for (int i = 0; i < 17; i++) {
		od1[idx] = (StrToInt(sg_od_1->Cells[i + 1][j + 1]) - bas_1);
		od2[idx] = (StrToInt(sg_od_2->Cells[i + 1][j + 1]) - bas_1);
		idx++;
	    }
	}
	int *od_w = new int[17 * 17 * 2];
	for (int i = 0; i < 17 * 17; i++) {	// signed => 2's Complement
	    od_w[i] = (od1[i] + 256) % 256;
	    od_w[17 * 17 + i] = (od2[i] + 256) % 256;
	}

	EngineerForm->SetWrite_PG(Addr_ODLUT[0], od_w, OD_IsChkSum);
	delete[]od1;
	delete[]od2;
	delete[]od_w;
    }
    OD_LUT_RW_over();		// Recover OD enable
    OD_LUT_FuncEnable(1);	// Table operation button enable
}

//---------------------------------------------------------------------------
// OD table Load
// 20100608 Add Table Operation Disable/Enable
// and Load table for 2 types of IP (AUO 18x18 & vender 17x17)
void __fastcall TFunctionForm1::btn_od_loadClick(TObject * Sender)
{				// File Format: 上方是OD1 17x17 table, 下方是OD2 17x17 table

    String Fpath;
    if (!LoadDialog->Execute())
	return;
    OD_LUT_FuncEnable(0);
    Fpath = LoadDialog->FileName;
    String *od_lut = NULL;
    od_lut = EngineerForm->Load_file(Fpath, 17 * 17 * 2);

    if (od_lut == NULL) {
	ShowMessage("Load file fail!");
	OD_LUT_FuncEnable(1);
	return;
    }

    int od1_len = 17 * 17;

    if (ODLUT_ip_type == 1) {	// AUO IP
	for (int j = 0; j <= 15; j += 2) {
	    for (int i = 0; i <= 15; i += 2) {
		sg_od_1->Cells[i + 1][j + 1] = od_lut[j * 17 + i];
		sg_od_1->Cells[i + 2][j + 1] = od_lut[j * 17 + i + 1];
		sg_od_1->Cells[i + 1][j + 2] = od_lut[(j + 1) * 17 + i];
		sg_od_1->Cells[i + 2][j + 2] = od_lut[(j + 1) * 17 + i + 1];

		sg_od_2->Cells[i + 1][j + 1] = od_lut[od1_len + j * 17 + i];
		sg_od_2->Cells[i + 2][j + 1] = od_lut[od1_len + j * 17 + i + 1];
		sg_od_2->Cells[i + 1][j + 2] = od_lut[od1_len + (j + 1) * 17 + i];
		sg_od_2->Cells[i + 2][j + 2] = od_lut[od1_len + (j + 1) * 17 + i + 1];
	    }
	}
	// 第17列與第18列
	for (int j = 0; j <= 16; j++) {
	    sg_od_1->Cells[16 + 1][j + 1] = od_lut[j * 17 + 16];
	    sg_od_2->Cells[16 + 1][j + 1] = od_lut[od1_len + j * 17 + 16];

	    sg_od_1->Cells[17 + 1][j + 1] = sg_od_1->Cells[16 + 1][j + 1];
	    sg_od_2->Cells[17 + 1][j + 1] = sg_od_2->Cells[16 + 1][j + 1];
	}
	// 第17行與第18行
	for (int i = 0; i <= 16; i++) {
	    sg_od_1->Cells[i + 1][16 + 1] = od_lut[16 * 17 + i];
	    sg_od_2->Cells[i + 1][16 + 1] = od_lut[od1_len + 16 * 17 + i];

	    sg_od_1->Cells[i + 1][17 + 1] = sg_od_1->Cells[i + 1][16 + 1];
	    sg_od_1->Cells[i + 1][17 + 1] = sg_od_2->Cells[i + 1][16 + 1];
	}
	// 第18行18列參數
	sg_od_1->Cells[17 + 1][17 + 1] = sg_od_1->Cells[16 + 1][16 + 1];
	sg_od_2->Cells[17 + 1][17 + 1] = sg_od_2->Cells[16 + 1][16 + 1];
    } else if (ODLUT_ip_type == 2) {	// Vender IP
	for (int j = 0; j <= 16; j++) {
	    for (int i = 0; i <= 16; i++) {
		sg_od_1->Cells[i + 1][j + 1] = od_lut[j * 17 + i];
		sg_od_2->Cells[i + 1][j + 1] = od_lut[od1_len + j * 17 + i];
	    }
	}
    }
    delete[]od_lut;
    OD_LUT_FuncEnable(1);
}

//---------------------------------------------------------------------------
// OD table Save
// 20100608 Add Table Operation Disable/Enable
// and Save table for 2 types of IP (AUO 18x18 & vender 17x17)
void __fastcall TFunctionForm1::btn_od_saveClick(TObject * Sender)
{				// File Format: 上方是OD1 17x17 table, 下方是OD2 17x17 table

    if (!SaveDialog->Execute()) {
	return;
    }
    OD_LUT_FuncEnable(0);
    String Fpath = SaveDialog->FileName /*+".txt" */ ;
    FILE *fptr = fopen(Fpath.c_str(), "w");

    //OD1, 排成17x17 table
    int val;
    for (int j = 0; j <= 16; j++) {
	for (int i = 0; i <= 16; i++) {
	    val = StrToInt(sg_od_1->Cells[i + 1][j + 1]);
	    fprintf(fptr, "%d\t", val);
	}
	fprintf(fptr, "\n");
    }
    //接著寫OD2, 排成17x17 table
    for (int j = 0; j <= 16; j++) {
	for (int i = 0; i <= 16; i++) {
	    val = StrToInt(sg_od_2->Cells[i + 1][j + 1]);
	    fprintf(fptr, "%d\t", val);
	}
	fprintf(fptr, "\n");
    }
    fclose(fptr);
    OD_LUT_FuncEnable(1);
}

//---------------------------------------------------------------------------
// 20100608 Choose OD table as Difference or Target Value
void __fastcall TFunctionForm1::rg_od_table_typeClick(TObject * Sender)
{
    if (sg_od_1->Cells[2][2] == "")
	return;
    int Ad_r;
    if (rg_od_table_type->ItemIndex == 0) {	// Show Difference
	Ad_r = -1;		// for remove Start Value
    } else if (rg_od_table_type->ItemIndex == 1) {	// Show Target
	Ad_r = 1;		// for add Start Value
    }
    int bas;			// Start value
    if (ODLUT_ip_type == 1) {	// AUO IP
	for (int j = 0; j <= 17; j++) {
	    bas = (16 * j) >= 256 ? 255 : 16 * j;	// Start value
	    for (int i = 0; i <= 17; i++) {
		sg_od_1->Cells[i + 1][j + 1] =
		    IntToStr((StrToInt(sg_od_1->Cells[i + 1][j + 1]) + Ad_r * bas) % 256);
		sg_od_2->Cells[i + 1][j + 1] =
		    IntToStr((StrToInt(sg_od_2->Cells[i + 1][j + 1]) + Ad_r * bas) % 256);
	    }
	}
    } else if (ODLUT_ip_type == 2) {	// Vender IP
	for (int j = 0; j <= 16; j++) {
	    bas = (16 * j) >= 256 ? 255 : (16 * j);	// Start value
	    for (int i = 0; i <= 16; i++) {
		sg_od_1->Cells[i + 1][j + 1] =
		    IntToStr((StrToInt(sg_od_1->Cells[i + 1][j + 1]) + Ad_r * bas) % 256);
		sg_od_2->Cells[i + 1][j + 1] =
		    IntToStr((StrToInt(sg_od_2->Cells[i + 1][j + 1]) + Ad_r * bas) % 256);
	    }
	}
    }
}

//---------------------------------------------------------------------------

