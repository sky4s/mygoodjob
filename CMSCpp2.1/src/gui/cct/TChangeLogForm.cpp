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
       *開啟I2C Test會造成量測delay時間拉長為10sec\r\n\
       *AUO11311 有新type |RH|RL|GH|GL|BH|BL|(14,0,30,16,46,32,6,10)\r\n\
        且Address當中有包含其他設定值的Register\r\n\
       \r\n\
       [3.7 build 1.69] 2014/06/25\r\n\
       +增加TCON Hawk\r\n\
       +增加I2C Control，2-byte data potocol(for USB card)\r\n\
       [3.7 build 1.68] 2014/06/17\r\n\
       +增加Timing setting eegister(for TCON 12411/2)\r\n\
       +Gamma Measure前預先等待5000ms, 讓液晶進入穩態\r\n\
       +PCInput具備以圖片做Pattern量測功能\r\n\
       +增加DoDoBird(豆豆鳥)I2C卡支援\r\n\
       [3.7 build 1.67] 2014/05/14\r\n\
       +增加PG Mode(for TCON 12802)\r\n\
       -解決程式未關閉而重複量測時，輸出的Excel會愈來愈大，最後可能當機\r\n\
       -解決ini檔若不能建立(別人電腦)，會一值跳出錯誤訊息\r\n\
       [3.6 build 1.66] 2014/04/21\r\n\
       +增加TCON 12412\r\n\
       +增加Defined Dim部分(1.定義目標黑點 2.Smooth 轉折點-3Parts)\r\n\
       [3.6 build 1.65] 2013/10/03\r\n\
       +增加TCON 12411(包括增加direct type: 12411Type)\r\n\
       +增加TCON 12411, Aging mode 驗證流程\r\n\
       [3.6 build 1.64] 2013/10/03\r\n\
       +增加TCON 11311(包括增加direct type: 11311Type)\r\n\
       -解決PC mode，執行Gamma measurement異常(加入一開始執行RadioButton_PCClick)\r\n\
       -解決PC mode，進行CCT LUT量測時有機率異常(加入targetWhiteShift初值設定)\r\n\
       [3.6 build 1.63] 2013/09/27\r\n\
       +增加Defined Dim中3 Parts選擇(Smooth Target x/y)\r\n\
       [3.6 build 1.62] 2013/07/19\r\n\
       +增加Input source : TCON(Aging mode) 選項\r\n\
       +增加TCON 12409(包括Aging setting部分)\r\n\
       +增加GammaMeasurementForm中的Aging Mode量測方式\r\n\
       [3.6 build 1.61] 2013/03/26\r\n\
       +增加12409 Aging Pattern的支援\r\n\
       [3.5 build 1.60] 2013/01/09\r\n\
       +Measure Sheet增加Intensity的紀錄\r\n\
       [3.5 build 1.59] 2013/01/08\r\n\
       +增加Target White Shift, 在Target White模式下增加色度/亮度準確率\r\n\
       [3.5 build 1.58] 2013/01/08\r\n\
       +Multi-Gen & Target White & 10Bit In下, 白點257以運算產生\r\n\
       +增加native(target) white的色度資料\r\n\
       -解決 非10Bit量測10Bit in LUT時,未內插出DG255.75的bug\r\n\
       [3.5 build 1.57] 2013/01/04\r\n\
       -去除10Bit In量測值最大到4095的限制(對應12405具備GL256 DG為13Bit的特性)\r\n\
       [3.5 build 1.56] 2012/12/28\r\n\
       -Gamma Measurement 10Bit in量測確保維持在1024階\r\n\
       -10Bit In時的Gamma偏移作了修正\r\n\
       +Defined Dim的Under預設值改為25\r\n\
       [3.5 build 1.55] 2012/12/18\r\n\
       +10in時, 1023若無法對應DG4080, 會顯示警告訊息\r\n\
       [3.5 build 1.54] 2012/12/14\r\n\
       -10Bit in時Target White修正256為255\r\n\
       +Target White時儲存Force Assign Target White的設定值\r\n\
       [3.5 build 1.53] 2012/12/13\r\n\
       改變版本號策略: 子版本供Product Team辨識, Build流水號供Platform Team內部識別\r\n\
       +加回Matrix Calibration Form\r\n\
       [3.4 build 1.52] 2012/12/13\r\n\
       +增加10bit in Gamma Measure\r\n\
       -解決10bit in Gamma Curve bug\r\n\
       [3.4 build 1.50] 2012/12/5\r\n\
       +增加Defined Dim:RB Fix(為解決低灰階偏色問題)\r\n\
       [3.4 build 1.48] 2012/11/23\r\n\
       +Main頁面修改\r\n\
       \r\n\
       [3.4 build 1.47] 2012/11/21\r\n\
       -Direct Gamma的輸出修正\r\n\
       \r\n\
       [3.4 build 1.45] 2012/11/05\r\n\
       +支援TCON 1H501以及其DirectGamma\r\n\
       +支援Custome Pattern的載入\r\n\
       \r\n\
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
       +Measurement Direct Gamma需\"Load Table\"之後才可使用, 避免誤用\r\n\
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



