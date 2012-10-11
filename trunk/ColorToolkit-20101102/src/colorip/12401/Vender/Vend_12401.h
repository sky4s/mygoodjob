//---------------------------------------------------------------------------
//    20090903 version
//---------------------------------------------------------------------------

#ifndef Vend_12401H
#define Vend_12401H
#include "Vender1.h"

//---------------------------------------------------------------------------
#endif
class Vend_12401:public AbstVender {
  public:
    virtual TBit * SetChkBx();
    virtual TBit *SetCboBx();
    virtual TBit *SetScrollBar();
    virtual TBit2 *SetScrollBar2();

    virtual TBit *SetDebugChkBx();
    virtual TBit *SetDebugCboBx();
    virtual TBit2 *SetDebugLblE2();

    virtual TBit *SetStaCboBx();
    virtual TBit2 *SetStaLblE2();
    virtual TBit2 *SetLblE2();

     Vend_12401();
};
;
