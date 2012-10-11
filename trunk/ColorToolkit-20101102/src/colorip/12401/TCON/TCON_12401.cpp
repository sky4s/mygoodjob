//---------------------------------------------------------------------------

#pragma hdrstop

#include "TCON_12401.h"
#include "auo_12401_address.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

/////////////////////////////////////////////////////////////////
//      device page -- items address                           //
/////////////////////////////////////////////////////////////////
TCON_12401::TCON_12401()
{
    DevChkBox_Nbr = 10;		//Number of CheckBox in device page
    DevCboBox_Nbr = 3;		//Number of ComboBox in device page

    IOChkBox_Nbr = 17;		//Number of CheckBox in input/output page
    IOCboBox_Nbr = 1;		//Number of ComboBox in input/output page

    DrvChkBox_Nbr = 11;		//Number of CheckBox in Driving page
    DrvCboBox_Nbr = 7;		//Number of ComboBox in Driving page
    DrvLblE2_Nbr = 4;		//Number of LabeledEdit in Driving page

    TimLblE2_Nbr = 37;		//Number of LabeledEdit2 in Timing page
    TimLblE3_Nbr = 0;
}

TBit3 *TCON_12401::SetTimLblE3()
{
    TBit3 *LEdt;
    return LEdt;
}

TBit *TCON_12401::SetDevChkBx()
{
    //CheckBox數量等於TCON1.cpp裡的DevChkBox_Nbr數量, 必須大於index
    TBit *ChkBox = new TBit[DevChkBox_Nbr];
    if (MainForm->addr_place == 0) {
	//setAddress(&ChkBox[0],_NULL);
	setAddress(&ChkBox[0], DEMO_TYPE);
	setAddress(&ChkBox[1], AGING_SRC);
	setAddress(&ChkBox[2], GATECLK_EN);
	setAddress(&ChkBox[3], CLKDET_EN);
	setAddress(&ChkBox[4], ODLUT_TYPE);
	setAddress(&ChkBox[5], Sync_EN);
	setAddress(&ChkBox[6], VOC_SEL);
	setAddress(&ChkBox[7], EEPROM64);
	setAddress(&ChkBox[8], Master_SEL);
	setAddress(&ChkBox[9], SSCG_EN);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&ChkBox[0], "DEMO_TYPE");
	setAddressFromFile(&ChkBox[1], "AGING_SRC");
	setAddressFromFile(&ChkBox[2], "GATECLK_EN");
	setAddressFromFile(&ChkBox[3], "CLKDET_EN");
	setAddressFromFile(&ChkBox[4], "ODLUT_TYPE");
	setAddressFromFile(&ChkBox[5], "Sync_EN");
	setAddressFromFile(&ChkBox[6], "VOC_SEL");
	setAddressFromFile(&ChkBox[7], "EEPROM64");
	setAddressFromFile(&ChkBox[8], "Master_SEL");
	setAddressFromFile(&ChkBox[9], "SSCG_EN");
    }
    return ChkBox;
}

TBit *TCON_12401::SetDevCboBx()
{
    TBit *CboBox = new TBit[DevCboBox_Nbr];

    if (MainForm->addr_place == 0) {
	setAddress(&CboBox[0], MASTER_SYNC_DLY);
	setAddress(&CboBox[1], SLAVER_SYNC_DLY);
	setAddress(&CboBox[2], SSCG_SEL);

    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&CboBox[0], "MASTER_SYNC_DLY");
	setAddressFromFile(&CboBox[1], "SLAVER_SYNC_DLY");
	setAddressFromFile(&CboBox[2], "SSCG_SEL");
	setAddressFromFile(&CboBox[3], "DEBUG_MODE");
    }
    CboBox[0].choice_nbr = 4;
    CboBox[0].choice = new String[4];
    CboBox[0].choice[0] = "0 clk";
    CboBox[0].choice[1] = "1 clk";
    CboBox[0].choice[2] = "2 clk";
    CboBox[0].choice[3] = "3 clk";

    CboBox[1].choice_nbr = 4;
    CboBox[1].choice = new String[4];
    CboBox[1].choice[0] = "0 clk";
    CboBox[1].choice[1] = "1 clk";
    CboBox[1].choice[2] = "2 clk";
    CboBox[1].choice[3] = "3 clk";

    CboBox[2].choice_nbr = 8;
    CboBox[2].choice = new String[8];
    CboBox[2].choice[0] = "+0.0";
    CboBox[2].choice[1] = "+0.5";
    CboBox[2].choice[2] = "+1.0";
    CboBox[2].choice[3] = "+1.5";
    CboBox[2].choice[4] = "+2.0";
    CboBox[2].choice[5] = "+2.5";
    CboBox[2].choice[6] = "+3.0";
    CboBox[2].choice[7] = "+3.5";

    return CboBox;
}

