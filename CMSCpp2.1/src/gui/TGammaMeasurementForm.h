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
    TGroupBox *GroupBox6;
    TGroupBox *GroupBox8;
    TGroupBox *GroupBox9;
    TCheckBox *CheckBox5;
    TCheckBox *CheckBox6;
    TRadioButton *RadioButton3;
    TRadioButton *RadioButton4;
    TLabel *Label4;
    TOutputFileFrame *TOutputFileFrame1;
    TGroupBox *GroupBox3;
    TCheckBox *CheckBox_W;
    TCheckBox *CheckBox_R;
    TCheckBox *CheckBox_G;
    TCheckBox *CheckBox_B;
    TButton *Button_Measure;
    TGroupBox *Table;
    TRadioButton *RadioButton1;
    TRadioButton *RadioButton2;
    TButton *Button2;
    void __fastcall Button_MeasureClick(TObject * Sender);
    void __fastcall FormShow(TObject * Sender);
  private:			// User declarations
     bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth;
    void setMeasureInfo();
    void pcMeasure(bool_vector_ptr rgbw, int start, int end, int step,
		   const std::string & filename);
    void tconMeasure(bool_vector_ptr rgbw, int start, int end, int step,
		     const std::string & filename);
     bptr < cms::measure::MeterMeasurement > mm;
     bptr < cms::lcd::calibrate::ComponentFetcher > fetcher;
    //bptr < cms::measure::IntensityAnalyzerIF > analyzer;
  public:			// User declarations
     __fastcall TGammaMeasurementForm(TComponent * Owner);
    void setBitDepthProcessor(bptr <
			      cms::lcd::calibrate::BitDepthProcessor >
			      bitDepth);
};
//---------------------------------------------------------------------------
extern PACKAGE TGammaMeasurementForm *GammaMeasurementForm;
//---------------------------------------------------------------------------
#endif

