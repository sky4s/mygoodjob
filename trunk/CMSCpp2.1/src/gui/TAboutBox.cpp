//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

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

