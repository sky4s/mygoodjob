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
    TargetWhiteForm2->ShowModal();
    //TargetWhiteForm2->Show();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject * Sender)
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    if (true == linkCA210) {
	meter = bptr < Meter > (new CA210());
	mm = bptr < MeterMeasurement >
	    (new MeterMeasurement(meter, false));

	analyzer.reset(new CA210IntensityAnalyzer(getCA210(), mm));
    } else {
	setDummyMeterFilename(METER_FILE);
    }
}

//---------------------------------------------------------------------------

void TMainForm::setDummyMeterFilename(const std::string & filename)
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    bptr < DGLutFile > dgcode(new DGLutFile(filename));
    meter.reset(new DGLutFileMeter(dgcode));
    //meter = bptr < Meter > (new DGLutFileMeter(dgcode));
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
    if (null == ca210) {
	ca210.reset(dynamic_cast <
		    cms::measure::meter::CA210 * >(meter.get()));
    }
    return ca210;
};

//---------------------------------------------------------------------------
int TMainForm::getInterval()
{
    return Edit_Interval->Text.ToInt();
};

//---------------------------------------------------------------------------

void __fastcall TMainForm::CCTLUT1Click(TObject * Sender)
{
    CCTLUTForm->ShowModal();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::GammaAdj1Click(TObject * Sender)
{
    MeasureWindow->ShowModal();
    //MeasureWindow->Visible = true;
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::RadioButton_TCONClick(TObject * Sender)
{
    CCTLUTForm->setTCONInput(true);
    this->GroupBox_Card->Enabled = true;
    this->GroupBox_DeviceAddress->Enabled = true;
    this->GroupBox_GammaTestAddress->Enabled = true;
    ShowMessage
	("Please Turn On DG and FRC for Measurement when T-CON Input Source is selected!!!");
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_PCClick(TObject * Sender)
{
    CCTLUTForm->setTCONInput(false);
    this->GroupBox_Card->Enabled = false;
    this->GroupBox_DeviceAddress->Enabled = false;
    this->GroupBox_GammaTestAddress->Enabled = false;
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::Button_ConnectClick(TObject * Sender)
{
    using namespace cms::i2c;
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
	int gammaTestBit = StrToInt(this->Edit_EnableBit->Text)+1;
	int testRGBAddress = StrToInt("0x" + this->Edit_LUTAddress->Text);
	bool indepRGB = this->CheckBox_IndepRGB->Checked;
	parameter.reset(new
			TCONParameter(gammaTestAddress, gammaTestBit,
				      testRGBAddress, indepRGB));
	if (!dual) {
	    control.reset(new TCONControl(parameter, i2c1st));
	} else {
	    control.reset(new TCONControl(parameter, i2c1st, i2c2nd));
	}
	this->Button_Connect->Enabled = false;
	this->CheckBox_Connecting->Checked = true;
	this->CheckBox_Connecting->Enabled = true;
        this->mm->setTCONControl(control);
    }
    else {
        this->mm->setTCONControlOff();
    }
}

//---------------------------------------------------------------------------
const cms::i2c::AddressingSize TMainForm::getAddressingSize()
{
    using namespace cms::i2c;
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


void __fastcall TMainForm::CheckBox_ConnectingClick(TObject * Sender)
{
    if (false == this->CheckBox_Connecting->Checked) {
//this->CheckBox_Connecting->Checked=false;
	this->Button_Connect->Enabled = true;
	this->CheckBox_Connecting->Enabled = false;
    }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Measurement1Click(TObject *Sender)
{
  MeasureWindow->ShowModal();
}
//---------------------------------------------------------------------------

