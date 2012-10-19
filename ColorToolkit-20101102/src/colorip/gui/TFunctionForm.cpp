//---------------------------------------------------------------------------

#include <vcl.h>
#include <lib/CMSCpp2.1/src/includeall.h>
#pragma hdrstop

#include "TMainForm.h"
#include "TFunctionForm.h"
#include "include.h"
#include  <colorip/11307/Func_11307.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFunctionForm *FunctionForm;
bool TFunctionForm::DG_IsChkSum = (1 == AbstractIPBase::getValueFromFile("DG_HAS_CHECK_SUM"));
//---------------------------------------------------------------------------
__fastcall TFunctionForm::TFunctionForm(TComponent * Owner)
:TForm(Owner)
{
    Func_Chg = 0;
    DGEN_idx = -1;
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm::FormClose(TObject * Sender, TCloseAction & Action)
{
    delete[]OFunc;

    // FRC DG
    delete[]FrcDg_cb;
    delete[]FrcDgChkB;
    delete[]FrcDg_cbo;
    delete[]FrcDgCboB;
    delete[]FrcDg_lble;
    delete[]FrcDgLblE;

    delete[]Addr_DgLUT;

    if (null != manualBasedDGLUT) {
	deleteDGLUT(manualBasedDGLUT);
    }
    if (null != gainDGLUT) {
	deleteDGLUT(gainDGLUT);
    }


    Action = caFree;
    //MainForm->FunctionFormNULL();


}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm::FrcDg_CheckBox_Click(TObject * Sender)
{
    if (Func_Chg == 0)
	return;
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (FrcDgChkB[idx]->Chkb->Checked ? 1 : 0);
    EngineerForm->SetWrite_Byte(FrcDgChkB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm::FrcDg_ComboBox_Click(TObject * Sender)
{
    if (Func_Chg == 0)
	return;
    TComboBox *c = (TComboBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (FrcDgCboB[idx]->Cbob->ItemIndex);
    EngineerForm->SetWrite_Byte(FrcDgCboB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm::FrcDg_LblEdit_KeyPress(TObject * Sender, char &Key)
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
void TFunctionForm::Initial_DG_table()
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

void __fastcall TFunctionForm::FormCreate(TObject * Sender)
{

    OFunc = new Func_11307;

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
    for (int i = 0; i < OFunc->FrcDgChkBox_Nbr; i++) {
	FrcDgChkB[i] = new _CHKB;
    }

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
	if (FrcDgChkB[i]->Addr.Name() == OFunc->DG_EN_Name()) {	// 20100608 find DG enable index
	    DGEN_idx = i;
	}
    }
    if (DGEN_idx == -1)		// 20100608 Check DG enable index
	ShowMessage("Can't Get DG enable index.");

    //ComboBox
    FrcDg_cbo = OFunc->SetFrcDgCboBx();
    FrcDgCboB = new _CBOB *[OFunc->FrcDgCboBox_Nbr];
    for (int i = 0; i < OFunc->FrcDgCboBox_Nbr; i++) {
	FrcDgCboB[i] = new _CBOB;
    }


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
	if (FrcDgCboB[i]->Addr.FuncEn()) {
	    for (int j = 0; j < FrcDgCboB[i]->Addr.choice_nbr; j++) {	//ComboBox choice
		FrcDgCboB[i]->Cbob->Items->Add(FrcDgCboB[i]->Addr.choice[j]);
	    }
	}
    }
    //LabeledEdit
    FrcDg_lble = OFunc->SetFrcDgLblE();
    FrcDgLblE = new _LBLE *[OFunc->FrcDgLblE_Nbr];
    for (int i = 0; i < OFunc->FrcDgLblE_Nbr; i++) {
	FrcDgLblE[i] = new _LBLE;
    }

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
bool TFunctionForm::DG_LUT_RW_start()
{
    if (DGEN_idx == -1) {
	ShowMessage("Unknown DG enabled index.");
	return 0;
    }
    if (CheckBox_FuncOn->Checked) {
	return true;
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
void TFunctionForm::DG_LUT_RW_over()
{
    if (CheckBox_FuncOn->Checked) {
	return;
    }
    // reload en state
    int set_val = (DG_EN_State == false ? 0 : 1);
    FrcDgChkB[DGEN_idx]->Chkb->Checked = DG_EN_State;
    EngineerForm->SetWrite_Byte(FrcDgChkB[DGEN_idx]->Addr, set_val);
}

// 20100608 DG table operation enable/disable
void TFunctionForm::DG_LUT_FuncEnable(bool en_flag)
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
int **TFunctionForm::getDGLUTFromUI()
{
    int **lut = new int *[OFunc->DGLUT_Nbr];
    for (int i = 0; i < OFunc->DGLUT_Nbr; i++) {
	int lutnum = Addr_DgLUT[i].LutNum();
	lut[i] = new int[lutnum];
	for (int j = 0; j < lutnum; j++) {
	    //從UI撈回資料
	    lut[i][j] = StrToInt(sg_dg->Cells[i + 1][j + 1]);
	}
    }
    return lut;
}

void TFunctionForm::setDGLUTToUI(int **dgLUT)
{
    for (int i = 0; i < OFunc->DGLUT_Nbr; i++) {
	int lutnum = Addr_DgLUT[i].LutNum();
	for (int j = 0; j < lutnum; j++) {	//To GUI
	    sg_dg->Cells[i + 1][j + 1] = IntToStr(dgLUT[i][j]);
	}
    }
}

// DG table write
// 20100608 add enable record and revise EngineerForm->SetWrite_DG(...)
void __fastcall TFunctionForm::btn_dg_wrtClick(TObject * Sender)
{
    DG_LUT_FuncEnable(0);	// Table operation button disable
    bool ok = DG_LUT_RW_start();	// Record the state of DG enable
    if (ok == 0) {		// Fail to record the state
	DG_LUT_FuncEnable(1);	// Table operation button enable
	return;
    }

    /*int **lut = new int *[OFunc->DGLUT_Nbr];

       for (int i = 0; i < OFunc->DGLUT_Nbr; i++) {
       lut[i] = new int[Addr_DgLUT[i].LutNum()];
       for (int j = 0; j < Addr_DgLUT[i].LutNum(); j++) {
       //從UI撈回資料
       lut[i][j] = StrToInt(sg_dg->Cells[i + 1][j + 1]);
       }
       } */
    int **lut = getDGLUTFromUI();

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
void __fastcall TFunctionForm::btn_dg_readClick(TObject * Sender)
{
    DG_LUT_FuncEnable(0);	// Table operation button disable
    bool ok = DG_LUT_RW_start();	// Record the state of DG enable
    if (ok == 0) {		// Fail to record the state
	DG_LUT_FuncEnable(1);	// Table operation button enable
	return;
    }

    int **DG_table = getEmptyDGLUT();
    EngineerForm->SetRead_DG(Addr_DgLUT, DG_table, OFunc->DGLUT_Nbr, DG_IsChkSum);

    setDGLUTToUI(DG_table);
    /*for (int i = 0; i < OFunc->DGLUT_Nbr; i++) {
       for (int j = 0; j < Addr_DgLUT[i].LutNum(); j++) {       //To GUI
       sg_dg->Cells[i + 1][j + 1] = IntToStr(DG_table[i][j]);
       }
       } */
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
void __fastcall TFunctionForm::btn_dg_loadClick(TObject * Sender)
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
void __fastcall TFunctionForm::btn_dg_saveClick(TObject * Sender)
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

void __fastcall TFunctionForm::Btn_FRC_DG_reloadClick(TObject * Sender)
{
    Btn_FRC_DG_reload->Enabled = false;
    DG_LUT_FuncEnable(0);
    Func_Chg = 0;
    unsigned char read_val;
    for (int i = 0; i < OFunc->FrcDgChkBox_Nbr; i++) {
	if (FrcDgChkB[i]->Chkb->Visible == true) {
	    EngineerForm->SetRead_Byte(FrcDgChkB[i]->Addr, &read_val);
	    if (read_val == 1) {
		FrcDgChkB[i]->Chkb->Checked = 1;
	    } else if (read_val == 0) {
		FrcDgChkB[i]->Chkb->Checked = 0;
	    } else {
		ShowMessage("FRC/DG CheckBox read error:" + IntToStr(read_val));
	    }
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

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TFunctionForm::FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift)
{
    if (Key == 0x40) {
	Btn_FRC_DG_reloadClick(Sender);
    }
}

//---------------------------------------------------------------------------

void __fastcall TFunctionForm::CheckBox_ManualEnableClick(TObject * Sender)
{
    bool checked = CheckBox_ManualEnable->Checked;
    GroupBox_ManualAdjust->Enabled = checked;
    if (checked) {
	if (NULL != manualBasedDGLUT) {
	    delete[]manualBasedDGLUT;
	}
	manualBasedDGLUT = getDGLUTFromUI();
    }
}

//---------------------------------------------------------------------------
void TFunctionForm::adjustNumberOfEdit(TEdit * edit, bool add)
{
    int v = edit->Text.ToInt();
    v = add ? v + 1 : v - 1;
    v = (v > 255) ? 255 : v;
    v = (v < 0) ? 0 : v;
    edit->Text = v;

    int **dglut =
	generateGainDGLUT(Edit_R->Text.ToInt(), Edit_G->Text.ToInt(), Edit_B->Text.ToInt());
    setDGLUTToUI(dglut);
    btn_dg_wrtClick(this);
}

int **TFunctionForm::getEmptyDGLUT()
{
    //int read_len = Addr_DgLUT[0].Addr();

    int **DG_table = new int *[OFunc->DGLUT_Nbr];
    for (int i = 0; i < OFunc->DGLUT_Nbr; i++) {
	int lutnum = Addr_DgLUT[i].LutNum();
	DG_table[i] = new int[lutnum];
    }
    //int (*a)[read_len] = new int[OFunc->DGLUT_Nbr][read_len];
    return DG_table;
};

void TFunctionForm::deleteDGLUT(int **dgLUT)
{

    for (int i = 0; i < OFunc->DGLUT_Nbr; i++) {
	delete[]dgLUT[i];
    }
    delete[]dgLUT;
}

int **TFunctionForm::generateGainDGLUT(int maxR, int maxG, int maxB)
{
    if (null == manualBasedDGLUT) {
	manualBasedDGLUT = getDGLUTFromUI();
    }
    if (null == gainDGLUT) {
	gainDGLUT = getEmptyDGLUT();
    }
    double rGain = ((double) manualBasedDGLUT[0][maxR]) / manualBasedDGLUT[0][255];
    double gGain = ((double) manualBasedDGLUT[1][maxG]) / manualBasedDGLUT[1][255];
    double bGain = ((double) manualBasedDGLUT[2][maxB]) / manualBasedDGLUT[2][255];
    int h = OFunc->DGLUT_Nbr;	//3
    //int w = Addr_DgLUT[0].Addr();     //n~
    int w = Addr_DgLUT[0].LutNum();	//n~

    for (int x = 0; x < w; x++) {
	gainDGLUT[0][x] = (int) (manualBasedDGLUT[0][x] * rGain);
    }
    for (int x = 0; x < w; x++) {
	gainDGLUT[1][x] = (int) (manualBasedDGLUT[1][x] * gGain);
    }
    for (int x = 0; x < w; x++) {
	gainDGLUT[2][x] = (int) (manualBasedDGLUT[2][x] * bGain);
    }
    //for(int x=0;x<


    return gainDGLUT;
}

void __fastcall TFunctionForm::Button_RAddClick(TObject * Sender)
{
    adjustNumberOfEdit(Edit_R, true);
}

//---------------------------------------------------------------------------

void __fastcall TFunctionForm::Button_RMinusClick(TObject * Sender)
{
    adjustNumberOfEdit(Edit_R, false);
}

//---------------------------------------------------------------------------

void __fastcall TFunctionForm::Button_GAddClick(TObject * Sender)
{
    adjustNumberOfEdit(Edit_G, true);
}

//---------------------------------------------------------------------------

void __fastcall TFunctionForm::Button_GMinusClick(TObject * Sender)
{
    adjustNumberOfEdit(Edit_G, false);
}

//---------------------------------------------------------------------------

void __fastcall TFunctionForm::Button_BAddClick(TObject * Sender)
{
    adjustNumberOfEdit(Edit_B, true);
}

//---------------------------------------------------------------------------

void __fastcall TFunctionForm::Button_BMinusClick(TObject * Sender)
{
    adjustNumberOfEdit(Edit_B, false);
}

//---------------------------------------------------------------------------

