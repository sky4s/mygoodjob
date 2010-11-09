//---------------------------------------------------------------------------
#include <fpga/includeallfpga.h>
#pragma hdrstop

#include "TCON_11307.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)

/////////////////////////////////////////////////////////////////
//      device page -- items address                           //
/////////////////////////////////////////////////////////////////
TCON_11307::TCON_11307()
{
    DevChkBox_Nbr = 12;		//Number of CheckBox in device page
    DevCboBox_Nbr = 2;		//Number of ComboBox in device page
    DevLblE2_Nbr = 8;		//Number of LabeledEdit in Driving page

    IOChkBox_Nbr = 13;		//Number of CheckBox in input/output page
    IOCboBox_Nbr = 1;		//Number of ComboBox in input/output page

    DrvChkBox_Nbr = 18;		//Number of CheckBox in Driving page
    DrvCboBox_Nbr = 9;		//Number of ComboBox in Driving page
    DrvLblE2_Nbr = 9;		//Number of LabeledEdit in Driving page
    DrvLblE3_Nbr = 1;		//Number of LabeledEdit3 in Driving page

    TimLblE2_Nbr = 152;		//Number of LabeledEdit2 in Timing page
    TimLblE3_Nbr = 0;
}

TBit *TCON_11307::SetDevChkBx()	//12
{
    //CheckBox�ƶq����TCON1.cpp�̪�DevChkBox_Nbr�ƶq, �����j��index
    TBit *ChkBox = new TBit[DevChkBox_Nbr];
    if (MainForm->addr_place == 0) {
	//setAddress(&ChkBox[0],_NULL);
	setAddress(&ChkBox[0], SSCG_EN);	//20100624
	setAddress(&ChkBox[1], GAT_CLK_EN);	//
	setAddress(&ChkBox[2], IMGEN_HUE);	//
	setAddress(&ChkBox[3], IMGEN_SP);	//
	setAddress(&ChkBox[4], IMGEN_CM);	//
	setAddress(&ChkBox[5], DCREN_DYN_BL);	//
	setAddress(&ChkBox[6], DCREN_GLT);	//
	setAddress(&ChkBox[7], IMGEN_FRC);	//
	setAddress(&ChkBox[8], IMGEN_GAM);	//
	setAddress(&ChkBox[9], CLK_NG_AUO_EN);	//                                                                     
	setAddress(&ChkBox[10], CLK_STOP_EN);	//
	setAddress(&ChkBox[11], CLK_NG_VENDOR_EN);	//

    } else if (MainForm->addr_place == 1) {
	GetAddr(&ChkBox[0], "SSCG_EN");	//20100624
	GetAddr(&ChkBox[1], "GAT_CLK_EN");	//
	GetAddr(&ChkBox[2], "IMGEN_HUE");	//
	GetAddr(&ChkBox[3], "IMGEN_SP");	//
	GetAddr(&ChkBox[4], "IMGEN_CM");	//
	GetAddr(&ChkBox[5], "DCREN_DYN_BL");	//
	GetAddr(&ChkBox[6], "DCREN_GLT");	//
	GetAddr(&ChkBox[7], "IMGEN_FRC");	//
	GetAddr(&ChkBox[8], "IMGEN_GAM");	//
	GetAddr(&ChkBox[9], "CLK_NG_AUO_EN");	//                                                                                
	GetAddr(&ChkBox[10], "CLK_STOP_EN");	//
	GetAddr(&ChkBox[11], "CLK_NG_VENDOR_EN");	//                                                

    }
    return ChkBox;
}

TBit *TCON_11307::SetDevCboBx()	//2
{
    TBit *CboBox = new TBit[DevCboBox_Nbr];

    if (MainForm->addr_place == 0) {
	setAddress(&CboBox[0], SSCG_SEL);	//20100624                
	setAddress(&CboBox[1], OTP_PTM);	//

    } else if (MainForm->addr_place == 1) {
	GetAddr(&CboBox[0], "SSCG_SEL");	//20100624               
	GetAddr(&CboBox[1], "OTP_PTM");	//
    }
    CboBox[0].choice_nbr = 4;	//20100624
    CboBox[0].choice = new String[4];
    CboBox[0].choice[0] = "1.5%";
    CboBox[0].choice[1] = "3.0%";
    CboBox[0].choice[2] = "4.5%";
    CboBox[0].choice[3] = "6.0%";

    CboBox[1].choice_nbr = 8;	//20100624
    CboBox[1].choice = new String[8];
    CboBox[1].choice[0] = "000";
    CboBox[1].choice[1] = "001";
    CboBox[1].choice[2] = "010";
    CboBox[1].choice[3] = "011";
    CboBox[1].choice[4] = "100";
    CboBox[1].choice[5] = "101";
    CboBox[1].choice[6] = "110";
    CboBox[1].choice[7] = "111";

    return CboBox;
}

TBit2 *TCON_11307::SetDevLblE2()	//8
{
    TBit2 *LEdt = new TBit2[DevLblE2_Nbr];

    if (MainForm->addr_place == 0) {
	setAddress(&LEdt[0], PROG_1);	//
	setAddress(&LEdt[1], PROG_2);	//
	setAddress(&LEdt[2], CLK_NG_AUO_TIME);	//
	setAddress(&LEdt[3], CLK_NG_AUO_DETREG);	//
	setAddress(&LEdt[4], DEBUNCE_PERIOD);	//
	setAddress(&LEdt[5], CLK_NG_HFREQ_MARGIN);	//
	setAddress(&LEdt[6], CLK_NG_LFREQ_MARGIN);	//
	setAddress(&LEdt[7], CLK_STOP_DETREG);	//      

    } else if (MainForm->addr_place == 1) {
	GetAddr(&LEdt[0], "PROG_1(0~7)");	//
	GetAddr(&LEdt[1], "PROG_1(0~7)");	//
	GetAddr(&LEdt[2], "CLK_NG_AUO_TIME(0~255)");	//
	GetAddr(&LEdt[3], "CLK_NG_AUO_DETREG(0~255)");	//
	GetAddr(&LEdt[4], "DEBUNCE_PERIOD(0~255)");	//
	GetAddr(&LEdt[5], "CLK_NG_HFREQ_MARGIN(0~255)");	//
	GetAddr(&LEdt[6], "CLK_NG_LFREQ_MARGIN(0~255)");	//
	GetAddr(&LEdt[7], "CLK_STOP_DETREG(0~63)");	// 
    }
    return LEdt;
}

