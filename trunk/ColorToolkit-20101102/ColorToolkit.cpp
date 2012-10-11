//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("src\gui\frame\TColorPickerFrame.cpp", ColorPickerFrame); /* TFrame: File Type */
USEFORM("src\gui\frame\THSVAdjustFrame.cpp", HSVAdjustFrame); /* TFrame: File Type */
USEFORM("src\c3d\gui\TInTargetForm.cpp", InTargetForm);
USEFORM("src\gui\TDebugForm.cpp", DebugForm);
USEFORM("src\gui\TExampleForm.cpp", ExampleForm);
USEFORM("src\colorip\gui\C3D1.cpp", C3DForm1);
USEFORM("src\colorip\gui\CM1.cpp", CMForm1);
USEFORM("src\colorip\gui\ContrastEnhance1.cpp", ContrastEnhanceForm1);
USEFORM("src\colorip\gui\DCR1.cpp", DCRForm1);
USEFORM("src\colorip\gui\Engineering.cpp", EngineerForm);
USEFORM("src\colorip\gui\Function1.cpp", FunctionForm1);
USEFORM("src\colorip\gui\HueSatVal1.cpp", HSVFormOrg);
USEFORM("src\colorip\gui\offset.cpp", offsetForm);
USEFORM("src\colorip\gui\SAT.cpp", SATForm);
USEFORM("src\colorip\gui\Sharpness1.cpp", SharpnessForm1);
USEFORM("src\colorip\gui\Sharpness12307.cpp", SharpnessForm12307);
USEFORM("src\colorip\gui\TCON1.cpp", TCONForm1);
USEFORM("src\colorip\gui\Unit1.cpp", MainForm);
USEFORM("src\colorip\gui\TGamutForm.cpp", GamutSetupForm);
USEFORM("src\colorip\gui\TPatternForm.cpp", PatternForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try {
	Application->Initialize();
	Application->Title = "Color Engine Toolkit";
	Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TGamutSetupForm), &GamutSetupForm);
                 Application->CreateForm(__classid(TPatternForm), &PatternForm);
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

