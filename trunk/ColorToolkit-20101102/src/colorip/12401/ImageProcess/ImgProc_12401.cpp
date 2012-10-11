//---------------------------------------------------------------------------
#pragma hdrstop

#include "ImgProc_12401.h"
#include "TCON_12401.h"
#include "auo_12401_address.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

CM_12401::CM_12401()
{
        CMChkBox_Nbr = 3;
        CMCboBox_Nbr = 1;
        CMval_Nbr = 3;
        CMofs_Nbr = 3;
}

TBit* CM_12401::SetChkBx()
{
        TBit* ChkBox = new TBit [CMChkBox_Nbr];
        //chb = new TBit [CMChkBox_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&ChkBox[0],CM_EN);
                setAddress(&ChkBox[1],CM_DEMO);
               //setAddress(&ChkBox[2],DEMO_LEFT);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&ChkBox[0],"CM_EN");
                setAddressFromFile(&ChkBox[1],"CM_DEMO");
               //setAddressFromFile(&ChkBox[2],"DEMO_LEFT");
        }
        return ChkBox;

}
TBit* CM_12401::SetCboBx()
{
        TBit* CboBox = new TBit [CMCboBox_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&CboBox[0],SEL_CM);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&CboBox[0],"SEL_CM");
        }
        CboBox[0].choice_nbr = 4;
        CboBox[0].choice = new String [4];
        CboBox[0].choice[0] = "by pass";
        CboBox[0].choice[1] = "CM1";
        CboBox[0].choice[2] = "CM2";
        CboBox[0].choice[3] = "CM3";
        return CboBox;
}
TLUT* CM_12401::Setval()
{
        TLUT* LUT = new TLUT [CMval_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&LUT[0],CM1);
                setAddress(&LUT[1],CM2);
                setAddress(&LUT[2],CM3);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&LUT[0],"CM1");
                setAddressFromFile(&LUT[1],"CM2");
                setAddressFromFile(&LUT[2],"CM3");
        }
        return LUT;
}

TLUT* CM_12401::Setofs()
{
        TLUT* LUT = new TLUT [CMofs_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&LUT[0],ofs1);
                setAddress(&LUT[1],ofs2);
                setAddress(&LUT[2],ofs3);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&LUT[0],"ofs1");
                setAddressFromFile(&LUT[1],"ofs2");
                setAddressFromFile(&LUT[2],"ofs3");
        }
        return LUT;
}
int CM_12401::Setofs_type()
{
        return 1;
}
//-------------------------------------------------------------------------//
//              Sharpness                                                  //
//-------------------------------------------------------------------------//
SP_12401::SP_12401()
{
        SPChkBox_Nbr = 6;
        SPScrollBar_Nbr = 4;
}
TBit* SP_12401::SetChkBx()
{
        TBit* ChkBox = new TBit [SPChkBox_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&ChkBox[0],SP_EN);
                setAddress(&ChkBox[1],SP_DEMO);
                setAddress(&ChkBox[2],TEXT_DET);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&ChkBox[0],"SP_EN");
                setAddressFromFile(&ChkBox[1],"SP_DEMO");
                setAddressFromFile(&ChkBox[2],"TEXT_DET");
        }
        return ChkBox;
}
TBit* SP_12401::SetScrollBar()
{
        TBit* ScrlB = new TBit [SPScrollBar_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&ScrlB[0],HORZ_THR);
                setAddress(&ScrlB[1],VERT_THR);
                setAddress(&ScrlB[2],EDGE_THR);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&ScrlB[0],"HORZ_THR");
                setAddressFromFile(&ScrlB[1],"VERT_THR");
                setAddressFromFile(&ScrlB[2],"EDGE_THR");
        }
        return ScrlB;
}
TLUT* SP_12401::SetSPLUT()
{
        TLUT* LUT = new TLUT [1];
        if(MainForm->addr_place == 0){
                setAddress(&LUT[0],SP_LUT);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&LUT[0],"SP_LUT");
        }
        return LUT;
}
//-------------------------------------------------------------------------//
//      Contrast Enhancement                                               //
//-------------------------------------------------------------------------//

CE_12401::CE_12401()
{
        CEChkBox_Nbr = 8;
        CECboBox_Nbr = 5;
        CEScrollBar_Nbr = 14;
}

