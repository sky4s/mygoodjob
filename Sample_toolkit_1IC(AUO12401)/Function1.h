//---------------------------------------------------------------------------

#ifndef Function1H
#define Function1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "Unit1.h"
#include "Engineering.h"
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>

//---------------------------------------------------------------------------

//Abstract class of FunctionForm
class AbstFunc
{
        public:
                //frc_dg
                virtual TBit* SetFrcDgChkBx()=0;
                virtual TBit* SetFrcDgCboBx()=0;
                virtual TBit* SetFrcDgLblE()=0;

                //P-state
                virtual TBit* SetPstateChkBx()=0;
                virtual TBit* SetPstateCboBx()=0;
                virtual TBit2* SetPstateLblE2()=0;

                //AGBS
                virtual TBit* SetAGBSChkBx()=0;
                virtual TBit* SetAGBSCboBx()=0;
                virtual TBit2* SetAGBSLblE2()=0;

                //OD
                virtual TBit* SetODChkBx()=0;
                virtual TBit* SetODCboBx()=0;
                virtual TBit2* SetODCboBx2()=0;
                virtual TBit* SetODScrollBar()=0;

                //DG LUT
                virtual TLUT* SetDGLUT()=0;
                virtual TLUT* SetODLUT1()=0;
                virtual TLUT* SetODLUT2()=0;

                int PstateChkBox_Nbr ;       //Number of CheckBox in Pstate page
                int PstateCboBox_Nbr;       //Number of ComboBox in Pstate page
                int PstateLblE2_Nbr;       //Number of LabeledEdit2 in Pstate page

                int AGBSChkBox_Nbr;       //Number of CheckBox in AGBS page
                int AGBSCboBox_Nbr;       //Number of ComboBox in AGBS page
                int AGBSLblE2_Nbr;       //Number of LabeledEdit2 in AGBS page

                int FrcDgChkBox_Nbr;       //Number of CheckBox in FrcDg page
                int FrcDgCboBox_Nbr;       //Number of ComboBox in FrcDg page
                int FrcDgLblE_Nbr;       //Number of LabeledEdit in FrcDg page

                int ODChkBox_Nbr;          //Number of CheckBox in OD page
                int ODCboBox_Nbr;          //Number of ComboBox in OD page
                int ODCboBox2_Nbr;         //Number of ComboBox2 in OD page
                int ODScrollBar_Nbr;       //Number of ScrollBar in OD page
};

