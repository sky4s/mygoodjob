//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "THSVStepSimForm.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <gui/c3d/TC3DForm.h>
#include "TC3D_SimualteForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THSVStepSimForm *HSVStepSimForm;
//---------------------------------------------------------------------------
__fastcall THSVStepSimForm::THSVStepSimForm(TComponent* Owner)
        : TForm(Owner)
{


}
//---------------------------------------------------------------------------


void __fastcall THSVStepSimForm::Image1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        double h_bas = StrToFloat(HSVStepSimForm->lb_c3d_sim_H_step->Caption);
        double s_bas = StrToFloat(HSVStepSimForm->lb_c3d_sim_S_step->Caption);
        //double v_bas = StrToFloat(Form3->lb_c3d_sim_V_step->Caption);

        double h_move = h_bas*(floor(double(X)/80)-2);
        double s_move = s_bas*(floor(double(Y)/80)-2)*(-1);
        double v_move = 0;

        double Ratio_s = StrToFloat(C3DForm1->edt_c3d_satC->Text);
        double s = StrToFloat(C3DForm1->lb_c3d_selS->Caption);

        if(C3DForm1->pc_Adjust->TabIndex==1 && C3DForm1->pc_point_color_adj->TabIndex == 0){
                //Point Color - RGB Domain
                C3DForm1->sb_c3d_hsv_h->Position = C3DForm1->sb_c3d_hsv_h->Max/2 + h_move*2;

                s_move = s_move/s;
                C3DForm1->sb_c3d_hsv_s->Position = C3DForm1->sb_c3d_hsv_s->Max/2 + s_move*Ratio_s*100;
                C3DForm1->sb_c3d_hsv_v->Position = C3DForm1->sb_c3d_hsv_v->Max/2;

        }else if(C3DForm1->pc_Adjust->TabIndex==1 && C3DForm1->pc_point_color_adj->TabIndex == 1){
                //Point Color - HSV Domain
                C3DForm1->sb_c3d_Point_HSV_h->Position = C3DForm1->sb_c3d_Point_HSV_h->Max/2+h_move;

                s_move = s_move/s;
                C3DForm1->sb_c3d_Point_HSV_s->Position = C3DForm1->sb_c3d_Point_HSV_s->Max/2+s_move*Ratio_s*100;
                C3DForm1->sb_c3d_Point_HSV_v->Position = C3DForm1->sb_c3d_Point_HSV_v->Max/2;

        }else if(C3DForm1->pc_Adjust->TabIndex==0 && C3DForm1->pc_global_adj->TabIndex == 1){
                //Manual 39 color (HSV)
                h_move += StrToFloat(Text_H_move->Caption);
                C3DForm1->sb_c3d_Manual39_h->Position = h_move+C3DForm1->sb_c3d_Manual39_h->Max/2;

                s_move = s_move*Ratio_s*100 + StrToFloat(Text_S_move->Caption);
                C3DForm1->sb_c3d_Manual39_s->Position = s_move+C3DForm1->sb_c3d_Manual39_s->Max/2;

                v_move = StrToFloat(Text_V_move->Caption);
                C3DForm1->sb_c3d_Manual39_v->Position = v_move+C3DForm1->sb_c3d_Manual39_v->Max/2;
        }
}
//---------------------------------------------------------------------------

