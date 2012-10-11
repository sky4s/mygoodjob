//---------------------------------------------------------------------------

#ifndef TSharpnessV2_1FormH
#define TSharpnessV2_1FormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TSharpnessV2_1Form : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox3;
        TGroupBox *GroupBox2;
        TLabel *Software;
        TScrollBar *sb_softgain;
        TStaticText *st_softgain;
        TGroupBox *GroupBox47;
        TImage *SP_LUT;
        TButton *btn_sp_lut_write;
        TButton *btn_sp_lut_Set;
        TBitBtn *btn_sp_lut_read;
        TButton *btn_GainSet;
        TRadioGroup *LUT_type;
        TButton *btn_sp_Load;
        TButton *btn_sp_Save;
        TBitBtn *Btn_SP_reload;
        TGroupBox *Sharpness;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label7;
        TLabel *Label8;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TScrollBar *ScrollBar1;
        TStaticText *StaticText1;
        TScrollBar *ScrollBar2;
        TScrollBar *ScrollBar3;
        TScrollBar *ScrollBar4;
        TStaticText *StaticText2;
        TStaticText *StaticText3;
        TStaticText *StaticText4;
        TCheckBox *CheckBox4;
        TCheckBox *CheckBox5;
        TScrollBar *ScrollBar5;
        TScrollBar *ScrollBar6;
        TStaticText *StaticText5;
        TStaticText *StaticText6;
        TComboBox *ComboBox1;
        TComboBox *ComboBox2;
        TCheckBox *CheckBox6;
        TCheckBox *CheckBox7;
        TGroupBox *Contrast;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label15;
        TLabel *Label16;
        TLabel *Label23;
        TLabel *Label24;
        TCheckBox *CheckBox8;
        TCheckBox *CheckBox9;
        TCheckBox *CheckBox10;
        TCheckBox *CheckBox11;
        TCheckBox *CheckBox12;
        TComboBox *ComboBox3;
        TComboBox *ComboBox4;
        TScrollBar *ScrollBar7;
        TScrollBar *ScrollBar8;
        TScrollBar *ScrollBar11;
        TScrollBar *ScrollBar12;
        TStaticText *StaticText7;
        TStaticText *StaticText8;
        TStaticText *StaticText11;
        TStaticText *StaticText12;
        TLabeledEdit *LabeledEdit1;
        TEdit *Edit_ResolutionH;
        TEdit *Edit_ResolutionV;
        TGroupBox *GroupBox_BrightScene;
        TLabel *Label13;
        TLabel *Label22;
        TScrollBar *ScrollBar9;
        TStaticText *StaticText9;
        TScrollBar *ScrollBar16;
        TStaticText *StaticText16;
        TGroupBox *GroupBox_DarkScene;
        TLabel *Label14;
        TLabel *Label21;
        TScrollBar *ScrollBar10;
        TStaticText *StaticText10;
        TScrollBar *ScrollBar15;
        TStaticText *StaticText15;
        TGroupBox *GroupBox_TurnPoint;
        TLabel *Label17;
        TLabel *Label19;
        TLabel *Label18;
        TLabel *Label20;
        TComboBox *ComboBox5;
        TScrollBar *ScrollBar13;
        TStaticText *StaticText13;
        TComboBox *ComboBox6;
        TScrollBar *ScrollBar14;
        TStaticText *StaticText14;
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
private:	// User declarations
public:		// User declarations
        __fastcall TSharpnessV2_1Form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSharpnessV2_1Form *SharpnessV2_1Form;
//---------------------------------------------------------------------------
#endif
