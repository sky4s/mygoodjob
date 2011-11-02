//---------------------------------------------------------------------------


#pragma hdrstop

#include "Vend_12401.h"
#include "TCON_12401.h"
#include "auo_12401_address.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
Vend_12401::Vend_12401()
{
    VendChkBox_Nbr = 4;
    VendCboBox_Nbr = 7;
    VendScrollBar_Nbr = 3;
    VendScrollBar2_Nbr = 1;
    DebugChkBox_Nbr = 4;
    DebugCboBox_Nbr = 1;
    DebugLblE2_Nbr = 5;
    VStaCboBox_Nbr = 5;
    VStaLblE2_Nbr = 4;
}

TBit2 *Vend_12401::SetLblE2()
{
    TBit2 *LEdt;
    return LEdt;
}

TBit *Vend_12401::SetChkBx()
{
    TBit *ChkBox = new TBit[VendChkBox_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&ChkBox[0], FIFO_SYNC_RST_EN);
	setAddress(&ChkBox[1], SDRAM_INITIAL_EN);
	setAddress(&ChkBox[2], SSCG_FIFO_RST_EN);
	setAddress(&ChkBox[3], CLKUS_EN);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&ChkBox[0], "FIFO_SYNC_RST_EN");
	setAddressFromFile(&ChkBox[1], "SDRAM_INITIAL_EN");
	setAddressFromFile(&ChkBox[2], "SSCG_FIFO_RST_EN");
	setAddressFromFile(&ChkBox[3], "CLKUS_EN");
    }
    return ChkBox;
}

//----------------------------------------------
TBit *Vend_12401::SetCboBx()
{
    TBit *CboBox = new TBit[VendCboBox_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&CboBox[0], FIFO_EN);
	setAddress(&CboBox[1], DIGITAL_FILTER_EN);
	setAddress(&CboBox[2], XDRV_CTL);
	setAddress(&CboBox[3], YDRV_CTL);
	setAddress(&CboBox[4], MINILVDS_SKEW);
	setAddress(&CboBox[5], CLKUS_WINDOW);
	setAddress(&CboBox[6], CLKUS_THR);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&CboBox[0], "FIFO_EN");
	setAddressFromFile(&CboBox[1], "DIGITAL_FILTER_EN");
	setAddressFromFile(&CboBox[2], "XDRV_CTL");
	setAddressFromFile(&CboBox[3], "YDRV_CTL");
	setAddressFromFile(&CboBox[4], "MINILVDS_SKEW");
	setAddressFromFile(&CboBox[5], "CLKUS_WINDOW");
	setAddressFromFile(&CboBox[6], "CLKUS_THR");
    }

    CboBox[0].choice_nbr = 2;
    CboBox[0].choice = new String[2];
    CboBox[0].choice[0] = "FIFO Enable base on SSCG_EN";
    CboBox[0].choice[1] = "FIFO Always Enable";

    CboBox[1].choice_nbr = 2;
    CboBox[1].choice = new String[2];
    CboBox[1].choice[0] = "ON";
    CboBox[1].choice[1] = "OFF";

    CboBox[2].choice_nbr = 4;
    CboBox[2].choice = new String[4];
    CboBox[2].choice[0] = "2 mA";
    CboBox[2].choice[1] = "4 mA";
    CboBox[2].choice[2] = "6 mA";
    CboBox[2].choice[3] = "8 mA";

    CboBox[3].choice_nbr = 4;
    CboBox[3].choice = new String[4];
    CboBox[3].choice[0] = "2 mA";
    CboBox[3].choice[1] = "4 mA";
    CboBox[3].choice[2] = "6 mA";
    CboBox[3].choice[3] = "8 mA";

    CboBox[4].choice_nbr = 16;
    CboBox[4].choice = new String[16];
    CboBox[4].choice[0] = "Clock Phase No Change";
    CboBox[4].choice[1] = "Clock Phase Right Shift T/64";
    CboBox[4].choice[2] = "Clock Phase Right Shift 2T/64";
    CboBox[4].choice[3] = "Clock Phase Right Shift 3T/64";
    CboBox[4].choice[4] = "Clock Phase Right Shift 4T/64";
    CboBox[4].choice[5] = "Clock Phase Right Shift 5T/64";
    CboBox[4].choice[6] = "Clock Phase Right Shift 6T/64";
    CboBox[4].choice[7] = "Clock Phase Right Shift 7T/64";
    CboBox[4].choice[8] = "Clock Phase No Change";
    CboBox[4].choice[9] = "Clock Phase Left Shift T/64";
    CboBox[4].choice[10] = "Clock Phase Left Shift 2T/64";
    CboBox[4].choice[11] = "Clock Phase Left Shift 3T/64";
    CboBox[4].choice[12] = "Clock Phase Left Shift 4T/64";
    CboBox[4].choice[13] = "Clock Phase Left Shift 5T/64";
    CboBox[4].choice[14] = "Clock Phase Left Shift 6T/64";
    CboBox[4].choice[15] = "Clock Phase Left Shift 7T/64";

    CboBox[5].choice_nbr = 2;
    CboBox[5].choice = new String[2];
    CboBox[5].choice[0] = "1024 x OSCCLK";
    CboBox[5].choice[1] = "2048 x OSCCLK";

    CboBox[6].choice_nbr = 4;
    CboBox[6].choice = new String[4];
    CboBox[6].choice[0] = "0";
    CboBox[6].choice[1] = "1";
    CboBox[6].choice[2] = "2";
    CboBox[6].choice[3] = "3";

    return CboBox;
}

