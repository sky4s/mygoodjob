//---------------------------------------------------------------------------

#include <fpga/includeall.h>
#pragma hdrstop

#include "Vend_11307.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
Vend_11307::Vend_11307()
{
    VendChkBox_Nbr = 4;
    VendCboBox_Nbr = 7;
    VendScrollBar_Nbr = 0;
    VendScrollBar2_Nbr = 0;
    DebugChkBox_Nbr = 7;
    DebugCboBox_Nbr = 7;
    DebugLblE2_Nbr = 7;
    VStaCboBox_Nbr = 5;
    VStaLblE2_Nbr = 12;
}

TBit2 *Vend_11307::SetLblE2()
{
    TBit2 *LEdt;
    return LEdt;
}

TBit *Vend_11307::SetChkBx()
{
    TBit *ChkBox = new TBit[VendChkBox_Nbr];
    if (MainForm->addr_place == 0) {
	SetAddr(&ChkBox[0], SSC_VSYNC_EN);	//
	SetAddr(&ChkBox[1], SSC_CLK_NG_EN);	//
	SetAddr(&ChkBox[2], SSC_CLK_STOP_EN);	//
	SetAddr(&ChkBox[3], PP_CHCD);	//
    } else if (MainForm->addr_place == 1) {
	GetAddr(&ChkBox[0], "SSC_VSYNC_EN");
	GetAddr(&ChkBox[1], "SSC_CLK_NG_EN");
	GetAddr(&ChkBox[2], "SSC_CLK_STOP_EN");
	GetAddr(&ChkBox[3], "PP_CHCD");
    }
    return ChkBox;
}

