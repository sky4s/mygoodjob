//---------------------------------------------------------------------
#include <includeall.h>
#pragma hdrstop

//C�t�Τ��

//C++�t�Τ��

//vcl�w�Y���

//��L�w�Y���

//�����ؤ��Y���
//�����ؤ�gui�Y���
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

