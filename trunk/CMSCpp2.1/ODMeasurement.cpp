//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("src\Unit3.cpp", Form3);
USEFORM("src\gui\T3DMeasurementForm.cpp", ThreeDMeasurementForm);
USEFORM("src\gui\T3DMeasureWindow.cpp", ThreeDMeasureWindow);
USEFORM("src\gui\TOutputFileFrame.cpp", OutputFileFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->Title = "OD Measurement";
                 Application->CreateForm(__classid(TThreeDMeasurementForm), &ThreeDMeasurementForm);
                 Application->CreateForm(__classid(TThreeDMeasureWindow), &ThreeDMeasureWindow);
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
