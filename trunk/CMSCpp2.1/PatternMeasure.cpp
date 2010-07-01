//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("src\gui\measure\TPatternMeasureForm.cpp", PatternMeasureForm);
USEFORM("src\gui\TOutputFileFrame.cpp", OutputFileFrame); /* TFrame: File Type */
USEFORM("src\gui\TMeasureWindow.cpp", MeasureWindow);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TPatternMeasureForm), &PatternMeasureForm);
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
