//---------------------------------------------------------------------------

#ifndef TGammaMeasurementFormH
#define TGammaMeasurementFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TGammaMeasurementForm:public TForm {
    __published:		// IDE-managed Components
    TPanel * Panel1;
    TGroupBox *GroupBox1;
    TGroupBox *GroupBox2;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TEdit *Edit_StartLevel;
    TComboBox *ComboBox_LevelStep;
    TEdit *Edit_EndLevel;
    TGroupBox *GroupBox3;
    TCheckBox *CheckBox_W;
    TCheckBox *CheckBox_R;
    TCheckBox *CheckBox_G;
    TCheckBox *CheckBox_B;
    TGroupBox *GroupBox4;
    TEdit *Edit_Channel;
    TButton *Button_PCMeasure;
    TLabel *Copyright;
    TPanel *Panel2;
    TGroupBox *GroupBox5;
    TGroupBox *GroupBox6;
    TGroupBox *GroupBox7;
    TRadioButton *RadioButton1;
    TRadioButton *RadioButton2;
    TGroupBox *GroupBox8;
    TGroupBox *GroupBox9;
    TCheckBox *CheckBox5;
    TCheckBox *CheckBox6;
    TRadioButton *RadioButton3;
    TRadioButton *RadioButton4;
    TLabel *Label4;
    TButton *Button2;
    TGroupBox *GroupBox10;
    TCheckBox *CheckBox_W2;
    TCheckBox *CheckBox_R2;
    TCheckBox *CheckBox_G2;
    TCheckBox *CheckBox_B2;
    TGroupBox *GroupBox11;
    TEdit *Edit_Channel2;
    TButton *Button_TCONMeasure;
    void __fastcall Button_PCMeasureClick(TObject * Sender);
    void __fastcall Button_TCONMeasureClick(TObject * Sender);
  private:			// User declarations
  public:			// User declarations
     __fastcall TGammaMeasurementForm(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGammaMeasurementForm *GammaMeasurementForm;
//---------------------------------------------------------------------------
#endif

