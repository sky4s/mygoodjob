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

//C�t�Τ��

//C++�t�Τ��

//vcl�w�Y���

//��L�w�Y���
#include "include.h"
//�����ؤ��Y���

//�����ؤ�gui�Y���
#include "THSVForm2nd.h"
#include "CM1.h"
#include "TGamutForm.h"
#include <fpga/11307/ImageProcess/ImgProc_11307.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TColorPickerFrame"
#pragma link "THSVAdjustFrame"
#pragma link "TColorPickerFrame"
#pragma link "THSVAdjustFrame"
#pragma link "TColorPickerFrame"
#pragma link "THSVAdjustFrame"
#pragma resource "*.dfm"


//const double THSVForm2nd::WHOLE_HUE_ANGLE = 360;
//---------------------------------------------------------------------------
__fastcall THSVForm2nd::THSVForm2nd(TComponent * Owner):TForm(Owner),
HSV_IsChkSum(true), tbl_step(WHOLE_HUE_ANGLE / HUE_COUNT),
lastStringGridSelectRow(-1), settingScrollBarPosition(false),
cursorRGBValues(new int[3]), patternMode(PatternMode::Single),
selectedRGBValues(new int[3]), customPattern(false), patternValue(192), isInversePattern(false)
{
    HSV_Chg = 0;
    HSVEN_idx = -1;
    hsvListener = bptr < HSVChangeListener > (new HSVChangeListener(this));
    hsvAdjust->addChangeListener(hsvListener);
    hsvAdjust->setMaxHueValue(MAX_HUE_VALUE);

    captionIFListener = bptr < CaptionIFListener > (new CaptionIFListener());
    hsvAdjust->setCaptionIF(captionIFListener);
    hsvAdjust->updateHSVCaption();

    mouseListener = bptr < MousePressedListener > (new MousePressedListener(this));
    colorPicker->addMouseListener(mouseListener);

    tpColorThread = bptr < TPColorThread1 > (new TPColorThread1(true, this));

    PatternForm->setPatternCallbackIF(this);
    ScrollBar_TurnPointChange(null);
}

//---------------------------------------------------------------------------
void __fastcall THSVForm2nd::CheckBox_Click(TObject * Sender)
{
    if (HSV_Chg == 0)
	return;
    TCheckBox *c = (TCheckBox *) Sender;
    int idx = StrToInt(c->Hint);
    int set_val = (ChkB[idx]->Chkb->Checked ? 1 : 0);
    EngineerForm->SetWrite_Byte(ChkB[idx]->Addr, set_val);
}

//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::FormCreate(TObject * Sender)
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
	if (ChkB[i]->Addr.Name() == OHSV->HSV_EN_Name()) {	// 20100608 Find HSV enable index
	    HSVEN_idx = i;
	}
    }
    // 20100608 check HSV enable index
    if (HSVEN_idx == -1) {
	ShowMessage("Can't Get HSV enable index.");
    }
    Initial_HSV_table();	// initial HSV table
    HSV_Chg = 1;

    this->initStringGrid_HSV();
    colorPicker->setTInTargetForm(InTargetForm);
    tpColorThread->Resume();
    RadioButton_deg60baseClick(RadioButton_deg0);
}


double THSVForm2nd::getSaturation()
{
    int index = RadioGroup_Saturation->ItemIndex;
    switch (index) {
    case 0:
	return .25;
    case 1:
	return .5;
    case 2:
	return .75;
    case 3:
	return 1;
    }
}

int THSVForm2nd::getValue()
{
    int index = RadioGroup_Value->ItemIndex;
    switch (index) {
    case 0:
	return 64;
    case 1:
	return 128;
    case 2:
	return 192;
    case 3:
	return 255;
    }
}

void THSVForm2nd::initGroupBoxBase(TGroupBox * groupBox_base)
{
    int count = groupBox_base->ControlCount;
    TColor fontColor = getValue() < 170 ? clWhite : clBlack;
    for (int x = 0; x < count; x++) {
	TRadioButton *b = dynamic_cast < TRadioButton * >(groupBox_base->Controls[x]);
	if (null != b) {
	    int row = hintToRow(b->Hint.ToInt()) - 1;
	    RGB_ptr rgb = getHueRGB(row);
	    b->Color = rgb->getColor();
	    b->Font->Color = fontColor;
	}
    }
}

//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::FormClose(TObject * Sender, TCloseAction & Action)
{
    delete[]OHSV;
    delete[]cb;
    delete[]ChkB;
    delete[]lut_addr;

    Action = caFree;
    tpColorThread->Terminate();
    MainForm->HSVFormNULL();
}

//---------------------------------------------------------------------------

void THSVForm2nd::Initial_HSV_table()
{
    //initial table setting
    for (int i = 0; i < HUE_COUNT; i++) {
	hueTableTemp[i] = hueTable[i] = ((double) i) * MAX_HUE_VALUE / HUE_COUNT;
	satTableTemp[i] = satTable[i] = 64;
	valTableTemp[i] = valTable[i] = 0;
    }

    //hsvAdjust->setHSVPostition(0, 32, 0);
    hsvAdjust->setDefaultHSVPosition(0, 64, 0);
}


//---------------------------------------------------------------------------

void THSVForm2nd::Reset_HSVshow()
{				// Set gain value relative to color choose
    int tbl_idx = getGridSelectRow();

    //Hue gain
    String hueStr = stringGrid_HSV->Cells[1][tbl_idx];
    String saturationStr = stringGrid_HSV->Cells[2][tbl_idx];
    String valueStr = stringGrid_HSV->Cells[3][tbl_idx];
    //hsvAdjust->setHSVPostition(hueStr.ToInt(),
    //                         (int) floor(saturationStr.ToDouble() * 32), valueStr.ToInt());
    hsvAdjust->setHSVPostition(hueStr.ToInt(), saturationStr.ToInt() + 64, valueStr.ToInt());
}

//---------------------------------------------------------------------------
void __fastcall THSVForm2nd::cb_Hue_RedClick(TObject * Sender)
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

void __fastcall THSVForm2nd::cb_Hue_YellowClick(TObject * Sender)
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

void __fastcall THSVForm2nd::cb_Hue_GreenClick(TObject * Sender)
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

void __fastcall THSVForm2nd::cb_Hue_BlueClick(TObject * Sender)
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

