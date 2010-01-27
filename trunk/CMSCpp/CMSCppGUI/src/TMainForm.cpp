//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "TMainForm.h"
#include "TTargetWhiteForm.h"
#include "TAboutBox.h"

//#include <string>
//#include <boost/shared_ptr.hpp>
//#include <cms/measure/meter.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent * Owner)
:TForm(Owner)
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
    //using namespace cms::measure::meter;
    //using namespace boost;
    //using namespace std;
    //boost::shared_ptr < CA210 > meter =
    //boost::shared_ptr < CA210 > (new CA210());
    //cms::measure::meter::CA210 *c = new  cms::measure::meter::CA210();
    //boost::shared_ptr < CA210 > meter(new CA210());
}

//---------------------------------------------------------------------------

