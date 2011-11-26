//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("src\gui\frame\TColorPickerFrame.cpp", ColorPickerFrame); /* TFrame: File Type */
USEFORM("src\gui\frame\THSVAdjustFrame.cpp", HSVAdjustFrame); /* TFrame: File Type */
USEFORM("src\fpga\gui\Unit1.cpp", MainForm);
USEFORM("src\fpga\gui\Vender1.cpp", VenderForm1);
USEFORM("src\fpga\gui\HueSatVal1.cpp", HSVFormOrg);
USEFORM("src\fpga\gui\Sharpness1.cpp", SharpnessForm1);
USEFORM("src\fpga\gui\TCON1.cpp", TCONForm1);
USEFORM("src\fpga\gui\Function1.cpp", FunctionForm1);
USEFORM("src\fpga\gui\Engineering.cpp", EngineerForm);
USEFORM("src\fpga\gui\DCR1.cpp", DCRForm1);
USEFORM("src\fpga\gui\ContrastEnhance1.cpp", ContrastEnhanceForm1);
USEFORM("src\fpga\gui\C3D1.cpp", C3DForm1);
USEFORM("src\fpga\gui\SAT.cpp", SATForm);
USEFORM("src\fpga\gui\offset.cpp", offsetForm);
USEFORM("src\c3d\gui\TInTargetForm.cpp", InTargetForm);
USEFORM("src\fpga\gui\TGamutForm.cpp", GamutSetupForm);
USEFORM("src\fpga\gui\TPatternForm.cpp", PatternForm);
USEFORM("src\fpga\gui\TPatternForm.cpp", PatternForm2);
USEFORM("src\fpga\gui\THSVForm2nd.cpp", HSVForm2nd);
USEFORM("src\fpga\gui\Sharpness12307.cpp", SharpnessForm12307);
USEFORM("src\fpga\gui\CM1.cpp", CMForm1);
USEFORM("src\gui\TDebugForm.cpp", DebugForm);
USEFORM("src\gui\TExampleForm.cpp", ExampleForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try {
	Application->Initialize();
	Application->Title = "Color Engine Toolkit";
	Application->CreateForm(__classid(TMainForm), &MainForm);
                 Application->CreateForm(__classid(TEngineerForm), &EngineerForm);
                 Application->CreateForm(__classid(TInTargetForm), &InTargetForm);
                 Application->CreateForm(__classid(TPatternForm), &PatternForm);
                 Application->CreateForm(__classid(TPatternForm), &PatternForm2);
                 Application->CreateForm(__classid(TDebugForm), &DebugForm);
                 Application->CreateForm(__classid(TExampleForm), &ExampleForm);
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

