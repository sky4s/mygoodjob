//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "DCR1.h"
#include "DCR_12401.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"


//---------------------------------------------------------------------------
__fastcall TDCRForm1::TDCRForm1(TComponent* Owner)
        : TForm(Owner)
{
        DCR_Chg = 0;
}
//---------------------------------------------------------------------------
void __fastcall TDCRForm1::DCR_ScrollBar_Scroll(TObject *Sender, TScrollCode ScrollCode, int &ScrollPos)
{
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (DCRScrlB[idx]->ScrlB->Position);
        DCRScrlB[idx]->StTxt->Caption = set_val;
        if(ScrollCode == scEndScroll){
                //滑鼠放開, 或鍵盤操作放開
                if(DCR_Chg==0)
                        return;
                EngineerForm->SetWrite_Byte(DCRScrlB[idx]->Addr ,set_val);
        }
}
//---------------------------------------------------------------------------
void __fastcall TDCRForm1::DCR_ScrollBar2_Scroll(TObject *Sender, TScrollCode ScrollCode, int &ScrollPos)
{
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (DCRScrlB2[idx]->ScrlB->Position);
        DCRScrlB2[idx]->StTxt->Caption = set_val;

        if(ScrollCode == scEndScroll){
                //滑鼠放開, 或鍵盤操作放開
                if(DCR_Chg==0)
                        return;
                int val1 = set_val/DCRScrlB2[idx]->Addr.Divide();
                int val2 = set_val%DCRScrlB2[idx]->Addr.Divide();
                EngineerForm->SetWrite_Byte(DCRScrlB2[idx]->Addr.Byte1 ,val1);
                EngineerForm->SetWrite_Byte(DCRScrlB2[idx]->Addr.Byte2 ,val2);
        }
}
//---------------------------------------------------------------------------
void __fastcall TDCRForm1::DCR_CheckBox_Click(TObject *Sender)
{
        if(DCR_Chg==0)
                return;
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (DCRChkB[idx]->Chkb->Checked?1:0);
        EngineerForm->SetWrite_Byte(DCRChkB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall TDCRForm1::DCR_ComboBox_Click(TObject *Sender)
{
        if(DCR_Chg==0)
                return;
        TComboBox *c = (TComboBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (DCRCboB[idx]->Cbob->ItemIndex);
        EngineerForm->SetWrite_Byte(DCRCboB[idx]->Addr ,set_val);
}
//----------------------------------------------------------------------------

void __fastcall TDCRForm1::DCRLblE3_KeyPress(TObject *Sender, char &Key)
{
        TLabeledEdit *c = (TLabeledEdit *)Sender;
        int idx = StrToInt(c->Hint);

        if(Key!=13){
                DCRLblE3[idx]->Lble->Font->Color = cl3DDkShadow;
                return;
        }
        //Key = 13, 按下Enter
        String tmp_v = DCRLblE3[idx]->Lble->Text;
        if(tmp_v==""){
                tmp_v = "0";
        }
        int set_val = StrToInt(tmp_v);

        if(DCR_Chg==0)
                return;

        unsigned char val1, val2, val3;
        //add for Max hint
        if(set_val>=pow(2,DCRLblE3[idx]->Addr.BitNum())){
                AnsiString max = "Max value:"+IntToStr((int)pow(2,DCRLblE3[idx]->Addr.BitNum()-1));
                ShowMessage(max);
                //read value
                EngineerForm->SetRead_Byte(DCRLblE3[idx]->Addr.Byte1, &val1);
                EngineerForm->SetRead_Byte(DCRLblE3[idx]->Addr.Byte2, &val2);
                EngineerForm->SetRead_Byte(DCRLblE3[idx]->Addr.Byte3, &val3);
                DCRLblE3[idx]->Lble->Text = (int)val1*DCRLblE3[idx]->Addr.Divide1()
                   +(int)val2*DCRLblE3[idx]->Addr.Divide1()+(int)val3;
        }else{
                val1 = set_val/DCRLblE3[idx]->Addr.Divide1();
                val2 = (set_val/DCRLblE3[idx]->Addr.Divide2())%(int)pow(2,DCRLblE3[idx]->Addr.Byte2.BitNum());
                val3 = set_val%DCRLblE3[idx]->Addr.Divide2();
                EngineerForm->SetWrite_Byte(DCRLblE3[idx]->Addr.Byte1 ,val1);
                if(DCRLblE3[idx]->Addr.Byte2.BitNum()!=0)
                        EngineerForm->SetWrite_Byte(DCRLblE3[idx]->Addr.Byte2 ,val2);
                if(DCRLblE3[idx]->Addr.Byte3.BitNum()!=0)
                        EngineerForm->SetWrite_Byte(DCRLblE3[idx]->Addr.Byte3 ,val3);
                DCRLblE3[idx]->Lble->Font->Color = clWindowText;
        }
}

//---------------------------------------------------------------------------

void __fastcall TDCRForm1::FormCreate(TObject *Sender)
{
        int ic_choice;
        if(MainForm->TCON_DEV=="12401")
                ic_choice = 0;

        switch(ic_choice)
        {
                case 0:
                ODCR = new DCR_12401;
                break;

        }

        dcr_lut_addr = ODCR->SetLUT();

        /*****************************************************************
        //      CheckBox: DCRChkBox_Nbr=9                               //
        //                                                              //
        *****************************************************************/

        DCR_cb = ODCR->SetChkBx();
        DCRChkB = new _CHKB* [ODCR->DCRChkBox_Nbr];
        for(int i = 0; i < ODCR->DCRChkBox_Nbr; i++)
                DCRChkB[i] = new _CHKB;

        DCRChkB[0]->Chkb = CheckBox1;
        DCRChkB[1]->Chkb = CheckBox2;
        DCRChkB[2]->Chkb = CheckBox3;
        DCRChkB[3]->Chkb = CheckBox4;
        DCRChkB[4]->Chkb = CheckBox5;
        DCRChkB[5]->Chkb = CheckBox6;
        DCRChkB[6]->Chkb = CheckBox7;
        DCRChkB[7]->Chkb = CheckBox8;
        DCRChkB[8]->Chkb = CheckBox9;

        for(int i = 0; i < ODCR->DCRChkBox_Nbr; i++){
                DCRChkB[i]->Addr = DCR_cb[i];
                DCRChkB[i]->Chkb->Visible = DCRChkB[i]->Addr.FuncEn();
                DCRChkB[i]->Chkb->OnClick = DCR_CheckBox_Click;
                DCRChkB[i]->Chkb->Hint = i;
                DCRChkB[i]->Chkb->Caption = DCRChkB[i]->Addr.Name();
        }

        /*****************************************************************
        //      ComboBox: DCRCboBox_Nbr=4                               //
        //                                                              //
        *****************************************************************/

        DCR_cbo = ODCR->SetCboBx();

        DCRCboB = new _CBOB* [ODCR->DCRCboBox_Nbr];
        for(int i = 0; i < ODCR->DCRCboBox_Nbr; i++)
                DCRCboB[i] = new _CBOB;

        DCRCboB[0]->Cbob = ComboBox1;
        DCRCboB[0]->CbobL= Label14;
        DCRCboB[1]->Cbob = ComboBox2;
        DCRCboB[1]->CbobL= Label15;
        DCRCboB[2]->Cbob = ComboBox3;
        DCRCboB[2]->CbobL= Label16;
        DCRCboB[3]->Cbob = ComboBox4;
        DCRCboB[3]->CbobL= Label17;

        for(int i = 0; i < ODCR->DCRCboBox_Nbr; i++){
                DCRCboB[i]->Addr = DCR_cbo[i];
                DCRCboB[i]->Cbob->Visible = DCRCboB[i]->Addr.FuncEn();
                DCRCboB[i]->CbobL->Visible = DCRCboB[i]->Addr.FuncEn();
                DCRCboB[i]->Cbob->OnClick = DCR_ComboBox_Click;
                DCRCboB[i]->Cbob->Hint = i;
                DCRCboB[i]->CbobL->Caption = DCRCboB[i]->Addr.Name();
                DCRCboB[i]->Cbob->Text = "";
                if(DCRCboB[i]->Addr.FuncEn() == true)
                        for(int j = 0; j < DCRCboB[i]->Addr.choice_nbr; j++)     //ComboBox choice
                                DCRCboB[i]->Cbob->Items->Add(DCRCboB[i]->Addr.choice[j]);
        }

        /*****************************************************************
        //      ScrollBar: DCRScrollBar_Nbr=11                          //
        //                                                              //
        *****************************************************************/

        ScrlB = ODCR->SetScrollBar();

        DCRScrlB = new _ScrollBar* [ODCR->DCRScrollBar_Nbr];
        for(int i = 0; i < ODCR->DCRScrollBar_Nbr; i++)
                DCRScrlB[i] = new _ScrollBar;

        DCRScrlB[0]->Lbl = Label1;
        DCRScrlB[0]->StTxt = StaticText1;
        DCRScrlB[0]->ScrlB = ScrollBar1;

        DCRScrlB[1]->Lbl = Label2;
        DCRScrlB[1]->StTxt = StaticText2;
        DCRScrlB[1]->ScrlB = ScrollBar2;

        DCRScrlB[2]->Lbl = Label3;
        DCRScrlB[2]->StTxt = StaticText3;
        DCRScrlB[2]->ScrlB = ScrollBar3;

        DCRScrlB[3]->Lbl = Label4;
        DCRScrlB[3]->StTxt = StaticText4;
        DCRScrlB[3]->ScrlB = ScrollBar4;

        DCRScrlB[4]->Lbl = Label5;
        DCRScrlB[4]->StTxt = StaticText5;
        DCRScrlB[4]->ScrlB = ScrollBar5;

        DCRScrlB[5]->Lbl = Label6;
        DCRScrlB[5]->StTxt = StaticText6;
        DCRScrlB[5]->ScrlB = ScrollBar6;

        DCRScrlB[6]->Lbl = Label7;
        DCRScrlB[6]->StTxt = StaticText7;
        DCRScrlB[6]->ScrlB = ScrollBar7;

        DCRScrlB[7]->Lbl = Label8;
        DCRScrlB[7]->StTxt = StaticText8;
        DCRScrlB[7]->ScrlB = ScrollBar8;

        DCRScrlB[8]->Lbl = Label9;
        DCRScrlB[8]->StTxt = StaticText9;
        DCRScrlB[8]->ScrlB = ScrollBar9;

        DCRScrlB[9]->Lbl = Label10;
        DCRScrlB[9]->StTxt = StaticText10;
        DCRScrlB[9]->ScrlB = ScrollBar10;

        DCRScrlB[10]->Lbl = Label11;
        DCRScrlB[10]->StTxt = StaticText11;
        DCRScrlB[10]->ScrlB = ScrollBar11;

         for(int i = 0; i < ODCR->DCRScrollBar_Nbr; i++){
                DCRScrlB[i]->Addr = ScrlB[i];
                DCRScrlB[i]->Lbl->Visible = DCRScrlB[i]->Addr.FuncEn();
                DCRScrlB[i]->StTxt->Visible = DCRScrlB[i]->Addr.FuncEn();
                DCRScrlB[i]->ScrlB->Visible = DCRScrlB[i]->Addr.FuncEn();
                DCRScrlB[i]->ScrlB->Min = 0;
                DCRScrlB[i]->ScrlB->Max = (int)pow(2,DCRScrlB[i]->Addr.BitNum())-1;
                DCRScrlB[i]->ScrlB->OnScroll = DCR_ScrollBar_Scroll;
                DCRScrlB[i]->ScrlB->Hint = i;
                DCRScrlB[i]->StTxt->Caption = 0;
                DCRScrlB[i]->Lbl->Caption = DCRScrlB[i]->Addr.Name();
        }

        /*****************************************************************
        //      ScrollBar2: DCRScrollBar2_Nbr=2                         //
        //                                                              //
        *****************************************************************/

        ScrlB2 = ODCR->SetScrollBar2();

        DCRScrlB2 = new _ScrollBar2* [ODCR->DCRScrollBar2_Nbr];
        for(int i = 0; i < ODCR->DCRScrollBar2_Nbr; i++)
                DCRScrlB2[i] = new _ScrollBar2;

        DCRScrlB2[0]->Lbl = Label12;
        DCRScrlB2[0]->StTxt = StaticText12;
        DCRScrlB2[0]->ScrlB = ScrollBar12;

        DCRScrlB2[1]->Lbl = Label13;
        DCRScrlB2[1]->StTxt = StaticText13;
        DCRScrlB2[1]->ScrlB = ScrollBar13;

        for(int i = 0; i < ODCR->DCRScrollBar2_Nbr; i++){
                DCRScrlB2[i]->Addr = ScrlB2[i];
                DCRScrlB2[i]->Lbl->Visible = DCRScrlB2[i]->Addr.FuncEn();
                DCRScrlB2[i]->StTxt->Visible = DCRScrlB2[i]->Addr.FuncEn();
                DCRScrlB2[i]->ScrlB->Visible = DCRScrlB2[i]->Addr.FuncEn();
                DCRScrlB2[i]->ScrlB->Min = 0;
                DCRScrlB2[i]->ScrlB->Max = (int)pow(2,DCRScrlB2[i]->Addr.BitNum())-1;
                DCRScrlB2[i]->ScrlB->OnScroll = DCR_ScrollBar2_Scroll;
                DCRScrlB2[i]->StTxt->Caption = 0;
                DCRScrlB2[i]->ScrlB->Hint = i;
                DCRScrlB2[i]->Lbl->Caption = DCRScrlB2[i]->Addr.Name();
        }

        //LabeledEdit3
        dcr_lble3 = ODCR->SetLblE3();

        DCRLblE3 = new _LBLE3* [ODCR->DCRLblE3_Nbr];
        for(int i = 0; i < ODCR->DCRLblE3_Nbr; i++)
                DCRLblE3[i] = new _LBLE3;

         //DCRLblE3[0]->Lble = LabeledEdit1;
         for(int i = 0; i < ODCR->DCRLblE3_Nbr; i++){
                DCRLblE3[i]->Addr = dcr_lble3[i];
                DCRLblE3[i]->Lble->Visible = DCRLblE3[i]->Addr.FuncEn();
                DCRLblE3[i]->Lble->Hint = i;
                DCRLblE3[i]->Lble->EditLabel->Caption = DCRLblE3[i]->Addr.Name();
                DCRLblE3[i]->Lble->OnKeyPress = DCRLblE3_KeyPress;
                DCRLblE3[i]->Lble->Text = 0;
        }

        DCR_Chg = 1;

        /*****************************************************************
        //      initial LUT                                             //
        *****************************************************************/
        for(int i=0;i<2;i++)
                for(int j=0;j<129;j++){
                        sg_dcr_bl->Cells[0][j+1] = j;
                }
        sg_dcr_bl->Cells[1][0]="BL";

        for(int i=0;i<2;i++)
                for(int j=0;j<129;j++){
                        sg_dcr_dim->Cells[0][j+1] = j;
                }
        sg_dcr_dim->Cells[1][0]="DIM";
}
//---------------------------------------------------------------------------

void __fastcall TDCRForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        delete [] ODCR;
        delete [] DCR_cb;
        delete [] DCRChkB;

        delete [] DCR_cbo;
        delete [] DCRCboB;

        delete [] ScrlB;
        delete [] DCRScrlB;

        delete [] ScrlB2;
        delete [] DCRScrlB2;

        delete [] dcr_lut_addr;
        Action = caFree;
        MainForm->DCRFormNULL();
}
//---------------------------------------------------------------------------

void __fastcall TDCRForm1::Btn_DCR_reloadClick(TObject *Sender)
{
        Btn_DCR_reload->Enabled = false;
        DCR_Chg = 0;
        unsigned char read_val;
        for(int i = 0; i < ODCR->DCRChkBox_Nbr; i++){
                if(DCRChkB[i]->Chkb->Visible==true){
                        EngineerForm->SetRead_Byte(DCRChkB[i]->Addr, &read_val);
                        if(read_val==1)
                                DCRChkB[i]->Chkb->Checked = 1;
                        else if(read_val==0)
                                DCRChkB[i]->Chkb->Checked = 0;
                        else
                                ShowMessage("DCR CheckBox read error:"+IntToStr(read_val));
                }
        }
        for(int i = 0; i < ODCR->DCRCboBox_Nbr; i++){
                if(DCRCboB[i]->Cbob->Visible==true){
                        EngineerForm->SetRead_Byte(DCRCboB[i]->Addr, &read_val);
                        DCRCboB[i]->Cbob->ItemIndex = read_val;
                }
        }

        for(int i = 0; i < ODCR->DCRScrollBar_Nbr; i++){
                if(DCRScrlB[i]->ScrlB->Visible==true){
                        EngineerForm->SetRead_Byte(DCRScrlB[i]->Addr, &read_val);
                        DCRScrlB[i]->ScrlB->Position = read_val;
                        DCRScrlB[i]->StTxt->Caption = read_val;
                }
        }
        unsigned char read_val1, read_val2,read_val3;
        for(int i = 0; i < ODCR->DCRScrollBar2_Nbr; i++){
                if(DCRScrlB2[i]->ScrlB->Visible==true){
                        EngineerForm->SetRead_Byte(DCRScrlB2[i]->Addr.Byte1, &read_val1);
                        EngineerForm->SetRead_Byte(DCRScrlB2[i]->Addr.Byte2, &read_val2);
                        DCRScrlB2[i]->ScrlB->Position = (int)read_val1*DCRScrlB2[i]->Addr.Divide()+read_val2;
                        DCRScrlB2[i]->StTxt->Caption = (int)read_val1*DCRScrlB2[i]->Addr.Divide()+read_val2;
                }
        }

        for(int i = 0; i < ODCR->DCRLblE3_Nbr; i++){
                if(DCRLblE3[i]->Lble->Visible==true){
                        EngineerForm->SetRead_Byte(DCRLblE3[i]->Addr.Byte1, &read_val1);
                        EngineerForm->SetRead_Byte(DCRLblE3[i]->Addr.Byte2, &read_val2);
                        EngineerForm->SetRead_Byte(DCRLblE3[i]->Addr.Byte3, &read_val3);
                        DCRLblE3[i]->Lble->Text = (int)read_val1*DCRLblE3[i]->Addr.Divide1()
                        +(int)read_val2*DCRLblE3[i]->Addr.Divide1()+(int)read_val3;
                }
        }

        DCR_Chg = 1;
        btn_dcr_lut_readClick(Sender);
        Btn_DCR_reload->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TDCRForm1::btn_dcr_lut_readClick(TObject *Sender)
{
        btn_dcr_lut_read->Enabled = false;
        unsigned char* dcr_lut = new unsigned char [128+192];
        EngineerForm->SetRead_DCR(dcr_lut_addr[0],dcr_lut, 128+192);

        for(int i=0; i<128 ; i++){ //backlight lut, 8bit, 128 value
                sg_dcr_bl->Cells[1][i+1] = dcr_lut[i];
        }
        int tmp_idx;
        for(int i = 0; i < 192; i+=3){ //dimming lut, 12bit, 128 value
                tmp_idx = i/3*2;
                sg_dcr_dim->Cells[1][tmp_idx+1] = dcr_lut[128+i]*16+(dcr_lut[128+i+1]/16)%16;
                sg_dcr_dim->Cells[1][tmp_idx+2] = dcr_lut[128+i+1]%16*256+dcr_lut[128+i+2]%256;
        }
        btn_dcr_lut_read->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TDCRForm1::btn_dcr_lut_writeClick(TObject *Sender)
{
        btn_dcr_lut_write->Enabled = false;
        int LUT[320];
        int tmp;
        for(int i=0; i<128 ; i++){  //backlight lut, 8bit, 128 value
                tmp = sg_dcr_bl->Cells[1][i+1].ToIntDef(-1);
                if(tmp==-1){
                        char str[40];
                        sprintf(str,"BL table index %d is wrong", i);
                        ShowMessage(str);
                        btn_dcr_lut_write->Enabled = true;
                        return;
                }
                LUT[i] = tmp;
        }
        int tmp_idx, idx_1, idx_2, idx_3;
        for(int i=0; i<128 ; i+=2){     //dimming lut, 12bit, 128 value
                tmp_idx = i/2*3;
                idx_1 = sg_dcr_dim->Cells[1][i+1].ToIntDef(-1);
                idx_2 = sg_dcr_dim->Cells[1][i+2].ToIntDef(-1);
                if(idx_1==-1 || idx_2==-1){
                        char str[40];
                        sprintf(str,"DIM table index %d is wrong", i);
                        ShowMessage(str);
                        btn_dcr_lut_write->Enabled = true;
                        return;
                }
                LUT[128+tmp_idx] = idx_1/16;
                LUT[128+tmp_idx+1] = idx_1%16*16+idx_2/256;
                LUT[128+tmp_idx+2] = idx_2%256;
        }

        EngineerForm->SetWrite_PG(dcr_lut_addr[0], LUT, 320);
        btn_dcr_lut_write->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TDCRForm1::btn_dcr_lut_loadClick(TObject *Sender)
{
        String Fpath;
        if (OpenDialog1->Execute()){
               Fpath = OpenDialog1->FileName;
               String *dcr_LUT = NULL;
               dcr_LUT = EngineerForm->Load_file(Fpath, 256);
               if(dcr_LUT==NULL){
                        ShowMessage("Load file fail!");
                        return;
               }
               int b_i = 0, d_i = 0;
               int lut_tmp;

               for(int i = 0; i < 128*2; i++){
                        if(i%2 == 0){
                                sg_dcr_bl->Cells[1][b_i+1] = StrToInt(dcr_LUT[i]);
                                b_i++;
                        }else{
                                sg_dcr_dim->Cells[1][d_i+1] = StrToInt(dcr_LUT[i]);
                                d_i++;
                        }
               }
        }
}
//---------------------------------------------------------------------------

void __fastcall TDCRForm1::btn_dcr_lut_saveClick(TObject *Sender)
{
        int bl,dim;
        btn_dcr_lut_save->Enabled=false;

        if(!SaveDialog1->Execute()){
                btn_dcr_lut_save->Enabled=true;
                return;
        }
        String Fpath = SaveDialog1->FileName;
        FILE* fptr = fopen (Fpath.c_str(),"w");

        for(int j=0;j<128; j++){
                bl = sg_dcr_bl->Cells[1][j+1].ToIntDef(-1);
                dim = sg_dcr_dim->Cells[1][j+1].ToIntDef(-1);
                fprintf(fptr,"%02d\t%02d\n",bl,dim);
        }
        fclose(fptr);
        btn_dcr_lut_save->Enabled=true;
}
//---------------------------------------------------------------------------

void __fastcall TDCRForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 0x40)
                Btn_DCR_reloadClick(Sender);
}
//---------------------------------------------------------------------------

