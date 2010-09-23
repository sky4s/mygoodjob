//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "c3d1.h"
#include "c3d_12401.h"
#include "c3d_sim.h"
#include "Engineering.h"
#include "Unit3.h"
//#include "Table_Step_Form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TC3DForm1* C3DForm1;
AbstC3D *OC3D;

int TBL_SIZE = 9;
int cube_dis = 256/(TBL_SIZE-1);
int bit_num = 12;
double Ratio = pow(2,bit_num-8);
bool c3d_detailadjust = false;
int tbl_s;
int tbl_val[4][33] = {
//{0,16,48,112,176,208,224,240,255},      //table 3
//{0,16,80,144,184,216,232,248,255}, //table 10
//{0,16,96,144,168,200,224,240,255},      //table a
//{0,16,96,144,176,200,224,240,255},      //table b
{0,32,64,96,128,160,192,224,(256-1.0/Ratio)},  //9x9x9 uniform table

{0,32,64,128,192,224,(256-1.0/Ratio),0,0},                           //7x7x7 table
{0,16,32,48,64,80,96,112,128,144,160,176,192,208,224,240,255},       //17x17x17 table
{0,8,16,24,32,40,48,56,64,72,80,88,96,104,112,120,128,136,144,       //33x33x33 table
152,160,168,176,184,192,200,208,216,224,232,240,248,255}};

int sim_val[72]={8.1, 4.1, 0.2, -1.1, -0.8, -1.7, -2.3, -3.4, -4.9, -4.3, -4.4,
-4.8, -3.3, -3.4, -3.2, -3.1, -3.3, -2.8, -0.5, 3.0, 4.8, 12.0, 14.9, 14.8,
14.9, 13.0, 11.8, 10.4, 9.7, 10.0, 9.4, 8.2, 6.7, 5.8, 4.6, 2.8, 2.3, 1.6, 0.7,
-0.2, -0.5, -1.3, -1.4, -1.9, -1.4, -1.3, -2.6, -4.4, -4.4, -5.5, -8.2, -6.2,
-3.8, -2.0, -0.1, 1.5, 1.7, 2.4, 4.1, 4.0, 3.5, 4.1, 3.4, 3.6, 3.6, 3.3, 2.9,
4.5, 3.7, 6.0, 8.9, 10.8};

int total_len = TBL_SIZE*TBL_SIZE*TBL_SIZE;
int **c3d_r, **c3d_g, **c3d_b;
TC3D_SimualteForm *C3D_SimualteForm;
//---------------------------------------------------------------------------
__fastcall TC3DForm1::TC3DForm1(TComponent* Owner)
        : TForm(Owner)
{
        new_array();
        interpol = true;
        if(TBL_SIZE == 9)
                tbl_s = 0;
        else if(TBL_SIZE == 7)
                tbl_s = 1;
        else if(TBL_SIZE == 17)
                tbl_s = 2;
        else if(TBL_SIZE == 33)
                tbl_s = 3;

        C3Dini();
}
__fastcall TC3DForm1::~TC3DForm1()
{
        delete_array();
}
//---------------------------------------------------------------------------
void TC3DForm1::new_array()
{
        c3d_lutR = new double** [TBL_SIZE];
        c3d_lutG = new double** [TBL_SIZE];
        c3d_lutB = new double** [TBL_SIZE];
        c3d_lutH = new double** [TBL_SIZE];
        c3d_lutS = new double** [TBL_SIZE];
        c3d_lutI = new double** [TBL_SIZE];
        c3d_lutV = new double** [TBL_SIZE];
        for(int i = 0; i < TBL_SIZE; i++){
                c3d_lutR[i] = new double* [TBL_SIZE];
                c3d_lutG[i] = new double* [TBL_SIZE];
                c3d_lutB[i] = new double* [TBL_SIZE];
                c3d_lutH[i] = new double* [TBL_SIZE];
                c3d_lutS[i] = new double* [TBL_SIZE];
                c3d_lutI[i] = new double* [TBL_SIZE];
                c3d_lutV[i] = new double* [TBL_SIZE];
                for(int j = 0; j < TBL_SIZE; j++){
                        c3d_lutR[i][j] = new double [TBL_SIZE];
                        c3d_lutG[i][j] = new double [TBL_SIZE];
                        c3d_lutB[i][j] = new double [TBL_SIZE];
                        c3d_lutH[i][j] = new double [TBL_SIZE];
                        c3d_lutS[i][j] = new double [TBL_SIZE];
                        c3d_lutI[i][j] = new double [TBL_SIZE];
                        c3d_lutV[i][j] = new double [TBL_SIZE];
                }
        }

        //===================================================================/

        c3d_r = new int* [2];
        c3d_g = new int* [2];
        c3d_b = new int* [2];
        for(int i=0; i < 2; i++){
                c3d_r[i] = new int [total_len];
                c3d_g[i] = new int [total_len];
                c3d_b[i] = new int [total_len];
        }

        //===================================================================/

        tmp_c3d_lutR = new double** [TBL_SIZE];
        tmp_c3d_lutG = new double** [TBL_SIZE];
        tmp_c3d_lutB = new double** [TBL_SIZE];
        tmp_c3d_lutH = new double** [TBL_SIZE];
        tmp_c3d_lutS = new double** [TBL_SIZE];
        tmp_c3d_lutV = new double** [TBL_SIZE];
        for(int i = 0; i < TBL_SIZE; i++){
                tmp_c3d_lutR[i] = new double* [TBL_SIZE];
                tmp_c3d_lutG[i] = new double* [TBL_SIZE];
                tmp_c3d_lutB[i] = new double* [TBL_SIZE];
                tmp_c3d_lutH[i] = new double* [TBL_SIZE];
                tmp_c3d_lutS[i] = new double* [TBL_SIZE];
                tmp_c3d_lutV[i] = new double* [TBL_SIZE];
                for(int j = 0; j < TBL_SIZE; j++){
                        tmp_c3d_lutR[i][j] = new double [TBL_SIZE];
                        tmp_c3d_lutG[i][j] = new double [TBL_SIZE];
                        tmp_c3d_lutB[i][j] = new double [TBL_SIZE];
                        tmp_c3d_lutH[i][j] = new double [TBL_SIZE];
                        tmp_c3d_lutS[i][j] = new double [TBL_SIZE];
                        tmp_c3d_lutV[i][j] = new double [TBL_SIZE];
                }
        }
}

