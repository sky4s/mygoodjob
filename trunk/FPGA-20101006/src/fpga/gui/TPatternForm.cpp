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

/*PatchManager::PatchManager(int width, int height, double gapPercent)
{
}
void PatchManager::setDimension(int width, int height)
{
}
void PatchManager::setPatchSize(int size)
{
}
void PatchManager::setGapPercent(double gapPercent)
{
}
int_array PatchManager::getPatchCoordinate(int index)
{
}*/


__fastcall TPatternForm::TPatternForm(TComponent * Owner):TForm(Owner),
patchCols(1), gapPercent(.05), mode(PatternMode::Single), inversePattern(false),
mouseLeftDown(false), mouseDownStart(new int[2])
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

    size = copy->size;
    patchPerCol = copy->patchPerCol;
    h = copy->h;
    w = copy->w;
    hgap = copy->hgap;
    wgap = copy->wgap;
}

//---------------------------------------------------------------------------

int TPatternForm::getPatchIndex(int x, int y)
{
    if (null == hsvVector || 0 == hsvVector->size()) {
	return -1;
    }

    int x0 = x / w;
    int y0 = y / h;
    int index = x0 * patchPerCol + y0;
    return index;
}

int_array TPatternForm::distanceToPatchOriginal(int x, int y)
{
    mouseDownPatchIndex = getPatchIndex(x, y);

    int x0 = mouseDownPatchIndex / patchPerCol;
    int y0 = mouseDownPatchIndex % patchPerCol;

    int_array result(new int[2]);
    result[0] = x - x0 * w - wgap;
    result[1] = y - y0 * h - hgap;
    return result;
}

int_array TPatternForm::getPatchDimension()
{
    if (null == hsvVector || 0 == hsvVector->size()) {
	return nil_int_array;
    }

    int_array dimension(new int[2]);
    dimension[0] = w - wgap * 2;
    dimension[1] = h - hgap * 2;
    return dimension;
}

void __fastcall TPatternForm::FormPaint(TObject * Sender)
{
    if (null == hsvVector || 0 == hsvVector->size()) {
	return;
    }

    using namespace cms::util;
    if (null == doubleBufferedCanvas) {
	doubleBufferedCanvas =
	    bptr < DoubleBufferedCanvas >
	    (new DoubleBufferedCanvas(this->Canvas, this->ClientWidth, this->ClientHeight));
    }
    //重新設定大小
    doubleBufferedCanvas->setSize(this->ClientWidth, this->ClientHeight);
    //取出doublebuffered
    TCanvas *dcanvas = doubleBufferedCanvas->getDoubleBufferedCanvas();

    //塗黑
    dcanvas->Brush->Color = clBlack;
    dcanvas->Rectangle(0, 0, this->ClientWidth, this->ClientHeight);

    //超過一行的話
    //bool verticalBorder = patchCols > 1;

    int_array patchDimension = getPatchDimension();
    int patchw = patchDimension[0];
    int patchh = patchDimension[1];

    int size = hsvVector->size();
    for (int i = 0; i < size; i++) {
	HSV_ptr hsv = (*hsvVector)[i];
	RGB_ptr rgb = hsv->toRGB();
	dcanvas->Brush->Color = rgb->getColor();
	int x = i / patchPerCol;
	int y = i % patchPerCol;
	//TRect rect(x * w + wgap, y * h + hgap, x * w + w - wgap, y * h + h - hgap);
	TRect rect(x * w + wgap, y * h + hgap, x * w + wgap + patchw, y * h + hgap + patchh);
	dcanvas->FillRect(rect);
    }

    //=========================================================================
    //黑白框顯示
    //=========================================================================
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
	    dcanvas->Brush->Color = boxColor[x];
	    for (int i = 0; i < vecSize; i++) {
		int index = (*vector)[i];
		int x = index / patchPerCol;
		int y = index % patchPerCol;
		TRect rect1(x * w + wgap, y * h + hgap, x * w + w - wgap, y * h + h - hgap);
		TRect rect2(x * w + wgap + 1,
			    y * h + hgap + 1, x * w + w - wgap - 1, y * h + h - hgap - 1);
		dcanvas->FrameRect(rect1);
		dcanvas->FrameRect(rect2);
	    }
	}

    }
    //=========================================================================

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

    size = hsvVector->size();
    patchPerCol = size / patchCols;
    h = this->ClientHeight / patchPerCol;
    w = this->ClientWidth / patchCols;
    hgap = h * gapPercent / 2.;
    wgap = w * gapPercent;

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

    if (Shift.Contains(ssLeft)) {
	//按下左鍵
	//int_array distance = distanceToPatchOriginal(X, Y);
	int_array patchDimension = getPatchDimension();
	int x0 = X - mouseDownDistance[0];
	int y0 = Y - mouseDownDistance[1];
	int x1 = x0 + patchDimension[0];
	int y1 = y0 + patchDimension[1];


	TRect rect(x0, y0, x1, y1);
	HSV_ptr hsv = (*hsvVector)[mouseDownPatchIndex];
	RGB_ptr rgb = hsv->toRGB();
	Canvas->Brush->Color = rgb->getColor();

	Canvas->FillRect(rect);
	//this->Canvas->f
	/*using namespace cms::util;
	   canvasCopy =
	   DoubleBufferedCanvas::getTBitmap(this->Canvas, this->ClientHeight, this->ClientWidth);
	   DoubleBufferedCanvas doubleBuffered(this->Canvas, this->ClientHeight, this->ClientWidth);
	   TCanvas *doubleBufferedCanvas = doubleBuffered.getDoubleBufferedCanvas(); */
    }
}

//---------------------------------------------------------------------------

void __fastcall TPatternForm::FormMouseWheelDown(TObject * Sender,
						 TShiftState Shift, TPoint & MousePos,
						 bool & Handled)
{
    callback->adjustValue(false);
}

//---------------------------------------------------------------------------

void __fastcall TPatternForm::FormMouseWheelUp(TObject * Sender,
					       TShiftState Shift, TPoint & MousePos, bool & Handled)
{
    callback->adjustValue(true);
}

//---------------------------------------------------------------------------

void __fastcall TPatternForm::FormMouseDown(TObject * Sender,
					    TMouseButton Button, TShiftState Shift, int X, int Y)
{
    if (Shift.Contains(ssMiddle)) {
	//按下中鍵
	inversePattern = !inversePattern;
	callback->inversePattern(inversePattern);
    }
    if (Shift.Contains(ssLeft)) {
	//按下左鍵
	mouseDownStart[0] = X;
	mouseDownStart[1] = Y;
	mouseDownDistance = distanceToPatchOriginal(X, Y);
    }
    //mouseLeftDown = Shift.Contains(ssLeft);

}

//---------------------------------------------------------------------------

void __fastcall TPatternForm::FormMouseUp(TObject * Sender,
					  TMouseButton Button, TShiftState Shift, int X, int Y)
{
    //mouseLeftDown = false;
}

//---------------------------------------------------------------------------

