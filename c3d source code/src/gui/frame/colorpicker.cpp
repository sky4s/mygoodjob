//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "colorpicker.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TColorPickerFrame *ColorPickerFrame;
//---------------------------------------------------------------------------
__fastcall TColorPickerFrame::TColorPickerFrame(TComponent* Owner)
        : TFrame(Owner)
{
}
//---------------------------------------------------------------------------
