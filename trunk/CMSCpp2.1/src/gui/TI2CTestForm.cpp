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
    //this->CheckBox_Connecting->Checked = !editable;
    //this->CheckBox_Connecting->Enabled = !editable;
    this->Edit_GammaTestAddress->Enabled = editable;
    this->Edit_GammaTestBit->Enabled = editable;
    this->Edit_TestRGBAdress->Enabled = editable;
    this->ComboBox_AddressingSize->Enabled = editable;
    //this->CheckBox_IndepRGB->Enabled = editable;
};

void __fastcall TI2CTestForm::Button1Click(TObject * Sender)
{
    MainForm->Button_ConnectClick(Sender);
    control = MainForm->getTCONControl();
    /*using namespace i2c;
       using namespace Dep;
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
       AddressingSize addressingSize = getAddressingSize();

       if (this->RadioButton_USB->Checked) {

       i2c1st = i2cControl::getUSBInstance(first, addressingSize, _3_3V, _400KHz);
       if (dual) {
       i2c2nd = i2cControl::getUSBInstance(second, addressingSize, _3_3V, _400KHz);
       };
       } else {

       const LPTCard card = this->RadioButton_LPTLarge->Checked ? Large : Small;

       i2c1st = i2cControl::getLPTInstance(first, addressingSize, card);
       if (dual) {
       i2c2nd = i2cControl::getLPTInstance(second, addressingSize, card);
       };
       };
       try {
       bool connect = i2c1st->connect();
       if (dual) {
       i2c2nd->connect();
       }
       if (true == connect) {
       setOptionsEditable(false);

       int dgEnableAddress = StrToInt("0x" + MainForm->Edit_DGEnableAddress->Text);
       int dgEnableBit = MainForm->Edit_DGEnableBit->Text.ToInt();
       int dgLUTAddress = StrToInt("0x" + MainForm->Edit_DGLUTAddress->Text);
       int dgLUTType = MainForm->ComboBox_DGLUTType->Text.ToInt();

       int gammaTestAddress = StrToInt("0x" + this->Edit_GammaTestAddress->Text);
       int gammaTestBit = StrToInt(this->Edit_GammaTestBit->Text);
       int testRGBAddress = StrToInt("0x" + this->Edit_TestRGBAdress->Text);
       bool indepRGB = CheckBox_IndepRGB->Checked;
       const TestRGBBit & testRGBBit =
       indepRGB ? TestRGBBit::IndependentInstance : TestRGBBit::DependentInstance;


       parameter =
       bptr < TCONParameter >
       (new
       TCONParameter(dgLUTType == 10 ? MaxValue::Int10Bit : MaxValue::Int12Bit,
       dgLUTAddress, dgEnableAddress, dgEnableBit, gammaTestAddress,
       gammaTestBit, testRGBAddress, testRGBBit));


       if (!dual) {
       control = bptr < TCONControl > (new TCONControl(parameter, i2c1st));
       } else {
       control = bptr < TCONControl > (new TCONControl(parameter, i2c1st, i2c2nd));
       }
       }


       }
       catch(java::lang::RuntimeException & ex) {
       ShowMessage("I2C link error!");
       } */
}

//---------------------------------------------------------------------------
void __fastcall TI2CTestForm::CheckBox_ConnectingClick(TObject * Sender)
{
    //if (false == this->CheckBox_Connecting->Checked) {
	//setOptionsEditable(true);
	/*this->Edit_GammaTestAddress->Enabled = true;
	   this->Edit_GammaTestBit->Enabled = true;
	   this->Edit_TestRGBAdress->Enabled = true;
	   this->CheckBox_IndepRGB->Enabled = true;
	   this->CheckBox_Connecting->Enabled = false; */
    //}
}

//---------------------------------------------------------------------------
void __fastcall TI2CTestForm::CheckBox1Click(TObject * Sender)
{
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
	    bool result = control->setGammaTestRGB(rgb);
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
    MainForm->Edit_GammaTestEnableAddress->Text = this->Edit_GammaTestAddress->Text;
    MainForm->Edit_GammaTestEnableBit->Text = this->Edit_GammaTestBit->Text;
    MainForm->Edit_GammaTestAddress->Text = this->Edit_TestRGBAdress->Text;
    MainForm->ComboBox_AddressingSize->ItemIndex = this->ComboBox_AddressingSize->ItemIndex;
    MainForm->RadioButton_LPTLarge->Checked = this->RadioButton_LPTLarge->Checked;
    MainForm->RadioButton_LPTSmall->Checked = this->RadioButton_LPTSmall->Checked;
    MainForm->RadioButton_USB->Checked = this->RadioButton_USB->Checked;
    MainForm->RadioButton_SingleTCON->Checked = this->RadioButton_Single->Checked;
    MainForm->RadioButton_DualTCON->Checked = this->RadioButton_Dual->Checked;

    //MainForm->ComboBox_GammaTestType->ItemIndex = this->CheckBox_IndepRGB->Checked ? 0 : 1;
    MainForm->ComboBox_GammaTestTypeChange(this);
}

//---------------------------------------------------------------------------


void __fastcall TI2CTestForm::CheckBox_DGClick(TObject * Sender)
{
    bool enable = this->CheckBox_DG->Checked;
    control->setDG(enable);
}

//---------------------------------------------------------------------------

void __fastcall TI2CTestForm::CheckBox_DGTestClick(TObject * Sender)
{
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

