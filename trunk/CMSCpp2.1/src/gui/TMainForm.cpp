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
    TargetWhiteForm2->setBitDepthProcessor(bitDepth);
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
	initCA210Meter();
    } else {
	setDummyMeterFilename(METER_FILE);
	this->Caption = this->Caption + " (debug mode)";
	this->GroupBox_CHSetting->Visible = false;
    }
    bitDepth.reset(new BitDepthProcessor(8, 10, 8, false));
}

//---------------------------------------------------------------------------
void TMainForm::initCA210Meter()
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    try {
	meter = bptr < Meter > (new CA210());
	mm = bptr < MeterMeasurement >
	    (new MeterMeasurement(meter, false));
	mm->setWaitTimes(this->getInterval());

    }
    catch(EOleException & ex) {
	ShowMessage("CA210 cannot be linked.");
	//Application->Terminate();
    }
};

//---------------------------------------------------------------------------
bptr < cms::measure::IntensityAnalyzerIF > TMainForm::getAnalyzer()
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    using namespace cms::lcd::calibrate;
    if (null == analyzer) {
	//產生ca210
	bptr < cms::measure::meter::CA210 > ca210 = getCA210();
	if (null == ca210) {
	    return bptr < IntensityAnalyzerIF >
		((IntensityAnalyzerIF *) null);
	}
	realAnalyzer.reset(new CA210IntensityAnalyzer(ca210, mm));
	//產生max matrix
	bptr < MaxMatrixIntensityAnayzer >
	    ma(new MaxMatrixIntensityAnayzer(mm));


	if (true == this->RadioButton_AnalyzerCA210->Checked) {
	    analyzer = realAnalyzer;
	} else if (true == this->RadioButton_AnalyzerMaxMatrix->Checked) {
	    analyzer = ma;
	} else if (true == this->RadioButton_AnalyzerDebug->Checked) {
	    //產生兩者的合體
	    analyzer.reset(new IntensityAnayzer(ma, realAnalyzer));
	}

    }
    return analyzer;
}

//---------------------------------------------------------------------------
void TMainForm::setAnalyzerToTargetChannel()
{
    using namespace std;
    if (true == linkCA210) {
	if (null == realAnalyzer) {
	    throw java::lang::
		IllegalStateException("call getAnalyzer() first!");
	}
	//撈出channel no和id
	int channel = this->Edit_TargetCH->Text.ToInt();
	string targetid = Edit_TargetID->Text.c_str();
	//若沒有值強制指定為空白字元的字串
	targetid = targetid.empty()? string(" ") : targetid;
	string_ptr id(new string(targetid));
	//設定在ca210
	realAnalyzer->setChannel(channel, id);

    }
};

//---------------------------------------------------------------------------

void TMainForm::setAnalyzerToSourceChannel()
{
    using namespace std;
    if (true == linkCA210) {
	if (null == realAnalyzer) {
	    throw java::lang::
		IllegalStateException("call getAnalyzer() first!");
	}
	//撈出channel no和id
	int channel = this->Edit_SourceCH->Text.ToInt();
	string_ptr id(new string(" "));
	//設定在ca210
	realAnalyzer->setChannel(channel, id);

    }
};

//---------------------------------------------------------------------------

void TMainForm::setDummyMeterFilename(const std::string & filename)
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    using namespace cms::lcd::calibrate;
    using namespace Indep;
    using namespace Dep;
    bptr < DGLutFile > dgcode(new DGLutFile(filename, ReadOnly));
    meter.reset(new DGLutFileMeter(dgcode));
    mm.reset(new MeterMeasurement(meter, false));
    mm->setFakeMeasure(true);
    bptr < MaxMatrixIntensityAnayzer >
	matrixAnalyzer(new MaxMatrixIntensityAnayzer(mm));
    //analyzer.reset(matrixAnalyzer.get());
    analyzer = matrixAnalyzer;

    fetcher.reset((ComponentFetcher *) null);

    bptr < DGLutProperty > property = dgcode->getProperty();
    xyY_ptr wxyY = property->getReferenceColor(Channel::W);
    if (null != wxyY) {
	xyY_ptr rxyY = property->getReferenceColor(Channel::R);
	xyY_ptr gxyY = property->getReferenceColor(Channel::G);
	xyY_ptr bxyY = property->getReferenceColor(Channel::B);

	matrixAnalyzer->setupComponent(Channel::W, wxyY->toXYZ());
	matrixAnalyzer->setupComponent(Channel::R, rxyY->toXYZ());
	matrixAnalyzer->setupComponent(Channel::G, gxyY->toXYZ());
	matrixAnalyzer->setupComponent(Channel::B, bxyY->toXYZ());
	matrixAnalyzer->enter();
    }
};

