//---------------------------------------------------------------------------
//    20090903 version
//---------------------------------------------------------------------------
#include "TCON1.h"
#ifndef TCON_12401H
#define TCON_12401H
//---------------------------------------------------------------------------


class TCON_12401:public AbstTCON {
  public:
    //device
    virtual TBit * SetDevChkBx();
    virtual TBit *SetDevCboBx();
    virtual TBit2 *SetDevLblE2();

    //status
    virtual TBit *SetStaCboBx();
    virtual TBit2 *SetStaLblE2();

    //input/output
    virtual TBit *SetIOChkBx();
    virtual TBit *SetIOCboBx();
    //driving
    virtual TBit *SetDrvChkBx();
    virtual TBit *SetDrvCboBx();
    virtual TBit2 *SetDrvLblE();
    //Timing
    virtual TBit2 *SetTimLblE2();
    virtual TBit3 *SetTimLblE3();

     TCON_12401();
};
 
#endif

