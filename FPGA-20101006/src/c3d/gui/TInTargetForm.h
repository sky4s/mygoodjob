//---------------------------------------------------------------------------

#ifndef TInTargetFormH
#define TInTargetFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TInTargetForm:public TForm {
    __published:		// IDE-managed Components
    TOpenDialog * OpenDialog1;
    TSaveDialog *SaveDialog1;
    TScrollBox *ScrollBox1;
    TImage *img_in_target;
  private:			// User declarations
  public:			// User declarations
     __fastcall TInTargetForm(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TInTargetForm *InTargetForm;
//---------------------------------------------------------------------------
#endif

