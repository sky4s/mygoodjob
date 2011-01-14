//---------------------------------------------------------------------------
#include <fpga/includeallfpga.h>
#pragma hdrstop

#include <fpga/11307/TCON/TCON_11307.h>
#include "ImgProc_11307.h"
#include "Unit1.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

CM_11307::CM_11307()
{
    CMChkBox_Nbr = 3;
    CMCboBox_Nbr = 1;
    CMval_Nbr = 3;
    CMofs_Nbr = 3;
}

TBit *CM_11307::SetChkBx()
{
    TBit *ChkBox = new TBit[CMChkBox_Nbr];
    //chb = new TBit [CMChkBox_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&ChkBox[0], CM_EN);	//
	setAddress(&ChkBox[1], CM_DEMO);	//
	setAddress(&ChkBox[2], CM_DEMO_LEFT);	//
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&ChkBox[0], "CM_EN");
	setAddressFromFile(&ChkBox[1], "CM_DEMO");
	setAddressFromFile(&ChkBox[2], "CM_DEMO_LEFT");
    }
    return ChkBox;

}

TBit *CM_11307::SetCboBx()
{
    TBit *CboBox = new TBit[CMCboBox_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&CboBox[0], CM_SEL);	//
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&CboBox[0], "CM_SEL");
    }
    CboBox[0].choice_nbr = 4;
    CboBox[0].choice = new String[4];
    CboBox[0].choice[0] = "by pass";
    CboBox[0].choice[1] = "CM1";
    CboBox[0].choice[2] = "CM2";
    CboBox[0].choice[3] = "CM3";
    return CboBox;
}

TLUT *CM_11307::Setval()
{
    TLUT *LUT = new TLUT[CMval_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&LUT[0], CM1);
	setAddress(&LUT[1], CM2);
	setAddress(&LUT[2], CM3);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&LUT[0], "CM1");
	setAddressFromFile(&LUT[1], "CM2");
	setAddressFromFile(&LUT[2], "CM3");
    }
    return LUT;
}

TLUT *CM_11307::Setofs()
{
    TLUT *LUT = new TLUT[CMofs_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&LUT[0], ofs1);
	setAddress(&LUT[1], ofs2);
	setAddress(&LUT[2], ofs3);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&LUT[0], "ofs1");
	setAddressFromFile(&LUT[1], "ofs2");
	setAddressFromFile(&LUT[2], "ofs3");
    }
    return LUT;
}

int CM_11307::Setofs_type()
{
    if (MainForm->addr_place == 0) {
	return 1;
    } else if (MainForm->addr_place == 1) {
	int_vector_ptr values = getValuesFromFile("OFS_TYPE");
	if (null != values) {
	    return (*values)[0];
	} else {
	    return -1;
	}
    }

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

TBit *SP_11307::SetChkBx()
{
    TBit *ChkBox = new TBit[SPChkBox_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&ChkBox[0], SP_EN);	//
	setAddress(&ChkBox[1], SP_DEMO);	//
	setAddress(&ChkBox[2], TEXT_DET);	//
	setAddress(&ChkBox[3], SP_DEMO_LEFT);	//
	setAddress(&ChkBox[4], SP_DEB);	//
	setAddress(&ChkBox[5], SP_MASK_EN);	//
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&ChkBox[0], "SP_EN");
	setAddressFromFile(&ChkBox[1], "SP_DEMO");
	setAddressFromFile(&ChkBox[2], "TEXT_DET");
	setAddressFromFile(&ChkBox[3], "SP_DEMO_LEFT");
	setAddressFromFile(&ChkBox[4], "SP_DEB");
	setAddressFromFile(&ChkBox[5], "SP_MASK_EN");
    }
    return ChkBox;
}

