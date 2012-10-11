//---------------------------------------------------------------------------

#ifndef Vender1H
#define Vender1H
//---------------------------------------------------------------------------

//C系統文件

//C++系統文件

//vcl庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
//其他庫頭文件

//本項目內頭文件
#include <colorip/gui_class.h>
#include <addresstype/Address_type.h>
//本項目內gui頭文件


class TVenderForm1:public TForm {
    __published:		// IDE-managed Components
    TPageControl * PageControl1;
    TTabSheet *ts_vender;
    TTabSheet *ts_debug;
    TGroupBox *GroupBox1;
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
    TComboBox *ComboBox1;
    TComboBox *ComboBox2;
    TComboBox *ComboBox3;
    TComboBox *ComboBox4;
    TComboBox *ComboBox5;
    TComboBox *ComboBox6;
    TComboBox *ComboBox7;
    TBitBtn *Btn_vender_reload;
    TGroupBox *GroupBox14;
    TLabel *Label12;
    TCheckBox *CheckBox5;
    TGroupBox *GroupBox15;
    TCheckBox *CheckBox8;
    TGroupBox *DCR;
    TCheckBox *CheckBox7;
    TCheckBox *CheckBox6;
    TComboBox *ComboBox8;
    TBitBtn *btn_debug_reload;
    TLabeledEdit *LabeledEdit3;
    TLabeledEdit *LabeledEdit4;
    TLabeledEdit *LabeledEdit5;
    TCheckBox *CheckBox9;
    TCheckBox *CheckBox10;
    TCheckBox *CheckBox11;
    TComboBox *ComboBox14;
    TLabel *Label8;
    TComboBox *ComboBox15;
    TLabel *Label9;
    TComboBox *ComboBox16;
    TComboBox *ComboBox17;
    TComboBox *ComboBox18;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label18;
    TLabeledEdit *LabeledEdit10;
    TLabeledEdit *LabeledEdit11;
    TLabeledEdit *LabeledEdit1;
    TLabeledEdit *LabeledEdit2;
    TTabSheet *TabSheet1;
    TGroupBox *GroupBox16;
    TBitBtn *btn_status_refresh;
    TGroupBox *GroupBox17;
    TLabeledEdit *LabeledEdit6;
    TLabeledEdit *LabeledEdit7;
    TLabeledEdit *LabeledEdit8;
    TLabeledEdit *LabeledEdit9;
    TLabeledEdit *LabeledEdit12;
    TLabeledEdit *LabeledEdit13;
    TLabeledEdit *LabeledEdit14;
    TLabeledEdit *LabeledEdit15;
    TLabeledEdit *LabeledEdit16;
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
    TLabeledEdit *LabeledEdit17;
    TLabeledEdit *LabeledEdit20;
    TLabeledEdit *LabeledEdit21;
    TComboBox *ComboBox19;
    TLabel *Label19;
    void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall Vend_CheckBox_Click(TObject * Sender);
    void __fastcall Vend_ComboBox_Click(TObject * Sender);
    void __fastcall Vend_ScrollBar_Scroll(TObject * Sender, TScrollCode ScrollCode, int &ScrollPos);
    void __fastcall Vend_ScrollBar2_Scroll(TObject * Sender, TScrollCode ScrollCode,
					   int &ScrollPos);
    void __fastcall Btn_vender_reloadClick(TObject * Sender);
    void __fastcall FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift);
    void __fastcall Debug_LblEdit2_KeyPress(TObject * Sender, char &Key);
    void __fastcall Debug_ComboBox_Click(TObject * Sender);
    void __fastcall Debug_CheckBox_Click(TObject * Sender);
    void __fastcall btn_status_refreshClick(TObject * Sender);
    void __fastcall btn_debug_reloadClick(TObject * Sender);

  private:			// User declarations
  public:			// User declarations
     __fastcall TVenderForm1(TComponent * Owner);

    AbstVender *OVender;

    TBit *Vend_cb;
    _CHKB **VendChkB;

    TBit *Vend_cbo;
    _CBOB **VendCboB;

    TBit *vend_scrlb;
    _ScrollBar **VendScrlB;

    TBit2 *vend_scrlb2;
    _ScrollBar2 **VendScrlB2;

    TBit *debug_cb;
    _CHKB **DebugChkB;

    TBit *debug_cbo;
    _CBOB **DebugCboB;

    TBit *sta_cbo;
    _CBOB **StaCboB;

    TBit2 *sta_lble2;
    _LBLE2 **StaLblE2;

    TBit2 *debug_lble2;
    _LBLE2 **DebugLblE2;

    bool Vend_Chg;
};



//---------------------------------------------------------------------------
extern PACKAGE TVenderForm1 *VenderForm1;
//extern String TCON_DEV;
//---------------------------------------------------------------------------
#endif