//----------------------------------------------
TBit *Vend_11307::SetCboBx()
{
    TBit *CboBox = new TBit[VendCboBox_Nbr];
    if (MainForm->addr_place == 0) {
	SetAddr(&CboBox[0], VOCSEL);	//                
	SetAddr(&CboBox[1], XDRV_CTL);	//
	SetAddr(&CboBox[2], YDRV_CTL);	//
	SetAddr(&CboBox[3], ML_SKEW_1);	//
	SetAddr(&CboBox[4], ML_SKEW_2);	//
	SetAddr(&CboBox[5], ML_SKEW_3);	//
	SetAddr(&CboBox[6], ML_SKEW_4);	//
    } else if (MainForm->addr_place == 1) {
	GetAddr(&CboBox[0], "VOCSEL");
	GetAddr(&CboBox[1], "XDRV_CTL");
	GetAddr(&CboBox[2], "YDRV_CTL");
	GetAddr(&CboBox[3], "ML_SKEW_1");
	GetAddr(&CboBox[4], "ML_SKEW_2");
	GetAddr(&CboBox[5], "ML_SKEW_3");
	GetAddr(&CboBox[6], "ML_SKEW_4");
    }

    CboBox[0].choice_nbr = 2;	//
    CboBox[0].choice = new String[2];
    CboBox[0].choice[0] = " 0.8V ";
    CboBox[0].choice[1] = " 1.2V ";

    CboBox[1].choice_nbr = 4;	//
    CboBox[1].choice = new String[4];
    CboBox[1].choice[0] = "6 mA";
    CboBox[1].choice[1] = "4 mA";
    CboBox[1].choice[2] = "8 mA";
    CboBox[1].choice[3] = "Resreve";

    CboBox[2].choice_nbr = 4;	//
    CboBox[2].choice = new String[4];
    CboBox[2].choice[0] = "6 mA";
    CboBox[2].choice[1] = "4 mA";
    CboBox[2].choice[2] = "8 mA";
    CboBox[2].choice[3] = "Reserve";


    CboBox[3].choice_nbr = 16;	// 
    CboBox[3].choice = new String[16];
    CboBox[3].choice[0] = "Clock Phase Right Shift 0T/32";
    CboBox[3].choice[1] = "Clock Phase Right Shift 1T/32";
    CboBox[3].choice[2] = "Clock Phase Right Shift 2T/32";
    CboBox[3].choice[3] = "Clock Phase Right Shift 3T/32";
    CboBox[3].choice[4] = "Clock Phase Right Shift 4T/32";
    CboBox[3].choice[5] = "Clock Phase Right Shift 5T/32";
    CboBox[3].choice[6] = "Clock Phase Right Shift 6T/32";
    CboBox[3].choice[7] = "Clock Phase Right Shift 7T/32";
    CboBox[3].choice[8] = "Clock Phase Right Shift 8T/32";
    CboBox[3].choice[9] = "Clock Phase Right Shift 9T/32";
    CboBox[3].choice[10] = "Clock Phase Right Shift 10T/32";
    CboBox[3].choice[11] = "Clock Phase Right Shift 11T/32";
    CboBox[3].choice[12] = "Clock Phase Right Shift 12T/32";
    CboBox[3].choice[13] = "Clock Phase Right Shift 13T/32";
    CboBox[3].choice[14] = "Clock Phase Right Shift 14T/32";
    CboBox[3].choice[15] = "Clock Phase Right Shift 15T/32";


    CboBox[4].choice_nbr = 16;	//
    CboBox[4].choice = new String[16];
    CboBox[4].choice[0] = "Clock Phase Right Shift 0T/32";
    CboBox[4].choice[1] = "Clock Phase Right Shift 1T/32";
    CboBox[4].choice[2] = "Clock Phase Right Shift 2T/32";
    CboBox[4].choice[3] = "Clock Phase Right Shift 3T/32";
    CboBox[4].choice[4] = "Clock Phase Right Shift 4T/32";
    CboBox[4].choice[5] = "Clock Phase Right Shift 5T/32";
    CboBox[4].choice[6] = "Clock Phase Right Shift 6T/32";
    CboBox[4].choice[7] = "Clock Phase Right Shift 7T/32";
    CboBox[4].choice[8] = "Clock Phase Right Shift 8T/32";
    CboBox[4].choice[9] = "Clock Phase Right Shift 9T/32";
    CboBox[4].choice[10] = "Clock Phase Right Shift 10T/32";
    CboBox[4].choice[11] = "Clock Phase Right Shift 11T/32";
    CboBox[4].choice[12] = "Clock Phase Right Shift 12T/32";
    CboBox[4].choice[13] = "Clock Phase Right Shift 13T/32";
    CboBox[4].choice[14] = "Clock Phase Right Shift 14T/32";
    CboBox[4].choice[15] = "Clock Phase Right Shift 15T/32";

    CboBox[5].choice_nbr = 16;	//
    CboBox[5].choice = new String[16];
    CboBox[5].choice[0] = "Clock Phase Right Shift 0T/32";
    CboBox[5].choice[1] = "Clock Phase Right Shift 1T/32";
    CboBox[5].choice[2] = "Clock Phase Right Shift 2T/32";
    CboBox[5].choice[3] = "Clock Phase Right Shift 3T/32";
    CboBox[5].choice[4] = "Clock Phase Right Shift 4T/32";
    CboBox[5].choice[5] = "Clock Phase Right Shift 5T/32";
    CboBox[5].choice[6] = "Clock Phase Right Shift 6T/32";
    CboBox[5].choice[7] = "Clock Phase Right Shift 7T/32";
    CboBox[5].choice[8] = "Clock Phase Right Shift 8T/32";
    CboBox[5].choice[9] = "Clock Phase Right Shift 9T/32";
    CboBox[5].choice[10] = "Clock Phase Right Shift 10T/32";
    CboBox[5].choice[11] = "Clock Phase Right Shift 11T/32";
    CboBox[5].choice[12] = "Clock Phase Right Shift 12T/32";
    CboBox[5].choice[13] = "Clock Phase Right Shift 13T/32";
    CboBox[5].choice[14] = "Clock Phase Right Shift 14T/32";
    CboBox[5].choice[15] = "Clock Phase Right Shift 15T/32";

    CboBox[6].choice_nbr = 16;	//
    CboBox[6].choice = new String[16];
    CboBox[6].choice[0] = "Clock Phase Right Shift 0T/32";
    CboBox[6].choice[1] = "Clock Phase Right Shift 1T/32";
    CboBox[6].choice[2] = "Clock Phase Right Shift 2T/32";
    CboBox[6].choice[3] = "Clock Phase Right Shift 3T/32";
    CboBox[6].choice[4] = "Clock Phase Right Shift 4T/32";
    CboBox[6].choice[5] = "Clock Phase Right Shift 5T/32";
    CboBox[6].choice[6] = "Clock Phase Right Shift 6T/32";
    CboBox[6].choice[7] = "Clock Phase Right Shift 7T/32";
    CboBox[6].choice[8] = "Clock Phase Right Shift 8T/32";
    CboBox[6].choice[9] = "Clock Phase Right Shift 9T/32";
    CboBox[6].choice[10] = "Clock Phase Right Shift 10T/32";
    CboBox[6].choice[11] = "Clock Phase Right Shift 11T/32";
    CboBox[6].choice[12] = "Clock Phase Right Shift 12T/32";
    CboBox[6].choice[13] = "Clock Phase Right Shift 13T/32";
    CboBox[6].choice[14] = "Clock Phase Right Shift 14T/32";
    CboBox[6].choice[15] = "Clock Phase Right Shift 15T/32";

    return CboBox;
}

