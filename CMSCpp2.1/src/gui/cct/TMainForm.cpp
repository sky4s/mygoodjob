//---------------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop
//C系統文件

//C++系統文件

//其他庫頭文件
#include "inifiles.hpp"

//本項目內頭文件
#include "TMainForm.h"
#include "TTargetWhiteForm2.h"
#include "TAboutBox.h"
#include "TCCTLUTForm.h"
#include "../TMatrixCalibration.h"
#include "TGammaAdjustmentForm.h"
#include "TGammaMeasurementForm.h"
#include "../TI2CTestForm.h"

#define SETUPFILE "cctv3.ini"
#define TCONFILE "tcon.ini"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent * Owner):TForm(Owner),
linkCA210(!FileExists(DEBUG_FILE)), newFunction(FileExists(DEBUG_NEWFUNC_FILE))
{
    connectCA210ByThread = true;
    //StatusBar1->SimplePanel = true;
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
    disconnectMeter();
    this->Close();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::TargetWhite1Click(TObject * Sender)
{
    if (TargetWhiteForm2 == null) {
	Application->CreateForm(__classid(TTargetWhiteForm2), &TargetWhiteForm2);
    }
    TargetWhiteForm2->setBitDepthProcessor(bitDepth);
    if (null != I2CTestForm && I2CTestForm->Showing) {
	TargetWhiteForm2->Show();
    } else {
	TargetWhiteForm2->ShowModal();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject * Sender)
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    using namespace cms::lcd::calibrate;
    using namespace gui::util;

    bitDepth = bptr < BitDepthProcessor > (new BitDepthProcessor(8, 12, 8, false));


    initTCONFile();
    readTCONSections();
    readSetup();

}

void TMainForm::initTCONFile()
{
    using namespace cms::util;
    tconFilename = ExtractFilePath(Application->ExeName) + TCONFILE;
    if (!Util::isFileExist(tconFilename.c_str())) {
	//=========================================================================================
	// produce tcon ini file
	//=========================================================================================
	bptr_ < TIniFile > ini(new TIniFile(tconFilename));

	//=========================================================================
	// 11303
	//=========================================================================
	ini->WriteInteger("11303", "AddressingSize", 5);

	ini->WriteString("11303", "DigitalGammaEnableAddress", "4");
	ini->WriteInteger("11303", "DigitalGammaEnableBit", 1);
	ini->WriteString("11303", "DigitalGammaLUTAddress", "302");
	ini->WriteInteger("11303", "DigitalGammaLUTType", 10);

	ini->WriteBool("11303", "GammaTestFunc", false);

	ini->WriteInteger("11303", "in", 8);
	ini->WriteInteger("11303", "out", 8);
	//=========================================================================
	// 11306
	//=========================================================================
	ini->WriteInteger("11306", "AddressingSize", 5);

	ini->WriteString("11306", "DigitalGammaEnableAddress", "28");
	ini->WriteInteger("11306", "DigitalGammaEnableBit", 0);
	ini->WriteString("11306", "DigitalGammaLUTAddress", "3C0");
	ini->WriteInteger("11306", "DigitalGammaLUTType", 10);

	ini->WriteBool("11306", "GammaTestFunc", true);
	ini->WriteString("11306", "GammaTestEnableAddress", "381");
	ini->WriteInteger("11306", "GammaTestEnableBit", 1);
	ini->WriteString("11306", "GammaTestAddress", "387");
	ini->WriteBool("11306", "IndepRGB", true);

	ini->WriteInteger("11306", "in", 6);
	ini->WriteInteger("11306", "out", 6);
	//=========================================================================
	// 11307
	//=========================================================================
	ini->WriteInteger("11307", "AddressingSize", 5);

	ini->WriteString("11307", "DigitalGammaEnableAddress", "28");
	ini->WriteInteger("11307", "DigitalGammaEnableBit", 0);
	ini->WriteString("11307", "DigitalGammaLUTAddress", "310");
	ini->WriteInteger("11307", "DigitalGammaLUTType", 10);

	ini->WriteBool("11307", "GammaTestFunc", true);
	ini->WriteString("11307", "GammaTestEnableAddress", "2F1");
	ini->WriteInteger("11307", "GammaTestEnableBit", 1);
	ini->WriteString("11307", "GammaTestAddress", "2F3");
	ini->WriteBool("11307", "IndepRGB", true);

	ini->WriteInteger("11307", "in", 6);
	ini->WriteInteger("11307", "out", 6);
	//=========================================================================
	// 12306
	//=========================================================================
	ini->WriteInteger("12306", "AddressingSize", 5);

	ini->WriteString("12306", "DigitalGammaEnableAddress", "28");
	ini->WriteInteger("12306", "DigitalGammaEnableBit", 0);
	ini->WriteString("12306", "DigitalGammaLUTAddress", "302");
	ini->WriteInteger("12306", "DigitalGammaLUTType", 12);

	ini->WriteBool("12306", "GammaTestFunc", true);
	ini->WriteString("12306", "GammaTestEnableAddress", "29");
	ini->WriteInteger("12306", "GammaTestEnableBit", 0);
	ini->WriteString("12306", "GammaTestAddress", "154");
	ini->WriteBool("12306", "IndepRGB", true);

	ini->WriteInteger("12306", "in", 8);
	ini->WriteInteger("12306", "out", 8);
	//=========================================================================
	// 12401
	//=========================================================================
	ini->WriteInteger("12401", "AddressingSize", 5);

	ini->WriteString("12401", "DigitalGammaEnableAddress", "28");
	ini->WriteInteger("12401", "DigitalGammaEnableBit", 0);
	ini->WriteString("12401", "DigitalGammaLUTAddress", "752");
	ini->WriteInteger("12401", "DigitalGammaLUTType", 12);

	ini->WriteBool("12401", "GammaTestFunc", true);
	ini->WriteString("12401", "GammaTestEnableAddress", "4A1");
	ini->WriteInteger("12401", "GammaTestEnableBit", 1);
	ini->WriteString("12401", "GammaTestAddress", "4A7");
	ini->WriteBool("12401", "IndepRGB", true);

	ini->WriteInteger("12401", "in", 8);
	ini->WriteInteger("12401", "out", 8);
	//=========================================================================
	// 12405
	//=========================================================================
	ini->WriteInteger("12405", "AddressingSize", 5);

	ini->WriteString("12405", "DigitalGammaEnableAddress", "29");
	ini->WriteInteger("12405", "DigitalGammaEnableBit", 0);
	ini->WriteString("12405", "DigitalGammaLUTAddress", "106D");
	ini->WriteInteger("12405", "DigitalGammaLUTType", 12);

	ini->WriteBool("12405", "GammaTestFunc", true);
	ini->WriteString("12405", "GammaTestEnableAddress", "1FEB");
	ini->WriteInteger("12405", "GammaTestEnableBit", 4);
	ini->WriteString("12405", "GammaTestAddress", "1FEC");
	ini->WriteBool("12405", "IndepRGB", false);

	ini->WriteInteger("12405", "in", 8);
	ini->WriteInteger("12405", "out", 8);
	//=========================================================================
	//=========================================================================
	// 12407
	//=========================================================================
	ini->WriteInteger("12407", "AddressingSize", 5);

	ini->WriteString("12407", "DigitalGammaEnableAddress", "29");
	ini->WriteInteger("12407", "DigitalGammaEnableBit", 0);
	ini->WriteString("12407", "DigitalGammaLUTAddress", "110D");
	ini->WriteInteger("12407", "DigitalGammaLUTType", 12);

	ini->WriteBool("12407", "GammaTestFunc", true);
	ini->WriteString("12407", "GammaTestEnableAddress", "3FEB");
	ini->WriteInteger("12407", "GammaTestEnableBit", 4);
	ini->WriteString("12407", "GammaTestAddress", "3FEC");
	ini->WriteBool("12407", "IndepRGB", false);

	ini->WriteInteger("12407", "in", 8);
	ini->WriteInteger("12407", "out", 8);
	//=========================================================================
    }
}

void TMainForm::readTCONSections()
{
    bptr_ < TIniFile > ini(new TIniFile(tconFilename));
    bptr_ < TStringList > tconSections(new TStringList());
    ini->ReadSections(tconSections.get());
    int size = tconSections->Count;
    for (int x = 0; x < size; x++) {
	String section = (*tconSections)[x];
	ComboBox_TCONType->AddItem(section, null);
    }
    ComboBox_TCONType->AddItem(CUSTOM, null);
    ComboBox_TCONType->ItemIndex = 0;
}

void TMainForm::readTCONSetup(String filename, String section)
{
    //=========================================================================
    bptr_ < TIniFile > ini(new TIniFile(filename));
    this->ComboBox_AddressingSize->ItemIndex = ini->ReadInteger(section, "AddressingSize", 5);
    bool gammaTestFunc = ini->ReadBool(section, "GammaTestFunc", true);

    if (gammaTestFunc) {
	GroupBox_GammaTestAddress->Visible = true;
	this->Edit_GammaTestEnableAddress->Text =
	    ini->ReadString(section, "GammaTestEnableAddress", "29");
	this->Edit_GammaTestEnableBit->Text = ini->ReadInteger(section, "GammaTestEnableBit", 0);
	this->Edit_GammaTestAddress->Text = ini->ReadString(section, "GammaTestAddress", "154");
	this->ComboBox_GammaTestType->ItemIndex = ini->ReadBool(section, "IndepRGB", true) ? 0 : 1;
	ComboBox_GammaTestTypeChange(this);
    }
    CheckBox_GammaTest->Checked = gammaTestFunc;

    this->Edit_DGEnableAddress->Text = ini->ReadString(section, "DigitalGammaEnableAddress", "28");
    this->Edit_DGEnableBit->Text = ini->ReadInteger(section, "DigitalGammaEnableBit", 0);
    this->Edit_DGLUTAddress->Text = ini->ReadString(section, "DigitalGammaLUTAddress", "302");
    int lut = ini->ReadInteger(section, "DigitalGammaLUTType", 10);
    this->ComboBox_DGLUTType->Text = lut;
    switch (lut) {
    case 10:
	RadioButton_Lut10->Checked = true;
	break;
    case 12:
	RadioButton_Lut12->Checked = true;
	break;
    }

    if (section != "Custom") {

	int in = ini->ReadInteger(section, "in", 6);
	int out = ini->ReadInteger(section, "out", 6);
	switch (in) {
	case 6:
	    RadioButton_In6->Checked = true;
	    break;
	case 8:
	    RadioButton_In8->Checked = true;
	    break;
	case 10:
	    RadioButton_In10->Checked = true;
	    break;
	}

	switch (out) {
	case 6:
	    RadioButton_Out6->Checked = true;
	    break;
	case 8:
	    RadioButton_Out8->Checked = true;
	    break;
	case 10:
	    RadioButton_Out10->Checked = true;
	    break;
	}
    }

}
const char *TMainForm::CUSTOM = "Custom";
void TMainForm::writeTCONCustomSetup()
{

    if (ComboBox_TCONType->Text == CUSTOM) {
	bptr_ < TIniFile > ini(new TIniFile(ExtractFilePath(Application->ExeName) + SETUPFILE));

	ini->WriteString(CUSTOM, "DigitalGammaEnableAddress", this->Edit_DGEnableAddress->Text);
	ini->WriteInteger(CUSTOM, "DigitalGammaEnableBit", this->Edit_DGEnableBit->Text.ToInt());
	ini->WriteString(CUSTOM, "DigitalGammaLUTAddress", this->Edit_DGLUTAddress->Text);
	ini->WriteInteger(CUSTOM, "DigitalGammaLUTType", ComboBox_DGLUTType->Text.ToInt());

	bool gammaTest = CheckBox_GammaTest->Checked;
	//CheckBox_GammaTest->Checked = gammaTest;
	//bool gammaTest = true;
	ini->WriteBool(CUSTOM, "GammaTestFunc", gammaTest);
	if (gammaTest) {
	    ini->WriteString(CUSTOM, "GammaTestEnableAddress",
			     this->Edit_GammaTestEnableAddress->Text);
	    ini->WriteInteger(CUSTOM, "GammaTestEnableBit",
			      this->Edit_GammaTestEnableBit->Text.ToInt());
	    ini->WriteString(CUSTOM, "GammaTestAddress", this->Edit_GammaTestAddress->Text);
	    ini->WriteBool(CUSTOM, "IndepRGB", this->CheckBox_GammaTestIndepRGB->Checked);
	}
	int in = bitDepth->getInputMaxValue().bit;
	int out = bitDepth->getOutputMaxValue().bit;
	ini->WriteInteger(CUSTOM, "in", in);
	ini->WriteInteger(CUSTOM, "out", out);
    }

};

void TMainForm::readSetup()
{
    bptr_ < TIniFile > ini(new TIniFile(ExtractFilePath(Application->ExeName) + SETUPFILE));
    //=========================================================================
    int cardIndex = ini->ReadInteger("I2C", "Card", 2);
    switch (cardIndex) {
    case 0:
	this->RadioButton_USB->Checked = true;
	break;
    case 1:
	this->RadioButton_LPTLarge->Checked = true;
	break;
    case 2:
	this->RadioButton_LPTSmall->Checked = true;
	break;
    };
    //=========================================================================
    int tconIndex = ini->ReadInteger("TCON", "Count", 0);
    switch (tconIndex) {
    case 0:
	this->RadioButton_SingleTCON->Checked = true;
	break;
    case 1:
	this->RadioButton_DualTCON->Checked = true;
	break;
    }
    //=========================================================================
    int typeIndex = ini->ReadInteger("TCON", "Type", 0);
    ComboBox_TCONType->ItemIndex = typeIndex;
    //=========================================================================
}

void TMainForm::writeSetup()
{
    bptr_ < TIniFile > ini(new TIniFile(ExtractFilePath(Application->ExeName) + SETUPFILE));
    //=========================================================================
    int cardIndex = this->RadioButton_LPTLarge->Checked ? 1 : 0;
    cardIndex += this->RadioButton_LPTSmall->Checked ? 2 : 0;
    ini->WriteInteger("I2C", "Card", cardIndex);
    //=========================================================================
    int tconIndex = this->RadioButton_DualTCON->Checked ? 1 : 0;
    ini->WriteInteger("TCON", "Count", tconIndex);
    //=========================================================================
    int typeIndex = ComboBox_TCONType->ItemIndex;
    ini->WriteInteger("TCON", "Type", typeIndex);

}

//---------------------------------------------------------------------------
void TMainForm::initCA210Meter()
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    try {
	meter = bptr < Meter > (new CA210());
	mm = bptr < MeterMeasurement > (new MeterMeasurement(meter, false));
	mm->WaitTimes = this->getInterval();
	StatusBar1->Panels->Items[1]->Text = "CA-210 Connected!";

	bptr < ca210api::CA210API > ca210api = getCA210()->getCA210API();
	//取出原先的ch
	long ch = ca210api->getChannelNO();
	Edit_SourceCH->Text = ch;
	GroupBox_CHSetting->Enabled = true;
	getAnalyzer();


	if (connectCA210ByThread) {
	    stopProgress(MainForm->ProgressBar1);
	    Enabled = true;
	    ca210Thread->Terminate();
	    delete ca210Thread;
	    ca210Thread = null;
	}

    }
    catch(EOleException & ex) {
	if (connectCA210ByThread) {
	    stopProgress(MainForm->ProgressBar1);
	    Enabled = true;
	}

	ShowMessage
	    ("CA210 cannot be linked or unsupported version of CA-SDK (CA-SDK v4.10 up needed).");
	//this->Close();

    }
};

