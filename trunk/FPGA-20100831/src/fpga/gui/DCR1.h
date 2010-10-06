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
#include <Graphics.hpp>
#include <fpga/includeall.h>
//---------------------------------------------------------------------------
//Abstract class of DCR
class AbstDCR
{
        public:
                //DCR setting
                virtual TBit* SetChkBx()=0;
                virtual TBit* SetCboBx()=0;

                virtual TBit* SetScrollBar()=0;
                virtual TBit2* SetScrollBar2()=0;

                virtual TLUT* SetLUT()=0;
                virtual TBit3* SetLblE3()=0;

                 virtual TBit2* SetDCRLblE2()=0;

                //ALS SMBUS
                virtual TBit* SetALSChkBx()=0;
                virtual TBit* SetALSCboBx()=0;
                virtual TBit* SetALSScrollBar()=0;
                //HDR
                virtual TBit* SetHDRCboBx()=0;
                virtual TBit* SetHDRScrollBar()=0;
                virtual TBit2* SetHDRScrollBar2()=0;
                virtual TBit2* SetHDRLblE2()=0;
                
                virtual String DCR_BL_EN_Name()=0;  // 20100608 return the name of BL_EN register
                virtual String DCR_GLT_EN_Name()=0; // 20100608 return the name of GLT_EN register

                int DCRScrollBar_Nbr;
                int DCRScrollBar2_Nbr;

                int DCRCboBox_Nbr;
                int DCRChkBox_Nbr;
                int DCRLblE3_Nbr;   
                int DCRLblE2_Nbr;

                int ALSScrollBar_Nbr;
                int ALSChkBox_Nbr;
                int ALSCboBox_Nbr;

                int HDRCboBox_Nbr;
                int HDRScrollBar_Nbr;
                int HDRScrollBar2_Nbr;
                int HDRLblE2_Nbr;
                int DCRLUT_Nbr;    // 20100608 set number of DCR table
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
        TGroupBox *GroupBox6;
        TLabel *Label10;
        TLabel *Label11;

        TScrollBar *ScrollBar10;
        TStaticText *StaticText10;

