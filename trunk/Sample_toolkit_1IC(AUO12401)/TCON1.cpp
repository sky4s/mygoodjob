//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "TCON1.h"
#include "TCON_12401.h"
#include "Engineering.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CSPIN"
#pragma resource "*.dfm"


//---------------------------------------------------------------------------
__fastcall TTCONForm1::TTCONForm1(TComponent* Owner)
        : TForm(Owner)
{
        TCON_Chg = 0;
}
//---------------------------------------------------------------------------

void __fastcall TTCONForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        delete [] OTCON;
        delete [] dev_cb;
        delete [] DevChkB;

        delete [] dev_cbo;
        delete [] DevCboB;

        delete [] io_cb;
        delete [] IOChkB;

        delete [] io_cbo;
        delete [] IOCboB;

        delete [] drv_cb;
        delete [] DrvChkB;

        delete [] drv_cbo;
        delete [] DrvCboB;

        delete [] drv_lble2;
        delete [] DrvLblE2;

        delete [] tim_lble2;
        delete [] TimLblE2;

        Action = caFree;
        MainForm->TCONFormNULL();
}

//=========================================================================//
//     Device Change                                                       //
//=========================================================================//

void __fastcall TTCONForm1::Dev_CheckBox_Click(TObject *Sender)
{
        if(TCON_Chg==0)
                return;
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (DevChkB[idx]->Chkb->Checked?1:0);
        EngineerForm->SetWrite_Byte(DevChkB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall TTCONForm1::Dev_ComboBox_Click(TObject *Sender)
{
        if(TCON_Chg==0)
                return;
        TComboBox *c = (TComboBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (DevCboB[idx]->Cbob->ItemIndex);
        EngineerForm->SetWrite_Byte(DevCboB[idx]->Addr ,set_val);
}


//=========================================================================//
//     IO Change    (input/ Output)                                        //
//=========================================================================//

void __fastcall TTCONForm1::IO_CheckBox_Click(TObject *Sender)
{
        if(TCON_Chg==0)
                return;
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (IOChkB[idx]->Chkb->Checked?1:0);
        EngineerForm->SetWrite_Byte(IOChkB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall TTCONForm1::IO_ComboBox_Click(TObject *Sender)
{
        if(TCON_Chg==0)
                return;
        TComboBox *c = (TComboBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (IOCboB[idx]->Cbob->ItemIndex);
        EngineerForm->SetWrite_Byte(IOCboB[idx]->Addr ,set_val);
}

//=========================================================================//
//     Driving change                                                      //
//=========================================================================//

void __fastcall TTCONForm1::Drv_CheckBox_Click(TObject *Sender)
{
        if(TCON_Chg==0)
                return;
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (DrvChkB[idx]->Chkb->Checked?1:0);
        EngineerForm->SetWrite_Byte(DrvChkB[idx]->Addr ,set_val);
}

//---------------------------------------------------------------------------

void __fastcall TTCONForm1::Drv_ComboBox_Click(TObject *Sender)
{
        if(TCON_Chg==0)
                return;
        TComboBox *c = (TComboBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (DrvCboB[idx]->Cbob->ItemIndex);
        EngineerForm->SetWrite_Byte(DrvCboB[idx]->Addr ,set_val);
}

//---------------------------------------------------------------------------

void __fastcall TTCONForm1::Drv_LblEdit2_KeyPress(TObject *Sender, char &Key)
{
        TLabeledEdit *c = (TLabeledEdit *)Sender;
        int idx = StrToInt(c->Hint);

        if(Key!=13){  
                DrvLblE2[idx]->Lble->Font->Color = cl3DDkShadow;
                return;
        }
        //Key = 13, «ö¤UEnter
        if(TCON_Chg==0)
                return;

        String tmp_v = DrvLblE2[idx]->Lble->Text;
        if(tmp_v==""){
                tmp_v = "0";
        }

        int set_val;
        set_val = StrToInt(tmp_v);

        unsigned char val1,val2;
        //add Max hint
        if(set_val>=pow(2,DrvLblE2[idx]->Addr.BitNum())){
                AnsiString max = "Max value:"+IntToStr((int)pow(2,DrvLblE2[idx]->Addr.BitNum())-1);
                ShowMessage(max);
                //read value
                EngineerForm->SetRead_Byte(DrvLblE2[idx]->Addr.Byte1, &val1);
                EngineerForm->SetRead_Byte(DrvLblE2[idx]->Addr.Byte2, &val2);
                DrvLblE2[idx]->Lble->Text = (int)val1*DrvLblE2[idx]->Addr.Divide()+val2;
                DrvLblE2[idx]->Lble->Font->Color = clWindowText;
        }else{
                val1 = set_val/DrvLblE2[idx]->Addr.Divide();
                val2 = set_val%DrvLblE2[idx]->Addr.Divide();
                EngineerForm->SetWrite_Byte(DrvLblE2[idx]->Addr.Byte1 ,val1);
                if(DrvLblE2[idx]->Addr.Byte2.BitNum()!=0)
                        EngineerForm->SetWrite_Byte(DrvLblE2[idx]->Addr.Byte2 ,val2);
                DrvLblE2[idx]->Lble->Font->Color = clWindowText;
        }
}
void __fastcall TTCONForm1::TimLblEdit3_KeyPress(TObject *Sender, char &Key)
{
        TLabeledEdit *c = (TLabeledEdit *)Sender;
        int idx = StrToInt(c->Hint);

        if(Key!=13){
                TimLblE3[idx]->Lble->Font->Color = cl3DDkShadow;
                return;
        }
        //Key = 13, «ö¤UEnter
        if(TCON_Chg==0)
                return;

        String tmp_v = TimLblE3[idx]->Lble->Text;
        if(tmp_v==""){
                tmp_v = "0";
        }
        int set_val = StrToInt(tmp_v);
        unsigned char val1, val2, val3;
        //add for Max hint
        if(set_val>=pow(2,TimLblE3[idx]->Addr.BitNum())){
                AnsiString max = "Max value:"+IntToStr((int)pow(2,TimLblE3[idx]->Addr.BitNum()-1));
                ShowMessage(max);
                //read value
                EngineerForm->SetRead_Byte(TimLblE3[idx]->Addr.Byte1, &val1);
                EngineerForm->SetRead_Byte(TimLblE3[idx]->Addr.Byte2, &val2);
                EngineerForm->SetRead_Byte(TimLblE3[idx]->Addr.Byte3, &val3);
                TimLblE3[idx]->Lble->Text = (int)val1*TimLblE3[idx]->Addr.Divide1()
                   +(int)val2*TimLblE3[idx]->Addr.Divide1()+(int)val3;
        }else{
                val1 = set_val/TimLblE3[idx]->Addr.Divide1();
                val2 = (set_val/TimLblE3[idx]->Addr.Divide2())%(int)pow(2,TimLblE3[idx]->Addr.Byte2.BitNum());
                val3 = set_val%TimLblE3[idx]->Addr.Divide2();
                EngineerForm->SetWrite_Byte(TimLblE3[idx]->Addr.Byte1 ,val1);
                if(TimLblE3[idx]->Addr.Byte2.BitNum()!=0)
                        EngineerForm->SetWrite_Byte(TimLblE3[idx]->Addr.Byte2 ,val2);
                if(TimLblE3[idx]->Addr.Byte3.BitNum()!=0)
                        EngineerForm->SetWrite_Byte(TimLblE3[idx]->Addr.Byte3 ,val3);
                TimLblE3[idx]->Lble->Font->Color = clWindowText;
        }
}
//=========================================================================//
//     Timing Change                                                       //
//=========================================================================//

void __fastcall TTCONForm1::Tim_LblEdit2_KeyPress(TObject *Sender, char &Key)
{
        TLabeledEdit *c = (TLabeledEdit *)Sender;
        int idx = StrToInt(c->Hint);

        if(Key!=13){
                TimLblE2[idx]->Lble->Font->Color = cl3DDkShadow;
                return;
        }
        if(TCON_Chg==0)
                return;
        String tmp_v = TimLblE2[idx]->Lble->Text;
        if(tmp_v==""){
                tmp_v = "0";
        }
        int set_val = StrToInt(tmp_v);
        unsigned char val1,val2;
        //add Max hint
        if(set_val>=pow(2,TimLblE2[idx]->Addr.BitNum())){
                AnsiString max = "Max value:"+IntToStr((int)pow(2,TimLblE2[idx]->Addr.BitNum())-1);
                ShowMessage(max);
                //read value
                EngineerForm->SetRead_Byte(TimLblE2[idx]->Addr.Byte1, &val1);
                EngineerForm->SetRead_Byte(TimLblE2[idx]->Addr.Byte2, &val2);
                TimLblE2[idx]->Lble->Text = (int)val1*TimLblE2[idx]->Addr.Divide()+val2;
                TimLblE2[idx]->Lble->Font->Color = clWindowText;
        }else{
                val1 = set_val/TimLblE2[idx]->Addr.Divide();
                val2 = set_val%TimLblE2[idx]->Addr.Divide();
                EngineerForm->SetWrite_Byte(TimLblE2[idx]->Addr.Byte1 ,val1);
                if(TimLblE2[idx]->Addr.Byte2.BitNum()!=0)
                        EngineerForm->SetWrite_Byte(TimLblE2[idx]->Addr.Byte2 ,val2);
                TimLblE2[idx]->Lble->Font->Color = clWindowText;
        }
}
//---------------------------------------------------------------------------
void __fastcall TTCONForm1::FormCreate(TObject *Sender)
{
        int ic_choice;
        String Path;
        if(MainForm->TCON_DEV=="12401"){
                ic_choice = 0;
                Path = "AUO_12401_addr.txt";
        }

        switch(ic_choice)
        {
                case 0:
                OTCON = new TCON_12401;
                break;
        }

        /********************************************************************/
        //                                                                  //
        //  Device page has CheckBox*14 & ComboBox*3 & LebleEdit2*6         //
        //                                                                  //
        //******************************************************************//

        //CheckBox
        dev_cb = OTCON->SetDevChkBx();

        DevChkB = new _CHKB* [OTCON->DevChkBox_Nbr];
        for(int i = 0; i < OTCON->DevChkBox_Nbr; i++)
                DevChkB[i] = new _CHKB;

        DevChkB[0]->Chkb = CheckBox1;
        DevChkB[1]->Chkb = CheckBox2;
        DevChkB[2]->Chkb = CheckBox3;
        DevChkB[3]->Chkb = CheckBox4;
        DevChkB[4]->Chkb = CheckBox5;
        DevChkB[5]->Chkb = CheckBox6;
        DevChkB[6]->Chkb = CheckBox7;
        DevChkB[7]->Chkb = CheckBox8;
        DevChkB[8]->Chkb = CheckBox9;
        DevChkB[9]->Chkb = CheckBox10;

        for(int i = 0; i < OTCON->DevChkBox_Nbr; i++){
                DevChkB[i]->Addr = dev_cb[i];
                DevChkB[i]->Chkb->Visible = DevChkB[i]->Addr.FuncEn();
                DevChkB[i]->Chkb->OnClick = Dev_CheckBox_Click;
                DevChkB[i]->Chkb->Hint = i;
                DevChkB[i]->Chkb->Caption = DevChkB[i]->Addr.Name();
        }

        //ComboBox
        dev_cbo = OTCON->SetDevCboBx();

        DevCboB = new _CBOB* [OTCON->DevCboBox_Nbr];
        for(int i = 0; i < OTCON->DevCboBox_Nbr; i++)
                DevCboB[i] = new _CBOB;

        DevCboB[0]->Cbob = ComboBox1;
        DevCboB[0]->CbobL= Label1;
        DevCboB[1]->Cbob = ComboBox2;
        DevCboB[1]->CbobL= Label3;
        DevCboB[2]->Cbob = ComboBox3;
        DevCboB[2]->CbobL= Label4;

        for(int i = 0; i < OTCON->DevCboBox_Nbr; i++){
                DevCboB[i]->Addr = dev_cbo[i];
                DevCboB[i]->Cbob->Visible = DevCboB[i]->Addr.FuncEn();
                DevCboB[i]->CbobL->Visible = DevCboB[i]->Addr.FuncEn();
                DevCboB[i]->Cbob->OnClick = Dev_ComboBox_Click;
                DevCboB[i]->Cbob->Hint = i;
                DevCboB[i]->CbobL->Caption = DevCboB[i]->Addr.Name();
                DevCboB[i]->Cbob->Text = "";
                if(DevCboB[i]->Addr.FuncEn())
                        for(int j = 0; j< DevCboB[i]->Addr.choice_nbr; j++)     //ComboBox choice
                                DevCboB[i]->Cbob->Items->Add(DevCboB[i]->Addr.choice[j]);
        }


        /********************************************************************/
        //                                                                  //
        //  Input/Output page has CheckBox*17 & ComboBox*1                  //
        //                                                                  //
        //******************************************************************//

         //CheckBox
        io_cb = OTCON->SetIOChkBx();

        IOChkB = new _CHKB* [OTCON->IOChkBox_Nbr];
        for(int i = 0; i < OTCON->IOChkBox_Nbr; i++)
                IOChkB[i] = new _CHKB;

        IOChkB[0]->Chkb = CheckBox11;
        IOChkB[1]->Chkb = CheckBox12;
        IOChkB[2]->Chkb = CheckBox13;
        IOChkB[3]->Chkb = CheckBox14;
        IOChkB[4]->Chkb = CheckBox15;
        IOChkB[5]->Chkb = CheckBox16;
        IOChkB[6]->Chkb = CheckBox17;
        IOChkB[7]->Chkb = CheckBox18;
        IOChkB[8]->Chkb = CheckBox19;
        IOChkB[9]->Chkb = CheckBox20;
        IOChkB[10]->Chkb = CheckBox21;
        IOChkB[11]->Chkb = CheckBox22;
        IOChkB[12]->Chkb = CheckBox23;
        IOChkB[13]->Chkb = CheckBox24;
        IOChkB[14]->Chkb = CheckBox25;
        IOChkB[15]->Chkb = CheckBox26;
        IOChkB[16]->Chkb = CheckBox27;

        for(int i = 0; i < OTCON->IOChkBox_Nbr; i++){
                IOChkB[i]->Addr = io_cb[i];
                IOChkB[i]->Chkb->Visible = IOChkB[i]->Addr.FuncEn();
                IOChkB[i]->Chkb->OnClick = IO_CheckBox_Click;
                IOChkB[i]->Chkb->Hint = i;
                IOChkB[i]->Chkb->Caption = IOChkB[i]->Addr.Name();
        }

        //ComboBox
        io_cbo = OTCON->SetIOCboBx();

        IOCboB = new _CBOB* [OTCON->IOChkBox_Nbr];
        for(int i = 0; i < OTCON->IOChkBox_Nbr; i++)
                IOCboB[i] = new _CBOB;

        IOCboB[0]->Cbob = ComboBox4;
        IOCboB[0]->CbobL= Label2;

        for(int i = 0; i < OTCON->IOCboBox_Nbr; i++){
                IOCboB[i]->Addr = io_cbo[i];
                IOCboB[i]->Cbob->Visible = IOCboB[i]->Addr.FuncEn();
                IOCboB[i]->CbobL->Visible = IOCboB[i]->Addr.FuncEn();
                IOCboB[i]->Cbob->OnClick = IO_ComboBox_Click;
                IOCboB[i]->Cbob->Hint = i;
                IOCboB[i]->CbobL->Caption = IOCboB[i]->Addr.Name();
                IOCboB[i]->Cbob->Text = "";
                if(IOCboB[i]->Addr.FuncEn())
                        for(int j = 0; j< IOCboB[i]->Addr.choice_nbr; j++)     //ComboBox choice
                                IOCboB[i]->Cbob->Items->Add(IOCboB[i]->Addr.choice[j]);
        }

        /*******************************************************************/
        //                                                                 //
        //      Driving Page CheckBox*13 & ComboBox*4 & Edit*5             //
        //                                                                 //
        /*******************************************************************/

        //CheckBox
        drv_cb = OTCON->SetDrvChkBx();

        DrvChkB = new _CHKB* [OTCON->DrvChkBox_Nbr];
        for(int i = 0; i < OTCON->DrvChkBox_Nbr; i++)
                DrvChkB[i] = new _CHKB;

        DrvChkB[0]->Chkb = CheckBox30;
        DrvChkB[1]->Chkb = CheckBox31;
        DrvChkB[2]->Chkb = CheckBox32;
        DrvChkB[3]->Chkb = CheckBox33;
        DrvChkB[4]->Chkb = CheckBox34;
        DrvChkB[5]->Chkb = CheckBox35;
        DrvChkB[6]->Chkb = CheckBox36;
        DrvChkB[7]->Chkb = CheckBox37;
        DrvChkB[8]->Chkb = CheckBox38;
        DrvChkB[9]->Chkb = CheckBox39;
        DrvChkB[10]->Chkb = CheckBox40;

        for(int i = 0; i < OTCON->DrvChkBox_Nbr; i++){
                DrvChkB[i]->Addr = drv_cb[i];
                DrvChkB[i]->Chkb->Visible = DrvChkB[i]->Addr.FuncEn();
                DrvChkB[i]->Chkb->OnClick = Drv_CheckBox_Click;
                DrvChkB[i]->Chkb->Hint = i;
                DrvChkB[i]->Chkb->Caption = DrvChkB[i]->Addr.Name();
        }
        //ComboBox
        drv_cbo = OTCON->SetDrvCboBx();

        DrvCboB = new _CBOB* [OTCON->DrvCboBox_Nbr];
        for(int i = 0; i < OTCON->DrvCboBox_Nbr; i++)
                DrvCboB[i] = new _CBOB;

        DrvCboB[0]->Cbob = ComboBox7;
        DrvCboB[0]->CbobL= Label8;
        DrvCboB[1]->Cbob = ComboBox8;
        DrvCboB[1]->CbobL= Label9;
        DrvCboB[2]->Cbob = ComboBox9;
        DrvCboB[2]->CbobL= Label10;
        DrvCboB[3]->Cbob = ComboBox10;
        DrvCboB[3]->CbobL= Label11;
        DrvCboB[4]->Cbob = ComboBox11;
        DrvCboB[4]->CbobL= Label12;
        DrvCboB[5]->Cbob = ComboBox12;
        DrvCboB[5]->CbobL= Label13;
        DrvCboB[6]->Cbob = ComboBox5;
        DrvCboB[6]->CbobL= Label14;

        for(int i = 0; i < OTCON->DrvCboBox_Nbr; i++){
                DrvCboB[i]->Addr = drv_cbo[i];
                DrvCboB[i]->Cbob->Visible = DrvCboB[i]->Addr.FuncEn();
                DrvCboB[i]->Cbob->OnClick = Drv_ComboBox_Click;
                DrvCboB[i]->Cbob->Hint = i;
                DrvCboB[i]->CbobL->Caption = DrvCboB[i]->Addr.Name();
                DrvCboB[i]->Cbob->Text = "";
                if(DrvCboB[i]->Addr.FuncEn())
                        for(int j = 0; j< DrvCboB[i]->Addr.choice_nbr; j++)     //ComboBox choice
                                DrvCboB[i]->Cbob->Items->Add(DrvCboB[i]->Addr.choice[j]);
        }

        //Edit
        drv_lble2 = OTCON->SetDrvLblE();

        DrvLblE2 = new _LBLE2* [OTCON->DrvLblE2_Nbr];
        for(int i = 0; i < OTCON->DrvLblE2_Nbr; i++)
                DrvLblE2[i] = new _LBLE2;

        DrvLblE2[0]->Lble = LabeledEdit1;
        DrvLblE2[1]->Lble = LabeledEdit2;
        DrvLblE2[2]->Lble = LabeledEdit4;
        DrvLblE2[3]->Lble = LabeledEdit5;

        for(int i = 0; i < OTCON->DrvLblE2_Nbr; i++){
                DrvLblE2[i]->Addr = drv_lble2[i];
                DrvLblE2[i]->Lble->Visible = DrvLblE2[i]->Addr.FuncEn();
                //DrvLblE2[i]->Lble->OnChange = Drv_LblEdit2_Change;
                DrvLblE2[i]->Lble->OnKeyPress = Drv_LblEdit2_KeyPress;
                DrvLblE2[i]->Lble->Hint = i;
                DrvLblE2[i]->Lble->EditLabel->Caption = DrvLblE2[i]->Addr.Name();
                DrvLblE2[i]->Lble->Text = 0;
        }

        /*****************************************************************/
        //                                                               //
        //   Timing Page  LabelEdit2*37                                  //
        //                                                               //
        /*****************************************************************/

        //LabeledEdit2
        tim_lble2 = OTCON->SetTimLblE2();

        TimLblE2 = new _LBLE2* [OTCON->TimLblE2_Nbr];
        for(int i = 0; i < OTCON->TimLblE2_Nbr; i++)
                TimLblE2[i] = new _LBLE2;

        TimLblE2[0]->Lble = LabeledEdit3;
        TimLblE2[1]->Lble = LabeledEdit6;
        TimLblE2[2]->Lble = LabeledEdit7;
        TimLblE2[3]->Lble = LabeledEdit8;
        //Normal
        TimLblE2[4]->Lble = LabeledEdit9;
        TimLblE2[5]->Lble = LabeledEdit10;
        TimLblE2[6]->Lble = LabeledEdit11;
        TimLblE2[7]->Lble = LabeledEdit12;
        //Frame 60
        TimLblE2[8]->Lble = LabeledEdit13;
        TimLblE2[9]->Lble = LabeledEdit14;
        TimLblE2[10]->Lble = LabeledEdit15;
        TimLblE2[11]->Lble = LabeledEdit16;

        //Fix Gate On
        TimLblE2[12]->Lble = LabeledEdit17;
        TimLblE2[13]->Lble = LabeledEdit18;
        TimLblE2[14]->Lble = LabeledEdit19;
        TimLblE2[15]->Lble = LabeledEdit20;
        //Frame 40
        TimLblE2[16]->Lble = LabeledEdit21;
        TimLblE2[17]->Lble = LabeledEdit22;
        TimLblE2[18]->Lble = LabeledEdit23;
        TimLblE2[19]->Lble = LabeledEdit24;
        //Fix Gate On
        TimLblE2[20]->Lble = LabeledEdit25;
        TimLblE2[21]->Lble = LabeledEdit26;
        TimLblE2[22]->Lble = LabeledEdit27;
        TimLblE2[23]->Lble = LabeledEdit28;

        //PreCharge
        TimLblE2[24]->Lble = LabeledEdit29;
        TimLblE2[25]->Lble = LabeledEdit30;
        TimLblE2[26]->Lble = LabeledEdit31;

        //goa
        TimLblE2[27]->Lble = LabeledEdit32;
        TimLblE2[28]->Lble = LabeledEdit33;
        TimLblE2[29]->Lble = LabeledEdit34;
        TimLblE2[30]->Lble = LabeledEdit35;
        TimLblE2[31]->Lble = LabeledEdit36;
        TimLblE2[32]->Lble = LabeledEdit37;
        TimLblE2[33]->Lble = LabeledEdit38;

         //2g1d
        TimLblE2[34]->Lble = LabeledEdit39;
        TimLblE2[35]->Lble = LabeledEdit40;
        TimLblE2[36]->Lble = LabeledEdit41;

        for(int i = 0; i < OTCON->TimLblE2_Nbr; i++){
                TimLblE2[i]->Addr = tim_lble2[i];
                TimLblE2[i]->Lble->Visible = TimLblE2[i]->Addr.FuncEn();
                TimLblE2[i]->Lble->OnKeyPress = Tim_LblEdit2_KeyPress;
                TimLblE2[i]->Lble->Hint = i;
                TimLblE2[i]->Lble->EditLabel->Caption = TimLblE2[i]->Addr.Name();
                TimLblE2[i]->Lble->Text = 0;
        }
		
	//LabeledEdit3
        tim_lble3 = OTCON->SetTimLblE3();

        TimLblE3 = new _LBLE3* [OTCON->TimLblE3_Nbr];
        for(int i = 0; i < OTCON->TimLblE3_Nbr; i++)
                TimLblE3[i] = new _LBLE3;

         //TimLblE3[0]->Lble = LabeledEdit42;
         for(int i = 0; i < OTCON->TimLblE3_Nbr; i++){
                TimLblE3[i]->Addr = tim_lble3[i];
                TimLblE3[i]->Lble->Visible = TimLblE3[i]->Addr.FuncEn();
                TimLblE3[i]->Lble->Hint = i;
                TimLblE3[i]->Lble->EditLabel->Caption = TimLblE3[i]->Addr.Name();
                TimLblE3[i]->Lble->OnKeyPress = TimLblEdit3_KeyPress;
                TimLblE3[i]->Lble->Text = 0;
        }
        TCON_Chg = 1;
}
//---------------------------------------------------------------------------



void __fastcall TTCONForm1::Btn_TCON_dev_reloadClick(TObject *Sender)
{
        Btn_TCON_dev_reload->Enabled = false;
        TCON_Chg = 0;
        unsigned char read_val;
        for(int i = 0; i < OTCON->DevChkBox_Nbr; i++){
                if(DevChkB[i]->Chkb->Visible==true){
                        EngineerForm->SetRead_Byte(DevChkB[i]->Addr, &read_val);
                        if(read_val==1)
                                DevChkB[i]->Chkb->Checked = 1;
                        else if(read_val==0)
                                DevChkB[i]->Chkb->Checked = 0;
                        else
                                ShowMessage("device CheckBox read error:"+IntToStr(read_val));
                }
        }
        for(int i = 0; i < OTCON->DevCboBox_Nbr; i++){
                if(DevCboB[i]->Cbob->Visible==true){
                        EngineerForm->SetRead_Byte(DevCboB[i]->Addr, &read_val);
                        DevCboB[i]->Cbob->ItemIndex = read_val;
                }
        }

        TCON_Chg = 1;
        Btn_TCON_dev_reload->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TTCONForm1::Btn_TCON_drv_reloadClick(TObject *Sender)
{
        Btn_TCON_drv_reload->Enabled = false;
        TCON_Chg = 0;
        unsigned char read_val;
        for(int i = 0; i < OTCON->DrvChkBox_Nbr; i++){
                if(DrvChkB[i]->Chkb->Visible==true){
                        EngineerForm->SetRead_Byte(DrvChkB[i]->Addr, &read_val);
                        if(read_val==1)
                                DrvChkB[i]->Chkb->Checked = 1;
                        else if(read_val==0)
                                DrvChkB[i]->Chkb->Checked = 0;
                        else
                                ShowMessage("device CheckBox read error:"+IntToStr(read_val));
                }
        }
        for(int i = 0; i < OTCON->DrvCboBox_Nbr; i++){
                if(DrvCboB[i]->Cbob->Visible==true){
                        EngineerForm->SetRead_Byte(DrvCboB[i]->Addr, &read_val);
                        DrvCboB[i]->Cbob->ItemIndex = read_val;
                }
        }
        unsigned char read_val1,read_val2;
        for(int i = 0; i < OTCON->DrvLblE2_Nbr; i++){
                if(DrvLblE2[i]->Lble->Visible==true){
                        EngineerForm->SetRead_Byte(DrvLblE2[i]->Addr.Byte1, &read_val1);
                        EngineerForm->SetRead_Byte(DrvLblE2[i]->Addr.Byte2, &read_val2);
                        DrvLblE2[i]->Lble->Text = (int)read_val1*DrvLblE2[i]->Addr.Divide()+read_val2;
                        DrvLblE2[i]->Lble->Font->Color = clWindowText;
                }
        }
        TCON_Chg = 1;
        Btn_TCON_drv_reload->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TTCONForm1::Btn_TCON_io_reloadClick(TObject *Sender)
{
        Btn_TCON_io_reload->Enabled = false;
        TCON_Chg = 0;
        unsigned char read_val;
        for(int i = 0; i < OTCON->IOChkBox_Nbr; i++){
                if(IOChkB[i]->Chkb->Visible==true){
                        EngineerForm->SetRead_Byte(IOChkB[i]->Addr, &read_val);
                        if(read_val==1)
                                IOChkB[i]->Chkb->Checked = 1;
                        else if(read_val==0)
                                IOChkB[i]->Chkb->Checked = 0;
                        else
                                ShowMessage("device CheckBox read error:"+IntToStr(read_val));
                }
        }
        for(int i = 0; i < OTCON->IOCboBox_Nbr; i++){
                if(IOCboB[i]->Cbob->Visible==true){
                        EngineerForm->SetRead_Byte(IOCboB[i]->Addr, &read_val);
                        IOCboB[i]->Cbob->ItemIndex = read_val;
                }
        }
        TCON_Chg = 1;
        Btn_TCON_io_reload->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TTCONForm1::Btn_TCON_Tim_reloadClick(TObject *Sender)
{
        Btn_TCON_Tim_reload->Enabled = false;
        unsigned char read_val1,read_val2,read_val3;
        for(int i = 0; i < OTCON->TimLblE2_Nbr; i++){
                if(TimLblE2[i]->Lble->Visible==true){
                        EngineerForm->SetRead_Byte(TimLblE2[i]->Addr.Byte1, &read_val1);
                        EngineerForm->SetRead_Byte(TimLblE2[i]->Addr.Byte2, &read_val2);
                        TimLblE2[i]->Lble->Text = (int)read_val1*TimLblE2[i]->Addr.Divide()+read_val2;
                        TimLblE2[i]->Lble->Font->Color = clWindowText;
                }
        }

        for(int i = 0; i < OTCON->TimLblE3_Nbr; i++){
                if(TimLblE3[i]->Lble->Visible==true){
                        EngineerForm->SetRead_Byte(TimLblE3[i]->Addr.Byte1, &read_val1);
                        EngineerForm->SetRead_Byte(TimLblE3[i]->Addr.Byte2, &read_val2);
                        EngineerForm->SetRead_Byte(TimLblE3[i]->Addr.Byte3, &read_val3);
                        TimLblE3[i]->Lble->Text = (int)read_val1*TimLblE3[i]->Addr.Divide1()
                        +(int)read_val2*TimLblE3[i]->Addr.Divide1()+(int)read_val3;
                }
        }
        Btn_TCON_Tim_reload->Enabled = true;
}
//---------------------------------------------------------------------------




void __fastcall TTCONForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 0x40){
                Btn_TCON_dev_reloadClick(Sender);
                Btn_TCON_drv_reloadClick(Sender);
                Btn_TCON_io_reloadClick(Sender);
                Btn_TCON_Tim_reloadClick(Sender);
        }
}
//---------------------------------------------------------------------------





