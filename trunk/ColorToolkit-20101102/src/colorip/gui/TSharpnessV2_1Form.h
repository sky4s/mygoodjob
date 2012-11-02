//---------------------------------------------------------------------------
//  20121101
//  仿製 From "TSharpnessV2Form"
//---------------------------------------------------------------------------

#ifndef TSharpnessV2_1FormH
#define TSharpnessV2_1FormH
//---------------------------------------------------------------------------

//C系統文件
#include <stdio.h>
//C++系統文件

//vcl庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Chart.hpp>
#include <ExtCtrls.hpp>
#include <Series.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Dialogs.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include <vcl.h>
//其他庫頭文件
#include <windows.h>
//本項目內頭文件
#include <colorip/gui_class.h>
#include <addresstype/Address_type.h>
//本項目內gui頭文件

#include "ImgProc_11307.h"

/*====================================================================
TSharpnessV2_1Form為一繼承TForm形態的class, 為Sharpness頁面的Interface
======================================================================*/
class TSharpnessV2_1Form : public TForm
{
__published:	// IDE-managed Components
        // Button (5)
        TButton *btn_sp_Load;
        TButton *btn_sp_Save;
        TButton *btn_sp_lut_write;
        TButton *btn_sp_lut_Set;
        TButton *btn_GainSet;
        // CheckBox (12)
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox8;
        TCheckBox *CheckBox9;
        TCheckBox *CheckBox10;
        TCheckBox *CheckBox11;
        TCheckBox *CheckBox12;
        // ComboBox & Label (7)
        TComboBox *ComboBox1;   TLabel *Label7;
        TComboBox *ComboBox2;   TLabel *Label8;
        TComboBox *ComboBox3;   TLabel *Label9;
        TComboBox *ComboBox4;   TLabel *Label10;
        TComboBox *ComboBox5;   TLabel *Label17;
        TComboBox *ComboBox6;   TLabel *Label18;
        TComboBox *ComboBox7;   TLabel *Label27;
        // GroupBox (17)
        TGroupBox *Sharpness;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TGroupBox *GroupBox3;
        TGroupBox *GroupBox4;
        TGroupBox *GroupBox5;
        TGroupBox *GroupBox6;
        TGroupBox *GroupBox7;
        TGroupBox *GroupBox8;
        TGroupBox *GroupBox9;
        TGroupBox *GroupBox10;
        TGroupBox *GroupBox11;
        TGroupBox *GroupBox12;
        TGroupBox *GroupBox13;
        TGroupBox *GroupBox14;
        TGroupBox *GroupBox15;
        TGroupBox *GroupBox16;
        // Label (28-7(ComboBox)-18(ScrollBar))
        TLabel *Label23;
        TLabel *Label24;
        TLabel *Software;
        // Label & ScrollBar & StaticText (19-1(without software_gain))
        TScrollBar *sb_softgain;        TStaticText *st_softgain;
        TLabel *Label1;         TScrollBar *ScrollBar1;         TStaticText *StaticText1;
        TLabel *Label2;         TScrollBar *ScrollBar2;         TStaticText *StaticText2;
        TLabel *Label3;         TScrollBar *ScrollBar3;         TStaticText *StaticText3;
        TLabel *Label4;         TScrollBar *ScrollBar4;         TStaticText *StaticText4;
        TLabel *Label5;         TScrollBar *ScrollBar5;         TStaticText *StaticText5;
        TLabel *Label6;         TScrollBar *ScrollBar6;         TStaticText *StaticText6;
        TLabel *Label11;        TScrollBar *ScrollBar7;         TStaticText *StaticText7;
        TLabel *Label12;        TScrollBar *ScrollBar8;         TStaticText *StaticText8;
        TLabel *Label13;        TScrollBar *ScrollBar9;         TStaticText *StaticText9;
        TLabel *Label14;        TScrollBar *ScrollBar10;        TStaticText *StaticText10;
        TLabel *Label15;        TScrollBar *ScrollBar11;        TStaticText *StaticText11;
        TLabel *Label16;        TScrollBar *ScrollBar12;        TStaticText *StaticText12;
        TLabel *Label19;        TScrollBar *ScrollBar13;        TStaticText *StaticText13;
        TLabel *Label20;        TScrollBar *ScrollBar14;        TStaticText *StaticText14;
        TLabel *Label21;        TScrollBar *ScrollBar15;        TStaticText *StaticText15;
        TLabel *Label22;        TScrollBar *ScrollBar16;        TStaticText *StaticText16;
        TLabel *Label25;        TScrollBar *ScrollBar17;        TStaticText *StaticText17;
        TLabel *Label26;        TScrollBar *ScrollBar18;        TStaticText *StaticText18;
        // Others
        TBitBtn *Btn_SP_reload;
        TBitBtn *btn_sp_lut_read;
        TRadioGroup *LUT_type;
        TImage *SP_LUT;
        TBevel *Bevel1;
        TBevel *Bevel2;
        TBevel *Bevel3;
        TBevel *Bevel4;
        TBevel *Bevel5;
        TLabeledEdit *LabeledEdit1;
        TEdit *Edit_ResolutionH;
        TEdit *Edit_ResolutionV;
        TSaveDialog *SaveDialog1;
        TOpenDialog *OpenDialog1;

