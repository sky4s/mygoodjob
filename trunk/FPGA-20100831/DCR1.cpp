//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "DCR1.h"
#include <fpga/11307/DCR/DCR_12401.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

bool DCR_IsChkSum = 0;// For checksum calculate 20100727 Michelle
//---------------------------------------------------------------------------
__fastcall TDCRForm1::TDCRForm1(TComponent* Owner)
        : TForm(Owner)
{
        DCR_Chg = 0;
        DCREN_idx[0] = -1;
        DCREN_idx[1] = -1;
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
                AnsiString max = "Max value:"+IntToStr((int)pow(2,DCRLblE3[idx]->Addr.BitNum())-1);   //DY0205(-1)->( )-1
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
void __fastcall TDCRForm1::ALS_CheckBox_Click(TObject *Sender)
{
        if(DCR_Chg==0)
                return;
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (ALSChkB[idx]->Chkb->Checked?1:0);
        EngineerForm->SetWrite_Byte(ALSChkB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall TDCRForm1::ALS_ComboBox_Click(TObject *Sender)
{
        if(DCR_Chg==0)
                return;
        TComboBox *c = (TComboBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (ALSCboB[idx]->Cbob->ItemIndex);
        EngineerForm->SetWrite_Byte(ALSCboB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall TDCRForm1::ALS_ScrollBar_Scroll(TObject *Sender, TScrollCode ScrollCode, int &ScrollPos)
{
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (ALSScrlB[idx]->ScrlB->Position);
        ALSScrlB[idx]->StTxt->Caption = set_val;
        if(ScrollCode == scEndScroll){
                //滑鼠放開, 或鍵盤操作放開
                if(DCR_Chg==0)
                        return;
                EngineerForm->SetWrite_Byte(ALSScrlB[idx]->Addr ,set_val);
        }
}
//---------------------------------------------------------------------------
void __fastcall TDCRForm1::HDR_ComboBox_Click(TObject *Sender)
{
        if(DCR_Chg==0)
                return;
        TComboBox *c = (TComboBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (HDRCboB[idx]->Cbob->ItemIndex);
        EngineerForm->SetWrite_Byte(HDRCboB[idx]->Addr ,set_val);
}
//----------------------------------------------------------------------------
void __fastcall TDCRForm1::HDR_ScrollBar_Scroll(TObject *Sender, TScrollCode ScrollCode, int &ScrollPos)
{
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (HDRScrlB[idx]->ScrlB->Position);
        HDRScrlB[idx]->StTxt->Caption = set_val;
        if(ScrollCode == scEndScroll){
                //滑鼠放開, 或鍵盤操作放開
                if(DCR_Chg==0)
                        return;
                EngineerForm->SetWrite_Byte(HDRScrlB[idx]->Addr ,set_val);
        }
}
//----------------------------------------------------------------------------
void __fastcall TDCRForm1::HDR_ScrollBar2_Scroll(TObject *Sender, TScrollCode ScrollCode, int &ScrollPos)
{
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (HDRScrlB2[idx]->ScrlB->Position);
        HDRScrlB2[idx]->StTxt->Caption = set_val;

        if(ScrollCode == scEndScroll){
                //滑鼠放開, 或鍵盤操作放開
                if(DCR_Chg==0)
                        return;
                int val1 = set_val/HDRScrlB2[idx]->Addr.Divide();
                int val2 = set_val%HDRScrlB2[idx]->Addr.Divide();
                EngineerForm->SetWrite_Byte(HDRScrlB2[idx]->Addr.Byte1 ,val1);
                EngineerForm->SetWrite_Byte(HDRScrlB2[idx]->Addr.Byte2 ,val2);
        }
}
//----------------------------------------------------------------------------
void __fastcall TDCRForm1::FormCreate(TObject *Sender)
{
        CheckBox16-> Visible = false;
        //GroupBox41-> Visible = false;
        int ic_choice;
        if(MainForm->TCON_DEV=="11307")
                ic_choice = 0;

        switch(ic_choice)
        {
                case 0:
                ODCR = new DCR_12401();
                break;

        }
        // 20100608 DCR enable name, [0]: BL_EN, [1]: GLT_EN
        String DCRenName[2];
        DCRenName[0] = ODCR->DCR_BL_EN_Name();   // Retrieve DCR enable name 1
        DCRenName[1] = ODCR->DCR_GLT_EN_Name();  // Retrieve DCR enable name 2

        //dcr_lut_addr = ODCR->SetLUT();

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
        	DCRChkB[3]->Chkb = CheckBox5;
        	DCRChkB[4]->Chkb = CheckBox6;
        	DCRChkB[5]->Chkb = CheckBox7;
        	DCRChkB[6]->Chkb = CheckBox8;
        	DCRChkB[7]->Chkb = CheckBox9;
        	DCRChkB[8]->Chkb = CheckBox12;
        	DCRChkB[9]->Chkb = CheckBox16;
        	DCRChkB[10]->Chkb = CheckBox17;
        	DCRChkB[11]->Chkb = CheckBox18;
        	DCRChkB[12]->Chkb = CheckBox20;
        	DCRChkB[13]->Chkb = CheckBox21;
        	DCRChkB[14]->Chkb = CheckBox22;

        for(int i = 0; i < ODCR->DCRChkBox_Nbr; i++){
                DCRChkB[i]->Addr = DCR_cb[i];
                DCRChkB[i]->Chkb->Visible = DCRChkB[i]->Addr.FuncEn();
                DCRChkB[i]->Chkb->OnClick = DCR_CheckBox_Click;
                DCRChkB[i]->Chkb->Hint = i;
                DCRChkB[i]->Chkb->Caption = DCRChkB[i]->Addr.Name();
                // 20100608 find index for DCR enable 1
                if(DCRChkB[i]->Addr.Name() == DCRenName[0])
                        DCREN_idx[0] = i;
                // 20100608 find index for DCR enable 2
                else if(DCRChkB[i]->Addr.Name() == DCRenName[1])
                        DCREN_idx[1] = i;
        }
        // 20100608 Fail to retriev DCR enable
        if(DCREN_idx[0]==-1 || DCREN_idx[1]==-1)
                ShowMessage("Can't Get DCR enable index.");

        /*****************************************************************
        //      ComboBox: DCRCboBox_Nbr=5                               //
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
        DCRCboB[4]->Cbob = ComboBox5;
        DCRCboB[4]->CbobL= Label54;
        DCRCboB[5]->Cbob = ComboBox12;
        DCRCboB[5]->CbobL= Label80;
        DCRCboB[6]->Cbob = ComboBox13;
        DCRCboB[6]->CbobL= Label81;
        DCRCboB[7]->Cbob = ComboBox15;
        DCRCboB[7]->CbobL= Label83;
        DCRCboB[8]->Cbob = ComboBox16;
        DCRCboB[8]->CbobL= Label84;

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
        //      ScrollBar: DCRScrollBar_Nbr=22                          //
        //                                                              //
        *****************************************************************/

        ScrlB = ODCR->SetScrollBar();

        DCRScrlB = new _ScrollBar* [ODCR->DCRScrollBar_Nbr];
        for(int i = 0; i < ODCR->DCRScrollBar_Nbr; i++)
                DCRScrlB[i] = new _ScrollBar;

        DCRScrlB[0]->Lbl = Label2;
        DCRScrlB[0]->StTxt = StaticText2;
        DCRScrlB[0]->ScrlB = ScrollBar2;

        DCRScrlB[1]->Lbl = Label1;
        DCRScrlB[1]->StTxt = StaticText1;
        DCRScrlB[1]->ScrlB = ScrollBar1;

        DCRScrlB[2]->Lbl = Label5;
        DCRScrlB[2]->StTxt = StaticText5;
        DCRScrlB[2]->ScrlB = ScrollBar5;

        DCRScrlB[3]->Lbl = Label35;
        DCRScrlB[3]->StTxt = StaticText31;
        DCRScrlB[3]->ScrlB = ScrollBar31;

        DCRScrlB[4]->Lbl = Label10;
        DCRScrlB[4]->StTxt = StaticText10;
        DCRScrlB[4]->ScrlB = ScrollBar10;

        DCRScrlB[5]->Lbl = Label11;         
        DCRScrlB[5]->StTxt = StaticText11;
        DCRScrlB[5]->ScrlB = ScrollBar11;   
                                            
        DCRScrlB[6]->Lbl = Label37;            
        DCRScrlB[6]->StTxt = StaticText33;      
        DCRScrlB[6]->ScrlB = ScrollBar33;       
                                               
        DCRScrlB[7]->Lbl = Label38;            
        DCRScrlB[7]->StTxt = StaticText34;     
        DCRScrlB[7]->ScrlB = ScrollBar34;      
                                               
        DCRScrlB[8]->Lbl = Label42;            
        DCRScrlB[8]->StTxt  = StaticText38;    
        DCRScrlB[8]->ScrlB  = ScrollBar38;     
                   
        DCRScrlB[9]->Lbl = Label43;       
        DCRScrlB[9]->StTxt = StaticText39;
        DCRScrlB[9]->ScrlB = ScrollBar39; 

        DCRScrlB[10]->Lbl = Label44;         
        DCRScrlB[10]->StTxt = StaticText40;  
        DCRScrlB[10]->ScrlB = ScrollBar40;  
                                                                    
        DCRScrlB[11]->Lbl = Label45;        
        DCRScrlB[11]->StTxt = StaticText41; 
        DCRScrlB[11]->ScrlB = ScrollBar41;  
                                            
        DCRScrlB[12]->Lbl = Label46;        
        DCRScrlB[12]->StTxt = StaticText42; 
        DCRScrlB[12]->ScrlB = ScrollBar42;  
                                            
        DCRScrlB[13]->Lbl = Label47;        
        DCRScrlB[13]->StTxt = StaticText43; 
        DCRScrlB[13]->ScrlB = ScrollBar43;  
                                            
        DCRScrlB[14]->Lbl = Label48;        
        DCRScrlB[14]->StTxt = StaticText44; 
        DCRScrlB[14]->ScrlB = ScrollBar44;  
                                            
        DCRScrlB[15]->Lbl = Label49;        
        DCRScrlB[15]->StTxt = StaticText45; 
        DCRScrlB[15]->ScrlB = ScrollBar45;  
                                            
        DCRScrlB[16]->Lbl = Label50;        
        DCRScrlB[16]->StTxt = StaticText46; 
        DCRScrlB[16]->ScrlB = ScrollBar46;  
                                            
        DCRScrlB[17]->Lbl = Label51;        
        DCRScrlB[17]->StTxt = StaticText47; 
        DCRScrlB[17]->ScrlB = ScrollBar47;  
                                            
        DCRScrlB[18]->Lbl = Label52;        
        DCRScrlB[18]->StTxt = StaticText48; 
        DCRScrlB[18]->ScrlB = ScrollBar48;  
                                            
        DCRScrlB[19]->Lbl = Label53;        
        DCRScrlB[19]->StTxt = StaticText49; 
        DCRScrlB[19]->ScrlB = ScrollBar49;

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
        //      ScrollBar2: DCRScrollBar2_Nbr=11                         //
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
        
        DCRScrlB2[2]->Lbl = Label8;
        DCRScrlB2[2]->StTxt = StaticText8;
        DCRScrlB2[2]->ScrlB = ScrollBar8;
        
        DCRScrlB2[3]->Lbl = Label9;
        DCRScrlB2[3]->StTxt = StaticText9;
        DCRScrlB2[3]->ScrlB = ScrollBar9;
        
        DCRScrlB2[4]->Lbl = Label33;
        DCRScrlB2[4]->StTxt = StaticText29;
        DCRScrlB2[4]->ScrlB = ScrollBar29;
        
        DCRScrlB2[5]->Lbl = Label39;
        DCRScrlB2[5]->StTxt = StaticText35;
        DCRScrlB2[5]->ScrlB = ScrollBar35;
        
        DCRScrlB2[6]->Lbl = Label40;
        DCRScrlB2[6]->StTxt = StaticText36;
        DCRScrlB2[6]->ScrlB = ScrollBar36;
        
        DCRScrlB2[7]->Lbl = Label3;
        DCRScrlB2[7]->StTxt = StaticText3;
        DCRScrlB2[7]->ScrlB = ScrollBar3;
        
        DCRScrlB2[8]->Lbl = Label32;
        DCRScrlB2[8]->StTxt = StaticText28;
        DCRScrlB2[8]->ScrlB = ScrollBar28;
        
        DCRScrlB2[9]->Lbl = Label41;
        DCRScrlB2[9]->StTxt = StaticText37;
        DCRScrlB2[9]->ScrlB = ScrollBar37;
        
        DCRScrlB2[10]->Lbl = Label34;
        DCRScrlB2[10]->StTxt = StaticText30;
        DCRScrlB2[10]->ScrlB = ScrollBar30;

        DCRScrlB2[11]->Lbl = Label4;
        DCRScrlB2[11]->StTxt = StaticText4;
        DCRScrlB2[11]->ScrlB = ScrollBar4;

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
        /*****************************************************************
        //      LableEdit: DCRLblE2_Nbr=10                              //
        //                                                              //
        *****************************************************************/
        dcr_lble2 = ODCR->SetDCRLblE2();

        DCRLblE2 = new _LBLE2* [ODCR->DCRLblE2_Nbr];
        for(int i = 0; i < ODCR->DCRLblE2_Nbr; i++)
                DCRLblE2[i] = new _LBLE2;

        DCRLblE2[0]->Lble = LabeledEdit2;
        DCRLblE2[1]->Lble = LabeledEdit3;
        DCRLblE2[2]->Lble = LabeledEdit5;
        DCRLblE2[3]->Lble = LabeledEdit6;   
        DCRLblE2[4]->Lble = LabeledEdit7;   
        DCRLblE2[5]->Lble = LabeledEdit8;   
        DCRLblE2[6]->Lble = LabeledEdit9;   
        DCRLblE2[7]->Lble = LabeledEdit10;


        for(int i = 0; i < ODCR->DCRLblE2_Nbr; i++){
                DCRLblE2[i]->Addr = dcr_lble2[i];
                DCRLblE2[i]->Lble->Visible = DCRLblE2[i]->Addr.FuncEn();
                //DrvLblE2[i]->Lble->OnChange = Drv_LblEdit2_Change;
                DCRLblE2[i]->Lble->OnKeyPress = DCR_LblEdit2_KeyPress;
                DCRLblE2[i]->Lble->Hint = i;
                DCRLblE2[i]->Lble->EditLabel->Caption = DCRLblE2[i]->Addr.Name();
                DCRLblE2[i]->Lble->Text = 0;
        }

        //LabeledEdit3
        dcr_lble3 = ODCR->SetLblE3();

        DCRLblE3 = new _LBLE3* [ODCR->DCRLblE3_Nbr];
        for(int i = 0; i < ODCR->DCRLblE3_Nbr; i++)
                DCRLblE3[i] = new _LBLE3;

        DCRLblE3[0]->Lble = LabeledEdit1;
        DCRLblE3[1]->Lble = LabeledEdit4;
        for(int i = 0; i < ODCR->DCRLblE3_Nbr; i++){
                DCRLblE3[i]->Addr = dcr_lble3[i];
                DCRLblE3[i]->Lble->Visible = DCRLblE3[i]->Addr.FuncEn();
                DCRLblE3[i]->Lble->Hint = i;
                DCRLblE3[i]->Lble->EditLabel->Caption = DCRLblE3[i]->Addr.Name();
                DCRLblE3[i]->Lble->OnKeyPress = DCRLblE3_KeyPress;
                DCRLblE3[i]->Lble->Text = 0;
        }
        Addr_DCRLUT = ODCR->SetLUT();
        Initial_DCR_table();   // 20100608 DCR table initial (BL,DIM,...)
        DCR_Chg = 1;

        /*****************************************************************
        //      initial LUT                                             //
        *****************************************************************/
        /*
        for(int i=0;i<2;i++)
                for(int j=0;j<128;j++){
                        sg_dcr_hist->Cells[0][j+1] ="hm"+IntToStr(j);
                }
        sg_dcr_hist->Cells[1][0]="HM";
        for(int i=0;i<2;i++)
                for(int j=0;j<256;j++){
                        sg_dcr_bl->Cells[0][j+1] = "idx"+IntToStr(j);
                }
        sg_dcr_bl->Cells[1][0]="BL";

        for(int i=0;i<2;i++)
                for(int j=0;j<256;j++){
                        sg_dcr_dim->Cells[0][j+1] = "dim"+IntToStr(j);
                }
        sg_dcr_dim->Cells[1][0]="DIM";
        */
        //--------------------------------------------------------------

        /*****************************************************************
        //      CheckBox: ALSChkBox_Nbr=4                               //
        //                                                              //
        *****************************************************************/

        ALS_cb = ODCR->SetALSChkBx();
        ALSChkB = new _CHKB* [ODCR->ALSChkBox_Nbr];
        for(int i = 0; i < ODCR->ALSChkBox_Nbr; i++)
                ALSChkB[i] = new _CHKB;

        	ALSChkB[0]->Chkb = CheckBox11;
        	ALSChkB[1]->Chkb = CheckBox23;
        	ALSChkB[2]->Chkb = CheckBox24;

        for(int i = 0; i < ODCR->ALSChkBox_Nbr; i++){
                ALSChkB[i]->Addr = ALS_cb[i];
                ALSChkB[i]->Chkb->Visible = ALSChkB[i]->Addr.FuncEn();
                ALSChkB[i]->Chkb->OnClick = ALS_CheckBox_Click;
                ALSChkB[i]->Chkb->Hint = i;
                ALSChkB[i]->Chkb->Caption = ALSChkB[i]->Addr.Name();
        }
        /*****************************************************************
        //      ComboBox: ALSCboBox_Nbr=1                               //
        //                                                              //
        *****************************************************************/
        ALS_cbo = ODCR->SetALSCboBx();

        ALSCboB = new _CBOB* [ODCR->ALSCboBox_Nbr];
        for(int i = 0; i < ODCR->ALSCboBox_Nbr; i++)
                ALSCboB[i] = new _CBOB;

        ALSCboB[0]->Cbob = ComboBox14;
        ALSCboB[0]->CbobL= Label82;

        for(int i = 0; i < ODCR->ALSCboBox_Nbr; i++){
                ALSCboB[i]->Addr = ALS_cbo[i];
                ALSCboB[i]->Cbob->Visible = ALSCboB[i]->Addr.FuncEn();
                ALSCboB[i]->CbobL->Visible = ALSCboB[i]->Addr.FuncEn();
                ALSCboB[i]->Cbob->OnClick = ALS_ComboBox_Click;
                ALSCboB[i]->Cbob->Hint = i;
                ALSCboB[i]->CbobL->Caption = ALSCboB[i]->Addr.Name();
                ALSCboB[i]->Cbob->Text = "";
                if(ALSCboB[i]->Addr.FuncEn() == true)
                        for(int j = 0; j < ALSCboB[i]->Addr.choice_nbr; j++)     //ComboBox choice
                                ALSCboB[i]->Cbob->Items->Add(ALSCboB[i]->Addr.choice[j]);
        }

        /*****************************************************************
        //      ScrollBar: ALSScrollBar_Nbr=11                          //
        //                                                              //
        *****************************************************************/

        alsScrlB = ODCR->SetALSScrollBar();

        ALSScrlB = new _ScrollBar* [ODCR->ALSScrollBar_Nbr];

        for(int i = 0; i < ODCR->ALSScrollBar_Nbr; i++)
                ALSScrlB[i] = new _ScrollBar;

        ALSScrlB[0]->Lbl = Label6;
        ALSScrlB[0]->StTxt = StaticText6;
        ALSScrlB[0]->ScrlB = ScrollBar6;

        ALSScrlB[1]->Lbl = Label7;
        ALSScrlB[1]->StTxt = StaticText7;
        ALSScrlB[1]->ScrlB = ScrollBar7;

        ALSScrlB[2]->Lbl = Label18;
        ALSScrlB[2]->StTxt = StaticText14;
        ALSScrlB[2]->ScrlB = ScrollBar14;

        ALSScrlB[3]->Lbl = Label19;
        ALSScrlB[3]->StTxt = StaticText15;
        ALSScrlB[3]->ScrlB = ScrollBar15;

        ALSScrlB[4]->Lbl = Label20;
        ALSScrlB[4]->StTxt = StaticText16;
        ALSScrlB[4]->ScrlB = ScrollBar16;

        ALSScrlB[5]->Lbl = Label21;
        ALSScrlB[5]->StTxt = StaticText17;
        ALSScrlB[5]->ScrlB = ScrollBar17;

        ALSScrlB[6]->Lbl = Label22;
        ALSScrlB[6]->StTxt = StaticText18;
        ALSScrlB[6]->ScrlB = ScrollBar18;

        ALSScrlB[7]->Lbl = Label23;
        ALSScrlB[7]->StTxt = StaticText19;
        ALSScrlB[7]->ScrlB = ScrollBar19;

        ALSScrlB[8]->Lbl = Label24;
        ALSScrlB[8]->StTxt = StaticText20;
        ALSScrlB[8]->ScrlB = ScrollBar20;

        ALSScrlB[9]->Lbl = Label25;
        ALSScrlB[9]->StTxt = StaticText21;
        ALSScrlB[9]->ScrlB = ScrollBar21;

        ALSScrlB[10]->Lbl = Label26;
        ALSScrlB[10]->StTxt = StaticText22;
        ALSScrlB[10]->ScrlB = ScrollBar22;

        ALSScrlB[11]->Lbl = Label27;
        ALSScrlB[11]->StTxt = StaticText23;
        ALSScrlB[11]->ScrlB = ScrollBar23;

        ALSScrlB[12]->Lbl = Label28;
        ALSScrlB[12]->StTxt = StaticText24;
        ALSScrlB[12]->ScrlB = ScrollBar24;

        ALSScrlB[13]->Lbl = Label29;
        ALSScrlB[13]->StTxt = StaticText25;
        ALSScrlB[13]->ScrlB = ScrollBar25;

        ALSScrlB[14]->Lbl = Label30;
        ALSScrlB[14]->StTxt = StaticText26;
        ALSScrlB[14]->ScrlB = ScrollBar26;

        ALSScrlB[15]->Lbl = Label31;
        ALSScrlB[15]->StTxt = StaticText27;
        ALSScrlB[15]->ScrlB = ScrollBar27;

        ALSScrlB[16]->Lbl = Label79;
        ALSScrlB[16]->StTxt = StaticText67;
        ALSScrlB[16]->ScrlB = ScrollBar67;

        ALSScrlB[17]->Lbl = Label36;
        ALSScrlB[17]->StTxt = StaticText32;
        ALSScrlB[17]->ScrlB = ScrollBar32;

        for(int i = 0; i < ODCR->ALSScrollBar_Nbr; i++){
                ALSScrlB[i]->Addr = alsScrlB[i];
                ALSScrlB[i]->Lbl->Visible = ALSScrlB[i]->Addr.FuncEn();
                ALSScrlB[i]->StTxt->Visible = ALSScrlB[i]->Addr.FuncEn();
                ALSScrlB[i]->ScrlB->Visible = ALSScrlB[i]->Addr.FuncEn();
                ALSScrlB[i]->ScrlB->Min = 0;
                ALSScrlB[i]->ScrlB->Max = (int)pow(2,ALSScrlB[i]->Addr.BitNum())-1;
                ALSScrlB[i]->ScrlB->OnScroll = ALS_ScrollBar_Scroll;
                ALSScrlB[i]->ScrlB->Hint = i;
                ALSScrlB[i]->StTxt->Caption = 0;
                ALSScrlB[i]->Lbl->Caption = ALSScrlB[i]->Addr.Name();
        }





        /*****************************************************************
        //      ScrollBar: HDRScrollBar_Nbr=11                          //
        //                                                              //
        *****************************************************************/

        hdrScrlB = ODCR->SetHDRScrollBar();

        HDRScrlB = new _ScrollBar* [ODCR->HDRScrollBar_Nbr];
    /*
        for(int i = 0; i < ODCR->HDRScrollBar_Nbr; i++)
                HDRScrlB[i] = new _ScrollBar;

        HDRScrlB[0]->Lbl = Label55;
        HDRScrlB[0]->StTxt = StaticText50;
        HDRScrlB[0]->ScrlB = ScrollBar50;

        HDRScrlB[1]->Lbl = Label56;
        HDRScrlB[1]->StTxt = StaticText51;
        HDRScrlB[1]->ScrlB = ScrollBar51;

        HDRScrlB[2]->Lbl = Label57;
        HDRScrlB[2]->StTxt = StaticText52;
        HDRScrlB[2]->ScrlB = ScrollBar52;

        HDRScrlB[3]->Lbl = Label58;
        HDRScrlB[3]->StTxt = StaticText53;
        HDRScrlB[3]->ScrlB = ScrollBar53;

        HDRScrlB[4]->Lbl = Label59;
        HDRScrlB[4]->StTxt = StaticText54;
        HDRScrlB[4]->ScrlB = ScrollBar54;

        HDRScrlB[5]->Lbl = Label60;
        HDRScrlB[5]->StTxt = StaticText55;
        HDRScrlB[5]->ScrlB = ScrollBar55;

        HDRScrlB[6]->Lbl = Label61;
        HDRScrlB[6]->StTxt = StaticText56;
        HDRScrlB[6]->ScrlB = ScrollBar56;

        HDRScrlB[7]->Lbl = Label62;
        HDRScrlB[7]->StTxt = StaticText57;
        HDRScrlB[7]->ScrlB = ScrollBar57;

        HDRScrlB[8]->Lbl = Label63;
        HDRScrlB[8]->StTxt = StaticText58;
        HDRScrlB[8]->ScrlB = ScrollBar58;

        HDRScrlB[9]->Lbl = Label64;
        HDRScrlB[9]->StTxt = StaticText59;
        HDRScrlB[9]->ScrlB = ScrollBar59;

        HDRScrlB[10]->Lbl = Label65;
        HDRScrlB[10]->StTxt = StaticText60;
        HDRScrlB[10]->ScrlB = ScrollBar60;

        HDRScrlB[11]->Lbl = Label66;
        HDRScrlB[11]->StTxt = StaticText61;
        HDRScrlB[11]->ScrlB = ScrollBar61;

        HDRScrlB[12]->Lbl = Label67;
        HDRScrlB[12]->StTxt = StaticText62;
        HDRScrlB[12]->ScrlB = ScrollBar62;

        HDRScrlB[13]->Lbl = Label68;
        HDRScrlB[13]->StTxt = StaticText63;
        HDRScrlB[13]->ScrlB = ScrollBar63;

        HDRScrlB[14]->Lbl = Label69;
        HDRScrlB[14]->StTxt = StaticText64;
        HDRScrlB[14]->ScrlB = ScrollBar64;

        HDRScrlB[15]->Lbl = Label70;
        HDRScrlB[15]->StTxt = StaticText65;
        HDRScrlB[15]->ScrlB = ScrollBar65;

        HDRScrlB[16]->Lbl = Label71;
        HDRScrlB[16]->StTxt = StaticText66;
        HDRScrlB[16]->ScrlB = ScrollBar66;


        for(int i = 0; i < ODCR->HDRScrollBar_Nbr; i++){
                HDRScrlB[i]->Addr = hdrScrlB[i];
                HDRScrlB[i]->Lbl->Visible = HDRScrlB[i]->Addr.FuncEn();
                HDRScrlB[i]->StTxt->Visible = HDRScrlB[i]->Addr.FuncEn();
                HDRScrlB[i]->ScrlB->Visible = HDRScrlB[i]->Addr.FuncEn();
                HDRScrlB[i]->ScrlB->Min = 0;
                HDRScrlB[i]->ScrlB->Max = (int)pow(2,HDRScrlB[i]->Addr.BitNum())-1;
                HDRScrlB[i]->ScrlB->OnScroll = HDR_ScrollBar_Scroll;
                HDRScrlB[i]->ScrlB->Hint = i;
                HDRScrlB[i]->StTxt->Caption = 0;
                HDRScrlB[i]->Lbl->Caption = HDRScrlB[i]->Addr.Name();
        }
     */




        /*****************************************************************
        //      ScrollBar2: HDRScrollBar2_Nbr=2                         //
        //                                                              //
        *****************************************************************/

        hdrScrlB2 = ODCR->SetHDRScrollBar2();

        HDRScrlB2 = new _ScrollBar2* [ODCR->HDRScrollBar2_Nbr];
        for(int i = 0; i < ODCR->HDRScrollBar2_Nbr; i++)
                HDRScrlB2[i] = new _ScrollBar2;

        HDRScrlB2[0]->Lbl = Label55;
        HDRScrlB2[0]->StTxt = StaticText50;
        HDRScrlB2[0]->ScrlB = ScrollBar50;

        HDRScrlB2[1]->Lbl = Label56;
        HDRScrlB2[1]->StTxt = StaticText51;
        HDRScrlB2[1]->ScrlB = ScrollBar51;

        HDRScrlB2[2]->Lbl = Label57;
        HDRScrlB2[2]->StTxt = StaticText52;
        HDRScrlB2[2]->ScrlB = ScrollBar52;

        HDRScrlB2[3]->Lbl = Label58;
        HDRScrlB2[3]->StTxt = StaticText53;
        HDRScrlB2[3]->ScrlB = ScrollBar53;

        HDRScrlB2[4]->Lbl = Label59;
        HDRScrlB2[4]->StTxt = StaticText54;
        HDRScrlB2[4]->ScrlB = ScrollBar54;

        HDRScrlB2[5]->Lbl = Label60;
        HDRScrlB2[5]->StTxt = StaticText55;
        HDRScrlB2[5]->ScrlB = ScrollBar55;

        HDRScrlB2[6]->Lbl = Label61;
        HDRScrlB2[6]->StTxt = StaticText56;
        HDRScrlB2[6]->ScrlB = ScrollBar56;

        HDRScrlB2[7]->Lbl = Label62;
        HDRScrlB2[7]->StTxt = StaticText57;
        HDRScrlB2[7]->ScrlB = ScrollBar57;

        HDRScrlB2[8]->Lbl = Label63;
        HDRScrlB2[8]->StTxt = StaticText58;
        HDRScrlB2[8]->ScrlB = ScrollBar58;

        HDRScrlB2[9]->Lbl = Label64;
        HDRScrlB2[9]->StTxt = StaticText59;
        HDRScrlB2[9]->ScrlB = ScrollBar59;

        HDRScrlB2[10]->Lbl = Label65;
        HDRScrlB2[10]->StTxt = StaticText60;
        HDRScrlB2[10]->ScrlB = ScrollBar60;

        HDRScrlB2[11]->Lbl = Label66;
        HDRScrlB2[11]->StTxt = StaticText61;
        HDRScrlB2[11]->ScrlB = ScrollBar61;

        HDRScrlB2[12]->Lbl = Label67;
        HDRScrlB2[12]->StTxt = StaticText62;
        HDRScrlB2[12]->ScrlB = ScrollBar62;

        HDRScrlB2[13]->Lbl = Label68;
        HDRScrlB2[13]->StTxt = StaticText63;
        HDRScrlB2[13]->ScrlB = ScrollBar63;

        HDRScrlB2[14]->Lbl = Label69;
        HDRScrlB2[14]->StTxt = StaticText64;
        HDRScrlB2[14]->ScrlB = ScrollBar64;

        HDRScrlB2[15]->Lbl = Label70;
        HDRScrlB2[15]->StTxt = StaticText65;
        HDRScrlB2[15]->ScrlB = ScrollBar65;

        HDRScrlB2[16]->Lbl = Label71;
        HDRScrlB2[16]->StTxt = StaticText66;
        HDRScrlB2[16]->ScrlB = ScrollBar66;

        for(int i = 0; i < ODCR->HDRScrollBar2_Nbr; i++){
                HDRScrlB2[i]->Addr = hdrScrlB2[i];
                HDRScrlB2[i]->Lbl->Visible = HDRScrlB2[i]->Addr.FuncEn();
                HDRScrlB2[i]->StTxt->Visible = HDRScrlB2[i]->Addr.FuncEn();
                HDRScrlB2[i]->ScrlB->Visible = HDRScrlB2[i]->Addr.FuncEn();
                HDRScrlB2[i]->ScrlB->Min = 0;
                HDRScrlB2[i]->ScrlB->Max = (int)pow(2,HDRScrlB2[i]->Addr.BitNum())-1;
                HDRScrlB2[i]->ScrlB->OnScroll = HDR_ScrollBar2_Scroll;
                HDRScrlB2[i]->StTxt->Caption = 0;
                HDRScrlB2[i]->ScrlB->Hint = i;
                HDRScrlB2[i]->Lbl->Caption = HDRScrlB2[i]->Addr.Name();
        }
        /*****************************************************************
        //      LableEdit: HDRLblE2_Nbr=5                               //
        //                                                              //
        *****************************************************************/
        hdr_lble2 = ODCR->SetHDRLblE2();

        HDRLblE2 = new _LBLE2* [ODCR->HDRLblE2_Nbr];
        for(int i = 0; i < ODCR->HDRLblE2_Nbr; i++)
                HDRLblE2[i] = new _LBLE2;

        HDRLblE2[0]->Lble = LabeledEdit11;
        HDRLblE2[1]->Lble = LabeledEdit12;
        HDRLblE2[2]->Lble = LabeledEdit13;
        HDRLblE2[3]->Lble = LabeledEdit14;
        HDRLblE2[4]->Lble = LabeledEdit15;



        for(int i = 0; i < ODCR->HDRLblE2_Nbr; i++){
                HDRLblE2[i]->Addr = hdr_lble2[i];
                HDRLblE2[i]->Lble->Visible = HDRLblE2[i]->Addr.FuncEn();
                //DrvLblE2[i]->Lble->OnChange = Drv_LblEdit2_Change;
                HDRLblE2[i]->Lble->OnKeyPress = HDR_LblEdit2_KeyPress;
                HDRLblE2[i]->Lble->Hint = i;
                HDRLblE2[i]->Lble->EditLabel->Caption = HDRLblE2[i]->Addr.Name();
                HDRLblE2[i]->Lble->Text = 0;
        }

        /*****************************************************************
        //      ComboBox: HDRCboBox_Nbr=5                               //
        //                                                              //
        *****************************************************************/

        HDR_cbo = ODCR->SetHDRCboBx();

        HDRCboB = new _CBOB* [ODCR->HDRCboBox_Nbr];
        for(int i = 0; i < ODCR->HDRCboBox_Nbr; i++)
                HDRCboB[i] = new _CBOB;

        HDRCboB[0]->Cbob = ComboBox6;
        HDRCboB[0]->CbobL= Label72;
        HDRCboB[1]->Cbob = ComboBox7;
        HDRCboB[1]->CbobL= Label73;
        HDRCboB[2]->Cbob = ComboBox8;
        HDRCboB[2]->CbobL= Label74;
        HDRCboB[3]->Cbob = ComboBox9;
        HDRCboB[3]->CbobL= Label75;
        HDRCboB[4]->Cbob = ComboBox10;
        HDRCboB[4]->CbobL= Label76;
        HDRCboB[5]->Cbob = ComboBox11;
        HDRCboB[5]->CbobL= Label77;

        for(int i = 0; i < ODCR->HDRCboBox_Nbr; i++){
                HDRCboB[i]->Addr = HDR_cbo[i];
                HDRCboB[i]->Cbob->Visible = HDRCboB[i]->Addr.FuncEn();
                HDRCboB[i]->CbobL->Visible = HDRCboB[i]->Addr.FuncEn();
                HDRCboB[i]->Cbob->OnClick = HDR_ComboBox_Click;
                HDRCboB[i]->Cbob->Hint = i;
                HDRCboB[i]->CbobL->Caption = HDRCboB[i]->Addr.Name();
                HDRCboB[i]->Cbob->Text = "";
                if(HDRCboB[i]->Addr.FuncEn() == true)
                        for(int j = 0; j < HDRCboB[i]->Addr.choice_nbr; j++)     //ComboBox choice
                                HDRCboB[i]->Cbob->Items->Add(HDRCboB[i]->Addr.choice[j]);
        }

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
        delete [] Addr_DCRLUT;

        delete [] dcr_lble2;
        delete [] DCRLblE2;
        //ALS
        delete [] ALS_cb;
        delete [] ALSChkB;

        delete [] alsScrlB;
        delete [] ALSScrlB;
        //HDR
        delete [] HDR_cbo;
        delete [] HDRCboB;

        delete [] hdrScrlB;
        delete [] HDRScrlB;

        delete [] hdr_lble2;
        delete [] HDRLblE2;
        delete [] sg_dcr;
        Action = caFree;
        MainForm->DCRFormNULL();
}
// 20100608 initial DCR table (dynamic StringGrid)
void TDCRForm1::Initial_DCR_table()
{
        sg_dcr = new TStringGrid* [ODCR->DCRLUT_Nbr];
        for(int i = 0; i < ODCR->DCRLUT_Nbr; i++){
                sg_dcr[i] = new TStringGrid(this) ;
                sg_dcr[i]->Parent = TabSheet5;
                sg_dcr[i]->Options<<goEditing;
                sg_dcr[i]->Top = 24;
                sg_dcr[i]->Left = 60+120*i;
                sg_dcr[i]->Height = 400;
                sg_dcr[i]->Width = 105;
                sg_dcr[i]->DefaultColWidth = 40;
                sg_dcr[i]->DefaultRowHeight = 20;
                sg_dcr[i]->ColCount = 2;
                sg_dcr[i]->RowCount = Addr_DCRLUT[i].LutNum()+1;
                sg_dcr[i]->Cells[1][0]=Addr_DCRLUT[i].Name();
                for(int j=0;j<Addr_DCRLUT[i].LutNum();j++){
                        sg_dcr[i]->Cells[0][j+1] = j;
                        sg_dcr[i]->Cells[1][j+1] = j;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TDCRForm1::Btn_DCR_reloadClick(TObject *Sender)
{
        Btn_DCR_reload->Enabled = false;
        DCR_Chg = 0;
        unsigned char read_val;
        //DCRChkBox
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
        //DCRCboBox
        for(int i = 0; i < ODCR->DCRCboBox_Nbr; i++){
                if(DCRCboB[i]->Cbob->Visible==true){
                        EngineerForm->SetRead_Byte(DCRCboB[i]->Addr, &read_val);
                        DCRCboB[i]->Cbob->ItemIndex = read_val;
                }
        }
        //DCRScrollBar
        for(int i = 0; i < ODCR->DCRScrollBar_Nbr; i++){
                if(DCRScrlB[i]->ScrlB->Visible==true){
                        EngineerForm->SetRead_Byte(DCRScrlB[i]->Addr, &read_val);
                        DCRScrlB[i]->ScrlB->Position = read_val;
                        DCRScrlB[i]->StTxt->Caption = read_val;
                }
        }
        //DCRScrollBar2
        unsigned char read_val1, read_val2,read_val3;
        for(int i = 0; i < ODCR->DCRScrollBar2_Nbr; i++){
                if(DCRScrlB2[i]->ScrlB->Visible==true){
                        EngineerForm->SetRead_Byte(DCRScrlB2[i]->Addr.Byte1, &read_val1);
                        EngineerForm->SetRead_Byte(DCRScrlB2[i]->Addr.Byte2, &read_val2);
                        DCRScrlB2[i]->ScrlB->Position = (int)read_val1*DCRScrlB2[i]->Addr.Divide()+read_val2;
                        DCRScrlB2[i]->StTxt->Caption = (int)read_val1*DCRScrlB2[i]->Addr.Divide()+read_val2;
                }
        }
        //DCRLblE3
        for(int i = 0; i < ODCR->DCRLblE3_Nbr; i++){
                if(DCRLblE3[i]->Lble->Visible==true){
                        EngineerForm->SetRead_Byte(DCRLblE3[i]->Addr.Byte1, &read_val1);
                        EngineerForm->SetRead_Byte(DCRLblE3[i]->Addr.Byte2, &read_val2);
                        EngineerForm->SetRead_Byte(DCRLblE3[i]->Addr.Byte3, &read_val3);
                        DCRLblE3[i]->Lble->Text = (int)read_val1*DCRLblE3[i]->Addr.Divide1()
                        +(int)read_val2*DCRLblE3[i]->Addr.Divide2()+(int)read_val3;
                }
        }
        //----------------------------------20100204
        //DCRLblE2
        for(int i = 0; i < ODCR->DCRLblE2_Nbr; i++){
                if(DCRLblE2[i]->Lble->Visible==true){
                        EngineerForm->SetRead_Byte(DCRLblE2[i]->Addr.Byte1, &read_val1);
                        EngineerForm->SetRead_Byte(DCRLblE2[i]->Addr.Byte2, &read_val2);
                        DCRLblE2[i]->Lble->Text = (int)read_val1*DCRLblE2[i]->Addr.Divide()
                        +(int)read_val2;
                }
        }
        //ALSScrollBar_Nbr = 17;
        for(int i = 0; i < ODCR->ALSScrollBar_Nbr; i++){
                if(ALSScrlB[i]->ScrlB->Visible==true){
                        EngineerForm->SetRead_Byte(ALSScrlB[i]->Addr, &read_val);
                        ALSScrlB[i]->ScrlB->Position = read_val;
                        ALSScrlB[i]->StTxt->Caption = read_val;
                }
        }

        //ALSChkBox_Nbr = 3;
        for(int i = 0; i < ODCR->ALSChkBox_Nbr; i++){
                if(ALSChkB[i]->Chkb->Visible==true){
                        EngineerForm->SetRead_Byte(ALSChkB[i]->Addr, &read_val);
                        if(read_val==1)
                                ALSChkB[i]->Chkb->Checked = 1;
                        else if(read_val==0)
                                ALSChkB[i]->Chkb->Checked = 0;
                        else
                                ShowMessage("ALS CheckBox read error:"+IntToStr(read_val));
                }
        }
        //ALSCboBox_Nbr = 1;
        for(int i = 0; i < ODCR->ALSCboBox_Nbr; i++){
                if(ALSCboB[i]->Cbob->Visible==true){
                        EngineerForm->SetRead_Byte(ALSCboB[i]->Addr, &read_val);
                        ALSCboB[i]->Cbob->ItemIndex = read_val;
                }
        }

        //HDRCboBox_Nbr = 6;
        for(int i = 0; i < ODCR->HDRCboBox_Nbr; i++){
                if(HDRCboB[i]->Cbob->Visible==true){
                        EngineerForm->SetRead_Byte(HDRCboB[i]->Addr, &read_val);
                        HDRCboB[i]->Cbob->ItemIndex = read_val;
                }
        }
        //HDRScrollBar_Nbr = 0;

        for(int i = 0; i < ODCR->HDRScrollBar_Nbr; i++){
                if(HDRScrlB[i]->ScrlB->Visible==true){
                        EngineerForm->SetRead_Byte(HDRScrlB[i]->Addr, &read_val);
                        HDRScrlB[i]->ScrlB->Position = read_val;
                        HDRScrlB[i]->StTxt->Caption = read_val;
                }
        }

        //HDRScrollBar2_Nbr = 17;

        for(int i = 0; i < ODCR->HDRScrollBar2_Nbr; i++){
                if(HDRScrlB2[i]->ScrlB->Visible==true){
                        EngineerForm->SetRead_Byte(HDRScrlB2[i]->Addr.Byte1, &read_val1);
                        EngineerForm->SetRead_Byte(HDRScrlB2[i]->Addr.Byte2, &read_val2);
                        HDRScrlB2[i]->ScrlB->Position = (int)read_val1*HDRScrlB2[i]->Addr.Divide()+read_val2;
                        HDRScrlB2[i]->StTxt->Caption = (int)read_val1*HDRScrlB2[i]->Addr.Divide()+read_val2;
                }
        }

        //HDRLblE2_Nbr= 5;
        for(int i = 0; i < ODCR->HDRLblE2_Nbr; i++){
                if(HDRLblE2[i]->Lble->Visible==true){
                        EngineerForm->SetRead_Byte(HDRLblE2[i]->Addr.Byte1, &read_val1);
                        EngineerForm->SetRead_Byte(HDRLblE2[i]->Addr.Byte2, &read_val2);
                        HDRLblE2[i]->Lble->Text = (int)read_val1*HDRLblE2[i]->Addr.Divide()
                        +(int)read_val2;
                }
        }


        DCR_Chg = 1;
        btn_dcr_lut_readClick(Sender);
        Btn_DCR_reload->Enabled = true;
}
//---------------------------------------------------------------------------

// 20100608 table operation button enable/ disable
void TDCRForm1::DCR_LUT_FuncEnable(bool flag_en)
{
        if(flag_en==true){ // Table operation button enable
                btn_dcr_lut_read->Enabled = true;
                btn_dcr_lut_write->Enabled = true;
                btn_dcr_lut_save->Enabled = true;
                btn_dcr_lut_load->Enabled = true;
        }else {            // Table operation button disable
                btn_dcr_lut_read->Enabled = false;
                btn_dcr_lut_write->Enabled = false;
                btn_dcr_lut_save->Enabled = false;
                btn_dcr_lut_load->Enabled = false;
        }
}
//---------------------------------------------------------------------------
// 20100608 Record the state of DCR enable
bool TDCRForm1::DCR_LUT_RW_start()
{
        if(DCREN_idx[0]==-1 || DCREN_idx[1]==-1){
                ShowMessage("Unknown DCR enabled index.");
                return 0;
        }
        unsigned char set_val;
        bool r_ok[2]={0};
        for(int i=0; i<2; i++){
                r_ok[i] = EngineerForm->SetRead_Byte(DCRChkB[DCREN_idx[i]]->Addr ,&set_val);
                if(r_ok[i]==0){
                        ShowMessage("read enable fail.");
                        return 0;
                }
                DCR_EN_State[i] = (set_val>0?1:0);
                DCRChkB[DCREN_idx[i]]->Chkb->Checked = false;
                EngineerForm->SetWrite_Byte(DCRChkB[DCREN_idx[i]]->Addr ,0);
        }
        return 1;
}
//---------------------------------------------------------------------------
// 20100608 Recover the state of DCR enable
void TDCRForm1::DCR_LUT_RW_over(){
        // Recover enable state
        for(int i=0; i<2; i++){
                int set_val = (DCR_EN_State[i] == false?0:1);
                EngineerForm->SetWrite_Byte(DCRChkB[DCREN_idx[i]]->Addr ,set_val);
                DCRChkB[DCREN_idx[i]]->Chkb->Checked = DCR_EN_State[i];
        }
}
//---------------------------------------------------------------------------
void __fastcall TDCRForm1::btn_dcr_lut_readClick(TObject *Sender)
{
        DCR_LUT_FuncEnable(0);          // Table operation button disable
        bool ok = DCR_LUT_RW_start();   // Record the state of DCR enable
        if(ok==0){                      // Fail to record the state
                DCR_LUT_FuncEnable(1);  // Table operation button enable
                return;
        }
#if 1
/////////////////////// DCR 3個table 算一組chksum ////////////////
        int** dcr_lut = new int* [ODCR->DCRLUT_Nbr];
        for( int i = 0; i < ODCR->DCRLUT_Nbr; i++){
                dcr_lut[i] = new int [Addr_DCRLUT[i].LutNum()];
        }

        ok = EngineerForm->SetRead_DG(Addr_DCRLUT, dcr_lut, ODCR->DCRLUT_Nbr, DCR_IsChkSum);
        if(!ok)
                ShowMessage ("DCR Table Read Fail!");

        int chk_len;
        if(DCR_IsChkSum)
                chk_len = 2;
        else if(!DCR_IsChkSum)
                chk_len = 0;

        int idx = chk_len;
        for( int i = 0; i < ODCR->DCRLUT_Nbr; i++){
                for(int j=0; j<Addr_DCRLUT[i].LutNum(); j++){    // Set to interface
                        sg_dcr[i]->Cells[1][j+1] = dcr_lut[i][j];
                }
                delete [] dcr_lut[i];
        }
        delete [] dcr_lut;
#endif
        ///////////////////////// DCR 3 個table 各自讀取 ////////////////////
#if 0
        for(int i = 0; i < ODCR->DCRLUT_Nbr; i++){      // Read 2 or 3 set of table
                int* dcr_lut = new int [Addr_DCRLUT[i].LutNum()];
                EngineerForm->SetRead_PG(Addr_DCRLUT[i], dcr_lut, 0);
                for(int j=0; j<Addr_DCRLUT[i].LutNum(); j++){    // Set to interface
                        sg_dcr[i]->Cells[1][j+1] = dcr_lut[j];
                }
                delete [] dcr_lut;
        }
#endif
        DCR_LUT_RW_over();      // Recover DCR enable
        DCR_LUT_FuncEnable(1);  // Table operation button enable
}
//---------------------------------------------------------------------------

void __fastcall TDCRForm1::btn_dcr_lut_writeClick(TObject *Sender)
{
        DCR_LUT_FuncEnable(0);           // Table operation button disable
        bool ok = DCR_LUT_RW_start();    // Record the state of DCR enable
        if(ok==0){                       // Fail to record the state
                DCR_LUT_FuncEnable(1);   // Table operation button enable
                return;
        }
#if 1
        ///////// DCR 3個table 算一組chksum ////////////////

        int** dcr_lut = new int* [ODCR->DCRLUT_Nbr];
        for(int i = 0; i < ODCR->DCRLUT_Nbr; i++){   // Write or 3 set of table
                dcr_lut[i] = new int [Addr_DCRLUT[i].LutNum()];
                for(int j=0; j<Addr_DCRLUT[i].LutNum(); j++){  // Get value from interface
                        dcr_lut[i][j] = StrToInt(sg_dcr[i]->Cells[1][j+1]);
                }
        }
        bool MSB_first = 0;
        ok = EngineerForm->SetWrite_DG(Addr_DCRLUT, dcr_lut, ODCR->DCRLUT_Nbr,  DCR_IsChkSum, 0);
        if(!ok)
                ShowMessage ("DCR Table Write Fail!");

        for(int i = 0; i < ODCR->DCRLUT_Nbr; i++)
                delete [] dcr_lut[i];
        delete [] dcr_lut;
#endif

#if 0
     ///////////////////////// DCR 3 個table 各自寫入 ////////////////////
        for(int i = 0; i < ODCR->DCRLUT_Nbr; i++){   // Write or 3 set of table
                int* dcr_lut = new int [Addr_DCRLUT[i].LutNum()];
                for(int j=0; j<Addr_DCRLUT[i].LutNum(); j++){  // Get value from interface
                        dcr_lut[j] = StrToInt(sg_dcr[i]->Cells[1][j+1]);
                }
                EngineerForm->SetWrite_PG(Addr_DCRLUT[i], dcr_lut, DCR_IsChkSum);
                Sleep(10);
                delete [] dcr_lut;
        }
#endif
        DCR_LUT_RW_over();          // Recover DCR enable
        DCR_LUT_FuncEnable(1);      // Table operation button enable
}
//---------------------------------------------------------------------------

void __fastcall TDCRForm1::btn_dcr_lut_loadClick(TObject *Sender)
{
        String Fpath;
        if (!OpenDialog1->Execute())
                return;
		
        Fpath = OpenDialog1->FileName;
        String *dcr_LUT = NULL;
        int data_num=0;
        for(int i = 0; i < ODCR->DCRLUT_Nbr; i++){
                data_num+=Addr_DCRLUT[i].LutNum();
        }
        dcr_LUT = EngineerForm->Load_file(Fpath, data_num);
        if(dcr_LUT==NULL){
                ShowMessage("Load file fail!");
                return;
        }
        DCR_LUT_FuncEnable(0);
        int idx=0;
        for(int i = 0; i < ODCR->DCRLUT_Nbr; i++){
                for(int j=0; j<Addr_DCRLUT[i].LutNum(); j++){
                        sg_dcr[i]->Cells[1][j+1] = StrToInt(dcr_LUT[idx]);
                        idx++;
                }
        }
        DCR_LUT_FuncEnable(1);
        delete [] dcr_LUT;
}
//---------------------------------------------------------------------------

void __fastcall TDCRForm1::btn_dcr_lut_saveClick(TObject *Sender)
{
        if(!SaveDialog1->Execute()){
                btn_dcr_lut_save->Enabled=true;
                return;
        }
        DCR_LUT_FuncEnable(0);

        String Fpath = SaveDialog1->FileName;
        FILE* fptr = fopen (Fpath.c_str(),"w");
        int data;
        for(int i = 0; i < ODCR->DCRLUT_Nbr; i++){
                for(int j=0; j<Addr_DCRLUT[i].LutNum(); j++){
                        data = sg_dcr[i]->Cells[1][j+1].ToIntDef(-1);
                        fprintf(fptr,"%04d\n",data);
                }
        }
        fclose(fptr);
        DCR_LUT_FuncEnable(1);
}
//---------------------------------------------------------------------------

void __fastcall TDCRForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 0x40)
                Btn_DCR_reloadClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TDCRForm1::DCR_LblEdit2_KeyPress(TObject *Sender, char &Key)
{
        TLabeledEdit *c = (TLabeledEdit *)Sender;
        int idx = StrToInt(c->Hint);

        if(Key!=13){
                DCRLblE2[idx]->Lble->Font->Color = cl3DDkShadow;
                return;
        }
        if(DCR_Chg==0)
                return;
        String tmp_v = DCRLblE2[idx]->Lble->Text;
        if(tmp_v==""){                                                                                        
                tmp_v = "0";
        }
        int set_val = StrToInt(tmp_v);                                                                        
        unsigned char val1,val2;                                                                              
        //add Max hint
        if(set_val>=pow(2,DCRLblE2[idx]->Addr.BitNum())){
                AnsiString max = "Max value:"+IntToStr((int)pow(2,DCRLblE2[idx]->Addr.BitNum())-1);
                ShowMessage(max);
                //read value                                                                                  
                EngineerForm->SetRead_Byte(DCRLblE2[idx]->Addr.Byte1, &val1);
                EngineerForm->SetRead_Byte(DCRLblE2[idx]->Addr.Byte2, &val2);
                DCRLblE2[idx]->Lble->Text = (int)val1*DCRLblE2[idx]->Addr.Divide()+val2;
                DCRLblE2[idx]->Lble->Font->Color = clWindowText;
        }else{
                val1 = set_val/DCRLblE2[idx]->Addr.Divide();
                val2 = set_val%DCRLblE2[idx]->Addr.Divide();
                EngineerForm->SetWrite_Byte(DCRLblE2[idx]->Addr.Byte1 ,val1);
                if(DCRLblE2[idx]->Addr.Byte2.BitNum()!=0)
                        EngineerForm->SetWrite_Byte(DCRLblE2[idx]->Addr.Byte2 ,val2);
                DCRLblE2[idx]->Lble->Font->Color = clWindowText;
        }
}
//----------------------------------------------------------------------------
void __fastcall TDCRForm1::HDR_LblEdit2_KeyPress(TObject *Sender, char &Key)
{
        TLabeledEdit *c = (TLabeledEdit *)Sender;
        int idx = StrToInt(c->Hint);

        if(Key!=13){
                HDRLblE2[idx]->Lble->Font->Color = cl3DDkShadow;
                return;
        }
        if(DCR_Chg==0)
                return;
        String tmp_v = HDRLblE2[idx]->Lble->Text;
        if(tmp_v==""){                                                                                        
                tmp_v = "0";
        }
        int set_val = StrToInt(tmp_v);                                                                        
        unsigned char val1,val2;                                                                              
        //add Max hint
        if(set_val>=pow(2,HDRLblE2[idx]->Addr.BitNum())){
                AnsiString max = "Max value:"+IntToStr((int)pow(2,HDRLblE2[idx]->Addr.BitNum())-1);
                ShowMessage(max);
                //read value                                                                                  
                EngineerForm->SetRead_Byte(HDRLblE2[idx]->Addr.Byte1, &val1);
                EngineerForm->SetRead_Byte(HDRLblE2[idx]->Addr.Byte2, &val2);
                HDRLblE2[idx]->Lble->Text = (int)val1*HDRLblE2[idx]->Addr.Divide()+val2;
                HDRLblE2[idx]->Lble->Font->Color = clWindowText;
        }else{
                val1 = set_val/HDRLblE2[idx]->Addr.Divide();
                val2 = set_val%HDRLblE2[idx]->Addr.Divide();
                EngineerForm->SetWrite_Byte(HDRLblE2[idx]->Addr.Byte1 ,val1);
                if(HDRLblE2[idx]->Addr.Byte2.BitNum()!=0)
                        EngineerForm->SetWrite_Byte(HDRLblE2[idx]->Addr.Byte2 ,val2);
                HDRLblE2[idx]->Lble->Font->Color = clWindowText;
        }
}












