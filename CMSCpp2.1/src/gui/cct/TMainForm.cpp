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
#include "TChangeLogForm.h"
#include "TCCTLUTForm.h"
#include "../TMatrixCalibration.h"
#include "TGammaAdjustmentForm.h"
#include "TGammaMeasurementForm.h"
#include "../TI2CTestForm.h"
#include "cms/core.h"
#include "TStabilityForm.h"

#define SETUPFILE "cctv3.ini"
#define TCONFILE "tcon.ini"
#define FACTORY_FILE "factory.txt"       //工廠簡化模式 20140605 byBS+

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
bool g_bIsRunAgain = false;


//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent * Owner):TForm(Owner), debugMode(FileExists(DEBUG_FILE)),
linkEyeOne(FileExists("i1.txt")), linkCA210(!FileExists("i1.txt") && !FileExists(DEBUG_FILE)),
newFunction(FileExists(DEBUG_NEWFUNC_FILE)), factoryMode(FileExists(FACTORY_FILE))
{
    //String a = "0100";
    //a[1];

    connectCA210ByThread = true;



    /*using namespace cms;
       using namespace cms::lcd;
       using namespace Dep;
       RGBPatchMap patchMap;
       Patch_vector_ptr vector(new Patch_vector());
       for (int x = 0; x < 10; x++) {
       RGB_ptr rgb(new RGBColor(x, 0, 0));
       Patch_ptr p(new Patch(nil_string_ptr, nil_XYZ_ptr, nil_XYZ_ptr, rgb));
       patchMap.insert(make_pair(rgb, p));
       vector->push_back(p);

       }
       LCDTarget_ptr lcdTarget = LCDTarget::Instance::get(vector);


       Patch_ptr r0p = lcdTarget->getPatch(5, 0, 0);
       RGB_ptr rgb(new RGBColor(5, 0, 0));
       Patch_ptr p = patchMap[rgb];
       int x = 1; */

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

    //=========================================================================
    // 外觀設定檔案讀取
    //=========================================================================
    String manifest = Application->ExeName + ".manifest";
    if (!FileExists(manifest)) {
	int handle = FileCreate(manifest);

	String a = "\
<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n\
<assembly xmlns=\"urn:schemas-microsoft-com:asm.v1\" manifestVersion=\"1.0\">\n\
\t<dependency>\n\
\t\t<dependentAssembly>\n\
\t\t\t<assemblyIdentity type=\"win32\" name=\"Microsoft.Windows.Common-Controls\" version=\"6.0.0.0\" processorArchitecture=\"X86\" publicKeyToken=\"6595b64144ccf1df\" language=\"*\"/>\n\
\t\t</dependentAssembly>\n\
\t</dependency>\n\
</assembly>";


	FileWrite(handle, a.c_str(), a.Length());

	FileClose(handle);
	g_bIsRunAgain = true;
	Application->Terminate();
    }
    //=========================================================================

    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    using namespace cms::lcd::calibrate;
    using namespace cms::lcd;
    using namespace gui::util;

    int_array version = Util::fetchVersionInfo();
    string build =
	" v" + _toString(version[0]) + "." + _toString(version[1]) + "(build:" +
	_toString(version[2]) + "." + _toString(version[3]) + ") ";
    Caption = Caption + build.c_str();

    bitDepth = bptr < BitDepthProcessor > (new BitDepthProcessor(8, 12, 8));

    //初始化參數設定
    initTCONFile();              //Setting all TCON as defult value
    readTCONSections();          //Setting ComboBox_TCONType context
    readSetup();                 //Read cctv3.ini (i2c card/TCONnum/TCONtype)
             //MeasureWindow->Visible=true;

    //Factory Mode    20140605 byBS+
    if(factoryMode)
        initialFactoryIF();

}




