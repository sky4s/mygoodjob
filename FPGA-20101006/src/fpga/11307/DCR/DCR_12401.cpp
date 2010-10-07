//---------------------------------------------------------------------------

#include <fpga/includeall.h>
#pragma hdrstop

#include "DCR_12401.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

DCR_12401::DCR_12401(){
        DCRChkBox_Nbr = 15;
        DCRCboBox_Nbr = 9;
        DCRScrollBar_Nbr = 20;
        DCRScrollBar2_Nbr = 12;
        DCRLblE3_Nbr = 2;
        DCRLblE2_Nbr=8;

        ALSChkBox_Nbr = 3;
        ALSCboBox_Nbr = 1;
        ALSScrollBar_Nbr = 18;

        HDRCboBox_Nbr = 6;
        HDRScrollBar_Nbr = 0;
        HDRScrollBar2_Nbr = 17;
        HDRLblE2_Nbr= 5;
        DCRLUT_Nbr=3;
}

//-----------------------------DCR--------------------------
TBit* DCR_12401::SetChkBx(){
        TBit* ChkBox = new TBit [DCRChkBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ChkBox[0],BL_EN);
                SetAddr(&ChkBox[1],DYN_BL_EN);
                SetAddr(&ChkBox[2],GLT_EN);
                SetAddr(&ChkBox[6],DCR_HDR_DEMO);

                SetAddr(&ChkBox[3],DUTY_DETECT_EN);
                SetAddr(&ChkBox[4],BL_GRAD_EN);
                SetAddr(&ChkBox[5],HIST_DIFF_RATIO_EN);
                SetAddr(&ChkBox[7],PWM_COEFF_EN);
                SetAddr(&ChkBox[8],GLT_255);

                SetAddr(&ChkBox[9],SPECIAL_STR);
                SetAddr(&ChkBox[10],DCREN_DYN_BL);
                SetAddr(&ChkBox[11],DCREN_GLT);
                SetAddr(&ChkBox[12],SW_DEMO);
                SetAddr(&ChkBox[13],BSM_EN);
                SetAddr(&ChkBox[14],DUTY_SMOOTH_EN);



        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBox[0],"BL_EN");
                GetAddr(&ChkBox[1],"DYN_BL_EN");
                GetAddr(&ChkBox[2],"GLT_EN");
                GetAddr(&ChkBox[3],"GLT_DEMO");
                GetAddr(&ChkBox[4],"DUTY_DETECT_EN");
                GetAddr(&ChkBox[5],"BL_GRAD_EN");
                GetAddr(&ChkBox[6],"IMG_DIFF_EN");
                GetAddr(&ChkBox[7],"SMBUS_EN");
                GetAddr(&ChkBox[8],"PWM_COEFF_EN");
        }
        return ChkBox;
}

