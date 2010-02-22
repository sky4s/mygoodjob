//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TTargetWhiteForm.h"
#include "TMainForm.h"
#include "TMeasureWindow.h"
#include <cms/colorspace/ciexyz.h>
#include <cms/core.h>
#include <cms/patch.h>
#include <cms/measure/meter.h>
#include <cms/measure/MeterMeasurement.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TTargetWhiteForm *TargetWhiteForm;
//---------------------------------------------------------------------------
__fastcall TTargetWhiteForm::TTargetWhiteForm(TComponent *
					      Owner):TForm(Owner)
{
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm::ScrollBar_RChange(TObject * Sender)
{
    Edit_R->Text = AnsiString(ScrollBar_R->Position);
    scrollBar_Change();
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm::ScrollBar_GChange(TObject * Sender)
{
    Edit_G->Text = AnsiString(ScrollBar_G->Position);
    scrollBar_Change();
}

//---------------------------------------------------------------------------

void __fastcall TTargetWhiteForm::ScrollBar_BChange(TObject * Sender)
{
    Edit_B->Text = AnsiString(ScrollBar_B->Position);
    scrollBar_Change();
}

//---------------------------------------------------------------------------


void TTargetWhiteForm::scrollBar_Change()
{
    Panel1->Color =
	(TColor) ScrollBar_R->Position + ((ScrollBar_G->Position) << 8) +
	((ScrollBar_B->Position) << 16);
}


//---------------------------------------------------------------------------



void TTargetWhiteForm::setColorimetricValues(double x, double y, double up,
					     double vp)
{

    AnsiString xStr = AnsiString().sprintf("%1.4g", x);
    AnsiString yStr = AnsiString().sprintf("%1.4g", y);

    this->Edit_x->Text = xStr;
    this->Edit_y->Text = yStr;
    this->Edit_targetx->Text = xStr;
    this->Edit_targety->Text = yStr;
    this->Edit_up->Text = AnsiString().sprintf("%1.4g", up);
    this->Edit_vp->Text = AnsiString().sprintf("%1.4g", vp);
}

void __fastcall TTargetWhiteForm::Edit_CTChange(TObject * Sender)
{
    using cms::CorrelatedColorTemperature;
    using Indep::CIExyY;
    using java::lang::IllegalArgumentException;
    using namespace boost;

    AnsiString ctText = this->Edit_CT->Text;
    if (ctText.Length() == 0) {
	setColorimetricValues(-1, -1, -1, -1);
	return;
    }

    int ct = ctText.ToInt();

    try {
	bptr < CIExyY > xyY =
	    CorrelatedColorTemperature::CCT2DIlluminantxyY(ct);
	double_array uvpValues = xyY->getuvPrimeValues();
	setColorimetricValues(xyY->x, xyY->y, uvpValues[0], uvpValues[1]);
    }
    catch(IllegalArgumentException ex) {
	setColorimetricValues(-1, -1, -1, -1);
    }
}

//---------------------------------------------------------------------------

/*
 流程
 根據Adjustment Options, 分成兩種:
 1. Adjust to xy
  從目標xy, 迭代找到最接近的RGB組合
 2. Adjust by RGB
 依據設定的RGB作為白點.

 取得RGB後, 將目標RGB作為TargetWhite, 設定到CA-210去.
 設定流程為:
 1. 打pattern > 等待(5s) > 量測 (共RGBW四色)
 2. 設定channel (NO及ID)
 3. 設定校正模式
 4. 設定校正資料 RGBW
 5. enter

*/

void __fastcall TTargetWhiteForm::Button2Click(TObject * Sender)
{
    /*using namespace cms::measure::meter;
       using namespace cms::measure;
       using namespace cms;
       using namespace cms::colorspace;
       using namespace ca210api;
       using namespace boost;

       CA210 & meter = *(dynamic_cast < CA210 * >(MainForm->meter.get()));
       CA210API & ca210api = *meter.getCA210API();
       ca210api.setRemoteMode(On);
       ca210api.setChannelNO(Edit_SourceCH->Text.ToInt());
       MeterMeasurement mm(MainForm->meter, true);
       mm.setWaitTimes(5000);

       int r = this->Edit_R->Text.ToInt();
       int g = this->Edit_G->Text.ToInt();
       int b = this->Edit_B->Text.ToInt();


       shared_ptr < Patch > wPatch = mm.measure(r, g, b, "W");
       shared_ptr < Patch > rPatch = mm.measure(r, 0, 0, "R");
       shared_ptr < Patch > gPatch = mm.measure(0, g, 0, "G");
       shared_ptr < Patch > bPatch = mm.measure(0, 0, b, "B"); */

    /*MeasureWindow->setRGB(r, g, b);
       Sleep(5000);
       shared_ptr < MeasureResult > wResult = ca210api.triggerMeasureResult();

       MeasureWindow->setRGB(r, 0, 0);
       Sleep(5000);
       shared_ptr < MeasureResult > rResult = ca210api.triggerMeasureResult();

       MeasureWindow->setRGB(0, g, 0);
       Sleep(5000);
       shared_ptr < MeasureResult > gResult = ca210api.triggerMeasureResult();

       MeasureWindow->setRGB(0, 0, b);
       Sleep(5000);
       shared_ptr < MeasureResult > bResult = ca210api.triggerMeasureResult(); */
    //wPatch->getXYZ()->
    //ca210api.setChannelNO(Edit_TargetCH->Text.ToInt());
    //ca210api.setLvxyCalMode();
    /*ca210api.setLvxyCalData(White, wResult->getxyYValues());
       ca210api.setLvxyCalData(Red, rResult->getxyYValues());
       ca210api.setLvxyCalData(Green, gResult->getxyYValues());
       ca210api.setLvxyCalData(Blue, bResult->getxyYValues()); */

    /*ca210api.enter();
       ca210api.setRemoteMode(Off);
       MeasureWindow->Visible = false;
       this->Close(); */
}

//---------------------------------------------------------------------------

