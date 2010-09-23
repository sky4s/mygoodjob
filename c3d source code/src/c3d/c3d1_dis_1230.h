//---------------------------------------------------------------------------

#ifndef c3d1_dis_1230H
#define c3d1_dis_1230H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Unit1.h"
#define  C3DChkBox_Nbr 1
#include <windows.h>
//---------------------------------------------------------------------------
class AbstC3D
{
        public:
                virtual TBit SetEn()=0;
                virtual TBit* SetChkBx()=0;
                virtual TLUT* SetLUT()=0;
};

//---------------------------------------------------------------------------


class TC3DForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *Img_3DLUT;
        TCheckBox *cb_en;
        TCheckBox *cb_demo;
        TButton *btn_c3d_load_img;
        TButton *btn_c3d_sim;
        TBitBtn *BitBtn_c3d_undo;
        TRadioGroup *rg_c3d_hsv_mode;
        TPageControl *PageControl7;
        TTabSheet *TabSheet23;
        TGroupBox *GroupBox44;
        TGroupBox *GroupBox34;
        TImage *Img_c3d_sel;
        TLabel *lb_c3d_selR;
        TLabel *lb_c3d_selH;
        TLabel *lb_c3d_selG;
        TLabel *lb_c3d_selB;
        TLabel *lb_c3d_selV;
        TLabel *lb_c3d_selS;
        TLabel *lb_c3d_selI;
        TLabel *Label190;
        TLabel *Label198;
        TLabel *Label202;
        TLabel *Label206;
        TLabel *Label208;
        TLabel *Label209;
        TLabel *Label213;
        TGroupBox *GroupBox45;
        TImage *Img_c3d_sim;
        TLabel *lb_c3d_simR;
        TLabel *lb_c3d_simH;
        TLabel *lb_c3d_simG;
        TLabel *lb_c3d_simB;
        TLabel *lb_c3d_simV;
        TLabel *lb_c3d_simS;
        TLabel *lb_c3d_simI;
        TLabel *Label246;
        TLabel *Label247;
        TLabel *Label248;
        TLabel *Label249;
        TLabel *Label250;
        TLabel *Label251;
        TLabel *Label252;
        TTabSheet *TabSheet24;
        TGroupBox *GroupBox22;
        TGroupBox *GroupBox35;
        TImage *Img_c3d_tbl;
        TLabel *lb_c3d_tblR;
        TLabel *lb_c3d_tblG;
        TLabel *lb_c3d_tblB;
        TLabel *lb_c3d_tblH;
        TLabel *lb_c3d_tblS;
        TLabel *lb_c3d_tblI;
        TLabel *lb_c3d_tblV;
        TLabel *Label215;
        TLabel *Label216;
        TLabel *Label219;
        TLabel *Label220;
        TLabel *Label221;
        TLabel *Label222;
        TLabel *Label223;
        TGroupBox *GroupBox37;
        TImage *Img_c3d_cor;
        TLabel *lb_c3d_corG;
        TLabel *lb_c3d_corB;
        TLabel *lb_c3d_corH;
        TLabel *lb_c3d_corS;
        TLabel *lb_c3d_corI;
        TLabel *lb_c3d_corV;
        TLabel *lb_c3d_corR;
        TLabel *Label224;
        TLabel *Label225;
        TLabel *Label226;
        TLabel *Label227;
        TLabel *Label228;
        TLabel *Label229;
        TLabel *Label230;
        TGroupBox *GroupBox46;
        TLabel *lb_c3d_showY;
        TLabel *lb_c3d_showX;
        TGroupBox *GroupBox4;
        TLabel *lb_c3d_showG;
        TLabel *lb_c3d_showB;
        TLabel *lb_c3d_showR;
        TGroupBox *GroupBox9;
        TLabel *lb_c3d_showS;
        TLabel *lb_c3d_showH;
        TLabel *lb_c3d_showI;
        TLabel *lb_c3d_showV;
        TButton *btn_c3d_reset;
        TButton *btn_c3d_load;
        TButton *btn_c3d_save;
        TButton *btn_c3d_write;
        TButton *btn_c3d_check;
        TGroupBox *GroupBox36;
        TRadioButton *rb_c3d_point;
        TRadioButton *rb_c3d_r;
        TRadioButton *rb_c3d_y;
        TRadioButton *rb_c3d_g;
        TRadioButton *rb_c3d_c;
        TRadioButton *rb_c3d_b;
        TRadioButton *rb_c3d_m;
        TStringGrid *sg_c3d_hsvi;
        TStaticText *StaticText34;
        TStaticText *StaticText35;
        TStaticText *StaticText36;
        TStaticText *StaticText37;
        TPageControl *PageC_c3d_adj;
        TTabSheet *TabSheet20;
        TGroupBox *gb_c3d_RGB_adj;
        TLabel *Label181;
        TLabel *lb_c3d_rgb_dis;
        TPageControl *PageControl3;
        TTabSheet *TS_C3D_RGB;
        TLabel *Label182;
        TLabel *Label183;
        TLabel *Label184;
        TLabel *lb_c3d_rgb_r;
        TLabel *lb_c3d_rgb_g;
        TLabel *lb_c3d_rgb_b;
        TScrollBar *sb_c3d_rgb_r;
        TScrollBar *sb_c3d_rgb_g;
        TScrollBar *sb_c3d_rgb_b;
        TTabSheet *TS_C3D_HSV;
        TLabel *Label186;
        TLabel *Label187;
        TLabel *Label188;
        TLabel *lb_c3d_hsv_h;
        TLabel *lb_c3d_hsv_s;
        TLabel *lb_c3d_hsv_v;
        TLabel *Label232;
        TLabel *Label234;
        TScrollBar *sb_c3d_hsv_h;
        TScrollBar *sb_c3d_hsv_s;
        TScrollBar *sb_c3d_hsv_v;
        TScrollBar *sb_c3d_hsv_i;
        TScrollBar *sb_c3d_rgb_dis;
        TTabSheet *TabSheet22;
        TGroupBox *gb_c3d_HSI_adj;
        TGroupBox *GroupBox40;
        TLabel *Label185;
        TLabel *lb_c3d_HSVBase_h;
        TLabel *Label197;
        TLabel *lb_c3d_HSVBase_hdn;
        TLabel *lb_c3d_HSVBase_hdp;
        TLabel *Label203;
        TLabel *Label204;
        TScrollBar *sb_c3d_HSVBase_h;
        TScrollBar *sb_c3d_HSVBase_hdn;
        TScrollBar *sb_c3d_HSVBase_hdp;
        TCheckBox *cb_c3d_HSVBase_h_rt;
        TGroupBox *GroupBox41;
        TLabel *Label205;
        TLabel *lb_c3d_HSVBase_s;
        TLabel *Label207;
        TLabel *lb_c3d_HSVBase_sdn;
        TLabel *lb_c3d_HSVBase_sdp;
        TLabel *Label210;
        TLabel *Label211;
        TScrollBar *sb_c3d_HSVBase_s;
        TScrollBar *sb_c3d_HSVBase_sdn;
        TScrollBar *sb_c3d_HSVBase_sdp;
        TEdit *edt_c3d_satC;
        TCheckBox *cb_c3d_HSVBase_s_ge;
        TPageControl *PageControl4;
        TTabSheet *TabSheet4;
        TGroupBox *GroupBox43;
        TLabel *Label236;
        TLabel *lb_c3d_HSVBase_v;
        TLabel *lb_c3d_HSVBase_vdn;
        TLabel *lb_c3d_HSVBase_vdp;
        TLabel *Label241;
        TLabel *Label242;
        TScrollBar *sb_c3d_HSVBase_v;
        TScrollBar *sb_c3d_HSVBase_vdn;
        TScrollBar *sb_c3d_HSVBase_vdp;
        TEdit *edt_c3d_valC;
        TTabSheet *TabSheet1;
        TGroupBox *GroupBox42;
        TLabel *Label212;
        TLabel *lb_c3d_HSVBase_i;
        TLabel *lb_c3d_HSVBase_idn;
        TLabel *lb_c3d_HSVBase_idp;
        TLabel *Label217;
        TLabel *Label218;
        TScrollBar *sb_c3d_HSVBase_i;
        TScrollBar *sb_c3d_HSVBase_idn;
        TScrollBar *sb_c3d_HSVBase_idp;
        TCheckBox *cb_c3d_HSVBase_v_ge;
        TOpenDialog *OpenDialog1;
        TGroupBox *GroupBox38;
        TLabel *Label231;
        TLabel *lb_c3d_tbl_ir;
        TLabel *Label233;
        TLabel *lb_c3d_tbl_ig;
        TLabel *Label235;
        TLabel *lb_c3d_tbl_ib;
        TRadioGroup *rg_c3d_interpl;
        TSaveDialog *SaveDialog1;
        TButton *btn_c3d_load_rgb;
        TButton *btn_tbl_search;
        TButton *btn_directly_sim;
        TTabSheet *TabSheet2;
        TStringGrid *sg_table_step;
        TBitBtn *BitBtn1;
        TLabeledEdit *LabeledEdit1;
        TBitBtn *BitBtn2;
        TButton *btn_sim_by_val;
        TButton *btn_dirSim_by_val;
        TEdit *edt_show_h;
        TCheckBox *CheckBox1;
        TRadioGroup *rg_c3d_TblSize;
        TStringGrid *sg_rgb_input;
        TBitBtn *btn_key_in_RGB;
        TComboBox *cb_sim_type;
        TBitBtn *btn_key_in_HSV;
        TEdit *Edit_h_adj;
        TEdit *Edit_s_adj;
        TEdit *Edit_v_adj;
        TCheckBox *CheckBox2;
        TEdit *Edit1;
        void __fastcall btn_c3d_load_imgClick(TObject *Sender);
        void __fastcall rg_c3d_interplClick(TObject *Sender);
        void __fastcall btn_c3d_simClick(TObject *Sender);
        void __fastcall rg_c3d_TblSizeClick(TObject *Sender);
        void __fastcall rb_c3d_pointClick(TObject *Sender);
        void __fastcall rb_c3d_colorClick(TObject *Sender);
        void __fastcall btn_c3d_resetClick(TObject *Sender);
        void __fastcall btn_c3d_loadClick(TObject *Sender);
        void __fastcall btn_c3d_saveClick(TObject *Sender);
        void __fastcall btn_c3d_writeClick(TObject *Sender);
        void __fastcall sb_c3d_rgb_disChange(TObject *Sender);
        void __fastcall sb_c3d_rgb_rChange(TObject *Sender);
        void __fastcall sb_c3d_rgb_gChange(TObject *Sender);
        void __fastcall sb_c3d_rgb_bChange(TObject *Sender);
        void __fastcall sb_c3d_hsv_Change(TObject *Sender);
        void __fastcall sb_c3d_HSVBase_hChange(TObject *Sender);
        void __fastcall sb_c3d_HSVBase_hdnChange(TObject *Sender);
        void __fastcall sb_c3d_HSVBase_hdpChange(TObject *Sender);
        void __fastcall sb_c3d_HSVBase_sChange(TObject *Sender);
        void __fastcall sb_c3d_HSVBase_sdnChange(TObject *Sender);
        void __fastcall sb_c3d_HSVBase_sdpChange(TObject *Sender);
        void __fastcall sb_c3d_HSVBase_vChange(TObject *Sender);
        void __fastcall sb_c3d_HSVBase_vdnChange(TObject *Sender);
        void __fastcall sb_c3d_HSVBase_vdpChange(TObject *Sender);
        void __fastcall Img_3DLUTMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall Img_3DLUTMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall BitBtn_c3d_undoClick(TObject *Sender);
        void __fastcall btn_c3d_checkClick(TObject *Sender);
        void __fastcall cb_enClick(TObject *Sender);
        void __fastcall CheckBox_Click(TObject *Sender);
        void __fastcall btn_c3d_load_rgbClick(TObject *Sender);
        void __fastcall btn_tbl_searchClick(TObject *Sender);
        void __fastcall btn_directly_simClick(TObject *Sender);
        void __fastcall sg_table_stepKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall LabeledEdit1SubLabelClick(TObject *Sender);
        void __fastcall btn_sim_by_valClick(TObject *Sender);
        void __fastcall btn_dirSim_by_valClick(TObject *Sender);
        void __fastcall Img_3DLUTDblClick(TObject *Sender);
        void __fastcall btn_key_in_RGBClick(TObject *Sender);
        void __fastcall btn_key_in_HSVClick(TObject *Sender);
        void __fastcall Edit_h_adjKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Edit_s_adjKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Edit_v_adjKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall CheckBox2Click(TObject *Sender);

