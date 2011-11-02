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
    for (int x = 0; x < size; x++) {
	TControl *c = GroupBox1->Controls[x];
	TEdit *edit = dynamic_cast < TEdit * >(c);
	if (NULL != edit && edit->Text.Length() == 0) {
	    allEditOk = false;
	    break;
	}
    }
    size = GroupBox2->ControlCount;
    for (int x = 0; x < size; x++) {
	TControl *c = GroupBox2->Controls[x];
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
double_array TGamutSetupForm::getSourceRGBxyY()
{
    double_array result(new double[9]);
    result[0] = Edit_SourceRx->Text.ToDouble();
    result[1] = Edit_SourceRy->Text.ToDouble();
    result[2] = Edit_SourceRLv->Text.ToDouble();
    result[3] = Edit_SourceGx->Text.ToDouble();
    result[4] = Edit_SourceGy->Text.ToDouble();
    result[5] = Edit_SourceGLv->Text.ToDouble();
    result[6] = Edit_SourceBx->Text.ToDouble();
    result[7] = Edit_SourceBy->Text.ToDouble();
    result[8] = Edit_SourceBLv->Text.ToDouble();
    return result;
}

double_array TGamutSetupForm::getTargetRGBxyY()
{
    double_array result(new double[9]);
    result[0] = Edit_TargetRx->Text.ToDouble();
    result[1] = Edit_TargetRy->Text.ToDouble();
    result[2] = Edit_TargetRLv->Text.ToDouble();
    result[3] = Edit_TargetGx->Text.ToDouble();
    result[4] = Edit_TargetGy->Text.ToDouble();
    result[5] = Edit_TargetGLv->Text.ToDouble();
    result[6] = Edit_TargetBx->Text.ToDouble();
    result[7] = Edit_TargetBy->Text.ToDouble();
    result[8] = Edit_TargetBLv->Text.ToDouble();
    return result;
}

void __fastcall TGamutSetupForm::Button1Click(TObject * Sender)
{
    Edit_SourceRx->Text = 0.5794164995352137;
    Edit_SourceRy->Text = 0.3452359396700706;
    Edit_SourceRLv->Text = 42.60552215576172;
    Edit_SourceGx->Text = 0.3200318457331593;
    Edit_SourceGy->Text = 0.5670029311753376;
    Edit_SourceGLv->Text = 112.3306121826172;
    Edit_SourceBx->Text = 0.1473404603349543;
    Edit_SourceBy->Text = 0.1087370563095248;
    Edit_SourceBLv->Text = 26.0684814453125;
}

//---------------------------------------------------------------------------

