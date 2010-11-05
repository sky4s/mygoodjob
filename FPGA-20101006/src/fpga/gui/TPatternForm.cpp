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
__fastcall TPatternForm::TPatternForm(TComponent * Owner):TForm(Owner),
patchCols(1), gapPercent(.05)
{

}

//---------------------------------------------------------------------------

void __fastcall TPatternForm::FormPaint(TObject * Sender)
{
  TCanvas *canvas = this->Canvas;
  //int h = this->ClientHeight;
  //int w = this->ClientWidth;
  bool verticalBorder = patchCols > 1;
  //hsvVector->
  int size = hsvVector->size();
  int patchPerCol = size / patchCols;

  int h = this->ClientHeight / patchPerCol;
  int w = this->ClientWidth / patchCols;

  for (int i = 0; i < size; i++)
  {
    HSV_ptr hsv = (*hsvVector)[i];
    RGB_ptr rgb = hsv->toRGB();
    canvas->Brush->Color = rgb->getColor();
    int x = i / size;
    int y = i % patchPerCol;

  }
  /*canvas->Brush->Color = clRed;
     canvas->Rectangle(0, 0, w, h); */
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

void TPatternForm::setGapPercent(double gapPercent)
{
  this->gapPercent = gapPercent;
}

void TPatternForm::setHSVVector(HSV_vector_ptr hsvVector)
{
  this->hsvVector = hsvVector;
}

void TPatternForm::setPatchCols(int cols)
{
  this->patchCols = cols;
}

