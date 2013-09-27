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
#include <ComCtrls.hpp>
#include <cms/lcd/calibrate/lcdcalibrator.h>
#include "TGammaMeasurementForm.h"
//---------------------------------------------------------------------------
class TCCTLUTForm:public TForm, cms::lcd::calibrate::FeedbackListener {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox_GrayLevel;
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
    TGroupBox *GroupBox4;
    TCheckBox *CheckBox_BGain;
    TEdit *Edit_BGain;
    TCheckBox *CheckBox_BMax;
    TGroupBox *GroupBox5;
    TCheckBox *CheckBox_AvoidNoise;
    TOpenDialog *OpenDialog1;
    TButton *Button_MeaRun;
    TButton *Button_Debug;
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
    TButton *Button_Run;
    TGroupBox *GroupBox_KeepMaxLuminance;
    TRadioButton *RadioButton_MaxYNative;
    TRadioButton *RadioButton_MaxYNativeAdv;
    TLabel *Label20;
    TEdit *Edit_MaxYAdvOver;
    TRadioButton *RadioButton_GammaValue;
    TCheckBox *CheckBox_MultiGen;
    TEdit *Edit_MultiGenTimes;
    TCheckBox *CheckBox_BTargetIntensity;
    TEdit *Edit_BTargetIntensity;
    TRadioButton *RadioButton_OriginalGamma;
    TCheckBox *CheckBox_BMax2;
    TLabel *Label18;
    TEdit *Edit_BMax2Begin;
    TEdit *Edit_BMax2Gamma;
    TLabel *Label19;
    TCheckBox *CheckBox_MemoryMeasure;
    TCheckBox *CheckBox_MaxYAdvAuto;
    TProgressBar *ProgressBar1;
    TRadioButton *RadioButton_3Gamma;
    TComboBox *ComboBox_DimGamma;
    TComboBox *ComboBox_BrightGamma;
    TLabel *Label16;
    TLabel *Label_BrightZone;
    TEdit *Edit_DimGammaEnd;
    TRadioGroup *RadioGroup_NormalCase;
    TCheckBox *CheckBox_AbsoluteGamma;
    TCheckBox *CheckBox_RTargetIntensity;
    TEdit *Edit_RTargetIntensity;
    TRadioButton *RadioButton_MaxYTargetWhite;
    TEdit *Edit_AbsGammaStart;
    TLabel *Label22;
    TLabel *Label23;
    TComboBox *ComboBox_AbsGammaStartAboveGamma;
    TLabel *Label24;
    TLabel *Label25;
    TStatusBar *StatusBar1;
    TLabel *Label26;
    TLabel *Label27;
    TLabel *Label28;
    TLabel *Label_MiddleZone;
    TEdit *Edit_MiddleGammaEnd;
    TGroupBox *GroupBox_DeHook;
    TRadioButton *RadioButton_DeHookNone;
    TRadioButton *RadioButton_DeHookKeepCCT;
    TCheckBox *CheckBox_KeepMaxYInMultiGen;
    TRadioButton *RadioButton_NewDeHook;
    TRadioGroup *RadioGroup_NewDeHookPriority;
    TCheckBox *CheckBox_AlterGammaCurveAtDeHook2;
    TGroupBox *GroupBox3;
    TLabel *Label17;
    TLabel *Label14;
    TRadioButton *RadioButton_NoneLowLevelCorrect;
    TRadioButton *RadioButton_DefinedDim;
    TEdit *Edit_DefinedDimUnder;
    TEdit *Edit_DimFixThreshold;
    TCheckBox *CheckBox_Feedback;
    TComboBox *ComboBox_DefinedDimGamma;
    TCheckBox *CheckBox_LuminanceCalInMultiGen;
    TCheckBox *CheckBox_YOnly;
    TGroupBox *GroupBox_DeIntensityError;
    TRadioButton *RadioButton_None;
    TRadioButton *RadioButton_ForceAssignWhite;
    TRadioButton *RadioButton_IntensityShift;
    TGroupBox *GroupBox_Execute;
    TCheckBox *CheckBox_FixInverseCIEZ;
    TRadioGroup *RadioGroup_KeepLBy;
    TCheckBox *CheckBox_MeasureRGBFromDebugFile;
    TCheckBox *CheckBox_DimRBFix;
    TEdit *Edit_DimRBFixUnder;
    TCheckBox *CheckBox_RBFixAuto;
    TRadioButton *RadioButton_WhiteShift;
        TCheckBox *CheckBox_DimThreePart;
    void __fastcall Button_MeaRunClick(TObject * Sender);
    void __fastcall Button_DebugClick(TObject * Sender);
    void __fastcall FormShow(TObject * Sender);
    void __fastcall RadioButton_GammaCurveClick(TObject * Sender);
    void __fastcall TOutputFileFrame1Button_BrowseDirClick(TObject * Sender);
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
    void __fastcall RadioButton_GammaClick(TObject * Sender);
    void __fastcall ComboBox_GammaChange(TObject * Sender);
    void __fastcall CheckBox_ExpandClick(TObject * Sender);
    void __fastcall Button_ResetClick(TObject * Sender);
    void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
    void __fastcall Button_RunClick(TObject * Sender);
    void __fastcall CheckBox_BTargetIntensityClick(TObject * Sender);
    void __fastcall RadioButton_GammaValueClick(TObject * Sender);
    void __fastcall CheckBox_BMax2Click(TObject * Sender);
    void __fastcall Edit_MaxYAdvOverChange(TObject * Sender);
    void __fastcall CheckBox_MaxYAdvAutoClick(TObject * Sender);
    void __fastcall Edit_DimGammaEndChange(TObject * Sender);
    void __fastcall RadioGroup_NormalCaseClick(TObject * Sender);
    void __fastcall CheckBox_RTargetIntensityClick(TObject * Sender);
    void __fastcall FormMouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall CheckBox_AbsoluteGammaClick(TObject * Sender);
    void __fastcall Edit_MiddleGammaEndChange(TObject * Sender);
    void __fastcall RadioButton_DeHookOrgClick(TObject * Sender);
    void __fastcall RadioButton_DeHookEvoClick(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall RadioButton_MaxYNativeClick(TObject * Sender);
    void __fastcall RadioButton_3GammaClick(TObject * Sender);
    void __fastcall RadioButton_OriginalGammaClick(TObject * Sender);
    void __fastcall RadioButton_NewDeHookClick(TObject * Sender);
    void __fastcall RadioButton_DeHookKeepCCTClick(TObject * Sender);
    void __fastcall RadioButton_DeHookNoneClick(TObject * Sender);
    void __fastcall Button1Click(TObject * Sender);
    void __fastcall CheckBox_MultiGenClick(TObject * Sender);
    void __fastcall CheckBox_DimRBFixClick(TObject * Sender);
    void __fastcall CheckBox_RBFixAutoClick(TObject * Sender);
        void __fastcall CheckBox_DimThreePartClick(TObject *Sender);
  private:			// User declarations
    void setMeasureInfo();
    int serialid;
    bptr < cms::lcd::BitDepthProcessor > bitDepth;
    RGBGamma_ptr rgbGamma;
    bptr < cms::lcd::calibrate::MeasureCondition > getMeasureCondition();

    bptr < cms::measure::MaxMatrixIntensityAnalyzer > secondWhiteAnalyzer;
    const bool debugMode;
    TGammaMeasurementForm *gammaMeasureForm;
    RGB_vector_ptr gammaTableFromDebugFile;
  public:			// User declarations
    __fastcall TCCTLUTForm(TComponent * Owner);
    void setBitDepthProcessor(bptr < cms::lcd::BitDepthProcessor > bitDepth);
    void doFeedback(int defectCount, int feedbackCount);
    void doFeedback(string msg);
    bool run;
};
//---------------------------------------------------------------------------
extern PACKAGE TCCTLUTForm *CCTLUTForm;
//---------------------------------------------------------------------------
#endif

