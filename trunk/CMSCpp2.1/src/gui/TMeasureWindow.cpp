//---------------------------------------------------------------------------


#include <includeall.h>
#pragma hdrstop

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include "TMeasureWindow.h"
//�B�έY�Ѧҫ��Хh�x�sWindowListener
#define WEAK_PTR

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMeasureWindow *MeasureWindow;
//---------------------------------------------------------------------------
__fastcall TMeasureWindow::TMeasureWindow(TComponent * Owner)
:TForm(Owner)
{

    DoubleBuffered = true;
    this->Button1->OnClick = Button1Click;
    pattern = Normal;
    tconinput = false;
    lineAdjoin = false;
}

//---------------------------------------------------------------------------
void __fastcall TMeasureWindow::FormKeyPress(TObject * Sender, char &Key)
{
    switch (Key) {
    case 27:			//esc
	if (tconinput) {
	    tconcontrol->setGammaTest(false);
	}
	this->Close();
	break;
    case 32:			//space
	this->Button1->Visible = true;
    }
}

//---------------------------------------------------------------------------

bptr < cms::util::DoubleBufferedCanvas > TMeasureWindow::getDoubleBufferedCanvas()
{
    using namespace cms::util;
    if (doubleBuffered == null) {
	doubleBuffered =
	    bptr < DoubleBufferedCanvas > (new DoubleBufferedCanvas(this->Canvas, Width, Height));
    }
    return doubleBuffered;

};

void TMeasureWindow::setRGB(int r, int g, int b)
{
    using namespace cms::util;
    this->Update();

    if (true == tconinput) {
	if (tconcontrol->isGammaTestEnable()) {
	    tconcontrol->setGammaTestRGB(r, g, b);
	} else {
	    throw java::lang::UnsupportedOperationException("");
	}
    } else {
	TColor color = (TColor) ((b << 16) + (g << 8) + r);
	switch (pattern) {
	case HStripe:{
		bptr < DoubleBufferedCanvas > doubleBuffered = getDoubleBufferedCanvas();
		TCanvas *canvas = doubleBuffered->getDoubleBufferedCanvas();
		int w = this->Width;
		int h = this->Height;
		for (int y = 0; y < h; y++) {
		    canvas->PenPos = TPoint(0, y);
		    if (y % 2 == 0) {
			canvas->Pen->Color = color;
		    } else {
			canvas->Pen->Color = clBlack;
		    }
		    canvas->LineTo(w, y);
		}
		doubleBuffered->excute();
	    }
	    break;
	case HSD:{
		bptr < DoubleBufferedCanvas > doubleBuffered = getDoubleBufferedCanvas();
		TCanvas *canvas = doubleBuffered->getDoubleBufferedCanvas();

		int w = this->Width;
		int h = this->Height;
		int w2 = w / 2;
		TColor gcolor = (TColor) (g << 8);
		TColor color1 = (TColor) ((b << 16) + r);

		for (int x = 0; x < w2; x++) {
		    int start = x * 2;
		    canvas->Pen->Color = color1;
		    canvas->PenPos = TPoint(start, 0);
		    canvas->LineTo(start, h);

		    start += 1;
		    canvas->Pen->Color = gcolor;
		    canvas->PenPos = TPoint(start, 0);
		    canvas->LineTo(start, h);
		}
		if (false == lineAdjoin) {
		    //�۶¦�, ��line�������n�۾F
		    canvas->Pen->Color = clBlack;
		    for (int y = 1; y < h; y += 2) {
			canvas->PenPos = TPoint(0, y);
			canvas->LineTo(w, y);
		    }
		}
		doubleBuffered->excute();
	    }
	    break;
	case Indepedent:{
		bptr < DoubleBufferedCanvas > doubleBuffered = getDoubleBufferedCanvas();
		TCanvas *canvas = doubleBuffered->getDoubleBufferedCanvas();
		doubleBuffered->clear();


		int w = this->Width;
		int h = this->Height;
		int w4 = w / 4;
		TColor rcolor = (TColor) (r);
		TColor gcolor = (TColor) (g << 8);
		TColor bcolor = (TColor) ((b << 16));

		for (int x = 0; x < w4; x++) {
		    int start = x * 4;
		    canvas->Pen->Color = rcolor;
		    canvas->PenPos = TPoint(start, 0);
		    canvas->LineTo(start, h);

		    start += 1;
		    canvas->Pen->Color = gcolor;
		    canvas->PenPos = TPoint(start, 0);
		    canvas->LineTo(start, h);

		    start += 1;
		    canvas->Pen->Color = bcolor;
		    canvas->PenPos = TPoint(start, 0);
		    canvas->LineTo(start, h);
		}
		if (false == lineAdjoin) {
		    //�۶¦�, ��line�������n�۾F
		    canvas->Pen->Color = clBlack;
		    for (int y = 1; y < h; y += 2) {
			canvas->PenPos = TPoint(0, y);
			canvas->LineTo(w, y);
		    }
		}
		doubleBuffered->excute();
	    }
	    break;
	case Normal:
	    this->Color = color;
	    break;
	case FlickrPixel:
	    {
		bptr < DoubleBufferedCanvas > doubleBuffered = getDoubleBufferedCanvas();
		TCanvas *canvas = doubleBuffered->getDoubleBufferedCanvas();
		doubleBuffered->clear();

		int w = this->Width;
		int h = this->Height;
		int w2 = w / 2;
		int h2 = h / 2;
		canvas->Pen->Color = color;
		for (int x = 0; x < w2; x++) {
		    canvas->PenPos = TPoint(x * 2, 0);
		    canvas->LineTo(x * 2, h);
		}
		for (int x = 0; x < h2; x++) {
		    canvas->PenPos = TPoint(0, x * 2);
		    canvas->LineTo(w, x * 2);
		}
		for (int y = 0; y < h2; y++) {
		    for (int x = 0; x < w2; x++) {
			canvas->Pixels[x * 2][y * 2] = clBlack;
		    }
		}

		doubleBuffered->excute();
	    }
	    break;
	case FlickrSubPixel:
	    {
		bptr < DoubleBufferedCanvas > doubleBuffered = getDoubleBufferedCanvas();
		TCanvas *canvas = doubleBuffered->getDoubleBufferedCanvas();

		int w = this->Width;
		int h = this->Height;
		int w2 = w / 2;
		TColor gcolor = (TColor) (g << 8);
		TColor color1 = (TColor) ((b << 16) + r);

		canvas->Brush->Color = gcolor;
		canvas->FillRect(TRect(0, 0, w, h));
		for (int y = 0; y < h; y++) {
		    for (int x = 0; x < w2; x++) {
			int index = x * 2 + y % 2;
			canvas->Pixels[index][y] = color1;
		    }
		}
		doubleBuffered->excute();
	    }
	    break;
	case Ninth:{
		bptr < DoubleBufferedCanvas > doubleBuffered = getDoubleBufferedCanvas();
		TCanvas *canvas = doubleBuffered->getDoubleBufferedCanvas();

		int w = this->Width;
		int h = this->Height;
		int w3 = w / 3;
		int h3 = h / 3;

		canvas->Brush->Color = clBlack;
		canvas->FillRect(TRect(0, 0, w, h));
		canvas->Brush->Color = color;
		canvas->FillRect(TRect(w3, h3, w3 * 2, h3 * 2));
		doubleBuffered->excute();
	    }
	}
    }
}

