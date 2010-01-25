//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMeasureWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMeasureWindow *MeasureWindow;
//---------------------------------------------------------------------------
__fastcall TMeasureWindow::TMeasureWindow(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TMeasureWindow::FormKeyPress(TObject * Sender, char &Key)
{
    if (Key == 27) {
	this->Close();
    }
}

//---------------------------------------------------------------------------


void TMeasureWindow::setRGB(int r, int g, int b)
{
    int color = (b << 16) + (g << 8) + r;
    this->Color = color;
}

void __fastcall TMeasureWindow::FormCreate(TObject * Sender)
{
    //this->setRGB(255, 0, 0);
}

//---------------------------------------------------------------------------

