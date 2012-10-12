//---------------------------------------------------------------------------

#ifndef SAT_11307H
#define SAT_11307H
#include "TSaturationForm.h"
//---------------------------------------------------------------------------
class SATForm_11307:public AbstSATForm
{
        public:
                virtual TBit* SetChkBx();
                virtual TBit* SetCboBx();
                virtual TBit* SetScrollBar();
                virtual TBit2* SetScrollBar2();
                virtual TBit3* SetLblE3();
                virtual TBit4* SetLblE4();
                SATForm_11307();
};


#endif

