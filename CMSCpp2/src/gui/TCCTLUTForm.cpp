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



void __fastcall TCCTLUTForm::Button_BrowseDirClick(TObject * Sender)
{
    //this->OpenDialog1->Execute();
    AnsiString Dir = "C:\\Program Files\\";
    SelectDirectory("¿ï¾Ü¥Ø¿ý", "", Dir);
}

//---------------------------------------------------------------------------

void TCCTLUTForm::resetBitDepth()
{
    //this->RadioButton_In8->Checked = true;
    this->CheckBox_Gamma256->Checked = false;
    setBitDepthEnable(true, true, true, true, false);
};

void TCCTLUTForm::setBitDepthEnable(bool lut10, bool lut12, bool out6,
				    bool out8, bool out10)
{
    this->RadioButton_Lut10->Enabled = lut10;
    this->RadioButton_Lut12->Enabled = lut12;
    this->RadioButton_Out6->Enabled = out6;
    this->RadioButton_Out8->Enabled = out8;
    this->RadioButton_Out10->Enabled = out10;
};

void __fastcall TCCTLUTForm::RadioButton_In6Click(TObject * Sender)
{
    resetBitDepth();
    this->RadioButton_Lut10->Checked = true;
    this->RadioButton_Out6->Checked = true;
    setBitDepthEnable(true, false, true, false, false);
    this->Edit_StartLevel->Text = "252";
    this->ComboBox_LevelStep->Text = "4";
    this->CheckBox_AvoidNoise->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_In8Click(TObject * Sender)
{
    resetBitDepth();
    this->RadioButton_Out8->Checked = true;
    setBitDepthEnable(true, true, true, true, false);
    this->Edit_StartLevel->Text = "255";
    this->ComboBox_LevelStep->Text = "1";
    this->CheckBox_AvoidNoise->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_In10Click(TObject * Sender)
{
    this->CheckBox_Gamma256->Checked = true;
    this->RadioButton_Lut12->Checked = true;
    this->RadioButton_Out8->Checked = true;
    setBitDepthEnable(false, true, false, true, true);
    this->Edit_StartLevel->Text = "255";
    this->ComboBox_LevelStep->Text = "1";
    this->CheckBox_AvoidNoise->Checked = false;
    this->CheckBox_AvoidNoise->Enabled = false;
    this->CheckBox_Gamma256->Enabled = true;
}

//---------------------------------------------------------------------------



void __fastcall TCCTLUTForm::RadioButton_RBInterpClick(TObject * Sender)
{
    this->Edit_RBInterpUnder->Enabled = true;
    this->Edit_P1->Enabled = false;
    this->Edit_P2->Enabled = false;
}

//---------------------------------------------------------------------------

void __fastcall TCCTLUTForm::RadioButton_P1P2Click(TObject * Sender)
{
    this->Edit_RBInterpUnder->Enabled = false;
    this->Edit_P1->Enabled = true;
    this->Edit_P2->Enabled = true;
}

//---------------------------------------------------------------------------