//=========================================================================//

TBit *TCON_11307::SetIOChkBx()
{
    TBit *ChkBox = new TBit[IOChkBox_Nbr];	//13
    if (MainForm->addr_place == 0) {
	setAddress(&ChkBox[0], IP8B);	//20100624
	setAddress(&ChkBox[1], LORD_INV);	//  
	setAddress(&ChkBox[2], CHPN);	//
	setAddress(&ChkBox[3], CHFB);	//
	setAddress(&ChkBox[4], CHWB);	//
	setAddress(&ChkBox[5], CHRB);	//
	setAddress(&ChkBox[6], CHML);	//
	setAddress(&ChkBox[7], OP3P);	//
	setAddress(&ChkBox[8], S2D_EN);	//          
	setAddress(&ChkBox[9], OP8B);	//
	setAddress(&ChkBox[10], FRVS);	//
	setAddress(&ChkBox[11], BRVS);	//                                
	setAddress(&ChkBox[12], PPFB_4P);	//       

    } else if (MainForm->addr_place == 1) {
	GetAddr(&ChkBox[0], "IP8B");	//20100624
	GetAddr(&ChkBox[1], "LORD_INV");	//
	GetAddr(&ChkBox[2], "CHPN");	//
	GetAddr(&ChkBox[3], "CHFB");	//
	GetAddr(&ChkBox[4], "CHWB");	//
	GetAddr(&ChkBox[5], "CHRB");	//
	GetAddr(&ChkBox[6], "CHML");	//
	GetAddr(&ChkBox[7], "OP3P");	//                                                                                 
	GetAddr(&ChkBox[8], "S2D_EN");	//                
	GetAddr(&ChkBox[9], "OP8B");	//
	GetAddr(&ChkBox[10], "FRVS");	//
	GetAddr(&ChkBox[11], "BRVS");	//                                               
	GetAddr(&ChkBox[12], "PPFB_4P");	//  

    }
    return ChkBox;
}

TBit *TCON_11307::SetIOCboBx()	//1
{
    TBit *CboBox = new TBit[IOCboBox_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&CboBox[0], RES);	//20100624
    } else if (MainForm->addr_place == 1) {
	GetAddr(&CboBox[0], "RES");	//20100624
    }
    CboBox[0].choice_nbr = 16;	//20100624
    CboBox[0].choice = new String[16];
    CboBox[0].choice[0] = "640x480";
    CboBox[0].choice[1] = "800x600";
    CboBox[0].choice[2] = "1024x768";
    CboBox[0].choice[3] = "1280x800";
    CboBox[0].choice[4] = "1366x768";
    CboBox[0].choice[5] = "800x480";
    CboBox[0].choice[6] = "1024x600";
    CboBox[0].choice[7] = "1024x640";
    CboBox[0].choice[8] = "1280x768";
    CboBox[0].choice[9] = "1280x720";
    CboBox[0].choice[10] = "1024x576";
    CboBox[0].choice[11] = "---";
    CboBox[0].choice[12] = "---";
    CboBox[0].choice[13] = "---";
    CboBox[0].choice[14] = "---";
    CboBox[0].choice[15] = "---";

    return CboBox;
}

//========================================================================//

TBit *TCON_11307::SetDrvChkBx()	//18
{
    TBit *ChkBox = new TBit[DrvChkBox_Nbr];
    if (MainForm->addr_place == 0) {
	setAddress(&ChkBox[0], HSD_EN);	//
	setAddress(&ChkBox[1], FIX_GATE_ON_EN);	//                                      
	setAddress(&ChkBox[2], TDEF_EN);	//                
	setAddress(&ChkBox[3], OFF_YOE2_3);	//                
	setAddress(&ChkBox[4], PRE_GIC);	//                 
	setAddress(&ChkBox[5], SWAPM);	//              
	setAddress(&ChkBox[6], SWAPL);	// 
	setAddress(&ChkBox[7], OE_AREA_PART_EN);	//
	setAddress(&ChkBox[8], ONE_Y);	//
	setAddress(&ChkBox[9], MIRROR);	//
	setAddress(&ChkBox[10], PPML_EN);	//                
	setAddress(&ChkBox[11], POLEN_CTRL);	// 
	setAddress(&ChkBox[12], DYN_POL_EN);	//                                                          
	setAddress(&ChkBox[13], POL_THRES_DEF_EN);	//
	setAddress(&ChkBox[14], SDR_DYN_POL_EN);	//
	setAddress(&ChkBox[15], MGOA_REF_EN);	//
	setAddress(&ChkBox[16], VST_SNG);	//
	setAddress(&ChkBox[17], HSD_DUMMY_EN);	//

    } else if (MainForm->addr_place == 1) {
	GetAddr(&ChkBox[0], "HSD_EN");	//                
	GetAddr(&ChkBox[1], "FIX_GATE_ON_EN");	//
	GetAddr(&ChkBox[2], "TDEF_EN");	//
	GetAddr(&ChkBox[3], "OFF_YOE2_3");	//                
	GetAddr(&ChkBox[4], "PRE_GIC");	//                
	GetAddr(&ChkBox[5], "SWAPM");	//
	GetAddr(&ChkBox[6], "SWAPL");	//
	GetAddr(&ChkBox[7], "OE_AREA_PART_EN");	//
	GetAddr(&ChkBox[8], "ONE_Y");	//
	GetAddr(&ChkBox[9], "MIRROR");	//
	GetAddr(&ChkBox[10], "PPML_EN");	//
	GetAddr(&ChkBox[11], "POLEN_CTRL");	//                                               
	GetAddr(&ChkBox[12], "DYN_POL_EN");	//
	GetAddr(&ChkBox[13], "POL_THRES_DEF_EN");	//
	GetAddr(&ChkBox[14], "SDR_DYN_POL_EN");	//
	GetAddr(&ChkBox[15], "MGOA_REF_EN");	//
	GetAddr(&ChkBox[16], "VST_SNG");	//
	GetAddr(&ChkBox[17], "HSD_DUMMY_EN");	//
    }
    return ChkBox;
}