void __fastcall THSVForm2nd::cb_Hue_CyanClick(TObject * Sender)
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

void __fastcall THSVForm2nd::cb_Hue_MagClick(TObject * Sender)
{				// 6 Color Adjust : Magenta
    if (cb_Hue_Mag->Checked == true) {
	cb_Hue_Red->Checked = false;
	cb_Hue_Green->Checked = false;
	cb_Hue_Blue->Checked = false;
	cb_Hue_Cyan->Checked = false;
	cb_Hue_Yellow->Checked = false;
	//le_ChAangle->Text = 300;      //���ʪ����׬�300
	ed_Hue_Custom->Text = 300;
    }
}



//---------------------------------------------------------------------------
bool THSVForm2nd::isFPGA()
{
    int_vector_ptr values = AbstractBase::getValuesFromFile("FPGA");
    if (null != values) {
	int result = (*values)[0];
	return 1 == result;
    } else {
	return false;
    }
}

void THSVForm2nd::Hue_LUTWrite()
{
    HSV_LUT_FuncEnable(0);	// Table operation button disable
    bool ok = HSV_LUT_RW_start();	// Record the state of HSV enable
    if (ok == 0) {		// Fail to record the state
	HSV_LUT_FuncEnable(1);	// Table operation button enable
	return;
    }

    for (int i = 0; i < HUE_COUNT; i++) {
	hueTable[i] =
	    (int) (StrToFloat(stringGrid_HSV->Cells[1][i + 1]) / WHOLE_HUE_ANGLE *
		   MAX_HUE_VALUE + 0.5);
	satTable[i] = StrToInt(stringGrid_HSV->Cells[2][i + 1]);
	valTable[i] = StrToInt(stringGrid_HSV->Cells[3][i + 1]);
    }

    bool fpga = isFPGA();
    int *HSV_lut = new int[HUE_COUNT * 3];
    int val_w;
    for (int i = 0; i < HUE_COUNT; i++) {
	hueTable[i] = hueTable[i] % 1024;	// 10 bit
	satTable[i] = satTable[i] % 128;	// 7 bit
	val_w = SignToCmplmnt2s(valTable[i], 128);
	val_w = val_w % 128;	// 7 bit

	if (fpga) {
	    //fpga
	    HSV_lut[i * 3] = hueTable[i] / 4;
	    HSV_lut[i * 3 + 1] = hueTable[i] % 4 * 64 + satTable[i] / 2;
	    HSV_lut[i * 3 + 2] = satTable[i] % 2 * 128 + val_w;
	} else {
	    //11307
	    HSV_lut[i * 3 + 2] = hueTable[i] / 4;
	    HSV_lut[i * 3 + 1] = hueTable[i] % 4 * 64 + satTable[i] / 2;
	    HSV_lut[i * 3] = satTable[i] % 2 * 128 + val_w;
	}

    }
    EngineerForm->SetWrite_PG(lut_addr[0], HSV_lut, HSV_IsChkSum);
    delete[]HSV_lut;

    HSV_LUT_RW_over();		// Recover HSV enable
    HSV_LUT_FuncEnable(1);	// Table operation button enable
}


//--------------------------------------------------------------------------

void __fastcall THSVForm2nd::btn_resetClick(TObject * Sender)
{
    Initial_HSV_table();
    initStringGrid_HSV();
}




//---------------------------------------------------------------------------


void __fastcall THSVForm2nd::btn_hsv_loadClick(TObject * Sender)
{
    if (!OpenDialog1->Execute())
	return;
    String Fpath;
    Fpath = OpenDialog1->FileName;

    Load_HSV(Fpath);
}

//---------------------------------------------------------------------------

bool THSVForm2nd::Load_HSV(String Fpath)
{
    if (Fpath == NULL)
	return 0;
    char *buffer = Load_File(Fpath);
    if (buffer == NULL)
	return 0;
    for (int i = 0; i < HUE_COUNT; i++) {
	hueTable[i] = -1;
	satTable[i] = -1;
	valTable[i] = 0;
    }



    //���X�ɮפ����ƭ�
    int c = 0;
    char *pch;
    pch = strtok(buffer, "\n\t");
    int Length = lut_addr[0].LutNum();
    while (c < Length && pch != NULL) {
	if (pch == NULL) {
	    ShowMessage("Can't open Hue table file.");
	    return 0;		//��Ƥ���data�ʤ�
	}
	int index = c / 3;
	if (c % 3 == 0) {
	    hueTable[index] = hueTableTemp[index] = StrToInt((AnsiString) pch);
	} else if (c % 3 == 1) {
	    satTable[index] = satTableTemp[index] = StrToInt((AnsiString) pch);
	} else {
	    valTable[index] = valTableTemp[index] = StrToInt((AnsiString) pch);
	}
	pch = strtok(NULL, "\n\t");
	c++;
    }
    delete[]buffer;

    for (int i = 0; i < HUE_COUNT; i++) {
	stringGrid_HSV->Cells[1][i + 1] = ((double) hueTable[i]) / MAX_HUE_VALUE * WHOLE_HUE_ANGLE;
	stringGrid_HSV->Cells[2][i + 1] = satTable[i];
	stringGrid_HSV->Cells[3][i + 1] = valTable[i];
    }

    stringGrid_HSVSelectCell(this, 0, lastStringGridSelectRow, false);

    //Hue_LUTWrite();
    return 1;
}


//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::btn_hsv_saveClick(TObject * Sender)
{
    if (!SaveDialog1->Execute())
	return;
    String Fpath = SaveDialog1->FileName /*+".txt" */ ;
    FILE *fptr = fopen(Fpath.c_str(), "w");

    //fprintf(fptr,"Hue_LUT\tSat_LUT\tBri_LUT\n");
    for (int i = 0; i < HUE_COUNT; i++) {
	fprintf(fptr, "%d\t%d\t%d\n", hueTable[i], satTable[i], valTable[i]);
    }

    fclose(fptr);
}

//---------------------------------------------------------------------------


void __fastcall THSVForm2nd::Hue_ImgMouseMove(TObject * Sender, TShiftState Shift, int X, int Y)
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

void __fastcall THSVForm2nd::btn_Hue_Img_loadClick(TObject * Sender)
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

