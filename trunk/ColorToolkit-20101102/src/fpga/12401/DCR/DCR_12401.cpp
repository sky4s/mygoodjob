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
        DCRLblE4_Nbr = 1;
        DCRLUT_Nbr = 2;
}
TBit3* DCR_12401::SetLblE3(){
        TBit3* LblE = new TBit3 [DCRLblE3_Nbr];
        return LblE;
}

// DCRLblE4
TBit4* DCR_12401::SetLblE4(){
        TBit4* LblE = new TBit4 [DCRLblE4_Nbr];
        return LblE;
}


TLUT* DCR_12401::SetLUT(){
        TLUT* LUT = new TLUT[DCRLUT_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&LUT[0], BL);
                setAddress(&LUT[1], DIM);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&LUT[0], "BL");
                setAddressFromFile(&LUT[1], "DIM");
        }
        return LUT;
}

TBit* DCR_12401::SetScrollBar(){
        TBit* ScrlB = new TBit [DCRScrollBar_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&ScrlB[0],PWM_BL_IDX);
                setAddress(&ScrlB[1],BL_FRM_INTV);
                setAddress(&ScrlB[2],BL_GRAD_STEP);
                setAddress(&ScrlB[3],IMG_DIFF);
                setAddress(&ScrlB[4],PWM_FREQ);
                setAddress(&ScrlB[5],SMBUS_DEV_ADDR);
                setAddress(&ScrlB[6],SMBUS_REG_ADDR);
                setAddress(&ScrlB[7],MIN_IDX_CUM_RATIO);
                setAddress(&ScrlB[8],MAX_IDX_CUM_RATIO);
                setAddress(&ScrlB[9],HIGH_DUTY_THRES);
                setAddress(&ScrlB[10],TOTAL_DUTY_THRES);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&ScrlB[0],"PWM_BL_IDX");
                setAddressFromFile(&ScrlB[1],"BL_FRM_INTV");
                setAddressFromFile(&ScrlB[2],"BL_GRAD_STEP");
                setAddressFromFile(&ScrlB[3],"IMG_DIFF");
                setAddressFromFile(&ScrlB[4],"PWM_FREQ");
                setAddressFromFile(&ScrlB[5],"SMBUS_DEV_ADDR");
                setAddressFromFile(&ScrlB[6],"SMBUS_REG_ADDR");
                setAddressFromFile(&ScrlB[7],"MIN_IDX_CUM_RATIO");
                setAddressFromFile(&ScrlB[8],"MAX_IDX_CUM_RATIO");
                setAddressFromFile(&ScrlB[9],"HIGH_DUTY_THRES");
                setAddressFromFile(&ScrlB[10],"TOTAL_DUTY_THRES");
        }
        return ScrlB;
}
TBit2* DCR_12401::SetScrollBar2(){
        TBit2* ScrlB = new TBit2 [DCRScrollBar2_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&ScrlB[0],PWM_COEFF_A);
                setAddress(&ScrlB[1],PWM_COEFF_B);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&ScrlB[0],"PWM_COEFF_A");
                setAddressFromFile(&ScrlB[1],"PWM_COEFF_B");
        }
        return ScrlB;
}
TBit* DCR_12401::SetChkBx(){
        TBit* ChkBox = new TBit [DCRChkBox_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&ChkBox[0],BL_EN);
                setAddress(&ChkBox[1],DYN_BL_EN);
                setAddress(&ChkBox[2],GLT_EN);
                setAddress(&ChkBox[3],GLT_DEMO);
                setAddress(&ChkBox[4],DUTY_DETECT_EN);
                setAddress(&ChkBox[5],BL_GRAD_EN);
                setAddress(&ChkBox[6],IMG_DIFF_EN);
                setAddress(&ChkBox[7],SMBUS_EN);
                setAddress(&ChkBox[8],PWM_COEFF_EN);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&ChkBox[0],"BL_EN");
                setAddressFromFile(&ChkBox[1],"DYN_BL_EN");
                setAddressFromFile(&ChkBox[2],"GLT_EN");
                setAddressFromFile(&ChkBox[3],"GLT_DEMO");
                setAddressFromFile(&ChkBox[4],"DUTY_DETECT_EN");
                setAddressFromFile(&ChkBox[5],"BL_GRAD_EN");
                setAddressFromFile(&ChkBox[6],"IMG_DIFF_EN");
                setAddressFromFile(&ChkBox[7],"SMBUS_EN");
                setAddressFromFile(&ChkBox[8],"PWM_COEFF_EN");
        }
        return ChkBox;
}
TBit* DCR_12401::SetCboBx(){
        TBit* CboBox = new TBit [DCRCboBox_Nbr];
        if(MainForm->addr_place == 0){
                setAddress(&CboBox[0],PWM_MODE);
                setAddress(&CboBox[1],BL_POL);
                setAddress(&CboBox[2],PWM_FL_MODE_SEL);
                setAddress(&CboBox[3],PWM_LINE_SYNC);
        }else if(MainForm->addr_place == 1){
                setAddressFromFile(&CboBox[0],"PWM_MODE");
                setAddressFromFile(&CboBox[1],"BL_POL");
                setAddressFromFile(&CboBox[2],"PWM_FL_MODE_SEL");
                setAddressFromFile(&CboBox[3],"PWM_LINE_SYNC");
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

String DCR_12401::DCR_BL_EN_Name(){ // 20100608 return BL enable register name
        return DCR_BL_EN_NAME;
}
String DCR_12401::DCR_GLT_EN_Name(){ // 20100608 return GLT enable register name
        return DCR_GLT_EN_NAME;
}
