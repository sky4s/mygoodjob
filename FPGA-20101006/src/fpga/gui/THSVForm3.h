//---------------------------------------------------------------------------
//
//    20100608 revise HSV H:10,S:7,V:7 by lynne
//    table讀寫使用 TEngineerForm::SetRead_PG 與 TEngineerForm::SetWrite_PG
//
//---------------------------------------------------------------------------

#ifndef THSVForm3H
#define THSVForm3H
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
#include "TColorPickerFrame.h"
#include "THSVAdjustFrame.h"
//其他庫頭文件
#include <java/lang.h>
#include <cms/cms.h>
#include <cms/util/util.h>
//本項目內頭文件
#include <fpga/gui_class.h>
#include <addresstype/Address_type.h>
//本項目內gui頭文件
#include "TColorPickerFrame.h"
#include "THSVAdjustFrame.h"
#include <c3d/GetCursorColor.h>
#include "TPatternForm.h"

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

class THSVFormNew:public TForm, cms::util::CallBackIF, RGBInfoCallbackIF, PatternCallbackIF {
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
    //THSVAdjustFrame *hsvAdjust;
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
    TGroupBox *GroupBox6;
    TRadioButton *RadioButton1;
    TRadioButton *RadioButton2;
    TRadioButton *RadioButton3;
    TRadioButton *RadioButton4;
    TRadioButton *RadioButton5;
    TRadioButton *RadioButton6;
    TRadioButton *RadioButton13;
    TRadioButton *RadioButton14;
    TRadioButton *RadioButton15;
    TRadioButton *RadioButton16;
    TRadioButton *RadioButton17;
    TRadioButton *RadioButton18;
    TBitBtn *Btn_HSV_reload;
    TGroupBox *GroupBox4;
    TGroupBox *GroupBox_60base;
    TRadioButton *RadioButton_deg0;
    TRadioButton *RadioButton_deg60;
    TRadioButton *RadioButton_deg120;
    TRadioButton *RadioButton_deg180;
    TRadioButton *RadioButton_deg240;
    TRadioButton *RadioButton_deg300;
    TButton *Button_60BaseInterp;
    TGroupBox *GroupBox_30base;
    TRadioButton *RadioButton_deg30;
    TRadioButton *RadioButton_deg90;
    TRadioButton *RadioButton_deg150;
    TRadioButton *RadioButton_deg210;
    TRadioButton *RadioButton_deg270;
    TRadioButton *RadioButton_deg330;
    TButton *Button_30BaseInterp;
    TRadioGroup *RadioGroup_Saturation;
    TRadioGroup *RadioGroup_Value;
    TCheckBox *CheckBox_AutoSet;
    TCheckBox *CheckBox_AutoWrite;
    THSVAdjustFrame *hsvAdjust;
    TEdit *Edit_CursorColor;
    TCheckBox *CheckBox_OffWhenWrite;
    TButton *Button_15BaseInterp;
    TButton *Button_HInterp;
    TButton *Button_SInterp;
    TButton *Button_VInterp;
    TGroupBox *GroupBox_OoG;
    TCheckBox *CheckBox_OoG;
    TButton *Button_OoGSetup;
    TEdit *Edit_CursorColorHSV;
    TEdit *Edit_TargetCursorColor;
    TRadioButton *RadioButton_SingleHue;
    TRadioButton *RadioButton_DoubleHue;
    TGroupBox *GroupBox5;
    TCheckBox *CheckBox_ShowPattern;
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
    void __fastcall stringGrid_HSVDrawCell(TObject * Sender, int ACol, int ARow,
					   TRect & Rect, TGridDrawState State);
    void __fastcall stringGrid_HSVSelectCell(TObject * Sender, int ACol,
					     int ARow, bool & CanSelect);
    void __fastcall hsvAdjustsb_c3d_Manual39_hChange(TObject * Sender);
    void __fastcall RadioButton_deg60baseClick(TObject * Sender);
    void __fastcall RadioButton_deg30baseClick(TObject * Sender);
    void __fastcall FormShow(TObject * Sender);
    void __fastcall RadioGroup_SaturationClick(TObject * Sender);
    void __fastcall RadioGroup_ValueClick(TObject * Sender);
    void __fastcall Button_60BaseInterpClick(TObject * Sender);
    void __fastcall Button_30BaseInterpClick(TObject * Sender);
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
    void __fastcall hsvAdjustButton_HueResetClick(TObject * Sender);
    void __fastcall stringGrid_HSVKeyDown(TObject * Sender, WORD & Key, TShiftState Shift);
    void __fastcall Button_15BaseInterpClick(TObject * Sender);
    void __fastcall hsvAdjustsb_Hue_gainChange(TObject * Sender);
    void __fastcall Button_HInterpClick(TObject * Sender);
    void __fastcall Button_SInterpClick(TObject * Sender);
    void __fastcall Button_VInterpClick(TObject * Sender);
    void __fastcall Button_OoGSetupClick(TObject * Sender);
    void __fastcall colorPickercb_show_ref_imgClick(TObject * Sender);
    void __fastcall CheckBox_ShowPatternClick(TObject * Sender);
  protected:
    bool settingScrollBarPosition;
    static const int HUE_COUNT = 24;	//原本是96, why?
    static const int MAX_HUE_VALUE = 768;
    static const int MAX_ADJUST_HUE_ANGLE = 45;
    static const int WHOLE_HUE_ANGLE = 360;

