//---------------------------------------------------------------------------

#include <vcl.h>
#include <lib/CMSCpp2.1/includeall.h>
#pragma hdrstop

#include "TPatternForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPatternForm *PatternForm;
//---------------------------------------------------------------------------
__fastcall TPatternForm::TPatternForm(TComponent * Owner)
:TForm(Owner)
{

}

//---------------------------------------------------------------------------

void __fastcall TPatternForm::FormPaint(TObject * Sender)
{
    TCanvas *canvas = this->Canvas;
    int h = this->ClientHeight;
    int w = this->ClientWidth;
    canvas->Brush->Color = clRed;
    canvas->Rectangle(0, 0, w, h);
}

//---------------------------------------------------------------------------

void __fastcall TPatternForm::FormResize(TObject * Sender)
{
    FormPaint(Sender);
}

//---------------------------------------------------------------------------
/*void TPatternForm::setHue(int hue)
{
    this->hue = hue;
}

void TPatternForm::setSaturationValue(int n, ...)
{
    //double *array = new double[n];
    patchCount = n / 2;
    saturationArray = int_array(new int[patchCount]);
    valueArray = int_array(new int[patchCount]);

    va_list num_list;
    va_start(num_list, n);

    for (int i = 0; i < n; i++) {
	const int d = va_arg(num_list, const int);
	int index = i / 2;
	if (i % 2 == 0) {
	    saturationArray[index] = d;
	} else {
	    valueArray[index] = d;
	}
    }
    va_end(num_list);
}*/

