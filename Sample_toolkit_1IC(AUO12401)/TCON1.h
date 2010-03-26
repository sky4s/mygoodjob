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
        TLabel *Label4;
        TComboBox *ComboBox3;
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
        TCheckBox *CheckBox24;
        TCheckBox *CheckBox25;
        TCheckBox *CheckBox26;
        TGroupBox *GroupBox3;
        TGroupBox *GroupBox5;
        TGroupBox *GroupBox6;
        TGroupBox *GroupBox7;
        TCheckBox *CheckBox32;
        TCheckBox *CheckBox33;
        TCheckBox *CheckBox34;
        TCheckBox *CheckBox35;
        TCheckBox *CheckBox36;
        TCheckBox *CheckBox37;
        TCheckBox *CheckBox27;
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
        TCheckBox *CheckBox30;
        TPageControl *PageControl2;
        TTabSheet *TabSheet4;
        TTabSheet *TabSheet5;
        TTabSheet *TabSheet6;
        TGroupBox *GroupBox4;
        TLabel *Label16;
        TPageControl *PageControl1;
        TTabSheet *TabSheet2;
        TGroupBox *GroupBox8;
        TLabel *Label6;
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
        TLabel *Label7;
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
        TGroupBox *GroupBox12;
        TLabeledEdit *LabeledEdit32;
        TLabeledEdit *LabeledEdit33;
        TLabeledEdit *LabeledEdit34;
        TLabeledEdit *LabeledEdit35;
        TLabeledEdit *LabeledEdit36;
        TLabeledEdit *LabeledEdit37;
        TLabeledEdit *LabeledEdit38;
        TGroupBox *GroupBox11;
        TLabeledEdit *LabeledEdit39;
        TLabeledEdit *LabeledEdit40;
        TLabeledEdit *LabeledEdit41;
        TLabeledEdit *LabeledEdit42;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormCreate(TObject *Sender);

        void __fastcall Dev_CheckBox_Click(TObject *Sender);
        void __fastcall Dev_ComboBox_Click(TObject *Sender);

        void __fastcall IO_CheckBox_Click(TObject *Sender);
        void __fastcall IO_ComboBox_Click(TObject *Sender);

        void __fastcall Drv_CheckBox_Click(TObject *Sender);
        void __fastcall Drv_ComboBox_Click(TObject *Sender);
        void __fastcall Drv_LblEdit2_KeyPress(TObject *Sender, char &Key);

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
