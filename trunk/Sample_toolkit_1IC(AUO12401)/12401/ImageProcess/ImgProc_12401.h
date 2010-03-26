//---------------------------------------------------------------------------
#include "CM1.h"
#include "Sharpness1.h"
#include "ContrastEnhance1.h"
#include "HueSatVal.h"
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
                virtual TBit SetEn();
                virtual TBit* SetChkBx();
                virtual TLUT* SetLUT();
                HSV_12401();
};
