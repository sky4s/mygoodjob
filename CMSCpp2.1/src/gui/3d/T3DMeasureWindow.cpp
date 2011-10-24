//---------------------------------------------------------------------------

#include <includeall.h>
#pragma hdrstop
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "T3DMeasureWindow.h"
#include "T3DMeasurementForm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TThreeDMeasureWindow *ThreeDMeasureWindow;
//---------------------------------------------------------------------------
__fastcall TThreeDMeasureWindow::TThreeDMeasureWindow(TComponent * Owner)
:TForm(Owner), patternGenMode(false), topBottomMode(false)
{
}

//---------------------------------------------------------------------------
void __fastcall TThreeDMeasureWindow::FormKeyPress(TObject * Sender, char &Key)
{
    if (null != keyPressListener) {
	keyPressListener->keyPress(Sender, Key);
    }
}

//---------------------------------------------------------------------------

void TThreeDMeasureWindow::setLeftRGB(int r, int g, int b)
{
    int color = (b << 16) + (g << 8) + r;
    this->Panel1->Color = (TColor) color;
};
void TThreeDMeasureWindow::setRightRGB(int r, int g, int b)
{
    int color = (b << 16) + (g << 8) + r;
    this->Panel2->Color = (TColor) color;
};
void __fastcall TThreeDMeasureWindow::Button1Click(TObject * Sender)
{
    using namespace Dep;
    RGB_ptr left(new RGBColor(255, 255, 255));
    RGB_ptr right(new RGBColor(0, 255, 0));
    this->setLeftRGB(left);
    this->setRightRGB(right);
}

 //---------------------------------------------------------------------------
void TThreeDMeasureWindow::setLeftRGB(RGB_ptr rgb)
{
    setLeftRGB(static_cast < int >(rgb->R), static_cast < int >(rgb->G),
	       static_cast < int >(rgb->B));
}

//---------------------------------------------------------------------------
void TThreeDMeasureWindow::setRightRGB(RGB_ptr rgb)
{
    setRightRGB(static_cast < int >(rgb->R), static_cast < int >(rgb->G),
		static_cast < int >(rgb->B));
}

//---------------------------------------------------------------------------
void TThreeDMeasureWindow::setRGB(RGB_ptr rgb)
{
    setLeftRGB(rgb);
    setRightRGB(rgb);
}


void __fastcall TThreeDMeasureWindow::FormPaint(TObject * Sender)
{
    int width = this->Width;
    int height = this->Height;
    int halfWidth = width / 2;
    int halfHeight = height / 2;

    if (topBottomMode) {
	this->Panel1->Left = 0;
	this->Panel1->Top = 0;
	this->Panel1->Width = width;
	this->Panel1->Height = halfHeight;
	this->Panel2->Left = 0;
	this->Panel2->Top = halfHeight;
	this->Panel2->Width = width;
	this->Panel2->Height = halfHeight;

    } else {
	this->Panel1->Left = 0;
	this->Panel1->Top = 0;
	this->Panel1->Width = halfWidth;
	this->Panel1->Height = height;
	this->Panel2->Left = halfWidth;
	this->Panel2->Top = 0;
	this->Panel2->Width = halfWidth;
	this->Panel2->Height = height;
    }

    Label_TargetAdj2->Visible = !patternGenMode;
    Label_TargetAdj->Visible = patternGenMode;

    Label_StartBase->Visible = !patternGenMode;
    Label_TargetBase->Visible = !patternGenMode;
    Label_StartTarget->Visible = !patternGenMode;
    Label_TargetStart->Visible = !patternGenMode;
    Label_WXtalk->Visible = !patternGenMode;
    Label_BXtalk->Visible = !patternGenMode;
}

//---------------------------------------------------------------------------
void TThreeDMeasureWindow::setKeyPressListener(KeyPressListener * listener)
{
    this->keyPressListener = listener;
}

void __fastcall TThreeDMeasureWindow::FormCreate(TObject * Sender)
{
    /*this->addKeyPressListener(dynamic_cast <
       KeyPressListener * >(ThreeDMeasurementForm)); */
    /*TThreeDMeasurementForm *listener =
       dynamic_cast < TThreeDMeasurementForm * >(ThreeDMeasurementForm); */
    this->setKeyPressListener((KeyPressListener *) ThreeDMeasurementForm);
}

//---------------------------------------------------------------------------