private:	// User declarations
public:		// User declarations
        __fastcall TC3DForm1(TComponent* Owner);
        __fastcall ~TC3DForm1();
        double ***c3d_lutR,***c3d_lutG, ***c3d_lutB;
        double ***c3d_lutH, ***c3d_lutS, ***c3d_lutV, ***c3d_lutI;
        double ***tmp_c3d_lutR, ***tmp_c3d_lutG, ***tmp_c3d_lutB, ***tmp_c3d_lutH, ***tmp_c3d_lutS,***tmp_c3d_lutV;
        bool interpol;  //true: techehedral, false: trilinear
        TBit* cb;
        _CHKB** ChkB;
        TLUT* lut;
        _CHKB en;
        bool C3D_Chg;
        void cal_c3d_rgb(bool flg_wri);
        void C3Dsim(double r, double g, double b, double* r_new, double* g_new, double* b_new);
        void C3Dsim_t(double r, double g, double b,double* r_new, double* g_new, double* b_new);
        void Show_c3d_CorImg(double cor_r, double cor_g, double cor_b);
        void Show_c3d_SimImg(double sim_r, double sim_g, double sim_b);
        void refresh_c3d_grid(double r, double g, double b);
        void refresh_c3d_grid_t(double r, double g, double b);
        void c3d_grid(int c, int r, int g, int b);
        void c3d_tmp_tbl_save();
        void c3d_scrollbar_reset();
        void C3Dini();
        void Show_c3d_TblImg(double tbl_r, double tbl_g, double tbl_b);
        void Show_c3d_SelImg(double sel_r, double sel_g, double sel_b);
        bool c3d_lutArrange();
        void new_array();
        void delete_array();

        double GetH_val();
        void SetH_caption(double H);
        void Adjust_H_diffusion(double H);
        int GetH_PosDif();
        int GetH_NegDif();
        int GetS_PosDif();
        int GetS_NegDif();
        int GetS_val();
        void SetS_Caption(int S);
        int GetV_PosDif();
        int GetV_NegDif();
        void SetV_Caption(int V);
        int GetV_val();
        void ShowColor();

        //method 2
      /*  void c3d_6axisAdj_h(bool flag);
        void c3d_6axisAdj_s(bool flag);
        void c3d_6axisAdj_v(bool flag);
         */

        //methid 1
        void c3d_hsvBase_adj(bool flg_wri);
        void c3d_HSVBase_h_adj();
        void c3d_HSVBase_s_adj();
        void c3d_HSVBase_v_adj();

        //methid 3
        void c3d_MixAdj_h(bool flag);
        void c3d_MixAdj_s(bool flag);
        void c3d_MixAdj_v(bool flag);
        void Direct_sim(double r, double g, double b, double* r_new,double* g_new, double* b_new);
        void c3d_MixAdj_r(int type, double dif_p, double dif_n, double gain);
        //method 4
        void c3d_hsv_FixGain_h(double tmp_c3d_lutH[9][9][9]);
        void c3d_hsv_FixGain(bool flg_wri);

        void caculte_HSV_disc();
        void caculate_disc();
        void caculte_NCTU_dif();
        void Caculate_dif_table(double*** c3d_dif_lutR, double*** c3d_dif_lutG, double*** c3d_dif_lutB, double*** c3d_dif, int modif);
        void C3Dsim_dif(double r, double g, double b,double* r_new,double* g_new, double* b_new, double*** c3d_dif);

};
//---------------------------------------------------------------------------
extern PACKAGE TC3DForm1 *C3DForm1;
//---------------------------------------------------------------------------

