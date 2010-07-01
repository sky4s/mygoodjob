//---------------------------------------------------------------------------

#ifndef TPatternMeasureFormH
#define TPatternMeasureFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TOutputFileFrame.h"
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
//---------------------------------------------------------------------------
class TPatternMeasureForm:public TForm {
    __published:		// IDE-managed Components
    TButton * Button_Measure;
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TEdit *Edit_Interval;
    TOutputFileFrame *TOutputFileFrame1;
    TImage *Image1;
    TLabel *Label6;
    TComboBox *ComboBox_FileFormat;
    void __fastcall Button_MeasureClick(TObject * Sender);
  private:			// User declarations
     bptr < cms::measure::meter::Meter > meter;
    const bool linkCA210;
  public:			// User declarations
     __fastcall TPatternMeasureForm(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPatternMeasureForm *PatternMeasureForm;
//---------------------------------------------------------------------------
#endif

