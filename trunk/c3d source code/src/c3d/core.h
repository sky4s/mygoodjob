#ifndef COREH
#define COREH

//C系統文件

//C++系統文件

//vcl庫頭文件
#include <vcl.h>
//其他庫頭文件

//本項目內頭文件
#include <addresstype/Address_type.h>
//本項目內gui頭文件


class _CHKB {
  public:
    __fastcall ~ _CHKB() {
	delete[]Chkb;
	//delete Addr.choice;
    };
    TCheckBox *Chkb;
    TBit Addr;
};

/*__fastcall _CHKB::~_CHKB()
{
    delete[]Chkb;
    //delete Addr.choice;
}*/

class _CBOB {
  public:
    __fastcall ~ _CBOB();
    TComboBox *Cbob;
    TLabel *CbobL;
    TBit Addr;
};
__fastcall _CBOB::~_CBOB()
{
    delete[]Cbob;
    delete[]CbobL;
    //delete Addr.choice;
}

class _CBOB2			//Address 為 2Byte
{
  public:
    __fastcall ~ _CBOB2();
    TComboBox *Cbob;
    TLabel *CbobL;
    TBit2 Addr;
};
__fastcall _CBOB2::~_CBOB2()
{
    delete[]Cbob;
    delete[]CbobL;
    //delete Addr.choice;
}

class _LBLE2			//Address 為 2Byte
{
  public:
    __fastcall ~ _LBLE2();
    TLabeledEdit *Lble;
    TBit2 Addr;
};
__fastcall _LBLE2::~_LBLE2()
{
    delete[]Lble;
    //delete Addr.choice;
}

class _LBLE			//Address 為 1 byte
{
  public:
    __fastcall ~ _LBLE();
    TLabeledEdit *Lble;
    TBit Addr;
};
__fastcall _LBLE::~_LBLE()
{
    delete[]Lble;
    //delete Addr.choice;
}

class _ScrollBar2		//Address 為 2Byte
{
  public:
    __fastcall ~ _ScrollBar2();
    TLabel *Lbl;
    TScrollBar *ScrlB;
    TStaticText *StTxt;
    TBit2 Addr;
};
__fastcall _ScrollBar2::~_ScrollBar2()
{
    delete[]Lbl;
    delete[]StTxt;
    delete[]ScrlB;
    //delete Addr.choice;
}

class _ScrollBar		//Address 為 1 byte
{
  public:
    __fastcall ~ _ScrollBar();
    TLabel *Lbl;
    TScrollBar *ScrlB;
    TStaticText *StTxt;
    TBit Addr;
};
__fastcall _ScrollBar::~_ScrollBar()
{
    delete[]Lbl;
    delete[]StTxt;
    delete[]ScrlB;
    //delete Addr.choice;
}

class _StaticText		//Address 為 1 byte
{
  public:
    __fastcall ~ _StaticText();
    TStaticText *StTxt;
    TBit Addr;
};
__fastcall _StaticText::~_StaticText()
{
    delete[]StTxt;
    //delete Addr.choice;
}

class AbstC3D {
  public:
    virtual TBit SetEn() = 0;
    virtual TBit *SetChkBx() = 0;
    virtual TLUT *SetLUT() = 0;
};

void rgb2h(double r, double g, double b, double *h)
{
    r = r / 255;
    g = g / 255;
    b = b / 255;
    double div = pow(pow(r - g, 2) + (r - b) * (g - b), 0.5);
    div = (div <= 0 ? 0.00001 : div);
    double tmp = 0.5 * ((r - g) + (r - b)) / div;
    if (tmp > 1)
	tmp = 1;
    else if (tmp < -1)
	tmp = -1;
    *h = acos(tmp) * 180 / 3.14159265;
    if (b > g)
	*h = 360 - *h;
}

//rgb <-> hsv
void rgb2hsv(double r, double g, double b, double *h, double *s, double *i, double *v)
{
    *i = (r + g + b) / 3;
    double max = (r > g ? r : g);
    max = (b > max ? b : max);
    *v = max;
    double min = (r < g ? r : g);
    min = (min < b ? min : b);
    double d = max - min;
    *s = d;
    d = (d == 0 ? d + 256 : d);

    if (max == 0)
	*s = 0;
    else
	*s = *s / max;

    if (s == 0)
	*h = 0;
    else {
	if (max == r)
	    *h = 60 * (g - b) / d;
	else if (max == g)
	    *h = 60 * (b - r) / d + 120;
	else if (max == b)
	    *h = 60 * (r - g) / d + 240;
	*h = fmod(*h + 360, 360);
    }

}

void hsv2rgb(double h, double s, double v, double *r, double *g, double *b)
{
    s = (s < 0 ? 0 : s);
    s = (s > 1 ? 1 : s);
    v = (v < 0 ? 0 : v);
    v = (v > 255 ? 255 : v);
    h = (h > 360 ? 360 : h);
    h = (h < 0 ? h + 360 : h);
    int hi = int (floor(h / 60)) % 6;
    double f = h / 60 - floor(h / 60);
    double p = v * (1 - s);
    double q = v * (1 - f * s);
    double t = v * (1 - (1 - f) * s);
    if (hi == 0) {
	*r = v;
	*g = t;
	*b = p;
    } else if (hi == 1) {
	*r = q;
	*g = v;
	*b = p;
    } else if (hi == 2) {
	*r = p;
	*g = v;
	*b = t;
    } else if (hi == 3) {
	*r = p;
	*g = q;
	*b = v;
    } else if (hi == 4) {
	*r = t;
	*g = p;
	*b = v;
    } else if (hi == 5) {
	*r = v;
	*g = p;
	*b = q;
    }
}

#endif

