//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TGamutForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGamutSetupForm *GamutSetupForm;
//---------------------------------------------------------------------------
__fastcall TGamutSetupForm::TGamutSetupForm(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TGamutSetupForm::CheckBox_sRGBClick(TObject * Sender)
{
    bool checked = CheckBox_sRGB->Checked;

    if (checked) {
	Edit_TargetRx->Text = "0.64";
	Edit_TargetRy->Text = "0.33";
	Edit_TargetGx->Text = "0.30";
	Edit_TargetGy->Text = "0.60";
	Edit_TargetBx->Text = "0.15";
	Edit_TargetBy->Text = "0.06";
	Edit_TargetGamma->Text = "2.2";
    }

    bool luminanceOk = Edit_SourceRLv->Text.Length() != 0 && Edit_SourceGLv->Text.Length() != 0
	&& Edit_SourceBLv->Text.Length() != 0;
    if (luminanceOk) {
	double sourceRY = Edit_SourceRLv->Text.ToDouble();
	double sourceGY = Edit_SourceGLv->Text.ToDouble();
	double sourceBY = Edit_SourceBLv->Text.ToDouble();
	double sourceY = sourceRY + sourceGY + sourceBY;
	double targetRY = sourceY * 0.212656;
	double targetGY = sourceY * 0.715158;
	double targetBY = sourceY * 0.072186;
	Edit_TargetRLv->Text = targetRY;
	Edit_TargetGLv->Text = targetGY;
	Edit_TargetBLv->Text = targetBY;
    }
}

//---------------------------------------------------------------------------

void __fastcall TGamutSetupForm::Button_SetupClick(TObject * Sender)
{
    this->Visible = false;

    bool allEditOk = true;
    int size = GroupBox1->ControlCount;
    //int size = GroupBox1->ComponentCount;
    for (int x = 0; x < size; x++) {
	TControl *c = GroupBox1->Controls[x];
	//TComponent *c = GroupBox1->Components[x];
	TEdit *edit = dynamic_cast < TEdit * >(c);
	if (NULL != edit && edit->Text.Length() == 0) {
	    allEditOk = false;
	    break;
	}
    }
    if (allEditOk) {
	callbackIF->callback();
    }
}

//---------------------------------------------------------------------------

