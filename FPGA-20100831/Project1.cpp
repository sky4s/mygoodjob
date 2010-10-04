//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Unit1.cpp", MainForm);
USEFORM("Vender1.cpp", VenderForm1);
USEFORM("CM1.cpp", CMForm1);
USEFORM("HueSatVal1.cpp", HSVForm1);
USEFORM("Sharpness1.cpp", SharpnessForm1);
USEFORM("TCON1.cpp", TCONForm1);
USEFORM("Function1.cpp", FunctionForm1);
USEFORM("Engineering.cpp", EngineerForm);
USEFORM("DCR1.cpp", DCRForm1);
USEFORM("ContrastEnhance1.cpp", ContrastEnhanceForm1);
USEFORM("C3D1.cpp", C3DForm1);
USEFORM("SAT.cpp", SATForm);
USEFORM("offset.cpp", offsetForm);
USEFORM("HueSatVal2.cpp", HSVForm2);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TEngineerForm), &EngineerForm);
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