void __fastcall THSVForm2nd::rg_HSV_ModeClick(TObject * Sender)
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

void __fastcall THSVForm2nd::Btn_HSV_reloadClick(TObject * Sender)
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

void __fastcall THSVForm2nd::FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift)
{
    if (Key == 0x40) {
	Btn_HSV_reloadClick(Sender);
    }
}

//---------------------------------------------------------------------------


void __fastcall THSVForm2nd::sb_dif_nChange(TObject * Sender)
{
    lb_dif_n->Caption = (4 - sb_dif_n->Position) * 15;
}

//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::sb_dif_pChange(TObject * Sender)
{
    lb_dif_p->Caption = sb_dif_p->Position * 15;
}

//---------------------------------------------------------------------------



void __fastcall THSVForm2nd::btn_setClick(TObject * Sender)
{
    for (int i = 0; i < HUE_COUNT; i++) {
	hueTable[i] = hueTableTemp[i];
	satTable[i] = satTableTemp[i];
	valTable[i] = valTableTemp[i];

	stringGrid_HSV->Cells[1][i + 1] =
	    FloatToStr((double) hueTableTemp[i] / MAX_HUE_VALUE * WHOLE_HUE_ANGLE);
	stringGrid_HSV->Cells[2][i + 1] = satTableTemp[i];
	stringGrid_HSV->Cells[3][i + 1] = valTableTemp[i];
    }
    btn_set->Enabled = false;
}

//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::btn_hsv_writeClick(TObject * Sender)
{
    Hue_LUTWrite();
}

//---------------------------------------------------------------------------
// Recover the state of HSV enable
bool THSVForm2nd::HSV_LUT_RW_start()
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
    if (CheckBox_OffWhenWrite->Checked) {
	ChkB[HSVEN_idx]->Chkb->Checked = false;
	EngineerForm->SetWrite_Byte(ChkB[HSVEN_idx]->Addr, 0);
    }
    return 1;
}

//---------------------------------------------------------------------------

// Recover the state of HSV disable
void THSVForm2nd::HSV_LUT_RW_over()
{
    if (CheckBox_OffWhenWrite->Checked) {
	// reload en state
	int set_val = (HSV_EN_State == false ? 0 : 1);
	ChkB[HSVEN_idx]->Chkb->Checked = HSV_EN_State;
	EngineerForm->SetWrite_Byte(ChkB[HSVEN_idx]->Addr, set_val);
    }
}

//---------------------------------------------------------------------------
void THSVForm2nd::HSV_LUT_FuncEnable(bool flag_en)
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

void __fastcall THSVForm2nd::btn_hsv_readClick(TObject * Sender)
{
    HSV_LUT_FuncEnable(0);	// Table operation button disable
    bool ok = HSV_LUT_RW_start();	// Record the state of HSV enable
    if (ok == 0) {		// Fail to record the state
	HSV_LUT_FuncEnable(1);	// Table operation button enable
	return;
    }

    int HSV_lut[HUE_COUNT * 3];

    if (!EngineerForm->SetRead_PG(lut_addr[0], HSV_lut, HSV_IsChkSum)) {
	ShowMessage("Hue page read fail.");
	return;
    }

    /*int HSV_lut[HUE_COUNT * 3];
       for(int x=0;x<HUE_COUNT * 3;x++) {
       HSV_lut[x]= HSV_lutTemp[x];
       } */


    EngineerForm->SetWrite_Byte(en.Addr, HSV_EN_State);
    bool fpga = isFPGA();

    int val_r;
    for (int i = 0; i < HUE_COUNT; i++) {
	//fpga
	if (fpga) {
	    hueTable[i] = HSV_lut[i * 3] * 4 + (HSV_lut[i * 3 + 1] / 64) % 4;
	    satTable[i] = (HSV_lut[i * 3 + 1] % 64) * 2 + (HSV_lut[i * 3 + 2] / 128) % 2;
	    val_r = HSV_lut[i * 3 + 2] % 128;
	} else {
	    // Modified only for AUO11307
	    hueTable[i] = hueTableTemp[i] = HSV_lut[i * 3 + 2] * 4 + (HSV_lut[i * 3 + 1] / 64) % 4;
	    satTable[i] = satTableTemp[i] =
		(HSV_lut[i * 3 + 1] % 64) * 2 + (HSV_lut[i * 3] / 128) % 2;
	    val_r = HSV_lut[i * 3] % 128;
	}

	valTable[i] = valTableTemp[i] = Cmplmnt2sToSign(val_r, 128);

	double hue = ((double) hueTable[i]) / MAX_HUE_VALUE * WHOLE_HUE_ANGLE;
	stringGrid_HSV->Cells[1][i + 1] = hue;
	stringGrid_HSV->Cells[2][i + 1] = (_toString(satTable[i]) + "%").c_str();
	stringGrid_HSV->Cells[3][i + 1] = valTable[i];
    }
    HSV_LUT_RW_over();		// Recover HSV enable
    HSV_LUT_FuncEnable(1);	// Table operation button enable
}

//---------------------------------------------------------------------------



void __fastcall THSVForm2nd::Hue_ImgMouseDown(TObject * Sender,
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
}

//---------------------------------------------------------------------------
void THSVForm2nd::initStringGrid_HSV()
{

    //initial table setting
    for (int i = 0; i < HUE_COUNT; i++) {
	stringGrid_HSV->Cells[0][i + 1] = IntToStr(WHOLE_HUE_ANGLE / HUE_COUNT * i) + "�X";	// Index as hue
	stringGrid_HSV->Cells[1][i + 1] = IntToStr(WHOLE_HUE_ANGLE / HUE_COUNT * i);	// Hue default value
	stringGrid_HSV->Cells[2][i + 1] = 0;	// Saturation default value
	stringGrid_HSV->Cells[3][i + 1] = 0;	// Luminance default value
    }

    stringGrid_HSV->Cells[1][0] = "H";
    stringGrid_HSV->Cells[2][0] = "S";
    stringGrid_HSV->Cells[3][0] = "V";
};

