//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TGammaMeasurementForm.h"
#include "TMainForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TGammaMeasurementForm *GammaMeasurementForm;
//---------------------------------------------------------------------------
__fastcall TGammaMeasurementForm::TGammaMeasurementForm(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TGammaMeasurementForm::Button_PCMeasureClick(TObject *
							     Sender)
{
    int targetWhiteChannel = this->Edit_Channel->Text.ToInt();
    MainForm->setChannel(targetWhiteChannel);
}

//---------------------------------------------------------------------------
void __fastcall TGammaMeasurementForm::Button_TCONMeasureClick(TObject *
							       Sender)
{
    int targetWhiteChannel = this->Edit_Channel2->Text.ToInt();
    MainForm->setChannel(targetWhiteChannel);
}

//---------------------------------------------------------------------------

