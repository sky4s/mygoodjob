//---------------------------------------------------------------------------

#include <vcl.h>
#include <lib/CMSCpp2.1/src/includeall.h>
#pragma hdrstop

#include "CM1.h"
#include "include.h"
#include <fpga/11307/ImageProcess/ImgProc_11307.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "PERFGRAP"
#pragma resource "*.dfm"


void TCMForm1::CM_val_initial()
{
    for (int i = 0; i < 3; i++) {
	for (int j = 0; j < 3; j++) {
	    CM1[i][j] = 0;
	    CM2[i][j] = 0;
	    CM3[i][j] = 0;
	}
	CM1[i][i] = 1;
	CM2[i][i] = 1;
	CM3[i][i] = 1;
    }
}

//---------------------------------------------------------------------------
__fastcall TCMForm1::TCMForm1(TComponent * Owner)
:TForm(Owner), CM_IsChkSum(false), CMInitialized(false)
{
    CM1EditArray[0] = CM1_11;
    CM1EditArray[1] = CM1_12;
    CM1EditArray[2] = CM1_13;
    CM1EditArray[3] = CM1_21;
    CM1EditArray[4] = CM1_22;
    CM1EditArray[5] = CM1_23;
    CM1EditArray[6] = CM1_31;
    CM1EditArray[7] = CM1_32;
    CM1EditArray[8] = CM1_33;

    CM2EditArray[0] = CM2_11;
    CM2EditArray[1] = CM2_12;
    CM2EditArray[2] = CM2_13;
    CM2EditArray[3] = CM2_21;
    CM2EditArray[4] = CM2_22;
    CM2EditArray[5] = CM2_23;
    CM2EditArray[6] = CM2_31;
    CM2EditArray[7] = CM2_32;
    CM2EditArray[8] = CM2_33;

    CM3EditArray[0] = CM3_11;
    CM3EditArray[1] = CM3_12;
    CM3EditArray[2] = CM3_13;
    CM3EditArray[3] = CM3_21;
    CM3EditArray[4] = CM3_22;
    CM3EditArray[5] = CM3_23;
    CM3EditArray[6] = CM3_31;
    CM3EditArray[7] = CM3_32;
    CM3EditArray[8] = CM3_33;
}

