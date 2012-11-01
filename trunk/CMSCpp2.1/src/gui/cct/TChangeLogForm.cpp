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
       +支援TCON 62301以及其DirectGamma\r\n\
       \r\n\
       [3.4 build 1.41] 2012/08/31\r\n\
       +PanelRegulator分為DGLut和GammaTest\r\n\
       +Target White下增加De-WhiteError功能,有:\r\n\
       1.None (不修正)\r\n\
       2.Intensity Shift (Intensity平移對齊至Target White, 需搭配Multi-Gen)\r\n\
       3.Force Assign White (白點DG強制指定為TargetWhite)\r\n\
       \r\n\
       [3.4 build 1.40] 2012/08/31\r\n\
       +Target White增加Force Assign White, 可選擇是否強制設定Target White的RGB\r\n\
       +Auto Intensity僅在MultiGen的第一次開啟, 若無MultiGen則不執行\r\n\
       \r\n\
       [3.4 build 1.39] 2012/08/30\r\n\
       -取消Target White的Auto Intensity\r\n\
       -取消Target White的Smooth Intensity\r\n\
       -解決Target White+MultiGen後Gamma不準確的問題\r\n\
       \r\n\
       [3.4 build 1.38] 2012/08/29\r\n\
       +新增H Stripe II Pattern\r\n\
       -關閉smooth intensity在multi-gen下的作用\r\n\
       \r\n\
       [3.4 build 1.37] 2012/08/24\r\n\
       -Target White下白點修正\r\n\
       \r\n\
       [3.4 build 1.34] 2012/08/03\r\n\
       +Gamma Measurement可設定背景功能\r\n\
       \r\n\
       [3.4 build 1.31] 2012/06/12\r\n\
       -量測時間(Pattern Display Interval)改成500ms, 較為穩定\r\n\
       \r\n\
       [3.4 build 1.30] 2012/06/06\r\n\
       +Stability量測功能\r\n\
       \r\n\
       [3.4 build 1.29] 2012/05/17\r\n\
       +Multi-Gen Gamma準確度提升\r\n\
       \r\n\
       [3.4 build 1.28] 2012/05/15\r\n\
       +每次CCTLUT皆做TargetWhite量測\r\n\
       -Gamma Curve準確度提升\r\n\
       \r\n\
       [3.4 build 1.25] 2012/04/25\r\n\
       +新De-Hook\r\n\
       \r\n\
       [3.4 build 1.24] 2012/04/18\r\n\
       -De-Hook的Gamma修正\r\n\
       -設定CA-X10時不影響到儀器內存資訊\r\n\
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
    /*int w = this->ClientRect.Width();
    int h = this->ClientRect.Height();
    int height = h - Memo1->Top * 2;
    int width = w - Memo1->Left * 2;*/
    //Memo1->Height = height;
    //Memo1->Width = width;
}

//---------------------------------------------------------------------------