TBit* DCR_12401::SetCboBx(){
        TBit* CboBox = new TBit [DCRCboBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&CboBox[1],BL_POL);
                SetAddr(&CboBox[0],PWM_MODE);
                SetAddr(&CboBox[3],PWM_LINE_SYNC);
                SetAddr(&CboBox[2],PWM_FL_MODE_SEL);
                SetAddr(&CboBox[5],IDX_MOD_SEL_SET);
                SetAddr(&CboBox[4],DCR_HDR_SEL);
                SetAddr(&CboBox[6],IDX_MOD_SEL_CUS);
                SetAddr(&CboBox[7],IN_DEMO_SIDE);
                SetAddr(&CboBox[8],PWM_BYPASS_SEL);

        }else if(MainForm->addr_place == 1){
                GetAddr(&CboBox[0],"PWM_MODE");
                GetAddr(&CboBox[1],"BL_POL");
                GetAddr(&CboBox[2],"PWM_FL_MODE_SEL");
                GetAddr(&CboBox[3],"PWM_LINE_SYNC");
        }
        CboBox[0].choice_nbr = 2;
        CboBox[0].choice = new String [2];
        CboBox[0].choice[0] = "0 : Hz";
        CboBox[0].choice[1] = "1 : kHz";

        CboBox[1].choice_nbr = 2;
        CboBox[1].choice = new String [2];
        CboBox[1].choice[0] = "0 : High Duty On";
        CboBox[1].choice[1] = "1 : Low Duty On";

        CboBox[2].choice_nbr = 2;
        CboBox[2].choice = new String [2];
        CboBox[2].choice[0] = "0 : Frame PWM mode";
        CboBox[2].choice[1] = "1 : Line PWM mode";

        CboBox[3].choice_nbr = 4;
        CboBox[3].choice = new String [4];
        CboBox[3].choice[0] = "0 : DE";
        CboBox[3].choice[1] = "1 : XSTB_PE";
        CboBox[3].choice[2] = "2 : XSTB_NE";
        CboBox[3].choice[3] = "3 : XDIO";

        CboBox[4].choice_nbr = 2;
        CboBox[4].choice = new String [2];
        CboBox[4].choice[0] = "0 : DCR";
        CboBox[4].choice[1] = "1 : HDR";

        CboBox[5].choice_nbr = 2;
        CboBox[5].choice = new String [2];
        CboBox[5].choice[0] = "0 : PWM_BL_IDX[7:0] as a Ratio";
        CboBox[5].choice[1] = "1 : PWM_BL_IDX[7:0] as a Clamp";

        CboBox[6].choice_nbr = 2;
        CboBox[6].choice = new String [2];
        CboBox[6].choice[0] = "0 : INPWM_DUTY[7:0] as a Ratio";
        CboBox[6].choice[1] = "1 : INPWM_DUTY[7:0] as a Clamp";

        CboBox[7].choice_nbr = 2;
        CboBox[7].choice = new String [2];
        CboBox[7].choice[0] = "0 : left data bypass, right compensation";
        CboBox[7].choice[1] = "1 : right data bypass, left compensation";

        CboBox[8].choice_nbr = 2;
        CboBox[8].choice = new String [2];
        CboBox[8].choice[0] = "0 : Duty bypass";
        CboBox[8].choice[1] = "1 : Frequency and duty bypass";
        return CboBox;
}

