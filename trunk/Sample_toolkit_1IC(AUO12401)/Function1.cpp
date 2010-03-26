//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Function1.h"
#include "Func_12401.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

//extern String TCON_DEV;
//---------------------------------------------------------------------------
__fastcall TFunctionForm1::TFunctionForm1(TComponent* Owner)
        : TForm(Owner)
{
        Func_Chg = 0;
}
//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::FormClose(TObject *Sender,
      TCloseAction &Action)
{
        delete [] OFunc;
        //Pstate
        delete [] Pstate_cb;
        delete [] PstateChkB;
        delete [] Pstate_cbo;
        delete [] PstateCboB;

        //AGBS
        delete [] AGBS_cb;
        delete [] AGBSChkB;
        delete [] AGBS_cbo;
        delete [] AGBSCboB;
        delete [] AGBS_lble2;
        delete [] AGBSLblE2;

        // FRC DG
        delete [] FrcDg_cb;
        delete [] FrcDgChkB;
        delete [] FrcDg_cbo;
        delete [] FrcDgCboB;
        delete [] FrcDg_lble;
        delete [] FrcDgLblE;
        //OD
        delete [] OD_cb;
        delete [] ODChkB;
        delete [] OD_cbo;
        delete [] ODCboB;
        delete [] OD_cbo2;
        delete [] ODCboB2;
        delete [] OD_ScrlB;
        delete [] ODScrlB;
        delete [] Addr_DgLUT;
        Action = caFree;
        MainForm->FunctionFormNULL();
}
//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::Pstate_CheckBox_Click(TObject *Sender)
{
        if(Func_Chg==0)
                return;
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (PstateChkB[idx]->Chkb->Checked?1:0);
        EngineerForm->SetWrite_Byte(PstateChkB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::Pstate_ComboBox_Click(TObject *Sender)
{
        if(Func_Chg==0)
                return;
        TComboBox *c = (TComboBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (PstateCboB[idx]->Cbob->ItemIndex);
        EngineerForm->SetWrite_Byte(PstateCboB[idx]->Addr ,set_val);
}

//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::Pstate_LblEdit2_KeyPress(TObject *Sender, char &Key)
{
        TLabeledEdit *c = (TLabeledEdit *)Sender;
        int idx = StrToInt(c->Hint);
        if(Key!=13){
                PstateLblE2[idx]->Lble->Font->Color = cl3DDkShadow;
                return;
        }

        if(Func_Chg==0)
                return;

        String tmp_v = PstateLblE2[idx]->Lble->Text;
        if(tmp_v==""){
                tmp_v = "0";
        }
        int set_val = StrToInt(tmp_v);

        unsigned char val1,val2;
        //add Max hint
        if(set_val>=pow(2,PstateLblE2[idx]->Addr.BitNum())){
                AnsiString max = "Max value:"+IntToStr((int)pow(2,PstateLblE2[idx]->Addr.BitNum())-1);
                ShowMessage(max);
                //read value
                EngineerForm->SetRead_Byte(PstateLblE2[idx]->Addr.Byte1, &val1);
                EngineerForm->SetRead_Byte(PstateLblE2[idx]->Addr.Byte2, &val2);
                PstateLblE2[idx]->Lble->Text = (int)val1*PstateLblE2[idx]->Addr.Divide()+val2;
                PstateLblE2[idx]->Lble->Font->Color = clWindowText;
        }else{
                val1 = set_val/PstateLblE2[idx]->Addr.Divide();
                val2 = set_val%PstateLblE2[idx]->Addr.Divide();
                EngineerForm->SetWrite_Byte(PstateLblE2[idx]->Addr.Byte1 ,val1);
                if(PstateLblE2[idx]->Addr.Byte2.BitNum()!=0)
                        EngineerForm->SetWrite_Byte(PstateLblE2[idx]->Addr.Byte2 ,val2);
                PstateLblE2[idx]->Lble->Font->Color = clWindowText;
        }
}
//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::AGBS_CheckBox_Click(TObject *Sender)
{
        if(Func_Chg==0)
                return;
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (AGBSChkB[idx]->Chkb->Checked?1:0);
        EngineerForm->SetWrite_Byte(AGBSChkB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::AGBS_ComboBox_Click(TObject *Sender)
{
        if(Func_Chg==0)
                return;
        TComboBox *c = (TComboBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (AGBSCboB[idx]->Cbob->ItemIndex);
        EngineerForm->SetWrite_Byte(AGBSCboB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::AGBS_LblEdit2_KeyPress(TObject *Sender, char &Key)
{
        TLabeledEdit *c = (TLabeledEdit *)Sender;
        int idx = StrToInt(c->Hint);

        if(Key!=13){
                AGBSLblE2[idx]->Lble->Font->Color = cl3DDkShadow;
                return;
        }

        if(Func_Chg==0)
                return;
        String tmp_v = AGBSLblE2[idx]->Lble->Text;
        if(tmp_v==""){
                tmp_v = "0";
        }
        int set_val = StrToInt(tmp_v);
        unsigned char val1,val2;
        //add Max hint
        if(set_val>=pow(2,AGBSLblE2[idx]->Addr.BitNum())){
                AnsiString max = "Max value:"+IntToStr((int)pow(2,AGBSLblE2[idx]->Addr.BitNum())-1);
                ShowMessage(max);
                //read value
                EngineerForm->SetRead_Byte(AGBSLblE2[idx]->Addr.Byte1, &val1);
                EngineerForm->SetRead_Byte(AGBSLblE2[idx]->Addr.Byte2, &val2);
                AGBSLblE2[idx]->Lble->Text = (int)val1*AGBSLblE2[idx]->Addr.Divide()+val2;
                AGBSLblE2[idx]->Lble->Font->Color = clWindowText;
        }else{
                val1 = set_val/AGBSLblE2[idx]->Addr.Divide();
                val2 = set_val%AGBSLblE2[idx]->Addr.Divide();
                EngineerForm->SetWrite_Byte(AGBSLblE2[idx]->Addr.Byte1 ,val1);
                if(AGBSLblE2[idx]->Addr.Byte2.BitNum()!=0)
                        EngineerForm->SetWrite_Byte(AGBSLblE2[idx]->Addr.Byte2 ,val2);
                AGBSLblE2[idx]->Lble->Font->Color = clWindowText;
        }
}
//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::FrcDg_CheckBox_Click(TObject *Sender)
{
        if(Func_Chg==0)
                return;
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (FrcDgChkB[idx]->Chkb->Checked?1:0);
        EngineerForm->SetWrite_Byte(FrcDgChkB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::FrcDg_ComboBox_Click(TObject *Sender)
{
        if(Func_Chg==0)
                return;
        TComboBox *c = (TComboBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (FrcDgCboB[idx]->Cbob->ItemIndex);
        EngineerForm->SetWrite_Byte(FrcDgCboB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::FrcDg_LblEdit_KeyPress(TObject *Sender, char &Key)
{
        TLabeledEdit *c = (TLabeledEdit *)Sender;
        int idx = StrToInt(c->Hint);
        if(Key!=13){
                FrcDgLblE[idx]->Lble->Font->Color = cl3DDkShadow;
                return;
        }
        if(Func_Chg==0)
                return;

        String tmp_v = FrcDgLblE[idx]->Lble->Text;
        if(tmp_v==""){
                tmp_v = "0";
        }
        int set_val = StrToInt(tmp_v);

        unsigned char read_val;
        //add Max hint
        if(set_val>=pow(2,FrcDgLblE[idx]->Addr.BitNum())){
                AnsiString max = "Max value:"+IntToStr((int)pow(2,FrcDgLblE[idx]->Addr.BitNum())-1);
                ShowMessage(max);
                //read value
                EngineerForm->SetRead_Byte(FrcDgLblE[idx]->Addr, &read_val);
                FrcDgLblE[idx]->Lble->Text = read_val;
                FrcDgLblE[idx]->Lble->Font->Color = clWindowText;
        }else{
                EngineerForm->SetWrite_Byte(FrcDgLblE[idx]->Addr ,set_val);
                FrcDgLblE[idx]->Lble->Font->Color = clWindowText;
        }
}
//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::OD_CheckBox_Click(TObject *Sender)
{
        if(Func_Chg==0)
                return;
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (ODChkB[idx]->Chkb->Checked?1:0);
        EngineerForm->SetWrite_Byte(ODChkB[idx]->Addr ,set_val);
}
//--------------------------------------------------------------------------
void __fastcall TFunctionForm1::OD_ComboBox_Click(TObject *Sender)
{
        if(Func_Chg==0)
                return;
        TComboBox *c = (TComboBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (ODCboB[idx]->Cbob->ItemIndex);
        EngineerForm->SetWrite_Byte(ODCboB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::OD_ComboBox2_Click(TObject *Sender)
{
        if(Func_Chg==0)
                return;
        TComboBox *c = (TComboBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = StrToInt(ODCboB2[idx]->Cbob->ItemIndex);
        int val1 = set_val/ODCboB2[idx]->Addr.Divide();
        int val2 = set_val%ODCboB2[idx]->Addr.Divide();
        EngineerForm->SetWrite_Byte(ODCboB2[idx]->Addr.Byte1 ,val1);
        Sleep(10);
        EngineerForm->SetWrite_Byte(ODCboB2[idx]->Addr.Byte2 ,val2);
}
//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::OD_ScrollBar_Scroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (ODScrlB[idx]->ScrlB->Position);
        ODScrlB[idx]->StTxt->Caption = set_val;

        if(ScrollCode == scEndScroll){
        //滑鼠放開, 或鍵盤操作放開
                if(Func_Chg==0)
                        return;
                EngineerForm->SetWrite_Byte(ODScrlB[idx]->Addr ,set_val);
        }
}
//---------------------------------------------------------------------------
void __fastcall TFunctionForm1::FormCreate(TObject *Sender)
{
        int ic_choice;
        if(MainForm->TCON_DEV=="12401")
                ic_choice = 0;

        switch(ic_choice)
        {
                case 0:
                OFunc = new Func_12401;
                break;

               /* case 1:
                OFunc = new Func_1240x;
                break;*/

        }
        //Set address
        Addr_DgLUT = OFunc->SetDGLUT();
        //Initial DG table
        sg_dg->Cells[1][0]="R"; //RGB top row
        sg_dg->Cells[2][0]="G";
        sg_dg->Cells[3][0]="B";

        int max_val = pow(2,Addr_DgLUT[0].BitNum());
        for(int j = 1; j<=256; j++){
                sg_dg->Cells[0][j] = IntToStr(j-1);       //index on the left of table
                for(int i = 1; i <=4; i++)
                        sg_dg->Cells[i][j] = IntToStr(max_val/256*(j-1));
        }
        sg_dg->Cells[0][257] = 256;
        sg_dg->Cells[1][257] = max_val-1;
        sg_dg->Cells[2][257] = max_val-1;
        sg_dg->Cells[3][257] = max_val-1;

        //////////////////////////////////////////////////////////////////

        //Initial DG table
        sg_od1->Cells[0][0]="Address";
        sg_od1->Cells[1][0]="data"; //RGB top row
        sg_od1->Cells[2][0]="data";
        sg_od1->Cells[3][0]="data";
        sg_od1->Cells[4][0]="data";

        sg_od2->Cells[0][0]="Address";
        sg_od2->Cells[1][0]="data"; //RGB top row
        sg_od2->Cells[2][0]="data";
        sg_od2->Cells[3][0]="data";
        sg_od2->Cells[4][0]="data";

        for(int j = 0; j<=80; j++){
                sg_od1->Cells[0][j+1] = IntToStr(j);       //index on the left of table
                sg_od2->Cells[0][j+1] = IntToStr(j);       //index on the left of table
        }
        //Set address
        Addr_ODLUT1 = OFunc->SetODLUT1();
        Addr_ODLUT2 = OFunc->SetODLUT2();

        /****************************************************************/
        //                                                              //
        //   P-state page CheckBox*2 & ComboBox*1 & LabeledEdit*4       //
        //                                                              //
        /****************************************************************/

        //CheckBox
        Pstate_cb = OFunc->SetPstateChkBx();

        PstateChkB = new _CHKB* [OFunc->PstateChkBox_Nbr];
        for(int i = 0; i < OFunc->PstateChkBox_Nbr; i++)
                PstateChkB[i] = new _CHKB;

        PstateChkB[0]->Chkb = CheckBox1;
        PstateChkB[1]->Chkb = CheckBox2;
        for(int i = 0; i < OFunc->PstateChkBox_Nbr; i++){
                PstateChkB[i]->Addr = Pstate_cb[i];
                PstateChkB[i]->Chkb->Visible = PstateChkB[i]->Addr.FuncEn();
                PstateChkB[i]->Chkb->OnClick = Pstate_CheckBox_Click;
                PstateChkB[i]->Chkb->Hint = i;
                PstateChkB[i]->Chkb->Caption = PstateChkB[i]->Addr.Name();
        }

        //ComboBox
        Pstate_cbo = OFunc->SetPstateCboBx();
        PstateCboB = new _CBOB* [OFunc->PstateCboBox_Nbr];
        for(int i = 0; i < OFunc->PstateCboBox_Nbr; i++)
                PstateCboB[i] = new _CBOB;

        PstateCboB[0]->Cbob = ComboBox1;
        PstateCboB[0]->CbobL= Label1;
        for(int i = 0; i < OFunc->PstateCboBox_Nbr; i++){
                PstateCboB[i]->Addr = Pstate_cbo[i];
                PstateCboB[i]->Cbob->Visible = PstateCboB[i]->Addr.FuncEn();
                PstateCboB[i]->Cbob->OnClick = Pstate_ComboBox_Click;
                PstateCboB[i]->Cbob->Hint = i;
                PstateCboB[i]->CbobL->Caption = PstateCboB[i]->Addr.Name();
                PstateCboB[i]->Cbob->Text = "";
                if(PstateCboB[i]->Addr.FuncEn())
                        for(int j = 0; j< PstateCboB[i]->Addr.choice_nbr; j++)     //ComboBox choice
                                PstateCboB[i]->Cbob->Items->Add(PstateCboB[i]->Addr.choice[j]);
        }

        //LabeledEdit2
        Pstate_lble2 = OFunc->SetPstateLblE2();
        PstateLblE2 = new _LBLE2* [OFunc->PstateLblE2_Nbr];
        for(int i = 0; i < OFunc->PstateLblE2_Nbr; i++)
                PstateLblE2[i] = new _LBLE2;

        PstateLblE2[0]->Lble = LabeledEdit1;
        PstateLblE2[1]->Lble = LabeledEdit2;
        PstateLblE2[2]->Lble = LabeledEdit3;
        PstateLblE2[3]->Lble = LabeledEdit4;

        for(int i = 0; i < OFunc->PstateLblE2_Nbr; i++){
                PstateLblE2[i]->Addr = Pstate_lble2[i];
                PstateLblE2[i]->Lble->Visible = PstateLblE2[i]->Addr.FuncEn();
                PstateLblE2[i]->Lble->OnKeyPress = Pstate_LblEdit2_KeyPress;
                PstateLblE2[i]->Lble->Hint = i;
                PstateLblE2[i]->Lble->EditLabel->Caption = PstateLblE2[i]->Addr.Name();
                PstateLblE2[i]->Lble->Text = 0;
        }

        /*********************************************************************/
        //                                                                   //
        //   Aging Bist Page CheckBox*2 & ComboBox*1 & 2byte LabeledEdit*3   //
        //                                                                   //
        /*********************************************************************/
        //CheckBox
        AGBS_cb = OFunc->SetAGBSChkBx();

        AGBSChkB = new _CHKB* [OFunc->AGBSChkBox_Nbr];
        for(int i = 0; i < OFunc->AGBSChkBox_Nbr; i++)
                AGBSChkB[i] = new _CHKB;

        AGBSChkB[0]->Chkb = CheckBox3;
        AGBSChkB[1]->Chkb = CheckBox4;
        for(int i = 0; i < OFunc->AGBSChkBox_Nbr; i++){
                AGBSChkB[i]->Addr = AGBS_cb[i];
                AGBSChkB[i]->Chkb->Visible = AGBSChkB[i]->Addr.FuncEn();
                AGBSChkB[i]->Chkb->OnClick = AGBS_CheckBox_Click;
                AGBSChkB[i]->Chkb->Hint = i;
                AGBSChkB[i]->Chkb->Caption = AGBSChkB[i]->Addr.Name();
        }

        //ComboBox
        AGBS_cbo = OFunc->SetAGBSCboBx();
        AGBSCboB = new _CBOB* [OFunc->AGBSCboBox_Nbr];
        for(int i = 0; i < OFunc->AGBSCboBox_Nbr; i++)
                AGBSCboB[i] = new _CBOB;

        AGBSCboB[0]->Cbob = ComboBox2;
        AGBSCboB[0]->CbobL= Label2;
        for(int i = 0; i < OFunc->AGBSCboBox_Nbr; i++){
                AGBSCboB[i]->Addr = AGBS_cbo[i];
                AGBSCboB[i]->Cbob->Visible = AGBSCboB[i]->Addr.FuncEn();
                AGBSCboB[i]->Cbob->OnClick = AGBS_ComboBox_Click;
                AGBSCboB[i]->Cbob->Hint = i;
                AGBSCboB[i]->CbobL->Caption = AGBSCboB[i]->Addr.Name();
                AGBSCboB[i]->Cbob->Text = "";
                if(AGBSCboB[i]->Addr.FuncEn())
                        for(int j = 0; j< AGBSCboB[i]->Addr.choice_nbr; j++)     //ComboBox choice
                                AGBSCboB[i]->Cbob->Items->Add(AGBSCboB[i]->Addr.choice[j]);
        }

        //LabeledEdit 2 byte size
        AGBS_lble2 = OFunc->SetAGBSLblE2();
        AGBSLblE2 = new _LBLE2* [OFunc->AGBSLblE2_Nbr];
        for(int i = 0; i < OFunc->AGBSLblE2_Nbr; i++)
                AGBSLblE2[i] = new _LBLE2;

        AGBSLblE2[0]->Lble = LabeledEdit5;
        AGBSLblE2[1]->Lble = LabeledEdit6;
        AGBSLblE2[2]->Lble = LabeledEdit7;

        for(int i = 0; i < OFunc->AGBSLblE2_Nbr; i++){
                AGBSLblE2[i]->Addr = AGBS_lble2[i];
                AGBSLblE2[i]->Lble->Visible = AGBSLblE2[i]->Addr.FuncEn();
                AGBSLblE2[i]->Lble->OnKeyPress = AGBS_LblEdit2_KeyPress;
                AGBSLblE2[i]->Lble->Hint = i;
                AGBSLblE2[i]->Lble->EditLabel->Caption = AGBSLblE2[i]->Addr.Name();
                AGBSLblE2[i]->Lble->Text = 0;
        }

        /*******************************************************************/
        //                                                                 //
        //   FRC DG page CheckBox*5 & ComboBox*1 & LabeledEdit*1           //
        //                                                                 //
        /*******************************************************************/
        //CheckBox
        FrcDg_cb = OFunc->SetFrcDgChkBx();

        FrcDgChkB = new _CHKB* [OFunc->FrcDgChkBox_Nbr];
        for(int i = 0; i < OFunc->FrcDgChkBox_Nbr; i++)
                FrcDgChkB[i] = new _CHKB;

        FrcDgChkB[0]->Chkb = CheckBox5;
        FrcDgChkB[1]->Chkb = CheckBox6;
        FrcDgChkB[2]->Chkb = CheckBox7;
        FrcDgChkB[3]->Chkb = CheckBox8;
        FrcDgChkB[4]->Chkb = CheckBox9;

        for(int i = 0; i < OFunc->FrcDgChkBox_Nbr; i++){
                FrcDgChkB[i]->Addr = FrcDg_cb[i];
                FrcDgChkB[i]->Chkb->Visible = FrcDgChkB[i]->Addr.FuncEn();
                FrcDgChkB[i]->Chkb->OnClick = FrcDg_CheckBox_Click;
                FrcDgChkB[i]->Chkb->Hint = i;
                FrcDgChkB[i]->Chkb->Caption = FrcDgChkB[i]->Addr.Name();
        }

        //ComboBox
        FrcDg_cbo = OFunc->SetFrcDgCboBx();
        FrcDgCboB = new _CBOB* [OFunc->FrcDgCboBox_Nbr];
        for(int i = 0; i < OFunc->FrcDgCboBox_Nbr; i++)
                FrcDgCboB[i] = new _CBOB;

        FrcDgCboB[0]->Cbob = ComboBox3;
        FrcDgCboB[0]->CbobL= Label3;
        
        for(int i = 0; i < OFunc->FrcDgCboBox_Nbr; i++){
                FrcDgCboB[i]->Addr = FrcDg_cbo[i];
                FrcDgCboB[i]->Cbob->Visible = FrcDgCboB[i]->Addr.FuncEn();
                FrcDgCboB[i]->Cbob->OnClick = FrcDg_ComboBox_Click;
                FrcDgCboB[i]->Cbob->Hint = i;
                FrcDgCboB[i]->CbobL->Caption = FrcDgCboB[i]->Addr.Name();
                FrcDgCboB[i]->Cbob->Text = "";
                if(FrcDgCboB[i]->Addr.FuncEn())
                        for(int j = 0; j< FrcDgCboB[i]->Addr.choice_nbr; j++)     //ComboBox choice
                                FrcDgCboB[i]->Cbob->Items->Add(FrcDgCboB[i]->Addr.choice[j]);
        }
        //LabeledEdit
        FrcDg_lble = OFunc->SetFrcDgLblE();
        FrcDgLblE = new _LBLE* [OFunc->FrcDgLblE_Nbr];
        for(int i = 0; i < OFunc->FrcDgLblE_Nbr; i++)
                FrcDgLblE[i] = new _LBLE;

        FrcDgLblE[0]->Lble = LabeledEdit8;
        for(int i = 0; i < OFunc->FrcDgLblE_Nbr; i++){
                FrcDgLblE[i]->Addr = FrcDg_lble[i];
                FrcDgLblE[i]->Lble->Visible = FrcDgLblE[i]->Addr.FuncEn();
                FrcDgLblE[i]->Lble->OnKeyPress = FrcDg_LblEdit_KeyPress;
                FrcDgLblE[i]->Lble->Hint = i;
                FrcDgLblE[i]->Lble->EditLabel->Caption = FrcDgLblE[i]->Addr.Name();
                FrcDgLblE[i]->Lble->Text = 0;
        }

        /*******************************************************************/
        //                                                                 //
        //      OD page CheckBox*3   ComboBox*3  ComboBox2*1  ScrollBar*3  //
        //                                                                 //
        /*******************************************************************/
        //CheckBox
        OD_cb = OFunc->SetODChkBx();

        ODChkB = new _CHKB* [OFunc->ODChkBox_Nbr];
        for(int i = 0; i < OFunc->ODChkBox_Nbr; i++)
                ODChkB[i] = new _CHKB;

        ODChkB[0]->Chkb = CheckBox10;
        ODChkB[1]->Chkb = CheckBox11;
        ODChkB[2]->Chkb = CheckBox12;

        for(int i = 0; i < OFunc->ODChkBox_Nbr; i++){
                ODChkB[i]->Addr = OD_cb[i];
                ODChkB[i]->Chkb->Visible = ODChkB[i]->Addr.FuncEn();
                ODChkB[i]->Chkb->OnClick = OD_CheckBox_Click;
                ODChkB[i]->Chkb->Hint = i;
                ODChkB[i]->Chkb->Caption = ODChkB[i]->Addr.Name();
        }
        //ComboBox
        OD_cbo = OFunc->SetODCboBx();
        ODCboB = new _CBOB* [OFunc->ODCboBox_Nbr];
        for(int i = 0; i < OFunc->ODCboBox_Nbr; i++)
                ODCboB[i] = new _CBOB;

        ODCboB[0]->Cbob = ComboBox4;
        ODCboB[0]->CbobL= Label4;
        ODCboB[1]->Cbob = ComboBox5;
        ODCboB[1]->CbobL= Label5;
        ODCboB[2]->Cbob = ComboBox6;
        ODCboB[2]->CbobL= Label6;
        for(int i = 0; i < OFunc->ODCboBox_Nbr; i++){
                ODCboB[i]->Addr = OD_cbo[i];
                ODCboB[i]->Cbob->Visible = ODCboB[i]->Addr.FuncEn();
                ODCboB[i]->Cbob->OnClick = OD_ComboBox_Click;
                ODCboB[i]->Cbob->Hint = i;
                ODCboB[i]->CbobL->Caption = ODCboB[i]->Addr.Name();
                ODCboB[i]->Cbob->Text = "";
                if(ODCboB[i]->Addr.FuncEn())
                        for(int j = 0; j< ODCboB[i]->Addr.choice_nbr; j++)     //ComboBox choice
                                ODCboB[i]->Cbob->Items->Add(ODCboB[i]->Addr.choice[j]);
        }
        //ComboBox2
        OD_cbo2 = OFunc->SetODCboBx2();
        ODCboB2 = new _CBOB2* [OFunc->ODCboBox2_Nbr];
        for(int i = 0; i < OFunc->ODCboBox2_Nbr; i++)
                ODCboB2[i] = new _CBOB2;

        ODCboB2[0]->Cbob = ComboBox7;
        ODCboB2[0]->CbobL= Label7;

        for(int i = 0; i < OFunc->ODCboBox2_Nbr; i++){
                ODCboB2[i]->Addr = OD_cbo2[i];
                ODCboB2[i]->Cbob->Visible = ODCboB2[i]->Addr.FuncEn();
                ODCboB2[i]->Cbob->OnClick = OD_ComboBox2_Click;
                ODCboB2[i]->Cbob->Hint = i;
                ODCboB2[i]->CbobL->Caption = ODCboB2[i]->Addr.Name();
                ODCboB2[i]->Cbob->Text = "";
                if(ODCboB2[i]->Addr.FuncEn())
                        for(int j = 0; j< ODCboB2[i]->Addr.choice_nbr; j++)     //ComboBox choice
                                ODCboB2[i]->Cbob->Items->Add(ODCboB2[i]->Addr.choice[j]);
        }
        //ScrollBar
        OD_ScrlB = OFunc->SetODScrollBar();

        ODScrlB = new _ScrollBar* [OFunc->ODScrollBar_Nbr];
        for(int i = 0; i < OFunc->ODScrollBar_Nbr; i++)
                ODScrlB[i] = new _ScrollBar;

        ODScrlB[0]->Lbl = Label8;
        ODScrlB[0]->StTxt = StaticText1;
        ODScrlB[0]->ScrlB = ScrollBar1;

        ODScrlB[1]->Lbl = Label9;
        ODScrlB[1]->StTxt = StaticText2;
        ODScrlB[1]->ScrlB = ScrollBar2;

        ODScrlB[2]->Lbl = Label10;
        ODScrlB[2]->StTxt = StaticText3;
        ODScrlB[2]->ScrlB = ScrollBar3;

        for(int i = 0; i < OFunc->ODScrollBar_Nbr; i++){
                ODScrlB[i]->Addr = OD_ScrlB[i];
                ODScrlB[i]->Lbl->Visible = ODScrlB[i]->Addr.FuncEn();
                ODScrlB[i]->StTxt->Visible = ODScrlB[i]->Addr.FuncEn();
                ODScrlB[i]->ScrlB->Visible = ODScrlB[i]->Addr.FuncEn();
                ODScrlB[i]->ScrlB->Min = 0;
                ODScrlB[i]->ScrlB->Max = (int)pow(2,ODScrlB[i]->Addr.BitNum())-1;
                ODScrlB[i]->ScrlB->OnScroll = OD_ScrollBar_Scroll;
                ODScrlB[i]->ScrlB->Hint = i;
                ODScrlB[i]->StTxt->Caption = 0;
                ODScrlB[i]->Lbl->Caption = ODScrlB[i]->Addr.Name();
        }
        Func_Chg = 1;
}
//---------------------------------------------------------------------------


void __fastcall TFunctionForm1::btn_dg_wrtClick(TObject *Sender)
{
        btn_dg_wrt->Enabled = false;
        int length = Addr_DgLUT[0].LutNum();
        int* lut = new int [length];
        //int *DG_table[3];

        //calculate checksum
        int chksum = 0;
        for(int i = 0; i < 3; i++){
                for(int j = 0; j < length; j++){
                        chksum += StrToInt(sg_dg->Cells[i+1][j+1]);
                }
        }
        dg_writechk->Caption = chksum;

          //checksum byte
        TBit ad1, ad2;
        ad1.set(1872, 0, 8, "");
        ad2.set(1873, 0 , 8, "");
        EngineerForm->SetWrite_Byte(ad1 ,(chksum/256)%256);
        EngineerForm->SetWrite_Byte(ad2 ,chksum%256);

        for(int i = 0; i < 3; i++){
                for(int j = 0; j < length; j++){
                        lut[j] = StrToInt(sg_dg->Cells[i+1][j+1]);
                }
                
                //Send 3 times each with R,G,B 3 channels
                EngineerForm->SetWrite_PG(Addr_DgLUT[i], lut, length);
                Sleep(10);
                /*
                int dif = 0;
                DG_table[i] = new int [Addr_DgLUT[i].LutNum()];
                EngineerForm->SetRead_DG(Addr_DgLUT[i], DG_table[i], length);
                for(int j = 0; j < length; j++)
                        if(DG_table[i][j] != lut[j])
                               dif++;
                */
        }
        delete [] lut;
        //delete [] DG_table;
        btn_dg_wrt->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::btn_dg_readClick(TObject *Sender)
{
        btn_dg_read->Enabled = false;
        int length = Addr_DgLUT[0].LutNum();
        int **DG_table = new int* [3];

        unsigned char read_val1, read_val2;
        TBit ad1, ad2;
        ad1.set(1872, 0, 8, "");
        ad2.set(1873, 0, 8, "");
        EngineerForm->SetRead_Byte(ad1, &read_val1);
        EngineerForm->SetRead_Byte(ad2, &read_val2);

        int chksum=0;
        for(int i = 0; i <= 2; i++){
                //Send 3 times for each with R,G,B 3 channels
                DG_table[i] = new int [Addr_DgLUT[i].LutNum()];
                EngineerForm->SetRead_DG(Addr_DgLUT[i], DG_table[i], length);
                if(DG_table[i]==NULL){
                        ShowMessage("DG_table == NULL");
                        return;
                }
                for(int j = 0; j <= length-1; j++){     //To GUI
                        sg_dg->Cells[i+1][j+1] = IntToStr(DG_table[i][j]);
                        chksum+=DG_table[i][j];
                }
        }
        dg_readchk->Caption = chksum;
        delete [] DG_table;
        btn_dg_read->Enabled = true;
}
//---------------------------------------------------------------------------




void __fastcall TFunctionForm1::btn_dg_loadClick(TObject *Sender)
{
        String Fpath;
        if (LoadDialog->Execute()){
               Fpath = LoadDialog->FileName;
               String *DG_LUT = NULL;
               DG_LUT = EngineerForm->Load_file(Fpath, Addr_DgLUT[0].LutNum()*3);
               if(DG_LUT==NULL){
                        ShowMessage("Load file fail!");
                        return;
               }

                for(int c=0; c<=2; c++){
                        for(int r = 0; r<Addr_DgLUT[0].LutNum(); r++){
                                sg_dg->Cells[c+1][r+1] = StrToInt(DG_LUT[r*3+c]);
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::btn_dg_saveClick(TObject *Sender)
{
        if(!SaveDialog->Execute())
                return;
        String Fpath = SaveDialog->FileName/*+".txt"*/;
        FILE* fptr = fopen (Fpath.c_str(),"w");
        //fprintf(fptr,"R\tG\tB\n");
        for(int i = 0; i < Addr_DgLUT[0].LutNum(); i++){
                fprintf(fptr,"%d\t", StrToInt(sg_dg->Cells[1][i+1]));
                fprintf(fptr,"%d\t", StrToInt(sg_dg->Cells[2][i+1]));
                fprintf(fptr,"%d\n", StrToInt(sg_dg->Cells[3][i+1]));
        }
        fclose(fptr);
}
//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::Btn_FRC_DG_reloadClick(TObject *Sender)
{
        Btn_FRC_DG_reload->Enabled = false;
        Func_Chg = 0;
        unsigned char read_val;
        for(int i = 0; i < OFunc->FrcDgChkBox_Nbr; i++){
                if(FrcDgChkB[i]->Chkb->Visible==true){
                        EngineerForm->SetRead_Byte(FrcDgChkB[i]->Addr, &read_val);
                        if(read_val==1)
                                FrcDgChkB[i]->Chkb->Checked = 1;
                        else if(read_val==0)
                                FrcDgChkB[i]->Chkb->Checked = 0;
                        else
                                ShowMessage("FRC/DG CheckBox read error:"+IntToStr(read_val));
                }
        }
        for(int i = 0; i < OFunc->FrcDgCboBox_Nbr; i++){
                if(FrcDgCboB[i]->Cbob->Visible==true){
                        EngineerForm->SetRead_Byte(FrcDgCboB[i]->Addr, &read_val);
                        FrcDgCboB[i]->Cbob->ItemIndex = read_val;
                }
        }
        for(int i = 0; i < OFunc->FrcDgLblE_Nbr; i++){
                if(FrcDgLblE[i]->Lble->Visible==true){
                        EngineerForm->SetRead_Byte(FrcDgLblE[i]->Addr, &read_val);
                        FrcDgLblE[i]->Lble->Text = read_val;
                        FrcDgLblE[i]->Lble->Font->Color = clWindowText;
                }
        }
        btn_dg_readClick(Sender);
        Func_Chg = 1;
        Btn_FRC_DG_reload->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::Btn_Pstate_reloadClick(TObject *Sender)
{
        Btn_Pstate_reload->Enabled = false;
        Func_Chg = 0;
        unsigned char read_val;
        for(int i = 0; i < OFunc->PstateChkBox_Nbr; i++){
                if(PstateChkB[i]->Chkb->Visible==true){
                        EngineerForm->SetRead_Byte(PstateChkB[i]->Addr, &read_val);
                        if(read_val==1)
                                PstateChkB[i]->Chkb->Checked = 1;
                        else if(read_val==0)
                                PstateChkB[i]->Chkb->Checked = 0;
                        else
                                ShowMessage("FRC/DG CheckBox read error:"+IntToStr(read_val));
                }
        }
        for(int i = 0; i < OFunc->PstateCboBox_Nbr; i++){
                if(PstateCboB[i]->Cbob->Visible==true){
                        EngineerForm->SetRead_Byte(PstateCboB[i]->Addr, &read_val);
                        PstateCboB[i]->Cbob->ItemIndex = read_val;
                }
        }

        unsigned char read_val1, read_val2;
        for(int i = 0; i < OFunc->PstateLblE2_Nbr; i++){
                if(PstateLblE2[i]->Lble->Visible==true){
                        EngineerForm->SetRead_Byte(PstateLblE2[i]->Addr.Byte1, &read_val1);
                        EngineerForm->SetRead_Byte(PstateLblE2[i]->Addr.Byte2, &read_val2);
                        PstateLblE2[i]->Lble->Text = (int)read_val1*PstateLblE2[i]->Addr.Divide()+read_val2;
                        PstateLblE2[i]->Lble->Font->Color = clWindowText;
                }
        }
        Func_Chg = 1;
        Btn_Pstate_reload->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::Btn_AGBS_reloadClick(TObject *Sender)
{
        Btn_AGBS_reload->Enabled = false;
        Func_Chg = 0;
        unsigned char read_val;
        for(int i = 0; i < OFunc->AGBSChkBox_Nbr; i++){
                if(AGBSChkB[i]->Chkb->Visible==true){
                        EngineerForm->SetRead_Byte(AGBSChkB[i]->Addr, &read_val);
                        if(read_val==1)
                                AGBSChkB[i]->Chkb->Checked = 1;
                        else if(read_val==0)
                                AGBSChkB[i]->Chkb->Checked = 0;
                        else
                                ShowMessage("FRC/DG CheckBox read error:"+IntToStr(read_val));
                }
        }
        for(int i = 0; i < OFunc->AGBSCboBox_Nbr; i++){
                if(AGBSCboB[i]->Cbob->Visible==true){
                        EngineerForm->SetRead_Byte(AGBSCboB[i]->Addr, &read_val);
                        AGBSCboB[i]->Cbob->ItemIndex = read_val;
                }
        }
        unsigned char read_val1, read_val2;
        for(int i = 0; i < OFunc->AGBSLblE2_Nbr; i++){
                if(AGBSLblE2[i]->Lble->Visible==true){
                        EngineerForm->SetRead_Byte(AGBSLblE2[i]->Addr.Byte1, &read_val1);
                        EngineerForm->SetRead_Byte(AGBSLblE2[i]->Addr.Byte2, &read_val2);
                        AGBSLblE2[i]->Lble->Text = (int)read_val1*AGBSLblE2[i]->Addr.Divide()+read_val2;
                        AGBSLblE2[i]->Lble->Font->Color = clWindowText;
                }
        }
        Func_Chg = 1;
        Btn_AGBS_reload->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TFunctionForm1::Btn_OD_reloadClick(TObject *Sender)
{
        Btn_OD_reload->Enabled = false;
        Func_Chg = 0;
        unsigned char read_val;
        for(int i = 0; i < OFunc->ODChkBox_Nbr; i++){
                if(ODChkB[i]->Chkb->Visible==true){
                        EngineerForm->SetRead_Byte(ODChkB[i]->Addr, &read_val);
                        if(read_val==1)
                                ODChkB[i]->Chkb->Checked = 1;
                        else if(read_val==0)
                                ODChkB[i]->Chkb->Checked = 0;
                        else
                                ShowMessage("OD CheckBox read error:"+IntToStr(read_val));
                }
        }
        for(int i = 0; i < OFunc->ODCboBox_Nbr; i++){
                if(ODCboB[i]->Cbob->Visible==true){
                        EngineerForm->SetRead_Byte(ODCboB[i]->Addr, &read_val);
                        ODCboB[i]->Cbob->ItemIndex = read_val;
                }
        }
        unsigned char read_val1, read_val2;
        for(int i = 0; i < OFunc->ODCboBox2_Nbr; i++){
                if(ODCboB2[i]->Cbob->Visible==true){
                        EngineerForm->SetRead_Byte(ODCboB2[i]->Addr.Byte1, &read_val1);
                        EngineerForm->SetRead_Byte(ODCboB2[i]->Addr.Byte2, &read_val2);
                        ODCboB2[i]->Cbob->Text = (int)read_val1*ODCboB2[i]->Addr.Divide()+read_val2;
                }
        }
        for(int i = 0; i < OFunc->ODScrollBar_Nbr; i++){
                if(ODScrlB[i]->ScrlB->Visible==true){
                        EngineerForm->SetRead_Byte(ODScrlB[i]->Addr, &read_val);
                        ODScrlB[i]->ScrlB->Position = read_val;
                        ODScrlB[i]->StTxt->Caption = read_val;
                }
        }
        Func_Chg = 1;
        Btn_OD_reload->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TFunctionForm1::btn_od1_loadClick(TObject *Sender)
{
        String Fpath;
        if (LoadDialog->Execute()){
               Fpath = LoadDialog->FileName;
               String *OD_LUT = NULL;
               OD_LUT = EngineerForm->Load_file(Fpath, Addr_ODLUT1[0].LutNum()*4);
               if(OD_LUT==NULL){
                        ShowMessage("Load file fail!");
                        return;
               }

                for(int c=0; c<=3; c++){
                        for(int r = 0; r<Addr_ODLUT1[0].LutNum(); r++){
                                sg_od1->Cells[c+1][r+1] = StrToInt(OD_LUT[r*4+c])%256;
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::btn_od2_readClick(TObject *Sender)
{
        btn_od2_read->Enabled = false;
        int length = Addr_ODLUT2[0].LutNum();
        int **OD_table = new int* [4];

        for(int i = 0; i <= 3; i++){
                //Send 4 times
                OD_table[i] = new int [Addr_ODLUT2[i].LutNum()];
                EngineerForm->SetRead_OD(Addr_ODLUT2[i], OD_table[i], length);
                if(OD_table[i]==NULL){
                        ShowMessage("OD_table == NULL");
                        return;
                }
                for(int j = 0; j <= length-1; j++){     //To GUI
                        sg_od2->Cells[i+1][j+1] = IntToStr(OD_table[i][j]);
                }
        }
        for(int i = 0; i < 4; i ++)
                delete [] OD_table[i];
        delete [] OD_table;
        btn_od2_read->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::btn_od1_saveClick(TObject *Sender)
{
        if(!SaveDialog->Execute())
                return;
        String Fpath = SaveDialog->FileName/*+".txt"*/;
        FILE* fptr = fopen (Fpath.c_str(),"w");
        //fprintf(fptr,"R\tG\tB\n");
        for(int i = 0; i < Addr_ODLUT1[0].LutNum(); i++){
                fprintf(fptr,"%d\t", StrToInt(sg_od1->Cells[1][i+1]));
                fprintf(fptr,"%d\t", StrToInt(sg_od1->Cells[2][i+1]));
                fprintf(fptr,"%d\t", StrToInt(sg_od1->Cells[3][i+1]));
                fprintf(fptr,"%d\n", StrToInt(sg_od1->Cells[4][i+1]));
        }
        fclose(fptr);
}
//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::btn_od2_saveClick(TObject *Sender)
{
        if(!SaveDialog->Execute())
                return;
        String Fpath = SaveDialog->FileName/*+".txt"*/;
        FILE* fptr = fopen (Fpath.c_str(),"w");
        //fprintf(fptr,"R\tG\tB\n");
        for(int i = 0; i < Addr_ODLUT2[0].LutNum(); i++){
                fprintf(fptr,"%d\t", StrToInt(sg_od2->Cells[1][i+1]));
                fprintf(fptr,"%d\t", StrToInt(sg_od2->Cells[2][i+1]));
                fprintf(fptr,"%d\t", StrToInt(sg_od2->Cells[3][i+1]));
                fprintf(fptr,"%d\n", StrToInt(sg_od2->Cells[4][i+1]));
        }
        fclose(fptr);
}
//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::btn_od1_readClick(TObject *Sender)
{
        btn_od1_read->Enabled = false;
        int length = Addr_ODLUT1[0].LutNum();
        int **OD_table = new int* [4];

        for(int i = 0; i <= 3; i++){
                //Send 4 times
                OD_table[i] = new int [Addr_ODLUT1[i].LutNum()];
                EngineerForm->SetRead_OD(Addr_ODLUT1[i], OD_table[i], length);
                if(OD_table[i]==NULL){
                        ShowMessage("OD_table == NULL");
                        return;
                }
                for(int j = 0; j <= length-1; j++){     //To GUI
                        sg_od1->Cells[i+1][j+1] = IntToStr(OD_table[i][j]);
                }
        }
        for(int i = 0; i < 4; i ++)
                delete [] OD_table[i];
        delete [] OD_table;
        btn_od1_read->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::btn_od2_loadClick(TObject *Sender)
{
        String Fpath;
        if (LoadDialog->Execute()){
               Fpath = LoadDialog->FileName;
               String *OD_LUT = NULL;
               OD_LUT = EngineerForm->Load_file(Fpath, Addr_ODLUT2[0].LutNum()*4);
               if(OD_LUT==NULL){
                        ShowMessage("Load file fail!");
                        return;
               }

                for(int c=0; c<=3; c++){
                        for(int r = 0; r<Addr_ODLUT2[0].LutNum(); r++){
                                sg_od2->Cells[c+1][r+1] = StrToInt(OD_LUT[r*4+c])%256;
                        }
                }
        }

}
//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::btn_od1_writeClick(TObject *Sender)
{
        btn_od1_write->Enabled = false;
        int length = Addr_ODLUT1[0].LutNum();
        int* lut = new int [length];
        int *OD_table[4];
        for(int i = 0; i < 4; i++){
                for(int j = 0; j < length; j++){
                        lut[j] = StrToInt(sg_od1->Cells[i+1][j+1]);
                }
                OD_table[i] = new int [Addr_ODLUT1[i].LutNum()];
                int dif = 0;
                //Send 3 times each with R,G,B 3 channels
                EngineerForm->SetWrite_PG(Addr_ODLUT1[i], lut, length);
                Sleep(20);
                EngineerForm->SetRead_OD(Addr_ODLUT1[i], OD_table[i], length);
                for(int j = 0; j < length; j++)
                        if(OD_table[i][j] != lut[j])
                                dif++;
        }
        delete [] lut;
        delete [] OD_table;
        btn_od1_write->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::btn_od2_writeClick(TObject *Sender)
{
        btn_od2_write->Enabled = false;
        int length = Addr_ODLUT2[0].LutNum();
        int* lut = new int [length];
        int *OD_table[4];
        for(int i = 0; i < 4; i++){
                for(int j = 0; j < length; j++){
                        lut[j] = StrToInt(sg_od2->Cells[i+1][j+1]);
                }
                OD_table[i] = new int [Addr_ODLUT2[i].LutNum()];
                int dif = 0;
                //Send 3 times each with R,G,B 3 channels
                EngineerForm->SetWrite_PG(Addr_ODLUT2[i], lut, length);
                Sleep(20);
                EngineerForm->SetRead_OD(Addr_ODLUT2[i], OD_table[i], length);
                for(int j = 0; j < length; j++)
                        if(OD_table[i][j] != lut[j])
                                dif++;
        }
        delete [] lut;
        delete [] OD_table;
        btn_od2_write->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TFunctionForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 0x40){
                Btn_FRC_DG_reloadClick(Sender);
                Btn_Pstate_reloadClick(Sender);
                Btn_AGBS_reloadClick(Sender);
                Btn_OD_reloadClick(Sender);
        }
}
//---------------------------------------------------------------------------

