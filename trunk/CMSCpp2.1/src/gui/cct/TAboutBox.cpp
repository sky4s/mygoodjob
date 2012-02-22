//---------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件
//本項目內gui頭文件
#include "TAboutBox.h"

//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TAboutBox *AboutBox;
//--------------------------------------------------------------------- 
__fastcall TAboutBox::TAboutBox(TComponent * AOwner)
:TForm(AOwner)
{

}

//---------------------------------------------------------------------
void __fastcall TAboutBox::FormKeyPress(TObject * Sender, char &Key)
{
    if (Key == 27) {		//esc
	this->Close();
    }
}

//---------------------------------------------------------------------------

void __fastcall TAboutBox::FormCreate(TObject * Sender)
{
    using namespace cms::util;
    int_array version = Util::fetchVersionInfo();
    string build = " (build:" + _toString(version[2]) + "." + _toString(version[3]) + ")";
    Version->Caption = Version->Caption + build.c_str();
}

//---------------------------------------------------------------------------

