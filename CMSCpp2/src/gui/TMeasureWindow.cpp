//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "TMeasureWindow.h"
#include <cms/colorspace/rgb.h>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMeasureWindow *MeasureWindow;
//---------------------------------------------------------------------------
__fastcall TMeasureWindow::TMeasureWindow(TComponent * Owner)
:TForm(Owner)
{
    DoubleBuffered = true;
}

//---------------------------------------------------------------------------
void __fastcall TMeasureWindow::FormKeyPress(TObject * Sender, char &Key)
{
    if (Key == 27) {
	//this->Visible = false;
        this->Close();
    }
}

//---------------------------------------------------------------------------


void TMeasureWindow::setRGB(int r, int g, int b)
{
    int color = (b << 16) + (g << 8) + r;
    this->Color = (TColor) color;
    this->Update();
}

void TMeasureWindow::setRGB(bptr < Dep::RGBColor > rgb)
{
    int r = static_cast < int >(rgb->R);
    int g = static_cast < int >(rgb->G);
    int b = static_cast < int >(rgb->B);
    setRGB(r, g, b);
}

//---------------------------------------------------------------------------

