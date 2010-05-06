//---------------------------------------------------------------------------

#include <includeall.h>
#pragma hdrstop

#include "TI2CTestForm.h"
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

const i2c::AddressingSize TI2CTestForm::getAddressingSize()
{
    using namespace i2c;
    int index = this->ComboBox_AddressingSize->ItemIndex;
    switch (index) {
    case 0:
	return _2k;
    case 1:
	return _4k;
    case 2:
	return _8k;
    case 3:
	return _16k;
    case 4:
	return _32k;
    case 5:
	return _64k;
    case 6:
	return _128k;
    case 7:
	return _256k;
    case 8:
	return _512k;

    }
}

void TI2CTestForm::setOptionsEditable(bool editable)
{
    this->CheckBox_Connecting->Checked = !editable;
    this->CheckBox_Connecting->Enabled = !editable;
    this->Edit_GammaTestAddress->Enabled = editable;
    this->Edit_GammaTestBit->Enabled = editable;
    this->Edit_TestRGBAdress->Enabled = editable;
    this->ComboBox_AddressingSize->Enabled = editable;
    this->CheckBox_IndepRGB->Enabled = editable;
};

void __fastcall TI2CTestForm::Button1Click(TObject * Sender)
{
    using namespace i2c;
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
    //int dataAddressLength = this->CheckBox_2ByteAddress->Checked ? 2 : 1;
    AddressingSize addressingSize = getAddressingSize();

    if (this->RadioButton_USB->Checked) {
	i2c1st =
	    i2cControl::getUSBInstance(first, addressingSize, _3_3V,
				       _400KHz);
	if (dual) {
	    i2c2nd =
		i2cControl::getUSBInstance(second, addressingSize,
					   _3_3V, _400KHz);
	};
    } else {

	const LPTCard card =
	    this->RadioButton_LPTLarge->Checked ? Large : Small;

	i2c1st = i2cControl::getLPTInstance(first, addressingSize, card);
	if (dual) {
	    i2c2nd =
		i2cControl::getLPTInstance(second, addressingSize, card);
	};
    };
    bool connect = i2c1st->connect();
    if (dual) {
	i2c2nd->connect();
    }
    //connect = true;
    if (true == connect) {
	setOptionsEditable(false);

	int gammaTestAddress =
	    StrToInt("0x" + this->Edit_GammaTestAddress->Text);
	int gammaTestBit = StrToInt(this->Edit_GammaTestBit->Text);
	int testRGBAddress =
	    StrToInt("0x" + this->Edit_TestRGBAdress->Text);
	bool indepRGB = this->CheckBox_IndepRGB->Checked;
    }
}

//---------------------------------------------------------------------------
void __fastcall TI2CTestForm::CheckBox_ConnectingClick(TObject * Sender)
{
    if (false == this->CheckBox_Connecting->Checked) {
	setOptionsEditable(true);
	/*this->Edit_GammaTestAddress->Enabled = true;
	   this->Edit_GammaTestBit->Enabled = true;
	   this->Edit_TestRGBAdress->Enabled = true;
	   this->CheckBox_IndepRGB->Enabled = true;
	   this->CheckBox_Connecting->Enabled = false; */
    }
}

//---------------------------------------------------------------------------
void __fastcall TI2CTestForm::CheckBox1Click(TObject * Sender)
{
    if (true == this->CheckBox_Connecting->Checked) {
	bool enable = this->CheckBox1->Checked;
	Edit_RChange(Sender);
	control->setGammaTest(enable);
    }
}

//---------------------------------------------------------------------------
void __fastcall TI2CTestForm::Edit_RChange(TObject * Sender)
{
    using namespace Dep;
    bool doing = Edit_R->Text.Length() != 0 && Edit_G->Text.Length() != 0
	&& Edit_B->Text.Length() != 0;
    if (true == this->CheckBox_Connecting->Checked && doing) {
	try {
	    int r = StrToInt(this->Edit_R->Text);
	    int g = StrToInt(this->Edit_G->Text);
	    int b = StrToInt(this->Edit_B->Text);

	    double_array rgbValues(new double[3]);
	    rgbValues[0] = r;
	    rgbValues[1] = g;
	    rgbValues[2] = b;
	    RGB_ptr rgb(new
			RGBColor(RGBColorSpace::unknowRGB, rgbValues,
				 MaxValue::Int12Bit));
	    control->setTestRGB(rgb);
	} catch(EConvertError & ex) {
	    Application->ShowException(&ex);
	}
    }

}

//---------------------------------------------------------------------------
void __fastcall TI2CTestForm::Edit_GChange(TObject * Sender)
{
    Edit_RChange(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TI2CTestForm::Edit_BChange(TObject * Sender)
{
    Edit_RChange(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::Button_ReadClick(TObject * Sender)
{
    if (true == this->CheckBox_Connecting->Checked) {
	int address = StrToInt("0x" + this->Edit_Address->Text);
	const unsigned char data = control->readByte(address);
	this->Edit_ReadData->Text = IntToStr(data);
    }
}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::Button_WriteClick(TObject * Sender)
{
    if (true == this->CheckBox_Connecting->Checked
	&& this->Edit_WriteData->Text.Length() != 0) {
	int address = StrToInt("0x" + this->Edit_Address->Text);
	const unsigned int data =
	    static_cast <
	    const unsigned int >(StrToInt(this->Edit_WriteData->Text));
	control->writeByte(address, data);
    }
}

//---------------------------------------------------------------------------


