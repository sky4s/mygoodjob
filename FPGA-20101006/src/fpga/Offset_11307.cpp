//---------------------------------------------------------------------------

#include <fpga/includeall.h>
#pragma hdrstop

#include "Offset_11307.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
offsetForm_11307::offsetForm_11307(){
        ScrollBar_Nbr = 1;
        ScrollBar2_Nbr = 0;
        CboBox_Nbr = 0;
        ChkBox_Nbr = 3;
        LblE3_Nbr = 0;
        LblE4_Nbr = 0;
}
// CheckBox
TBit* offsetForm_11307::SetChkBx(){
        TBit* ChkBox = new TBit [ChkBox_Nbr];
        SetAddr(&ChkBox[0],OFFSET_EN);
        SetAddr(&ChkBox[1],OFFSET_DEMO);
        SetAddr(&ChkBox[2],OFFSET_DEMO_LEFT);
        return ChkBox;
}

// ComboBox
TBit* offsetForm_11307::SetCboBx(){
        TBit* CboBox = new TBit [CboBox_Nbr];
        //SetAddr(&CboBox[0],PWM_MODE);

        /*CboBox[0].choice_nbr = 2;
        CboBox[0].choice = new String [2];
        CboBox[0].choice[0] = "Hz";
        CboBox[0].choice[1] = "kHz";     */

        return CboBox;
}

// LabeledEdit 3 byte
TBit3* offsetForm_11307::SetLblE3(){
        TBit3* LblE = new TBit3 [LblE3_Nbr];
        return LblE;
}

// LabeledEdit 4 byte
TBit4* offsetForm_11307::SetLblE4(){
        TBit4* LblE = new TBit4 [LblE4_Nbr];
        return LblE;
}

// ScrollBar 1 byte
TBit* offsetForm_11307::SetScrollBar(){
        TBit* ScrlB = new TBit [ScrollBar_Nbr];
        SetAddr(&ScrlB[0],OFFSET_LEVEL);
        return ScrlB;
}

// ScrollBar 2 byte
TBit2* offsetForm_11307::SetScrollBar2(){
        TBit2* ScrlB = new TBit2 [ScrollBar2_Nbr];
        //SetAddr(&ScrlB[0],PWM_COEFF_A);
        return ScrlB;
}