//---------------------------------------------------------------------------
void TC3DForm1::delete_array()
{
        for(int i = 0; i < TBL_SIZE; i++){
                for(int j = 0; j < TBL_SIZE; j++){
                        delete [] c3d_lutR[i][j];
                        delete [] c3d_lutG[i][j];
                        delete [] c3d_lutB[i][j];
                        delete [] c3d_lutH[i][j];
                        delete [] c3d_lutS[i][j];
                        delete [] c3d_lutI[i][j];
                        delete [] c3d_lutV[i][j];
                }
                delete [] c3d_lutR[i];
                delete [] c3d_lutG[i];
                delete [] c3d_lutB[i];
                delete [] c3d_lutH[i];
                delete [] c3d_lutS[i];
                delete [] c3d_lutI[i];
                delete [] c3d_lutV[i];
        }
        delete [] c3d_lutR;
        delete [] c3d_lutG;
        delete [] c3d_lutB;
        delete [] c3d_lutH;
        delete [] c3d_lutS;
        delete [] c3d_lutI;
        delete [] c3d_lutV;

        //================================================================//

        for(int i = 0; i < 2; i++){
                delete [] c3d_r[i];
                delete [] c3d_g[i];
                delete [] c3d_b[i];
        }
        delete [] c3d_r;
        delete [] c3d_g;
        delete [] c3d_b;

        //================================================================//

        for(int i = 0; i < TBL_SIZE; i++){
                for(int j = 0; j < TBL_SIZE; j++){
                        delete [] tmp_c3d_lutR[i][j];
                        delete [] tmp_c3d_lutG[i][j];
                        delete [] tmp_c3d_lutB[i][j];
                        delete [] tmp_c3d_lutH[i][j];
                        delete [] tmp_c3d_lutS[i][j];
                        delete [] tmp_c3d_lutV[i][j];

                }
                delete [] tmp_c3d_lutR[i];
                delete [] tmp_c3d_lutG[i];
                delete [] tmp_c3d_lutB[i];
                delete [] tmp_c3d_lutH[i];
                delete [] tmp_c3d_lutS[i];
                delete [] tmp_c3d_lutV[i];
        }
        delete [] tmp_c3d_lutR;
        delete [] tmp_c3d_lutG;
        delete [] tmp_c3d_lutB;
        delete [] tmp_c3d_lutH;
        delete [] tmp_c3d_lutS;
        delete [] tmp_c3d_lutV;
}
//---------------------------------------------------------------------------
//initianl 3D lookup table or initial table value from file
void TC3DForm1::C3Dini()
{
        for(int i = 0; i < TBL_SIZE; i++){
                for(int j = 0; j < TBL_SIZE; j++){
                        for( int k = 0; k < TBL_SIZE ; k++){
                                c3d_lutR[i][j][k] = tbl_val[tbl_s][i];
                                c3d_lutG[i][j][k] = tbl_val[tbl_s][j];
                                c3d_lutB[i][j][k] = tbl_val[tbl_s][k];
                                rgb2hsv(c3d_lutR[i][j][k],c3d_lutG[i][j][k],c3d_lutB[i][j][k],
                                &c3d_lutH[i][j][k],&c3d_lutS[i][j][k],&c3d_lutI[i][j][k],&c3d_lutV[i][j][k]);
                        }
                }
        }
        Show_c3d_SelImg(255, 255, 255);
        Show_c3d_CorImg(255, 255, 255);
        Show_c3d_TblImg(255, 255, 255);
        Show_c3d_SimImg(255, 255, 255);
        refresh_c3d_grid(255,255, 255);
}
//---------------------------------------------------------------------------
void TC3DForm1::Show_c3d_TblImg(double tbl_r, double tbl_g, double tbl_b)
{
        double tbl_h,tbl_s,tbl_i,tbl_v;
        rgb2hsv(tbl_r, tbl_g, tbl_b, &tbl_h, &tbl_s, &tbl_i, &tbl_v);
        tbl_i = (double(int(tbl_i*10)))/10.0;
        tbl_h = (double(int(tbl_h*10)))/10.0;
        tbl_s = (double(int(tbl_s*100)))/100.0;
        tbl_v = (double(int(tbl_v*10)))/10.0;
        lb_c3d_tblR->Caption = IntToStr((int)tbl_r);
        lb_c3d_tblG->Caption = IntToStr((int)tbl_g);
        lb_c3d_tblB->Caption = IntToStr((int)tbl_b);
        lb_c3d_tblH->Caption = FloatToStr(tbl_h);
        lb_c3d_tblS->Caption = FloatToStr(tbl_s);
        lb_c3d_tblI->Caption = FloatToStr(tbl_i);
        lb_c3d_tblV->Caption = FloatToStr(tbl_v);

        Graphics ::TBitmap *TmpBitmap;
        TmpBitmap=new Graphics::TBitmap();
        TmpBitmap->Width = Img_c3d_tbl->Width;
        TmpBitmap->Height = Img_c3d_tbl->Height;
        TmpBitmap->Canvas->Brush->Color = (TColor)RGB(tbl_r, tbl_g, tbl_b);
        TmpBitmap->Canvas->Rectangle(0,0,TmpBitmap->Width,TmpBitmap->Height);
        Img_c3d_tbl->Canvas->Draw(0,0,TmpBitmap);

        delete TmpBitmap;
}
//---------------------------------------------------------------------------
void TC3DForm1::Show_c3d_SelImg(double sel_r, double sel_g, double sel_b)
{
        double sel_h,sel_s,sel_i,sel_v;
        rgb2hsv(sel_r, sel_g, sel_b, &sel_h, &sel_s, &sel_i, &sel_v);
        sel_i = (double(int(sel_i*10)))/10.0;
        sel_h = (double(int(sel_h*10)))/10.0;
        sel_s = (double(int(sel_s*100)))/100.0;
        sel_v = (double(int(sel_v*10)))/10.0;
        lb_c3d_selR->Caption = IntToStr((int)sel_r);
        lb_c3d_selG->Caption = IntToStr((int)sel_g);
        lb_c3d_selB->Caption = IntToStr((int)sel_b);
        lb_c3d_selH->Caption = FloatToStr(sel_h);
        lb_c3d_selS->Caption = FloatToStr(sel_s);
        lb_c3d_selI->Caption = FloatToStr(sel_i);
        lb_c3d_selV->Caption = FloatToStr(sel_v);

        Graphics ::TBitmap *TmpBitmap;
        TmpBitmap=new Graphics::TBitmap();
        TmpBitmap->Width = Img_c3d_sel->Width;
        TmpBitmap->Height = Img_c3d_sel->Height;
        TmpBitmap->Canvas->Brush->Color =(TColor) RGB(sel_r, sel_g, sel_b);
        TmpBitmap->Canvas->Rectangle(0,0,TmpBitmap->Width,TmpBitmap->Height);
        Img_c3d_sel->Canvas->Draw(0,0,TmpBitmap);

        delete TmpBitmap;
}
//--------------------------------------------------------------------------
void __fastcall TC3DForm1::btn_c3d_load_imgClick(TObject *Sender)
{
        if(!OpenDialog1->Execute())
                return;
        String Fpath = OpenDialog1->FileName;
        Img_3DLUT->Picture->LoadFromFile(Fpath.c_str());
        edt_show_h->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_c3d_simClick(TObject *Sender)
{
        C3D_SimualteForm = new TC3D_SimualteForm(this);
        btn_c3d_sim->Enabled = false;
        int x = Img_3DLUT->Picture->Width;
        int y = Img_3DLUT->Picture->Height;

        int color;
        Graphics ::TBitmap *TmpBitmap;
        TmpBitmap=new Graphics::TBitmap();
        TmpBitmap->Width = x;
        TmpBitmap->Height = y;
        //c3d_tmp_tbl_save();
        if(PageC_c3d_adj->TabIndex == 0){  //rgb adjust
                cal_c3d_rgb(true);
        }else if(PageC_c3d_adj->TabIndex == 1){    //hsv adjust
                /*if(rg_c3d_hsv_mode->ItemIndex==1){        //method 2
                        //c3d_6axisAdj_h(true);
                        //c3d_6axisAdj_s(true);
                        //c3d_6axisAdj_v(true);
                }else */
                if(rg_c3d_hsv_mode->ItemIndex==0)   //method 1
                        c3d_hsvBase_adj(true);
                else if(rg_c3d_hsv_mode->ItemIndex==2){   //method 3
                        c3d_MixAdj_h(true);
                        //c3d_MixAdj_s(true);
                        //c3d_MixAdj_v(true);
                }else if(rg_c3d_hsv_mode->ItemIndex==3){        //method 4
                        c3d_hsv_FixGain(true);
                }
        }
        //double Y[15][11];
        for(int i = 0; i < x; i++)
                for(int j = 0; j < y; j++){
                        color = Img_3DLUT->Canvas->Pixels[i][j];
                        if(color==-1)
                                color = 0;

                        double r,g,b, r_new, g_new, b_new;
                        b = color/65536;
                        g = color/256%256;
                        r = color%256;
                        C3Dsim(r,g,b,&r_new,&g_new,&b_new);
                        C3D_SimualteForm->Image1->Canvas->Pixels[i][j] = (TColor)RGB(r_new,g_new,b_new);
                }

        C3D_SimualteForm->lb_hsv_adj_h->Caption = IntToStr(GetH_val());
        C3D_SimualteForm->lb_hsv_adj_s->Caption = IntToStr(GetS_val());
        C3D_SimualteForm->lb_hsv_adj_v->Caption = IntToStr(GetV_val());
        delete TmpBitmap;
        c3d_scrollbar_reset();
        btn_c3d_sim->Enabled = true;
        C3D_SimualteForm->Show();
        /*
        if(!SaveDialog1->Execute()){
                return;
        }

        String Fpath = SaveDialog1->FileName;
        if(Fpath==NULL)
                return;

        FILE* fptr = fopen (Fpath.c_str(),"w");
        for(int i = 0; i < 15; i++)
                fprintf(fptr,"%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
                Y[i][0],Y[i][1],Y[i][2],Y[i][3],Y[i][4],Y[i][5],Y[i][6],Y[i][7],Y[i][8],Y[i][9],Y[i][10]);
        fclose(fptr);  */
        //C3D_SimualteForm->Image2->Picture->SaveToFile("dif_r.bmp");
        //C3D_SimualteForm->Image3->Picture->SaveToFile("dif_g.bmp");
        //C3D_SimualteForm->Image4->Picture->SaveToFile("dif_b.bmp");
}
//----------------------------------------------------------------------------

void TC3DForm1::c3d_scrollbar_reset()
{
        sb_c3d_rgb_dis->Position = 0;
        sb_c3d_rgb_r->Position = 800;
        sb_c3d_rgb_g->Position = 800;
        sb_c3d_rgb_b->Position = 800;
        sb_c3d_hsv_h->Position = 500;
        sb_c3d_hsv_s->Position = 1000;
        sb_c3d_hsv_v->Position = 500;
        sb_c3d_hsv_i->Position = 100;
        sb_c3d_HSVBase_h->Position = sb_c3d_HSVBase_h->Max/2;
        sb_c3d_HSVBase_s->Position = sb_c3d_HSVBase_s->Max/2;
        sb_c3d_HSVBase_v->Position = sb_c3d_HSVBase_v->Max/2;
        sb_c3d_HSVBase_i->Position = sb_c3d_HSVBase_i->Max/2;
}
//----------------------------------------------------------------------------
bool TC3DForm1::c3d_lutArrange()
{
        int idx = 0;
        for(int k = 0; k < TBL_SIZE; k+=2)
                for(int j = 0; j < TBL_SIZE; j+=2)
                        for(int i = 0; i < TBL_SIZE; i+=2){
                                c3d_r[1][idx] = c3d_lutR[i][j][k]*Ratio;
                                c3d_g[1][idx] = c3d_lutG[i][j][k]*Ratio;
                                c3d_b[1][idx] = c3d_lutB[i][j][k]*Ratio;
                                c3d_r[0][idx] = tbl_val[tbl_s][i];
                                c3d_g[0][idx] = tbl_val[tbl_s][j];
                                c3d_b[0][idx] = tbl_val[tbl_s][k];
                                idx++;
                        }

        for(int k = 0; k <TBL_SIZE; k+=2)
                for(int j = 0; j <TBL_SIZE; j+=2)
                        for(int i = 1; i <TBL_SIZE-1; i+=2){
                                c3d_r[1][idx] = c3d_lutR[i][j][k]*Ratio;
                                c3d_g[1][idx] = c3d_lutG[i][j][k]*Ratio;
                                c3d_b[1][idx] = c3d_lutB[i][j][k]*Ratio;
                                c3d_r[0][idx] = tbl_val[tbl_s][i];
                                c3d_g[0][idx] = tbl_val[tbl_s][j];
                                c3d_b[0][idx] = tbl_val[tbl_s][k];
                                idx++;
                        }

        for(int k = 0; k <TBL_SIZE; k+=2)
                for(int j = 1; j <TBL_SIZE-1; j+=2)
                         for(int i = 0; i <TBL_SIZE; i+=2){
                                c3d_r[1][idx] = c3d_lutR[i][j][k]*Ratio;
                                c3d_g[1][idx] = c3d_lutG[i][j][k]*Ratio;
                                c3d_b[1][idx] = c3d_lutB[i][j][k]*Ratio;
                                c3d_r[0][idx] = tbl_val[tbl_s][i];
                                c3d_g[0][idx] = tbl_val[tbl_s][j];
                                c3d_b[0][idx] = tbl_val[tbl_s][k];
                                idx++;
                         }

        for(int k = 0; k <TBL_SIZE; k+=2)
                for(int j = 1; j <TBL_SIZE-1; j+=2)
                        for(int i = 1; i <TBL_SIZE-1; i+=2){
                                c3d_r[1][idx] = c3d_lutR[i][j][k]*Ratio;
                                c3d_g[1][idx] = c3d_lutG[i][j][k]*Ratio;
                                c3d_b[1][idx] = c3d_lutB[i][j][k]*Ratio;
                                c3d_r[0][idx] = tbl_val[tbl_s][i];
                                c3d_g[0][idx] = tbl_val[tbl_s][j];
                                c3d_b[0][idx] = tbl_val[tbl_s][k];
                                idx++;
                        }

        for(int k = 1; k <TBL_SIZE-1; k+=2)
                for(int j = 0; j <TBL_SIZE; j+=2)
                        for(int i = 0; i <TBL_SIZE; i+=2){
                                c3d_r[1][idx] = c3d_lutR[i][j][k]*Ratio;
                                c3d_g[1][idx] = c3d_lutG[i][j][k]*Ratio;
                                c3d_b[1][idx] = c3d_lutB[i][j][k]*Ratio;
                                c3d_r[0][idx] = tbl_val[tbl_s][i];
                                c3d_g[0][idx] = tbl_val[tbl_s][j];
                                c3d_b[0][idx] = tbl_val[tbl_s][k];
                                idx++;
                        }

        for(int k = 1; k <TBL_SIZE-1; k+=2)
                for(int j = 0; j <TBL_SIZE; j+=2)
                        for(int i = 1; i <TBL_SIZE-1; i+=2){
                                c3d_r[1][idx] = c3d_lutR[i][j][k]*Ratio;
                                c3d_g[1][idx] = c3d_lutG[i][j][k]*Ratio;
                                c3d_b[1][idx] = c3d_lutB[i][j][k]*Ratio;
                                c3d_r[0][idx] = tbl_val[tbl_s][i];
                                c3d_g[0][idx] = tbl_val[tbl_s][j];
                                c3d_b[0][idx] = tbl_val[tbl_s][k];
                                idx++;
                        }

        for(int k = 1; k <TBL_SIZE-1; k+=2)
                for(int j = 1; j <TBL_SIZE-1; j+=2)
                         for(int i = 0; i <TBL_SIZE; i+=2){
                                c3d_r[1][idx] = c3d_lutR[i][j][k]*Ratio;
                                c3d_g[1][idx] = c3d_lutG[i][j][k]*Ratio;
                                c3d_b[1][idx] = c3d_lutB[i][j][k]*Ratio;
                                c3d_r[0][idx] = tbl_val[tbl_s][i];
                                c3d_g[0][idx] = tbl_val[tbl_s][j];
                                c3d_b[0][idx] = tbl_val[tbl_s][k];
                                idx++;
                         }

        for(int k = 1; k <TBL_SIZE-1; k+=2)
                for(int j = 1; j <TBL_SIZE-1; j+=2)
                        for(int i = 1; i <TBL_SIZE-0; i+=2){
                                c3d_r[1][idx] = c3d_lutR[i][j][k]*Ratio;
                                c3d_g[1][idx] = c3d_lutG[i][j][k]*Ratio;
                                c3d_b[1][idx] = c3d_lutB[i][j][k]*Ratio;
                                c3d_r[0][idx] = tbl_val[tbl_s][i];
                                c3d_g[0][idx] = tbl_val[tbl_s][j];
                                c3d_b[0][idx] = tbl_val[tbl_s][k];
                                idx++;
                        }
        return 1;
}
//---------------------------------------------------------------------------
void TC3DForm1::c3d_tmp_tbl_save()
{
        String Fpath = "tmp_tbl.txt";
        if(Fpath==NULL)
                return;
        FILE* fptr = fopen (Fpath.c_str(),"w");

        c3d_lutArrange();
        fprintf(fptr,"C3D_LUT\nRin\tGin\tBin\tRout\tGout\tBout\tH\tS\tV\tI\n");
        double h,s, in, v;
        for(int i = 0; i < total_len; i++){
                fprintf(fptr,"%d\t%d\t%d\t%d\t%d\t%d\t",c3d_r[0][i],c3d_g[0][i],
                c3d_b[0][i], c3d_r[1][i],c3d_g[1][i],c3d_b[1][i]);
                rgb2hsv(c3d_r[1][i],c3d_g[1][i],c3d_b[1][i],&h,&s,&in,&v);
                fprintf(fptr,"%2.2f\t%2.2f\t%2.2f\t%2.2f\n",h,s,v,in);
        }
        fclose(fptr);
        BitBtn_c3d_undo->Enabled = true;

        /*
        FILE* fptr = fopen("tmp_tbl.txt","w");
        fprintf(fptr, "R\tG\tB\tH\tS\tI\tV\n");
        for(int i = 0; i < 9; i++)
                for(int j = 0; j < 9; j++)
                        for(int k = 0; k < 9; k++){
                                fprintf(fptr, "%f\t%f\t%f\t%f\t%f\t%f\t%f\n",c3d_lutR[i][j][k],
                                c3d_lutG[i][j][k],c3d_lutB[i][j][k],c3d_lutH[i][j][k],c3d_lutS[i][j][k],
                                c3d_lutI[i][j][k],c3d_lutV[i][j][k]);
        }
        fclose(fptr);
        */
}

//----------------------------------------------------------------------------

//------------------------------------------------------------------------

void TC3DForm1::cal_c3d_rgb(bool flg_wri)
{
        int d = (sb_c3d_rgb_dis->Position);
        int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
        int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
        int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);
        double r_gain = double(sb_c3d_rgb_r->Position-800)/Ratio;
        double g_gain = double(sb_c3d_rgb_g->Position-800)/Ratio;
        double b_gain = double(sb_c3d_rgb_b->Position-800)/Ratio;
        double ratio;

        for(int i = 0; i < TBL_SIZE; i++){
	        for(int j = 0; j < TBL_SIZE; j++){
		        for(int k = 0; k < TBL_SIZE; k++){
			        tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
        			tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
	        		tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
		        }
                }
        }

        int tmp_i, tmp_j, tmp_k;
        if(d == 1){     //choose distance = 1
                for(int i_r = idx_r; i_r <= idx_r+1; i_r++){
                        for(int i_g = idx_g; i_g <= idx_g+1; i_g++){
                                for(int i_b = idx_b; i_b <= idx_b+1; i_b++){
                                        tmp_c3d_lutR[i_r][i_g][i_b] += r_gain;
                                        tmp_c3d_lutG[i_r][i_g][i_b] += g_gain;
                                        tmp_c3d_lutB[i_r][i_g][i_b] += b_gain;

                                        if(tmp_c3d_lutR[i_r][i_g][i_b]>256-1.0/Ratio)
                                                tmp_c3d_lutR[i_r][i_g][i_b] = 256-1.0/Ratio;
                                        else if(tmp_c3d_lutR[i_r][i_g][i_b]<0)
                                                tmp_c3d_lutR[i_r][i_g][i_b] = 0;

                                        if(tmp_c3d_lutG[i_r][i_g][i_b]>256-1.0/Ratio)
                                                tmp_c3d_lutG[i_r][i_g][i_b] = 256-1.0/Ratio;
                                        else if(tmp_c3d_lutG[i_r][i_g][i_b]<0)
                                                tmp_c3d_lutG[i_r][i_g][i_b] = 0;

                                        if(tmp_c3d_lutB[i_r][i_g][i_b]>256-1.0/Ratio)
                                                tmp_c3d_lutB[i_r][i_g][i_b] = 256-1.0/Ratio;
                                        else if(tmp_c3d_lutB[i_r][i_g][i_b]<0)
                                                tmp_c3d_lutB[i_r][i_g][i_b] = 0;
                                }
                        }
                }
        }else if (d >= 2){      //choose distance more than 2
                double rat;
                for(int i =(d)*(-1); i <= d; i++){
                        tmp_i = idx_r+i;
                        if(tmp_i>=0 & tmp_i<=TBL_SIZE-1){
                                for(int j =(d)*(-1); j <= d; j++){
                                        tmp_j = idx_g+j;
                                        if(tmp_j>=0 & tmp_j<=TBL_SIZE-1){
                                                for(int k =(d)*(-1); k <= d; k++){
                                                        tmp_k = idx_b+k;
                                                        if(tmp_k>=0 & tmp_k<=TBL_SIZE-1){
                                                                //c3d_Aratio(i,j,k,&rat,d);
                                                                ratio = 1 - sqrt(double(i*i+j*j+k*k)/3)/d;
                                                                //ratio = 1-rat/d;
                                                                if(ratio>0){
                                                                        tmp_c3d_lutR[tmp_i][tmp_j][tmp_k] += ratio*r_gain;
                                                                        tmp_c3d_lutG[tmp_i][tmp_j][tmp_k] += ratio*g_gain;
                                                                        tmp_c3d_lutB[tmp_i][tmp_j][tmp_k] += ratio*b_gain;
                                                                        if(tmp_c3d_lutR[tmp_i][tmp_j][tmp_k]>256-1.0/Ratio)
                                                                                tmp_c3d_lutR[tmp_i][tmp_j][tmp_k] = 256-1.0/Ratio;
                                                                        else if(tmp_c3d_lutR[tmp_i][tmp_j][tmp_k]<0)
                                                                                tmp_c3d_lutR[tmp_i][tmp_j][tmp_k] = 0;
                                                                        if(tmp_c3d_lutG[tmp_i][tmp_j][tmp_k]>256-1.0/Ratio)
                                                                                tmp_c3d_lutG[tmp_i][tmp_j][tmp_k] = 256-1.0/Ratio;
                                                                        else if(tmp_c3d_lutG[tmp_i][tmp_j][tmp_k]<0)
                                                                                tmp_c3d_lutG[tmp_i][tmp_j][tmp_k] = 0;
                                                                        if(tmp_c3d_lutB[tmp_i][tmp_j][tmp_k]>256-1.0/Ratio)
                                                                                tmp_c3d_lutB[tmp_i][tmp_j][tmp_k] = 256-1.0/Ratio;
                                                                        else if(tmp_c3d_lutB[tmp_i][tmp_j][tmp_k]<0)
                                                                                tmp_c3d_lutB[tmp_i][tmp_j][tmp_k] = 0;
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                }
        }

        if(flg_wri==true){
                for(int i = 0; i < TBL_SIZE; i++)
                        for(int j = 0; j < TBL_SIZE; j++)
                                for(int k = 0; k < TBL_SIZE; k++){
                                        c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
                                        c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
                                        c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
                                }
        }

        double cor_r, cor_g, cor_b, cor_h, cor_s, cor_i, cor_v;
        cor_r = (double)tmp_c3d_lutR[idx_r][idx_g][idx_b];
        cor_g = (double)tmp_c3d_lutG[idx_r][idx_g][idx_b];
        cor_b = (double)tmp_c3d_lutB[idx_r][idx_g][idx_b];

        if(cor_r>=256)
                cor_r = 256-1.0/Ratio;
        if(cor_g>=256)
                cor_g = 256-1.0/Ratio;
        if(cor_b>=256)
                cor_b = 256-1.0/Ratio;

        Show_c3d_CorImg(cor_r, cor_g, cor_b);
        double r = StrToFloat(lb_c3d_selR->Caption);
        double g = StrToFloat(lb_c3d_selG->Caption);
        double b = StrToFloat(lb_c3d_selB->Caption);
        double sim_r, sim_g, sim_b;
        C3Dsim_t(r, g, b, &sim_r, &sim_g, &sim_b);
        if(sim_r>=256)
                sim_r = 256-1.0/Ratio;
        if(sim_g>=256)
                sim_g = 256-1.0/Ratio;
        if(sim_b>=256)
                sim_b = 256-1.0/Ratio;
        Show_c3d_SimImg(sim_r, sim_g, sim_b);
        refresh_c3d_grid_t(sim_r,sim_g,sim_b);
}

//---------------------------------------------------------------------------

void TC3DForm1::C3Dsim_t(double r, double g, double b,double* r_new, double* g_new, double* b_new)
{//techehedral
        int idx_r, idx_g, idx_b;
        double v_r[2], v_g[2], v_b[2];

        for(int i = 0; i <= TBL_SIZE-2; i++){
                if( r>=tbl_val[tbl_s][i] && r <=tbl_val[tbl_s][i+1]){
                        v_r[0] = tbl_val[tbl_s][i];
                        v_r[1] = tbl_val[tbl_s][i+1];
                        idx_r = i;
                        break;
                }
        }
        for(int i = 0; i <= TBL_SIZE-2; i++){
                if( g>=tbl_val[tbl_s][i] && g <=tbl_val[tbl_s][i+1]){
                        v_g[0] = tbl_val[tbl_s][i];
                        v_g[1] = tbl_val[tbl_s][i+1];
                        idx_g = i;
                        break;
                }
        }
        for(int i = 0; i <= TBL_SIZE-2; i++){
                if( b>=tbl_val[tbl_s][i] && b <=tbl_val[tbl_s][i+1]){
                        v_b[0] = tbl_val[tbl_s][i];
                        v_b[1] = tbl_val[tbl_s][i+1];
                        idx_b = i;
                        break;
                }
        }

        double P[2][2][2][3];
        // p[][][][0]=> red  p[][][][1]=> green  p[][][][2]=> blue
        for(int i = 0; i < 2; i++)
                for(int j = 0; j < 2; j++)
                        for(int k = 0; k < 2; k++){
                                P[i][j][k][0] = tmp_c3d_lutR[idx_r+i][idx_g+j][idx_b+k];
                                P[i][j][k][1] = tmp_c3d_lutG[idx_r+i][idx_g+j][idx_b+k];
                                P[i][j][k][2] = tmp_c3d_lutB[idx_r+i][idx_g+j][idx_b+k];
                        }

        double dlt_x = (r-v_r[0])/(v_r[1]-v_r[0]);
        double dlt_y = (g-v_g[0])/(v_g[1]-v_g[0]);
        double dlt_z = (b-v_b[0])/(v_b[1]-v_b[0]);

        if( interpol == true){
        double C1[3], C2[3], C3[3];

        if(dlt_x>=dlt_y && dlt_y>dlt_z){        //T1
                for(int c = 0; c < 3; c++){
                        C1[c] = P[1][0][0][c]-P[0][0][0][c];
                        C2[c] = P[1][1][0][c]-P[1][0][0][c];
                        C3[c] = P[1][1][1][c]-P[1][1][0][c];
                }
        }else if(dlt_x>dlt_z && dlt_z>=dlt_y){  //T2
                for(int c = 0; c < 3; c++){
                        C1[c] = P[1][0][0][c]-P[0][0][0][c];
                        C2[c] = P[1][1][1][c]-P[1][0][1][c];
                        C3[c] = P[1][0][1][c]-P[1][0][0][c];
                }
        }else if(dlt_z>=dlt_x && dlt_x>=dlt_y){ //T3
                for(int c = 0; c < 3; c++){
                        C1[c] = P[1][0][1][c]-P[0][0][1][c];
                        C2[c] = P[1][1][1][c]-P[1][0][1][c];
                        C3[c] = P[0][0][1][c]-P[0][0][0][c];
                }
        }else if(dlt_y>dlt_x && dlt_x>dlt_z){   //T4
                for(int c = 0; c < 3; c++){
                        C1[c] = P[1][1][0][c]-P[0][1][0][c];
                        C2[c] = P[0][1][0][c]-P[0][0][0][c];
                        C3[c] = P[1][1][1][c]-P[1][1][0][c];
                }
        }else if(dlt_y>dlt_z && dlt_z>=dlt_x){  //T5
                for(int c = 0; c < 3; c++){
                        C1[c] = P[1][1][1][c]-P[0][1][1][c];
                        C2[c] = P[0][1][0][c]-P[0][0][0][c];
                        C3[c] = P[0][1][1][c]-P[0][1][0][c];
                }
        }else if(dlt_z>=dlt_y && dlt_y>dlt_x){  //T6
                for(int c = 0; c < 3; c++){
                        C1[c] = P[1][1][1][c]-P[0][1][1][c];
                        C2[c] = P[0][1][1][c]-P[0][0][1][c];
                        C3[c] = P[0][0][1][c]-P[0][0][0][c];
                }
        }

        double P_[3];
        for(int c = 0; c < 3 ;c++){
                P_[c] = P[0][0][0][c]+C1[c]*dlt_x+C2[c]*dlt_y+C3[c]*dlt_z;
        }

        *r_new = P_[0];
        *g_new = P_[1];
        *b_new = P_[2];
        }
        else{   //trilinear
        	double i[2][3], j[2][3], w[2][3];

		for(int c = 0; c < 3; c++){
				i[0][c] = P[0][0][0][c]*(1-dlt_x)+P[1][0][0][c]*dlt_x;
				i[1][c] = P[0][1][0][c]*(1-dlt_x)+P[1][1][0][c]*dlt_x;
				j[0][c] = P[0][0][1][c]*(1-dlt_x)+P[1][0][1][c]*dlt_x;
				j[1][c] = P[0][1][1][c]*(1-dlt_x)+P[1][1][1][c]*dlt_x;
		}
		for(int c = 0; c < 3; c++){
				w[0][c] = i[0][c]*(1-dlt_y)+i[1][c]*dlt_y;
				w[1][c] = j[0][c]*(1-dlt_y)+j[1][c]*dlt_y;
		}
		*r_new  = w[0][0]*(1-dlt_z)+w[1][0]*dlt_z;
		*g_new  = w[0][1]*(1-dlt_z)+w[1][1]*dlt_z;
		*b_new  = w[0][2]*(1-dlt_z)+w[1][2]*dlt_z;
        }
}

//---------------------------------------------------------------------------
void TC3DForm1::C3Dsim(double r, double g, double b, double* r_new, double* g_new, double* b_new)
{
        int idx_r, idx_g, idx_b;
        double v_r[2], v_g[2], v_b[2];
        for(int i = 0; i <= TBL_SIZE-2; i++){
                if( r>=tbl_val[tbl_s][i] && r <=tbl_val[tbl_s][i+1]){
                        v_r[0] = tbl_val[tbl_s][i];
                        v_r[1] = tbl_val[tbl_s][i+1];
                        idx_r = i;
                        break;
                }
        }
        for(int i = 0; i <= TBL_SIZE-2; i++){
                if( g>=tbl_val[tbl_s][i] && g <=tbl_val[tbl_s][i+1]){
                        v_g[0] = tbl_val[tbl_s][i];
                        v_g[1] = tbl_val[tbl_s][i+1];
                        idx_g = i;
                        break;
                }
        }
        for(int i = 0; i <= TBL_SIZE-2; i++){
                if( b>=tbl_val[tbl_s][i] && b <=tbl_val[tbl_s][i+1]){
                        v_b[0] = tbl_val[tbl_s][i];
                        v_b[1] = tbl_val[tbl_s][i+1];
                        idx_b = i;
                        break;
                }
        }

        double P[2][2][2][3];
        // p000[0]=> red  p000[0]=> green  p000[0]=> blue
        for(int i = 0; i < 2; i++)
                for(int j = 0; j < 2; j++)
                        for(int k = 0; k < 2; k++){
                                P[i][j][k][0] = c3d_lutR[idx_r+i][idx_g+j][idx_b+k];
                                P[i][j][k][1] = c3d_lutG[idx_r+i][idx_g+j][idx_b+k];
                                P[i][j][k][2] = c3d_lutB[idx_r+i][idx_g+j][idx_b+k];
                        }

        double dlt_x = (r-v_r[0])/(v_r[1]-v_r[0]);
        double dlt_y = (g-v_g[0])/(v_g[1]-v_g[0]);
        double dlt_z = (b-v_b[0])/(v_b[1]-v_b[0]);

        if( interpol == true){     //techehedral
        double C1[3], C2[3], C3[3];

        if(dlt_x>=dlt_y && dlt_y>dlt_z){        //T1
                for(int c = 0; c < 3; c++){
                        C1[c] = P[1][0][0][c]-P[0][0][0][c];
                        C2[c] = P[1][1][0][c]-P[1][0][0][c];
                        C3[c] = P[1][1][1][c]-P[1][1][0][c];
                }
        }else if(dlt_x>dlt_z && dlt_z>=dlt_y){  //T2
                for(int c = 0; c < 3; c++){
                        C1[c] = P[1][0][0][c]-P[0][0][0][c];
                        C2[c] = P[1][1][1][c]-P[1][0][1][c];
                        C3[c] = P[1][0][1][c]-P[1][0][0][c];
                }
        }else if(dlt_z>=dlt_x && dlt_x>=dlt_y){ //T3
                for(int c = 0; c < 3; c++){
                        C1[c] = P[1][0][1][c]-P[0][0][1][c];
                        C2[c] = P[1][1][1][c]-P[1][0][1][c];
                        C3[c] = P[0][0][1][c]-P[0][0][0][c];
                }
        }else if(dlt_y>dlt_x && dlt_x>dlt_z){   //T4
                for(int c = 0; c < 3; c++){
                        C1[c] = P[1][1][0][c]-P[0][1][0][c];
                        C2[c] = P[0][1][0][c]-P[0][0][0][c];
                        C3[c] = P[1][1][1][c]-P[1][1][0][c];
                }
        }else if(dlt_y>dlt_z && dlt_z>=dlt_x){  //T5
                for(int c = 0; c < 3; c++){
                        C1[c] = P[1][1][1][c]-P[0][1][1][c];
                        C2[c] = P[0][1][0][c]-P[0][0][0][c];
                        C3[c] = P[0][1][1][c]-P[0][1][0][c];
                }
        }else if(dlt_z>=dlt_y && dlt_y>dlt_x){  //T6
                for(int c = 0; c < 3; c++){
                        C1[c] = P[1][1][1][c]-P[0][1][1][c];
                        C2[c] = P[0][1][1][c]-P[0][0][1][c];
                        C3[c] = P[0][0][1][c]-P[0][0][0][c];
                }
        }

        double P_[3];
        for(int c = 0; c < 3 ;c++){
                P_[c] = P[0][0][0][c]+C1[c]*dlt_x+C2[c]*dlt_y+C3[c]*dlt_z;
        }

        *r_new = P_[0];
        *g_new = P_[1];
        *b_new = P_[2];
        }
        else{   //trilinear
        	double i[2][3], j[2][3], w[2][3];

		for(int c = 0; c < 3; c++){
				i[0][c] = P[0][0][0][c]*(1-dlt_x)+P[1][0][0][c]*dlt_x;
				i[1][c] = P[0][1][0][c]*(1-dlt_x)+P[1][1][0][c]*dlt_x;
				j[0][c] = P[0][0][1][c]*(1-dlt_x)+P[1][0][1][c]*dlt_x;
				j[1][c] = P[0][1][1][c]*(1-dlt_x)+P[1][1][1][c]*dlt_x;
		}
		for(int c = 0; c < 3; c++){
				w[0][c] = i[0][c]*(1-dlt_y)+i[1][c]*dlt_y;
				w[1][c] = j[0][c]*(1-dlt_y)+j[1][c]*dlt_y;
		}
		*r_new  = w[0][0]*(1-dlt_z)+w[1][0]*dlt_z;
		*g_new  = w[0][1]*(1-dlt_z)+w[1][1]*dlt_z;
		*b_new  = w[0][2]*(1-dlt_z)+w[1][2]*dlt_z;
        }
}
//------------------------------------------------------------------------------
void TC3DForm1::Show_c3d_CorImg(double cor_r, double cor_g, double cor_b)
{
        double cor_h,cor_s,cor_i,cor_v;
        rgb2hsv(cor_r, cor_g, cor_b, &cor_h, &cor_s, &cor_i, &cor_v);
        cor_i = (double(int(cor_i*10)))/10.0;
        cor_h = (double(int(cor_h*10)))/10.0;
        cor_s = (double(int(cor_s*100)))/100.0;
        cor_v = (double(int(cor_v*10)))/10.0;
        lb_c3d_corR->Caption = IntToStr((int)cor_r);
        lb_c3d_corG->Caption = IntToStr((int)cor_g);
        lb_c3d_corB->Caption = IntToStr((int)cor_b);
        lb_c3d_corH->Caption = FloatToStr(cor_h);
        lb_c3d_corS->Caption = FloatToStr(cor_s);
        lb_c3d_corI->Caption = FloatToStr(cor_i);
        lb_c3d_corV->Caption = FloatToStr(cor_v);

        Graphics ::TBitmap *TmpBitmap;
        TmpBitmap=new Graphics::TBitmap();
        TmpBitmap->Width = Img_c3d_cor->Width;
        TmpBitmap->Height = Img_c3d_cor->Height;
        TmpBitmap->Canvas->Brush->Color = (TColor)RGB(cor_r, cor_g, cor_b);
        TmpBitmap->Canvas->Rectangle(0,0,TmpBitmap->Width,TmpBitmap->Height);
        Img_c3d_cor->Canvas->Draw(0,0,TmpBitmap);

        delete TmpBitmap;
}
//---------------------------------------------------------------------------
void TC3DForm1::Show_c3d_SimImg(double sim_r, double sim_g, double sim_b)
{
        double sim_h,sim_s,sim_i,sim_v;
        rgb2hsv(sim_r, sim_g, sim_b, &sim_h, &sim_s, &sim_i, &sim_v);
        sim_i = (double(int(sim_i*10)))/10.0;
        sim_h = (double(int(sim_h*10)))/10.0;
        sim_s = (double(int(sim_s*100)))/100.0;
        sim_v = (double(int(sim_v*10)))/10.0;
        lb_c3d_simR->Caption = IntToStr((int)sim_r);
        lb_c3d_simG->Caption = IntToStr((int)sim_g);
        lb_c3d_simB->Caption = IntToStr((int)sim_b);
        lb_c3d_simH->Caption = FloatToStr(sim_h);
        lb_c3d_simS->Caption = FloatToStr(sim_s);
        lb_c3d_simI->Caption = FloatToStr(sim_i);
        lb_c3d_simV->Caption = FloatToStr(sim_v);

        Graphics ::TBitmap *TmpBitmap;
        TmpBitmap=new Graphics::TBitmap();
        TmpBitmap->Width = Img_c3d_sim->Width;
        TmpBitmap->Height = Img_c3d_sim->Height;
        TmpBitmap->Canvas->Brush->Color = (TColor)RGB(sim_r, sim_g, sim_b);
        TmpBitmap->Canvas->Rectangle(0,0,TmpBitmap->Width,TmpBitmap->Height);
        Img_c3d_sim->Canvas->Draw(0,0,TmpBitmap);

        delete TmpBitmap;
}

//---------------------------------------------------------------------------
void TC3DForm1::refresh_c3d_grid(double r, double g, double b)
{
        int idx = TBL_SIZE-1;
        c3d_grid(0,r,g,b);
        c3d_grid(1,c3d_lutR[idx][0][0],c3d_lutG[idx][0][0],c3d_lutB[idx][0][0]);
        c3d_grid(2,c3d_lutR[idx][idx][0],c3d_lutG[idx][idx][0],c3d_lutB[idx][idx][0]);
        c3d_grid(3,c3d_lutR[0][idx][0],c3d_lutG[0][idx][0],c3d_lutB[0][idx][0]);
        c3d_grid(4,c3d_lutR[0][idx][idx],c3d_lutG[0][idx][idx],c3d_lutB[0][idx][idx]);
        c3d_grid(5,c3d_lutR[0][0][idx],c3d_lutG[0][0][idx],c3d_lutB[0][0][idx]);
        c3d_grid(6,c3d_lutR[idx][0][idx],c3d_lutG[idx][0][idx],c3d_lutB[idx][0][idx]);
}
//----------------------------------------------------------------------------
void TC3DForm1::refresh_c3d_grid_t(double r, double g, double b)
{
        int idx = TBL_SIZE-1;
        c3d_grid(0,r,g,b);
        c3d_grid(1,tmp_c3d_lutR[idx][0][0],tmp_c3d_lutG[idx][0][0],tmp_c3d_lutB[idx][0][0]);
        c3d_grid(2,tmp_c3d_lutR[idx][idx][0],tmp_c3d_lutG[idx][idx][0],tmp_c3d_lutB[idx][idx][0]);
        c3d_grid(3,tmp_c3d_lutR[0][idx][0],tmp_c3d_lutG[0][idx][0],tmp_c3d_lutB[0][idx][0]);
        c3d_grid(4,tmp_c3d_lutR[0][idx][idx],tmp_c3d_lutG[0][idx][idx],tmp_c3d_lutB[0][idx][idx]);
        c3d_grid(5,tmp_c3d_lutR[0][0][idx],tmp_c3d_lutG[0][0][idx],tmp_c3d_lutB[0][0][idx]);
        c3d_grid(6,tmp_c3d_lutR[idx][0][idx],tmp_c3d_lutG[idx][0][idx],tmp_c3d_lutB[idx][0][idx]);
}
//------------------------------------------------------------------------------
void TC3DForm1::c3d_grid(int c, int r, int g, int b)
{
        double h, s, v, in;
        rgb2hsv(r,g,b,&h, &s, &in, &v);
        sg_c3d_hsvi->Cells[0][c] = h;
        sg_c3d_hsvi->Cells[1][c] = s;
        sg_c3d_hsvi->Cells[2][c] = v;
}
//------------------------------------------------------------------------------

void __fastcall TC3DForm1::rg_c3d_interplClick(TObject *Sender)
{
        if(rg_c3d_interpl->ItemIndex==0)
                interpol = true;
        else
                interpol = false;
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::rg_c3d_TblSizeClick(TObject *Sender)
{
        delete_array();
        tbl_s = rg_c3d_TblSize->ItemIndex;
        if(tbl_s == 0)
                TBL_SIZE = 9;
        else if(tbl_s == 1)
                TBL_SIZE = 7;
        else if(tbl_s == 2)
                TBL_SIZE = 17;
        else if(tbl_s == 3)
                TBL_SIZE = 33;
        cube_dis = 256/(TBL_SIZE-1);
        if(TBL_SIZE==7)
                cube_dis = 32;
        total_len = TBL_SIZE*TBL_SIZE*TBL_SIZE;
        new_array();
        btn_c3d_resetClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::rb_c3d_pointClick(TObject *Sender)
{
        //point color mode to adjust color
        if(c3d_detailadjust == true)
                for(int i = 0; i < TBL_SIZE; i++)
                        for(int j = 0; j < TBL_SIZE; j++)
                                for(int k = 0; k < TBL_SIZE; k++){
                                        hsv2rgb(c3d_lutH[i][j][k],c3d_lutS[i][j][k],c3d_lutV[i][j][k],
                                        &c3d_lutR[i][j][k],&c3d_lutG[i][j][k],&c3d_lutB[i][j][k]);
                                }
        c3d_detailadjust = false;
        c3d_scrollbar_reset();
}
//---------------------------------------------------------------------------
void __fastcall TC3DForm1::rb_c3d_colorClick(TObject *Sender)
{
        c3d_scrollbar_reset();
        //HSI mode to adjust color
        double in;
        if(c3d_detailadjust == false)
                for(int i = 0; i <TBL_SIZE; i++)
                        for(int j = 0; j <TBL_SIZE; j++)
                                for(int k = 0; k <TBL_SIZE; k++){
                                        rgb2hsv(c3d_lutR[i][j][k],c3d_lutG[i][j][k],c3d_lutB[i][j][k],
                                        &c3d_lutH[i][j][k],&c3d_lutS[i][j][k],&in,&c3d_lutV[i][j][k]);
                                }
        c3d_detailadjust = true;
        int idx_r,idx_g,idx_b;
        if(rb_c3d_r->Checked == true){
                idx_r = TBL_SIZE-1;
                idx_g = 0;
                idx_b = 0;
        }else if(rb_c3d_y->Checked == true){
                idx_r = TBL_SIZE-1;
                idx_g = TBL_SIZE-1;
                idx_b = 0;
        }else if(rb_c3d_g->Checked == true){
                idx_r = 0;
                idx_g = TBL_SIZE-1;
                idx_b = 0;
        }else if(rb_c3d_c->Checked == true){
                idx_r = 0;
                idx_g = TBL_SIZE-1;
                idx_b = TBL_SIZE-1;
        }else if(rb_c3d_b->Checked == true){
                idx_r = 0;
                idx_g = 0;
                idx_b = TBL_SIZE-1;
        }else if(rb_c3d_m->Checked == true){
                idx_r = TBL_SIZE-1;
                idx_g = 0;
                idx_b = TBL_SIZE-1;
        }

        lb_c3d_tbl_ir->Caption = idx_r;
        lb_c3d_tbl_ig->Caption = idx_g;
        lb_c3d_tbl_ib->Caption = idx_b;

        double r = c3d_lutR[idx_r][idx_g][idx_b];
        double g = c3d_lutG[idx_r][idx_g][idx_b];
        double b = c3d_lutB[idx_r][idx_g][idx_b];

        Show_c3d_SelImg(r, g, b);
        Show_c3d_CorImg(r, g, b);
        Show_c3d_TblImg(r, g, b);
        Show_c3d_SimImg(r, g, b);
}
//---------------------------------------------------------------------------
void __fastcall TC3DForm1::btn_c3d_resetClick(TObject *Sender)
{
        c3d_tmp_tbl_save();
                
        sb_c3d_rgb_dis->Position = 0;
        sb_c3d_rgb_r->Position = 800;
        sb_c3d_rgb_g->Position = 800;
        sb_c3d_rgb_b->Position = 800;
        sb_c3d_hsv_h->Position = 500;
        sb_c3d_hsv_s->Position = 1000;
        sb_c3d_hsv_v->Position = 500;
        sb_c3d_hsv_i->Position = 100;
        sb_c3d_HSVBase_h->Position = sb_c3d_HSVBase_h->Max/2;
        sb_c3d_HSVBase_s->Position = sb_c3d_HSVBase_s->Max/2;
        sb_c3d_HSVBase_v->Position = sb_c3d_HSVBase_v->Max/2;
        sb_c3d_HSVBase_i->Position = sb_c3d_HSVBase_i->Max/2;
        C3Dini();
        rb_c3d_point->Checked = false;
        rb_c3d_r->Checked = false;
        rb_c3d_g->Checked = false;
        rb_c3d_b->Checked = false;
        rb_c3d_c->Checked = false;
        rb_c3d_y->Checked = false;
        rb_c3d_m->Checked = false;
        //cal_c3d_rgb(false);
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_c3d_loadClick(TObject *Sender)
{
        if(!OpenDialog1->Execute())
                return;
        String Fpath = OpenDialog1->FileName;
        char* buffer = Load_File(Fpath);

        int tbl_tl = pow(TBL_SIZE,3);

        int idx_r, idx_g, idx_b;
        char* str[11];          int str_l[11];
        str[0]="C3D_LUT";       str_l[0]=7;
        str[1]="Rin";           str_l[1]=4;
        str[2]="Gin";           str_l[2]=4;
        str[3]="Bin";           str_l[3]=4;
        str[4]="Rout";          str_l[4]=4;
        str[5]="Gout";          str_l[5]=4;
        str[6]="Bout";          str_l[6]=4;
        str[7]="H";             str_l[7]=1;
        str[8]="S";             str_l[8]=1;
        str[9]="V";             str_l[9]=1;
        str[10]="I";            str_l[10]=1;

        char* pch = strtok (buffer,"\n\t");
        for(int i = 0; i < 11; i++){
                while (memcmp(pch,str[i],str_l[i])!=0){
                        if(pch == NULL){
                                ShowMessage("Can't open c3d table file.");
                                return;
                        }
                        pch = strtok (NULL,"\n\t");
                }
        }
        int c = 0;
        pch = strtok (NULL,"\n\t");
        while (c < tbl_tl*10 && pch!=NULL){
                if(pch == NULL){
                        ShowMessage("Can't open c3d table file.");
                        return;        //資料中的data缺少
                }
                if(c%10 == 0)
                        idx_r = (int)ceil((double)StrToInt((AnsiString)pch)/cube_dis);
                else if(c%10 == 1)
                        idx_g = (int)ceil((double)StrToInt((AnsiString)pch)/cube_dis);
                else if(c%10 == 2)
                        idx_b = (int)ceil((double)StrToInt((AnsiString)pch)/cube_dis);
                else if(c%10 == 3)
                        c3d_lutR[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch)/Ratio;
                else if(c%10 == 4)
                        c3d_lutG[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch)/Ratio;
                else if(c%10 == 5)
                        c3d_lutB[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch)/Ratio;
                else if(c%10 == 6)
                        c3d_lutH[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch);
                else if(c%10 == 7)
                        c3d_lutS[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch);
                else if(c%10 == 8)
                        c3d_lutV[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch);
                else if(c%10 == 9)
                        c3d_lutI[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch);

                pch = strtok (NULL,"\n\t");
                c++;
       }
       delete [] buffer;
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_c3d_saveClick(TObject *Sender)
{
        if(!SaveDialog1->Execute()){
                return;
        }

        String Fpath = SaveDialog1->FileName/*+".txt"*/;
        if(Fpath==NULL)
                return;
        btn_c3d_save->Enabled = false;
        FILE* fptr = fopen (Fpath.c_str(),"w");

        c3d_lutArrange();
        fprintf(fptr,"C3D_LUT\nRin\tGin\tBin\tRout\tGout\tBout\tH\tS\tV\tI\n");
        int tbl_tl = pow(TBL_SIZE,3);
        double h,s, in, v;
        for(int i = 0; i < tbl_tl; i++){
                fprintf(fptr,"%d\t%d\t%d\t%d\t%d\t%d\t",c3d_r[0][i],c3d_g[0][i],
                c3d_b[0][i],c3d_r[1][i],c3d_g[1][i],c3d_b[1][i]);
                rgb2hsv(c3d_r[1][i]/Ratio,c3d_g[1][i]/Ratio,c3d_b[1][i]/Ratio,&h,&s,&in,&v);
                fprintf(fptr,"%2.2f\t%2.2f\t%2.2f\t%2.2f\n",h,s,v,in);
        }
        fclose(fptr);

        sb_c3d_rgb_dis->Position = 0;
        sb_c3d_rgb_r->Position = 800;
        sb_c3d_rgb_g->Position = 800;
        sb_c3d_rgb_b->Position = 800;
        sb_c3d_hsv_h->Position = 500;
        sb_c3d_hsv_s->Position = 1000;
        sb_c3d_hsv_v->Position = 500;
        sb_c3d_hsv_i->Position = 100;
        sb_c3d_HSVBase_h->Position = sb_c3d_HSVBase_h->Max/2;
        sb_c3d_HSVBase_s->Position = sb_c3d_HSVBase_s->Max/2;
        sb_c3d_HSVBase_v->Position = sb_c3d_HSVBase_v->Max/2;
        sb_c3d_HSVBase_i->Position = sb_c3d_HSVBase_i->Max/2;
        btn_c3d_save->Enabled = true;
}
//---------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
//    HSV adjust method 2
//    c3d_6axisAdj_h(bool flag), c3d_6axisAdj_s(bool flag), c3d_6axisAdj_v(bool flag)
//-----------------------------------------------------------------------------------
/*
void c3d_6axisAdj_r(int type, double dif_p, double dif_n, double gain, double tmp_c3d_lutR[9][9][9], double tmp_c3d_lutG[9][9][9], double tmp_c3d_lutB[9][9][9])
{
        double r_gain[9][9] = {0}, g_gain[9][9] = {0}, b_gain[9][9] = {0};
        double h, s, v, in;
        double tmp_r, tmp_g, tmp_b;
        double ratio;

        if(type == 1){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                rgb2hsv(c3d_lutR[i][j][j],c3d_lutG[i][j][j],c3d_lutB[i][j][j],&h, &s, &in, &v);
                                h += gain;
                                h = fmod(h+360, 360);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[i][j][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[i][j][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[i][j][j];
                        }
                }
        }else if(type == 2){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                rgb2hsv(c3d_lutR[i][j][j],c3d_lutG[i][j][j], c3d_lutB[i][j][j],&h, &s, &in, &v);
                                s += s*gain;
                                s = (s<0?0:s);
                                s = (s>1?1:s);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[i][j][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[i][j][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[i][j][j];
                        }
                }
        }else if(type == 3){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                //hsv
                                rgb2hsv(c3d_lutR[i][j][j],c3d_lutG[i][j][j],c3d_lutB[i][j][j],&h,&s,&in,&v);
                                v += v*gain*s;
                                v = (v<0?0:v);
                                v = (v>=256?256-1.0/Ratio:v);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[i][j][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[i][j][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[i][j][j];
                        }
                }
        }
        double avg;

        for(int i = 0; i < 9; i++){
                for(int j =0; j < 9; j++){
                        for(int k =0; k < 9; k++){
                                if(i==j && j==k)
                                        break;
                                rgb2hsv(i*32,j*32,k*32,&h,&s,&in,&v);
                                if(h<dif_p || h>360+dif_n){
                                        avg = double(j+k)/2;
                                        ratio = (h<180?1-h/dif_p:1-(360-h)/dif_n*(-1));
                                        double intpart, fractpart;
                                        fractpart = modf (avg , &intpart);
                                        int intval = (int)intpart;
                                        tmp_c3d_lutR[i][j][k] += ratio*(r_gain[i][intval]*(1-fractpart)+r_gain[i][intval+1]*fractpart);
                                        tmp_c3d_lutG[i][j][k] += ratio*(g_gain[i][intval]*(1-fractpart)+g_gain[i][intval+1]*fractpart);
                                        tmp_c3d_lutB[i][j][k] += ratio*(b_gain[i][intval]*(1-fractpart)+b_gain[i][intval+1]*fractpart);
                                        fix_val(&tmp_c3d_lutR[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutG[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutB[i][j][k],256-1.0/Ratio);
                                }
                        }
                }
        }

}

//------------------------------------------------------------------------
void c3d_6axisAdj_g(int type, double dif_p, double dif_n,double gain, double tmp_c3d_lutR[9][9][9], double tmp_c3d_lutG[9][9][9], double tmp_c3d_lutB[9][9][9])
{
        double r_gain[9][9] = {0}, g_gain[9][9] = {0}, b_gain[9][9] = {0};
        double h, s, v, in;
        double tmp_r, tmp_g, tmp_b;
        double ratio;

        if(type == 1){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                rgb2hsv(c3d_lutR[j][i][j],c3d_lutG[j][i][j],c3d_lutB[j][i][j],&h,&s,&in,&v);
                                h += gain;
                                h = fmod(h+360, 360);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][i][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][i][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][i][j];
                        }
                }
        }else if(type == 2){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                rgb2hsv(c3d_lutR[j][i][j],c3d_lutG[j][i][j], c3d_lutB[j][i][j],&h,&s,&in,&v);
                                s += s*gain;
                                s = (s<0?0:s);
                                s = (s>1?1:s);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][i][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][i][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][i][j];
                        }
                }
        }else if(type == 3){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                //hsv
                                rgb2hsv(c3d_lutR[j][i][j],c3d_lutG[j][i][j],c3d_lutB[j][i][j],&h,&s,&in,&v);
                                v += v*gain*s;
                                v = (v<0?0:v);
                                v = (v>=256?256-1.0/Ratio:v);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][i][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][i][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][i][j];
                        }
                }
        }
        double avg;
        for(int i = 0; i < 9; i++){
                for(int j =0; j < 9; j++){
                        for(int k =0; k < 9; k++){
                                rgb2hsv(i*32,j*32,k*32,&h,&s,&in,&v);
                                if(h>120+dif_n && h<120+dif_p){
                                        avg = double(i+k)/2;
                                        ratio = (h>120?1-(h-120)/dif_p:1-(120-h)/dif_n*(-1));
                                        double intpart, fractpart;
                                        fractpart = modf (avg , &intpart);
                                        int intval = (int)intpart;
                                        tmp_c3d_lutR[i][j][k] += ratio*(r_gain[j][intval]*(1-fractpart)+r_gain[j][intval+1]*fractpart);
                                        tmp_c3d_lutG[i][j][k] += ratio*(g_gain[j][intval]*(1-fractpart)+g_gain[j][intval+1]*fractpart);
                                        tmp_c3d_lutB[i][j][k] += ratio*(b_gain[j][intval]*(1-fractpart)+b_gain[j][intval+1]*fractpart);
                                        fix_val(&tmp_c3d_lutR[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutG[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutB[i][j][k],256-1.0/Ratio);
                                }
                        }
                }
        }
}
//---------------------------------------------------------------------

void c3d_6axisAdj_b(int type, double dif_p, double dif_n,double gain, double tmp_c3d_lutR[9][9][9], double tmp_c3d_lutG[9][9][9], double tmp_c3d_lutB[9][9][9])
{
        double r_gain[9][9] = {0}, g_gain[9][9] = {0}, b_gain[9][9] = {0};
        double h, s, v, in;
        double tmp_r, tmp_g, tmp_b;
        double ratio;

        if(type == 1){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                rgb2hsv(c3d_lutR[j][j][i],c3d_lutG[j][j][i],c3d_lutB[j][j][i],&h,&s,&in,&v);
                                h += gain;
                                h = fmod(h+360, 360);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][j][i];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][j][i];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][j][i];
                        }
                }
        }else if(type == 2){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                rgb2hsv(c3d_lutR[j][j][i],c3d_lutG[j][j][i],c3d_lutB[j][j][i],&h,&s,&in,&v);
                                s += s*gain;
                                s = (s<0?0:s);
                                s = (s>1?1:s);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][j][i];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][j][i];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][j][i];
                        }
                }
        }else if(type == 3){
                for(int i = 0; i < 9; i++){
                        for(int  j = 0; j < i; j++){
                                //hsv
                                rgb2hsv(c3d_lutR[j][j][i],c3d_lutG[j][j][i],c3d_lutB[j][j][i],&h,&s,&in,&v);
                                v += v*gain*s;
                                v = (v<0?0:v);
                                v = (v>=256?256-1.0/Ratio:v);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][j][i];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][j][i];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][j][i];
                        }
                }
        }
        double avg;
        for(int i = 0; i < 9; i++){
                for(int j =0; j < 9; j++){
                        for(int k =0; k < 9; k++){
                                rgb2hsv(i*32,j*32,k*32,&h,&s,&in,&v);
                                if(h>240+dif_n && h<240+dif_p){
                                        ratio = (h>240?1-(h-240)/dif_p:1-(240-h)/dif_n*(-1));
                                        avg = double(i+j)/2;
                                        double intpart, fractpart;
                                        fractpart = modf (avg , &intpart);
                                        int intval = (int)intpart;
                                        tmp_c3d_lutR[i][j][k] += ratio*(r_gain[k][intval]*(1-fractpart)+r_gain[k][intval+1]*fractpart);
                                        tmp_c3d_lutG[i][j][k] += ratio*(g_gain[k][intval]*(1-fractpart)+g_gain[k][intval+1]*fractpart);
                                        tmp_c3d_lutB[i][j][k] += ratio*(b_gain[k][intval]*(1-fractpart)+b_gain[k][intval+1]*fractpart);
                                        fix_val(&tmp_c3d_lutR[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutG[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutB[i][j][k],256-1.0/Ratio);
                                }
                        }
                }
        }
}

//------------------------------------------------------------------------
void c3d_6axisAdj_c(int type, double dif_p, double dif_n,double gain, double tmp_c3d_lutR[9][9][9], double tmp_c3d_lutG[9][9][9], double tmp_c3d_lutB[9][9][9])
{
        double r_gain[9][9] = {0}, g_gain[9][9] = {0}, b_gain[9][9] = {0};
        double h, s, v, in;
        double tmp_r, tmp_g, tmp_b;
        double ratio;

        if(type == 1){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                rgb2hsv(c3d_lutR[i][j][j],c3d_lutG[i][j][j],c3d_lutB[i][j][j],&h,&s,&in,&v);
                                h += gain;
                                h = fmod(h+360, 360);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[i][j][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[i][j][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[i][j][j];
                        }
                }
        }else if(type == 2){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                rgb2hsv(c3d_lutR[i][j][j],c3d_lutG[i][j][j],c3d_lutB[i][j][j],&h,&s,&in,&v);
                                s += s*gain;
                                s = (s<0?0:s);
                                s = (s>1?1:s);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[i][j][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[i][j][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[i][j][j];
                        }
                }
        }else if(type == 3){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                //hsv
                                rgb2hsv(c3d_lutR[i][j][j],c3d_lutG[i][j][j],c3d_lutB[i][j][j],&h,&s,&in,&v);
                                v += v*gain*s;
                                v = (v<0?0:v);
                                v = (v>=256?256-1.0/Ratio:v);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[i][j][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[i][j][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[i][j][j];
                        }
                }
        }

        double avg;
        for(int i = 0; i < 9; i++){
                for(int j =0; j < 9; j++){
                        for(int k =0; k < 9; k++){
                                rgb2hsv(i*32,j*32,k*32,&h,&s,&in,&v);
                                if(h>180+dif_n && h< 180+dif_p){
                                        ratio = (h>180?1-(h-180)/dif_p:1-(180-h)/dif_n*(-1));
                                        avg = double(j+k)/2;
                                        double intpart, fractpart;
                                        fractpart = modf (avg , &intpart);
                                        int intval = (int)intpart;
                                        tmp_c3d_lutR[i][j][k] += ratio*(r_gain[i][intval]*(1-fractpart)+r_gain[i][intval+1]*fractpart);
                                        tmp_c3d_lutG[i][j][k] += ratio*(g_gain[i][intval]*(1-fractpart)+g_gain[i][intval+1]*fractpart);
                                        tmp_c3d_lutB[i][j][k] += ratio*(b_gain[i][intval]*(1-fractpart)+b_gain[i][intval+1]*fractpart);
                                        fix_val(&tmp_c3d_lutR[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutG[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutB[i][j][k],256-1.0/Ratio);
                                }
                        }
                }
        }
}
//------------------------------------------------------------------------

void c3d_6axisAdj_m(int type, double dif_p, double dif_n, double gain, double tmp_c3d_lutR[9][9][9], double tmp_c3d_lutG[9][9][9], double tmp_c3d_lutB[9][9][9])
{
        double r_gain[9][9] = {0}, g_gain[9][9] = {0}, b_gain[9][9] = {0};
        double h, s, v, in;
        double tmp_r, tmp_g, tmp_b;
        double ratio;

        if(type == 1){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                rgb2hsv(c3d_lutR[j][i][j],c3d_lutG[j][i][j],c3d_lutB[j][i][j],&h,&s,&in,&v);
                                h += gain;
                                h = fmod(h+360, 360);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][i][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][i][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][i][j];
                        }
                }
        }else if(type == 2){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                rgb2hsv(c3d_lutR[j][i][j],c3d_lutG[j][i][j],c3d_lutB[j][i][j],&h,&s,&in,&v);
                                s += s*gain;
                                s = (s<0?0:s);
                                s = (s>1?1:s);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][i][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][i][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][i][j];
                        }
                }
        }else if(type == 3){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                //hsv
                                rgb2hsv(c3d_lutR[j][i][j],c3d_lutG[j][i][j],c3d_lutB[j][i][j],&h,&s,&in,&v);
                                v += v*gain*s;
                                v = (v<0?0:v);
                                v = (v>=256?256-1.0/Ratio:v);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][i][j];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][i][j];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][i][j];
                        }
                }
        }
        double avg;
        for(int i = 0; i < 9; i++){
                for(int j =0; j < 9; j++){
                        for(int k =0; k < 9; k++){
                                rgb2hsv(i*32,j*32,k*32,&h,&s,&in,&v);
                                if(h>300+dif_n && h< 300+dif_p){
                                        ratio = (h>300?1-(h-300)/dif_p:1-(300-h)/dif_n*(-1));
                                        avg = double(i+k)/2;
                                        double intpart, fractpart;
                                        fractpart = modf (avg , &intpart);
                                        int intval = (int)intpart;
                                        tmp_c3d_lutR[i][j][k] += ratio*(r_gain[j][intval]*(1-fractpart)+r_gain[j][intval+1]*fractpart);
                                        tmp_c3d_lutG[i][j][k] += ratio*(g_gain[j][intval]*(1-fractpart)+g_gain[j][intval+1]*fractpart);
                                        tmp_c3d_lutB[i][j][k] += ratio*(b_gain[j][intval]*(1-fractpart)+b_gain[j][intval+1]*fractpart);
                                        fix_val(&tmp_c3d_lutR[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutG[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutB[i][j][k],256-1.0/Ratio);
                                }
                        }
                }
        }
}
//------------------------------------------------------------------------
void c3d_6axisAdj_y(int type,double dif_p, double dif_n,double gain, double tmp_c3d_lutR[9][9][9], double tmp_c3d_lutG[9][9][9], double tmp_c3d_lutB[9][9][9])
{
        double r_gain[9][9] = {0}, g_gain[9][9] = {0}, b_gain[9][9] = {0};
        double h, s, v, in;
        double tmp_r, tmp_g, tmp_b;
        double ratio;

        if(type == 1){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                rgb2hsv(c3d_lutR[j][j][i],c3d_lutG[j][j][i],c3d_lutB[j][j][i],&h,&s,&in,&v);
                                h += gain;
                                h = fmod(h+360, 360);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][j][i];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][j][i];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][j][i];
                        }
                }
        }else if(type == 2){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                //rgb2hsi(c3d_lutR[j][j][i]/power_dump,c3d_lutG[j][j][i]/power_dump,
                                //c3d_lutB[j][j][i]/power_dump,&h,&s,&in);
                                rgb2hsv(c3d_lutR[j][j][i],c3d_lutG[j][j][i],c3d_lutB[j][j][i],&h,&s,&in,&v);
                                s += s*gain;
                                s = (s<0?0:s);
                                s = (s>1?1:s);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                //hsi2rgb(h, s, in, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][j][i];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][j][i];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][j][i];
                        }
                }
        }else if(type == 3){
                for(int i = 7; i >= 0; i--){
                        for(int  j = 8; j > i; j--){
                                //hsv
                                rgb2hsv(c3d_lutR[j][j][i],c3d_lutG[j][j][i],c3d_lutB[j][j][i],&h,&s,&in,&v);
                                v += v*gain*s;
                                v = (v<0?0:v);
                                v = (v>=256?256-1.0/Ratio:v);
                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                r_gain[i][j] = tmp_r-c3d_lutR[j][j][i];
                                g_gain[i][j] = tmp_g-c3d_lutG[j][j][i];
                                b_gain[i][j] = tmp_b-c3d_lutB[j][j][i];
                        }
                }
        }
        double avg;
        for(int i = 0; i < 9; i++){
                for(int j =0; j < 9; j++){
                        for(int k =0; k < 9; k++){
                                rgb2hsv(i*32,j*32,k*32,&h,&s,&in,&v);
                                //rgb2h(i*32,j*32,k*32,&h);
                                if(h>60+dif_n && h<60+dif_p){
                                        ratio = (h>60?1-(h-60)/dif_p:1-(60-h)/dif_n*(-1));
                                        avg = double(i+j)/2;
                                        double intpart, fractpart;
                                        fractpart = modf (avg , &intpart);
                                        int intval = (int)intpart;
                                        tmp_c3d_lutR[i][j][k] += ratio*(r_gain[k][intval]*(1-fractpart)+r_gain[k][intval+1]*fractpart);
                                        tmp_c3d_lutG[i][j][k] += ratio*(g_gain[k][intval]*(1-fractpart)+g_gain[k][intval+1]*fractpart);
                                        tmp_c3d_lutB[i][j][k] += ratio*(b_gain[k][intval]*(1-fractpart)+b_gain[k][intval+1]*fractpart);
                                        fix_val(&tmp_c3d_lutR[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutG[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutB[i][j][k],256-1.0/Ratio);
                                }
                        }
                }
        }
}
//----------------------------------------------------------------------------
void TC3DForm1::c3d_6axisAdj_h(bool flag)
{
        double h_gain = double(sb_c3d_HSVBase_h->Position-sb_c3d_HSVBase_h->Max/2)/10;
        double dif_n = double(sb_c3d_HSVBase_hdn->Position-sb_c3d_HSVBase_hdn->Max)/10;
        double dif_p = double(sb_c3d_HSVBase_hdp->Position)/10;

        double tmp_c3d_lutR[9][9][9],tmp_c3d_lutG[9][9][9],tmp_c3d_lutB[9][9][9];

        for(int i = 0; i < 9; i ++)
                for(int j = 0; j < 9; j ++)
                        for(int k = 0; k < 9; k ++){
                                tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
                                tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
                                tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
                        }
        double h, s, in, v;
        double r=0, g=0, b=0;
        if(cb_c3d_HSVBase_h_rt->Checked == true){    //global color rotate
                for(int i = 0; i < 9; i ++)
                        for(int j = 0; j < 9; j ++)
                                for(int k = 0; k < 9; k ++){
                                        rgb2hsv(tmp_c3d_lutR[i][j][k],tmp_c3d_lutG[i][j][k],tmp_c3d_lutB[i][j][k],&h,&s,&in,&v);
                                        h+=h_gain;
                                        h=fmod(h+360,360);
                                        hsv2rgb(h,s,v,&tmp_c3d_lutR[i][j][k],&tmp_c3d_lutG[i][j][k],&tmp_c3d_lutB[i][j][k]);
                                }
        }else{      //six color adjust
                if(rb_c3d_r->Checked == true){  //red
                        c3d_6axisAdj_r(1,dif_p,dif_n,h_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_g->Checked == true){    //green
                        c3d_6axisAdj_g(1,dif_p,dif_n,h_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_b->Checked == true){    //blue
                        c3d_6axisAdj_b(1,dif_p,dif_n,h_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_c->Checked == true){    //cyan
                        c3d_6axisAdj_c(1,dif_p,dif_n,h_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_y->Checked == true){    //yellow
                        c3d_6axisAdj_y(1,dif_p,dif_n,h_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_m->Checked == true){    //magenta
                        c3d_6axisAdj_m(1,dif_p,dif_n,h_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }
        }

        if(rb_c3d_r->Checked == true){
                r = tmp_c3d_lutR[8][0][0];
                g = tmp_c3d_lutG[8][0][0];
                b = tmp_c3d_lutB[8][0][0];
        }else if(rb_c3d_g->Checked == true){
                r = tmp_c3d_lutR[0][8][0];
                g = tmp_c3d_lutG[0][8][0];
                b = tmp_c3d_lutB[0][8][0];
        }else if(rb_c3d_b->Checked == true){
                r = tmp_c3d_lutR[0][0][8];
                g = tmp_c3d_lutG[0][0][8];
                b = tmp_c3d_lutB[0][0][8];
        }else if(rb_c3d_c->Checked == true){
                r = tmp_c3d_lutR[0][8][8];
                g = tmp_c3d_lutG[0][8][8];
                b = tmp_c3d_lutB[0][8][8];
        }else if(rb_c3d_y->Checked == true){
                r = tmp_c3d_lutR[8][8][0];
                g = tmp_c3d_lutG[8][8][0];
                b = tmp_c3d_lutB[8][8][0];
        }else if(rb_c3d_m->Checked == true){
                r = tmp_c3d_lutR[8][0][8];
                g = tmp_c3d_lutG[8][0][8];
                b = tmp_c3d_lutB[8][0][8];
        }
        Show_c3d_SimImg(r,g,b);
        refresh_c3d_grid(r,g,b,tmp_c3d_lutR,tmp_c3d_lutG,tmp_c3d_lutB);

        if(flag==true){
                for(int i = 0; i < 9; i++)
                        for(int j = 0; j < 9; j++)
                                for(int k = 0; k < 9; k++){
                                        c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
                                        c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
                                        c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
                                }
        }
}
//---------------------------------------------------------------------------
void TC3DForm1::c3d_6axisAdj_s(bool flag)
{
        double c = StrToFloat(edt_c3d_satC->Text);
        double s_gain = (double)GetS_val()/100/c;
        double dif_n = double(sb_c3d_HSVBase_sdn->Position-500)/10;
        double dif_p = double(sb_c3d_HSVBase_sdp->Position)/10;

        double tmp_c3d_lutR[9][9][9],tmp_c3d_lutG[9][9][9],tmp_c3d_lutB[9][9][9];

        for(int i = 0; i < 9; i ++)
                for(int j = 0; j < 9; j ++)
                        for(int k = 0; k < 9; k ++){
                                tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
                                tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
                                tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
                        }
        double h, s, in, v;
        double r=0, g=0, b=0;
        if(cb_c3d_HSVBase_s_ge->Checked == true){
                for(int i = 0; i < 9; i ++)
                        for(int j = 0; j < 9; j ++)
                                for(int k = 0; k < 9; k ++){
                                        rgb2hsv(tmp_c3d_lutR[i][j][k],tmp_c3d_lutG[i][j][k],tmp_c3d_lutB[i][j][k],&h,&s,&in,&v);
                                        s+=s_gain*s;
                                        s = (s<0?0:s);
                                        s = (s>1?1:s);
                                        hsv2rgb(h,s,v,&tmp_c3d_lutR[i][j][k],&tmp_c3d_lutG[i][j][k],&tmp_c3d_lutB[i][j][k]);
                                }
        }else{
                if(rb_c3d_r->Checked == true){
                        c3d_6axisAdj_r(2,dif_p,dif_n,s_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_g->Checked == true){
                        c3d_6axisAdj_g(2,dif_p,dif_n,s_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_b->Checked == true){
                        c3d_6axisAdj_b(2,dif_p,dif_n,s_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_c->Checked == true){
                        c3d_6axisAdj_c(2,dif_p,dif_n,s_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_y->Checked == true){
                        c3d_6axisAdj_y(2,dif_p,dif_n,s_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_m->Checked == true){
                        c3d_6axisAdj_m(2,dif_p,dif_n,s_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }
                Show_c3d_SimImg(r,g,b);
        }
        if(rb_c3d_r->Checked == true){
                r = tmp_c3d_lutR[8][0][0];
                g = tmp_c3d_lutG[8][0][0];
                b = tmp_c3d_lutB[8][0][0];
        }else if(rb_c3d_g->Checked == true){
                r = tmp_c3d_lutR[0][8][0];
                g = tmp_c3d_lutG[0][8][0];
                b = tmp_c3d_lutB[0][8][0];
        }else if(rb_c3d_b->Checked == true){
                r = tmp_c3d_lutR[0][0][8];
                g = tmp_c3d_lutG[0][0][8];
                b = tmp_c3d_lutB[0][0][8];
        }else if(rb_c3d_c->Checked == true){
                r = tmp_c3d_lutR[0][8][8];
                g = tmp_c3d_lutG[0][8][8];
                b = tmp_c3d_lutB[0][8][8];
        }else if(rb_c3d_y->Checked == true){
                r = tmp_c3d_lutR[8][8][0];
                g = tmp_c3d_lutG[8][8][0];
                b = tmp_c3d_lutB[8][8][0];
        }else if(rb_c3d_m->Checked == true){
                r = tmp_c3d_lutR[8][0][8];
                g = tmp_c3d_lutG[8][0][8];
                b = tmp_c3d_lutB[8][0][8];
        }
        Show_c3d_SimImg(r,g,b);
        refresh_c3d_grid(r,g,b,tmp_c3d_lutR,tmp_c3d_lutG,tmp_c3d_lutB);
        if(flag==true){
                for(int i = 0; i < 9; i++)
                        for(int j = 0; j < 9; j++)
                                for(int k = 0; k < 9; k++){
                                        c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
                                        c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
                                        c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
                                }
        }
}
//------------------------------------------------------------------------
void TC3DForm1::c3d_6axisAdj_v(bool flag)
{
        double c = StrToFloat(edt_c3d_valC->Text);
        double v_gain = double(sb_c3d_HSVBase_v->Position-1000)/1000/c;
        double dif_n = double(sb_c3d_HSVBase_vdn->Position-500)/10;
        double dif_p = double(sb_c3d_HSVBase_vdp->Position)/10;
        double tmp_c3d_lutR[9][9][9],tmp_c3d_lutG[9][9][9],tmp_c3d_lutB[9][9][9];

        for(int i = 0; i < 9; i ++)
                for(int j = 0; j < 9; j ++)
                        for(int k = 0; k < 9; k ++){
                                tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
                                tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
                                tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
                        }
        double h, s, in, v;
        double r=0, g=0, b=0;
        if(cb_c3d_HSVBase_v_ge->Checked == true){
                for(int i = 0; i < 9; i ++)
                        for(int j = 0; j < 9; j ++)
                                for(int k = 0; k < 9; k ++){
                                        rgb2hsv(tmp_c3d_lutR[i][j][k],tmp_c3d_lutG[i][j][k],tmp_c3d_lutB[i][j][k],&h,&s,&in,&v);
                                        v+=v*v_gain*s;
                                        v = (v<0?0:v);
                                        v = (v>=256?256-1.0/Ratio:v);
                                        hsv2rgb(h,s,v,&tmp_c3d_lutR[i][j][k],&tmp_c3d_lutG[i][j][k],&tmp_c3d_lutB[i][j][k]);
                                }
        }else{
                if(rb_c3d_r->Checked == true){
                        c3d_6axisAdj_r(3,dif_p,dif_n,v_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_g->Checked == true){
                        c3d_6axisAdj_g(3,dif_p,dif_n,v_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_b->Checked == true){
                        c3d_6axisAdj_b(3,dif_p,dif_n,v_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_c->Checked == true){
                        c3d_6axisAdj_c(3,dif_p,dif_n,v_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_y->Checked == true){
                        c3d_6axisAdj_y(3,dif_p,dif_n,v_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }else if(rb_c3d_m->Checked == true){
                        c3d_6axisAdj_m(3,dif_p,dif_n,v_gain, tmp_c3d_lutR, tmp_c3d_lutG, tmp_c3d_lutB);
                }
                Show_c3d_SimImg(r,g,b);
        }
        if(rb_c3d_r->Checked == true){
                r = tmp_c3d_lutR[8][0][0];
                g = tmp_c3d_lutG[8][0][0];
                b = tmp_c3d_lutB[8][0][0];
        }else if(rb_c3d_g->Checked == true){
                r = tmp_c3d_lutR[0][8][0];
                g = tmp_c3d_lutG[0][8][0];
                b = tmp_c3d_lutB[0][8][0];
        }else if(rb_c3d_b->Checked == true){
                r = tmp_c3d_lutR[0][0][8];
                g = tmp_c3d_lutG[0][0][8];
                b = tmp_c3d_lutB[0][0][8];
        }else if(rb_c3d_c->Checked == true){
                r = tmp_c3d_lutR[0][8][8];
                g = tmp_c3d_lutG[0][8][8];
                b = tmp_c3d_lutB[0][8][8];
        }else if(rb_c3d_y->Checked == true){
                r = tmp_c3d_lutR[8][8][0];
                g = tmp_c3d_lutG[8][8][0];
                b = tmp_c3d_lutB[8][8][0];
        }else if(rb_c3d_m->Checked == true){
                r = tmp_c3d_lutR[8][0][8];
                g = tmp_c3d_lutG[8][0][8];
                b = tmp_c3d_lutB[8][0][8];
        }
        Show_c3d_SimImg(r,g,b);
        refresh_c3d_grid(r,g,b,tmp_c3d_lutR,tmp_c3d_lutG,tmp_c3d_lutB);

        if(flag==true){
                for(int i = 0; i < 9; i++)
                        for(int j = 0; j < 9; j++)
                                for(int k = 0; k < 9; k++){
                                        c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
                                        c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
                                        c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
                                }
        }
}
*/
/***********************************************
//      methid 1                              //
***********************************************/

void TC3DForm1::c3d_hsv_FixGain_h(double tmp_c3d_lutH[9][9][9])
{
        if(cb_c3d_HSVBase_h_rt->Checked == true){
                double h_gain = double(sb_c3d_HSVBase_h->Position-sb_c3d_HSVBase_h->Max/2)/10;
                for(int i = 0; i < 9; i++)
                        for(int j = 0; j < 9; j++)
                                for(int k = 0; k < 9; k++){
                                        if(c3d_lutH[i][j][k]!=0 || c3d_lutS[i][j][k]!=0 ) //固定灰階
                                                tmp_c3d_lutH[i][j][k] = fmod((c3d_lutH[i][j][k]+h_gain)+360,360);
                                }
                return;
        }

        int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
        int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
        int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);

        double h_gain = double(sb_c3d_HSVBase_h->Position-sb_c3d_HSVBase_h->Max/2)/10;
        if(h_gain==0){
                for(int i = 0; i < TBL_SIZE; i++)
                        for(int j = 0; j < TBL_SIZE; j++)
                                for(int k = 0; k < TBL_SIZE; k++)
                                        tmp_c3d_lutH[i][j][k] = c3d_lutH[i][j][k];
                return;
        }
        double h1,h2;
        double dif_n = double(sb_c3d_HSVBase_hdn->Position-sb_c3d_HSVBase_hdn->Max);
        double dif_p = double(sb_c3d_HSVBase_hdp->Position);
        double low = c3d_lutH[idx_r][idx_g][idx_b]+dif_n;   //負向的diffusion邊界
        double high = c3d_lutH[idx_r][idx_g][idx_b]+dif_p;   //正向的diffusion邊界
        double new_pos_rng, new_neg_rng;
        if(h_gain >0){
                h1 = c3d_lutH[idx_r][idx_g][idx_b];      //使用者調整的h 上界
                h2 = c3d_lutH[idx_r][idx_g][idx_b]-h_gain;             //使用者調整的h 下界
                new_pos_rng = dif_p-h_gain;      //原本做正向diffusion的範圍所要對應到的新範圍
                new_neg_rng = dif_n*(-1); //原本做負向diffusion的範圍所要對應到的新範圍
                dif_n = dif_n+h_gain;
        }else{
                h1 = c3d_lutH[idx_r][idx_g][idx_b]-h_gain;             //使用者調整的h 上界
                h2 = c3d_lutH[idx_r][idx_g][idx_b];      //使用者調整的h 下界
                new_pos_rng = dif_p;      //原本做正向diffusion的範圍所要對應到的新範圍
                new_neg_rng = dif_n*(-1)+h_gain; //原本做負向diffusion的範圍所要對應到的新範圍
                dif_p = dif_p+h_gain;
        }

        double tmp_h;   //對每個hue值(tmp_h)計算diffusion量

        bool Is_dif = false;    //flag recording tmp_h to do diffusion or not
        double ratio, rslt;

        for(int i = 0; i < TBL_SIZE; i++)
                for(int j = 0; j < TBL_SIZE; j++)
                        for(int k = 0; k < TBL_SIZE; k++){
                                Is_dif = false;
                                tmp_h = c3d_lutH[i][j][k];

                                if(low <0 && tmp_h>low+360){
                                        tmp_h -=360;
                                        Is_dif = true;
                                }
                                else if(high>=360 && tmp_h<fmod(high,360)){
                                        tmp_h+=360;
                                        Is_dif = true;
                                }
                                else if(tmp_h>=low && tmp_h<high){
                                        Is_dif = true;
                                }
                                if(Is_dif == true){
                                        if(tmp_h<=h1 && tmp_h>=h2){
                                                rslt = tmp_h+h_gain;
                                        }
                                        else if(tmp_h < h2){
                                                ratio = (tmp_h-low)/dif_n*(-1);
                                                rslt =  ratio * new_neg_rng + low;
                                        }else if(tmp_h > h1){
                                                ratio = (tmp_h-high)/dif_p;
                                                rslt = ratio * new_pos_rng + high;
                                        }
                                        tmp_c3d_lutH[i][j][k] = fmod(rslt + 360, 360);
                                }
                                else{
                                        tmp_c3d_lutH[i][j][k] = c3d_lutH[i][j][k];
                                }
                        }
}

void TC3DForm1::c3d_hsv_FixGain(bool flg_wri)
{
/*       //ouble tmp_c3d_lutH[9][9][9],tmp_c3d_lutS[9][9][9],tmp_c3d_lutV[9][9][9];

        c3d_hsv_FixGain_h(tmp_c3d_lutH);

        //Sat & Value值不動
        for(int i = 0; i < 9; i++)
                for(int j = 0; j < 9; j++)
                        for(int k = 0; k < 9; k++){
                                tmp_c3d_lutS[i][j][k] = c3d_lutS[i][j][k];
                                tmp_c3d_lutV[i][j][k] = c3d_lutV[i][j][k];
                        }
        //Grey level remain original value
        for(int c = 0; c < TBL_SIZE; c++){
                tmp_c3d_lutH[c][c][c] = c3d_lutH[c][c][c];
                tmp_c3d_lutS[c][c][c] = c3d_lutS[c][c][c];
                tmp_c3d_lutV[c][c][c] = c3d_lutV[c][c][c];
        }

        for(int i = 0; i < TBL_SIZE; i++)
                for(int j = 0; j < TBL_SIZE; j++)
                        for(int k = 0; k < TBL_SIZE; k++){
                                hsv2rgb(tmp_c3d_lutH[i][j][k],tmp_c3d_lutS[i][j][k],tmp_c3d_lutV[i][j][k],
                                &tmp_c3d_lutR[i][j][k], &tmp_c3d_lutG[i][j][k], &tmp_c3d_lutB[i][j][k]);
                        }

        if(flg_wri==true){
                for(int i = 0; i < TBL_SIZE; i++)
                        for(int j = 0; j < TBL_SIZE; j++)
                                for(int k = 0; k < TBL_SIZE; k++){
                                        c3d_lutH[i][j][k] = tmp_c3d_lutH[i][j][k];
                                        c3d_lutS[i][j][k] = tmp_c3d_lutS[i][j][k];
                                        c3d_lutV[i][j][k] = tmp_c3d_lutV[i][j][k];
                                        c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
                                        c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
                                        c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
                                }
        }
        int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
        int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
        int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);

        Show_c3d_CorImg(tmp_c3d_lutR[idx_r][idx_g][idx_b], tmp_c3d_lutG[idx_r][idx_g][idx_b],
        tmp_c3d_lutB[idx_r][idx_g][idx_b]);

        double r = StrToFloat(lb_c3d_selR->Caption);
        double g = StrToFloat(lb_c3d_selG->Caption);
        double b = StrToFloat(lb_c3d_selB->Caption);
        double sim_r, sim_g, sim_b;
        C3Dsim_t(r, g, b, &sim_r, &sim_g, &sim_b);
        Show_c3d_SimImg(sim_r, sim_g, sim_b);
        refresh_c3d_grid_t(r,g,b);             */

}
void TC3DForm1::c3d_hsvBase_adj(bool flg_wri)
{
        c3d_HSVBase_h_adj();

        //Sat & Value值不動
        for(int i = 0; i < TBL_SIZE; i++)
                for(int j = 0; j < TBL_SIZE; j++)
                        for(int k = 0; k < TBL_SIZE; k++){
                                tmp_c3d_lutS[i][j][k] = c3d_lutS[i][j][k];
                                tmp_c3d_lutV[i][j][k] = c3d_lutV[i][j][k];
                        }

        c3d_HSVBase_s_adj();
        c3d_HSVBase_v_adj();

        //Grey level remain original value
        for(int c = 0; c < TBL_SIZE; c++){
                tmp_c3d_lutH[c][c][c] = c3d_lutH[c][c][c];
                tmp_c3d_lutS[c][c][c] = c3d_lutS[c][c][c];
                tmp_c3d_lutV[c][c][c] = c3d_lutV[c][c][c];
        }

        for(int i = 0; i < TBL_SIZE; i++)
                for(int j = 0; j < TBL_SIZE; j++)
                        for(int k = 0; k < TBL_SIZE; k++){
                                hsv2rgb(tmp_c3d_lutH[i][j][k],tmp_c3d_lutS[i][j][k],tmp_c3d_lutV[i][j][k],
                                &tmp_c3d_lutR[i][j][k], &tmp_c3d_lutG[i][j][k], &tmp_c3d_lutB[i][j][k]);
                        }

        if(flg_wri==true){
                for(int i = 0; i < TBL_SIZE; i++)
                        for(int j = 0; j < TBL_SIZE; j++)
                                for(int k = 0; k < TBL_SIZE; k++){
                                        c3d_lutH[i][j][k] = tmp_c3d_lutH[i][j][k];
                                        c3d_lutS[i][j][k] = tmp_c3d_lutS[i][j][k];
                                        c3d_lutV[i][j][k] = tmp_c3d_lutV[i][j][k];
                                        c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
                                        c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
                                        c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
                                }
        }
        int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
        int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
        int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);

        Show_c3d_CorImg(tmp_c3d_lutR[idx_r][idx_g][idx_b], tmp_c3d_lutG[idx_r][idx_g][idx_b],
        tmp_c3d_lutB[idx_r][idx_g][idx_b]);

        double r = StrToFloat(lb_c3d_selR->Caption);
        double g = StrToFloat(lb_c3d_selG->Caption);
        double b = StrToFloat(lb_c3d_selB->Caption);
        double sim_r, sim_g, sim_b;
        C3Dsim_t(r, g, b,&sim_r, &sim_g, &sim_b);
        Show_c3d_SimImg(sim_r, sim_g, sim_b);
        refresh_c3d_grid_t(r,g,b);
}
//----------------------------------------------------------------------------


void TC3DForm1::c3d_HSVBase_h_adj()
{
        if(cb_c3d_HSVBase_h_rt->Checked == true){
                double h_gain = (double)GetH_val();
                for(int i = 0; i < TBL_SIZE; i++)
                        for(int j = 0; j < TBL_SIZE; j++)
                                for(int k = 0; k < TBL_SIZE; k++){
                                        if(c3d_lutH[i][j][k]!=0 || c3d_lutS[i][j][k]!=0 ) //固定灰階
                                                tmp_c3d_lutH[i][j][k] = fmod((c3d_lutH[i][j][k]+h_gain)+360,360);
                                }
                return;
        }

        int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
        int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
        int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);

        double h_gain = (double)GetH_val();
        if(h_gain==0){
                for(int i = 0; i < TBL_SIZE; i++)
                        for(int j = 0; j < TBL_SIZE; j++)
                                for(int k = 0; k < TBL_SIZE; k++)
                                        tmp_c3d_lutH[i][j][k] = c3d_lutH[i][j][k];
                return;
        }
        double h = c3d_lutH[idx_r][idx_g][idx_b];       //使用者調整的h
        double dif_n = (double)GetH_NegDif();
        double dif_p = (double)GetH_PosDif();

        double tmp_h;   //對每個hue值(tmp_h)計算diffusion量
        double low = h+dif_n;   //負向的diffusion邊界
        double high = h+dif_p;   //正向的diffusion邊界
        double new_pos_rng = dif_p-h_gain;      //原本做正向diffusion的範圍所要對應到的新範圍
        double new_neg_rng = dif_n*(-1)+h_gain; //原本做負向diffusion的範圍所要對應到的新範圍
        bool Is_dif = false;    //flag recording tmp_h to do diffusion or not
        double ratio, rslt;

        for(int i = 0; i < TBL_SIZE; i++)
                for(int j = 0; j < TBL_SIZE; j++)
                        for(int k = 0; k < TBL_SIZE; k++){
                                Is_dif = false;
                                tmp_h = c3d_lutH[i][j][k];

                                if(low <0 && tmp_h>low+360){
                                        tmp_h -=360;
                                        Is_dif = true;
                                }
                                else if(high>=360 && tmp_h<fmod(high,360)){
                                        tmp_h+=360;
                                        Is_dif = true;
                                }
                                else if(tmp_h>=low && tmp_h<high){
                                        Is_dif = true;
                                }
                                if(Is_dif == true){
                                        if(tmp_h < h){
                                                ratio = (tmp_h-low)/dif_n*(-1);
                                                rslt =  ratio * new_neg_rng + low;
                                        }else if(tmp_h >= h){
                                                ratio = (tmp_h-high)/dif_p;
                                                rslt = ratio * new_pos_rng + high;
                                        }
                                        tmp_c3d_lutH[i][j][k] = fmod(rslt + 360, 360);
                                }
                                else{
                                        tmp_c3d_lutH[i][j][k] = c3d_lutH[i][j][k];
                                }
                        }
}

//---------------------------------------------------------------------------
void  TC3DForm1::c3d_HSVBase_s_adj()
{
        if(cb_c3d_HSVBase_s_ge->Checked == true){
                double c = StrToFloat(edt_c3d_satC->Text);
                double s_gain = (double)GetS_val()/100/c;
                double tmp;
                for(int i = 0; i < TBL_SIZE; i++)
                        for(int j = 0; j < TBL_SIZE; j++)
                                for(int k = 0; k < TBL_SIZE; k++){
                                        if(c3d_lutH[i][j][k]!=0 || c3d_lutS[i][j][k]!=0){//固定灰階
                                                tmp = c3d_lutS[i][j][k]*(s_gain+1);
                                                tmp = (tmp<0?0:tmp);
                                                tmp = (tmp>1?1:tmp);
                                                tmp_c3d_lutS[i][j][k] = tmp;
                                        }
                                }
                return;
        }

        int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
        int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
        int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);

        double c = StrToFloat(edt_c3d_satC->Text);
        double s_gain = (double)GetS_val()/100/c;
        double h = c3d_lutH[idx_r][idx_g][idx_b];
        double dif_n = (double)GetS_NegDif();
        double dif_p = (double)GetS_PosDif();

        /*FILE* fptr = fopen ("change_S.txt","w");
        if(fptr==NULL){
                ShowMessage("can't open sat record file.");
                return;
        } */

        double tmp_h;   //對每個hue值(tmp_h)計算diffusion量
        double low = h+dif_n;   //負向的diffusion邊界
        double high = h+dif_p;   //正向的diffusion邊界
        bool Is_dif = false;    //flag recording tmp_h to do diffusion or not
        double ratio;
        for(int i = 0; i < TBL_SIZE; i++)
                for(int j = 0; j < TBL_SIZE; j++)
                        for(int k = 0; k < TBL_SIZE; k++){
                                Is_dif = false;
                                tmp_h = c3d_lutH[i][j][k];
                                if(low <0 && tmp_h>low+360){
                                        tmp_h -=360;
                                        Is_dif = true;
                                }
                                else if(high>=360 && tmp_h<fmod(high,360)){
                                        tmp_h+=360;
                                        Is_dif = true;
                                }
                                else if(tmp_h>low && tmp_h<high){
                                        Is_dif = true;
                                }
                                if(Is_dif == true){
                                        if(tmp_h < h){
                                                ratio = 1-(h-tmp_h)/dif_n*(-1);
                                        }else if(tmp_h >= h){
                                                ratio = 1-(tmp_h-h)/dif_p;
                                        }
                                        if(ratio>1)
                                                ShowMessage("S ratio >1");
                                        tmp_c3d_lutS[i][j][k] = (ratio * s_gain/c +1)*c3d_lutS[i][j][k];
                                        if(tmp_c3d_lutS[i][j][k] > 1)
                                                tmp_c3d_lutS[i][j][k] = 1;
                                        else if(tmp_c3d_lutS[i][j][k] < 0)
                                                tmp_c3d_lutS[i][j][k] = 0;
                                }else
                                        tmp_c3d_lutS[i][j][k] = c3d_lutS[i][j][k];
                                //if(tmp_h>260 && tmp_h<280)
                                //        ShowMessage("h="+FloatToStr(tmp_h)+"ratio"+FloatToStr(ratio)+"");
                                //fprintf(fptr, "%.2f\t%.2f\n", c3d_lutS[i][j][k],tmp_c3d_lutS[i][j][k]);
                        }
        //fclose(fptr);
}
//------------------------------------------------------------------------

void  TC3DForm1::c3d_HSVBase_v_adj()
{
        if(cb_c3d_HSVBase_v_ge->Checked == true){
                double c = StrToFloat(edt_c3d_valC->Text);
                double v_gain = (double)GetV_val()/100/c;
                double tmp;
                for(int i = 0; i < TBL_SIZE; i++)
                        for(int j = 0; j < TBL_SIZE; j++)
                                for(int k = 0; k < TBL_SIZE; k++){
                                                tmp = c3d_lutV[i][j][k]*(v_gain+1);
                                                tmp = (tmp<0?0:tmp);
                                                tmp = (tmp>=256?256-1.0/Ratio:tmp);
                                                tmp_c3d_lutV[i][j][k] = tmp;
                                }
                return;
        }

        int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
        int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
        int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);

        double c = StrToFloat(edt_c3d_valC->Text);
        double v_gain = (double)GetV_val()/100/c;
        double h = c3d_lutH[idx_r][idx_g][idx_b];
        double dif_n = (double)GetV_NegDif();
        double dif_p = (double)GetV_PosDif();

        FILE* fptr = fopen ("change_V.txt","w");
        if(fptr==NULL){
                ShowMessage("can't open value record file.");
                return;
        }

        double tmp_h;   //對每個hue值(tmp_h)計算diffusion量
        double low = h+dif_n;   //負向的diffusion邊界
        double high = h+dif_p;   //正向的diffusion邊界
        bool Is_dif = false;    //flag recording tmp_h to do diffusion or not
        double ratio;
        for(int i = 0; i < TBL_SIZE; i++)
                for(int j = 0; j < TBL_SIZE; j++)
                        for(int k = 0; k < TBL_SIZE; k++){
                                Is_dif = false;
                                tmp_h = c3d_lutH[i][j][k];
                                if(low <0 && tmp_h>low+360){
                                        tmp_h -=360;
                                        Is_dif = true;
                                }
                                else if(high>=360 && tmp_h<fmod(high,360)){
                                        tmp_h+=360;
                                        Is_dif = true;
                                }
                                else if(tmp_h>=low && tmp_h<high){
                                        Is_dif = true;
                                }
                                if(Is_dif == true){
                                        if(tmp_h < h){
                                                ratio = 1-(h-tmp_h)/dif_n*(-1);
                                        }else if(tmp_h >= h){
                                                ratio = 1-(tmp_h-h)/dif_p;
                                        }
                                        tmp_c3d_lutV[i][j][k] = (ratio *v_gain/c +1)*c3d_lutV[i][j][k];
                                        if(tmp_c3d_lutV[i][j][k] >= 256)
                                                tmp_c3d_lutV[i][j][k] = 256-1.0/Ratio;
                                        else if(tmp_c3d_lutV[i][j][k] < 0)
                                                tmp_c3d_lutV[i][j][k] = 0;
                                         if(ratio>1)
                                                ShowMessage("V ratio >1");
                                }else
                                        tmp_c3d_lutV[i][j][k] = c3d_lutV[i][j][k];
                                fprintf(fptr, "%.2f\t%.2f\n", c3d_lutV[i][j][k],tmp_c3d_lutV[i][j][k]);
                        }
        fclose(fptr);
}

//----------------------------------------------------------------------------
void __fastcall TC3DForm1::btn_c3d_writeClick(TObject *Sender)
{
        //cb_en->Checked = false;
        //cb_enClick(Sender);
        btn_c3d_write->Enabled = false;
        c3d_tmp_tbl_save();
        if(PageC_c3d_adj->TabIndex == 0){
                cal_c3d_rgb(true);
        }else if(PageC_c3d_adj->TabIndex == 1){
                if(rg_c3d_hsv_mode->ItemIndex==1){
                //        c3d_6axisAdj_h(true);
                //        c3d_6axisAdj_s(true);
                //        c3d_6axisAdj_v(true);
                }else if(rg_c3d_hsv_mode->ItemIndex==0)
                        c3d_hsvBase_adj(true);
                else if(rg_c3d_hsv_mode->ItemIndex==2)
                        c3d_MixAdj_h(true);
        }

        c3d_lutArrange();
        /*
        FILE* fptr = fopen("1.txt","w");

        int tbl_tl = pow(TBL_SIZE,3);
        for(int i = 0; i < tbl_tl; i++){
                fprintf(fptr,"%d\t%d\t%d\t%d\t%d\t%d\n",c3d_r[0][i],c3d_g[0][i],
                c3d_b[0][i],c3d_r[1][i],c3d_g[1][i],c3d_b[1][i]);
        }
        fclose(fptr);         */
        EngineerForm->SetWrite_PG(lut[0], c3d_r[1], total_len);      //red  LUT
        EngineerForm->SetWrite_PG(lut[1], c3d_g[1], total_len);      //green  LUT
        EngineerForm->SetWrite_PG(lut[2], c3d_b[1], total_len);      //blue  LUT

        sb_c3d_rgb_dis->Position = 0;
        sb_c3d_rgb_r->Position = 800;
        sb_c3d_rgb_g->Position = 800;
        sb_c3d_rgb_b->Position = 800;
        sb_c3d_hsv_h->Position = 500;
        sb_c3d_hsv_s->Position = 1000;
        sb_c3d_hsv_v->Position = 500;
        sb_c3d_hsv_i->Position = 100;
        sb_c3d_HSVBase_h->Position = sb_c3d_HSVBase_h->Max/2;
        sb_c3d_HSVBase_s->Position = sb_c3d_HSVBase_s->Max/2;
        sb_c3d_HSVBase_v->Position = sb_c3d_HSVBase_v->Max/2;
        sb_c3d_HSVBase_i->Position = sb_c3d_HSVBase_i->Max/2;
        btn_c3d_write->Enabled = true;
        //cb_en->Checked = true;
        //cb_enClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::sb_c3d_rgb_disChange(TObject *Sender)
{
        lb_c3d_rgb_dis->Caption = sb_c3d_rgb_dis->Position+1;
        cal_c3d_rgb(false);
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::sb_c3d_rgb_rChange(TObject *Sender)
{
//sb_c3d_rgb_r為做3D LUT的Point Color adjust時, 對選擇的顏色做紅色值的增減量
        double r = double(sb_c3d_rgb_r->Position-800)/Ratio;      //scroll bar的800為0
        lb_c3d_rgb_r->Caption = r;
        double d = (sb_c3d_rgb_dis->Position+1)*cube_dis;     //實際的pixel數值差距為32

        if(r>0 && d<r){
                d+=cube_dis;
                while(d-5<r){
                        d+=cube_dis;
                }
                sb_c3d_rgb_dis->Position = int(d/cube_dis)-1;
        }else if(r<0 && d<r*(-1)){
                d+=cube_dis;
                while(d-5<r*(-1)){
                        d+=cube_dis;
                }
                sb_c3d_rgb_dis->Position = int(d/cube_dis)-1;
        }
        else
                cal_c3d_rgb(false);
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::sb_c3d_rgb_gChange(TObject *Sender)
{
 //sb_c3d_rgb_g為做3D LUT的Point Color adjust時, 對選擇的顏色做綠色值的增減量
        double g = double(sb_c3d_rgb_g->Position-800)/Ratio;
        lb_c3d_rgb_g->Caption = g;
        double d = (sb_c3d_rgb_dis->Position+1)*cube_dis;

        if(g>0 && d<g){
                d+=cube_dis;
                while(d-5<g){
                        d+=cube_dis;
                }
                sb_c3d_rgb_dis->Position = int(d/cube_dis)-1;
        }else if(g<0 && d<g*(-1)){
                d+=cube_dis;
                while(d-5<g*(-1)){
                        d+=cube_dis;
                }
                sb_c3d_rgb_dis->Position = int(d/cube_dis)-1;
        }
        else
                cal_c3d_rgb(false);
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::sb_c3d_rgb_bChange(TObject *Sender)
{
  //sb_c3d_rgb_b為做3D LUT的Point Color adjust時, 對選擇的顏色做藍色值的增減量
        double b = double(sb_c3d_rgb_b->Position-800)/Ratio;
        lb_c3d_rgb_b->Caption = b;
        double d = (sb_c3d_rgb_dis->Position+1)*cube_dis;

        if(b>0 && d<b){
                d+=cube_dis;
                while(d-5<b){
                        d+=cube_dis;
                }
                sb_c3d_rgb_dis->Position = int(d/cube_dis)-1;
        }else if(b<0 && d<b*(-1)){
                d+=cube_dis;
                while(d-5<b*(-1)){
                        d+=cube_dis;
                }
                sb_c3d_rgb_dis->Position = int(d/cube_dis)-1;
        }
        else
                cal_c3d_rgb(false);
}
//---------------------------------------------------------------------------


void __fastcall TC3DForm1::sb_c3d_hsv_Change(TObject *Sender)
{
        double r,g,b,h,s,v,i;
        int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
        int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
        int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);
        int Tbl_r = c3d_lutR[idx_r][idx_g][idx_b];
        int Tbl_g = c3d_lutG[idx_r][idx_g][idx_b];
        int Tbl_b = c3d_lutB[idx_r][idx_g][idx_b];
        rgb2hsv(Tbl_r, Tbl_g,Tbl_b, &h, &s, &i, &v);

        double h_gain = ((double)sb_c3d_hsv_h->Position-500)/10;
        double s_gain = ((double)sb_c3d_hsv_s->Position-1000)/1000;
        double v_gain = ((double)sb_c3d_hsv_v->Position-500)/10;
        lb_c3d_hsv_h->Caption = h_gain;
        lb_c3d_hsv_s->Caption = double(s_gain);
        lb_c3d_hsv_v->Caption = v_gain;

        h += h_gain;
        s += s_gain;
        v += v_gain;
        h = fmod(h+360,360);

        if(s>1)
                s = 1;
        else if(s<0)
                s = 0;
        if(v>255)
                v = 255;
        else if(v<0)
                v = 0;
        hsv2rgb( h, s, v, &r, &g, &b);


        if(r>256 || g>256 || b>256 || r<0 || g<0 || b<0)
                return;

        sb_c3d_rgb_r->Position = (r-Tbl_r)*16+800;
        sb_c3d_rgb_g->Position = (g-Tbl_g)*16+800;
        sb_c3d_rgb_b->Position = (b-Tbl_b)*16+800;

        sb_c3d_rgb_rChange(Sender);
        sb_c3d_rgb_gChange(Sender);
        sb_c3d_rgb_bChange(Sender);

        Show_c3d_CorImg(r, g, b);

        //cal_c3d_rgb(false);
}
int TC3DForm1::GetH_val()
{
        int H = sb_c3d_HSVBase_h->Position-sb_c3d_HSVBase_h->Max/2;
        return H;
}

void TC3DForm1::SetH_caption(int H)
{
        lb_c3d_HSVBase_h->Caption = FloatToStr(H) + "°";
}
void TC3DForm1::Adjust_H_diffusion(int H)
{
        if(H>0){
                if(sb_c3d_HSVBase_hdp->Position<H)
                        sb_c3d_HSVBase_hdp->Position = H;
        }else if(H<0){
                if(sb_c3d_HSVBase_hdn->Position-sb_c3d_HSVBase_hdn->Max>H)
                        sb_c3d_HSVBase_hdn->Position = H+sb_c3d_HSVBase_hdn->Max;
        }
}

void __fastcall TC3DForm1::sb_c3d_HSVBase_hChange(TObject *Sender)
{
        int H = GetH_val();
        SetH_caption(H);
        Adjust_H_diffusion(H);
        /*if(rg_c3d_hsv_mode->ItemIndex==1)
                c3d_6axisAdj_h(false);
        else */
        if(rg_c3d_hsv_mode->ItemIndex==0)
                c3d_hsvBase_adj(false);
        else if(rg_c3d_hsv_mode->ItemIndex==2)
                c3d_MixAdj_h(false);
        else if(rg_c3d_hsv_mode->ItemIndex==3)
                c3d_hsv_FixGain(false);
}
//---------------------------------------------------------------------------
int TC3DForm1::GetH_NegDif()
{
        int neg = sb_c3d_HSVBase_hdn->Position-sb_c3d_HSVBase_hdn->Max;
        return neg;
}

void __fastcall TC3DForm1::sb_c3d_HSVBase_hdnChange(TObject *Sender)
{
        int neg = GetH_NegDif();
        lb_c3d_HSVBase_hdn->Caption = IntToStr(neg) + "°";     //position 1000 means 0
}
//---------------------------------------------------------------------------

int TC3DForm1::GetH_PosDif()
{
        int pos = sb_c3d_HSVBase_hdp->Position;
        return pos;
}

void __fastcall TC3DForm1::sb_c3d_HSVBase_hdpChange(TObject *Sender)
{
        int pos = GetH_PosDif();
        lb_c3d_HSVBase_hdp->Caption = IntToStr(pos) + "°";
}
//---------------------------------------------------------------------------

int TC3DForm1::GetS_val()
{
        int S = sb_c3d_HSVBase_s->Position-sb_c3d_HSVBase_s->Max/2;
        return S;
}
void TC3DForm1::SetS_Caption(int S)
{
        lb_c3d_HSVBase_s->Caption = IntToStr(S);
}

void __fastcall TC3DForm1::sb_c3d_HSVBase_sChange(TObject *Sender)
{
        int S = GetS_val();
        SetS_Caption(S);

        /*if(rg_c3d_hsv_mode->ItemIndex==1)
                c3d_6axisAdj_s(false);
        else*/
        if(rg_c3d_hsv_mode->ItemIndex==0)
                c3d_hsvBase_adj(false);
        else if(rg_c3d_hsv_mode->ItemIndex==2)
                c3d_MixAdj_s(false);
}
//---------------------------------------------------------------------------

int TC3DForm1::GetS_NegDif()
{
        int neg = sb_c3d_HSVBase_sdn->Position-sb_c3d_HSVBase_sdn->Max;
        return neg;
}

void __fastcall TC3DForm1::sb_c3d_HSVBase_sdnChange(TObject *Sender)
{
        int neg = GetS_NegDif();
        lb_c3d_HSVBase_sdn->Caption = IntToStr(neg)+ "°";
}
//---------------------------------------------------------------------------

int TC3DForm1::GetS_PosDif()
{
        int pos = sb_c3d_HSVBase_sdp->Position;
        return pos;
}

void __fastcall TC3DForm1::sb_c3d_HSVBase_sdpChange(TObject *Sender)
{
        int pos = GetS_PosDif();
        lb_c3d_HSVBase_sdp->Caption = IntToStr(pos)+ "°";
}
//---------------------------------------------------------------------------
int TC3DForm1::GetV_val()
{
       int V = sb_c3d_HSVBase_v->Position-sb_c3d_HSVBase_v->Max/2;
       return V;
}
void TC3DForm1::SetV_Caption(int V)
{
       lb_c3d_HSVBase_v->Caption = IntToStr(V);
}

void __fastcall TC3DForm1::sb_c3d_HSVBase_vChange(TObject *Sender)
{
        int V = GetV_val();
        SetV_Caption(V);
        /*if(rg_c3d_hsv_mode->ItemIndex==1)
                c3d_6axisAdj_v(false);
        else */
        if(rg_c3d_hsv_mode->ItemIndex==0)
                c3d_hsvBase_adj(false);
        else if(rg_c3d_hsv_mode->ItemIndex==2)
                c3d_MixAdj_v(false);
}
//---------------------------------------------------------------------------
int TC3DForm1::GetV_NegDif()
{
        int neg = sb_c3d_HSVBase_vdn->Position-sb_c3d_HSVBase_vdn->Max;
        return neg;
}

void __fastcall TC3DForm1::sb_c3d_HSVBase_vdnChange(TObject *Sender)
{
        int neg = GetV_NegDif();
        lb_c3d_HSVBase_vdn->Caption = IntToStr(neg)+ "°";
}
//---------------------------------------------------------------------------
int TC3DForm1::GetV_PosDif()
{
        int pos = sb_c3d_HSVBase_vdp->Position;
        return pos;
}

void __fastcall TC3DForm1::sb_c3d_HSVBase_vdpChange(TObject *Sender)
{
        int pos = GetV_PosDif();
        lb_c3d_HSVBase_vdp->Caption = IntToStr(pos)+ "°";
}
//---------------------------------------------------------------------------
/*****************************************************
//      Method 3                                    //
*****************************************************/
//----------------------------------------------------------------------------

struct Color_Val{
        double d_r, d_g, d_b;   //移動後的r,g,b差值
        double h, s, v; //原始的移動軸的hsv值
};

void TC3DForm1::c3d_MixAdj_r(int type, double dif_p, double dif_n, double gain)
{
        double h, s, v, in;
        double tmp_r, tmp_g, tmp_b;
        Color_Val* color_val;
        color_val = new Color_Val [32770];
        int idx = 0;
        if(type == 1){
                for(int i = 0; i < 256; i++){
                        for(int  j = 0; j < i; j++){
                                //for(int  k = 0; k < i; k++){
                                        //rgb2hsv(i,j,k,&h, &s, &in, &v);
                                        rgb2h(i, j, j, &h);
                                        if(h == 0){
                                                rgb2hsv(i,j,j,&h, &s, &in, &v);
                                                color_val[idx].h = h;
                                                color_val[idx].s = s;
                                                color_val[idx].v = v;
                                                h += gain;
                                                h = fmod(h+360, 360);
                                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                                color_val[idx].d_r = tmp_r-i;
                                                color_val[idx].d_g = tmp_g-j;
                                                color_val[idx].d_b = tmp_b-j;
                                                idx++;
                                        }
                                //}
                        }
                }
        }else if(type == 2){
                for(int i = 0; i < 256; i++){
                        for(int  j = 0; j < i; j++){
                                //for(int  k = 0; k < 256; k++){
                                        rgb2h(i, j, j, &h);
                                        h = floor(h*100+0.5)/100;     //4捨5入2位小數
                                        s = floor(s*1000+0.5)/1000;   //4捨5入3位小數
                                        if(h == 0){
                                                color_val[idx].h = h;
                                                color_val[idx].s = s;
                                                color_val[idx].v = v;
                                                s += s*gain;
                                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                                color_val[idx].d_r = tmp_r-i;
                                                color_val[idx].d_g = tmp_g-j;
                                                color_val[idx].d_b = tmp_b-j;
                                                idx++;
                                        }
                                //}
                        }
                }
        }else if(type == 3){
                for(int i = 0; i < 256; i++){
                        for(int  j = 0; j < i; j++){
                                //for(int  k = 0; k < 256; k++){
                                        rgb2hsv(i,j,j,&h, &s, &in, &v);
                                        h = floor(h*100+0.5)/100;
                                        s = floor(s*1000+0.5)/1000;
                                        if(h == 0){
                                                color_val[idx].h = h;
                                                color_val[idx].s = s;
                                                color_val[idx].v = v;
                                                v += s*v*gain;
                                                hsv2rgb(h, s, v, &tmp_r, &tmp_g, &tmp_b);
                                                color_val[idx].d_r = tmp_r-i;
                                                color_val[idx].d_g = tmp_g-j;
                                                color_val[idx].d_b = tmp_b-j;
                                                idx++;
                                        }
                                //}
                        }
                }
        }

        double r,g,b;
        double ratio;
        for(int i = 0; i < 9; i++){
                for(int j =0; j < 9; j++){
                        for(int k =0; k < 9; k++){
                                if(i==j && j==k)
                                        break;
                                rgb2hsv(i*32,j*32,k*32,&h,&s,&in,&v);
                                if(h<dif_p || h>360+dif_n){
                                        ratio = (h<180?1-h/dif_p:1-(360-h)/dif_n*(-1));
                                        //ratio = (h<180?h/dif_p:(h-360)/dif_n);
                                        if(h==0)
                                                ratio = 1;
                                        r = 0; g = 0; b = 0;
                                        int t = 0;
                                        for(int c = 0; c < idx; c++){
                                                if(v==256)
                                                        v--;
                                                if(color_val[c].v < v+1 && color_val[c].v > v-1 &&
                                                (color_val[c].s < s+0.01 && color_val[c].s >= s-0.01 && color_val[c].s!=0)){
                                                        r += color_val[c].d_r;
                                                        g += color_val[c].d_g;
                                                        b += color_val[c].d_b;
                                                        t++;
                                                }
                                        }
                                        tmp_c3d_lutR[i][j][k] += ratio*r/t;
                                        tmp_c3d_lutG[i][j][k] += ratio*g/t;
                                        tmp_c3d_lutB[i][j][k] += ratio*b/t;
                                        fix_val(&tmp_c3d_lutR[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutG[i][j][k],256-1.0/Ratio);
                                        fix_val(&tmp_c3d_lutB[i][j][k],256-1.0/Ratio);
                                }
                        }
                }
        }
        delete [] color_val;
}
//---------------------------------------------------------------------------
void TC3DForm1::c3d_MixAdj_v(bool flag)       //can't use
{
        double c = StrToFloat(edt_c3d_valC->Text);
        double v_gain = double(sb_c3d_HSVBase_v->Position-1000)/1000/c;
        double dif_n = double(sb_c3d_HSVBase_vdn->Position-1000)/10;
        double dif_p = double(sb_c3d_HSVBase_vdp->Position)/10;

        for(int i = 0; i < 9; i ++)
                for(int j = 0; j < 9; j ++)
                        for(int k = 0; k < 9; k ++){
                                tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
                                tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
                                tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
                        }
        double h, s, in, v;
        if(cb_c3d_HSVBase_v_ge->Checked == true){
                for(int i = 0; i < 9; i ++)
                        for(int j = 0; j < 9; j ++)
                                for(int k = 0; k < 9; k ++){
                                        rgb2hsv(tmp_c3d_lutR[i][j][k],tmp_c3d_lutG[i][j][k],tmp_c3d_lutB[i][j][k],&h,&s,&in,&v);
                                        v+=v*v_gain*s;
                                        v = (v<0?0:v);
                                        v = (v>=256?256-1.0/Ratio:v);
                                        hsv2rgb(h,s,v,&tmp_c3d_lutR[i][j][k],&tmp_c3d_lutG[i][j][k],&tmp_c3d_lutB[i][j][k]);
                                }
        }else{
                if(rb_c3d_r->Checked == true){
                        c3d_MixAdj_r(3,dif_p,dif_n,v_gain);
                }
        }

        if(flag==true){
                for(int i = 0; i < 9; i++)
                        for(int j = 0; j < 9; j++)
                                for(int k = 0; k < 9; k++){
                                        c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
                                        c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
                                        c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
                                }
        }
        int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
        int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
        int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);
        Show_c3d_CorImg(tmp_c3d_lutR[idx_r][idx_g][idx_b], tmp_c3d_lutG[idx_r][idx_g][idx_b],
        tmp_c3d_lutB[idx_r][idx_g][idx_b]);

        double r = StrToFloat(lb_c3d_selR->Caption);
        double g = StrToFloat(lb_c3d_selG->Caption);
        double b = StrToFloat(lb_c3d_selB->Caption);
        double sim_r, sim_g, sim_b;
        C3Dsim_t(r, g, b, &sim_r, &sim_g, &sim_b);
        Show_c3d_SimImg(sim_r, sim_g, sim_b);
}
//----------------------------------------------------------------------------
void TC3DForm1::c3d_MixAdj_s(bool flag)    //can't use
{
        double s_gain = double(sb_c3d_HSVBase_s->Position-500)/10;
        double dif_n = double(sb_c3d_HSVBase_sdn->Position-1000)/10;
        double dif_p = double(sb_c3d_HSVBase_sdp->Position)/10;

        double tmp_c3d_lutR[9][9][9],tmp_c3d_lutG[9][9][9],tmp_c3d_lutB[9][9][9];

        for(int i = 0; i < 9; i ++)
                for(int j = 0; j < 9; j ++)
                        for(int k = 0; k < 9; k ++){
                                tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
                                tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
                                tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
                        }
        double h, s, in, v;
        if(cb_c3d_HSVBase_s_ge->Checked == true){
                for(int i = 0; i < 9; i ++)
                        for(int j = 0; j < 9; j ++)
                                for(int k = 0; k < 9; k ++){
                                        rgb2hsv(tmp_c3d_lutR[i][j][k],tmp_c3d_lutG[i][j][k],tmp_c3d_lutB[i][j][k],&h,&s,&in,&v);
                                        s+=s_gain*s;
                                        s = (s<0?0:s);
                                        s = (s>1?1:s);
                                        hsv2rgb(h,s,v,&tmp_c3d_lutR[i][j][k],&tmp_c3d_lutG[i][j][k],&tmp_c3d_lutB[i][j][k]);
                                }
        }else{
                if(rb_c3d_r->Checked == true){
                        c3d_MixAdj_r(2,dif_p,dif_n,s_gain);
                }
        }

        if(flag==true){
                for(int i = 0; i < 9; i++)
                        for(int j = 0; j < 9; j++)
                                for(int k = 0; k < 9; k++){
                                        c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
                                        c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
                                        c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
                                }
        }
        int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
        int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
        int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);
        Show_c3d_CorImg(tmp_c3d_lutR[idx_r][idx_g][idx_b], tmp_c3d_lutG[idx_r][idx_g][idx_b],
        tmp_c3d_lutB[idx_r][idx_g][idx_b]);

        double r = StrToFloat(lb_c3d_selR->Caption);
        double g = StrToFloat(lb_c3d_selG->Caption);
        double b = StrToFloat(lb_c3d_selB->Caption);
        double sim_r, sim_g, sim_b;
        C3Dsim_t(r, g, b, &sim_r, &sim_g, &sim_b);
        Show_c3d_SimImg(sim_r, sim_g, sim_b);
}
//----------------------------------------------------------------------------
void TC3DForm1::c3d_MixAdj_h(bool flag)
{
        double h_gain = double(sb_c3d_HSVBase_h->Position-sb_c3d_HSVBase_h->Max/2)/10;
        double dif_n = double(sb_c3d_HSVBase_hdn->Position-sb_c3d_HSVBase_hdn->Max);
        double dif_p = double(sb_c3d_HSVBase_hdp->Position);

        for(int i = 0; i < 9; i ++)
                for(int j = 0; j < 9; j ++)
                        for(int k = 0; k < 9; k ++){
                                tmp_c3d_lutR[i][j][k] = c3d_lutR[i][j][k];
                                tmp_c3d_lutG[i][j][k] = c3d_lutG[i][j][k];
                                tmp_c3d_lutB[i][j][k] = c3d_lutB[i][j][k];
                        }
        double h, s, in, v;
        if(cb_c3d_HSVBase_h_rt->Checked == true){
                for(int i = 0; i < 9; i ++)
                        for(int j = 0; j < 9; j ++)
                                for(int k = 0; k < 9; k ++){
                                        rgb2hsv(tmp_c3d_lutR[i][j][k],tmp_c3d_lutG[i][j][k],
                                        tmp_c3d_lutB[i][j][k],&h,&s,&in,&v);
                                        h+=h_gain;
                                        h=fmod(h+360,360);
                                        hsv2rgb(h,s,v,&tmp_c3d_lutR[i][j][k],&tmp_c3d_lutG[i][j][k],&tmp_c3d_lutB[i][j][k]);
                                }
        }else{
                if(rb_c3d_r->Checked == true){
                        c3d_MixAdj_r(1,dif_p,dif_n,h_gain);
                }
        }

        if(flag==true){
                for(int i = 0; i < 9; i++)
                        for(int j = 0; j < 9; j++)
                                for(int k = 0; k < 9; k++){
                                        c3d_lutR[i][j][k] = tmp_c3d_lutR[i][j][k];
                                        c3d_lutG[i][j][k] = tmp_c3d_lutG[i][j][k];
                                        c3d_lutB[i][j][k] = tmp_c3d_lutB[i][j][k];
                                }
        }
        int idx_r = StrToInt(lb_c3d_tbl_ir->Caption);
        int idx_g = StrToInt(lb_c3d_tbl_ig->Caption);
        int idx_b = StrToInt(lb_c3d_tbl_ib->Caption);
        Show_c3d_CorImg(tmp_c3d_lutR[idx_r][idx_g][idx_b], tmp_c3d_lutG[idx_r][idx_g][idx_b],
        tmp_c3d_lutB[idx_r][idx_g][idx_b]);

        double r = StrToFloat(lb_c3d_selR->Caption);
        double g = StrToFloat(lb_c3d_selG->Caption);
        double b = StrToFloat(lb_c3d_selB->Caption);
        double sim_r, sim_g, sim_b;
        C3Dsim(r, g, b, &sim_r, &sim_g, &sim_b);
        Show_c3d_SimImg(sim_r, sim_g, sim_b);
}
//----------------------------------------------------------------------------
void __fastcall TC3DForm1::Img_3DLUTMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
        int color;
        double h,s,v,i, r,g, b;
        color = Img_3DLUT->Canvas->Pixels[X][Y];
        if(color==-1)
                color = 0;

        b = color/65536;
        g = color/256%256;
        r = color%256;
        rgb2hsv(r, g, b, &h, &s, &i, &v);

        i = (double(int(i*10)))/10.0;
        h = (double(int(h*10)))/10.0;
        s = (double(int(s*100)))/100.0;

        lb_c3d_showX->Caption = "X: "+IntToStr((int)X);
        lb_c3d_showY->Caption = "Y: "+IntToStr((int)Y);
        lb_c3d_showR->Caption = "R: "+IntToStr((int)r);
        lb_c3d_showG->Caption = "G: "+IntToStr((int)g);
        lb_c3d_showB->Caption = "B: "+IntToStr((int)b);
        lb_c3d_showH->Caption = "H: "+IntToStr((int)h);
        lb_c3d_showS->Caption = "S: "+FloatToStr((float)s);
        lb_c3d_showI->Caption = "I: "+FloatToStr(i);
        lb_c3d_showV->Caption = "V: "+IntToStr((int)v);

        //Graphics *TempBitmap, *TheBitmap;
        //TempBitmap=new Graphics::TBitmap()Picture ->;
        //TheBitmap=Hue_Img->Picture->Bitmap;
        //TempBitmap->Assign(TheBitmap);
        //delete TempBitmap;
        //  const String s = /* something */;
          //mages[i]->Picture->LoadFromFile(sl);
}
//---------------------------------------------------------------------------
void c3d_find_point(int tbl_l,int tbl_n,double r,double g,double b,int* idx_r,int* idx_g,int* idx_b)
{
        //找最接近的點
        if(r%cube_dis>cube_dis/2)
                *idx_r = (r%cube_dis)/cube_dis+1;
        else
                *idx_r = (r%cube_dis)/cube_dis;

        if(g%cube_dis>cube_dis/2)
                *idx_g = (g%cube_dis)/cube_dis+1;
        else
                *idx_g = (g%cube_dis)/cube_dis;

        if(b%cube_dis>cube_dis/2)
                *idx_b = (b%cube_dis)/cube_dis+1;
        else
                *idx_b = (b%cube_dis)/cube_dis;


        /* //找存在的那個block中最小的點
        for(int i = 0; i <= tbl_l-2; i++){
                if( r>=tbl_val[tbl_n][i] && r <=tbl_val[tbl_n][i+1]){   //找出r值在那一個區間,
                        *idx_r = i;
                        break;
                }
        }
        for(int i = 0; i <= tbl_l-2; i++){
                if( g>=tbl_val[tbl_n][i] && g <=tbl_val[tbl_n][i+1]){   //找出g值在那一個區間,
                        *idx_g = i;
                        break;
                }
        }
        for(int i = 0; i <= tbl_l-2; i++){
                if( b>=tbl_val[tbl_n][i] && b <=tbl_val[tbl_n][i+1]){   //找出b值在那一個區間,
                        *idx_b = i;
                        break;
                }
        }*/
}

//----------------------------------------------------------------------------

void __fastcall TC3DForm1::Img_3DLUTMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        rb_c3d_point->Checked = true;
        int color;
        double h, s, i, v, r,g, b;
        color = Img_3DLUT->Canvas->Pixels[X][Y];
        if(color==-1)
                color = 0;
        b = color/65536;
        g = color/256%256;
        r = color%256;

        Show_c3d_SelImg(r,g,b);

        int tbl_n;
        if(rg_c3d_TblSize->ItemIndex==0){
                tbl_n = 0;
        }else if(rg_c3d_TblSize->ItemIndex==1){
                tbl_n = 1;
        }else if(rg_c3d_TblSize->ItemIndex==2){
                tbl_n = 2;
        }else if(rg_c3d_TblSize->ItemIndex==3){
                tbl_n = 3;
        }

        int idx_r, idx_g, idx_b;
        //c3d_find_smallpoint(tbl_l,tbl_n,r,g,b,&idx_r,&idx_g,&idx_b); //取最近點
        c3d_find_point(TBL_SIZE,tbl_n,r,g,b,&idx_r,&idx_g,&idx_b); //取block裡的最小點

        lb_c3d_tbl_ir->Caption = idx_r;
        lb_c3d_tbl_ig->Caption = idx_g;
        lb_c3d_tbl_ib->Caption = idx_b;

//----------------table r, g, b, h, s, i, v 即Matrix rgb---------------------------

        double tbl_r, tbl_g, tbl_b, tbl_h, tbl_s, tbl_i, tbl_v;

        tbl_r = c3d_lutR[idx_r][idx_g][idx_b];
        tbl_g = c3d_lutG[idx_r][idx_g][idx_b];
        tbl_b = c3d_lutB[idx_r][idx_g][idx_b];

        if(tbl_r == 256)
                tbl_r = 256-1.0/Ratio;
        if(tbl_g == 256)
                tbl_g = 256-1.0/Ratio;
        if(tbl_b == 256)
                tbl_b = 256-1.0/Ratio;

        Show_c3d_TblImg(tbl_r, tbl_g, tbl_b);
        Show_c3d_CorImg(tbl_r, tbl_g, tbl_b);

        double sim_r, sim_g, sim_b, sim_h, sim_s, sim_i, sim_v;
        C3Dsim(r,g,b,&sim_r,&sim_g,&sim_b);
        Show_c3d_SimImg(sim_r, sim_g, sim_b);
        refresh_c3d_grid(sim_r,sim_g,sim_b);
}
//---------------------------------------------------------------------------
bool IsC3Dshow = false;
void __fastcall TC3DForm1::FormCreate(TObject *Sender)
{
        if(IsC3Dshow==false){
                C3Dini();
                IsC3Dshow = true;
        }
        C3D_Chg = 0;
        OC3D = new C3D_12401;

        en.Addr = OC3D->SetEn();
        cb_en->Visible = en.Addr.FuncEn();
        cb_en->Caption = en.Addr.Name();

        lut = OC3D->SetLUT();
        cb = OC3D->SetChkBx();
        ChkB = new _CHKB* [C3DChkBox_Nbr];
        for(int i = 0; i < C3DChkBox_Nbr; i++)
                ChkB[i] = new _CHKB;

        ChkB[0]->Chkb = cb_demo;

        for(int i = 0; i < C3DChkBox_Nbr; i++){
                ChkB[i]->Addr = cb[i];
                ChkB[i]->Chkb->Visible = ChkB[i]->Addr.FuncEn();
                ChkB[i]->Chkb->OnClick = CheckBox_Click;
                ChkB[i]->Chkb->Hint = i;
                ChkB[i]->Chkb->Caption = ChkB[i]->Addr.Name();
        }

        C3D_Chg = 1;

        for(int i = 0; i < 9; i++){
                sg_table_step->Cells[i][0]=i+1;
                sg_table_step->Cells[i][1]=tbl_val[0][i];
        }
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::BitBtn_c3d_undoClick(TObject *Sender)
{
        BitBtn_c3d_undo->Enabled = false;
        String Fpath = "tmp_tbl.txt";
        char* buffer = Load_File(Fpath);

        int tbl_tl = pow(TBL_SIZE,3);

        int idx_r, idx_g, idx_b;
        char* str[11];          int str_l[11];
        str[0]="C3D_LUT";       str_l[0]=7;
        str[1]="Rin";           str_l[1]=4;
        str[2]="Gin";           str_l[2]=4;
        str[3]="Bin";           str_l[3]=4;
        str[4]="Rout";          str_l[4]=4;
        str[5]="Gout";          str_l[5]=4;
        str[6]="Bout";          str_l[6]=4;
        str[7]="H";             str_l[7]=1;
        str[8]="S";             str_l[8]=1;
        str[9]="V";             str_l[9]=1;
        str[10]="I";            str_l[10]=1;

        char* pch = strtok (buffer,"\n\t");
        for(int i = 0; i < 11; i++){
                while (memcmp(pch,str[i],str_l[i])!=0){
                        if(pch == NULL){
                                ShowMessage("Can't open c3d table file.");
                                return;
                        }
                        pch = strtok (NULL,"\n\t");
                }
        }
        int c = 0;
        pch = strtok (NULL,"\n\t");
        while (c < tbl_tl*10 && pch!=NULL){
                if(pch == NULL){
                        ShowMessage("Can't open c3d table file.");
                        return;        //資料中的data缺少
                }
                if(c%10 == 0)
                        idx_r = (int)ceil((double)StrToInt((AnsiString)pch)/32);
                else if(c%10 == 1)
                        idx_g = (int)ceil((double)StrToInt((AnsiString)pch)/32);
                else if(c%10 == 2)
                        idx_b = (int)ceil((double)StrToInt((AnsiString)pch)/32);
                else if(c%10 == 3){
                        c3d_lutR[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch)/Ratio;
                }else if(c%10 == 4){
                        c3d_lutG[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch)/Ratio;
                }else if(c%10 == 5){
                        c3d_lutB[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch)/Ratio;
                }else if(c%10 == 6)
                        c3d_lutH[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch);
                else if(c%10 == 7)
                        c3d_lutS[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch);
                else if(c%10 == 8)
                        c3d_lutV[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch);
                else if(c%10 == 9)
                        c3d_lutI[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch);

                pch = strtok (NULL,"\n\t");
                c++;
       }
       delete [] buffer;
       refresh_c3d_grid(255,255,255);
       //BitBtn_c3d_undo->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_c3d_checkClick(TObject *Sender)
{
        /*
        //AddrC3D.R_LUT[ASIC_num].LutNum()
        if(AddrC3D.R_LUT[ASIC_num].LutNum()!=729){
                ShowMessage("Address Naming wrong!(c3d lookup table number)");
                return;
        }

        int buff_length = ceil(double(729)*3/2);
        unsigned char* data_buff = new unsigned char [buff_length];
        i2c_read_byte_seq(dev_addr, AddrC3D.R_LUT[ASIC_num].Addr(),data_buff, buff_length, 0);

        int tmp_lut[729];
        int tbl_idx = 0;
        for(int i = 0; i < buff_length; i+=3){
                tmp_lut[tbl_idx] = (unsigned int)data_buff[i]+ (unsigned int)data_buff[i+1]%16*256;
                tmp_lut[tbl_idx+1] = (unsigned int)data_buff[i+1]/16;
                if(i+2< buff_length)
                        tmp_lut[tbl_idx+1] += (unsigned int)data_buff[i+2]*16;
                tbl_idx += 2;
        }
        SaveDialog1->Execute();
        String Fpath = SaveDialog1->FileName;
        FILE* fptr;
        if((fptr = fopen(Fpath.c_str(),"w"))==NULL)
                return;
        for(int i = 0; i<buff_length; i++)
        fprintf(fptr,"%d:\t%d\n",i,data_buff[i]);
        fclose(fptr);

        int c3d_r[2][729],c3d_g[2][729],c3d_b[2][729];
        c3d_lutArrange(c3d_r, c3d_g, c3d_b);

        int t = 0;
        for(int i = 0; i < 729; i ++){
                if(tmp_lut[i]!=c3d_r[1][i]){
                        ShowMessage("c3d r value r["+IntToStr(i)+"] not match!");
                        t++;
                        if(t>=5)
                                break;
                }
        }

        tbl_idx = 0;
        i2c_read_byte_seq(dev_addr, AddrC3D.G_LUT[ASIC_num].Addr(),data_buff, buff_length, 0);
        for(int i = buff_length; i < buff_length*2; i+=3){
                tmp_lut[tbl_idx] = (unsigned int)data_buff[i]+ (unsigned int)data_buff[i+1]%16*256;
                tmp_lut[tbl_idx+1] = (unsigned int)data_buff[i+1]/16;
                if(i+2< buff_length)
                        tmp_lut[tbl_idx+1] += (unsigned int)data_buff[i+2]*16;
                tbl_idx += 2;
        }
        t = 0;
        for(int i = 0; i < 729; i ++){
                if(tmp_lut[i]!=c3d_g[1][i]){
                        ShowMessage("c3d g value g["+IntToStr(i)+"] not match!");
                        t++;
                        if(t>=5)
                                break;
                }
        }

        tbl_idx = 0;
        i2c_read_byte_seq(dev_addr, AddrC3D.B_LUT[ASIC_num].Addr(),data_buff, buff_length, 0);
        SaveDialog1->Execute();
        Fpath = SaveDialog1->FileName;
        if((fptr = fopen(Fpath.c_str(),"w"))==NULL)
                return;
        for(int i = 0; i<buff_length; i++)
                fprintf(fptr,"%d:\t%d\n",i,data_buff[i]);
        fclose(fptr);
        for(int i = buff_length*2; i < buff_length*3; i+=3){
                tmp_lut[tbl_idx] = (unsigned int)data_buff[i]+ (unsigned int)data_buff[i+1]%16*256;
                tmp_lut[tbl_idx+1] = (unsigned int)data_buff[i+1]/16;
                if(i+2< buff_length)
                        tmp_lut[tbl_idx+1] += (unsigned int)data_buff[i+2]*16;
                tbl_idx += 2;
        }
        SaveDialog1->Execute();
        Fpath = SaveDialog1->FileName;
        if((fptr = fopen(Fpath.c_str(),"w"))==NULL)
                return;
        for(int i = 0; i<buff_length; i++)
        fprintf(fptr,"%d:\t%d\n",i,data_buff[i]);
        fclose(fptr);

        for(int i = 0; i < 729; i ++){
                if(tmp_lut[i]!=c3d_b[1][i]){
                        ShowMessage("c3d b value b["+IntToStr(i)+"] not match!");
                        t++;
                        if(t>=5)
                                break;
                }
        }
        delete [] data_buff;
        ShowMessage("3DLUT Tcon value check ok!");        */
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::cb_enClick(TObject *Sender)
{
        if(C3D_Chg==0)
                return;
        int set_val = (cb_en->Checked?1:0);
        EngineerForm->SetWrite_Byte(en.Addr ,set_val);
}
//---------------------------------------------------------------------------
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

void __fastcall TC3DForm1::btn_c3d_load_rgbClick(TObject *Sender)
{
        if(!OpenDialog1->Execute())
                return;
        String Fpath = OpenDialog1->FileName;
        char* buffer = Load_File(Fpath);

        int tbl_tl = pow(TBL_SIZE,3);

        int idx_r, idx_g, idx_b;
        char* str[7];          int str_l[7];
        str[0]="C3D_LUT";       str_l[0]=7;
        str[1]="Rin";           str_l[1]=4;
        str[2]="Gin";           str_l[2]=4;
        str[3]="Bin";           str_l[3]=4;
        str[4]="Rout";          str_l[4]=4;
        str[5]="Gout";          str_l[5]=4;
        str[6]="Bout";           str_l[6]=4;

        char* pch = strtok (buffer,"\n\t");
        for(int i = 0; i < 7; i++){
                while (memcmp(pch,str[i],str_l[i])!=0){
                        if(pch == NULL){
                                ShowMessage("Can't open c3d table file.");
                                return;
                        }
                        pch = strtok (NULL,"\n\t");
                }
        }
        int c = 0;
        pch = strtok (NULL,"\n\t");
        while (c < tbl_tl*6 && pch!=NULL){
                if(pch == NULL){
                        ShowMessage("Can't open c3d table file.");
                        return;        //資料中的data缺少
                }
                if(c%6 == 0)
                        idx_r = (int)ceil((double)StrToInt((AnsiString)pch)/32);
                else if(c%6 == 1)
                        idx_g = (int)ceil((double)StrToInt((AnsiString)pch)/32);
                else if(c%6 == 2)
                        idx_b = (int)ceil((double)StrToInt((AnsiString)pch)/32);
                else if(c%6 == 3)
                        c3d_lutR[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch)/Ratio;
                else if(c%6 == 4)
                        c3d_lutG[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch)/Ratio;
                else if(c%6 == 5)
                        c3d_lutB[idx_r][idx_g][idx_b] = StrToFloat((AnsiString)pch)/Ratio;
                pch = strtok (NULL,"\n\t");
                c++;
       }
       delete [] buffer;

       double h,s,v,i;
       for(int u = 0; u < TBL_SIZE; u++)
               for(int j = 0; j < TBL_SIZE; j++)
                       for(int k = 0; k < TBL_SIZE; k++){
                                rgb2hsv(c3d_lutR[u][j][k], c3d_lutG[u][j][k],
                                   c3d_lutB[u][j][k], &h, &s, &i, &v);
                                c3d_lutH[u][j][k] = h;
                                c3d_lutS[u][j][k] = s;
                                c3d_lutI[u][j][k] = i;
                                c3d_lutV[u][j][k] = v;
                       }
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_tbl_searchClick(TObject *Sender)
{
        SaveDialog1->Title = "Enter File Name of the cross & plane";
        if(!SaveDialog1->Execute())
                return;
        String Fpath = SaveDialog1->FileName;
        FILE* fptr;
        if((fptr = fopen(Fpath.c_str(),"w"))==NULL)
                return ;
        double r_new, g_new, b_new;


        //對角線
        fprintf(fptr,"cross1\n");
        for(int i = 0; i < 32; i++){
                   C3Dsim((double)(192+i),(double)(64-i), (double)0, &r_new, &g_new, &b_new);
                   fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n",(int)(192+i),(int)(64-i), 0,r_new,g_new,b_new);
        }

        fprintf(fptr,"cross2\n");
        for(int i = 0; i < 16; i++){
                   C3Dsim((double)(192+i),(double)(48-i), (double)0, &r_new, &g_new, &b_new);
                   fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n",(int)(192+i),(int)(48-i), 0,r_new,g_new,b_new);
        }
        fprintf(fptr,"cross3\n");
        for(int i = 0; i < 16; i++){
                   C3Dsim((double)(208+i),(double)(64-i), (double)0, &r_new, &g_new, &b_new);
                   fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n",(int)(208+i),(int)(64-i),0,r_new,g_new,b_new);
        }                       

        fprintf(fptr,"cross4\n");
        for(int i = 0; i < 8; i++){
                   C3Dsim((double)(200-i),(double)(32+i), (double)0, &r_new, &g_new, &b_new);
                   fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n",(int)(200-i),(int)(32+i), 0,r_new,g_new,b_new);
        }

        fprintf(fptr,"cross5\n");
        for(int i = 0; i < 24; i++){
                   C3Dsim((double)(216-i),(double)(32+i), (double)0, &r_new, &g_new, &b_new);
                   fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n",(int)(216-i),(int)(32+i),0,r_new,g_new,b_new);
        }
        fprintf(fptr,"cross6\n");
        for(int i = 0; i < 24; i++){
                   C3Dsim((double)(224-i),(double)(40+i), (double)0, &r_new, &g_new, &b_new);
                   fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n",(int)(224-i),(int)(40+i),0,r_new,g_new,b_new);
        }
        fprintf(fptr,"cross7\n");
        for(int i = 0; i < 8; i++){
                   C3Dsim((double)(224-i),(double)(56+i), (double)0, &r_new, &g_new, &b_new);
                   fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n",(int)(224-i),(int)(56+i),0,r_new,g_new,b_new);
        }

        /*
        fprintf(fptr,"cross2\n");
        for(int i = 0; i <= 32; i++){
                   C3Dsim((double)255.0, (double)(64+i),(double)(160-i), &r_new, &g_new, &b_new);
                   fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n",255, (int)(64+i),(int)(160-i),r_new,g_new,b_new);
        }
        */
        // 4 disc cube plane
        fprintf(fptr,"plane_incube\n");
        int b=0;
        for(int r = 192;  r<= 224; r++)
                for(int g = 32; g <= 64; g++){
                        //for(int b = 32; b <= 64; b++){
                                C3Dsim((double)r,(double)g, (double)b, &r_new, &g_new, &b_new);
                                fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", r,g,b,r_new,g_new,b_new);
                        }
        fclose(fptr);
        /*
        SaveDialog1->Title = "Enter File Name of the 2nd Plane";
        if(!SaveDialog1->Execute())
                return;
        Fpath = SaveDialog1->FileName;
        if((fptr = fopen(Fpath.c_str(),"w"))==NULL)
                return ;
        fprintf(fptr,"plane_incube\n");
        g=255;
        for(int r = 192; r <= 255; r++)
                //for(int g = 96; g <= 224; g++)
                        for(int b = 32; b <= 64; b++){
                                C3Dsim((double)r,(double)g, (double)b, &r_new, &g_new, &b_new);
                                fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", r,g,b,r_new,g_new,b_new);
                        }

        SaveDialog1->Title = "Enter File Name of the 3rd Plane";

        if(!SaveDialog1->Execute())
                return;
        Fpath = SaveDialog1->FileName;
        if((fptr = fopen(Fpath.c_str(),"w"))==NULL)
                return ;
        fprintf(fptr,"plane_incube\n");
        g=255;
        for(int r = 192; r <= 255; r++)
                //for(int g = 96; g <= 224; g++)
                        for(int b = 96; b <= 128; b++){
                                C3Dsim((double)r,(double)g, (double)b, &r_new, &g_new, &b_new);
                                fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", r,g,b,r_new,g_new,b_new);
                        }*/
        //fclose(fptr);
        /*
        fprintf(fptr,"acme*4cube");

        int table [24][3]={{128,224,64},{128,224,96},{128,255,64},{128,255,96},
        {160,224,64},{160,224,96},{160,255,64},{160,255,96},
        {160,224,64},{160,224,96},{160,255,64},{160,255,96},{192,224,64},{192,224,96},
        {192,255,64},{192,255,96},
        {160,224,32},{160,224,64},{160,255,32},{160,255,64},{192,224,32},{192,224,64},
        {192,255,32},{192,255,64}};

        for(int i=0; i < 24;i++){
                C3Dsim((double)table[i][0], (double)table[i][1], (double)table[i][2]+32, &r_new, &g_new, &b_new);
                fprintf(fptr, "%d\t%d\t%d\t%.2f\t%.2f\t%.2f\n", table[i][0], table[i][1], table[i][2]+32,r_new,g_new,b_new);
                if((i+1)%8==0)
                        fprintf(fptr,"\n");
        }
        */
         /*
        //輸入8個頂點, 找出轉換後的table值
        OpenDialog1->Title = "Choose acme point file";
        if(!OpenDialog1->Execute())
                return;
        Fpath = OpenDialog1->FileName;
        //Fpath = OpenDialog1->FileName;
        char* buffer = Load_File(Fpath);

        //write file
        SaveDialog1->Title = "Enter acme point result file name";
        if(!SaveDialog1->Execute())
                return;
        Fpath = SaveDialog1->FileName;

        FILE* fptr1;
        if((fptr1 = fopen(Fpath.c_str(),"w"))==NULL)
                return ;

        int tbl_R,tbl_G,tbl_B;
        double tbl_H;
        int idxR,idxG,idxB;
        char* pch = strtok (buffer,"\n\t");
        tbl_R = StrToInt((AnsiString)pch);
        pch = strtok (NULL,"\n\t");
        tbl_G = StrToInt((AnsiString)pch);
        pch = strtok (NULL,"\n\t");
        tbl_B = StrToInt((AnsiString)pch);
        rgb2h((double)tbl_R,(double)tbl_G,(double)tbl_B,&tbl_H);
        idxR=tbl_R/cube_dis;
        idxG=tbl_G/cube_dis;
        idxB=tbl_B/cube_dis;
        fprintf(fptr1, "%d\t%d\t%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",(int)tbl_R,(int)tbl_G,(int)tbl_B,tbl_H,c3d_lutR[idxR][idxG][idxB],
                c3d_lutG[idxR][idxG][idxB],c3d_lutB[idxR][idxG][idxB],c3d_lutH[idxR][idxG][idxB]);

        int idx=1;
        while(idx<128){
                for(int i = 0; i < 3; i++){
                        if(pch == NULL){
                                ShowMessage("Table items missing.");
                                return;
                        }
                        pch = strtok (NULL,"\n\t");
                        if(i==0)
                                tbl_R = StrToInt((AnsiString)pch);
                        else if(i==1)
                                tbl_G = StrToInt((AnsiString)pch);
                        else if(i==2)
                                tbl_B = StrToInt((AnsiString)pch);
                }
                rgb2h(tbl_R,tbl_G,tbl_B,&tbl_H);
                idxR=tbl_R/cube_dis;
                idxG=tbl_G/cube_dis;
                idxB=tbl_B/cube_dis;
                fprintf(fptr1, "%d\t%d\t%d\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n",(int)tbl_R,(int)tbl_G,(int)tbl_B,tbl_H,c3d_lutR[idxR][idxG][idxB],
                c3d_lutG[idxR][idxG][idxB],c3d_lutB[idxR][idxG][idxB],c3d_lutH[idxR][idxG][idxB]);
                idx++;
                //if(idx%8==0)
                //        fprintf(fptr1,"\n");
        }
        fclose(fptr1); */
}
//---------------------------------------------------------------------------
void TC3DForm1::Direct_sim(double r, double g, double b, double* r_new,double* g_new, double* b_new){
        //h_adj --- start
       	double h,s,i,v;
       	rgb2hsv(r,g,b,&h,&s,&i,&v);
        if(s==0){ //固定灰階
                *r_new=r;
                *g_new=g;
                *b_new=b;
                return;
        }
        double h_gain = (double)GetH_val();
        double trans_h = StrToFloat(lb_c3d_selH->Caption);
        if(cb_c3d_HSVBase_h_rt->Checked == true){
                h = fmod((h+h_gain)+360,360);
                hsv2rgb(h,s,v,&r,&g,&b);
                *r_new=r;
                *g_new=g;
                *b_new=b;
        }else{
                if(h_gain==0){
                        *r_new=r;
                        *g_new=g;
                        *b_new=b;
                        return;
                }else{
                        double dif_n = (double)GetH_NegDif();
                        double dif_p = (double)GetH_PosDif();
                        double low = trans_h+dif_n;   //負向的diffusion邊界
                        double high = trans_h+dif_p;   //正向的diffusion邊界
                        double new_pos_rng = dif_p-h_gain;      //原本做正向diffusion的範圍所要對應到的新範圍
                        double new_neg_rng = dif_n*(-1)+h_gain; //原本做負向diffusion的範圍所要對應到的新範圍
                        bool Is_dif = false;    //flag recording tmp_h to do diffusion or not
                        double ratio, rslt;

                        if(low <0 && h>low+360){
                                h -=360;
                                Is_dif = true;
                        }else if(high>=360 && h<fmod(high,360)){
                                h+=360;
                                Is_dif = true;
                        }else if(h>=low && h<high){
                                Is_dif = true;
                        }
                        if(Is_dif == true){
                                if(h < trans_h){
                                        ratio = (h-low)/dif_n*(-1);
                                        rslt =  ratio * new_neg_rng + low;
                                }else if(h >= trans_h){
                                        ratio = (h-high)/dif_p;
                                        rslt = ratio * new_pos_rng + high;
                                }
                                h = fmod(rslt + 360, 360);
                        }
                        hsv2rgb(h,s,v,&r,&g,&b);
                        *r_new=r;
                        *g_new=g;
                        *b_new=b;
                }
        }

            //S adj
        double c = StrToFloat(edt_c3d_satC->Text);
        double s_gain = (double)GetS_val()/100/c;
        if(cb_c3d_HSVBase_s_ge->Checked == true){
                double tmp;
                for(int i = 0; i < TBL_SIZE; i++)
                        for(int j = 0; j < TBL_SIZE; j++)
                                for(int k = 0; k < TBL_SIZE; k++){
                                        if(h!=0 ||s!=0){//固定灰階
                                                tmp = s*(s_gain+1);
                                                tmp = (tmp<0?0:tmp);
                                                tmp = (tmp>1?1:tmp);
                                                s = tmp;
                                        }
                                }
                return;
        }

        double dif_n = (double)GetS_NegDif();
        double dif_p = (double)GetS_PosDif();

        double low = h+dif_n;   //負向的diffusion邊界
        double high = h+dif_p;   //正向的diffusion邊界
        bool Is_dif = false;    //flag recording tmp_h to do diffusion or not
        double ratio;
        Is_dif = false;

        if(low <0 && h>low+360){
                h -=360;
                Is_dif = true;
        }
        else if(high>=360 && h<fmod(high,360)){
                h+=360;
                Is_dif = true;
        }
        else if(h>low && h<high){
                Is_dif = true;
        }
        if(Is_dif == true){
                if(h < trans_h){
                        ratio = 1-(trans_h-h)/dif_n*(-1);
                }else if(h >= trans_h){
                        ratio = 1-(h-trans_h)/dif_p;
                }
                if(ratio>1)
                        ShowMessage("S ratio >1");
                s = (ratio * s_gain/c +1)*s;
                if(s > 1)
                        s = 1;
                else if(s < 0)
                        s = 0;

        }
}

void __fastcall TC3DForm1::btn_directly_simClick(TObject *Sender)
{
        btn_directly_sim->Enabled = false;
        TC3D_SimualteForm *C3D_SimualteForm;
        C3D_SimualteForm = new TC3D_SimualteForm(this);

        int x = Img_3DLUT->Picture->Width;
        int y = Img_3DLUT->Picture->Height;

        int color;
        Graphics ::TBitmap *TmpBitmap;
        TmpBitmap=new Graphics::TBitmap();
        TmpBitmap->Width = x;
        TmpBitmap->Height = y;

        //double Y[15][11] ;
        for(int i = 0; i < x; i++)
                for(int j = 0; j < y; j++){
                        color = Img_3DLUT->Canvas->Pixels[i][j];
                        if(color==-1)
                                color = 0;

                        double r,g,b, r_new, g_new, b_new;
                        b = color/65536;
                        g = color/256%256;
                        r = color%256;
                        Direct_sim(r,g,b,&r_new,&g_new,&b_new);
                       /* if(r>=123 && r<=137 && g==255 && b>=27 && b<=37){
                                Y[(int)r-123][(int)b-27] = 0.299 * r_new + 0.587 * g_new + 0.114 * b_new;
                        }
                        
                        if((r==123 || r==137) && g==255 && (b==27 || b==37)){
                                r_new = 0;
                                g_new = 0;
                                b_new = 0;
                        } */
                        //Img_3DLUT->Canvas->Pixels[i][j] = (TColor)RGB(r_new,g_new,b_new);
                        C3D_SimualteForm->Image1->Canvas->Pixels[i][j] = (TColor)RGB(r_new,g_new,b_new);
                        //C3D_SimualteForm->Image2->Canvas->Pixels[i][j] = (TColor)RGB(((r-r_new)>0?(r-r_new)+20:0),0,0);
                        //C3D_SimualteForm->Image3->Canvas->Pixels[i][j] = (TColor)RGB(0,((g-g_new)>0?(g-g_new)+20:0),0);
                        //C3D_SimualteForm->Image4->Canvas->Pixels[i][j] = (TColor)RGB(0,0,((b_new-b)>0?(b_new-b)+20:0));
                }
        C3D_SimualteForm->Image1->Picture->SaveToFile("sim_tmp.bmp");
        Img_3DLUT->Picture->LoadFromFile("sim_tmp.bmp");

        delete TmpBitmap;
        /*
        if(!SaveDialog1->Execute()){
                return;
        }

        String Fpath = SaveDialog1->FileName;
        if(Fpath==NULL)
                return;

        FILE* fptr = fopen (Fpath.c_str(),"w");
        for(int i = 0; i < 15; i++)
                fprintf(fptr,"%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
                Y[i][0],Y[i][1],Y[i][2],Y[i][3],Y[i][4],Y[i][5],Y[i][6],Y[i][7],Y[i][8],Y[i][9],Y[i][10]);
        fclose(fptr);*/
        c3d_scrollbar_reset();
        btn_directly_sim->Enabled = true;
        C3D_SimualteForm->Show();

}
//---------------------------------------------------------------------------





void __fastcall TC3DForm1::sg_table_stepKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        for(int i = 0; i < 9; i++){
                tbl_val[0][i] = StrToInt(sg_table_step->Cells[i][1]);
        }
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::BitBtn1Click(TObject *Sender)
{
       C3Dini();
}
//---------------------------------------------------------------------------


void __fastcall TC3DForm1::BitBtn2Click(TObject *Sender)
{

        int x = Img_3DLUT->Picture->Width;
        int y = Img_3DLUT->Picture->Height;

        double r,g,b;
        double h = StrToFloat( LabeledEdit1->Text);
        hsv2rgb(h, 0.5, 128, &r, &g, &b);
        for(int i = 0; i < x; i++)
                for(int j = 0; j < y; j++)
                        Img_3DLUT->Canvas->Pixels[i][j] = (int)r+256*(int)g+65536*(int)b;

        edt_show_h->Visible = false;
}
//---------------------------------------------------------------------------


void __fastcall TC3DForm1::LabeledEdit1SubLabelClick(TObject *Sender)
{
        double h = StrToFloat( LabeledEdit1->Text);
        h+=5;
        LabeledEdit1->Text = FloatToStr(h);
        BitBtn2Click(Sender);
        TMouseButton Button; TShiftState Shift;
        Img_3DLUTMouseDown(Sender, Button, Shift, 100, 100);
}
//---------------------------------------------------------------------------

void __fastcall TC3DForm1::btn_sim_by_valClick(TObject *Sender)
{
       // sb_c3d_HSVBase_hdn->Position = 950;
       // sb_c3d_HSVBase_hdp->Position = 50;
        int tbl_n;
        if(rg_c3d_TblSize->ItemIndex==0){
                tbl_n = 0;
        }else if(rg_c3d_TblSize->ItemIndex==1){
                tbl_n = 1;
        }else if(rg_c3d_TblSize->ItemIndex==2){
                tbl_n = 2;
        }else if(rg_c3d_TblSize->ItemIndex==3){
                tbl_n = 3;
        }

        int idx_r, idx_g, idx_b;
        double r,g,b,h,s=0.6,v=0.6*255;

        for(int i = 0; i < 72; i++){
                h=i*5;
                hsv2rgb(h,s,v,&r,&g,&b);
                c3d_find_point(TBL_SIZE,tbl_n,r,g,b,&idx_r,&idx_g,&idx_b); //取block裡的最小點
                lb_c3d_tbl_ir->Caption = IntToStr(idx_r);
                lb_c3d_tbl_ig->Caption = IntToStr(idx_g);
                lb_c3d_tbl_ib->Caption = IntToStr(idx_b);
                sb_c3d_HSVBase_h->Position = 500+ sim_val[i]*10;
                c3d_hsvBase_adj(true);
        }
        btn_c3d_simClick(Sender);
}
//---------------------------------------------------------------------------



void __fastcall TC3DForm1::btn_dirSim_by_valClick(TObject *Sender)
{
        btn_c3d_simClick(Sender);
}
//---------------------------------------------------------------------------


//double ShowH=-30;
void __fastcall TC3DForm1::Img_3DLUTDblClick(TObject *Sender)
{
        double r,g,b,h,s,v;
        h = StrToFloat(lb_c3d_simH->Caption);
        s = StrToFloat(lb_c3d_simS->Caption);
        v = StrToFloat(lb_c3d_simV->Caption);
        r = StrToFloat(lb_c3d_simR->Caption);
        g = StrToFloat(lb_c3d_simG->Caption);
        b = StrToFloat(lb_c3d_simB->Caption);

        double H_step = StrToFloat(Form3->EditH->Text);
        double S_step = StrToFloat(Form3->EditS->Text);
        double V_step = StrToFloat(Form3->EditV->Text);

        TCanvas *pCanvas = Form3->Image1->Canvas;
        for(int i=0; i<5; i++)
                for( int j=0; j<5; j++){
                        hsv2rgb(h+(i-2)*H_step,s+(j-2)*S_step,v,&r,&g,&b);
                        pCanvas->Brush->Color = (int)r+256*(int)g+65536*(int)b;;
                        pCanvas->Brush->Style = bsSolid;
                        pCanvas->Rectangle(i*140+0, j*140+0, i*140+140, j*140+140);
                }
        TCanvas *pCanvas2 = Form3->Image2->Canvas;
        for(int i=0; i<5; i++)
                for( int j=0; j<5; j++){
                        hsv2rgb(h+(i-2)*H_step,s,v+(j-2)*V_step,&r,&g,&b);
                        pCanvas2->Brush->Color = (int)r+256*(int)g+65536*(int)b;;
                        pCanvas2->Brush->Style = bsSolid;
                        pCanvas2->Rectangle(i*140+0, j*140+0, i*140+140, j*140+140);
                }


        /*
        int x = Img_3DLUT->Width;
        int y = Img_3DLUT->Height;

        ShowH += 30;
        if(ShowH == 360)
                ShowH = 0;
        double r,g,b;

        hsv2rgb(ShowH, 0.5, 128, &r, &g, &b);
        for(int i = 0; i < x; i++)
                for(int j = 0; j < y; j++)
                        Img_3DLUT->Canvas->Pixels[i][j] = (int)r+256*(int)g+65536*(int)b;
        edt_show_h->Visible = true;
        edt_show_h->Text = FloatToStr(ShowH);*/
}
//---------------------------------------------------------------------------