//---------------------------------------------------------------------------

void TMainForm::resetDummyMeter()
{
    using namespace cms::measure::meter;
    using namespace cms::lcd::calibrate;
    DGLutFileMeter *dgc = dynamic_cast < DGLutFileMeter * >(meter.get());
    dgc->reset();
};

//---------------------------------------------------------------------------
bptr < cms::lcd::calibrate::ComponentFetcher >
    TMainForm::getComponentFetcher()
{
    if (null == fetcher) {
	bptr < cms::measure::IntensityAnalyzerIF > analyzer =
	    getAnalyzer();
	fetcher.
	    reset(new cms::lcd::calibrate::
		  ComponentFetcher(analyzer, bitDepth));
    }
    MeasureWindow->addWindowListener(fetcher);
    return fetcher;
};

//---------------------------------------------------------------------------
bptr < cms::measure::meter::CA210 > TMainForm::getCA210()
{
    if (null == ca210 && true == linkCA210) {
	using namespace cms::measure::meter;
	if (null == meter) {
	    //throw IllegalStateException("CA210 cannot be linked.");
	    ShowMessage("CA210 cannot be linked.");
	    return bptr < CA210 > ((CA210 *) null);
	}

	cms::measure::meter::Meter * pointer = meter.get();
	ca210.reset(dynamic_cast < CA210 * >(pointer));
    }
    return ca210;
};

//---------------------------------------------------------------------------



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
    //ShowMessage("Sorry! This function is unavailable right now.");
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
	MeasureWindow->setTCONControl(control);
    } else {
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
    default:
	return _2k;
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
    /*if (bitDepth->isTCONInput()) {
       ShowMessage
       ("Sorry! T-CON Input measurement is unavailable right now.");
       return;
       } */


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
    //ShowMessage("Sorry! This function is unavailable right now.");
    if (MatrixCalibrationForm == null) {
	Application->CreateForm(__classid(TMatrixCalibrationForm),
				&MatrixCalibrationForm);
    }

    if (true == linkCA210
	&& true == MatrixCalibrationForm->setMeter(getCA210(), mm)) {
	MatrixCalibrationForm->ShowModal();
    } else {
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

//---------------------------------------------------------------------------
void TMainForm::setFRCAbility()
{
    string_ptr ability = bitDepth->getFRCAbility();
    this->Edit_FRCAbility->Text = ability->c_str();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_In6Click(TObject * Sender)
{
    using namespace boost;
    bitDepth->setInBit(6);
    // 設定lut/out bit depth checked
    setBitDepthChecked(0, 0);
    // 設定enable
    setBitDepthEnable(true, false, true, false, false);
    setFRCAbility();
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
    setFRCAbility();
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
    setFRCAbility();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_Lut10Click(TObject * Sender)
{
    bitDepth->setLUTBit(10);
    setFRCAbility();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_Lut12Click(TObject * Sender)
{
    bitDepth->setLUTBit(12);
    setFRCAbility();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_Out6Click(TObject * Sender)
{
    bitDepth->setOutBit(6);
    setFRCAbility();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_Out8Click(TObject * Sender)
{
    bitDepth->setOutBit(8);
    setFRCAbility();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_Out10Click(TObject * Sender)
{
    if (!bitDepth->isTCONInput()) {
	ShowMessage("Recommend using T-CON Input.");
    };
    bitDepth->setOutBit(10);
    setFRCAbility();
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::Button1Click(TObject * Sender)
{
    MeasureWindow->setVisible(true);
    MeasureWindow->Visible = true;
    MeasureWindow->setRGB(255, 0, 0);
    Application->ProcessMessages();
    Sleep(300);
    MeasureWindow->setRGB(0, 255, 0);
    Application->ProcessMessages();
    Sleep(300);
    MeasureWindow->setRGB(0, 0, 255);
    Application->ProcessMessages();
    Sleep(1000);
    MeasureWindow->setVisible(false);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Edit_IntervalChange(TObject * Sender)
{
    mm->setWaitTimes(this->getInterval());
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject * Sender)
{
    if (null == meter) {
	ShowMessage("CA210 cannot be linked.");
	//Application->Terminate();
    }
}

//---------------------------------------------------------------------------
void TMainForm::setMeterMeasurementWaitTimes()
{
    this->mm->setWaitTimes(this->getInterval());
};