//----------------------------------------------------------
TBit* DCR_12401::SetScrollBar(){
        TBit* ScrlB = new TBit [DCRScrollBar_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ScrlB[0],GLT_SHARPNESS_RATIO);
		SetAddr(&ScrlB[1],PWM_BL_IDX);
		SetAddr(&ScrlB[2],PWM_FREQ);
		SetAddr(&ScrlB[3],BL_SW_FRM);
		SetAddr(&ScrlB[4],HIGH_DUTY_THRES);
		SetAddr(&ScrlB[5],TOTAL_DUTY_THRES);
		SetAddr(&ScrlB[6],THRES_MODULATION);
		SetAddr(&ScrlB[7],LIGHT_PIXEL_NUMBER);
		SetAddr(&ScrlB[8],NIZ_FILTER_NUM);
		SetAddr(&ScrlB[9],DUTY_GRAD_STEP);
		SetAddr(&ScrlB[10],DUTY_SW_FRM);
		SetAddr(&ScrlB[11],SMOOTH_RATIO);
		SetAddr(&ScrlB[12],MATRIX_WEIGHTING_A);
		SetAddr(&ScrlB[13],MATRIX_WEIGHTING_B);
		SetAddr(&ScrlB[14],MATRIX_WEIGHTING_C);
		SetAddr(&ScrlB[15],MATRIX_WEIGHTING_D);
		SetAddr(&ScrlB[16],MATRIX_WEIGHTING_E);
		SetAddr(&ScrlB[17],MATRIX_WEIGHTING_F);
		SetAddr(&ScrlB[18],MATRIX_WEIGHTING_EDGE);
		SetAddr(&ScrlB[19],MATRIX_WEIGHTING_CORNER);

        }else if(MainForm->addr_place == 1){
                GetAddr(&ScrlB[0],"PWM_BL_IDX");
                GetAddr(&ScrlB[1],"BL_FRM_INTV");
                GetAddr(&ScrlB[2],"BL_GRAD_STEP");
                GetAddr(&ScrlB[3],"IMG_DIFF");
                GetAddr(&ScrlB[4],"PWM_FREQ");
                GetAddr(&ScrlB[5],"SMBUS_DEV_ADDR");
                GetAddr(&ScrlB[6],"SMBUS_REG_ADDR");
                GetAddr(&ScrlB[7],"MIN_IDX_CUM_RATIO");
                GetAddr(&ScrlB[8],"MAX_IDX_CUM_RATIO");
                GetAddr(&ScrlB[9],"HIGH_DUTY_THRES");
                GetAddr(&ScrlB[10],"TOTAL_DUTY_THRES");
        }

        return ScrlB;
}
//--------------------------------------------------------
TBit2* DCR_12401::SetScrollBar2(){
        TBit2* ScrlB = new TBit2 [DCRScrollBar2_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ScrlB[0],PWM_COEFF_A);
                SetAddr(&ScrlB[1],PWM_COEFF_B);
                SetAddr(&ScrlB[2],MIN_IDX_CUM_RATIO);
                SetAddr(&ScrlB[3],MAX_IDX_CUM_RATIO);
                SetAddr(&ScrlB[4],BSM_IDX);
                SetAddr(&ScrlB[5],LIGHT_THRESHOLD);
                SetAddr(&ScrlB[6],SW_DEMO_TIME);
                SetAddr(&ScrlB[7],BL_GRAD_STEP_UP);
                SetAddr(&ScrlB[8],BL_GRAD_STEP_DN);
                SetAddr(&ScrlB[9],MIN_BL_IDX);
                SetAddr(&ScrlB[10],GS_TIME);
                SetAddr(&ScrlB[11],HIST_DIFF_RATIO);


        }else if(MainForm->addr_place == 1){
                GetAddr(&ScrlB[0],"PWM_COEFF_A");
                GetAddr(&ScrlB[1],"PWM_COEFF_B");
        }
        return ScrlB;
}
//------------------------------------------------------------
TBit2* DCR_12401::SetDCRLblE2()
{
        TBit2* LEdt = new TBit2 [DCRLblE2_Nbr];//1

        if(MainForm->addr_place == 0){
                SetAddr(&LEdt[0],H_SECTION_NUM);
                SetAddr(&LEdt[1],V_SECTION_NUM);
                SetAddr(&LEdt[2],HORIZONTAL_DIVIDE_NUM);
                SetAddr(&LEdt[3],VERTICAL_DIVIDE_NUM);
                SetAddr(&LEdt[4],DE_LENGTH);
                SetAddr(&LEdt[5],LINE_NUM);
                SetAddr(&LEdt[6],H_INTP_COEFF);
                SetAddr(&LEdt[7],V_INTP_COEFF);

        }else if(MainForm->addr_place == 1){
                GetAddr(&LEdt[0], "SLOPE");
        }
        return LEdt;
}
//-----------------------------------------
TBit3* DCR_12401::SetLblE3(){
        TBit3* LblE= new TBit3 [DCRLblE3_Nbr];

        if(MainForm->addr_place == 0){
                SetAddr(&LblE[0],SLOPE);
                SetAddr(&LblE[1],GRAY_SCALE_UNIT);

        }else if(MainForm->addr_place == 1){
                //GetAddr(&LblE[0],"SLOPE");
        }
        return LblE;
}

//----------------------------DCR LUT-----------------------
TLUT* DCR_12401::SetLUT(){
        TLUT* LUT = new TLUT[DCRLUT_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&LUT[0], HM_LUT);
                SetAddr(&LUT[1], BL_LUT);
                SetAddr(&LUT[2], DIM_LUT);   

        }else if(MainForm->addr_place == 1){
                GetAddr(&LUT[0], "HM_LUT");
                GetAddr(&LUT[1], "BL_LUT");
                GetAddr(&LUT[2], "DIM_LUT");
        }

        return LUT;
}

