//---------------------------------------------------------------------------
//////////////////////////////////////////////////////////////////////////////
//        20100608
//     table Hue 10 bit/ Saturation 7 bit/ Value 7 bit
//     Total 24 bit, 24 set of HSV
//     hue: 0=>0, 768 => 360; Saturation: 0=>0, 32=>1, 64=>2, 96=>3, 128=>4
//     value: -64~+63, use 2's complement
//////////////////////////////////////////////////////////////////////////////

#include <vcl.h>
#include <lib/includeall.h>
#pragma hdrstop

#include "THSVForm3.h"
#include "include.h"
#include <fpga/11307/ImageProcess/ImgProc_11307.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TColorPickerFrame"
#pragma link "THSVAdjustFrame"
#pragma link "TColorPickerFrame"
#pragma link "THSVAdjustFrame"
#pragma resource "*.dfm"


//const double THSVForm3::WHOLE_HUE_ANGLE = 360;
//---------------------------------------------------------------------------
__fastcall THSVForm3::THSVForm3(TComponent * Owner)
:TForm(Owner), HSV_IsChkSum(true), tbl_step(WHOLE_HUE_ANGLE / HUE_COUNT),
lastStringGridSelectRow(-1), settingScrollBarPosition(false)
{
    HSV_Chg = 0;
    HSVEN_idx = -1;
    listener = bptr < HSVChangeListener > (new HSVChangeListener(this));
    hsvAdjust->addChangeListener(listener);
    tpColorThread =
	bptr < TPColorThread1 > (new TPColorThread1(true, Edit_CursorColor, Edit_CursorColorHSV));
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
    if (HSVEN_idx == -1) {
	ShowMessage("Can't Get HSV enable index.");
    }
    Initial_HSV_table();	// initial HSV table
    HSV_Chg = 1;

    this->initStringGrid_HSV();
    colorPicker->setTInTargetForm(InTargetForm);
    tpColorThread->Resume();
}


double THSVForm3::getSaturation()
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

int THSVForm3::getValue()
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

void THSVForm3::initGroupBoxBase(TGroupBox * groupBox_base)
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

void __fastcall THSVForm3::FormClose(TObject * Sender, TCloseAction & Action)
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

void THSVForm3::Initial_HSV_table()
{
    //initial table setting
    for (int i = 0; i < HUE_COUNT; i++) {
	hueTableTemp[i] = hueTable[i] = ((double) i) * MAX_HUE_VALUE / HUE_COUNT;
	satTableTemp[i] = satTable[i] = 32;
	valTableTemp[i] = valTable[i] = 0;
    }

    //hsvAdjust->setHSVPostition(0, 32, 0);
    hsvAdjust->setDefaultHSVPosition(0, 32, 0);
}


//---------------------------------------------------------------------------

void THSVForm3::Reset_HSVshow()
{				// Set gain value relative to color choose
    int tbl_idx = getGridSelectRow();

    //Hue gain
    String hueStr = stringGrid_HSV->Cells[1][tbl_idx];
    String saturationStr = stringGrid_HSV->Cells[2][tbl_idx];
    String valueStr = stringGrid_HSV->Cells[3][tbl_idx];
    hsvAdjust->setHSVPostition(hueStr.ToInt(), (int) floor(saturationStr.ToDouble() * 32),
			       valueStr.ToInt());
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

    for (int i = 0; i < HUE_COUNT; i++) {
	hueTable[i] =
	    (int) (StrToFloat(stringGrid_HSV->Cells[1][i + 1]) / WHOLE_HUE_ANGLE * MAX_HUE_VALUE +
		   0.5);
	satTable[i] = (int) (StrToFloat(stringGrid_HSV->Cells[2][i + 1]) * 32);
	valTable[i] = StrToInt(stringGrid_HSV->Cells[3][i + 1]);
    }

    int *HSV_lut = new int[HUE_COUNT * 3];
    int val_w;
    for (int i = 0; i < HUE_COUNT; i++) {
	hueTable[i] = hueTable[i] % 1024;	// 10 bit
	satTable[i] = satTable[i] % 128;	// 7 bit
	val_w = SignToCmplmnt2s(valTable[i], 128);
	val_w = val_w % 128;	// 7 bit

	//fpga
	/*HSV_lut[i * 3] = hueTable[i] / 4;
	   HSV_lut[i * 3 + 1] = hueTable[i] % 4 * 64 + satTable[i] / 2;
	   HSV_lut[i * 3 + 2] = satTable[i] % 2 * 128 + val_w; */

	//11307
	HSV_lut[i * 3 + 2] = hueTable[i] / 4;
	HSV_lut[i * 3 + 1] = hueTable[i] % 4 * 64 + satTable[i] / 2;
	HSV_lut[i * 3] = satTable[i] % 2 * 128 + val_w;

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
    initStringGrid_HSV();
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
	hueTable[i] = -1;
	satTable[i] = -1;
	valTable[i] = 0;
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
	stringGrid_HSV->Cells[2][i + 1] = satTable[i] / 32.;
	stringGrid_HSV->Cells[3][i + 1] = valTable[i];
    }

    stringGrid_HSVSelectCell(this, 0, lastStringGridSelectRow, false);

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
    for (int i = 0; i < HUE_COUNT; i++) {
	fprintf(fptr, "%d\t%d\t%d\n", hueTable[i], satTable[i], valTable[i]);
    }

    fclose(fptr);
}

