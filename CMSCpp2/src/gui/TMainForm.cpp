//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TMainForm.h"
#include "TTargetWhiteForm.h"
#include "TAboutBox.h"
#include <cms/measure/meter.h>
#include <UIConfig.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent * Owner):TForm(Owner),linkCA210(LINK_CA210)
{
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::About1Click(TObject * Sender)
{
    AboutBox->ShowModal();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::Exit1Click(TObject * Sender)
{
    this->Close();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::TargetWhite1Click(TObject * Sender)
{
    TargetWhiteForm->ShowModal();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject * Sender)
{
    using namespace cms::measure::meter;
    if (true == linkCA210) {
	meter = bptr < Meter > (new CA210());
    } else {

    }
}


//---------------------------------------------------------------------------