TBit *SP_11307::SetScrollBar()
{
    TBit *ScrlB = new TBit[SPScrollBar_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&ScrlB[0], SP_HORZ_THRESHOLD);	//
	setAddress(&ScrlB[1], SP_VERT_THRESHOLD);	//
	setAddress(&ScrlB[2], SP_EDGE_THRESHOLD);	//
	setAddress(&ScrlB[3], GLB_STR);	//
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&ScrlB[0], "SP_HORZ_THRESHOLD");
	setAddressFromFile(&ScrlB[1], "SP_VERT_THRESHOLD");
	setAddressFromFile(&ScrlB[2], "SP_EDGE_THRESHOLD");
	setAddressFromFile(&ScrlB[3], "GLB_STR");
    }
    return ScrlB;
}

TBit2 *SP_11307::SetLblE2()	//Add by Michelle 20100702             
{
    TBit2 *LEdt = new TBit2[SPLblE2_Nbr];

    if (MainForm->addr_place == 0) {
	//       setAddress(&LEdt[0],SP_VACTIVE);                     //

    } else if (MainForm->addr_place == 1) {
	//       setAddressFromFile(&LEdt[0],"SP_VACTIVE(0~4095)");           

    }
    return LEdt;
}

TLUT *SP_11307::SetSPLUT()
{
    TLUT *LUT = new TLUT[1];
    if (MainForm->addr_place == 0) {
	setAddress(&LUT[0], SP_LUT);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&LUT[0], "SP_LUT");
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

TBit *CE_11307::SetChkBx()
{
    TBit *ChkBox = new TBit[CEChkBox_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&ChkBox[0], LC_EN);
	setAddress(&ChkBox[1], LC_DEMO);
	setAddress(&ChkBox[2], PURITYWT_EN);
	setAddress(&ChkBox[3], FASTCHG_EN);
	setAddress(&ChkBox[4], SPRS_BLK1);
	setAddress(&ChkBox[5], SPRS_BLK0);
	setAddress(&ChkBox[6], GRAD_EN);
	setAddress(&ChkBox[7], MLC_EN);
	setAddress(&ChkBox[8], LC_DEMO_LEFT);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&ChkBox[0], "LC_EN");
	setAddressFromFile(&ChkBox[1], "LC_DEMO");
	setAddressFromFile(&ChkBox[2], "PURITYWT_EN");
	setAddressFromFile(&ChkBox[3], "FASTCHG_EN");
	setAddressFromFile(&ChkBox[4], "SPRS_BLK1");
	setAddressFromFile(&ChkBox[5], "SPRS_BLK0");
	setAddressFromFile(&ChkBox[6], "GRAD_EN");
	setAddressFromFile(&ChkBox[7], "MLC_EN");
	setAddressFromFile(&ChkBox[8], "LC_DEMO_LEFT");
    }
    return ChkBox;
}

TBit *CE_11307::SetCboBx()
{
    TBit *CboBox = new TBit[CECboBox_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&CboBox[0], MAXLIMT_SEL);
	setAddress(&CboBox[1], PIXHIST_SEL);
	setAddress(&CboBox[2], LOWST_SEL);
	setAddress(&CboBox[3], JND_SEL);
	setAddress(&CboBox[4], ST_SEL);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&CboBox[0], "MAXLIMT_SEL");
	setAddressFromFile(&CboBox[1], "PIXHIST_SEL");
	setAddressFromFile(&CboBox[2], "LOWST_SEL");
	setAddressFromFile(&CboBox[3], "JND_SEL");
	setAddressFromFile(&CboBox[4], "ST_SEL");
    }
    CboBox[0].choice_nbr = 2;
    CboBox[0].choice = new String[2];
    CboBox[0].choice[0] = "No Limit";
    CboBox[0].choice[1] = "Smaller than Max LUT";

    CboBox[1].choice_nbr = 2;
    CboBox[1].choice = new String[2];
    CboBox[1].choice[0] = "RGB";
    CboBox[1].choice[1] = "Y(Luminance)";

    CboBox[2].choice_nbr = 4;
    CboBox[2].choice = new String[4];
    CboBox[2].choice[0] = "Original";
    CboBox[2].choice[1] = "Fast";
    CboBox[2].choice[2] = "Middle";
    CboBox[2].choice[3] = "Slow";

    CboBox[3].choice_nbr = 2;
    CboBox[3].choice = new String[2];
    CboBox[3].choice[0] = "JND LUT";
    CboBox[3].choice[1] = "Pixel Histogram";

    CboBox[4].choice_nbr = 2;
    CboBox[4].choice = new String[2];
    CboBox[4].choice[0] = "ST LUT";
    CboBox[4].choice[1] = "Gradual progress Gamma Curve";
    return CboBox;
}

