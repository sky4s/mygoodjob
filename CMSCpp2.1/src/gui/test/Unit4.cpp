//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ComObj.hpp"
#include "Unit4.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------


void __fastcall TForm4::Button1Click(TObject * Sender)
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

