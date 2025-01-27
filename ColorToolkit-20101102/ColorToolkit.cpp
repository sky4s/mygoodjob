//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("src\gui\frame\TColorPickerFrame.cpp", ColorPickerFrame); /* TFrame: File Type */
USEFORM("src\gui\frame\THSVAdjustFrame.cpp", HSVAdjustFrame); /* TFrame: File Type */
USEFORM("src\gui\TDebugForm.cpp", DebugForm);
USEFORM("src\gui\TExampleForm.cpp", ExampleForm);
USEFORM("src\colorip\gui\TC3DForm.cpp", C3DForm);
USEFORM("src\colorip\gui\TCMForm.cpp", CMForm);
USEFORM("src\colorip\gui\TCEForm.cpp", CEForm);
USEFORM("src\colorip\gui\TEngineerForm.cpp", EngineerForm);
USEFORM("src\colorip\gui\TFunctionForm.cpp", FunctionForm);
USEFORM("src\colorip\gui\THSVV1Form.cpp", HSVV1Form);
USEFORM("src\colorip\gui\TOffsetForm.cpp", OffsetForm);
USEFORM("src\colorip\gui\TSaturationForm.cpp", SaturationForm);
USEFORM("src\colorip\gui\TSharpnessV1Form.cpp", SharpnessV1Form);
USEFORM("src\colorip\gui\TSharpnessV2Form.cpp", SharpnessV2Form);
USEFORM("src\colorip\gui\TMainForm.cpp", MainForm);
USEFORM("src\colorip\gui\TGamutForm.cpp", GamutSetupForm);
USEFORM("src\colorip\gui\TPatternForm.cpp", PatternForm);
USEFORM("src\colorip\gui\THSVV2Form.cpp", HSVV2Form);
USEFORM("src\colorip\gui\TSharpnessV2_1Form.cpp", SharpnessV2_1Form);
USEFORM("src\gui\util\TInTargetForm.cpp", InTargetForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try {
	Application->Initialize();
	Application->Title = "Color Engine Toolkit";
	Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TEngineerForm), &EngineerForm);
                 Application->CreateForm(__classid(TInTargetForm), &InTargetForm);
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