/*const int THSVForm2nd::HueRGBValues[HUE_COUNT][3] = {
    {255, 0, 0}, {255, 64, 0}, {255, 128, 0}, {255, 191, 0}, {255, 255, 0},
    {191, 255, 0}, {128, 255, 0}, {64, 255, 0}, {0, 255, 0}, {0, 255, 64},
    {0, 255, 128}, {0, 255, 191}, {0, 255, 255}, {0, 191, 255}, {0, 128,
								 255},
    {0, 64, 255}, {0, 0, 255}, {64, 0, 255}, {128, 0, 255}, {191, 0, 255},
    {255, 0, 255}, {255, 0, 191}, {255, 0, 128}, {255, 0, 64}
};*/

int THSVForm2nd::getHueAngle(int index)
{
    return WHOLE_HUE_ANGLE / HUE_COUNT * index;
}

int THSVForm2nd::getHueIndex(double angle)
{
    using namespace java::lang;
    double round = Math::round(angle / (WHOLE_HUE_ANGLE / HUE_COUNT));
    return static_cast < int >(round) % 24;
}

int THSVForm2nd::hueAngleToValue(double hueAngle)
{
    double value = hueAngle / WHOLE_HUE_ANGLE * MAX_HUE_VALUE;
    return static_cast < int >(value);
}

double THSVForm2nd::hueValueToAngle(int hueValue)
{
    double angle = ((double) hueValue) / MAX_HUE_VALUE * WHOLE_HUE_ANGLE;
    return angle;
    //return static_cast < int >(angle);
}

RGB_ptr THSVForm2nd::getHueRGB(int index)
{
    RGB_ptr rgb = getHueRGB(index, getSaturation(), getValue());
    return rgb;
}

RGB_ptr THSVForm2nd::getHueRGB(int index, double s, int v)
{
    using namespace Dep;
    int hue = getHueAngle(index);
    HSV_ptr hsv(new HSV(RGBColorSpace::sRGB, hue, s, v));

    RGB_ptr rgb = hsv->toRGB();
    return rgb;
}

void __fastcall THSVForm2nd::stringGrid_HSVDrawCell(TObject * Sender,
						    int ACol, int ARow,
						    TRect & Rect, TGridDrawState State)
{
    using namespace Dep;

    //int row = ARow;
    if (ARow >= 1 && ARow <= 24 && ACol == 1) {
	int index = ARow - 1;
	RGB_ptr rgb = getHueRGB(index);
	stringGrid_HSV->Canvas->Brush->Color = rgb->getColor();
	int height = stringGrid_HSV->DefaultRowHeight + 1;
	int width = stringGrid_HSV->ColWidths[0];
	stringGrid_HSV->Canvas->Rectangle(0, height * ARow, width, height * (ARow + 1));
	TColor fontColor = getValue() < 170 ? clWhite : clBlack;
	stringGrid_HSV->Canvas->Font->Color = fontColor;
	int hueAngle = index * 15;
	stringGrid_HSV->Canvas->TextOut(0 + 4, height * ARow + 1, hueAngle);
    }
}

void THSVForm2nd::drawStringGrid_HSVCell(TObject * Sender)
{
    TRect r;
    TGridDrawState g;
    for (int x = 1; x <= 24; x++) {
	stringGrid_HSVDrawCell(Sender, 1, x, r, g);
    }
}

//---------------------------------------------------------------------------

int_array THSVForm2nd::getHSVAdjustValue(int index)
{
    int_array adjustValue(new int[3]);
    adjustValue[0] = hueTableTemp[index];
    adjustValue[1] = satTableTemp[index];
    adjustValue[2] = valTableTemp[index];
    return adjustValue;
}

void __fastcall THSVForm2nd::stringGrid_HSVSelectCell(TObject * Sender,
						      int ACol, int ARow, bool & CanSelect)
{
    lastStringGridSelectRow = ARow;
    int index = ARow - 1;

    //�p�G�O15�ת�base
    //bool base15deg = index % 2 == 1;
    //Button_15BaseInterp->Enabled = base15deg;

    RGB_ptr rgb = getHueRGB(index);
    //�]�wcolorpicker
    selectedRGBValues[0] = rgb->R;
    selectedRGBValues[1] = rgb->G;
    selectedRGBValues[2] = rgb->B;
    customPattern = false;
    colorPicker->setOriginalColor(rgb->R, rgb->G, rgb->B);
    //�]�whsvadjust
    int_array hsvAdjustValue = getHSVAdjustValue(index);
    int s = hsvAdjustValue[1], v = hsvAdjustValue[2];

    int standardHueAngle = getHueAngle(ARow - 1);
    int standardHueValue = hueAngleToValue(standardHueAngle);

    //hue�O�H���վ㪺hue����ǭ�, standardHueAngle�O���վ㪺"����"
    //���ӭn��"����"�ର"��ǭ�"
    //����: 0~360 ��ǭ�: 0~768
    double adjustHueValue = hsvAdjustValue[0];
    int h = adjustHueValue - standardHueValue;
    //h = (h > 96 || h < -96 )? h % 96 : h;
    //�p�󰻴��O�_��L0/360�o�Ӭɭ�?
    bool negative = (standardHueAngle - MAX_ADJUST_HUE_ANGLE) < 0
	&& adjustHueValue > hueAngleToValue((standardHueAngle + MAX_ADJUST_HUE_ANGLE));
    bool positive = (standardHueAngle + MAX_ADJUST_HUE_ANGLE) >= WHOLE_HUE_ANGLE
	&& adjustHueValue < hueAngleToValue(standardHueAngle - MAX_ADJUST_HUE_ANGLE);

    if (negative) {
	h -= MAX_HUE_VALUE;
    }
    if (positive) {
	h += MAX_HUE_VALUE;
    }

    hsvAdjust->setHSVPostition(h, s, v);
    setupPatternForm();
}

//---------------------------------------------------------------------------


