//---------------------------------------------------------------------------

#ifndef TPatternFormH
#define TPatternFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TPatternForm:public TForm
{
  __published:                  // IDE-managed Components
  void __fastcall FormPaint(TObject * Sender);
  void __fastcall FormResize(TObject * Sender);
private:                       // User declarations
  //int hue;
  //int_array saturationArray;
  //int_array valueArray;
  //int patchCount;
  //bool patchUpdate;
  double gapPercent;
  int patchCols;
  HSV_vector_ptr hsvVector;
public:                        // User declarations
   __fastcall TPatternForm(TComponent * Owner);
  //void setHue(int hue);
  //void setSaturationValue(int n, ...);
  void setGapPercent(double gapPercent);
  void setHSVVector(HSV_vector_ptr hsvVector);
  void setPatchCols(int cols);
};
//---------------------------------------------------------------------------
extern PACKAGE TPatternForm *PatternForm;
//---------------------------------------------------------------------------
#endif

