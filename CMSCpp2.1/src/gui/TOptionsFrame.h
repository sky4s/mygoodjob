//---------------------------------------------------------------------------


#ifndef TOptionsFrameH
#define TOptionsFrameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TOptionsFrame : public TFrame
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox5;
        TGroupBox *GroupBox6;
        TGroupBox *GroupBox8;
        TRadioButton *RadioButton_In6;
        TRadioButton *RadioButton_In8;
        TRadioButton *RadioButton_In10;
        TGroupBox *GroupBox9;
        TRadioButton *RadioButton_Lut10;
        TRadioButton *RadioButton_Lut12;
        TGroupBox *GroupBox10;
        TRadioButton *RadioButton_Out6;
        TRadioButton *RadioButton_Out8;
        TRadioButton *RadioButton_Out10;
        TCheckBox *CheckBox_Gamma256;
        TCheckBox *CheckBox_AvoidNoise;
        TCheckBox *CheckBox_KeepMax;
private:	// User declarations
public:		// User declarations
        __fastcall TOptionsFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOptionsFrame *OptionsFrame;
//---------------------------------------------------------------------------
#endif
