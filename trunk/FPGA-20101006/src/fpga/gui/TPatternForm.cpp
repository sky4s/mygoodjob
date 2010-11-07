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
patchCols(1), gapPercent(.05), mode(PatternMode::Single)
{

}

//---------------------------------------------------------------------------

void __fastcall TPatternForm::FormPaint(TObject * Sender)
{
  if (null == hsvVector || 0 == hsvVector->size())
  {
    return;
  }

  int size = hsvVector->size();
  TCanvas *canvas = this->Canvas;
  canvas->Brush->Color = clBlack;
  canvas->Rectangle(0, 0, this->ClientWidth, this->ClientHeight);

  bool verticalBorder = patchCols > 1;
  int patchPerCol = size / patchCols;
  int h = this->ClientHeight / patchPerCol;
  int w = this->ClientWidth / patchCols;


  int hgap = h * gapPercent / 2.;
  int wgap = w * gapPercent;

  for (int i = 0; i < size; i++)
  {
    HSV_ptr hsv = (*hsvVector)[i];
    RGB_ptr rgb = hsv->toRGB();
    canvas->Brush->Color = rgb->getColor();
    int x = i / patchPerCol;
    int y = i % patchPerCol;

    TRect rect(x * w + wgap, y * h + hgap, x * w + w - wgap,
               y * h + h - hgap);
    canvas->FillRect(rect);

  }

  int_vector_ptr boxVector[2] = { blackIndexVector, whiteIndexVector };
  TColor boxColor[2] = { clBlack, clWhite };
  for (int x = 0; x < 2; x++)
  {
    int_vector_ptr vector = boxVector[x];
    if (null != vector)
    {
      int vecSize = vector->size();
      canvas->Brush->Color = boxColor[x];

      for (int i = 0; i < vecSize; i++)
      {
        int index = (*vector)[i];
        int x = index / size;
        int y = index % patchPerCol;

        TRect rect1(x * w + wgap, y * h + hgap, x * w + w - wgap,
                    y * h + h - hgap);
        TRect rect2(x * w + wgap + 1, y * h + hgap + 1, x * w + w - wgap - 1,
                    y * h + h - hgap - 1);
        canvas->FrameRect(rect1);
        canvas->FrameRect(rect2);
      }
    }

  }

  foreach(int_vector_ptr vector, boxVector)
  {
    if (null != vector)
    {
      int blackSize = blackIndexVector->size();
      canvas->Brush->Color = clBlack;

      for (int i = 0; i < blackSize; i++)
      {
        int index = (*blackIndexVector)[i];
        int x = index / size;
        int y = index % patchPerCol;

        TRect rect1(x * w + wgap, y * h + hgap, x * w + w - wgap,
                    y * h + h - hgap);
        TRect rect2(x * w + wgap + 1, y * h + hgap + 1, x * w + w - wgap - 1,
                    y * h + h - hgap - 1);
        canvas->FrameRect(rect1);
        canvas->FrameRect(rect2);
      }
    }

  }

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

void TPatternForm::setBlackBoxIndexVector(int_vector_ptr indexVector)
{
  this->blackIndexVector = indexVector;
}

void TPatternForm::setWhiteBoxIndexVector(int_vector_ptr indexVector)
{
  this->whiteIndexVector = indexVector;
}
void __fastcall TPatternForm::Button_Show7p5DegClick(TObject * Sender)
{
  switch (mode)
  {
  case PatternMode::Hue15:
    this->Width = this->Width / 3 * 5;
    break;
  case PatternMode::Single:
    this->Width *= 5;
    break;
  }
  mode = PatternMode::Hue7p5;
  if (null != callback)
  {
    callback->show7p5DegBasePattern();
  }
}

//---------------------------------------------------------------------------

void __fastcall TPatternForm::Button_Show15DegClick(TObject * Sender)
{
  switch (mode)
  {
  case PatternMode::Single:
    this->Width *= 3;
    break;
  case PatternMode::Hue7p5:
    this->Width = this->Width / 5 * 3;
    break;
  }

  mode = PatternMode::Hue15;
  if (null != callback)
  {
    callback->show15DegBasePattern();
  }
}

//---------------------------------------------------------------------------

void __fastcall TPatternForm::Button_ShowSingleDegClick(TObject * Sender)
{

  switch (mode)
  {
  case PatternMode::Hue15:
    this->Width /= 3;
    break;
  case PatternMode::Hue7p5:
    this->Width /= 5;
    break;
  }
  mode = PatternMode::Single;
  if (null != callback)
  {
    callback->showSinglePattern();
  }
}

//---------------------------------------------------------------------------

void TPatternForm::setPatternCallbackIF(PatternCallbackIF * callback)
{
  this->callback = callback;
}

