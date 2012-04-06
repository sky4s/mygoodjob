//---------------------------------------------------------------------------

#ifndef TGammaMeasurementFormH
#define TGammaMeasurementFormH
//---------------------------------------------------------------------------
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "TOutputFileFrame.h"
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
//�����ؤ��Y���
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
    TGroupBox *GroupBox3;
    TCheckBox *CheckBox_W;
    TCheckBox *CheckBox_R;
    TCheckBox *CheckBox_G;
    TCheckBox *CheckBox_B;
    TButton *Button_Measure;
    TGroupBox *Table;
    TRadioButton *RadioButton_10Bit;
    TRadioButton *RadioButton_12Bit;
    TButton *Button2;
    TOpenDialog *OpenDialog1;
    TCheckBox *CheckBox_Loaded;
    TCheckBox *CheckBox_FlickerFMA;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TEdit *Edit_StartLevelT;
    TEdit *Edit_EndLevelT;
    TEdit *Edit_Count;
    TProgressBar *ProgressBar1;
    void __fastcall Button_MeasureClick(TObject * Sender);
    void __fastcall FormShow(TObject * Sender);
    void __fastcall TOutputFileFrame1Button_BrowseDirClick(TObject * Sender);
    void __fastcall Button2Click(TObject * Sender);
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
    void __fastcall CheckBox_LoadedClick(TObject * Sender);
  private:			// User declarations
     bptr < cms::lcd::BitDepthProcessor > bitDepth;
    void setMeasureInfo();
    bool measure(bool_vector_ptr rgbw,
		 bptr < cms::lcd::calibrate::MeasureCondition >
		 measureCondition, bool flicker, const std::string & filename);
    void tconMeasure(bool_vector_ptr rgbw, int start, int end, int step,
		     const std::string & filename);
     bptr < cms::measure::MeterMeasurement > mm;
     bptr < cms::lcd::calibrate::ComponentFetcher > fetcher;
    //bptr < cms::measure::IntensityAnalyzerIF > analyzer;
    RGB_vector_ptr dgcodeTable;
     bptr < cms::lcd::calibrate::MeasureCondition > getMeasureCondition();
    bool run;
     bptr < cms::measure::MeasureTool > mt;
    bool checkMeasureable();
  public:			// User declarations
     __fastcall TGammaMeasurementForm(TComponent * Owner);
    void setBitDepthProcessor(bptr < cms::lcd::BitDepthProcessor > bitDepth);
};
//---------------------------------------------------------------------------
extern PACKAGE TGammaMeasurementForm *GammaMeasurementForm;
//---------------------------------------------------------------------------
#endif

