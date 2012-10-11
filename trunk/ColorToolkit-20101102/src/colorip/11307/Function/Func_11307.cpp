#include <colorip/includeallcolorip.h>
#pragma hdrstop

#include "Func_11307.h"
//#include "Function1.h"
#include <colorip/11307/TCON/TCON_11307.h>
//---------------------------------------------------------------------------

#pragma package(smart_init)
Func_11307::Func_11307()
{
    PstateChkBox_Nbr = 2;	//Number of CheckBox in Pstate page
    PstateCboBox_Nbr = 1;	//Number of ComboBox in Pstate page
    PstateLblE2_Nbr = 4;	//Number of LabeledEdit2 in Pstate page

    AGBSChkBox_Nbr = 3;		//Number of CheckBox in AGBS page
    AGBSCboBox_Nbr = 0;		//Number of ComboBox in AGBS page
    AGBSLblE2_Nbr = 3;		//Number of LabeledEdit2 in AGBS page

    FrcDgChkBox_Nbr = 6;	//Number of CheckBox in FrcDg page
    FrcDgCboBox_Nbr = 1;	//Number of ComboBox in FrcDg page
    FrcDgLblE_Nbr = 0;		//Number of LabeledEdit in FrcDg page

    ODChkBox_Nbr = 0;		//Number of CheckBox in OD page
    ODCboBox_Nbr = 0;		//Number of ComboBox in OD page
    ODCboBox2_Nbr = 0;		//Number of ComboBox2 in OD page
    ODScrollBar_Nbr = 0;	//Number of ScrollBar in OD page

    //DGLUT_Nbr = 4;
    DGLUT_Nbr = 3;
}


//FRC/DG**********************************************************************
TBit *Func_11307::SetFrcDgChkBx()
{
    TBit *ChkBox = new TBit[FrcDgChkBox_Nbr];
    if (false == MainForm->addressFromFile) {
	setAddress(&ChkBox[0], FRC_EN);	//
	setAddress(&ChkBox[1], FRC_DEMO_EN);	//
	setAddress(&ChkBox[2], FRC_DEMO_LEFTEN);	//
	setAddress(&ChkBox[3], GAM_EN);	//
	setAddress(&ChkBox[4], SPECIAL_2LINE);	//
	setAddress(&ChkBox[5], OP6B);	//

    } else {
	setAddressFromFile(&ChkBox[0], "FRC_EN");
	setAddressFromFile(&ChkBox[1], "FRC_DEMO_EN");
	setAddressFromFile(&ChkBox[2], "FRC_DEMO_LEFTEN");
	setAddressFromFile(&ChkBox[3], "GAM_EN");
	setAddressFromFile(&ChkBox[4], "SPECIAL_2LINE");
	setAddressFromFile(&ChkBox[5], "OP6B");
    }
    return ChkBox;
}

TBit *Func_11307::SetFrcDgCboBx()
{
    TBit *CboBox = new TBit[FrcDgCboBox_Nbr];
    if (false == MainForm->addressFromFile) {
	setAddress(&CboBox[0], FRAME_DEMO);	//
    } else {
	setAddressFromFile(&CboBox[0], "FRAME_DEMO");
    }
    CboBox[0].choice_nbr = 16;
    CboBox[0].choice = new String[16];
    CboBox[0].choice[0] = " 0 ";
    CboBox[0].choice[1] = " 1 ";
    CboBox[0].choice[2] = " 2 ";
    CboBox[0].choice[3] = " 3 ";
    CboBox[0].choice[4] = " 4 ";
    CboBox[0].choice[5] = " 5 ";
    CboBox[0].choice[6] = " 6 ";
    CboBox[0].choice[7] = " 7 ";
    CboBox[0].choice[8] = " 8 ";
    CboBox[0].choice[9] = " 9 ";
    CboBox[0].choice[10] = " 10 ";
    CboBox[0].choice[11] = " 11 ";
    CboBox[0].choice[12] = " 12 ";
    CboBox[0].choice[13] = " 13 ";
    CboBox[0].choice[14] = " 14 ";
    CboBox[0].choice[15] = " 15 ";

    return CboBox;
}

TBit *Func_11307::SetFrcDgLblE()
{
    TBit *LEdt = new TBit[FrcDgLblE_Nbr];
    if (false == MainForm->addressFromFile) {
	//setAddress(&LEdt[0],FRC_FRMCHG);
    } else {
	//setAddress(&LEdt[0],"FRC_FRMCHG");
    }
    return LEdt;
}

