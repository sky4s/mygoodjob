//---------------------------------------------------------------------------
//   20100608
//   tableÅª¼g¨Ï¥Î TEngineerForm::SetRead_PG »P TEngineerForm::SetWrite_PG
//---------------------------------------------------------------------------

#ifndef ContrastEnhance1H
#define ContrastEnhance1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
#include "Unit1.h"
#include "Engineering.h"
#include <Dialogs.hpp>
#include <Buttons.hpp>

class AbstCE {
  public:
    virtual TBit * SetChkBx() = 0;
    virtual TBit *SetCboBx() = 0;
    virtual TBit *SetScrollBar() = 0;
    virtual TLUT *SetJNDlut() = 0;
    virtual TLUT *SetSTlut() = 0;
    virtual TLUT *SetMAXlut() = 0;
    virtual TLUT *SetMINlut() = 0;
    int CEChkBox_Nbr;
    int CECboBox_Nbr;
    int CEScrollBar_Nbr;
};
//---------------------------------------------------------------------------
class TContrastEnhanceForm1:public TForm {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox3;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TCheckBox *CheckBox3;
    TCheckBox *CheckBox4;
    TCheckBox *CheckBox5;
    TCheckBox *CheckBox6;
    TLabel *Label1;
    TComboBox *ComboBox1;
    TLabel *Label2;
    TComboBox *ComboBox2;
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TGroupBox *GroupBox1;
    TCheckBox *CheckBox7;
    TScrollBar *ScrollBar3;
    TStaticText *StaticText3;
    TGroupBox *GroupBox2;
    TCheckBox *CheckBox8;
    TTabSheet *TabSheet2;
    TTabSheet *TabSheet3;
    TScrollBar *ScrollBar6;
    TStaticText *StaticText6;
    TLabel *Label11;
    TScrollBar *ScrollBar7;
    TStaticText *StaticText7;
    TLabel *Label12;
    TScrollBar *ScrollBar8;
    TStaticText *StaticText8;
    TLabel *Label3;
    TComboBox *ComboBox3;
    TComboBox *ComboBox5;
    TComboBox *ComboBox4;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label8;
    TScrollBar *ScrollBar4;
    TScrollBar *ScrollBar5;
    TLabel *Label9;
    TStaticText *StaticText4;
    TStaticText *StaticText5;
    TLabel *Label10;
    TLabel *Label13;
    TLabel *Label14;
    TScrollBar *ScrollBar9;
    TStaticText *StaticText9;
    TLabel *Label15;
    TScrollBar *ScrollBar10;
    TStaticText *StaticText10;
    TLabel *Label16;
    TLabel *Label17;
    TScrollBar *ScrollBar11;
    TScrollBar *ScrollBar12;
    TStaticText *StaticText11;
    TStaticText *StaticText12;
    TLabel *Label18;
    TLabel *Label19;
    TScrollBar *ScrollBar13;
    TScrollBar *ScrollBar14;
    TStaticText *StaticText13;
    TStaticText *StaticText14;
    TImage *JND_LUT;
    TButton *JND_Write;
    TButton *btn_JND_Clear;
    TStringGrid *sg_JND_LUT;
    TImage *ST_LUT;
    TStringGrid *sg_ST_LUT;
    TButton *ST_Write;
    TButton *btn_ST_Clear;
    TTabSheet *TabSheet4;
    TTabSheet *TabSheet5;
    TImage *MAX_LUT;
    TStringGrid *sg_MAX_LUT;
    TButton *MAX_Write;
    TButton *btn_MAX_Clear;
    TImage *MIN_LUT;
    TStringGrid *sg_MIN_LUT;
    TButton *MIN_Write;
    TButton *btn_MIN_Clear;
    TRadioGroup *rg_ce_mode;
    TButton *btn_CE_load;
    TButton *btn_CE_save;
    TGroupBox *GroupBox4;
    TLabel *Label6;
    TLabel *Label7;
    TScrollBar *ScrollBar1;
    TStaticText *StaticText1;
    TScrollBar *ScrollBar2;
    TStaticText *StaticText2;
    TButton *btn_wrt_all;
    TOpenDialog *OpenDialog1;
    TSaveDialog *SaveDialog1;
    TButton *JND_Read;
    TButton *ST_Read;
    TButton *MAX_Read;
    TButton *MIN_Read;
    TBitBtn *Btn_CE_reload;
    TCheckBox *CheckBox9;
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall CheckBox_Click(TObject * Sender);
    void __fastcall ComboBox_Change(TObject * Sender);
    void __fastcall ScrollBar_Change(TObject * Sender);
    void __fastcall JND_LUTMouseDown(TObject * Sender,
				     TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall JND_WriteClick(TObject * Sender);
    void __fastcall ST_LUTMouseDown(TObject * Sender,
				    TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall MAX_LUTMouseDown(TObject * Sender,
				     TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall MIN_LUTMouseDown(TObject * Sender,
				     TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall ST_WriteClick(TObject * Sender);
    void __fastcall MAX_WriteClick(TObject * Sender);
    void __fastcall MIN_WriteClick(TObject * Sender);
    void __fastcall btn_CE_loadClick(TObject * Sender);
    void __fastcall btn_wrt_allClick(TObject * Sender);
    void __fastcall btn_CE_saveClick(TObject * Sender);
    void __fastcall btn_JND_ClearClick(TObject * Sender);
    void __fastcall btn_ST_ClearClick(TObject * Sender);
    void __fastcall btn_MAX_ClearClick(TObject * Sender);
    void __fastcall btn_MIN_ClearClick(TObject * Sender);
    void __fastcall rg_ce_modeClick(TObject * Sender);
    void __fastcall JND_ReadClick(TObject * Sender);
    void __fastcall ST_ReadClick(TObject * Sender);
    void __fastcall MAX_ReadClick(TObject * Sender);
    void __fastcall MIN_ReadClick(TObject * Sender);
    void __fastcall Btn_CE_reloadClick(TObject * Sender);
    void __fastcall FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift);
    void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
  private:			// User declarations
  public:			// User declarations

     TBit * cb;
    _CHKB **ChkB;

    TBit *cbo;
    _CBOB **CboB;

    TBit *scrlb;
    _ScrollBar **ScrlB;

    TLUT *JND_addr;
    TLUT *ST_addr;
    TLUT *MAX_addr;
    TLUT *MIN_addr;

    AbstCE *OCE;
    bool CE_Chg;

    __fastcall TContrastEnhanceForm1(TComponent * Owner);
    void Clear_JND_LUT(bool type);
    void Clear_ST_LUT(bool type);
    void Clear_MAX_LUT(bool type);
    void Clear_MIN_LUT(bool type);
    bool Load_CEini(String Fpath);

};
//---------------------------------------------------------------------------
extern PACKAGE TContrastEnhanceForm1 *ContrastEnhanceForm1;
//---------------------------------------------------------------------------


#endif