TBit *CE_11307::SetScrollBar()
{
    TBit *ScrlB = new TBit[CEScrollBar_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&ScrlB[0], PATDET_FRM_NUM);
	setAddress(&ScrlB[1], PATDET_LINE_NUM);
	setAddress(&ScrlB[2], GRAD_GMA_STEP);
	setAddress(&ScrlB[3], GRAD_FRM_STEP);
	setAddress(&ScrlB[4], GRAD_PIXDIFF_THR);
	setAddress(&ScrlB[5], EDG_DIFF_THR);
	setAddress(&ScrlB[6], PIX_DIFF_THR);
	setAddress(&ScrlB[7], STRENGTH_K);
	setAddress(&ScrlB[8], MIN_EDGE);
	setAddress(&ScrlB[9], MLC_THR);
	setAddress(&ScrlB[10], JND_MAX);
	setAddress(&ScrlB[11], JND_MIN);
	setAddress(&ScrlB[12], ST_MAX);
	setAddress(&ScrlB[13], ST_MIN);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&ScrlB[0], "PATDET_FRM_NUM");
	setAddressFromFile(&ScrlB[1], "PATDET_LINE_NUM");
	setAddressFromFile(&ScrlB[2], "GRAD_GMA_STEP");
	setAddressFromFile(&ScrlB[3], "GRAD_FRM_STEP");
	setAddressFromFile(&ScrlB[4], "GRAD_PIXDIFF_THR");
	setAddressFromFile(&ScrlB[5], "EDG_DIFF_THR");
	setAddressFromFile(&ScrlB[6], "PIX_DIFF_THR");
	setAddressFromFile(&ScrlB[7], "STRENGTH_K");
	setAddressFromFile(&ScrlB[8], "MIN_EDGE");
	setAddressFromFile(&ScrlB[9], "MLC_THR");
	setAddressFromFile(&ScrlB[10], "JND_MAX");
	setAddressFromFile(&ScrlB[11], "JND_MIN");
	setAddressFromFile(&ScrlB[12], "ST_MAX");
	setAddressFromFile(&ScrlB[13], "ST_MIN");
    }
    return ScrlB;
}

TLUT *CE_11307::SetJNDlut()
{
    TLUT *lut = new TLUT[1];
    if (MainForm->addr_place == 0) {
	setAddress(&lut[0], JND_LUT);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&lut[0], "JND_LUT");
    }
    return lut;
}

TLUT *CE_11307::SetSTlut()
{
    TLUT *lut = new TLUT[1];
    if (MainForm->addr_place == 0) {
	setAddress(&lut[0], ST_LUT);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&lut[0], "ST_LUT");
    }
    return lut;
}

TLUT *CE_11307::SetMAXlut()
{
    TLUT *lut = new TLUT[1];
    if (MainForm->addr_place == 0) {
	setAddress(&lut[0], MAX_LUT);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&lut[0], "MAX_LUT");
    }
    return lut;
}

