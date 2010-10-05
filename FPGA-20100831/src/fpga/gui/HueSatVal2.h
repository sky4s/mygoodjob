//---------------------------------------------------------------------------

#ifndef HueSatVal2H
#define HueSatVal2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "HueSatVal1.h"
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class THSVForm2:public THSVForm1 {
    __published:		// IDE-managed Components
        TGroupBox *GroupBox2;
        TGroupBox *GroupBox3;
        TGroupBox *GroupBox4;
        TGroupBox *GroupBox5;
        TGroupBox *GroupBox6;
        TRadioButton *RadioButton_deg0;
        TRadioButton *RadioButton_deg60;
        TRadioButton *RadioButton_deg120;
        TRadioButton *RadioButton_deg180;
        TRadioButton *RadioButton_deg240;
        TRadioButton *RadioButton_deg300;
        TRadioButton *RadioButton1;
        TRadioButton *RadioButton2;
        TRadioButton *RadioButton3;
        TRadioButton *RadioButton4;
        TRadioButton *RadioButton5;
        TRadioButton *RadioButton6;
    void __fastcall sb_Hue_gainScroll(TObject * Sender, TScrollCode ScrollCode, int &ScrollPos);
    void __fastcall sb_Hue_gainChange(TObject * Sender);
  private:			// User declarations
  public:			// User declarations
     __fastcall THSVForm2(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE THSVForm2 *HSVForm2;
//---------------------------------------------------------------------------
#endif

