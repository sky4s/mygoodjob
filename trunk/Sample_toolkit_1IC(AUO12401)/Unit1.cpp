//---------------------------------------------------------------------------

#pragma hdrstop
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;

TForm *TCONForm;
TForm *FunctionForm;
TForm *DCRForm;
TForm *VenderForm;
TForm *CMForm;
TForm *SharpnessForm;
TForm *ContrastEnhanceForm;
TForm *HSVForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
        //Set Real-Time Priority of process
        SetPriorityClass(GetCurrentProcess(),REALTIME_PRIORITY_CLASS);
        addr_place = 0;    //0:auo_12401_address.h   1:auo_12401_address.txt
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::mn_TCONClick(TObject *Sender)
{
        if(TCONForm!=NULL)
                TCONForm->Show();
        else{
                if(TCON_DEV=="12401"){
                        TCONForm = new TTCONForm1(this);
                        TCONForm->Show();
                }
                /*else if(TCON_DEV=="12303"){
                        TCONForm = new TTCONForm2(this);
                        TCONForm->Show();
                }*/
        }
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_EngineerClick(TObject *Sender)
{
        EngineerForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_FunctionClick(TObject *Sender)
{
        if(FunctionForm!=NULL)
                FunctionForm->Show();
        else{
                if(TCON_DEV=="12401"){
                        FunctionForm = new TFunctionForm1(this);
                        FunctionForm->Show();
                }/*else if(TCON_DEV=="12303"){
                        FunctionForm = new TFunctionForm2(this);
                        FunctionForm->Show();
                }*/
        }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_DCRClick(TObject *Sender)
{
        if(DCRForm!=NULL)
                DCRForm->Show();
        else{
                if(TCON_DEV=="12401"){
                        DCRForm = new TDCRForm1(this);
                        DCRForm->Show();
                }
                /*else if(TCON_DEV=="12303"){
                        DCRForm = new TDCRForm2(this);
                        DCRForm->Show();
                }*/
        }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mn_VenderClick(TObject *Sender)
{
        if(VenderForm!=NULL)
                VenderForm->Show();
        else{
                if(TCON_DEV=="12401"){
                        VenderForm = new TVenderForm1(this);
                        VenderForm->Show();
                }
                /*else if(TCON_DEV=="12303"){
                        VenderForm = new TVenderForm2(this);
                        VenderForm->Show();
                }*/
        }
}

//---------------------------------------------------------------------------
void TMainForm::TCONFormNULL()
{
        TCONForm = NULL;
}
void TMainForm::FunctionFormNULL()
{
        FunctionForm = NULL;
}
void TMainForm::DCRFormNULL()
{
        DCRForm = NULL;
}
void TMainForm::VenderFormNULL()
{
        VenderForm = NULL;
}
void TMainForm::CMFormNULL()
{
        CMForm = NULL;
}
void TMainForm::SharpnessFormNULL()
{
        SharpnessForm = NULL;
}
void TMainForm::ContrastEnhanceFormNULL()
{
        ContrastEnhanceForm = NULL;
}
void TMainForm::HSVFormNULL()
{
        HSVForm = NULL;
}
void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
        EngineerForm->FormClose(Sender, Action);

        if(TCONForm!=NULL){
               TCONForm->Close();
               TCONForm = NULL;
               delete TCONForm;
        }
        if(FunctionForm!=NULL){
                FunctionForm->Close();
                FunctionForm = NULL;
                delete FunctionForm;
        }
        if(DCRForm!=NULL){
                DCRForm->Close();
                DCRForm = NULL;
                delete DCRForm;
        }
        if(VenderForm!=NULL){
                VenderForm->Close();
                VenderForm = NULL;
                delete VenderForm;
        }
        if(CMForm!=NULL){
                CMForm->Close();
                CMForm = NULL;
                delete CMForm;
        }
        if(SharpnessForm!=NULL){
                SharpnessForm->Close();
                SharpnessForm = NULL;
                delete SharpnessForm;
        }
        if(ContrastEnhanceForm!=NULL){
                ContrastEnhanceForm->Close();
                ContrastEnhanceForm = NULL;
                delete ContrastEnhanceForm;
        }
        if(HSVForm!=NULL){
                HSVForm->Close();
                HSVForm = NULL;
                delete HSVForm;
        }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::AUO_12401Click(TObject *Sender)
{
        if(TCONForm!=NULL){
               TCONForm->Close();
               TCONForm = NULL;
        }
        if(FunctionForm!=NULL){
                FunctionForm->Close();
                FunctionForm = NULL;
        }
        if(DCRForm!=NULL){
                DCRForm->Close();
                DCRForm = NULL;
        }
        if(VenderForm!=NULL){
                VenderForm->Close();
                VenderForm = NULL;
        }
        if(CMForm!=NULL){
                CMForm->Close();
                CMForm = NULL;
        }
        if(SharpnessForm!=NULL){
                SharpnessForm->Close();
                SharpnessForm = NULL;
        }

        TCON_DEV = "12401";
        MainForm->Caption = "AUO 12401";
        mn_Function->Enabled = true;
        mn_TCON->Enabled = true;
        mn_DCR->Enabled = true;
        mn_Vender->Enabled = true;
        mn_ImageProc->Enabled = true;
        mn_CE->Enabled = true;
        mn_HSV->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::AUO_12303Click(TObject *Sender)
{
        if(TCONForm!=NULL){
               TCONForm->Close();
               TCONForm = NULL;
        }
        if(FunctionForm!=NULL){
                FunctionForm->Close();
                FunctionForm = NULL;
        }
        if(DCRForm!=NULL){
                DCRForm->Close();
                DCRForm = NULL;
        }
        if(VenderForm!=NULL){
                VenderForm->Close();
                VenderForm = NULL;
        }
        if(CMForm!=NULL){
                CMForm->Close();
                CMForm = NULL;
        }
        if(SharpnessForm!=NULL){
                SharpnessForm->Close();
                SharpnessForm = NULL;
        }

        TCON_DEV = "12303";
        MainForm->Caption = "AUO 12303";
        mn_TCON->Enabled = true;
        mn_Function->Enabled = true;
        mn_Vender->Enabled = true;
        mn_DCR->Enabled = true;
        mn_ImageProc->Enabled = true;
        mn_CM->Enabled = true;
        mn_Sharpness->Enabled = true;
        mn_CE->Enabled = false;
        mn_HSV->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject *Sender)
{
        TCON_DEV = "12401";     //default device
        MainForm->Caption = "AUO 12401";
        mn_Function->Enabled = true;
        mn_TCON->Enabled = true;
        mn_DCR->Enabled = true;
        mn_Vender->Enabled = true;
        mn_ImageProc->Enabled = true;
        mn_CM->Enabled = true;
        mn_Sharpness->Enabled = true;
        mn_CE->Enabled = true;
        mn_HSV->Enabled = true;
}
//---------------------------------------------------------------------------
void TMainForm::reload_all(TObject *Sender)
{
        mn_TCONClick(Sender);
        mn_FunctionClick(Sender);
        mn_DCRClick(Sender);
        mn_VenderClick(Sender);
        mn_CMClick(Sender);
        mn_SharpnessClick(Sender);
        mn_CEClick(Sender);
        mn_HSVClick(Sender);
        TShiftState Shift;
        WORD Key = 0x40;
        TCONForm->OnKeyDown(Sender, Key, Shift);
        FunctionForm->OnKeyDown(Sender, Key, Shift);
        DCRForm->OnKeyDown(Sender, Key, Shift);
        VenderForm->OnKeyDown(Sender, Key, Shift);
        CMForm->OnKeyDown(Sender, Key, Shift);
        SharpnessForm->OnKeyDown(Sender, Key, Shift);
        ContrastEnhanceForm->OnKeyDown(Sender, Key, Shift);
        HSVForm->OnKeyDown(Sender, Key, Shift);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_CMClick(TObject *Sender)
{
        if(CMForm!=NULL)
                CMForm->Show();
        else{
                if(TCON_DEV=="12401"){
                        CMForm = new TCMForm1(this);
                        CMForm->Show();
                }
                /*else if(TCON_DEV=="12303"){
                        CMForm = new TCMForm2(this);
                        CMForm->Show();

                }*/
        }
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::mn_SharpnessClick(TObject *Sender)
{
        if(SharpnessForm!=NULL)
                SharpnessForm->Show();
        else{
                if(TCON_DEV=="12401"){
                        SharpnessForm = new TSharpnessForm1(this);
                        SharpnessForm->Show();
                }
                /*else if(TCON_DEV=="12303"){
                        SharpnessForm = new TSharpnessForm2(this);
                        SharpnessForm->Show();

                }*/
        }
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormMouseDown(TObject *Sender, TMouseButton Button,
      TShiftState Shift, int X, int Y)
{
        if (Button == mbRight){
                TPoint pt=MainForm->ClientToScreen(Point(X, Y));
                PopupMenu1->Popup(pt.x, pt.y);
        }

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::mn_CEClick(TObject *Sender)
{
        if(ContrastEnhanceForm!=NULL)
                ContrastEnhanceForm->Show();
        else{
                if(TCON_DEV=="12401"){
                        ContrastEnhanceForm = new TContrastEnhanceForm1(this);
                        ContrastEnhanceForm->Show();
                }
        }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_HSVClick(TObject *Sender)
{
        if(HSVForm!=NULL)
                HSVForm->Show();
        else{
                if(TCON_DEV=="12401"){
                        HSVForm = new THSVForm1(this);
                        HSVForm->Show();
                }
        }

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::cb_address_txtClick(TObject *Sender)
{
        if(cb_address_txt->Checked == true)
                addr_place = 1;
        else
                addr_place = 0;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StatusBar1DblClick(TObject *Sender)
{
         cb_address_txt->Visible = true;
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

