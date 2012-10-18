//---------------------------------------------------------------------------

#ifndef THSVV2FormH
#define THSVV2FormH
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
#include <gui/util/binder.h>
//本項目內頭文件
#include <colorip/gui_class.h>
#include <addresstype/Address_type.h>
//本項目內gui頭文件
#include "TColorPickerFrame.h"
#include "THSVAdjustFrame.h"
#include <gui/util/GetCursorColor.h>
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

class THSVV2Form:public TForm, cms::util::CallBackIF, RGBInfoCallbackIF, PatternCallbackIF {
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
    TStringGrid *hsvStringGrid;
    TColorPickerFrame *colorPicker;
    TGroupBox *GroupBox_Adjust;
    TButton *btn_set;
    TButton *btn_reset;
    TButton *btn_hsv_write;
    TButton *btn_hsv_read;
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
    TGroupBox *GroupBox7;
    TScrollBar *ScrollBar_TurnPoint;
    TLabel *Label_TurnPoint;
    TCheckBox *CheckBox_SAT_CLIP_EN;
    TGroupBox *GroupBox8;
    TRadioButton *RadioButton_CSkin;
    TRadioButton *RadioButton_OSkin;
    TRadioButton *RadioButton_Orange;
    TRadioButton *RadioButton_GreenGrass;
    TRadioButton *RadioButton_DFoliage;
    TRadioButton *RadioButton_BlueSky;
    TCheckBox *CheckBox_MemoryColor;
    TGroupBox *GroupBox9;
    TLabel *Label25;
    TScrollBar *ScrollBar_Chroma;
    TLabel *Label_Chroma;
    TButton *Button_ChromaReset;
    TCheckBox *CheckBox_ShowPattern;
    TEdit *Edit_TargetCursorColorHSV;
    TRadioButton *RadioButton_Single;
    TRadioButton *RadioButton_Local;
    TRadioButton *RadioButton_Global;
    TGroupBox *GroupBox5;
    TGroupBox *GroupBox_HSVVersion;
    TRadioButton *RadioButton_v1;
    TRadioButton *RadioButton_v2;
    TRadioGroup *RadioGroup_Global;
    TCheckBox *CheckBox_FuncOn;
    TButton *Button_SaveOldFormat;
    TGroupBox *GroupBox_ReadWrite;
    TBitBtn *Btn_HSV_reload;
    TLabel *Label1;

    void __fastcall btn_hsv_loadClick(TObject * Sender);
    void __fastcall btn_hsv_saveClick(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall CheckBox_Click(TObject * Sender);
    void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
    void __fastcall btn_resetClick(TObject * Sender);

    void __fastcall rg_HSV_ModeClick(TObject * Sender);
    void __fastcall Btn_HSV_reloadClick(TObject * Sender);
    void __fastcall FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift);
    void __fastcall btn_setClick(TObject * Sender);
    void __fastcall btn_hsv_writeClick(TObject * Sender);
    void __fastcall btn_hsv_readClick(TObject * Sender);
    void __fastcall hsvStringGridDrawCell(TObject * Sender, int ACol,
					  int ARow, TRect & Rect, TGridDrawState State);
    void __fastcall hsvStringGridSelectCell(TObject * Sender, int ACol,
					    int ARow, const bool & CanSelect);
    void __fastcall hsvAdjustsb_Manual39_hChange(TObject * Sender);
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
    void __fastcall hsvAdjustsb_Sat_gainChange(TObject * Sender);
    void __fastcall ScrollBar_TurnPointChange(TObject * Sender);
    void __fastcall RadioButton_MemoryColorClick(TObject * Sender);
    void __fastcall RadioButton_MemoryColorMouseDown(TObject * Sender,
						     TMouseButton Button,
						     TShiftState Shift, int X, int Y);
    void __fastcall Button_ChromaResetClick(TObject * Sender);
    void __fastcall hsvAdjustsb_Val_gainChange(TObject * Sender);
    void __fastcall ScrollBar_ChromaChange(TObject * Sender);
    void __fastcall RadioButton_GlobalClick(TObject * Sender);
    void __fastcall colorPickerbtn_load_imgClick(TObject * Sender);
    void __fastcall RadioButton_SingleClick(TObject * Sender);
    void __fastcall RadioButton_LocalClick(TObject * Sender);
    void __fastcall RadioGroup_GlobalClick(TObject * Sender);
    void __fastcall Button_SaveOldFormatClick(TObject * Sender);
    void __fastcall RadioButton_v1Click(TObject * Sender);
    void __fastcall RadioButton_v2Click(TObject * Sender);
  private:			// User declarations
    static const int HUE_COUNT = 24;	//原本是96, why?
    static const int MAX_HUE_VALUE = 768;
    static const int MAX_ADJUST_HUE_ANGLE = 45;
    static const int WHOLE_HUE_ANGLE = 360;
    bool HSV_IsChkSum;
    const int EachHueStep;