//--------------------------ALS and SMBUS--------------------------------


TBit* DCR_12401::SetALSChkBx(){
        TBit* ChkBox = new TBit [ALSChkBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ChkBox[0],SMBUS_EN);
                SetAddr(&ChkBox[1],ALS_EN);
                SetAddr(&ChkBox[2],ALS_COM_SEL);

        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBox[0],"BL_EN");
                GetAddr(&ChkBox[1],"DYN_BL_EN");
                GetAddr(&ChkBox[2],"GLT_EN");
                GetAddr(&ChkBox[3],"GLT_DEMO");
                GetAddr(&ChkBox[4],"DUTY_DETECT_EN");
                GetAddr(&ChkBox[5],"BL_GRAD_EN");
                GetAddr(&ChkBox[6],"IMG_DIFF_EN");
                GetAddr(&ChkBox[7],"SMBUS_EN");
                GetAddr(&ChkBox[8],"PWM_COEFF_EN");
        }
        return ChkBox;
}
TBit* DCR_12401::SetALSCboBx(){
        TBit* CboBox = new TBit [ALSCboBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&CboBox[0],IN_LUX_SEL);

        }else if(MainForm->addr_place == 1){
                GetAddr(&CboBox[0],"PWM_MODE");
        }
        CboBox[0].choice_nbr = 2;
        CboBox[0].choice = new String [2];
        CboBox[0].choice[0] = "0 : normal mode";
        CboBox[0].choice[1] = "1 : test ALS by register setting";
        return CboBox;
}

TBit* DCR_12401::SetALSScrollBar(){
        TBit* ScrlB = new TBit [ALSScrollBar_Nbr];
        if(MainForm->addr_place == 0){
               	SetAddr(&ScrlB[0],SMBUS_DEV_ADDR);
                SetAddr(&ScrlB[1],SMBUS_REG_ADDR);
                SetAddr(&ScrlB[2],ALS_SEGM_COEF);
                SetAddr(&ScrlB[3],ALS_SLOPE);
                SetAddr(&ScrlB[4],ALS_SW_FRM);
                SetAddr(&ScrlB[5],ALS_SAMP_FRM);
                SetAddr(&ScrlB[6],STABLE_CNT_NUM);
                SetAddr(&ScrlB[7],DIF_THRESHOLD);
                SetAddr(&ScrlB[8],ALS_MAX_LUX);
                SetAddr(&ScrlB[9],ALS_MIN_LUX);
                SetAddr(&ScrlB[10],ALS_DEV_ADDR);
                SetAddr(&ScrlB[11],ALS_COM_ADDR);
                SetAddr(&ScrlB[12],ALS_COM_SET1);
                SetAddr(&ScrlB[13],ALS_COM_SET2);
                SetAddr(&ScrlB[14],ALS_DATA_ADDR1);
                SetAddr(&ScrlB[15],ALS_DATA_ADDR2);
                SetAddr(&ScrlB[16],BL_2_ALS_TH);
                SetAddr(&ScrlB[17],TEST_LUX);

        }else if(MainForm->addr_place == 1){
                GetAddr(&ScrlB[0],"PWM_BL_IDX");
                GetAddr(&ScrlB[1],"BL_FRM_INTV");
                GetAddr(&ScrlB[2],"BL_GRAD_STEP");
                GetAddr(&ScrlB[3],"IMG_DIFF");
                GetAddr(&ScrlB[4],"PWM_FREQ");
                GetAddr(&ScrlB[5],"SMBUS_DEV_ADDR");
                GetAddr(&ScrlB[6],"SMBUS_REG_ADDR");
                GetAddr(&ScrlB[7],"MIN_IDX_CUM_RATIO");
                GetAddr(&ScrlB[8],"MAX_IDX_CUM_RATIO");
                GetAddr(&ScrlB[9],"HIGH_DUTY_THRES");
                GetAddr(&ScrlB[10],"TOTAL_DUTY_THRES");
        }
        return ScrlB;
}

