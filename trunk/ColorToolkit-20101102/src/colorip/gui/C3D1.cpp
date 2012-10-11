//---------------------------------------------------------------------------

#include <vcl.h>
#include <lib/CMSCpp2.1/src/includeall.h>
#pragma hdrstop

#include "C3D1.h"
#include <colorip/11307/ImageProcess/ImgProc_11307.h>
#include "include.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//TC3DForm1 *C3DForm1;
int **c3d_r, **c3d_g, **c3d_b;
bool C3D_IsChkSum = 1;
int TBL_SIZE;
//double Ratio;
int tbl_s;
int tbl_val[4][33] = {{0,32,64,96,128,160,192,224,255},  //9x9x9 uniform table, first index is 0
        {0,32,64,128,192,224,255,0,0},                           //7x7x7 table, first index is 1
        {0,16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,255},       //17x17x17 table, first index is 2
        {0,8,16,24,32,40,48,56,64,72,80,88,96,104,112,120,128,136,144,       //33x33x33 table, first index is 3
        152,160,168,176,184,192,200,208,216,224,232,240,248,255}};
//---------------------------------------------------------------------------


__fastcall TC3DForm1::TC3DForm1(TComponent* Owner)
        : TForm(Owner)
{
        C3D_Chg = 0;
        C3DEN_idx = -1;
}