void fix_val(double* value, double upbound)
{
        if(*value<0)
                *value = 0;
        else if(*value>upbound)
                *value = upbound;
}
void c3d_Aratio(int i_r,int i_g,int i_b,double* rat, int d)
{

        double tmp;
        *rat = d;
        for(int i = i_r; i <= i_r+1; i++)
                for(int j = i_g; j <= i_g+1; j++)
                        for(int k = i_b; k <= i_b+1; k++){
                                if(sqrt(double(i*i+j*j+k*k))<d){
                                        tmp = sqrt(double(i*i+j*j+k*k));
                                        *rat = (*rat>tmp?tmp:*rat);
                                }
                        }

}

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
        buffer = (char*) malloc (sizeof(char)*lSize);
        if(buffer == NULL)
                return 0;
        // copy the file into the buffer:
        fread (buffer,1,lSize,fptr);
        fclose(fptr);
        return buffer;
}
void rgb2h(double r, double g, double b, double *h)
{
        r = r/255;
        g = g/255;
        b = b/255;
        double tmp = 0.5*((r-g)+(r-b))/pow(pow(r-g,2)+(r-b)*(g-b),0.5);
        if(tmp>1)
                tmp=1;
        else if(tmp<-1)
                tmp=-1;
        *h = acos(tmp)*180/3.14159265;
        if(b>g)
                *h = 360-*h;
}
void rgb2hsv(double r, double g, double b, double *h, double *s, double *i, double *v)
{
        *i = (r+g+b)/3;
        double max = (r>g?r:g);
        max = (b>max?b:max);
        *v = max;
        double min = (r<g?r:g);
        min = (min<b?min:b);
        double d = max-min;
        *s = d;
        d = (d==0?d+256:d);

        if(max==0)
                *s = 0;
        else
                *s = *s/max;

        if(s==0)
                *h = 0;
        else {
        if(max==r)
                *h = 60*(g-b)/d;
        else if(max==g)
                *h = 60*(b-r)/d+120;
        else if(max==b)
                *h = 60*(r-g)/d+240;
        *h = fmod(*h+360,360);

        /*        r /= 255;
                g /= 255;
                b /= 255;

                double tmp = 0.5*((r-g)+(r-b))/pow(pow(r-g,2)+(r-b)*(g-b),0.5);
                tmp = (tmp<-1?-1:tmp);
                tmp = (tmp>1?1:tmp);
                *h = acos(tmp)*180/3.14159265;
                if(b>g)
                        *h = 360-*h;*/
        }

}

