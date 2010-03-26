//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "HueSatVal.h"
#include "ImgProc_12401.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//THSVForm1 *HSVForm1;
//---------------------------------------------------------------------------
__fastcall THSVForm1::THSVForm1(TComponent* Owner)
        : TForm(Owner)
{
        HSV_Chg = 0;
}

//---------------------------------------------------------------------------
void __fastcall THSVForm1::CheckBox_Click(TObject *Sender)
{
        if(HSV_Chg==0)
                return;
        TCheckBox *c = (TCheckBox *)Sender;
        int idx = StrToInt(c->Hint);
        int set_val = (ChkB[idx]->Chkb->Checked?1:0);
        EngineerForm->SetWrite_Byte(ChkB[idx]->Addr ,set_val);
}
//---------------------------------------------------------------------------
void __fastcall THSVForm1::cb_enClick(TObject *Sender)
{
        int set_val = (cb_en->Checked?1:0);
        EngineerForm->SetWrite_Byte(en.Addr ,set_val);
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::FormCreate(TObject *Sender)
{
        HSV_Chg = 0;
        int ic_choice;
        if(MainForm->TCON_DEV=="12401")
                ic_choice = 0;

        switch(ic_choice)
        {
                case 0:
                OHSV = new HSV_12401;
                break;
        }

        en.Addr = OHSV->SetEn();
        cb_en->Visible = en.Addr.FuncEn();
        cb_en->Caption = en.Addr.Name();

        lut_addr = OHSV->SetLUT();

        cb = OHSV->SetChkBx();
        ChkB = new _CHKB* [OHSV->HSVChkBox_Nbr];
        for(int i = 0; i <OHSV->HSVChkBox_Nbr; i++)
                ChkB[i] = new _CHKB;

        ChkB[0]->Chkb = CheckBox1;

        for(int i = 0; i < OHSV->HSVChkBox_Nbr; i++){
                ChkB[i]->Addr = cb[i];
                ChkB[i]->Chkb->Visible = ChkB[i]->Addr.FuncEn();
                ChkB[i]->Chkb->OnClick = CheckBox_Click;
                ChkB[i]->Chkb->Hint = i;
                ChkB[i]->Chkb->Caption = ChkB[i]->Addr.Name();
        }

        Initial_HSV_table();
        HSV_Chg = 1;
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::FormClose(TObject *Sender, TCloseAction &Action)
{
        delete [] OHSV;
        delete [] cb;
        delete [] ChkB;
        delete [] lut_addr;

        Action = caFree;
        MainForm->HSVFormNULL();
}
//---------------------------------------------------------------------------

void THSVForm1::Initial_HSV_table()
{
        //initial table setting
        for(int i = 0; i < 96; i++){
              Hue_table[i] = 2*i;
              Sat_table[i] = 127;
              Val_table[i] = 0;
        }

        sg_HSV_table->Cells[0][1]="Hue";
        sg_HSV_table->Cells[0][2]="Sat";
        sg_HSV_table->Cells[0][3]="Val";

        int idx_tmp;
        for(int i = 0; i <96; i++){     //table index with angle
                idx_tmp = (double)i*3.75;
                sg_HSV_table->Cells[i+1][0]=IntToStr(i)+"/"+IntToStr(idx_tmp)+"°";
        }
        sg_HSV_table->Cells[1][0] = "R 0/0°";
        sg_HSV_table->Cells[17][0] = "Y 16/60°";
        sg_HSV_table->Cells[33][0] = "G 32/120°";
        sg_HSV_table->Cells[49][0] = "C 48/180°";
        sg_HSV_table->Cells[65][0] = "B 64/240°";
        sg_HSV_table->Cells[81][0] = "M 80/300°";

        for(int i = 0; i < 96; i++){    //table value
                sg_HSV_table->Cells[i+1][1] = Hue_table[i];
                sg_HSV_table->Cells[i+1][2] = Sat_table[i];
                sg_HSV_table->Cells[i+1][3] = Val_table[i]<0?Val_table[i]+256:Val_table[i];
        }
        for(int i = 0; i < 6; i++){
                sg_Hue_Sat_val->Cells[0][i] = int(double(Hue_table[i*16])*18.75)/10;
                sg_Hue_Sat_val->Cells[1][i] = double(int(double(Sat_table[i*16])/1.27))/100;
                sg_Hue_Sat_val->Cells[2][i] = Val_table[i*16];
        }
        if(lut_addr[0].LutNum()==192){
                GB_HSV_Val->Enabled = false;
                GB_HSV_Val->Font->Color = clInactiveCaption;
                sb_Val_gain->Enabled = false;
                sb_Val_dif_n->Enabled = false;
                sb_Val_dif_p->Enabled = false;
                btn_set_val->Enabled = false;
                btn_reset_val->Enabled = false;
        }
}
//---------------------------------------------------------------------------
void THSVForm1::Reset_HSVshow()
{
        //Hue gain
        sb_Hue_gain->Position = 96;
        lb_Hue_gain->Caption = "0°";

        sb_Sat_gain->Position = 100;
        lb_Sat_gain->Caption = 0+"°";

        sb_Val_gain->Position = 127;
        lb_Val_gain->Caption = 0;
}
//---------------------------------------------------------------------------
void __fastcall THSVForm1::cb_Hue_RedClick(TObject *Sender)
{
        if(cb_Hue_Red->Checked==true){
                cb_Hue_Green->Checked = false;
                cb_Hue_Blue->Checked = false;
                cb_Hue_Cyan->Checked = false;
                cb_Hue_Mag->Checked = false;
                cb_Hue_Yellow->Checked = false;
                le_ChAangle->Text = 0;
        }
        Reset_HSVshow();
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::cb_Hue_YellowClick(TObject *Sender)
{
        if(cb_Hue_Yellow->Checked==true){
                cb_Hue_Red->Checked = false;
                cb_Hue_Green->Checked = false;
                cb_Hue_Blue->Checked = false;
                cb_Hue_Cyan->Checked = false;
                cb_Hue_Mag->Checked = false;
                le_ChAangle->Text = 60;
        }
        Reset_HSVshow();
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::cb_Hue_GreenClick(TObject *Sender)
{
         if(cb_Hue_Green->Checked==true){
                cb_Hue_Red->Checked = false;
                cb_Hue_Blue->Checked = false;
                cb_Hue_Cyan->Checked = false;
                cb_Hue_Mag->Checked = false;
                cb_Hue_Yellow->Checked = false;
                le_ChAangle->Text = 120;
         }
        Reset_HSVshow();
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::cb_Hue_BlueClick(TObject *Sender)
{
         if(cb_Hue_Blue->Checked==true){
                cb_Hue_Red->Checked = false;
                cb_Hue_Green->Checked = false;
                cb_Hue_Cyan->Checked = false;
                cb_Hue_Mag->Checked = false;
                cb_Hue_Yellow->Checked = false;
                le_ChAangle->Text = 240;
         }
        Reset_HSVshow();
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::cb_Hue_CyanClick(TObject *Sender)
{
        if(cb_Hue_Cyan->Checked==true){
                cb_Hue_Red->Checked = false;
                cb_Hue_Green->Checked = false;
                cb_Hue_Blue->Checked = false;
                cb_Hue_Mag->Checked = false;
                cb_Hue_Yellow->Checked = false;
                le_ChAangle->Text = 180;
        }

        Reset_HSVshow();
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::cb_Hue_MagClick(TObject *Sender)
{
        if(cb_Hue_Mag->Checked==true){
                cb_Hue_Red->Checked = false;
                cb_Hue_Green->Checked = false;
                cb_Hue_Blue->Checked = false;
                cb_Hue_Cyan->Checked = false;
                cb_Hue_Yellow->Checked = false;
                le_ChAangle->Text = 300;        //移動的角度為300
        }
        Reset_HSVshow();
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::ed_Hue_CustomChange(TObject *Sender)
{
        le_ChAangle->Text = ed_Hue_Custom->Text;        //移動的角度
        double tmp;
        String str = ed_Hue_Custom->Text;

        //判斷輸入的角度是否合法, type_ok = true(合法,皆為數字), type_ok = false(不合法)
        bool type_ok = true;
        if(str==""){
             type_ok = false;
        }
        else{
                for(int i=0;i<le_ChAangle->Text.Length();i++){
                        //逐字元比對, 是否為數字
                        if(!isdigit(*(le_ChAangle->Text.c_str()+i))){
                                type_ok = false;
                                break;
                        }
                }
        }

        if(type_ok == false){   //輸入角度不合法
                sg_Hue_Sat_val->Cells[0][6] = "";
                sg_Hue_Sat_val->Cells[1][6] = "";
                sg_Hue_Sat_val->Cells[2][6] = "";
                return;
        }
        //輸入角度合法
        tmp = StrToFloat(le_ChAangle->Text);
        tmp = fabs(tmp);        //取絕對值, 型態為float

        if(tmp>360){
                double frac_tmp, int_tmp;
                frac_tmp = modf (tmp , &int_tmp);       //將tmp分成整數"int_tmp"與小數"frac_tmp"
                tmp = (int)int_tmp%360+frac_tmp;
        }
        int tbl_idx = (int)ceil((tmp/3.75));    //取變動的Table值
        if(tbl_idx==96)
                tbl_idx--;

        //選擇變動的HSV值
        double tmp_hue = int((StrToFloat(sg_HSV_table->Cells[tbl_idx+1][1])*1.875)*100)/100.0;
        double tmp_sat = ceil((double)StrToInt(sg_HSV_table->Cells[tbl_idx+1][2])/1.27);
        sg_Hue_Sat_val->Cells[0][6] = FloatToStr(tmp_hue);
        sg_Hue_Sat_val->Cells[1][6] = FloatToStr(tmp_sat/100);
        sg_Hue_Sat_val->Cells[2][6] = sg_HSV_table->Cells[tbl_idx+1][3];
        Reset_HSVshow();
}
//---------------------------------------------------------------------------

void THSVForm1::Hue_LUTWrite()
{
        if(lut_addr[0].LutNum()!=192 && lut_addr[0].LutNum()!=288){
                String str = IntToStr(lut_addr[0].LutNum());
                ShowMessage("Hue LUT number "+str +" is illegal.");
                return;
        }

        btn_set_hue->Enabled = false;
        btn_reset_hue->Enabled = false;
        btn_set_sat->Enabled = false;
        btn_reset_sat->Enabled = false;
        btn_set_val->Enabled = false;
        btn_reset_val->Enabled = false;

        //Set enable => 0, if not will be failed when writing
        if(!EngineerForm->SetWrite_Byte(en.Addr, 0)){
                ShowMessage("Enable HUE fail.");
                return;
        }

        int mul = 3;
        if(lut_addr[0].LutNum()==192)
                mul = 2;
        int HSV_lut[96*3];
        for(int i = 0; i < 96; i++){
                Hue_table[i] = StrToInt(sg_HSV_table->Cells[i+1][1]);
                HSV_lut[i*mul] = Hue_table[i];
                Sat_table[i] = StrToInt(sg_HSV_table->Cells[i+1][2]);
                HSV_lut[i*mul+1] = Sat_table[i];
                if(lut_addr[0].LutNum()==288){
                        Val_table[i] = StrToInt(sg_HSV_table->Cells[i+1][3]);
                        HSV_lut[i*mul+2] = Val_table[i];
                }
        }
        EngineerForm->SetWrite_PG(lut_addr[0], HSV_lut, lut_addr[0].LutNum());

        if(!EngineerForm->SetWrite_Byte(en.Addr, 1)){
                ShowMessage("Enable HUE fail.");
                return;
        }

        btn_set_hue->Enabled = true;
        btn_reset_hue->Enabled = true;
        btn_set_sat->Enabled = true;
        btn_reset_sat->Enabled = true;
        btn_set_val->Enabled = true;
        btn_reset_val->Enabled = true;
}

//--------------------------------------------------------------------------
void __fastcall THSVForm1::btn_set_hueClick(TObject *Sender)
{
        Hue_LUTWrite();

        //Hue gain, Hue diffusion設為0
        sb_Hue_gain->Position = 96;
        lb_Hue_gain->Caption = "0°";
}
//---------------------------------------------------------------------------

bool THSVForm1::Load_HSV(String Fpath)
{
        if(Fpath==NULL)
                return 0;
        char* buffer = Load_File(Fpath);
        if(buffer==NULL)
                return 0;
        for(int i = 0; i < 96; i++){
              Hue_table[i]=-1;
              Sat_table[i]=-1;
              Val_table[i] = 0;
        }

        //比對檔案中的Hue_LUT, Sat_LUT, Bri_LUT字串
        char* str[3];
        char* pch;
        str[0]="Hue_LUT";
        str[1]="Sat_LUT";
        str[2]="Bri_LUT";
        pch = strtok (buffer,"\n\t");
        for(int i = 0; i < 3; i++){
                while (memcmp(pch,str[i],7)!=0){
                        if(pch == NULL){
                                ShowMessage("Can't open Hue table file.");
                                return 0;
                        }
                        pch = strtok (NULL,"\n\t");
                }
        }

        //取出檔案中的數值
        int c = 0;
        pch = strtok (NULL,"\n\t");
        while (c < 288 && pch!=NULL){
                if(pch == NULL){
                        ShowMessage("Can't open Hue table file.");
                        return 0;        //資料中的data缺少
                }
                if(c%3 == 0)
                        Hue_table[c/3] = StrToInt((AnsiString)pch);
                else if(c%3 == 1)
                        Sat_table[c/3] = StrToInt((AnsiString)pch);
                else if(lut_addr[0].LutNum()==288)
                        Val_table[c/3] = StrToInt((AnsiString)pch);
                pch = strtok (NULL,"\n\t");
                c++;
        }
        delete [] buffer;

        for(int i = 0; i < 96; i++){
                sg_HSV_table->Cells[i+1][1] = Hue_table[i];
                sg_HSV_table->Cells[i+1][2] = Sat_table[i];
                sg_HSV_table->Cells[i+1][3] = Val_table[i];
        }
        sg_Hue_Sat_val->Cells[0][0] = (int)((double)StrToInt(sg_HSV_table->Cells[1][1])*1.875);      //Red
        sg_Hue_Sat_val->Cells[0][2] = (int)((double)StrToInt(sg_HSV_table->Cells[33][1])*1.875);     //Green
        sg_Hue_Sat_val->Cells[0][4] = (int)((double)StrToInt(sg_HSV_table->Cells[65][1])*1.875);     //Blue
        sg_Hue_Sat_val->Cells[0][3] = (int)((double)StrToInt(sg_HSV_table->Cells[49][1])*1.875);     //Cyan
        sg_Hue_Sat_val->Cells[0][1] = (int)((double)StrToInt(sg_HSV_table->Cells[17][1])*1.875);     //Magenta
        sg_Hue_Sat_val->Cells[0][5] = (int)((double)StrToInt(sg_HSV_table->Cells[81][1])*1.875);     //Yellow

        //Red
        double tmp_sat = ceil((double)StrToInt(sg_HSV_table->Cells[1][2])/1.27);
        sg_Hue_Sat_val->Cells[1][0] = FloatToStr(tmp_sat/100);
        sg_Hue_Sat_val->Cells[2][0] = StrToInt(sg_HSV_table->Cells[1][3]);

        //Yellow
        tmp_sat = ceil((double)StrToInt(sg_HSV_table->Cells[17][2])/1.27);
        sg_Hue_Sat_val->Cells[1][1] = FloatToStr(tmp_sat/100);
        sg_Hue_Sat_val->Cells[2][1] = StrToInt(sg_HSV_table->Cells[17][3]);

        //Green
        tmp_sat = ceil((double)StrToInt(sg_HSV_table->Cells[33][2])/1.27);
        sg_Hue_Sat_val->Cells[1][2] = FloatToStr(tmp_sat/100);
        sg_Hue_Sat_val->Cells[2][2] = StrToInt(sg_HSV_table->Cells[33][3]);

        //Cyan
        tmp_sat = ceil((double)StrToInt(sg_HSV_table->Cells[49][2])/1.27);
        sg_Hue_Sat_val->Cells[1][3] = FloatToStr(tmp_sat/100);
        sg_Hue_Sat_val->Cells[2][3] = StrToInt(sg_HSV_table->Cells[49][3]);

        //Blue
        tmp_sat = ceil((double)StrToInt(sg_HSV_table->Cells[65][2])/1.27);
        sg_Hue_Sat_val->Cells[1][4] = FloatToStr(tmp_sat/100);
        sg_Hue_Sat_val->Cells[2][4] = StrToInt(sg_HSV_table->Cells[65][3]);

        //Magenta
        tmp_sat = ceil((double)StrToInt(sg_HSV_table->Cells[81][2])/1.27);
        sg_Hue_Sat_val->Cells[1][5] = FloatToStr(tmp_sat/100);
        sg_Hue_Sat_val->Cells[2][5] = StrToInt(sg_HSV_table->Cells[81][3]);

        if(ed_Hue_Custom->Text!=""){
                double tmp = StrToFloat(ed_Hue_Custom->Text);
                tmp = ceil(tmp/3.75);
                tmp_sat = ceil((double)StrToInt(sg_HSV_table->Cells[int(tmp)+1][2])/1.27);
                sg_Hue_Sat_val->Cells[1][6] = FloatToStr(tmp_sat/100);
                sg_Hue_Sat_val->Cells[1][6] = StrToInt(sg_HSV_table->Cells[int(tmp)+1][3]);
        }

        sb_Sat_gain->Position = 100;
        lb_Sat_gain->Caption = 0+"°";
        sb_Hue_gain->Position = 96;
        lb_Hue_gain->Caption = "0°";
        sb_Val_gain->Position = 127;
        lb_Val_gain->Caption = "0°";

        Hue_LUTWrite();
        return 1;
}

//--------------------------------------------------------------------------

void __fastcall THSVForm1::btn_HSV_loadClick(TObject *Sender)
{
        if(!OpenDialog1->Execute())
                return;
        String Fpath;
        Fpath = OpenDialog1->FileName;

        Load_HSV(Fpath);

}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::btn_HSV_saveClick(TObject *Sender)
{
        if(!SaveDialog1->Execute())
                return;
        String Fpath = SaveDialog1->FileName/*+".txt"*/;
        FILE* fptr = fopen (Fpath.c_str(),"w");

        fprintf(fptr,"Hue_LUT\tSat_LUT\tBri_LUT\n");
        for(int i = 0; i < 96; i++){
                fprintf(fptr,"%d\t%d\t%d\n", StrToInt(sg_HSV_table->Cells[i+1][1]),StrToInt(sg_HSV_table->Cells[i+1][2]),StrToInt(sg_HSV_table->Cells[i+1][3]));
        }

        fclose(fptr);        
}
//---------------------------------------------------------------------------


void __fastcall THSVForm1::Hue_ImgMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
        int color;
        double h,s,v,i,r, g, b;
        color = Hue_Img->Canvas->Pixels[X][Y];

        b = color/65536;
        g = color/256%256;
        r = color%256;

        rgb2hsv(r, g, b, &h, &s, &i, &v);
        i = (double)(int(i*10))/10.0;
        h = (double)(int(h*10))/10.0;
        s = (double)(int(s*100))/100.0;
        Hue_Img_Infor->Caption = "B:"+IntToStr((int)b)+" G:"+IntToStr((int)g)+" R:"+IntToStr((int)r)+" H:"+FloatToStr(h)+" S:"+FloatToStr(s)+" V:"+FloatToStr(v)+" I:"+FloatToStr(i);
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::btn_reset_hueClick(TObject *Sender)
{
        //Initial HSI table value
        //Red
        sg_Hue_Sat_val->Cells[0][0]=0;
        //Magenta
        sg_Hue_Sat_val->Cells[0][1]=60;
        //Green
        sg_Hue_Sat_val->Cells[0][2]=120;
        //Cyan
        sg_Hue_Sat_val->Cells[0][3]=180;
        //Blue
        sg_Hue_Sat_val->Cells[0][4]=240;
        //Yellow
        sg_Hue_Sat_val->Cells[0][5]=300;
        //Custom
        sg_Hue_Sat_val->Cells[0][6]="";


        for(int i = 0; i <96; i++){
                Hue_table[i] = i*2;
                sg_HSV_table->Cells[i+1][1]=Hue_table[i];
        }
        if(ed_Hue_Custom->Text!=""){
                double tmp = StrToFloat(ed_Hue_Custom->Text);
                tmp = ceil(tmp/3.75);
                sg_Hue_Sat_val->Cells[0][6] = (int)((double)StrToInt(sg_HSV_table->Cells[int(tmp)+1][1])*1.875);
        }
        btn_set_hueClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::btn_set_satClick(TObject *Sender)
{
        Hue_LUTWrite();

        //Sat gain, Sat diffusion設為0
        sb_Sat_gain->Position = 100;
        lb_Sat_gain->Caption = 0+"°";        
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::btn_reset_satClick(TObject *Sender)
{
        //Initial HSI table value
        //Red
        sg_Hue_Sat_val->Cells[1][0]=1;
        //Yellow
        sg_Hue_Sat_val->Cells[1][1]=1;
        //Green
        sg_Hue_Sat_val->Cells[1][2]=1;
        //Cyan
        sg_Hue_Sat_val->Cells[1][3]=1;
        //Blue
        sg_Hue_Sat_val->Cells[1][4]=1;
        //Magenta
        sg_Hue_Sat_val->Cells[1][5]=1;

        for(int i = 0; i <96; i++){
                Sat_table[i] = 127;
                sg_HSV_table->Cells[i+1][2]=127;
        }
        if(ed_Hue_Custom->Text!=""){
                double tmp = StrToFloat(ed_Hue_Custom->Text);
                tmp = ceil(tmp/3.75);
                double tmp_sat = ceil((double)StrToInt(sg_HSV_table->Cells[int(tmp)+1][2])/1.27);
                sg_Hue_Sat_val->Cells[1][6] = FloatToStr(tmp_sat/100);
        }
        btn_set_satClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::btn_set_valClick(TObject *Sender)
{
        Hue_LUTWrite();

        //Sat gain, Sat diffusion設為0
        sb_Val_gain->Position = 127;
        lb_Val_gain->Caption = 0;
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::btn_reset_valClick(TObject *Sender)
{
        //Initial HSV table value
        //Red
        sg_Hue_Sat_val->Cells[2][0]=0;
        //Yellow
        sg_Hue_Sat_val->Cells[2][1]=0;
        //Green
        sg_Hue_Sat_val->Cells[2][2]=0;
        //Cyan
        sg_Hue_Sat_val->Cells[2][3]=0;
        //Blue
        sg_Hue_Sat_val->Cells[2][4]=0;
        //Magenta
        sg_Hue_Sat_val->Cells[2][5]=0;

        for(int i = 0; i <96; i++){
                Val_table[i] = 127;
                sg_HSV_table->Cells[i+1][3]=0;
        }
        Hue_LUTWrite();

        //Sat gain, Sat diffusion設為0
        sb_Val_gain->Position = 127;
        lb_Val_gain->Caption = 0;
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::sb_Hue_dif_nChange(TObject *Sender)
{
        lb_Hue_dif_n->Caption = FloatToStr((sb_Hue_dif_n->Position-48)*3.75)+"°";        
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::sb_Hue_dif_pChange(TObject *Sender)
{
        lb_Hue_dif_p->Caption = FloatToStr(sb_Hue_dif_p->Position*3.75)+"°";
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::sb_Sat_dif_nChange(TObject *Sender)
{
        lb_Sat_dif_n->Caption = FloatToStr((sb_Sat_dif_n->Position-48)*3.75)+"°";
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::sb_Sat_dif_pChange(TObject *Sender)
{
        lb_Sat_dif_p->Caption = FloatToStr(sb_Sat_dif_p->Position*3.75)+"°";
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::sb_Val_dif_nChange(TObject *Sender)
{
        lb_Val_dif_n->Caption = FloatToStr((sb_Val_dif_n->Position-48)*3.75)+"°";
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::sb_Val_dif_pChange(TObject *Sender)
{
        lb_Val_dif_p->Caption = FloatToStr(sb_Val_dif_p->Position*3.75)+"°";
}
//---------------------------------------------------------------------------


void __fastcall THSVForm1::sb_Hue_gainScroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
        int tmp_Hue_table[96];
        int tmp_Hue_table1[96];

        int gain = sb_Hue_gain->Position-96;
        //gain_arc代表角度,介面顯示用
        int gain_arc = (double)gain/192*360;
        lb_Hue_gain->Caption = IntToStr(gain_arc)+"°";

        int Change_idx = floor(StrToFloat(le_ChAangle->Text)/3.75);      //將使用者輸入的角度換成table表中的index
        int Hue_tmp;
        if(cb_Hue_rotation->Checked == false){   //diffusion
                  tmp_Hue_table[0] = Hue_table[(Change_idx+96/2)%96];
                  for(int i = 1; i <96; i++){
                        tmp_Hue_table[i] = Hue_table[(Change_idx+96/2+i)%96];
                        if(tmp_Hue_table[i]<tmp_Hue_table[i-1])
                                tmp_Hue_table[i] += 192;
                  }
                  //Check if table value really increasing
                  for(int i = 1; i <= 95; i++)
                        if(tmp_Hue_table[i-1]>tmp_Hue_table[i]){
                                String str = "index "+IntToStr(i-1)+" value is smaller than index "+IntToStr(i);
                                //ShowMessage(str);
                        }
                  ////////////////////////////////////////////
                  //根據給予的gain值找出適合的diffusion邊界值
                  int low = (sb_Hue_dif_n->Position-48)+48;
                  int high = sb_Hue_dif_p->Position+48;
                  tmp_Hue_table[48] += gain;
                  if(tmp_Hue_table[48]>=tmp_Hue_table[high]){
                        high++;
                        while(tmp_Hue_table[48]>=tmp_Hue_table[high]){
                                high++;
                        }
                  }
                  else if(tmp_Hue_table[48]<=tmp_Hue_table[low]){
                        low--;
                        while(tmp_Hue_table[48]<=tmp_Hue_table[low]){
                                low--;
                        }
                        
                  }
                  sb_Hue_dif_p->Position = high-48;
                  sb_Hue_dif_n->Position = (low+48)%49;

                  //作數值的diffusion運算
                        if(high>48 && high<96){
                                float delta_high = (float)(tmp_Hue_table[high]-tmp_Hue_table[48])/(high-48);
                                float tmp;
                                for(int i = 48+1; i < high; i++){
                                        tmp = (delta_high*(i-48));
                                        tmp_Hue_table[i] = tmp_Hue_table[48]+floor(tmp);
                                }

                        }else{
                                String str = IntToStr(high);
                                //ShowMessage("Overflow or underflow error: High value is "+str);
                                high--;
                                sb_Hue_gain->Position--;
                                return;
                        }

                        //作數值的diffusion運算
                        if(low<48 && low>=0){
                                float delta_low = (float)(tmp_Hue_table[48]-tmp_Hue_table[low])/(48-low);
                                float tmp;
                                for(int i = 48-1; i > low; i--){
                                        tmp = delta_low*(float)(48-i);
                                        tmp_Hue_table[i] = tmp_Hue_table[48]-ceil(tmp);
                                }
                                
                        }else{
                                String str = IntToStr(low);
                                //ShowMessage("Overflow or underflow error: Low value is "+str);
                                sb_Hue_gain->Position++;
                                low++;
                                return;
                        }
                  /*
                  //smooth
                  int x[4];
                  for(int i = 0; i <5; i++){
                        x[i]=tmp_Hue_table[low-(2-i)];
                  }
                  int dif_tmp = (x[0]+x[1]+x[2]+x[3])/4;
                  */

                  for(int i = 0; i <96; i++){
                        tmp_Hue_table1[i] = tmp_Hue_table[(96/2-Change_idx+i+96)%96]%192;
                  }
        }else{  //rotation
                for(int i = 0; i < 96; i++)
                        tmp_Hue_table1[i] = (Hue_table[i]+gain+192)%192;
                int tmp_Sat_table[96];
                int trnAng = floor(gain/2);
                int tmp_idx;
                for(int i = 0; i < 96; i++){
                        tmp_idx = (trnAng+i+96)%96;
                        tmp_Sat_table[i] = Sat_table[tmp_idx];
                }
                for(int i = 0; i < 96; i++)
                        sg_HSV_table->Cells[i+1][2] = tmp_Sat_table[i];
        }
        for(int i = 0; i < 96; i++)
                sg_HSV_table->Cells[i+1][1] = tmp_Hue_table1[i];

        sg_Hue_Sat_val->Cells[0][0] = (int)((double)StrToInt(sg_HSV_table->Cells[1][1])*1.875);      //Red
        sg_Hue_Sat_val->Cells[0][2] = (int)((double)StrToInt(sg_HSV_table->Cells[33][1])*1.875);     //Green
        sg_Hue_Sat_val->Cells[0][4] = (int)((double)StrToInt(sg_HSV_table->Cells[65][1])*1.875);     //Blue
        sg_Hue_Sat_val->Cells[0][3] = (int)((double)StrToInt(sg_HSV_table->Cells[49][1])*1.875);     //Cyan
        sg_Hue_Sat_val->Cells[0][1] = (int)((double)StrToInt(sg_HSV_table->Cells[17][1])*1.875);     //Magenta
        sg_Hue_Sat_val->Cells[0][5] = (int)((double)StrToInt(sg_HSV_table->Cells[81][1])*1.875);     //Yellow

        if(ed_Hue_Custom->Text!=""){
                double tmp = StrToFloat(ed_Hue_Custom->Text);
                tmp = ceil(tmp/3.75);
                sg_Hue_Sat_val->Cells[0][6] = (int)((double)StrToInt(sg_HSV_table->Cells[int(tmp)+1][1])*1.875);
        }
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::sb_Sat_gainScroll(TObject *Sender,
      TScrollCode ScrollCode, int &ScrollPos)
{
        float gain = (float)sb_Sat_gain->Position/100;
        if(gain==0)
                return;
        int tmp_Sat_table[96];
        for(int i = 0; i < 96; i++){
                tmp_Sat_table[i] = Sat_table[i];
                sg_HSV_table->Cells[i+1][2]= Sat_table[i];
        }

        int Change_idx = ceil(StrToFloat(le_ChAangle->Text)/3.75);

        lb_Sat_gain->Caption = IntToStr(sb_Sat_gain->Position)+"%";

        if(cb_Sat_glb->Checked == false){
                tmp_Sat_table[Change_idx] = (float)Sat_table[Change_idx]*gain;
                int dif_n = StrToInt(sb_Sat_dif_n->Position-48)-1;
                int dif_p = StrToInt(sb_Sat_dif_p->Position)+1;
                int tmp_Sat_idx;
                gain-=1;
                if(dif_p>0)
                        for(int i = 1; i <= dif_p; i++){
                            tmp_Sat_idx = (Change_idx+i)%96;
                            tmp_Sat_table[tmp_Sat_idx] = (float)Sat_table[tmp_Sat_idx]*(1+gain*(dif_p-i)/(dif_p));
                            sg_HSV_table->Cells[tmp_Sat_idx+1][2] = tmp_Sat_table[tmp_Sat_idx];
                        }
                if(dif_n<0)
                        for(int i = -1; i >= dif_n; i--){
                            tmp_Sat_idx = (Change_idx+i+96)%96;
                            tmp_Sat_table[tmp_Sat_idx] = (float)Sat_table[tmp_Sat_idx]*(1+gain*(dif_n-i)*(-1)/(dif_n*(-1)));
                            sg_HSV_table->Cells[tmp_Sat_idx+1][2] = tmp_Sat_table[tmp_Sat_idx];
                        }
                sg_HSV_table->Cells[Change_idx+1][2] = tmp_Sat_table[Change_idx];
        }else{
                for(int i = 0; i < 96; i++){
                        tmp_Sat_table[i] = (float)Sat_table[i]*gain;
                        sg_HSV_table->Cells[i+1][2] = tmp_Sat_table[i];
                }
        }

        double tmp_sat = ceil((double)StrToInt(sg_HSV_table->Cells[1][2])/1.27);
        sg_Hue_Sat_val->Cells[1][0] = FloatToStr(tmp_sat/100);      //Red
        tmp_sat = ceil((double)StrToInt(sg_HSV_table->Cells[33][2])/1.27);
        sg_Hue_Sat_val->Cells[1][2] = FloatToStr(tmp_sat/100);     //Green
        tmp_sat = ceil((double)StrToInt(sg_HSV_table->Cells[65][2])/1.27);
        sg_Hue_Sat_val->Cells[1][4] = FloatToStr(tmp_sat/100);     //Blue
        tmp_sat = ceil((double)StrToInt(sg_HSV_table->Cells[49][2])/1.27);
        sg_Hue_Sat_val->Cells[1][3] = FloatToStr(tmp_sat/100);     //Cyan
        tmp_sat = ceil((double)StrToInt(sg_HSV_table->Cells[17][2])/1.27);
        sg_Hue_Sat_val->Cells[1][1] = FloatToStr(tmp_sat/100);     //Magenta
        tmp_sat = ceil((double)StrToInt(sg_HSV_table->Cells[81][2])/1.27);
        sg_Hue_Sat_val->Cells[1][5] = FloatToStr(tmp_sat/100);     //Yellow

        if(ed_Hue_Custom->Text!=""){
                double tmp = StrToFloat(ed_Hue_Custom->Text);
                tmp = ceil(tmp/3.75);
                tmp_sat = ceil((double)StrToInt(sg_HSV_table->Cells[int(tmp)+1][2])/1.27);
                sg_Hue_Sat_val->Cells[1][6] = FloatToStr(tmp_sat/100);
        }
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::sb_Val_gainChange(TObject *Sender)
{
	float gain = sb_Val_gain->Position-127;
        int tmp_Val_table[96];

        for(int i = 0; i < 96; i++){
                tmp_Val_table[i] = Val_table[i];
                sg_HSV_table->Cells[i+1][3]= Val_table[i];
        }
        int Change_idx = floor(StrToFloat(le_ChAangle->Text)/3.75);
        lb_Val_gain->Caption = IntToStr(sb_Val_gain->Position-127);

        if(cb_Val_glb->Checked == false){
                //if(Int_table[Change_idx]+gain>=127)
                  //      tmp_Int_table[Change_idx] = 127;
                //else
                tmp_Val_table[Change_idx] = (Val_table[Change_idx]+(int)gain+256)%256;
                double dif_n = StrToInt(sb_Val_dif_n->Position-48)-1;
                double dif_p = StrToInt(sb_Val_dif_p->Position)+1;
                int tmp_Val_idx;
                double add_gain;

		sg_HSV_table->Cells[Change_idx+1][3] = tmp_Val_table[Change_idx];

                if(dif_p>0)
                        add_gain = tmp_Val_table[Change_idx] - Val_table[(Change_idx+(int)dif_p)%96];
                        for(int i = 1; i <= dif_p; i++){
                            tmp_Val_idx = (Change_idx+i)%96;
                            tmp_Val_table[tmp_Val_idx] = (float)Val_table[tmp_Val_idx]+(add_gain*(dif_p-i)/(dif_p));
                            tmp_Val_table[tmp_Val_idx] = (tmp_Val_table[tmp_Val_idx]+256)%256;
                            sg_HSV_table->Cells[tmp_Val_idx+1][3] = tmp_Val_table[tmp_Val_idx];
                        }
                if(dif_n<0)
                        add_gain = tmp_Val_table[Change_idx] - Val_table[(Change_idx+(int)dif_n+96)%96] ;
                        for(int i = -1; i >= dif_n; i--){
                            tmp_Val_idx = (Change_idx+i+96)%96;
                            tmp_Val_table[tmp_Val_idx] = (float)Val_table[tmp_Val_idx]+(add_gain*(dif_n-i)*(-1)/(dif_n*(-1)));
                            tmp_Val_table[tmp_Val_idx] = (tmp_Val_table[tmp_Val_idx]+256)%256;
                            sg_HSV_table->Cells[tmp_Val_idx+1][3] = tmp_Val_table[tmp_Val_idx];
                        }

        }else{
                for(int i = 0; i < 96; i++){
                        //if(Int_table[i]+gain>=256)
                        //        tmp_Int_table[i] = 255;
                        //else if(Int_table[i]+gain<0)
                        //        tmp_Int_table[i] = 0;
                        //else
                                tmp_Val_table[i] = (Val_table[i]+(int)gain+256)%256;
                        sg_HSV_table->Cells[i+1][3] = tmp_Val_table[i];
                }
        }
        int tmp;
        for(int i = 0; i < 6; i++){
                tmp = StrToInt(sg_HSV_table->Cells[i*16+1][3]);
                sg_Hue_Sat_val->Cells[2][i] = tmp>128?tmp-256:tmp;
        }
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::btn_Hue_Img_loadClick(TObject *Sender)
{
        if(!OpenDialog1->Execute())
                return;
        String Fpath;
        //Hue_Img->Picture->LoadFromFile(Fpath);

        Fpath = OpenDialog1->FileName;
        Graphics::TBitmap *Bitmap;

        Graphics::TBitmap *RefGraph;
        RefGraph = new Graphics::TBitmap();
        RefGraph->Height = Hue_Img->Height;
        RefGraph->Width = Hue_Img->Width;
        RefGraph->LoadFromFile(Fpath);
        Hue_Img->Picture->Graphic = RefGraph;
//        Hue_Img->Canvas->Draw(0,0,RefGraph);
        delete RefGraph;

}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::rg_HSV_ModeClick(TObject *Sender)
{
        String Fpath;

        if(rg_HSV_Mode->ItemIndex==0)
                Fpath = "\HSV_default1.txt";
        else if(rg_HSV_Mode->ItemIndex==1)
                Fpath = "\HSV_default2.txt";
        else if(rg_HSV_Mode->ItemIndex==2)
                Fpath = "\HSV_default3.txt";

        btn_HSV_load->Enabled = false;
        btn_HSV_save->Enabled = false;
        rg_HSV_Mode->Enabled = false;
        if(!Load_HSV(Fpath)){
                ShowMessage("Load File fail.");
        }
        btn_HSV_load->Enabled = true;
        btn_HSV_save->Enabled = true;
        rg_HSV_Mode->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall THSVForm1::Btn_HSV_reloadClick(TObject *Sender)
{
        Btn_HSV_reload->Enabled = false;
/*        unsigned char read_val;
        for(int i = 0; i < HSVChkBox_Nbr; i++){
                if(ChkB[i]->Chkb->Visible==true){
                        EngineerForm->SetRead_Byte(ChkB[i]->Addr, &read_val);
                        if(read_val==1)
                                ChkB[i]->Chkb->Checked = 1;
                        else if(read_val==0)
                                ChkB[i]->Chkb->Checked = 0;
                        else
                                ShowMessage("HSV CheckBox read error:"+IntToStr(read_val));
                }
        }
        EngineerForm->SetRead_Byte(en.Addr, &read_val);
        if(read_val==1)
                cb_en->Checked = 1;
        else if(read_val==0)
                cb_en->Checked = 0;
        else
                ShowMessage("HSV CheckBox read error:"+IntToStr(read_val));

        if(lut_addr[0].LutNum()!=192 && lut_addr[0].LutNum()!=288){
                String str = IntToStr(lut_addr[0].LutNum());
                ShowMessage("Hue LUT number "+str +" is illegal.");
                return;
        }
        */
        btn_set_hue->Enabled = false;
        btn_reset_hue->Enabled = false;
        btn_set_sat->Enabled = false;
        btn_reset_sat->Enabled = false;
        btn_set_val->Enabled = false;
        btn_reset_val->Enabled = false;

        //Set enable => 0, if not will be failed when writing
 //       if(!EngineerForm->SetWrite_Byte(en.Addr, 0))
 //               exit(0);

        int HSV_lut[96*3];
        if(!EngineerForm->SetRead_PG(lut_addr[0], HSV_lut, lut_addr[0].LutNum())){
                ShowMessage("Hue page read fail.");
                return;
        }

        int mul = 3;
        if(lut_addr[0].LutNum()==192)
                mul = 2;

        for(int i = 0; i < 96; i++){
                Hue_table[i] = HSV_lut[i*mul];
                sg_HSV_table->Cells[i+1][1] = IntToStr(Hue_table[i]);
                Sat_table[i] = HSV_lut[i*mul+1];
                sg_HSV_table->Cells[i+1][2] = IntToStr(Sat_table[i]);

                if(lut_addr[0].LutNum()==288){
                        Val_table[i] = HSV_lut[i*mul+2];
                        sg_HSV_table->Cells[i+1][3] = IntToStr(Val_table[i]);
                }
        }

  //      if(!EngineerForm->SetWrite_Byte(en.Addr, 1))
  //              exit(0);

        btn_set_hue->Enabled = true;
        btn_reset_hue->Enabled = true;
        btn_set_sat->Enabled = true;
        btn_reset_sat->Enabled = true;
        btn_set_val->Enabled = true;
        btn_reset_val->Enabled = true;

        Btn_HSV_reload->Enabled = true;
}
//---------------------------------------------------------------------------





void __fastcall THSVForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if(Key == 0x40){
                Btn_HSV_reloadClick(Sender);
        }
}
//---------------------------------------------------------------------------

