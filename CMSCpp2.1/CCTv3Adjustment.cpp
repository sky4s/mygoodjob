//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#define NO_PROMPT_ON_HRCHECK_FAILURE
#include <comobj.hpp>
#include "src\gui\cct\TMainForm.h"
//---------------------------------------------------------------------------
USEFORM("src\gui\TMeasureWindow.cpp", MeasureWindow);
USEFORM("src\gui\TAnalyzerFrame.cpp", AnalyzerFrame); /* TFrame: File Type */
USEFORM("src\gui\TI2CTestForm.cpp", I2CTestForm);
USEFORM("src\gui\TCA210SettingFrame.cpp", CA210SettingFrame); /* TFrame: File Type */
USEFORM("src\gui\TMatrixCalibration.cpp", MatrixCalibrationForm);
USEFORM("src\gui\TOptionsFrame.cpp", OptionsFrame); /* TFrame: File Type */
USEFORM("src\gui\TOutputFileFrame.cpp", OutputFileFrame); /* TFrame: File Type */
USEFORM("src\gui\cct\TGammaAdjustmentForm.cpp", GammaAdjustmentForm);
USEFORM("src\gui\cct\TGammaMeasurementForm.cpp", GammaMeasurementForm);
USEFORM("src\gui\cct\TMainForm.cpp", MainForm);
USEFORM("src\gui\cct\TTargetWhiteForm2.cpp", TargetWhiteForm2);
USEFORM("src\gui\cct\TAboutBox.cpp", AboutBox);
USEFORM("src\gui\cct\TCCTLUTForm.cpp", CCTLUTForm);
USEFORM("src\gui\cct\TChangeLogForm.cpp", ChangeLogForm);
USEFORM("src\gui\cct\TStabilityForm.cpp", StabilityForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{



    try {
	Application->Initialize();
	Application->Title = "CCTAdjustment v3.3b ";
	Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TMeasureWindow), &MeasureWindow);
                 Application->CreateForm(__classid(TStabilityForm), &StabilityForm);
                 Application->Run();
    }
    catch(EOleException & ex) {
	ShowMessage("CA210 cannot be linked.");
	//Application->Terminate();
    }
    catch(Exception & exception) {
	Application->ShowException(&exception);
    }
    catch(...) {
	try {
	    throw Exception("");
	}
	catch(Exception & exception) {
	    Application->ShowException(&exception);
	}
    }

    if (g_bIsRunAgain)		//g_bIsRunAgain是用于判?是否重?的bool型?量，在Unit1.h中?明
    {
	AnsiString strPath;
	STARTUPINFO StartInfo;
	PROCESS_INFORMATION procStruct;
	memset(&StartInfo, 0, sizeof(STARTUPINFO));
	StartInfo.cb = sizeof(STARTUPINFO);
	strPath = Application->ExeName;
	if (!::CreateProcess((LPCTSTR) strPath.c_str(), NULL, NULL, NULL,
			     FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &StartInfo, &procStruct))
	    return 0;
    }


    return 0;
}

//---------------------------------------------------------------------------