//**********************************************************************

//P-state**********************************************************************
TBit *Func_11307::SetPstateChkBx()
{
    TBit *ChkBox = new TBit[PstateChkBox_Nbr];
    if (false == MainForm->addressFromFile) {
	setAddress(&ChkBox[0], PSTATE_EN);	//
	setAddress(&ChkBox[1], FR_DET_EN);	// 
    } else {
	setAddressFromFile(&ChkBox[0], "PSTATE_EN");
	setAddressFromFile(&ChkBox[1], "FR_DET_EN");
    }
    return ChkBox;
}

TBit *Func_11307::SetPstateCboBx()
{
    TBit *CboBox = new TBit[PstateCboBox_Nbr];
    if (false == MainForm->addressFromFile) {
	setAddress(&CboBox[0], STOPFRM);	//
    } else {
	setAddressFromFile(&CboBox[0], "STOPFRM");
    }
    CboBox[0].choice_nbr = 3;
    CboBox[0].choice = new String[3];
    CboBox[0].choice[0] = "Stop 0 Frame";
    CboBox[0].choice[1] = "Stop 1 Frame";
    CboBox[0].choice[2] = "Stop 2 Frame";
    return CboBox;
}

TBit2 *Func_11307::SetPstateLblE2()
{
    TBit2 *LEdt = new TBit2[PstateLblE2_Nbr];
    if (false == MainForm->addressFromFile) {
	setAddress(&LEdt[0], CLK_DET_PERIOD);	//
	setAddress(&LEdt[1], PSTATE_DET_PRIOD);	//
	setAddress(&LEdt[2], FR_DIFF_THR);	// 
	setAddress(&LEdt[3], FR_DET_NUM);	//
    } else {
	/*setAddress(&LEdt[0], "CLK_DET_PERIOD");
	   setAddress(&LEdt[1], "PSTATE_DET_PRIOD");
	   setAddress(&LEdt[2], "FR_DIFF_THR");
	   setAddress(&LEdt[3], "FR_DET_NUM"); */

    }
    return LEdt;
}

//**********************************************************************

//AGBS******************************************************************
TBit *Func_11307::SetAGBSChkBx()
{
    TBit *ChkBox = new TBit[AGBSChkBox_Nbr];
    if (false == MainForm->addressFromFile) {
	setAddress(&ChkBox[0], AGBSEN_INV);	//
	setAddress(&ChkBox[1], CHESS_EN);	//
	setAddress(&ChkBox[2], AGING_SRC);	//
    } else {
	setAddressFromFile(&ChkBox[0], "AGBSEN_INV");
	setAddressFromFile(&ChkBox[1], "CHESS_EN");
	setAddressFromFile(&ChkBox[2], "AGING_SRC");
    }
    return ChkBox;
}

TBit *Func_11307::SetAGBSCboBx()
{
    TBit *CboBox = new TBit[AGBSCboBox_Nbr];
    if (false == MainForm->addressFromFile) {
	//setAddress(&CboBox[0],AG_TYPE);
    } else {
	//setAddress(&CboBox[0],"AG_TYPE");
    }
    /*
       CboBox[0].choice_nbr = 4;
       CboBox[0].choice = new String [4];
       CboBox[0].choice[0] = "TCON1(Front/Back,Up/Down dual/single driving)";
       CboBox[0].choice[1] = "TCON2(Front/Back,Up/Down dual driving)";
       CboBox[0].choice[2] = "TCON1(Even/Odd dual driving)";
       CboBox[0].choice[3] = "TCON2(Even/Odd dual driving)"; */
    return CboBox;
}

TBit2 *Func_11307::SetAGBSLblE2()
{
    TBit2 *LEdt = new TBit2[AGBSLblE2_Nbr];
    /*for (int x = 0; x < AGBSLblE2_Nbr; x++) {
       TBit2 a = LEdt[x];
       } */
    if (false == MainForm->addressFromFile) {
	setAddress(&LEdt[0], AG_HBLK);	//
	setAddress(&LEdt[1], AG_VBLK);	//
	setAddress(&LEdt[2], AG_SPEED);	//
    } else {
	setAddressFromFile(&LEdt[0], "AG_HBLK");
	setAddressFromFile(&LEdt[1], "AG_VBLK");
	setAddressFromFile(&LEdt[2], "AG_SPEED");
    }
    return LEdt;
}

