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
    +每次CCTLUT皆做TargetWhite量測\r\n\
    -Gamma Curve準確度提升\r\n\
    \r\n\
    [3.4 build 1.25] 2012/04/25\r\n\
    +新De-Hook\r\n\
    \r\n\
    [3.4 build 1.24] 2012/04/18\r\n\
    -De-Hook的Gamma修正\r\n\
    -設定CA-X10時不影響到內存資訊\r\n\
    \r\n\
    [3.3b build 1.22] 2012/04/12\r\n\
    +簡化De-Hook功能的使用\r\n\
    +Gamma量測保留Property供參考\r\n\
    +Target Sheet新增Sim x/Sim y供參考\r\n\
    \r\n\
    [3.3b build 1.21] 2012/03/16\r\n\
    +Target White Form的Pattern大小可調整\r\n\
    \r\n\
    [3.3b build 1.20] 2012/03/15\r\n\
    -取消2 Gamma\r\n\
    +Defined Dim Strength介面修改\r\n\
    +增加3 Gamma\r\n\
    \r\n\
    [3.3b build 1.19] 2012/03/02\r\n\
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

