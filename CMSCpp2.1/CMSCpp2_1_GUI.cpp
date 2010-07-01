//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#define NO_PROMPT_ON_HRCHECK_FAILURE
#include <comobj.hpp>

//---------------------------------------------------------------------------
USEFORM("src\Unit1.cpp", Form1);
USEFORM("src\gui\TMeasureWindow.cpp", MeasureWindow);
USEFORM("src\gui\TAnalyzerFrame.cpp", AnalyzerFrame); /* TFrame: File Type */
USEFORM("src\gui\TI2CTestForm.cpp", I2CTestForm);
USEFORM("src\gui\TMatrixCalibration.cpp", MatrixCalibrationForm);
USEFORM("src\gui\TCA210SettingFrame.cpp", CA210SettingFrame); /* TFrame: File Type */
USEFORM("src\gui\TOptionsFrame.cpp", OptionsFrame); /* TFrame: File Type */
USEFORM("src\gui\TOutputFileFrame.cpp", OutputFileFrame); /* TFrame: File Type */
USEFORM("src\gui\cct\TGammaMeasurementForm.cpp", GammaMeasurementForm);
USEFORM("src\gui\cct\TMainForm.cpp", MainForm);
USEFORM("src\gui\cct\TTargetWhiteForm2.cpp", TargetWhiteForm2);
USEFORM("src\gui\cct\TAboutBox.cpp", AboutBox);
USEFORM("src\gui\cct\TCCTLUTForm.cpp", CCTLUTForm);
USEFORM("src\gui\cct\TGammaAdjustmentForm.cpp", GammaAdjustmentForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try {
	Application->Initialize();
	Application->Title = "CCTv3 Adjustment";
	Application->CreateForm(__classid(TGammaMeasurementForm), &GammaMeasurementForm);
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TTargetWhiteForm2), &TargetWhiteForm2);
                 Application->CreateForm(__classid(TAboutBox), &AboutBox);
                 Application->CreateForm(__classid(TCCTLUTForm), &CCTLUTForm);
                 Application->CreateForm(__classid(TGammaAdjustmentForm), &GammaAdjustmentForm);
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
    return 0;
}

//---------------------------------------------------------------------------