//----------------------------------------------
TBit *Vend_11307::SetScrollBar()
{
    TBit *ScrlB = new TBit[VendScrollBar_Nbr];
    if (MainForm->addr_place == 0) {
	//SetAddr(&ScrlB[0],_NULL);
	//SetAddr(&ScrlB[1],_NULL);
    } else if (MainForm->addr_place == 1) {
	//GetAddr(&ScrlB[0],"_NULL");
	//GetAddr(&ScrlB[1],"_NULL");
    }
    return ScrlB;
}

//----------------------------------------------
TBit2 *Vend_11307::SetScrollBar2()
{
    TBit2 *ScrlB = new TBit2[VendScrollBar2_Nbr];
    if (MainForm->addr_place == 0) {
	//SetAddr(&ScrlB[0],_NULL);
    } else if (MainForm->addr_place == 1) {
	//GetAddr(&ScrlB[0],"_NULL");
    }
    return ScrlB;
}

//---------------------------------------------------------------------------------------
TBit *Vend_11307::SetDebugChkBx()
{
    TBit *ChkBox = new TBit[DebugChkBox_Nbr];
    if (MainForm->addr_place == 0) {
	SetAddr(&ChkBox[0], LUX_SEL);	// 
	SetAddr(&ChkBox[1], DIRECT_DUTY_EN);	//
	SetAddr(&ChkBox[2], HUE_TEST);	//
	SetAddr(&ChkBox[3], GAM_TEST);	//  
	SetAddr(&ChkBox[4], MGHSD_1ST_TDEF_EN);	//
	SetAddr(&ChkBox[5], OE_AREA_CNT_MODE_EN);	//
	SetAddr(&ChkBox[6], CM_TEST);	// 

    } else if (MainForm->addr_place == 1) {
	GetAddr(&ChkBox[0], "LUX_SEL");
	GetAddr(&ChkBox[1], "DIRECT_DUTY_EN");
	GetAddr(&ChkBox[2], "HUE_TEST");
	GetAddr(&ChkBox[3], "GAM_TEST");
	GetAddr(&ChkBox[4], "MGHSD_1ST_TDEF_EN");
	GetAddr(&ChkBox[5], "OE_AREA_CNT_MODE_EN");
	GetAddr(&ChkBox[6], "CM_TEST");
    }
    return ChkBox;
}