        TScrollBar *ScrollBar11;
        TStaticText *StaticText11;
        TTabSheet *TabSheet4;
        TTabSheet *TabSheet3;
        TGroupBox *GroupBox8;
        TLabel *Label6;
        TLabel *Label7;
        TScrollBar *ScrollBar6;
        TStaticText *StaticText6;
        TScrollBar *ScrollBar7;
        TStaticText *StaticText7;
        TCheckBox *CheckBox11;
        TGroupBox *GroupBox9;
        TLabel *Label18;
        TLabel *Label19;
        TLabel *Label20;
        TLabel *Label21;
        TLabel *Label22;
        TLabel *Label23;
        TLabel *Label24;
        TLabel *Label25;
        TLabel *Label26;
        TLabel *Label27;
        TLabel *Label28;
        TLabel *Label29;
        TLabel *Label30;
        TLabel *Label31;
        TCheckBox *CheckBox24;
        TCheckBox *CheckBox23;
        TScrollBar *ScrollBar14;
        TScrollBar *ScrollBar15;
        TScrollBar *ScrollBar16;
        TScrollBar *ScrollBar17;
        TScrollBar *ScrollBar18;
        TScrollBar *ScrollBar19;
        TScrollBar *ScrollBar20;
        TScrollBar *ScrollBar21;
        TScrollBar *ScrollBar22;
        TScrollBar *ScrollBar23;
        TScrollBar *ScrollBar24;
        TScrollBar *ScrollBar25;
        TScrollBar *ScrollBar26;
        TScrollBar *ScrollBar27;
        TStaticText *StaticText14;
        TStaticText *StaticText15;
        TStaticText *StaticText16;
        TStaticText *StaticText17;
        TStaticText *StaticText18;
        TStaticText *StaticText19;
        TStaticText *StaticText20;
        TStaticText *StaticText21;
        TStaticText *StaticText22;
        TStaticText *StaticText23;
        TStaticText *StaticText24;
        TStaticText *StaticText25;
        TStaticText *StaticText26;
        TStaticText *StaticText27;
        TScrollBar *ScrollBar28;
        TLabel *Label32;
        TStaticText *StaticText28;
        TTabSheet *TabSheet5;
        TGroupBox *GroupBox10;
        TButton *btn_dcr_lut_read;
        TButton *btn_dcr_lut_write;
        TButton *btn_dcr_lut_save;
        TButton *btn_dcr_lut_load;
        TGroupBox *GroupBox11;
        TGroupBox *GroupBox19;
        TCheckBox *CheckBox12;
        TGroupBox *GroupBox32;
        TGroupBox *GroupBox31;
        TLabel *Label1;
        TScrollBar *ScrollBar1;
        TStaticText *StaticText1;
        TGroupBox *GroupBox5;
        TLabel *Label8;
        TLabel *Label9;
        TScrollBar *ScrollBar8;
        TStaticText *StaticText8;
        TScrollBar *ScrollBar9;
        TStaticText *StaticText9;
        TGroupBox *GroupBox18;
        TLabel *Label41;
        TScrollBar *ScrollBar37;
        TStaticText *StaticText37;
        TGroupBox *GroupBox34;
        TScrollBar *ScrollBar50;
        TScrollBar *ScrollBar51;
        TScrollBar *ScrollBar52;
        TScrollBar *ScrollBar53;
        TScrollBar *ScrollBar54;
        TScrollBar *ScrollBar55;
        TScrollBar *ScrollBar56;
        TScrollBar *ScrollBar57;
        TScrollBar *ScrollBar58;
        TScrollBar *ScrollBar59;
        TScrollBar *ScrollBar60;
        TScrollBar *ScrollBar61;
        TScrollBar *ScrollBar62;
        TScrollBar *ScrollBar63;
        TScrollBar *ScrollBar64;
        TScrollBar *ScrollBar65;
        TScrollBar *ScrollBar66;
        TLabel *Label55;
        TLabel *Label56;
        TLabel *Label57;
        TLabel *Label58;
        TLabel *Label59;
        TLabel *Label60;
        TLabel *Label61;
        TLabel *Label62;
        TLabel *Label63;
        TLabel *Label64;
        TLabel *Label65;
        TLabel *Label66;
        TLabel *Label67;
        TLabel *Label68;
        TLabel *Label69;
        TLabel *Label70;
        TLabel *Label71;
        TStaticText *StaticText50;
        TStaticText *StaticText51;
        TStaticText *StaticText53;
        TStaticText *StaticText54;
        TStaticText *StaticText55;
        TStaticText *StaticText56;
        TStaticText *StaticText57;
        TStaticText *StaticText58;
        TStaticText *StaticText59;
        TStaticText *StaticText60;
        TStaticText *StaticText61;
        TStaticText *StaticText62;
        TStaticText *StaticText63;
        TStaticText *StaticText64;
        TStaticText *StaticText65;
        TStaticText *StaticText66;
        TGroupBox *GroupBox35;
        TGroupBox *GroupBox36;
        TGroupBox *GroupBox37;
        TLabeledEdit *LabeledEdit9;
        TLabeledEdit *LabeledEdit10;
        TGroupBox *GroupBox38;
        TLabeledEdit *LabeledEdit2;
        TLabeledEdit *LabeledEdit3;
        TLabeledEdit *LabeledEdit4;
        TGroupBox *GroupBox39;
        TLabeledEdit *LabeledEdit5;
        TLabeledEdit *LabeledEdit6;
        TLabeledEdit *LabeledEdit7;
        TLabeledEdit *LabeledEdit8;
        TBitBtn *Btn_DCR_reload;
        TComboBox *ComboBox6;
        TComboBox *ComboBox7;
        TComboBox *ComboBox8;
        TComboBox *ComboBox9;
        TComboBox *ComboBox10;
        TLabel *Label72;
        TLabel *Label73;
        TLabel *Label74;
        TLabel *Label75;
        TLabel *Label76;
        TLabeledEdit *LabeledEdit11;
        TLabeledEdit *LabeledEdit12;
        TLabeledEdit *LabeledEdit13;
        TLabeledEdit *LabeledEdit14;
        TLabeledEdit *LabeledEdit15;
        TStaticText *StaticText52;
        TComboBox *ComboBox11;
        TLabel *Label77;
        TLabeledEdit *edt_seq_addr;
        TGroupBox *GroupBox42;
        TLabel *Label2;
        TScrollBar *ScrollBar2;
        TStaticText *StaticText2;
        TLabel *Label79;
        TScrollBar *ScrollBar67;
        TStaticText *StaticText67;
        TGroupBox *GroupBox22;
        TLabel *Label45;
        TScrollBar *ScrollBar41;
        TStaticText *StaticText41;
        TCheckBox *CheckBox5;
        TLabel *Label35;
        TScrollBar *ScrollBar31;
        TStaticText *StaticText31;
        TGroupBox *GroupBox40;
        TCheckBox *CheckBox16;
        TLabel *Label80;
        TGroupBox *GroupBox13;
        TLabel *Label36;
        TScrollBar *ScrollBar32;
        TStaticText *StaticText32;
        TComboBox *ComboBox14;
        TLabel *Label82;
        TCheckBox *CheckBox20;
        TGroupBox *GroupBox43;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label17;
        TComboBox *ComboBox2;
        TComboBox *ComboBox3;
        TComboBox *ComboBox4;
        TGroupBox *GroupBox20;
        TLabel *Label43;
        TLabel *Label44;
        TScrollBar *ScrollBar39;
        TStaticText *StaticText39;
        TScrollBar *ScrollBar40;
        TStaticText *StaticText40;
        TCheckBox *CheckBox22;
        TLabel *Label40;
        TScrollBar *ScrollBar36;
        TStaticText *StaticText36;
        TGroupBox *GroupBox17;
        TLabel *Label42;
        TScrollBar *ScrollBar38;
        TStaticText *StaticText38;
        TGroupBox *GroupBox3;
        TLabel *Label5;
        TLabel *Label14;
        TComboBox *ComboBox1;
        TScrollBar *ScrollBar5;
        TStaticText *StaticText5;
        TGroupBox *GroupBox7;
        TLabel *Label13;
        TLabel *Label12;
        TScrollBar *ScrollBar12;
        TScrollBar *ScrollBar13;
        TStaticText *StaticText12;
        TStaticText *StaticText13;
        TCheckBox *CheckBox9;
        TLabeledEdit *LabeledEdit1;
        TGroupBox *GroupBox4;
        TLabel *Label33;
        TLabel *Label34;
        TScrollBar *ScrollBar29;
        TCheckBox *CheckBox21;
        TScrollBar *ScrollBar30;
        TStaticText *StaticText29;
        TStaticText *StaticText30;
        TGroupBox *GroupBox21;
        TGroupBox *GroupBox23;
        TLabel *Label46;
        TScrollBar *ScrollBar42;
        TStaticText *StaticText42;
        TGroupBox *GroupBox24;
        TLabel *Label47;
        TScrollBar *ScrollBar43;
        TStaticText *StaticText43;
        TGroupBox *GroupBox25;
        TLabel *Label48;
        TScrollBar *ScrollBar44;
        TStaticText *StaticText44;
        TGroupBox *GroupBox26;
        TLabel *Label49;
        TScrollBar *ScrollBar45;
        TStaticText *StaticText45;
        TGroupBox *GroupBox27;
        TLabel *Label50;
        TScrollBar *ScrollBar46;
        TStaticText *StaticText46;
        TGroupBox *GroupBox28;
        TLabel *Label51;
        TScrollBar *ScrollBar47;
        TStaticText *StaticText47;
        TGroupBox *GroupBox29;
        TLabel *Label52;
        TScrollBar *ScrollBar48;
        TStaticText *StaticText48;
        TGroupBox *GroupBox30;
        TLabel *Label53;
        TScrollBar *ScrollBar49;
        TStaticText *StaticText49;
        TGroupBox *GroupBox44;
        TLabel *Label84;
        TComboBox *ComboBox16;
        TLabel *Label81;
        TComboBox *ComboBox13;
        TComboBox *ComboBox12;
        TGroupBox *GroupBox46;
        TCheckBox *CheckBox2;
        TGroupBox *GroupBox33;
        TCheckBox *CheckBox17;
        TGroupBox *GroupBox47;
        TCheckBox *CheckBox3;
        TGroupBox *GroupBox48;
        TCheckBox *CheckBox18;
        TGroupBox *GroupBox45;
        TLabel *Label54;
        TComboBox *ComboBox5;
        TGroupBox *GroupBox49;
        TGroupBox *GroupBox15;
        TLabel *Label38;
        TScrollBar *ScrollBar34;
        TStaticText *StaticText34;
        TGroupBox *GroupBox14;
        TLabel *Label37;
        TScrollBar *ScrollBar33;
        TStaticText *StaticText33;
        TGroupBox *GroupBox16;
        TLabel *Label39;
        TScrollBar *ScrollBar35;
        TStaticText *StaticText35;
        TGroupBox *GroupBox12;
        TLabel *Label83;
        TCheckBox *CheckBox8;
        TComboBox *ComboBox15;

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
        void __fastcall DCR_LblEdit2_KeyPress(TObject *Sender, char &Key);

