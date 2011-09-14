//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件
#include <FileCtrl.hpp>
#pragma   link   "vclx.lib"
//本項目內頭文件
#include "TOutputFileFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOutputFileFrame *OutputFileFrame;
//---------------------------------------------------------------------------
__fastcall TOutputFileFrame::TOutputFileFrame(TComponent * Owner)
:TFrame(Owner), serialid(0)
{
    /*String_ptr filename = getOutputFilename();
       if (FileExists(*filename)) {
       String onlyfilename = ExtractFileName(*filename);
       this->Label_Warning->Caption = onlyfilename + " exists!";
       } */
}

//---------------------------------------------------------------------------
void __fastcall TOutputFileFrame::Button_BrowseDirClick(TObject * Sender)
{
    AnsiString Dir = this->Edit_Directory->Text;
    SelectDirectory("選擇目錄", "", Dir);
    this->Edit_Directory->Text = Dir + "\\";
}

//---------------------------------------------------------------------------
bool TOutputFileFrame::createDir()
{
    AnsiString dir = this->Edit_Directory->Text;
    if (!DirectoryExists(dir)) {
	bool result = CreateDir(dir);
	if (!result) {
	    ShowMessage("Create " + dir + " is failed.");
	    return false;
	}
    }
    return true;
}

//---------------------------------------------------------------------------
String_ptr TOutputFileFrame::getFullPrefix()
{
    String_ptr prefix(new AnsiString(this->Edit_Directory->Text + "\\" + this->Edit_Prefix->Text));
    return prefix;
}

//---------------------------------------------------------------------------
String_ptr TOutputFileFrame::getOutputFilename()
{

    String_ptr filename = _getOutputFilename();
    serialid++;
    updateWarning();
    return filename;
};
String_ptr TOutputFileFrame::_getOutputFilename()
{
    String_ptr output(new String(*getFullPrefix() + FormatFloat("00", serialid) + ".xls"));
    return output;
};
void TOutputFileFrame::updateWarning()
{
    String_ptr filename = _getOutputFilename();
    String s = *filename;

    if (FileExists(*filename)) {
	String onlyfilename = ExtractFileName(*filename);

	int handle = FileOpen(*filename, fmOpenWrite);
	bool lock = (-1 == handle);
	if (lock) {
	    this->Label_Warning->Font->Color = clRed;
	    this->Label_Warning->Caption = onlyfilename + " locked!";

	} else {
	    FileClose(handle);
	    this->Label_Warning->Font->Color = clGreen;
	    this->Label_Warning->Caption = onlyfilename + " exists!";
	}


    } else {
	this->Label_Warning->Caption = "";
    }

};

//---------------------------------------------------------------------------

void __fastcall TOutputFileFrame::Edit_PrefixChange(TObject * Sender)
{
    updateWarning();
}

//---------------------------------------------------------------------------

void __fastcall TOutputFileFrame::Edit_DirectoryChange(TObject * Sender)
{
    updateWarning();
}

//---------------------------------------------------------------------------