    int getGridSelectRow();

    //=========================================================================
    // hue
    //=========================================================================
    static int getHueAngle(int index);
    static int getHueIndex(double angle);
    static int hueAngleToValue(double hueAngle);
    static double hueValueToAngle(int hueValue);
    static RGB_ptr getHueRGB(int index, double s, int v);
    RGB_ptr getHueRGB(int index);
    int_array getHSVAdjustValue(int row);
    double getSaturation();
    int getValue();
    static int getSuggestLastHueValue(int firstHueValue);
    //=========================================================================

    virtual void hsvAdjustsb_hChange(TObject * Sender);
  private:			// User declarations

    bool HSV_IsChkSum;
    int tbl_step;
    void initStringGrid_HSV();



    void deg60baseClick(TObject * Sender);
    void deg30baseClick(TObject * Sender);

    void drawStringGrid_HSVCell(TObject * Sender);
    void setGridSelectRow(int row);

    void initGroupBoxBase(TGroupBox * groupBox_base);
    void deChecked(TGroupBox * groupBox_base);
    int hintToRow(int hint);
    int lastStringGridSelectRow;

    void interpolation(int angleBase);
    bool isInverse(int *array, int size);
    bool isInverse(double_vector_ptr vector, int size);
    void base15DegInterpClick(TObject * Sender, bool hInterp, bool sInterp, bool vInterp);

    class HSVChangeListener:public gui::event::ChangeListener {
      private:
	THSVFormNew * parent;
      public:
	HSVChangeListener(THSVFormNew * parent):parent(parent) {
	};
	virtual void stateChanged(TObject * Sender) {
	    parent->hsvAdjustsb_c3d_Manual39_hChange(Sender);
	};
    };


    class MousePressedListener:public gui::event::MouseListener {
      private:
	THSVFormNew * parent;
      public:
	MousePressedListener(THSVFormNew * parent):parent(parent) {
	};
	virtual void mousePressed(TObject * Sender,
				  TMouseButton Button, TShiftState Shift, int X, int Y) {
	    parent->imageMousePressed(Sender, Button, Shift, X, Y);
	}
	virtual void mouseReleased(TObject * Sender,
				   TMouseButton Button, TShiftState Shift, int X, int Y) {
	};
    };
    bptr < HSVChangeListener > hsvListener;
    bptr < MousePressedListener > mouseListener;
    bptr < TPColorThread1 > tpColorThread;
    static double_array toWhiteXYZValues(double_array rgbxyYValues);
    bptr < Dep::RGBColorSpace > sourceColorSpace, targetColorSpace;
    int_array cursorRGBValues;
    int_array selectedRGBValues;
    bool customPattern;


    /*enum PatternMode
       {
       Single, Hue15, Hue7p5
       }; */
    PatternMode patternMode;

    bool isOutOfGamut(int_array rgbValues);
    RGB_ptr outOfGamutRGB;
    void setupPatternForm();
    int patternValue;
    bool isInversePattern;
    void selectColor();

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

    __fastcall THSVFormNew(TComponent * Owner);
    void Reset_HSVshow();
    void Hue_LUTWrite();
    void Initial_HSV_table();
    bool Load_HSV(String Fpath);


    bool HSV_EN_State;		// 紀錄HSV table 的 Enable狀態
    int HSVEN_idx;		// 紀錄HSV Enable的CheckBox的index
    bool HSV_LUT_RW_start();	// 紀錄enable狀態
    void HSV_LUT_RW_over();	// 回復enable狀態
    void HSV_LUT_FuncEnable(bool flag_en);	// 設定HSV lut button是否作用, flag =0 不作用, 反之,作用
    virtual void callback();
    virtual void callback(int_array rgbValues);
    void imageMousePressed(TObject * Sender, TMouseButton Button, TShiftState Shift, int X, int Y);

    virtual void show15DegBasePattern();
    virtual void show7p5DegBasePattern();
    virtual void showSinglePattern();
    virtual void adjustValue(bool minus);
    virtual void inversePattern(bool inverse);
    virtual void keyPress(char &Key);
};


//---------------------------------------------------------------------------
extern PACKAGE THSVFormNew *HSVFormNew;
//---------------------------------------------------------------------------
#endif

