//---------------------------------------------------------------------------

#ifndef T3DMeasureWindowH
#define T3DMeasureWindowH
//---------------------------------------------------------------------------
//C系統文件

//C++系統文件

//其他庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//本項目內頭文件

//---------------------------------------------------------------------------
class KeyPressListener;
class TThreeDMeasureWindow:public TForm {
    __published:		// IDE-managed Components
    TPanel * Panel1;
    TPanel *Panel2;
    TButton *Button1;
    TLabel *Label_StartAdj;
    TLabel *Label_TargetAdj;
    TLabel *Label_StartBase;
    TLabel *Label_TargetBase;
        TLabel *Label_StartTarget;
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
    void __fastcall Button1Click(TObject * Sender);
    void __fastcall FormPaint(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
  private:			// User declarations
     KeyPressListener * keyPressListener;
    char test;
  public:			// User declarations
     __fastcall TThreeDMeasureWindow(TComponent * Owner);
    void setLeftRGB(int r, int g, int b);
    void setRightRGB(int r, int g, int b);
    void setLeftRGB(RGB_ptr rgb);
    void setRightRGB(RGB_ptr rgb);
    void setKeyPressListener(KeyPressListener * listener);
};
//---------------------------------------------------------------------------
extern PACKAGE TThreeDMeasureWindow *ThreeDMeasureWindow;
//---------------------------------------------------------------------------
#endif

