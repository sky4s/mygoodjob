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
        DevChkBox_Nbr = 10;       //Number of CheckBox in device page
        DevCboBox_Nbr = 3;        //Number of ComboBox in device page

        IOChkBox_Nbr = 17;        //Number of CheckBox in input/output page
        IOCboBox_Nbr = 1;         //Number of ComboBox in input/output page

        DrvChkBox_Nbr = 11;       //Number of CheckBox in Driving page
        DrvCboBox_Nbr = 7;        //Number of ComboBox in Driving page
        DrvLblE2_Nbr = 4;          //Number of LabeledEdit in Driving page

        TimLblE2_Nbr = 37;        //Number of LabeledEdit2 in Timing page
        TimLblE3_Nbr = 0;
}
TBit3* TCON_12401::SetTimLblE3()
{
        TBit3* LEdt;
        return LEdt;
}

TBit* TCON_12401::SetDevChkBx()
{
        //CheckBox數量等於TCON1.cpp裡的DevChkBox_Nbr數量, 必須大於index
        TBit* ChkBox = new TBit [DevChkBox_Nbr];
        if(MainForm->addr_place == 0){
                //SetAddr(&ChkBox[0],_NULL);
                SetAddr(&ChkBox[0],DEMO_TYPE);
                SetAddr(&ChkBox[1],AGING_SRC);
                SetAddr(&ChkBox[2],GATECLK_EN);
                SetAddr(&ChkBox[3],CLKDET_EN);
                SetAddr(&ChkBox[4],ODLUT_TYPE);
                SetAddr(&ChkBox[5],Sync_EN);
                SetAddr(&ChkBox[6],VOC_SEL);
                SetAddr(&ChkBox[7],EEPROM64);
                SetAddr(&ChkBox[8],Master_SEL);
                SetAddr(&ChkBox[9],SSCG_EN);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBox[0],"DEMO_TYPE");
                GetAddr(&ChkBox[1],"AGING_SRC");
                GetAddr(&ChkBox[2],"GATECLK_EN");
                GetAddr(&ChkBox[3],"CLKDET_EN");
                GetAddr(&ChkBox[4],"ODLUT_TYPE");
                GetAddr(&ChkBox[5],"Sync_EN");
                GetAddr(&ChkBox[6],"VOC_SEL");
                GetAddr(&ChkBox[7],"EEPROM64");
                GetAddr(&ChkBox[8],"Master_SEL");
                GetAddr(&ChkBox[9],"SSCG_EN");
        }
        return ChkBox;
}

TBit* TCON_12401::SetDevCboBx()
{
        TBit* CboBox = new TBit [DevCboBox_Nbr];

        if(MainForm->addr_place == 0){
                SetAddr(&CboBox[0],MASTER_SYNC_DLY);
                SetAddr(&CboBox[1],SLAVER_SYNC_DLY);
                SetAddr(&CboBox[2],SSCG_SEL);

        }else if(MainForm->addr_place == 1){
                GetAddr(&CboBox[0],"MASTER_SYNC_DLY");
                GetAddr(&CboBox[1],"SLAVER_SYNC_DLY");
                GetAddr(&CboBox[2],"SSCG_SEL");
                GetAddr(&CboBox[3],"DEBUG_MODE");
        }
        CboBox[0].choice_nbr = 4;
        CboBox[0].choice = new String [4];
        CboBox[0].choice[0] = "0 clk";
        CboBox[0].choice[1] = "1 clk";
        CboBox[0].choice[2] = "2 clk";
        CboBox[0].choice[3] = "3 clk";

        CboBox[1].choice_nbr = 4;
        CboBox[1].choice = new String [4];
        CboBox[1].choice[0] = "0 clk";
        CboBox[1].choice[1] = "1 clk";
        CboBox[1].choice[2] = "2 clk";
        CboBox[1].choice[3] = "3 clk";

        CboBox[2].choice_nbr = 8;
        CboBox[2].choice = new String [8];
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

TBit* TCON_12401::SetIOChkBx()
{
        TBit* ChkBox = new TBit [IOChkBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ChkBox[0], IP10B);
                SetAddr(&ChkBox[1], S2D_EN);
                SetAddr(&ChkBox[2], LORD_INV);
                SetAddr(&ChkBox[3], OP6B);
                SetAddr(&ChkBox[4], OP10B);
                SetAddr(&ChkBox[5], OP6B3P);
                SetAddr(&ChkBox[6], CHPN);
                SetAddr(&ChkBox[7], CHPXB);
                SetAddr(&ChkBox[8], CHPXF);
                SetAddr(&ChkBox[9], CHML);

                SetAddr(&ChkBox[11],CHWB);
                SetAddr(&ChkBox[10],CHRB);
                SetAddr(&ChkBox[12],CHFB);
                SetAddr(&ChkBox[13],BRVS_1);
                SetAddr(&ChkBox[14],BRVS_2);
                SetAddr(&ChkBox[15],FRVS_1);
                SetAddr(&ChkBox[16],FRVS_2);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBox[0], "IP10B");
                GetAddr(&ChkBox[1], "S2D_EN");
                GetAddr(&ChkBox[2], "LORD_INV");
                GetAddr(&ChkBox[3], "OP6B");
                GetAddr(&ChkBox[4], "OP10B");
                GetAddr(&ChkBox[5], "OP6B3P");
                GetAddr(&ChkBox[6], "CHPN");
                GetAddr(&ChkBox[7], "CHPXB");
                GetAddr(&ChkBox[8], "CHPXF");
                GetAddr(&ChkBox[9], "CHML");

                GetAddr(&ChkBox[10], "CHRB");
                GetAddr(&ChkBox[11], "CHWB");
                GetAddr(&ChkBox[12], "CHFB");
                GetAddr(&ChkBox[13], "BRVS_1");
                GetAddr(&ChkBox[14], "BRVS_2");
                GetAddr(&ChkBox[15], "FRVS_1");
                GetAddr(&ChkBox[16], "FRVS_2");
        }
        return ChkBox;
}
TBit* TCON_12401::SetIOCboBx()
{
        TBit* CboBox = new TBit [IOCboBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&CboBox[0],Resolution);
        }else if(MainForm->addr_place == 1){
                GetAddr(&CboBox[0],"Resolution");
        }
        CboBox[0].choice_nbr = 16;
        CboBox[0].choice = new String [16];
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

