//---------------------------------------------------------------------------


#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TMainForm.h"
#include "TTargetWhiteForm.h"
#include "TTargetWhiteForm2.h"
#include "TAboutBox.h"
#include "TCCTLUTForm.h"

#include <debug.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMainForm *MainForm;
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent * Owner):TForm(Owner),
linkCA210(!FileExists(DEBUG_FILE))
{
    //bool debug = FileExists(DEBUG_FILE);
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
    TargetWhiteForm2->ShowModal();
    //TargetWhiteForm2->Show();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::FormCreate(TObject * Sender)
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    if (true == linkCA210) {
	meter = bptr < Meter > (new CA210());
	mm = bptr < MeterMeasurement >
	    (new MeterMeasurement(meter, false));

	analyzer.reset(new CA210IntensityAnalyzer(getCA210(), mm));
    } else {
	setDummyMeterFilename(METER_FILE);
    }
}

//---------------------------------------------------------------------------

void TMainForm::setDummyMeterFilename(const std::string & filename)
{
    using namespace cms::measure::meter;
    using namespace cms::measure;
    using namespace cms::colorformat;
    bptr < DGLutFile > dgcode(new DGLutFile(filename));
    meter.reset(new DGLutFileMeter(dgcode));
    mm.reset(new MeterMeasurement(meter, false));
    mm->setFakeMeasure(true);
    analyzer.reset(new CA210IntensityAnalyzer(mm));
};

//---------------------------------------------------------------------------

void TMainForm::resetDummyMeter()
{
    using namespace cms::measure::meter;
    DGLutFileMeter *dgc = dynamic_cast < DGLutFileMeter * >(meter.get());
    dgc->reset();
};


//---------------------------------------------------------------------------
bptr < cms::measure::meter::CA210 > TMainForm::getCA210()
{
    if (null == ca210) {
	ca210.reset(dynamic_cast <
		    cms::measure::meter::CA210 * >(meter.get()));
    }
    return ca210;
};

//---------------------------------------------------------------------------
int TMainForm::getInterval()
{
    return Edit_Interval->Text.ToInt();
};

//---------------------------------------------------------------------------

void __fastcall TMainForm::CCTLUT1Click(TObject * Sender)
{
    CCTLUTForm->ShowModal();
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::GammaAdj1Click(TObject * Sender)
{
    //MeasureWindow->ShowModal();
    //MeasureWindow->Visible = true;
}

//---------------------------------------------------------------------------


void __fastcall TMainForm::RadioButton_TCONClick(TObject * Sender)
{
    CCTLUTForm->setTCONInput(true);
}

//---------------------------------------------------------------------------

void __fastcall TMainForm::RadioButton_PCClick(TObject * Sender)
{
    CCTLUTForm->setTCONInput(false);
}

//---------------------------------------------------------------------------

