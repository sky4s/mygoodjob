//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TMainForm.h"
#include "TTargetWhiteForm.h"
#include "TTargetWhiteForm2.h"
#include "TAboutBox.h"
#include <cms/measure/meter.h>
#include <cms/measure/metermeasurement.h>
#include <UIConfig.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent * Owner):TForm(Owner),
linkCA210(LINK_CA210)
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
    //TargetWhiteForm->ShowModal();
    TargetWhiteForm2->ShowModal();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject * Sender)
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    if (true == linkCA210) {
	meter = bptr < Meter > (new CA210());
	mm = bptr < MeterMeasurement >
	    (new MeterMeasurement(meter, false));
    } else {

    }
}


//---------------------------------------------------------------------------
bptr < cms::measure::meter::CA210 > TMainForm::getCA210()
{
    if (null == ca210) {
	ca210.reset(dynamic_cast <
		    cms::measure::meter::CA210 * >(meter.get()));
    }
    return ca210;
    /*bptr < CA210 >
       ca210((dynamic_cast < CA210 * >(meter.get())));
       return ca210; */
};

//---------------------------------------------------------------------------


