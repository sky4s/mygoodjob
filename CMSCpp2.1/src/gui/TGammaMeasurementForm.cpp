//---------------------------------------------------------------------------

#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TGammaMeasurementForm.h"
#include "TMainForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TOutputFileFrame"
#pragma resource "*.dfm"
TGammaMeasurementForm *GammaMeasurementForm;
//---------------------------------------------------------------------------
__fastcall TGammaMeasurementForm::TGammaMeasurementForm(TComponent * Owner)
:TForm(Owner)
{
}

//---------------------------------------------------------------------------
void __fastcall TGammaMeasurementForm::Button_MeasureClick(TObject *
							   Sender)
{
    MainForm->setToTargetChannel();
}


//---------------------------------------------------------------------------
void TGammaMeasurementForm::setBitDepthProcessor(bptr <
						 cms::lcd::calibrate::
						 BitDepthProcessor >
						 bitDepth)
{
    this->bitDepth = bitDepth;
}

//---------------------------------------------------------------------------


void TGammaMeasurementForm::setMeasureInfo()
{
    using namespace cms::util;
    int start = bitDepth->getMeasureStart();
    int step = bitDepth->getMeasureStep();
    this->Edit_StartLevel->Text = Util::toString(start).c_str();
    this->ComboBox_LevelStep->Text = Util::toString(step).c_str();
};

void __fastcall TGammaMeasurementForm::FormShow(TObject * Sender)
{
    setMeasureInfo();
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

