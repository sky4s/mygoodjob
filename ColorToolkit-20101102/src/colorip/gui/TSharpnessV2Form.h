//---------------------------------------------------------------------------
//  20100608
//  Sharpness tableŪ�g�ϥ� TEngineerForm::SetRead_PG �P TEngineerForm::SetWrite_PG
//---------------------------------------------------------------------------

#ifndef TSharpnessV2FormH
#define TSharpnessV2FormH
//---------------------------------------------------------------------------

//C�t�Τ��
#include <stdio.h>
//C++�t�Τ��

//vcl�w�Y���
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
//��L�w�Y���
#include <windows.h>
//�����ؤ��Y���
#include <colorip/gui_class.h>
#include <addresstype/Address_type.h>
//�����ؤ�gui�Y���

#include "ImgProc_11307.h"

/*====================================================================
TSharpnessForm12307���@�~��TForm�κA��class, ��Sharpness������Interface
======================================================================*/
class TSharpnessV2Form:public TForm {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox3;
    TGroupBox *GroupBox2;
    TLabel *Software;
    TScrollBar *sb_softgain;
    TStaticText *st_softgain;
    TGroupBox *GroupBox47;
    TImage *SP_LUT;
    TButton *btn_sp_lut_write;
    TButton *btn_sp_lut_Set;
    TButton *btn_GainSet;
    TOpenDialog *OpenDialog1;
    TSaveDialog *SaveDialog1;
    TRadioGroup *LUT_type;
    TButton *btn_sp_Load;
    TButton *btn_sp_Save;
    TBitBtn *btn_sp_lut_read;
    TBitBtn *Btn_SP_reload;
    TGroupBox *Sharpness;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TCheckBox *CheckBox3;
    TLabel *Label1;
    TScrollBar *ScrollBar1;
    TStaticText *StaticText1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TScrollBar *ScrollBar2;
    TScrollBar *ScrollBar3;
    TScrollBar *ScrollBar4;
    TStaticText *StaticText2;
    TStaticText *StaticText3;
    TStaticText *StaticText4;
    TCheckBox *CheckBox4;
    TCheckBox *CheckBox5;
    TScrollBar *ScrollBar5;
    TScrollBar *ScrollBar6;
    TStaticText *StaticText5;
    TStaticText *StaticText6;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TComboBox *ComboBox1;
    TComboBox *ComboBox2;
    TCheckBox *CheckBox6;
    TCheckBox *CheckBox7;
    TGroupBox *Contrast;
    TCheckBox *CheckBox8;
    TCheckBox *CheckBox9;
    TCheckBox *CheckBox10;
    TCheckBox *CheckBox11;
    TCheckBox *CheckBox12;
    TLabel *Label9;
    TLabel *Label10;
    TComboBox *ComboBox3;
    TComboBox *ComboBox4;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label15;
    TLabel *Label16;
    TScrollBar *ScrollBar7;
    TScrollBar *ScrollBar8;
    TScrollBar *ScrollBar9;
    TScrollBar *ScrollBar10;
    TScrollBar *ScrollBar11;
    TScrollBar *ScrollBar12;
    TStaticText *StaticText7;
    TStaticText *StaticText8;
    TStaticText *StaticText9;
    TStaticText *StaticText10;
    TStaticText *StaticText11;
    TStaticText *StaticText12;
    TLabeledEdit *LabeledEdit1;
    TLabel *Label17;
    TLabel *Label18;
    TComboBox *ComboBox5;
    TComboBox *ComboBox6;
    TLabel *Label19;
    TLabel *Label20;
    TLabel *Label21;
    TLabel *Label22;
    TScrollBar *ScrollBar13;
    TScrollBar *ScrollBar14;
    TScrollBar *ScrollBar15;
    TScrollBar *ScrollBar16;
    TStaticText *StaticText13;
    TStaticText *StaticText14;
    TStaticText *StaticText15;
    TStaticText *StaticText16;
    TEdit *Edit_ResolutionH;
    TLabel *Label23;
    TEdit *Edit_ResolutionV;
    TLabel *Label24;
    TGroupBox *GroupBox_BrightScene;
    TGroupBox *GroupBox_DarkScene;
    TGroupBox *GroupBox_TurnPoint;
    void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall CheckBox_Click(TObject * Sender);
    void __fastcall ComboBox_Click(TObject * Sender);
    void __fastcall LblE3_KeyPress(TObject * Sender,  char &Key);
    void __fastcall ScrollBar_Change(TObject * Sender);
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
    void __fastcall Edit_ResolutionHKeyPress(TObject * Sender,const char &Key);
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
  private:			// User declarations
     bool SP_IsChkSum;
  public:			// User declarations
     __fastcall TSharpnessV2Form(TComponent * Owner);
    /*
       Sharpness �����ϥΪ��ܼ�
       AbstSP:�O�@��class,�֦��i�Ǧ^Sharpness Address���禡
       OSP: �ŧi��AbstSP�κA���ܼ�
       cb: ��checkbox����ҹ�����address
       ChkB: �㦳checkbox����ҹ�������������Paddress
       scrlb: ��ScrollBar����ҹ�����address
       ScrlB: �㦳ScrollBar����ҹ�������������Paddress
       ChkB: �㦳checkbox����ҹ�������������Paddress
       TBit,TLUT: ���۩w��Address class,�ԲӤ��e�Ѧ�Address_type.h
       _CHKB,_ScrollBar: ���۩w��class, ���t�ϧΤ�������P��m���Ѽ�,�Ա��Ѧ�MainForm.h
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

    TLUT *SP_addr;		//lookup table��address
    int SP_lut[32];		//lookup table
    bool SP_Chg;		//�Ψӳ]�w��������O�_�i�g�J��flag
    int LUT_g[32];
    int gain_flag;
    void Clear_LUT(bool type);	//�M��table�����W�����I
    bool Load_SP(String Fpath);

    void SP_LUT_FuncEnable(bool);
};
//---------------------------------------------------------------------------
extern PACKAGE TSharpnessV2Form *SharpnessV2Form;
//---------------------------------------------------------------------------


#endif