//--------------------------HDR-------------------------------
TBit* DCR_12401::SetHDRCboBx(){
        TBit* CboBox = new TBit [HDRCboBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&CboBox[0],HSC_DRIVER_MULT);
                SetAddr(&CboBox[1],HSC_DATA_ORD);
                SetAddr(&CboBox[2],HSC_DATA_ORD_CHROW);
                SetAddr(&CboBox[3],HSC_DEV_ADDR_ORD);
                SetAddr(&CboBox[4],PWM_WAVEFORM);
                SetAddr(&CboBox[5],HSC_PWM_FREQ);


        }else if(MainForm->addr_place == 1){
                GetAddr(&CboBox[0],"PWM_MODE");
                GetAddr(&CboBox[1],"BL_POL");
                GetAddr(&CboBox[2],"PWM_FL_MODE_SEL");
                GetAddr(&CboBox[3],"PWM_LINE_SYNC");
        }
        CboBox[0].choice_nbr = 4;
        CboBox[0].choice = new String [4];
        CboBox[0].choice[0] = "00 : ---";
        CboBox[0].choice[1] = "01 : ---";
        CboBox[0].choice[2] = "10 : ---";
        CboBox[0].choice[3] = "11 : ---";


        CboBox[1].choice_nbr = 2;
        CboBox[1].choice = new String [2];
        CboBox[1].choice[0] = "0 : The data order of first row is increase(+) (1~8)";
        CboBox[1].choice[1] = "1 : The data order of first row is decrease(-) (8~1)";

        CboBox[2].choice_nbr = 2;
        CboBox[2].choice = new String [2];
        CboBox[2].choice[0] = "0 : The data order of each row is the same (+, +, +, +¡K)";
        CboBox[2].choice[1] = "1 : The data order of each row is change (+, -, +, -¡K)";

        CboBox[3].choice_nbr = 2;
        CboBox[3].choice = new String [2];
        CboBox[3].choice[0] = "0 : The device address from first row is increase(+) (1,2,3...)";
        CboBox[3].choice[1] = "1 : The device address from first row is decrease(-) (N,N-1,N-2...)";

        CboBox[4].choice_nbr = 4;
        CboBox[4].choice = new String [4];
        CboBox[4].choice[0] = "0 : ---";
        CboBox[4].choice[1] = "1 : ---";
        CboBox[4].choice[2] = "2 : ---";
        CboBox[4].choice[3] = "3 : ---";

        CboBox[5].choice_nbr = 4;
        CboBox[5].choice = new String [4];
        CboBox[5].choice[0] = "0 : 1x";
        CboBox[5].choice[1] = "1 : 2x";
        CboBox[5].choice[2] = "2 : 4x";
        CboBox[5].choice[3] = "3 : 8x";

        return CboBox;
}

