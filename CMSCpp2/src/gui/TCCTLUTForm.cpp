//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TCCTLUTForm.h"
#include <FileCtrl.hpp>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TCCTLUTForm *CCTLUTForm;
//---------------------------------------------------------------------------
__fastcall TCCTLUTForm::TCCTLUTForm(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioGroup_inClick(TObject * Sender)
{
    checkAvailable();
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioGroup_outClick(TObject * Sender)
{
    checkAvailable();
}
bool TCCTLUTForm::checkAvailable(int in, int lut, int out)
{
    bool case66 = in == 0 && lut == 0 && out == 0;
    bool case86 = in == 1 && lut == 0 && out == 0;
    bool case88 = in == 1 && out == 1;
    bool case108 = in == 2 && lut == 1 && out == 1;
    bool case1010 = in == 2 && lut == 1 && out == 2;
    return case66 || case86 || case88 || case108 || case1010;
}

void TCCTLUTForm::checkAvailable()
{
    bool available = checkAvailable(this->RadioGroup_in->ItemIndex,
				    this->RadioGroup_lut->ItemIndex,
				    this->RadioGroup_out->ItemIndex);

    this->Edit_available->Text = available ? "available" : "unavailable";
    this->Edit_available->Font->Color = available ? clLime : clRed;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioGroup_lutClick(TObject * Sender)
{
    checkAvailable();
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::FormCreate(TObject * Sender)
{
    this->RadioGroup_in->ItemIndex = 1;
    this->RadioGroup_lut->ItemIndex = 1;
    this->RadioGroup_out->ItemIndex = 1;
}

//---------------------------------------------------------------------------




void __fastcall TCCTLUTForm::Button2Click(TObject * Sender)
{
    //this->OpenDialog1->Execute();
    AnsiString Dir = "C:\\Program Files\\";
    SelectDirectory("¿ï¾Ü¥Ø¿ý", "", Dir);
}

//---------------------------------------------------------------------------

