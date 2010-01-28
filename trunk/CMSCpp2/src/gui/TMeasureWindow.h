//---------------------------------------------------------------------------

#ifndef TMeasureWindowH
#define TMeasureWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>

#include <java/lang.h>
//---------------------------------------------------------------------------
namespace cms {
    namespace colorspace {
	namespace depend {
	    class RGBColor;
	};
    };
};

class TMeasureWindow:public TForm {
    __published:		// IDE-managed Components
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
  private:			// User declarations
  public:			// User declarations
     __fastcall TMeasureWindow(TComponent * Owner);
    void setRGB(int r, int g, int b);
    void setRGB(bptr < Dep::RGBColor > rgb);
};
//---------------------------------------------------------------------------
extern PACKAGE TMeasureWindow *MeasureWindow;
//---------------------------------------------------------------------------
#endif

