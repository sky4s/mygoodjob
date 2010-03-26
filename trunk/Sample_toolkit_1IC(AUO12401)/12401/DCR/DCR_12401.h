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
                virtual TLUT* SetLUT();
                virtual TBit3* SetLblE3();

                DCR_12401();                
};
