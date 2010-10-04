//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("src\gui\c3d\TC3DForm.cpp", C3DForm1);
USEFORM("src\gui\c3d\TC3D_SimualteForm.cpp", C3DSimualteForm);
USEFORM("src\gui\c3d\TInTargetForm.cpp", InTargetForm);
USEFORM("src\gui\c3d\TEngineering.cpp", EngineerForm);
USEFORM("src\gui\c3d\TMainForm.cpp", MainForm);
USEFORM("src\gui\c3d\THSVStepSimForm.cpp", HSVStepSimForm);
USEFORM("src\gui\frame\TColorPickerFrame.cpp", ColorPickerFrame); /* TFrame: File Type */
USEFORM("src\gui\c3d\TTestForm.cpp", TestForm2);
USEFORM("src\gui\frame\TColorFrame.cpp", PointColorFrame); /* TFrame: File Type */
USEFORM("src\gui\frame\THSVAdjustFrame.cpp", HSVAdjustFrame); /* TFrame: File Type */
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try {
	Application->Initialize();
	Application->CreateForm(__classid(TTestForm2), &TestForm2);
                 Application->Run();
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

