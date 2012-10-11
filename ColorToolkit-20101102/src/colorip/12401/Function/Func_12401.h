//---------------------------------------------------------------------------
//     20100608
//   1. Func_12401::DGLUT_Nbr �]�wDG table ��3��table (RGB)��4��table (RGBW)
//   2. Func_12401::DG_EN_Name(), �^��DG enable register���W�l
//   3. Func_12401::OD_EN_Name(), �^��OD enable register���W�l
//   4. Func_12401::ODLUT_IP_Type(), �^��OD �ϥ�AUO(18x18)�άOVender(17x17)��ip
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
                virtual String DG_EN_Name();
                virtual TLUT* SetDGLUT();

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
                virtual String OD_EN_Name();
                virtual TLUT* SetODLUT();
                virtual int ODLUT_IP_Type(); // OD IP TYPE  1: AUO IP , 2: Vender IP

                Func_12401();
};