TBit *TCON_11307::SetDrvCboBx()	//9
{
    TBit *CboBox = new TBit[DrvCboBox_Nbr];

    if (MainForm->addr_place == 0) {
	setAddress(&CboBox[0], HSD_MODE);	//                                           
	setAddress(&CboBox[1], BGI);	//
	setAddress(&CboBox[2], TF_INV);	//
	setAddress(&CboBox[3], INV_SEL);	//
	setAddress(&CboBox[4], POL_FRAME_4N_SEL);	//     
	setAddress(&CboBox[5], MULTI_GOA_SEL);	//
	setAddress(&CboBox[6], MULTI_GOA_PRESEL);	//
	setAddress(&CboBox[7], TCON_POL_JUDGE_SEL);	//
	setAddress(&CboBox[8], VST_FALLING_EXT);	//
    } else if (MainForm->addr_place == 1) {
	GetAddr(&CboBox[0], "HSD_MODE");	//                
	GetAddr(&CboBox[1], "BGI");	//
	GetAddr(&CboBox[2], "TF_INV");	//
	GetAddr(&CboBox[3], "INV_SEL");	//  
	GetAddr(&CboBox[4], "POL_FRAME_4N_SEL");	//     
	GetAddr(&CboBox[5], "MULTI_GOA_SEL");	//
	GetAddr(&CboBox[6], "MULTI_GOA_PRESEL");	// 
	GetAddr(&CboBox[7], "TCON_POL_JUDGE_SEL");	// 
	GetAddr(&CboBox[8], "VST_FALLING_EXT");	// 
    }

    CboBox[0].choice_nbr = 7;	//20100624
    CboBox[0].choice = new String[7];
    CboBox[0].choice[0] = "TYPE1";
    CboBox[0].choice[1] = "TYPE3-1";
    CboBox[0].choice[2] = "TYPE3-2";
    CboBox[0].choice[3] = "TYPE3-3";
    CboBox[0].choice[4] = "TYPE3-4";
    CboBox[0].choice[5] = "TYPE3-5";
    CboBox[0].choice[6] = "TYPE5";

    CboBox[1].choice_nbr = 4;	//20100624
    CboBox[1].choice = new String[4];
    CboBox[1].choice[0] = "00";
    CboBox[1].choice[1] = "01";
    CboBox[1].choice[2] = "10";
    CboBox[1].choice[3] = "11";

    CboBox[2].choice_nbr = 2;	//20100624
    CboBox[2].choice = new String[2];
    CboBox[2].choice[0] = "1 Frame";
    CboBox[2].choice[1] = "2 Frame";

    CboBox[3].choice_nbr = 7;	//20100624
    CboBox[3].choice = new String[7];
    CboBox[3].choice[0] = "Dot inversion";
    CboBox[3].choice[1] = "2-Line dot inversion";
    CboBox[3].choice[2] = "Column inversion";
    CboBox[3].choice[3] = "2-Line+1 inversion";
    CboBox[3].choice[4] = "4-Line dot inversion";
    CboBox[3].choice[5] = "8-Line dot inversion";
    CboBox[3].choice[6] = "3H+1 inversion";

    CboBox[4].choice_nbr = 4;	//20100624                     
    CboBox[4].choice = new String[4];
    CboBox[4].choice[0] = "4 Frame";
    CboBox[4].choice[1] = "8 Frame";
    CboBox[4].choice[2] = "12 Frame";
    CboBox[4].choice[3] = "Reserve";

    CboBox[5].choice_nbr = 2;	//20100624
    CboBox[5].choice = new String[2];
    CboBox[5].choice[0] = "4 Phase";
    CboBox[5].choice[1] = "6 Phase";

    CboBox[6].choice_nbr = 4;	//20100624
    CboBox[6].choice = new String[4];
    CboBox[6].choice[0] = "No Precharge";
    CboBox[6].choice[1] = "Pre-charge 1 Line";
    CboBox[6].choice[2] = "Pre-charge 2 Line";
    CboBox[6].choice[3] = "Reserve";

    CboBox[7].choice_nbr = 2;	//20100624
    CboBox[7].choice = new String[2];
    CboBox[7].choice[0] = "Subpixel";
    CboBox[7].choice[1] = "Pixel";

    CboBox[8].choice_nbr = 4;	//20100625
    CboBox[8].choice = new String[4];
    CboBox[8].choice[0] = "00";
    CboBox[8].choice[1] = "01";
    CboBox[8].choice[2] = "10";
    CboBox[8].choice[3] = "11";
    return CboBox;
}

TBit2 *TCON_11307::SetDrvLblE()	//9
{
    TBit2 *LEdt = new TBit2[DrvLblE2_Nbr];

    if (MainForm->addr_place == 0) {
	setAddress(&LEdt[0], OE_AREA1);	//
	setAddress(&LEdt[1], OE_AREA2);	//
	setAddress(&LEdt[2], BGI_GRAY);	//
	setAddress(&LEdt[3], PP_PORT_NUM);	//
	setAddress(&LEdt[4], POL_LOW_THRES);	//
	setAddress(&LEdt[5], POL_HIGH_THRES);	//
	setAddress(&LEdt[6], SDR_POL_PIX_THRES);	//
	setAddress(&LEdt[7], DUMMY_CK_NUM);	//
	setAddress(&LEdt[8], HSD_DUMMY_DIV2);	//        

    } else if (MainForm->addr_place == 1) {
	GetAddr(&LEdt[0], "OE_AREA1(0~4095)");	//
	GetAddr(&LEdt[1], "OE_AREA2(0~4095)");	//
	GetAddr(&LEdt[2], "BGI_GRAY(0~255)");	//
	GetAddr(&LEdt[3], "PP_PORT_NUM(0~1023)");	//
	GetAddr(&LEdt[4], "POL_LOW_THRES(0~255)");	//
	GetAddr(&LEdt[5], "POL_HIGH_THRES(0~255)");	//
	GetAddr(&LEdt[6], "SDR_POL_PIX_THRES(0~255)");	//
	GetAddr(&LEdt[7], "DUMMY_CK_NUM(0~15)");	//
	GetAddr(&LEdt[8], "HSD_DUMMY_DIV2(0~1023)");	// 
    }
    return LEdt;
}