//**********************************************************************

//OD
TBit *Func_11307::SetODChkBx()
{
    TBit *ChkBox = new TBit[ODChkBox_Nbr];
    if (false == MainForm->addressFromFile) {
	//setAddress(&ChkBox[0],OD_EN);
	//setAddress(&ChkBox[1],OD_DEMO);
	//setAddress(&ChkBox[2],SDR_CHKEN);
    } else {
	//setAddress(&ChkBox[0],"OD_EN");
	//setAddress(&ChkBox[1],"OD_DEMO");
	//setAddress(&ChkBox[2],"SDR_CHKEN");
    }
    return ChkBox;
}

TBit *Func_11307::SetODCboBx()
{
    TBit *CboBox = new TBit[ODCboBox_Nbr];
    if (false == MainForm->addressFromFile) {
	//setAddress(&CboBox[0],SEL_OD);
	//setAddress(&CboBox[1],ODLUTSEL_INV);
	//setAddress(&CboBox[2],SCALE16);
    } else {
	//setAddress(&CboBox[0],"SEL_OD");
	//setAddress(&CboBox[1],"ODLUTSEL_INV");
	//setAddress(&CboBox[2],"SCALE16");
    }
    CboBox[0].choice_nbr = 2;
    CboBox[0].choice = new String[2];
    CboBox[0].choice[0] = "OD Before Gamma & FRC";
    CboBox[0].choice[1] = "OD After Gamma & FRC";

    CboBox[1].choice_nbr = 2;
    CboBox[1].choice = new String[2];
    CboBox[1].choice[0] = "Non Inversion";
    CboBox[1].choice[1] = "Inversion";

    CboBox[2].choice_nbr = 2;
    CboBox[2].choice = new String[2];
    CboBox[2].choice[0] = "8 step";
    CboBox[2].choice[1] = "16 step";
    return CboBox;
}

TBit2 *Func_11307::SetODCboBx2()
{
    TBit2 *CboBox = new TBit2[ODCboBox_Nbr];
    if (false == MainForm->addressFromFile) {
	//setAddress(&CboBox[0],OD_LEVEL_SEL);
    } else {
	//setAddress(&CboBox[0],"OD_LEVEL_SEL");
    }
    CboBox[0].choice_nbr = 8;
    CboBox[0].choice = new String[8];
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

TBit *Func_11307::SetODScrollBar()
{
    TBit *ScrlB = new TBit[ODScrollBar_Nbr];
    if (false == MainForm->addressFromFile) {
	//setAddress(&ScrlB[0],OD_THR);
	//setAddress(&ScrlB[1],OD_THR_VALUE1);
	//setAddress(&ScrlB[2],OD_THR_VALUE2);
    } else {
	//setAddress(&ScrlB[0],"OD_THR");
	//setAddress(&ScrlB[1],"OD_THR_VALUE1");
	//setAddress(&ScrlB[2],"OD_THR_VALUE2");
    }
    return ScrlB;
}


TLUT *Func_11307::SetDGLUT()
{
    TLUT *LUT = new TLUT[DGLUT_Nbr];
    if (false == MainForm->addressFromFile) {
	setAddress(&LUT[0], DG_LUTR);
	setAddress(&LUT[1], DG_LUTG);
	setAddress(&LUT[2], DG_LUTB);
	//setAddress(&LUT[3], DG_LUTW);
    } else {
	setAddressFromFile(&LUT[0], "DG_LUTR");
	setAddressFromFile(&LUT[1], "DG_LUTG");
	setAddressFromFile(&LUT[2], "DG_LUTB");
	//setAddress(&LUT[3], "DG_LUTW");
    }
    return LUT;

}

TLUT *Func_11307::SetODLUT()
{
    TLUT *LUT = new TLUT[1];
    if (false == MainForm->addressFromFile) {
	//setAddress(&LUT[0],OD_LUT);
    } else {
    }
    return LUT;
}

String Func_11307::OD_EN_Name()
{
    return OD_FUNC_EN_NAME;
}

String Func_11307::DG_EN_Name()
{
    return DG_FUNC_EN_NAME;
}

int Func_11307::ODLUT_IP_Type()
{				// OD IP TYPE  1: AUO IP , 2: Vender IP
    return ODLUT_IP_TYPE;
}

