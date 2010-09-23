//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Table_Step_Form.h"
//#include "c3d1.cpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm4 *Form4;
//---------------------------------------------------------------------------
__fastcall TForm4::TForm4(TComponent* Owner)
        : TForm(Owner)
{
        for(int i = 0; i < 9; i++){
                sg_table_step->Cells[i][0]=i+1;
                sg_table_step->Cells[i][1]=tbl_val[0][i];
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm4::sg_table_stepKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        for(int i = 0; i < 9; i++){
                tbl_val[0][i] = StrToInt(sg_table_step->Cells[i][1]);
        }

}
//---------------------------------------------------------------------------
void __fastcall TForm4::btn_set_new_table_stepClick(TObject *Sender)
{
        C3DForm1->C3Dini();
}
//---------------------------------------------------------------------------
