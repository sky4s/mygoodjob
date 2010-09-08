//---------------------------------------------------------------------------
#pragma hdrstop

#include "ImgProc_11307.h"
#include "TCON_11307.h"
#include "auo_11307_address.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

CM_11307::CM_11307()
{
        CMChkBox_Nbr = 3;
        CMCboBox_Nbr = 1;
        CMval_Nbr = 3;
        CMofs_Nbr = 3;
}

TBit* CM_11307::SetChkBx()
{
        TBit* ChkBox = new TBit [CMChkBox_Nbr];
        //chb = new TBit [CMChkBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ChkBox[0],CM_EN);        //
                SetAddr(&ChkBox[1],CM_DEMO);   //
                SetAddr(&ChkBox[2],CM_DEMO_LEFT); //
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBox[0],"CM_EN");
                GetAddr(&ChkBox[1],"CM_DEMO");
                GetAddr(&ChkBox[2],"CM_DEMO_LEFT");
        }
        return ChkBox;

}
TBit* CM_11307::SetCboBx()
{
        TBit* CboBox = new TBit [CMCboBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&CboBox[0],CM_SEL);     //
        }else if(MainForm->addr_place == 1){
                GetAddr(&CboBox[0],"CM_SEL");
        }
        CboBox[0].choice_nbr = 4;
        CboBox[0].choice = new String [4];
        CboBox[0].choice[0] = "by pass";
        CboBox[0].choice[1] = "CM1";
        CboBox[0].choice[2] = "CM2";
        CboBox[0].choice[3] = "CM3";
        return CboBox;
}
TLUT* CM_11307::Setval()
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

TLUT* CM_11307::Setofs()
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
int CM_11307::Setofs_type()
{
        return 4;
}
//-------------------------------------------------------------------------//
//              Sharpness                                                  //
//-------------------------------------------------------------------------//
SP_11307::SP_11307()
{
        SPChkBox_Nbr = 6;
        SPScrollBar_Nbr = 4;
        SPLblE2_Nbr = 0;
}
TBit* SP_11307::SetChkBx()
{
        TBit* ChkBox = new TBit [SPChkBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ChkBox[0],SP_EN);        //
                SetAddr(&ChkBox[1],SP_DEMO);      //
                SetAddr(&ChkBox[2],TEXT_DET);     //
                SetAddr(&ChkBox[3],SP_DEMO_LEFT); //
                SetAddr(&ChkBox[4],SP_DEB);       //
                SetAddr(&ChkBox[5],SP_MASK_EN);       //
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBox[0],"SP_EN");
                GetAddr(&ChkBox[1],"SP_DEMO");
                GetAddr(&ChkBox[2],"TEXT_DET");
                GetAddr(&ChkBox[3],"SP_DEMO_LEFT");
                GetAddr(&ChkBox[4],"SP_DEB");
                GetAddr(&ChkBox[5],"SP_MASK_EN");
        }
        return ChkBox;
}
TBit* SP_11307::SetScrollBar()
{
        TBit* ScrlB = new TBit [SPScrollBar_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ScrlB[0],SP_HORZ_THRESHOLD);//
                SetAddr(&ScrlB[1],SP_VERT_THRESHOLD);//
                SetAddr(&ScrlB[2],SP_EDGE_THRESHOLD);//
                SetAddr(&ScrlB[3],GLB_STR);          //
        }else if(MainForm->addr_place == 1){
                GetAddr(&ScrlB[0],"SP_HORZ_THRESHOLD");
                GetAddr(&ScrlB[1],"SP_VERT_THRESHOLD");
                GetAddr(&ScrlB[2],"SP_EDGE_THRESHOLD");
                GetAddr(&ScrlB[3],"GLB_STR");
        }
        return ScrlB;        
}

TBit2* SP_11307::SetLblE2()                     //Add by Michelle 20100702             
{
        TBit2* LEdt = new TBit2 [SPLblE2_Nbr];                                 

        if(MainForm->addr_place == 0){
         //       SetAddr(&LEdt[0],SP_VACTIVE);                     //
        
        }else if(MainForm->addr_place == 1){
         //       GetAddr(&LEdt[0],"SP_VACTIVE(0~4095)");           

        }
        return LEdt;
}

TLUT* SP_11307::SetSPLUT()
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

CE_11307::CE_11307()
{
        CEChkBox_Nbr = 9;
        CECboBox_Nbr = 5;
        CEScrollBar_Nbr = 14;
}

