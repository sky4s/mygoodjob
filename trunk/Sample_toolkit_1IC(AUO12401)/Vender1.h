//---------------------------------------------------------------------------

#ifndef Vender1H
#define Vender1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "Unit1.h"
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
//Abstract class of Vender
class AbstVender
{
        public:
                virtual TBit* SetChkBx()=0;
                virtual TBit* SetCboBx()=0;
                virtual TBit* SetScrollBar()=0;
                virtual TBit2* SetScrollBar2()=0;

                virtual TBit* SetDebugChkBx()=0;
                virtual TBit* SetDebugCboBx()=0;
                virtual TBit2* SetDebugLblE2()=0;

                virtual TBit* SetStaCboBx()=0;
                virtual TBit2* SetStaLblE2()=0;
                virtual TBit2* SetLblE2()=0;

                int VendChkBox_Nbr;
                int VendCboBox_Nbr;
                int VendScrollBar_Nbr;
                int VendScrollBar2_Nbr;
                int VendLblE2_Nbr;
                int DebugChkBox_Nbr;
                int DebugCboBox_Nbr;
                int DebugLblE2_Nbr;
                int VStaCboBox_Nbr;
                int VStaLblE2_Nbr;
};

class TVenderForm1 : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl1;
        TTabSheet *ts_vender;
        TTabSheet *ts_debug;
        TGroupBox *GroupBox1;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TScrollBar *ScrollBar1;
        TScrollBar *ScrollBar2;
        TScrollBar *ScrollBar3;
        TScrollBar *ScrollBar4;
        TComboBox *ComboBox1;
        TComboBox *ComboBox2;
        TComboBox *ComboBox3;
        TComboBox *ComboBox4;
        TComboBox *ComboBox5;
        TComboBox *ComboBox6;
        TComboBox *ComboBox7;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TStaticText *StaticText3;
        TStaticText *StaticText4;
        TBitBtn *Btn_vender_reload;
        TGroupBox *GroupBox14;
        TLabel *Label12;
        TCheckBox *CheckBox5;
        TGroupBox *GroupBox15;
        TLabeledEdit *LabeledEdit3;
        TCheckBox *CheckBox8;
        TLabeledEdit *LabeledEdit4;
        TLabeledEdit *LabeledEdit5;
        TGroupBox *DCR;
        TCheckBox *CheckBox7;
        TCheckBox *CheckBox6;
        TLabeledEdit *LabeledEdit2;
        TComboBox *ComboBox8;
        TGroupBox *GroupBox16;
        TBitBtn *btn_status_refresh;
        TGroupBox *GroupBox17;
        TLabeledEdit *LabeledEdit6;
        TLabeledEdit *LabeledEdit7;
        TLabeledEdit *LabeledEdit8;
        TLabeledEdit *LabeledEdit9;
        TGroupBox *GroupBox18;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TComboBox *ComboBox9;
        TComboBox *ComboBox10;
        TComboBox *ComboBox11;
        TComboBox *ComboBox12;
        TComboBox *ComboBox13;
        TLabeledEdit *LabeledEdit1;
        TBitBtn *btn_debug_reload;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Vend_CheckBox_Click(TObject *Sender);
        void __fastcall Vend_ComboBox_Click(TObject *Sender);
        void __fastcall Vend_ScrollBar_Scroll(TObject *Sender, TScrollCode ScrollCode, int &ScrollPos);
        void __fastcall Vend_ScrollBar2_Scroll(TObject *Sender, TScrollCode ScrollCode, int &ScrollPos);
        void __fastcall Btn_vender_reloadClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall Debug_LblEdit2_KeyPress(TObject *Sender, char &Key);
        void __fastcall Debug_ComboBox_Click(TObject *Sender);
        void __fastcall Debug_CheckBox_Click(TObject *Sender);
        void __fastcall btn_status_refreshClick(TObject *Sender);
        void __fastcall btn_debug_reloadClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
        __fastcall TVenderForm1(TComponent* Owner);

        AbstVender *OVender;

        TBit* Vend_cb;
        _CHKB** VendChkB;

        TBit* Vend_cbo;
        _CBOB** VendCboB;

        TBit* vend_scrlb;
        _ScrollBar** VendScrlB;

        TBit2* vend_scrlb2;
        _ScrollBar2** VendScrlB2;

        TBit* debug_cb;
        _CHKB** DebugChkB;

        TBit* debug_cbo;
        _CBOB** DebugCboB;

        TBit* sta_cbo;
        _CBOB** StaCboB;

        TBit2* sta_lble2;
        _LBLE2** StaLblE2;

        TBit2* debug_lble2;
        _LBLE2** DebugLblE2;

        bool Vend_Chg;
};



//---------------------------------------------------------------------------
extern PACKAGE TVenderForm1 *VenderForm1;
//extern String TCON_DEV;
//---------------------------------------------------------------------------
#endif
