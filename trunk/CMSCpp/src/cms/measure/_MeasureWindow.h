//---------------------------------------------------------------------------

#ifndef _MeasureWindowH
#define _MeasureWindowH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TMeasureWindow : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
        __fastcall TMeasureWindow(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMeasureWindow *MeasureWindow;
//---------------------------------------------------------------------------
#endif
