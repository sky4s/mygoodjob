//---------------------------------------------------------------------------
//    20090903 version
//---------------------------------------------------------------------------

#include <vcl.h>
#include <lib/includeall.h>
#pragma hdrstop

#include "Vender1.h"
#include <fpga/11307/Vender/Vend_11307.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
__fastcall TVenderForm1::TVenderForm1(TComponent* Owner)
        : TForm(Owner)
{
        Vend_Chg = 0;
}
//---------------------------------------------------------------------------
void __fastcall TVenderForm1::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        delete [] OVender;

        delete [] Vend_cb;
        delete [] VendChkB;

        delete [] Vend_cbo;
        delete [] VendCboB;

        delete [] vend_scrlb;
        delete [] VendScrlB;

        delete [] vend_scrlb2;
        delete [] VendScrlB2;

        delete [] debug_cb;
        delete [] DebugChkB;

        delete [] DebugCboB;
        delete [] debug_cbo;

        delete [] StaCboB;
        delete [] sta_cbo;

        delete [] StaLblE2;
        delete [] sta_lble2;

        delete [] debug_lble2;
        delete [] DebugLblE2;
        
        Action = caFree;
        MainForm->VenderFormNULL();
}

//---------------------------------------------------------------------------

void __fastcall TVenderForm1::Vend_ScrollBar2_Scroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (VendScrlB2[idx]->ScrlB->Position);
        VendScrlB2[idx]->StTxt->Caption = set_val;
        if(ScrollCode == scEndScroll){
                //滑鼠放開, 或鍵盤操作放開
                if(Vend_Chg==0)
                        return;

                int val1 = set_val/VendScrlB2[idx]->Addr.Divide();
                int val2 = set_val%VendScrlB2[idx]->Addr.Divide();
                EngineerForm->SetWrite_Byte(VendScrlB2[idx]->Addr.Byte1 ,val1);
                EngineerForm->SetWrite_Byte(VendScrlB2[idx]->Addr.Byte2 ,val2);
        }
}
//------------------------------------------------------------------------------
void __fastcall TVenderForm1::Vend_ScrollBar_Scroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (ScrollPos);
        VendScrlB[idx]->StTxt->Caption = set_val;
        if(ScrollCode == scEndScroll){
        //滑鼠放開, 或鍵盤操作放開
                if(Vend_Chg==0)
                        return;

                EngineerForm->SetWrite_Byte(VendScrlB[idx]->Addr ,set_val);
        }
}

