//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件
#include <FileCtrl.hpp>
//本項目內頭文件
#include "TOutputFileFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOutputFileFrame *OutputFileFrame;
//---------------------------------------------------------------------------
__fastcall TOutputFileFrame::TOutputFileFrame(TComponent * Owner)
:TFrame(Owner)
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
void TOutputFileFrame::createDir()
{
    AnsiString dir = this->Edit_Directory->Text;
    if (!DirectoryExists(dir)) {
	bool result = CreateDir(dir);
	if (!result) {
	    ShowMessage("Create " + dir + " is failed.");
	    return;
	}
    }
}

//---------------------------------------------------------------------------
AnsiString TOutputFileFrame::getFullPrefix()
{
    AnsiString dir = this->Edit_Directory->Text;
    AnsiString full = dir + "\\" + this->Edit_Prefix->Text;
    return full;
}
//---------------------------------------------------------------------------

