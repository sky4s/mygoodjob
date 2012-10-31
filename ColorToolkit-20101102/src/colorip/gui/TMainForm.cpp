
#pragma hdrstop
#include "TMainForm.h"
//C系統文件                  

//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件
#include <addresstype/Address_type.h>
//本項目內gui頭文件

#include <colorip/gui/TSharpnessV2_1Form.h>
#include "include.h"
#include <iostream>
#include <fstream>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent * Owner):TForm(Owner)
{
    //Set Real-Time Priority of process
    SetPriorityClass(GetCurrentProcess(), REALTIME_PRIORITY_CLASS);
    //addr_place = 0;           //0:auo_12401_address.h   1:auo_12401_address.txt
    addressFromFile = false;
    C3D_type = 7;

    using namespace cms::util;
    if (Util::isFileExist("tcon.txt")) {
	setAddressFile("tcon.txt");
    }
    //if (Util::isFileExist("debug.txt")) {
    mn_Header2Address->Visible = true;
    //}


}

//---------------------------------------------------------------------------


void __fastcall TMainForm::mn_EngineerClick(TObject * Sender)
{
    //EngineerForm->action
    /*if (NULL == EngineerForm || !EngineerForm->Showing ) {
	EngineerForm = new TEngineerForm(this);
    }*/
    if (wsMinimized == EngineerForm->WindowState) {
	EngineerForm->WindowState = wsMaximized;
    }

    EngineerForm->Show();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_FunctionClick(TObject * Sender)
{
    if (NULL == FunctionForm || !FunctionForm->Showing) {
	FunctionForm = new TFunctionForm(this);

    }
    FunctionForm->Show();
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::FormClose(TObject * Sender, TCloseAction & Action)
{
    /*EngineerForm->FormClose(Sender, Action);

       if (FunctionForm != NULL) {
       FunctionForm->Close();
       FunctionForm = NULL;
       delete FunctionForm;
       }

       if (CMForm != NULL) {
       CMForm->Close();
       CMForm = NULL;
       delete CMForm;
       }
       if (SharpnessV1Form != NULL) {
       SharpnessV1Form->Close();
       SharpnessV1Form = NULL;
       delete SharpnessV1Form;
       }
       if (SharpnessV2Form != NULL) {
       SharpnessV2Form->Close();
       SharpnessV2Form = NULL;
       delete SharpnessV2Form;
       }
       if (CEForm != NULL) {
       CEForm->Close(); // mask by Michelle 20100716
       CEForm = NULL;
       delete CEForm;
       }
       if (HSVV1Form != NULL) {
       HSVV1Form->Close();
       HSVV1Form = NULL;
       delete HSVV1Form;
       }
       if (HSVV2Form != NULL) {
       HSVV2Form->Close();
       HSVV2Form = NULL;
       delete HSVV2Form;
       }
       if (C3DForm != NULL) {
       C3DForm->Close();        // mask by Michelle 20100716
       C3DForm = NULL;
       delete C3DForm;
       }
       if (SaturationForm != NULL) {
       SaturationForm->Close();
       SaturationForm = NULL;
       delete SaturationForm;
       }
       if (offsetForm != NULL) {
       offsetForm->Close();
       offsetForm = NULL;
       delete offsetForm;
       } */
}

//---------------------------------------------------------------------------
void TMainForm::closeAllForms()
{


    for (int i = MDIChildCount - 1; i >= 0; i--) {
	TForm *form = MDIChildren[i];
	if (form != EngineerForm) {
	    form->Close();
	}
    }

    /*if (FunctionForm != NULL) {
       FunctionForm->Close();
       FunctionForm = NULL;
       }

       if (CMForm != NULL) {
       CMForm->Close();
       CMForm = NULL;
       }
       if (SharpnessV1Form != NULL) {
       SharpnessV1Form->Close();
       SharpnessV1Form = NULL;
       }
       if (SharpnessV2Form != NULL) {
       SharpnessV2Form->Close();
       SharpnessV2Form = NULL;
       }
       if (HSVV1Form != NULL) {
       HSVV1Form->Close();
       HSVV1Form = NULL;
       }
       if (HSVV2Form != NULL) {
       HSVV2Form->Close();
       HSVV2Form = NULL;
       }
       if (C3DForm != NULL) {
       C3DForm->Close();
       C3DForm = NULL;
       }
       if (SaturationForm != NULL) {
       SaturationForm->Close();
       SaturationForm = NULL;
       }
       if (offsetForm != NULL) {
       offsetForm->Close();
       offsetForm = NULL;
       } */
}


void __fastcall TMainForm::FormCreate(TObject * Sender)
{

    //TCON_DEV = "11307";               //default device
    //String info = getFileVersionInfo();
    //MainForm->Caption = "AUO 11307";
    MainForm->Caption = "Color Engine Toolkit";
    mn_Function->Enabled = true;
    //mn_TCON->Enabled = true;
    //mn_DCR->Enabled = true;
    //mn_Vender->Enabled = true;
    using namespace cms::util;
    if (Util::isFileExist("rgbgain.txt")) {
	mn_ImageProc->Visible = false;
	mn_Test->Visible = false;
    } else {
	mn_ImageProc->Enabled = true;
    }
    mn_CM->Enabled = true;
    mn_Sharpness->Enabled = true;
    mn_Sharpness12307->Enabled = true;
    mn_CE->Enabled = true;	// mask by Michelle 20100716
    mn_HSV2->Enabled = true;
    mn_C3D->Enabled = true;
    mn_SAT->Enabled = true;
    mn_offset->Enabled = true;
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_CMClick(TObject * Sender)
{

    if (NULL == CMForm || !CMForm->Showing) {
	CMForm = new TCMForm(this);

    }
    CMForm->Show();


}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mn_SharpnessClick(TObject * Sender)
{

    if (NULL == SharpnessV1Form || !SharpnessV1Form->Showing) {
	SharpnessV1Form = new TSharpnessV1Form(this);
    }

    SharpnessV1Form->Show();

}

//---------------------------------------------------------------------------



 // remove by Michelle 20100716
void __fastcall TMainForm::mn_CEClick(TObject * Sender)
{

    if (NULL == CEForm || !CEForm->Showing) {
	CEForm = new TCEForm(this);
    }

    CEForm->Show();
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::StatusBar1DblClick(TObject * Sender)
{
    //cb_address_txt->Visible = true;
}

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
 //remove by Michelle 20100716
void __fastcall TMainForm::mn_C3DClick(TObject * Sender)
{

    if (NULL == C3DForm || !C3DForm->Showing) {
	C3DForm = new TC3DForm(this);
    }

    C3DForm->Show();

}

//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_C3D_777Click(TObject * Sender)
{
    C3D_type = 7;

    if (NULL == C3DForm || !C3DForm->Showing || C3DForm->Hint != C3D_type) {
	if (NULL != C3DForm && C3DForm->Showing) {
	    C3DForm->Close();
	}
	C3DForm = new TC3DForm(this);
    }

    C3DForm->Show();


    /*if (C3DForm != NULL) {
       if (C3DForm->Hint == C3D_type) {
       C3DForm->Show();
       return;
       } else
       C3DForm->Close();
       }

       C3DForm = new TC3DForm(this);
       C3DForm->Show(); */


}

//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_C3D_999Click(TObject * Sender)
{
    C3D_type = 9;

    if (NULL == C3DForm || !C3DForm->Showing || C3DForm->Hint != C3D_type) {
	if (NULL != C3DForm && C3DForm->Showing) {
	    C3DForm->Close();
	}
	C3DForm = new TC3DForm(this);
    }

    C3DForm->Show();


    /*if (C3DForm != NULL) {
       if (C3DForm->Hint == C3D_type) {
       C3DForm->Show();
       return;
       } else
       C3DForm->Close();
       }
       C3DForm = new TC3DForm(this);
       C3DForm->Show(); */

}

//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_SATClick(TObject * Sender)
{

    if (NULL == SaturationForm || !SaturationForm->Showing) {
	SaturationForm = new TSaturationForm(this);
    }

    SaturationForm->Show();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_offsetClick(TObject * Sender)
{


    if (NULL == offsetForm || !offsetForm->Showing) {
	offsetForm = new TOffsetForm(this);
    }

    offsetForm->Show();
}

//---------------------------------------------------------------------------
String TMainForm::getFileVersionInfo()
{

    DWORD dwVerInfoSize = 0;
    AnsiString szFile = Application->ExeName;
    dwVerInfoSize = GetFileVersionInfoSize(szFile.c_str(), &dwVerInfoSize);
    String caption;
    if (dwVerInfoSize > 0) {
	BYTE *bVerInfoBuf = new BYTE[dwVerInfoSize];
	if (GetFileVersionInfo(szFile.c_str(), 0, dwVerInfoSize, bVerInfoBuf)) {
	    VS_FIXEDFILEINFO *vsInfo;
	    UINT vsInfoSize;
	    if (VerQueryValue(bVerInfoBuf, "\\", (void **) &vsInfo, &vsInfoSize)) {
		int iFileVerMajor = HIWORD(vsInfo->dwFileVersionMS);
		int iFileVerMinor = LOWORD(vsInfo->dwFileVersionMS);
		int iFileVerRelease = HIWORD(vsInfo->dwFileVersionLS);
		int iFileVerBuild = LOWORD(vsInfo->dwFileVersionLS);
		caption = IntToStr(iFileVerMajor) + "."
		    + IntToStr(iFileVerMinor) + "."
		    + IntToStr(iFileVerRelease) + "." + IntToStr(iFileVerBuild);

	    }
	}
	delete bVerInfoBuf;
    }
    return caption;
}


void __fastcall TMainForm::mn_Header2AddressClick(TObject * Sender)
{
    using namespace std;
    OpenDialog1->Filter = "Header Files(*.h)|*.h";
    if (OpenDialog1->Execute()) {
	const AnsiString & header = OpenDialog1->FileName;
	SaveDialog1->Filter = "Address Files(*.txt)|*.txt";
	if (SaveDialog1->Execute()) {
	    const AnsiString & address = SaveDialog1->FileName;
	    header2AddressFile(header, address);
	    ShowMessage("Conversion done!");
	}
    };
}

//---------------------------------------------------------------------------
void TMainForm::header2AddressFile(const AnsiString & header, const AnsiString & address)
{
    using namespace std;
    using namespace cms::util;
    ifstream infile(header.c_str());
    ofstream outfile(address.c_str());

    if (infile.is_open() && outfile.is_open()) {
	string line;
	bool comment = false;
	while (infile.good() && outfile.good()) {
	    getline(infile, line);

	    if (comment || line.size() == 0) {
		if (-1 != line.find("*/", 0)) {
		    comment = false;
		}
		continue;
	    }
	    int beginCommentIndex = line.find("/*", 0);
	    int doubleSlashIndex = line.find("//", 1);
	    if (!comment && -1 != beginCommentIndex && -1 == doubleSlashIndex) {
		comment = true;
		continue;
	    }

	    if (-1 != doubleSlashIndex) {
		line = line.substr(0, doubleSlashIndex - 1);
	    }

	    string_vector_ptr stringvector = StringVector::tokenize(line, " \t");
	    int size = stringvector->size();
	    if (size == 0) {
		continue;
	    }
	    string first = (*stringvector)[0];

	    if ((size == 3 || size == 4) && first.find("#define") == 0) {
		string define = (*stringvector)[2];

		string sub = define.substr(1, define.size() - 2);
		size_t found = sub.find(",");
		if (found != string::npos) {
		    outfile << sub + '\n';
		}
	    }

	}
    }

    outfile.flush();
    outfile.close();
    infile.close();
}

void __fastcall TMainForm::mn_LoadAddressFromFileClick(TObject * Sender)
{
    using namespace std;
    ForceCurrentDirectory = true;
    OpenDialog1->Filter = "T-CON Address Files(*.*)|*.*";
    /*if (0 == OpenDialog1->InitialDir) {
       String appPath = ExtractFilePath(Application->ExeName);
       OpenDialog1->InitialDir = appPath;
       } */
    if (OpenDialog1->Execute()) {
	const AnsiString & header = OpenDialog1->FileName;
	setAddressFile(header);
    };
}

void TMainForm::setAddressFile(AnsiString filename)
{
    AddressFile = filename;
    AnsiString caption = ExtractFileName(filename);
    int dotIndex = caption.Pos(".");
    if (0 != dotIndex) {
	caption = caption.SubString(1, dotIndex - 1);
    }
    MainForm->Caption = caption;
    addressFromFile = true;
    mn_LoadAddressFromFile->Checked = true;
    AbstractIPBase::resetAddressMap();
    closeAllForms();
}

AnsiString TMainForm::AddressFile;


//---------------------------------------------------------------------------


void __fastcall TMainForm::mn_HSV2Click(TObject * Sender)
{

    if (NULL == HSVV2Form || !HSVV2Form->Showing) {
	HSVV2Form = new THSVV2Form(this);
    }

    HSVV2Form->Show();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_HSV1Click(TObject * Sender)
{


    if (NULL == HSVV1Form || !HSVV1Form->Showing) {
	HSVV1Form = new THSVV1Form(this);
    }

    HSVV1Form->Show();


}

//---------------------------------------------------------------------------


void __fastcall TMainForm::mn_Sharpness12307Click(TObject * Sender)
{


    if (NULL == SharpnessV2Form || !SharpnessV2Form->Showing) {
	SharpnessV2Form = new TSharpnessV2Form(this);
    }

    SharpnessV2Form->Show();
}

//---------------------------------------------------------------------------



void __fastcall TMainForm::mn_DebugClick(TObject * Sender)
{
    /*if (null == SharpnessForm12307_2) {
       SharpnessForm12307_2 = new TSharpnessForm12307_2(this);
       }
       SharpnessForm12307_2->Show(); */

    int count = MDIChildCount;
    for (int i = MDIChildCount - 1; i >= 0; i--) {
	//MDIChildren[i]->Close();
    }

}

//---------------------------------------------------------------------------

void __fastcall TMainForm::mn_Example2Click(TObject * Sender)
{


    if (NULL == ExampleForm || !ExampleForm->Showing) {
	ExampleForm = new TExampleForm(this);
    }

    ExampleForm->Show();

}

//---------------------------------------------------------------------------


void __fastcall TMainForm::Sharpnessv211Click(TObject * Sender)
{
    if (SharpnessV2_1Form != NULL) {
       SharpnessV2_1Form->Show();
       } else {
        SharpnessV2_1Form = new TSharpnessV2_1Form(this);
        SharpnessV2_1Form->Show();

    }
}

//---------------------------------------------------------------------------

