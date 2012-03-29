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
    +Target White Form的Pattern大小可調整\r\n\
    \r\n\
    Version 3.3b (build 1.20) 20120315\r\n\
    -取消2 Gamma\r\n\
    +Defined Dim Strength介面修改\r\n\
    +增加3 Gamma\r\n\
    \r\n\
    Version 3.3b (build 1.19) 20120302\r\n\
    -Measurement PC Input修正\r\n\
    -量測時間(Pattern Display Interval)更改為400ms\r\n\
    +增加PC w/ T-CON的功能(透過DG-LUT達到與Direct Gamma相同功能)\r\n\
    -De-Hook量測功能修正\r\n\
    +Measurement T-CON Input需\"Load Table\"之後才可使用, 避免誤用\r\n\
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