void __fastcall TC3DForm1::CheckBox_Click(TObject *Sender)
{
        if(C3D_Chg==0)
                return;
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (ChkB[idx]->Chkb->Checked?1:0);
        EngineerForm->SetWrite_Byte(ChkB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall TC3DForm1::FormCreate(TObject *Sender)
{
        C3D_Chg = 0;
        int ic_choice=0;
        /*if(MainForm->TCON_DEV=="11307")
                ic_choice = 0;*/

        switch(ic_choice)
        {
                case 0:
                        if(MainForm->C3D_type==7)
                        {
                                OC3D = new C3D_11307_777;
                                Hint = 7;
                        }
                        else if(MainForm->C3D_type==9)
                        {
                                OC3D = new C3D_11307_999;
                                Hint = 9;
                        }
                break;
        }

        Addr_LUT = OC3D->SetLUT();
        if(Addr_LUT[0].LutNum()==729)
                TBL_SIZE = 9;
        else if(Addr_LUT[0].LutNum()==343){
                TBL_SIZE = 7;
        }
        cb = OC3D->SetChkBx();
        ChkB = new _CHKB* [OC3D->C3DChkBox_Nbr];
        for(int i = 0; i <OC3D->C3DChkBox_Nbr; i++)
                ChkB[i] = new _CHKB;

        ChkB[0]->Chkb = CheckBox1;
        ChkB[1]->Chkb = CheckBox2;
        ChkB[2]->Chkb = CheckBox3;

        for(int i = 0; i < OC3D->C3DChkBox_Nbr; i++){
                ChkB[i]->Addr = cb[i];
                ChkB[i]->Chkb->Visible = ChkB[i]->Addr.FuncEn();
                ChkB[i]->Chkb->OnClick = CheckBox_Click;
                ChkB[i]->Chkb->Hint = i;
                ChkB[i]->Chkb->Caption = ChkB[i]->Addr.Name();
                if(ChkB[i]->Addr.Name() == OC3D->C3D_EN_Name()) // 20100608 find C3D enable index
                        C3DEN_idx = i;
        }
        if(C3DEN_idx==-1)             // 2010608 Check C3D enable index
                ShowMessage("Can't Get C3D enable index.");
        Initial_C3D_table();    // 2010608 Initial C3D table
        C3D_Chg = 1;
}
//---------------------------------------------------------------------------
void __fastcall TC3DForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        delete [] OC3D;
        delete [] ChkB;
        delete [] Addr_LUT;

        Action = caFree;
        MainForm->C3DFormNULL();
}
//---------------------------------------------------------------------------
void TC3DForm1::Initial_C3D_table()
{
        //initial table setting
        if(TBL_SIZE == 9)
                tbl_s = 0;
        else if(TBL_SIZE == 7)
                tbl_s = 1;
        else if(TBL_SIZE == 17)
                tbl_s = 2;
        else if(TBL_SIZE == 33)
                tbl_s = 3;

        int total_len = TBL_SIZE*TBL_SIZE*TBL_SIZE;
        //排列lookup table 成儲存格式時使用的陣列
        c3d_r = new int* [2];
        c3d_g = new int* [2];
        c3d_b = new int* [2];
        for(int i=0; i < 2; i++){
                c3d_r[i] = new int [total_len];
                c3d_g[i] = new int [total_len];
                c3d_b[i] = new int [total_len];
        }

        c3d_lutArrange();

        sg_C3D_table->RowCount = Addr_LUT[0].LutNum()+1;
        for(int i = 1; i <= Addr_LUT[0].LutNum(); i++){
                sg_C3D_table->Cells[0][i] = i-1;
                sg_C3D_table->Cells[1][i] = c3d_r[0][i-1];
                sg_C3D_table->Cells[2][i] = c3d_g[0][i-1];
                sg_C3D_table->Cells[3][i] = c3d_b[0][i-1];
        }
        sg_C3D_table->Cells[1][0]="Rin";
        sg_C3D_table->Cells[2][0]="Gin";
        sg_C3D_table->Cells[3][0]="Bin";
        sg_C3D_table->Cells[4][0]="Rout";         
        sg_C3D_table->Cells[5][0]="Gout";
        sg_C3D_table->Cells[6][0]="Bout";                                 

        if(OC3D->C3DLUT_Nbr==4){
                sg_C3D_table->ColCount = 8;
                sg_C3D_table->RowCount = Addr_LUT[0].LutNum()+1;
                sg_C3D_table->Width = 365;
                sg_C3D_table->Cells[7][0]="Wout";
        }else if(OC3D->C3DLUT_Nbr==3){   // Default 數值
                int ratio = pow(2,Addr_LUT[0].BitNum()-8);
                for(int i = 1; i <= Addr_LUT[0].LutNum(); i++){
                        sg_C3D_table->Cells[4][i] = c3d_r[0][i-1]*ratio;
                        sg_C3D_table->Cells[5][i] = c3d_g[0][i-1]*ratio;
                        sg_C3D_table->Cells[6][i] = c3d_b[0][i-1]*ratio;
                }
        }
}
 bool TC3DForm1::c3d_lutArrange()
{
        int idx = 0;

        // 1
        for(int k = 0; k < TBL_SIZE; k+=2)
                for(int j = 0; j < TBL_SIZE; j+=2)
                        for(int i = 0; i < TBL_SIZE; i+=2){
                                c3d_r[0][idx] = tbl_val[tbl_s][i];
                                c3d_g[0][idx] = tbl_val[tbl_s][j];
                                c3d_b[0][idx] = tbl_val[tbl_s][k];
                                idx++;
                        }

        //2
        if(TBL_SIZE==7){
                for(int k = 0; k <TBL_SIZE; k+=2)
                        for(int i = 1; i <TBL_SIZE-1; i+=2)
                                for(int j = 0; j <TBL_SIZE; j+=2){
                                        c3d_r[0][idx] = tbl_val[tbl_s][i];
                                        c3d_g[0][idx] = tbl_val[tbl_s][j];
                                        c3d_b[0][idx] = tbl_val[tbl_s][k];
                                        idx++;
                                }
        }else if(TBL_SIZE==9 || TBL_SIZE==17 ){
                for(int k = 0; k <TBL_SIZE; k+=2)
                        for(int j = 0; j <TBL_SIZE; j+=2)
                                for(int i = 1; i <TBL_SIZE-1; i+=2){
                                        c3d_r[0][idx] = tbl_val[tbl_s][i];
                                        c3d_g[0][idx] = tbl_val[tbl_s][j];
                                        c3d_b[0][idx] = tbl_val[tbl_s][k];
                                        idx++;
                                }
        }

        //3
        for(int k = 0; k <TBL_SIZE; k+=2)
                for(int j = 1; j <TBL_SIZE-1; j+=2)
                         for(int i = 0; i <TBL_SIZE; i+=2){
                                c3d_r[0][idx] = tbl_val[tbl_s][i];
                                c3d_g[0][idx] = tbl_val[tbl_s][j];
                                c3d_b[0][idx] = tbl_val[tbl_s][k];
                                idx++;
                         }
         //4
        for(int k = 0; k <TBL_SIZE; k+=2)
                for(int j = 1; j <TBL_SIZE-1; j+=2)
                        for(int i = 1; i <TBL_SIZE-1; i+=2){
                                c3d_r[0][idx] = tbl_val[tbl_s][i];
                                c3d_g[0][idx] = tbl_val[tbl_s][j];
                                c3d_b[0][idx] = tbl_val[tbl_s][k];
                                idx++;
                        }
        //5
        for(int k = 1; k <TBL_SIZE-1; k+=2)
                for(int j = 0; j <TBL_SIZE; j+=2)
                        for(int i = 0; i <TBL_SIZE; i+=2){
                                c3d_r[0][idx] = tbl_val[tbl_s][i];
                                c3d_g[0][idx] = tbl_val[tbl_s][j];
                                c3d_b[0][idx] = tbl_val[tbl_s][k];
                                idx++;
                        }
        //6
        if(TBL_SIZE==7){
                for(int k = 1; k <TBL_SIZE-1; k+=2)
                        for(int i = 1; i <TBL_SIZE-1; i+=2)
                                for(int j = 0; j <TBL_SIZE; j+=2){
                                        c3d_r[0][idx] = tbl_val[tbl_s][i];
                                        c3d_g[0][idx] = tbl_val[tbl_s][j];
                                        c3d_b[0][idx] = tbl_val[tbl_s][k];
                                        idx++;
                                }
        }else if(TBL_SIZE==9 || TBL_SIZE==17 ){
                for(int k = 1; k <TBL_SIZE-1; k+=2)
                        for(int j = 0; j <TBL_SIZE; j+=2)
                                for(int i = 1; i <TBL_SIZE-1; i+=2){
                                        c3d_r[0][idx] = tbl_val[tbl_s][i];
                                        c3d_g[0][idx] = tbl_val[tbl_s][j];
                                        c3d_b[0][idx] = tbl_val[tbl_s][k];
                                        idx++;
                                }
        }

        //7
        for(int k = 1; k <TBL_SIZE-1; k+=2)
                for(int j = 1; j <TBL_SIZE-1; j+=2)
                         for(int i = 0; i <TBL_SIZE; i+=2){
                                c3d_r[0][idx] = tbl_val[tbl_s][i];
                                c3d_g[0][idx] = tbl_val[tbl_s][j];
                                c3d_b[0][idx] = tbl_val[tbl_s][k];
                                idx++;
                         }
        //8
        for(int k = 1; k <TBL_SIZE-1; k+=2)
                for(int j = 1; j <TBL_SIZE-1; j+=2)
                        for(int i = 1; i <TBL_SIZE-0; i+=2){
                                c3d_r[0][idx] = tbl_val[tbl_s][i];
                                c3d_g[0][idx] = tbl_val[tbl_s][j];
                                c3d_b[0][idx] = tbl_val[tbl_s][k];
                                idx++;
                        }
        return 1;
}
void __fastcall TC3DForm1::btn_C3D_readClick(TObject *Sender)
{
        C3D_LUT_FuncEnable(0);           // Table operation button disable
        bool ok = C3D_LUT_RW_start();    // Record the state of C3D enable
        if(ok==0){                       // Fail to record the state
                C3D_LUT_FuncEnable(1);   // Table operation button enable
                return;
        }

        if(TBL_SIZE==7){   // 7x7x7 位置多一個空白數值的做法
                int **C3D_table = new int* [OC3D->C3DLUT_Nbr];
                // 新的look up table Address 定義
                TLUT* Addr_LUT_7 = new TLUT [3];
                for(int i = 0; i < OC3D->C3DLUT_Nbr; i++){
                        Addr_LUT_7[i].set(Addr_LUT[i].Addr(), Addr_LUT[i].LutNum()+1,
                        Addr_LUT[i].BitNum(), Addr_LUT[i].Type(), Addr_LUT[i].Name());
                }
                int read_len = Addr_LUT_7[0].LutNum();
                for(int i = 0; i < OC3D->C3DLUT_Nbr; i++){
                        C3D_table[i] = new int [read_len];
                }
                // 使用DG的方式分RGB或是RGBW寫入
                EngineerForm->SetRead_DG(Addr_LUT_7, C3D_table, OC3D->C3DLUT_Nbr, C3D_IsChkSum);
                for(int i = 0; i < OC3D->C3DLUT_Nbr; i++){
                        for(int j = 0; j < Addr_LUT_7[i].LutNum()-1; j++){     //To GUI
                                sg_C3D_table->Cells[3+i+1][j+1] = IntToStr(C3D_table[i][j]);
                        }
                }
                for(int i = 0; i < OC3D->C3DLUT_Nbr; i++){
                        delete [] C3D_table[i];
                }
                delete [] C3D_table;
                delete [] Addr_LUT_7;
        }
        else
        {
                int **C3D_table = new int* [OC3D->C3DLUT_Nbr];
                int read_len = Addr_LUT[0].Addr();
                for(int i = 0; i < OC3D->C3DLUT_Nbr; i++){
                        C3D_table[i] = new int [read_len];
                }

                // 使用DG的方式分RGB或是RGBW寫入
                EngineerForm->SetRead_DG(Addr_LUT, C3D_table, OC3D->C3DLUT_Nbr, C3D_IsChkSum);

                for(int i = 0; i < OC3D->C3DLUT_Nbr; i++){
                        for(int j = 0; j < Addr_LUT[i].LutNum(); j++){     //To GUI
                                sg_C3D_table->Cells[3+i+1][j+1] = IntToStr(C3D_table[i][j]);
                        }
                }
                for(int i = 0; i < OC3D->C3DLUT_Nbr; i++){
                        delete [] C3D_table[i];
                }
                delete [] C3D_table;
        }
        C3D_LUT_RW_over();          // Recover the state of C3D enable
        C3D_LUT_FuncEnable(1);      // Table operation button enable
}
//---------------------------------------------------------------------------
void __fastcall TC3DForm1::btn_C3D_wrtClick(TObject *Sender)
{
        C3D_LUT_FuncEnable(0);           // Table operation button disable
        bool ok = C3D_LUT_RW_start();    // Record the state of C3D enable
        if(ok==0){                       // Fail to record the state
                C3D_LUT_FuncEnable(1);   // Table operation button enable
                return;
        }

        if(TBL_SIZE==7){   // 7x7x7 位置多一個空白數值的做法
                int** lut = new int* [OC3D->C3DLUT_Nbr];
                // 新的look up table Address 定義
                TLUT* Addr_LUT_7 = new TLUT [3];
                for(int i = 0; i < OC3D->C3DLUT_Nbr; i++){
                        Addr_LUT_7[i].set(Addr_LUT[i].Addr(), Addr_LUT[i].LutNum()+1,
                         Addr_LUT[i].BitNum(), Addr_LUT[i].Type(), Addr_LUT[i].Name());
                }
                for(int i = 0; i < OC3D->C3DLUT_Nbr; i++){
                        lut[i] = new int [Addr_LUT_7[i].LutNum()];
                       for(int j = 0; j < Addr_LUT_7[i].LutNum()-1; j++){
                               lut[i][j] = StrToInt(sg_C3D_table->Cells[3+i+1][j+1]);
                       }
                       lut[i][Addr_LUT_7[i].LutNum()-1]=0;
                }
                EngineerForm->SetWrite_DG(Addr_LUT_7, lut, OC3D->C3DLUT_Nbr, C3D_IsChkSum);
                for(int i = 0; i < OC3D->C3DLUT_Nbr; i++)
                        delete [] lut[i];
                        delete [] lut;
                        delete [] Addr_LUT_7;
                }
        else   
        {
                int** lut = new int* [OC3D->C3DLUT_Nbr];
                for(int i = 0; i < OC3D->C3DLUT_Nbr; i++){
                       lut[i] = new int [Addr_LUT[i].LutNum()];
                       for(int j = 0; j < Addr_LUT[i].LutNum(); j++){
                               lut[i][j] = StrToInt(sg_C3D_table->Cells[3+i+1][j+1]);
                       }
                }
                EngineerForm->SetWrite_DG(Addr_LUT, lut, OC3D->C3DLUT_Nbr, C3D_IsChkSum);
                for(int i = 0; i < OC3D->C3DLUT_Nbr; i++)
                        delete [] lut[i];
                delete [] lut;
        }
        C3D_LUT_RW_over();          // Recover the state of C3D enable
        C3D_LUT_FuncEnable(1);      // Table operation button enable
}
//---------------------------------------------------------------------------
// Record the state of C3D enable
bool TC3DForm1::C3D_LUT_RW_start()
{
        if(C3DEN_idx==-1){
                ShowMessage("Unknown C3D enabled index.");
                return 0;
        }
        unsigned char set_val;
        bool ok = EngineerForm->SetRead_Byte(ChkB[C3DEN_idx]->Addr ,&set_val);
        if(ok==0){
                ShowMessage("read enable fail.");
                return 0;
        }
        C3D_EN_State = (set_val>0?1:0);
        ChkB[C3DEN_idx]->Chkb->Checked = false;
        EngineerForm->SetWrite_Byte(ChkB[C3DEN_idx]->Addr ,0);
        return 1;
}
// Recover the state of C3D enable
void TC3DForm1::C3D_LUT_RW_over(){
        // reload en state
        int set_val = (C3D_EN_State == false?0:1);
        ChkB[C3DEN_idx]->Chkb->Checked = C3D_EN_State;
        EngineerForm->SetWrite_Byte(ChkB[C3DEN_idx]->Addr ,set_val);
}
void TC3DForm1::C3D_LUT_FuncEnable(bool en_flag)
{
        if(en_flag == true){  // Table operation button enable
                btn_C3D_wrt->Enabled = true;
                btn_C3D_read->Enabled = true;
                btn_C3D_save->Enabled = true;
                btn_C3D_load->Enabled = true;
        }else {               // Table operation button disable
                btn_C3D_wrt->Enabled = false;
                btn_C3D_read->Enabled = false;
                btn_C3D_save->Enabled = false;
                btn_C3D_load->Enabled = false;
        }
}

//---------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_C3D_saveClick(TObject *Sender)
{
        C3D_LUT_FuncEnable(0);
        if(!SaveDialog1->Execute()){
                C3D_LUT_FuncEnable(1);
                return;
        }
        String Fpath = SaveDialog1->FileName/*+".txt"*/;
        FILE* fptr = fopen (Fpath.c_str(),"w");
        //fprintf(fptr,"R\tG\tB\n");

         for(int i = 1; i <= Addr_LUT[0].LutNum(); i++){
                for(int j = 1; j <= OC3D->C3DLUT_Nbr; j++){
                        fprintf(fptr,"%d\t", StrToInt(sg_C3D_table->Cells[3+j][i]));
                }
                fprintf(fptr,"\n");
         }

        fclose(fptr);
        C3D_LUT_FuncEnable(1);
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_C3D_loadClick(TObject *Sender)
{
        C3D_LUT_FuncEnable(0);
        String Fpath;
        if (OpenDialog1->Execute()){
               Fpath = OpenDialog1->FileName;
               String *LUT = NULL;
               LUT = EngineerForm->Load_file(Fpath, Addr_LUT[0].LutNum()*OC3D->C3DLUT_Nbr);
               if(LUT==NULL){
                        ShowMessage("Load file fail!");
                        C3D_LUT_FuncEnable(1);
                        return;
               }

               for(int c=0; c< OC3D->C3DLUT_Nbr; c++){
                        for(int r = 0; r<Addr_LUT[0].LutNum(); r++){
                                sg_C3D_table->Cells[c+1+3][r+1] = StrToInt(LUT[r*OC3D->C3DLUT_Nbr+c]);
                        }
               }
               delete [] LUT;
        }
        
        C3D_LUT_FuncEnable(1);
}
//---------------------------------------------------------------------------


void __fastcall TC3DForm1::OnKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 0x40)
                Btn_C3D_reloadClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::Btn_C3D_reloadClick(TObject *Sender)
{
        Btn_C3D_reload->Enabled = false;
        C3D_Chg = 0;
        unsigned char read_val;
        for(int i = 0; i < OC3D->C3DChkBox_Nbr; i++){
                if(ChkB[i]->Chkb->Visible==true){
                        EngineerForm->SetRead_Byte(ChkB[i]->Addr, &read_val);
                        if(read_val==1)
                                ChkB[i]->Chkb->Checked = 1;
                        else if(read_val==0)
                                ChkB[i]->Chkb->Checked = 0;
                        else
                                ShowMessage("CM CheckBox read error:"+IntToStr(read_val));
                }
        }

        btn_C3D_readClick(Sender);
        C3D_Chg = 1;
        Btn_C3D_reload->Enabled = true;
}
//---------------------------------------------------------------------------

