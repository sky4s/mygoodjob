//---------------------------------------------------------------------------
//    20090903 version
//---------------------------------------------------------------------------

#ifndef TCON1H
#define TCON1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "Unit1.h"
#include <Buttons.hpp>
#include "CSPIN.h"

//---------------------------------------------------------------------------
//Abstract class of TCON
class AbstTCON
{
        public:
                //device
                virtual TBit* SetDevChkBx()=0;
                virtual TBit* SetDevCboBx()=0;
                virtual TBit2* SetDevLblE2()=0;

                //status
                virtual TBit* SetStaCboBx()=0;
                virtual TBit2* SetStaLblE2()=0;

                //Input/Output
                virtual TBit* SetIOChkBx()=0;
                virtual TBit* SetIOCboBx()=0;
                //Driving
                virtual TBit* SetDrvChkBx()=0;
                virtual TBit* SetDrvCboBx()=0;
                virtual TBit2* SetDrvLblE()=0;
                virtual TBit3* SetDrvLblE3()=0; //Add by Michelle 20100625
                //Timing
                virtual TBit2* SetTimLblE2()=0;
		virtual TBit3* SetTimLblE3()=0;

                int DevChkBox_Nbr;        //Number of CheckBox in device page
                int DevCboBox_Nbr;        //Number of ComboBox in device page
                int DevLblE2_Nbr;

                int IOChkBox_Nbr;         //Number of CheckBox in input/output page
                int IOCboBox_Nbr;         //Number of ComboBox in input/output page

                int DrvChkBox_Nbr;        //Number of CheckBox in Driving page
                int DrvCboBox_Nbr;        //Number of ComboBox in Driving page
                int DrvLblE2_Nbr;         //Number of LabeledEdit in Driving page
                int DrvLblE3_Nbr;

                int TimLblE2_Nbr;         //Number of LabeledEdit2 in Timing page
		int TimLblE3_Nbr;
                int StaCboBox_Nbr;
                int StaLblE2_Nbr;
};


