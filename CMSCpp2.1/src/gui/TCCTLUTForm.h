//---------------------------------------------------------------------------

#ifndef TCCTLUTFormH
#define TCCTLUTFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <cms/lcd/calibrate/lcdcalibrator.h>
//---------------------------------------------------------------------------
class TCCTLUTForm:public TForm {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox1;
    TLabel *Label1;
    TEdit *Edit_StartLevel;
    TLabel *Label2;
    TLabel *Label3;
    TComboBox *ComboBox_LevelStep;
    TEdit *Edit_EndLevel;
    TGroupBox *GroupBox2;
    TRadioButton *RadioButton_GammaCurve;
    TButton *Button_LoadGammaCurve;
    TCheckBox *CheckBox_GByPass;
    TRadioButton *RadioButton_Gamma;
    TComboBox *ComboBox_Gamma;
    TGroupBox *GroupBox3;
    TRadioButton *RadioButton_P1P2;
    TRadioButton *RadioButton_RBInterp;
    TLabel *Label4;
    TEdit *Edit_RBInterpUnder;
    TGroupBox *GroupBox4;
    TCheckBox *CheckBox_BGain;
    TEdit *Edit_BGain;
    TCheckBox *CheckBox_BMax;
    TGroupBox *GroupBox5;
    TCheckBox *CheckBox_Gamma256;
    TCheckBox *CheckBox_AvoidNoise;
    TGroupBox *GroupBox6;
    TGroupBox *GroupBox7;
    TLabel *Label5;
    TEdit *Edit_Prefix;
    TLabel *Label6;
    TEdit *Edit_Directory;
    TButton *Button_BrowseDir;
    TOpenDialog *OpenDialog1;
    TButton *Button_Run;
    TGroupBox *GroupBox8;
    TGroupBox *GroupBox9;
    TGroupBox *GroupBox10;
    TRadioButton *RadioButton_In6;
    TRadioButton *RadioButton_In8;
    TRadioButton *RadioButton_In10;
    TRadioButton *RadioButton_Lut10;
    TRadioButton *RadioButton_Lut12;
    TRadioButton *RadioButton_Out6;
    TRadioButton *RadioButton_Out8;
    TRadioButton *RadioButton_Out10;
    TLabel *Label7;
    TEdit *Edit_P1;
    TLabel *Label8;
    TEdit *Edit_P2;
    TButton *Button_Debug;
    TRadioButton *RadioButton_None;
    TButton *Button_Reset;
    TCheckBox *CheckBox_KeepMax;
    void __fastcall Button_BrowseDirClick(TObject * Sender);
    void __fastcall RadioButton_In6Click(TObject * Sender);
    void __fastcall RadioButton_In8Click(TObject * Sender);
    void __fastcall RadioButton_In10Click(TObject * Sender);
    void __fastcall RadioButton_RBInterpClick(TObject * Sender);
    void __fastcall RadioButton_P1P2Click(TObject * Sender);
    void __fastcall Button_RunClick(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall Button_DebugClick(TObject * Sender);
    void __fastcall Button_ResetClick(TObject * Sender);
    void __fastcall RadioButton_Out6Click(TObject * Sender);
    void __fastcall RadioButton_Out8Click(TObject * Sender);
    void __fastcall Button_LoadGammaCurveClick(TObject * Sender);
    void __fastcall CheckBox_Gamma256Click(TObject * Sender);
    void __fastcall RadioButton_Out10Click(TObject * Sender);
    void __fastcall FormShow(TObject * Sender);
    void __fastcall RadioButton_Lut12Click(TObject * Sender);
    void __fastcall RadioButton_Lut10Click(TObject * Sender);
  private:			// User declarations
    void setBitDepthEnable(bool lut10, bool lut12, bool out6, bool out8,
			   bool out10);
    void setBitDepthChecked(int lutSelect, int outSelect);
    void setMeasureInfo();
    int serialid;
     bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth;
    int in, lut, out;


  public:			// User declarations
     __fastcall TCCTLUTForm(TComponent * Owner);
    void setTCONInput(bool tconInput);
};
//---------------------------------------------------------------------------
extern PACKAGE TCCTLUTForm *CCTLUTForm;
//---------------------------------------------------------------------------
#endif

