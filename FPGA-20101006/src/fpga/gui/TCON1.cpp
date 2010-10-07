//---------------------------------------------------------------------------

#include <vcl.h>
#include <fpga/includeall.h>
#pragma hdrstop
#include "TCON1.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"


//---------------------------------------------------------------------------
__fastcall TTCONForm1::TTCONForm1(TComponent * Owner)
:TForm(Owner)
{
    TCON_Chg = 0;
}

//---------------------------------------------------------------------------

void __fastcall TTCONForm1::FormClose(TObject * Sender, TCloseAction & Action)
{
    delete[]OTCON;
    delete[]dev_cb;
    delete[]DevChkB;

    delete[]dev_cbo;
    delete[]DevCboB;

    delete[]dev_lble2;		//Add by Michelle 20100629
    delete[]DevLblE2;

    delete[]io_cb;
    delete[]IOChkB;

    delete[]io_cbo;
    delete[]IOCboB;

    delete[]drv_cb;
    delete[]DrvChkB;

    delete[]drv_cbo;
    delete[]DrvCboB;

    delete[]drv_lble2;
    delete[]DrvLblE2;

    delete[]drv_lble3;		//Add by michelle 20100625
    delete[]DrvLblE3;

    delete[]tim_lble2;
    delete[]TimLblE2;

    //delete [] tim_lble3;
    //delete [] TimLblE3;

    Action = caFree;
    MainForm->TCONFormNULL();
}

//=========================================================================//
//     Device Change                                                       //
//=========================================================================//