void TMeasureWindow::setRGB(bptr < Dep::RGBColor > rgb)
{
    double_array values(new double[3]);
    using namespace Dep;
    //bool tconinput = false;
    const MaxValue & maxValue = tconinput ? MaxValue::Int12Bit : MaxValue::Int8Bit;
    rgb->getValues(values, maxValue);

    int r = static_cast < int >(values[0]);
    int g = static_cast < int >(values[1]);
    int b = static_cast < int >(values[2]);
    setRGB(r, g, b);
}

//---------------------------------------------------------------------------

void __fastcall TMeasureWindow::Button1Click(TObject * Sender)
{
    //pattern = HSD;
    //pattern = HStripe;
    //pattern = Indepedent;
    //pattern = FlickrPixel;
    //pattern = Ninth;
    //setRGB(255, 255, 255);
    setRGB(128, 128, 128);
    /*int color = (255 << 16) + (255 << 8) + 255;
       this->Canvas->Pen->Color = color;
       this->Canvas->LineTo(100, 100); */
}

//---------------------------------------------------------------------------
void TMeasureWindow::setTCONControl(bptr < i2c::TCONControl > tconcontrol)
{
    this->tconcontrol = tconcontrol;
    tconinput = true;
};

//---------------------------------------------------------------------------
void TMeasureWindow::setTCONControlOff()
{
    tconinput = false;
};

//---------------------------------------------------------------------------
void TMeasureWindow::setVisible(bool visible)
{
#ifdef DEBUG_STOP_TCONINPUT
    if (tconinput) {
	tconcontrol->setGammaTest(visible);
    }
    this->Visible = visible;
    if (visible) {
	this->BringToFront();
    }
#else
    if (tconinput) {
	tconcontrol->setGammaTest(visible);
    } else {
	this->Visible = visible;
	if (visible) {
	    this->BringToFront();
	}
    }
#endif

};

//---------------------------------------------------------------------------
void TMeasureWindow::addWindowListener(bptr < cms::util::WindowListener > listener)
{
#ifndef WEAK_PTR
    listenerVector.push_back(listener);
#else
    bwptr < cms::util::WindowListener > wptr(listener);
    listenerVector2.push_back(wptr);
#endif
}

//---------------------------------------------------------------------------


void __fastcall TMeasureWindow::FormClose(TObject * Sender, TCloseAction & Action)
{
#ifndef WEAK_PTR
    foreach(bptr < cms::util::WindowListener > listener, listenerVector) {
	if (null != listener) {
	    listener->windowClosing();
	}
    }
#else
    foreach(bwptr < cms::util::WindowListener > listener, listenerVector2) {
	bptr < cms::util::WindowListener > l = listener.lock();
	if (null != l) {
	    l->windowClosing();
	}
    }
#endif
}

//---------------------------------------------------------------------------

void __fastcall TMeasureWindow::FormShow(TObject * Sender)
{
    Image1->Width = this->Width;
    Image1->Height = this->Height;
}

//---------------------------------------------------------------------------

void __fastcall TMeasureWindow::Button2Click(TObject * Sender)
{
    Image1->Picture->LoadFromFile("sponge.jpg");
}

//----\-----------------------------------------------------------------------
void TMeasureWindow::setImageFilename(const std::string & filename)
{
    Image1->Picture->LoadFromFile(filename.c_str());
    Image1->Visible = true;
}

void TMeasureWindow::setImageOff()
{
    Image1->Visible = false;
}

void TMeasureWindow::setPattern(Pattern pattern)
{
    this->pattern = pattern;
};

void TMeasureWindow::setLineAdjoin(bool lineAdjoin)
{
    this->lineAdjoin = lineAdjoin;
};
