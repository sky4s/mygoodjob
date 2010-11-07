//---------------------------------------------------------------------------

#ifndef TPatternFormH
#define TPatternFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class PatternCallbackIF
{
public:
/*
  show在節點上 :  15<7.5<0, 15<0
  不show在節點上: 15<7.5<x, 15<x
*/
  virtual void show15DegBasePattern() = 0;
  virtual void show7p5DegBasePattern() = 0;
  virtual void showSinglePattern() = 0;
};

class TPatternForm:public TForm
{
  __published:                  // IDE-managed Components
  TButton * Button_Show7p5Deg;
  TButton *Button_Show15Deg;
  TButton *Button_ShowSingleDeg;
  void __fastcall FormPaint(TObject * Sender);
  void __fastcall FormResize(TObject * Sender);
  void __fastcall Button_Show7p5DegClick(TObject * Sender);
  void __fastcall Button_Show15DegClick(TObject * Sender);
  void __fastcall Button_ShowSingleDegClick(TObject * Sender);
private:                       // User declarations
  double gapPercent;
  int patchCols;
  HSV_vector_ptr hsvVector;
  int_vector_ptr blackIndexVector;
  PatternCallbackIF *callback;
public:                        // User declarations
   __fastcall TPatternForm(TComponent * Owner);
  void setPatternCallbackIF(PatternCallbackIF * callback);
  void setGapPercent(double gapPercent);
  void setHSVVector(HSV_vector_ptr hsvVector);
  void setBlackBoxIndexVector(int_vector_ptr indexVector);
  void setPatchCols(int cols);
};

//---------------------------------------------------------------------------
extern PACKAGE TPatternForm *PatternForm;
//---------------------------------------------------------------------------
#endif

