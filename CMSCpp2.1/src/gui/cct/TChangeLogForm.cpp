//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TChangeLogForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TChangeLogForm *ChangeLogForm;
//---------------------------------------------------------------------------
__fastcall TChangeLogForm::TChangeLogForm(TComponent * Owner)
:TForm(Owner)
{
    Memo1->Text = "\
       [3.4 build 1.42] 2012/09/14\r\n\
       +�䴩TCON 62301�H�Ψ�DirectGamma\r\n\
       \r\n\
       [3.4 build 1.41] 2012/08/31\r\n\
       +PanelRegulator����DGLut�MGammaTest\r\n\
       +Target White�U�W�[De-WhiteError�\��,��:\r\n\
       1.None (���ץ�)\r\n\
       2.Intensity Shift (Intensity���������Target White, �ݷf�tMulti-Gen)\r\n\
       3.Force Assign White (���IDG�j����w��TargetWhite)\r\n\
       \r\n\
       [3.4 build 1.40] 2012/08/31\r\n\
       +Target White�W�[Force Assign White, �i��ܬO�_�j��]�wTarget White��RGB\r\n\
       +Auto Intensity�ȦbMultiGen���Ĥ@���}��, �Y�LMultiGen�h������\r\n\
       \r\n\
       [3.4 build 1.39] 2012/08/30\r\n\
       -����Target White��Auto Intensity\r\n\
       -����Target White��Smooth Intensity\r\n\
       -�ѨMTarget White+MultiGen��Gamma���ǽT�����D\r\n\
       \r\n\
       [3.4 build 1.38] 2012/08/29\r\n\
       +�s�WH Stripe II Pattern\r\n\
       -����smooth intensity�bmulti-gen�U���@��\r\n\
       \r\n\
       [3.4 build 1.37] 2012/08/24\r\n\
       -Target White�U���I�ץ�\r\n\
       \r\n\
       [3.4 build 1.34] 2012/08/03\r\n\
       +Gamma Measurement�i�]�w�I���\��\r\n\
       \r\n\
       [3.4 build 1.31] 2012/06/12\r\n\
       -�q���ɶ�(Pattern Display Interval)�令500ms, ����í�w\r\n\
       \r\n\
       [3.4 build 1.30] 2012/06/06\r\n\
       +Stability�q���\��\r\n\
       \r\n\
       [3.4 build 1.29] 2012/05/17\r\n\
       +Multi-Gen Gamma�ǽT�״���\r\n\
       \r\n\
       [3.4 build 1.28] 2012/05/15\r\n\
       +�C��CCTLUT�Ұ�TargetWhite�q��\r\n\
       -Gamma Curve�ǽT�״���\r\n\
       \r\n\
       [3.4 build 1.25] 2012/04/25\r\n\
       +�sDe-Hook\r\n\
       \r\n\
       [3.4 build 1.24] 2012/04/18\r\n\
       -De-Hook��Gamma�ץ�\r\n\
       -�]�wCA-X10�ɤ��v�T��������s��T\r\n\
       \r\n\
       [3.3b build 1.22] 2012/04/12\r\n\
       +²��De-Hook�\�઺�ϥ�\r\n\
       +Gamma�q���O�dProperty�ѰѦ�\r\n\
       +Target Sheet�s�WSim x/Sim y�ѰѦ�\r\n\
       \r\n\
       [3.3b build 1.21] 2012/03/16\r\n\
       +Target White Form��Pattern�j�p�i�վ�\r\n\
       \r\n\
       [3.3b build 1.20] 2012/03/15\r\n\
       -����2 Gamma\r\n\
       +Defined Dim Strength�����ק�\r\n\
       +�W�[3 Gamma\r\n\
       \r\n\
       [3.3b build 1.19] 2012/03/02\r\n\
       -Measurement PC Input�ץ�\r\n\
       -�q���ɶ�(Pattern Display Interval)��אּ400ms\r\n\
       +�W�[PC w/ T-CON���\��(�z�LDG-LUT�F��PDirect Gamma�ۦP�\��)\r\n\
       -De-Hook�q���\��ץ�\r\n\
       +Measurement T-CON Input��\"Load Table\"����~�i�ϥ�, �קK�~��\r\n\
       ";
}

//---------------------------------------------------------------------------

void __fastcall TChangeLogForm::FormResize(TObject * Sender)
{
    /*int w = this->ClientRect.Width();
    int h = this->ClientRect.Height();
    int height = h - Memo1->Top * 2;
    int width = w - Memo1->Left * 2;*/
    //Memo1->Height = height;
    //Memo1->Width = width;
}

//---------------------------------------------------------------------------

