//---------------------------------------------------------------------------

#ifndef TChangeLogFormH
#define TChangeLogFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TChangeLogForm:public TForm
{
  __published:                  // IDE-managed Components
  TMemo * Memo1;
  void __fastcall FormResize(TObject * Sender);
private:                       // User declarations
public:                        // User declarations
   __fastcall TChangeLogForm(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TChangeLogForm *ChangeLogForm;
//---------------------------------------------------------------------------
#endif

