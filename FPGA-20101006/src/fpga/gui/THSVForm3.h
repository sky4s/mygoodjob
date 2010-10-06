//---------------------------------------------------------------------------
//
//    20100608 revise HSV H:10,S:7,V:7 by lynne
//    table讀寫使用 TEngineerForm::SetRead_PG 與 TEngineerForm::SetWrite_PG
//
//---------------------------------------------------------------------------

#ifndef THSVForm3H
#define THSVForm3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Unit1.h"
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
#include "TColorPickerFrame.h"
#include "THSVAdjustFrame.h"
#include <cms/cms.h>

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

/*class AbstHSV {
  public:
    virtual TBit * SetChkBx() = 0;
    virtual TLUT *SetLUT() = 0;
    virtual String HSV_EN_Name() = 0;	// 20100608 return the name of HSV_EN register
    int HSVChkBox_Nbr;
};*/

class THSVForm3:public TForm {
    __published:		// IDE-managed Components
    TOpenDialog * OpenDialog1;
    TSaveDialog *SaveDialog1;
    TGroupBox *GroupBox1;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TRadioGroup *rg_HSV_Mode;
    TButton *btn_hsv_load;
    TButton *btn_hsv_save;
    TCheckBox *CheckBox3;
    TCheckBox *CheckBox4;
    TButton *btn_Hue_Img_load;
    TImage *Hue_Img;
    TStaticText *Hue_Img_Infor;
    TGroupBox *GroupBox28;
    TLabel *Label1;
    TLabel *lb_Hue_gain;
    TLabel *Label136;
    TLabel *lb_dif_n;
    TLabel *lb_dif_p;
    TLabel *Label192;
    TLabel *Label193;
    TLabel *lb_Sat_gain;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *lb_Val_gain;
    TScrollBar *sb_Hue_gain;
    TScrollBar *sb_dif_n;
    TScrollBar *sb_dif_p;
    TScrollBar *sb_Sat_gain;
    TScrollBar *sb_Val_gain;
    TStringGrid *stringGrid_HSV;
    TColorPickerFrame *colorPicker;
    TGroupBox *GroupBox2;
    THSVAdjustFrame *hsvAdjust;
    TCheckBox *cb_Hue_rotation;
    TButton *btn_set;
    TButton *btn_reset;
    TButton *btn_hsv_write;
    TButton *btn_hsv_read;
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
    TLabeledEdit *le_ChAangle;
    TGroupBox *GroupBox3;
    TGroupBox *GroupBox_60base;
    TRadioButton *RadioButton_deg0;
    TRadioButton *RadioButton_deg60;
    TRadioButton *RadioButton_deg120;
    TRadioButton *RadioButton_deg180;
    TRadioButton *RadioButton_deg240;
    TRadioButton *RadioButton_deg300;
    TGroupBox *GroupBox_30base;
    TRadioButton *RadioButton_deg30;
    TRadioButton *RadioButton_deg90;
    TRadioButton *RadioButton_deg150;
    TRadioButton *RadioButton_deg210;
    TRadioButton *RadioButton_deg270;
    TRadioButton *RadioButton_deg330;
    TGroupBox *GroupBox6;
    TRadioButton *RadioButton1;
    TRadioButton *RadioButton2;
    TRadioButton *RadioButton3;
    TRadioButton *RadioButton4;
    TRadioButton *RadioButton5;
    TRadioButton *RadioButton6;
    TButton *Button_InterpTo30base;
    TButton *Button_InterpTo15base;
    TRadioButton *RadioButton13;
    TRadioButton *RadioButton14;
    TRadioButton *RadioButton15;
    TRadioButton *RadioButton16;
    TRadioButton *RadioButton17;
    TRadioButton *RadioButton18;
    TBitBtn *Btn_HSV_reload;
    void __fastcall cb_Hue_RedClick(TObject * Sender);
    void __fastcall cb_Hue_YellowClick(TObject * Sender);
    void __fastcall cb_Hue_GreenClick(TObject * Sender);
    void __fastcall cb_Hue_BlueClick(TObject * Sender);
    void __fastcall cb_Hue_CyanClick(TObject * Sender);
    void __fastcall cb_Hue_MagClick(TObject * Sender);
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
    void __fastcall stringGrid_HSVDrawCell(TObject * Sender, int ACol,
					   int ARow, TRect & Rect, TGridDrawState State);
    void __fastcall stringGrid_HSVSelectCell(TObject * Sender, int ACol,
					     int ARow, bool & CanSelect);
    void __fastcall hsvAdjustsb_c3d_Manual39_hChange(TObject * Sender);
    void __fastcall RadioButton_deg60baseClick(TObject * Sender);
    void __fastcall RadioButton_deg30baseClick(TObject * Sender);
    void __fastcall FormShow(TObject * Sender);
  private:			// User declarations
    static const int HUE_COUNT = 24;	//原本是96, why?
    bool HSV_IsChkSum;
    int tbl_step;
    void initStringGrid_HSV();
    static const int HueRGBValues[HUE_COUNT][3];
    static RGB_ptr getHueRGB(int row);
    double_array getHSVAdjustValue(int row);
    void deg60baseClick(TObject * Sender);
    void deg30baseClick(TObject * Sender);
    void setGridSelectRow(int row);
    void initGroupBoxBase(TGroupBox * groupBox_base);
    int hintToRow(int hint);
  public:			// User declarations
     TBit * cb;
    _CHKB **ChkB;
    TLUT *lut_addr;
    _CHKB en;

    AbstHSV *OHSV;

    int hueTable[HUE_COUNT];
    int satTable[HUE_COUNT];
    int valTable[HUE_COUNT];

    int hueTableTemp[HUE_COUNT];
    int satTableTemp[HUE_COUNT];
    int valTableTemp[HUE_COUNT];


    bool HSV_Chg;		// HSV_Chg = 0 為禁止寫入, HSV_Chg =1 為允許寫入, 以避免動作被中斷

    __fastcall THSVForm3(TComponent * Owner);
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

    bool HSV_EN_State;		// 紀錄HSV table 的 Enable狀態
    int HSVEN_idx;		// 紀錄HSV Enable的CheckBox的index
    bool HSV_LUT_RW_start();	// 紀錄enable狀態
    void HSV_LUT_RW_over();	// 回復enable狀態
    void HSV_LUT_FuncEnable(bool flag_en);	// 設定HSV lut button是否作用, flag =0 不作用, 反之,作用
};
//---------------------------------------------------------------------------
extern PACKAGE THSVForm3 *HSVForm3;
//---------------------------------------------------------------------------
#endif

