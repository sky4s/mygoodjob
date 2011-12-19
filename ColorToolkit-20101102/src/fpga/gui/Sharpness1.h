//---------------------------------------------------------------------------
//  20100608
//  Sharpness table讀寫使用 TEngineerForm::SetRead_PG 與 TEngineerForm::SetWrite_PG
//---------------------------------------------------------------------------

#ifndef Sharpness1H
#define Sharpness1H
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
#include <fpga/gui_class.h>
#include <addresstype/Address_type.h>
//本項目內gui頭文件



/*====================================================================
TSharpnessForm1為一繼承TForm形態的class, 為Sharpness頁面的Interface
======================================================================*/
class TSharpnessForm1:public TForm {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox3;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TCheckBox *CheckBox4;
    TCheckBox *CheckBox5;
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TLabel *Label2;
    TScrollBar *ScrollBar1;
    TScrollBar *ScrollBar2;
    TStaticText *StaticText1;
    TStaticText *StaticText2;
    TGroupBox *GroupBox2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TScrollBar *ScrollBar3;
    TScrollBar *ScrollBar4;
    TScrollBar *sb_softgain;
    TStaticText *StaticText3;
    TStaticText *StaticText4;
    TStaticText *st_softgain;
    TGroupBox *GroupBox47;
    TImage *SP_LUT;
    TButton *btn_sp_lut_write;
    TButton *btn_sp_lut_Set;
    TButton *btn_GainSet;
    TCheckBox *CheckBox3;
    TOpenDialog *OpenDialog1;
    TSaveDialog *SaveDialog1;
    TRadioGroup *LUT_type;
    TButton *btn_sp_Load;
    TButton *btn_sp_Save;
    TBitBtn *btn_sp_lut_read;
    TBitBtn *Btn_SP_reload;
    TCheckBox *CheckBox6;
    TButton *Button_LoadOldSetting;
    TButton *Button_SaveOldSetting;
    TGroupBox *GroupBox4;
    void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall CheckBox_Click(TObject * Sender);
    void __fastcall ScrollBar_Change(TObject * Sender);
    void __fastcall LblEdit2_KeyPress(TObject * Sender, char &Key);	//Add by Michelle 20100702
    void __fastcall SP_LUTMouseDown(TObject * Sender,
				    TMouseButton Button, TShiftState Shift, int X, int Y);
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
    void __fastcall Button_LoadOldSettingClick(TObject * Sender);
    void __fastcall Button_SaveOldSettingClick(TObject * Sender);
  private:			// User declarations
     bool SP_IsChkSum;
    bool loadSetting(String filename);
  public:			// User declarations
     __fastcall TSharpnessForm1(TComponent * Owner);
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
       _CHKB,_ScrollBar: 為自定的class, 內含圖形介面物件與位置的參數,詳情參考Unit1.h
     */

    AbstSP *OSP;

    TBit *cb;
    _CHKB **ChkB;

    TBit *scrlb;
    _ScrollBar **ScrlB;

    TBit2 *lble2;		// Add by Michelle 20100702
    _LBLE2 **LblE2;

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
extern PACKAGE TSharpnessForm1 *SharpnessForm1;
//---------------------------------------------------------------------------


#endif