void __fastcall THSVForm2nd::hsvAdjustsb_c3d_Manual39_hChange(TObject * Sender)
{
    if (true == settingScrollBarPosition) {
	//return;
    }
    for (int i = 0; i < HUE_COUNT; i++) {
	hueTableTemp[i] = hueTable[i];
	satTableTemp[i] = satTable[i];
	valTableTemp[i] = valTable[i];
    }

    int index = getGridSelectRow() - 1;

    //��s
    int_array hsvPosition = hsvAdjust->getHSVPosition();
    int h = hsvPosition[0];
    int s = hsvPosition[1];
    int v = hsvPosition[2];

    //�i�H��set
    btn_set->Enabled = true;
    if (cb_Hue_rotation->Checked == false) {
	//�D����վ�
	int standardHueValue = hueAngleToValue(getHueAngle(index));
	hueTableTemp[index] = (standardHueValue + h + MAX_HUE_VALUE) % MAX_HUE_VALUE;
	satTableTemp[index] = s;
	valTableTemp[index] = v;
    } else {			//rotation
	//����վ�
	for (int i = 0; i < HUE_COUNT; i++) {
	    int standardHueValue = hueAngleToValue(getHueAngle(i));

	    hueTableTemp[i] = (standardHueValue + h + MAX_HUE_VALUE) % MAX_HUE_VALUE;
	    satTableTemp[i] = s;
	    valTableTemp[i] = v;
	}
    }

    //�P�B��grid
    for (int i = 0; i < HUE_COUNT; i++) {
	stringGrid_HSV->Cells[1][i + 1] =
	    (((double) hueTableTemp[i]) / MAX_HUE_VALUE) * WHOLE_HUE_ANGLE;
	stringGrid_HSV->Cells[2][i + 1] = satTableTemp[i];
	stringGrid_HSV->Cells[3][i + 1] = valTableTemp[i];
    }
    if (true == CheckBox_AutoSet->Checked) {
	btn_setClick(Sender);
    }
    if (true == CheckBox_AutoWrite->Checked) {
	btn_hsv_writeClick(Sender);
    }
}

//---------------------------------------------------------------------------






void __fastcall THSVForm2nd::RadioButton_deg60baseClick(TObject * Sender)
{
    TRadioButton *button = dynamic_cast < TRadioButton * >(Sender);
    if (null != button) {
	setGridSelectRow(hintToRow(button->Hint.ToInt()));
    }
    deChecked(GroupBox_30base);
}

int THSVForm2nd::hintToRow(int hint)
{
    return hint / 15 + 1;
}
void THSVForm2nd::setGridSelectRow(int row)
{
    TGridRect select = stringGrid_HSV->Selection;
    select.Top = row;
    select.Bottom = row;
    stringGrid_HSV->Selection = select;
    stringGrid_HSVSelectCell(null, -1, row, true);
}

int THSVForm2nd::getGridSelectRow()
{
    return stringGrid_HSV->Selection.Top;
}

//---------------------------------------------------------------------------//---------------------------------------------------------------------------
void __fastcall THSVForm2nd::RadioButton_deg30baseClick(TObject * Sender)
{
    TRadioButton *button = dynamic_cast < TRadioButton * >(Sender);
    if (null != button) {
	setGridSelectRow(hintToRow(button->Hint.ToInt()));
    }
    deChecked(GroupBox_60base);
}

void THSVForm2nd::deChecked(TGroupBox * groupBox_base)
{
    int count = groupBox_base->ControlCount;
    for (int x = 0; x < count; x++) {
	TRadioButton *b = dynamic_cast < TRadioButton * >(groupBox_base->Controls[x]);
	if (null != b) {
	    b->Checked = false;
	}
    }
}

//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::FormShow(TObject * Sender)
{
    initGroupBoxBase(GroupBox_30base);
    initGroupBoxBase(GroupBox_60base);
}

//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::RadioGroup_SaturationClick(TObject * Sender)
{
    initGroupBoxBase(GroupBox_30base);
    initGroupBoxBase(GroupBox_60base);
    drawStringGrid_HSVCell(Sender);
    setGridSelectRow(getGridSelectRow());
}

//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::RadioGroup_ValueClick(TObject * Sender)
{
    initGroupBoxBase(GroupBox_30base);
    initGroupBoxBase(GroupBox_60base);
    drawStringGrid_HSVCell(Sender);
    setGridSelectRow(getGridSelectRow());
}

//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::Button_60BaseInterpClick(TObject * Sender)
{
    //�H60base����
    interpolation(60);
    btn_setClick(Sender);
}


int THSVForm2nd::getSuggestLastHueValue(int firstHueValue)
{
    double firsthueAngle = hueValueToAngle(firstHueValue);
    int suggestHueValue = (firsthueAngle >= 0 && firsthueAngle <=
			   MAX_ADJUST_HUE_ANGLE) ?
	hueAngleToValue(firsthueAngle + WHOLE_HUE_ANGLE) : firstHueValue;
    return suggestHueValue;
}

bool THSVForm2nd::isInverse(int *array, int size)
{
    int pre = array[0];
    for (int x = 1; x < size; x++) {
	int now = array[x];
	if (pre > now) {
	    return true;
	}
	pre = now;
    }
    return false;
}

bool THSVForm2nd::isInverse(double_vector_ptr vector, int size)
{
    int pre = (*vector)[0];
    for (int x = 1; x < size; x++) {
	int now = (*vector)[x];
	if (pre > now) {
	    return true;
	}
	pre = now;
    }
    return false;
}
void THSVForm2nd::interpolation(int angleBase)
{
    //������key�ƶq
    int keyCount = WHOLE_HUE_ANGLE / angleBase + 1;
    //���oindex�ɪ��������Y
    int indexFactor = HUE_COUNT / (WHOLE_HUE_ANGLE / angleBase);


    //�H60base����
    double_vector_ptr keys(new double_vector(keyCount));
    double_vector_ptr hvalues(new double_vector(keyCount));
    double_vector_ptr svalues(new double_vector(keyCount));
    double_vector_ptr vvalues(new double_vector(keyCount));

    const int ADD_HUE_VALUE = MAX_HUE_VALUE;

    int preHueValue = -1;
    for (int x = 0; x < keyCount; x++) {
	int hue = angleBase * x;
	(*keys)[x] = hue;
	int index = (x * indexFactor) % HUE_COUNT;
	int hueValue = hueTableTemp[index];
	if (-1 == preHueValue) {
	    preHueValue = hueValue;
	}
	bool inverse = preHueValue > hueValue;

	(*hvalues)[x] = inverse ? hueValue + ADD_HUE_VALUE : hueValue;
	(*svalues)[x] = satTableTemp[index];
	(*vvalues)[x] = valTableTemp[index];
    }
    (*hvalues)[keyCount - 1] = (*hvalues)[0] + ADD_HUE_VALUE;

    if (isInverse(hvalues, keyCount)) {
	ShowMessage("Hue inverse! Interpolation result would error!");
    }


    using namespace math;
    Interpolation1DLUT hlut(keys, hvalues);
    Interpolation1DLUT slut(keys, svalues);
    Interpolation1DLUT vlut(keys, vvalues);

    for (int x = 0; x < HUE_COUNT; x++) {
	int hue = WHOLE_HUE_ANGLE / HUE_COUNT * x;
	if (hue % angleBase != 0) {
	    int h = hlut.getValue(hue);
	    int s = slut.getValue(hue);
	    int v = vlut.getValue(hue);
	    hueTableTemp[x] = h % ADD_HUE_VALUE;
	    satTableTemp[x] = s;
	    valTableTemp[x] = v;
	}
    }
}