int TMainForm::getAverageTimes()
{
    return Edit_AverageTimes->Text.ToInt();
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
	    return bptr < IntensityAnalyzerIF > ((IntensityAnalyzerIF *) null);
	}
	if (null == ca210Analyzer) {
	    ca210Analyzer = bptr < CA210IntensityAnalyzer > (new CA210IntensityAnalyzer(ca210, mm));
	}
	//產生max matrix
	bptr < MaxMatrixIntensityAnalyzer > ma(new MaxMatrixIntensityAnalyzer(mm));


	if (true == this->RadioButton_AnalyzerCA210->Checked) {
	    analyzer = ca210Analyzer;
	} else if (true == this->RadioButton_AnalyzerMaxMatrix->Checked) {
	    analyzer = ma;
	} else if (true == this->RadioButton_AnalyzerDebug->Checked) {
	    //產生兩者的合體
	    analyzer = bptr < IntensityAnalyzerIF > (new IntensityAnayzer(ma, ca210Analyzer));
	}
    }
    return analyzer;
}

bptr < cms::measure::MaxMatrixIntensityAnalyzer > TMainForm::getNativeWhiteAnalyzer()
{
    return nativeWhiteAnalyzer;
};

//---------------------------------------------------------------------------
/*
  dprecated
*/
void TMainForm::setAnalyzerToTargetChannel()
{
    using namespace std;


    if (true == linkCA210) {
	if (null == ca210Analyzer) {
	    throw java::lang::IllegalStateException("call getAnalyzer()first !");
	}
	//撈出channel no和id
	/*int channel = this->Edit_TargetCH->Text.ToInt();
	   string targetid = Edit_TargetID->Text.c_str();
	   //若沒有值強制指定為空白字元的字串
	   targetid = targetid.empty()? string("") : targetid;
	   string_ptr id(new string(targetid));
	   //設定在ca210
	   ca210Analyzer->setChannel(channel, id); */

    }
};

