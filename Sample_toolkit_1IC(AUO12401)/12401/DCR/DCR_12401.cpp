//---------------------------------------------------------------------------


#pragma hdrstop

#include "DCR_12401.h"
#include "Engineering.h"
#include "TCON_12401.h"
#include "auo_12401_address.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

DCR_12401::DCR_12401(){
        DCRScrollBar_Nbr = 11;
        DCRScrollBar2_Nbr = 2;
        DCRCboBox_Nbr = 4;
        DCRChkBox_Nbr = 9;
        DCRLblE3_Nbr = 0;
}
TBit3* DCR_12401::SetLblE3(){
        TBit3* LblE;
        return LblE;
}

TLUT* DCR_12401::SetLUT(){
        TLUT* LUT = new TLUT[1];
        if(MainForm->addr_place == 0){
                SetAddr(&LUT[0], BL_DIM);
        }else if(MainForm->addr_place == 1){
                GetAddr(&LUT[0], "BL_DIM");
        }
        return LUT;
}

TBit* DCR_12401::SetScrollBar(){
        TBit* ScrlB = new TBit [DCRScrollBar_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ScrlB[0],PWM_BL_IDX);
                SetAddr(&ScrlB[1],BL_FRM_INTV);
                SetAddr(&ScrlB[2],BL_GRAD_STEP);
                SetAddr(&ScrlB[3],IMG_DIFF);
                SetAddr(&ScrlB[4],PWM_FREQ);
                SetAddr(&ScrlB[5],SMBUS_DEV_ADDR);
                SetAddr(&ScrlB[6],SMBUS_REG_ADDR);
                SetAddr(&ScrlB[7],MIN_IDX_CUM_RATIO);
                SetAddr(&ScrlB[8],MAX_IDX_CUM_RATIO);
                SetAddr(&ScrlB[9],HIGH_DUTY_THRES);
                SetAddr(&ScrlB[10],TOTAL_DUTY_THRES);
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
TBit2* DCR_12401::SetScrollBar2(){
        TBit2* ScrlB = new TBit2 [DCRScrollBar2_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ScrlB[0],PWM_COEFF_A);
                SetAddr(&ScrlB[1],PWM_COEFF_B);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ScrlB[0],"PWM_COEFF_A");
                GetAddr(&ScrlB[1],"PWM_COEFF_B");
        }
        return ScrlB;
}
TBit* DCR_12401::SetChkBx(){
        TBit* ChkBox = new TBit [DCRChkBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ChkBox[0],BL_EN);
                SetAddr(&ChkBox[1],DYN_BL_EN);
                SetAddr(&ChkBox[2],GLT_EN);
                SetAddr(&ChkBox[3],GLT_DEMO);
                SetAddr(&ChkBox[4],DUTY_DETECT_EN);
                SetAddr(&ChkBox[5],BL_GRAD_EN);
                SetAddr(&ChkBox[6],IMG_DIFF_EN);
                SetAddr(&ChkBox[7],SMBUS_EN);
                SetAddr(&ChkBox[8],PWM_COEFF_EN);
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
                SetAddr(&CboBox[0],PWM_MODE);
                SetAddr(&CboBox[1],BL_POL);
                SetAddr(&CboBox[2],PWM_FL_MODE_SEL);
                SetAddr(&CboBox[3],PWM_LINE_SYNC);
        }else if(MainForm->addr_place == 1){
                GetAddr(&CboBox[0],"PWM_MODE");
                GetAddr(&CboBox[1],"BL_POL");
                GetAddr(&CboBox[2],"PWM_FL_MODE_SEL");
                GetAddr(&CboBox[3],"PWM_LINE_SYNC");
        }
        CboBox[0].choice_nbr = 2;
        CboBox[0].choice = new String [2];
        CboBox[0].choice[0] = "Hz";
        CboBox[0].choice[1] = "kHz";

        CboBox[1].choice_nbr = 2;
        CboBox[1].choice = new String [2];
        CboBox[1].choice[0] = "High Duty On";
        CboBox[1].choice[1] = "Low Duty On";

        CboBox[2].choice_nbr = 2;
        CboBox[2].choice = new String [2];
        CboBox[2].choice[0] = "Frame mode";
        CboBox[2].choice[1] = "Line mode";

        CboBox[3].choice_nbr = 4;
        CboBox[3].choice = new String [4];
        CboBox[3].choice[0] = "DE";
        CboBox[3].choice[1] = "XSTB_PE";
        CboBox[3].choice[2] = "XSTB_NE";
        CboBox[3].choice[3] = "XDIO";

        return CboBox;
}
