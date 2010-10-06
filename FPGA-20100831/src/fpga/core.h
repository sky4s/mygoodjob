#ifndef COREH
#define COREH

#include <addresstype/Address_type.h>

class AbstHSV {
  public:
    virtual TBit * SetChkBx() = 0;
    virtual TLUT *SetLUT() = 0;
    virtual String HSV_EN_Name() = 0;	// 20100608 return the name of HSV_EN register
    int HSVChkBox_Nbr;
};

#endif
 
