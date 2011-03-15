//---------------------------------------------------------------------------
//
//    20100608 revise HSV H:10,S:7,V:7 by lynne
//    table讀寫使用 TEngineerForm::SetRead_PG 與 TEngineerForm::SetWrite_PG
//
//---------------------------------------------------------------------------

#ifndef HueSatVal1H
#define HueSatVal1H
//---------------------------------------------------------------------------

//C系統文件

//C++系統文件

//vcl庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
//其他庫頭文件

//本項目內頭文件
#include <fpga/gui_class.h>
#include <addresstype/Address_type.h>
//本項目內gui頭文件

//---------------------------------------------------------------------------
///////// HSV Table Address Arrange /////////
//
//  Byte 0 :  Hue0 [9:2]
//  Byte 1 :  Hue0 [1:0]  SAT0 [6:1]
//  Byte 2 :  SAT0 [0]    LUM0 [6:0]
//  Byte 3 :  Hue1 [9:2]
//  Byte 4 :  Hue1 [1:0]  SAT1 [6:1]
//  Byte 5 :  SAT1 [0]    LUM1 [6:0]
/////////////////////////////////////////////


class THSVFormOrg:public TForm {
    __published:		// IDE-managed Components
    TOpenDialog * OpenDialog1;
    TSaveDialog *SaveDialog1;
    TGroupBox *GroupBox1;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TRadioGroup *rg_HSV_Mode;
    TButton *btn_hsv_load;
    TButton *btn_hsv_save;
    TGroupBox *GroupBox29;
    TLabel *Label111;
    TCheckBox *cb_Hue_Red;
    TStringGrid *sg_6HSV;
    TCheckBox *cb_Hue_Green;
    TCheckBox *cb_Hue_Blue;
    TCheckBox *cb_Hue_Mag;
    TCheckBox *cb_Hue_Yellow;
    TCheckBox *cb_Hue_Cyan;
    TStaticText *StaticText31;
    TStaticText *StaticText32;
    TStaticText *StaticText33;
    TEdit *ed_Hue_Custom;
    TButton *btn_Hue_Img_load;
    TGroupBox *GroupBox28;
    TBitBtn *Btn_HSV_reload;
    TStaticText *Hue_Img_Infor;
    TImage *Hue_Img;
    TLabeledEdit *le_ChAangle;
    TLabel *Label1;
    TCheckBox *cb_Hue_rotation;
    TScrollBar *sb_Hue_gain;
    TScrollBar *sb_dif_n;
    TScrollBar *sb_dif_p;
    TLabel *lb_Hue_gain;
    TLabel *Label136;
    TLabel *lb_dif_n;
    TLabel *lb_dif_p;
    TLabel *Label192;
    TLabel *Label193;
    TLabel *lb_Sat_gain;
    TScrollBar *sb_Sat_gain;
    TLabel *Label2;
    TLabel *Label3;
    TScrollBar *sb_Val_gain;
    TLabel *lb_Val_gain;
    TButton *btn_hsv_write;
    TButton *btn_hsv_read;
    TButton *btn_reset;
    TButton *btn_set;
    TStringGrid *sg_HSV;
    TCheckBox *CheckBox3;
    TCheckBox *CheckBox4;
    void __fastcall cb_Hue_RedClick(TObject * Sender);
    void __fastcall cb_Hue_YellowClick(TObject * Sender);
    void __fastcall cb_Hue_GreenClick(TObject * Sender);
    void __fastcall cb_Hue_BlueClick(TObject * Sender);
    void __fastcall cb_Hue_CyanClick(TObject * Sender);
    void __fastcall cb_Hue_MagClick(TObject * Sender);
    void __fastcall ed_Hue_CustomChange(TObject * Sender);
    void __fastcall btn_hsv_loadClick(TObject * Sender);
    void __fastcall btn_hsv_saveClick(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall CheckBox_Click(TObject * Sender);
    void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
    void __fastcall Hue_ImgMouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall btn_resetClick(TObject * Sender);
    void __fastcall sb_Hue_gainScroll(TObject * Sender, TScrollCode ScrollCode, int &ScrollPos);

    void __fastcall btn_Hue_Img_loadClick(TObject * Sender);
    void __fastcall rg_HSV_ModeClick(TObject * Sender);
    void __fastcall Btn_HSV_reloadClick(TObject * Sender);
    void __fastcall FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift);
    void __fastcall sb_dif_nChange(TObject * Sender);
    void __fastcall sb_dif_pChange(TObject * Sender);
    void __fastcall btn_setClick(TObject * Sender);
    void __fastcall btn_hsv_writeClick(TObject * Sender);
    void __fastcall btn_hsv_readClick(TObject * Sender);
    void __fastcall Hue_ImgMouseDown(TObject * Sender,
				     TMouseButton Button, TShiftState Shift, int X, int Y);
  private:			// User declarations
  public:			// User declarations
     TBit * cb;
    _CHKB **ChkB;
    TLUT *lut_addr;
    _CHKB en;