void TMainForm::readTCONSetup(String filename, String section)
{
    //=========================================================================
    bptr_ < TIniFile > ini(new TIniFile(filename));
    this->ComboBox_AddressingSize->ItemIndex = ini->ReadInteger(section, "AddressingSize", 5);
    bool directGammaFunc = ini->ReadBool(section, "DirectGammaFunc", false);

    if (directGammaFunc) {
	GroupBox_DirectGamma->Visible = true;
	this->Edit_GammaTestEnableAddress->Text =
	    ini->ReadString(section, "GammaTestEnableAddress", "??");
	this->Edit_GammaTestEnableBit->Text = ini->ReadInteger(section, "GammaTestEnableBit", -1);
	this->Edit_DirectGammaAddress->Text = ini->ReadString(section, "DirectGammaAddress", "??");
	String directGammaType = ini->ReadString(section, "DirectGammaType", "N/A");
	if (directGammaType == "12401Type") {
	    ComboBox_DirectGammaType->ItemIndex = 0;
	} else if (directGammaType == "12403Type") {
	    ComboBox_DirectGammaType->ItemIndex = 1;
	} else if (directGammaType == "62301Type") {
	    ComboBox_DirectGammaType->ItemIndex = 2;
	} else if (directGammaType == "1H501Type") {
	    ComboBox_DirectGammaType->ItemIndex = 3;
	} else if (directGammaType == "12409Type") {
	    ComboBox_DirectGammaType->ItemIndex = 4;
	} else if (directGammaType == "12409Aging"){
	    ComboBox_DirectGammaType->ItemIndex = 5;
	} else if (directGammaType == "11311Type"){
	    ComboBox_DirectGammaType->ItemIndex = 6;
        } else if (directGammaType == "12411Aging"){
	    ComboBox_DirectGammaType->ItemIndex = 7;
        } else if (directGammaType == "12411Type"){
	    ComboBox_DirectGammaType->ItemIndex = 8;
        } else if (directGammaType == "HawkType"){
	    ComboBox_DirectGammaType->ItemIndex = 9;
        } else if (directGammaType == "N/A") {
	    int index = ini->ReadBool(section, "DirectGammaIndepRGB", true) ? 0 : 1;
	    ComboBox_DirectGammaType->ItemIndex = index;
	}

	bool hideFunc = ini->ReadBool(section, "HideFunc", false);
	if (hideFunc) {
	    this->Edit_HideEnableAddress->Text =
		ini->ReadString(section, "HideEnableAddress", "29");
	    this->Edit_HideEnableBit->Text = ini->ReadInteger(section, "HideEnableBit", -1);
	}
	CheckBox_HideEN->Visible = hideFunc;
	CheckBox_HideEN->Checked = hideFunc;
	GroupBox_HideEN->Visible = hideFunc;
    }
    CheckBox_DirectGamma->Checked = directGammaFunc;

    //Aging Mode byBS+
    bool agingFunc = ini->ReadBool(section, "AgingFunc", false);
    if (agingFunc) {
        GroupBox_AgingMode->Visible = true;
        this->Edit_AgingAGBSDebugAddress->Text =
            ini->ReadString(section, "AgingAGBSDebugAddress", "FE8");
        this->Edit_AgingAGBSDebugBit->Text =
            ini->ReadInteger(section, "AgingAGBSDebugBit", -1);

        this->Edit_AgingModeSelectAddress->Text =
            ini->ReadString(section, "AgingModeSelectAddress", "40");
        this->Edit_AgingModeSelectValue->Text =
            ini->ReadInteger(section, "AgingModeSelectValue", -1);
        this->Edit_AgingModeSelectStartBit->Text =
            ini->ReadInteger(section, "AgingModeSelectStartBit", -1);
        this->Edit_AgingModeSelectEndBit->Text =
            ini->ReadInteger(section, "AgingModeSelectEndBit", -1);
        this->Edit_AgingPatternSelectAddress->Text =
            ini->ReadString(section, "AgingPatternSelectAddress", "??");
        this->Edit_AgingPatternSelectValue->Text =
            ini->ReadInteger(section, "AgingPatternSelectValue", -1);
        this->Edit_AgingPatternSelectStartBit->Text =
            ini->ReadInteger(section, "AgingPatternSelectStartBit", -1);
        this->Edit_AgingPatternSelectEndBit->Text =
            ini->ReadInteger(section, "AgingPatternSelectEndBit", -1);
        this->Edit_AgingRasterGrayAddress->Text =
            ini->ReadString(section, "AgingRasterGrayAddress", "??");
        this->Edit_AgingManuSelectAddress->Text =
            ini->ReadString(section, "AgingManuSelectAddress", "N/A");
        this->Edit_AgingManuSelectBit->Text =
            ini->ReadInteger(section, "AgingManuSelectBit", -1);
        String agingType = ini->ReadString(section, "AgingType", "N/A");
        if (agingType == "12401Type") {
            ComboBox_AgingType->ItemIndex = 0;
        } else if (agingType == "12403Type") {
            ComboBox_AgingType->ItemIndex = 1;
        } else if (agingType == "62301Type") {
            ComboBox_AgingType->ItemIndex = 2;
        } else if (agingType == "1H501Type") {
            ComboBox_AgingType->ItemIndex = 3;
        } else if (agingType == "12409Type") {
            ComboBox_AgingType->ItemIndex = 4;
        } else if (agingType == "12409Aging") {
            ComboBox_AgingType->ItemIndex = 5;
        } else if (agingType == "11311Type") {
            ComboBox_AgingType->ItemIndex = 6;
        } else if (agingType == "12411Aging") {
            ComboBox_AgingType->ItemIndex = 7;
        } else if (agingType == "12411Type") {
            ComboBox_AgingType->ItemIndex = 8;
        } else if (agingType == "HawkType") {
            ComboBox_AgingType->ItemIndex = 9;
        } else if (agingType == "N/A") {
            int index = ini->ReadBool(section, "DirectGammaIndepRGB", true) ? 0 : 1;
            ComboBox_AgingType->ItemIndex = index;
        }
    }
    CheckBox_AgingMode->Checked = agingFunc;
    if(Edit_AgingManuSelectAddress->Text == "N/A")     //有些tcon(EX:12409)，不用選Manu
        GroupBox_MANU_SEL->Visible = false;
    else
        GroupBox_MANU_SEL->Visible = true;

    //Second gamma byBS+
    bool secondGam = ini->ReadBool(section, "SecondGamma", false);
    if (secondGam) {
        this->Edit_DG2EnableAddress->Text =
                ini->ReadString(section, "DigitalGamma2EnableAddress", "??");
        this->Edit_DG2EnableBit->Text =
                ini->ReadInteger(section, "DigitalGamma2EnableBit", -1);
        this->Edit_DG2LUTAddress->Text =
                ini->ReadString(section, "DigitalGammaLUT2Address", "??");
        this->Edit_GammaTest2EnableAddress->Text =
                ini->ReadString(section, "Gamma2TestEnableAddress", "??");
        this->Edit_GammaTest2EnableBit->Text =
                ini->ReadInteger(section, "Gamma2TestEnableBit", -1);
        this->Edit_DirectGamma2Address->Text =
                ini->ReadString(section, "DirectGamma2Address", "??");
        this->Edit_FRC2EnableAddress->Text =
                ini->ReadString(section, "FRCE2nableAddress", "??");
        this->Edit_FRC2EnableBit->Text =
                ini->ReadInteger(section, "FRC2EnableBit", -1);
    }
    CheckBox_SecondGamma->Checked = secondGam;

    this->Edit_FRCEnableAddress->Text = ini->ReadString(section, "FRCEnableAddress", "??");
    this->Edit_FRCEnableBit->Text = ini->ReadInteger(section, "FRCEnableBit", -1);
    this->Edit_DGEnableAddress->Text = ini->ReadString(section, "DigitalGammaEnableAddress", "??");
    this->Edit_DGEnableBit->Text = ini->ReadInteger(section, "DigitalGammaEnableBit", -1);
    this->Edit_DGLUTAddress->Text = ini->ReadString(section, "DigitalGammaLUTAddress", "??");
    String lutType = ini->ReadString(section, "DigitalGammaLUTType", "N/A");
    if (lutType == "10bit") {
        ComboBox_DGLUTType->ItemIndex = 0;
        RadioButton_Lut10->Checked = true;
    } else if (lutType == "12bitType1") {
        ComboBox_DGLUTType->ItemIndex = 1;
        RadioButton_Lut12->Checked = true;
    } else if (lutType == "12bitType2") {
        ComboBox_DGLUTType->ItemIndex = 2;
        RadioButton_Lut12->Checked = true;
    }

    //Second Gamma byBS+
    bool secondGamma = ini->ReadBool(section, "SecondGamma", false);
    if (secondGamma) {
        GroupBox_SecondGamma->Visible = true;
        this->Edit_DG2EnableAddress->Text =
            ini->ReadString(section, "DigitalGamma2EnableAddress", "??");
        this->Edit_DG2EnableBit->Text =
            ini->ReadInteger(section, "DigitalGamma2EnableBit", -1);
        this->Edit_DG2LUTAddress->Text =
            ini->ReadString(section, "DigitalGammaLUT2Address", "??");
        this->Edit_GammaTest2EnableAddress->Text =
            ini->ReadString(section, "Gamma2TestEnableAddress", "??");
        this->Edit_GammaTest2EnableBit->Text =
            ini->ReadInteger(section, "Gamma2TestEnableBit", -1);
        this->Edit_DirectGamma2Address->Text =
            ini->ReadString(section, "DirectGamma2Address", -1);
        this->Edit_FRC2EnableAddress->Text =
            ini->ReadString(section, "FRCE2nableAddress", "??");
        this->Edit_FRC2EnableBit->Text =
            ini->ReadInteger(section, "FRC2EnableBit", -1);
    }
    CheckBox_SecondGamma->Checked = secondGamma;


    //PG mode byBS+ 20140505
    bool pgMode = ini->ReadBool(section, "PGMode", false);
    if (pgMode) {
        GroupBox_PGmode->Visible = true;

        this->Edit_PGEnableAddress->Text =
            ini->ReadString(section, "PGEnableAddress", "??");
        this->Edit_PGEnableBit->Text =
            ini->ReadInteger(section, "PGEnableBit", -1);
        this->Edit_PGModeAddress->Text =
            ini->ReadString(section, "PGModeAddress", "??");
        this->Edit_PGModeStartBit->Text =
            ini->ReadString(section, "PGModeStartBit", -1);
        this->Edit_PGModeEndBit->Text =
            ini->ReadInteger(section, "PGModeEndBit", -1);

        this->Edit_PGPatternMSBAddress->Text =
            ini->ReadString(section, "PGPatternMSBAddress", "??");
        this->Edit_PGPatternMSBStartBit->Text =
            ini->ReadString(section, "PGPatternMSBStartBit", -1);
        this->Edit_PGPatternMSBEndBit->Text =
            ini->ReadInteger(section, "PGPatternMSBEndBit", -1);
        this->Edit_PGPatternLSBAddress->Text =
            ini->ReadString(section, "PGPatternLSBAddress", "??");
        this->Edit_PGPatternLSBStartBit->Text =
            ini->ReadString(section, "PGPatternLSBStartBit", -1);
        this->Edit_PGPatternLSBEndBit->Text =
            ini->ReadString(section, "PGPatternlSBEndBit", -1);

        this->Edit_PGHblkMSBAddress->Text =
            ini->ReadString(section, "PGHblkMSBAddress", "??");
        this->Edit_PGHblkMSBStartBit->Text =
            ini->ReadString(section, "PGHblkMSBStartBit", -1);
        this->Edit_PGHblkMSBEndBit->Text =
            ini->ReadString(section, "PGHblkMSBEndBit", -1);
        this->Edit_PGHblkLSBAddress->Text =
            ini->ReadString(section, "PGHblkLSBAddress", "??");
        this->Edit_PGHblkLSBStartBit->Text =
            ini->ReadString(section, "PGHblkLSBStartBit", -1);
        this->Edit_PGHblkLSBEndBit->Text =
            ini->ReadString(section, "PGHblkLSBEndBit", -1);
        this->Edit_PGHblkValue->Text =
            ini->ReadString(section, "PGHblkValue", -1);

        this->Edit_PGVblkMSBAddress->Text =
            ini->ReadString(section, "PGVblkMSBAddress", "??");
        this->Edit_PGVblkMSBStartBit->Text =
            ini->ReadString(section, "PGVblkMSBStartBit", -1);
        this->Edit_PGVblkMSBEndBit->Text =
            ini->ReadString(section, "PGVblkMSBEndBit", -1);
        this->Edit_PGVblkLSBAddress->Text =
            ini->ReadString(section, "PGVblkLSBAddress", "??");
        this->Edit_PGVblkLSBStartBit->Text =
            ini->ReadString(section, "PGVblkLSBStartBit", -1);
        this->Edit_PGVblkLSBEndBit->Text =
            ini->ReadString(section, "PGVblkLSBEndBit", -1);
        this->Edit_PGVblkValue->Text =
            ini->ReadString(section, "PGVblkValue", -1);
    }
    CheckBox_PGMode->Checked = pgMode;

    //AG Timing Setting byBS+ 20140610
    bool agTiming = ini->ReadBool(section, "AGTiming", false);
    ComboBox_AGFrameRate->ItemIndex = -1; //初始化 (防呆)
    if(agTiming){
        TabSheet_AGTiming->TabVisible = true;    //開啟 Aging timing 設定
        GroupBox_AG_FRM_RATE->Visible = true;
        CheckBox_AGtiming->Checked = true;       //用來決定是否要設定timing register

        String agFrameRate = ini->ReadString(section, "AGFrameRate", "N/A");
        if (agFrameRate == "60Hz") {
            ComboBox_AGFrameRate->ItemIndex = 0;
        } else if (agFrameRate == "120Hz") {
            ComboBox_AGFrameRate->ItemIndex = 1;
        } else if (agFrameRate == "240Hz") {
            ComboBox_AGFrameRate->ItemIndex = 2;
        } else if (agFrameRate == "480Hz") {
            ComboBox_AGFrameRate->ItemIndex = 3;
        }
        this->Edit_AGFrameRateAddress->Text =
            ini->ReadString(section, "AGFrameRateAddress", "??");
        this->Edit_AGFrameRateStartBit->Text =
            ini->ReadInteger(section, "AGFrameRateStartBit", -1);
        this->Edit_AGFrameRateEndBit->Text =
            ini->ReadInteger(section, "AGFrameRateEndBit", -1);

        this->Edit_mpllModeAddress->Text =
            ini->ReadString(section, "AGmpllModeAddress", "??");
        this->Edit_mpllModeStartBit->Text =
            ini->ReadString(section, "AGmpllModeStartBit", -1);
        this->Edit_mpllModeEndBit->Text =
            ini->ReadString(section, "AGmpllModeEndBit", -1);
        this->Edit_mpllModeValue->Text =
            ini->ReadString(section, "AGmpllModeValue", -1);

        this->Edit_mpllNMSBAddress->Text =
            ini->ReadString(section, "AGmpllNMSBAddress", "??");
        this->Edit_mpllNMSBStartBit->Text =
            ini->ReadString(section, "AGmpllNMSBStartBit", -1);
        this->Edit_mpllNMSBEndBit->Text =
            ini->ReadString(section, "AGmpllNMSBEndBit", -1);
        this->Edit_mpllNLSBAddress->Text =
            ini->ReadString(section, "AGmpllNLSBAddress", "??");
        this->Edit_mpllNLSBStartBit->Text =
            ini->ReadString(section, "AGmpllNLSBStartBit", -1);
        this->Edit_mpllNLSBEndBit->Text =
            ini->ReadString(section, "AGmpllNLSBEndBit", -1);
        this->Edit_mpllNValue->Text =
            ini->ReadString(section, "AGmpllNValue", -1);

        this->Edit_mpllFMSBAddress->Text =
            ini->ReadString(section, "AGmpllFMSBAddress", "??");
        this->Edit_mpllFMSBStartBit->Text =
            ini->ReadString(section, "AGmpllFMSBStartBit", -1);
        this->Edit_mpllFMSBEndBit->Text =
            ini->ReadString(section, "AGmpllFMSBEndBit", -1);
        this->Edit_mpllFLSBAddress->Text =
            ini->ReadString(section, "AGmpllFLSBAddress", "??");
        this->Edit_mpllFLSBStartBit->Text =
            ini->ReadString(section, "AGmpllFLSBStartBit", -1);
        this->Edit_mpllFLSBEndBit->Text =
            ini->ReadString(section, "AGmpllFLSBEndBit", -1);
        this->Edit_mpllFValue->Text =
            ini->ReadString(section, "AGmpllFValue", -1);

        this->Edit_mpllMAddress->Text =
            ini->ReadString(section, "AGmpllMAddress", "??");
        this->Edit_mpllMStartBit->Text =
            ini->ReadString(section, "AGmpllMStartBit", -1);
        this->Edit_mpllMEndBit->Text =
            ini->ReadString(section, "AGmpllMEndBit", -1);
        this->Edit_mpllMValue->Text =
            ini->ReadString(section, "AGmpllMValue", -1);

        this->Edit_AGHblkMSBAddress->Text =
            ini->ReadString(section, "AGHblkMSBAddress", "??");
        this->Edit_AGHblkMSBStartBit->Text =
            ini->ReadString(section, "AGHblkMSBStartBit", -1);
        this->Edit_AGHblkMSBEndBit->Text =
            ini->ReadString(section, "AGHblkMSBEndBit", -1);
        this->Edit_AGHblkLSBAddress->Text =
            ini->ReadString(section, "AGHblkLSBAddress", "??");
        this->Edit_AGHblkLSBStartBit->Text =
            ini->ReadString(section, "AGHblkLSBStartBit", -1);
        this->Edit_AGHblkLSBEndBit->Text =
            ini->ReadString(section, "AGHblkLSBEndBit", -1);
        this->Edit_AGHblkValue->Text =
            ini->ReadString(section, "AGHblkValue", -1);

        this->Edit_AGVblk1MSBAddress->Text =
            ini->ReadString(section, "AGVblk1MSBAddress", "??");
        this->Edit_AGVblk1MSBStartBit->Text =
            ini->ReadString(section, "AGVblk1MSBStartBit", -1);
        this->Edit_AGVblk1MSBEndBit->Text =
            ini->ReadString(section, "AGVblk1MSBEndBit", -1);
        this->Edit_AGVblk1LSBAddress->Text =
            ini->ReadString(section, "AGVblk1LSBAddress", "??");
        this->Edit_AGVblk1LSBStartBit->Text =
            ini->ReadString(section, "AGVblk1LSBStartBit", -1);
        this->Edit_AGVblk1LSBEndBit->Text =
            ini->ReadString(section, "AGVblk1LSBEndBit", -1);
        this->Edit_AGVblk1Value->Text =
            ini->ReadString(section, "AGVblk1Value", -1);

        this->Edit_AGVblk2MSBAddress->Text =
            ini->ReadString(section, "AGVblk2MSBAddress", "??");
        this->Edit_AGVblk2MSBStartBit->Text =
            ini->ReadString(section, "AGVblk2MSBStartBit", -1);
        this->Edit_AGVblk2MSBEndBit->Text =
            ini->ReadString(section, "AGVblk2MSBEndBit", -1);
        this->Edit_AGVblk2LSBAddress->Text =
            ini->ReadString(section, "AGVblk2LSBAddress", "??");
        this->Edit_AGVblk2LSBStartBit->Text =
            ini->ReadString(section, "AGVblk2LSBStartBit", -1);
        this->Edit_AGVblk2LSBEndBit->Text =
            ini->ReadString(section, "AGVblk2LSBEndBit", -1);
        this->Edit_AGVblk2Value->Text =
            ini->ReadString(section, "AGVblk2Value", -1);

    } else {
        TabSheet_AGTiming->TabVisible = false;        //關閉 Aging timing 設定
        GroupBox_AG_FRM_RATE->Visible = false;
        CheckBox_AGtiming->Checked = false;
    }



    /*int lut = ini->ReadInteger(section, "DigitalGammaLUTType", 10);
    this->ComboBox_DGLUTType->Text = lut;
    switch (lut) {
    case 10:
	RadioButton_Lut10->Checked = true;
	break;
    case 12:
	RadioButton_Lut12->Checked = true;
	break;
    }*/

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

	ini->WriteString(CUSTOM, "FRCEnableAddress", this->Edit_FRCEnableAddress->Text);
	ini->WriteInteger(CUSTOM, "FRCEnableBit", this->Edit_FRCEnableBit->Text.ToInt());
	ini->WriteString(CUSTOM, "DigitalGammaEnableAddress", this->Edit_DGEnableAddress->Text);
	ini->WriteInteger(CUSTOM, "DigitalGammaEnableBit", this->Edit_DGEnableBit->Text.ToInt());
	ini->WriteString(CUSTOM, "DigitalGammaLUTAddress", this->Edit_DGLUTAddress->Text);
	ini->WriteString(CUSTOM, "DigitalGammaLUTType", this->ComboBox_DGLUTType->Text);

	bool directGamma = CheckBox_DirectGamma->Checked;
	//CheckBox_GammaTest->Checked = gammaTest;
	//bool gammaTest = true;
	ini->WriteBool(CUSTOM, "DirectGammaFunc", directGamma);
	if (directGamma) {
	    ini->WriteString(CUSTOM, "GammaTestEnableAddress",
			     this->Edit_GammaTestEnableAddress->Text);
	    ini->WriteInteger(CUSTOM, "GammaTestEnableBit",
			      this->Edit_GammaTestEnableBit->Text.ToInt());
	    ini->WriteString(CUSTOM, "DirectGammaAddress", this->Edit_DirectGammaAddress->Text);
	    ini->WriteString(CUSTOM, "DirectGammaType", this->ComboBox_DirectGammaType->Text);

	    bool hideEN = CheckBox_HideEN->Checked;
	    ini->WriteBool(CUSTOM, "HideFunc", hideEN);
	    if (hideEN) {

		ini->WriteString("CUSTOM", "HideEnableAddress", this->Edit_HideEnableAddress->Text);
		ini->WriteInteger("CUSTOM", "HideEnableBit",
				  this->Edit_HideEnableBit->Text.ToInt());
	    }

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
    int cardIndex = ini->ReadInteger("I2C", "Card", 0);
    switch (cardIndex) {
    case 0:
	this->RadioButton_AUO_USB->Checked = true;
	break;
    case 1:
	this->RadioButton_LPTLarge->Checked = true;
	break;
    case 2:
	this->RadioButton_LPTSmall->Checked = true;
	break;
    case 3:
	this->RadioButton_DoDoBird_USB->Checked = true;
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
    cardIndex += this->RadioButton_DoDoBird_USB->Checked ? 3 : 0;
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
	StatusBar1->Panels->Items[1]->Text = "CA-210 Connected";

	bptr < cms::measure::meter::CA210 > ca210 = getCA210();
	if (null != ca210) {
	    bptr < ca210api::CA210API > ca210api = ca210->getCA210API();
	    //取出原先的ch
	    long ch = ca210api->getChannelNO();
	    Edit_SourceCH->Text = ch;
	    GroupBox_CHSetting->Enabled = true;
	}
	initAnalyzer();


	if (connectCA210ByThread) {
	    stopProgress(MainForm->ProgressBar1);
	    setAllFunctionOn(true);
	    ca210Thread->Terminate();
	    delete ca210Thread;
	    ca210Thread = null;
	}

    }
    catch(EOleException & ex) {
	if (connectCA210ByThread) {
	    stopProgress(MainForm->ProgressBar1);
	    //MainForm->PageControl1->Enabled = true;
	    //MainForm->MainMenu1->Enabled = true;
	}

	ShowMessage
	    ("CA210 cannot be linked or unsupported version of CA - SDK(CA - SDK v4 .10 up needed).");
	//this->Close();

    }
};

int TMainForm::getAverageTimes()
{
    return Edit_AverageTimes->Text.ToInt();
};

//---------------------------------------------------------------------------
bptr < cms::measure::IntensityAnalyzerIF > TMainForm::initAnalyzer()
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
	analyzer = ma;
    }
    return analyzer;
}

bptr < cms::measure::MaxMatrixIntensityAnalyzer > TMainForm::getSecondAnalyzerFromProperty()
{
    return secondWhiteAnalyzer;
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
	   targetid = targetid.empty()? string(" ") : targetid;
	   string_ptr id(new string(targetid));
	   //設定在ca210
	   ca210Analyzer->setChannel(channel, id); */

    }
};

