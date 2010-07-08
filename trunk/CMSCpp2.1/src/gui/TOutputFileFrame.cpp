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
    String_ptr
	prefix(new AnsiString(this->Edit_Directory->Text + "\\" +
			      this->Edit_Prefix->Text));
    return prefix;
}

//---------------------------------------------------------------------------
String_ptr TOutputFileFrame::getOutputFilename()
{
    String_ptr output(new
		      String(*getFullPrefix() +
			     FormatFloat("00", serialid++) + ".xls"));
    return output;
};

