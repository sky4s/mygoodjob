//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("src\Unit1.cpp", Form1);
USEFORM("src\gui\TMeasureWindow.cpp", MeasureWindow);
USEFORM("src\gui\TMainForm.cpp", MainForm);
USEFORM("src\gui\TCCTLUTForm.cpp", CCTLUTForm);
USEFORM("src\gui\TAnalyzerFrame.cpp", AnalyzerFrame); /* TFrame: File Type */
USEFORM("src\gui\TAboutBox.cpp", AboutBox);
USEFORM("src\gui\TTargetWhiteForm2.cpp", TargetWhiteForm2);
USEFORM("src\gui\TI2CTestForm.cpp", I2CTestForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "CCTv3 Adjustment";
                 Application->CreateForm(__classid(TI2CTestForm), &I2CTestForm);
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TMeasureWindow), &MeasureWindow);
                 Application->CreateForm(__classid(TCCTLUTForm), &CCTLUTForm);
                 Application->CreateForm(__classid(TAboutBox), &AboutBox);
                 Application->CreateForm(__classid(TTargetWhiteForm2), &TargetWhiteForm2);
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
