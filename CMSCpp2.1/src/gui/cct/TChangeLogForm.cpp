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
    Version 3.3b (build 1.21) 20120316\r\n\
    +Target White Form��Pattern�j�p�i�վ�\r\n\
    \r\n\
    Version 3.3b (build 1.20) 20120315\r\n\
    -����2 Gamma\r\n\
    +Defined Dim Strength�����ק�\r\n\
    +�W�[3 Gamma\r\n\
    \r\n\
    Version 3.3b (build 1.19) 20120302\r\n\
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

