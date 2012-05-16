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
    [3.4 build 1.28] 2012/05/15\r\n\
    +�C��CCTLUT�Ұ�TargetWhite�q��\r\n\
    -Gamma Curve�ǽT�״���\r\n\
    \r\n\
    [3.4 build 1.25] 2012/04/25\r\n\
    +�sDe-Hook\r\n\
    \r\n\
    [3.4 build 1.24] 2012/04/18\r\n\
    -De-Hook��Gamma�ץ�\r\n\
    -�]�wCA-X10�ɤ��v�T�줺�s��T\r\n\
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
    int w = this->ClientRect.Width();
    int h = this->ClientRect.Height();
    Memo1->Height = h - Memo1->Top * 2;
    Memo1->Width = w - Memo1->Left * 2;
}

//---------------------------------------------------------------------------