//----------------------------------------------
TBit *Vend_12401::SetScrollBar()
{
    TBit *ScrlB = new TBit[VendScrollBar_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&ScrlB[0], KME_SDRAM_REG);
	setAddress(&ScrlB[1], KME_REG);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&ScrlB[0], "KME_SDRAM_REG");
	setAddressFromFile(&ScrlB[1], "KME_REG");
    }
    return ScrlB;
}

//----------------------------------------------
TBit2 *Vend_12401::SetScrollBar2()
{
    TBit2 *ScrlB = new TBit2[VendScrollBar2_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&ScrlB[0], HFRQ_VAL);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&ScrlB[0], "HFRQ_VAL");
    }
    return ScrlB;
}

TBit *Vend_12401::SetDebugChkBx()
{
    TBit *ChkBox = new TBit[DebugChkBox_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&ChkBox[0], MEM_TEST);
	setAddress(&ChkBox[1], DIRECT_DUTY_EN);
	setAddress(&ChkBox[2], DUTY_DETECT_TEST_EN);
	setAddress(&ChkBox[3], GAM_TEST);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&ChkBox[0], "MEM_TEST");
	setAddressFromFile(&ChkBox[1], "DIRECT_DUTY_EN");
	setAddressFromFile(&ChkBox[2], "DUTY_DETECT_TEST_EN");
	setAddressFromFile(&ChkBox[3], "GAM_TEST");
    }
    return ChkBox;
}

TBit *Vend_12401::SetDebugCboBx()
{
    TBit *CboBox = new TBit[DebugCboBox_Nbr];

    if (MainForm->addr_place == 0) {
	setAddress(&CboBox[0], DEBUG_MODE);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&CboBox[0], "DEBUG_MODE");
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

    return CboBox;
}

TBit *Vend_12401::SetStaCboBx()
{
    TBit *CboBox = new TBit[VStaCboBox_Nbr];

    if (MainForm->addr_place == 0) {
	setAddress(&CboBox[0], CLK_UNSTABLE);
	setAddress(&CboBox[1], CLK_STOP);
	setAddress(&CboBox[2], CLK_DET_REGION);
	setAddress(&CboBox[3], END_FRAME_MODI);
	setAddress(&CboBox[4], CORE_STATE);

    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&CboBox[0], "CLK_UNSTABLE");
	setAddressFromFile(&CboBox[1], "CLK_STOP");
	setAddressFromFile(&CboBox[2], "CLK_DET_REGION");
	setAddressFromFile(&CboBox[3], "END_FRAME_MODI");
	setAddressFromFile(&CboBox[4], "CORE_STATE");
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

TBit2 *Vend_12401::SetDebugLblE2()
{
    TBit2 *LEdt = new TBit2[DebugLblE2_Nbr];

    if (MainForm->addr_place == 0) {
	setAddress(&LEdt[0], DIRECT_DUTY);
	setAddress(&LEdt[1], FRAME_CUM_RATIO);
	setAddress(&LEdt[2], GAM_DIRECT_R);
	setAddress(&LEdt[3], GAM_DIRECT_G);
	setAddress(&LEdt[4], GAM_DIRECT_B);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&LEdt[0], "DIRECT_DUTY");
	setAddressFromFile(&LEdt[1], "FRAME_CUM_RATIO");
	setAddressFromFile(&LEdt[2], "GAM_DIRECT_R");
	setAddressFromFile(&LEdt[3], "GAM_DIRECT_G");
	setAddressFromFile(&LEdt[4], "GAM_DIRECT_B");
    }
    return LEdt;
}

//=========================================================================

TBit2 *Vend_12401::SetStaLblE2()
{
    TBit2 *LEdt = new TBit2[VStaLblE2_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&LEdt[0], BL_IDX);
	setAddress(&LEdt[1], OUT_DUTY_DETECT_VALUE);
	setAddress(&LEdt[2], BL_LUT_RD_DATA);
	setAddress(&LEdt[3], DR_LUT_RD_DATA);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&LEdt[0], "BL_IDX");
	setAddressFromFile(&LEdt[1], "OUT_DUTY_DETECT_VALUE");
	setAddressFromFile(&LEdt[2], "BL_LUT_RD_DATA");
	setAddressFromFile(&LEdt[3], "DR_LUT_RD_DATA");
    }
    return LEdt;
}

