//---------------------------------------------------------------------------

#ifndef TMeasureWindowH
#define TMeasureWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
//---------------------------------------------------------------------------
namespace cms {
    namespace colorspace {
	class RGBColor;
    };
};

class TMeasureWindow:public TForm {
    __published:		// IDE-managed Components
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
    void __fastcall FormCreate(TObject * Sender);
  private:			// User declarations
  public:			// User declarations
     __fastcall TMeasureWindow(TComponent * Owner);
    void setRGB(int r, int g, int b);
    void setRGB(cms::colorspace::RGBColor & rgb);
};
//---------------------------------------------------------------------------
extern PACKAGE TMeasureWindow *MeasureWindow;
//---------------------------------------------------------------------------
#endif

