//---------------------------------------------------------------------------

#ifndef TMeasureWindowH
#define TMeasureWindowH
//---------------------------------------------------------------------------
//C系統文件

//C++系統文件

//其他庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
//本項目內頭文件
#include <java/lang.h>
//---------------------------------------------------------------------------

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