//---------------------------------------------------------------------------


void __fastcall THSVForm3::Hue_ImgMouseMove(TObject * Sender, TShiftState Shift, int X, int Y)
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
		ShowMessage("HSV CheckBox read error:" + IntToStr(read_val));
	}
    }
    btn_hsv_readClick(Sender);
    HSV_LUT_FuncEnable(1);
    Btn_HSV_reload->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift)
{
    if (Key == 0x40) {
	Btn_HSV_reloadClick(Sender);
    }
}

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
    for (int i = 0; i < HUE_COUNT; i++) {
	hueTable[i] = hueTableTemp[i];
	satTable[i] = satTableTemp[i];
	valTable[i] = valTableTemp[i];

	stringGrid_HSV->Cells[1][i + 1] =
	    FloatToStr((double) hueTableTemp[i] / MAX_HUE_VALUE * WHOLE_HUE_ANGLE);
	stringGrid_HSV->Cells[2][i + 1] = FloatToStr((double) (satTableTemp[i]) / 32);
	stringGrid_HSV->Cells[3][i + 1] = valTableTemp[i];
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
    if (CheckBox_OffWhenWrite->Checked) {
	ChkB[HSVEN_idx]->Chkb->Checked = false;
	EngineerForm->SetWrite_Byte(ChkB[HSVEN_idx]->Addr, 0);
    }
    return 1;
}

//---------------------------------------------------------------------------

// Recover the state of HSV disable
void THSVForm3::HSV_LUT_RW_over()
{
    if (CheckBox_OffWhenWrite->Checked) {
	// reload en state
	int set_val = (HSV_EN_State == false ? 0 : 1);
	ChkB[HSVEN_idx]->Chkb->Checked = HSV_EN_State;
	EngineerForm->SetWrite_Byte(ChkB[HSVEN_idx]->Addr, set_val);
    }
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

    int HSV_lut[HUE_COUNT * 3];
    if (!EngineerForm->SetRead_PG(lut_addr[0], HSV_lut, HSV_IsChkSum)) {
	ShowMessage("Hue page read fail.");
	return;
    }
    EngineerForm->SetWrite_Byte(en.Addr, HSV_EN_State);

    int val_r;
    for (int i = 0; i < HUE_COUNT; i++) {
	//fpga
	/*hueTable[i] = HSV_lut[i * 3] * 4 + (HSV_lut[i * 3 + 1] / 64) % 4;
	   satTable[i] = (HSV_lut[i * 3 + 1] % 64) * 2 + (HSV_lut[i * 3 + 2] / 128) % 2;
	   val_r = HSV_lut[i * 3 + 2] % 128; */
	// Modified only for AUO11307
	hueTable[i] = hueTableTemp[i] = HSV_lut[i * 3 + 2] * 4 + (HSV_lut[i * 3 + 1] / 64) % 4;
	satTable[i] = satTableTemp[i] = (HSV_lut[i * 3 + 1] % 64) * 2 + (HSV_lut[i * 3] / 128) % 2;

	val_r = HSV_lut[i * 3] % 128;
	valTable[i] = valTableTemp[i] = Cmplmnt2sToSign(val_r, 128);

	stringGrid_HSV->Cells[1][i + 1] = ((double) hueTable[i]) / MAX_HUE_VALUE * WHOLE_HUE_ANGLE;
	stringGrid_HSV->Cells[2][i + 1] = satTable[i] / 32.;
	stringGrid_HSV->Cells[3][i + 1] = valTable[i];
    }
    HSV_LUT_RW_over();		// Recover HSV enable
    HSV_LUT_FuncEnable(1);	// Table operation button enable
}