//---------------------------------------------------------------------------

void TMainForm::setAnalyzerToSourceChannel()
{
    using namespace std;
    if (true == linkCA210) {
	if (null == ca210Analyzer) {
	    throw java::lang::IllegalStateException("call getAnalyzer()first !");
	}
	//撈出channel no和id
	int channel = this->Edit_SourceCH->Text.ToInt();
	string_ptr id(new string(""));
	//設定在ca210
	ca210Analyzer->setChannel(channel, id);


    }
};

//---------------------------------------------------------------------------
bool TMainForm::isCA210Analyzer()
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    using namespace cms::lcd::calibrate;
    if (null != analyzer) {
	CA210IntensityAnalyzer *ca210Analyzer =
	    dynamic_cast < CA210IntensityAnalyzer * >(analyzer.get());
	return null != ca210Analyzer;
    } else {
	return false;
    }
};

//---------------------------------------------------------------------------
void TMainForm::setDummyMeterFilename(const std::string & filename)
{
    using namespace cms::colorformat;
    bptr < DGLutFile > dglutFile(new DGLutFile(filename, ReadOnly));
    setDummyMeterFile(dglutFile);
}

//---------------------------------------------------------------------------
void TMainForm::setDummyMeterFile(bptr < cms::colorformat::DGLutFile > dglutFile)
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    using namespace cms::lcd::calibrate;
    using namespace Indep;
    using namespace Dep;

    meter = bptr < Meter > (new DGLutFileMeter(dglutFile));
    mm = bptr < MeterMeasurement > (new MeterMeasurement(meter, false));
    mm->FakeMeasure = true;

    fetcher = bptr < ComponentFetcher > ((ComponentFetcher *) null);

    bptr < DGLutProperty > property = dglutFile->getProperty();
    if (null != property) {
	//若有property則為新版
	bptr < MaxMatrixIntensityAnalyzer > matrixAnalyzer(new MaxMatrixIntensityAnalyzer(mm));
	analyzer = matrixAnalyzer;

	//=====================================================================
	// 設定target analyzer
	//=====================================================================
	xyY_ptr targetwxyY = property->getTargetReferenceColor(Channel::W);
	if (null != targetwxyY) {
	    xyY_ptr rxyY = property->getTargetReferenceColor(Channel::R);
	    xyY_ptr gxyY = property->getTargetReferenceColor(Channel::G);
	    xyY_ptr bxyY = property->getTargetReferenceColor(Channel::B);

	    matrixAnalyzer->setupComponent(Channel::W, targetwxyY->toXYZ());
	    matrixAnalyzer->setupComponent(Channel::R, rxyY->toXYZ());
	    matrixAnalyzer->setupComponent(Channel::G, gxyY->toXYZ());
	    matrixAnalyzer->setupComponent(Channel::B, bxyY->toXYZ());
	    matrixAnalyzer->enter();

	    string_ptr comment = property->getProperty("reference white comment");
	    if (null != comment) {
		matrixAnalyzer->setReferenceColorComment(*comment);
	    }
	    RGB_ptr rgb = property->getTargetReferenceRGB();
	    matrixAnalyzer->setReferenceRGB(rgb);
	}
	//=====================================================================

	//=====================================================================
	// 設定native analyzer
	//=====================================================================
	xyY_ptr nativewxyY = property->getNativeReferenceColor(Channel::W);
	if (null != nativewxyY) {
	    bptr < MaxMatrixIntensityAnalyzer > matrixAnalyzer2(new MaxMatrixIntensityAnalyzer(mm));
	    nativeWhiteAnalyzer = matrixAnalyzer2;
	    xyY_ptr rxyY = property->getNativeReferenceColor(Channel::R);
	    xyY_ptr gxyY = property->getNativeReferenceColor(Channel::G);
	    xyY_ptr bxyY = property->getNativeReferenceColor(Channel::B);

	    matrixAnalyzer2->setupComponent(Channel::W, nativewxyY->toXYZ());
	    matrixAnalyzer2->setupComponent(Channel::R, rxyY->toXYZ());
	    matrixAnalyzer2->setupComponent(Channel::G, gxyY->toXYZ());
	    matrixAnalyzer2->setupComponent(Channel::B, bxyY->toXYZ());
	    matrixAnalyzer2->enter();
	}
	//=====================================================================

	//=====================================================================
	// BitDepthProcessor
	//=====================================================================
	bptr < BitDepthProcessor > bitDepth = property->getBitDepthProcessor();
	switch (bitDepth->getInputMaxValue().bit) {
	case 6:
	    RadioButton_In6->Checked = true;
	    break;
	case 8:
	    RadioButton_In8->Checked = true;
	    break;
	case 10:
	    RadioButton_In10->Checked = true;
	    break;
	}
	switch (bitDepth->getLutMaxValue().bit) {
	case 10:
	    RadioButton_Lut10->Checked = true;
	    break;
	case 12:
	    RadioButton_Lut12->Checked = true;
	    break;
	}
	switch (bitDepth->getOutputMaxValue().bit) {
	case 6:
	    RadioButton_Out6->Checked = true;
	    break;
	case 8:
	    RadioButton_Out8->Checked = true;
	    break;
	case 10:
	    RadioButton_Out10->Checked = true;
	    break;
	}
	//=====================================================================

    } else {
	ShowMessage("Old version Raw Data.");
	//無property則為舊版
	analyzer = bptr < CA210IntensityAnalyzer > (new CA210IntensityAnalyzer(mm));
    }
}


