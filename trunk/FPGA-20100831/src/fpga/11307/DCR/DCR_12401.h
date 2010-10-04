//---------------------------------------------------------------------------
#include "DCR1.h"
#ifndef DCR_12401H
#define DCR_12401H
//---------------------------------------------------------------------------
#endif


class DCR_12401:public AbstDCR
{
        public:
                virtual TBit* SetChkBx();
                virtual TBit* SetCboBx();
                virtual TBit* SetScrollBar();
                virtual TBit2* SetScrollBar2();
                //DCR LUT
                virtual TLUT* SetLUT();
                virtual TBit3* SetLblE3();
                //ALS
                virtual TBit* SetALSChkBx();
                virtual TBit* SetALSCboBx();
                virtual TBit* SetALSScrollBar();
                //
                virtual TBit2* SetDCRLblE2();

                virtual TBit* SetHDRCboBx();
                virtual TBit* SetHDRScrollBar();
                virtual TBit2* SetHDRScrollBar2();
                virtual TBit2* SetHDRLblE2();
                virtual String DCR_BL_EN_Name();  // 20100608 return BL enable register name
                virtual String DCR_GLT_EN_Name(); // 20100608 return GLT enable register name
                DCR_12401();                
};
