//---------------------------------------------------------------------------

#ifndef Table_Step_FormH
#define Table_Step_FormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm4 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TStringGrid *sg_table_step;
        TButton *btn_set_new_table_step;
        void __fastcall sg_table_stepKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall btn_set_new_table_stepClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm4(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm4 *Form4;
//---------------------------------------------------------------------------
#endif
