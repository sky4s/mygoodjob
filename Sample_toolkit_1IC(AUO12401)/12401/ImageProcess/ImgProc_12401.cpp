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
                SetAddr(&ChkBox[0],CM_EN);
                SetAddr(&ChkBox[1],CM_DEMO);
               //SetAddr(&ChkBox[2],DEMO_LEFT);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBox[0],"CM_EN");
                GetAddr(&ChkBox[1],"CM_DEMO");
               //GetAddr(&ChkBox[2],"DEMO_LEFT");
        }
        return ChkBox;

}
TBit* CM_12401::SetCboBx()
{
        TBit* CboBox = new TBit [CMCboBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&CboBox[0],SEL_CM);
        }else if(MainForm->addr_place == 1){
                GetAddr(&CboBox[0],"SEL_CM");
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
                SetAddr(&LUT[0],CM1);
                SetAddr(&LUT[1],CM2);
                SetAddr(&LUT[2],CM3);
        }else if(MainForm->addr_place == 1){
                GetAddr(&LUT[0],"CM1");
                GetAddr(&LUT[1],"CM2");
                GetAddr(&LUT[2],"CM3");
        }
        return LUT;
}

TLUT* CM_12401::Setofs()
{
        TLUT* LUT = new TLUT [CMofs_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&LUT[0],ofs1);
                SetAddr(&LUT[1],ofs2);
                SetAddr(&LUT[2],ofs3);
        }else if(MainForm->addr_place == 1){
                GetAddr(&LUT[0],"ofs1");
                GetAddr(&LUT[1],"ofs2");
                GetAddr(&LUT[2],"ofs3");
        }
        return LUT;
}
int CM_12401::Setofs_type()
{
        return 2;
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
                SetAddr(&ChkBox[0],SP_EN);
                SetAddr(&ChkBox[1],SP_DEMO);
                SetAddr(&ChkBox[2],TEXT_DET);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBox[0],"SP_EN");
                GetAddr(&ChkBox[1],"SP_DEMO");
                GetAddr(&ChkBox[2],"TEXT_DET");
        }
        return ChkBox;
}
TBit* SP_12401::SetScrollBar()
{
        TBit* ScrlB = new TBit [SPScrollBar_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ScrlB[0],HORZ_THR);
                SetAddr(&ScrlB[1],VERT_THR);
                SetAddr(&ScrlB[2],EDGE_THR);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ScrlB[0],"HORZ_THR");
                GetAddr(&ScrlB[1],"VERT_THR");
                GetAddr(&ScrlB[2],"EDGE_THR");
        }
        return ScrlB;
}
TLUT* SP_12401::SetSPLUT()
{
        TLUT* LUT = new TLUT [1];
        if(MainForm->addr_place == 0){
                SetAddr(&LUT[0],SP_LUT);
        }else if(MainForm->addr_place == 1){
                GetAddr(&LUT[0],"SP_LUT");
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
                SetAddr(&ChkBox[0],LC_EN);
                SetAddr(&ChkBox[1],LC_DEMO);
                SetAddr(&ChkBox[2],PURITYWT_EN);
                SetAddr(&ChkBox[3],FASTCHG_EN);
                SetAddr(&ChkBox[4],SPRS_BLK1);
                SetAddr(&ChkBox[5],SPRS_BLK0);
                SetAddr(&ChkBox[6],GRAD_EN);
                SetAddr(&ChkBox[7],MLC_EN);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBox[0],"LC_EN");
                GetAddr(&ChkBox[1],"LC_DEMO");
                GetAddr(&ChkBox[2],"PURITYWT_EN");
                GetAddr(&ChkBox[3],"FASTCHG_EN");
                GetAddr(&ChkBox[4],"SPRS_BLK1");
                GetAddr(&ChkBox[5],"SPRS_BLK0");
                GetAddr(&ChkBox[6],"GRAD_EN");
                GetAddr(&ChkBox[7],"MLC_EN");
        }
        return ChkBox;
}
TBit* CE_12401::SetCboBx()
{
        TBit* CboBox = new TBit [CECboBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&CboBox[0],MAXLIMT_SEL);
                SetAddr(&CboBox[1],PIXHIST_SEL);
                SetAddr(&CboBox[2],LOWST_SEL);
                SetAddr(&CboBox[3],JND_SEL);
                SetAddr(&CboBox[4],ST_SEL);
        }else if(MainForm->addr_place == 1){
                GetAddr(&CboBox[0],"MAXLIMT_SEL");
                GetAddr(&CboBox[1],"PIXHIST_SEL");
                GetAddr(&CboBox[2],"LOWST_SEL");
                GetAddr(&CboBox[3],"JND_SEL");
                GetAddr(&CboBox[4],"ST_SEL");
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
                SetAddr(&ScrlB[0],PATDET_FRM_NUM);
                SetAddr(&ScrlB[1],PATDET_LINE_NUM);
                SetAddr(&ScrlB[2],GRAD_GMA_STEP);
                SetAddr(&ScrlB[3],GRAD_FRM_STEP);
                SetAddr(&ScrlB[4],GRAD_PIXDIFF_THR);
                SetAddr(&ScrlB[5],EDG_DIFF_THR);
                SetAddr(&ScrlB[6],PIX_DIFF_THR);
                SetAddr(&ScrlB[7],STRENGTH_K);
                SetAddr(&ScrlB[8],MIN_EDGE);
                SetAddr(&ScrlB[9],MLC_THR);
                SetAddr(&ScrlB[10],JND_MAX);
                SetAddr(&ScrlB[11],JND_MIN);
                SetAddr(&ScrlB[12],ST_MAX);
                SetAddr(&ScrlB[13],ST_MIN);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ScrlB[0],"PATDET_FRM_NUM");
                GetAddr(&ScrlB[1],"PATDET_LINE_NUM");
                GetAddr(&ScrlB[2],"GRAD_GMA_STEP");
                GetAddr(&ScrlB[3],"GRAD_FRM_STEP");
                GetAddr(&ScrlB[4],"GRAD_PIXDIFF_THR");
                GetAddr(&ScrlB[5],"EDG_DIFF_THR");
                GetAddr(&ScrlB[6],"PIX_DIFF_THR");
                GetAddr(&ScrlB[7],"STRENGTH_K");
                GetAddr(&ScrlB[8],"MIN_EDGE");
                GetAddr(&ScrlB[9],"MLC_THR");
                GetAddr(&ScrlB[10],"JND_MAX");
                GetAddr(&ScrlB[11],"JND_MIN");
                GetAddr(&ScrlB[12],"ST_MAX");
                GetAddr(&ScrlB[13],"ST_MIN");
        }
        return ScrlB;
}
TLUT* CE_12401::SetJNDlut()
{
        TLUT* lut = new TLUT [1];
        if(MainForm->addr_place == 0){
                SetAddr(&lut[0],JND_LUT);
        }else if(MainForm->addr_place == 1){
                GetAddr(&lut[0],"JND_LUT");
        }
        return lut;
}
TLUT* CE_12401::SetSTlut()
{
        TLUT* lut = new TLUT [1];
        if(MainForm->addr_place == 0){
                SetAddr(&lut[0],ST_LUT);
        }else if(MainForm->addr_place == 1){
                GetAddr(&lut[0],"ST_LUT");
        }
        return lut;
}
TLUT* CE_12401::SetMAXlut()
{
        TLUT* lut = new TLUT [1];
        if(MainForm->addr_place == 0){
                SetAddr(&lut[0],MAX_LUT);
        }else if(MainForm->addr_place == 1){
                GetAddr(&lut[0],"MAX_LUT");
        }
        return lut;
}
TLUT* CE_12401::SetMINlut()
{
        TLUT* lut = new TLUT [1];
        if(MainForm->addr_place == 0){
                SetAddr(&lut[0],MIN_LUT);
        }else if(MainForm->addr_place == 1){
                GetAddr(&lut[0],"MIN_LUT");
        }
        return lut;
}
//--------------------------------------------------------------------------
//      Hue/ Saturation
//--------------------------------------------------------------------------
HSV_12401::HSV_12401()
{
        HSVChkBox_Nbr = 1;
}
TBit HSV_12401::SetEn()
{
        TBit en;
        if(MainForm->addr_place == 0){
                SetAddr(&en,HUE_EN);
        }else if(MainForm->addr_place == 1){
                GetAddr(&en,"HUE_EN");
        }
        return en;
}
TBit* HSV_12401::SetChkBx()
{
        TBit* ChkBx = new TBit[HSVChkBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ChkBx[0],HUE_DEMO);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBx[0],"HUE_DEMO");
        }
        return ChkBx;
}
TLUT* HSV_12401::SetLUT()
{
        TLUT* lut = new TLUT[1];
        if(MainForm->addr_place == 0){
                SetAddr(&lut[0],HSVlut);
        }else if(MainForm->addr_place == 1){
                GetAddr(&lut[0],"HSVlut");
        }
        return lut;
}