//---------------------------------------------------------------------------

void TMainForm::resetDummyMeter()
{
    using namespace cms::measure::meter;
    using namespace cms::lcd::calibrate;
    DGLutFileMeter *dgc = dynamic_cast < DGLutFileMeter * >(meter.get());
    if (null != dgc) {
	dgc->reset();
    }
};

//---------------------------------------------------------------------------
void TMainForm::setAnalyzerNull()
{
    analyzer.reset();
    fetcher.reset();
}

//---------------------------------------------------------------------------

bptr < cms::lcd::calibrate::ComponentFetcher > TMainForm::getComponentFetcher()
{
    using namespace cms::lcd::calibrate;
    if (null == fetcher) {
	bptr < cms::measure::IntensityAnalyzerIF > analyzer = getAnalyzer();
	fetcher = bptr < ComponentFetcher > (new cms::lcd::calibrate::
					     ComponentFetcher(analyzer, bitDepth));
	MeasureWindow->addWindowListener(fetcher);
    }

    return fetcher;
};

//---------------------------------------------------------------------------
bptr < cms::measure::meter::CA210 > TMainForm::getCA210()
{
    if (null == ca210 && true == linkCA210) {
	using namespace cms::measure::meter;
	if (null == meter) {
	    ShowMessage("CA210 cannot be linked.");
	    return bptr < CA210 > ((CA210 *) null);
	}

	cms::measure::meter::Meter * pointer = meter.get();
	ca210 = bptr < CA210 > (dynamic_cast < CA210 * >(pointer));
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
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::lcd::calibrate;
    if (CCTLUTForm == null) {
	Application->CreateForm(__classid(TCCTLUTForm), &CCTLUTForm);
    }

    if (true == this->RadioButton_AnalyzerMaxMatrix->Checked) {
	MaxMatrixIntensityAnalyzer *ma =
	    dynamic_cast < MaxMatrixIntensityAnalyzer * >(analyzer.get());
	if (null == ma || ma->isInverseMatrixNull()) {
	    ShowMessage("Set \"Target White \"first.");
	    return;
	}
    }

    CCTLUTForm->setBitDepthProcessor(bitDepth);
    CCTLUTForm->ShowModal();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::GammaAdj1Click(TObject * Sender)
{
    if (GammaAdjustmentForm == null) {
	Application->CreateForm(__classid(TGammaAdjustmentForm), &GammaAdjustmentForm);
    }
    GammaAdjustmentForm->setBitDepthProcessor(bitDepth);
    GammaAdjustmentForm->ShowModal();
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::RadioButton_TCONClick(TObject * Sender)
{
    this->Panel_TCON->Visible = true;
    ComboBox_TCONTypeChange(this);
    ShowMessage("Please Turn On DG and FRC for Measurement when T-CON Input Source is selected!!!");
    PageControl1->ActivePageIndex = 1;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_PCClick(TObject * Sender)
{
    this->Panel_TCON->Visible = false;
    bitDepth->setTCONInput(false);
    MeasureWindow->setTCONControlOff();
    control.reset();
    Button_Connect->Enabled = true;
    this->StatusBar1->Panels->Items[2]->Text = "T-CON Disconnected";
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::Button_ConnectClick(TObject * Sender)
{
    using namespace i2c;
    using namespace Dep;
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
	USBPower power = (USBPower) RadioGroup_USBPower->ItemIndex;
	USBSpeed speed = (USBSpeed) RadioGroup_Speed->ItemIndex;

	i2c1st = i2cControl::getUSBInstance(first, addressingSize, power, speed);
	if (dual) {
	    i2c2nd = i2cControl::getUSBInstance(second, addressingSize, power, speed);
	};
    } else {

	const LPTCard card = this->RadioButton_LPTLarge->Checked ? Large : Small;
	try {
	    i2c1st = i2cControl::getLPTInstance(first, addressingSize, card);
	    if (dual) {
		i2c2nd = i2cControl::getLPTInstance(second, addressingSize, card);
	    };
	}
	catch(java::lang::IllegalStateException & ex) {
	    ShowMessage(ex.toString().c_str());
	    return;
	}
    };
    bool connect = i2c1st->connect();
    if (dual) {
	i2c2nd->connect();
    }

    if (true == connect) {
	//=====================================================================
	// digital gamma
	//=====================================================================
	int dgEnableAddress = StrToInt("0x" + Edit_DGEnableAddress->Text);
	int dgEnableBit = this->Edit_DGEnableBit->Text.ToInt();
	int dgLUTAddress = StrToInt("0x" + Edit_DGLUTAddress->Text);
	int dgLUTType = ComboBox_DGLUTType->Text.ToInt();
	//=====================================================================
	//=====================================================================
	// gamma test
	//=====================================================================
	bool gammaTest = CheckBox_GammaTest->Checked;
	//bool gammaTest = true;
	if (gammaTest) {
	    int gammaTestAddress = StrToInt("0x" + this->Edit_GammaTestEnableAddress->Text);
	    int gammaTestBit = this->Edit_GammaTestEnableBit->Text.ToInt();
	    int testRGBAddress = StrToInt("0x" + this->Edit_GammaTestAddress->Text);
	    bool indepRGB = this->ComboBox_GammaTestType->ItemIndex == 0;
	    const TestRGBBit & testRGBBit = indepRGB ? TestRGBBit::
		IndependentInstance : TestRGBBit::DependentInstance;

	    parameter =
		bptr < TCONParameter >
		(new
		 TCONParameter(dgLUTType == 10 ? MaxValue::Int10Bit : MaxValue::Int12Bit,
			       dgLUTAddress, dgEnableAddress, dgEnableBit, gammaTestAddress,
			       gammaTestBit, testRGBAddress, testRGBBit));
	} else {
	    parameter =
		bptr < TCONParameter >
		(new
		 TCONParameter(dgLUTType == 10 ? MaxValue::Int10Bit : MaxValue::Int12Bit,
			       dgLUTAddress, dgEnableAddress, dgEnableBit));
	}

	//=====================================================================


	if (!dual) {
	    control = bptr < TCONControl > (new TCONControl(parameter, i2c1st));
	} else {
	    control = bptr < TCONControl > (new TCONControl(parameter, i2c1st, i2c2nd));
	}
	this->Button_Connect->Enabled = false;
	this->StatusBar1->Panels->Items[2]->Text = "T-CON Connected";
	if (!this->RadioButton_PCTCON_NB->Checked) {

	    if (this->RadioButton_PCTCON_TV->Checked) {
		MeasureWindow->setDGLUTInput(control, bitDepth);
		this->bitDepth->setTCONInput(true);
	    } else {

		MeasureWindow->setTCONInput(control);
		this->bitDepth->setTCONInput(true);
	    }
	}


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



void __fastcall TMainForm::Measurement1Click(TObject * Sender)
{
    if (GammaMeasurementForm == null) {
	Application->CreateForm(__classid(TGammaMeasurementForm), &GammaMeasurementForm);
    }
    GammaMeasurementForm->setBitDepthProcessor(bitDepth);
    GammaMeasurementForm->ShowModal();
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::MatrixCalibration1Click(TObject * Sender)
{
    if (MatrixCalibrationForm == null) {
	Application->CreateForm(__classid(TMatrixCalibrationForm), &MatrixCalibrationForm);
    }

    if (true == linkCA210 && true == MatrixCalibrationForm->setMeter(getCA210()->getCA210API(), mm)) {
	MatrixCalibrationForm->ShowModal();
    } else {
	MatrixCalibrationForm->ShowModal();
    }

}

//---------------------------------------------------------------------------

void TMainForm::setBitDepthEnable(bool lut10, bool lut12, bool out6, bool out8, bool out10)
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
    setBitDepthChecked(1, 1);
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
    if (!bitDepth->isTCONInput() && this->Visible) {
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
    setMeterMeasurementWaitTimes();
}

//---------------------------------------------------------------------------

void TMainForm::setMeterMeasurementWaitTimes()
{
    this->mm->WaitTimes = this->getInterval();
};
void __fastcall TMainForm::Button_I2CTestClick(TObject * Sender)
{
    if (I2CTestForm == null) {
	Application->CreateForm(__classid(TI2CTestForm), &I2CTestForm);
    }
    I2CTestForm->Edit_GammaTestAddress->Text = this->Edit_GammaTestEnableAddress->Text;
    I2CTestForm->Edit_GammaTestBit->Text = this->Edit_GammaTestEnableBit->Text;
    I2CTestForm->Edit_TestRGBAdress->Text = this->Edit_GammaTestAddress->Text;
    I2CTestForm->ComboBox_AddressingSize->ItemIndex = this->ComboBox_AddressingSize->ItemIndex;
    I2CTestForm->RadioButton_LPTLarge->Checked = this->RadioButton_LPTLarge->Checked;
    I2CTestForm->RadioButton_LPTSmall->Checked = this->RadioButton_LPTSmall->Checked;
    I2CTestForm->RadioButton_USB->Checked = this->RadioButton_USB->Checked;
    I2CTestForm->RadioButton_Single->Checked = this->RadioButton_SingleTCON->Checked;
    I2CTestForm->RadioButton_Dual->Checked = this->RadioButton_DualTCON->Checked;
    I2CTestForm->CheckBox_IndepRGB->Checked = this->CheckBox_GammaTestIndepRGB->Checked;
    I2CTestForm->setBitDepthProcessor(bitDepth);
    //I2CTestForm->ShowModal();
    I2CTestForm->Height = 350;
    I2CTestForm->Width = 350;
    I2CTestForm->Show();
}

//---------------------------------------------------------------------------

void TMainForm::disconnectMeter()
{
    bptr < cms::measure::meter::CA210 > ca210 = getCA210();
    if (null != ca210) {
	ca210->getCA210API()->setRemoteMode(ca210api::Off);
    }
};
void TMainForm::connectMeter()
{

    bptr < cms::measure::meter::CA210 > ca210 = getCA210();
    if (null != ca210) {
	ca210->getCA210API()->setRemoteMode(ca210api::Locked);
    }
};
void __fastcall TMainForm::RadioButton_AnalyzerMaxMatrixClick(TObject * Sender)
{
    setAnalyzerNull();
    Edit_TargetCH->Enabled = false;
    Edit_TargetID->Enabled = false;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_AnalyzerCA210Click(TObject * Sender)
{
    setAnalyzerNull();
    Edit_TargetCH->Enabled = true;
    Edit_TargetID->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_AnalyzerDebugClick(TObject * Sender)
{
    setAnalyzerNull();
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::RadioButton_NormalClick(TObject * Sender)
{
    MeasureWindow->setPattern(Normal);
    this->CheckBox_LineAdjoin->Visible = false;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_HStripeClick(TObject * Sender)
{
    MeasureWindow->setPattern(HStripe);
    this->CheckBox_LineAdjoin->Visible = false;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_IndepClick(TObject * Sender)
{
    MeasureWindow->setPattern(Indepedent);
    this->CheckBox_LineAdjoin->Visible = true;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_HSDClick(TObject * Sender)
{
    MeasureWindow->setPattern(HSD);
    this->CheckBox_LineAdjoin->Visible = true;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_FlickrPixelClick(TObject * Sender)
{
    MeasureWindow->setPattern(FlickrPixel);
    this->CheckBox_LineAdjoin->Visible = false;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_FlickrSubPixelClick(TObject * Sender)
{
    MeasureWindow->setPattern(FlickrSubPixel);
    this->CheckBox_LineAdjoin->Visible = false;
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::ComboBox_GammaTestTypeChange(TObject * Sender)
{
    bool indepRGB = this->ComboBox_GammaTestType->ItemIndex == 0;
    CheckBox_GammaTestIndepRGB->Checked = indepRGB;
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::FormDestroy(TObject * Sender)
{
    writeSetup();
    writeTCONCustomSetup();
    if (null != ca210) {
	ca210->close();
    }
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::RadioButton_USBClick(TObject * Sender)
{
    Button_Connect->Enabled = true;
    GroupBox_USBSetting->Visible = true;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_LPTLargeClick(TObject * Sender)
{
    Button_Connect->Enabled = true;
    GroupBox_USBSetting->Visible = false;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_LPTSmallClick(TObject * Sender)
{
    Button_Connect->Enabled = true;
    GroupBox_USBSetting->Visible = false;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ComboBox_TCONTypeChange(TObject * Sender)
{
    using namespace cms::util;
    String section = this->ComboBox_TCONType->Text;
    if (section != null && section.Length() != 0 && section != "Custom") {
	CheckBox_GammaTest->Visible = false;
	if (Util::isFileExist(tconFilename.c_str())) {
	    readTCONSetup(tconFilename, section);

	    GroupBox_DigitalGamma->Enabled = false;
	    //GroupBox_DigitalGamma->Visible = false;
	    GroupBox_GammaTestAddress->Enabled = false;
	}
    } else {
	ShowMessage("Remember setting Bit Depth!");

	readTCONSetup(ExtractFilePath(Application->ExeName) + SETUPFILE, "Custom");
	CheckBox_GammaTest->Visible = true;
	CheckBox_GammaTestClick(null);
	GroupBox_DigitalGamma->Enabled = true;
	//GroupBox_DigitalGamma->Visible = true;
	GroupBox_GammaTestAddress->Enabled = true;
    }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox_GammaTestClick(TObject * Sender)
{
    bool gammaTest = this->CheckBox_GammaTest->Checked;
    GroupBox_GammaTestAddress->Visible = gammaTest;
}

//---------------------------------------------------------------------------
bptr < i2c::TCONControl > TMainForm::getTCONControl()
{
    return control;
};
bool TMainForm::isTCONInput()
{
    return true == RadioButton_TCON->Checked;
};

bool TMainForm::isPCwithTCONInput()
{
    return true == RadioButton_PCTCON_TV->Checked || true == RadioButton_PCTCON_NB->Checked;
};

void __fastcall TMainForm::RadioButton_PCTCON_NBClick(TObject * Sender)
{
    this->Panel_TCON->Visible = true;
    ComboBox_TCONTypeChange(this);
    bitDepth->setTCONInput(false);
    MeasureWindow->setTCONControlOff();
    PageControl1->ActivePageIndex = 1;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_NinthClick(TObject * Sender)
{
    MeasureWindow->setPattern(Ninth);
    this->CheckBox_LineAdjoin->Visible = false;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::ComboBox_DGLUTTypeChange(TObject * Sender)
{
    int lut = ComboBox_DGLUTType->Text.ToInt();
    switch (lut) {
    case 10:
	if (RadioButton_Lut10->Enabled) {
	    RadioButton_Lut10->Checked = true;
	} else {
	    ShowMessage("Cannot select 10Bit LUT in present Bit Depth setting");
	    ComboBox_DGLUTType->ItemIndex = 1;
	}
	break;
    case 12:
	if (RadioButton_Lut12->Enabled) {
	    RadioButton_Lut12->Checked = true;
	} else {
	    ShowMessage("Cannot select 12Bit LUT in present Bit Depth setting");
	    ComboBox_DGLUTType->ItemIndex = 0;
	}
	break;
    }
}

//---------------------------------------------------------------------------



void TMainForm::showProgress(TProgressBar * progress)
{
    if (null != progressThread) {
	progressThread->Terminate();
	delete progressThread;

    }
    progress->Visible = true;
    progressThread = new ProgressThread(false, progress);
    progressThread->Resume();
};
void TMainForm::stopProgress(TProgressBar * progress)
{

    if (null != progressThread) {
	progressThread->Terminate();
	progress->Visible = false;
	delete progressThread;
	progressThread = null;
    }
};


//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ProgressThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall ProgressThread::ProgressThread(bool CreateSuspended, TProgressBar * progress)
:TThread(CreateSuspended), progress(progress)
{
}

//---------------------------------------------------------------------------
void __fastcall ProgressThread::Execute()
{
    //---- Place thread code here ----
    while (!this->Terminated) {
	Application->ProcessMessages();
	Sleep(50);
	progress->StepIt();
    }
}

//---------------------------------------------------------------------------
/*
CA-X10 init procedure
  FormActive
  ->connectCA210ByThread
        true:
                showProgress
                CA210Thread->Resume
                        initCA210Meter();
                        	meter = bptr < Meter > (new CA210());
	                        mm = bptr < MeterMeasurement > (new MeterMeasurement(meter, false));
	                        StatusBar1->Panels->Items[1]->Text = "CA-210 Connected!";

	                        if (connectCA210ByThread) {

        false:
                initCA210Meter();
*/
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormActivate(TObject * Sender)
{
    if (true == linkCA210) {
	if (connectCA210ByThread) {

	    class CA210Thread:public TThread {
	      protected:
		void __fastcall Execute() {
		    MainForm->StatusBar1->Panels->Items[1]->Text = "CA-210 Connecting...";

		    MainForm->Enabled = false;
		    MainForm->initCA210Meter();
		};
	      public:
	      __fastcall CA210Thread(bool CreateSuspended):TThread(CreateSuspended) {
		};
	    };


	    showProgress(ProgressBar1);
	    //memory leakage...but..懶的鳥他, 反正程式關閉的時候,heap就一併清掉
	    ca210Thread = new CA210Thread(false);
	    //改用thread去啟動ca-210, 這樣可以正常更新progress bar!
	    ca210Thread->Resume();
	} else {
	    initCA210Meter();
	}
    } else {
	if (FileExists(METER_FILE)) {
	    setDummyMeterFilename(METER_FILE);
	}
	//this->Caption = this->Caption + " (debug mode)";
	//this->StatusBar1->SimpleText = "Debug mode";
	MainForm->StatusBar1->Panels->Items[1]->Text = "Debug mode";
	this->GroupBox_CHSetting->Visible = false;
    }
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::TabSheet2Exit(TObject * Sender)
{
    if (true == Button_Connect->Enabled) {
	RadioButton_PC->Checked = true;
    }
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::Edit_AverageTimesChange(TObject * Sender)
{
    mm->AverageTimes = this->Edit_AverageTimes->Text.ToInt();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_PCTCON_TVClick(TObject * Sender)
{
    this->Panel_TCON->Visible = true;
    ComboBox_TCONTypeChange(this);
    bitDepth->setTCONInput(false);
    MeasureWindow->setTCONControlOff();
    PageControl1->ActivePageIndex = 1;
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::Edit_SourceCHKeyPress(TObject * Sender, char &Key)
{
    if ('\r' == Key && null != ca210Analyzer) {
	TEdit *edit = dynamic_cast < TEdit * >(Sender);
	int ch = edit->Text.ToInt();
	if (ch >= 0 && ch <= 99) {
	    string_ptr id(new string());
	    ca210Analyzer->setChannel(ch, id);
	}
    }
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::TabSheet2Enter(TObject * Sender)
{
    Button_Connect->Enabled = true;
}

//---------------------------------------------------------------------------

