//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#define NO_PROMPT_ON_HRCHECK_FAILURE
#include <comobj.hpp>

//---------------------------------------------------------------------------
USEFORM("src\gui\TOutputFileFrame.cpp", OutputFileFrame); /* TFrame: File Type */
USEFORM("src\gui\3d\T3DMeasureWindow.cpp", ThreeDMeasureWindow);
USEFORM("src\gui\3d\T3DMeasurementForm.cpp", ThreeDMeasurementForm);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    try {
	Application->Initialize();
	Application->Title = "ODMeasurement.exe";
	Application->CreateForm(__classid(TThreeDMeasurementForm), &ThreeDMeasurementForm);
                 Application->CreateForm(__classid(TThreeDMeasureWindow), &ThreeDMeasureWindow);
                 Application->CreateForm(__classid(TOutputFileFrame), &OutputFileFrame);
                 Application->Run();
    }
    catch(EOleException & ex) {
	ShowMessage("CA210 cannot be linked.");
	//Application->Terminate();
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

