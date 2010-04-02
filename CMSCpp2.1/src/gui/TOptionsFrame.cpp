//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TOptionsFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOptionsFrame *OptionsFrame;
//---------------------------------------------------------------------------
__fastcall TOptionsFrame::TOptionsFrame(TComponent* Owner)
        : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