TBit3 *TCON_11307::SetDrvLblE3()	//1
{
    TBit3 *LEdt = new TBit3[DrvLblE3_Nbr];

    if (MainForm->addr_place == 0) {
	setAddress(&LEdt[0], SDR_POL_ACCUM_THRES);	//

    } else if (MainForm->addr_place == 1) {
	//GetAddr(&LEdt[0],"SDR_POL_ACCUM_THRES(0~8388607)"); // Not support GetAddr(TBit3)
    }
    return LEdt;
}

//=========================================================================//

TBit2 *TCON_11307::SetTimLblE2()
{
    TBit2 *LEdt = new TBit2[TimLblE2_Nbr];	//152

    if (MainForm->addr_place == 0) {
	setAddress(&LEdt[0], TXSTBR_DEF);	//6
	setAddress(&LEdt[35], TXSTBR_DEF2);	//
	setAddress(&LEdt[1], PWXSTB_DEF);	//
	setAddress(&LEdt[36], PWXSTB_DEF2);	//
	setAddress(&LEdt[2], TXPOL_DEF);	//
	setAddress(&LEdt[3], PWXRST_DEF);	//
	//Normal
	setAddress(&LEdt[4], TYDIOR_DEF);	//4
	setAddress(&LEdt[5], PWYDIO_DEF);	//
	setAddress(&LEdt[6], TYCLKR_DEF);	//
	setAddress(&LEdt[7], PWYCLK_DEF);	// 
	//Frame 60
	setAddress(&LEdt[8], TYOEF_DEF);	//8
	setAddress(&LEdt[37], TYOEF_DEF2);	//
	setAddress(&LEdt[9], PWYOE_DEF);	//
	setAddress(&LEdt[38], PWYOE_DEF2);	//
	setAddress(&LEdt[10], TYV1CF_DEF);	//
	setAddress(&LEdt[39], TYV1CF_DEF2);	//
	setAddress(&LEdt[11], PWYV1C_DEF);	//
	setAddress(&LEdt[40], PWYV1C_DEF2);	//
	//Frame 40
	setAddress(&LEdt[16], TYOEF_FR2_DEF);	//8
	setAddress(&LEdt[41], TYOEF_FR2_DEF2);	//
	setAddress(&LEdt[17], PWYOE_FR2_DEF);	// 
	setAddress(&LEdt[42], PWYOE_FR2_DEF2);	//
	setAddress(&LEdt[18], TYV1CF_FR2_DEF);	// 
	setAddress(&LEdt[43], TYV1CF_FR2_DEF2);	//
	setAddress(&LEdt[19], PWYV1C_FR2_DEF);	//
	setAddress(&LEdt[44], PWYV1C_FR2_DEF2);	//
	//Frame 60 Area2
	setAddress(&LEdt[72], TYOEF_AREA2_DEF);	//8
	setAddress(&LEdt[73], TYOEF_AREA2_DEF2);	//
	setAddress(&LEdt[74], PWYOE_AREA2_DEF);	//
	setAddress(&LEdt[75], PWYOE_AREA2_DEF2);	//
	setAddress(&LEdt[51], TYV1CF_AREA2_DEF);	//
	setAddress(&LEdt[64], TYV1CF_AREA2_DEF2);	//
	setAddress(&LEdt[65], PWYV1C_AREA2_DEF);	//  
	setAddress(&LEdt[71], PWYV1C_AREA2_DEF2);	// 
	//Frame 40 Area2
	setAddress(&LEdt[92], TYOEF_FR2_AREA2_DEF);	//8
	setAddress(&LEdt[93], TYOEF_FR2_AREA2_DEF2);	//
	setAddress(&LEdt[94], PWYOE_FR2_AREA2_DEF);	//
	setAddress(&LEdt[95], PWYOE_FR2_AREA2_DEF2);	// 
	setAddress(&LEdt[88], TYV1CF_FR2_AREA2_DEF);	//
	setAddress(&LEdt[89], TYV1CF_FR2_AREA2_DEF2);	//
	setAddress(&LEdt[90], PWYV1C_FR2_AREA2_DEF);	//  
	setAddress(&LEdt[91], PWYV1C_FR2_AREA2_DEF2);	//                                                              
	//Frame 60 Area3 
	setAddress(&LEdt[86], TYOEF_AREA3_DEF);	//
	setAddress(&LEdt[87], TYOEF_AREA3_DEF2);	//
	setAddress(&LEdt[46], PWYOE_AREA3_DEF);	//8
	setAddress(&LEdt[34], PWYOE_AREA3_DEF2);	//
	setAddress(&LEdt[76], TYV1CF_AREA3_DEF);	//
	setAddress(&LEdt[82], TYV1CF_AREA3_DEF2);	//
	setAddress(&LEdt[84], PWYV1C_AREA3_DEF);	//
	setAddress(&LEdt[85], PWYV1C_AREA3_DEF2);	//
	//Frame 40 Area3
	setAddress(&LEdt[100], TYOEF_FR2_AREA3_DEF);	//8
	setAddress(&LEdt[101], TYOEF_FR2_AREA3_DEF2);	//
	setAddress(&LEdt[102], PWYOE_FR2_AREA3_DEF);	//
	setAddress(&LEdt[103], PWYOE_FR2_AREA3_DEF2);	//
	setAddress(&LEdt[96], TYV1CF_FR2_AREA3_DEF);	//
	setAddress(&LEdt[97], TYV1CF_FR2_AREA3_DEF2);	//
	setAddress(&LEdt[98], PWYV1C_FR2_AREA3_DEF);	//
	setAddress(&LEdt[99], PWYV1C_FR2_AREA3_DEF2);	//                                                                
	//Fix Gate On 60
	setAddress(&LEdt[12], TXSTBR_YOER_FIX_DEF);	//8
	setAddress(&LEdt[151], TXSTBR_YOER_FIX_DEF2);	//
	setAddress(&LEdt[13], PWYOE_FIX_DEF);	//
	setAddress(&LEdt[122], PWYOE_FIX_DEF2);	//
	setAddress(&LEdt[14], TYOER_YV1CF_FIX_DEF);	//
	setAddress(&LEdt[123], TYOER_YV1CF_FIX_DEF2);	//
	setAddress(&LEdt[15], PWYV1C_FIX_DEF);	//
	setAddress(&LEdt[124], PWYV1C_FIX_DEF2);	//                                             
	//Fix Gate On 40
	setAddress(&LEdt[20], TXSTBR_YOER_FR2_FIX_DEF);	//8
	setAddress(&LEdt[144], TXSTBR_YOER_FR2_FIX_DEF2);	//
	setAddress(&LEdt[21], PWYOE_FR2_FIX_DEF);	//
	setAddress(&LEdt[145], PWYOE_FR2_FIX_DEF2);	//
	setAddress(&LEdt[22], TYOER_YV1CF_FR2_FIX_DEF);	//
	setAddress(&LEdt[105], TYOER_YV1CF_FR2_FIX_DEF2);	//
	setAddress(&LEdt[23], PWYV1C_FR2_FIX_DEF);	//
	setAddress(&LEdt[146], PWYV1C_FR2_FIX_DEF2);	//
	//Fix Gate On 60 Area2
	setAddress(&LEdt[115], TXSTBR_YOER_FIX_DEF_AREA2);	//
	setAddress(&LEdt[150], TXSTBR_YOER_FIX_DEF2_AREA2);	//
	setAddress(&LEdt[104], PWYOE_FIX_DEF_AREA2);	//8
	setAddress(&LEdt[125], PWYOE_FIX_DEF2_AREA2);	//
	setAddress(&LEdt[116], TYOER_YV1CF_FIX_DEF_AREA2);	//
	setAddress(&LEdt[126], TYOER_YV1CF_FIX_DEF2_AREA2);	//
	setAddress(&LEdt[117], PWYV1C_FIX_DEF_AREA2);	//
	setAddress(&LEdt[127], PWYV1C_FIX_DEF2_AREA2);	//  
	//Fix Gate On 40 Area2
	setAddress(&LEdt[136], TXSTBR_YOER_FR2_FIX_DEF_AREA2);	//8
	setAddress(&LEdt[147], TXSTBR_YOER_FR2_FIX_DEF2_AREA2);	//
	setAddress(&LEdt[137], PWYOE_FR2_FIX_DEF_AREA2);	//
	setAddress(&LEdt[148], PWYOE_FR2_FIX_DEF2_AREA2);	//
	setAddress(&LEdt[138], TYOER_YV1CF_FR2_FIX_DEF_AREA2);	//
	setAddress(&LEdt[27], TYOER_YV1CF_FR2_FIX_DEF2_AREA2);	//
	setAddress(&LEdt[139], PWYV1C_FR2_FIX_DEF_AREA2);	//
	setAddress(&LEdt[28], PWYV1C_FR2_FIX_DEF2_AREA2);	//
	//Fix Gate On 60 Area3
	setAddress(&LEdt[119], TXSTBR_YOER_FIX_DEF_AREA3);	//               
	setAddress(&LEdt[128], TXSTBR_YOER_FIX_DEF2_AREA3);	//
	setAddress(&LEdt[118], PWYOE_FIX_DEF_AREA3);	//8
	setAddress(&LEdt[129], PWYOE_FIX_DEF2_AREA3);	//
	setAddress(&LEdt[120], TYOER_YV1CF_FIX_DEF_AREA3);	//
	setAddress(&LEdt[130], TYOER_YV1CF_FIX_DEF2_AREA3);	//
	setAddress(&LEdt[121], PWYV1C_FIX_DEF_AREA3);	//
	setAddress(&LEdt[131], PWYV1C_FIX_DEF2_AREA3);	//              
	//Fix Gate On 40 Area3
	setAddress(&LEdt[140], TXSTBR_YOER_FR2_FIX_DEF_AREA3);	//8
	setAddress(&LEdt[30], TXSTBR_YOER_FR2_FIX_DEF2_AREA3);	//
	setAddress(&LEdt[141], PWYOE_FR2_FIX_DEF_AREA3);	//
	setAddress(&LEdt[32], PWYOE_FR2_FIX_DEF2_AREA3);	//
	setAddress(&LEdt[142], TYOER_YV1CF_FR2_FIX_DEF_AREA3);	//
	setAddress(&LEdt[33], TYOER_YV1CF_FR2_FIX_DEF2_AREA3);	//
	setAddress(&LEdt[143], PWYV1C_FR2_FIX_DEF_AREA3);	//
	setAddress(&LEdt[48], PWYV1C_FR2_FIX_DEF2_AREA3);	//
	//Pre-Cgarge
	setAddress(&LEdt[24], TYOEF_PRE_DEF);	//17
	setAddress(&LEdt[50], TYOEF_FR2_PRE_DEF);	//
	setAddress(&LEdt[25], PWYOE_PRE_DEF);	//
	setAddress(&LEdt[106], PWYOE_FR2_PRE_DEF);	//
	setAddress(&LEdt[26], TYCLKR_PRE_DEF);	//
	setAddress(&LEdt[60], YV1CF_PRE_DEF);	//
	setAddress(&LEdt[62], YV1CF_FR2_PRE_DEF);	//
	setAddress(&LEdt[61], PWYV1C_PRE_DEF);	//
	setAddress(&LEdt[63], PWYV1C_FR2_PRE_DEF);	//
	setAddress(&LEdt[111], TXSTBR_YOER_FIX_DEF_PRE_AREA);	//
	setAddress(&LEdt[132], TXSTBR_YOER_FR2_FIX_DEF_PRE_AREA);	//
	setAddress(&LEdt[112], PWYOE_FIX_DEF_PRE_AREA);	//
	setAddress(&LEdt[133], PWYOE_FR2_FIX_DEF_PRE_AREA);	//
	setAddress(&LEdt[113], TYOER_YV1CF_FIX_DEF_PRE_AREA);	//
	setAddress(&LEdt[134], TYOER_YV1CF_FR2_FIX_DEF_PRE_AREA);	//
	setAddress(&LEdt[114], PWYV1C_FIX_DEF_PRE_AREA);	//  
	setAddress(&LEdt[135], PWYV1C_FR2_FIX_DEF_PRE_AREA);	//                                                                
	// GOA
	setAddress(&LEdt[66], PWVDDA_DEF);	//2
	setAddress(&LEdt[108], PWLOW_REF_PRE12_DEF);	//  
	//GOA 60
	setAddress(&LEdt[77], TVCK_REF_PRE2_DEF);	//11 
	setAddress(&LEdt[52], TVCK_1ST_DEF);	//
	setAddress(&LEdt[107], TVCKR_DEF);	//                                                
	setAddress(&LEdt[29], TVCK_DEF);	//
	setAddress(&LEdt[45], TVCK_DEF2);	// Check use it?
	setAddress(&LEdt[31], PWVCS_DEF);	// 
	setAddress(&LEdt[47], PWVCS_DEF2);	//
	setAddress(&LEdt[109], PWVCS_DEF3);	//
	setAddress(&LEdt[67], PWVCK_DEF);	// 
	setAddress(&LEdt[69], PWVCK_DEF2);	// 
	setAddress(&LEdt[79], PWVCK_DEF3);	//                
	//GOA 40
	setAddress(&LEdt[78], TVCK_FR2_REF_PRE2_DEF);	//10
	setAddress(&LEdt[53], TVCK_FR2_1ST_DEF);	//
	setAddress(&LEdt[149], TVCKR_FR2_DEF);	//
	setAddress(&LEdt[81], TVCK_FR2_DEF);	//
	setAddress(&LEdt[83], PWVCS_FR2_DEF);	//
	setAddress(&LEdt[49], PWVCS_FR2_DEF2);	//
	setAddress(&LEdt[110], PWVCS_FR2_DEF3);	//
	setAddress(&LEdt[68], PWVCK_FR2_DEF);	//
	setAddress(&LEdt[70], PWVCK_FR2_DEF2);	//
	setAddress(&LEdt[80], PWVCK_FR2_DEF3);	//
	//HSD_XSTB
	setAddress(&LEdt[54], HSD_PWXSTB_VAR_CNT1);	//6
	setAddress(&LEdt[55], HSD_PWXSTB_VAR_CNT2);	//
	setAddress(&LEdt[56], HSD_PWXSTB_VAR_CNT3);	//
	setAddress(&LEdt[57], HSD_PWXSTB_VAR_CNT4);	//
	setAddress(&LEdt[58], HSD_PWXSTB_VAR_CNT5);	//
	setAddress(&LEdt[59], HSD_PWXSTB_VAR_CNT6);	//

    } else if (MainForm->addr_place == 1) {
	GetAddr(&LEdt[0], "TXSTBR_DEF");	//
	GetAddr(&LEdt[35], "TXSTBR_DEF2");	//
	GetAddr(&LEdt[1], "PWXSTB_DEF");	//
	GetAddr(&LEdt[36], "PWXSTB_DEF2");	//
	GetAddr(&LEdt[2], "TXPOL_DEF");	// 
	GetAddr(&LEdt[3], "PWXRST_DEF");	//
	//Normal                                                   
	GetAddr(&LEdt[4], "TYDIOR_DEF");	//
	GetAddr(&LEdt[5], "PWYDIO_DEF");	//
	GetAddr(&LEdt[6], "TYCLKR_DEF");	//
	GetAddr(&LEdt[7], "PWYCLK_DEF");	//
	//Frame 60                                                
	GetAddr(&LEdt[8], "TYOEF_DEF");	//
	GetAddr(&LEdt[37], "TYOEF_DEF2");	//
	GetAddr(&LEdt[9], "PWYOE_DEF");	//
	GetAddr(&LEdt[38], "PWYOE_DEF2");	//
	GetAddr(&LEdt[10], "TYV1CF_DEF");	//
	GetAddr(&LEdt[39], "TYV1CF_DEF2");	//
	GetAddr(&LEdt[11], "PWYV1C_DEF");	//
	GetAddr(&LEdt[40], "PWYV1C_DEF2");	//
	//Frame 40
	GetAddr(&LEdt[16], "TYOEF_FR2_DEF");	//
	GetAddr(&LEdt[41], "TYOEF_FR2_DEF2");	//
	GetAddr(&LEdt[17], "PWYOE_FR2_DEF");	//
	GetAddr(&LEdt[42], "PWYOE_FR2_DEF2");	//
	GetAddr(&LEdt[18], "TYV1CF_FR2_DEF");	//
	GetAddr(&LEdt[43], "TYV1CF_FR2_DEF2");	//
	GetAddr(&LEdt[19], "PWYV1C_FR2_DEF");	//  
	GetAddr(&LEdt[44], "PWYV1C_FR2_DEF2");	//                
	//Frame 60 Area2
	GetAddr(&LEdt[72], "TYOEF_AREA2_DEF");	//
	GetAddr(&LEdt[73], "TYOEF_AREA2_DEF2");	//
	GetAddr(&LEdt[74], "PWYOE_AREA2_DEF");	//
	GetAddr(&LEdt[75], "PWYOE_AREA2_DEF2");	//              
	GetAddr(&LEdt[51], "TYV1CF_AREA2_DEF");	//
	GetAddr(&LEdt[64], "TYV1CF_AREA2_DEF2");	//
	GetAddr(&LEdt[65], "PWYV1C_AREA2_DEF");	// 
	GetAddr(&LEdt[71], "PWYV1C_AREA2_DEF2");	// 
	//Frame 40 Area2
	GetAddr(&LEdt[92], "TYOEF_FR2_AREA2_DEF");	//
	GetAddr(&LEdt[93], "TYOEF_FR2_AREA2_DEF2");	//
	GetAddr(&LEdt[94], "PWYOE_FR2_AREA2_DEF");	//
	GetAddr(&LEdt[95], "PWYOE_FR2_AREA2_DEF2");	//
	GetAddr(&LEdt[88], "TYV1CF_FR2_AREA2_DEF");	//
	GetAddr(&LEdt[89], "TYV1CF_FR2_AREA2_DEF2");	//
	GetAddr(&LEdt[90], "PWYV1C_FR2_AREA2_DEF");	//  
	GetAddr(&LEdt[91], "PWYV1C_FR2_AREA2_DEF2");	//               
	//Frame 60 Area3 
	GetAddr(&LEdt[86], "TYOEF_AREA3_DEF");	//
	GetAddr(&LEdt[87], "TYOEF_AREA3_DEF2");	//
	GetAddr(&LEdt[46], "PWYOE_AREA3_DEF");	//
	GetAddr(&LEdt[34], "PWYOE_AREA3_DEF2");	//
	GetAddr(&LEdt[76], "TYV1CF_AREA3_DEF");	//
	GetAddr(&LEdt[82], "TYV1CF_AREA3_DEF2");	//
	GetAddr(&LEdt[84], "PWYV1C_AREA3_DEF");	//
	GetAddr(&LEdt[85], "PWYV1C_AREA3_DEF2");	//
	//Frame 40 Area3
	GetAddr(&LEdt[100], "TYOEF_FR2_AREA3_DEF");	//
	GetAddr(&LEdt[101], "TYOEF_FR2_AREA3_DEF2");	//
	GetAddr(&LEdt[102], "PWYOE_FR2_AREA3_DEF");	//
	GetAddr(&LEdt[103], "PWYOE_FR2_AREA3_DEF2");	//
	GetAddr(&LEdt[96], "TYV1CF_FR2_AREA3_DEF");	//
	GetAddr(&LEdt[97], "TYV1CF_FR2_AREA3_DEF2");	//
	GetAddr(&LEdt[98], "PWYV1C_FR2_AREA3_DEF");	//
	GetAddr(&LEdt[99], "PWYV1C_FR2_AREA3_DEF2");	//             
	//Fix Gate On 60                
	GetAddr(&LEdt[12], "TXSTBR_YOER_FIX_DEF");	//
	GetAddr(&LEdt[151], "TXSTBR_YOER_FIX_DEF2");	//                
	GetAddr(&LEdt[13], "PWYOE_FIX_DEF");	//
	GetAddr(&LEdt[122], "PWYOE_FIX_DEF2");	//
	GetAddr(&LEdt[14], "TYOER_YV1CF_FIX_DEF");	//              
	GetAddr(&LEdt[123], "TYOER_YV1CF_FIX_DEF2");	//                
	GetAddr(&LEdt[15], "PWYV1C_FIX_DEF");	//
	GetAddr(&LEdt[124], "PWYV1C_FIX_DEF2");	//
	//Fix Gate On 40
	GetAddr(&LEdt[20], "TXSTBR_YOER_FR2_FIX_DEF");	//
	GetAddr(&LEdt[144], "TXSTBR_YOER_FR2_FIX_DEF2");	//
	GetAddr(&LEdt[21], "PWYOE_FR2_FIX_DEF");	//
	GetAddr(&LEdt[145], "PWYOE_FR2_FIX_DEF2");	//
	GetAddr(&LEdt[22], "TYOER_YV1CF_FR2_FIX_DEF");	//
	GetAddr(&LEdt[105], "TYOER_YV1CF_FR2_FIX_DEF2");	//
	GetAddr(&LEdt[23], "PWYV1C_FR2_FIX_DEF");	//
	GetAddr(&LEdt[146], "PWYV1C_FR2_FIX_DEF2");	//
	//Fix Gate On 60 Area2
	GetAddr(&LEdt[115], "TXSTBR_YOER_FIX_DEF_AREA2");	//               
	GetAddr(&LEdt[150], "TXSTBR_YOER_FIX_DEF2_AREA2");	//                               
	GetAddr(&LEdt[104], "PWYOE_FIX_DEF_AREA2");	//
	GetAddr(&LEdt[125], "PWYOE_FIX_DEF2_AREA2");	//
	GetAddr(&LEdt[116], "TYOER_YV1CF_FIX_DEF_AREA2");	//
	GetAddr(&LEdt[126], "TYOER_YV1CF_FIX_DEF2_AREA2");	//
	GetAddr(&LEdt[117], "PWYV1C_FIX_DEF_AREA2");	//
	GetAddr(&LEdt[127], "PWYV1C_FIX_DEF2_AREA2");	//                                
	//Fix Gate On 40 Area2
	GetAddr(&LEdt[136], "TXSTBR_YOER_FR2_FIX_DEF_AREA2");	//
	GetAddr(&LEdt[147], "TXSTBR_YOER_FR2_FIX_DEF2_AREA2");	//
	GetAddr(&LEdt[137], "PWYOE_FR2_FIX_DEF_AREA2");	//
	GetAddr(&LEdt[148], "PWYOE_FR2_FIX_DEF2_AREA2");	//
	GetAddr(&LEdt[138], "TYOER_YV1CF_FR2_FIX_DEF_AREA2");	//
	GetAddr(&LEdt[27], "TYOER_YV1CF_FR2_FIX_DEF2_AREA2");	//
	GetAddr(&LEdt[139], "PWYV1C_FR2_FIX_DEF_AREA2");	//
	GetAddr(&LEdt[28], "PWYV1C_FR2_FIX_DEF2_AREA2");	//
	//Fix Gate On 60 Area3
	GetAddr(&LEdt[119], "TXSTBR_YOER_FIX_DEF_AREA3");	//               
	GetAddr(&LEdt[128], "TXSTBR_YOER_FIX_DEF2_AREA3");	//
	GetAddr(&LEdt[118], "PWYOE_FIX_DEF_AREA3");	//
	GetAddr(&LEdt[129], "PWYOE_FIX_DEF2_AREA3");	//
	GetAddr(&LEdt[120], "TYOER_YV1CF_FIX_DEF_AREA3");	//
	GetAddr(&LEdt[130], "TYOER_YV1CF_FIX_DEF2_AREA3");	//
	GetAddr(&LEdt[121], "PWYV1C_FIX_DEF_AREA3");	//
	GetAddr(&LEdt[131], "PWYV1C_FIX_DEF2_AREA3");	//
	//Fix Gate On Area3(Frame 40)
	GetAddr(&LEdt[140], "TXSTBR_YOER_FR2_FIX_DEF_AREA3");	//
	GetAddr(&LEdt[30], "TXSTBR_YOER_FR2_FIX_DEF2_AREA3");	//
	GetAddr(&LEdt[141], "PWYOE_FR2_FIX_DEF_AREA3");	//
	GetAddr(&LEdt[32], "PWYOE_FR2_FIX_DEF2_AREA3");	//
	GetAddr(&LEdt[142], "TYOER_YV1CF_FR2_FIX_DEF_AREA3");	//
	GetAddr(&LEdt[33], "TYOER_YV1CF_FR2_FIX_DEF2_AREA3");	//
	GetAddr(&LEdt[143], "PWYV1C_FR2_FIX_DEF_AREA3");	//                
	GetAddr(&LEdt[48], "PWYV1C_FR2_FIX_DEF2_AREA3");	//               
	//Pre-Charge
	GetAddr(&LEdt[24], "TYOEF_PRE_DEF");	//
	GetAddr(&LEdt[50], "TYOEF_FR2_PRE_DEF");	//                                      
	GetAddr(&LEdt[25], "PWYOE_PRE_DEF");	//  
	GetAddr(&LEdt[106], "PWYOE_FR2_PRE_DEF");	//
	GetAddr(&LEdt[26], "TYCLKR_PRE_DEF");	//
	GetAddr(&LEdt[60], "YV1CF_PRE_DEF");	//
	GetAddr(&LEdt[62], "YV1CF_FR2_PRE_DEF");	//
	GetAddr(&LEdt[61], "PWYV1C_PRE_DEF");	//
	GetAddr(&LEdt[63], "PWYV1C_FR2_PRE_DEF");	//
	GetAddr(&LEdt[111], "TXSTBR_YOER_FIX_DEF_PRE_AREA");	//
	GetAddr(&LEdt[132], "TXSTBR_YOER_FR2_FIX_DEF_PRE_AREA");	//
	GetAddr(&LEdt[112], "PWYOE_FIX_DEF_PRE_AREA");	//
	GetAddr(&LEdt[133], "PWYOE_FR2_FIX_DEF_PRE_AREA");	//
	GetAddr(&LEdt[113], "TYOER_YV1CF_FIX_DEF_PRE_AREA");	//
	GetAddr(&LEdt[134], "TYOER_YV1CF_FR2_FIX_DEF_PRE_AREA");	// 
	GetAddr(&LEdt[114], "PWYV1C_FIX_DEF_PRE_AREA");	//
	GetAddr(&LEdt[135], "PWYV1C_FR2_FIX_DEF_PRE_AREA");	//
	// GOA
	GetAddr(&LEdt[66], "PWVDDA_DEF");	//2
	setAddress(&LEdt[108], "PWLOW_REF_PRE12_DEF");	// 
	//GOA 60
	GetAddr(&LEdt[77], "TVCK_REF_PRE2_DEF");	//11
	GetAddr(&LEdt[52], "TVCK_1ST_DEF");	//
	GetAddr(&LEdt[107], "TVCKR_DEF");	//
	GetAddr(&LEdt[29], "TVCK_DEF");	//
	GetAddr(&LEdt[45], "TVCK_DEF2");	//
	GetAddr(&LEdt[31], "PWVCS_DEF");	//
	GetAddr(&LEdt[47], "PWVCS_DEF2");	// 
	GetAddr(&LEdt[109], "PWVCS_DEF3");	//
	GetAddr(&LEdt[67], "PWVCK_DEF");	//
	GetAddr(&LEdt[69], "PWVCK_DEF2");	//
	GetAddr(&LEdt[79], "PWVCK_DEF3");	//
	//GOA 40
	GetAddr(&LEdt[78], "TVCK_FR2_REF_PRE2_DEF");	//10
	GetAddr(&LEdt[53], "TVCK_FR2_1ST_DEF");	//
	GetAddr(&LEdt[149], "TVCKR_FR2_DEF");	//
	GetAddr(&LEdt[81], "TVCK_FR2_DEF");	//
	GetAddr(&LEdt[83], "PWVCS_FR2_DEF");	//
	GetAddr(&LEdt[49], "PWVCS_FR2_DEF2");	//
	GetAddr(&LEdt[110], "PWVCS_FR2_DEF3");	//
	GetAddr(&LEdt[68], "PWVCK_FR2_DEF");	//
	GetAddr(&LEdt[70], "PWVCK_FR2_DEF2");	//
	GetAddr(&LEdt[80], "PWVCK_FR2_DEF3");	//
	//HSD_XSTB
	GetAddr(&LEdt[54], "HSD_PWXSTB_VAR_CNT1");	//6
	GetAddr(&LEdt[55], "HSD_PWXSTB_VAR_CNT2");	//
	GetAddr(&LEdt[56], "HSD_PWXSTB_VAR_CNT3");	//
	GetAddr(&LEdt[57], "HSD_PWXSTB_VAR_CNT4");	//
	GetAddr(&LEdt[58], "HSD_PWXSTB_VAR_CNT5");	//
	GetAddr(&LEdt[59], "HSD_PWXSTB_VAR_CNT6");	//
    }
    return LEdt;
}

TBit3 *TCON_11307::SetTimLblE3()
{
    TBit3 *LEdt;
    return LEdt;
}

TBit *TCON_11307::SetStaCboBx()
{
    TBit *CboBox;
    return CboBox;
}

TBit2 *TCON_11307::SetStaLblE2()
{
    TBit2 *LEdt;
    return LEdt;
}

