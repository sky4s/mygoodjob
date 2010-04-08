//---------------------------------------------------------------------------


#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TMainForm.h"
#include "TTargetWhiteForm.h"
#include "TTargetWhiteForm2.h"
#include "TAboutBox.h"
#include "TCCTLUTForm.h"
#include "TMatrixCalibration.h"
#include "TGammaAdjustmentForm.h"
#include "TGammaMeasurementForm.h"

#include <debug.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent * Owner):TForm(Owner),
linkCA210(!FileExists(DEBUG_FILE))
{
    //bool debug = FileExists(DEBUG_FILE);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::About1Click(TObject * Sender)
{
    if (AboutBox == null) {
	Application->CreateForm(__classid(TAboutBox), &AboutBox);
    }
    AboutBox->ShowModal();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Exit1Click(TObject * Sender)
{
    this->Close();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::TargetWhite1Click(TObject * Sender)
{
    if (TargetWhiteForm2 == null) {
	Application->CreateForm(__classid(TTargetWhiteForm2),
				&TargetWhiteForm2);
    }
    TargetWhiteForm2->ShowModal();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject * Sender)
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    using namespace cms::lcd::calibrate;

    if (true == linkCA210) {
	try {
	    meter = bptr < Meter > (new CA210());
	    mm = bptr < MeterMeasurement >
		(new MeterMeasurement(meter, false));

	    analyzer.reset(new CA210IntensityAnalyzer(getCA210(), mm));
	}
	catch(EOleException & ex) {
	    ShowMessage("CA210 cannot be linked.");
	}
    } else {
	setDummyMeterFilename(METER_FILE);
	this->Caption = this->Caption + " (debug mode)";
	this->GroupBox_CHSetting->Visible = false;
    }

    bitDepth.reset(new BitDepthProcessor(8, 10, 8, false));
}

//---------------------------------------------------------------------------

void TMainForm::setDummyMeterFilename(const std::string & filename)
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    bptr < DGLutFile > dgcode(new DGLutFile(filename));
    meter.reset(new DGLutFileMeter(dgcode));
    mm.reset(new MeterMeasurement(meter, false));
    mm->setFakeMeasure(true);
    analyzer.reset(new CA210IntensityAnalyzer(mm));
};

//---------------------------------------------------------------------------

void TMainForm::resetDummyMeter()
{
    using namespace cms::measure::meter;
    DGLutFileMeter *dgc = dynamic_cast < DGLutFileMeter * >(meter.get());
    dgc->reset();
};


//---------------------------------------------------------------------------
bptr < cms::measure::meter::CA210 > TMainForm::getCA210()
{
    if (null == ca210 && true == linkCA210) {
	ca210.reset(dynamic_cast <
		    cms::measure::meter::CA210 * >(meter.get()));
    }
    return ca210;
};

//---------------------------------------------------------------------------
/*void TMainForm::setChannel(int channel)
{
    if (true == linkCA210) {
	getCA210()->getCA210API()->setChannelNO(channel);
    }
};*/

//---------------------------------------------------------------------------
void TMainForm::setToTargetChannel()
{
    if (true == linkCA210) {
	int channel = this->Edit_TargetCH->Text.ToInt();
	getCA210()->getCA210API()->setChannelNO(channel);
    }
};

//---------------------------------------------------------------------------
int TMainForm::getInterval()
{
    return Edit_Interval->Text.ToInt();
};

//---------------------------------------------------------------------------

void __fastcall TMainForm::CCTLUT1Click(TObject * Sender)
{
    if (CCTLUTForm == null) {
	Application->CreateForm(__classid(TCCTLUTForm), &CCTLUTForm);
    }
    CCTLUTForm->setBitDepthProcessor(bitDepth);
    CCTLUTForm->ShowModal();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::GammaAdj1Click(TObject * Sender)
{
    if (GammaAdjustmentForm == null) {
	Application->CreateForm(__classid(TGammaAdjustmentForm),
				&GammaAdjustmentForm);
    }
    GammaAdjustmentForm->setBitDepthProcessor(bitDepth);
    GammaAdjustmentForm->ShowModal();
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::RadioButton_TCONClick(TObject * Sender)
{
    this->Panel_TCON->Visible = true;
    this->bitDepth->setTCONInput(true);
    ShowMessage
	("Please Turn On DG and FRC for Measurement when T-CON Input Source is selected!!!");
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_PCClick(TObject * Sender)
{
    this->Panel_TCON->Visible = false;
    bitDepth->setTCONInput(false);
    MeasureWindow->setTCONControlOff();
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::Button_ConnectClick(TObject * Sender)
{
    using namespace i2c;
    bptr < i2cControl > i2c1st;
    bptr < i2cControl > i2c2nd;
    unsigned char first, second;
    bool dual = false;

    if (this->RadioButton_SingleTCON->Checked) {
	first = StrToInt("0x" + this->Edit_DeviceAddress->Text);
    } else {
	first = StrToInt("0x" + this->Edit_MasterDeviceAddress->Text);
	second = StrToInt("0x" + this->Edit_SlaveDeviceAddress->Text);
	dual = true;
    }
    AddressingSize addressingSize = getAddressingSize();

    if (this->RadioButton_USB->Checked) {
	i2c1st =
	    i2cControl::getUSBInstance(first, addressingSize, _3_3V,
				       _400KHz);
	if (dual) {
	    i2c2nd =
		i2cControl::getUSBInstance(second, addressingSize,
					   _3_3V, _400KHz);
	};
    } else {

	const LPTCard card =
	    this->RadioButton_LPTLarge->Checked ? Large : Small;

	i2c1st = i2cControl::getLPTInstance(first, addressingSize, card);
	if (dual) {
	    i2c2nd =
		i2cControl::getLPTInstance(second, addressingSize, card);
	};
    };
    bool connect = i2c1st->connect();
    if (dual) {
	i2c2nd->connect();
    }

    if (true == connect) {

	int gammaTestAddress =
	    StrToInt("0x" + this->Edit_EnableAddress->Text);
	int gammaTestBit = StrToInt(this->Edit_EnableBit->Text) + 1;
	int testRGBAddress = StrToInt("0x" + this->Edit_LUTAddress->Text);
	bool indepRGB = this->CheckBox_IndepRGB->Checked;


	parameter.reset(new
			TCONParameter(gammaTestAddress, gammaTestBit,
				      testRGBAddress, indepRGB,
				      bitDepth->getLutMaxValue()));
	if (!dual) {
	    control.reset(new TCONControl(parameter, i2c1st));
	} else {
	    control.reset(new TCONControl(parameter, i2c1st, i2c2nd));
	}
	this->Button_Connect->Enabled = false;
	this->CheckBox_Connecting->Checked = true;
	this->CheckBox_Connecting->Enabled = true;
	//this->mm->setTCONControl(control);
	MeasureWindow->setTCONControl(control);
    } else {
	//this->mm->setTCONControlOff();
	MeasureWindow->setTCONControlOff();
    }
}

//---------------------------------------------------------------------------
const i2c::AddressingSize TMainForm::getAddressingSize()
{
    using namespace i2c;
    int index = this->ComboBox_AddressingSize->ItemIndex;
    switch (index) {
    case 0:
	return _2k;
    case 1:
	return _4k;
    case 2:
	return _8k;
    case 3:
	return _16k;
    case 4:
	return _32k;
    case 5:
	return _64k;
    case 6:
	return _128k;
    case 7:
	return _256k;
    case 8:
	return _512k;

    }
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::CheckBox_ConnectingClick(TObject * Sender)
{
    if (false == this->CheckBox_Connecting->Checked) {
	this->Button_Connect->Enabled = true;
	this->CheckBox_Connecting->Enabled = false;
    }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Measurement1Click(TObject * Sender)
{
    if (GammaMeasurementForm == null) {
	Application->CreateForm(__classid(TGammaMeasurementForm),
				&GammaMeasurementForm);
    }
    GammaMeasurementForm->setBitDepthProcessor(bitDepth);
    GammaMeasurementForm->ShowModal();
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::MatrixCalibration1Click(TObject * Sender)
{
    if (MatrixCalibrationForm == null) {
	Application->CreateForm(__classid(TMatrixCalibrationForm),
				&MatrixCalibrationForm);
    }
#ifdef _DEBUG
    if (true) {
#else
    if (true == MatrixCalibrationForm->setCA210(ca210)) {
#endif
	MatrixCalibrationForm->ShowModal();
    }
}

//---------------------------------------------------------------------------

void TMainForm::setBitDepthEnable(bool lut10, bool lut12, bool out6,
				  bool out8, bool out10)
{
    this->RadioButton_Lut10->Enabled = lut10;
    this->RadioButton_Lut12->Enabled = lut12;
    this->RadioButton_Out6->Enabled = out6;
    this->RadioButton_Out8->Enabled = out8;
    this->RadioButton_Out10->Enabled = out10;
};

//---------------------------------------------------------------------------

void TMainForm::setBitDepthChecked(int lutSelect, int outSelect)
{

    switch (lutSelect) {
    case 0:
	this->RadioButton_Lut10->Checked = true;
	break;
    case 1:
	this->RadioButton_Lut12->Checked = true;
	break;
    };
    switch (outSelect) {
    case 0:
	this->RadioButton_Out6->Checked = true;
	break;
    case 1:
	this->RadioButton_Out8->Checked = true;
	break;
    case 2:
	this->RadioButton_Out10->Checked = true;
	break;
    };
};

void __fastcall TMainForm::RadioButton_In6Click(TObject * Sender)
{
    using namespace boost;
    bitDepth->setInBit(6);
    // 設定lut/out bit depth checked
    setBitDepthChecked(0, 0);
    // 設定enable
    setBitDepthEnable(true, false, true, false, false);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_In8Click(TObject * Sender)
{
    using namespace cms::util;
    bitDepth->setInBit(8);
    // 設定lut/out bit depth checked
    setBitDepthChecked(0, 1);
    // 設定enable
    setBitDepthEnable(true, true, true, true, false);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_In10Click(TObject * Sender)
{
    using namespace cms::util;
    bitDepth->setInBit(10);
    // 設定lut/out bit depth checked
    setBitDepthChecked(1, 1);
    // 設定enable
    setBitDepthEnable(false, true, false, true, true);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_Lut10Click(TObject * Sender)
{
    bitDepth->setLUTBit(10);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_Lut12Click(TObject * Sender)
{
    bitDepth->setLUTBit(12);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_Out6Click(TObject * Sender)
{
    bitDepth->setOutBit(6);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_Out8Click(TObject * Sender)
{
    bitDepth->setOutBit(8);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_Out10Click(TObject * Sender)
{
    if (!bitDepth->isTCONInput()) {
	ShowMessage("Recommend using T-CON Input.");
    };
    bitDepth->setOutBit(10);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Edit_TargetIDChange(TObject * Sender)
{
    using namespace ca210api;
    bptr < CA210API > ca210api = getCA210()->getCA210API();
    ca210api->setChannelNO(Edit_TargetCH->Text.ToInt());
    ca210api->setChannelID(Edit_TargetID->Text);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Edit_TargetCHChange(TObject * Sender)
{
    getCA210()->getCA210API()->setChannelNO(Edit_TargetCH->Text.ToInt());
}


//---------------------------------------------------------------------------

