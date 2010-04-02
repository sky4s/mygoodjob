//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TOutputFileFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TOutputFileFrame *OutputFileFrame;
//---------------------------------------------------------------------------
__fastcall TOutputFileFrame::TOutputFileFrame(TComponent* Owner)
        : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