//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::Button_30BaseInterpClick(TObject * Sender)
{
    //�H60+30base����
    interpolation(30);
    btn_setClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::FormKeyPress(TObject * Sender, char &Key)
{
    using namespace math;
    using namespace Dep;
    int_array hsvPos = hsvAdjust->getHSVPosition();
    bool hsvAdjusting = false;
    bool manualHsvAdjusting = false;

    switch (Key) {
    case 'v':
    case 'V':
	/*{
	   double_array hsviValues =
	   HSV::getHSVIValues(IntArray::toDoubleArray(cursorRGBValues, 3));
	   int hueIndex = getHueIndex(hsviValues[0]);
	   setGridSelectRow(hueIndex + 1);

	   customPattern = true;
	   IntArray::arraycopy(cursorRGBValues, selectedRGBValues, 3);
	   colorPicker->setOriginalColor(cursorRGBValues[0], cursorRGBValues[1],
	   cursorRGBValues[2]);
	   setupPatternForm();

	   break;
	   } */
	selectColor();
	break;
    case 'w':
    case 'W':
	hsvPos[0] += 1;
	manualHsvAdjusting = true;
	break;
    case 'q':
    case 'Q':
	hsvPos[0] -= 1;
	manualHsvAdjusting = true;
	break;
    case 's':
    case 'S':
	hsvPos[1] += 1;
	manualHsvAdjusting = true;
	break;
    case 'a':
    case 'A':
	hsvPos[1] -= 1;
	manualHsvAdjusting = true;
	break;
    case 'x':
    case 'X':
	hsvPos[2] += 1;
	manualHsvAdjusting = true;
	break;
    case 'z':
    case 'Z':
	hsvPos[2] -= 1;
	manualHsvAdjusting = true;
	break;
    case '1':
    case 'e':
    case 'E':
	hsvAdjust->Button_HueResetClick(Sender);
	hsvAdjusting = true;
	break;
    case '2':
    case 'd':
    case 'D':
	hsvAdjust->Button_SaturationResetClick(Sender);
	hsvAdjusting = true;
	break;
    case '3':
    case 'c':
    case 'C':
	hsvAdjust->Button_BrightnessResetClick(Sender);
	hsvAdjusting = true;
	break;
    }

    if (manualHsvAdjusting) {
	hsvAdjust->setHSVPostition(hsvPos);
	hsvAdjusting = true;
    }
    if (hsvAdjusting) {
	hsvAdjust->sb_HSV_gainChange(Sender);
    }
}


//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::hsvAdjustButton_HueResetClick(TObject * Sender)
{
    hsvAdjust->Button_HueResetClick(Sender);

}

//---------------------------------------------------------------------------




void __fastcall THSVForm2nd::stringGrid_HSVKeyDown(TObject * Sender, WORD & Key, TShiftState Shift)
{
    FormKeyPress(Sender, Key);
}

//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::Button_15BaseInterpClick(TObject * Sender)
{

    base15DegInterpClick(Sender, true, true, true);

}

void THSVForm2nd::base15DegInterpClick(TObject * Sender, bool hInterp, bool sInterp, bool vInterp)
{
    int index = lastStringGridSelectRow - 1;
    bool firstIndex = (index == 0);
    int index0 = firstIndex ? (HUE_COUNT - 1) : (index - 1) % HUE_COUNT;
    int index1 = (index + 1) % HUE_COUNT;

    int_array hsv0 = getHSVAdjustValue(index0);
    int_array hsv1 = getHSVAdjustValue(index1);
    int hsv00 = hsv0[0];
    int hsv10 = (hsv1[0] < hsv00) ? hsv1[0] + MAX_HUE_VALUE : hsv1[0];

    using namespace math;

    if (hInterp) {
	const int ADD_HUE_VALUE = MAX_HUE_VALUE;
	int h = (int) Interpolation::linear(0, 2, hsv00, hsv10, 1);
	hueTableTemp[index] = h % ADD_HUE_VALUE;
    }

    if (sInterp) {
	int s = (int) Interpolation::linear(0, 2, hsv0[1], hsv1[1], 1);
	satTableTemp[index] = s;
    }

    if (vInterp) {
	int v = (int) Interpolation::linear(0, 2, hsv0[2], hsv1[2], 1);
	valTableTemp[index] = v;
    }

    btn_setClick(Sender);
    stringGrid_HSVSelectCell(Sender, 0, lastStringGridSelectRow, false);
}

//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::hsvAdjustsb_Hue_gainChange(TObject * Sender)
{
    hsvAdjust->sb_Hue_gainChange(Sender);

}

//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::Button_HInterpClick(TObject * Sender)
{
    base15DegInterpClick(Sender, true, false, false);
}

//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::Button_SInterpClick(TObject * Sender)
{
    base15DegInterpClick(Sender, false, true, false);
}

//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::Button_VInterpClick(TObject * Sender)
{
    base15DegInterpClick(Sender, false, false, true);
}

//---------------------------------------------------------------------------


void __fastcall THSVForm2nd::Button_OoGSetupClick(TObject * Sender)
{
    if (null == GamutSetupForm) {
	Application->CreateForm(__classid(TGamutSetupForm), &GamutSetupForm);
	GamutSetupForm->callbackIF = this;
    }
    GamutSetupForm->Visible = true;
}

//---------------------------------------------------------------------------
void THSVForm2nd::callback()
{
    using namespace Dep;
    using namespace cms;
    using namespace math;
    using namespace std;
    //���X
    double_array sourceRGBxyY = GamutSetupForm->getSourceRGBxyY();
    double_array targetRGBxyY = GamutSetupForm->getTargetRGBxyY();
    double_array sourceWhiteXYZValues = toWhiteXYZValues(sourceRGBxyY);
    double_array targetWhiteXYZValues = toWhiteXYZValues(targetRGBxyY);
    //���W��
    double sourceNormalFactor = 1. / sourceWhiteXYZValues[1];
    double targetNormalFactor = 1. / targetWhiteXYZValues[1];
    sourceRGBxyY[2] *= sourceNormalFactor;
    targetRGBxyY[2] *= targetNormalFactor;
    for (int x = 0; x < 3; x++) {
	sourceWhiteXYZValues[x] *= sourceNormalFactor;
	targetWhiteXYZValues[x] *= targetNormalFactor;
    }

    //�x�}�B��
    double2D_ptr sourceToXYZMatrix =
	RGBBase::calculateRGBXYZMatrix(sourceRGBxyY[0], sourceRGBxyY[1],
				       sourceRGBxyY[3],
				       sourceRGBxyY[4], sourceRGBxyY[6],
				       sourceRGBxyY[7],
				       sourceWhiteXYZValues);
    double2D_ptr targetToXYZMatrix =
	RGBBase::calculateRGBXYZMatrix(targetRGBxyY[0], targetRGBxyY[1],
				       targetRGBxyY[3],
				       targetRGBxyY[4], targetRGBxyY[6],
				       targetRGBxyY[7],
				       targetWhiteXYZValues);
    //���Xgamma
    double sourceGamma = GamutSetupForm->Edit_SourceGamma->Text.ToDouble();
    double targetGamma = GamutSetupForm->Edit_TargetGamma->Text.ToDouble();

    sourceColorSpace =
	bptr < RGBColorSpace >
	(new RGBColorSpace(CSType::Unknow, Illuminant::D65, sourceToXYZMatrix, sourceGamma));
    targetColorSpace =
	bptr < RGBColorSpace >
	(new RGBColorSpace(CSType::Unknow, Illuminant::D65, targetToXYZMatrix, targetGamma));
    CheckBox_OoG->Enabled = true;
    setupPatternForm();
}

double_array THSVForm2nd::toWhiteXYZValues(double_array rgbxyYValues)
{
    using namespace Indep;
    xyY_ptr rxyY(new CIExyY(rgbxyYValues[0], rgbxyYValues[1], rgbxyYValues[2]));
    xyY_ptr gxyY(new CIExyY(rgbxyYValues[3], rgbxyYValues[4], rgbxyYValues[5]));
    xyY_ptr bxyY(new CIExyY(rgbxyYValues[6], rgbxyYValues[7], rgbxyYValues[8]));
    XYZ_ptr rXYZ = rxyY->toXYZ();
    XYZ_ptr gXYZ = gxyY->toXYZ();
    XYZ_ptr bXYZ = bxyY->toXYZ();
    double_array whiteXYZValues(new double[3]);

    whiteXYZValues[0] = rXYZ->X + gXYZ->X + bXYZ->X;
    whiteXYZValues[1] = rXYZ->Y + gXYZ->Y + bXYZ->Y;
    whiteXYZValues[2] = rXYZ->Z + gXYZ->Z + bXYZ->Z;

    return whiteXYZValues;
}

bool THSVForm2nd::isOutOfGamut(int_array rgbValues)
{
    using namespace math;
    using namespace Dep;
    double_array doubleRGBValues = IntArray::toDoubleArray(rgbValues, 3);

    RGBColor rgb(*targetColorSpace, doubleRGBValues, MaxValue::Int8Bit);
    XYZ_ptr XYZ = rgb.toXYZ();
    //RGBColor rgb2(*sourceColorSpace, XYZ);
    outOfGamutRGB = RGB_ptr(new RGBColor(*sourceColorSpace, XYZ));
    bool isLegal = outOfGamutRGB->isLegal();
    return !isLegal;
}

void THSVForm2nd::callback(int_array rgbValues)
{

    cursorRGBValues = rgbValues;
    Edit_CursorColor->Text =
	"R" + IntToStr(rgbValues[0]) + ", G" + IntToStr(rgbValues[1]) + ", B" +
	IntToStr(rgbValues[2]);

    using namespace math;
    using namespace Dep;
    RGB_ptr rgb(new RGBColor(rgbValues[0], rgbValues[1], rgbValues[2]));
    HSV hsv(rgb);
    double_array hsviValues = hsv.getHSVIValues();

    Edit_CursorColorHSV->Text =
	"H" + IntToStr((int) hsviValues[0]) + ", S" +
	Edit_CursorColorHSV->Text.sprintf("%.3f",
					  hsviValues[1]) + ", V" +
	IntToStr((int) (hsviValues[2] * 255));


    if (CheckBox_OoG->Enabled) {
	if (isOutOfGamut(rgbValues)) {
	    CheckBox_OoG->Checked = true;
	    CheckBox_OoG->Color = clRed;
	} else {
	    CheckBox_OoG->Checked = false;
	    CheckBox_OoG->Color = clBtnFace;
	}

	double_array targetRGBValues(new double[3]);
	outOfGamutRGB->getValues(targetRGBValues, MaxValue::Int8Bit);
	string_ptr targetString = DoubleArray::toString(targetRGBValues, 3);
	Edit_TargetCursorColor->Text = targetString->c_str();
    }
}

void THSVForm2nd::selectColor()
{
    using namespace Dep;
    using namespace math;
    double_array hsviValues = HSV::getHSVIValues(IntArray::toDoubleArray(cursorRGBValues, 3));
    int hueIndex = getHueIndex(hsviValues[0]);
    setGridSelectRow(hueIndex + 1);

    customPattern = true;
    IntArray::arraycopy(cursorRGBValues, selectedRGBValues, 3);
    colorPicker->setOriginalColor(cursorRGBValues[0], cursorRGBValues[1], cursorRGBValues[2]);
    setupPatternForm();
}

void THSVForm2nd::imageMousePressed(TObject * Sender, TMouseButton Button,
				    TShiftState Shift, int X, int Y)
{
    /*using namespace Dep;
       using namespace math;
       double_array hsviValues = HSV::getHSVIValues(IntArray::toDoubleArray(cursorRGBValues, 3));
       int hueIndex = getHueIndex(hsviValues[0]);
       setGridSelectRow(hueIndex + 1);

       customPattern = true;
       IntArray::arraycopy(cursorRGBValues, selectedRGBValues, 3);
       colorPicker->setOriginalColor(cursorRGBValues[0], cursorRGBValues[1], cursorRGBValues[2]);
       setupPatternForm(); */
    selectColor();

}

void __fastcall THSVForm2nd::colorPickercb_show_ref_imgClick(TObject * Sender)
{
    colorPicker->cb_show_ref_imgClick(Sender);

}

//---------------------------------------------------------------------------

void THSVForm2nd::setupPatternForm()
{

    using namespace Dep;
    using namespace math;
    HSV_vector_ptr hsvVector(new HSV_vector());

    const int stdSize = 5;
    int valueArray[stdSize] = { 192, 192, 192, 192, 192 /*, 128, 255, 255 */  };
    double saturationArray[stdSize] =
	{ .33333333333333336, .5, .58333333333333336, .6666666666666667, .75 /*, 1, .5, 1 */  };
    double_array hsvValues(new double[3]);

    int totalSize = customPattern ? stdSize + 1 : stdSize;
    int_vector hueVector;
    double_array hsviValues;
    double hue = 0;

    if (customPattern) {
	//custom pattern�U, �~���D�`�Ihue���ݭn
	hsviValues = HSV::getHSVIValues(IntArray::toDoubleArray(selectedRGBValues, 3));
	hue = hsviValues[0];

    } else {
	hue = getHueAngle(lastStringGridSelectRow - 1);
    }

    switch (patternMode) {
    case PatternMode::Hue15:
	{
	    totalSize *= 3;
	    int hueIndex = getHueIndex(hue);
	    double hue0 = getHueAngle(hueIndex - 1);
	    double hue1 = getHueAngle(hueIndex + 1);

	    hueVector.push_back(hue0);
	    hueVector.push_back(hue);
	    hueVector.push_back(hue1);
	    PatternForm->setPatchCols(3);
	    break;
	}
    case PatternMode::Hue7p5:
	{
	    totalSize *= 5;
	    int hueIndex = getHueIndex(hue);
	    double hue0 = getHueAngle(hueIndex - 1);
	    double hue01 = (hue0 + hue) / 2;
	    double hue1 = getHueAngle(hueIndex + 1);
	    double hue11 = (hue1 + hue) / 2;

	    hueVector.push_back(hue0);
	    hueVector.push_back(hue01);
	    hueVector.push_back(hue);
	    hueVector.push_back(hue11);
	    hueVector.push_back(hue1);
	    PatternForm->setPatchCols(5);
	    break;
	}
    case PatternMode::Single:
	hueVector.push_back(hue);
	PatternForm->setPatchCols(1);
	break;
    }

    for (int x = 0; x < hueVector.size(); x++) {
	int h = hueVector[x];
	if (customPattern) {
	    hsvValues[0] = h;
	    hsvValues[1] = hsviValues[1];
	    hsvValues[2] = hsviValues[2];
	    HSV_ptr hsv(new HSV(RGBColorSpace::sRGB, hsvValues));
	    hsvVector->push_back(hsv);
	}

	for (int y = 0; y < stdSize; y++) {
	    int index = isInversePattern ? stdSize - 1 - y : y;
	    hsvValues[0] = h;
	    double saturation = customPattern ? hsviValues[1] : saturationArray[index];
	    hsvValues[1] = saturation;
	    //hsvValues[1] = saturationArray[index];
	    hsvValues[2] = patternValue;
	    HSV_ptr hsv(new HSV(RGBColorSpace::sRGB, hsvValues));
	    hsvVector->push_back(hsv);
	}
    }

    PatternForm->setHSVVector(hsvVector);

    if (true == CheckBox_OoG->Enabled) {
	int_vector_ptr whiteIndexVector(new int_vector());
	for (int x = 0; x < hsvVector->size(); x++) {
	    HSV_ptr hsv = (*hsvVector)[x];
	    RGB_ptr rgb = hsv->toRGB();
	    int_array rgbValues(new int[3]);
	    rgbValues[0] = rgb->R;
	    rgbValues[1] = rgb->G;
	    rgbValues[2] = rgb->B;
	    if (isOutOfGamut(rgbValues)) {
		whiteIndexVector->push_back(x);
	    }
	}
	PatternForm->setWhiteBoxIndexVector(whiteIndexVector);
    }

    PatternForm->Refresh();
}

void __fastcall THSVForm2nd::CheckBox_ShowPatternClick(TObject * Sender)
{

    if (true == CheckBox_ShowPattern->Checked) {
	setupPatternForm();
	PatternForm->WindowState = wsNormal;
    } else {
	PatternForm->WindowState = wsMinimized;
	PatternForm2->WindowState = wsMinimized;
    }
}

//---------------------------------------------------------------------------
void THSVForm2nd::show15DegBasePattern()
{
    patternMode = PatternMode::Hue15;
    setupPatternForm();

}

void THSVForm2nd::show7p5DegBasePattern()
{
    patternMode = PatternMode::Hue7p5;
    setupPatternForm();
}

void THSVForm2nd::showSinglePattern()
{
    patternMode = PatternMode::Single;
    setupPatternForm();
}

void THSVForm2nd::adjustValue(bool minus)
{
    if (minus) {
	patternValue -= 32;
    } else {
	patternValue += 32;
    }
    patternValue = patternValue < 64 ? 64 : patternValue;
    patternValue = patternValue > 255 ? 255 : patternValue;
    setupPatternForm();
}

void THSVForm2nd::inversePattern(bool inverse)
{
    isInversePattern = inverse;
    setupPatternForm();
}

void THSVForm2nd::keyPress(char &Key)
{
    FormKeyPress(this, Key);
}



void __fastcall THSVForm2nd::hsvAdjustsb_Sat_gainChange(TObject * Sender)
{
    hsvAdjust->sb_Sat_gainChange(Sender);

}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall THSVForm2nd::ScrollBar_TurnPointChange(TObject * Sender)
{
    using namespace std;
    int pos = ScrollBar_TurnPoint->Position;
    string str = _toString(100. / 8 * (pos + 1));
    Label_TurnPoint->Caption = (_toString(pos) + " (" + str + "%)").c_str();
}

//---------------------------------------------------------------------------

