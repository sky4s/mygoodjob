//---------------------------------------------------------------------------

#ifndef DCR1H
#define DCR1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Unit1.h"
#include "Engineering.h"
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <Grids.hpp>
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------
//Abstract class of DCR
class AbstDCR
{
        public:
                virtual TBit* SetChkBx()=0;
                virtual TBit* SetCboBx()=0;
                virtual TBit* SetScrollBar()=0;
                virtual TBit2* SetScrollBar2()=0;
                virtual TLUT* SetLUT()=0;
                virtual TBit3* SetLblE3()=0;

                int DCRScrollBar_Nbr;
                int DCRScrollBar2_Nbr;
                int DCRCboBox_Nbr;
                int DCRChkBox_Nbr;
                int DCRLblE3_Nbr;
};

class TDCRForm1 : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox5;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TComboBox *ComboBox2;
        TComboBox *ComboBox3;
        TComboBox *ComboBox4;
        TLabel *Label1;
        TLabel *Label2;
        TScrollBar *ScrollBar1;
        TScrollBar *ScrollBar2;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TGroupBox *GroupBox1;
        TLabel *Label3;
        TCheckBox *CheckBox6;
        TScrollBar *ScrollBar3;
        TStaticText *StaticText3;
        TGroupBox *GroupBox2;
        TLabel *Label4;
        TScrollBar *ScrollBar4;
        TStaticText *StaticText4;
        TCheckBox *CheckBox7;
        TGroupBox *GroupBox3;
        TLabel *Label5;
        TLabel *Label14;
        TComboBox *ComboBox1;
        TScrollBar *ScrollBar5;
        TStaticText *StaticText5;
        TGroupBox *GroupBox4;
        TLabel *Label6;
        TLabel *Label7;
        TScrollBar *ScrollBar6;
        TStaticText *StaticText6;
        TScrollBar *ScrollBar7;
        TStaticText *StaticText7;
        TCheckBox *CheckBox8;
        TGroupBox *GroupBox5;
        TLabel *Label8;
        TLabel *Label9;
        TScrollBar *ScrollBar8;
        TStaticText *StaticText8;
        TScrollBar *ScrollBar9;
        TStaticText *StaticText9;
        TGroupBox *GroupBox6;
        TLabel *Label10;
        TLabel *Label11;
        TScrollBar *ScrollBar10;
        TStaticText *StaticText10;
        TScrollBar *ScrollBar11;
        TStaticText *StaticText11;
        TGroupBox *GroupBox7;
        TLabel *Label13;
        TLabel *Label12;
        TScrollBar *ScrollBar12;
        TScrollBar *ScrollBar13;
        TStaticText *StaticText12;
        TStaticText *StaticText13;
        TCheckBox *CheckBox9;
        TStringGrid *sg_dcr_bl;
        TStringGrid *sg_dcr_dim;
        TButton *btn_dcr_lut_read;
        TButton *btn_dcr_lut_write;
        TButton *btn_dcr_lut_save;
        TButton *btn_dcr_lut_load;
        TBitBtn *Btn_DCR_reload;
        TCheckBox *CheckBox10;

        void __fastcall FormCreate(TObject *Sender);
        void __fastcall DCR_ScrollBar_Scroll(TObject *Sender, TScrollCode ScrollCode, int &ScrollPos);
        void __fastcall DCR_ScrollBar2_Scroll(TObject *Sender, TScrollCode ScrollCode, int &ScrollPos);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall DCR_CheckBox_Click(TObject *Sender);
        void __fastcall DCR_ComboBox_Click(TObject *Sender);
        void __fastcall Btn_DCR_reloadClick(TObject *Sender);
        void __fastcall btn_dcr_lut_readClick(TObject *Sender);
        void __fastcall btn_dcr_lut_writeClick(TObject *Sender);
        void __fastcall btn_dcr_lut_loadClick(TObject *Sender);
        void __fastcall btn_dcr_lut_saveClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall DCRLblE3_KeyPress(TObject *Sender, char &Key);
        
private:	// User declarations
public:		// User declarations
        __fastcall TDCRForm1(TComponent* Owner);

        
        //TDCRForm1 *DCRForm1;
        AbstDCR* ODCR;

        TBit* DCR_cb;
        _CHKB** DCRChkB;

        TBit* DCR_cbo;
        _CBOB** DCRCboB;

        TBit* ScrlB;
        _ScrollBar** DCRScrlB;

        TBit2* ScrlB2;
        _ScrollBar2** DCRScrlB2;

        TBit3* dcr_lble3;
        _LBLE3** DCRLblE3;

        int bl_lut[128];
        int dim_lut[192];
        TLUT* dcr_lut_addr;

        bool DCR_Chg;   //用來設定在FormCreate與reload時, OnClick與Onchange類的函式不動作
};

//---------------------------------------------------------------------------
extern PACKAGE TDCRForm1 *DCRForm1;

//---------------------------------------------------------------------------

#endif
