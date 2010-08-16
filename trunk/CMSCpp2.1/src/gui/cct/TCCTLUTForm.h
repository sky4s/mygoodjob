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
#include "TOutputFileFrame.h"
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
    TCheckBox *CheckBox_AvoidNoise;
    TOpenDialog *OpenDialog1;
    TButton *Button_MeaRun;
    TLabel *Label7;
    TEdit *Edit_P1;
    TLabel *Label8;
    TEdit *Edit_P2;
    TButton *Button_Debug;
    TRadioButton *RadioButton_NoneLowLevelCorrect;
    TLabel *Label9;
    TOutputFileFrame *TOutputFileFrame1;
    TCheckBox *CheckBox_Expand;
    TPanel *Panel_Expand;
    TGroupBox *GroupBox6;
    TComboBox *ComboBox_LowStep;
    TLabel *Label5;
    TLabel *Label6;
    TEdit *Edit_LowEndLevel;
    TEdit *Edit_LowStartLevel;
    TLabel *Label10;
    TGroupBox *GroupBox7;
    TLabel *Label11;
    TEdit *Edit_HighStartLevel;
    TEdit *Edit_HighEndLevel;
    TComboBox *ComboBox_HighStep;
    TLabel *Label12;
    TLabel *Label13;
    TButton *Button_Reset;
    TRadioButton *RadioButton_DefinedDim;
    TLabel *Label17;
    TEdit *Edit_DefinedDimUnder;
    TButton *Button_Run;
    TCheckBox *CheckBox_AverageDimDG;
    TLabel *Label14;
    TEdit *Edit_DimGamma;
    TCheckBox *CheckBox_NewMethod;
    TGroupBox *GroupBox_KeepMaxLuminance;
    TRadioButton *RadioButton_MaxYTarget;
    TRadioButton *RadioButton_MaxYNative;
    TRadioButton *RadioButton_MaxYNone;
    TRadioButton *RadioButton_MaxYNativeAdv;
    TLabel *Label20;
    TEdit *Edit_MaxYAdvOver;
    TEdit *Edit_MaxYAdvGamma;
    TLabel *Label21;
    TRadioButton *RadioButton_GammaValue;
    TCheckBox *CheckBox_MultiGen;
    TEdit *Edit_MultiGenTimes;
    TCheckBox *CheckBox_BTargetIntensity;
    TEdit *Edit_BTargetIntensity;
    TCheckBox *CheckBox_AvoidHookNB;
    TRadioButton *RadioButton_OriginalGamma;
    TCheckBox *CheckBox_BMax2;
    TLabel *Label18;
    TEdit *Edit_BMax2Begin;
    TEdit *Edit_BMax2Gamma;
    TLabel *Label19;
    TCheckBox *CheckBox_SkipInverseB;
    TCheckBox *CheckBox_MemoryMeasure;
    TCheckBox *CheckBox_MaxYAdvAuto;
    void __fastcall RadioButton_P1P2Click(TObject * Sender);
    void __fastcall Button_MeaRunClick(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall Button_DebugClick(TObject * Sender);
    void __fastcall FormShow(TObject * Sender);
    void __fastcall RadioButton_GammaCurveClick(TObject * Sender);
    void __fastcall TOutputFileFrame1Button_BrowseDirClick(TObject * Sender);
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
    void __fastcall RadioButton_GammaClick(TObject * Sender);
    void __fastcall ComboBox_GammaChange(TObject * Sender);
    void __fastcall CheckBox_ExpandClick(TObject * Sender);
    void __fastcall Button_ResetClick(TObject * Sender);
    void __fastcall CheckBox_NewMethodClick(TObject * Sender);
    void __fastcall RadioButton_MaxYNativeAdvClick(TObject * Sender);
    void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
    void __fastcall Button_RunClick(TObject * Sender);
    void __fastcall CheckBox_BTargetIntensityClick(TObject * Sender);
    void __fastcall RadioButton_GammaValueClick(TObject * Sender);
    void __fastcall CheckBox_BMax2Click(TObject * Sender);
    void __fastcall CheckBox_AvoidHookNBClick(TObject * Sender);
  private:			// User declarations
    void setMeasureInfo();
    int serialid;
     bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth;
    RGBGamma_ptr rgbGamma;
     bptr < cms::lcd::calibrate::MeasureCondition > getMeasureCondition();
    bool run;
    int getMaxZDGCode();
     bptr < cms::measure::MaxMatrixIntensityAnayzer > nativeWhiteAnalyzer;
  public:			// User declarations
     __fastcall TCCTLUTForm(TComponent * Owner);
    void setBitDepthProcessor(bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth);
};
//---------------------------------------------------------------------------
extern PACKAGE TCCTLUTForm *CCTLUTForm;
//---------------------------------------------------------------------------
#endif