void __fastcall THSVStepSimForm::Image2MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        double h_bas = StrToFloat(HSVStepSimForm->lb_c3d_sim_H_step->Caption);
        //double s_bas = StrToFloat(Form3->lb_c3d_sim_S_step->Caption);
        double v_bas = StrToFloat(HSVStepSimForm->lb_c3d_sim_V_step->Caption);

        double h_move = h_bas*(floor(double(X)/80)-2);
        double v_move = v_bas*(floor(double(Y)/80)-2)*(-1);
        double s_move = 0;

        double Ratio_v = StrToFloat(C3DForm1->edt_c3d_valC->Text);
        double v = StrToFloat(C3DForm1->lb_c3d_selV->Caption);

        if(C3DForm1->pc_Adjust->TabIndex==1 && C3DForm1->pc_point_color_adj->TabIndex == 0){
                //Point Color - RGB Domain
                C3DForm1->sb_c3d_hsv_h->Position = C3DForm1->sb_c3d_hsv_h->Max/2 + h_move*2;
                C3DForm1->sb_c3d_hsv_s->Position = C3DForm1->sb_c3d_hsv_s->Max/2;

                v_move = v_move/v;
                C3DForm1->sb_c3d_hsv_v->Position = C3DForm1->sb_c3d_hsv_v->Max/2 + v_move*Ratio_v*100;

        }else if(C3DForm1->pc_Adjust->TabIndex==1 && C3DForm1->pc_point_color_adj->TabIndex == 1){
                //Point Color - HSV Domain
                C3DForm1->sb_c3d_Point_HSV_h->Position = C3DForm1->sb_c3d_Point_HSV_h->Max/2+h_move;
                C3DForm1->sb_c3d_Point_HSV_s->Position = C3DForm1->sb_c3d_Point_HSV_s->Max/2;

                v_move = v_move/v;
                C3DForm1->sb_c3d_Point_HSV_v->Position = C3DForm1->sb_c3d_Point_HSV_v->Max/2+v_move*Ratio_v*100;

        }else if(C3DForm1->pc_Adjust->TabIndex==0 && C3DForm1->pc_global_adj->TabIndex == 1){
                //Manual 39 color (HSV)
                h_move += StrToFloat(Text_H_move->Caption);
                C3DForm1->sb_c3d_Manual39_h->Position = h_move+C3DForm1->sb_c3d_Manual39_h->Max/2;

                s_move = StrToFloat(Text_S_move->Caption);
                C3DForm1->sb_c3d_Manual39_s->Position = s_move+C3DForm1->sb_c3d_Manual39_s->Max/2;

                v_move += StrToFloat(Text_V_move->Caption);
                C3DForm1->sb_c3d_Manual39_v->Position = v_move+C3DForm1->sb_c3d_Manual39_v->Max/2;
        }
}
//---------------------------------------------------------------------------

