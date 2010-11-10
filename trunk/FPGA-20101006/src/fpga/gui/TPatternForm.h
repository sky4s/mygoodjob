//---------------------------------------------------------------------------

#ifndef TPatternFormH
#define TPatternFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <cms/util/util.h>
//---------------------------------------------------------------------------
class PatternCallbackIF {
  public:
/*
  show在節點上 :  15<7.5<0, 15<0
  不show在節點上: 15<7.5<x, 15<x
*/
    virtual void show15DegBasePattern() = 0;
    virtual void show7p5DegBasePattern() = 0;
    virtual void showSinglePattern() = 0;
    virtual void adjustValue(bool minus) = 0;
};

Enumeration(PatternMode) Single, Hue15, Hue7p5, EnumerationEnd();


class TPatternForm:public TForm {
    __published:		// IDE-managed Components
    TButton * Button_Show7p5Deg;
    TButton *Button_Show15Deg;
    TButton *Button_ShowSingleDeg;
    void __fastcall FormPaint(TObject * Sender);
    void __fastcall FormResize(TObject * Sender);
    void __fastcall Button_Show7p5DegClick(TObject * Sender);
    void __fastcall Button_Show15DegClick(TObject * Sender);
    void __fastcall Button_ShowSingleDegClick(TObject * Sender);
    void __fastcall FormMouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall FormMouseWheelDown(TObject * Sender,
				       TShiftState Shift, TPoint & MousePos, bool & Handled);
    void __fastcall FormMouseWheelUp(TObject * Sender,
				     TShiftState Shift, TPoint & MousePos, bool & Handled);
  private:			// User declarations
    double gapPercent;
    int patchCols;
    HSV_vector_ptr hsvVector;
    int_vector_ptr blackIndexVector;
    int_vector_ptr whiteIndexVector;
    PatternCallbackIF *callback;
    PatternMode mode;
    bptr < cms::util::DoubleBufferedCanvas > doubleBufferedCanvas;
    void setTPatternForm(TPatternForm * copy);
  public:			// User declarations
    __fastcall TPatternForm(TComponent * Owner);
    void setPatternCallbackIF(PatternCallbackIF * callback);
    void setGapPercent(double gapPercent);
    void setHSVVector(HSV_vector_ptr hsvVector);
    void setBlackBoxIndexVector(int_vector_ptr indexVector);
    void setWhiteBoxIndexVector(int_vector_ptr indexVector);
    void setPatchCols(int cols);
};

//---------------------------------------------------------------------------
extern PACKAGE TPatternForm *PatternForm;
extern PACKAGE TPatternForm *PatternForm2;
//---------------------------------------------------------------------------
#endif