//---------------------------------------------------------------------------



void __fastcall THSVForm3::Hue_ImgMouseDown(TObject * Sender,
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
void THSVForm3::initStringGrid_HSV()
{

    //initial table setting
    for (int i = 0; i < HUE_COUNT; i++) {
	stringGrid_HSV->Cells[0][i + 1] = IntToStr(WHOLE_HUE_ANGLE / HUE_COUNT * i) + "°";	// Index as hue
	stringGrid_HSV->Cells[1][i + 1] = IntToStr(WHOLE_HUE_ANGLE / HUE_COUNT * i);	// Hue default value
	stringGrid_HSV->Cells[2][i + 1] = 1;	// Saturation default value
	stringGrid_HSV->Cells[3][i + 1] = 0;	// Luminance default value
    }

    stringGrid_HSV->Cells[1][0] = "H";
    stringGrid_HSV->Cells[2][0] = "S";
    stringGrid_HSV->Cells[3][0] = "V";
};

/*const int THSVForm3::HueRGBValues[HUE_COUNT][3] = {
    {255, 0, 0}, {255, 64, 0}, {255, 128, 0}, {255, 191, 0}, {255, 255, 0},
    {191, 255, 0}, {128, 255, 0}, {64, 255, 0}, {0, 255, 0}, {0, 255, 64},
    {0, 255, 128}, {0, 255, 191}, {0, 255, 255}, {0, 191, 255}, {0, 128,
								 255},
    {0, 64, 255}, {0, 0, 255}, {64, 0, 255}, {128, 0, 255}, {191, 0, 255},
    {255, 0, 255}, {255, 0, 191}, {255, 0, 128}, {255, 0, 64}
};*/

int THSVForm3::getHueAngle(int index)
{
    return WHOLE_HUE_ANGLE / HUE_COUNT * index;
}

int THSVForm3::hueAngleToValue(double hueAngle)
{
    double value = hueAngle / WHOLE_HUE_ANGLE * MAX_HUE_VALUE;
    return static_cast < int >(value);
}

double THSVForm3::hueValueToAngle(int hueValue)
{
    double angle = ((double) hueValue) / MAX_HUE_VALUE * WHOLE_HUE_ANGLE;
    return angle;
    //return static_cast < int >(angle);
}

RGB_ptr THSVForm3::getHueRGB(int index)
{
    RGB_ptr rgb = getHueRGB(index, getSaturation(), getValue());
    return rgb;
}

RGB_ptr THSVForm3::getHueRGB(int index, double s, int v)
{
    using namespace Dep;
    int hue = getHueAngle(index);
    //double hue256 = hue / 360. * 255;
    RGB_ptr rgb = RGBColor::fromHSVValues(hue, s, v);
    return rgb;
}

void __fastcall THSVForm3::stringGrid_HSVDrawCell(TObject * Sender,
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

void THSVForm3::drawStringGrid_HSVCell(TObject * Sender)
{
    TRect r;
    TGridDrawState g;
    for (int x = 1; x <= 24; x++) {
	stringGrid_HSVDrawCell(Sender, 1, x, r, g);
    }
}

//---------------------------------------------------------------------------

int_array THSVForm3::getHSVAdjustValue(int index)
{
    int_array adjustValue(new int[3]);
    adjustValue[0] = hueTableTemp[index];
    adjustValue[1] = satTableTemp[index];
    adjustValue[2] = valTableTemp[index];
    return adjustValue;
}

void __fastcall THSVForm3::stringGrid_HSVSelectCell(TObject * Sender,
						    int ACol, int ARow, bool & CanSelect)
{
    /*if (lastStringGridSelectRow == ARow) {
       return;
       } */
    lastStringGridSelectRow = ARow;
    int index = ARow - 1;

    //如果是15度的base
    //bool base15deg = index % 2 == 1;
    //Button_15BaseInterp->Enabled = base15deg;

    RGB_ptr rgb = getHueRGB(index);
    //設定colorpicker
    colorPicker->setOriginalColor(rgb->R, rgb->G, rgb->B);
    //設定hsvadjust
    int_array hsvAdjustValue = getHSVAdjustValue(index);
    int s = hsvAdjustValue[1], v = hsvAdjustValue[2];

    int standardHueAngle = getHueAngle(ARow - 1);
    int standardHueValue = hueAngleToValue(standardHueAngle);

    //hue是以未調整的hue為基準值, standardHueAngle是未調整的"角度"
    //應該要把"角度"轉為"基準值"
    //角度: 0~360 基準值: 0~768
    double adjustHueValue = hsvAdjustValue[0];
    int h = adjustHueValue - standardHueValue;
    //h = (h > 96 || h < -96 )? h % 96 : h;
    //如何偵測是否跨過0/360這個界限?
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
}

//---------------------------------------------------------------------------


void __fastcall THSVForm3::hsvAdjustsb_c3d_Manual39_hChange(TObject * Sender)
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

    //更新
    int_array hsvPosition = hsvAdjust->getHSVPosition();
    int h = hsvPosition[0];
    int s = hsvPosition[1];
    int v = hsvPosition[2];

    //可以做set
    btn_set->Enabled = true;
    if (cb_Hue_rotation->Checked == false) {
	//非全域調整
	int standardHueValue = hueAngleToValue(getHueAngle(index));
	hueTableTemp[index] = (standardHueValue + h + MAX_HUE_VALUE) % MAX_HUE_VALUE;
	satTableTemp[index] = s;
	valTableTemp[index] = v;
    } else {			//rotation
	//全域調整
	for (int i = 0; i < HUE_COUNT; i++) {
	    int standardHueValue = hueAngleToValue(getHueAngle(i));

	    hueTableTemp[i] = (standardHueValue + h + MAX_HUE_VALUE) % MAX_HUE_VALUE;
	    satTableTemp[i] = s;
	    valTableTemp[i] = v;
	}
    }

    //同步到grid
    for (int i = 0; i < HUE_COUNT; i++) {
	stringGrid_HSV->Cells[1][i + 1] =
	    (((double) hueTableTemp[i]) / MAX_HUE_VALUE) * WHOLE_HUE_ANGLE;
	stringGrid_HSV->Cells[2][i + 1] = satTableTemp[i] / 32.;
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






void __fastcall THSVForm3::RadioButton_deg60baseClick(TObject * Sender)
{
    TRadioButton *button = dynamic_cast < TRadioButton * >(Sender);
    if (null != button) {
	setGridSelectRow(hintToRow(button->Hint.ToInt()));
    }
    deChecked(GroupBox_30base);
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

int THSVForm3::getGridSelectRow()
{
    return stringGrid_HSV->Selection.Top;
}

//---------------------------------------------------------------------------//---------------------------------------------------------------------------
void __fastcall THSVForm3::RadioButton_deg30baseClick(TObject * Sender)
{
    TRadioButton *button = dynamic_cast < TRadioButton * >(Sender);
    if (null != button) {
	setGridSelectRow(hintToRow(button->Hint.ToInt()));
    }
    deChecked(GroupBox_60base);
}

void THSVForm3::deChecked(TGroupBox * groupBox_base)
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

void __fastcall THSVForm3::FormShow(TObject * Sender)
{
    initGroupBoxBase(GroupBox_30base);
    initGroupBoxBase(GroupBox_60base);
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::RadioGroup_SaturationClick(TObject * Sender)
{
    initGroupBoxBase(GroupBox_30base);
    initGroupBoxBase(GroupBox_60base);
    drawStringGrid_HSVCell(Sender);
    setGridSelectRow(getGridSelectRow());
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::RadioGroup_ValueClick(TObject * Sender)
{
    initGroupBoxBase(GroupBox_30base);
    initGroupBoxBase(GroupBox_60base);
    drawStringGrid_HSVCell(Sender);
    setGridSelectRow(getGridSelectRow());
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::Button_60BaseInterpClick(TObject * Sender)
{
    //以60base內插
    interpolation(60);
    btn_setClick(Sender);
}


int THSVForm3::getSuggestLastHueValue(int firstHueValue)
{
    double firsthueAngle = hueValueToAngle(firstHueValue);
    int suggestHueValue = (firsthueAngle >= 0 && firsthueAngle <=
			   MAX_ADJUST_HUE_ANGLE) ?
	hueAngleToValue(firsthueAngle + WHOLE_HUE_ANGLE) : firstHueValue;
    return suggestHueValue;
}

bool THSVForm3::isInverse(int *array, int size)
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

bool THSVForm3::isInverse(double_vector_ptr vector, int size)
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
void THSVForm3::interpolation(int angleBase)
{
    //內插的key數量
    int keyCount = WHOLE_HUE_ANGLE / angleBase + 1;
    //取得index時的倍數關係
    int indexFactor = HUE_COUNT / (WHOLE_HUE_ANGLE / angleBase);


    //以60base內插
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

void __fastcall THSVForm3::Button_30BaseInterpClick(TObject * Sender)
{
    //以60+30base內插
    interpolation(30);
    btn_setClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::FormKeyPress(TObject * Sender, char &Key)
{
    int_array hsvPos = hsvAdjust->getHSVPosition();
    bool hsvAdjusting = false;
    bool manualHsvAdjusting = false;

    switch (Key) {
    case 'v':
    case 'V':
	colorPicker->setOriginalColor(tpColorThread->r, tpColorThread->g, tpColorThread->b);
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

void __fastcall THSVForm3::hsvAdjustButton_HueResetClick(TObject * Sender)
{
    hsvAdjust->Button_HueResetClick(Sender);

}

//---------------------------------------------------------------------------




void __fastcall THSVForm3::stringGrid_HSVKeyDown(TObject * Sender, WORD & Key, TShiftState Shift)
{
    FormKeyPress(Sender, Key);
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::Button_15BaseInterpClick(TObject * Sender)
{

    base15DegInterpClick(Sender, true, true, true);
    /*int index = lastStringGridSelectRow - 1;
       bool firstIndex = (index == 0);
       int index0 = firstIndex ? (HUE_COUNT - 1) : (index - 1) % HUE_COUNT;
       int index1 = (index + 1) % HUE_COUNT;

       int_array hsv0 = getHSVAdjustValue(index0);
       int_array hsv1 = getHSVAdjustValue(index1);
       int hsv00 = hsv0[0];
       int hsv10 = (hsv1[0] < hsv00) ? hsv1[0] + MAX_HUE_VALUE : hsv1[0];

       using namespace math;
       int h = (int) Interpolation::linear(0, 2, hsv00, hsv10, 1);
       int s = (int) Interpolation::linear(0, 2, hsv0[1], hsv1[1], 1);
       int v = (int) Interpolation::linear(0, 2, hsv0[2], hsv1[2], 1);

       const int ADD_HUE_VALUE = MAX_HUE_VALUE;
       hueTableTemp[index] = h % ADD_HUE_VALUE;
       satTableTemp[index] = s;
       valTableTemp[index] = v;

       btn_setClick(Sender);
       stringGrid_HSVSelectCell(Sender, 0, lastStringGridSelectRow, false); */

}

void THSVForm3::base15DegInterpClick(TObject * Sender, bool hInterp, bool sInterp, bool vInterp)
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

void __fastcall THSVForm3::hsvAdjustsb_Hue_gainChange(TObject * Sender)
{
    hsvAdjust->sb_Hue_gainChange(Sender);

}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::Button_HInterpClick(TObject * Sender)
{
    base15DegInterpClick(Sender, true, false, false);
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::Button_SInterpClick(TObject * Sender)
{
    base15DegInterpClick(Sender, false, true, false);
}

//---------------------------------------------------------------------------

void __fastcall THSVForm3::Button_VInterpClick(TObject * Sender)
{
    base15DegInterpClick(Sender, false, false, true);
}

//---------------------------------------------------------------------------

