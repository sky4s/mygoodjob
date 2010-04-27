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
	TCA210SettingFrame1->setCA210API(ca210API);
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

    double rx = this->Edit_Rx->Text.ToDouble();
    double ry = this->Edit_Ry->Text.ToDouble();
    double rY = this->Edit_RLv->Text.ToDouble();
    double gx = this->Edit_Gx->Text.ToDouble();
    double gy = this->Edit_Gy->Text.ToDouble();
    double gY = this->Edit_GLv->Text.ToDouble();
    double bx = this->Edit_Bx->Text.ToDouble();
    double by = this->Edit_By->Text.ToDouble();
    double bY = this->Edit_BLv->Text.ToDouble();
    double wx = this->Edit_Wx->Text.ToDouble();
    double wy = this->Edit_Wy->Text.ToDouble();
    double wY = this->Edit_WLv->Text.ToDouble();

    if (rx == 0 || ry == 0 || rY == 0 || gx == 0 || gy == 0 || gY == 0 ||
	bx == 0 || by == 0 || bY == 0 || wx == 0 || wy == 0 || wY == 0) {
	ShowMessage("Target xyY is empty.");
	return;
    }

    if (this->Edit_R->Text.IsEmpty() || this->Edit_G->Text.IsEmpty()
	|| this->Edit_B->Text.IsEmpty()) {
	ShowMessage("Pattern RGB is empty.");
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
    ca210API->setLvxyCalData(Red, rx, ry, rY);

    Patch_ptr gp = mm->measure(g, g->toString());
    ca210API->setLvxyCalData(Green, gx, gy, gY);

    Patch_ptr bp = mm->measure(b, b->toString());
    ca210API->setLvxyCalData(Blue, bx, by, bY);

    Patch_ptr wp = mm->measure(w, w->toString());
    ca210API->setLvxyCalData(White, wx, wy, wY);

    ca210API->enter();
    mm->setWaitTimes(waitTimes);
    ShowMessage("Matrix Calibration is Success!");
}

//---------------------------------------------------------------------------