//=========================================================================//

TBit *TCON_12401::SetIOChkBx()
{
    TBit *ChkBox = new TBit[IOChkBox_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&ChkBox[0], IP10B);
	setAddress(&ChkBox[1], S2D_EN);
	setAddress(&ChkBox[2], LORD_INV);
	setAddress(&ChkBox[3], OP6B);
	setAddress(&ChkBox[4], OP10B);
	setAddress(&ChkBox[5], OP6B3P);
	setAddress(&ChkBox[6], CHPN);
	setAddress(&ChkBox[7], CHPXB);
	setAddress(&ChkBox[8], CHPXF);
	setAddress(&ChkBox[9], CHML);

	setAddress(&ChkBox[11], CHWB);
	setAddress(&ChkBox[10], CHRB);
	setAddress(&ChkBox[12], CHFB);
	setAddress(&ChkBox[13], BRVS_1);
	setAddress(&ChkBox[14], BRVS_2);
	setAddress(&ChkBox[15], FRVS_1);
	setAddress(&ChkBox[16], FRVS_2);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&ChkBox[0], "IP10B");
	setAddressFromFile(&ChkBox[1], "S2D_EN");
	setAddressFromFile(&ChkBox[2], "LORD_INV");
	setAddressFromFile(&ChkBox[3], "OP6B");
	setAddressFromFile(&ChkBox[4], "OP10B");
	setAddressFromFile(&ChkBox[5], "OP6B3P");
	setAddressFromFile(&ChkBox[6], "CHPN");
	setAddressFromFile(&ChkBox[7], "CHPXB");
	setAddressFromFile(&ChkBox[8], "CHPXF");
	setAddressFromFile(&ChkBox[9], "CHML");

	setAddressFromFile(&ChkBox[10], "CHRB");
	setAddressFromFile(&ChkBox[11], "CHWB");
	setAddressFromFile(&ChkBox[12], "CHFB");
	setAddressFromFile(&ChkBox[13], "BRVS_1");
	setAddressFromFile(&ChkBox[14], "BRVS_2");
	setAddressFromFile(&ChkBox[15], "FRVS_1");
	setAddressFromFile(&ChkBox[16], "FRVS_2");
    }
    return ChkBox;
}

TBit *TCON_12401::SetIOCboBx()
{
    TBit *CboBox = new TBit[IOCboBox_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&CboBox[0], Resolution);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&CboBox[0], "Resolution");
    }
    CboBox[0].choice_nbr = 16;
    CboBox[0].choice = new String[16];
    CboBox[0].choice[0] = "1280x1024";
    CboBox[0].choice[1] = "1366x768";
    CboBox[0].choice[2] = "1440x1050";
    CboBox[0].choice[3] = "1440x900";
    CboBox[0].choice[4] = "1600x1200";
    CboBox[0].choice[5] = "1680x1050";
    CboBox[0].choice[6] = "1920x1200";
    CboBox[0].choice[7] = "1920x1080";
    CboBox[0].choice[8] = "1920x540";
    CboBox[0].choice[9] = "960x1080";
    CboBox[0].choice[10] = "1280x800";
    CboBox[0].choice[11] = "---";
    CboBox[0].choice[12] = "---";
    CboBox[0].choice[13] = "---";
    CboBox[0].choice[14] = "---";
    CboBox[0].choice[15] = "---";

    return CboBox;
}

//========================================================================//