TBit* DCR_12401::SetHDRScrollBar(){
        TBit* ScrlB = new TBit [HDRScrollBar_Nbr];
        if(MainForm->addr_place == 0){
      /*        SetAddr(&ScrlB[0],fix_phase_shift);
                SetAddr(&ScrlB[1],scanning_offset_row_01);
                SetAddr(&ScrlB[2],scanning_offset_row_02);
                SetAddr(&ScrlB[3],scanning_offset_row_03);
                SetAddr(&ScrlB[4],scanning_offset_row_04);
                SetAddr(&ScrlB[5],scanning_offset_row_05);
                SetAddr(&ScrlB[6],scanning_offset_row_06);
                SetAddr(&ScrlB[7],scanning_offset_row_07);
                SetAddr(&ScrlB[8],scanning_offset_row_08);
                SetAddr(&ScrlB[9],scanning_offset_row_09);
                SetAddr(&ScrlB[10],scanning_offset_row_10);
                SetAddr(&ScrlB[11],scanning_offset_row_11);
                SetAddr(&ScrlB[12],scanning_offset_row_12);
                SetAddr(&ScrlB[13],scanning_offset_row_13);
                SetAddr(&ScrlB[14],scanning_offset_row_14);
                SetAddr(&ScrlB[15],scanning_offset_row_15);
                SetAddr(&ScrlB[16],scanning_offset_row_16);

        */
        }else if(MainForm->addr_place == 1){
                GetAddr(&ScrlB[0],"PWM_BL_IDX");
                GetAddr(&ScrlB[1],"BL_FRM_INTV");
                GetAddr(&ScrlB[2],"BL_GRAD_STEP");
                GetAddr(&ScrlB[3],"IMG_DIFF");
                GetAddr(&ScrlB[4],"PWM_FREQ");
                GetAddr(&ScrlB[5],"SMBUS_DEV_ADDR");
                GetAddr(&ScrlB[6],"SMBUS_REG_ADDR");
                GetAddr(&ScrlB[7],"MIN_IDX_CUM_RATIO");
                GetAddr(&ScrlB[8],"MAX_IDX_CUM_RATIO");
                GetAddr(&ScrlB[9],"HIGH_DUTY_THRES");
                GetAddr(&ScrlB[10],"TOTAL_DUTY_THRES");
        }
        return ScrlB;
}
TBit2* DCR_12401::SetHDRScrollBar2(){
        TBit2* ScrlB = new TBit2 [HDRScrollBar2_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ScrlB[0],FIX_PHASE_SHIFT);
                SetAddr(&ScrlB[1],SCANNING_OFFSET_ROW_01);
                SetAddr(&ScrlB[2],SCANNING_OFFSET_ROW_02);
                SetAddr(&ScrlB[3],SCANNING_OFFSET_ROW_03);
                SetAddr(&ScrlB[4],SCANNING_OFFSET_ROW_04);
                SetAddr(&ScrlB[5],SCANNING_OFFSET_ROW_05);
                SetAddr(&ScrlB[6],SCANNING_OFFSET_ROW_06);
                SetAddr(&ScrlB[7],SCANNING_OFFSET_ROW_07);
                SetAddr(&ScrlB[8],SCANNING_OFFSET_ROW_08);
                SetAddr(&ScrlB[9],SCANNING_OFFSET_ROW_09);
                SetAddr(&ScrlB[10],SCANNING_OFFSET_ROW_10);
                SetAddr(&ScrlB[11],SCANNING_OFFSET_ROW_11);
                SetAddr(&ScrlB[12],SCANNING_OFFSET_ROW_12);
                SetAddr(&ScrlB[13],SCANNING_OFFSET_ROW_13);
                SetAddr(&ScrlB[14],SCANNING_OFFSET_ROW_14);
                SetAddr(&ScrlB[15],SCANNING_OFFSET_ROW_15);
                SetAddr(&ScrlB[16],SCANNING_OFFSET_ROW_16);

        }else if(MainForm->addr_place == 1){
                GetAddr(&ScrlB[0],"PWM_COEFF_A");
                GetAddr(&ScrlB[1],"PWM_COEFF_B");
        }
        return ScrlB;
}

TBit2* DCR_12401::SetHDRLblE2()
{
        TBit2* LEdt = new TBit2 [HDRLblE2_Nbr];//1

        if(MainForm->addr_place == 0){
                SetAddr(&LEdt[0],HSC_ROW_DRIVER_NUM);
                SetAddr(&LEdt[1],HSC_DRIVER_CH_1);
                SetAddr(&LEdt[2],HSC_DRIVER_CH_2);
                SetAddr(&LEdt[3],HSC_DRIVER_CH_3);
                SetAddr(&LEdt[4],HSC_DRIVER_CH_4);

        }else if(MainForm->addr_place == 1){
                GetAddr(&LEdt[0], "SLOPE");
        }
        return LEdt;
}

String DCR_12401::DCR_BL_EN_Name(){ // 20100608 return BL enable register name
        return DCR_BL_EN_NAME;
}
String DCR_12401::DCR_GLT_EN_Name(){ // 20100608 return GLT enable register name
        return DCR_GLT_EN_NAME;
}