class TTCONForm1 : public TForm
{
__published:	// IDE-managed Components
        TPageControl *pc_tcon;
        TTabSheet *ts_tcon_dev;
        TTabSheet *ts_tcon_drive;
        TTabSheet *ts_tcon_inoutp;
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
        TComboBox *ComboBox1;
        TLabel *Label1;
        TComboBox *ComboBox2;
        TLabel *Label3;
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TCheckBox *CheckBox11;
        TCheckBox *CheckBox12;
        TCheckBox *CheckBox13;
        TCheckBox *CheckBox14;
        TCheckBox *CheckBox15;
        TComboBox *ComboBox4;
        TLabel *Label2;
        TLabel *Label5;
        TCheckBox *CheckBox16;
        TCheckBox *CheckBox17;
        TCheckBox *CheckBox18;
        TCheckBox *CheckBox19;
        TCheckBox *CheckBox20;
        TCheckBox *CheckBox21;
        TCheckBox *CheckBox22;
        TCheckBox *CheckBox23;
        TGroupBox *GroupBox3;
        TGroupBox *GroupBox6;
        TGroupBox *GroupBox7;
        TCheckBox *CheckBox32;
        TCheckBox *CheckBox33;
        TCheckBox *CheckBox34;
        TCheckBox *CheckBox35;
        TCheckBox *CheckBox36;
        TCheckBox *CheckBox37;
        TLabel *Label8;
        TComboBox *ComboBox7;
        TComboBox *ComboBox8;
        TComboBox *ComboBox9;
        TComboBox *ComboBox10;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabeledEdit *LabeledEdit1;
        TLabeledEdit *LabeledEdit2;
        TLabeledEdit *LabeledEdit4;
        TLabeledEdit *LabeledEdit5;
        TBitBtn *Btn_TCON_dev_reload;
        TBitBtn *Btn_TCON_drv_reload;
        TBitBtn *Btn_TCON_io_reload;
        TCheckBox *CheckBox40;
        TLabel *Label12;
        TLabel *Label13;
        TComboBox *ComboBox11;
        TComboBox *ComboBox12;
        TTabSheet *TabSheet1;
        TLabel *Label14;
        TComboBox *ComboBox5;
        TCheckBox *CheckBox39;
        TCheckBox *CheckBox38;
        TBitBtn *Btn_TCON_Tim_reload;
        TGroupBox *GroupBox13;
        TLabeledEdit *LabeledEdit6;
        TLabeledEdit *LabeledEdit3;
        TLabeledEdit *LabeledEdit7;
        TLabeledEdit *LabeledEdit8;
        TCheckBox *CheckBox31;
        TPageControl *PageControl2;
        TTabSheet *TabSheet4;
        TTabSheet *TabSheet6;
        TGroupBox *GroupBox4;
        TPageControl *PageControl1;
        TTabSheet *TabSheet2;
        TGroupBox *GroupBox8;
        TLabeledEdit *LabeledEdit13;
        TLabeledEdit *LabeledEdit14;
        TLabeledEdit *LabeledEdit15;
        TLabeledEdit *LabeledEdit16;
        TLabeledEdit *LabeledEdit17;
        TLabeledEdit *LabeledEdit18;
        TLabeledEdit *LabeledEdit19;
        TLabeledEdit *LabeledEdit20;
        TTabSheet *TabSheet3;
        TGroupBox *GroupBox9;
        TLabeledEdit *LabeledEdit21;
        TLabeledEdit *LabeledEdit22;
        TLabeledEdit *LabeledEdit23;
        TLabeledEdit *LabeledEdit24;
        TLabeledEdit *LabeledEdit25;
        TLabeledEdit *LabeledEdit26;
        TLabeledEdit *LabeledEdit27;
        TLabeledEdit *LabeledEdit28;
        TLabeledEdit *LabeledEdit9;
        TLabeledEdit *LabeledEdit10;
        TLabeledEdit *LabeledEdit11;
        TLabeledEdit *LabeledEdit29;
        TLabeledEdit *LabeledEdit30;
        TLabeledEdit *LabeledEdit12;
        TLabeledEdit *LabeledEdit31;
        TGroupBox *GroupBox11;
        TLabeledEdit *LabeledEdit42;
        TCheckBox *CheckBox28;
        TCheckBox *CheckBox29;
        TGroupBox *GroupBox10;
        TLabeledEdit *LabeledEdit43;
        TLabeledEdit *LabeledEdit44;
        TLabeledEdit *LabeledEdit45;
        TLabeledEdit *LabeledEdit46;
        TLabeledEdit *LabeledEdit47;
        TLabeledEdit *LabeledEdit48;
        TLabeledEdit *LabeledEdit49;
        TLabeledEdit *LabeledEdit50;
        TGroupBox *GroupBox14;
        TCheckBox *CheckBox30;
        TCheckBox *CheckBox41;
        TCheckBox *CheckBox42;
        TCheckBox *CheckBox43;
        TCheckBox *CheckBox44;
        TCheckBox *CheckBox45;
        TCheckBox *CheckBox46;
        TCheckBox *CheckBox47;
        TComboBox *ComboBox3;
        TLabel *Label4;
        TComboBox *ComboBox6;
        TLabel *Label15;
        TLabeledEdit *LabeledEdit51;
        TLabeledEdit *LabeledEdit52;
        TLabeledEdit *LabeledEdit53;
        TLabeledEdit *LabeledEdit54;
        TLabeledEdit *LabeledEdit55;
        TLabeledEdit *LabeledEdit56;
        TLabeledEdit *LabeledEdit57;
        TLabeledEdit *LabeledEdit58;
        TLabeledEdit *LabeledEdit59;
        TLabeledEdit *LabeledEdit60;
        TLabeledEdit *LabeledEdit61;
        TLabeledEdit *LabeledEdit62;
        TTabSheet *TabSheet8;
        TTabSheet *TabSheet9;
        TTabSheet *TabSheet10;
        TTabSheet *TabSheet11;
        TGroupBox *GroupBox5;
        TLabeledEdit *LabeledEdit63;
        TLabeledEdit *LabeledEdit64;
        TLabeledEdit *LabeledEdit65;
        TLabeledEdit *LabeledEdit66;
        TLabeledEdit *LabeledEdit71;
        TLabeledEdit *LabeledEdit72;
        TLabeledEdit *LabeledEdit73;
        TLabeledEdit *LabeledEdit74;
        TLabeledEdit *LabeledEdit67;
        TLabeledEdit *LabeledEdit68;
        TLabeledEdit *LabeledEdit69;
        TLabeledEdit *LabeledEdit70;
        TGroupBox *GroupBox15;
        TLabeledEdit *LabeledEdit75;
        TLabeledEdit *LabeledEdit76;
        TLabeledEdit *LabeledEdit77;
        TLabeledEdit *LabeledEdit78;
        TLabeledEdit *LabeledEdit79;
        TLabeledEdit *LabeledEdit80;
        TLabeledEdit *LabeledEdit81;
        TLabeledEdit *LabeledEdit82;
        TGroupBox *GroupBox16;
        TLabeledEdit *LabeledEdit83;
        TLabeledEdit *LabeledEdit84;
        TLabeledEdit *LabeledEdit85;
        TLabeledEdit *LabeledEdit86;
        TLabeledEdit *LabeledEdit87;
        TLabeledEdit *LabeledEdit88;
        TLabeledEdit *LabeledEdit89;
        TLabeledEdit *LabeledEdit90;
        TGroupBox *GroupBox17;
        TLabeledEdit *LabeledEdit91;
        TLabeledEdit *LabeledEdit92;
        TLabeledEdit *LabeledEdit93;
        TLabeledEdit *LabeledEdit94;
        TLabeledEdit *LabeledEdit95;
        TLabeledEdit *LabeledEdit96;
        TLabeledEdit *LabeledEdit97;
        TLabeledEdit *LabeledEdit98;
        TPageControl *PageControl3;
        TTabSheet *TabSheet7;
        TGroupBox *GroupBox18;
        TLabeledEdit *LabeledEdit99;
        TLabeledEdit *LabeledEdit100;
        TLabeledEdit *LabeledEdit101;
        TLabeledEdit *LabeledEdit102;
        TTabSheet *TabSheet12;
        TGroupBox *GroupBox19;
        TLabeledEdit *LabeledEdit111;
        TLabeledEdit *LabeledEdit112;
        TLabeledEdit *LabeledEdit113;
        TLabeledEdit *LabeledEdit114;
        TTabSheet *TabSheet13;
        TGroupBox *GroupBox20;
        TLabeledEdit *LabeledEdit123;
        TLabeledEdit *LabeledEdit124;
        TLabeledEdit *LabeledEdit125;
        TLabeledEdit *LabeledEdit126;
        TLabeledEdit *LabeledEdit127;
        TLabeledEdit *LabeledEdit128;
        TLabeledEdit *LabeledEdit129;
        TLabeledEdit *LabeledEdit130;
        TTabSheet *TabSheet14;
        TGroupBox *GroupBox21;
        TLabeledEdit *LabeledEdit131;
        TLabeledEdit *LabeledEdit132;
        TLabeledEdit *LabeledEdit133;
        TLabeledEdit *LabeledEdit134;
        TLabeledEdit *LabeledEdit135;
        TLabeledEdit *LabeledEdit136;
        TLabeledEdit *LabeledEdit137;
        TLabeledEdit *LabeledEdit138;
        TTabSheet *TabSheet15;
        TGroupBox *GroupBox22;
        TLabeledEdit *LabeledEdit139;
        TLabeledEdit *LabeledEdit140;
        TLabeledEdit *LabeledEdit141;
        TLabeledEdit *LabeledEdit142;
        TLabeledEdit *LabeledEdit143;
        TLabeledEdit *LabeledEdit144;
        TLabeledEdit *LabeledEdit145;
        TLabeledEdit *LabeledEdit146;
        TTabSheet *TabSheet16;
        TGroupBox *GroupBox23;
        TLabeledEdit *LabeledEdit147;
        TLabeledEdit *LabeledEdit148;
        TLabeledEdit *LabeledEdit149;
        TLabeledEdit *LabeledEdit150;
        TLabeledEdit *LabeledEdit151;
        TLabeledEdit *LabeledEdit152;
        TLabeledEdit *LabeledEdit153;
        TLabeledEdit *LabeledEdit154;
        TTabSheet *TabSheet17;
        TGroupBox *GroupBox24;
        TGroupBox *GroupBox25;
        TLabeledEdit *LabeledEdit39;
        TLabeledEdit *LabeledEdit40;
        TLabeledEdit *LabeledEdit41;
        TLabeledEdit *LabeledEdit103;
        TLabeledEdit *LabeledEdit104;
        TLabeledEdit *LabeledEdit105;
        TLabeledEdit *LabeledEdit106;
        TLabeledEdit *LabeledEdit107;
        TLabeledEdit *LabeledEdit108;
        TLabeledEdit *LabeledEdit109;
        TLabeledEdit *LabeledEdit110;
        TLabeledEdit *LabeledEdit115;
        TLabeledEdit *LabeledEdit116;
        TTabSheet *TabSheet5;
        TGroupBox *GroupBox12;
        TGroupBox *GroupBox26;
        TGroupBox *GroupBox27;
        TLabeledEdit *LabeledEdit32;
        TLabeledEdit *LabeledEdit33;
        TLabeledEdit *LabeledEdit34;
        TLabeledEdit *LabeledEdit35;
        TLabeledEdit *LabeledEdit36;
        TLabeledEdit *LabeledEdit37;
        TLabeledEdit *LabeledEdit38;
        TLabeledEdit *LabeledEdit117;
        TLabeledEdit *LabeledEdit118;
        TLabeledEdit *LabeledEdit119;
        TLabeledEdit *LabeledEdit120;
        TLabeledEdit *LabeledEdit121;
        TLabeledEdit *LabeledEdit122;
        TLabeledEdit *LabeledEdit155;
        TLabeledEdit *LabeledEdit156;
        TLabeledEdit *LabeledEdit157;
        TLabeledEdit *LabeledEdit158;
        TLabeledEdit *LabeledEdit159;
        TLabeledEdit *LabeledEdit160;
        TLabeledEdit *LabeledEdit161;
        TLabeledEdit *LabeledEdit162;
        TLabeledEdit *LabeledEdit163;
        TLabeledEdit *LabeledEdit164;
        TTabSheet *TabSheet18;
        TGroupBox *GroupBox28;
        TLabeledEdit *LabeledEdit165;
        TLabeledEdit *LabeledEdit166;
        TLabeledEdit *LabeledEdit167;
        TLabeledEdit *LabeledEdit168;
        TLabeledEdit *LabeledEdit169;
        TLabeledEdit *LabeledEdit170;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);

        void __fastcall Dev_CheckBox_Click(TObject *Sender);
        void __fastcall Dev_ComboBox_Click(TObject *Sender);
        void __fastcall Dev_LblEdit2_KeyPress(TObject *Sender, char &Key); //Add by michelle 20100629

        void __fastcall IO_CheckBox_Click(TObject *Sender);
        void __fastcall IO_ComboBox_Click(TObject *Sender);

        void __fastcall Drv_CheckBox_Click(TObject *Sender);
        void __fastcall Drv_ComboBox_Click(TObject *Sender);
        void __fastcall Drv_LblEdit2_KeyPress(TObject *Sender, char &Key);
        void __fastcall Drv_LblEdit3_KeyPress(TObject *Sender, char &Key); //Add by Michelle 20100625

        void __fastcall Tim_LblEdit2_KeyPress(TObject *Sender, char &Key);

        void __fastcall Btn_TCON_dev_reloadClick(TObject *Sender);
        void __fastcall Btn_TCON_drv_reloadClick(TObject *Sender);
        void __fastcall Btn_TCON_io_reloadClick(TObject *Sender);
        void __fastcall Btn_TCON_Tim_reloadClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall TimLblEdit3_KeyPress(TObject *Sender, char &Key);

