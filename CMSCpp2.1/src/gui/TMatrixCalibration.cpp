//---------------------------------------------------------------------------

#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TMatrixCalibration.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TCA210SettingFrame"
#pragma resource "*.dfm"
TMatrixCalibrationForm *MatrixCalibrationForm;
//---------------------------------------------------------------------------
__fastcall TMatrixCalibrationForm::TMatrixCalibrationForm(TComponent *
							  Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------
bool TMatrixCalibrationForm::setMeter(bptr < cms::measure::meter::CA210 >
				      ca210,
				      bptr <
				      cms::measure::MeterMeasurement > mm)
{
    this->ca210 = ca210;
    if (ca210 != null) {
	ca210API = ca210->getCA210API();
	this->mm = mm;
	return true;
    } else {
	ShowMessage("CA210 cannot be linked.");
	return false;
    }
}

//---------------------------------------------------------------------------

void __fastcall TMatrixCalibrationForm::
TCA210SettingFrame1Button_ConnectClick(TObject * Sender)
{
    TCA210SettingFrame1->Button_ConnectClick(Sender);

}

//---------------------------------------------------------------------------

void __fastcall TMatrixCalibrationForm::
TCA210SettingFrame1ComboBox_SyncModeChange(TObject * Sender)
{
    TCA210SettingFrame1->ComboBox_SyncModeChange(Sender);

}

//---------------------------------------------------------------------------



void __fastcall TMatrixCalibrationForm::
Button_MatrixCalibrateClick(TObject * Sender)
{
    using namespace Dep;
    using namespace Indep;
    using namespace ca210api;
    int ch = this->Edit_MatrixChannel->Text.ToInt();
    if (ch == 0) {
	ShowMessage("CH00 cannot be calibrated.");
	return;
    }
    int rValue = this->Edit_R->Text.ToInt();
    int gValue = this->Edit_G->Text.ToInt();
    int bValue = this->Edit_B->Text.ToInt();
    RGB_ptr r(new RGBColor(rValue, 0, 0));
    RGB_ptr g(new RGBColor(0, gValue, 0));
    RGB_ptr b(new RGBColor(0, 0, bValue));
    RGB_ptr w(new RGBColor(rValue, gValue, bValue));
    ca210API->setLvxyCalMode();
    int waitTimes = mm->getWaitTimes();
    mm->setWaitTimes(10000);

    Patch_ptr rp = mm->measure(r, r->toString());
    xyY_ptr rxyY(new CIExyY(rp->getXYZ()));
    ca210API->setLvxyCalData(Red, rxyY->x, rxyY->y, rxyY->Y);

    Patch_ptr gp = mm->measure(r, r->toString());
    xyY_ptr gxyY(new CIExyY(gp->getXYZ()));
    ca210API->setLvxyCalData(Green, gxyY->x, gxyY->y, gxyY->Y);

    Patch_ptr bp = mm->measure(r, r->toString());
    xyY_ptr bxyY(new CIExyY(bp->getXYZ()));
    ca210API->setLvxyCalData(Blue, bxyY->x, bxyY->y, bxyY->Y);

    Patch_ptr wp = mm->measure(r, r->toString());
    xyY_ptr wxyY(new CIExyY(wp->getXYZ()));
    ca210API->setLvxyCalData(White, wxyY->x, wxyY->y, wxyY->Y);

    ca210API->enter();

    mm->setWaitTimes(waitTimes);
    ShowMessage("Matrix Calibration is Success!");
}

//---------------------------------------------------------------------------

