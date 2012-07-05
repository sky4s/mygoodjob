//---------------------------------------------------------------------------

#ifndef TGammaAdjustmentFormH
#define TGammaAdjustmentFormH
//---------------------------------------------------------------------------
//C系統文件

//C++系統文件

//其他庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//本項目內頭文件
#include "TOutputFileFrame.h"
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TGammaAdjustmentForm:public TForm {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox2;
    TComboBox *ComboBox_LevelStep;
    TLabel *Label9;
    TGroupBox *GroupBox3;
    TGroupBox *GroupBox4;
    TGroupBox *GroupBox5;
    TLabel *Label1;
    TButton *Button_GrayGamma;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TButton *Button_RGBGamma;
    TButton *Button_LoadGamma;
    TGroupBox *GroupBox1;
    TCheckBox *CheckBox_AvoidNoise;
    TCheckBox *CheckBox_KeepMax;
    TOutputFileFrame *TOutputFileFrame1;
    TOpenDialog *OpenDialog1;
    TCheckBox *CheckBox_LoadGamma;
    TComboBox *ComboBox_GrayGamma;
    TComboBox *ComboBox_RGamma;
    TComboBox *ComboBox_GGamma;
    TComboBox *ComboBox_BGamma;
    TProgressBar *ProgressBar1;
    TCheckBox *CheckBox_FineCalibrate;
    void __fastcall FormShow(TObject * Sender);
    void __fastcall Button_LoadGammaClick(TObject * Sender);
    void __fastcall CheckBox_LoadGammaClick(TObject * Sender);
    void __fastcall Button_GrayGammaClick(TObject * Sender);
    void __fastcall Button_RGBGammaClick(TObject * Sender);
    void __fastcall TOutputFileFrame1Button_BrowseDirClick(TObject * Sender);
    void __fastcall FormMouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
  private:			// User declarations
     bptr < cms::lcd::BitDepthProcessor > bitDepth;
    RGBGamma_ptr rgbGamma;
     bptr < cms::lcd::calibrate::LCDCalibrator > calibrator;
    void gammaAdjust(bool rgbGammaAdjust);
     bptr < cms::lcd::calibrate::MeasureCondition > getMeasureCondition();
    bool run;
  public:			// User declarations
     __fastcall TGammaAdjustmentForm(TComponent * Owner);
    void setBitDepthProcessor(bptr < cms::lcd::BitDepthProcessor > bitDepth);
};
//---------------------------------------------------------------------------
extern PACKAGE TGammaAdjustmentForm *GammaAdjustmentForm;
//---------------------------------------------------------------------------
#endif

