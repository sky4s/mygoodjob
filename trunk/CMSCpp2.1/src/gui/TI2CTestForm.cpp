//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TI2CTestForm.h"
#include <cms/i2c/i2ccontrol.h>
//#include <cms/i2c/core/ReadWriteFunc.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TI2CTestForm *I2CTestForm;
//---------------------------------------------------------------------------
__fastcall TI2CTestForm::TI2CTestForm(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TI2CTestForm::Button1Click(TObject * Sender)
{
    using namespace cms::i2c;
    bptr < i2cControl > i2c1st;
    bptr < i2cControl > i2c2nd;
    unsigned char first, second;
    bool dual = false;

    if (this->RadioButton_Single->Checked) {
	first = StrToInt("0x" + this->Edit_Single->Text);
    } else {
	first = StrToInt("0x" + this->Edit_Master->Text);
	second = StrToInt("0x" + this->Edit_Slave->Text);
	dual = true;
    }

    if (this->RadioButton_USB->Checked) {
	i2c1st = i2cControl::getUSBInstance(first, _3_3V, _400KHz);
	if (dual) {
	    i2c2nd = i2cControl::getUSBInstance(second, _3_3V, _400KHz);
	};
    } else {
	i2c1st = i2cControl::getLPTInstance(first);
	if (dual) {
	    i2c2nd = i2cControl::getLPTInstance(second);
	};
    };
    bool connect = i2c1st->connect();
    i2c2nd->connect();
    this->CheckBox_Connecting->Checked = connect;
    //i2c1st->read()
    //i2cControl::
}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::FormCreate(TObject * Sender)
{
    //RW_Func rw;
    i2c = cms::i2c::i2cControl::getLPTInstance(0);
}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::Edit1Change(TObject * Sender)
{
/* TODO : */
}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::Edit2Change(TObject * Sender)
{
    Edit1Change(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::Edit3Change(TObject * Sender)
{
    Edit1Change(Sender);
}

//---------------------------------------------------------------------------


