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
//#include "T3DMeasureWindow.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class KeyPressListener {
  public:
    virtual void keyPress(TObject * Sender, char &Key) = 0;
};
//---------------------------------------------------------------------------
class TThreeDMeasurementForm:public TForm, KeyPressListener {
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
    TEdit *Edit2;
    TEdit *Edit3;
    TEdit *Edit4;
    TEdit *Edit14;
    TLabel *Label8;
    TCheckBox *CheckBox_Extend;
    TTabSheet *TabSheet3;
    TGroupBox *GroupBox2;
    TLabel *Label9;
    TLabel *Label10;
    TEdit *Edit_DStart;
    TEdit *Edit_DTarget;
    TButton *Button_DynamicMeasure;
    TTabSheet *TabSheet4;
    TButton *Button1;
    TComboBox *ComboBox_MeasureMode2;
    TCheckBox *CheckBox_AutoReleaseCA210;
    TImage *Image1;
    TLabel *Label11;
    TCheckBox *CheckBox_StableTest;
    TComboBox *ComboBox_MeasureMode;
    void __fastcall Button_MeasureClick(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall Button_SpotMeasureClick(TObject * Sender);
    void __fastcall CheckBox_StableTestClick(TObject * Sender);
    void __fastcall CheckBox_ExtendClick(TObject * Sender);
    void __fastcall Button_DynamicMeasureClick(TObject * Sender);
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
    void __fastcall Button1Click(TObject * Sender);
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
    bool dynamicMode;
    double measure(int start, int target);
    bool whiteFont;
    int startAdj, targetAdj, start, target;
    void dynamicMeasure(int start, int target, int adjustStart,
			int adjustTarget);
    void updateAdjust();
  public:			// User declarations
    static double whiteXTalk(double BB, double BW, double WW);
    static double blackXTalk(double BB, double WB, double WW);
    __fastcall TThreeDMeasurementForm(TComponent * Owner);
    bool stop;
    void keyPress(TObject * Sender, char &Key);
};
//---------------------------------------------------------------------------
extern PACKAGE TThreeDMeasurementForm *ThreeDMeasurementForm;
//---------------------------------------------------------------------------
#endif