//---------------------------------------------------------------------------
/*
  dprecated
*/
void TMainForm::setAnalyzerToSourceChannel()
{
    using namespace std;
    if (true == linkCA210) {
	if (null == ca210Analyzer) {
	    throw java::lang::IllegalStateException("call getAnalyzer()first !");
	}
	//撈出channel no和id
	int channel = this->Edit_SourceCH->Text.ToInt();
	//this->Edit_SourceCH->Text + this->Edit_SourceCH->Text;
	string_ptr id(new string(" "));
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
    using namespace cms::lcd;
    using namespace Indep;
    using namespace Dep;

    meter = bptr < Meter > (new DGLutFileMeter(dglutFile));
    mm = bptr < MeterMeasurement > (new MeterMeasurement(meter, false));


    fetcher = bptr < ComponentFetcher > ((ComponentFetcher *) null);

    bptr < DGLutProperty > property = dglutFile->getProperty();
    if (null != property) {
	//若有property則為新版
	//if (!measurePatchVectorAvailable) {
	//=====================================================================
	// 設定target analyzer
	//=====================================================================
	xyY_ptr targetwxyY = property->getTargetReferenceColor(Channel::W);
	if (null != targetwxyY) {
	    xyY_ptr rxyY = property->getTargetReferenceColor(Channel::R);
	    xyY_ptr gxyY = property->getTargetReferenceColor(Channel::G);
	    xyY_ptr bxyY = property->getTargetReferenceColor(Channel::B);

	    bptr < MaxMatrixIntensityAnalyzer > matrixAnalyzer =
		MaxMatrixIntensityAnalyzer::getReadyAnalyzer(mm, rxyY->toXYZ(), gxyY->toXYZ(),
							     bxyY->toXYZ(), targetwxyY->toXYZ());

	    string_ptr comment = property->getProperty("reference white comment");
	    if (null != comment) {
		matrixAnalyzer->setReferenceColorComment(*comment);
	    }
	    RGB_ptr rgb = property->getTargetReferenceRGB();
	    matrixAnalyzer->setReferenceRGB(rgb);
	    analyzer = matrixAnalyzer;
	}
	//=====================================================================

	//=====================================================================
	// 設定2nd white analyzer
	//=====================================================================
	xyY_ptr secondxyY = property->getSecondReferenceColor(Channel::W);
	if (null != secondxyY) {
	    xyY_ptr rxyY = property->getSecondReferenceColor(Channel::R);
	    xyY_ptr gxyY = property->getSecondReferenceColor(Channel::G);
	    xyY_ptr bxyY = property->getSecondReferenceColor(Channel::B);
	    RGB_ptr refRGB = property->getSecondReferenceRGB();

	    bptr < MaxMatrixIntensityAnalyzer > matrixAnalyzer2 =
		MaxMatrixIntensityAnalyzer::getReadyAnalyzer(rxyY->toXYZ(), gxyY->toXYZ(),
							     bxyY->toXYZ(), secondxyY->toXYZ());
	    matrixAnalyzer2->setReferenceRGB(refRGB);
	    secondWhiteAnalyzer = matrixAnalyzer2;
	}
	//=====================================================================
	//}
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
	bptr < cms::measure::IntensityAnalyzerIF > analyzer = initAnalyzer();
	fetcher = bptr < ComponentFetcher > (new cms::lcd::calibrate::ComponentFetcher(analyzer));
	bool inverseMeasure = CheckBox_InverseMeasure->Checked;
	fetcher->InverseMeasure = inverseMeasure;
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
	    //ShowMessage(" CA210 cannot be linked.");
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
    CCTLUTForm->setBitDepthProcessor(bitDepth);
    MaxMatrixIntensityAnalyzer *ma = dynamic_cast < MaxMatrixIntensityAnalyzer * >(analyzer.get());
    if (null == ma || ma->isInverseMatrixNull()) {
	ShowMessage("Set Target White first.");
	return;
    }

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


void __fastcall TMainForm::RadioButton_TCON_directGammaClick(TObject * Sender)
{
    GroupBox_Pattern->Enabled = false;
    this->Panel_TCON->Visible = true;
    this->TargetWhite1->Enabled = true;
    this->CCTLUT1->Enabled = true;
    this->GammaAdj1->Enabled = true;

    ComboBox_TCONType->Clear();
    readTCONSections();
    ComboBox_TCONTypeChange(this);
    ShowMessage
	("Please Turn On FRC for Measurement when \"Direct Gamma\" is selected!!!\n(當選擇Direct Gamma時, 請打開FRC!!)");
    PageControl1->ActivePageIndex = 1;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_PCClick(TObject * Sender)
{
    GroupBox_Pattern->Enabled = true;
    this->Panel_TCON->Visible = false;
    bitDepth->setDirectGamma(false);
    bitDepth->setAgingMode(false);
    this->TargetWhite1->Enabled = true;
    this->CCTLUT1->Enabled = true;
    this->GammaAdj1->Enabled = true;
    MeasureWindow->setTCONControlOff();
    control.reset();
    Button_Connect->Enabled = true;
    this->StatusBar1->Panels->Items[2]->Text = "T-CON Disconnected";
    ComboBox_TCONType->ItemIndex = -1;
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::Button_ConnectClick(TObject * Sender)
{
    if(ComboBox_TCONType->Text.IsEmpty()) { //防呆
        ShowMessage("Please choose TCON.");
        return;
    }          

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
    if (this->RadioButton_AUO_USB->Checked) {
	USBPower power = (USBPower) RadioGroup_USBPower->ItemIndex;
	USBSpeed speed = (USBSpeed) RadioGroup_Speed->ItemIndex;

        int dataByteNum = (RadioGroup_DataByte->ItemIndex==0) ? 1:2;

	i2c1st = i2cControl::getUSBInstance(first, addressingSize, dataByteNum, power, speed);
	if (dual) {
	    i2c2nd = i2cControl::getUSBInstance(second, addressingSize, dataByteNum, power, speed);
	};
    } else if (this->RadioButton_DoDoBird_USB->Checked) {     //DoDoBird I2C Card  20140604 byBS+
        int dataByteNum = (RadioGroup_DataByte->ItemIndex==0) ? 1:2;

        i2c1st = i2cControl::getDoDoBirdInstance(first, addressingSize, dataByteNum);
	if (dual) {
	    i2c2nd = i2cControl::getDoDoBirdInstance(second, addressingSize, dataByteNum);
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

    AnsiString tconNum = ComboBox_TCONType->Text;   //傳給tconparameter(for顯示在excel中)   20140618 byBS+
    //if (true == connect) {
    if (true) {
	//=====================================================================
	// FRC
	//=====================================================================
	int frcEnableAddress =
	    (Edit_FRCEnableAddress->Text !=
	     "??") ? StrToInt("0x" + Edit_FRCEnableAddress->Text) : -1;
	int frcEnableBit = this->Edit_FRCEnableBit->Text.ToInt();
	//=====================================================================
	//=====================================================================
	// digital gamma
	//=====================================================================
	int dgEnableAddress =
	    (Edit_DGEnableAddress->Text !=
	     "??") ? StrToInt("0x" + Edit_DGEnableAddress->Text) : -1;
	int dgEnableBit = this->Edit_DGEnableBit->Text.ToInt();
	int dgLUTAddress =
	    (Edit_DGLUTAddress->Text !=
	     "??") ? StrToInt("0x" + Edit_DGLUTAddress->Text) : -1;
        int DGLUTTypeIndex = this->ComboBox_DGLUTType->ItemIndex;

	//int dgLUTType = (DGLUTTypeIndex == 1) ? 10 : 12;
        int dgLUTBit = (DGLUTTypeIndex == 1) ? 10 : 12;
        AnsiString dgLUTType = this->ComboBox_DGLUTType->Text;
	//=====================================================================
	//=====================================================================
	// gamma test / Aging mode / Second gamma
	//=====================================================================
	bool directGamma = CheckBox_DirectGamma->Checked;
        bool AgingMode = RadioButton_TCON_aging->Checked;
        bool secondGamma = CheckBox_SecondGamma->Checked;
        bool pgMode = CheckBox_PGMode->Checked;
        //int gammaTestAddress, gammaTestBit, directGammaRGBAddress, index;

	if (directGamma) {
            int gammaTestAddress = StrToInt("0x" + this->Edit_GammaTestEnableAddress->Text);
            int gammaTestBit = this->Edit_GammaTestEnableBit->Text.ToInt();
            int directGammaRGBAddress = StrToInt("0x" + this->Edit_DirectGammaAddress->Text);
            int index = this->ComboBox_DirectGammaType->ItemIndex;

	    const DirectGammaType & directGammaType =
		(0 == index) ? DirectGammaType::IndependentInstance :
		(1 == index) ? DirectGammaType::DependentInstance :
		(2 == index) ? DirectGammaType::TCON62301Instance :
		(3 == index) ? DirectGammaType::TCON1H501Instance :
                (4 == index) ? DirectGammaType::TCON12409Instance :
                (5 == index) ? DirectGammaType::TCON11311Instance :
                (6 == index) ? DirectGammaType::TCON12409AgingInstance :
                (7 == index) ? DirectGammaType::TCON12411AgingInstance :
                (8 == index) ? DirectGammaType::TCON12411Instance :
                (9 == index) ? DirectGammaType::HawkTypeInstance :
                               DirectGammaType::NotAssignInstance;


	    //hide en
	    bool hideEN = CheckBox_HideEN->Checked;
	    if (hideEN) {
		int hideEnableAddress = StrToInt("0x" + Edit_HideEnableAddress->Text);
		int hideEnableBit = this->Edit_HideEnableBit->Text.ToInt();

		parameter =
		    bptr < TCONParameter >
		    (new
		     TCONParameter(tconNum, dgLUTBit == 10 ? MaxValue::Int10Bit : MaxValue::Int12Bit,
				   dgLUTAddress, dgLUTType, dgEnableAddress, dgEnableBit, gammaTestAddress,
				   gammaTestBit, directGammaRGBAddress, directGammaType,
				   frcEnableAddress, frcEnableBit, hideEnableAddress,
				   hideEnableBit));
	    } else {
                if(AgingMode) {    //TCON包括DirectGamma與Aging功能  byBS+
                    int agingAGBSDebugAddress = StrToInt("0x" + Edit_AgingAGBSDebugAddress->Text);
                    int agingAGBSDebugBit = this->Edit_AgingAGBSDebugBit->Text.ToInt();

                    int agingModeSelectAddress = StrToInt("0x" + Edit_AgingModeSelectAddress->Text);
                    int agingModeSelectValue = this->Edit_AgingModeSelectValue->Text.ToInt();
                    int agingModeSelectStartBit = this->Edit_AgingModeSelectStartBit->Text.ToInt();
                    int agingModeSelectEndBit = this->Edit_AgingModeSelectEndBit->Text.ToInt();

                    int agingPatternSelectAddress = StrToInt("0x" + Edit_AgingPatternSelectAddress->Text);
                    int agingPatternSelectValue = this->Edit_AgingPatternSelectValue->Text.ToInt();
                    int agingPatternSelectStartBit = this->Edit_AgingPatternSelectStartBit->Text.ToInt();
                    int agingPatternSelectEndBit = this->Edit_AgingPatternSelectEndBit->Text.ToInt();

                    int agingRasterGrayAddress = StrToInt("0x" + this->Edit_AgingRasterGrayAddress->Text);
                    int aging_index = this->ComboBox_AgingType->ItemIndex;

                    //for 12411/2 (not for 12409)
                    int agingManuSelectAddress;
                    int agingManuSelectBit;
                    if(Edit_AgingManuSelectAddress->Text != "N/A") {
                        agingManuSelectAddress = StrToInt("0x" + Edit_AgingManuSelectAddress->Text);
                        agingManuSelectBit = this->Edit_AgingManuSelectBit->Text.ToInt();
                    }

                    const DirectGammaType & agingModeType =
                        (0 == aging_index) ? DirectGammaType::IndependentInstance :
                        (1 == aging_index) ? DirectGammaType::DependentInstance :
                        (2 == aging_index) ? DirectGammaType::TCON62301Instance :
                        (3 == aging_index) ? DirectGammaType::TCON1H501Instance :
                        (4 == aging_index) ? DirectGammaType::TCON12409Instance :
                        (5 == aging_index) ? DirectGammaType::TCON11311Instance :
                        (6 == aging_index) ? DirectGammaType::TCON12409AgingInstance:
                        (7 == aging_index) ? DirectGammaType::TCON12411AgingInstance:
                        (8 == aging_index) ? DirectGammaType::TCON12411Instance:
                        (9 == aging_index) ? DirectGammaType::HawkTypeInstance:
                                             DirectGammaType::NotAssignInstance;


                    //aging timing setting  20140611 byBS+
                    bool agingTimingControl = CheckBox_AGtiming->Checked;
                    int agingFrameRate = ComboBox_AGFrameRate->ItemIndex;
                    int agingFrameRateAddress = StrToInt("0x" + Edit_AGFrameRateAddress->Text);
                    int agingFrameRateStartBit = this->Edit_AGFrameRateStartBit->Text.ToInt();
                    int agingFrameRateEndBit = this->Edit_AGFrameRateEndBit->Text.ToInt();

                    int agingMpllModeAddress = StrToInt("0x" + Edit_mpllModeAddress->Text);
                    int agingMpllModeStartBit = this->Edit_mpllModeStartBit->Text.ToInt();
                    int agingMpllModeEndBit = this->Edit_mpllModeEndBit->Text.ToInt();
                    int agingMpllModeValue = this->Edit_mpllModeValue->Text.ToInt();

                    int agingMpllNMSBAddress = StrToInt("0x" + Edit_mpllNMSBAddress->Text);
                    int agingMpllNMSBStartBit = this->Edit_mpllNMSBStartBit->Text.ToInt();
                    int agingMpllNMSBEndBit = this->Edit_mpllNMSBEndBit->Text.ToInt();
                    int agingMpllNLSBAddress = StrToInt("0x" + Edit_mpllNLSBAddress->Text);
                    int agingMpllNLSBStartBit = this->Edit_mpllNLSBStartBit->Text.ToInt();
                    int agingMpllNLSBEndBit = this->Edit_mpllNLSBEndBit->Text.ToInt();
                    int agingMpllNValue = this->Edit_mpllNValue->Text.ToInt();

                    int agingMpllFMSBAddress = StrToInt("0x" + Edit_mpllFMSBAddress->Text);
                    int agingMpllFMSBStartBit = this->Edit_mpllFMSBStartBit->Text.ToInt();
                    int agingMpllFMSBEndBit = this->Edit_mpllFMSBEndBit->Text.ToInt();
                    int agingMpllFLSBAddress = StrToInt("0x" + Edit_mpllFLSBAddress->Text);
                    int agingMpllFLSBStartBit = this->Edit_mpllFLSBStartBit->Text.ToInt();
                    int agingMpllFLSBEndBit = this->Edit_mpllFLSBEndBit->Text.ToInt();
                    int agingMpllFValue = this->Edit_mpllFValue->Text.ToInt();

                    int agingMpllMAddress = StrToInt("0x" + Edit_mpllMAddress->Text);
                    int agingMpllMStartBit = this->Edit_mpllMStartBit->Text.ToInt();
                    int agingMpllMEndBit = this->Edit_mpllMEndBit->Text.ToInt();
                    int agingMpllMValue = this->Edit_mpllMValue->Text.ToInt();

                    int agingHblkMSBAddress = StrToInt("0x" + Edit_AGHblkMSBAddress->Text);
                    int agingHblkMSBStartBit = this->Edit_AGHblkMSBStartBit->Text.ToInt();
                    int agingHblkMSBEndBit = this->Edit_AGHblkMSBEndBit->Text.ToInt();
                    int agingHblkLSBAddress = StrToInt("0x" + Edit_AGHblkLSBAddress->Text);
                    int agingHblkLSBStartBit = this->Edit_AGHblkLSBStartBit->Text.ToInt();
                    int agingHblkLSBEndBit = this->Edit_AGHblkLSBEndBit->Text.ToInt();
                    int agingHblkValue = this->Edit_AGHblkValue->Text.ToInt();

                    int agingVblk1MSBAddress = StrToInt("0x" + Edit_AGVblk1MSBAddress->Text);
                    int agingVblk1MSBStartBit = this->Edit_AGVblk1MSBStartBit->Text.ToInt();
                    int agingVblk1MSBEndBit = this->Edit_AGVblk1MSBEndBit->Text.ToInt();
                    int agingVblk1LSBAddress = StrToInt("0x" + Edit_AGVblk1LSBAddress->Text);
                    int agingVblk1LSBStartBit = this->Edit_AGVblk1LSBStartBit->Text.ToInt();
                    int agingVblk1LSBEndBit = this->Edit_AGVblk1LSBEndBit->Text.ToInt();
                    int agingVblk1Value = this->Edit_AGVblk1Value->Text.ToInt();

                    int agingVblk2MSBAddress = StrToInt("0x" + Edit_AGVblk2MSBAddress->Text);
                    int agingVblk2MSBStartBit = this->Edit_AGVblk2MSBStartBit->Text.ToInt();
                    int agingVblk2MSBEndBit = this->Edit_AGVblk2MSBEndBit->Text.ToInt();
                    int agingVblk2LSBAddress = StrToInt("0x" + Edit_AGVblk2LSBAddress->Text);
                    int agingVblk2LSBStartBit = this->Edit_AGVblk2LSBStartBit->Text.ToInt();
                    int agingVblk2LSBEndBit = this->Edit_AGVblk2LSBEndBit->Text.ToInt();
                    int agingVblk2Value = this->Edit_AGVblk2Value->Text.ToInt();


                    if(secondGamma) {  //TCON包括DirectGamma與Aging與secondGamma功能 (EX: 12411)  byBS+
                        int dg2EnableAddress = StrToInt("0x" + Edit_DG2EnableAddress->Text);
                        int dg2EnableBit = this->Edit_DG2EnableBit->Text.ToInt();
                        int dg2LUTAddress = StrToInt("0x" + Edit_DG2LUTAddress->Text);

                        int gammaTest2Address = StrToInt("0x" + this->Edit_GammaTest2EnableAddress->Text);
                        int gammaTest2Bit = this->Edit_GammaTest2EnableBit->Text.ToInt();
                        int directGamma2RGBAddress = StrToInt("0x" + this->Edit_DirectGamma2Address->Text);

                        int frc2EnableAddress =
                            (Edit_FRC2EnableAddress->Text != "??") ? StrToInt("0x" + Edit_FRC2EnableAddress->Text) : -1;
                        int frc2EnableBit = this->Edit_FRC2EnableBit->Text.ToInt();

                        parameter =
		        bptr < TCONParameter >
		        (new TCONParameter(tconNum, dgLUTBit == 10 ? MaxValue::Int10Bit : MaxValue::Int12Bit,
                                           dgLUTAddress, dgLUTType, dgEnableAddress, dgEnableBit,
                                           gammaTestAddress, gammaTestBit,
                                           directGammaRGBAddress, directGammaType,
                                           frcEnableAddress, frcEnableBit,
                                           agingAGBSDebugAddress, agingAGBSDebugBit,
                                           agingModeSelectAddress, agingModeSelectValue,
                                           agingModeSelectStartBit , agingModeSelectEndBit,
                                           agingPatternSelectAddress,
                                           agingPatternSelectValue, agingPatternSelectStartBit,
                                           agingPatternSelectEndBit, agingRasterGrayAddress,
                                           agingModeType,agingManuSelectAddress,agingManuSelectBit,
                                           dg2EnableAddress, dg2EnableBit, dg2LUTAddress,
                                           gammaTest2Address, gammaTest2Bit, directGamma2RGBAddress,
                                           frc2EnableAddress, frc2EnableBit,
                                           agingTimingControl,
                                           agingFrameRate, agingFrameRateAddress, agingFrameRateStartBit, agingFrameRateEndBit,
                                           agingMpllModeAddress, agingMpllModeStartBit, agingMpllModeEndBit, agingMpllModeValue,
                                           agingMpllNMSBAddress, agingMpllNMSBStartBit, agingMpllNMSBEndBit, agingMpllNLSBAddress, agingMpllNLSBStartBit, agingMpllNLSBEndBit,agingMpllNValue,
                                           agingMpllFMSBAddress, agingMpllFMSBStartBit, agingMpllFMSBEndBit, agingMpllFLSBAddress, agingMpllFLSBStartBit, agingMpllFLSBEndBit, agingMpllFValue,
                                           agingMpllMAddress, agingMpllMStartBit, agingMpllMEndBit, agingMpllMValue,
                                           agingHblkMSBAddress, agingHblkMSBStartBit, agingHblkMSBEndBit, agingHblkLSBAddress, agingHblkLSBStartBit, agingHblkLSBEndBit, agingHblkValue,
                                           agingVblk1MSBAddress, agingVblk1MSBStartBit, agingVblk1MSBEndBit, agingVblk1LSBAddress, agingVblk1LSBStartBit, agingVblk1LSBEndBit, agingVblk1Value,
                                           agingVblk2MSBAddress, agingVblk2MSBStartBit, agingVblk2MSBEndBit, agingVblk2LSBAddress, agingVblk2LSBStartBit, agingVblk2LSBEndBit, agingVblk2Value));

                    } else {
                        parameter =
		        bptr < TCONParameter >
		        (new
		         TCONParameter(tconNum, dgLUTBit == 10 ? MaxValue::Int10Bit : MaxValue::Int12Bit,
			   	       dgLUTAddress, dgLUTType, dgEnableAddress, dgEnableBit,
                                       gammaTestAddress, gammaTestBit,
                                       directGammaRGBAddress, directGammaType,
				       frcEnableAddress, frcEnableBit,
                                       agingAGBSDebugAddress, agingAGBSDebugBit,
                                       agingModeSelectAddress, agingModeSelectValue,
                                       agingModeSelectStartBit , agingModeSelectEndBit,
                                       agingPatternSelectAddress,
                                       agingPatternSelectValue, agingPatternSelectStartBit,
                                       agingPatternSelectEndBit, agingRasterGrayAddress,
                                       agingModeType,agingManuSelectAddress,agingManuSelectBit,
                                       agingTimingControl,
                                       agingFrameRate, agingFrameRateAddress, agingFrameRateStartBit, agingFrameRateEndBit,
                                       agingMpllModeAddress, agingMpllModeStartBit, agingMpllModeEndBit, agingMpllModeValue,
                                       agingMpllNMSBAddress, agingMpllNMSBStartBit, agingMpllNMSBEndBit, agingMpllNLSBAddress, agingMpllNLSBStartBit, agingMpllNLSBEndBit,agingMpllNValue,
                                       agingMpllFMSBAddress, agingMpllFMSBStartBit, agingMpllFMSBEndBit, agingMpllFLSBAddress, agingMpllFLSBStartBit, agingMpllFLSBEndBit, agingMpllFValue,
                                       agingMpllMAddress, agingMpllMStartBit, agingMpllMEndBit, agingMpllMValue,
                                       agingHblkMSBAddress, agingHblkMSBStartBit, agingHblkMSBEndBit, agingHblkLSBAddress, agingHblkLSBStartBit, agingHblkLSBEndBit, agingHblkValue,
                                       agingVblk1MSBAddress, agingVblk1MSBStartBit, agingVblk1MSBEndBit, agingVblk1LSBAddress, agingVblk1LSBStartBit, agingVblk1LSBEndBit, agingVblk1Value,
                                       agingVblk2MSBAddress, agingVblk2MSBStartBit, agingVblk2MSBEndBit, agingVblk2LSBAddress, agingVblk2LSBStartBit, agingVblk2LSBEndBit, agingVblk2Value));

                    }
                } else {
	            parameter =
		        bptr < TCONParameter >
		        (new
		         TCONParameter(tconNum, dgLUTBit == 10 ? MaxValue::Int10Bit : MaxValue::Int12Bit,
			   	       dgLUTAddress, dgLUTType, dgEnableAddress, dgEnableBit,
                                       gammaTestAddress, gammaTestBit, directGammaRGBAddress,
                                       directGammaType, frcEnableAddress, frcEnableBit));
                }
	    }
	} else {
            if(pgMode) {
                int pgEnableAddress = StrToInt("0x" + Edit_PGEnableAddress->Text);
                int pgEnableBit = Edit_PGEnableBit->Text.ToInt();

                int pgModeAddress = StrToInt("0x" + Edit_PGModeAddress->Text);
                int pgModeStartBit = Edit_PGModeStartBit->Text.ToInt();
                int pgModeEndBit = Edit_PGModeEndBit->Text.ToInt();

                int pgPatternMSBAddress = StrToInt("0x" + Edit_PGPatternMSBAddress->Text);
                int pgPatternMSBStartBit = Edit_PGPatternMSBStartBit->Text.ToInt();
                int pgPatternMSBEndBit = Edit_PGPatternMSBEndBit->Text.ToInt();
                int pgPatternLSBAddress = StrToInt("0x" + Edit_PGPatternLSBAddress->Text);
                int pgPatternLSBStartBit = Edit_PGPatternLSBStartBit->Text.ToInt();
                int pgPatternLSBEndBit = Edit_PGPatternLSBEndBit->Text.ToInt();

                int pgHblkMSBAddress = StrToInt("0x" + Edit_PGHblkMSBAddress->Text);
                int pgHblkMSBStartBit = Edit_PGHblkMSBStartBit->Text.ToInt();
                int pgHblkMSBEndBit = Edit_PGHblkMSBEndBit->Text.ToInt();
                int pgHblkLSBAddress = StrToInt("0x" + Edit_PGHblkLSBAddress->Text);
                int pgHblkLSBStartBit = Edit_PGHblkLSBStartBit->Text.ToInt();
                int pgHblkLSBEndBit = Edit_PGHblkLSBEndBit->Text.ToInt();
                int pgHblkValue = Edit_PGHblkValue->Text.ToInt();

                int pgVblkMSBAddress = StrToInt("0x" + Edit_PGVblkMSBAddress->Text);
                int pgVblkMSBStartBit = Edit_PGVblkMSBStartBit->Text.ToInt();
                int pgVblkMSBEndBit = Edit_PGVblkMSBEndBit->Text.ToInt();
                int pgVblkLSBAddress = StrToInt("0x" + Edit_PGVblkLSBAddress->Text);
                int pgVblkLSBStartBit = Edit_PGVblkLSBStartBit->Text.ToInt();
                int pgVblkLSBEndBit = Edit_PGVblkLSBEndBit->Text.ToInt();
                int pgVblkValue = Edit_PGVblkValue->Text.ToInt();

                parameter =
		        bptr < TCONParameter >
		        (new
		          TCONParameter(tconNum, frcEnableAddress, frcEnableBit,
                                        pgEnableAddress, pgEnableBit,
                                        pgModeAddress, pgModeStartBit, pgModeEndBit,
                                        pgPatternMSBAddress, pgPatternMSBStartBit, pgPatternMSBEndBit,
                                        pgPatternLSBAddress, pgPatternLSBStartBit, pgPatternLSBEndBit,
                                        pgHblkMSBAddress, pgHblkMSBStartBit, pgHblkMSBEndBit,
                                        pgHblkLSBAddress, pgHblkLSBStartBit, pgHblkLSBEndBit,
                                        pgHblkValue,
                                        pgVblkMSBAddress, pgVblkMSBStartBit, pgVblkMSBEndBit,
                                        pgVblkLSBAddress, pgVblkLSBStartBit, pgVblkLSBEndBit,
                                        pgVblkValue));
            } else if(AgingMode) {

                  int gammaTestAddress = StrToInt("0x" + this->Edit_GammaTestEnableAddress->Text);
                  int gammaTestBit = this->Edit_GammaTestEnableBit->Text.ToInt();
                  int directGammaRGBAddress = StrToInt("0x" + this->Edit_DirectGammaAddress->Text);
                  int index = this->ComboBox_DirectGammaType->ItemIndex;

                  const DirectGammaType & directGammaType =
                      (0 == index) ? DirectGammaType::IndependentInstance :
                      (1 == index) ? DirectGammaType::DependentInstance :
                      (2 == index) ? DirectGammaType::TCON62301Instance :
                      (3 == index) ? DirectGammaType::TCON1H501Instance :
                      (4 == index) ? DirectGammaType::TCON12409Instance :
                      (5 == index) ? DirectGammaType::TCON11311Instance :
                      (6 == index) ? DirectGammaType::TCON12409AgingInstance :
                      (7 == index) ? DirectGammaType::TCON12411AgingInstance :
                      (8 == index) ? DirectGammaType::TCON12411Instance :
                      (9 == index) ? DirectGammaType::HawkTypeInstance :
                                     DirectGammaType::NotAssignInstance;



                    //TCON包括DirectGamma與Aging功能  byBS+
                    int agingAGBSDebugAddress = StrToInt("0x" + Edit_AgingAGBSDebugAddress->Text);
                    int agingAGBSDebugBit = this->Edit_AgingAGBSDebugBit->Text.ToInt();

                    int agingModeSelectAddress = StrToInt("0x" + Edit_AgingModeSelectAddress->Text);
                    int agingModeSelectValue = this->Edit_AgingModeSelectValue->Text.ToInt();
                    int agingModeSelectStartBit = this->Edit_AgingModeSelectStartBit->Text.ToInt();
                    int agingModeSelectEndBit = this->Edit_AgingModeSelectEndBit->Text.ToInt();

                    int agingPatternSelectAddress = StrToInt("0x" + Edit_AgingPatternSelectAddress->Text);
                    int agingPatternSelectValue = this->Edit_AgingPatternSelectValue->Text.ToInt();
                    int agingPatternSelectStartBit = this->Edit_AgingPatternSelectStartBit->Text.ToInt();
                    int agingPatternSelectEndBit = this->Edit_AgingPatternSelectEndBit->Text.ToInt();

                    int agingRasterGrayAddress = StrToInt("0x" + this->Edit_AgingRasterGrayAddress->Text);
                    int aging_index = this->ComboBox_AgingType->ItemIndex;

                    //for 12411/2 (not for 12409)
                    int agingManuSelectAddress;
                    int agingManuSelectBit;
                    if(Edit_AgingManuSelectAddress->Text != "N/A") {
                        agingManuSelectAddress = StrToInt("0x" + Edit_AgingManuSelectAddress->Text);
                        agingManuSelectBit = this->Edit_AgingManuSelectBit->Text.ToInt();
                    }

                    const DirectGammaType & agingModeType =
                        (0 == aging_index) ? DirectGammaType::IndependentInstance :
                        (1 == aging_index) ? DirectGammaType::DependentInstance :
                        (2 == aging_index) ? DirectGammaType::TCON62301Instance :
                        (3 == aging_index) ? DirectGammaType::TCON1H501Instance :
                        (4 == aging_index) ? DirectGammaType::TCON12409Instance :
                        (5 == aging_index) ? DirectGammaType::TCON11311Instance :
                        (6 == aging_index) ? DirectGammaType::TCON12409AgingInstance:
                        (7 == aging_index) ? DirectGammaType::TCON12411AgingInstance:
                        (8 == aging_index) ? DirectGammaType::TCON12411Instance:
                        (9 == aging_index) ? DirectGammaType::HawkTypeInstance:
                                             DirectGammaType::NotAssignInstance;


                    //aging timing setting  20140611 byBS+
                    bool agingTimingControl = CheckBox_AGtiming->Checked;
                    int agingFrameRate = ComboBox_AGFrameRate->ItemIndex;
                    int agingFrameRateAddress = StrToInt("0x" + Edit_AGFrameRateAddress->Text);
                    int agingFrameRateStartBit = this->Edit_AGFrameRateStartBit->Text.ToInt();
                    int agingFrameRateEndBit = this->Edit_AGFrameRateEndBit->Text.ToInt();

                    int agingMpllModeAddress = StrToInt("0x" + Edit_mpllModeAddress->Text);
                    int agingMpllModeStartBit = this->Edit_mpllModeStartBit->Text.ToInt();
                    int agingMpllModeEndBit = this->Edit_mpllModeEndBit->Text.ToInt();
                    int agingMpllModeValue = this->Edit_mpllModeValue->Text.ToInt();

                    int agingMpllNMSBAddress = StrToInt("0x" + Edit_mpllNMSBAddress->Text);
                    int agingMpllNMSBStartBit = this->Edit_mpllNMSBStartBit->Text.ToInt();
                    int agingMpllNMSBEndBit = this->Edit_mpllNMSBEndBit->Text.ToInt();
                    int agingMpllNLSBAddress = StrToInt("0x" + Edit_mpllNLSBAddress->Text);
                    int agingMpllNLSBStartBit = this->Edit_mpllNLSBStartBit->Text.ToInt();
                    int agingMpllNLSBEndBit = this->Edit_mpllNLSBEndBit->Text.ToInt();
                    int agingMpllNValue = this->Edit_mpllNValue->Text.ToInt();

                    int agingMpllFMSBAddress = StrToInt("0x" + Edit_mpllFMSBAddress->Text);
                    int agingMpllFMSBStartBit = this->Edit_mpllFMSBStartBit->Text.ToInt();
                    int agingMpllFMSBEndBit = this->Edit_mpllFMSBEndBit->Text.ToInt();
                    int agingMpllFLSBAddress = StrToInt("0x" + Edit_mpllFLSBAddress->Text);
                    int agingMpllFLSBStartBit = this->Edit_mpllFLSBStartBit->Text.ToInt();
                    int agingMpllFLSBEndBit = this->Edit_mpllFLSBEndBit->Text.ToInt();
                    int agingMpllFValue = this->Edit_mpllFValue->Text.ToInt();

                    int agingMpllMAddress = StrToInt("0x" + Edit_mpllMAddress->Text);
                    int agingMpllMStartBit = this->Edit_mpllMStartBit->Text.ToInt();
                    int agingMpllMEndBit = this->Edit_mpllMEndBit->Text.ToInt();
                    int agingMpllMValue = this->Edit_mpllMValue->Text.ToInt();

                    int agingHblkMSBAddress = StrToInt("0x" + Edit_AGHblkMSBAddress->Text);
                    int agingHblkMSBStartBit = this->Edit_AGHblkMSBStartBit->Text.ToInt();
                    int agingHblkMSBEndBit = this->Edit_AGHblkMSBEndBit->Text.ToInt();
                    int agingHblkLSBAddress = StrToInt("0x" + Edit_AGHblkLSBAddress->Text);
                    int agingHblkLSBStartBit = this->Edit_AGHblkLSBStartBit->Text.ToInt();
                    int agingHblkLSBEndBit = this->Edit_AGHblkLSBEndBit->Text.ToInt();
                    int agingHblkValue = this->Edit_AGHblkValue->Text.ToInt();

                    int agingVblk1MSBAddress = StrToInt("0x" + Edit_AGVblk1MSBAddress->Text);
                    int agingVblk1MSBStartBit = this->Edit_AGVblk1MSBStartBit->Text.ToInt();
                    int agingVblk1MSBEndBit = this->Edit_AGVblk1MSBEndBit->Text.ToInt();
                    int agingVblk1LSBAddress = StrToInt("0x" + Edit_AGVblk1LSBAddress->Text);
                    int agingVblk1LSBStartBit = this->Edit_AGVblk1LSBStartBit->Text.ToInt();
                    int agingVblk1LSBEndBit = this->Edit_AGVblk1LSBEndBit->Text.ToInt();
                    int agingVblk1Value = this->Edit_AGVblk1Value->Text.ToInt();

                    int agingVblk2MSBAddress = StrToInt("0x" + Edit_AGVblk2MSBAddress->Text);
                    int agingVblk2MSBStartBit = this->Edit_AGVblk2MSBStartBit->Text.ToInt();
                    int agingVblk2MSBEndBit = this->Edit_AGVblk2MSBEndBit->Text.ToInt();
                    int agingVblk2LSBAddress = StrToInt("0x" + Edit_AGVblk2LSBAddress->Text);
                    int agingVblk2LSBStartBit = this->Edit_AGVblk2LSBStartBit->Text.ToInt();
                    int agingVblk2LSBEndBit = this->Edit_AGVblk2LSBEndBit->Text.ToInt();
                    int agingVblk2Value = this->Edit_AGVblk2Value->Text.ToInt();



                        parameter =
		        bptr < TCONParameter >
		        (new
		         TCONParameter(tconNum, dgLUTBit == 10 ? MaxValue::Int10Bit : MaxValue::Int12Bit,
			   	       dgLUTAddress, dgLUTType, dgEnableAddress, dgEnableBit,
                                       gammaTestAddress, gammaTestBit,
                                       directGammaRGBAddress, directGammaType,
				       frcEnableAddress, frcEnableBit,
                                       agingAGBSDebugAddress, agingAGBSDebugBit,
                                       agingModeSelectAddress, agingModeSelectValue,
                                       agingModeSelectStartBit , agingModeSelectEndBit,
                                       agingPatternSelectAddress,
                                       agingPatternSelectValue, agingPatternSelectStartBit,
                                       agingPatternSelectEndBit, agingRasterGrayAddress,
                                       agingModeType,agingManuSelectAddress,agingManuSelectBit,
                                       agingTimingControl,
                                       agingFrameRate, agingFrameRateAddress, agingFrameRateStartBit, agingFrameRateEndBit,
                                       agingMpllModeAddress, agingMpllModeStartBit, agingMpllModeEndBit, agingMpllModeValue,
                                       agingMpllNMSBAddress, agingMpllNMSBStartBit, agingMpllNMSBEndBit, agingMpllNLSBAddress, agingMpllNLSBStartBit, agingMpllNLSBEndBit,agingMpllNValue,
                                       agingMpllFMSBAddress, agingMpllFMSBStartBit, agingMpllFMSBEndBit, agingMpllFLSBAddress, agingMpllFLSBStartBit, agingMpllFLSBEndBit, agingMpllFValue,
                                       agingMpllMAddress, agingMpllMStartBit, agingMpllMEndBit, agingMpllMValue,
                                       agingHblkMSBAddress, agingHblkMSBStartBit, agingHblkMSBEndBit, agingHblkLSBAddress, agingHblkLSBStartBit, agingHblkLSBEndBit, agingHblkValue,
                                       agingVblk1MSBAddress, agingVblk1MSBStartBit, agingVblk1MSBEndBit, agingVblk1LSBAddress, agingVblk1LSBStartBit, agingVblk1LSBEndBit, agingVblk1Value,
                                       agingVblk2MSBAddress, agingVblk2MSBStartBit, agingVblk2MSBEndBit, agingVblk2LSBAddress, agingVblk2LSBStartBit, agingVblk2LSBEndBit, agingVblk2Value));

            } else {
	        parameter =
		        bptr < TCONParameter >
		        (new
		        TCONParameter(tconNum, dgLUTBit == 10 ? MaxValue::Int10Bit : MaxValue::Int12Bit,
                                      dgLUTAddress, dgLUTType, dgEnableAddress, dgEnableBit, frcEnableAddress,
                                      frcEnableBit));
            }
	}


	if (!dual) {
	    control = bptr < TCONControl > (new TCONControl(parameter, i2c1st));
	} else {
	    control = bptr < TCONControl > (new TCONControl(parameter, i2c1st, i2c2nd));
	}
	this->Button_Connect->Enabled = false;
	this->StatusBar1->Panels->Items[2]->Text = "T-CON Connected";
	if (!this->RadioButton_PCTCON_NB->Checked) {
	    //不是TCON+NB的話

	    if (this->RadioButton_PCTCON_TV->Checked) {
		//看是TCON+TV
		this->bitDepth->setDirectGamma(true);
		MeasureWindow->setDGLUTInput(control, bitDepth);
	    } else if(RadioButton_TCON_directGamma->Checked) {
		//TCON (DirectGamma)
		this->bitDepth->setDirectGamma(true);
                this->bitDepth->setAgingMode(false);
		MeasureWindow->setDirectGamma(control, bitDepth);
	    } else if(RadioButton_TCON_aging->Checked) {
                //TCON (Aging)
		this->bitDepth->setAgingMode(true);
                this->bitDepth->setDirectGamma(false);
		MeasureWindow->setAgingMode(control, bitDepth);

            }
	}
    } //end if(connect)

    else {  //純pc
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
    if (!bitDepth->isDirectGamma() && this->Visible) {
	ShowMessage("Recommend using Direct Gamma.");
    }
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
    int waitTimes = this->getInterval();
    this->mm->WaitTimes = waitTimes;
};
void __fastcall TMainForm::Button_I2CTestClick(TObject * Sender)
{

    if (I2CTestForm == null) {
	Application->CreateForm(__classid(TI2CTestForm), &I2CTestForm);
	I2CTestForm->Height = 300;
	I2CTestForm->Width = 230;
    }
    I2CTestForm->RadioButton_LPTLarge->Checked = this->RadioButton_LPTLarge->Checked;
    I2CTestForm->RadioButton_LPTSmall->Checked = this->RadioButton_LPTSmall->Checked;
    I2CTestForm->RadioButton_AUO_USB->Checked = this->RadioButton_AUO_USB->Checked;
    I2CTestForm->RadioButton_DoDoBird_USB->Checked = this->RadioButton_DoDoBird_USB->Checked;
    I2CTestForm->RadioButton_Single->Checked = this->RadioButton_SingleTCON->Checked;
    I2CTestForm->RadioButton_Dual->Checked = this->RadioButton_DualTCON->Checked;
    //I2CTestForm->CheckBox_IndepRGB->Checked = this->CheckBox_GammaTestIndepRGB->Checked;
    I2CTestForm->setBitDepthProcessor(bitDepth);
    //I2CTestForm->ShowModal();

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





void __fastcall TMainForm::FormDestroy(TObject * Sender)
{
    writeSetup();
    writeTCONCustomSetup();
    if (null != ca210) {
	ca210->close();
    }
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::RadioButton_AUO_USBClick(TObject * Sender)
{
    Button_Connect->Enabled = true;
    GroupBox_USBSetting->Visible = true;
    RadioGroup_DataByte->Visible = true;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_LPTLargeClick(TObject * Sender)
{
    Button_Connect->Enabled = true;
    GroupBox_USBSetting->Visible = false;
    RadioGroup_DataByte->Visible = false;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_LPTSmallClick(TObject * Sender)
{
    Button_Connect->Enabled = true;
    GroupBox_USBSetting->Visible = false;
    RadioGroup_DataByte->Visible = false;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_DoDoBird_USBClick(TObject *Sender)
{
    Button_Connect->Enabled = true;
    GroupBox_USBSetting->Visible = false;
    RadioGroup_DataByte->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ComboBox_TCONTypeChange(TObject * Sender)
{
    using namespace cms::util;
    String section = this->ComboBox_TCONType->Text;
    if (section != null && section.Length() != 0 && section != "Custom") {
	CheckBox_DirectGamma->Visible = false;
        CheckBox_AgingMode->Visible = false;
        CheckBox_SecondGamma->Visible = false;
	if (Util::isFileExist(tconFilename.c_str())) {
	    readTCONSetup(tconFilename, section);

	    GroupBox_DigitalGamma->Enabled = false;
	    GroupBox_DirectGamma->Enabled = false;

	}

        if(section == "Hawk") {
            RadioGroup_DataByte->ItemIndex = 1;
            Edit_DeviceAddress->Text = "EC";
        } else {
            RadioGroup_DataByte->ItemIndex = 0;
            Edit_DeviceAddress->Text = "7C";

        }        
    } else {
	ShowMessage("Remember setting Bit Depth!");

	//CheckBox_HideEN->Visible = true;
	//GroupBox_HideEN->Visible = false;


	readTCONSetup(ExtractFilePath(Application->ExeName) + SETUPFILE, "Custom");
	CheckBox_DirectGamma->Visible = true;
	CheckBox_DirectGammaClick(null);
	GroupBox_DigitalGamma->Enabled = true;
	//GroupBox_DigitalGamma->Visible = true;
	GroupBox_DirectGamma->Enabled = true;
	CheckBox_HideEN->Visible = true;
	//CheckBox_HideEN->Enabled = true;

    }
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox_DirectGammaClick(TObject * Sender)
{
    bool directGamma = this->CheckBox_DirectGamma->Checked;
    GroupBox_DirectGamma->Visible = directGamma;
}

//---------------------------------------------------------------------------
bptr < i2c::TCONControl > TMainForm::getTCONControl()
{
    return control;
};



bool TMainForm::isPCwithDirectGamma()
{
    return true == RadioButton_PCTCON_TV->Checked || true == RadioButton_PCTCON_NB->Checked;
};
bool TMainForm::isInTCONSetup()
{
    return debugMode ? 1 == MainForm->PageControl1->ActivePageIndex : false;
};
void __fastcall TMainForm::RadioButton_PCTCON_NBClick(TObject * Sender)
{
    this->Panel_TCON->Visible = true;
    ComboBox_TCONTypeChange(this);
    bitDepth->setDirectGamma(false);
    bitDepth->setAgingMode(false);
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
    String lutType = ComboBox_DGLUTType->Text;
    if (lutType == "10bit") {
	if (RadioButton_Lut10->Enabled) {
	    RadioButton_Lut10->Checked = true;
	} else {
	    ShowMessage("Cannot select 10Bit LUT in present Bit Depth setting");
	    ComboBox_DGLUTType->ItemIndex = 1;
	}
    } else if (lutType == "12bitType1" || lutType == "12bitType2") {
	if (RadioButton_Lut12->Enabled) {
	    RadioButton_Lut12->Checked = true;
	} else {
	    ShowMessage("Cannot select 12Bit LUT in present Bit Depth setting");
	    ComboBox_DGLUTType->ItemIndex = 0;
	}
    }

    /*int lut = ComboBox_DGLUTType->Text.ToInt();
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
    }*/
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

void TMainForm::setAllFunctionOn(bool on)
{
    MainForm->PageControl1->Visible = on;
    MainForm->MatrixCalibration1->Enabled = on;
    MainForm->TargetWhite1->Enabled = on;
    MainForm->CCTLUT1->Enabled = on;
    MainForm->GammaAdj1->Enabled = on;
    MainForm->Measurement1->Enabled = on;
};


void __fastcall TMainForm::TabSheet2Exit(TObject * Sender)
{
    /*if (true == Button_Connect->Enabled) {
	RadioButton_PC->Checked = true;
    }*/

    //影響到選bit數時，TabSheet2 消失。    20130607 byBS-
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::Edit_AverageTimesChange(TObject * Sender)
{
    mm->AverageTimes = this->Edit_AverageTimes->Text.ToInt();
    //Edit_Interval->Text = Edit_Interval->Text + Edit_Interval->Text;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_PCTCON_TVClick(TObject * Sender)
{
    this->Panel_TCON->Visible = true;
    ComboBox_TCONTypeChange(this);
    bitDepth->setDirectGamma(false);
    bitDepth->setAgingMode(false);
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
	    ca210Analyzer->setChannel(ch);
	}
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::TabSheet2Enter(TObject * Sender)
{
    Button_Connect->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::About2Click(TObject * Sender)
{
    if (AboutBox == null) {
	Application->CreateForm(__classid(TAboutBox), &AboutBox);
    }
    AboutBox->ShowModal();
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::ChangeLog1Click(TObject * Sender)
{
    if (ChangeLogForm == null) {
	Application->CreateForm(__classid(TChangeLogForm), &ChangeLogForm);
    }
    ChangeLogForm->ShowModal();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::GammaMeasure1Click(TObject * Sender)
{
    /*if (GammaMeasurementForm == null) {
       Application->CreateForm(__classid(TGammaMeasurementForm), &GammaMeasurementForm);
       } */
    getGammaMeasurementForm();
    GammaMeasurementForm->setBitDepthProcessor(bitDepth);
    GammaMeasurementForm->ShowModal();
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::StabilityMeasure1Click(TObject * Sender)
{
    if (StabilityForm == null) {
	Application->CreateForm(__classid(TStabilityForm), &StabilityForm);
    }
    StabilityForm->Show();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_HStripe2Click(TObject * Sender)
{
    MeasureWindow->setPattern(HStripe2);
    this->CheckBox_LineAdjoin->Visible = false;
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::CheckBox_HideENClick(TObject * Sender)
{
    bool hide = this->CheckBox_HideEN->Checked;
    GroupBox_HideEN->Visible = hide;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Button_PatternTestClick(TObject * Sender)
{
    //MeasureWindow->setRGB(128, 128, 128);
    MeasureWindow->Visible = true;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_NinthMouseMove(TObject * Sender,
						      TShiftState Shift, int X, int Y)
{
    TRadioButton *button = dynamic_cast < TRadioButton * >(Sender);
    if (RadioButton_Ninth == button) {
	MeasureWindow->setTestPattern(Ninth);
    }
    if (null != button) {

    }
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::GroupBox4MouseMove(TObject * Sender, TShiftState Shift, int X, int Y)
{
    MeasureWindow->Visible = false;
    //MeasureWindow->WindowState = wsMaximized;
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::TabSheet1MouseMove(TObject * Sender, TShiftState Shift, int X, int Y)
{
    MeasureWindow->Visible = false;
    //MeasureWindow->WindowState = wsMaximized;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_IndepMouseMove(TObject * Sender,
						      TShiftState Shift, int X, int Y)
{
    MeasureWindow->setTestPattern(Indepedent);
    RadioButton_NinthMouseMove(Sender, Shift, X, Y);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_HSDMouseMove(TObject * Sender,
						    TShiftState Shift, int X, int Y)
{
    MeasureWindow->setTestPattern(HSD);
    RadioButton_NinthMouseMove(Sender, Shift, X, Y);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_FlickrPixelMouseMove(TObject * Sender, TShiftState Shift,
							    int X, int Y)
{
    MeasureWindow->setTestPattern(FlickrPixel);
    RadioButton_NinthMouseMove(Sender, Shift, X, Y);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_FlickrSubPixelMouseMove(TObject * Sender, TShiftState Shift,
							       int X, int Y)
{
    MeasureWindow->setTestPattern(FlickrSubPixel);
    RadioButton_NinthMouseMove(Sender, Shift, X, Y);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_HStripeMouseMove(TObject * Sender,
							TShiftState Shift, int X, int Y)
{
    MeasureWindow->setTestPattern(HStripe);
    RadioButton_NinthMouseMove(Sender, Shift, X, Y);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_HStripe2MouseMove(TObject * Sender,
							 TShiftState Shift, int X, int Y)
{
    MeasureWindow->setTestPattern(HStripe2);
    RadioButton_NinthMouseMove(Sender, Shift, X, Y);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_NormalMouseMove(TObject * Sender,
						       TShiftState Shift, int X, int Y)
{
    MeasureWindow->Visible = false;
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormActivate(TObject * Sender)
{
    //original from form active

    if (debugMode) {
	ShowMessage("It's in Debug Mode, stop connecting to CA-X10");
	Button_PatternTest->Visible = true;
    } else {

    }
    if (true == linkCA210) {
	if (connectCA210ByThread) {

	    class CA210Thread:public TThread {
	      protected:
		void __fastcall Execute() {
		    MainForm->setAllFunctionOn(false);
		    MainForm->StatusBar1->Panels->Items[1]->Text = "CA-210 Connecting...";
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
	MainForm->StatusBar1->Panels->Items[1]->Text = "Debug mode";
	this->GroupBox_CHSetting->Visible = false;
    }
    
    this->RadioButton_PCClick(Sender);     //預設PC設定  btBS+
}

//---------------------------------------------------------------------------

static int TCONIniVerstion = 1;
void TMainForm::initTCONFile()
{
    using namespace cms::util;
    tconFilename = ExtractFilePath(Application->ExeName) + TCONFILE;
    if (!Util::isFileExist(tconFilename.c_str())) {
	//=========================================================================================
	// produce tcon ini file
	//=========================================================================================
	bptr_ < TIniFile > ini(new TIniFile(tconFilename));
	int_array version = Util::fetchVersionInfo();

        try{     //避免唯讀資料夾時，無法創建.ini檔造成當機    by BS+ 20140429
	        ini->WriteInteger("Version", "Release", version[2]);
	        ini->WriteInteger("Version", "Build", version[3]);
	        ini->WriteInteger("Version", "T-CON ini", TCONIniVerstion);
        }

        catch (Exception &exception) {
                MessageBox(NULL,"無法建立TCON.ini檔","",MB_OK);
                return;
                //Application->Terminate();
        }


	//=========================================================================
	// 11303
	//=========================================================================
	ini->WriteInteger("11303", "AddressingSize", 5);

	ini->WriteString("11303", "FRCEnableAddress", "4");
	ini->WriteInteger("11303", "FRCEnableBit", 2);

	ini->WriteString("11303", "DigitalGammaEnableAddress", "4");
	ini->WriteInteger("11303", "DigitalGammaEnableBit", 1);
	ini->WriteString("11303", "DigitalGammaLUTAddress", "302");
	ini->WriteString("11303", "DigitalGammaLUTType", "10bit");

	ini->WriteBool("11303", "DirectGammaFunc", false);

	ini->WriteInteger("11303", "in", 8);
	ini->WriteInteger("11303", "out", 8);
	//=========================================================================
	// 11306
	//=========================================================================
	ini->WriteInteger("11306", "AddressingSize", 5);

	ini->WriteString("11306", "FRCEnableAddress", "28");
	ini->WriteInteger("11306", "FRCEnableBit", 1);

	ini->WriteString("11306", "DigitalGammaEnableAddress", "28");
	ini->WriteInteger("11306", "DigitalGammaEnableBit", 0);
	ini->WriteString("11306", "DigitalGammaLUTAddress", "3C0");
	ini->WriteString("11306", "DigitalGammaLUTType", "10bit");

	ini->WriteBool("11306", "DirectGammaFunc", true);
	ini->WriteString("11306", "GammaTestEnableAddress", "381");
	ini->WriteInteger("11306", "GammaTestEnableBit", 1);
	ini->WriteString("11306", "DirectGammaAddress", "387");
	ini->WriteBool("11306", "DirectGammaIndepRGB", true);
	ini->WriteString("11306", "DirectGammaType", "12401Type");
	//ini->WriteString("11306", "GammaTestBit", "12");

	ini->WriteInteger("11306", "in", 6);
	ini->WriteInteger("11306 ", "out", 6);
	//=========================================================================
	// 11307
	//=========================================================================
	ini->WriteInteger("11307", "AddressingSize", 5);

	ini->WriteString("11307", "FRCEnableAddress", "28");
	ini->WriteInteger("11307", "FRCEnableBit", 1);

	ini->WriteString("11307", "DigitalGammaEnableAddress", "28");
	ini->WriteInteger("11307", "DigitalGammaEnableBit", 0);
	ini->WriteString("11307", "DigitalGammaLUTAddress", "310");
	ini->WriteString("11307", "DigitalGammaLUTType", "10bit");

	ini->WriteBool("11307", "DirectGammaFunc", true);
	ini->WriteString("11307", "GammaTestEnableAddress", "2F1");
	ini->WriteInteger("11307", "GammaTestEnableBit", 1);
	ini->WriteString("11307", "DirectGammaAddress", "2F3");
	ini->WriteBool("11307", "DirectGammaIndepRGB", true);
	ini->WriteString("11307", "DirectGammaType", "12401Type");
	//ini->WriteString("11307", "GammaTestBit", "12");

	ini->WriteInteger("11307", "in", 6);
	ini->WriteInteger("11307", "out", 6);
	//=========================================================================
	// 12306
	//=========================================================================
	ini->WriteInteger("12306", "AddressingSize", 5);

	ini->WriteString("12306", "FRCEnableAddress", "28");
	ini->WriteInteger("12306", "FRCEnableBit", 1);

	ini->WriteString("12306", "DigitalGammaEnableAddress", "28");
	ini->WriteInteger("12306", "DigitalGammaEnableBit", 0);
	ini->WriteString("12306", "DigitalGammaLUTAddress", "302");
	ini->WriteString("12306", "DigitalGammaLUTType", "12bitType1");

	ini->WriteBool("12306", "DirectGammaFunc", true);
	ini->WriteString("12306", "GammaTestEnableAddress", "29");
	ini->WriteInteger("12306", "GammaTestEnableBit", 0);
	ini->WriteString("12306", "DirectGammaAddress", "154");
	ini->WriteBool("12306", "DirectGammaIndepRGB", true);
	ini->WriteString("12306", "DirectGammaType", "12401Type");
	//ini->WriteString("12306", "GammaTestBit", "12");

	ini->WriteInteger("12306", "in", 8);
	ini->WriteInteger("12306", "out", 8);
	//=========================================================================
	// 12309
	//=========================================================================
	ini->WriteInteger("12309", "AddressingSize", 5);

	ini->WriteString("12309", "FRCEnableAddress", "76");
	ini->WriteInteger("12309", "FRCEnableBit", 0);

	ini->WriteString("12309", "DigitalGammaEnableAddress", "76");
	ini->WriteInteger("12309", "DigitalGammaEnableBit", 1);
	ini->WriteString("12309", "DigitalGammaLUTAddress", "800");
	ini->WriteString("12309", "DigitalGammaLUTType", "12bitType1");

	ini->WriteBool("12309", "DirectGammaFunc", true);
	ini->WriteString("12309", "GammaTestEnableAddress", "76");
	ini->WriteInteger("12309", "GammaTestEnableBit", 5);
	ini->WriteString("12309", "DirectGammaAddress", "107");
	ini->WriteBool("12309", "DirectGammaIndepRGB", true);
	ini->WriteString("12309", "DirectGammaType", "12401Type");
	//ini->WriteString("12309", "GammaTestBit", "12");

	ini->WriteInteger("12309", "in", 8);
	ini->WriteInteger("12309", "out", 8);
	//=========================================================================
	// 12401
	//=========================================================================
	ini->WriteInteger("12401", "AddressingSize", 5);

	ini->WriteString("12401", "FRCEnableAddress", "28");
	ini->WriteInteger("12401", "FRCEnableBit", 4);

	ini->WriteString("12401", "DigitalGammaEnableAddress", "28");
	ini->WriteInteger("12401", "DigitalGammaEnableBit", 0);
	ini->WriteString("12401", "DigitalGammaLUTAddress", "752");
	ini->WriteString("12401", "DigitalGammaLUTType", "12bitType1");

	ini->WriteBool("12401", "DirectGammaFunc", true);
	ini->WriteString("12401", "GammaTestEnableAddress", "4A1");
	ini->WriteInteger("12401", "GammaTestEnableBit", 1);
	ini->WriteString("12401", "DirectGammaAddress", "4A7");
	ini->WriteBool("12401", "DirectGammaIndepRGB", true);
	ini->WriteString("12401", "DirectGammaType", "12401Type");
	//ini->WriteString("12401", "GammaTestBit", "12");

	ini->WriteInteger("12401", "in", 8);
	ini->WriteInteger("12401", "out", 8);
	//=========================================================================
	// 12403
	//=========================================================================
	ini->WriteInteger("12403", "AddressingSize", 5);

	ini->WriteString("12403", "FRCEnableAddress", "29");
	ini->WriteInteger("12403", "FRCEnableBit", 2);

	ini->WriteString("12403", "DigitalGammaEnableAddress", "29");
	ini->WriteInteger("12403", "DigitalGammaEnableBit", 0);
	ini->WriteString("12403", "DigitalGammaLUTAddress", "B60");
	ini->WriteString("12403", "DigitalGammaLUTType", "12bitType1");

	ini->WriteBool("12403", "DirectGammaFunc", true);
	ini->WriteString("12403", "GammaTestEnableAddress", "FF9");
	ini->WriteInteger("12403", "GammaTestEnableBit", 4);
	ini->WriteString("12403", "DirectGammaAddress", "FFA");
	ini->WriteBool("12403", "DirectGammaIndepRGB", false);
	ini->WriteString("12403", "DirectGammaType", "12403Type");
	//ini->WriteString("12403", "GammaTestBit", "12");

	ini->WriteInteger("12403", "in", 8);
	ini->WriteInteger("12403", "out", 8);
	//=========================================================================
	// 12405
	//=========================================================================
	ini->WriteInteger("12405", "AddressingSize", 5);

	ini->WriteString("12405", "FRCEnableAddress", "29");
	ini->WriteInteger("12405", "FRCEnableBit", 2);

	ini->WriteString("12405", "DigitalGammaEnableAddress", "29");
	ini->WriteInteger("12405", "DigitalGammaEnableBit", 0);
	ini->WriteString("12405", "DigitalGammaLUTAddress", "106D");
	ini->WriteString("12405", "DigitalGammaLUTType", "12bitType1");

	ini->WriteBool("12405", "DirectGammaFunc", true);
	ini->WriteString("12405", "GammaTestEnableAddress", "1FEB");
	ini->WriteInteger("12405", "GammaTestEnableBit", 4);
	ini->WriteString("12405", "DirectGammaAddress", "1FEC");
	ini->WriteBool("12405", "DirectGammaIndepRGB", false);
	ini->WriteString("12405", "DirectGammaType", "12403Type");
	//ini->WriteString("12405", "GammaTestBit", "12");

	ini->WriteInteger("12405", "in", 8);
	ini->WriteInteger("12405", "out", 8);
	//=========================================================================
	// 12407
	//=========================================================================
	ini->WriteInteger("12407", "AddressingSize", 5);

	ini->WriteString("12407", "FRCEnableAddress", "29");
	ini->WriteInteger("12407", "FRCEnableBit", 2);

	ini->WriteString("12407", "DigitalGammaEnableAddress", "29");
	ini->WriteInteger("12407", "DigitalGammaEnableBit", 0);
	ini->WriteString("12407", "DigitalGammaLUTAddress", "110D");
	ini->WriteString("12407", "DigitalGammaLUTType", "12bitType1");

	ini->WriteBool("12407", "DirectGammaFunc", true);
	ini->WriteString("12407", "GammaTestEnableAddress", "3FEB");
	ini->WriteInteger("12407", "GammaTestEnableBit", 4);
	ini->WriteString("12407", "DirectGammaAddress", "3FEC");
	ini->WriteBool("12407", "DirectGammaIndepRGB", false);
	ini->WriteString("12407", "DirectGammaType", "12403Type");
	//ini->WriteString("12407", "GammaTestBit", "12");

	ini->WriteInteger("12407", "in", 8);
	ini->WriteInteger("12407", "out", 8);
	//=========================================================================
	// 62301
	//=========================================================================
	ini->WriteInteger("62301", "AddressingSize", 5);

	//ini->WriteString("62301", "FRCEnableAddress", "28");
	//ini->WriteInteger("62301", "FRCEnableBit", 1);

	ini->WriteString("62301", "DigitalGammaEnableAddress", "28");
	ini->WriteInteger("62301", "DigitalGammaEnableBit", 0);
	ini->WriteString("62301", "DigitalGammaLUTAddress", "400");
	ini->WriteString("62301", "DigitalGammaLUTType", "10bit");

	ini->WriteBool("62301", "DirectGammaFunc", true);
	ini->WriteString("62301", "GammaTestEnableAddress", "307");
	ini->WriteInteger("62301", "GammaTestEnableBit", 6);
	ini->WriteString("62301", "DirectGammaAddress", "307");
	ini->WriteString("62301", "DirectGammaType", "62301Type");
	//ini->WriteString("62301", "GammaTestBit", "10");

	ini->WriteInteger("62301", "in", 8);
	ini->WriteInteger("62301", "out", 6);
	//=========================================================================
	// 1H501
	//=========================================================================
	ini->WriteInteger("1H501", "AddressingSize", 5);

	ini->WriteString("1H501", "FRCEnableAddress", "28");
	ini->WriteInteger("1H501", "FRCEnableBit", 1);

	ini->WriteString("1H501", "DigitalGammaEnableAddress", "28");
	ini->WriteInteger("1H501", "DigitalGammaEnableBit", 0);
	ini->WriteString("1H501", "DigitalGammaLUTAddress", "BE0");
	ini->WriteString("1H501", "DigitalGammaLUTType", "10bit");

	ini->WriteBool("1H501", "DirectGammaFunc", true);
	ini->WriteString("1H501", "GammaTestEnableAddress", "B");
	ini->WriteInteger("1H501", "GammaTestEnableBit", 0);
	ini->WriteString("1H501", "DirectGammaAddress", "5");
	ini->WriteString("1H501", "DirectGammaType", "1H501Type");
	ini->WriteBool("1H501", "HideFunc", true);
	ini->WriteString("1H501", "HideEnableAddress", "2");
	ini->WriteInteger("1H501", "HideEnableBit", 6);

	ini->WriteInteger("1H501", "in", 8);
	ini->WriteInteger("1H501", "out", 8);
	//=========================================================================
	// 12409
	//=========================================================================
	ini->WriteInteger("12409", "AddressingSize", 5);            //EEPROM Size

	ini->WriteString("12409", "FRCEnableAddress", "55");
	ini->WriteInteger("12409", "FRCEnableBit", 0);

	ini->WriteString("12409", "DigitalGammaEnableAddress", "55");
	ini->WriteInteger("12409", "DigitalGammaEnableBit", 1);
	ini->WriteString("12409", "DigitalGammaLUTAddress", "302"); //不包含CheckSum
	ini->WriteString("12409", "DigitalGammaLUTType", "12bitType2");

	ini->WriteBool("12409", "DirectGammaFunc", true);
	ini->WriteString("12409", "GammaTestEnableAddress", "FE1");
	ini->WriteInteger("12409", "GammaTestEnableBit", 0);
	ini->WriteString("12409", "DirectGammaAddress", "FE2");
	ini->WriteString("12409", "DirectGammaType", "12409Type");

	ini->WriteBool("12409", "AgingFunc", true);
	ini->WriteString("12409", "AgingAGBSDebugAddress", "FE8");
	ini->WriteInteger("12409", "AgingAGBSDebugBit", 0);
	ini->WriteString("12409", "AgingModeSelectAddress", "40");
        ini->WriteInteger("12409", "AgingModeSelectValue", 1);
	ini->WriteInteger("12409", "AgingModeSelectStartBit", 5);
        ini->WriteInteger("12409", "AgingModeSelectEndBit", 5);
	ini->WriteString("12409", "AgingPatternSelectAddress", "40");
        ini->WriteInteger("12409", "AgingPatternSelectValue", 16);
        ini->WriteInteger("12409", "AgingPatternSelectStartBit", 0);
        ini->WriteInteger("12409", "AgingPatternSelectEndBit", 4);
	ini->WriteString("12409", "AgingRasterGrayAddress", "41");
	ini->WriteString("12409", "AgingType", "12409Aging");

	ini->WriteInteger("12409", "in", 8);
	ini->WriteInteger("12409", "out", 8);
	//=========================================================================
	// 11311
	//=========================================================================
	ini->WriteInteger("11311", "AddressingSize", 5);            //EEPROM Size

        ini->WriteString("11311", "FRCEnableAddress", "47");
	ini->WriteInteger("11311", "FRCEnableBit", 6);

	ini->WriteString("11311", "DigitalGammaEnableAddress", "47");
	ini->WriteInteger("11311", "DigitalGammaEnableBit", 7);
	ini->WriteString("11311", "DigitalGammaLUTAddress", "230"); //不包含CheckSum
	ini->WriteString("11311", "DigitalGammaLUTType", "10bit");

	ini->WriteBool("11311", "DirectGammaFunc", true);
	ini->WriteString("11311", "GammaTestEnableAddress", "607");
	ini->WriteInteger("11311", "GammaTestEnableBit", 1);
	ini->WriteString("11311", "DirectGammaAddress", "606");
	ini->WriteString("11311", "DirectGammaType", "11311Type");

	ini->WriteInteger("11311", "in", 8);
	ini->WriteInteger("11311", "out", 8);

	//=========================================================================
	// 12411/2
	//=========================================================================
	ini->WriteInteger("12411/2", "AddressingSize", 7);            //EEPROM Size

	ini->WriteString("12411/2", "FRCEnableAddress", "A9");
	ini->WriteInteger("12411/2", "FRCEnableBit", 2);

	ini->WriteString("12411/2", "DigitalGammaEnableAddress", "A9");
	ini->WriteInteger("12411/2", "DigitalGammaEnableBit", 0);
	ini->WriteString("12411/2", "DigitalGammaLUTAddress", "CE2"); //不包含CheckSum，有四張gamma表
	ini->WriteString("12411/2", "DigitalGammaLUTType", "12bitType2");

	ini->WriteBool("12411/2", "DirectGammaFunc", true);
	ini->WriteString("12411/2", "GammaTestEnableAddress", "7FC0");
	ini->WriteInteger("12411/2", "GammaTestEnableBit", 0);
	ini->WriteString("12411/2", "DirectGammaAddress", "7FC1");
	ini->WriteString("12411/2", "DirectGammaType", "12411Type");

	ini->WriteBool("12411/2", "AgingFunc", true);
	ini->WriteString("12411/2", "AgingAGBSDebugAddress", "7FF3");
	ini->WriteInteger("12411/2", "AgingAGBSDebugBit", 6);
	ini->WriteString("12411/2", "AgingModeSelectAddress", "46");
        ini->WriteInteger("12411/2", "AgingModeSelectValue", 1);
	ini->WriteInteger("12411/2", "AgingModeSelectStartBit", 0);
        ini->WriteInteger("12411/2", "AgingModeSelectEndBit", 0);
	ini->WriteString("12411/2", "AgingPatternSelectAddress", "46");
        ini->WriteInteger("12411/2", "AgingPatternSelectValue", 17);
        ini->WriteInteger("12411/2", "AgingPatternSelectStartBit", 3);
        ini->WriteInteger("12411/2", "AgingPatternSelectEndBit", 7);
	ini->WriteString("12411/2", "AgingRasterGrayAddress", "50");   //50 9:4(0~5)  51 3:0(0~3)
	ini->WriteString("12411/2", "AgingType", "12411Aging");

        ini->WriteString("12411/2", "AgingManuSelectAddress", "46");
        ini->WriteInteger("12411/2", "AgingManuSelectBit", 1);

        ini->WriteBool("12411/2", "SecondGamma", true);
	ini->WriteString("12411/2", "DigitalGamma2EnableAddress", "A9");
	ini->WriteInteger("12411/2", "DigitalGamma2EnableBit", 1);
        ini->WriteString("12411/2", "DigitalGammaLUT2Address", "1168"); //不包含CheckSum，有四張gamma表
	ini->WriteString("12411/2", "Gamma2TestEnableAddress", "7FC7");
	ini->WriteInteger("12411/2", "Gamma2TestEnableBit", 0);
	ini->WriteString("12411/2", "DirectGamma2Address", "7FC8");
	ini->WriteString("12411/2", "FRCE2nableAddress", "A9");
	ini->WriteInteger("12411/2", "FRC2EnableBit", 3);

        //AG Timnig Setting
        ini->WriteBool("12411/2", "AGTiming", true);
	ini->WriteString("12411/2", "AGFrameRate", "60Hz");
	ini->WriteString("12411/2", "AGFrameRateAddress", "5A");
        ini->WriteInteger("12411/2", "AGFrameRateStartBit", 4);
        ini->WriteInteger("12411/2", "AGFrameRateEndBit", 5);
	ini->WriteString("12411/2", "AGmpllModeAddress", "1C6");
        ini->WriteInteger("12411/2", "AGmpllModeStartBit", 3);
        ini->WriteInteger("12411/2", "AGmpllModeEndBit", 4);
        ini->WriteInteger("12411/2", "AGmpllModeValue", 0);
	ini->WriteString("12411/2", "AGmpllNMSBAddress", "1C2");
        ini->WriteInteger("12411/2", "AGmpllNMSBStartBit", 5);
        ini->WriteInteger("12411/2", "AGmpllNMSBEndBit", 7);
	ini->WriteString("12411/2", "AGmpllNLSBAddress", "1C4");
        ini->WriteInteger("12411/2", "AGmpllNLSBStartBit", 5);
        ini->WriteInteger("12411/2", "AGmpllNLSBEndBit", 7);
        ini->WriteInteger("12411/2", "AGmpllNValue", 12);
	ini->WriteString("12411/2", "AGmpllFMSBAddress", "1C7");
        ini->WriteInteger("12411/2", "AGmpllFMSBStartBit", 0);
        ini->WriteInteger("12411/2", "AGmpllFMSBEndBit", 6);
	ini->WriteString("12411/2", "AGmpllFLSBAddress", "1C8");
        ini->WriteInteger("12411/2", "AGmpllFLSBStartBit", 0);
        ini->WriteInteger("12411/2", "AGmpllFLSBEndBit", 7);
        ini->WriteInteger("12411/2", "AGmpllFValue", 0);
	ini->WriteString("12411/2", "AGmpllMAddress", "1C6");
        ini->WriteInteger("12411/2", "AGmpllMStartBit", 5);
        ini->WriteInteger("12411/2", "AGmpllMEndBit", 6);
        ini->WriteInteger("12411/2", "AGmpllMValue", 3);
	ini->WriteString("12411/2", "AGHblkMSBAddress", "47");
        ini->WriteInteger("12411/2", "AGHblkMSBStartBit", 0);
        ini->WriteInteger("12411/2", "AGHblkMSBEndBit", 7);
	ini->WriteString("12411/2", "AGHblkLSBAddress", "48");
        ini->WriteInteger("12411/2", "AGHblkLSBStartBit", 5);
        ini->WriteInteger("12411/2", "AGHblkLSBEndBit", 7);
        ini->WriteInteger("12411/2", "AGHblkValue", 176);
	ini->WriteString("12411/2", "AGVblk1MSBAddress", "48");
        ini->WriteInteger("12411/2", "AGVblk1MSBStartBit", 0);
        ini->WriteInteger("12411/2", "AGVblk1MSBEndBit", 4);
	ini->WriteString("12411/2", "AGVblk1LSBAddress", "49");
        ini->WriteInteger("12411/2", "AGVblk1LSBStartBit", 2);
        ini->WriteInteger("12411/2", "AGVblk1LSBEndBit", 7);
        ini->WriteInteger("12411/2", "AGVblk1Value", 20);
	ini->WriteString("12411/2", "AGVblk2MSBAddress", "51");
        ini->WriteInteger("12411/2", "AGVblk2MSBStartBit", 4);
        ini->WriteInteger("12411/2", "AGVblk2MSBEndBit", 7);
	ini->WriteString("12411/2", "AGVblk2LSBAddress", "52");
        ini->WriteInteger("12411/2", "AGVblk2LSBStartBit", 0);
        ini->WriteInteger("12411/2", "AGVblk2LSBEndBit", 6);
        ini->WriteInteger("12411/2", "AGVblk2Value", 20);

	ini->WriteInteger("12411/2", "in", 8);
	ini->WriteInteger("12411/2", "out", 8);

	//=========================================================================
	// 12412
	//=========================================================================
	/*ini->WriteInteger("12412", "AddressingSize", 7);            //EEPROM Size

	ini->WriteString("12412", "FRCEnableAddress", "A9");
	ini->WriteInteger("12412", "FRCEnableBit", 2);

	ini->WriteString("12412", "DigitalGammaEnableAddress", "A9");
	ini->WriteInteger("12412", "DigitalGammaEnableBit", 0);
	ini->WriteString("12412", "DigitalGammaLUTAddress", "CE2"); //不包含CheckSum，有四張gamma表
	ini->WriteString("12412", "DigitalGammaLUTType", "12bitType2");

	ini->WriteBool("12412", "DirectGammaFunc", true);
	ini->WriteString("12412", "GammaTestEnableAddress", "7FC0");
	ini->WriteInteger("12412", "GammaTestEnableBit", 0);
	ini->WriteString("12412", "DirectGammaAddress", "7FC1");
	ini->WriteString("12412", "DirectGammaType", "12411Type");

	ini->WriteBool("12412", "AgingFunc", true);
	ini->WriteString("12412", "AgingAGBSDebugAddress", "7FF3");
	ini->WriteInteger("12412", "AgingAGBSDebugBit", 6);
	ini->WriteString("12412", "AgingModeSelectAddress", "46");
	ini->WriteInteger("12412", "AgingModeSelectBit", 0);
	ini->WriteString("12412", "AgingPatternSelectAddress", "46");
        ini->WriteInteger("12412", "AgingPatternSelectValue", 17);
        ini->WriteInteger("12412", "AgingPatternSelectStartBit", 3);
        ini->WriteInteger("12412", "AgingPatternSelectEndBit", 7);
	ini->WriteString("12412", "AgingRasterGrayAddress", "50");   //50 9:4(0~5)  51 3:0(0~3)
	ini->WriteString("12412", "AgingType", "12411Aging");

        ini->WriteString("12412", "AgingManuSelectAddress", "46");
        ini->WriteInteger("12412", "AgingManuSelectBit", 1);

        ini->WriteBool("12412", "SecondGamma", true);
	ini->WriteString("12412", "DigitalGamma2EnableAddress", "A9");
	ini->WriteInteger("12412", "DigitalGamma2EnableBit", 1);
        ini->WriteString("12412", "DigitalGammaLUT2Address", "1168"); //不包含CheckSum，有四張gamma表
	ini->WriteString("12412", "Gamma2TestEnableAddress", "7FC7");
	ini->WriteInteger("12412", "Gamma2TestEnableBit", 0);
	ini->WriteString("12412", "DirectGamma2Address", "7FC8");
	ini->WriteString("12412", "FRCE2nableAddress", "A9");
	ini->WriteInteger("12412", "FRC2EnableBit", 3);

	ini->WriteInteger("12412", "in", 8);
	ini->WriteInteger("12412", "out", 8);
        */
        //=========================================================================
	// 12802
	//=========================================================================
	ini->WriteInteger("12802", "AddressingSize", 5);

	ini->WriteString("12802", "FRCEnableAddress", "70016");  
	ini->WriteInteger("12802", "FRCEnableBit", 4);

        ini->WriteBool("12802", "PGMode", true);
	ini->WriteString("12802", "PGEnableAddress", "7000D");
	ini->WriteInteger("12802", "PGEnableBit", 0);
	ini->WriteString("12802", "PGModeAddress", "70013");
	ini->WriteInteger("12802", "PGModeStartBit", 0);
	ini->WriteInteger("12802", "PGModeEndBit", 2);
	ini->WriteString("12802", "PGPatternMSBAddress", "70011");
	ini->WriteInteger("12802", "PGPatternMSBStartBit", 0);
	ini->WriteInteger("12802", "PGPatternMSBEndBit", 5);
	ini->WriteString("12802", "PGPatternLSBAddress", "70012");
	ini->WriteInteger("12802", "PGPatternLSBStartBit", 4);
	ini->WriteInteger("12802", "PGPatternlSBEndBit", 7);
	ini->WriteString("12802", "PGHblkMSBAddress", "7000E");
	ini->WriteInteger("12802", "PGHblkMSBStartBit", 0);
	ini->WriteInteger("12802", "PGHblkMSBEndBit", 6);
	ini->WriteString("12802", "PGHblkLSBAddress", "7000F");
	ini->WriteInteger("12802", "PGHblkLSBStartBit", 4);
	ini->WriteInteger("12802", "PGHblkLSBEndBit", 7);
        ini->WriteInteger("12802", "PGHblkValue", 160);
	ini->WriteString("12802", "PGVblkMSBAddress", "7000F");
	ini->WriteInteger("12802", "PGVblkMSBStartBit", 0);
	ini->WriteInteger("12802", "PGVblkMSBEndBit", 2);
	ini->WriteString("12802", "PGVblkLSBAddress", "70010");
	ini->WriteInteger("12802", "PGVblkLSBStartBit", 0);
	ini->WriteInteger("12802", "PGVblkLSBEndBit", 7);
        ini->WriteInteger("12802", "PGVblkValue", 24);


	ini->WriteString("12802", "DigitalGammaEnableAddress", "70016");
	ini->WriteInteger("12802", "DigitalGammaEnableBit", 0);
	ini->WriteString("12802", "DigitalGammaLUTAddress", "70140");
	ini->WriteString("12802", "DigitalGammaLUTType", "12bitType2");

	ini->WriteBool("12802", "DirectGammaFunc", false);

	ini->WriteInteger("12802", "in", 8);
	ini->WriteInteger("12802", "out", 8);

        //=========================================================================
	// Hawk
	//=========================================================================
	ini->WriteInteger("Hawk", "AddressingSize", 5);            //EEPROM Size
        /*
	ini->WriteString("Hawk", "FRCEnableAddress", "55");
	ini->WriteInteger("Hawk", "FRCEnableBit", 0);

	ini->WriteString("Hawk", "DigitalGammaEnableAddress", "55");
	ini->WriteInteger("Hawk", "DigitalGammaEnableBit", 1);
	ini->WriteString("Hawk", "DigitalGammaLUTAddress", "302"); //不包含CheckSum
	ini->WriteString("Hawk", "DigitalGammaLUTType", "12bitType2");

	ini->WriteBool("Hawk", "DirectGammaFunc", true);
	ini->WriteString("Hawk", "GammaTestEnableAddress", "FE1");
	ini->WriteInteger("Hawk", "GammaTestEnableBit", 0);
	ini->WriteString("Hawk", "DirectGammaAddress", "FE2");
	ini->WriteString("Hawk", "DirectGammaType", "12409Type");
        */

        //ini->WriteBool("Hawk", "DirectGammaFunc", true);

	ini->WriteBool("Hawk", "AgingFunc", true);
	ini->WriteString("Hawk", "AgingAGBSDebugAddress", "1F0");
	ini->WriteInteger("Hawk", "AgingAGBSDebugBit", 0);

	ini->WriteString("Hawk", "AgingModeSelectAddress", "1FD");
        ini->WriteInteger("Hawk", "AgingModeSelectValue", 1);
	ini->WriteInteger("Hawk", "AgingModeSelectStartBit", 4);
        ini->WriteInteger("Hawk", "AgingModeSelectEndBit", 6);
	ini->WriteString("Hawk", "AgingPatternSelectAddress", "206");
        ini->WriteInteger("Hawk", "AgingPatternSelectValue", 26);
        ini->WriteInteger("Hawk", "AgingPatternSelectStartBit", 0);
        ini->WriteInteger("Hawk", "AgingPatternSelectEndBit", 4);
	ini->WriteString("Hawk", "AgingRasterGrayAddress", "20A");
	ini->WriteString("Hawk", "AgingType", "HawkType");

	ini->WriteInteger("Hawk", "in", 8);
	ini->WriteInteger("Hawk", "out", 8);


    }
}

void TMainForm::readTCONSections()
{
    bptr_ < TIniFile > ini(new TIniFile(tconFilename));
    bptr_ < TStringList > tconSections(new TStringList());
    ini->ReadSections(tconSections.get());
    int size = tconSections->Count;
    // bool hadVersionSection = false;
    for (int x = 0; x < size; x++) {
	String section = (*tconSections)[x];
        bool directGammaFunc = ini->ReadBool(section, "DirectGammaFunc", false);

	if (section != "Version" && directGammaFunc==true ) {
	    ComboBox_TCONType->AddItem(section, null);
	}

    }

    //if (hadVersionSection) {
    int tconIniVersion = ini->ReadInteger("Version", "T-CON ini", 0);
    if (tconIniVersion < TCONIniVerstion) {
	ShowMessage("\"tcon.ini\" needs updating!");
    }
    //ini->ReadInteger(section, "AddressingSize", 5);
    /*} else {
       ShowMessage("\"tcon.ini\" needs updating!");
       } */

    ComboBox_TCONType->AddItem(CUSTOM, null);
    ComboBox_TCONType->ItemIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::RadioButton_TCON_agingClick(TObject *Sender)
{

    GroupBox_Pattern->Enabled = false;
    this->Panel_TCON->Visible = true;
    this->TargetWhite1->Enabled = false;   //*******************//
    this->CCTLUT1->Enabled = false;        //  鎖定演算法相關   //
    this->GammaAdj1->Enabled = false;      //*******************//

    setComboBoxTCONType();                 //設定顯示只有Aging mode的Tcon

    ShowMessage
        ("\"Aging mode\" only for Gamma Measurement, not support CCT algo to produce DG LUT.\n And please turn on FRC for measurement.");

    PageControl1->ActivePageIndex = 1;

}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox_AgingModeClick(TObject *Sender)
{
    bool hide = this->CheckBox_AgingMode->Checked;
    GroupBox_AgingMode->Visible = hide;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox_SecondGammaClick(TObject *Sender)
{
    bool hide = this->CheckBox_SecondGamma->Checked;
    GroupBox_SecondGamma->Visible = hide;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::CheckBox_PGModeClick(TObject *Sender)
{
    bool hide = this->CheckBox_PGMode->Checked;
    GroupBox_PGmode->Visible = hide;
}

//---------------------------------------------------------------------------

void TMainForm::setComboBoxTCONType()
{
    ComboBox_TCONType->Clear();

    bptr_ < TIniFile > ini(new TIniFile(tconFilename));
    bptr_ < TStringList > tconSections(new TStringList());
    ini->ReadSections(tconSections.get());
    int size = tconSections->Count;

    for (int x = 0; x < size; x++) {
	String section = (*tconSections)[x];
        bool agingFunc = ini->ReadBool(section, "AgingFunc", false);
        bool pgMode = ini->ReadBool(section, "PGMode", false);

	if (section != "Version" && (agingFunc==true || pgMode==true)) {
	    ComboBox_TCONType->AddItem(section, null);
	}
    }

    /*for (int x = size-1; x >0; x--) {
	String section = (*tconSections)[x];
        bool agingFunc = ini->ReadBool(section, "AgingFunc", false);
        bool pgMode = ini->ReadBool(section, "PGMode", false);

	if (agingFunc==false && pgMode==false && section != "Version") {
	    ComboBox_TCONType->Items->Delete(x-1);
	}
    }     */

    ComboBox_TCONType->ItemIndex = -1; //顯示空白給user自己選擇tcon
}
//---------------------------------------------------------------------------

void TMainForm::initialFactoryIF()
{
    GroupBox_BitDepth->Visible = false;
    MatrixCalibration1->Visible = false;
    TargetWhite1->Visible = false;
    CCTLUT1->Visible = false;
    GammaAdj1->Visible = false;
    StabilityMeasure1->Visible = false;
    RadioButton_DoDoBird_USB->Checked = true;
    MainForm->Width = 850;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ComboBox_AGFrameRateChange(TObject *Sender)
{
        int FreqSelect = ComboBox_AGFrameRate->ItemIndex;
        if(FreqSelect==0) {
                Edit_AGHblkValue->Text = "176";
        } else if(FreqSelect==1) {
                Edit_AGHblkValue->Text = "88";
        }
}
//---------------------------------------------------------------------------

