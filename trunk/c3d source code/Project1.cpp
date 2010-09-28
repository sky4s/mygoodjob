//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("src\gui\c3d\TC3DForm.cpp", C3DForm1);
USEFORM("src\gui\c3d\TC3D_SimualteForm.cpp", C3D_SimualteForm);
USEFORM("src\gui\c3d\TFormInTarget.cpp", FormInTarget);
USEFORM("src\gui\c3d\TEngineering.cpp", EngineerForm);
USEFORM("src\gui\c3d\TMainForm.cpp", MainForm);
USEFORM("src\gui\c3d\THSVStepSimForm.cpp", HSVStepSimForm);
USEFORM("src\gui\frame\colorpicker.cpp", ColorPickerFrame); /* TFrame: File Type */
USEFORM("src\gui\c3d\Unit2.cpp", Form2);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                  Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TForm2), &Form2);
                 Application->CreateForm(__classid(TC3DForm1), &C3DForm1);
                 Application->CreateForm(__classid(TC3D_SimualteForm), &C3D_SimualteForm);
                 Application->CreateForm(__classid(TFormInTarget), &FormInTarget);
                 Application->CreateForm(__classid(TEngineerForm), &EngineerForm);
                 Application->CreateForm(__classid(THSVStepSimForm), &HSVStepSimForm);
                 Application->CreateForm(__classid(TColorPickerFrame), &ColorPickerFrame);
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
