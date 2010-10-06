
#pragma hdrstop

#include "Func_12401.h"
#include "Function1.h"
#include "TCON_12401.h"
#include "auo_12401_address.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
Func_12401::Func_12401(){
        PstateChkBox_Nbr = 2;       //Number of CheckBox in Pstate page
        PstateCboBox_Nbr = 1;       //Number of ComboBox in Pstate page
        PstateLblE2_Nbr = 4;       //Number of LabeledEdit2 in Pstate page

        AGBSChkBox_Nbr = 2;       //Number of CheckBox in AGBS page
        AGBSCboBox_Nbr = 1;       //Number of ComboBox in AGBS page
        AGBSLblE2_Nbr = 3;       //Number of LabeledEdit2 in AGBS page

        FrcDgChkBox_Nbr = 5;       //Number of CheckBox in FrcDg page
        FrcDgCboBox_Nbr = 1;       //Number of ComboBox in FrcDg page
        FrcDgLblE_Nbr = 1;       //Number of LabeledEdit in FrcDg page

        ODChkBox_Nbr = 3;          //Number of CheckBox in OD page
        ODCboBox_Nbr = 3;          //Number of ComboBox in OD page
        ODCboBox2_Nbr = 1;         //Number of ComboBox2 in OD page
        ODScrollBar_Nbr = 3;       //Number of ScrollBar in OD page

        //DGLUT_Nbr = 4;
        DGLUT_Nbr = 3;
}


//FRC/DG
TBit* Func_12401::SetFrcDgChkBx(){
        TBit* ChkBox = new TBit [FrcDgChkBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ChkBox[0],FRC_EN);
                SetAddr(&ChkBox[1],FRC_DEMO);
                SetAddr(&ChkBox[2],FRC_SPECIAL_2H);
                SetAddr(&ChkBox[3],GAM_EN);
                SetAddr(&ChkBox[4],GAM_DEMO);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBox[0],"FRC_EN");
                GetAddr(&ChkBox[1],"FRC_DEMO");
                GetAddr(&ChkBox[2],"FRC_SPECIAL_2H");
                GetAddr(&ChkBox[3],"GAM_EN");
                GetAddr(&ChkBox[4],"GAM_DEMO");
        }
        return ChkBox;
}
TBit* Func_12401::SetFrcDgCboBx(){
        TBit* CboBox = new TBit [FrcDgCboBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&CboBox[0],FRC_MODE);
        }else if(MainForm->addr_place == 1){
                GetAddr(&CboBox[0],"FRC_MODE");
        }
        CboBox[0].choice_nbr = 4;
        CboBox[0].choice = new String [4];
        CboBox[0].choice[0] = "Normal (Single TCON)";
        CboBox[0].choice[1] = "CH1 and CH3 output (Dual TCON)";
        CboBox[0].choice[2] = "CH2 and CH4 output (Dual TCON)";
        CboBox[0].choice[3] = "Normal (Single TCON)";
        return CboBox;
}
TBit* Func_12401::SetFrcDgLblE(){
        TBit* LEdt = new TBit [FrcDgLblE_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&LEdt[0],FRC_FRMCHG);
        }else if(MainForm->addr_place == 1){
                GetAddr(&LEdt[0],"FRC_FRMCHG");
        }
        return LEdt;
}

//P-state
TBit* Func_12401::SetPstateChkBx(){
        TBit* ChkBox = new TBit [PstateChkBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ChkBox[0],Pstate_en);
                SetAddr(&ChkBox[1],FR_DETECT_EN);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBox[0],"Pstate_en");
                GetAddr(&ChkBox[1],"FR_DETECT_EN");
        }
        return ChkBox;
}
TBit* Func_12401::SetPstateCboBx(){
        TBit* CboBox = new TBit [PstateCboBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&CboBox[0],STOPFRM);
        }else if(MainForm->addr_place == 1){
                GetAddr(&CboBox[0],"STOPFRM");
        }
        CboBox[0].choice_nbr = 3;
        CboBox[0].choice = new String [3];
        CboBox[0].choice[0] = "0 Frame";
        CboBox[0].choice[1] = "1 Frame";
        CboBox[0].choice[2] = "2 Frame";
        return CboBox;
}

TBit2* Func_12401::SetPstateLblE2(){
        TBit2* LEdt = new TBit2 [PstateLblE2_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&LEdt[0],CLK_DET_PERIOD);
                SetAddr(&LEdt[1],PSTATE_DET_PRIOD);
                SetAddr(&LEdt[2],FR_DETECT_THRTD);
                SetAddr(&LEdt[3],FR_DETECT_NUM);
        }else if(MainForm->addr_place == 1){
                GetAddr(&LEdt[0],"CLK_DET_PERIOD");
                GetAddr(&LEdt[1],"PSTATE_DET_PRIOD");
                GetAddr(&LEdt[2],"FR_DETECT_THRTD");
                GetAddr(&LEdt[3],"FR_DETECT_NUM");
        }
        return LEdt;
}

