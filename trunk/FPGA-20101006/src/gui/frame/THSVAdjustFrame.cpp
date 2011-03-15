//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "THSVAdjustFrame.h"

//C系統文件

//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件
#include <gui/event/listener.h>
#include <java/lang.h>
//本項目內gui頭文件
//#includ"THSVForm3.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THSVAdjustFrame *HSVAdjustFrame;
//---------------------------------------------------------------------------
__fastcall THSVAdjustFrame::THSVAdjustFrame(TComponent * Owner)
:TFrame(Owner), settingHSVPosition(false)
{
    using namespace gui::util;
    setHSVEdit(0, .666, 192);
    maxHueValue = 768;
}

//---------------------------------------------------------------------------

void THSVAdjustFrame::sb_HSV_gainChange(TObject * Sender)
{
    using namespace gui::event;
    using namespace java::lang;
    updateHSVCaption();
    if (true == settingHSVPosition) {
	return;
    }

    foreach(bwptr < ChangeListener > listener, changeListenerVector) {
	bptr < ChangeListener > l = listener.lock();
	if (null != l) {
	    l->stateChanged(Sender);
	}
    }
}

void __fastcall THSVAdjustFrame::sb_Hue_gainChange(TObject * Sender)
{
    /*if (false == hgainChange) {
       //如果沒改過, 就儲存default
       lastDefault = sb_Hue_gain->Position;
       hgainChange = true;
       } */
    sb_HSV_gainChange(Sender);
}

void THSVAdjustFrame::updateHSVCaption()
{
    //從scrollbar拉出pos
    int_array hsvPosition = getHSVPosition();
    int h = hsvPosition[0];
    int s = hsvPosition[1];
    int v = hsvPosition[2];

    //從pos計算成實際值並且顯示
    double h_show = ((double) h) / maxHueValue * 360;
    lb_Hue_gain->Caption = lb_Hue_gain->Caption.sprintf("%+.2f°", h_show);
    if (captionIF == null) {
	double s_show = s / 32.;
	lb_Sat_gain->Caption = lb_Sat_gain->Caption.sprintf("%.2f", s_show);
    } else {
	lb_Sat_gain->Caption = captionIF->getSaturationCaption(s);
    }

    lb_Val_gain->Caption = IntToStr(v);
}

void THSVAdjustFrame::setCaptionIF(bptr < CaptionIF > caption)
{
    this->captionIF = caption;
}

void THSVAdjustFrame::setMaxHueValue(int maxHueValue)
{
    this->maxHueValue = maxHueValue;
}

    //---------------------------------------------------------------------------
void THSVAdjustFrame::setHSVEdit(double h, double s, double v)
{
    Edit_c3d_Manual39_h_adj->Text = h;
    Edit_c3d_Manual39_s_adj->Text = s;
    Edit_c3d_Manual39_v_adj->Text = v;
};


void THSVAdjustFrame::addChangeListener(bptr < gui::event::ChangeListener > listener)
{
    bwptr < gui::event::ChangeListener > wptr(listener);
    changeListenerVector.push_back(wptr);
};

double_array THSVAdjustFrame::getHSVGain()
{

    int_array hsvPosition = getHSVPosition();
    double h = hsvPosition[0] - sb_Hue_gain->Max / 2;
    int spos = hsvPosition[1] - sb_Sat_gain->Max / 2;
    double s = (double) spos / 100. / edt_c3d_satC->Text.ToDouble();
    int vpos = hsvPosition[2] - sb_Val_gain->Max / 2;
    double v = (double) vpos / 100. / edt_c3d_valC->Text.ToDouble();

    double_array hsvgain(new double[3]);
    hsvgain[0] = h;
    hsvgain[1] = s;
    hsvgain[2] = v;
    return hsvgain;
};

int_array THSVAdjustFrame::getHSVPosition()
{
    int_array hsv(new int[3]);
    hsv[0] = sb_Hue_gain->Position;
    hsv[1] = sb_Sat_gain->Position;
    hsv[2] = sb_Val_gain->Position;
    return hsv;
}
void THSVAdjustFrame::setHSVPostition(int h, int s, int v)
{
    settingHSVPosition = true;
    sb_Hue_gain->Position = h;
    if (captionIF == null) {
	sb_Sat_gain->Position = s;
    } else {
	sb_Sat_gain->Position = s;
    }
    sb_Val_gain->Position = v;
    settingHSVPosition = false;
}

void THSVAdjustFrame::setHSVPostition(int_array hsvPostition)
{
    setHSVPostition(hsvPostition[0], hsvPostition[1], hsvPostition[2]);
}

void THSVAdjustFrame::setColorAdjustable(bool enable)
{
    sb_Hue_gain->Enabled = enable;
    sb_Sat_gain->Enabled = enable;
};

void THSVAdjustFrame::setTStringGrid(TStringGrid * stringGrid)
{
    this->stringGrid = stringGrid;
}

double_array THSVAdjustFrame::getHSVGain(double h, double s, double v, int row)
{
    if (null != stringGrid) {
	double huse = stringGrid->Cells[1][row].ToDouble();
	double suse = stringGrid->Cells[2][row].ToDouble();
	double vuse = stringGrid->Cells[3][row].ToDouble();

	double hgain = huse - h;
	double sgain = ((suse / s) - 1) * 100 * edt_c3d_satC->Text.ToDouble();
	double vgain = ((vuse / v) - 1) * 100 * edt_c3d_valC->Text.ToDouble();

	double_array hsvgain(new double[3]);
	hsvgain[0] = hgain;
	hsvgain[1] = sgain;
	hsvgain[2] = vgain;
	return hsvgain;
    }
    return nil_double_array;
}

void THSVAdjustFrame::setDefaultHSVPosition(int h, int s, int v)
{
    defaultH = h;
    defaultS = s;
    defaultV = v;
    setHSVPostition(defaultH, defaultS, defaultV);
}

void __fastcall THSVAdjustFrame::Button_HueResetClick(TObject * Sender)
{
    sb_Hue_gain->Position = defaultH;
}

    //---------------------------------------------------------------------------

void __fastcall THSVAdjustFrame::Button_SaturationResetClick(TObject * Sender)
{
    sb_Sat_gain->Position = defaultS;
}

    //---------------------------------------------------------------------------

void __fastcall THSVAdjustFrame::Button_BrightnessResetClick(TObject * Sender)
{
    sb_Val_gain->Position = defaultV;
}

    //---------------------------------------------------------------------------

void __fastcall THSVAdjustFrame::sb_Sat_gainChange(TObject * Sender)
{
    sb_HSV_gainChange(Sender);
}

    //---------------------------------------------------------------------------

void __fastcall THSVAdjustFrame::sb_Val_gainChange(TObject * Sender)
{
    sb_HSV_gainChange(Sender);
}

    //---------------------------------------------------------------------------

void __fastcall THSVAdjustFrame::Button_HueReturnClick(TObject * Sender)
{
    if (true == hgainChange) {
	sb_Hue_gain->Position = lastDefault;
	hgainChange = false;
    }
}

    //---------------------------------------------------------------------------

