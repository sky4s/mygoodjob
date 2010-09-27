//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMainForm.h"
#include "Engineering.h"
#include "c3d1_dis_new.h"
#include "color_converter.h"
#include <iostream>
#include <conio.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TMainForm *MainForm;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
        : TForm(Owner)
{
        addr_place = 0;

}
//---------------------------------------------------------------------------


void __fastcall TMainForm::Engineering1Click(TObject *Sender)
{
        EngineerForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::c3d1Click(TObject *Sender)
{
        C3DForm1->Show();
}
//---------------------------------------------------------------------------