TBit *TCON_12401::SetDrvChkBx()
{
    TBit *ChkBox = new TBit[DrvChkBox_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&ChkBox[0], TDEF_EN);
	setAddress(&ChkBox[1], FIX_GATE);
	setAddress(&ChkBox[2], P2G1D_EN);
	setAddress(&ChkBox[3], DGPS_EN);
	setAddress(&ChkBox[4], ANTI_MYDIO_EN);
	setAddress(&ChkBox[5], MSHD_EN);
	setAddress(&ChkBox[6], X2D1D_EN);
	setAddress(&ChkBox[7], PRE_CHR_EN);
	setAddress(&ChkBox[8], ONE_Y);
	setAddress(&ChkBox[9], PIXSFT_EN);
	setAddress(&ChkBox[10], MODE41);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&ChkBox[0], "TDEF_EN");
	setAddressFromFile(&ChkBox[1], "FIX_GATE");
	setAddressFromFile(&ChkBox[2], "P2G1D_EN");
	setAddressFromFile(&ChkBox[3], "DGPS_EN");
	setAddressFromFile(&ChkBox[4], "ANTI_MYDIO_EN");
	setAddressFromFile(&ChkBox[5], "MSHD_EN");
	setAddressFromFile(&ChkBox[6], "X2D1D_EN");
	setAddressFromFile(&ChkBox[7], "PRE_CHR_EN");
	setAddressFromFile(&ChkBox[8], "ONE_Y");
	setAddressFromFile(&ChkBox[9], "PIXSFT_EN");
	setAddressFromFile(&ChkBox[10], "MODE41");
    }
    return ChkBox;
}

TBit *TCON_12401::SetDrvCboBx()
{
    TBit *CboBox = new TBit[DrvCboBox_Nbr];
    /*
       setAddressFromFile(&Cb  oBox[0],"YDIOB_NUM");
       //CboBox[0].set(22,4,3,"YDIOB_NUM");
       CboBox[0].choice_nbr = 8;
       CboBox[0].choice = new String [8];
       CboBox[0].choice[0] = "0";
       CboBox[0].choice[1] = "1";
       CboBox[0].choice[2] = "2";
       CboBox[0].choice[3] = "3";
       CboBox[0].choice[4] = "4";
       CboBox[0].choice[5] = "5";
       CboBox[0].choice[6] = "6";
       CboBox[0].choice[7] = "7";
     */
    if (MainForm->addr_place == 0) {
	setAddress(&CboBox[1], BGI);
	setAddress(&CboBox[2], TF_INV);
	setAddress(&CboBox[3], INV_SEL);
	setAddress(&CboBox[4], DATA_SEL);
	setAddress(&CboBox[5], SFT_SEL);
	setAddress(&CboBox[6], GOA_MNT_EN);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&CboBox[1], "BGI");
	setAddressFromFile(&CboBox[2], "TF_INV");
	setAddressFromFile(&CboBox[3], "INV_SEL");
	setAddressFromFile(&CboBox[4], "DATA_SEL");
	setAddressFromFile(&CboBox[5], "SFT_SEL");
	setAddressFromFile(&CboBox[6], "GOA_MNT_EN");
    }

    CboBox[1].choice_nbr = 4;
    CboBox[1].choice = new String[4];
    CboBox[1].choice[0] = "The same INV_SEL";
    CboBox[1].choice[1] = "Dot Inversion";
    CboBox[1].choice[2] = "2-Line Dot Inversion";
    CboBox[1].choice[3] = "DC";

    CboBox[2].choice_nbr = 2;
    CboBox[2].choice = new String[2];
    CboBox[2].choice[0] = "1 Frame";
    CboBox[2].choice[1] = "2 Frame";

    CboBox[3].choice_nbr = 4;
    CboBox[3].choice = new String[4];
    CboBox[3].choice[0] = "Dot inversion";
    CboBox[3].choice[1] = "2-Line dot inversion";
    CboBox[3].choice[2] = "Column inversion";
    CboBox[3].choice[3] = "Special 2-Line inversion";

    CboBox[4].choice_nbr = 2;
    CboBox[4].choice = new String[2];
    CboBox[4].choice[0] = "Delay";
    CboBox[4].choice[1] = "Lead";

    CboBox[5].choice_nbr = 8;
    CboBox[5].choice = new String[8];
    CboBox[5].choice[0] = "LHLH";
    CboBox[5].choice[1] = "LLHH";
    CboBox[5].choice[2] = "LHHLL";
    CboBox[5].choice[3] = "Reserved";
    CboBox[5].choice[4] = "HLHL";
    CboBox[5].choice[5] = "HHLL";
    CboBox[5].choice[6] = "HLLHH";
    CboBox[5].choice[7] = "Reserved";

    CboBox[6].choice_nbr = 2;
    CboBox[6].choice = new String[2];
    CboBox[6].choice[0] = "NB Type";
    CboBox[6].choice[1] = "Monitor Type";
    return CboBox;
}

