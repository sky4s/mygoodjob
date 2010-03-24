//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TAnalyzerFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAnalyzerFrame *AnalyzerFrame;
//---------------------------------------------------------------------------
__fastcall TAnalyzerFrame::TAnalyzerFrame(TComponent* Owner)
        : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