TBit *Vend_11307::SetDebugCboBx()
{
    TBit *CboBox = new TBit[DebugCboBox_Nbr];

    if (MainForm->addr_place == 0) {
	SetAddr(&CboBox[0], DEBUG_MODE);	//
	SetAddr(&CboBox[1], ST_INI_EN);	//
	SetAddr(&CboBox[2], OE_AREA_CNT_MODE);	//
	SetAddr(&CboBox[3], SDR_POL_DE_SEL);	//
	SetAddr(&CboBox[4], SDR_POL_CASE_SEL);	//
	SetAddr(&CboBox[5], POL_VBK_TYPE);	//
	SetAddr(&CboBox[6], YV1C_AREA_CNT_MODE);	//
    } else if (MainForm->addr_place == 1) {
	GetAddr(&CboBox[0], "DEBUG_MODE");
	GetAddr(&CboBox[1], "ST_INI_EN");
	GetAddr(&CboBox[2], "OE_AREA_CNT_MODE");
	GetAddr(&CboBox[3], "SDR_POL_DE_SEL");
	GetAddr(&CboBox[4], "SDR_POL_CASE_SEL");
	GetAddr(&CboBox[5], "POL_VBK_TYPE");
	GetAddr(&CboBox[6], "YV1C_AREA_CNT_MODE");
    }

    CboBox[0].choice_nbr = 8;
    CboBox[0].choice = new String[8];
    CboBox[0].choice[0] = "Normal output";
    CboBox[0].choice[1] = "Core State Debug Mode";
    CboBox[0].choice[2] = "I2C Debug Mode";
    CboBox[0].choice[3] = "Aging and Bist Mode Debug Mode";
    CboBox[0].choice[4] = "In Process Debug Mode";
    CboBox[0].choice[5] = "Out Process Debug Mode";
    CboBox[0].choice[6] = "TCON Debug Mode";
    CboBox[0].choice[7] = "Data Flow Debug Mode";

    CboBox[1].choice_nbr = 4;
    CboBox[1].choice = new String[4];
    CboBox[1].choice[0] = "7->3 no mask, 8->3 no mask";
    CboBox[1].choice[1] = "7->3 mask, 8->3 no mask";
    CboBox[1].choice[2] = "7->3 no mask, 8->3 mask";
    CboBox[1].choice[3] = "7->3 mask, 8->3 mask";

    CboBox[2].choice_nbr = 4;
    CboBox[2].choice = new String[4];
    CboBox[2].choice[0] = "Positive Edge";
    CboBox[2].choice[1] = "Negative Edge";
    CboBox[2].choice[2] = "MiniLVDS RST Positive Edge";
    CboBox[2].choice[3] = "Reserve";

    CboBox[3].choice_nbr = 2;
    CboBox[3].choice = new String[2];
    CboBox[3].choice[0] = "rt6 output data";
    CboBox[3].choice[1] = "rt5 output data";

    CboBox[4].choice_nbr = 2;
    CboBox[4].choice = new String[2];
    CboBox[4].choice[0] = "R-R,G-G,B-B";
    CboBox[4].choice[1] = "R-G,B-R,G-B";

    CboBox[5].choice_nbr = 2;
    CboBox[5].choice = new String[2];
    CboBox[5].choice[0] = "Original Polarity";
    CboBox[5].choice[1] = "Column Polarity";

    CboBox[6].choice_nbr = 4;
    CboBox[6].choice = new String[4];
    CboBox[6].choice[0] = "Positive Edge";
    CboBox[6].choice[1] = "Negative Edge";
    CboBox[6].choice[2] = "MiniLVDS RST Positive Edge";
    CboBox[6].choice[3] = "Reserve";

    return CboBox;
}

TBit *Vend_11307::SetStaCboBx()
{
    TBit *CboBox = new TBit[VStaCboBox_Nbr];

    if (MainForm->addr_place == 0) {
	SetAddr(&CboBox[0], CLK_UNSTABLE);	//
	SetAddr(&CboBox[1], CLK_STOP);	//
	SetAddr(&CboBox[2], CLK_DET_REGION);	//
	SetAddr(&CboBox[3], END_FRAME_MODI);	//
	SetAddr(&CboBox[4], CORE_STATE);	//

    } else if (MainForm->addr_place == 1) {
	GetAddr(&CboBox[0], "CLK_UNSTABLE");
	GetAddr(&CboBox[1], "CLK_STOP");
	GetAddr(&CboBox[2], "CLK_DET_REGION");
	GetAddr(&CboBox[3], "END_FRAME_MODI");
	GetAddr(&CboBox[4], "CORE_STATE");

    }

    CboBox[0].choice_nbr = 2;
    CboBox[0].choice = new String[2];
    CboBox[0].choice[0] = "False";
    CboBox[0].choice[1] = "True";

    CboBox[1].choice_nbr = 2;
    CboBox[1].choice = new String[2];
    CboBox[1].choice[0] = "False";
    CboBox[1].choice[1] = "True";

    CboBox[2].choice_nbr = 2;
    CboBox[2].choice = new String[2];
    CboBox[2].choice[0] = "False";
    CboBox[2].choice[1] = "True";

    CboBox[3].choice_nbr = 2;
    CboBox[3].choice = new String[2];
    CboBox[3].choice[0] = "False";
    CboBox[3].choice[1] = "True";

    CboBox[4].choice_nbr = 16;
    CboBox[4].choice = new String[16];
    CboBox[4].choice[0] = "Start";
    CboBox[4].choice[1] = "AS0";
    CboBox[4].choice[2] = "AS1";
    CboBox[4].choice[3] = "AS2";
    CboBox[4].choice[4] = "AS3";
    CboBox[4].choice[5] = "BS";
    CboBox[4].choice[6] = "AG";
    CboBox[4].choice[7] = "DE_det";
    CboBox[4].choice[8] = "Normal";
    CboBox[4].choice[9] = "Pstate";
    CboBox[4].choice[10] = "---";
    CboBox[4].choice[11] = "---";
    CboBox[4].choice[12] = "---";
    CboBox[4].choice[13] = "---";
    CboBox[4].choice[14] = "---";
    CboBox[4].choice[15] = "---";


    return CboBox;
}

