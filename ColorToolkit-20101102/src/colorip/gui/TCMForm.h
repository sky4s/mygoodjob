//---------------------------------------------------------------------------
//
//       20100608 更新cm offset type     by lynne
//       Value Transform type : CM->Setofs_type()
//       1. Range: ±63.875,  2s’ Complement
//       2. Range: ±127.75,  use sign bit
//       3. Range: ±256.5,   2s’ Complement
//       4. Range: ±512,     2s’ Complement
//
//      對應到OFS_TYPE裡的順序為:
//      1. -127.75~127.75
//      2. -63.875~63.875
//      3. -256.5~256.5
//      4. -511~511
//
//       table讀寫使用 TEngineerForm::SetRead_PG 與 TEngineerForm::SetWrite_PG
//
//----------------------------------------------------------------------------

#ifndef TCMFormH
#define TCMFormH
//---------------------------------------------------------------------------

//C系統文件

//C++系統文件

//vcl庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ActnList.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
//其他庫頭文件

//本項目內頭文件
#include <colorip/gui_class.h>
#include <addresstype/Address_type.h>
//本項目內gui頭文件
#include "PERFGRAP.h"
//---------------------------------------------------------------------------

/*====================================================================
TCMForm1為一繼承TForm形態的class, 為Color Matrix頁面的Interface
======================================================================*/

enum OffsetType {
    Unknow, _128, _64, _257, _511
};

enum Mode {
    Manual, WhiteBalance, Vivid
};
class TCMForm:public TForm {
    __published:		// IDE-managed Components
    TOpenDialog * OpenDialog1;
    TSaveDialog *SaveDialog1;
    TGroupBox *GroupBox19;
    TLabel *Label4;
    TPageControl *TS_CM;
    TTabSheet *th_CM1;
    TLabel *CM1_hint;
    TLabel *Label1;
    TStaticText *StaticText7;
    TStaticText *StaticText8;
    TStaticText *StaticText9;
    TEdit *CM1_11;
    TEdit *CM1_12;
    TEdit *CM1_13;
    TEdit *CM1_21;
    TEdit *CM1_22;
    TEdit *CM1_23;
    TEdit *CM1_31;
    TEdit *CM1_32;
    TEdit *CM1_33;
    TButton *btn_CM1_Write;
    TStaticText *StaticText12;
    TStaticText *StaticText13;
    TStaticText *StaticText14;
    TButton *bn_CM1Save;
    TButton *bn_CM1Load;
    TCheckBox *cb_CM1_W255;
    TRadioGroup *rg_CM1_mode;
    TScrollBar *sb_cm11;
    TScrollBar *sb_cm12;
    TScrollBar *sb_cm13;
    TStaticText *st_ofs1;
    TStaticText *st_CM11gain;
    TStaticText *st_CM12gain;
    TStaticText *st_CM13gain;
    TTabSheet *th_CM2;
    TLabel *CM2_hint;
    TLabel *Label2;
    TButton *btn_CM2_Write;
    TStaticText *StaticText1;
    TStaticText *StaticText4;
    TStaticText *StaticText5;
    TEdit *CM2_11;
    TEdit *CM2_12;
    TEdit *CM2_13;
    TEdit *CM2_21;
    TEdit *CM2_22;
    TEdit *CM2_23;
    TEdit *CM2_31;
    TEdit *CM2_32;
    TEdit *CM2_33;
    TStaticText *StaticText21;
    TStaticText *StaticText22;
    TStaticText *StaticText23;
    TButton *bn_CM2Save;
    TButton *bn_CM2Load;
    TCheckBox *cb_CM2_W255;
    TRadioGroup *rg_CM2_mode;
    TScrollBar *sb_ofs2;
    TStaticText *st_ofs2;
    TScrollBar *sb_cm21;
    TScrollBar *sb_cm22;
    TScrollBar *sb_cm23;
    TStaticText *st_CM21gain;
    TStaticText *st_CM22gain;
    TStaticText *st_CM23gain;
    TTabSheet *th_CM3;
    TLabel *CM3_hint;
    TLabel *Label3;
    TButton *btn_CM3_Write;
    TStaticText *StaticText6;
    TStaticText *StaticText10;
    TStaticText *StaticText11;
    TEdit *CM3_11;
    TEdit *CM3_12;
    TEdit *CM3_13;
    TEdit *CM3_21;
    TEdit *CM3_22;
    TEdit *CM3_23;
    TEdit *CM3_31;
    TEdit *CM3_32;
    TEdit *CM3_33;
    TStaticText *StaticText24;
    TStaticText *StaticText25;
    TStaticText *StaticText26;
    TButton *bn_CM3Save;
    TButton *bn_CM3Load;
    TCheckBox *cb_CM3_W255;
    TRadioGroup *rg_CM3_mode;
    TScrollBar *sb_ofs3;
    TStaticText *st_ofs3;
    TScrollBar *sb_cm31;
    TScrollBar *sb_cm32;
    TScrollBar *sb_cm33;
    TStaticText *st_CM31gain;
    TStaticText *st_CM32gain;
    TStaticText *st_CM33gain;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TCheckBox *CheckBox3;
    TComboBox *ComboBox1;
    TBitBtn *Btn_CM_reload;
    TButton *btn_CM1_Read;
    TButton *btn_CM2_Read;
    TButton *btn_CM3_Read;
    TScrollBar *sb_ofs1;
    TCheckBox *CheckBox4;
    void __fastcall CM_CheckBox_Click(TObject * Sender);
    void __fastcall CM_ComboBox_Click(TObject * Sender);
    void __fastcall btn_CM1_WriteClick(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall btn_CM2_WriteClick(TObject * Sender);
    void __fastcall btn_CM3_WriteClick(TObject * Sender);
    void __fastcall sb_cm11Change(TObject * Sender);
    void __fastcall CM1_keyPress(TObject * Sender,const char &Key);
    void __fastcall rg_CM1_modeClick(TObject * Sender);
    void __fastcall sb_cm12Change(TObject * Sender);
    void __fastcall sb_cm13Change(TObject * Sender);
    void __fastcall CM2_keyPress(TObject * Sender,const char &Key);
    void __fastcall sb_cm21Change(TObject * Sender);
    void __fastcall CM3_keyPress(TObject * Sender,const char &Key);
    void __fastcall sb_cm22Change(TObject * Sender);
    void __fastcall sb_cm23Change(TObject * Sender);
    void __fastcall sb_cm31Change(TObject * Sender);
    void __fastcall sb_cm32Change(TObject * Sender);
    void __fastcall sb_cm33Change(TObject * Sender);
    void __fastcall sb_ofs1Change(TObject * Sender);
    void __fastcall sb_ofs2Change(TObject * Sender);
    void __fastcall sb_ofs3Change(TObject * Sender);
    void __fastcall TS_CMChange(TObject * Sender);
    void __fastcall bn_CM1SaveClick(TObject * Sender);
    void __fastcall bn_CM2SaveClick(TObject * Sender);
    void __fastcall bn_CM3SaveClick(TObject * Sender);
    void __fastcall bn_CM1LoadClick(TObject * Sender);
    void __fastcall bn_CM2LoadClick(TObject * Sender);
    void __fastcall bn_CM3LoadClick(TObject * Sender);
    void __fastcall Btn_CM_reloadClick(TObject * Sender);
    void __fastcall btn_CM1_ReadClick(TObject * Sender);
    void __fastcall btn_CM2_ReadClick(TObject * Sender);
    void __fastcall btn_CM3_ReadClick(TObject * Sender);
    void __fastcall rg_CM2_modeClick(TObject * Sender);
    void __fastcall rg_CM3_modeClick(TObject * Sender);
    void __fastcall FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift);
    void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
  private:			// User declarations
    void CM_val_initial();
    static int FloatToMemForm(int temp);
    static int MemToFloatForm(int mem);
    int FloatToMemOfsForm(int ofs);
    int MemToFloatOfsForm(int ofs);
    float parsePosition(float originalPosition);
    void writeOffset(TLUT offsetAddress, int position);

