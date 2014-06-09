//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("src\gui\measure\TPatternMeasureForm.cpp", PatternMeasureForm);
USEFORM("src\gui\TOutputFileFrame.cpp", OutputFileFrame); /* TFrame: File Type */
USEFORM("src\gui\TMeasureWindow.cpp", MeasureWindow);
USEFORM("src\gui\cct\TTargetWhiteForm2.cpp", TargetWhiteForm2);
USEFORM("src\gui\cct\TMainForm.cpp", MainForm);
USEFORM("src\gui\cct\TChangeLogForm.cpp", ChangeLogForm);
USEFORM("src\gui\cct\TStabilityForm.cpp", StabilityForm);
USEFORM("src\gui\cct\TGammaMeasurementForm.cpp", GammaMeasurementForm);
USEFORM("src\gui\cct\TAboutBox.cpp", AboutBox);
USEFORM("src\gui\TI2CTestForm.cpp", I2CTestForm);
USEFORM("src\gui\TMatrixCalibration.cpp", MatrixCalibrationForm);
USEFORM("src\gui\TCA210SettingFrame.cpp", CA210SettingFrame); /* TFrame: File Type */
USEFORM("src\gui\cct\TCCTLUTForm.cpp", CCTLUTForm);
USEFORM("src\gui\cct\TGammaAdjustmentForm.cpp", GammaAdjustmentForm);
USEFORM("src\gui\TOptionsFrame.cpp", OptionsFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "Pattern Measure";
                 Application->CreateForm(__classid(TPatternMeasureForm), &PatternMeasureForm);
                 Application->CreateForm(__classid(TMeasureWindow), &MeasureWindow);
                 Application->CreateForm(__classid(TTargetWhiteForm2), &TargetWhiteForm2);
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TChangeLogForm), &ChangeLogForm);
                 Application->CreateForm(__classid(TStabilityForm), &StabilityForm);
                 Application->CreateForm(__classid(TGammaMeasurementForm), &GammaMeasurementForm);
                 Application->CreateForm(__classid(TAboutBox), &AboutBox);
                 Application->CreateForm(__classid(TI2CTestForm), &I2CTestForm);
                 Application->CreateForm(__classid(TMatrixCalibrationForm), &MatrixCalibrationForm);
                 Application->CreateForm(__classid(TCCTLUTForm), &CCTLUTForm);
                 Application->CreateForm(__classid(TGammaAdjustmentForm), &GammaAdjustmentForm);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
