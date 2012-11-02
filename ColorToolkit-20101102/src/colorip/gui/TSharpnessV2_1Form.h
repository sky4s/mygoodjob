//---------------------------------------------------------------------------
//  20121101
//  ��s From "TSharpnessV2Form"
//---------------------------------------------------------------------------

#ifndef TSharpnessV2_1FormH
#define TSharpnessV2_1FormH
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
TSharpnessV2_1Form���@�~��TForm�κA��class, ��Sharpness������Interface
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
extern PACKAGE TSharpnessV2_1Form *SharpnessV2_1Form;
//---------------------------------------------------------------------------

#endif




