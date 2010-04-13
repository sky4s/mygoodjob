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
    using namespace std;
    MainForm->setToTargetChannel();
    bool_vector_ptr rgbw(new bool_vector(4));
    (*rgbw)[0] = this->CheckBox_R->Checked;
    (*rgbw)[1] = this->CheckBox_G->Checked;
    (*rgbw)[2] = this->CheckBox_B->Checked;
    (*rgbw)[3] = this->CheckBox_W->Checked;
    if (bitDepth->isTCONInput()) {
	tconMeasure(rgbw);
    } else {
	pcMeasure(rgbw);
    }
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

//---------------------------------------------------------------------------
void TGammaMeasurementForm::pcMeasure(bool_vector_ptr rgbw)
{
    using namespace Dep;
    channel_vector_ptr channels = Channel::RGBWChannel;
    int size = channels->size();

    for (int x = 0; x < size; x++) {
	const Channel & ch = (*channels)[x];
    }
};

//---------------------------------------------------------------------------
void TGammaMeasurementForm::tconMeasure(bool_vector_ptr rgbw)
{
    using namespace Dep;
    channel_vector_ptr channels = Channel::RGBWChannel;
    int size = channels->size();
};

//---------------------------------------------------------------------------

void __fastcall TGammaMeasurementForm::FormShow(TObject * Sender)
{
    setMeasureInfo();
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