private:	// User declarations
public:		// User declarations
        __fastcall TTCONForm1(TComponent* Owner);
        void set_address();

        AbstTCON* OTCON;

        //device
        TBit* dev_cb;
        _CHKB** DevChkB;

        TBit* dev_cbo;
        _CBOB** DevCboB;

        TBit2* dev_lble2; // Add by Michelle 20100629
        _LBLE2** DevLblE2;

        //Input Output
        TBit* io_cb;
        _CHKB** IOChkB;

        TBit* io_cbo;
        _CBOB** IOCboB;

        //driving
        TBit* drv_cb;
        _CHKB** DrvChkB;

        TBit* drv_cbo;
        _CBOB** DrvCboB;

        TBit2* drv_lble2;
        _LBLE2** DrvLblE2;

        TBit3* drv_lble3;     // Add by Michelle 20100625
        _LBLE3** DrvLblE3;

        //Timing
        TBit2* tim_lble2;
        _LBLE2** TimLblE2;
		
		//Timing
        TBit3* tim_lble3;
        _LBLE3** TimLblE3;

        bool TCON_Chg;  //用來設定在FormCreate與reload時, OnClick與Onchange類的函式不動作
};


//---------------------------------------------------------------------------
extern PACKAGE TTCONForm1 *TCONForm1;
//---------------------------------------------------------------------------
#endif
