//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "c3d1_dis_new.h"
#include "color_converter.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_in_target *Form_in_target;
//---------------------------------------------------------------------------
__fastcall TForm_in_target::TForm_in_target(TComponent* Owner)
        : TForm(Owner)
{
        sg_rgb->Cells[0][0] = "R";
        sg_rgb->Cells[0][1] = "G";
        sg_rgb->Cells[0][2] = "B";
        sg_hsv->Cells[0][0] = "H";
        sg_hsv->Cells[0][1] = "S";
        sg_hsv->Cells[0][2] = "V";
        sg_hsv->Cells[0][3] = "I";
}
//---------------------------------------------------------------------------

void __fastcall TForm_in_target::btn_rgb2hsvClick(TObject *Sender)
{
        double r = StrToFloat(sg_rgb->Cells[1][0]);
        double g = StrToFloat(sg_rgb->Cells[1][1]);
        double b = StrToFloat(sg_rgb->Cells[1][2]);

        double h, s, i, v;
        rgb2hsv(r, g, b, &h, &s, &i, &v);

        sg_hsv->Cells[1][0] = FloatToStr((double)(int(h*10))/10);
        sg_hsv->Cells[1][1] = FloatToStr((double)(int(s*1000))/1000);
        sg_hsv->Cells[1][2] = FloatToStr((double)(int(v*10))/10);
}
//---------------------------------------------------------------------------

void __fastcall TForm_in_target::btn_hsv2rgbClick(TObject *Sender)
{
        double h = StrToFloat(sg_hsv->Cells[1][0]);
        double s = StrToFloat(sg_hsv->Cells[1][1]);
        double v = StrToFloat(sg_hsv->Cells[1][2]);

        double r,g,b;
        hsv2rgb(h, s, v, &r, &g, &b);

        sg_rgb->Cells[1][0] = FloatToStr((double)(int(r*10))/10);
        sg_rgb->Cells[1][1] = FloatToStr((double)(int(g*10))/10);
        sg_rgb->Cells[1][2] = FloatToStr((double)(int(b*10))/10);
}
//---------------------------------------------------------------------------

void __fastcall TForm_in_target::btn_hsv2rgb_bachClick(TObject *Sender)
{
        if(!OpenDialog1->Execute())
                return;
        String Fpath = OpenDialog1->FileName;

        char* buffer = Load_File(Fpath);

        int num = edt_num->Text.ToIntDef(-1);
        if(num == -1)
                return;
        double* r = new double [num];
        double* g = new double [num];
        double* b = new double [num];
        for(int i = 0; i < num; i++){
                r[i]=0.0;
                g[i]=0.0;
                b[i]=0.0;
        }
        int c = 0;
        double h, s, v;
        int num_idx = 0;
        char* pch = strtok (buffer,"\n\t");
        while (c < num*3 && pch!=NULL){
                if(pch == NULL){
                        ShowMessage("Can't open file.");
                        return;        //資料中的data缺少
                }
                if(c%3 == 0)
                        h = (double)StrToFloat((AnsiString)pch);
                else if(c%3 == 1)
                        s = (double)StrToFloat((AnsiString)pch);
                else if(c%3 == 2){
                        v = (double)StrToFloat((AnsiString)pch);
                        hsv2rgb(h, s, v, &r[num_idx],&g[num_idx],&b[num_idx]);
                        num_idx++;
                }
                pch = strtok (NULL,"\n\t");
                c++;
       }
       delete [] buffer;
       

        if(!SaveDialog1->Execute()){
                return;
        }

        String Fpath1 = SaveDialog1->FileName;
        if(Fpath1==NULL)
                return;
        FILE* fptr = fopen (Fpath1.c_str(),"w");

        for(int i = 0; i < num; i++)
                fprintf(fptr,"%.2f\t%.2f\t%.2f\n",r[i],g[i],b[i]);
        fclose(fptr);
        delete [] r;
       delete [] g;
       delete [] b;
}
//---------------------------------------------------------------------------

void __fastcall TForm_in_target::btn_rgb2hsv_bachClick(TObject *Sender)
{
        if(!OpenDialog1->Execute())
                return;
        String Fpath = OpenDialog1->FileName;

        char* buffer = Load_File(Fpath);

        int num = edt_num->Text.ToIntDef(-1);
        if(num == -1)
                return;

        if(!SaveDialog1->Execute()){
                return;
        }

        String Fpath1 = SaveDialog1->FileName;
        if(Fpath1==NULL)
                return;
        FILE* fptr = fopen (Fpath1.c_str(),"w");

        double r =0.0;
        double g =0.0;
        double b =0.0;

        int c = 0;
        double h, s, v, i;

        char* pch = strtok (buffer,"\n\t");
        while (c < num*3 && pch!=NULL){
                if(pch == NULL){
                        ShowMessage("Can't open c3d table file.");
                        return;        //資料中的data缺少
                }
                if(c%3 == 0)
                        r = StrToFloat((AnsiString)pch);
                else if(c%3 == 1)
                        g = StrToFloat((AnsiString)pch);
                else if(c%3 == 2){
                        b = StrToFloat((AnsiString)pch);
                        rgb2hsv(r,g,b,&h, &s, &i, &v);
                        fprintf(fptr,"%.3f\t%.3f\t%.3f\t%.3f\t%.3f\t%.3f\n",r,g,b,h,s,v);
                }
                pch = strtok (NULL,"\n\t");
                c++;
       }
       delete [] buffer;

        fclose(fptr);
}
//---------------------------------------------------------------------------

void __fastcall TForm_in_target::btn_sim_colorClick(TObject *Sender)
{
        if(!OpenDialog1->Execute())
                return;
        String Fpath_load = OpenDialog1->FileName;

        char* buffer = Load_File(Fpath_load);

        int num = edt_num->Text.ToIntDef(-1);
        if(num == -1)
                return;

        if(!SaveDialog1->Execute()){
                return;
        }
        String Fpath_save = SaveDialog1->FileName;
        if(Fpath_save==NULL)
                return;
        FILE* fptr = fopen (Fpath_save.c_str(),"w");
        double r =0.0, g =0.0, b =0.0;
        double r_new, g_new, b_new;
        char* pch = strtok (buffer,"\n\t");
        int c = 0;
        while (c < num*3 && pch!=NULL){
                if(pch == NULL){
                        ShowMessage("Can't open c3d table file.");
                        return;        //資料中的data缺少
                }
                if(c%3 == 0)
                        r = StrToFloat((AnsiString)pch);
                else if(c%3 == 1)
                        g = StrToFloat((AnsiString)pch);
                else if(c%3 == 2){
                        b = StrToFloat((AnsiString)pch);
                        C3DForm1->C3Dsim(r,g,b,&r_new,&g_new,&b_new);
                        fprintf(fptr,"%d\t%d\t%d\t%d\t%d\t%d\n",(int)r,(int)g,(int)b,
                         (int)(r_new+0.5),(int)(g_new+0.5),(int)(b_new+0.5));
                }
                pch = strtok (NULL,"\n\t");
                c++;
       }
       delete [] buffer;
       fclose(fptr);
}
//---------------------------------------------------------------------------