void __fastcall TTCONForm1::Dev_CheckBox_Click(TObject * Sender)
{
    if (TCON_Chg == 0)
	return;
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (DevChkB[idx]->Chkb->Checked ? 1 : 0);
    EngineerForm->SetWrite_Byte(DevChkB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void __fastcall TTCONForm1::Dev_ComboBox_Click(TObject * Sender)
{
    if (TCON_Chg == 0)
	return;
    TComboBox *c = (TComboBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (DevCboB[idx]->Cbob->ItemIndex);
    EngineerForm->SetWrite_Byte(DevCboB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
//Add by Michelle 20100629
void __fastcall TTCONForm1::Dev_LblEdit2_KeyPress(TObject * Sender, char &Key)
{
    TLabeledEdit *c = (TLabeledEdit *) Sender;
    int idx = StrToInt(c->Hint);

    if (Key != 13) {
	DevLblE2[idx]->Lble->Font->Color = cl3DDkShadow;
	return;
    }
    //Key = 13, 按下Enter
    if (TCON_Chg == 0)
	return;

    String tmp_v = DevLblE2[idx]->Lble->Text;
    if (tmp_v == "") {
	tmp_v = "0";
    }

    int set_val;
    set_val = StrToInt(tmp_v);

    unsigned char val1, val2;
    //add Max hint
    if (set_val >= pow(2, DevLblE2[idx]->Addr.BitNum())) {
	AnsiString max = "Max value:" + IntToStr((int) pow(2, DevLblE2[idx]->Addr.BitNum()) - 1);
	ShowMessage(max);
	//read value
	EngineerForm->SetRead_Byte(DevLblE2[idx]->Addr.Byte1, &val1);
	EngineerForm->SetRead_Byte(DevLblE2[idx]->Addr.Byte2, &val2);
	DevLblE2[idx]->Lble->Text = (int) val1 *DevLblE2[idx]->Addr.Divide() + val2;
	DevLblE2[idx]->Lble->Font->Color = clWindowText;
    } else {
	val1 = set_val / DevLblE2[idx]->Addr.Divide();
	val2 = set_val % DevLblE2[idx]->Addr.Divide();
	EngineerForm->SetWrite_Byte(DevLblE2[idx]->Addr.Byte1, val1);
	if (DevLblE2[idx]->Addr.Byte2.BitNum() != 0)
	    EngineerForm->SetWrite_Byte(DevLblE2[idx]->Addr.Byte2, val2);
	DevLblE2[idx]->Lble->Font->Color = clWindowText;
    }
}

//=========================================================================//
//     IO Change    (input/ Output)                                        //
//=========================================================================//

void __fastcall TTCONForm1::IO_CheckBox_Click(TObject * Sender)
{
    if (TCON_Chg == 0)
	return;
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (IOChkB[idx]->Chkb->Checked ? 1 : 0);
    EngineerForm->SetWrite_Byte(IOChkB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void __fastcall TTCONForm1::IO_ComboBox_Click(TObject * Sender)
{
    if (TCON_Chg == 0)
	return;
    TComboBox *c = (TComboBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (IOCboB[idx]->Cbob->ItemIndex);
    EngineerForm->SetWrite_Byte(IOCboB[idx]->Addr, set_val);
}

//=========================================================================//
//     Driving change                                                      //
//=========================================================================//

void __fastcall TTCONForm1::Drv_CheckBox_Click(TObject * Sender)
{
    if (TCON_Chg == 0)
	return;
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (DrvChkB[idx]->Chkb->Checked ? 1 : 0);
    EngineerForm->SetWrite_Byte(DrvChkB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------

void __fastcall TTCONForm1::Drv_ComboBox_Click(TObject * Sender)
{
    if (TCON_Chg == 0)
	return;
    TComboBox *c = (TComboBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (DrvCboB[idx]->Cbob->ItemIndex);
    EngineerForm->SetWrite_Byte(DrvCboB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------

void __fastcall TTCONForm1::Drv_LblEdit2_KeyPress(TObject * Sender, char &Key)
{
    TLabeledEdit *c = (TLabeledEdit *) Sender;
    int idx = StrToInt(c->Hint);

    if (Key != 13) {
	DrvLblE2[idx]->Lble->Font->Color = cl3DDkShadow;
	return;
    }
    //Key = 13, 按下Enter
    if (TCON_Chg == 0)
	return;

    String tmp_v = DrvLblE2[idx]->Lble->Text;
    if (tmp_v == "") {
	tmp_v = "0";
    }

    int set_val;
    set_val = StrToInt(tmp_v);

    unsigned char val1, val2;
    //add Max hint
    if (set_val >= pow(2, DrvLblE2[idx]->Addr.BitNum())) {
	AnsiString max = "Max value:" + IntToStr((int) pow(2, DrvLblE2[idx]->Addr.BitNum()) - 1);
	ShowMessage(max);
	//read value
	EngineerForm->SetRead_Byte(DrvLblE2[idx]->Addr.Byte1, &val1);
	EngineerForm->SetRead_Byte(DrvLblE2[idx]->Addr.Byte2, &val2);
	DrvLblE2[idx]->Lble->Text = (int) val1 *DrvLblE2[idx]->Addr.Divide() + val2;
	DrvLblE2[idx]->Lble->Font->Color = clWindowText;
    } else {
	val1 = set_val / DrvLblE2[idx]->Addr.Divide();
	val2 = set_val % DrvLblE2[idx]->Addr.Divide();
	EngineerForm->SetWrite_Byte(DrvLblE2[idx]->Addr.Byte1, val1);
	if (DrvLblE2[idx]->Addr.Byte2.BitNum() != 0)
	    EngineerForm->SetWrite_Byte(DrvLblE2[idx]->Addr.Byte2, val2);
	DrvLblE2[idx]->Lble->Font->Color = clWindowText;
    }
}

void __fastcall TTCONForm1::Drv_LblEdit3_KeyPress(TObject * Sender, char &Key)	//Add by Michelle 20100625
{
    TLabeledEdit *c = (TLabeledEdit *) Sender;
    int idx = StrToInt(c->Hint);

    if (Key != 13) {
	DrvLblE3[idx]->Lble->Font->Color = cl3DDkShadow;
	return;
    }
    //Key = 13, 按下Enter
    if (TCON_Chg == 0)
	return;

    String tmp_v = DrvLblE3[idx]->Lble->Text;

    if (tmp_v == "") {
	tmp_v = "0";
    }
    int set_val = StrToInt(tmp_v);
    unsigned char val1, val2, val3;
    //add for Max hint
    if (set_val >= pow(2, DrvLblE3[idx]->Addr.BitNum())) {
	AnsiString max = "Max value:" + IntToStr((int) pow(2, DrvLblE3[idx]->Addr.BitNum()) - 1);
	ShowMessage(max);
	//read value
	EngineerForm->SetRead_Byte(DrvLblE3[idx]->Addr.Byte1, &val1);
	EngineerForm->SetRead_Byte(DrvLblE3[idx]->Addr.Byte2, &val2);
	EngineerForm->SetRead_Byte(DrvLblE3[idx]->Addr.Byte3, &val3);
	DrvLblE3[idx]->Lble->Text = (int) val1 *DrvLblE3[idx]->Addr.Divide1()
	+ (int) val2 *DrvLblE3[idx]->Addr.Divide2() + (int) val3;	//Mod. Divide1 -> Divide2
    } else {
	val1 = set_val / DrvLblE3[idx]->Addr.Divide1();
	val2 =
	    (set_val / DrvLblE3[idx]->Addr.Divide2()) % (int) pow(2,
								  DrvLblE3[idx]->Addr.Byte2.
								  BitNum());
	val3 = set_val % DrvLblE3[idx]->Addr.Divide2();
	EngineerForm->SetWrite_Byte(DrvLblE3[idx]->Addr.Byte1, val1);
	if (DrvLblE3[idx]->Addr.Byte2.BitNum() != 0)
	    EngineerForm->SetWrite_Byte(DrvLblE3[idx]->Addr.Byte2, val2);
	if (DrvLblE3[idx]->Addr.Byte3.BitNum() != 0)
	    EngineerForm->SetWrite_Byte(DrvLblE3[idx]->Addr.Byte3, val3);
	DrvLblE3[idx]->Lble->Font->Color = clWindowText;
    }
}

//=========================================================================//
//     Timing Change                                                       //
//=========================================================================//

void __fastcall TTCONForm1::Tim_LblEdit2_KeyPress(TObject * Sender, char &Key)
{
    TLabeledEdit *c = (TLabeledEdit *) Sender;
    int idx = StrToInt(c->Hint);

    if (Key != 13) {
	TimLblE2[idx]->Lble->Font->Color = cl3DDkShadow;
	return;
    }
    if (TCON_Chg == 0)
	return;
    String tmp_v = TimLblE2[idx]->Lble->Text;
    if (tmp_v == "") {
	tmp_v = "0";
    }
    int set_val = StrToInt(tmp_v);
    unsigned char val1, val2;
    //add Max hint
    if (set_val >= pow(2, TimLblE2[idx]->Addr.BitNum())) {
	AnsiString max = "Max value:" + IntToStr((int) pow(2, TimLblE2[idx]->Addr.BitNum()) - 1);
	ShowMessage(max);
	//read value
	EngineerForm->SetRead_Byte(TimLblE2[idx]->Addr.Byte1, &val1);
	EngineerForm->SetRead_Byte(TimLblE2[idx]->Addr.Byte2, &val2);
	TimLblE2[idx]->Lble->Text = (int) val1 *TimLblE2[idx]->Addr.Divide() + val2;
	TimLblE2[idx]->Lble->Font->Color = clWindowText;
    } else {
	val1 = set_val / TimLblE2[idx]->Addr.Divide();
	val2 = set_val % TimLblE2[idx]->Addr.Divide();
	EngineerForm->SetWrite_Byte(TimLblE2[idx]->Addr.Byte1, val1);
	if (TimLblE2[idx]->Addr.Byte2.BitNum() != 0)
	    EngineerForm->SetWrite_Byte(TimLblE2[idx]->Addr.Byte2, val2);
	TimLblE2[idx]->Lble->Font->Color = clWindowText;
    }
}

void __fastcall TTCONForm1::TimLblEdit3_KeyPress(TObject * Sender, char &Key)
{
    TLabeledEdit *c = (TLabeledEdit *) Sender;
    int idx = StrToInt(c->Hint);

    if (Key != 13) {
	TimLblE3[idx]->Lble->Font->Color = cl3DDkShadow;
	return;
    }
    //Key = 13, 按下Enter
    if (TCON_Chg == 0)
	return;

    String tmp_v = TimLblE3[idx]->Lble->Text;
    if (tmp_v == "") {
	tmp_v = "0";
    }
    int set_val = StrToInt(tmp_v);
    unsigned char val1, val2, val3;
    //add for Max hint
    if (set_val >= pow(2, TimLblE3[idx]->Addr.BitNum())) {
	AnsiString max = "Max value:" + IntToStr((int) pow(2, TimLblE3[idx]->Addr.BitNum()) - 1);
	ShowMessage(max);
	//read value
	EngineerForm->SetRead_Byte(TimLblE3[idx]->Addr.Byte1, &val1);
	EngineerForm->SetRead_Byte(TimLblE3[idx]->Addr.Byte2, &val2);
	EngineerForm->SetRead_Byte(TimLblE3[idx]->Addr.Byte3, &val3);
	TimLblE3[idx]->Lble->Text = (int) val1 *TimLblE3[idx]->Addr.Divide1()
	+ (int) val2 *TimLblE3[idx]->Addr.Divide2() + (int) val3;	//Mod. Divide1 -> Divide2
    } else {
	val1 = set_val / TimLblE3[idx]->Addr.Divide1();
	val2 =
	    (set_val / TimLblE3[idx]->Addr.Divide2()) % (int) pow(2,
								  TimLblE3[idx]->Addr.Byte2.
								  BitNum());
	val3 = set_val % TimLblE3[idx]->Addr.Divide2();
	EngineerForm->SetWrite_Byte(TimLblE3[idx]->Addr.Byte1, val1);
	if (TimLblE3[idx]->Addr.Byte2.BitNum() != 0)
	    EngineerForm->SetWrite_Byte(TimLblE3[idx]->Addr.Byte2, val2);
	if (TimLblE3[idx]->Addr.Byte3.BitNum() != 0)
	    EngineerForm->SetWrite_Byte(TimLblE3[idx]->Addr.Byte3, val3);
	TimLblE3[idx]->Lble->Font->Color = clWindowText;
    }
}

//---------------------------------------------------------------------------
void __fastcall TTCONForm1::FormCreate(TObject * Sender)
{
    int ic_choice;
    String Path;
    if (MainForm->TCON_DEV == "11307") {
	ic_choice = 0;
	Path = "AUO_11307_addr.txt";
    }

    switch (ic_choice) {
    case 0:
	OTCON = new TCON_11307;
	break;
    }

	/********************************************************************/
    //                                                                  //
    //  Device page has CheckBox*12 & ComboBox*2 & LebleEdit2*8         //
    //                                                                  //
    //******************************************************************//

    //CheckBox
    dev_cb = OTCON->SetDevChkBx();

    DevChkB = new _CHKB *[OTCON->DevChkBox_Nbr];
    for (int i = 0; i < OTCON->DevChkBox_Nbr; i++)
	DevChkB[i] = new _CHKB;

    DevChkB[0]->Chkb = CheckBox1;
    DevChkB[1]->Chkb = CheckBox2;
    DevChkB[2]->Chkb = CheckBox3;
    DevChkB[3]->Chkb = CheckBox4;
    DevChkB[4]->Chkb = CheckBox5;
    DevChkB[5]->Chkb = CheckBox6;
    DevChkB[6]->Chkb = CheckBox7;
    DevChkB[7]->Chkb = CheckBox8;
    DevChkB[8]->Chkb = CheckBox9;
    DevChkB[9]->Chkb = CheckBox10;
    DevChkB[10]->Chkb = CheckBox28;
    DevChkB[11]->Chkb = CheckBox29;
    for (int i = 0; i < OTCON->DevChkBox_Nbr; i++) {
	DevChkB[i]->Addr = dev_cb[i];
	DevChkB[i]->Chkb->Visible = DevChkB[i]->Addr.FuncEn();
	DevChkB[i]->Chkb->OnClick = Dev_CheckBox_Click;
	DevChkB[i]->Chkb->Hint = i;
	DevChkB[i]->Chkb->Caption = DevChkB[i]->Addr.Name();
    }

    //ComboBox
    dev_cbo = OTCON->SetDevCboBx();

    DevCboB = new _CBOB *[OTCON->DevCboBox_Nbr];
    for (int i = 0; i < OTCON->DevCboBox_Nbr; i++)
	DevCboB[i] = new _CBOB;

    DevCboB[0]->Cbob = ComboBox1;
    DevCboB[0]->CbobL = Label1;
    DevCboB[1]->Cbob = ComboBox2;
    DevCboB[1]->CbobL = Label3;


    for (int i = 0; i < OTCON->DevCboBox_Nbr; i++) {
	DevCboB[i]->Addr = dev_cbo[i];
	DevCboB[i]->Cbob->Visible = DevCboB[i]->Addr.FuncEn();
	DevCboB[i]->CbobL->Visible = DevCboB[i]->Addr.FuncEn();
	DevCboB[i]->Cbob->OnClick = Dev_ComboBox_Click;
	DevCboB[i]->Cbob->Hint = i;
	DevCboB[i]->CbobL->Caption = DevCboB[i]->Addr.Name();
	DevCboB[i]->Cbob->Text = "";
	if (DevCboB[i]->Addr.FuncEn())
	    for (int j = 0; j < DevCboB[i]->Addr.choice_nbr; j++)	//ComboBox choice
		DevCboB[i]->Cbob->Items->Add(DevCboB[i]->Addr.choice[j]);
    }

    //Edit    Add by Michelle 20100629
    dev_lble2 = OTCON->SetDevLblE2();

    DevLblE2 = new _LBLE2 *[OTCON->DevLblE2_Nbr];
    for (int i = 0; i < OTCON->DevLblE2_Nbr; i++)
	DevLblE2[i] = new _LBLE2;

    DevLblE2[0]->Lble = LabeledEdit43;
    DevLblE2[1]->Lble = LabeledEdit44;
    DevLblE2[2]->Lble = LabeledEdit45;
    DevLblE2[3]->Lble = LabeledEdit46;
    DevLblE2[4]->Lble = LabeledEdit47;
    DevLblE2[5]->Lble = LabeledEdit48;
    DevLblE2[6]->Lble = LabeledEdit49;
    DevLblE2[7]->Lble = LabeledEdit50;

    for (int i = 0; i < OTCON->DevLblE2_Nbr; i++) {
	DevLblE2[i]->Addr = dev_lble2[i];
	DevLblE2[i]->Lble->Visible = DevLblE2[i]->Addr.FuncEn();
	//DrvLblE2[i]->Lble->OnChange = Drv_LblEdit2_Change;
	DevLblE2[i]->Lble->OnKeyPress = Dev_LblEdit2_KeyPress;
	DevLblE2[i]->Lble->Hint = i;
	DevLblE2[i]->Lble->EditLabel->Caption = DevLblE2[i]->Addr.Name();
	DevLblE2[i]->Lble->Text = 0;
    }

	/********************************************************************/
    //                                                                  //
    //  Input/Output page has CheckBox*13 & ComboBox*1                  //
    //                                                                  //
    //******************************************************************//

    //CheckBox
    io_cb = OTCON->SetIOChkBx();

    IOChkB = new _CHKB *[OTCON->IOChkBox_Nbr];
    for (int i = 0; i < OTCON->IOChkBox_Nbr; i++)
	IOChkB[i] = new _CHKB;

    IOChkB[0]->Chkb = CheckBox11;
    IOChkB[1]->Chkb = CheckBox12;
    IOChkB[2]->Chkb = CheckBox13;
    IOChkB[3]->Chkb = CheckBox14;
    IOChkB[4]->Chkb = CheckBox15;
    IOChkB[5]->Chkb = CheckBox16;
    IOChkB[6]->Chkb = CheckBox17;
    IOChkB[7]->Chkb = CheckBox18;
    IOChkB[8]->Chkb = CheckBox19;
    IOChkB[9]->Chkb = CheckBox20;
    IOChkB[10]->Chkb = CheckBox21;
    IOChkB[11]->Chkb = CheckBox22;
    IOChkB[12]->Chkb = CheckBox23;

    for (int i = 0; i < OTCON->IOChkBox_Nbr; i++) {
	IOChkB[i]->Addr = io_cb[i];
	IOChkB[i]->Chkb->Visible = IOChkB[i]->Addr.FuncEn();
	IOChkB[i]->Chkb->OnClick = IO_CheckBox_Click;
	IOChkB[i]->Chkb->Hint = i;
	IOChkB[i]->Chkb->Caption = IOChkB[i]->Addr.Name();
    }

    //ComboBox
    io_cbo = OTCON->SetIOCboBx();

    IOCboB = new _CBOB *[OTCON->IOChkBox_Nbr];
    for (int i = 0; i < OTCON->IOChkBox_Nbr; i++)
	IOCboB[i] = new _CBOB;

    IOCboB[0]->Cbob = ComboBox4;
    IOCboB[0]->CbobL = Label2;

    for (int i = 0; i < OTCON->IOCboBox_Nbr; i++) {
	IOCboB[i]->Addr = io_cbo[i];
	IOCboB[i]->Cbob->Visible = IOCboB[i]->Addr.FuncEn();
	IOCboB[i]->CbobL->Visible = IOCboB[i]->Addr.FuncEn();
	IOCboB[i]->Cbob->OnClick = IO_ComboBox_Click;
	IOCboB[i]->Cbob->Hint = i;
	IOCboB[i]->CbobL->Caption = IOCboB[i]->Addr.Name();
	IOCboB[i]->Cbob->Text = "";
	if (IOCboB[i]->Addr.FuncEn())
	    for (int j = 0; j < IOCboB[i]->Addr.choice_nbr; j++)	//ComboBox choice
		IOCboB[i]->Cbob->Items->Add(IOCboB[i]->Addr.choice[j]);
    }

	/*******************************************************************/
    //                                                                 //
    //      Driving Page CheckBox*18 & ComboBox*9 & Edit*9             //
    //                                                                 //
	/*******************************************************************/

    //CheckBox
    drv_cb = OTCON->SetDrvChkBx();

    DrvChkB = new _CHKB *[OTCON->DrvChkBox_Nbr];
    for (int i = 0; i < OTCON->DrvChkBox_Nbr; i++)
	DrvChkB[i] = new _CHKB;

    DrvChkB[0]->Chkb = CheckBox30;
    DrvChkB[1]->Chkb = CheckBox31;
    DrvChkB[2]->Chkb = CheckBox32;
    DrvChkB[3]->Chkb = CheckBox33;
    DrvChkB[4]->Chkb = CheckBox34;
    DrvChkB[5]->Chkb = CheckBox35;
    DrvChkB[6]->Chkb = CheckBox36;
    DrvChkB[7]->Chkb = CheckBox37;
    DrvChkB[8]->Chkb = CheckBox38;
    DrvChkB[9]->Chkb = CheckBox39;
    DrvChkB[10]->Chkb = CheckBox40;
    DrvChkB[11]->Chkb = CheckBox41;
    DrvChkB[12]->Chkb = CheckBox42;
    DrvChkB[13]->Chkb = CheckBox43;
    DrvChkB[14]->Chkb = CheckBox44;
    DrvChkB[15]->Chkb = CheckBox45;
    DrvChkB[16]->Chkb = CheckBox46;
    DrvChkB[17]->Chkb = CheckBox47;

    for (int i = 0; i < OTCON->DrvChkBox_Nbr; i++) {
	DrvChkB[i]->Addr = drv_cb[i];
	DrvChkB[i]->Chkb->Visible = DrvChkB[i]->Addr.FuncEn();
	DrvChkB[i]->Chkb->OnClick = Drv_CheckBox_Click;
	DrvChkB[i]->Chkb->Hint = i;
	DrvChkB[i]->Chkb->Caption = DrvChkB[i]->Addr.Name();
    }
    //ComboBox
    drv_cbo = OTCON->SetDrvCboBx();

    DrvCboB = new _CBOB *[OTCON->DrvCboBox_Nbr];
    for (int i = 0; i < OTCON->DrvCboBox_Nbr; i++)
	DrvCboB[i] = new _CBOB;

    DrvCboB[0]->Cbob = ComboBox7;
    DrvCboB[0]->CbobL = Label8;
    DrvCboB[1]->Cbob = ComboBox8;
    DrvCboB[1]->CbobL = Label9;
    DrvCboB[2]->Cbob = ComboBox9;
    DrvCboB[2]->CbobL = Label10;
    DrvCboB[3]->Cbob = ComboBox10;
    DrvCboB[3]->CbobL = Label11;
    DrvCboB[4]->Cbob = ComboBox11;
    DrvCboB[4]->CbobL = Label12;
    DrvCboB[5]->Cbob = ComboBox12;
    DrvCboB[5]->CbobL = Label13;
    DrvCboB[6]->Cbob = ComboBox5;
    DrvCboB[6]->CbobL = Label14;
    DrvCboB[7]->Cbob = ComboBox3;
    DrvCboB[7]->CbobL = Label4;
    DrvCboB[8]->Cbob = ComboBox6;
    DrvCboB[8]->CbobL = Label15;

    for (int i = 0; i < OTCON->DrvCboBox_Nbr; i++) {
	DrvCboB[i]->Addr = drv_cbo[i];
	DrvCboB[i]->Cbob->Visible = DrvCboB[i]->Addr.FuncEn();
	DrvCboB[i]->Cbob->OnClick = Drv_ComboBox_Click;
	DrvCboB[i]->Cbob->Hint = i;
	DrvCboB[i]->CbobL->Caption = DrvCboB[i]->Addr.Name();
	DrvCboB[i]->Cbob->Text = "";
	if (DrvCboB[i]->Addr.FuncEn())
	    for (int j = 0; j < DrvCboB[i]->Addr.choice_nbr; j++)	//ComboBox choice
		DrvCboB[i]->Cbob->Items->Add(DrvCboB[i]->Addr.choice[j]);
    }

    //LabeledEdit2
    drv_lble2 = OTCON->SetDrvLblE();

    DrvLblE2 = new _LBLE2 *[OTCON->DrvLblE2_Nbr];
    for (int i = 0; i < OTCON->DrvLblE2_Nbr; i++)
	DrvLblE2[i] = new _LBLE2;

    DrvLblE2[0]->Lble = LabeledEdit1;
    DrvLblE2[1]->Lble = LabeledEdit2;
    DrvLblE2[2]->Lble = LabeledEdit4;
    DrvLblE2[3]->Lble = LabeledEdit5;
    DrvLblE2[4]->Lble = LabeledEdit51;
    DrvLblE2[5]->Lble = LabeledEdit52;
    DrvLblE2[6]->Lble = LabeledEdit53;
    DrvLblE2[7]->Lble = LabeledEdit54;
    DrvLblE2[8]->Lble = LabeledEdit55;

    for (int i = 0; i < OTCON->DrvLblE2_Nbr; i++) {
	DrvLblE2[i]->Addr = drv_lble2[i];
	DrvLblE2[i]->Lble->Visible = DrvLblE2[i]->Addr.FuncEn();
	//DrvLblE2[i]->Lble->OnChange = Drv_LblEdit2_Change;
	DrvLblE2[i]->Lble->OnKeyPress = Drv_LblEdit2_KeyPress;
	DrvLblE2[i]->Lble->Hint = i;
	DrvLblE2[i]->Lble->EditLabel->Caption = DrvLblE2[i]->Addr.Name();
	DrvLblE2[i]->Lble->Text = 0;
    }
    //LabeledEdit3
    drv_lble3 = OTCON->SetDrvLblE3();

    DrvLblE3 = new _LBLE3 *[OTCON->DrvLblE3_Nbr];
    for (int i = 0; i < OTCON->DrvLblE3_Nbr; i++)
	DrvLblE3[i] = new _LBLE3;

    DrvLblE3[0]->Lble = LabeledEdit56;

    for (int i = 0; i < OTCON->DrvLblE3_Nbr; i++) {
	DrvLblE3[i]->Addr = drv_lble3[i];
	DrvLblE3[i]->Lble->Visible = DrvLblE3[i]->Addr.FuncEn();
	DrvLblE3[i]->Lble->Hint = i;
	DrvLblE3[i]->Lble->EditLabel->Caption = DrvLblE3[i]->Addr.Name();
	DrvLblE3[i]->Lble->OnKeyPress = Drv_LblEdit3_KeyPress;
	DrvLblE3[i]->Lble->Text = 0;
    }
	/*****************************************************************/
    //                                                               //
    //   Timing Page  LabelEdit2*152                                  //
    //                                                               //
	/*****************************************************************/

    //LabeledEdit2
    tim_lble2 = OTCON->SetTimLblE2();

    TimLblE2 = new _LBLE2 *[OTCON->TimLblE2_Nbr];
    for (int i = 0; i < OTCON->TimLblE2_Nbr; i++)
	TimLblE2[i] = new _LBLE2;

    TimLblE2[0]->Lble = LabeledEdit3;
    TimLblE2[35]->Lble = LabeledEdit57;
    TimLblE2[1]->Lble = LabeledEdit6;
    TimLblE2[36]->Lble = LabeledEdit58;
    TimLblE2[2]->Lble = LabeledEdit7;
    TimLblE2[3]->Lble = LabeledEdit8;
    //Normal
    TimLblE2[4]->Lble = LabeledEdit9;
    TimLblE2[5]->Lble = LabeledEdit10;
    TimLblE2[6]->Lble = LabeledEdit11;
    TimLblE2[7]->Lble = LabeledEdit12;
    //Frame 60 Area1
    TimLblE2[8]->Lble = LabeledEdit13;
    TimLblE2[37]->Lble = LabeledEdit59;
    TimLblE2[9]->Lble = LabeledEdit14;
    TimLblE2[38]->Lble = LabeledEdit60;
    TimLblE2[10]->Lble = LabeledEdit15;
    TimLblE2[39]->Lble = LabeledEdit61;
    TimLblE2[11]->Lble = LabeledEdit16;
    TimLblE2[40]->Lble = LabeledEdit62;
    //Frame 40 Area1
    TimLblE2[16]->Lble = LabeledEdit21;
    TimLblE2[41]->Lble = LabeledEdit67;
    TimLblE2[17]->Lble = LabeledEdit22;
    TimLblE2[42]->Lble = LabeledEdit68;
    TimLblE2[18]->Lble = LabeledEdit23;
    TimLblE2[43]->Lble = LabeledEdit69;
    TimLblE2[19]->Lble = LabeledEdit24;
    TimLblE2[44]->Lble = LabeledEdit70;
    //Frame 60 Area2
    TimLblE2[72]->Lble = LabeledEdit63;
    TimLblE2[73]->Lble = LabeledEdit71;
    TimLblE2[74]->Lble = LabeledEdit64;
    TimLblE2[75]->Lble = LabeledEdit72;
    TimLblE2[51]->Lble = LabeledEdit65;
    TimLblE2[64]->Lble = LabeledEdit73;
    TimLblE2[65]->Lble = LabeledEdit66;
    TimLblE2[71]->Lble = LabeledEdit74;
    //Frame 40 Area2
    TimLblE2[92]->Lble = LabeledEdit75;
    TimLblE2[93]->Lble = LabeledEdit79;
    TimLblE2[94]->Lble = LabeledEdit76;
    TimLblE2[95]->Lble = LabeledEdit80;
    TimLblE2[88]->Lble = LabeledEdit77;
    TimLblE2[89]->Lble = LabeledEdit81;
    TimLblE2[90]->Lble = LabeledEdit78;
    TimLblE2[91]->Lble = LabeledEdit82;
    //Frame 60 Area3
    TimLblE2[86]->Lble = LabeledEdit83;
    TimLblE2[87]->Lble = LabeledEdit87;
    TimLblE2[46]->Lble = LabeledEdit84;
    TimLblE2[34]->Lble = LabeledEdit88;
    TimLblE2[76]->Lble = LabeledEdit85;
    TimLblE2[82]->Lble = LabeledEdit89;
    TimLblE2[84]->Lble = LabeledEdit86;
    TimLblE2[85]->Lble = LabeledEdit90;
    //Frame 40 Area3
    TimLblE2[100]->Lble = LabeledEdit91;
    TimLblE2[101]->Lble = LabeledEdit95;
    TimLblE2[102]->Lble = LabeledEdit92;
    TimLblE2[103]->Lble = LabeledEdit96;
    TimLblE2[96]->Lble = LabeledEdit93;
    TimLblE2[97]->Lble = LabeledEdit97;
    TimLblE2[98]->Lble = LabeledEdit94;
    TimLblE2[99]->Lble = LabeledEdit98;
    //Fix Gate On 60
    TimLblE2[12]->Lble = LabeledEdit17;
    TimLblE2[151]->Lble = LabeledEdit99;
    TimLblE2[13]->Lble = LabeledEdit18;
    TimLblE2[122]->Lble = LabeledEdit100;
    TimLblE2[14]->Lble = LabeledEdit19;
    TimLblE2[123]->Lble = LabeledEdit101;
    TimLblE2[15]->Lble = LabeledEdit20;
    TimLblE2[124]->Lble = LabeledEdit102;
    //Fix Gate On 40
    TimLblE2[20]->Lble = LabeledEdit25;
    TimLblE2[144]->Lble = LabeledEdit111;
    TimLblE2[21]->Lble = LabeledEdit26;
    TimLblE2[145]->Lble = LabeledEdit112;
    TimLblE2[22]->Lble = LabeledEdit27;
    TimLblE2[105]->Lble = LabeledEdit113;
    TimLblE2[23]->Lble = LabeledEdit28;
    TimLblE2[146]->Lble = LabeledEdit114;
    //Fix Gate On 60 Area2
    TimLblE2[115]->Lble = LabeledEdit123;
    TimLblE2[150]->Lble = LabeledEdit127;
    TimLblE2[104]->Lble = LabeledEdit124;
    TimLblE2[125]->Lble = LabeledEdit128;
    TimLblE2[116]->Lble = LabeledEdit125;
    TimLblE2[126]->Lble = LabeledEdit129;
    TimLblE2[117]->Lble = LabeledEdit126;
    TimLblE2[127]->Lble = LabeledEdit130;
    //Fix Gate On 40 Area2
    TimLblE2[136]->Lble = LabeledEdit131;
    TimLblE2[147]->Lble = LabeledEdit135;
    TimLblE2[137]->Lble = LabeledEdit132;
    TimLblE2[148]->Lble = LabeledEdit136;
    TimLblE2[138]->Lble = LabeledEdit133;
    TimLblE2[27]->Lble = LabeledEdit137;
    TimLblE2[139]->Lble = LabeledEdit134;
    TimLblE2[28]->Lble = LabeledEdit138;
    //Fix Gate On 60 Area3
    TimLblE2[119]->Lble = LabeledEdit139;
    TimLblE2[128]->Lble = LabeledEdit143;
    TimLblE2[118]->Lble = LabeledEdit140;
    TimLblE2[129]->Lble = LabeledEdit144;
    TimLblE2[120]->Lble = LabeledEdit141;
    TimLblE2[130]->Lble = LabeledEdit145;
    TimLblE2[121]->Lble = LabeledEdit142;
    TimLblE2[131]->Lble = LabeledEdit146;
    //Fix Gate On 40 Area3
    TimLblE2[140]->Lble = LabeledEdit147;
    TimLblE2[30]->Lble = LabeledEdit151;
    TimLblE2[141]->Lble = LabeledEdit148;
    TimLblE2[32]->Lble = LabeledEdit152;
    TimLblE2[142]->Lble = LabeledEdit149;
    TimLblE2[33]->Lble = LabeledEdit153;
    TimLblE2[143]->Lble = LabeledEdit150;
    TimLblE2[48]->Lble = LabeledEdit154;
    //Pre-Cgarge
    TimLblE2[24]->Lble = LabeledEdit29;
    TimLblE2[50]->Lble = LabeledEdit39;
    TimLblE2[25]->Lble = LabeledEdit30;
    TimLblE2[106]->Lble = LabeledEdit40;
    TimLblE2[26]->Lble = LabeledEdit42;
    TimLblE2[60]->Lble = LabeledEdit31;
    TimLblE2[62]->Lble = LabeledEdit41;
    TimLblE2[61]->Lble = LabeledEdit103;
    TimLblE2[63]->Lble = LabeledEdit104;

    TimLblE2[111]->Lble = LabeledEdit105;
    TimLblE2[132]->Lble = LabeledEdit106;
    TimLblE2[112]->Lble = LabeledEdit107;
    TimLblE2[133]->Lble = LabeledEdit108;
    TimLblE2[113]->Lble = LabeledEdit109;
    TimLblE2[134]->Lble = LabeledEdit110;
    TimLblE2[114]->Lble = LabeledEdit115;
    TimLblE2[135]->Lble = LabeledEdit116;
    //GOA
    TimLblE2[66]->Lble = LabeledEdit32;
    TimLblE2[108]->Lble = LabeledEdit33;
    //GOA 60
    TimLblE2[77]->Lble = LabeledEdit34;
    TimLblE2[52]->Lble = LabeledEdit35;
    TimLblE2[107]->Lble = LabeledEdit36;
    TimLblE2[29]->Lble = LabeledEdit37;
    TimLblE2[45]->Lble = LabeledEdit38;
    TimLblE2[31]->Lble = LabeledEdit117;
    TimLblE2[47]->Lble = LabeledEdit118;
    TimLblE2[109]->Lble = LabeledEdit119;
    TimLblE2[67]->Lble = LabeledEdit120;
    TimLblE2[69]->Lble = LabeledEdit121;
    TimLblE2[79]->Lble = LabeledEdit122;
    //GOA 40
    TimLblE2[78]->Lble = LabeledEdit155;
    TimLblE2[53]->Lble = LabeledEdit156;
    TimLblE2[149]->Lble = LabeledEdit157;
    TimLblE2[81]->Lble = LabeledEdit158;

    TimLblE2[83]->Lble = LabeledEdit159;
    TimLblE2[49]->Lble = LabeledEdit160;
    TimLblE2[110]->Lble = LabeledEdit161;
    TimLblE2[68]->Lble = LabeledEdit162;
    TimLblE2[70]->Lble = LabeledEdit163;
    TimLblE2[80]->Lble = LabeledEdit164;
    //HSD_XSTB
    TimLblE2[54]->Lble = LabeledEdit165;
    TimLblE2[55]->Lble = LabeledEdit166;
    TimLblE2[56]->Lble = LabeledEdit167;
    TimLblE2[57]->Lble = LabeledEdit168;
    TimLblE2[58]->Lble = LabeledEdit169;
    TimLblE2[59]->Lble = LabeledEdit170;

    for (int i = 0; i < OTCON->TimLblE2_Nbr; i++) {
	TimLblE2[i]->Addr = tim_lble2[i];
	TimLblE2[i]->Lble->Visible = TimLblE2[i]->Addr.FuncEn();
	TimLblE2[i]->Lble->OnKeyPress = Tim_LblEdit2_KeyPress;
	TimLblE2[i]->Lble->Hint = i;
	TimLblE2[i]->Lble->EditLabel->Caption = TimLblE2[i]->Addr.Name();
	TimLblE2[i]->Lble->Text = 0;
    }

    //LabeledEdit3
    tim_lble3 = OTCON->SetTimLblE3();

    TimLblE3 = new _LBLE3 *[OTCON->TimLblE3_Nbr];
    for (int i = 0; i < OTCON->TimLblE3_Nbr; i++)
	TimLblE3[i] = new _LBLE3;

    //TimLblE3[0]->Lble = LabeledEdit42;
    for (int i = 0; i < OTCON->TimLblE3_Nbr; i++) {
	TimLblE3[i]->Addr = tim_lble3[i];
	TimLblE3[i]->Lble->Visible = TimLblE3[i]->Addr.FuncEn();
	TimLblE3[i]->Lble->Hint = i;
	TimLblE3[i]->Lble->EditLabel->Caption = TimLblE3[i]->Addr.Name();
	TimLblE3[i]->Lble->OnKeyPress = TimLblEdit3_KeyPress;
	TimLblE3[i]->Lble->Text = 0;
    }
    TCON_Chg = 1;
}

//---------------------------------------------------------------------------



void __fastcall TTCONForm1::Btn_TCON_dev_reloadClick(TObject * Sender)
{
    Btn_TCON_dev_reload->Enabled = false;
    TCON_Chg = 0;
    unsigned char read_val;
    for (int i = 0; i < OTCON->DevChkBox_Nbr; i++) {
	if (DevChkB[i]->Chkb->Visible == true) {
	    EngineerForm->SetRead_Byte(DevChkB[i]->Addr, &read_val);
	    if (read_val == 1)
		DevChkB[i]->Chkb->Checked = 1;
	    else if (read_val == 0)
		DevChkB[i]->Chkb->Checked = 0;
	    else
		ShowMessage("device CheckBox read error:" + IntToStr(read_val));
	}
    }
    for (int i = 0; i < OTCON->DevCboBox_Nbr; i++) {
	if (DevCboB[i]->Cbob->Visible == true) {
	    EngineerForm->SetRead_Byte(DevCboB[i]->Addr, &read_val);
	    DevCboB[i]->Cbob->ItemIndex = read_val;
	}
    }
    unsigned char read_val1, read_val2;
    for (int i = 0; i < OTCON->DevLblE2_Nbr; i++) {
	if (DevLblE2[i]->Lble->Visible == true) {
	    EngineerForm->SetRead_Byte(DevLblE2[i]->Addr.Byte1, &read_val1);
	    EngineerForm->SetRead_Byte(DevLblE2[i]->Addr.Byte2, &read_val2);
	    DevLblE2[i]->Lble->Text = (int) read_val1 *DevLblE2[i]->Addr.Divide() + read_val2;
	    DevLblE2[i]->Lble->Font->Color = clWindowText;
	}
    }

    TCON_Chg = 1;
    Btn_TCON_dev_reload->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TTCONForm1::Btn_TCON_drv_reloadClick(TObject * Sender)
{
    Btn_TCON_drv_reload->Enabled = false;
    TCON_Chg = 0;
    unsigned char read_val;
    for (int i = 0; i < OTCON->DrvChkBox_Nbr; i++) {
	if (DrvChkB[i]->Chkb->Visible == true) {
	    EngineerForm->SetRead_Byte(DrvChkB[i]->Addr, &read_val);
	    if (read_val == 1)
		DrvChkB[i]->Chkb->Checked = 1;
	    else if (read_val == 0)
		DrvChkB[i]->Chkb->Checked = 0;
	    else
		ShowMessage("device CheckBox read error:" + IntToStr(read_val));
	}
    }
    for (int i = 0; i < OTCON->DrvCboBox_Nbr; i++) {
	if (DrvCboB[i]->Cbob->Visible == true) {
	    EngineerForm->SetRead_Byte(DrvCboB[i]->Addr, &read_val);
	    DrvCboB[i]->Cbob->ItemIndex = read_val;
	}
    }
    unsigned char read_val1, read_val2, read_val3;
    for (int i = 0; i < OTCON->DrvLblE2_Nbr; i++) {
	if (DrvLblE2[i]->Lble->Visible == true) {
	    EngineerForm->SetRead_Byte(DrvLblE2[i]->Addr.Byte1, &read_val1);
	    EngineerForm->SetRead_Byte(DrvLblE2[i]->Addr.Byte2, &read_val2);
	    DrvLblE2[i]->Lble->Text = (int) read_val1 *DrvLblE2[i]->Addr.Divide() + read_val2;
	    DrvLblE2[i]->Lble->Font->Color = clWindowText;
	}
    }
    // Add by Michelle 20100701
    for (int i = 0; i < OTCON->DrvLblE3_Nbr; i++) {
	if (DrvLblE3[i]->Lble->Visible == true) {
	    EngineerForm->SetRead_Byte(DrvLblE3[i]->Addr.Byte1, &read_val1);
	    EngineerForm->SetRead_Byte(DrvLblE3[i]->Addr.Byte2, &read_val2);
	    EngineerForm->SetRead_Byte(DrvLblE3[i]->Addr.Byte3, &read_val3);
	    DrvLblE3[i]->Lble->Text = (int) read_val1 *DrvLblE3[i]->Addr.Divide1()
	    + (int) read_val2 *DrvLblE3[i]->Addr.Divide2() + (int) read_val3;
	}
    }
    TCON_Chg = 1;
    Btn_TCON_drv_reload->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TTCONForm1::Btn_TCON_io_reloadClick(TObject * Sender)
{
    Btn_TCON_io_reload->Enabled = false;
    TCON_Chg = 0;
    unsigned char read_val;
    for (int i = 0; i < OTCON->IOChkBox_Nbr; i++) {
	if (IOChkB[i]->Chkb->Visible == true) {
	    EngineerForm->SetRead_Byte(IOChkB[i]->Addr, &read_val);
	    if (read_val == 1)
		IOChkB[i]->Chkb->Checked = 1;
	    else if (read_val == 0)
		IOChkB[i]->Chkb->Checked = 0;
	    else
		ShowMessage("device CheckBox read error:" + IntToStr(read_val));
	}
    }
    for (int i = 0; i < OTCON->IOCboBox_Nbr; i++) {
	if (IOCboB[i]->Cbob->Visible == true) {
	    EngineerForm->SetRead_Byte(IOCboB[i]->Addr, &read_val);
	    IOCboB[i]->Cbob->ItemIndex = read_val;
	}
    }
    TCON_Chg = 1;
    Btn_TCON_io_reload->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TTCONForm1::Btn_TCON_Tim_reloadClick(TObject * Sender)
{
    Btn_TCON_Tim_reload->Enabled = false;
    unsigned char read_val1, read_val2, read_val3;
    for (int i = 0; i < OTCON->TimLblE2_Nbr; i++) {
	if (TimLblE2[i]->Lble->Visible == true) {
	    EngineerForm->SetRead_Byte(TimLblE2[i]->Addr.Byte1, &read_val1);
	    EngineerForm->SetRead_Byte(TimLblE2[i]->Addr.Byte2, &read_val2);
	    TimLblE2[i]->Lble->Text = (int) read_val1 *TimLblE2[i]->Addr.Divide() + read_val2;
	    TimLblE2[i]->Lble->Font->Color = clWindowText;
	}
    }

    for (int i = 0; i < OTCON->TimLblE3_Nbr; i++) {
	if (TimLblE3[i]->Lble->Visible == true) {
	    EngineerForm->SetRead_Byte(TimLblE3[i]->Addr.Byte1, &read_val1);
	    EngineerForm->SetRead_Byte(TimLblE3[i]->Addr.Byte2, &read_val2);
	    EngineerForm->SetRead_Byte(TimLblE3[i]->Addr.Byte3, &read_val3);
	    TimLblE3[i]->Lble->Text = (int) read_val1 *TimLblE3[i]->Addr.Divide1()
	    + (int) read_val2 *TimLblE3[i]->Addr.Divide2() + (int) read_val3;
	}
    }
    Btn_TCON_Tim_reload->Enabled = true;
}

//---------------------------------------------------------------------------




void __fastcall TTCONForm1::FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift)
{
    if (Key == 0x40) {
	Btn_TCON_dev_reloadClick(Sender);
	Btn_TCON_drv_reloadClick(Sender);
	Btn_TCON_io_reloadClick(Sender);
	Btn_TCON_Tim_reloadClick(Sender);
    }
}

//---------------------------------------------------------------------------

