//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "THSVAdjustFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
THSVAdjustFrame *HSVAdjustFrame;
//---------------------------------------------------------------------------
__fastcall THSVAdjustFrame::THSVAdjustFrame(TComponent * Owner)
:TFrame(Owner)
{
    using namespace gui::util;

    hueSetter = bptr < HueSetter > (new HueSetter(lb_c3d_Manual39_h, sb_c3d_Manual39_h));
    binder.bind(lb_c3d_Manual39_h, sb_c3d_Manual39_h, hueSetter);

    saturationSetter = bptr < SaturationSetter > (new SaturationSetter(lb_c3d_Manual39_s, sb_c3d_Manual39_s,
						      edt_c3d_satC->Text.ToDouble(), null));
}

//---------------------------------------------------------------------------

void __fastcall THSVAdjustFrame::sb_c3d_Manual39_hChange(TObject * Sender)
{
    binder.active(Sender);
}

//---------------------------------------------------------------------------
void THSVAdjustFrame::setHSV(double h, double s, double v)
{
    this->h = h;

    this->s = s;

    this->v = v;
};

