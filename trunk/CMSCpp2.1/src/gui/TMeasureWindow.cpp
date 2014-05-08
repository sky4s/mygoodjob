//---------------------------------------------------------------------------


#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TTargetWhiteForm2.h"
#include "TMeasureWindow.h"
#include "TCCTLUTForm.h"
#include "TMainForm.h"
//運用弱參考指標去儲存WindowListener
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
    //this->Button1->OnClick = Button1Click;
    pattern = Normal;
    lineAdjoin = false;
    source = PC;
}

//---------------------------------------------------------------------------
void __fastcall TMeasureWindow::FormKeyPress(TObject * Sender, char &Key)
{
    switch (Key) {
    case 27:			//esc
	if (DIRECT_GAMMA == source) {
	    tconcontrol->setGammaTest(false);
	}

	this->Visible = false;
	//=====================================================================
	// 這個部份應該改用listener pattern會較好, 但是實際上也就只有這兩個視窗會呼叫到
	// 所以就免了!
	//=====================================================================
	if (null != TargetWhiteForm2) {
	    TargetWhiteForm2->stopMeasure = true;
	}
	if (null != CCTLUTForm) {
	    CCTLUTForm->run = false;
	}
	//=====================================================================
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



    if (DIRECT_GAMMA == source) {
	//=========================================================================
	// tcon-input (Direct Gamma)
	//=========================================================================
	if (tconcontrol->isGammaTestEnable()) {
	    bool result = tconcontrol->setDirectGammaRGB(r, g, b);
	    if (false == result) {
		ShowMessage("Set Gamma Test failed!");
	    }
	} else {
	    throw java::lang::UnsupportedOperationException("");
	}
	//=========================================================================
    } else if (AGING == source) {
	//=========================================================================
	// tcon-input (Aging mode)
	//=========================================================================
	if (tconcontrol->isAgingModeEnable()) {
	    bool result = tconcontrol->setAgingModeRGB(r, g, b);
	    if (false == result) {
		ShowMessage("Set Aging Mode failed!");
	    }
	} else if(tconcontrol->isPGModeEnable()) {   //PG mode (same 10-bit input)   byBS+ 20140506
	    bool result = tconcontrol->setPGModeRGB(r, g, b);
	    if (false == result) {
		ShowMessage("Set PG Pattern failed!");
	    }
        } else {
	    throw java::lang::UnsupportedOperationException("");
	}
    } else if (DGLUT == source) {
	//=========================================================================
	// dglut-input
	//=========================================================================
	//8bit
	RGB_vector_ptr rgbVector = RGBVector::getLinearRGBVector(bitDepth->getLevelInTCon());
	const Dep::MaxValue & lutBit = tconcontrol->getLUTBit();
	RGB_ptr rgb0 = (*rgbVector)[0];
	rgb0->changeMaxValue(lutBit);
	rgb0->R = r;
	rgb0->G = g;
	rgb0->B = b;
	//tconcontrol->setDG(false);
	tconcontrol->setDGLut(rgbVector);
	//tconcontrol->setDG(true);

	this->Color = clBlack;
    } else if (PC == source) {
	//=========================================================================
	// pc-input
	//=========================================================================
	TColor color = (TColor) ((b << 16) + (g << 8) + r);
	Pattern displayPattern = (wsMaximized == this->WindowState) ? pattern : testPattern;
	switch (displayPattern) {
	case HStripe:
	case HStripe2:
	    {
		TColor color1, color2;
		if (displayPattern == HStripe) {
		    color1 = color;
		    color2 = clBlack;
		} else {
		    color1 = clBlack;
		    color2 = color;
		}

		bptr < DoubleBufferedCanvas > doubleBuffered = getDoubleBufferedCanvas();
		TCanvas *canvas = doubleBuffered->getDoubleBufferedCanvas();
		int w = this->Width;
		int h = this->Height;
		for (int y = 0; y < h; y++) {
		    canvas->PenPos = TPoint(0, y);
		    if (y % 2 == 0) {
			canvas->Pen->Color = color1;
		    } else {
			canvas->Pen->Color = color2;
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
		    //著黑色, 讓line之間不要相鄰
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
		    //著黑色, 讓line之間不要相鄰
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
    if ((DIRECT_GAMMA == source || AGING == source || DGLUT == source) && null == bitDepth) {
	ShowMessage("State of TMeasureWindow is wrong!");
	return;
    }

    if(DIRECT_GAMMA == source || DGLUT == source) {
        const MaxValue & maxValue = (DIRECT_GAMMA == source || DGLUT == source) ?
            bitDepth->getLutMaxValue() : MaxValue::Int8Bit;
        /*(DIRECT_GAMMA == source) ? MaxValue::Int12Bit :
          ((DGLUT == source) ? bitDepth->getLutMaxValue() : MaxValue::Int8Bit); */
        rgb->getValues(values, maxValue);
    } else {       // AGING == source
        rgb->getValues(values);
    }

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
void TMeasureWindow::setDirectGamma(bptr < i2c::TCONControl > tconcontrol,
				    bptr < cms::lcd::BitDepthProcessor > bitDepth)
{
    this->tconcontrol = tconcontrol;
    source = DIRECT_GAMMA;
    this->bitDepth = bitDepth;
};
void TMeasureWindow::setAgingMode(bptr < i2c::TCONControl > tconcontrol,
				  bptr < cms::lcd::BitDepthProcessor > bitDepth)
{
    this->tconcontrol = tconcontrol;
    source = AGING;
    this->bitDepth = bitDepth;
};
void TMeasureWindow::setDGLUTInput(bptr < i2c::TCONControl > tconcontrol,
				   bptr < cms::lcd::BitDepthProcessor > bitDepth)
{
    this->tconcontrol = tconcontrol;
    source = DGLUT;
    this->bitDepth = bitDepth;
};

//---------------------------------------------------------------------------
void TMeasureWindow::setTCONControlOff()
{
    source = PC;
};

//---------------------------------------------------------------------------
void TMeasureWindow::setAgingEnable(RGB_vector_ptr rgbMeasureCodeVector)	//for AgingMode byBS+
{
    tconcontrol->setDG(false);
    tconcontrol->setDGLut(rgbMeasureCodeVector);
    tconcontrol->setDG(true);
};

//---------------------------------------------------------------------------
bool TMeasureWindow::isAgingSource()	//for AgingMode byBS+
{
    return (source == AGING) ? true : false;
};

//---------------------------------------------------------------------------
void TMeasureWindow::setVisible(bool visible)
{
#ifdef DEBUG_STOP_DIRECTGAMMA
    if (DIRECT_GAMMA == source) {
	tconcontrol->setGammaTest(visible);
    }
    this->Visible = visible;
    if (visible) {
	this->BringToFront();
    }
#else
    if (DIRECT_GAMMA == source) {
	tconcontrol->setGammaTest(visible);
    } else if (AGING == source) {
        if (tconcontrol->isAgingModeEnable()) {
           tconcontrol->setGammaTest(false);
           tconcontrol->setDG(true);
	   tconcontrol->setTconAgingMode(visible);
        } else if (tconcontrol->isPGModeEnable()) {
           tconcontrol->setTconPGMode(visible);
        }
    } else {
	this->Visible = visible;
	if (visible) {
	    this->BringToFront();
	}
	if (DGLUT == source) {
	    tconcontrol->setDG(visible);
	}
    }
#endif

};

//---------------------------------------------------------------------------
void TMeasureWindow::addWindowListener(bptr < gui::event::WindowListener > listener)
{
#ifndef WEAK_PTR
    listenerVector.push_back(listener);
#else
    bwptr < gui::event::WindowListener > wptr(listener);
    listenerVector2.push_back(wptr);
#endif
}

//---------------------------------------------------------------------------


void __fastcall TMeasureWindow::FormClose(TObject * Sender, TCloseAction & Action)
{
#ifndef WEAK_PTR
    foreach(bptr < gui::event::WindowListener > listener, listenerVector) {
	if (null != listener) {
	    listener->windowClosing(Sender, Action);
	}
    }
#else
    foreach(bwptr < gui::event::WindowListener > listener, listenerVector2) {
	bptr < gui::event::WindowListener > l = listener.lock();
	if (null != l) {
	    l->windowClosing(Sender, Action);
	}
    }
#endif
}

//---------------------------------------------------------------------------

void __fastcall TMeasureWindow::FormShow(TObject * Sender)
{
    Image1->Width = this->Width;
    Image1->Height = this->Height;
    if (this->WindowState == wsNormal) {
	setRGB(255, 255, 255);
    }
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

void TMeasureWindow::setPattern(Pattern _pattern)
{
    this->pattern = _pattern;
};
void TMeasureWindow::setTestPattern(Pattern _pattern)
{
    this->testPattern = _pattern;
};
void TMeasureWindow::setLineAdjoin(bool lineAdjoin)
{
    this->lineAdjoin = lineAdjoin;
};

void __fastcall TMeasureWindow::FormCreate(TObject * Sender)
{
    //Button1->Visible = MainForm->debugMode;

}

//---------------------------------------------------------------------------


void __fastcall TMeasureWindow::Button3Click(TObject *Sender)
{

	/*using namespace cms::measure;
	using namespace Indep;
	bptr < IntensityAnalyzerIF > analyzer = MainForm->initAnalyzer();
	bptr < MeterMeasurement > mm = analyzer->getMeterMeasurement();
	bptr < cms::measure::meter::Meter > meter = mm->getMeter();

        double_array result;

        tconcontrol->setGammaTest(false);
        tconcontrol->setDG(true);*/
	tconcontrol->setTconAgingMode(true);


        //setRGB(512, 512, 512);
        //tconcontrol->setAgingModeRGB(1020, 1020, 1020);
        //tconcontrol->setAgingModeRGB(1022, 1022, 1022);
        //tconcontrol->setAgingModeRGB(1023, 1023, 1023);

        //Sleep(500);
        //result = meter->triggerMeasurementInXYZ();
}
//---------------------------------------------------------------------------

void __fastcall TMeasureWindow::Button4Click(TObject *Sender)
{
	using namespace cms::measure;
	using namespace Indep;
	bptr < IntensityAnalyzerIF > analyzer = MainForm->initAnalyzer();
	bptr < MeterMeasurement > mm = analyzer->getMeterMeasurement();
	bptr < cms::measure::meter::Meter > meter = mm->getMeter();

        double_array result;

        tconcontrol->setTconAgingMode(false);
        tconcontrol->setDG(false);
        tconcontrol->setGammaTest(true);
	//tconcontrol->setTconAgingMode(true);

        //Sleep();
        //setRGB(512, 512, 512);
        tconcontrol->setDirectGammaRGB(4080, 4080, 4080);
        //tconcontrol->setDirectGammaRGB(4095, 4095, 4095);
        //tconcontrol->setDirectGammaRGB(4064, 4064, 4064);

        Sleep(500);
        result = meter->triggerMeasurementInXYZ();
}
//---------------------------------------------------------------------------


void __fastcall TMeasureWindow::Button5Click(TObject *Sender)
{
        tconcontrol->setAgingModeRGB(1020, 1020, 1020);
}
//---------------------------------------------------------------------------

void __fastcall TMeasureWindow::Button7Click(TObject *Sender)
{
        tconcontrol->setTconPGMode(true);
}
//---------------------------------------------------------------------------

void __fastcall TMeasureWindow::Button6Click(TObject *Sender)
{
        tconcontrol->setAgingModeRGB(1020, 1020, 1020);
}
//---------------------------------------------------------------------------

void __fastcall TMeasureWindow::Button8Click(TObject *Sender)
{
        tconcontrol->setPGModeRGB(1020, 1020, 1020);
}
//---------------------------------------------------------------------------