TBit2 *Vend_11307::SetDebugLblE2()
{
    TBit2 *LEdt = new TBit2[DebugLblE2_Nbr];

    if (MainForm->addr_place == 0) {
	SetAddr(&LEdt[0], DIRECT_DUTY);	// 
	SetAddr(&LEdt[1], TEST_LUX);	//
	SetAddr(&LEdt[2], GAM_DIRECT_R);	//
	SetAddr(&LEdt[3], GAM_DIRECT_G);	//  
	SetAddr(&LEdt[4], GAM_DIRECT_B);	//
	SetAddr(&LEdt[5], ST_FRAME_NUM);	//
	SetAddr(&LEdt[6], IN_DEB_HDR_BL_SECTION);	//
    } else if (MainForm->addr_place == 1) {
	GetAddr(&LEdt[0], "DIRECT_DUTY");
	GetAddr(&LEdt[1], "TEST_LUX");
	GetAddr(&LEdt[2], "GAM_DIRECT_R");
	GetAddr(&LEdt[3], "GAM_DIRECT_G");
	GetAddr(&LEdt[4], "GAM_DIRECT_B");
	GetAddr(&LEdt[5], "ST_FRAME_NUM");
	GetAddr(&LEdt[6], "IN_DEB_HDR_BL_SECTION");
    }
    return LEdt;
}

//=========================================================================

TBit2 *Vend_11307::SetStaLblE2()
{
    TBit2 *LEdt = new TBit2[VStaLblE2_Nbr];
    if (MainForm->addr_place == 0) {
	SetAddr(&LEdt[0], OUT_BL_IDX);	//
	SetAddr(&LEdt[1], OUT_DUTY_DETECT_VALUE);	// 
	SetAddr(&LEdt[2], OUT_BL_LUT_RD_DATA);	//
	SetAddr(&LEdt[3], OUT_DR_LUT_RD_DATA);	//
	SetAddr(&LEdt[4], OTP_IDX);	//
	SetAddr(&LEdt[5], OUT_GLT_EN_STATUS);	//
	SetAddr(&LEdt[6], OUT_DCR_EN_STATUS);	// 
	SetAddr(&LEdt[7], OUT_PWM_DUTY);	//
	SetAddr(&LEdt[8], FRAME_CUM_RATIO);	//
	//SetAddr(&LEdt[9],OUT_DCR_EN_STATUS);           //
	//SetAddr(&LEdt[10],OUT_DCR_EN_STATUS);          //    
	SetAddr(&LEdt[9], OUT_DEB_HDR_BL_DATA);	//
	SetAddr(&LEdt[10], SLAVE_FSM);	//
	SetAddr(&LEdt[11], CHKSUM_FSM);	//
    } else if (MainForm->addr_place == 1) {
	GetAddr(&LEdt[0], "OUT_BL_IDX");
	GetAddr(&LEdt[1], "OUT_DUTY_DETECT_VALUE");
	GetAddr(&LEdt[2], "OUT_BL_LUT_RD_DATA");
	GetAddr(&LEdt[3], "OUT_DR_LUT_RD_DATA");
	GetAddr(&LEdt[4], "OTP_IDX");
	GetAddr(&LEdt[5], "OUT_GLT_EN_STATUS");
	GetAddr(&LEdt[6], "OUT_DCR_EN_STATUS");
	GetAddr(&LEdt[7], "OUT_PWM_DUTY");
	GetAddr(&LEdt[8], "FRAME_CUM_RATIO");
	//GetAddr(&LEdt[9],"OUT_DCR_EN_STATUS"); 
	//GetAddr(&LEdt[10],"OUT_DCR_EN_STATUS"); 
	GetAddr(&LEdt[9], "OUT_DEB_HDR_BL_DATA");
	GetAddr(&LEdt[10], "SLAVE_FSM");
	GetAddr(&LEdt[11], "CHKSUM_FSM");
    }
    return LEdt;
}

