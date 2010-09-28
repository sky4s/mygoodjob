//---------------------------------------------------------------------------
#pragma hdrstop
#include "c3d_12401.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
TBit C3D_12401::SetEn()
{
        TBit en;
        if(MainForm->addr_place == 0){
                SetAddr(&en,C3D_EN);
        }else if(MainForm->addr_place == 1){
                GetAddr(&en,"C3D_EN");
        }
        return en;
}
TBit* C3D_12401::SetChkBx()
{
        TBit* ChkBx = new TBit[C3DChkBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ChkBx[0],C3D_DEMO);
                SetAddr(&ChkBx[1],C3D_DEMO_LEFT);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBx[0],"C3D_DEMO");
                GetAddr(&ChkBx[1],"C3D_DEMO_LEFT");
        }
        return ChkBx;
}
TLUT* C3D_12401::SetLUT()
{
        TLUT* lut = new TLUT[3];
        if(MainForm->addr_place == 0){
                SetAddr(&lut[0],C3D_LUTR);
                SetAddr(&lut[1],C3D_LUTG);
                SetAddr(&lut[2],C3D_LUTB);
        }else if(MainForm->addr_place == 1){
                GetAddr(&lut[0],"C3D_LUTR");
                GetAddr(&lut[1],"C3D_LUTG");
                GetAddr(&lut[2],"C3D_LUTB");
        }
        return lut;
}