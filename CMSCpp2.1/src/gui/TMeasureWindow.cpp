//---------------------------------------------------------------------------


#include <includeall.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TMeasureWindow.h"

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
}

//---------------------------------------------------------------------------
void __fastcall TMeasureWindow::FormKeyPress(TObject * Sender, char &Key)
{


    switch (Key) {
    case 27:			//esc
	this->Close();
	break;
    case 32:			//space
	this->Button1->Visible = true;
    }
}

//---------------------------------------------------------------------------


void TMeasureWindow::setRGB(int r, int g, int b)
{
    if (true == tconinput) {
	tconcontrol->setTestRGB(r, g, b);
    } else {
	int color = (b << 16) + (g << 8) + r;
	this->Color = (TColor) color;
    }
    //this->Update();
}

void TMeasureWindow::setRGB(bptr < Dep::RGBColor > rgb)
{
    double_array values(new double[3]);
    if (true == tconinput) {
	rgb->getValues(values, tconcontrol->getLUTBit());
    } else {
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
    setRGB(128, 0, 128);
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
    this->Visible = visible;
    if (tconinput) {
	tconcontrol->setGammaTest(visible);
    }
};

//---------------------------------------------------------------------------
void TMeasureWindow::addWindowListener(bptr < cms::util::WindowListener >
				       listener)
{
    listenerVector.push_back(listener);
}

//---------------------------------------------------------------------------


void __fastcall TMeasureWindow::FormClose(TObject * Sender,
					  TCloseAction & Action)
{
    foreach(bptr < cms::util::WindowListener > listener, listenerVector) {
	listener->windowClosing();
    }
}

//---------------------------------------------------------------------------

