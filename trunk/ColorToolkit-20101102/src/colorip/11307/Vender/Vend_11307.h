//---------------------------------------------------------------------------
//    20090903 version
//---------------------------------------------------------------------------

#ifndef Vend_11307H
#define Vend_11307H
#include "Vender1.h"

//---------------------------------------------------------------------------

class Vend_11307:public AbstVender {
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

     Vend_11307();
};
#endif

