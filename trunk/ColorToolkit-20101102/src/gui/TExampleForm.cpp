//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TExampleForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TExampleForm *ExampleForm;
//---------------------------------------------------------------------------
__fastcall TExampleForm::TExampleForm(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------


void __fastcall TExampleForm::ScrollBar1Change(TObject * Sender)
{
    regframework.active(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TExampleForm::FormActivate(TObject * Sender)
{
    regframework.scanUI(this);
}

//---------------------------------------------------------------------------

