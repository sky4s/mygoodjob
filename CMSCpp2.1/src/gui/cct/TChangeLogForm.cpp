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
       {Issue List}\r\n\
       *�}��I2C Test�|�y���q��delay�ɶ��Ԫ���10sec\r\n\
       *AUO11311 ���stype |RH|RL|GH|GL|BH|BL|(14,0,30,16,46,32,6,10)\r\n\
        �BAddress�����]�t��L�]�w�Ȫ�Register\r\n\
       \r\n\
       [3.7 build 1.69] 2014/06/25\r\n\
       +�W�[TCON Hawk\r\n\
       +�W�[I2C Control�A2-byte data potocol(for USB card)\r\n\
       [3.7 build 1.68] 2014/06/17\r\n\
       +�W�[Timing setting eegister(for TCON 12411/2)\r\n\
       +Gamma Measure�e�w������5000ms, ���G���i�Jí�A\r\n\
       +PCInput��ƥH�Ϥ���Pattern�q���\��\r\n\
       +�W�[DoDoBird(������)I2C�d�䴩\r\n\
       [3.7 build 1.67] 2014/05/14\r\n\
       +�W�[PG Mode(for TCON 12802)\r\n\
       -�ѨM�{���������ӭ��ƶq���ɡA��X��Excel�|�U�ӷU�j�A�̫�i����\r\n\
       -�ѨMini�ɭY����إ�(�O�H�q��)�A�|�@�ȸ��X���~�T��\r\n\
       [3.6 build 1.66] 2014/04/21\r\n\
       +�W�[TCON 12412\r\n\
       +�W�[Defined Dim����(1.�w�q�ؼж��I 2.Smooth ����I-3Parts)\r\n\
       [3.6 build 1.65] 2013/10/03\r\n\
       +�W�[TCON 12411(�]�A�W�[direct type: 12411Type)\r\n\
       +�W�[TCON 12411, Aging mode ���Ҭy�{\r\n\
       [3.6 build 1.64] 2013/10/03\r\n\
       +�W�[TCON 11311(�]�A�W�[direct type: 11311Type)\r\n\
       -�ѨMPC mode�A����Gamma measurement���`(�[�J�@�}�l����RadioButton_PCClick)\r\n\
       -�ѨMPC mode�A�i��CCT LUT�q���ɦ����v���`(�[�JtargetWhiteShift��ȳ]�w)\r\n\
       [3.6 build 1.63] 2013/09/27\r\n\
       +�W�[Defined Dim��3 Parts���(Smooth Target x/y)\r\n\
       [3.6 build 1.62] 2013/07/19\r\n\
       +�W�[Input source : TCON(Aging mode) �ﶵ\r\n\
       +�W�[TCON 12409(�]�AAging setting����)\r\n\
       +�W�[GammaMeasurementForm����Aging Mode�q���覡\r\n\
       [3.6 build 1.61] 2013/03/26\r\n\
       +�W�[12409 Aging Pattern���䴩\r\n\
       [3.5 build 1.60] 2013/01/09\r\n\
       +Measure Sheet�W�[Intensity������\r\n\
       [3.5 build 1.59] 2013/01/08\r\n\
       +�W�[Target White Shift, �bTarget White�Ҧ��U�W�[���/�G�׷ǽT�v\r\n\
       [3.5 build 1.58] 2013/01/08\r\n\
       +Multi-Gen & Target White & 10Bit In�U, ���I257�H�B�ⲣ��\r\n\
       +�W�[native(target) white����׸��\r\n\
       -�ѨM �D10Bit�q��10Bit in LUT��,�������XDG255.75��bug\r\n\
       [3.5 build 1.57] 2013/01/04\r\n\
       -�h��10Bit In�q���ȳ̤j��4095������(����12405���GL256 DG��13Bit���S��)\r\n\
       [3.5 build 1.56] 2012/12/28\r\n\
       -Gamma Measurement 10Bit in�q���T�O�����b1024��\r\n\
       -10Bit In�ɪ�Gamma�����@�F�ץ�\r\n\
       +Defined Dim��Under�w�]�ȧאּ25\r\n\
       [3.5 build 1.55] 2012/12/18\r\n\
       +10in��, 1023�Y�L�k����DG4080, �|���ĵ�i�T��\r\n\
       [3.5 build 1.54] 2012/12/14\r\n\
       -10Bit in��Target White�ץ�256��255\r\n\
       +Target White���x�sForce Assign Target White���]�w��\r\n\
       [3.5 build 1.53] 2012/12/13\r\n\
       ���ܪ���������: �l������Product Team����, Build�y������Platform Team�����ѧO\r\n\
       +�[�^Matrix Calibration Form\r\n\
       [3.4 build 1.52] 2012/12/13\r\n\
       +�W�[10bit in Gamma Measure\r\n\
       -�ѨM10bit in Gamma Curve bug\r\n\
       [3.4 build 1.50] 2012/12/5\r\n\
       +�W�[Defined Dim:RB Fix(���ѨM�C�Ƕ�������D)\r\n\
       [3.4 build 1.48] 2012/11/23\r\n\
       +Main�����ק�\r\n\
       \r\n\
       [3.4 build 1.47] 2012/11/21\r\n\
       -Direct Gamma����X�ץ�\r\n\
       \r\n\
       [3.4 build 1.45] 2012/11/05\r\n\
       +�䴩TCON 1H501�H�Ψ�DirectGamma\r\n\
       +�䴩Custome Pattern�����J\r\n\
       \r\n\
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
       +Measurement Direct Gamma��\"Load Table\"����~�i�ϥ�, �קK�~��\r\n\
       ";
}

//---------------------------------------------------------------------------

void __fastcall TChangeLogForm::FormResize(TObject * Sender)
{
    /*int w = this->ClientRect.Width();
       int h = this->ClientRect.Height();
       int height = h - Memo1->Top * 2;
       int width = w - Memo1->Left * 2; */
    //Memo1->Height = height;
    //Memo1->Width = width;
}

//---------------------------------------------------------------------------



