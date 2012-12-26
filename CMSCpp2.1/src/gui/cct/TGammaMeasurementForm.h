//---------------------------------------------------------------------------

#ifndef TGammaMeasurementFormH
#define TGammaMeasurementFormH
//---------------------------------------------------------------------------
//C系統文件

//C++系統文件

//其他庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "TOutputFileFrame.h"
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
//本項目內頭文件
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
    TLabel *Copyright;
    TPanel *Panel2;
    TGroupBox *GroupBox5;
    TOutputFileFrame *TOutputFileFrame1;
    TGroupBox *GroupBox_Color;
    TCheckBox *CheckBox_W;
    TCheckBox *CheckBox_R;
    TCheckBox *CheckBox_G;
    TCheckBox *CheckBox_B;
    TButton *Button_Measure;
    TGroupBox *GroupBox_GrayScale;
    TRadioButton *RadioButton_GrayScale10Bit;
    TRadioButton *RadioButton_GrayScale12Bit;
    TButton *Button_LoadDGTable;
    TOpenDialog *OpenDialog1;
    TCheckBox *CheckBox_DGLoaded;
    TCheckBox *CheckBox_FlickerFMA;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TEdit *Edit_StartLevelT;
    TEdit *Edit_EndLevelT;
    TEdit *Edit_GrayScaleCount;
    TProgressBar *ProgressBar1;
    TPanel *Panel3;
    TGroupBox *GroupBox4;
    TEdit *Edit_BackgroundR;
    TEdit *Edit_BackgroundG;
    TEdit *Edit_BackgroundB;
    TGroupBox *GroupBox_CustomPattern;
    TRadioButton *RadioButton_TCONInputGrayScale;
    TRadioButton *RadioButton_TCONInputCustomPattern;
    TButton *Button_LoadPattern;
    TCheckBox *CheckBox_CustomLoaded;
    TRadioButton *RadioButton_Custom10Bit;
    TRadioButton *RadioButton_Custom12Bit;
    TRadioButton *RadioButton_Custom8Bit;
    TLabel *Label7;
    TEdit *Edit_CustormPatternCount;
    TCheckBox *CheckBox_10BitInMeasurement;
    TLabel *Label8;
    void __fastcall Button_MeasureClick(TObject * Sender);
    void __fastcall FormShow(TObject * Sender);
    void __fastcall TOutputFileFrame1Button_BrowseDirClick(TObject * Sender);
    void __fastcall Button_LoadDGTableClick(TObject * Sender);
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
    void __fastcall CheckBox_DGLoadedClick(TObject * Sender);
    void __fastcall FormMouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall RadioButton_TCONInputGrayScaleClick(TObject * Sender);
    void __fastcall Button_LoadPatternClick(TObject * Sender);
    void __fastcall CheckBox_CustomLoadedClick(TObject * Sender);
    void __fastcall CheckBox_10BitInMeasurementClick(TObject * Sender);
  private:			// User declarations
     bptr < cms::lcd::BitDepthProcessor > bitDepth;
     bptr < cms::lcd::BitDepthProcessor > dgLutBitDepth;
    void setMeasureInfo();

    void tconMeasure(bool_vector_ptr rgbw, int start, int end, int step,
		     const std::string & filename);
     bptr < cms::measure::MeterMeasurement > mm;
     bptr < cms::lcd::calibrate::ComponentFetcher > fetcher;
    //bptr < cms::measure::IntensityAnalyzerIF > analyzer;
    RGB_vector_ptr dgcodeTable;
    RGB_vector_ptr grayScaleTable;
    RGB_vector_ptr customTable;
     bptr < cms::colorformat::DGLutProperty > property;
     bptr < cms::lcd::calibrate::MeasureCondition > getMeasureCondition();
    bool run;
     bptr < cms::measure::MeasureTool > mt;
    bool checkMeasureable();
    const bool debugMode;
  public:			// User declarations
     __fastcall TGammaMeasurementForm(TComponent * Owner);
    void setBitDepthProcessor(bptr < cms::lcd::BitDepthProcessor > bitDepth);
    bool measure(bool_vector_ptr rgbw, int_vector_ptr background,
		 bptr < cms::lcd::calibrate::MeasureCondition >
		 measureCondition, bool flicker, const std::string & filename);
    void stopMeasure(TObject * Sender);
};
//---------------------------------------------------------------------------
extern PACKAGE TGammaMeasurementForm *GammaMeasurementForm;
//---------------------------------------------------------------------------
#endif

