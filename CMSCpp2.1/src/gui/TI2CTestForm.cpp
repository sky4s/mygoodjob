//---------------------------------------------------------------------------

#include <includeall.h>
#pragma hdrstop

#include "TI2CTestForm.h"
#include "TMainForm.h"
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

/*const i2c::AddressingSize TI2CTestForm::getAddressingSize()
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
    default:
	throw java::lang::IllegalArgumentException("Unsupported AddressingSize.");
    }
}*/

void TI2CTestForm::setOptionsEditable(bool editable)
{

};

void __fastcall TI2CTestForm::Button1Click(TObject * Sender)
{
    MainForm->Button_ConnectClick(Sender);
    control = MainForm->getTCONControl();

}

//---------------------------------------------------------------------------
void __fastcall TI2CTestForm::CheckBox1Click(TObject * Sender)
{
if(null==control) {
return;
}
    //if (true == this->CheckBox_Connecting->Checked) {
	bool enable = this->CheckBox1->Checked;
	Edit_RChange(Sender);
	control->setGammaTest(enable);
    //}
}

//---------------------------------------------------------------------------
void __fastcall TI2CTestForm::Edit_RChange(TObject * Sender)
{
    using namespace Dep;
    bool doing = Edit_R->Text.Length() != 0 && Edit_G->Text.Length() != 0
	&& Edit_B->Text.Length() != 0 && true == CheckBox1->Checked
	/*&& true == this->CheckBox_Connecting->Checked*/;
    if (doing) {
	try {
	    int r = StrToInt(this->Edit_R->Text);
	    int g = StrToInt(this->Edit_G->Text);
	    int b = StrToInt(this->Edit_B->Text);

	    double_array rgbValues(new double[3]);
	    rgbValues[0] = r;
	    rgbValues[1] = g;
	    rgbValues[2] = b;
	    RGB_ptr rgb(new RGBColor(RGBColorSpace::unknowRGB, rgbValues, MaxValue::Int12Bit));
	    bool result = control->setDirectGammaRGB(rgb);
	    if (false == result) {
		ShowMessage("Set Gamma Test failed!");
	    }
	}
	catch(EConvertError & ex) {
	    Application->ShowException(&ex);
	}
    }

}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::Button_ReadClick(TObject * Sender)
{
    //if (true == this->CheckBox_Connecting->Checked) {
	int address = StrToInt("0x" + this->Edit_Address->Text);
	const unsigned char data = control->readByte(address);
	this->Edit_ReadData->Text = IntToHex(data, 2);
    //}
}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::Button_WriteClick(TObject * Sender)
{
    if (/*true == this->CheckBox_Connecting->Checked &&*/ this->Edit_WriteData->Text.Length() != 0) {
	int address = StrToInt("0x" + this->Edit_Address->Text);
	const unsigned int data =
	    static_cast < const unsigned int >(StrToInt(this->Edit_WriteData->Text));
	control->writeByte(address, data);
    }
}

//---------------------------------------------------------------------------


void __fastcall TI2CTestForm::FormDeactivate(TObject * Sender)
{

    MainForm->RadioButton_LPTLarge->Checked = this->RadioButton_LPTLarge->Checked;
    MainForm->RadioButton_LPTSmall->Checked = this->RadioButton_LPTSmall->Checked;
    MainForm->RadioButton_USB->Checked = this->RadioButton_USB->Checked;
    MainForm->RadioButton_SingleTCON->Checked = this->RadioButton_Single->Checked;
    MainForm->RadioButton_DualTCON->Checked = this->RadioButton_Dual->Checked;

}

//---------------------------------------------------------------------------


void __fastcall TI2CTestForm::CheckBox_DGClick(TObject * Sender)
{
if(null==control) {
return;
}
    bool enable = this->CheckBox_DG->Checked;
    control->setDG(enable);
}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::CheckBox_DGTestClick(TObject * Sender)
{
if(null==control) {
return;
}
    using namespace cms::util;
    bool test = this->CheckBox_DGTest->Checked;
    if (test) {
	control->setDG(false);
	RGB_vector_ptr rgbVector = RGBVector::getLinearRGBVector(bitDepth->getLevelInTCon());
	rgbVector = RGBVector::reverse(rgbVector);
	control->setDGLut(rgbVector);
    }
    CheckBox_DG->Checked = test;

}

//---------------------------------------------------------------------------
void TI2CTestForm::setBitDepthProcessor(bptr < cms::lcd::BitDepthProcessor > bitDepth)
{
    this->bitDepth = bitDepth;
}


void __fastcall TI2CTestForm::Edit_WKeyDown(TObject * Sender, WORD & Key, TShiftState Shift)
{
    bool down = Key == 0x28;
    bool up = Key == 0x26;


    if (down || up) {
	TEdit *edit = dynamic_cast < TEdit * >(Sender);
	int dg = edit->Text.ToInt();
	dg = down ? dg - 1 : dg + 1;
	dg = (dg < 0) ? 0 : dg;
	edit->Text = dg;
    }
}

//---------------------------------------------------------------------------


void __fastcall TI2CTestForm::Edit_WChange(TObject * Sender)
{
    String w = Edit_W->Text;
    Edit_R->Text = w;
    Edit_G->Text = w;
    Edit_B->Text = w;
}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::Edit_RKeyDown(TObject * Sender, WORD & Key, TShiftState Shift)
{
    bool down = Key == 0x28;
    bool up = Key == 0x26;


    if (down || up) {
	TEdit *edit = dynamic_cast < TEdit * >(Sender);
	int dg = edit->Text.ToInt();
	dg = down ? dg - 1 : dg + 1;
	dg = (dg < 0) ? 0 : dg;
	edit->Text = dg;
    }

}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::CheckBox_FRCClick(TObject *Sender)
{
if(null==control) {
return;
}
    bool enable = this->CheckBox_FRC->Checked;
    control->setFRC(enable);
}
//---------------------------------------------------------------------------


