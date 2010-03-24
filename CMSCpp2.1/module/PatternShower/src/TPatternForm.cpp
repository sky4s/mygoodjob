//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TPatternForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPatternForm *PatternForm;
//---------------------------------------------------------------------------
__fastcall TPatternForm::TPatternForm(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TPatternForm::Button_ExitClick(TObject * Sender)
{
    this->Close();
}

//---------------------------------------------------------------------------

void __fastcall TPatternForm::FormDblClick(TObject * Sender)
{
    this->ToolBar1->Visible = !this->ToolBar1->Visible;
}

//---------------------------------------------------------------------------





void __fastcall TPatternForm::Button1Click(TObject * Sender)
{
    Types::TPoint PenPos = this->Canvas->PenPos;
    PenPos.x = 100;
    PenPos.y = 100;
    this->Canvas->Pixels[100][100] = clBlue;
}

//---------------------------------------------------------------------------