TBit* CE_12401::SetChkBx()
{
        TBit* ChkBox = new TBit [CEChkBox_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&ChkBox[0],LC_EN);
                setAddress(&ChkBox[1],LC_DEMO);
                setAddress(&ChkBox[2],PURITYWT_EN);
                setAddress(&ChkBox[3],FASTCHG_EN);
                setAddress(&ChkBox[4],SPRS_BLK1);
                setAddress(&ChkBox[5],SPRS_BLK0);
                setAddress(&ChkBox[6],GRAD_EN);
                setAddress(&ChkBox[7],MLC_EN);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&ChkBox[0],"LC_EN");
                setAddressFromFile(&ChkBox[1],"LC_DEMO");
                setAddressFromFile(&ChkBox[2],"PURITYWT_EN");
                setAddressFromFile(&ChkBox[3],"FASTCHG_EN");
                setAddressFromFile(&ChkBox[4],"SPRS_BLK1");
                setAddressFromFile(&ChkBox[5],"SPRS_BLK0");
                setAddressFromFile(&ChkBox[6],"GRAD_EN");
                setAddressFromFile(&ChkBox[7],"MLC_EN");
        }
        return ChkBox;
}
TBit* CE_12401::SetCboBx()
{
        TBit* CboBox = new TBit [CECboBox_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&CboBox[0],MAXLIMT_SEL);
                setAddress(&CboBox[1],PIXHIST_SEL);
                setAddress(&CboBox[2],LOWST_SEL);
                setAddress(&CboBox[3],JND_SEL);
                setAddress(&CboBox[4],ST_SEL);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&CboBox[0],"MAXLIMT_SEL");
                setAddressFromFile(&CboBox[1],"PIXHIST_SEL");
                setAddressFromFile(&CboBox[2],"LOWST_SEL");
                setAddressFromFile(&CboBox[3],"JND_SEL");
                setAddressFromFile(&CboBox[4],"ST_SEL");
        }
        CboBox[0].choice_nbr = 2;
        CboBox[0].choice = new String [2];
        CboBox[0].choice[0] = "No Limit";
        CboBox[0].choice[1] = "Smaller than Max LUT";

        CboBox[1].choice_nbr = 2;
        CboBox[1].choice = new String [2];
        CboBox[1].choice[0] = "RGB";
        CboBox[1].choice[1] = "Y(Luminance)";

        CboBox[2].choice_nbr = 4;
        CboBox[2].choice = new String [4];
        CboBox[2].choice[0] = "Original";
        CboBox[2].choice[1] = "Fast";
        CboBox[2].choice[2] = "Middle";
        CboBox[2].choice[3] = "Slow";

        CboBox[3].choice_nbr = 2;
        CboBox[3].choice = new String [2];
        CboBox[3].choice[0] = "JND LUT";
        CboBox[3].choice[1] = "Pixel Histogram";

        CboBox[4].choice_nbr = 2;
        CboBox[4].choice = new String [2];
        CboBox[4].choice[0] = "ST LUT";
        CboBox[4].choice[1] = "Gradual progress Gamma Curve";
        return CboBox;
}
TBit* CE_12401::SetScrollBar()
{
        TBit* ScrlB = new TBit [CEScrollBar_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&ScrlB[0],PATDET_FRM_NUM);
                setAddress(&ScrlB[1],PATDET_LINE_NUM);
                setAddress(&ScrlB[2],GRAD_GMA_STEP);
                setAddress(&ScrlB[3],GRAD_FRM_STEP);
                setAddress(&ScrlB[4],GRAD_PIXDIFF_THR);
                setAddress(&ScrlB[5],EDG_DIFF_THR);
                setAddress(&ScrlB[6],PIX_DIFF_THR);
                setAddress(&ScrlB[7],STRENGTH_K);
                setAddress(&ScrlB[8],MIN_EDGE);
                setAddress(&ScrlB[9],MLC_THR);
                setAddress(&ScrlB[10],JND_MAX);
                setAddress(&ScrlB[11],JND_MIN);
                setAddress(&ScrlB[12],ST_MAX);
                setAddress(&ScrlB[13],ST_MIN);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&ScrlB[0],"PATDET_FRM_NUM");
                setAddressFromFile(&ScrlB[1],"PATDET_LINE_NUM");
                setAddressFromFile(&ScrlB[2],"GRAD_GMA_STEP");
                setAddressFromFile(&ScrlB[3],"GRAD_FRM_STEP");
                setAddressFromFile(&ScrlB[4],"GRAD_PIXDIFF_THR");
                setAddressFromFile(&ScrlB[5],"EDG_DIFF_THR");
                setAddressFromFile(&ScrlB[6],"PIX_DIFF_THR");
                setAddressFromFile(&ScrlB[7],"STRENGTH_K");
                setAddressFromFile(&ScrlB[8],"MIN_EDGE");
                setAddressFromFile(&ScrlB[9],"MLC_THR");
                setAddressFromFile(&ScrlB[10],"JND_MAX");
                setAddressFromFile(&ScrlB[11],"JND_MIN");
                setAddressFromFile(&ScrlB[12],"ST_MAX");
                setAddressFromFile(&ScrlB[13],"ST_MIN");
        }
        return ScrlB;
}
TLUT* CE_12401::SetJNDlut()
{
        TLUT* lut = new TLUT [1];
        if(MainForm->addr_place == 0){
                setAddress(&lut[0],JND_LUT);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&lut[0],"JND_LUT");
        }
        return lut;
}
TLUT* CE_12401::SetSTlut()
{
        TLUT* lut = new TLUT [1];
        if(MainForm->addr_place == 0){
                setAddress(&lut[0],ST_LUT);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&lut[0],"ST_LUT");
        }
        return lut;
}
TLUT* CE_12401::SetMAXlut()
{
        TLUT* lut = new TLUT [1];
        if(MainForm->addr_place == 0){
                setAddress(&lut[0],MAX_LUT);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&lut[0],"MAX_LUT");
        }
        return lut;
}
TLUT* CE_12401::SetMINlut()
{
        TLUT* lut = new TLUT [1];
        if(MainForm->addr_place == 0){
                setAddress(&lut[0],MIN_LUT);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&lut[0],"MIN_LUT");
        }
        return lut;
}
//--------------------------------------------------------------------------
//      Hue/ Saturation
//--------------------------------------------------------------------------
HSV_12401::HSV_12401()
{
        HSVChkBox_Nbr = 2;
}

