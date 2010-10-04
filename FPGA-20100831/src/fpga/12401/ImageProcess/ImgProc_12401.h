//---------------------------------------------------------------------------
//    20100608
//   ·s¼Wclass C3D_12401{...}
//---------------------------------------------------------------------------
#include "CM1.h"
#include "Sharpness1.h"
#include "ContrastEnhance1.h"
#include "HueSatVal1.h"
#include "C3D1.h"
#ifndef ImgProc_12401H
#define ImgProc_12401H
//---------------------------------------------------------------------------
#endif

class CM_12401: public AbstCM
{
        public:
                //CM
//                virtual TBit* SetChkBx();
                virtual TBit* SetChkBx();
                virtual TBit* SetCboBx();
                virtual TLUT* Setval();
                virtual TLUT* Setofs();
                virtual int Setofs_type();

                CM_12401();
};

class SP_12401: public AbstSP
{
        public:
                virtual TBit* SetChkBx();
                virtual TBit* SetScrollBar();
                virtual TLUT* SetSPLUT();

                SP_12401();
};

class CE_12401: public AbstCE
{
        public:
                virtual TBit* SetChkBx();
                virtual TBit* SetCboBx();
                virtual TBit* SetScrollBar();
                virtual TLUT* SetJNDlut();
                virtual TLUT* SetSTlut();
                virtual TLUT* SetMAXlut();
                virtual TLUT* SetMINlut();
                CE_12401();
};
class HSV_12401: public AbstHSV
{
        public:
                virtual TBit* SetChkBx();
                virtual TLUT* SetLUT();
                virtual String HSV_EN_Name();  // return the name of HSV_EN register
                HSV_12401();
};
class C3D_12401: public AbstC3D
{
        public:
                virtual TBit* SetChkBx();
                virtual TLUT* SetLUT();
                virtual String C3D_EN_Name(); // 20100608 return C3D enable register name
                C3D_12401();
};