TBit* TCON_12401::SetDrvChkBx()
{
        TBit* ChkBox = new TBit [DrvChkBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ChkBox[0], TDEF_EN);
                SetAddr(&ChkBox[1], FIX_GATE);
                SetAddr(&ChkBox[2], P2G1D_EN);
                SetAddr(&ChkBox[3], DGPS_EN);
                SetAddr(&ChkBox[4], ANTI_MYDIO_EN);
                SetAddr(&ChkBox[5], MSHD_EN);
                SetAddr(&ChkBox[6], X2D1D_EN);
                SetAddr(&ChkBox[7], PRE_CHR_EN);
                SetAddr(&ChkBox[8], ONE_Y);
                SetAddr(&ChkBox[9], PIXSFT_EN);
                SetAddr(&ChkBox[10],MODE41);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBox[0], "TDEF_EN");
                GetAddr(&ChkBox[1], "FIX_GATE");
                GetAddr(&ChkBox[2], "P2G1D_EN");
                GetAddr(&ChkBox[3], "DGPS_EN");
                GetAddr(&ChkBox[4], "ANTI_MYDIO_EN");
                GetAddr(&ChkBox[5], "MSHD_EN");
                GetAddr(&ChkBox[6], "X2D1D_EN");
                GetAddr(&ChkBox[7], "PRE_CHR_EN");
                GetAddr(&ChkBox[8], "ONE_Y");
                GetAddr(&ChkBox[9], "PIXSFT_EN");
                GetAddr(&ChkBox[10], "MODE41");
        }
        return ChkBox;
}
TBit* TCON_12401::SetDrvCboBx()
{
        TBit* CboBox = new TBit [DrvCboBox_Nbr];
        /*
        GetAddr(&Cb	oBox[0],"YDIOB_NUM");
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
        if(MainForm->addr_place == 0){
                SetAddr(&CboBox[1],BGI);
                SetAddr(&CboBox[2],TF_INV);
                SetAddr(&CboBox[3],INV_SEL);
                SetAddr(&CboBox[4],DATA_SEL);
                SetAddr(&CboBox[5],SFT_SEL);
                SetAddr(&CboBox[6],GOA_MNT_EN);
        }else if(MainForm->addr_place == 1){
                GetAddr(&CboBox[1],"BGI");
                GetAddr(&CboBox[2],"TF_INV");
                GetAddr(&CboBox[3],"INV_SEL");
                GetAddr(&CboBox[4],"DATA_SEL");
                GetAddr(&CboBox[5],"SFT_SEL");
                GetAddr(&CboBox[6],"GOA_MNT_EN");
        }

        CboBox[1].choice_nbr = 4;
        CboBox[1].choice = new String [4];
        CboBox[1].choice[0] = "The same INV_SEL";
        CboBox[1].choice[1] = "Dot Inversion";
        CboBox[1].choice[2] = "2-Line Dot Inversion";
        CboBox[1].choice[3] = "DC";

        CboBox[2].choice_nbr = 2;
        CboBox[2].choice = new String [2];
        CboBox[2].choice[0] = "1 Frame";
        CboBox[2].choice[1] = "2 Frame";

        CboBox[3].choice_nbr = 4;
        CboBox[3].choice = new String [4];
        CboBox[3].choice[0] = "Dot inversion";
        CboBox[3].choice[1] = "2-Line dot inversion";
        CboBox[3].choice[2] = "Column inversion";
        CboBox[3].choice[3] = "Special 2-Line inversion";

        CboBox[4].choice_nbr = 2;
        CboBox[4].choice = new String [2];
        CboBox[4].choice[0] = "Delay";
        CboBox[4].choice[1] = "Lead";

        CboBox[5].choice_nbr = 8;
        CboBox[5].choice = new String [8];
        CboBox[5].choice[0] = "LHLH";
        CboBox[5].choice[1] = "LLHH";
        CboBox[5].choice[2] = "LHHLL";
        CboBox[5].choice[3] = "Reserved";
        CboBox[5].choice[4] = "HLHL";
        CboBox[5].choice[5] = "HHLL";
        CboBox[5].choice[6] = "HLLHH";
        CboBox[5].choice[7] = "Reserved";

        CboBox[6].choice_nbr = 2;
        CboBox[6].choice = new String [2];
        CboBox[6].choice[0] = "NB Type";
        CboBox[6].choice[1] = "Monitor Type";
        return CboBox;
}
TBit2* TCON_12401::SetDrvLblE()
{
        TBit2* LEdt = new TBit2 [DrvLblE2_Nbr];

        if(MainForm->addr_place == 0){
                SetAddr(&LEdt[0],GAM_2G1D_RISING);
                SetAddr(&LEdt[1],GAM_2G1D_FALLING);
                SetAddr(&LEdt[2],BGI_GRAY);
                SetAddr(&LEdt[3],BGI_GRAY2);
        }else if(MainForm->addr_place == 1){
                GetAddr(&LEdt[0],"GAM_2G1D_RISING(0~2048)");
                GetAddr(&LEdt[1],"GAM_2G1D_FALLING(0~2048)");
                GetAddr(&LEdt[2],"BGI_GRAY(0~1024)");
                GetAddr(&LEdt[3],"BGI_GRAY2(0~1024)");
        }
        return LEdt;
}

//=========================================================================//

TBit2* TCON_12401::SetTimLblE2()
{
        TBit2* LEdt = new TBit2 [TimLblE2_Nbr];//37

        if(MainForm->addr_place == 0){
                SetAddr(&LEdt[0], TXSTBR_DEF);
                SetAddr(&LEdt[1], PWXSTB_DEF);
                SetAddr(&LEdt[2], TXPOL_DEF);
                SetAddr(&LEdt[3], PWXRST_DEF);
                //Normal
                SetAddr(&LEdt[4], TYDIOR_DEF);
                SetAddr(&LEdt[5], PWYDIO_DEF);
                SetAddr(&LEdt[6], TYCLKR_DEF);
                SetAddr(&LEdt[7], PWYCLK_DEF);
                //Normal 60
                SetAddr(&LEdt[8], TYOEF_DEF);
                SetAddr(&LEdt[9], PWYOE_DEF);
                SetAddr(&LEdt[10], TYV1CF_DEF);
                SetAddr(&LEdt[11], PWYV1C_DEF);

                //Fix Gate On
                SetAddr(&LEdt[12], TXSTBR_YOER_FIX_DEF);
                SetAddr(&LEdt[13], PWYOE_FIX_DEF);
                SetAddr(&LEdt[14], TYOER_YV1CDF_FIX_DEF);
                SetAddr(&LEdt[15], PWYV1C_FIX_DEF);

                //Pstate ( Frame 40)
                SetAddr(&LEdt[16], TYOEF_FR2_DEF);
                SetAddr(&LEdt[17], PWYOE_FR2_DEF);
                SetAddr(&LEdt[18], TYV1CF_FR2_DEF);
                SetAddr(&LEdt[19], PWYV1C_FR2_DEF);

                //Fix Gate On
                SetAddr(&LEdt[20], TXSTBR_YOER_FR2_FIX_DEF);
                SetAddr(&LEdt[21], PWYOE_FR2_FIX_DEF);
                SetAddr(&LEdt[22], TYOER_YV1CF_FR2_FIX_DEF);
                SetAddr(&LEdt[23], PWYV1C_FR2_FIX_DEF);

                //Pre-Cgarge
                SetAddr(&LEdt[24], TYOER_PC_DEF);
                SetAddr(&LEdt[25], PWYOE_PC_DEF);
                SetAddr(&LEdt[26], TYCLKR_PC_DEF);

                //GOA
                SetAddr(&LEdt[27], TVSTR_DEF);
                SetAddr(&LEdt[28], PWVST_DEF);
                SetAddr(&LEdt[29], TVCK_DEF);
                SetAddr(&LEdt[30], TVCSF_DEF);
                SetAddr(&LEdt[31], PWVCS_DEF);
                SetAddr(&LEdt[32], TYV1CF_GOA_DEF);
                SetAddr(&LEdt[33], PWYV1C_GOA_DEF);

                //2G1D
                SetAddr(&LEdt[34], TYDIO2R_DEF);
                SetAddr(&LEdt[35], PWYDIO2_DEF);
                SetAddr(&LEdt[36], TYCLK2R_DEF);
        }else if(MainForm->addr_place == 1){
                GetAddr(&LEdt[0], "TXSTBR_DEF");
                GetAddr(&LEdt[1], "PWXSTB_DEF");
                GetAddr(&LEdt[2], "TXPOL_DEF");
                GetAddr(&LEdt[3], "PWXRST_DEF");
                //Normal
                GetAddr(&LEdt[4], "TYDIOR_DEF");
                GetAddr(&LEdt[5], "PWYDIO_DEF");
                GetAddr(&LEdt[6], "TYCLKR_DEF");
                GetAddr(&LEdt[7], "PWYCLK_DEF");
                //Normal 60
                GetAddr(&LEdt[8], "TYOEF_DEF");
                GetAddr(&LEdt[9], "PWYOE_DEF");
                GetAddr(&LEdt[10], "TYV1CF_DEF");
                GetAddr(&LEdt[11], "PWYV1C_DEF");

                //Fix Gate On
                GetAddr(&LEdt[12], "TXSTBR_YOER_FIX_DEF");
                GetAddr(&LEdt[13], "PWYOE_FIX_DEF");
                GetAddr(&LEdt[14], "TYOER_YV1CDF_FIX_DEF");
                GetAddr(&LEdt[15], "PWYV1C_FIX_DEF");

                //Pstate ( Frame 40)
                GetAddr(&LEdt[16], "TYOEF_FR2_DEF");
                GetAddr(&LEdt[17], "PWYOE_FR2_DEF");
                GetAddr(&LEdt[18], "TYV1CF_FR2_DEF");
                GetAddr(&LEdt[19], "PWYV1C_FR2_DEF");

                //Fix Gate On
                GetAddr(&LEdt[20], "TXSTBR_YOER_FR2_FIX_DEF");
                GetAddr(&LEdt[21], "PWYOE_FR2_FIX_DEF");
                GetAddr(&LEdt[22], "TYOER_YV1CF_FR2_FIX_DEF");
                GetAddr(&LEdt[23], "PWYV1C_FR2_FIX_DEF");

                //Pre-Cgarge
                GetAddr(&LEdt[24], "TYOER_PC_DEF");
                GetAddr(&LEdt[25], "PWYOE_PC_DEF");
                GetAddr(&LEdt[26], "TYCLKR_PC_DEF");

                //GOA
                GetAddr(&LEdt[27], "TVSTR_DEF");
                GetAddr(&LEdt[28], "PWVST_DEF");
                GetAddr(&LEdt[29], "TVCK_DEF");
                GetAddr(&LEdt[30], "TVCSF_DEF");
                GetAddr(&LEdt[31], "PWVCS_DEF");
                GetAddr(&LEdt[32], "TYV1CF_GOA_DEF");
                GetAddr(&LEdt[33], "PWYV1C_GOA_DEF");

                //2G1D
                GetAddr(&LEdt[34], "TYDIO2R_DEF");
                GetAddr(&LEdt[35], "PWYDIO2_DEF");
                GetAddr(&LEdt[36], "TYCLK2R_DEF");
        }
        return LEdt;
}

TBit2* TCON_12401::SetDevLblE2()
{
        TBit2* LEdt;
        return LEdt;
}
TBit* TCON_12401::SetStaCboBx()
{
        TBit* CboBox;
        return CboBox;
}
TBit2* TCON_12401::SetStaLblE2()
{
        TBit2* LEdt;
        return LEdt;
}
