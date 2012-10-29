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
        TBitBtn *Btn_SP_reload;
        TGroupBox *GroupBox1;
        TRadioGroup *LUT_type;
        TButton *btn_sp_Load;
        TButton *btn_sp_Save;
        TGroupBox *Sharpness;
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TCheckBox *CheckBox3;
        TCheckBox *CheckBox6;
        TGroupBox *GroupBox2;
        TLabel *Label3;
        TGroupBox *GroupBox4;
        TImage *SP_LUT;
        TLabel *Software;
        TButton *btn_sp_lut_write;
        TBitBtn *btn_sp_lut_read;
        TButton *btn_sp_lut_Set;
        TScrollBar *sb_softgain;
        TStaticText *st_softgain;
        TButton *btn_GainSet;
        TScrollBar *ScrollBar3;
        TStaticText *StaticText3;
        TGroupBox *GroupBox5;
        TLabel *Label2;
        TScrollBar *ScrollBar2;
        TStaticText *StaticText2;
        TGroupBox *GroupBox6;
        TLabel *Label1;
        TScrollBar *ScrollBar1;
        TStaticText *StaticText1;
        TGroupBox *GroupBox7;
        TLabel *Label4;
        TCheckBox *CheckBox4;
        TScrollBar *ScrollBar4;
        TStaticText *StaticText4;
        TGroupBox *GroupBox8;
        TLabel *Label5;
        TLabel *Label6;
        TCheckBox *CheckBox5;
        TScrollBar *ScrollBar5;
        TStaticText *StaticText5;
        TScrollBar *ScrollBar6;
        TStaticText *StaticText6;
        TGroupBox *GroupBox9;
        TLabel *Label7;
        TLabel *Label8;
        TComboBox *ComboBox1;
        TComboBox *ComboBox2;
        TGroupBox *GroupBox10;
        TBevel *Bevel1;
        TCheckBox *CheckBox8;
        TCheckBox *CheckBox9;
        TCheckBox *CheckBox10;
        TGroupBox *GroupBox14;
        TLabel *Label17;
        TLabel *Label19;
        TLabel *Label18;
        TLabel *Label20;
        TBevel *Bevel2;
        TComboBox *ComboBox5;
        TScrollBar *ScrollBar13;
        TStaticText *StaticText13;
        TComboBox *ComboBox6;
        TScrollBar *ScrollBar14;
        TStaticText *StaticText14;
        TGroupBox *GroupBox15;
        TLabel *Label14;
        TLabel *Label21;
        TBevel *Bevel3;
        TLabel *Label15;
        TLabel *Label22;
        TBevel *Bevel4;
        TLabel *Label16;
        TScrollBar *ScrollBar10;
        TStaticText *StaticText10;
        TScrollBar *ScrollBar15;
        TStaticText *StaticText15;
        TScrollBar *ScrollBar11;
        TStaticText *StaticText11;
        TScrollBar *ScrollBar16;
        TStaticText *StaticText16;
        TScrollBar *ScrollBar12;
        TStaticText *StaticText12;
        TGroupBox *GroupBox16;
        TLabel *Label25;
        TLabel *Label26;
        TCheckBox *CheckBox12;
        TScrollBar *ScrollBar17;
        TStaticText *StaticText17;
        TScrollBar *ScrollBar18;
        TStaticText *StaticText18;
        TGroupBox *GroupBox11;
        TLabel *Label11;
        TScrollBar *ScrollBar7;
        TStaticText *StaticText7;
        TGroupBox *GroupBox12;
        TLabel *Label9;
        TLabel *Label10;
        TLabel *Label24;
        TLabel *Label23;
        TComboBox *ComboBox3;
        TComboBox *ComboBox4;
        TLabeledEdit *LabeledEdit1;
        TEdit *Edit_ResolutionH;
        TEdit *Edit_ResolutionV;
        TGroupBox *GroupBox13;
        TLabel *Label12;
        TLabel *Label13;
        TCheckBox *CheckBox11;
        TScrollBar *ScrollBar8;
        TScrollBar *ScrollBar9;
        TStaticText *StaticText8;
        TStaticText *StaticText9;
        TSaveDialog *SaveDialog1;
        TOpenDialog *OpenDialog1;
        TCheckBox *CheckBox7;
        TBevel *Bevel5;
        TLabel *Label27;
        TComboBox *ComboBox7;
private:	// User declarations
public:		// User declarations
        __fastcall TSharpnessV2_1Form(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TSharpnessV2_1Form *SharpnessV2_1Form;
//---------------------------------------------------------------------------
#endif