class TFunctionForm1 : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *LoadDialog;
        TSaveDialog *SaveDialog;
        TPageControl *pc_Function;
        TTabSheet *ts_frc_gamma;
        TGroupBox *GroupBox1;
        TLabel *Label3;
        TCheckBox *CheckBox5;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox7;
        TComboBox *ComboBox3;
        TLabeledEdit *LabeledEdit8;
        TGroupBox *GroupBox2;
        TStringGrid *sg_dg;
        TButton *btn_dg_read;
        TButton *btn_dg_wrt;
        TButton *btn_dg_save;
        TButton *btn_dg_load;
        TCheckBox *CheckBox8;
        TCheckBox *CheckBox9;
        TBitBtn *Btn_FRC_DG_reload;
        TTabSheet *ts_p_state;
        TLabel *Label1;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TComboBox *ComboBox1;
        TLabeledEdit *LabeledEdit1;
        TLabeledEdit *LabeledEdit2;
        TLabeledEdit *LabeledEdit3;
        TLabeledEdit *LabeledEdit4;
        TBitBtn *Btn_Pstate_reload;
        TTabSheet *ts_agbs;
        TLabel *Label2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox4;
        TComboBox *ComboBox2;
        TLabeledEdit *LabeledEdit5;
        TLabeledEdit *LabeledEdit6;
        TLabeledEdit *LabeledEdit7;
        TBitBtn *Btn_AGBS_reload;
        TTabSheet *TabSheet1;
        TCheckBox *CheckBox10;
        TCheckBox *CheckBox11;
        TCheckBox *CheckBox12;
        TComboBox *ComboBox4;
        TLabel *Label4;
        TComboBox *ComboBox5;
        TLabel *Label5;
        TComboBox *ComboBox6;
        TComboBox *ComboBox7;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label10;
        TScrollBar *ScrollBar1;
        TScrollBar *ScrollBar2;
        TScrollBar *ScrollBar3;
        TStaticText *StaticText1;
        TStaticText *StaticText2;
        TStaticText *StaticText3;
        TBitBtn *Btn_OD_reload;
        TPageControl *PageControl1;
        TTabSheet *TabSheet2;
        TTabSheet *TabSheet3;
        TStringGrid *sg_od1;
        TButton *btn_od1_read;
        TButton *btn_od1_write;
        TButton *btn_od1_save;
        TButton *btn_od1_load;
        TStringGrid *sg_od2;
        TButton *btn_od2_read;
        TButton *btn_od2_write;
        TButton *btn_od2_save;
        TButton *btn_od2_load;
        TLabel *Label11;
        TStaticText *dg_writechk;
        TLabel *Label12;
        TStaticText *dg_readchk;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall btn_dg_wrtClick(TObject *Sender);
        void __fastcall btn_dg_readClick(TObject *Sender);
        void __fastcall btn_dg_loadClick(TObject *Sender);
        void __fastcall btn_dg_saveClick(TObject *Sender);

        void __fastcall Pstate_CheckBox_Click(TObject *Sender);
        void __fastcall Pstate_ComboBox_Click(TObject *Sender);
        void __fastcall Pstate_LblEdit2_KeyPress(TObject *Sender, char &Key);

        void __fastcall AGBS_CheckBox_Click(TObject *Sender);
        void __fastcall AGBS_ComboBox_Click(TObject *Sender);
        void __fastcall AGBS_LblEdit2_KeyPress(TObject *Sender, char &Key);
        void __fastcall OD_CheckBox_Click(TObject *Sender);
        void __fastcall OD_ComboBox_Click(TObject *Sender);
        void __fastcall OD_ComboBox2_Click(TObject *Sender);
        void __fastcall OD_ScrollBar_Scroll(TObject *Sender,TScrollCode ScrollCode, int &ScrollPos);

        void __fastcall FrcDg_CheckBox_Click(TObject *Sender);
        void __fastcall FrcDg_ComboBox_Click(TObject *Sender);
        void __fastcall FrcDg_LblEdit_KeyPress(TObject *Sender, char &Key);
        void __fastcall Btn_FRC_DG_reloadClick(TObject *Sender);
        void __fastcall Btn_Pstate_reloadClick(TObject *Sender);
        void __fastcall Btn_AGBS_reloadClick(TObject *Sender);
        void __fastcall Btn_OD_reloadClick(TObject *Sender);
        void __fastcall btn_od1_loadClick(TObject *Sender);
        void __fastcall btn_od2_readClick(TObject *Sender);
        void __fastcall btn_od1_saveClick(TObject *Sender);
        void __fastcall btn_od2_saveClick(TObject *Sender);
        void __fastcall btn_od1_readClick(TObject *Sender);
        void __fastcall btn_od2_loadClick(TObject *Sender);
        void __fastcall btn_od1_writeClick(TObject *Sender);
        void __fastcall btn_od2_writeClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);

private:	// User declarations
public:		// User declarations
        __fastcall TFunctionForm1(TComponent* Owner);

        AbstFunc* OFunc;

        //P-state parameter declare
        TBit* Pstate_cb;
        _CHKB** PstateChkB;

        TBit* Pstate_cbo;
        _CBOB** PstateCboB;

        TBit2* Pstate_lble2;
        _LBLE2** PstateLblE2;

        //Aging Bist parameter declare
        TBit* AGBS_cb;
        _CHKB** AGBSChkB;

        TBit* AGBS_cbo;
        _CBOB** AGBSCboB;

        TBit2* AGBS_lble2;
        _LBLE2** AGBSLblE2;

        // FRC DG
        TBit* FrcDg_cb;
        _CHKB** FrcDgChkB;

        TBit* FrcDg_cbo;
        _CBOB** FrcDgCboB;

        TBit* FrcDg_lble;
        _LBLE** FrcDgLblE;

        //OD
        TBit* OD_cb;
        _CHKB** ODChkB;

        TBit* OD_cbo;
        _CBOB** ODCboB;

        TBit2* OD_cbo2;
        _CBOB2** ODCboB2;

        TBit* OD_ScrlB;
        _ScrollBar** ODScrlB;

        TLUT* Addr_DgLUT;
        TLUT* Addr_ODLUT1;
        TLUT* Addr_ODLUT2;

        bool Func_Chg;    //用來設定在FormCreate與reload時, OnClick與Onchange類的函式不動作
};
//---------------------------------------------------------------------------
extern PACKAGE TFunctionForm1 *FunctionForm1;

//---------------------------------------------------------------------------





#endif