    AbstHSV *OHSV;
    int Hue_table[96];
    int Sat_table[96];
    int Val_table[96];

    int Hue_table_t[96];
    int Sat_table_t[96];
    int Val_table_t[96];

    bool HSV_Chg;		// HSV_Chg = 0 為禁止寫入, HSV_Chg =1 為允許寫入, 以避免動作被中斷

    __fastcall THSVFormOrg(TComponent * Owner);
    void Reset_HSVshow();
    //bool Load_HSIini(String Fpath);
    void Hue_LUTWrite();
    void Initial_HSV_table();
    bool Load_HSV(String Fpath);
    void show_gain(int h, int s, int v);
    bool CheckDif(int &high, int &low, int *tmp_H, int tbl_n);
    void Get_Adj_tbl(int *tmp_H, int *tmp_S, int *tmp_V, int tbl_idx);
    void Set_Adj_tbl(int *tmp_H, int *tmp_S, int *tmp_V, int tbl_idx);
    bool CheckHueIncrease(int high, int low, int *tmp_H);
    void Set_6HSV_grid();

    bool HSV_EN_State;		// 紀錄HSV table 的 Enable狀態
    int HSVEN_idx;		// 紀錄HSV Enable的CheckBox的index
    bool HSV_LUT_RW_start();	// 紀錄enable狀態
    void HSV_LUT_RW_over();	// 回復enable狀態
    void HSV_LUT_FuncEnable(bool flag_en);	// 設定HSV lut button是否作用, flag =0 不作用, 反之,作用
};

void rgb2hsv(double r, double g, double b, double *h, double *s, double *i, double *v)
{
    r = (int) r;
    g = (int) g;
    b = (int) b;
    *i = (r + g + b) / 3;
    double max = (r > g ? r : g);
    max = (b > max ? b : max);
    *v = max;
    double min = (r < g ? r : g);
    min = (min < b ? min : b);
    double d = max - min;
    *s = d;
    d = (d == 0 ? d + 256 : d);

    if (s == 0)
	*h = 0;
    else if (max == r)
	*h = 60 * (g - b) / d;
    else if (max == g)
	*h = 60 * (b - r) / d + 120;
    else if (max == b)
	*h = 60 * (r - g) / d + 240;
    *h = fmod(*h + 360, 360);
    if (max == 0)
	*s = 0;
    else
	*s = *s / max;
}

//--------------------------------------------------------------------------
int SignToCmplmnt2s(int value, int Range)
{
    if (value < 0)
	value += Range;
    return value;
}

int Cmplmnt2sToSign(int value, int Range)
{
    int max = floor(Range / 2 + 0.5) - 1;
    if (value > max)
	value -= Range;
    return value;
}
int Get_select_idx(double angle);
//---------------------------------------------------------------------------
extern PACKAGE THSVFormOrg *HSVFormOrg;
//---------------------------------------------------------------------------
#endif