//AGBS
TBit* Func_12401::SetAGBSChkBx(){
        TBit* ChkBox = new TBit [AGBSChkBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ChkBox[0],AGBSEN_INV);
                SetAddr(&ChkBox[1],CHESS_EN);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBox[0],"AGBSEN_INV");
                GetAddr(&ChkBox[1],"CHESS_EN");
        }
        return ChkBox;
}
TBit* Func_12401::SetAGBSCboBx(){
        TBit* CboBox = new TBit [AGBSCboBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&CboBox[0],AG_TYPE);
        }else if(MainForm->addr_place == 1){
                GetAddr(&CboBox[0],"AG_TYPE");
        }
        CboBox[0].choice_nbr = 4;
        CboBox[0].choice = new String [4];
        CboBox[0].choice[0] = "TCON1(Front/Back,Up/Down dual/single driving)";
        CboBox[0].choice[1] = "TCON2(Front/Back,Up/Down dual driving)";
        CboBox[0].choice[2] = "TCON1(Even/Odd dual driving)";
        CboBox[0].choice[3] = "TCON2(Even/Odd dual driving)";
        return CboBox;
}
TBit2* Func_12401::SetAGBSLblE2(){
        TBit2* LEdt = new TBit2 [AGBSLblE2_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&LEdt[0],AG_HBLK);
                SetAddr(&LEdt[1],VG_HBLK);
                SetAddr(&LEdt[2],AG_SPEED);
        }else if(MainForm->addr_place == 1){
                GetAddr(&LEdt[0],"AG_HBLK");
                GetAddr(&LEdt[1],"VG_HBLK");
                GetAddr(&LEdt[2],"AG_SPEED");
        }
        return LEdt;
}

//OD
TBit* Func_12401::SetODChkBx(){
        TBit* ChkBox = new TBit [ODChkBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ChkBox[0],OD_EN);
                SetAddr(&ChkBox[1],OD_DEMO);
                SetAddr(&ChkBox[2],SDR_CHKEN);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ChkBox[0],"OD_EN");
                GetAddr(&ChkBox[1],"OD_DEMO");
                GetAddr(&ChkBox[2],"SDR_CHKEN");
        }
        return ChkBox;
}
TBit* Func_12401::SetODCboBx(){
        TBit* CboBox = new TBit [ODCboBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&CboBox[0],SEL_OD);
                SetAddr(&CboBox[1],ODLUTSEL_INV);
                SetAddr(&CboBox[2],SCALE16);
        }else if(MainForm->addr_place == 1){
                GetAddr(&CboBox[0],"SEL_OD");
                GetAddr(&CboBox[1],"ODLUTSEL_INV");
                GetAddr(&CboBox[2],"SCALE16");
        }
        CboBox[0].choice_nbr = 2;
        CboBox[0].choice = new String [2];
        CboBox[0].choice[0] = "OD Before Gamma & FRC";
        CboBox[0].choice[1] = "OD After Gamma & FRC";

        CboBox[1].choice_nbr = 2;
        CboBox[1].choice = new String [2];
        CboBox[1].choice[0] = "Non Inversion";
        CboBox[1].choice[1] = "Inversion";

        CboBox[2].choice_nbr = 2;
        CboBox[2].choice = new String [2];
        CboBox[2].choice[0] = "8 step";
        CboBox[2].choice[1] = "16 step";
        return CboBox;
}
TBit2* Func_12401::SetODCboBx2(){
        TBit2* CboBox = new TBit2 [ODCboBox_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&CboBox[0],OD_LEVEL_SEL);
        }else if(MainForm->addr_place == 1){
                GetAddr(&CboBox[0],"OD_LEVEL_SEL");
        }
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
        return CboBox;
}
TBit* Func_12401::SetODScrollBar()
{
        TBit* ScrlB = new TBit [ODScrollBar_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&ScrlB[0],OD_THR);
                SetAddr(&ScrlB[1],OD_THR_VALUE1);
                SetAddr(&ScrlB[2],OD_THR_VALUE2);
        }else if(MainForm->addr_place == 1){
                GetAddr(&ScrlB[0],"OD_THR");
                GetAddr(&ScrlB[1],"OD_THR_VALUE1");
                GetAddr(&ScrlB[2],"OD_THR_VALUE2");
        }
        return ScrlB;
}


TLUT* Func_12401::SetDGLUT(){
        TLUT* LUT = new TLUT [DGLUT_Nbr];
        if(MainForm->addr_place == 0){
                SetAddr(&LUT[0], DG_LUTR);
                SetAddr(&LUT[1], DG_LUTG);
                SetAddr(&LUT[2], DG_LUTB);
                //SetAddr(&LUT[3], DG_LUTW);
        }else if(MainForm->addr_place == 1){
                GetAddr(&LUT[0], "DG_LUTR");
                GetAddr(&LUT[1], "DG_LUTG");
                GetAddr(&LUT[2], "DG_LUTB");
                //GetAddr(&LUT[3], "DG_LUTW");
        }
        return LUT;

}

TLUT* Func_12401::SetODLUT()
{
        TLUT* LUT = new TLUT [1];
        if(MainForm->addr_place == 0){
                SetAddr(&LUT[0],OD_LUT);
        }else if(MainForm->addr_place == 1){
                GetAddr(&LUT[0],"OD_LUT");
        }
        return LUT;
}

String Func_12401::OD_EN_Name()
{       return OD_FUNC_EN_NAME; }

String Func_12401::DG_EN_Name()
{        return DG_FUNC_EN_NAME; }

int Func_12401::ODLUT_IP_Type()
{       // OD IP TYPE  1: AUO IP , 2: Vender IP
        return ODLUT_IP_TYPE;
}


