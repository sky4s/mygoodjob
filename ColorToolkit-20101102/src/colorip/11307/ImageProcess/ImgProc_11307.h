//---------------------------------------------------------------------------
//    20100608
//   ·s¼Wclass C3D_12401{...}
//---------------------------------------------------------------------------

#ifndef ImgProc_11307H
#define ImgProc_11307H
#include <colorip/gui_class.h>
//---------------------------------------------------------------------------


class CM_11307:public AbstCM {
  public:
    //CM
    virtual TBit * SetChkBx();
    virtual TBit *SetCboBx();
    virtual TLUT *Setval();
    virtual TLUT *Setofs();
    virtual int Setofs_type();

     CM_11307();
};

class SP_11307:public AbstSP {
  public:
    virtual TBit * SetChkBx();
    virtual TBit *SetScrollBar();
    virtual TLUT *SetSPLUT();
    virtual TBit2 *SetLblE2();	//Add by Michelle 20100702
    virtual TBit3 *SetLblE3();
    virtual TBit *SetCboBx();

     SP_11307();
};

class SP_12307:public AbstSP {
  public:
    virtual TBit * SetChkBx();
    virtual TBit *SetScrollBar();
    virtual TLUT *SetSPLUT();
    virtual TBit2 *SetLblE2();
    virtual TBit3 *SetLblE3();
    virtual TBit *SetCboBx();

     SP_12307();
};

class CE_11307:public AbstCE {
  public:
    virtual TBit * SetChkBx();
    virtual TBit *SetCboBx();
    virtual TBit *SetScrollBar();
    virtual TLUT *SetJNDlut();
    virtual TLUT *SetSTlut();
    virtual TLUT *SetMAXlut();
    virtual TLUT *SetMINlut();
     CE_11307();
};

class HSV_11307:public AbstHSV {
  public:
    virtual TBit * SetChkBx();
    virtual TLUT *SetLUT();
    virtual String HSV_EN_Name();	// return the name of HSV_EN register
    //virtual TBit *SetScrollBar();
     HSV_11307();
};

class C3D_11307_777:public AbstC3D {
  public:
    virtual TBit * SetChkBx();
    virtual TLUT *SetLUT();
    virtual String C3D_EN_Name();	// 20100608 return C3D enable register name
     C3D_11307_777();
};
class C3D_11307_999:public AbstC3D {
  public:
    virtual TBit * SetChkBx();
    virtual TLUT *SetLUT();
    virtual String C3D_EN_Name();	// 20100608 return C3D enable register name
     C3D_11307_999();
};

#endif

