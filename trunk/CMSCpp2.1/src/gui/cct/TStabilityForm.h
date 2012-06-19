//---------------------------------------------------------------------------

#ifndef TStabilityFormH
#define TStabilityFormH
//---------------------------------------------------------------------------

//C系統文件

//C++系統文件

//其他庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//本項目內頭文件
#include <java/lang.h>
#include <cms/cms.h>

//---------------------------------------------------------------------------
class TStabilityForm:public TForm {
    __published:		// IDE-managed Components
    TButton * Button1;
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TEdit *Edit_Start;
    TLabel *Label2;
    TEdit *Edit_Step;
    TLabel *Label3;
    TLabel *Label4;
    TEdit *Edit_Count;
    TEdit *Edit_WaitTime;
    TOpenDialog *OpenDialog1;
    TButton *Button3;
    TButton *Button_ContinueMeasure;
    TLabel *Label5;
    TEdit *Edit_Blank;
    TGroupBox *GroupBox2;
    TButton *Button2;
    TButton *Button4;
    TCheckBox *CheckBox_Flicker;
        TCheckBox *CheckBox_JEITA;
    void __fastcall Button1Click(TObject * Sender);
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
    void __fastcall Button3Click(TObject * Sender);
    void __fastcall Button_ContinueMeasureClick(TObject * Sender);
    void __fastcall Button4Click(TObject * Sender);
  private:			// User declarations
     bptr < cms::measure::MeterMeasurement > mm;
    void storeMeasurePatchVector();
    bool run;
    RGB_vector_ptr dgcodeTable;
  public:			// User declarations
     __fastcall TStabilityForm(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TStabilityForm *StabilityForm;
//---------------------------------------------------------------------------
#endif