        // Function
        void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
        void __fastcall FormCreate(TObject * Sender);
        void __fastcall CheckBox_Click(TObject * Sender);
        void __fastcall ComboBox_Click(TObject * Sender);
        void __fastcall LblE3_KeyPress(TObject * Sender,  char &Key);
        void __fastcall ScrollBar_Change(TObject * Sender);
        void __fastcall SP_LUTMouseDown(TObject * Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall SP_LUTDblClick(TObject * Sender);
        void __fastcall btn_sp_lut_SetClick(TObject * Sender);
        void __fastcall sb_softgainChange(TObject * Sender);
        void __fastcall btn_GainSetClick(TObject * Sender);
        void __fastcall btn_sp_lut_writeClick(TObject * Sender);
        void __fastcall btn_sp_LoadClick(TObject * Sender);
        void __fastcall btn_sp_SaveClick(TObject * Sender);
        void __fastcall LUT_typeClick(TObject * Sender);
        void __fastcall btn_sp_lut_readClick(TObject * Sender);
        void __fastcall Btn_SP_reloadClick(TObject * Sender);
        void __fastcall FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift);
        void __fastcall Edit_ResolutionHKeyPress(TObject * Sender,const char &Key);
        void __fastcall FormKeyPress(TObject * Sender, char &Key);
  private:			// User declarations
     bool SP_IsChkSum;
  public:			// User declarations
     __fastcall TSharpnessV2_1Form(TComponent * Owner);
    /*
       Sharpness 頁面使用的變數
       AbstSP:是一個class,擁有可傳回Sharpness Address的函式
       OSP: 宣告成AbstSP形態的變數
       cb: 為checkbox物件所對應的address
       ChkB: 具有checkbox物件所對應的介面物件與address
       scrlb: 為ScrollBar物件所對應的address
       ScrlB: 具有ScrollBar物件所對應的介面物件與address
       ChkB: 具有checkbox物件所對應的介面物件與address
       TBit,TLUT: 為自定的Address class,詳細內容參考Address_type.h
       _CHKB,_ScrollBar: 為自定的class, 內含圖形介面物件與位置的參數,詳情參考MainForm.h
     */

    AbstSP *OSP;

    TBit *cb;
    _CHKB **ChkB;

    TBit *cbo;
    _CBOB **CboB;

    TBit3 *lble3;
    _LBLE3 **LblE3;

    TBit *scrlb;
    _ScrollBar **ScrlB;

    TLUT *SP_addr;		//lookup table的address
    int SP_lut[32];		//lookup table
    bool SP_Chg;		//用來設定介面物件是否可寫入的flag
    int LUT_g[32];
    int gain_flag;
    void Clear_LUT(bool type);	//清空table介面上面的點
    bool Load_SP(String Fpath);

    void SP_LUT_FuncEnable(bool);
};
//---------------------------------------------------------------------------
extern PACKAGE TSharpnessV2_1Form *SharpnessV2_1Form;
//---------------------------------------------------------------------------

#endif