void __fastcall THSVStepSimForm::Image3MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        //double h_bas = StrToFloat(Form3->lb_c3d_sim_H_step->Caption);
        double s_bas = StrToFloat(HSVStepSimForm->lb_c3d_sim_S_step->Caption);
        double v_bas = StrToFloat(HSVStepSimForm->lb_c3d_sim_V_step->Caption);

        double h_move = 0;
        double s_move = s_bas*(floor(double(X)/80)-2);
        double v_move = v_bas*(floor(double(Y)/80)-2)*(-1);

        double Ratio_s = StrToFloat(C3DForm1->edt_c3d_satC->Text);
        double Ratio_v = StrToFloat(C3DForm1->edt_c3d_valC->Text);

        double s = StrToFloat(C3DForm1->lb_c3d_selS->Caption);
        double v = StrToFloat(C3DForm1->lb_c3d_selV->Caption);

        if(C3DForm1->pc_Adjust->TabIndex==1 && C3DForm1->pc_point_color_adj->TabIndex == 0){
                //Point Color - RGB Domain
                C3DForm1->sb_c3d_hsv_h->Position = C3DForm1->sb_c3d_hsv_h->Max/2 + h_move*2;

                s_move = s_move/s;
                C3DForm1->sb_c3d_hsv_s->Position = C3DForm1->sb_c3d_hsv_s->Max/2 + s_move*Ratio_s*100;

                v_move = v_move/v;
                C3DForm1->sb_c3d_hsv_v->Position = C3DForm1->sb_c3d_hsv_v->Max/2 + v_move*Ratio_v*100;

        }else if(C3DForm1->pc_Adjust->TabIndex==1 && C3DForm1->pc_point_color_adj->TabIndex == 1){
                //Point Color - HSV Domain
                C3DForm1->sb_c3d_Point_HSV_h->Position = C3DForm1->sb_c3d_Point_HSV_h->Max/2+h_move;

                s_move = s_move/s;
                C3DForm1->sb_c3d_Point_HSV_s->Position = C3DForm1->sb_c3d_Point_HSV_s->Max/2+s_move*Ratio_s*100;

                v_move = v_move/v;
                C3DForm1->sb_c3d_Point_HSV_v->Position = C3DForm1->sb_c3d_Point_HSV_v->Max/2+v_move*Ratio_v*100;

        }else if(C3DForm1->pc_Adjust->TabIndex==0 && C3DForm1->pc_global_adj->TabIndex == 1){
                //Manual 39 color (HSV)
                h_move += StrToFloat(Text_H_move->Caption);
                C3DForm1->sb_c3d_Manual39_h->Position = h_move+C3DForm1->sb_c3d_Manual39_h->Max/2;

                s_move = s_move*Ratio_s*100 + StrToFloat(Text_S_move->Caption);
                C3DForm1->sb_c3d_Manual39_s->Position = s_move+C3DForm1->sb_c3d_Manual39_s->Max/2;

                v_move = v_move*Ratio_v*100 + StrToFloat(Text_V_move->Caption);
                C3DForm1->sb_c3d_Manual39_v->Position = v_move+C3DForm1->sb_c3d_Manual39_v->Max/2;
        }
}
//---------------------------------------------------------------------------
void THSVStepSimForm::ResetClickAdj()
{
        if(C3DForm1->pc_Adjust->TabIndex==1 && C3DForm1->pc_point_color_adj->TabIndex == 0){
                //Point Color - RGB Domain
                C3DForm1->sb_c3d_hsv_h->Position = C3DForm1->sb_c3d_hsv_h->Max/2;
                C3DForm1->sb_c3d_hsv_s->Position = C3DForm1->sb_c3d_hsv_s->Max/2;
                C3DForm1->sb_c3d_hsv_v->Position = C3DForm1->sb_c3d_hsv_v->Max/2;
        }else if(C3DForm1->pc_Adjust->TabIndex==1 && C3DForm1->pc_point_color_adj->TabIndex == 1){
                C3DForm1->sb_c3d_Point_HSV_h->Position = C3DForm1->sb_c3d_Point_HSV_h->Max/2;
                C3DForm1->sb_c3d_Point_HSV_s->Position = C3DForm1->sb_c3d_Point_HSV_s->Max/2;
                C3DForm1->sb_c3d_Point_HSV_v->Position = C3DForm1->sb_c3d_Point_HSV_v->Max/2;
        }else if(C3DForm1->pc_Adjust->TabIndex==0 && C3DForm1->pc_global_adj->TabIndex == 1){
                C3DForm1->sb_c3d_Manual39_h->Position = StrToFloat(Text_H_move->Caption)+C3DForm1->sb_c3d_Manual39_h->Max/2;
                C3DForm1->sb_c3d_Manual39_s->Position = StrToFloat(Text_S_move->Caption)+C3DForm1->sb_c3d_Manual39_s->Max/2;
                C3DForm1->sb_c3d_Manual39_v->Position = StrToFloat(Text_V_move->Caption)+C3DForm1->sb_c3d_Manual39_v->Max/2;
        }
}

void __fastcall THSVStepSimForm::sb_c3d_sim_H_stepChange(TObject *Sender)
{
        ResetClickAdj();
        lb_c3d_sim_H_step->Caption = sb_c3d_sim_H_step->Position;
        if(C3DForm1->fl_ref_HSV_img_col == 1)
                C3DForm1->c3d_Sim_Color_HSV_StepClick(Sender);
        else
                C3DForm1->c3d_Sim_Image_HSV_StepClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THSVStepSimForm::sb_c3d_sim_S_stepChange(TObject *Sender)
{
        ResetClickAdj();
        lb_c3d_sim_S_step->Caption = FloatToStr(StrToFloat(sb_c3d_sim_S_step->Position)/100);
        if(C3DForm1->fl_ref_HSV_img_col == 1)
                C3DForm1->c3d_Sim_Color_HSV_StepClick(Sender);
        else
                C3DForm1->c3d_Sim_Image_HSV_StepClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall THSVStepSimForm::sb_c3d_sim_V_stepChange(TObject *Sender)
{
        ResetClickAdj();
        lb_c3d_sim_V_step->Caption = sb_c3d_sim_V_step->Position;
        if(C3DForm1->fl_ref_HSV_img_col == 1)
                C3DForm1->c3d_Sim_Color_HSV_StepClick(Sender);
        else
                C3DForm1->c3d_Sim_Image_HSV_StepClick(Sender);
}
//---------------------------------------------------------------------------