    bool CM_IsChkSum;
    AbstCM *OCM;
    TBit *cm_cb;
    _CHKB **CMChkB;
    TBit *cm_cbo;
    _CBOB **CMCboB;
    TLUT *CM_addr, *ofs_addr;

    //int CMofs_type;
    OffsetType offsetType;
    static int getBaseNumber(OffsetType offsetType);
    int Convert_type;
    bool CMInitialized;

    float CM1[3][3];
    float CM2[3][3];
    float CM3[3][3];
    TEdit *CM1EditArray[9];
    TEdit *CM2EditArray[9];
    TEdit *CM3EditArray[9];

    void selectMode(int mode, TEdit * e[9]);
    void scrollBarOffsetChange(int index, bool w255Fix, TEdit * e[9],
			       TScrollBar * scroll, TStaticText * text);
    void storeCMToTCON(int index, TEdit * e[9], TScrollBar * offset);
    //void loadCMFromTCON(int index, TEdit * e[9], TStaticText * offset);
    void loadCMFromTCON(int index, TEdit * e[9], TScrollBar * offset);
    void storeCMToFile(String filename, TEdit * e[9], TStaticText * offset);
    void loadCMFromFile(String filename, OffsetType offsetType,
			float CM[3][3], TEdit * CMEditArray[9],
			TScrollBar * gain[3], TScrollBar * offset);
  public:			// User declarations
     __fastcall TCMForm(TComponent * Owner);

};
//---------------------------------------------------------------------------
extern PACKAGE TCMForm *CMForm;
//---------------------------------------------------------------------------



#endif