TBit* HSV_12401::SetChkBx()
{
        TBit* ChkBx = new TBit[HSVChkBox_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&ChkBx[0],HUE_EN);
                setAddress(&ChkBx[1],HUE_DEMO);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&ChkBx[0],"HUE_EN");
                setAddressFromFile(&ChkBx[1],"HUE_DEMO");
        }
        return ChkBx;
}
TLUT* HSV_12401::SetLUT()
{
        TLUT* lut = new TLUT[1];
        if(MainForm->addr_place == 0){
                setAddress(&lut[0],HSVlut);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&lut[0],"HSVlut");
        }
        return lut;
}
String HSV_12401::HSV_EN_Name()
{
        return HSV_FUNC_EN_NAME;
}

C3D_12401::C3D_12401()
{
        C3DChkBox_Nbr = 2;
        C3DLUT_Nbr = 3;
        //C3DLUT_Nbr = 4;
}
TBit* C3D_12401::SetChkBx()
{
        TBit* ChkBx = new TBit[C3DChkBox_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&ChkBx[0],C3D_EN);
                setAddress(&ChkBx[1],C3D_DEMO);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&ChkBx[0],"C3D_EN");
                setAddressFromFile(&ChkBx[1],"C3D_DEMO");
        }
        return ChkBx;
}
TLUT* C3D_12401::SetLUT()
{
        TLUT* lut = new TLUT[C3DLUT_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&lut[0],C3D_LUTR);
                setAddress(&lut[1],C3D_LUTG);
                setAddress(&lut[2],C3D_LUTB);
               // setAddress(&lut[3],C3D_LUTW);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&lut[0],"C3D_LUTR");
                setAddressFromFile(&lut[1],"C3D_LUTG");
                setAddressFromFile(&lut[2],"C3D_LUTB");
               // setAddressFromFile(&lut[3],"C3D_LUTW");
        }
        return lut;
}
String C3D_12401::C3D_EN_Name()   // 20100608 return C3D enable register name
{        return C3D_FUNC_EN_NAME; }
