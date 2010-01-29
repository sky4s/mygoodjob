//---------------------------------------------------------------------------

#ifndef TPatternFormH
#define TPatternFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ToolWin.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TPatternForm:public TForm {
    __published:		// IDE-managed Components
    TToolBar * ToolBar1;
    TButton *Button_Exit;
    TButton *Button1;
    TEdit *Edit_Start;
    TEdit *Edit_End;
    TEdit *Edit_Code;
    TButton *Button2;
    TButton *Button3;
    TButton *Button4;
    TButton *Button5;
    TButton *Button6;
    TButton *Button7;
    TButton *Button8;
    TButton *Button12;
    TButton *Button13;
    TButton *Button14;
    TButton *Button15;
    TButton *Button16;
    TButton *Button17;
    TSpeedButton *SpeedButton1;
    TSpeedButton *SpeedButton2;
    TSpeedButton *SpeedButton3;
    TSplitter *Splitter2;
    TSplitter *Splitter3;
    TSplitter *Splitter4;
    TSplitter *Splitter5;
    TSplitter *Splitter6;
    TSplitter *Splitter7;
    TSplitter *Splitter8;
    void __fastcall Button_ExitClick(TObject * Sender);
    void __fastcall FormDblClick(TObject * Sender);
    void __fastcall Button1Click(TObject * Sender);
  private:			// User declarations
  public:			// User declarations
     __fastcall TPatternForm(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TPatternForm *PatternForm;
//---------------------------------------------------------------------------
#endif

