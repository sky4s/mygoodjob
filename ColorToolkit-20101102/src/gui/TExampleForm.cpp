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



void __fastcall TExampleForm::FormActivate(TObject * Sender)
{
    // regframework.scanUI(this);
}

//---------------------------------------------------------------------------


void __fastcall TExampleForm::FormCreate(TObject * Sender)
{
    //regframework.scanUI(this);
    //regframework.bindComboBox("FPGA", 2, "AA", "BB");
}

//---------------------------------------------------------------------------
static int count = 0;
void __fastcall TExampleForm::StringGrid1SelectCell(TObject * Sender,
						    int ACol, int ARow, bool & CanSelect)
{
    Label5->Caption = _toString(count++).c_str();
}

//---------------------------------------------------------------------------

