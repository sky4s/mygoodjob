//---------------------------------------------------------------------------


#ifndef TOutputFileFrameH
#define TOutputFileFrameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TOutputFileFrame : public TFrame
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox7;
        TLabel *Label5;
        TLabel *Label6;
        TEdit *Edit_Prefix;
        TEdit *Edit_Directory;
        TButton *Button_BrowseDir;
private:	// User declarations
public:		// User declarations
        __fastcall TOutputFileFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TOutputFileFrame *OutputFileFrame;
//---------------------------------------------------------------------------
#endif
