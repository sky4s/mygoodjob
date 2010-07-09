//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <ComObj.hpp>

#include "Form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject * Sender)
{
    Variant EXCEL, WORKbooks, WORKbook, WORKsheets, WORKsheet, CELL;
    EXCEL = CreateOleObject("Excel.Application");
    EXCEL.OlePropertySet("Visible", true);
    WORKbooks = EXCEL.OlePropertyGet("Workbooks");
    WORKbook = WORKbooks.OleFunction("Add");
    WORKsheets = WORKbook.OlePropertyGet("Worksheets");
    WORKsheet = WORKsheets.OlePropertyGet("Item", 1);
    CELL = WORKsheet.OlePropertyGet("Cells", 1, 1);
    CELL.OlePropertySet("Value", "MY DATA");
}

//---------------------------------------------------------------------------