    //=========================================================================
    // hue
    //=========================================================================
    static int getHueAngle(int index);
    static int getHueIndex(double angle);
    static int getBaseHueIndex(double angle);
    static int hueAngleToValue(double hueAngle);
    static double hueValueToAngle(int hueValue);
    static RGB_ptr getHueRGB(int index, double s, int v);
    RGB_ptr getHueRGB(int index);
    int_array getHSVAdjustValue(int row);
    double getSaturation();
    int getValue();
    static int getSuggestLastHueValue(int firstHueValue);
    bool doubleHueSelected;
    std::string getSaturationString(int saturation);
    int getSaturationValue(String saturationString);

    //=========================================================================

    //=========================================================================
    // UI
    //=========================================================================
    void deg60baseClick(TObject * Sender);
    void deg30baseClick(TObject * Sender);

    void drawHSVStringGridCell(TObject * Sender);
    void setGridSelectRow(int row);
    void setGridSelectRow(int startRow, int endRow);
    int getGridSelectRow();
    void initGroupBoxBase(TGroupBox * groupBox_base);
    void deChecked(TGroupBox * groupBox_base);
    int hintToRow(int hint);
    int lastStringGridSelectRow;
    bool settingScrollBarPosition;
    void base15DegInterpClick(TObject * Sender, bool hInterp, bool sInterp, bool vInterp);
    bool hsvInitialized;	// hsvInitialized = F 為禁止寫入, hsvInitialized = T 為允許寫入, 以避免動作被中斷
    bool turnToRelativeGlobalAdjust;
    //=========================================================================

    void interpolation(int angleBase);
    bool isInverse(int *array, int size);
    bool isInverse(double_vector_ptr vector, int size);


    class HSVChangeListener:public gui::event::ChangeListener {
      private:
	THSVV2Form * parent;
      public:
	HSVChangeListener(THSVV2Form * parent):parent(parent) {
	};
	virtual void stateChanged(TObject * Sender) {
	    parent->hsvAdjustsb_Manual39_hChange(Sender);
	};
    };


    class MousePressedListener:public gui::event::MouseListener {
      private:
	THSVV2Form * parent;
      public:
	MousePressedListener(THSVV2Form * parent):parent(parent) {
	};
	virtual void mousePressed(TObject * Sender,
				  TMouseButton Button, TShiftState Shift, int X, int Y) {
	    parent->imageMousePressed(Sender, Button, Shift, X, Y);
	}
	virtual void mouseReleased(TObject * Sender,
				   TMouseButton Button, TShiftState Shift, int X, int Y) {
	};
    };

    class CaptionIFListener:public CaptionIF {
      private:
	//AnsiString astr;
	THSVV2Form * parent;
      public:
	CaptionIFListener(THSVV2Form * parent):parent(parent) {
	};
	virtual String getSaturationCaption(int saturationPos) {
	    String result = parent->isInHSVv1()? (saturationPos) / 32. : (saturationPos - 32);
	    return result;
	};

    };

