//---------------------------------------------------------------------------
//      20100608
//   1. DCR_12401::DCR_BL_EN_Name() �^��BL_EN register���W�l
//   2. DCR_12401::DCR_GLT_EN_Name() �^��GLT_EN register���W�l
//   3. DCR_12401::DCRLUT_Nbr �]�wDCR��Table��, 2 or 3  (in DCR_12401.cpp)
//---------------------------------------------------------------------------

#ifndef DCR_12401H
#define DCR_12401H
#include "DCR1.h"
//---------------------------------------------------------------------------



class DCR_12401:public AbstDCR
{
        public:
                virtual TBit* SetChkBx();
                virtual TBit* SetCboBx();
                virtual TBit* SetScrollBar();
                virtual TBit2* SetScrollBar2();
                virtual TLUT* SetLUT();
                virtual TBit3* SetLblE3();
                virtual TBit4* SetLblE4();
                virtual String DCR_BL_EN_Name();  // 20100608 return BL enable register name
                virtual String DCR_GLT_EN_Name(); // 20100608 return GLT enable register name
                DCR_12401();
};
#endif