void hsv2rgb(double h, double s, double v, double* r, double* g, double* b)
{
        s = (s<0?0:s);
        s = (s>1?1:s);
        v = (v<0?0:v);
        v = (v>255?255:v);
        h = (h>360?360:h);
        h = (h<0?h+360:h);
        int hi = int(floor(h/60))%6;
        double f = h/60-floor(h/60);
        double p = v*(1-s);
        double q = v*(1-f*s);
        double t = v*(1-(1-f)*s);
        if(hi==0){
                *r = v;
                *g = t;
                *b = p;
        }else if(hi == 1){
                *r = q;
                *g = v;
                *b = p;
        }else if(hi == 2){
                *r = p;
                *g = v;
                *b = t;
        }else if(hi == 3){
                *r = p;
                *g = q;
                *b = v;
        }else if(hi == 4){
                *r = t;
                *g = p;
                *b = v;
        }else if(hi == 5){
                *r = v;
                *g = p;
                *b = q;
        }
}

void rgb2hsi(double r, double g, double b, double *h, double *s, double *i)
{
        r /= 255;
        g /= 255;
        b /= 255;

        double tmp = 0.5*((r-g)+(r-b))/pow(pow(r-g,2)+(r-b)*(g-b),0.5);
        tmp = (tmp<-1?-1:tmp);
        tmp = (tmp>1?1:tmp);
        *h = acos(tmp)*180/3.14159265;
        if(b>g)
                *h = 360-*h;

        double min = (r<g?r:g);
        min = (min<b?min:b);
        *s = 1-3*min/(r+g+b);
        *i = (r+g+b)/3;
}
//---------------------------------------------------------------------------
bool hsi2rgb(double h, double s, double i, double* r, double* g, double* b)
{
        double PI = 3.14159265;
        if(h<120){
                *b = i*(1-s);
                *r = i*(1+s*cos(h*PI/180)/cos((60-h)*PI/180));
                *g = 3*i-(*r+*b);
        }else if(h<240){
                h = h-120;
                *r = i*(1-s);
                *g = i*(1+s*cos(h*PI/180)/cos((60-h)*PI/180));
                *b = 3*i-(*r+*g);
        }else{
                h = h-240;
                *g = i*(1-s);
                *b = i*(1+s*cos(h*PI/180)/cos((60-h)*PI/180));
                *r = 3*i-(*g+*b);
        }
        *r *= 255;
        *g *= 255;
        *b *= 255;
        return 1;
}
#endif
/*
bool hsi2rgb(double H, double S, double I, double* R, double* G, double* B)
{
        double h, s, i;
        double r, g, b;
        double x, y, z;
        double PI = 3.14159265;
        h = H*PI/180;
        s = S;
        i = I/255;

        if(H <= 120) {
                b = i*(1-s);
                r = i*(1+ ((s*cos(h))/(cos(PI/3-h))) );
                g = 3*i-(b+r);
        } else if( H>120 && H<=240 ){
                h=h-2*PI/3;
                r = i*(1-s);
                g = i*(1+ ((s*cos(h))/(cos(PI/3-h))) );
                b = 3*i-(r+g);
        } else if( H>240){
                h=h-4*PI/3;
                g = i*(1-s);
                b = i*(1+ ((s*cos(h))/(cos(PI/3-h))) );
                r = 3*i-(g+b);
        }

        *R = r*255;
        *G = g*255;
        *B = b*255;
        if(*R>=256 || *G>=256 || *B>=256 )
                return false;
        else return true;
}
*/

