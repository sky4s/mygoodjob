//---------------------------------------------------------------------------
//     20100608
//   1. Func_12401::DGLUT_Nbr 設定DG table 為3個table (RGB)或4個table (RGBW)
//   2. Func_12401::DG_EN_Name(), 回傳DG enable register的名子
//   3. Func_12401::OD_EN_Name(), 回傳OD enable register的名子
//   4. Func_12401::ODLUT_IP_Type(), 回傳OD 使用AUO(18x18)或是Vender(17x17)的ip
//---------------------------------------------------------------------------
#include "Function1.h"
#ifndef Func_11307H
#define Func_11307H
//---------------------------------------------------------------------------
#endif
class Func_11307:public AbstFunc
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
                  
                Func_11307();
};


