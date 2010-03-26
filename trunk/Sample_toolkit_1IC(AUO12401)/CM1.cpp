//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CM1.h"
#include "ImgProc_12401.h"
#include "Engineering.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "PERFGRAP"
#pragma resource "*.dfm"
//TCMForm1 *CMForm1;

AbstCM* OCM;

TBit* cm_cb;
_CHKB** CMChkB;

TBit* cm_cbo;
_CBOB** CMCboB;

TLUT *CM_addr, *ofs_addr;

int CMofs_type;

bool CM_Chg = 0;

float CM1[3][3];
float CM2[3][3];
float CM3[3][3];


void CM_val_initial()
{
        for(int i = 0; i < 3; i++){
                for(int j = 0; j < 3; j++){
                        CM1[i][j] = 0;
                        CM2[i][j] = 0;
                        CM3[i][j] = 0;
                }
                CM1[i][i] = 1;
                CM2[i][i] = 1;
                CM3[i][i] = 1;
        }
}
//---------------------------------------------------------------------------
__fastcall TCMForm1::TCMForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TCMForm1::CM_CheckBox_Click(TObject *Sender)
{
        if(CM_Chg==0)
                return;
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (CMChkB[idx]->Chkb->Checked?1:0);
        EngineerForm->SetWrite_Byte(CMChkB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall TCMForm1::CM_ComboBox_Click(TObject *Sender)
{
        if(CM_Chg==0)
                return;
        TComboBox *c = (TComboBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (CMCboB[idx]->Cbob->ItemIndex);
        EngineerForm->SetWrite_Byte(CMCboB[idx]->Addr ,set_val);
        if(idx == 0){    //CM_SEL
                TS_CM->TabIndex = CMCboB[idx]->Cbob->ItemIndex-1;
                if(TS_CM->TabIndex==0){
                        TS_CM->ActivePage = th_CM1;
                        TS_CM->Visible = true;
                }else if (TS_CM->TabIndex==1){
                        TS_CM->ActivePage = th_CM2;
                        TS_CM->Visible = true;
                }else if (TS_CM->TabIndex==2){
                        TS_CM->ActivePage = th_CM3;
                        TS_CM->Visible = true;
                }else
                        TS_CM->Visible = false;
        }
}
//---------------------------------------------------------------------------
void __fastcall TCMForm1::FormCreate(TObject *Sender)
{
        CM_Chg = 0;
        int ic_choice;
        if(MainForm->TCON_DEV=="12401")
                ic_choice = 0;

        switch(ic_choice)
        {
                case 0:
                OCM = new CM_12401;
                break;
        }

        /********************************************************************/
        //                                                                  //
        //  Image Process CM has CheckBox*3 & ComboBox*1  & CM*3 & ofs*3    //
        //                                                                  //
        //******************************************************************//

        //CheckBox
        //cm_cb = OCM->SetChkBx(cm_cb);
        cm_cb = OCM->SetChkBx();

        CMChkB = new _CHKB* [OCM->CMChkBox_Nbr];
        for(int i = 0; i < OCM->CMChkBox_Nbr; i++)
                CMChkB[i] = new _CHKB;

        CMChkB[0]->Chkb = CheckBox1;
        CMChkB[1]->Chkb = CheckBox2;
        CMChkB[2]->Chkb = CheckBox3;

        for(int i = 0; i < OCM->CMChkBox_Nbr; i++){
                CMChkB[i]->Addr = cm_cb[i];
                CMChkB[i]->Chkb->Visible = CMChkB[i]->Addr.FuncEn();
                CMChkB[i]->Chkb->OnClick = CM_CheckBox_Click;
                CMChkB[i]->Chkb->Hint = i;
                CMChkB[i]->Chkb->Caption = CMChkB[i]->Addr.Name();
        } 

        //Combobox
        cm_cbo = OCM->SetCboBx();

        CMCboB = new _CBOB* [OCM->CMCboBox_Nbr];
        for(int i = 0; i < OCM->CMCboBox_Nbr; i++)
                CMCboB[i] = new _CBOB;

        CMCboB[0]->Cbob = ComboBox1;
        CMCboB[0]->CbobL= Label4;

        for(int i = 0; i < OCM->CMCboBox_Nbr; i++){
                CMCboB[i]->Addr = cm_cbo[i];
                CMCboB[i]->Cbob->Visible = CMCboB[i]->Addr.FuncEn();
                CMCboB[i]->CbobL->Visible = CMCboB[i]->Addr.FuncEn();
                CMCboB[i]->Cbob->OnClick = CM_ComboBox_Click;
                CMCboB[i]->Cbob->Hint = i;
                CMCboB[i]->CbobL->Caption = CMCboB[i]->Addr.Name();
                CMCboB[i]->Cbob->Text = "";
                if(CMCboB[i]->Addr.FuncEn())
                        for(int j = 0; j< CMCboB[i]->Addr.choice_nbr; j++)     //ComboBox choice
                                CMCboB[i]->Cbob->Items->Add(CMCboB[i]->Addr.choice[j]);
        }

        //CM value
        CM_addr = OCM->Setval();
        CM_val_initial();

        float tmp = sb_cm11->Position;
        st_CM11gain->Caption = FloatToStr(tmp)+"%";
        tmp = sb_cm12->Position;
        st_CM12gain->Caption = FloatToStr(tmp)+"%";
        tmp = sb_cm13->Position;
        st_CM13gain->Caption = FloatToStr(tmp)+"%";

        //offset value
        ofs_addr = OCM->Setofs();
        st_ofs1->Caption = 0;
        st_ofs2->Caption = 0;
        st_ofs3->Caption = 0;
        CMofs_type = OCM->Setofs_type();
        CM_Chg = 1;

}
//---------------------------------------------------------------------------
void __fastcall TCMForm1::Btn_CM_reloadClick(TObject *Sender)
{
        Btn_CM_reload->Enabled = false;
        CM_Chg = 0;
        unsigned char read_val;
        for(int i = 0; i < OCM->CMChkBox_Nbr; i++){
                if(CMChkB[i]->Chkb->Visible==true){
                        EngineerForm->SetRead_Byte(CMChkB[i]->Addr, &read_val);
                        if(read_val==1)
                                CMChkB[i]->Chkb->Checked = 1;
                        else if(read_val==0)
                                CMChkB[i]->Chkb->Checked = 0;
                        else
                                ShowMessage("CM CheckBox read error:"+IntToStr(read_val));
                }
        }
        for(int i = 0; i < OCM->CMCboBox_Nbr; i++){
                if(CMCboB[i]->Cbob->Visible==true){
                        EngineerForm->SetRead_Byte(CMCboB[i]->Addr, &read_val);
                        CMCboB[i]->Cbob->ItemIndex = read_val;
                }
        }
        btn_CM1_ReadClick(Sender);
        btn_CM2_ReadClick(Sender);
        btn_CM3_ReadClick(Sender);
        CM_Chg = 1;
        Btn_CM_reload->Enabled = true;        
}

//---------------------------------------------------------------------------
int FloatToMemForm(int temp)    //CM 10bit value to sign value
{
        if (temp>511)
                temp=511;
        if(temp<0){
                temp = 512-temp;
                if(temp>1023)
                        temp=1023;
        }
        return temp;
}
//-----------------------------------------------------------------------------
int MemToFloatForm(int mem)     //CM 10bit from sign value to 10bit value
{
        if(mem>512)
               mem = 512-mem;
        return mem;
}

//---------------------------------------------------------------------------
//CM offset 10bit from 10bit value to 2's complement value
int FloatToMemOfsForm(int ofs, int ofs_type)
{
        ofs -= 256;
        if(ofs >= 0){
                ofs = ofs*2;
        }else{
                if(ofs_type==2)
                        ofs = 512-ofs*2;
                else if(ofs_type == 1)   //2's completement
                        ofs = 1024+ofs*2;
        }
        return ofs;
}
//-----------------------------------------------------------------------------
//CM offset 10bit from 2's complement value to 10 bit value
int MemToFloatOfsForm(int ofs, int ofs_type)
{
        if(ofs<512){
                ofs = ofs/2;
        }else{
                if(ofs_type==2)
                        ofs = 512-ofs;
                else if(ofs_type == 1)   //2's completement
                        ofs = ofs-1024;
                ofs = ofs/2;
        }
        ofs += 256;
        return ofs;
}

//---------------------------------------------------------------------------

void __fastcall TCMForm1::btn_CM1_ReadClick(TObject *Sender)
{
        btn_CM1_Read->Enabled = false;

        //Write CM
        if(CM_addr[0].LutNum()!=9){     //Check CM1 table number
                ShowMessage("CM1 LUT number defined in AddressCM.cpp is wrong.");
                return;
        }
        int* CM = new int [CM_addr[0].LutNum()];
        EngineerForm->SetRead_CM(CM_addr[0], CM, CM_addr[0].LutNum());

        float* CM_f = new float [CM_addr[0].LutNum()];
        for(int i = 0; i < CM_addr[0].LutNum(); i++){
                CM_f[i] = (double)(MemToFloatForm(CM[i]))/256;
        }
        CM1_11->Text = FloatToStr(CM_f[0]);
        CM1_12->Text = FloatToStr(CM_f[1]);
        CM1_13->Text = FloatToStr(CM_f[2]);
        CM1_21->Text = FloatToStr(CM_f[3]);
        CM1_22->Text = FloatToStr(CM_f[4]);
        CM1_23->Text = FloatToStr(CM_f[5]);
        CM1_31->Text = FloatToStr(CM_f[6]);
        CM1_32->Text = FloatToStr(CM_f[7]);
        CM1_33->Text = FloatToStr(CM_f[8]);

        float ofs[3];
        EngineerForm->SetRead_CMofs(ofs_addr[0], ofs, ofs_addr[0].LutNum());

        if(ofs[0]!=ofs[1] || ofs[1]!=ofs[2])
                ShowMessage("The 3 Offset values are different.");

        int sb_position;
        float s;
        if(ofs_addr[0].Type()==3){
                sb_position = ofs[0]+256;
        }else{
                sb_position = MemToFloatOfsForm(ofs[0],CMofs_type);
        }
        sb_ofs1->Position = sb_position;

        if(ofs_addr[0].Type()==3){
                s = ofs[0];
        }else if(CMofs_type==2){
                s = (sb_position-256)/4;  //-63.875~63.875
        }else if(CMofs_type==1){
                s = (sb_position-256)/2;  //-127.75~127.75
        }
        char buf[6];
        sprintf (buf, "%3.2f", s);
        st_ofs1-> Caption = (AnsiString)buf;

        btn_CM1_Read->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TCMForm1::btn_CM2_ReadClick(TObject *Sender)
{
        btn_CM2_Read->Enabled = false;

        //Write CM
        if(CM_addr[1].LutNum()!=9){     //Check CM1 table number
                ShowMessage("CM2 LUT number defined in AddressCM.cpp is wrong.");
                return;
        }
        int* CM = new int [CM_addr[1].LutNum()];
        EngineerForm->SetRead_CM(CM_addr[1], CM, CM_addr[1].LutNum());

        float* CM_f = new float [CM_addr[1].LutNum()];
        for(int i = 0; i < CM_addr[1].LutNum(); i++){
                CM_f[i] = (double)(MemToFloatForm(CM[i]))/256;
        }
        CM2_11->Text = FloatToStr(CM_f[0]);
        CM2_12->Text = FloatToStr(CM_f[1]);
        CM2_13->Text = FloatToStr(CM_f[2]);
        CM2_21->Text = FloatToStr(CM_f[3]);
        CM2_22->Text = FloatToStr(CM_f[4]);
        CM2_23->Text = FloatToStr(CM_f[5]);
        CM2_31->Text = FloatToStr(CM_f[6]);
        CM2_32->Text = FloatToStr(CM_f[7]);
        CM2_33->Text = FloatToStr(CM_f[8]);

        float ofs[3];
        EngineerForm->SetRead_CMofs(ofs_addr[1], ofs, ofs_addr[1].LutNum());

        if(ofs[0]!=ofs[1] || ofs[1]!=ofs[2])
                ShowMessage("The 3 Offset values are different.");
        int sb_position;
        float s;
        if(ofs_addr[0].Type()==3){
                sb_position = ofs[0]+256;
        }else{
                sb_position = MemToFloatOfsForm(ofs[0],CMofs_type);
        }
        sb_ofs1->Position = sb_position;

        if(ofs_addr[0].Type()==3){
                s = ofs[0];
        }else if(CMofs_type==2){
                s = (sb_position-256)/4;  //-63.875~63.875
        }else if(CMofs_type==1){
                s = (sb_position-256)/2;  //-127.75~127.75
        }
        char buf[6];
        sprintf (buf, "%3.2f", s);
        st_ofs2-> Caption = (AnsiString)buf;

        btn_CM2_Read->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TCMForm1::btn_CM3_ReadClick(TObject *Sender)
{
        btn_CM3_Read->Enabled = false;

        //Write CM
        if(CM_addr[2].LutNum()!=9){     //Check CM1 table number
                ShowMessage("CM1 LUT number defined in AddressCM.cpp is wrong.");
                return;
        }
        int* CM = new int [CM_addr[2].LutNum()];
        EngineerForm->SetRead_CM(CM_addr[2], CM, CM_addr[2].LutNum());

        float* CM_f = new float [CM_addr[2].LutNum()];
        for(int i = 0; i < CM_addr[2].LutNum(); i++){
                CM_f[i] = (double)(MemToFloatForm(CM[i]))/256;
        }
        CM3_11->Text = FloatToStr(CM_f[0]);
        CM3_12->Text = FloatToStr(CM_f[1]);
        CM3_13->Text = FloatToStr(CM_f[2]);
        CM3_21->Text = FloatToStr(CM_f[3]);
        CM3_22->Text = FloatToStr(CM_f[4]);
        CM3_23->Text = FloatToStr(CM_f[5]);
        CM3_31->Text = FloatToStr(CM_f[6]);
        CM3_32->Text = FloatToStr(CM_f[7]);
        CM3_33->Text = FloatToStr(CM_f[8]);

        float ofs[3];
        EngineerForm->SetRead_CMofs(ofs_addr[2], ofs, ofs_addr[2].LutNum());

        if(ofs[0]!=ofs[1] || ofs[1]!=ofs[2])
                ShowMessage("The 3 Offset values are different.");
        int sb_position;
        float s;
        if(ofs_addr[0].Type()==3){
                sb_position = ofs[0]+256;
        }else{
                sb_position = MemToFloatOfsForm(ofs[0],CMofs_type);
        }
        sb_ofs1->Position = sb_position;

        if(ofs_addr[0].Type()==3){
                s = ofs[0];
        }else if(CMofs_type==2){
                s = (sb_position-256)/4;  //-63.875~63.875
        }else if(CMofs_type==1){
                s = (sb_position-256)/2;  //-127.75~127.75
        }
        char buf[6];
        sprintf (buf, "%3.2f", s);
        st_ofs3-> Caption = (AnsiString)buf;
        btn_CM3_Read->Enabled = true;
}
//---------------------------------------------------------------------------



void __fastcall TCMForm1::btn_CM1_WriteClick(TObject *Sender)
{
        btn_CM1_Write->Enabled = false;

        //Write CM
        if(CM_addr[0].LutNum()!=9){     //Check CM1 table number
                ShowMessage("CM1 LUT number defined in AddressCM.cpp is wrong.");
                return;
        }

        int CM[9];
        CM[0] = StrToFloat(CM1_11->Text)*256;
        CM[0] = FloatToMemForm(CM[0]);
        CM[1] = StrToFloat(CM1_12->Text)*256;
        CM[1] = FloatToMemForm(CM[1]);
        CM[2] = StrToFloat(CM1_13->Text)*256;
        CM[2] = FloatToMemForm(CM[2]);

        CM[3] = StrToFloat(CM1_21->Text)*256;
        CM[3] = FloatToMemForm(CM[3]);
        CM[4] = StrToFloat(CM1_22->Text)*256;
        CM[4] = FloatToMemForm(CM[4]);
        CM[5] = StrToFloat(CM1_23->Text)*256;
        CM[5] = FloatToMemForm(CM[5]);

        CM[6] = StrToFloat(CM1_31->Text)*256;
        CM[6] = FloatToMemForm(CM[6]);
        CM[7] = StrToFloat(CM1_32->Text)*256;
        CM[7] = FloatToMemForm(CM[7]);
        CM[8] = StrToFloat(CM1_33->Text)*256;
        CM[8] = FloatToMemForm(CM[8]);

        EngineerForm->SetWrite_PG(CM_addr[0], CM, CM_addr[0].LutNum());
        //Write Offset
        if(ofs_addr[0].LutNum()!=3){    //check offset table number
                ShowMessage("CM1 offset LUT number defined in AddressCM.cpp is wrong.");
                return;
        }
        int ofs[3];
        if(ofs_addr[0].Type()==3){
                ofs[0] = ((float)sb_ofs1-> Position-256);  //range: -256~+256
        }else{

                int tmp = sb_ofs1-> Position;
                ofs[0] = FloatToMemOfsForm(tmp, CMofs_type);
        }
        ofs[1] = ofs[0];
        ofs[2] = ofs[0];
        EngineerForm->SetWrite_PG(ofs_addr[0], ofs, ofs_addr[0].LutNum());

        btn_CM1_Write->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TCMForm1::btn_CM2_WriteClick(TObject *Sender)
{
        btn_CM2_Write->Enabled = false;

        //write CM
        if(CM_addr[1].LutNum()!=9){     //check CM2 table number
                ShowMessage("CM2 LUT number defined in AddressCM.cpp is wrong.");
                return;
        }

        int CM[9];
        CM[0] = StrToFloat(CM2_11->Text)*256;
        CM[0] = FloatToMemForm(CM[0]);
        CM[1] = StrToFloat(CM2_12->Text)*256;
        CM[1] = FloatToMemForm(CM[1]);
        CM[2] = StrToFloat(CM2_13->Text)*256;
        CM[2] = FloatToMemForm(CM[2]);

        CM[3] = StrToFloat(CM2_21->Text)*256;
        CM[3] = FloatToMemForm(CM[3]);
        CM[4] = StrToFloat(CM2_22->Text)*256;
        CM[4] = FloatToMemForm(CM[4]);
        CM[5] = StrToFloat(CM2_23->Text)*256;
        CM[5] = FloatToMemForm(CM[5]);

        CM[6] = StrToFloat(CM2_31->Text)*256;
        CM[6] = FloatToMemForm(CM[6]);
        CM[7] = StrToFloat(CM2_32->Text)*256;
        CM[7] = FloatToMemForm(CM[7]);
        CM[8] = StrToFloat(CM2_33->Text)*256;
        CM[8] = FloatToMemForm(CM[8]);

        EngineerForm->SetWrite_PG(CM_addr[1], CM, CM_addr[1].LutNum());

        //write offset
        if(ofs_addr[1].LutNum()!=3){    //check offset table number
                ShowMessage("CM2 offset LUT number defined in AddressCM.cpp is wrong.");
                return;
        }
        int ofs[3];
        if(ofs_addr[0].Type()==3){
                ofs[0] = ((float)sb_ofs2-> Position-256);  //range: -256~+256
        }else{
                int tmp = sb_ofs2-> Position;
                ofs[0] = FloatToMemOfsForm(tmp, CMofs_type);
        }
        ofs[1] = ofs[0];
        ofs[2] = ofs[0];
        //EngineerForm->SetWrite_PG(ofs_addr[1], ofs, ofs_addr[1].LutNum());

        btn_CM2_Write->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TCMForm1::btn_CM3_WriteClick(TObject *Sender)
{
        btn_CM3_Write->Enabled = false;

        //write CM
        if(CM_addr[2].LutNum()!=9){     //check CM3 table number
                ShowMessage("CM3 LUT number defined in AddressCM.cpp is wrong.");
                return;
        }

        int CM[9];
        CM[0] = StrToFloat(CM3_11->Text)*256;
        CM[0] = FloatToMemForm(CM[0]);
        CM[1] = StrToFloat(CM3_12->Text)*256;
        CM[1] = FloatToMemForm(CM[1]);
        CM[2] = StrToFloat(CM3_13->Text)*256;
        CM[2] = FloatToMemForm(CM[2]);

        CM[3] = StrToFloat(CM3_21->Text)*256;
        CM[3] = FloatToMemForm(CM[3]);
        CM[4] = StrToFloat(CM3_22->Text)*256;
        CM[4] = FloatToMemForm(CM[4]);
        CM[5] = StrToFloat(CM3_23->Text)*256;
        CM[5] = FloatToMemForm(CM[5]);

        CM[6] = StrToFloat(CM3_31->Text)*256;
        CM[6] = FloatToMemForm(CM[6]);
        CM[7] = StrToFloat(CM3_32->Text)*256;
        CM[7] = FloatToMemForm(CM[7]);
        CM[8] = StrToFloat(CM3_33->Text)*256;
        CM[8] = FloatToMemForm(CM[8]);

        EngineerForm->SetWrite_PG(CM_addr[2], CM, CM_addr[2].LutNum());

        //write offset
        if(ofs_addr[2].LutNum()!=3){    //check offset table number
                ShowMessage("CM3 offset LUT number defined in AddressCM.cpp is wrong.");
                return;
        }
        int ofs[3];
        if(ofs_addr[0].Type()==3){
                ofs[0] = ((float)sb_ofs3-> Position-256);  //range: -256~+256
        }else{
                
                int tmp = sb_ofs3-> Position;
                ofs[0] = FloatToMemOfsForm(tmp, CMofs_type);
        }
        ofs[1] = ofs[0];
        ofs[2] = ofs[0];
        //EngineerForm->SetWrite_PG(ofs_addr[2], ofs, ofs_addr[2].LutNum());

        btn_CM3_Write->Enabled = true;
}
//---------------------------------------------------------------------------

void CM_GainFunc(double* d_ratio, float var1, float var2)
{
        if(var1==0 && var2 == 0){
                d_ratio[0] = 0.5;
                d_ratio[1] = 0.5;
        }else if(var1+var2 == 0 & var1 < 0){
                d_ratio[0] = -0.5;
                d_ratio[1] = 0.5;
        }else if(var1+var2 == 0 & var2 < 0){
                d_ratio[0] = 0.5;
                d_ratio[1] = -0.5;
        }else{
                d_ratio[0] = var1/(var1+ var2);
                d_ratio[1] = var2/(var1+ var2);
        }
}
//---------------------------------------------------------------------------

void __fastcall TCMForm1::sb_cm11Change(TObject *Sender)
{
        float tmp = sb_cm11->Position;
        st_CM11gain->Caption = FloatToStr(tmp)+"%";
        tmp /= 100;

        char buffer[5];
        sprintf (buffer, "%f", tmp*CM1[0][0]);
        CM1_11->Text = (AnsiString) buffer;

        if(rg_CM1_mode->ItemIndex == 1){        //White Balance
                CM1_12->Text = 0;
                CM1_13->Text = 0;
        }else{                                  //normal
                double diff = CM1[0][0] - tmp*CM1[0][0];
                double d_ratio[2];
                CM_GainFunc(d_ratio, CM1[0][1], CM1[0][2]);

                sprintf (buffer, "%f",  CM1[0][1]+diff*d_ratio[0]);
                CM1_12->Text = (AnsiString) buffer;

                sprintf (buffer, "%f", CM1[0][2]+diff*d_ratio[1]);
                CM1_13->Text = (AnsiString) buffer;
        }
        btn_CM1_WriteClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCMForm1::sb_cm12Change(TObject *Sender)
{
        float tmp = sb_cm12->Position;
        st_CM12gain->Caption = FloatToStr(tmp)+"%";
        tmp /= 100;

        char buffer[5];
        sprintf (buffer, "%f", tmp*CM1[1][1]);
        CM1_22->Text = (AnsiString) buffer;

        if(rg_CM1_mode->ItemIndex == 1){        //White Balance
                CM1_21->Text = 0;
                CM1_23->Text = 0;
        }else{                                  //normal
                double diff = CM1[1][1] - tmp*CM1[1][1];
                double d_ratio[2];
                CM_GainFunc(d_ratio, CM1[1][0], CM1[1][2]);

                sprintf (buffer, "%f",  CM1[1][0]+diff*d_ratio[0]);
                CM1_21->Text = (AnsiString) buffer;

                sprintf (buffer, "%f", CM1[1][2]+diff*d_ratio[1]);
                CM1_23->Text = (AnsiString) buffer;
        }
        btn_CM1_WriteClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TCMForm1::sb_cm13Change(TObject *Sender)
{
        float tmp = sb_cm13->Position;
        st_CM13gain->Caption = FloatToStr(tmp)+"%";
        tmp /= 100;

        char buffer[5];
        sprintf (buffer, "%f", tmp*CM1[2][2]);
        CM1_33->Text = (AnsiString) buffer;

        if(rg_CM1_mode->ItemIndex == 1){        //White Balance
                CM1_31->Text = 0;
                CM1_32->Text = 0;
        }else{                                  //normal
                double diff = CM1[2][2] - tmp*CM1[2][2];
                double d_ratio[2];
                CM_GainFunc(d_ratio, CM1[2][0], CM1[2][1]);

                sprintf (buffer, "%f",  CM1[2][0]+diff*d_ratio[0]);
                CM1_31->Text = (AnsiString) buffer;

                sprintf (buffer, "%f", CM1[2][1]+diff*d_ratio[1]);
                CM1_32->Text = (AnsiString) buffer;
        }
        btn_CM1_WriteClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TCMForm1::sb_cm21Change(TObject *Sender)
{
        float tmp = sb_cm21->Position;
        st_CM21gain->Caption = FloatToStr(tmp)+"%";
        tmp /= 100;

        char buffer[5];
        sprintf (buffer, "%f", tmp*CM2[0][0]);
        CM2_11->Text = (AnsiString) buffer;

        if(rg_CM2_mode->ItemIndex == 1){        //White Balance
                CM2_12->Text = 0;
                CM2_13->Text = 0;
        }else{                                  //normal
                double diff = CM2[0][0] - tmp*CM2[0][0];
                double d_ratio[2];
                CM_GainFunc(d_ratio, CM2[0][1], CM2[0][2]);

                sprintf (buffer, "%f",  CM2[0][1]+diff*d_ratio[0]);
                CM2_12->Text = (AnsiString) buffer;

                sprintf (buffer, "%f", CM2[0][2]+diff*d_ratio[1]);
                CM2_13->Text = (AnsiString) buffer;
        }
        btn_CM2_WriteClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TCMForm1::sb_cm22Change(TObject *Sender)
{
        float tmp = sb_cm22->Position;
        st_CM22gain->Caption = FloatToStr(tmp)+"%";
        tmp /= 100;

        char buffer[5];
        sprintf (buffer, "%f", tmp*CM2[1][1]);
        CM2_22->Text = (AnsiString) buffer;

        if(rg_CM2_mode->ItemIndex == 1){        //White Balance
                CM2_21->Text = 0;
                CM2_23->Text = 0;
        }else{                                  //normal
                double diff = CM2[1][1] - tmp*CM2[1][1];
                double d_ratio[2];
                CM_GainFunc(d_ratio, CM2[1][0], CM2[1][2]);

                sprintf (buffer, "%f",  CM2[1][0]+diff*d_ratio[0]);
                CM2_21->Text = (AnsiString) buffer;

                sprintf (buffer, "%f", CM2[1][2]+diff*d_ratio[1]);
                CM2_23->Text = (AnsiString) buffer;
        }
        btn_CM2_WriteClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TCMForm1::sb_cm23Change(TObject *Sender)
{
        float tmp = sb_cm23->Position;
        st_CM23gain->Caption = FloatToStr(tmp)+"%";
        tmp /= 100;

        char buffer[5];
        sprintf (buffer, "%f", tmp*CM2[2][2]);
        CM2_33->Text = (AnsiString) buffer;

        if(rg_CM2_mode->ItemIndex == 1){        //White Balance
                CM2_31->Text = 0;
                CM2_32->Text = 0;
        }else{                                  //normal
                double diff = CM2[2][2] - tmp*CM2[2][2];
                double d_ratio[2];
                CM_GainFunc(d_ratio, CM2[2][0], CM2[2][1]);

                sprintf (buffer, "%f",  CM2[2][0]+diff*d_ratio[0]);
                CM2_31->Text = (AnsiString) buffer;

                sprintf (buffer, "%f", CM2[2][1]+diff*d_ratio[1]);
                CM2_32->Text = (AnsiString) buffer;
        }
        btn_CM2_WriteClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCMForm1::sb_cm31Change(TObject *Sender)
{
        float tmp = sb_cm31->Position;
        st_CM31gain->Caption = FloatToStr(tmp)+"%";
        tmp /= 100;

        char buffer[5];
        sprintf (buffer, "%f", tmp*CM3[0][0]);
        CM3_11->Text = (AnsiString) buffer;

        if(rg_CM3_mode->ItemIndex == 1){        //White Balance
                CM3_12->Text = 0;
                CM3_13->Text = 0;
        }else{                                  //normal
                double diff = CM3[0][0] - tmp*CM3[0][0];
                double d_ratio[2];
                CM_GainFunc(d_ratio, CM3[0][1], CM3[0][2]);

                sprintf (buffer, "%f",  CM3[0][1]+diff*d_ratio[0]);
                CM3_12->Text = (AnsiString) buffer;

                sprintf (buffer, "%f", CM3[0][2]+diff*d_ratio[1]);
                CM3_13->Text = (AnsiString) buffer;
        }
        btn_CM3_WriteClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TCMForm1::sb_cm32Change(TObject *Sender)
{
        float tmp = sb_cm32->Position;
        st_CM32gain->Caption = FloatToStr(tmp)+"%";
        tmp /= 100;

        char buffer[5];
        sprintf (buffer, "%f", tmp*CM3[1][1]);
        CM3_22->Text = (AnsiString) buffer;

        if(rg_CM3_mode->ItemIndex == 1){        //White Balance
                CM3_21->Text = 0;
                CM3_23->Text = 0;
        }else{                                  //normal
                double diff = CM3[1][1] - tmp*CM3[1][1];
                double d_ratio[2];
                CM_GainFunc(d_ratio, CM3[1][0], CM3[1][2]);

                sprintf (buffer, "%f",  CM3[1][0]+diff*d_ratio[0]);
                CM3_21->Text = (AnsiString) buffer;

                sprintf (buffer, "%f", CM3[1][2]+diff*d_ratio[1]);
                CM3_23->Text = (AnsiString) buffer;
        }
        btn_CM3_WriteClick(Sender);
}
//---------------------------------------------------------------------------
void __fastcall TCMForm1::sb_cm33Change(TObject *Sender)
{
        float tmp = sb_cm33->Position;
        st_CM33gain->Caption = FloatToStr(tmp)+"%";
        tmp /= 100;

        char buffer[5];
        sprintf (buffer, "%f", tmp*CM3[2][2]);
        CM3_33->Text = (AnsiString) buffer;

        if(rg_CM3_mode->ItemIndex == 1){        //White Balance
                CM3_31->Text = 0;
                CM3_32->Text = 0;
        }else{                                  //normal
                double diff = CM3[2][2] - tmp*CM3[2][2];
                double d_ratio[2];
                CM_GainFunc(d_ratio, CM3[2][0], CM3[2][1]);

                sprintf (buffer, "%f",  CM3[2][0]+diff*d_ratio[0]);
                CM3_31->Text = (AnsiString) buffer;

                sprintf (buffer, "%f", CM3[2][1]+diff*d_ratio[1]);
                CM3_32->Text = (AnsiString) buffer;
        }
        btn_CM3_WriteClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TCMForm1::rg_CM1_modeClick(TObject *Sender)
{
        char c = '0';
        if(rg_CM1_mode->ItemIndex == 1){        //White Balance
                CM1_11->Text = 1;
                CM1_12->Text = 0;
                CM1_13->Text = 0;

                CM1_21->Text = 0;
                CM1_22->Text = 1;
                CM1_23->Text = 0;

                CM1_31->Text = 0;
                CM1_32->Text = 0;
                CM1_33->Text = 1;
                CM1_keyPress(Sender,c);         //refesh memory
        }else if(rg_CM1_mode->ItemIndex == 2){        //vivid mode
                CM1_11->Text = 1.04;
                CM1_12->Text = -0.02;
                CM1_13->Text = -0.02;

                CM1_21->Text = -0.02;
                CM1_22->Text = 1.04;
                CM1_23->Text = -0.02;

                CM1_31->Text = -0.02;
                CM1_32->Text = -0.02;
                CM1_33->Text = 1.04;
                CM1_keyPress(Sender,c);         //refesh memory
        }
}
//---------------------------------------------------------------------------

void __fastcall TCMForm1::rg_CM2_modeClick(TObject *Sender)
{
        char c = '0';
        if(rg_CM2_mode->ItemIndex == 1){        //White Balance
                CM2_11->Text = 1;
                CM2_12->Text = 0;
                CM2_13->Text = 0;

                CM2_21->Text = 0;
                CM2_22->Text = 1;
                CM2_23->Text = 0;

                CM2_31->Text = 0;
                CM2_32->Text = 0;
                CM2_33->Text = 1;
                CM2_keyPress(Sender,c);         //refesh memory
        }else if(rg_CM2_mode->ItemIndex == 2){        //vivid mode
                CM2_11->Text = 1.04;
                CM2_12->Text = -0.02;
                CM2_13->Text = -0.02;

                CM2_21->Text = -0.02;
                CM2_22->Text = 1.04;
                CM2_23->Text = -0.02;

                CM2_31->Text = -0.02;
                CM2_32->Text = -0.02;
                CM2_33->Text = 1.04;
                CM2_keyPress(Sender,c);         //refesh memory
        }
}
//---------------------------------------------------------------------------

void __fastcall TCMForm1::rg_CM3_modeClick(TObject *Sender)
{
        char c = '0';
        if(rg_CM3_mode->ItemIndex == 1){        //White Balance
                CM3_11->Text = 1;
                CM3_12->Text = 0;
                CM3_13->Text = 0;

                CM3_21->Text = 0;
                CM3_22->Text = 1;
                CM3_23->Text = 0;

                CM3_31->Text = 0;
                CM3_32->Text = 0;
                CM3_33->Text = 1;
                CM3_keyPress(Sender,c);         //refesh memory
        }else if(rg_CM3_mode->ItemIndex == 2){        //vivid mode
                CM3_11->Text = 1.04;
                CM3_12->Text = -0.02;
                CM3_13->Text = -0.02;

                CM3_21->Text = -0.02;
                CM3_22->Text = 1.04;
                CM3_23->Text = -0.02;

                CM3_31->Text = -0.02;
                CM3_32->Text = -0.02;
                CM3_33->Text = 1.04;
                CM3_keyPress(Sender,c);         //refesh memory
        }
}
//---------------------------------------------------------------------------


void __fastcall TCMForm1::CM1_keyPress(TObject *Sender, char &Key)
{
        CM1[0][0] = StrToFloat(CM1_11->Text);
        CM1[0][1] = StrToFloat(CM1_12->Text);
        CM1[0][2] = StrToFloat(CM1_13->Text);

        CM1[1][0] = StrToFloat(CM1_21->Text);
        CM1[1][1] = StrToFloat(CM1_22->Text);
        CM1[1][2] = StrToFloat(CM1_23->Text);

        CM1[2][0] = StrToFloat(CM1_31->Text);
        CM1[2][1] = StrToFloat(CM1_32->Text);
        CM1[2][2] = StrToFloat(CM1_33->Text);

        sb_cm11->Position = 100;
        sb_cm12->Position = 100;
        sb_cm13->Position = 100;
}
//---------------------------------------------------------------------------

void __fastcall TCMForm1::CM2_keyPress(TObject *Sender, char &Key)
{
        CM2[0][0] = StrToFloat(CM2_11->Text);
        CM2[0][1] = StrToFloat(CM2_12->Text);
        CM2[0][2] = StrToFloat(CM2_13->Text);

        CM2[1][0] = StrToFloat(CM2_21->Text);
        CM2[1][1] = StrToFloat(CM2_22->Text);
        CM2[1][2] = StrToFloat(CM2_23->Text);

        CM2[2][0] = StrToFloat(CM2_31->Text);
        CM2[2][1] = StrToFloat(CM2_32->Text);
        CM2[2][2] = StrToFloat(CM2_33->Text);

        sb_cm21->Position = 100;
        sb_cm22->Position = 100;
        sb_cm23->Position = 100;
}
//---------------------------------------------------------------------------
void __fastcall TCMForm1::CM3_keyPress(TObject *Sender, char &Key)
{
        CM3[0][0] = StrToFloat(CM3_11->Text);
        CM3[0][1] = StrToFloat(CM3_12->Text);
        CM3[0][2] = StrToFloat(CM3_13->Text);

        CM3[1][0] = StrToFloat(CM3_21->Text);
        CM3[1][1] = StrToFloat(CM3_22->Text);
        CM3[1][2] = StrToFloat(CM3_23->Text);

        CM3[2][0] = StrToFloat(CM3_31->Text);
        CM3[2][1] = StrToFloat(CM3_32->Text);
        CM3[2][2] = StrToFloat(CM3_33->Text);

        sb_cm31->Position = 100;
        sb_cm32->Position = 100;
        sb_cm33->Position = 100;
}
//---------------------------------------------------------------------------
void __fastcall TCMForm1::sb_ofs1Change(TObject *Sender)
{
        float s;
        if(sb_ofs1-> Position==0)
                sb_ofs1-> Position = 1;

        if(ofs_addr[0].Type()==3){
                s = ((float)sb_ofs1-> Position-256);  //range: -256~+256
        }else if(CMofs_type==2){
                s = ((float)sb_ofs1-> Position-256)/4;  //range: -63.875~63.875
        }else if(CMofs_type==1){
                s = ((float)sb_ofs1-> Position-256)/2;  //range: -127.75~127.75
        }

        char buf[6];
        sprintf (buf, "%3.2f", s);
        st_ofs1-> Caption = (AnsiString)buf;

        int ofs[3];
        int tmp = sb_ofs1-> Position;
        if(ofs_addr[0].Type()==3){
                if(s<0)                 //2'complement
                        s = 1023+s+1;
                ofs[0] = s;
        }else
                ofs[0] = FloatToMemOfsForm(tmp, CMofs_type);
        ofs[1] = ofs[0];
        ofs[2] = ofs[0];

        EngineerForm->SetWrite_PG(ofs_addr[0], ofs, ofs_addr[0].LutNum());

        if(cb_CM1_W255->Checked == true){
                double CM12= StrToFloat(CM1_12->Text);
                double CM13 = StrToFloat(CM1_13->Text);
                double CM11 = (255-((CM12+CM13)*255+s))/255;
                CM1_11->Text = FloatToStr(CM11);

                double CM21= StrToFloat(CM1_21->Text);
                double CM23 = StrToFloat(CM1_23->Text);
                double CM22 = (255-((CM21+CM23)*255+s))/255;
                CM1_22->Text = FloatToStr(CM22);

                double CM31= StrToFloat(CM1_31->Text);
                double CM32 = StrToFloat(CM1_32->Text);
                double CM33 = (255-((CM31+CM32)*255+s))/255;
                CM1_33->Text = FloatToStr(CM33);

                int CM[9];
                CM[0] = FloatToMemForm(CM11*256);
                CM[1] = FloatToMemForm(CM12*256);
                CM[2] = FloatToMemForm(CM13*256);

                CM[3] = FloatToMemForm(CM21*256);
                CM[4] = FloatToMemForm(CM22*256);
                CM[5] = FloatToMemForm(CM23*256);

                CM[6] = FloatToMemForm(CM31*256);
                CM[7] = FloatToMemForm(CM32*256);
                CM[8] = FloatToMemForm(CM33*256);

                EngineerForm->SetWrite_PG(CM_addr[0], CM, CM_addr[0].LutNum());
       }
}
//---------------------------------------------------------------------------

void __fastcall TCMForm1::sb_ofs2Change(TObject *Sender)
{
        float s;
        if(sb_ofs2-> Position==0)
                sb_ofs2-> Position = 1;
        if(ofs_addr[0].Type()==3){
                s = ((float)sb_ofs2-> Position-256);  //range: -256~+256
        }else if(CMofs_type==2){
                s = ((float)sb_ofs2-> Position-256)/4;
        }else if(CMofs_type==1){
                s = ((float)sb_ofs2-> Position-256)/2;
        }
        char buf[6];
        sprintf (buf, "%3.2f", s);
        st_ofs2-> Caption = (AnsiString)buf;

        int ofs[3];
        int tmp = sb_ofs2-> Position;
        if(ofs_addr[0].Type()==3){
                if(s<0)                 //2'complement
                        s = 1023+s+1;
                ofs[0] = s;
        }else
                ofs[0] = FloatToMemOfsForm(tmp, CMofs_type);
        ofs[1] = ofs[0];
        ofs[2] = ofs[0];
        EngineerForm->SetWrite_PG(ofs_addr[1], ofs, ofs_addr[1].LutNum());

        if(cb_CM2_W255->Checked == true){
                double CM12= StrToFloat(CM2_12->Text);
                double CM13 = StrToFloat(CM2_13->Text);
                double CM11 = (255-((CM12+CM13)*255+s))/255;
                CM2_11->Text = FloatToStr(CM11);

                double CM21= StrToFloat(CM2_21->Text);
                double CM23 = StrToFloat(CM2_23->Text);
                double CM22 = (255-((CM21+CM23)*255+s))/255;
                CM2_22->Text = FloatToStr(CM22);

                double CM31= StrToFloat(CM2_31->Text);
                double CM32 = StrToFloat(CM2_32->Text);
                double CM33 = (255-((CM31+CM32)*255+s))/255;
                CM2_33->Text = FloatToStr(CM33);

                int CM[9];
                CM[0] = FloatToMemForm(CM11*256);
                CM[1] = FloatToMemForm(CM12*256);
                CM[2] = FloatToMemForm(CM13*256);

                CM[3] = FloatToMemForm(CM21*256);
                CM[4] = FloatToMemForm(CM22*256);
                CM[5] = FloatToMemForm(CM23*256);

                CM[6] = FloatToMemForm(CM31*256);
                CM[7] = FloatToMemForm(CM32*256);
                CM[8] = FloatToMemForm(CM33*256);

                EngineerForm->SetWrite_PG(CM_addr[1], CM, CM_addr[1].LutNum());
       }
}
//---------------------------------------------------------------------------

void __fastcall TCMForm1::sb_ofs3Change(TObject *Sender)
{
        float s;
        if(sb_ofs3-> Position==0)
                sb_ofs3-> Position = 1;

        if(ofs_addr[0].Type()==3){
                s = ((float)sb_ofs3-> Position-256);  //range: -256~+256
        }else if(CMofs_type==2){
                s = ((float)sb_ofs3-> Position-256)/4;
        }else if(CMofs_type==1){
                s = ((float)sb_ofs3-> Position-256)/2;
        }
        char buf[6];
        sprintf (buf, "%3.2f", s);
        st_ofs3-> Caption = (AnsiString)buf;

        int ofs[3];
        int tmp = sb_ofs3-> Position;
        if(ofs_addr[0].Type()==3){
                if(s<0)                 //2'complement
                        s = 1023+s+1;
                ofs[0] = s;
        }else
                ofs[0] = FloatToMemOfsForm(tmp, CMofs_type);
        ofs[1] = ofs[0];
        ofs[2] = ofs[0];
        EngineerForm->SetWrite_PG(ofs_addr[2], ofs, ofs_addr[2].LutNum());

        if(cb_CM3_W255->Checked == true){
                double CM12= StrToFloat(CM3_12->Text);
                double CM13 = StrToFloat(CM3_13->Text);
                double CM11 = (255-((CM12+CM13)*255+s))/255;
                CM3_11->Text = FloatToStr(CM11);

                double CM21= StrToFloat(CM3_21->Text);
                double CM23 = StrToFloat(CM3_23->Text);
                double CM22 = (255-((CM21+CM23)*255+s))/255;
                CM3_22->Text = FloatToStr(CM22);

                double CM31= StrToFloat(CM3_31->Text);
                double CM32 = StrToFloat(CM3_32->Text);
                double CM33 = (255-((CM31+CM32)*255+s))/255;
                CM3_33->Text = FloatToStr(CM33);

                int CM[9];
                CM[0] = FloatToMemForm(CM11*256);
                CM[1] = FloatToMemForm(CM12*256);
                CM[2] = FloatToMemForm(CM13*256);

                CM[3] = FloatToMemForm(CM21*256);
                CM[4] = FloatToMemForm(CM22*256);
                CM[5] = FloatToMemForm(CM23*256);

                CM[6] = FloatToMemForm(CM31*256);
                CM[7] = FloatToMemForm(CM32*256);
                CM[8] = FloatToMemForm(CM33*256);

                EngineerForm->SetWrite_PG(CM_addr[2], CM, CM_addr[2].LutNum());
       }
}
//---------------------------------------------------------------------------

void __fastcall TCMForm1::TS_CMChange(TObject *Sender)
{
        CMCboB[0]->Cbob->ItemIndex = TS_CM->TabIndex+1;
        //將CM select值寫入硬體
        int set_val = (CMCboB[0]->Cbob->ItemIndex);
        EngineerForm->SetWrite_Byte(CMCboB[0]->Addr ,set_val);
}
//---------------------------------------------------------------------------

void __fastcall TCMForm1::bn_CM1SaveClick(TObject *Sender)
{
        if(!SaveDialog1->Execute())
                return;
        String Fpath = SaveDialog1->FileName/*+".txt"*/;
        FILE* fptr = fopen (Fpath.c_str(),"w");
        fprintf(fptr,"CM\n");
        float CM[9];
        CM[0] = StrToFloat(CM1_11->Text);
        CM[1] = StrToFloat(CM1_12->Text);
        CM[2] = StrToFloat(CM1_13->Text);

        CM[3] = StrToFloat(CM1_21->Text);
        CM[4] = StrToFloat(CM1_22->Text);
        CM[5] = StrToFloat(CM1_23->Text);

        CM[6] = StrToFloat(CM1_31->Text);
        CM[7] = StrToFloat(CM1_32->Text);
        CM[8] = StrToFloat(CM1_33->Text);
        for(int i = 0; i < 3; i++){
                fprintf(fptr, "%f\t%f\t%f\n", CM[0+i*3], CM[1+i*3], CM[2+i*3]);
        }
        float CMofs;
        CMofs = StrToFloat(st_ofs1->Caption);

        fprintf(fptr, "%f\n", CMofs);
        fclose(fptr);
}
//---------------------------------------------------------------------------

void __fastcall TCMForm1::bn_CM2SaveClick(TObject *Sender)
{
        if(!SaveDialog1->Execute())
                return;
        String Fpath = SaveDialog1->FileName;
        FILE* fptr = fopen (Fpath.c_str(),"w");
        fprintf(fptr,"CM\n");
        float CM[9];
        CM[0] = StrToFloat(CM2_11->Text);
        CM[1] = StrToFloat(CM2_12->Text);
        CM[2] = StrToFloat(CM2_13->Text);

        CM[3] = StrToFloat(CM2_21->Text);
        CM[4] = StrToFloat(CM2_22->Text);
        CM[5] = StrToFloat(CM2_23->Text);

        CM[6] = StrToFloat(CM2_31->Text);
        CM[7] = StrToFloat(CM2_32->Text);
        CM[8] = StrToFloat(CM2_33->Text);
        for(int i = 0; i < 3; i++){
                fprintf(fptr, "%f\t%f\t%f\n", CM[0+i*3], CM[1+i*3], CM[2+i*3]);
        }
        float CMofs;
        CMofs = StrToFloat(st_ofs2->Caption);

        fprintf(fptr, "%f\n", CMofs);
        fclose(fptr);        
}
//---------------------------------------------------------------------------

void __fastcall TCMForm1::bn_CM3SaveClick(TObject *Sender)
{
        if(!SaveDialog1->Execute())
                return;
        String Fpath = SaveDialog1->FileName;
        FILE* fptr = fopen (Fpath.c_str(),"w");
        fprintf(fptr,"CM\n");
        float CM[9];
        CM[0] = StrToFloat(CM3_11->Text);
        CM[1] = StrToFloat(CM3_12->Text);
        CM[2] = StrToFloat(CM3_13->Text);

        CM[3] = StrToFloat(CM3_21->Text);
        CM[4] = StrToFloat(CM3_22->Text);
        CM[5] = StrToFloat(CM3_23->Text);

        CM[6] = StrToFloat(CM3_31->Text);
        CM[7] = StrToFloat(CM3_32->Text);
        CM[8] = StrToFloat(CM3_33->Text);
        for(int i = 0; i < 3; i++){
                fprintf(fptr, "%f\t%f\t%f\n", CM[0+i*3], CM[1+i*3], CM[2+i*3]);
        }
        float CMofs;
        CMofs = StrToFloat(st_ofs3->Caption);
        fprintf(fptr, "%f\n", CMofs);
        fclose(fptr);
}
//---------------------------------------------------------------------------
/*
char* Load_File(String Fpath)
{
        long lSize;
        char* buffer;
        FILE* fptr;
        if((fptr = fopen(Fpath.c_str(),"r"))==NULL)
                return 0;

         // obtain file size:
        fseek (fptr , 0 , SEEK_END);
        lSize = ftell (fptr);
        rewind (fptr);

        // allocate memory to contain the whole file:
        buffer = (char*) malloc (sizeof(char)*lSize+1);
        if(buffer == NULL)
                return 0;
        // copy the file into the buffer:
        fread (buffer,1,lSize,fptr);
        buffer[lSize] = '\0';
        fclose(fptr);
        return buffer;
}  */
//-----------------------------------------------------------------------
void TCMForm1::CM1Load(String Fpath)
{
        char* buffer = Load_File(Fpath);

        char * pch;
        pch = strtok (buffer,"\n\t");
        String tmp;
        if((AnsiString)pch != "CM"){
                while (pch!="CM"){
                        if(pch == NULL)
                                return;        //資料中沒有cm
                        pch = strtok (NULL,"\n\t");
                }
        }

        int c= 0;
        pch = strtok (NULL,"\n\t");
        while (c < 9 && pch!=NULL){
                if(pch == NULL)
                        return;        //資料中的data缺少
                CM1[c/3][c%3] = StrToFloat((AnsiString)pch);
                pch = strtok (NULL,"\n\t");
                c++;
        }
        float CMofs;

        if(pch == NULL)
                return;        //資料中的data缺少
        CMofs = StrToFloat((AnsiString)pch);

        char cm_buf[5];
        sprintf (cm_buf, "%f", CM1[0][0]);
        CM1_11->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM1[0][1]);
        CM1_12->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM1[0][2]);
        CM1_13->Text = (AnsiString) cm_buf;

        sprintf (cm_buf, "%f", CM1[1][0]);
        CM1_21->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM1[1][1]);
        CM1_22->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM1[1][2]);
        CM1_23->Text = (AnsiString) cm_buf;

        sprintf (cm_buf, "%f", CM1[2][0]);
        CM1_31->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM1[2][1]);
        CM1_32->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM1[2][2]);
        CM1_33->Text = (AnsiString) cm_buf;

        sb_cm11->Position = 100;
        sb_cm12->Position = 100;
        sb_cm13->Position = 100;

        if(ofs_addr[0].Type()==3){      //ofs range -511~+511
                if(CMofs<0)
                        CMofs = CMofs+1023+1;
                sb_ofs1->Position = CMofs;
        }else{
                int CMofs_order;
                if(CM_addr[0].Type()==2)
                        CMofs_order = 4;
                else if(CM_addr[0].Type()==1)
                        CMofs_order = 2;
                sb_ofs1->Position = CMofs*CMofs_order+256;
        }
}
//------------------------------------------------------------------------
void __fastcall TCMForm1::bn_CM1LoadClick(TObject *Sender)
{
        if(!OpenDialog1->Execute())
                return;
        String Fpath = OpenDialog1->FileName;
        CM1Load(Fpath);
        btn_CM1_WriteClick(Sender);
}
//---------------------------------------------------------------------------
void TCMForm1::CM2Load(String Fpath)
{
        char* buffer = Load_File(Fpath);

        char * pch;
        pch = strtok (buffer,"\n\t");
        String tmp;
        if((AnsiString)pch != "CM"){
                while (pch!="CM"){
                        if(pch == NULL)
                                return;        //資料中沒有cm
                        pch = strtok (NULL,"\n\t");
                }
        }

        int c= 0;
        pch = strtok (NULL,"\n\t");
        while (c < 9 && pch!=NULL){
                if(pch == NULL)
                        return;        //資料中的data缺少
                CM2[c/3][c%3] = StrToFloat((AnsiString)pch);
                pch = strtok (NULL,"\n\t");
                c++;
        }
        float CMofs;

        if(pch == NULL)
                return;        //資料中的data缺少
        CMofs = StrToFloat((AnsiString)pch);

        char cm_buf[5];
        sprintf (cm_buf, "%f", CM2[0][0]);
        CM2_11->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM2[0][1]);
        CM2_12->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM2[0][2]);
        CM2_13->Text = (AnsiString) cm_buf;

        sprintf (cm_buf, "%f", CM2[1][0]);
        CM2_21->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM2[1][1]);
        CM2_22->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM2[1][2]);
        CM2_23->Text = (AnsiString) cm_buf;

        sprintf (cm_buf, "%f", CM2[2][0]);
        CM2_31->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM2[2][1]);
        CM2_32->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM2[2][2]);
        CM2_33->Text = (AnsiString) cm_buf;

        sb_cm21->Position = 100;
        sb_cm22->Position = 100;
        sb_cm23->Position = 100;

        if(ofs_addr[0].Type()==3){      //ofs range -511~+511
                if(CMofs<0)
                        CMofs = CMofs+1023+1;
                sb_ofs2->Position = CMofs;
        }else{
                int CMofs_order;
                if(CM_addr[1].Type()==2)
                        CMofs_order = 4;
                else if(CM_addr[1].Type()==1)
                        CMofs_order = 2;

                sb_ofs2->Position = CMofs*CMofs_order+256;
        }
}
//---------------------------------------------------------------------------
void __fastcall TCMForm1::bn_CM2LoadClick(TObject *Sender)
{
        if(!OpenDialog1->Execute())
                return;
        String Fpath = OpenDialog1->FileName;
        CM2Load(Fpath);
        btn_CM2_WriteClick(Sender);
}
//---------------------------------------------------------------------------
void TCMForm1::CM3Load(String Fpath)
{
        char* buffer = Load_File(Fpath);

        char * pch;
        pch = strtok (buffer,"\n\t");
        String tmp;
        if((AnsiString)pch != "CM"){
                while (pch!="CM"){
                        if(pch == NULL)
                                return;        //資料中沒有cm
                        pch = strtok (NULL,"\n\t");
                }
        }

        int c= 0;
        pch = strtok (NULL,"\n\t");
        while (c < 9 && pch!=NULL){
                if(pch == NULL)
                        return;        //資料中的data缺少
                CM3[c/3][c%3] = StrToFloat((AnsiString)pch);
                pch = strtok (NULL,"\n\t");
                c++;
        }
        float CMofs;

        if(pch == NULL)
                return;        //資料中的data缺少
        CMofs = StrToFloat((AnsiString)pch);

        char cm_buf[5];
        sprintf (cm_buf, "%f", CM3[0][0]);
        CM3_11->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM3[0][1]);
        CM3_12->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM3[0][2]);
        CM3_13->Text = (AnsiString) cm_buf;

        sprintf (cm_buf, "%f", CM3[1][0]);
        CM3_21->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM3[1][1]);
        CM3_22->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM3[1][2]);
        CM3_23->Text = (AnsiString) cm_buf;

        sprintf (cm_buf, "%f", CM3[2][0]);
        CM3_31->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM3[2][1]);
        CM3_32->Text = (AnsiString) cm_buf;
        sprintf (cm_buf, "%f", CM3[2][2]);
        CM3_33->Text = (AnsiString) cm_buf;

        sb_cm31->Position = 100;
        sb_cm32->Position = 100;
        sb_cm33->Position = 100;

        if(ofs_addr[0].Type()==3){      //ofs range -511~+511
                if(CMofs<0)
                        CMofs = CMofs+1023+1;
                sb_ofs3->Position = CMofs;
        }else{
                int CMofs_order;
                if(CM_addr[2].Type()==2)
                        CMofs_order = 4;
                else if(CM_addr[2].Type()==1)
                        CMofs_order = 2;

                sb_ofs3->Position = CMofs*CMofs_order+256;
        }
}
//---------------------------------------------------------------------------
void __fastcall TCMForm1::bn_CM3LoadClick(TObject *Sender)
{
        if(!OpenDialog1->Execute())
                return;
        String Fpath = OpenDialog1->FileName;
        CM3Load(Fpath);
        btn_CM3_WriteClick(Sender);
}
//---------------------------------------------------------------------------



void __fastcall TCMForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 0x40)
                Btn_CM_reloadClick(Sender);
}
//---------------------------------------------------------------------------



void __fastcall TCMForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        delete [] cm_cb;
        delete [] CMChkB;

        delete [] cm_cbo;
        delete [] CMCboB;

        delete [] CM_addr;
        delete [] ofs_addr;
        delete [] OCM;
}
//---------------------------------------------------------------------------



