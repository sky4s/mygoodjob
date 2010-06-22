//---------------------------------------------------------------------------

#ifndef T3DMeasurementFormH
#define T3DMeasurementFormH
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
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------
class TThreeDMeasurementForm:public TForm {
    __published:		// IDE-managed Components
    TPageControl * PageControl1;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TButton *Button_Measure;
    TOutputFileFrame *OutputFileFrame1;
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TEdit *Edit_IdleTime;
    TEdit *Edit_AveTimes;
    TCheckBox *CheckBox_LeftRightChange;
    TGroupBox *GroupBox3;
    TCheckBox *CheckBox_W;
    TCheckBox *CheckBox_R;
    TCheckBox *CheckBox_G;
    TCheckBox *CheckBox_B;
    TButton *Button_SpotMeasure;
    TGroupBox *GroupBox4;
    TLabel *Label5;
    TEdit *Edit_Start;
    TEdit *Edit_Target;
    TLabel *Label6;
    TGroupBox *GroupBox5;
    TEdit *Edit5;
    TEdit *Edit6;
    TEdit *Edit7;
    TEdit *Edit8;
    TEdit *Edit9;
    TEdit *Edit10;
    TEdit *Edit11;
    TEdit *Edit12;
    TEdit *Edit13;
    TEdit *Edit1;
    TLabel *Label7;
    TCheckBox *CheckBox_StableTest;
    TComboBox *ComboBox_MeasureMode;
    TEdit *Edit2;
    TEdit *Edit3;
    TEdit *Edit4;
    TEdit *Edit14;
    TLabel *Label8;
    TCheckBox *CheckBox_Extend;
    void __fastcall Button_MeasureClick(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall Button_SpotMeasureClick(TObject * Sender);
    void __fastcall CheckBox_StableTestClick(TObject * Sender);
    void __fastcall CheckBox_ExtendClick(TObject * Sender);
    //void __fastcall CheckBox_ExtendClick(TObject *Sender);

  private:			// User declarations
     bptr < cms::measure::meter::CA210 > ca210;
    double patternMeasure(RGB_ptr left, RGB_ptr right, int idleTime,
			  int aveTimes, bool leftrightChange);
    double_vector_ptr patternMeasure0(RGB_ptr left, RGB_ptr right,
				      int idleTime, int aveTimes,
				      bool leftrightChange);
    double getMeanLuminance(double_vector_ptr result);
    double2D_ptr ODMeasure(const Dep::Channel & ch, int idleTime,
			   int aveTimes, bool leftrightChange,
			   bool stableTest);
    void storeResult(const string & sheetName, double2D_ptr result,
		     bptr < cms::colorformat::ExcelAccessBase > excel);
    string_vector_ptr fieldNames;
    const bool linkCA210;
    double2D_ptr crosstalk(double2D_ptr meaureResult);

  public:			// User declarations
    static double whiteXTalk(double BB, double BW, double WW);
    static double blackXTalk(double BB, double WB, double WW);
    __fastcall TThreeDMeasurementForm(TComponent * Owner);
    bool stop;
};
//---------------------------------------------------------------------------
extern PACKAGE TThreeDMeasurementForm *ThreeDMeasurementForm;
//---------------------------------------------------------------------------
#endif