/*  method from wiki
void rgb2hsv(double r, double g, double b, double *h, double *s, double *i, double *v)
{
        r = (int)r;
        g = (int)g;
        b = (int)b;
        *i = (r+g+b)/3;
        //double min = (r<g?r:g);
        //min = (min<b?min:b);
        //*s = 1-3*(min/(r+g+b));

        if(r==g && g==b){
                *h = 0;
                *s = 0;
                *v = r;
        }else if(r>=g && g>=b){
                *h = fmod((60*(g-b)/(r-b)),360);
                *s = 1-b/r;
                *v = r;
        }else if(r>=b && b>=g){
                *h = fmod((60*(g-b)/(r-g)+360),360);
                *s = 1-g/r;
                *v = r;
        }else if(g>=r && r>=b){
                *h = fmod((60*(b-r)/(g-b)+360+120),360);
                *s = 1-b/g;
                *v = g;
        }else if(g>=b && b>=r){
                *h = fmod((60*(b-r)/(g-r)+120),360);
                *s = 1-r/g;
                *v = g;
        }else if(b>=r && r>=g){
                *h = fmod((60*(r-g)/(b-g)+240),360);
                *s = 1-g/b;
                *v = b;
        }else if(b>=g && g>=r){
                *h = fmod((60*(r-g)/(b-r)+360+240),360);
                *s = 1-r/b;
                *v = b;
        }
}
*/
