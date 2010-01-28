//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("src\gui\Unit1.cpp", Form1);
USEFORM("src\gui\TAboutBox.cpp", AboutBox);
USEFORM("src\gui\TMainForm.cpp", MainForm);
USEFORM("src\gui\TTargetWhiteForm.cpp", TargetWhiteForm);
USEFORM("src\gui\TMeasureWindow.cpp", MeasureWindow);
USEFORM("src\gui\TTargetWhiteForm2.cpp", TargetWhiteForm2);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TTargetWhiteForm2), &TargetWhiteForm2);
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TForm1), &Form1);
                 Application->CreateForm(__classid(TAboutBox), &AboutBox);
                 Application->CreateForm(__classid(TTargetWhiteForm), &TargetWhiteForm);
                 Application->CreateForm(__classid(TMeasureWindow), &MeasureWindow);
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