TLUT *CE_11307::SetMINlut()
{
    TLUT *lut = new TLUT[1];
    if (MainForm->addr_place == 0) {
	setAddress(&lut[0], MIN_LUT);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&lut[0], "MIN_LUT");
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

TBit *HSV_11307::SetChkBx()
{
    TBit *ChkBx = new TBit[HSVChkBox_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&ChkBx[0], HUE_EN);	//
	setAddress(&ChkBx[1], HUE_DEMO);	//
	setAddress(&ChkBx[2], HUE_DEMO_LEFT);	//
	setAddress(&ChkBx[3], V_OFS_EN);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&ChkBx[0], "HUE_EN");
	setAddressFromFile(&ChkBx[1], "HUE_DEMO");
	setAddressFromFile(&ChkBx[2], "HUE_DEMO_LEFT");
	setAddressFromFile(&ChkBx[3], "V_OFS_EN");
    }
    return ChkBx;
}

TLUT *HSV_11307::SetLUT()
{
    TLUT *lut = new TLUT[1];
    if (MainForm->addr_place == 0) {
	setAddress(&lut[0], HSVlut);	//
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&lut[0], "HSVlut");
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

TBit *C3D_11307_777::SetChkBx()
{
    TBit *ChkBx = new TBit[C3DChkBox_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&ChkBx[0], C3D_777_EN);
	setAddress(&ChkBx[1], C3D_777_DEMO);
	setAddress(&ChkBx[2], C3D_777_DEMO_LEFT);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&ChkBx[0], "C3D_777_EN");
	setAddressFromFile(&ChkBx[1], "C3D_777_DEMO");
	setAddressFromFile(&ChkBx[2], "C3D_777_DEMO_LEFT");
    }
    return ChkBx;
}

TLUT *C3D_11307_777::SetLUT()
{
    TLUT *lut = new TLUT[C3DLUT_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&lut[0], C3D_777_LUTR);
	setAddress(&lut[1], C3D_777_LUTG);
	setAddress(&lut[2], C3D_777_LUTB);
	// setAddress(&lut[3],C3D_LUTW);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&lut[0], "C3D_777_LUTR");
	setAddressFromFile(&lut[1], "C3D_777_LUTG");
	setAddressFromFile(&lut[2], "C3D_777_LUTB");
	//setAddressFromFile(&lut[3],"C3D_LUTW");
    }
    return lut;
}

String C3D_11307_777::C3D_EN_Name()	// 20100608 return C3D enable register name
{
    return C3D_777_FUNC_EN_NAME;
}

////////////////////////////////////////////////////////////////////

C3D_11307_999::C3D_11307_999()
{
    C3DChkBox_Nbr = 3;
    C3DLUT_Nbr = 3;

}

TBit *C3D_11307_999::SetChkBx()
{
    TBit *ChkBx = new TBit[C3DChkBox_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&ChkBx[0], C3D_999_EN);
	setAddress(&ChkBx[1], C3D_999_DEMO);
	setAddress(&ChkBx[2], C3D_999_DEMO_LEFT);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&ChkBx[0], "C3D_999_EN");
	setAddressFromFile(&ChkBx[1], "C3D_999_DEMO");
	setAddressFromFile(&ChkBx[2], "C3D_999_DEMO_LEFT");
    }
    return ChkBx;
}

TLUT *C3D_11307_999::SetLUT()
{
    TLUT *lut = new TLUT[C3DLUT_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&lut[0], C3D_999_LUTR);
	setAddress(&lut[1], C3D_999_LUTG);
	setAddress(&lut[2], C3D_999_LUTB);
	// setAddress(&lut[3],C3D_LUTW);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&lut[0], "C3D_999_LUTR");
	setAddressFromFile(&lut[1], "C3D_999_LUTG");
	setAddressFromFile(&lut[2], "C3D_999_LUTB");
	//setAddressFromFile(&lut[3],"C3D_LUTW");
    }
    return lut;
}

String C3D_11307_999::C3D_EN_Name()	// 20100608 return C3D enable register name
{
    return C3D_999_FUNC_EN_NAME;
}

