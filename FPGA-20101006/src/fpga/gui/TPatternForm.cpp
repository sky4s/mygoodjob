//---------------------------------------------------------------------------

#include <vcl.h>
#include <lib/CMSCpp2.1/src/includeall.h>
#pragma hdrstop

#include "TPatternForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TPatternForm *PatternForm;
TPatternForm *PatternForm2;
//---------------------------------------------------------------------------
__fastcall TPatternForm::TPatternForm(TComponent * Owner):TForm(Owner),
patchCols(1), gapPercent(.05), mode(PatternMode::Single)
{
}

void TPatternForm::setTPatternForm(TPatternForm * copy)
{
    gapPercent = copy->gapPercent;
    patchCols = copy->patchCols;
    hsvVector = copy->hsvVector;
    blackIndexVector = copy->blackIndexVector;
    whiteIndexVector = copy->whiteIndexVector;
    callback = copy->callback;
    mode = copy->mode;
    Button_Show7p5Deg->Visible = false;
    Button_Show15Deg->Visible = false;
    Button_ShowSingleDeg->Visible = false;
}

//---------------------------------------------------------------------------

void __fastcall TPatternForm::FormPaint(TObject * Sender)
{
    if (null == hsvVector || 0 == hsvVector->size()) {
	return;
    }


    int size = hsvVector->size();

    using namespace cms::util;
    if (null == doubleBufferedCanvas) {
	doubleBufferedCanvas =
	    bptr < DoubleBufferedCanvas >
	    (new DoubleBufferedCanvas(this->Canvas, this->ClientWidth, this->ClientHeight));
    }
    doubleBufferedCanvas->setSize(this->ClientWidth, this->ClientHeight);
    TCanvas *canvas = doubleBufferedCanvas->getDoubleBufferedCanvas();

    canvas->Brush->Color = clBlack;
    canvas->Rectangle(0, 0, this->ClientWidth, this->ClientHeight);
    bool verticalBorder = patchCols > 1;
    int patchPerCol = size / patchCols;
    int h = this->ClientHeight / patchPerCol;
    int w = this->ClientWidth / patchCols;
    int hgap = h * gapPercent / 2.;
    int wgap = w * gapPercent;
    for (int i = 0; i < size; i++) {
	HSV_ptr hsv = (*hsvVector)[i];
	RGB_ptr rgb = hsv->toRGB();
	canvas->Brush->Color = rgb->getColor();
	int x = i / patchPerCol;
	int y = i % patchPerCol;
	TRect rect(x * w + wgap, y * h + hgap, x * w + w - wgap, y * h + h - hgap);
	canvas->FillRect(rect);
    }

    int_vector_ptr boxVector[2] = {
	blackIndexVector,
	whiteIndexVector
    };
    TColor boxColor[2] = {
	clBlack, clWhite
    };
    for (int x = 0; x < 2; x++) {
	int_vector_ptr vector = boxVector[x];
	if (null != vector) {
	    int vecSize = vector->size();
	    canvas->Brush->Color = boxColor[x];
	    for (int i = 0; i < vecSize; i++) {
		int index = (*vector)[i];
		int x = index / patchPerCol;
		int y = index % patchPerCol;
		TRect rect1(x * w + wgap, y * h + hgap, x * w + w - wgap, y * h + h - hgap);
		TRect rect2(x * w + wgap + 1,
			    y * h + hgap + 1, x * w + w - wgap - 1, y * h + h - hgap - 1);
		canvas->FrameRect(rect1);
		canvas->FrameRect(rect2);
	    }
	}

    }

    doubleBufferedCanvas->excute();

}

//---------------------------------------------------------------------------

void __fastcall TPatternForm::FormResize(TObject * Sender)
{
    FormPaint(Sender);
}

//---------------------------------------------------------------------------


void TPatternForm::setGapPercent(double gapPercent)
{
    this->gapPercent = gapPercent;
}

void TPatternForm::setHSVVector(HSV_vector_ptr hsvVector)
{
    this->hsvVector = hsvVector;
    if (wsNormal == PatternForm2->WindowState) {
	PatternForm2->setTPatternForm(this);
	PatternForm2->Refresh();
    }
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
    switch (mode) {
    case PatternMode::Hue15:
	this->Width = this->Width / 3 * 5;
	break;
    case PatternMode::Single:
	this->Width *= 5;
	break;
    }
    mode = PatternMode::Hue7p5;
    if (null != callback) {
	callback->show7p5DegBasePattern();
    }
}

//---------------------------------------------------------------------------

void __fastcall TPatternForm::Button_Show15DegClick(TObject * Sender)
{
    switch (mode) {
    case PatternMode::Single:
	this->Width *= 3;
	break;
    case PatternMode::Hue7p5:
	this->Width = this->Width / 5 * 3;
	break;
    }

    mode = PatternMode::Hue15;
    if (null != callback) {
	callback->show15DegBasePattern();
    }
}

//---------------------------------------------------------------------------

void __fastcall TPatternForm::Button_ShowSingleDegClick(TObject * Sender)
{

    switch (mode) {
    case PatternMode::Hue15:
	this->Width /= 3;
	break;
    case PatternMode::Hue7p5:
	this->Width /= 5;
	break;
    case PatternMode::Single:
	if (wsNormal == PatternForm2->WindowState) {
	    PatternForm2->WindowState = wsMinimized;
	} else {
	    PatternForm2->setTPatternForm(this);
	    PatternForm2->WindowState = wsNormal;
	}
	break;
    }
    mode = PatternMode::Single;
    if (null != callback) {
	callback->showSinglePattern();
    }
}

//---------------------------------------------------------------------------

void TPatternForm::setPatternCallbackIF(PatternCallbackIF * callback)
{
    this->callback = callback;
}


void __fastcall TPatternForm::FormMouseMove(TObject * Sender, TShiftState Shift, int X, int Y)
{
    using namespace Dep;
    TColor color = this->Canvas->Pixels[X][Y];
    double_array rgbValues(new double[3]);
    rgbValues[0] = GetRValue(color);
    rgbValues[1] = GetGValue(color);
    rgbValues[2] = GetBValue(color);
    double_array hsviValues = HSV::getHSVIValues(rgbValues);
    AnsiString astr;

    this->Hint =
	"rgb(" + FloatToStr(rgbValues[0]) + ", " + FloatToStr(rgbValues[1]) + ", " +
	FloatToStr(rgbValues[2]) + ") hsv(" + astr.sprintf("%.1f", hsviValues[0]) + ", " +
	astr.sprintf("%.3f", hsviValues[1]) + ", " + FloatToStr(hsviValues[2]) + ")";
}

//---------------------------------------------------------------------------