//---------------------------------------------------------------------------
void __fastcall TCMForm1::CM_CheckBox_Click(TObject * Sender)
{
    if (false == CMInitialized) {
	return;
    }
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (CMChkB[idx]->Chkb->Checked ? 1 : 0);
    EngineerForm->SetWrite_Byte(CMChkB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void __fastcall TCMForm1::CM_ComboBox_Click(TObject * Sender)
{
    if (false == CMInitialized) {
	return;
    }
    TComboBox *c = (TComboBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (CMCboB[idx]->Cbob->ItemIndex);
    EngineerForm->SetWrite_Byte(CMCboB[idx]->Addr, set_val);
    if (idx == 0) {		//CM_SEL
	TS_CM->TabIndex = CMCboB[idx]->Cbob->ItemIndex - 1;
	if (TS_CM->TabIndex == 0) {
	    TS_CM->ActivePage = th_CM1;
	    TS_CM->Visible = true;
	} else if (TS_CM->TabIndex == 1) {
	    TS_CM->ActivePage = th_CM2;
	    TS_CM->Visible = true;
	} else if (TS_CM->TabIndex == 2) {
	    TS_CM->ActivePage = th_CM3;
	    TS_CM->Visible = true;
	}			//else
	//TS_CM->Visible = false;    //remove by Michelle 20100720
    }
}

//---------------------------------------------------------------------------
void __fastcall TCMForm1::FormCreate(TObject * Sender)
{
    CMInitialized = false;
    int ic_choice;
    if (MainForm->TCON_DEV == "11307") {
	ic_choice = 0;
    }

    switch (ic_choice) {
    case 0:
	OCM = new CM_11307;
	break;
    }

	/********************************************************************/
    //                                                                  //
    //  Image Process CM has CheckBox*3 & ComboBox*1  & CM*3 & ofs*3    //
    //                                                                  //
    //******************************************************************//

    //=========================================================================
    //CheckBox
    //=========================================================================
    cm_cb = OCM->SetChkBx();

    CMChkB = new _CHKB *[OCM->CMChkBox_Nbr];
    for (int i = 0; i < OCM->CMChkBox_Nbr; i++) {
	CMChkB[i] = new _CHKB;
    }

    CMChkB[0]->Chkb = CheckBox1;
    CMChkB[1]->Chkb = CheckBox2;
    CMChkB[2]->Chkb = CheckBox3;
    CMChkB[3]->Chkb = CheckBox4;

    for (int i = 0; i < OCM->CMChkBox_Nbr; i++) {
	CMChkB[i]->Addr = cm_cb[i];
	CMChkB[i]->Chkb->Visible = CMChkB[i]->Addr.FuncEn();
	CMChkB[i]->Chkb->OnClick = CM_CheckBox_Click;
	CMChkB[i]->Chkb->Hint = i;
	CMChkB[i]->Chkb->Caption = CMChkB[i]->Addr.Name();
    }
    //=========================================================================
    //=========================================================================
    //Combobox
    //=========================================================================
    cm_cbo = OCM->SetCboBx();

    CMCboB = new _CBOB *[OCM->CMCboBox_Nbr];
    for (int i = 0; i < OCM->CMCboBox_Nbr; i++) {
	CMCboB[i] = new _CBOB;
    }

    CMCboB[0]->Cbob = ComboBox1;
    CMCboB[0]->CbobL = Label4;

    for (int i = 0; i < OCM->CMCboBox_Nbr; i++) {
	CMCboB[i]->Addr = cm_cbo[i];
	CMCboB[i]->Cbob->Visible = CMCboB[i]->Addr.FuncEn();
	CMCboB[i]->CbobL->Visible = CMCboB[i]->Addr.FuncEn();
	CMCboB[i]->Cbob->OnClick = CM_ComboBox_Click;
	CMCboB[i]->Cbob->Hint = i;
	CMCboB[i]->CbobL->Caption = CMCboB[i]->Addr.Name();
	CMCboB[i]->Cbob->Text = "";
	if (CMCboB[i]->Addr.FuncEn()) {
	    for (int j = 0; j < CMCboB[i]->Addr.choice_nbr; j++) {	//ComboBox choice
		CMCboB[i]->Cbob->Items->Add(CMCboB[i]->Addr.choice[j]);
	    }

	}
    }
    //=========================================================================

    //CM value
    CM_addr = OCM->Setval();
    CM_val_initial();

    float tmp = sb_cm11->Position;
    st_CM11gain->Caption = FloatToStr(tmp) + "%";
    tmp = sb_cm12->Position;
    st_CM12gain->Caption = FloatToStr(tmp) + "%";
    tmp = sb_cm13->Position;
    st_CM13gain->Caption = FloatToStr(tmp) + "%";

    //offset value
    ofs_addr = OCM->Setofs();
    st_ofs1->Caption = 0;
    st_ofs2->Caption = 0;
    st_ofs3->Caption = 0;
    offsetType = (OffsetType) OCM->Setofs_type();
    if (_128 == offsetType || _257 == offsetType || _511 == offsetType) {
	Convert_type = 1;
    }				// 2's completement
    else if (_64 == offsetType) {
	Convert_type = 2;
    }				// highest bit is sign bit

    CMInitialized = true;


}

//---------------------------------------------------------------------------
void __fastcall TCMForm1::Btn_CM_reloadClick(TObject * Sender)
{
    Btn_CM_reload->Enabled = false;
    CMInitialized = false;
    unsigned char read_val;
    for (int i = 0; i < OCM->CMChkBox_Nbr; i++) {
	if (CMChkB[i]->Chkb->Visible == true) {
	    EngineerForm->SetRead_Byte(CMChkB[i]->Addr, &read_val);
	    if (read_val == 1) {
		CMChkB[i]->Chkb->Checked = 1;
	    } else if (read_val == 0) {
		CMChkB[i]->Chkb->Checked = 0;
	    } else {
		ShowMessage("CM CheckBox read error:" + IntToStr(read_val));
	    }
	}
    }
    for (int i = 0; i < OCM->CMCboBox_Nbr; i++) {
	if (CMCboB[i]->Cbob->Visible == true) {
	    EngineerForm->SetRead_Byte(CMCboB[i]->Addr, &read_val);
	    CMCboB[i]->Cbob->ItemIndex = read_val;
	}
    }
    btn_CM1_ReadClick(Sender);
    btn_CM2_ReadClick(Sender);
    btn_CM3_ReadClick(Sender);
    CMInitialized = true;
    Btn_CM_reload->Enabled = true;
}

//---------------------------------------------------------------------------
int TCMForm1::FloatToMemForm(int temp)	//CM 10bit value to sign value
{
    temp = temp > 511 ? 511 : temp;
    temp = temp < 0 ? 512 - temp : temp;
    temp = temp > 1023 ? 1023 : temp;

    return temp;
}

//-----------------------------------------------------------------------------
int TCMForm1::MemToFloatForm(int mem)	//CM 10bit from sign value to 10bit value
{
    mem = mem > 512 ? 512 - mem : mem;
    return mem;
}

//---------------------------------------------------------------------------
//CM offset 10bit from 10bit value to 2's complement value
int TCMForm1::FloatToMemOfsForm(int ofs)
{
    ofs -= 512;			// Position 512 => value 0
    if (ofs < 0) {
	if (Convert_type == 2) {
	    ofs = 512 - ofs;
	} else if (Convert_type == 1) {	//2's completement
	    ofs = 1024 + ofs;
	}
    }
    return ofs;
}

//-----------------------------------------------------------------------------
//CM offset 10bit from 2's complement value to 10 bit value
int TCMForm1::MemToFloatOfsForm(int ofs)
{
    if (ofs > 512) {
	if (Convert_type == 2) {
	    ofs = 512 - ofs;
	} else if (Convert_type == 1) {	//2's completement
	    ofs = ofs - 1024;
	}
    }
    ofs += 512;			// Position 512 => value 0
    return ofs;
}

//---------------------------------------------------------------------------
void TCMForm1::loadCMFromTCON(int index, TEdit * e[9], TScrollBar * offset)
{

    if (CM_addr[index].LutNum() != 9) {	//Check CM1 table number
	String msg = "CM";
	msg += (index + 1);
	msg += " LUT number defined is wrong.";
	ShowMessage(msg);
	return;
    }
    int lutLum = CM_addr[index].LutNum();
    int *CM = new int[lutLum];
    //read Matrix
    EngineerForm->SetRead_PG(CM_addr[index], CM, CM_IsChkSum);
    float *CM_f = new float[lutLum];
    for (int i = 0; i < lutLum; i++) {
	CM_f[i] = (double) (MemToFloatForm(CM[i])) / 256;
    }
    e[0]->Text = FloatToStr(CM_f[0]);
    e[1]->Text = FloatToStr(CM_f[1]);
    e[2]->Text = FloatToStr(CM_f[2]);
    e[3]->Text = FloatToStr(CM_f[3]);
    e[4]->Text = FloatToStr(CM_f[4]);
    e[5]->Text = FloatToStr(CM_f[5]);
    e[6]->Text = FloatToStr(CM_f[6]);
    e[7]->Text = FloatToStr(CM_f[7]);
    e[8]->Text = FloatToStr(CM_f[8]);

    int *ofs = new int[ofs_addr[index].LutNum()];
    //read Offset
    EngineerForm->SetRead_PG(ofs_addr[index], ofs, CM_IsChkSum);
    if (ofs[0] != ofs[1] || ofs[1] != ofs[2]) {
	ShowMessage("The 3 Offset values are different.");
    }

    int sb_position = MemToFloatOfsForm(ofs[0]);
    /*sb_ofs1->Position = sb_position;

       float s = parsePosition(sb_position);

       char buf[6];
       sprintf(buf, "%3.2f", s);
       offset->Caption = (AnsiString) buf; */
    offset->Position = sb_position;

    delete[]CM;
    delete[]ofs;
    delete[]CM_f;
};

void __fastcall TCMForm1::btn_CM1_ReadClick(TObject * Sender)
{
    btn_CM1_Read->Enabled = false;
    loadCMFromTCON(0, CM1EditArray, sb_ofs1);
    btn_CM1_Read->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TCMForm1::btn_CM2_ReadClick(TObject * Sender)
{
    btn_CM2_Read->Enabled = false;
    loadCMFromTCON(1, CM2EditArray, sb_ofs2);
    btn_CM2_Read->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TCMForm1::btn_CM3_ReadClick(TObject * Sender)
{
    btn_CM3_Read->Enabled = false;
    loadCMFromTCON(2, CM3EditArray, sb_ofs3);
    btn_CM3_Read->Enabled = true;
}

//---------------------------------------------------------------------------

void TCMForm1::storeCMToTCON(const int index, TEdit * e[9], TScrollBar * offset)
{
    //Write CM
    if (CM_addr[index].LutNum() != 9) {	//Check CM1 table number
	String msg = "CM";
	msg += index;
	msg += " LUT number defined in AddressCM.cpp is wrong.";

	ShowMessage(msg);
	return;
    }

    int CM[9];
    CM[0] = StrToFloat(e[0]->Text) * 256;
    CM[0] = FloatToMemForm(CM[0]);
    CM[1] = StrToFloat(e[1]->Text) * 256;
    CM[1] = FloatToMemForm(CM[1]);
    CM[2] = StrToFloat(e[2]->Text) * 256;
    CM[2] = FloatToMemForm(CM[2]);

    CM[3] = StrToFloat(e[3]->Text) * 256;
    CM[3] = FloatToMemForm(CM[3]);
    CM[4] = StrToFloat(e[4]->Text) * 256;
    CM[4] = FloatToMemForm(CM[4]);
    CM[5] = StrToFloat(e[5]->Text) * 256;
    CM[5] = FloatToMemForm(CM[5]);

    CM[6] = StrToFloat(e[6]->Text) * 256;
    CM[6] = FloatToMemForm(CM[6]);
    CM[7] = StrToFloat(e[7]->Text) * 256;
    CM[7] = FloatToMemForm(CM[7]);
    CM[8] = StrToFloat(e[8]->Text) * 256;
    CM[8] = FloatToMemForm(CM[8]);

    EngineerForm->SetWrite_PG(CM_addr[index], CM, CM_IsChkSum);

    //Write Offset
    if (ofs_addr[index].LutNum() != 3) {	//check offset table number
	ShowMessage("CM1 offset LUT number defined in AddressCM.cpp is wrong.");
	return;
    }

    writeOffset(ofs_addr[index], offset->Position);
};

void __fastcall TCMForm1::btn_CM1_WriteClick(TObject * Sender)
{
    btn_CM1_Write->Enabled = false;
    storeCMToTCON(0, CM1EditArray, sb_ofs1);
    btn_CM1_Write->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TCMForm1::btn_CM2_WriteClick(TObject * Sender)
{
    btn_CM2_Write->Enabled = false;
    storeCMToTCON(1, CM2EditArray, sb_ofs2);
    btn_CM2_Write->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TCMForm1::btn_CM3_WriteClick(TObject * Sender)
{
    btn_CM3_Write->Enabled = false;
    storeCMToTCON(2, CM3EditArray, sb_ofs3);
    btn_CM3_Write->Enabled = true;
}

//---------------------------------------------------------------------------

void CM_GainFunc(double *d_ratio, float var1, float var2)
{
    if (var1 == 0 && var2 == 0) {
	d_ratio[0] = 0.5;
	d_ratio[1] = 0.5;
    } else if (var1 + var2 == 0 & var1 < 0) {
	d_ratio[0] = -0.5;
	d_ratio[1] = 0.5;
    } else if (var1 + var2 == 0 & var2 < 0) {
	d_ratio[0] = 0.5;
	d_ratio[1] = -0.5;
    } else {
	d_ratio[0] = var1 / (var1 + var2);
	d_ratio[1] = var2 / (var1 + var2);
    }
}

//---------------------------------------------------------------------------



void __fastcall TCMForm1::sb_cm11Change(TObject * Sender)
{
    float tmp = sb_cm11->Position;
    st_CM11gain->Caption = FloatToStr(tmp) + "%";
    tmp /= 100;

    char buffer[5];
    sprintf(buffer, "%f", tmp * CM1[0][0]);
    CM1_11->Text = (AnsiString) buffer;

    if (rg_CM1_mode->ItemIndex == 1) {	//White Balance
	CM1_12->Text = 0;
	CM1_13->Text = 0;
    } else {			//normal
	double diff = CM1[0][0] - tmp * CM1[0][0];
	double d_ratio[2];
	CM_GainFunc(d_ratio, CM1[0][1], CM1[0][2]);

	sprintf(buffer, "%f", CM1[0][1] + diff * d_ratio[0]);
	CM1_12->Text = (AnsiString) buffer;

	sprintf(buffer, "%f", CM1[0][2] + diff * d_ratio[1]);
	CM1_13->Text = (AnsiString) buffer;
    }
    btn_CM1_WriteClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TCMForm1::sb_cm12Change(TObject * Sender)
{
    float tmp = sb_cm12->Position;
    st_CM12gain->Caption = FloatToStr(tmp) + "%";
    tmp /= 100;

    char buffer[5];
    sprintf(buffer, "%f", tmp * CM1[1][1]);
    CM1_22->Text = (AnsiString) buffer;

    if (rg_CM1_mode->ItemIndex == 1) {	//White Balance
	CM1_21->Text = 0;
	CM1_23->Text = 0;
    } else {			//normal
	double diff = CM1[1][1] - tmp * CM1[1][1];
	double d_ratio[2];
	CM_GainFunc(d_ratio, CM1[1][0], CM1[1][2]);

	sprintf(buffer, "%f", CM1[1][0] + diff * d_ratio[0]);
	CM1_21->Text = (AnsiString) buffer;

	sprintf(buffer, "%f", CM1[1][2] + diff * d_ratio[1]);
	CM1_23->Text = (AnsiString) buffer;
    }
    btn_CM1_WriteClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TCMForm1::sb_cm13Change(TObject * Sender)
{
    float tmp = sb_cm13->Position;
    st_CM13gain->Caption = FloatToStr(tmp) + "%";
    tmp /= 100;

    char buffer[5];
    sprintf(buffer, "%f", tmp * CM1[2][2]);
    CM1_33->Text = (AnsiString) buffer;

    if (rg_CM1_mode->ItemIndex == 1) {	//White Balance
	CM1_31->Text = 0;
	CM1_32->Text = 0;
    } else {			//normal
	double diff = CM1[2][2] - tmp * CM1[2][2];
	double d_ratio[2];
	CM_GainFunc(d_ratio, CM1[2][0], CM1[2][1]);

	sprintf(buffer, "%f", CM1[2][0] + diff * d_ratio[0]);
	CM1_31->Text = (AnsiString) buffer;

	sprintf(buffer, "%f", CM1[2][1] + diff * d_ratio[1]);
	CM1_32->Text = (AnsiString) buffer;
    }
    btn_CM1_WriteClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TCMForm1::sb_cm21Change(TObject * Sender)
{
    float tmp = sb_cm21->Position;
    st_CM21gain->Caption = FloatToStr(tmp) + "%";
    tmp /= 100;

    char buffer[5];
    sprintf(buffer, "%f", tmp * CM2[0][0]);
    CM2_11->Text = (AnsiString) buffer;

    if (rg_CM2_mode->ItemIndex == 1) {	//White Balance
	CM2_12->Text = 0;
	CM2_13->Text = 0;
    } else {			//normal
	double diff = CM2[0][0] - tmp * CM2[0][0];
	double d_ratio[2];
	CM_GainFunc(d_ratio, CM2[0][1], CM2[0][2]);

	sprintf(buffer, "%f", CM2[0][1] + diff * d_ratio[0]);
	CM2_12->Text = (AnsiString) buffer;

	sprintf(buffer, "%f", CM2[0][2] + diff * d_ratio[1]);
	CM2_13->Text = (AnsiString) buffer;
    }
    btn_CM2_WriteClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TCMForm1::sb_cm22Change(TObject * Sender)
{
    float tmp = sb_cm22->Position;
    st_CM22gain->Caption = FloatToStr(tmp) + "%";
    tmp /= 100;

    char buffer[5];
    sprintf(buffer, "%f", tmp * CM2[1][1]);
    CM2_22->Text = (AnsiString) buffer;

    if (rg_CM2_mode->ItemIndex == 1) {	//White Balance
	CM2_21->Text = 0;
	CM2_23->Text = 0;
    } else {			//normal
	double diff = CM2[1][1] - tmp * CM2[1][1];
	double d_ratio[2];
	CM_GainFunc(d_ratio, CM2[1][0], CM2[1][2]);

	sprintf(buffer, "%f", CM2[1][0] + diff * d_ratio[0]);
	CM2_21->Text = (AnsiString) buffer;

	sprintf(buffer, "%f", CM2[1][2] + diff * d_ratio[1]);
	CM2_23->Text = (AnsiString) buffer;
    }
    btn_CM2_WriteClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TCMForm1::sb_cm23Change(TObject * Sender)
{
    float tmp = sb_cm23->Position;
    st_CM23gain->Caption = FloatToStr(tmp) + "%";
    tmp /= 100;

    char buffer[5];
    sprintf(buffer, "%f", tmp * CM2[2][2]);
    CM2_33->Text = (AnsiString) buffer;

    if (rg_CM2_mode->ItemIndex == 1) {	//White Balance
	CM2_31->Text = 0;
	CM2_32->Text = 0;
    } else {			//normal
	double diff = CM2[2][2] - tmp * CM2[2][2];
	double d_ratio[2];
	CM_GainFunc(d_ratio, CM2[2][0], CM2[2][1]);

	sprintf(buffer, "%f", CM2[2][0] + diff * d_ratio[0]);
	CM2_31->Text = (AnsiString) buffer;

	sprintf(buffer, "%f", CM2[2][1] + diff * d_ratio[1]);
	CM2_32->Text = (AnsiString) buffer;
    }
    btn_CM2_WriteClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TCMForm1::sb_cm31Change(TObject * Sender)
{
    float tmp = sb_cm31->Position;
    st_CM31gain->Caption = FloatToStr(tmp) + "%";
    tmp /= 100;

    char buffer[5];
    sprintf(buffer, "%f", tmp * CM3[0][0]);
    CM3_11->Text = (AnsiString) buffer;

    if (rg_CM3_mode->ItemIndex == 1) {	//White Balance
	CM3_12->Text = 0;
	CM3_13->Text = 0;
    } else {			//normal
	double diff = CM3[0][0] - tmp * CM3[0][0];
	double d_ratio[2];
	CM_GainFunc(d_ratio, CM3[0][1], CM3[0][2]);

	sprintf(buffer, "%f", CM3[0][1] + diff * d_ratio[0]);
	CM3_12->Text = (AnsiString) buffer;

	sprintf(buffer, "%f", CM3[0][2] + diff * d_ratio[1]);
	CM3_13->Text = (AnsiString) buffer;
    }
    btn_CM3_WriteClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TCMForm1::sb_cm32Change(TObject * Sender)
{
    float tmp = sb_cm32->Position;
    st_CM32gain->Caption = FloatToStr(tmp) + "%";
    tmp /= 100;

    char buffer[5];
    sprintf(buffer, "%f", tmp * CM3[1][1]);
    CM3_22->Text = (AnsiString) buffer;

    if (rg_CM3_mode->ItemIndex == 1) {	//White Balance
	CM3_21->Text = 0;
	CM3_23->Text = 0;
    } else {			//normal
	double diff = CM3[1][1] - tmp * CM3[1][1];
	double d_ratio[2];
	CM_GainFunc(d_ratio, CM3[1][0], CM3[1][2]);

	sprintf(buffer, "%f", CM3[1][0] + diff * d_ratio[0]);
	CM3_21->Text = (AnsiString) buffer;

	sprintf(buffer, "%f", CM3[1][2] + diff * d_ratio[1]);
	CM3_23->Text = (AnsiString) buffer;
    }
    btn_CM3_WriteClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TCMForm1::sb_cm33Change(TObject * Sender)
{
    float tmp = sb_cm33->Position;
    st_CM33gain->Caption = FloatToStr(tmp) + "%";
    tmp /= 100;

    char buffer[5];
    sprintf(buffer, "%f", tmp * CM3[2][2]);
    CM3_33->Text = (AnsiString) buffer;

    if (rg_CM3_mode->ItemIndex == 1) {	//White Balance
	CM3_31->Text = 0;
	CM3_32->Text = 0;
    } else {			//normal
	double diff = CM3[2][2] - tmp * CM3[2][2];
	double d_ratio[2];
	CM_GainFunc(d_ratio, CM3[2][0], CM3[2][1]);

	sprintf(buffer, "%f", CM3[2][0] + diff * d_ratio[0]);
	CM3_31->Text = (AnsiString) buffer;

	sprintf(buffer, "%f", CM3[2][1] + diff * d_ratio[1]);
	CM3_32->Text = (AnsiString) buffer;
    }
    btn_CM3_WriteClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TCMForm1::rg_CM1_modeClick(TObject * Sender)
{
    selectMode(rg_CM1_mode->ItemIndex, CM1EditArray);
    CM1_keyPress(Sender, '0');	//refesh memory
}

//---------------------------------------------------------------------------

void TCMForm1::selectMode(int mode, TEdit * e[9])
{
    if (WhiteBalance == mode) {
	e[0]->Text = 1;
	e[1]->Text = 0;
	e[2]->Text = 0;

	e[3]->Text = 0;
	e[4]->Text = 1;
	e[5]->Text = 0;

	e[6]->Text = 0;
	e[7]->Text = 0;
	e[8]->Text = 1;
    } else if (Vivid == mode) {
	e[0]->Text = 1.04;
	e[1]->Text = -0.02;
	e[2]->Text = -0.02;

	e[3]->Text = -0.02;
	e[4]->Text = 1.04;
	e[5]->Text = -0.02;

	e[6]->Text = -0.02;
	e[7]->Text = -0.02;
	e[8]->Text = 1.04;
    }
}

void __fastcall TCMForm1::rg_CM2_modeClick(TObject * Sender)
{
    selectMode(rg_CM2_mode->ItemIndex, CM2EditArray);
    CM2_keyPress(Sender, '0');	//refesh memory
}

//---------------------------------------------------------------------------

void __fastcall TCMForm1::rg_CM3_modeClick(TObject * Sender)
{
    selectMode(rg_CM3_mode->ItemIndex, CM3EditArray);
    CM3_keyPress(Sender, '0');	//refesh memory
}

//---------------------------------------------------------------------------


void __fastcall TCMForm1::CM1_keyPress(TObject * Sender, char &Key)
{
    CM1[0][0] = StrToFloat(CM1_11->Text);
    CM1[0][1] = StrToFloat(CM1_12->Text);
    CM1[0][2] = StrToFloat(CM1_13->Text);

    CM1[1][0] = StrToFloat(CM1_21->Text);
    CM1[1][1] = StrToFloat(CM1_22->Text);
    CM1[1][2] = StrToFloat(CM1_23->Text);

    CM1[2][0] = StrToFloat(CM1_31->Text);
    CM1[2][1] = StrToFloat(CM1_32->Text);
    CM1[2][2] = StrToFloat(CM1_33->Text);

    sb_cm11->Position = 100;
    sb_cm12->Position = 100;
    sb_cm13->Position = 100;
}

//---------------------------------------------------------------------------

void __fastcall TCMForm1::CM2_keyPress(TObject * Sender, char &Key)
{
    CM2[0][0] = StrToFloat(CM2_11->Text);
    CM2[0][1] = StrToFloat(CM2_12->Text);
    CM2[0][2] = StrToFloat(CM2_13->Text);

    CM2[1][0] = StrToFloat(CM2_21->Text);
    CM2[1][1] = StrToFloat(CM2_22->Text);
    CM2[1][2] = StrToFloat(CM2_23->Text);

    CM2[2][0] = StrToFloat(CM2_31->Text);
    CM2[2][1] = StrToFloat(CM2_32->Text);
    CM2[2][2] = StrToFloat(CM2_33->Text);

    sb_cm21->Position = 100;
    sb_cm22->Position = 100;
    sb_cm23->Position = 100;
}

//---------------------------------------------------------------------------
void __fastcall TCMForm1::CM3_keyPress(TObject * Sender, char &Key)
{
    CM3[0][0] = StrToFloat(CM3_11->Text);
    CM3[0][1] = StrToFloat(CM3_12->Text);
    CM3[0][2] = StrToFloat(CM3_13->Text);

    CM3[1][0] = StrToFloat(CM3_21->Text);
    CM3[1][1] = StrToFloat(CM3_22->Text);
    CM3[1][2] = StrToFloat(CM3_23->Text);

    CM3[2][0] = StrToFloat(CM3_31->Text);
    CM3[2][1] = StrToFloat(CM3_32->Text);
    CM3[2][2] = StrToFloat(CM3_33->Text);

    sb_cm31->Position = 100;
    sb_cm32->Position = 100;
    sb_cm33->Position = 100;
}

//---------------------------------------------------------------------------
void __fastcall TCMForm1::sb_ofs1Change(TObject * Sender)
{
    scrollBarOffsetChange(0, cb_CM1_W255->Checked, CM1EditArray, sb_ofs1, st_ofs1);
}

int TCMForm1::getBaseNumber(OffsetType offsetType)
{
    switch (offsetType) {
    case _128:
	return 4;
    case _64:
	return 8;
    case _257:
	return 2;
    case _511:			//-511~511
	return 1;
    default:
	return -1;
    };
}
float TCMForm1::parsePosition(float originalPosition)
{
    float s = (float) originalPosition - 512;
    s /= getBaseNumber(offsetType);
    return s;
};

void TCMForm1::writeOffset(TLUT offsetAddress, int position)
{
    int ofs[3];
    ofs[0] = FloatToMemOfsForm(position);
    ofs[1] = ofs[0];
    ofs[2] = ofs[0];

    int_vector_ptr values = AbstractBase::getValuesFromFile("TCON_12307");
    bool isTCON12307 = (null != values) ? (*values)[0] == 1 : false;

    if (isTCON12307 && 5 == offsetAddress.Type()) {
	//如果是12307,offset要用register的方式不能用lut的方式寫
	//因為兩個lut會互相cover到, 會無法順利寫入
	int address = offsetAddress.Addr();
	TBit2 tBitR(address, address + 1, 10, 4, "");
	TBit2 tBitG(address, address + 2, 10, 0, "");
	TBit2 tBitB(address + 3, address + 4, 10, 4, "");
	int_array rValues = tBitR.getValues(ofs[0]);
	int_array gValues = tBitG.getValues(ofs[0]);
	int_array bValues = tBitB.getValues(ofs[0]);

	EngineerForm->SetWrite_Byte(tBitR.Byte1, rValues[0]);
	EngineerForm->SetWrite_Byte(tBitR.Byte2, rValues[1]);
	EngineerForm->SetWrite_Byte(tBitG.Byte1, gValues[0]);
	EngineerForm->SetWrite_Byte(tBitG.Byte2, gValues[1]);
	EngineerForm->SetWrite_Byte(tBitB.Byte1, bValues[0]);
	EngineerForm->SetWrite_Byte(tBitB.Byte2, bValues[1]);
    } else {
	EngineerForm->SetWrite_PG(offsetAddress, ofs, CM_IsChkSum);
    }
};

//---------------------------------------------------------------------------
void TCMForm1::scrollBarOffsetChange(int index, bool w255Fix, TEdit * e[9],
				     TScrollBar * scroll, TStaticText * text)
{

    float s = parsePosition(scroll->Position);

    char buf[6];
    sprintf(buf, "%3.2f", s);
    text->Caption = (AnsiString) buf;

    writeOffset(ofs_addr[index], scroll->Position);

    if (true == w255Fix) {

	double CM12 = StrToFloat(e[1]->Text);	//1,2
	double CM13 = StrToFloat(e[2]->Text);
	double CM11 = (255 - ((CM12 + CM13) * 255 + s)) / 255;
	e[0]->Text = FloatToStr(CM11);

	double CM21 = StrToFloat(e[3]->Text);	//3,4
	double CM23 = StrToFloat(e[5]->Text);
	double CM22 = (255 - ((CM21 + CM23) * 255 + s)) / 255;
	e[4]->Text = FloatToStr(CM22);

	double CM31 = StrToFloat(e[6]->Text);	//5,6
	double CM32 = StrToFloat(e[7]->Text);
	double CM33 = (255 - ((CM31 + CM32) * 255 + s)) / 255;
	e[8]->Text = FloatToStr(CM33);

	int CM[9];
	CM[0] = FloatToMemForm(CM11 * 256);
	CM[1] = FloatToMemForm(CM12 * 256);
	CM[2] = FloatToMemForm(CM13 * 256);

	CM[3] = FloatToMemForm(CM21 * 256);
	CM[4] = FloatToMemForm(CM22 * 256);
	CM[5] = FloatToMemForm(CM23 * 256);

	CM[6] = FloatToMemForm(CM31 * 256);
	CM[7] = FloatToMemForm(CM32 * 256);
	CM[8] = FloatToMemForm(CM33 * 256);

	EngineerForm->SetWrite_PG(CM_addr[index], CM, CM_IsChkSum);
    }
}

void __fastcall TCMForm1::sb_ofs2Change(TObject * Sender)
{

    scrollBarOffsetChange(1, cb_CM2_W255->Checked, CM2EditArray, sb_ofs2, st_ofs2);

}

//---------------------------------------------------------------------------

void __fastcall TCMForm1::sb_ofs3Change(TObject * Sender)
{
    scrollBarOffsetChange(2, cb_CM3_W255->Checked, CM3EditArray, sb_ofs3, st_ofs3);
}

//---------------------------------------------------------------------------

void __fastcall TCMForm1::TS_CMChange(TObject * Sender)
{
    CMCboB[0]->Cbob->ItemIndex = TS_CM->TabIndex + 1;
    //將CM select值寫入硬體
    int set_val = (CMCboB[0]->Cbob->ItemIndex);
    EngineerForm->SetWrite_Byte(CMCboB[0]->Addr, set_val);
}

//---------------------------------------------------------------------------

void __fastcall TCMForm1::bn_CM1SaveClick(TObject * Sender)
{
    if (!SaveDialog1->Execute())
	return;
    String Fpath = SaveDialog1->FileName /*+".txt" */ ;
    storeCMToFile(Fpath, CM1EditArray, st_ofs1);
}

//---------------------------------------------------------------------------

void __fastcall TCMForm1::bn_CM2SaveClick(TObject * Sender)
{
    if (!SaveDialog1->Execute())
	return;
    String Fpath = SaveDialog1->FileName;
    storeCMToFile(Fpath, CM2EditArray, st_ofs2);
}

//---------------------------------------------------------------------------

void __fastcall TCMForm1::bn_CM3SaveClick(TObject * Sender)
{
    if (!SaveDialog1->Execute())
	return;
    String Fpath = SaveDialog1->FileName;
    storeCMToFile(Fpath, CM3EditArray, st_ofs3);

}

void TCMForm1::storeCMToFile(String filename, TEdit * e[9], TStaticText * offset)
{
    FILE *fptr = fopen(filename.c_str(), "w");
    fprintf(fptr, "CM\n");
    float CM[9];
    CM[0] = StrToFloat(e[0]->Text);
    CM[1] = StrToFloat(e[1]->Text);
    CM[2] = StrToFloat(e[2]->Text);

    CM[3] = StrToFloat(e[3]->Text);
    CM[4] = StrToFloat(e[4]->Text);
    CM[5] = StrToFloat(e[5]->Text);

    CM[6] = StrToFloat(e[6]->Text);
    CM[7] = StrToFloat(e[7]->Text);
    CM[8] = StrToFloat(e[8]->Text);
    for (int i = 0; i < 3; i++) {
	fprintf(fptr, "%f\t%f\t%f\n", CM[0 + i * 3], CM[1 + i * 3], CM[2 + i * 3]);
    }
    float CMofs;
    CMofs = StrToFloat(offset->Caption);
    fprintf(fptr, "%f\n", CMofs);
    fclose(fptr);
};


//-----------------------------------------------------------------------

void TCMForm1::loadCMFromFile(String filename, OffsetType offsetType,
			      float CM[3][3], TEdit * e[9],
			      TScrollBar * gain[3], TScrollBar * offset)
{
    char *buffer = Load_File(filename);

    char *pch;
    pch = strtok(buffer, "\n\t");
    String tmp;
    if ((AnsiString) pch != "CM") {
	while (pch != "CM") {
	    if (pch == NULL) {
		return;		//資料中沒有cm
	    }
	    pch = strtok(NULL, "\n\t");
	}
    }
    // Load CM
    int c = 0;
    pch = strtok(NULL, "\n\t");
    while (c < 9 && pch != NULL) {
	if (pch == NULL) {
	    return;		//資料中的data缺少
	}
	CM[c / 3][c % 3] = StrToFloat((AnsiString) pch);
	pch = strtok(NULL, "\n\t");
	c++;
    }

    // Load CM offset
    float CMofs;
    if (pch == NULL) {
	return;			//資料中的data缺少
    }
    CMofs = StrToFloat((AnsiString) pch);

    // Set to CM Interface

    // CM1
    char cm_buf[5];
    sprintf(cm_buf, "%f", CM[0][0]);
    e[0]->Text = (AnsiString) cm_buf;
    sprintf(cm_buf, "%f", CM[0][1]);
    e[1]->Text = (AnsiString) cm_buf;
    sprintf(cm_buf, "%f", CM[0][2]);
    e[2]->Text = (AnsiString) cm_buf;
    // CM2
    sprintf(cm_buf, "%f", CM[1][0]);
    e[3]->Text = (AnsiString) cm_buf;
    sprintf(cm_buf, "%f", CM[1][1]);
    e[4]->Text = (AnsiString) cm_buf;
    sprintf(cm_buf, "%f", CM[1][2]);
    e[5]->Text = (AnsiString) cm_buf;
    // CM3
    sprintf(cm_buf, "%f", CM[2][0]);
    e[6]->Text = (AnsiString) cm_buf;
    sprintf(cm_buf, "%f", CM[2][1]);
    e[7]->Text = (AnsiString) cm_buf;
    sprintf(cm_buf, "%f", CM[2][2]);
    e[8]->Text = (AnsiString) cm_buf;

    // Reset CM gain ScrollBar
    gain[0]->Position = 100;
    gain[1]->Position = 100;
    gain[2]->Position = 100;

    // Set to CM offset Interface
    int CMofs_power = getBaseNumber(offsetType);
    offset->Position = CMofs * CMofs_power + 512;
    delete[]buffer;
}


//------------------------------------------------------------------------
void __fastcall TCMForm1::bn_CM1LoadClick(TObject * Sender)
{
    if (!OpenDialog1->Execute()) {
	return;
    }
    String Fpath = OpenDialog1->FileName;

    TScrollBar *gainArray[3] = { sb_cm11, sb_cm12, sb_cm13 };
    loadCMFromFile(Fpath, offsetType, CM1, CM1EditArray, gainArray, sb_ofs1);

    btn_CM1_WriteClick(Sender);
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TCMForm1::bn_CM2LoadClick(TObject * Sender)
{
    if (!OpenDialog1->Execute()) {
	return;
    }
    String Fpath = OpenDialog1->FileName;

    TScrollBar *gainArray[3] = { sb_cm21, sb_cm22, sb_cm23 };
    loadCMFromFile(Fpath, offsetType, CM2, CM2EditArray, gainArray, sb_ofs2);

    btn_CM2_WriteClick(Sender);
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
void __fastcall TCMForm1::bn_CM3LoadClick(TObject * Sender)
{
    if (!OpenDialog1->Execute()) {
	return;
    }
    String Fpath = OpenDialog1->FileName;

    TScrollBar *gainArray[3] = { sb_cm31, sb_cm32, sb_cm33 };
    loadCMFromFile(Fpath, offsetType, CM3, CM3EditArray, gainArray, sb_ofs3);

    btn_CM3_WriteClick(Sender);
}

//---------------------------------------------------------------------------



void __fastcall TCMForm1::FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift)
{
    if (Key == 0x40)
	Btn_CM_reloadClick(Sender);
}

//---------------------------------------------------------------------------



void __fastcall TCMForm1::FormClose(TObject * Sender, TCloseAction & Action)
{
    delete[]cm_cb;
    delete[]CMChkB;
    delete[]cm_cbo;
    delete[]CMCboB;
    delete[]CM_addr;
    delete[]ofs_addr;
    delete[]OCM;
}

//---------------------------------------------------------------------------