        void __fastcall ALS_CheckBox_Click(TObject *Sender);
        void __fastcall ALS_ComboBox_Click(TObject *Sender);
        void __fastcall ALS_ScrollBar_Scroll(TObject *Sender, TScrollCode ScrollCode, int &ScrollPos);

        void __fastcall HDR_ComboBox_Click(TObject *Sender);
        void __fastcall HDR_ScrollBar_Scroll(TObject *Sender, TScrollCode ScrollCode, int &ScrollPos);
        void __fastcall HDR_ScrollBar2_Scroll(TObject *Sender, TScrollCode ScrollCode, int &ScrollPos);
        void __fastcall HDR_LblEdit2_KeyPress(TObject *Sender, char &Key);

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

        TBit2* dcr_lble2;
        _LBLE2** DCRLblE2;

        //ALS
        TBit* ALS_cb;
        _CHKB** ALSChkB;
        
        TBit* ALS_cbo;
        _CBOB** ALSCboB;

        TBit* alsScrlB;
        _ScrollBar** ALSScrlB;

        //HDR
        TBit* HDR_cbo;
        _CBOB** HDRCboB;

        TBit* hdrScrlB;
        _ScrollBar** HDRScrlB;

        TBit2* hdrScrlB2;
        _ScrollBar2** HDRScrlB2;

        TBit2* hdr_lble2;
        _LBLE2** HDRLblE2;

        int bl_lut[128];
        int dim_lut[192];
        TLUT* dcr_lut_addr;
        TLUT* Addr_DCRLUT;
        bool DCR_Chg;   //用來設定在FormCreate與reload時,
                        // OnClick與Onchange類的函式不動作

        ////////////// 20100608 Add Function Enable Record & recover function/////////////

        bool DCR_EN_State[2];            // 紀錄DCR table 的 Enable狀態, [0]=>BL_EN, [1]=>GLT_EN
        int DCREN_idx[2];                // 紀錄DCR Enable的CheckBox的index  [0]=>BL_EN, [1]=>GLT_EN
        bool DCR_LUT_RW_start();         // 紀錄enable狀態
        void DCR_LUT_RW_over();          // 回復enable狀態
        void DCR_LUT_FuncEnable(bool);   // 設定DCR lut button是否作用, flag =0 不作用, 反之,作用
        //////////////////////////////////////////////////////////////////////////////////

        void Initial_DCR_table();
        TStringGrid** sg_dcr;
};

//---------------------------------------------------------------------------
extern PACKAGE TDCRForm1 *DCRForm1;

//---------------------------------------------------------------------------

#endif
