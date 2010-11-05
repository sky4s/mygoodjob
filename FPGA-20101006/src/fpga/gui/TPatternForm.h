//---------------------------------------------------------------------------

#ifndef TPatternFormH
#define TPatternFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TPatternForm:public TForm {
    __published:		// IDE-managed Components
    void __fastcall FormPaint(TObject * Sender);
    void __fastcall FormResize(TObject * Sender);
  private:			// User declarations
    //int hue;
    //int_array saturationArray;
    //int_array valueArray;
    int patchCount;
    //bool patchUpdate;
  public:			// User declarations
     __fastcall TPatternForm(TComponent * Owner);
    //void setHue(int hue);
    //void setSaturationValue(int n, ...);
};
//---------------------------------------------------------------------------
extern PACKAGE TPatternForm *PatternForm;
//---------------------------------------------------------------------------
#endif

