//---------------------------------------------------------------------------
#include "Function1.h"
#ifndef Func_12401H
#define Func_12401H
//---------------------------------------------------------------------------
#endif
class Func_12401:public AbstFunc
{
        public:
                //frc_dg
                virtual TBit* SetFrcDgChkBx();
                virtual TBit* SetFrcDgCboBx();
                virtual TBit* SetFrcDgLblE();

                //P-state
                virtual TBit* SetPstateChkBx();
                virtual TBit* SetPstateCboBx();
                virtual TBit2* SetPstateLblE2();
                
                //AGBS
                virtual TBit* SetAGBSChkBx();
                virtual TBit* SetAGBSCboBx();
                virtual TBit2* SetAGBSLblE2();

                //OD
                virtual TBit* SetODChkBx();
                virtual TBit* SetODCboBx();
                virtual TBit2* SetODCboBx2();
                virtual TBit* SetODScrollBar();

                //DG LUT
                virtual TLUT* SetDGLUT();
                virtual TLUT* SetODLUT1();
                virtual TLUT* SetODLUT2();
                Func_12401();

};


