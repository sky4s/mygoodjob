//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "_MeasureWindow.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMeasureWindow *MeasureWindow;
//---------------------------------------------------------------------------
__fastcall TMeasureWindow::TMeasureWindow(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
