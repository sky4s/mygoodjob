//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("src\c3d\c3d1_dis_new.cpp", C3DForm1);
USEFORM("src\c3d\c3d_sim.cpp", C3D_SimualteForm);
USEFORM("src\c3d\color_converter.cpp", Form_in_target);
USEFORM("src\c3d\Engineering.cpp", EngineerForm);
USEFORM("src\gui\c3d\TMainForm.cpp", MainForm);
USEFORM("src\c3d\Unit3.cpp", Form3);
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
                 Application->CreateForm(__classid(TForm_in_target), &Form_in_target);
                 Application->CreateForm(__classid(TEngineerForm), &EngineerForm);
                 Application->CreateForm(__classid(TForm3), &Form3);
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