TBit* CE_11307::SetChkBx()
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
                SetAddr(&ChkBox[8],LC_DEMO_LEFT);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBox[0],"LC_EN");
                GetAddr(&ChkBox[1],"LC_DEMO");
                GetAddr(&ChkBox[2],"PURITYWT_EN");
                GetAddr(&ChkBox[3],"FASTCHG_EN");
                GetAddr(&ChkBox[4],"SPRS_BLK1");
                GetAddr(&ChkBox[5],"SPRS_BLK0");
                GetAddr(&ChkBox[6],"GRAD_EN");
                GetAddr(&ChkBox[7],"MLC_EN");
                GetAddr(&ChkBox[8],"LC_DEMO_LEFT");
        }
        return ChkBox;
}
TBit* CE_11307::SetCboBx()
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
TBit* CE_11307::SetScrollBar()
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
TLUT* CE_11307::SetJNDlut()
{
        TLUT* lut = new TLUT [1];
        if(MainForm->addr_place == 0){
                SetAddr(&lut[0],JND_LUT);
        }else if(MainForm->addr_place == 1){
                GetAddr(&lut[0],"JND_LUT");
        }
        return lut;
}
TLUT* CE_11307::SetSTlut()
{
        TLUT* lut = new TLUT [1];
        if(MainForm->addr_place == 0){
                SetAddr(&lut[0],ST_LUT);
        }else if(MainForm->addr_place == 1){
                GetAddr(&lut[0],"ST_LUT");
        }
        return lut;
}
TLUT* CE_11307::SetMAXlut()
{
        TLUT* lut = new TLUT [1];
        if(MainForm->addr_place == 0){
                SetAddr(&lut[0],MAX_LUT);
        }else if(MainForm->addr_place == 1){
                GetAddr(&lut[0],"MAX_LUT");
        }
        return lut;
}
TLUT* CE_11307::SetMINlut()
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
HSV_11307::HSV_11307()
{
        HSVChkBox_Nbr = 4;
}

TBit* HSV_11307::SetChkBx()
{
        TBit* ChkBx = new TBit[HSVChkBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ChkBx[0],HUE_EN);         //
                SetAddr(&ChkBx[1],HUE_DEMO);    //
                SetAddr(&ChkBx[2],HUE_DEMO_LEFT);  //
                SetAddr(&ChkBx[3],V_OFS_EN);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBx[0],"HUE_EN");
                GetAddr(&ChkBx[1],"HUE_DEMO");
                GetAddr(&ChkBx[2],"HUE_DEMO_LEFT");
                GetAddr(&ChkBx[3],"V_OFS_EN");
        }
        return ChkBx;
}
TLUT* HSV_11307::SetLUT()
{
        TLUT* lut = new TLUT[1];
        if(MainForm->addr_place == 0){
                SetAddr(&lut[0],HSVlut);           //
        }else if(MainForm->addr_place == 1){
                GetAddr(&lut[0],"HSVlut");
        }
        return lut;
}
String HSV_11307::HSV_EN_Name()
{
        return HSV_FUNC_EN_NAME;
}


//---------------------------------------------------------------------
//      C3D
//--------------------------------------------------------------------------
C3D_11307_777::C3D_11307_777()
{
        C3DChkBox_Nbr = 3;
        C3DLUT_Nbr = 3;

}
TBit* C3D_11307_777::SetChkBx()
{
        TBit* ChkBx = new TBit[C3DChkBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ChkBx[0],C3D_777_EN);
                SetAddr(&ChkBx[1],C3D_777_DEMO);
                SetAddr(&ChkBx[2],C3D_777_DEMO_LEFT);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBx[0],"C3D_777_EN");
                GetAddr(&ChkBx[1],"C3D_777_DEMO");
                GetAddr(&ChkBx[2],"C3D_777_DEMO_LEFT");
        }
        return ChkBx;
}
TLUT* C3D_11307_777::SetLUT()
{
        TLUT* lut = new TLUT[C3DLUT_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&lut[0],C3D_777_LUTR);
                SetAddr(&lut[1],C3D_777_LUTG);
                SetAddr(&lut[2],C3D_777_LUTB);
                // SetAddr(&lut[3],C3D_LUTW);
        }else if(MainForm->addr_place == 1){
                GetAddr(&lut[0],"C3D_777_LUTR");
                GetAddr(&lut[1],"C3D_777_LUTG");
                GetAddr(&lut[2],"C3D_777_LUTB");
                //GetAddr(&lut[3],"C3D_LUTW");
        }
        return lut;
}
String C3D_11307_777::C3D_EN_Name()   // 20100608 return C3D enable register name
{
        return C3D_777_FUNC_EN_NAME;
}

////////////////////////////////////////////////////////////////////

C3D_11307_999::C3D_11307_999()
{
        C3DChkBox_Nbr = 3;
        C3DLUT_Nbr = 3;

}
TBit* C3D_11307_999::SetChkBx()
{
        TBit* ChkBx = new TBit[C3DChkBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ChkBx[0],C3D_999_EN);
                SetAddr(&ChkBx[1],C3D_999_DEMO);
                SetAddr(&ChkBx[2],C3D_999_DEMO_LEFT);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBx[0],"C3D_999_EN");
                GetAddr(&ChkBx[1],"C3D_999_DEMO");
                GetAddr(&ChkBx[2],"C3D_999_DEMO_LEFT");
        }
        return ChkBx;
}
TLUT* C3D_11307_999::SetLUT()
{
        TLUT* lut = new TLUT[C3DLUT_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&lut[0],C3D_999_LUTR);
                SetAddr(&lut[1],C3D_999_LUTG);
                SetAddr(&lut[2],C3D_999_LUTB);
                // SetAddr(&lut[3],C3D_LUTW);
        }else if(MainForm->addr_place == 1){
                GetAddr(&lut[0],"C3D_999_LUTR");
                GetAddr(&lut[1],"C3D_999_LUTG");
                GetAddr(&lut[2],"C3D_999_LUTB");
                //GetAddr(&lut[3],"C3D_LUTW");
        }
        return lut;
}
String C3D_11307_999::C3D_EN_Name()   // 20100608 return C3D enable register name
{
        return C3D_999_FUNC_EN_NAME;
}