TBit2 *TCON_12401::SetDrvLblE()
{
    TBit2 *LEdt = new TBit2[DrvLblE2_Nbr];

    if (MainForm->addr_place == 0) {
	setAddress(&LEdt[0], GAM_2G1D_RISING);
	setAddress(&LEdt[1], GAM_2G1D_FALLING);
	setAddress(&LEdt[2], BGI_GRAY);
	setAddress(&LEdt[3], BGI_GRAY2);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&LEdt[0], "GAM_2G1D_RISING(0~2048)");
	setAddressFromFile(&LEdt[1], "GAM_2G1D_FALLING(0~2048)");
	setAddressFromFile(&LEdt[2], "BGI_GRAY(0~1024)");
	setAddressFromFile(&LEdt[3], "BGI_GRAY2(0~1024)");
    }
    return LEdt;
}

//=========================================================================//

TBit2 *TCON_12401::SetTimLblE2()
{
    TBit2 *LEdt = new TBit2[TimLblE2_Nbr];	//37

    if (MainForm->addr_place == 0) {
	setAddress(&LEdt[0], TXSTBR_DEF);
	setAddress(&LEdt[1], PWXSTB_DEF);
	setAddress(&LEdt[2], TXPOL_DEF);
	setAddress(&LEdt[3], PWXRST_DEF);
	//Normal
	setAddress(&LEdt[4], TYDIOR_DEF);
	setAddress(&LEdt[5], PWYDIO_DEF);
	setAddress(&LEdt[6], TYCLKR_DEF);
	setAddress(&LEdt[7], PWYCLK_DEF);
	//Normal 60
	setAddress(&LEdt[8], TYOEF_DEF);
	setAddress(&LEdt[9], PWYOE_DEF);
	setAddress(&LEdt[10], TYV1CF_DEF);
	setAddress(&LEdt[11], PWYV1C_DEF);

	//Fix Gate On
	setAddress(&LEdt[12], TXSTBR_YOER_FIX_DEF);
	setAddress(&LEdt[13], PWYOE_FIX_DEF);
	setAddress(&LEdt[14], TYOER_YV1CDF_FIX_DEF);
	setAddress(&LEdt[15], PWYV1C_FIX_DEF);

	//Pstate ( Frame 40)
	setAddress(&LEdt[16], TYOEF_FR2_DEF);
	setAddress(&LEdt[17], PWYOE_FR2_DEF);
	setAddress(&LEdt[18], TYV1CF_FR2_DEF);
	setAddress(&LEdt[19], PWYV1C_FR2_DEF);

	//Fix Gate On
	setAddress(&LEdt[20], TXSTBR_YOER_FR2_FIX_DEF);
	setAddress(&LEdt[21], PWYOE_FR2_FIX_DEF);
	setAddress(&LEdt[22], TYOER_YV1CF_FR2_FIX_DEF);
	setAddress(&LEdt[23], PWYV1C_FR2_FIX_DEF);

	//Pre-Cgarge
	setAddress(&LEdt[24], TYOER_PC_DEF);
	setAddress(&LEdt[25], PWYOE_PC_DEF);
	setAddress(&LEdt[26], TYCLKR_PC_DEF);

	//GOA
	setAddress(&LEdt[27], TVSTR_DEF);
	setAddress(&LEdt[28], PWVST_DEF);
	setAddress(&LEdt[29], TVCK_DEF);
	setAddress(&LEdt[30], TVCSF_DEF);
	setAddress(&LEdt[31], PWVCS_DEF);
	setAddress(&LEdt[32], TYV1CF_GOA_DEF);
	setAddress(&LEdt[33], PWYV1C_GOA_DEF);

	//2G1D
	setAddress(&LEdt[34], TYDIO2R_DEF);
	setAddress(&LEdt[35], PWYDIO2_DEF);
	setAddress(&LEdt[36], TYCLK2R_DEF);
    } else if (MainForm->addr_place == 1) {
	setAddressFromFile(&LEdt[0], "TXSTBR_DEF");
	setAddressFromFile(&LEdt[1], "PWXSTB_DEF");
	setAddressFromFile(&LEdt[2], "TXPOL_DEF");
	setAddressFromFile(&LEdt[3], "PWXRST_DEF");
	//Normal
	setAddressFromFile(&LEdt[4], "TYDIOR_DEF");
	setAddressFromFile(&LEdt[5], "PWYDIO_DEF");
	setAddressFromFile(&LEdt[6], "TYCLKR_DEF");
	setAddressFromFile(&LEdt[7], "PWYCLK_DEF");
	//Normal 60
	setAddressFromFile(&LEdt[8], "TYOEF_DEF");
	setAddressFromFile(&LEdt[9], "PWYOE_DEF");
	setAddressFromFile(&LEdt[10], "TYV1CF_DEF");
	setAddressFromFile(&LEdt[11], "PWYV1C_DEF");

	//Fix Gate On
	setAddressFromFile(&LEdt[12], "TXSTBR_YOER_FIX_DEF");
	setAddressFromFile(&LEdt[13], "PWYOE_FIX_DEF");
	setAddressFromFile(&LEdt[14], "TYOER_YV1CDF_FIX_DEF");
	setAddressFromFile(&LEdt[15], "PWYV1C_FIX_DEF");

	//Pstate ( Frame 40)
	setAddressFromFile(&LEdt[16], "TYOEF_FR2_DEF");
	setAddressFromFile(&LEdt[17], "PWYOE_FR2_DEF");
	setAddressFromFile(&LEdt[18], "TYV1CF_FR2_DEF");
	setAddressFromFile(&LEdt[19], "PWYV1C_FR2_DEF");

	//Fix Gate On
	setAddressFromFile(&LEdt[20], "TXSTBR_YOER_FR2_FIX_DEF");
	setAddressFromFile(&LEdt[21], "PWYOE_FR2_FIX_DEF");
	setAddressFromFile(&LEdt[22], "TYOER_YV1CF_FR2_FIX_DEF");
	setAddressFromFile(&LEdt[23], "PWYV1C_FR2_FIX_DEF");

	//Pre-Cgarge
	setAddressFromFile(&LEdt[24], "TYOER_PC_DEF");
	setAddressFromFile(&LEdt[25], "PWYOE_PC_DEF");
	setAddressFromFile(&LEdt[26], "TYCLKR_PC_DEF");

	//GOA
	setAddressFromFile(&LEdt[27], "TVSTR_DEF");
	setAddressFromFile(&LEdt[28], "PWVST_DEF");
	setAddressFromFile(&LEdt[29], "TVCK_DEF");
	setAddressFromFile(&LEdt[30], "TVCSF_DEF");
	setAddressFromFile(&LEdt[31], "PWVCS_DEF");
	setAddressFromFile(&LEdt[32], "TYV1CF_GOA_DEF");
	setAddressFromFile(&LEdt[33], "PWYV1C_GOA_DEF");

	//2G1D
	setAddressFromFile(&LEdt[34], "TYDIO2R_DEF");
	setAddressFromFile(&LEdt[35], "PWYDIO2_DEF");
	setAddressFromFile(&LEdt[36], "TYCLK2R_DEF");
    }
    return LEdt;
}

TBit2 *TCON_12401::SetDevLblE2()
{
    TBit2 *LEdt;
    return LEdt;
}

TBit *TCON_12401::SetStaCboBx()
{
    TBit *CboBox;
    return CboBox;
}

TBit2 *TCON_12401::SetStaLblE2()
{
    TBit2 *LEdt;
    return LEdt;
}

