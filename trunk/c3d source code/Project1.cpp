//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("src\c3d\c3d1_dis_new.cpp", C3DForm1);
USEFORM("src\c3d\c3d_sim.cpp", C3D_SimualteForm);
USEFORM("src\c3d\color_converter.cpp", Form_in_target);
USEFORM("src\c3d\Engineering.cpp", EngineerForm);
USEFORM("src\c3d\Unit1.cpp", MainForm);
USEFORM("src\c3d\Unit2.cpp", Frame2); /* TFrame: File Type */
USEFORM("src\c3d\Unit3.cpp", Form3);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TForm_in_target), &Form_in_target);
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TForm3), &Form3);
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