//---------------------------------------------------------------------------
void __fastcall TVenderForm1::Vend_CheckBox_Click(TObject *Sender)
{
        if(Vend_Chg==0)
                return;
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (VendChkB[idx]->Chkb->Checked?1:0);
        EngineerForm->SetWrite_Byte(VendChkB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall TVenderForm1::Vend_ComboBox_Click(TObject *Sender)
{
        if(Vend_Chg==0)
                return;
        TComboBox *c = (TComboBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (VendCboB[idx]->Cbob->ItemIndex);
        EngineerForm->SetWrite_Byte(VendCboB[idx]->Addr ,set_val);
}
//--------------------------------------------------------------------------
void __fastcall TVenderForm1::Debug_CheckBox_Click(TObject *Sender)
{
        if(Vend_Chg==0)
                return;
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (DebugChkB[idx]->Chkb->Checked?1:0);
        EngineerForm->SetWrite_Byte(DebugChkB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall TVenderForm1::Debug_ComboBox_Click(TObject *Sender)
{
        if(Vend_Chg==0)
                return;
        TComboBox *c = (TComboBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (DebugCboB[idx]->Cbob->ItemIndex);
        EngineerForm->SetWrite_Byte(DebugCboB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall TVenderForm1::Debug_LblEdit2_KeyPress(TObject *Sender, char &Key)
{
        TLabeledEdit *c = (TLabeledEdit *)Sender;
        int idx = StrToInt(c->Hint);
        if(Key!=13){
                DebugLblE2[idx]->Lble->Font->Color = cl3DDkShadow;
                return;
        }

        if(Vend_Chg==0)
                return;

        String tmp_v = DebugLblE2[idx]->Lble->Text;
        if(tmp_v==""){
                tmp_v = "0";
        }
        int set_val = StrToInt(tmp_v);

        unsigned char val1,val2;
        //add Max hint
        if(set_val>=pow(2,DebugLblE2[idx]->Addr.BitNum())){
                AnsiString max = "Max value:"+IntToStr((int)pow(2,DebugLblE2[idx]->Addr.BitNum())-1);
                ShowMessage(max);
                //read value
                EngineerForm->SetRead_Byte(DebugLblE2[idx]->Addr.Byte1, &val1);
                EngineerForm->SetRead_Byte(DebugLblE2[idx]->Addr.Byte2, &val2);
                DebugLblE2[idx]->Lble->Text = (int)val1*DebugLblE2[idx]->Addr.Divide()+val2;
                DebugLblE2[idx]->Lble->Font->Color = clWindowText;
        }else{
                val1 = set_val/DebugLblE2[idx]->Addr.Divide();
                val2 = set_val%DebugLblE2[idx]->Addr.Divide();
                EngineerForm->SetWrite_Byte(DebugLblE2[idx]->Addr.Byte1 ,val1);
                if(DebugLblE2[idx]->Addr.Byte2.BitNum()!=0)
                        EngineerForm->SetWrite_Byte(DebugLblE2[idx]->Addr.Byte2 ,val2);
                DebugLblE2[idx]->Lble->Font->Color = clWindowText;
        }
}

//---------------------------------------------------------------------------
void __fastcall TVenderForm1::FormCreate(TObject *Sender)
{
        int ic_choice;
        if(MainForm->TCON_DEV=="11307")
                ic_choice = 0;

        switch(ic_choice)
        {
                case 0:
                OVender = new Vend_11307;
                break;

               /* case 1:
                OVender = new Vend_1240x;
                break;*/

        }

        /****************************************************************/
        //   Vender CheckBox*4 & ComboBox*7 & ScrollBar*0               //
        /****************************************************************/

        //CheckBox
        Vend_cb = OVender->SetChkBx();

        VendChkB = new _CHKB* [OVender->VendChkBox_Nbr];
        for(int i = 0; i < OVender->VendChkBox_Nbr; i++)
                VendChkB[i] = new _CHKB;

        VendChkB[0]->Chkb = CheckBox1;
        VendChkB[1]->Chkb = CheckBox2;
        VendChkB[2]->Chkb = CheckBox3;
        VendChkB[3]->Chkb = CheckBox4;
        for(int i = 0; i < OVender->VendChkBox_Nbr; i++){
                VendChkB[i]->Addr = Vend_cb[i];
                VendChkB[i]->Chkb->Visible = VendChkB[i]->Addr.FuncEn();
                VendChkB[i]->Chkb->OnClick = Vend_CheckBox_Click;
                VendChkB[i]->Chkb->Hint = i;
                VendChkB[i]->Chkb->Caption = VendChkB[i]->Addr.Name();
        }

        //ComboBox
        Vend_cbo = OVender->SetCboBx();
        VendCboB = new _CBOB* [OVender->VendCboBox_Nbr];
        for(int i = 0; i < OVender->VendCboBox_Nbr; i++)
                VendCboB[i] = new _CBOB;

        VendCboB[0]->Cbob = ComboBox1;
        VendCboB[0]->CbobL= Label1;
        VendCboB[1]->Cbob = ComboBox2;
        VendCboB[1]->CbobL= Label2;
        VendCboB[2]->Cbob = ComboBox3;
        VendCboB[2]->CbobL= Label3;
        VendCboB[3]->Cbob = ComboBox4;
        VendCboB[3]->CbobL= Label4;
        VendCboB[4]->Cbob = ComboBox5;
        VendCboB[4]->CbobL= Label5;
        VendCboB[5]->Cbob = ComboBox6;
        VendCboB[5]->CbobL= Label6;
        VendCboB[6]->Cbob = ComboBox7;
        VendCboB[6]->CbobL= Label7;

        for(int i = 0; i < OVender->VendCboBox_Nbr; i++){
                VendCboB[i]->Addr = Vend_cbo[i];
                VendCboB[i]->Cbob->Visible = VendCboB[i]->Addr.FuncEn();
                VendCboB[i]->Cbob->OnClick = Vend_ComboBox_Click;
                VendCboB[i]->Cbob->Hint = i;
                VendCboB[i]->CbobL->Caption = VendCboB[i]->Addr.Name();
                VendCboB[i]->Cbob->Text = "";
                if(VendCboB[i]->Addr.FuncEn())
                        for(int j = 0; j< VendCboB[i]->Addr.choice_nbr; j++)     //ComboBox choice
                                VendCboB[i]->Cbob->Items->Add(VendCboB[i]->Addr.choice[j]);
        }
        //ScrollBar
        vend_scrlb = OVender->SetScrollBar();

        VendScrlB = new _ScrollBar* [OVender->VendScrollBar_Nbr];
        for(int i = 0; i < OVender->VendScrollBar_Nbr; i++)
                VendScrlB[i] = new _ScrollBar;

        for(int i = 0; i < OVender->VendScrollBar_Nbr; i++){
                VendScrlB[i]->Addr = vend_scrlb[i];
                VendScrlB[i]->Lbl->Visible = VendScrlB[i]->Addr.FuncEn();
                VendScrlB[i]->StTxt->Visible = VendScrlB[i]->Addr.FuncEn();
                VendScrlB[i]->ScrlB->Visible = VendScrlB[i]->Addr.FuncEn();
                VendScrlB[i]->ScrlB->Min = 0;
                VendScrlB[i]->ScrlB->Max = (int)pow(2,VendScrlB[i]->Addr.BitNum())-1;
                VendScrlB[i]->ScrlB->OnScroll = Vend_ScrollBar_Scroll;
                VendScrlB[i]->ScrlB->Hint = i;
                VendScrlB[i]->StTxt->Caption = 0;
                VendScrlB[i]->Lbl->Caption = VendScrlB[i]->Addr.Name();
        }

        //ScrollBar2
        vend_scrlb2 = OVender->SetScrollBar2();

        VendScrlB2 = new _ScrollBar2* [OVender->VendScrollBar2_Nbr];
        for(int i = 0; i < OVender->VendScrollBar2_Nbr; i++)
                VendScrlB2[i] = new _ScrollBar2;

        for(int i = 0; i < OVender->VendScrollBar2_Nbr; i++){
                VendScrlB2[i]->Addr = vend_scrlb2[i];
                VendScrlB2[i]->Lbl->Visible = VendScrlB2[i]->Addr.FuncEn();
                VendScrlB2[i]->StTxt->Visible = VendScrlB2[i]->Addr.FuncEn();
                VendScrlB2[i]->ScrlB->Visible = VendScrlB2[i]->Addr.FuncEn();
                VendScrlB2[i]->ScrlB->Min = 0;
                VendScrlB2[i]->ScrlB->Max = (int)pow(2,VendScrlB2[i]->Addr.BitNum())-1;
                VendScrlB2[i]->ScrlB->OnScroll = Vend_ScrollBar2_Scroll;
                VendScrlB2[i]->StTxt->Caption = 0;
                VendScrlB2[i]->ScrlB->Hint = i;
                VendScrlB2[i]->Lbl->Caption = VendScrlB2[i]->Addr.Name();
        }

        /****************************************************************/
        //   Debug CheckBox*7 & ComboBox*7 & LblE2*7                    //
        //   Status CheckBox*0 & ComboBox*5 & LblE2*14                  //
        /****************************************************************/

        //CheckBox
        debug_cb = OVender->SetDebugChkBx();

        DebugChkB = new _CHKB* [OVender->DebugChkBox_Nbr];
        for(int i = 0; i < OVender->DebugChkBox_Nbr; i++)
                DebugChkB[i] = new _CHKB;

        DebugChkB[0]->Chkb = CheckBox5;
        DebugChkB[1]->Chkb = CheckBox6;
        DebugChkB[2]->Chkb = CheckBox7;
        DebugChkB[3]->Chkb = CheckBox8;
        DebugChkB[4]->Chkb = CheckBox9;
        DebugChkB[5]->Chkb = CheckBox10;
        DebugChkB[6]->Chkb = CheckBox11;

        for(int i = 0; i < OVender->DebugChkBox_Nbr; i++){
                DebugChkB[i]->Addr = debug_cb[i];
                DebugChkB[i]->Chkb->Visible = DebugChkB[i]->Addr.FuncEn();
                DebugChkB[i]->Chkb->OnClick = Debug_CheckBox_Click;
                DebugChkB[i]->Chkb->Hint = i;
                DebugChkB[i]->Chkb->Caption = DebugChkB[i]->Addr.Name();
        }

        //ComboBox
        debug_cbo = OVender->SetDebugCboBx();

        DebugCboB = new _CBOB* [OVender->DebugCboBox_Nbr];
        for(int i = 0; i < OVender->DebugCboBox_Nbr; i++)
                DebugCboB[i] = new _CBOB;

        DebugCboB[0]->Cbob = ComboBox8;
        DebugCboB[0]->CbobL= Label12;
        DebugCboB[1]->Cbob = ComboBox14;
        DebugCboB[1]->CbobL= Label8;
        DebugCboB[2]->Cbob = ComboBox15;
        DebugCboB[2]->CbobL= Label9;
        DebugCboB[3]->Cbob = ComboBox16;
        DebugCboB[3]->CbobL= Label10;
        DebugCboB[4]->Cbob = ComboBox17;
        DebugCboB[4]->CbobL= Label11;
        DebugCboB[5]->Cbob = ComboBox18;
        DebugCboB[5]->CbobL= Label18;
        DebugCboB[6]->Cbob = ComboBox19;
        DebugCboB[6]->CbobL= Label19;
        for(int i = 0; i < OVender->DebugCboBox_Nbr; i++){
                DebugCboB[i]->Addr = debug_cbo[i];
                DebugCboB[i]->Cbob->Visible = DebugCboB[i]->Addr.FuncEn();
                DebugCboB[i]->CbobL->Visible = DebugCboB[i]->Addr.FuncEn();
                DebugCboB[i]->Cbob->OnClick = Debug_ComboBox_Click;
                DebugCboB[i]->Cbob->Hint = i;
                DebugCboB[i]->CbobL->Caption = DebugCboB[i]->Addr.Name();
                DebugCboB[i]->Cbob->Text = "";
                if(DebugCboB[i]->Addr.FuncEn())
                        for(int j = 0; j< DebugCboB[i]->Addr.choice_nbr; j++)     //ComboBox choice
                                DebugCboB[i]->Cbob->Items->Add(DebugCboB[i]->Addr.choice[j]);
        }

        sta_cbo = OVender->SetStaCboBx();

        StaCboB = new _CBOB* [OVender->VStaCboBox_Nbr];
        for(int i = 0; i < OVender->VStaCboBox_Nbr; i++)
                StaCboB[i] = new _CBOB;

        StaCboB[0]->Cbob = ComboBox9;
        StaCboB[0]->CbobL= Label13;
        StaCboB[1]->Cbob = ComboBox10;
        StaCboB[1]->CbobL= Label14;
        StaCboB[2]->Cbob = ComboBox11;
        StaCboB[2]->CbobL= Label15;
        StaCboB[3]->Cbob = ComboBox12;
        StaCboB[3]->CbobL= Label16;
        StaCboB[4]->Cbob = ComboBox13;
        StaCboB[4]->CbobL= Label17;

        for(int i = 0; i < OVender->VStaCboBox_Nbr; i++){
                StaCboB[i]->Addr = sta_cbo[i];
                StaCboB[i]->Cbob->Enabled = false;       //status enable set false
                StaCboB[i]->Cbob->Visible = StaCboB[i]->Addr.FuncEn();
                StaCboB[i]->CbobL->Visible = StaCboB[i]->Addr.FuncEn();
                StaCboB[i]->Cbob->Hint = i;
                StaCboB[i]->CbobL->Caption = StaCboB[i]->Addr.Name();
                StaCboB[i]->Cbob->Text = "";
                if(StaCboB[i]->Addr.FuncEn())
                        for(int j = 0; j< StaCboB[i]->Addr.choice_nbr; j++)     //ComboBox choice
                                StaCboB[i]->Cbob->Items->Add(StaCboB[i]->Addr.choice[j]);
        }

        //LabeledEdit2 *7
        debug_lble2 = OVender->SetDebugLblE2();

        DebugLblE2 = new _LBLE2* [OVender->DebugLblE2_Nbr];
        for(int i = 0; i < OVender->DebugLblE2_Nbr; i++)
                DebugLblE2[i] = new _LBLE2;

        DebugLblE2[0]->Lble = LabeledEdit1;
        DebugLblE2[1]->Lble = LabeledEdit2;
        DebugLblE2[2]->Lble = LabeledEdit3;
        DebugLblE2[3]->Lble = LabeledEdit4;
        DebugLblE2[4]->Lble = LabeledEdit5;
        DebugLblE2[5]->Lble = LabeledEdit10;
        DebugLblE2[6]->Lble = LabeledEdit11;

        for(int i = 0; i < OVender->DebugLblE2_Nbr; i++){
                DebugLblE2[i]->Addr = debug_lble2[i];
                DebugLblE2[i]->Lble->Visible = DebugLblE2[i]->Addr.FuncEn();
                DebugLblE2[i]->Lble->OnKeyPress = Debug_LblEdit2_KeyPress;
                DebugLblE2[i]->Lble->Hint = i;
                DebugLblE2[i]->Lble->EditLabel->Caption = DebugLblE2[i]->Addr.Name();
                DebugLblE2[i]->Lble->Text = 0;
        }

        //LabeledEdit2 *4
        sta_lble2 = OVender->SetStaLblE2();

        StaLblE2 = new _LBLE2* [OVender->VStaLblE2_Nbr];
        for(int i = 0; i < OVender->VStaLblE2_Nbr; i++)
                StaLblE2[i] = new _LBLE2;

        StaLblE2[0]->Lble = LabeledEdit6;
        StaLblE2[1]->Lble = LabeledEdit7;
        StaLblE2[2]->Lble = LabeledEdit8;
        StaLblE2[3]->Lble = LabeledEdit9;
        StaLblE2[4]->Lble = LabeledEdit12;
        StaLblE2[5]->Lble = LabeledEdit13;
        StaLblE2[6]->Lble = LabeledEdit14;
        StaLblE2[7]->Lble = LabeledEdit15;
        StaLblE2[8]->Lble = LabeledEdit16;
        StaLblE2[9]->Lble = LabeledEdit17;
        StaLblE2[10]->Lble = LabeledEdit20;
        StaLblE2[11]->Lble = LabeledEdit21;

        for(int i = 0; i < OVender->VStaLblE2_Nbr; i++){
                StaLblE2[i]->Addr = sta_lble2[i];
                StaLblE2[i]->Lble->Visible = StaLblE2[i]->Addr.FuncEn();
                StaLblE2[i]->Lble->ReadOnly = true;    //status ReadOnly is true
                StaLblE2[i]->Lble->ParentColor = true; //status ParentColor is true
                StaLblE2[i]->Lble->Hint = i;
                StaLblE2[i]->Lble->EditLabel->Caption = StaLblE2[i]->Addr.Name();
                StaLblE2[i]->Lble->Text = 0;
        }

        Vend_Chg = 1;
}
//---------------------------------------------------------------------------

void __fastcall TVenderForm1::Btn_vender_reloadClick(TObject *Sender)
{
        Btn_vender_reload->Enabled = false;
        Vend_Chg = 0;
        unsigned char read_val;
        for(int i = 0; i < OVender->VendChkBox_Nbr; i++){
                if(VendChkB[i]->Chkb->Visible==true){
                        EngineerForm->SetRead_Byte(VendChkB[i]->Addr, &read_val);
                        if(read_val==1)
                                VendChkB[i]->Chkb->Checked = 1;
                        else if(read_val==0)
                                VendChkB[i]->Chkb->Checked = 0;
                        else
                                ShowMessage("Vender CheckBox read error:"+IntToStr(read_val));
                }
        }
        for(int i = 0; i < OVender->VendCboBox_Nbr; i++){
                if(VendCboB[i]->Cbob->Visible==true){
                        EngineerForm->SetRead_Byte(VendCboB[i]->Addr, &read_val);
                        VendCboB[i]->Cbob->ItemIndex = read_val;
                }
        }

        for(int i = 0; i < OVender->VendScrollBar_Nbr; i++){
                if(VendScrlB[i]->ScrlB->Visible==true){
                        EngineerForm->SetRead_Byte(VendScrlB[i]->Addr, &read_val);
                        VendScrlB[i]->ScrlB->Position = read_val;
                        VendScrlB[i]->StTxt->Caption = read_val;
                }
        }
        unsigned char read_val1, read_val2;
        for(int i = 0; i < OVender->VendScrollBar2_Nbr; i++){
                if(VendScrlB2[i]->ScrlB->Visible==true){
                        EngineerForm->SetRead_Byte(VendScrlB2[i]->Addr.Byte1, &read_val1);
                        EngineerForm->SetRead_Byte(VendScrlB2[i]->Addr.Byte2, &read_val2);
                        VendScrlB2[i]->ScrlB->Position = (int)read_val1*VendScrlB2[i]->Addr.Divide()+read_val2;
                        VendScrlB2[i]->StTxt->Caption = (int)read_val1*VendScrlB2[i]->Addr.Divide()+read_val2;
                }
        }
        Vend_Chg = 1;
        Btn_vender_reload->Enabled = true;        
}
//---------------------------------------------------------------------------

void __fastcall TVenderForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 0x40){
                Btn_vender_reloadClick(Sender);
                btn_debug_reloadClick(Sender); // Add by Michelle 20100721
                btn_status_refreshClick(Sender);  // Add by Michelle 20100721
        }
}
//---------------------------------------------------------------------------

void __fastcall TVenderForm1::btn_status_refreshClick(TObject *Sender)
{
        btn_status_refresh->Enabled = false;
        unsigned char read_val;
        for(int i = 0; i < OVender->VStaCboBox_Nbr; i++){
                if(StaCboB[i]->Cbob->Visible==true){
                        EngineerForm->SetRead_Byte(StaCboB[i]->Addr, &read_val);
                        StaCboB[i]->Cbob->ItemIndex = read_val;
                }
        }

        unsigned char read_val1,read_val2;
        for(int i = 0; i < OVender->VStaLblE2_Nbr; i++){
                if(StaLblE2[i]->Lble->Visible==true){
                        EngineerForm->SetRead_Byte(StaLblE2[i]->Addr.Byte1, &read_val1);
                        EngineerForm->SetRead_Byte(StaLblE2[i]->Addr.Byte2, &read_val2);
                        StaLblE2[i]->Lble->Text = (int)read_val1*StaLblE2[i]->Addr.Divide()+read_val2;
                }
        }
        btn_status_refresh->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TVenderForm1::btn_debug_reloadClick(TObject *Sender)
{
        btn_debug_reload->Enabled = false;
        Vend_Chg = 0;
        unsigned char read_val;
        for(int i = 0; i < OVender->DebugChkBox_Nbr; i++){
                if(DebugChkB[i]->Chkb->Visible==true){
                        EngineerForm->SetRead_Byte(DebugChkB[i]->Addr, &read_val);
                        if(read_val==1)
                                DebugChkB[i]->Chkb->Checked = 1;
                        else if(read_val==0)
                                DebugChkB[i]->Chkb->Checked = 0;
                        else
                                ShowMessage("Debug CheckBox read error:"+IntToStr(read_val));
                }
        }
        for(int i = 0; i < OVender->DebugCboBox_Nbr; i++){
                if(DebugCboB[i]->Cbob->Visible==true){
                        EngineerForm->SetRead_Byte(DebugCboB[i]->Addr, &read_val);
                        DebugCboB[i]->Cbob->ItemIndex = read_val;
                }
        }

        unsigned char read_val1,read_val2;
        for(int i = 0; i < OVender->DebugLblE2_Nbr; i++){
                if(DebugLblE2[i]->Lble->Visible==true){
                        EngineerForm->SetRead_Byte(DebugLblE2[i]->Addr.Byte1, &read_val1);
                        EngineerForm->SetRead_Byte(DebugLblE2[i]->Addr.Byte2, &read_val2);
                        DebugLblE2[i]->Lble->Text = (int)read_val1*DebugLblE2[i]->Addr.Divide()+read_val2;
                        DebugLblE2[i]->Lble->Font->Color = clWindowText;
                }
        }
        btn_status_refreshClick(Sender);
        btn_debug_reload->Enabled = true;
        Vend_Chg = 1;
}
//---------------------------------------------------------------------------