    class MinFunction:public algo::MinimisationFunction {
      private:
	bptr < cms::hsvip::ChromaEnhance > ce;
	short hue, saturation;
      public:
	MinFunction(short _hue, short _saturation, bptr < cms::hsvip::ChromaEnhance > _ce):ce(_ce) {
	    setHueAndSaturation(_hue, _saturation);
	};
	double function(double_vector_ptr param) {
	    short value = (short) (*param)[0];
	    const cms::hsvip::SingleHueAdjustValue shav(hue, saturation, value);
	    double deltaL = ce->calculateDeltaL(shav);
	    return deltaL;
	};
	void setHueAndSaturation(short _hue, short _saturation) {
	    hue = _hue;
	    saturation = _saturation;
	};

    };

    bptr < HSVChangeListener > hsvListener;
    bptr < MousePressedListener > mouseListener;
    bptr < TPColorThread1 > tpColorThread;
    bptr < CaptionIFListener > captionIFListener;


    bptr < Dep::RGBColorSpace > sourceColorSpace, targetColorSpace;
    int_array cursorRGBValues;
    int_array selectedRGBValues;
    int_array storeHSVPosition4DoubleHue;
    bool customPattern;

    PatternMode patternMode;

    //=========================================================================
    // out of gamut
    //=========================================================================
    static double_array toWhiteXYZValues(double_array rgbxyYValues);
    bool isOutOfGamut(int_array rgbValues);
    RGB_ptr outOfGamutRGB;
    bptr < Dep::RGBColorSpace > colorspace;	// = RGBColorSpace::sRGB_gamma22;
    //=========================================================================

    void setupPatternForm();
    int patternValue;
    bool isInversePattern;
    void selectColor();


    //=========================================================================
    // chroma
    //=========================================================================
    cms::hsvip::IntegerSaturationFormula isf;	//((byte) 7, 3);
    bptr < cms::hsvip::ChromaEnhance > ce;
    short getValueFromChromaEnhance(short hue, short chroma);
    void setChromaOfScrollBar(short chroma);
    bool changeChromaBySystem;
    //=========================================================================

    //=========================================================================
    // bind ui and setting
    //=========================================================================
    gui::util::MultiUIBinder binder;

    TBit *cb;
    _CHKB **ChkB;
    TLUT *lut_addr;

    _CHKB en;			//用途不明?

    AbstHSV *OHSV;
    //=========================================================================

    //=========================================================================
    //hsv table
    //=========================================================================
    int hueTable[HUE_COUNT];
    int satTable[HUE_COUNT];
    int valTable[HUE_COUNT];
    int hsvTableForRelative[3][HUE_COUNT];
    void syncStringGridToTable();
    void syncTableToStringGrid();
    void initHSVStringGrid();
    static const int DefaultSaturationPos = 32;
    //=========================================================================

  public:			// User declarations




    __fastcall THSVV2Form(TComponent * Owner);
    void Hue_LUTWrite();
    void initHSVTable();
    bool Load_HSV(String Fpath);


    bool HSV_EN_State;		// 紀錄HSV table 的 Enable狀態
    int HSVEN_idx;		// 紀錄HSV Enable的CheckBox的index
    bool HSV_LUT_RW_start();	// 紀錄enable狀態
    void HSV_LUT_RW_over();	// 回復enable狀態
    void HSV_LUT_FuncEnable(bool flag_en);	// 設定HSV lut button是否作用, flag =0 不作用, 反之,作用
    virtual void callback();
    virtual void callback(int_array rgbValues);
    bool isInHSVv1();
    void imageMousePressed(TObject * Sender, TMouseButton Button, TShiftState Shift, int X, int Y);

    virtual void show15DegBasePattern();
    virtual void show7p5DegBasePattern();
    virtual void showSinglePattern();
    virtual void adjustValue(bool minus);
    virtual void inversePattern(bool inverse);
    virtual void keyPress(char &Key);
};


//---------------------------------------------------------------------------
extern PACKAGE THSVV2Form *HSVV2Form;
//---------------------------------------------------------------------------
#endif

