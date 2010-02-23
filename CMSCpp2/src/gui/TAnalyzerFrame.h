//---------------------------------------------------------------------------


#ifndef TAnalyzerFrameH
#define TAnalyzerFrameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TAnalyzerFrame : public TFrame
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox3;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TEdit *Edit_SourceCH;
        TEdit *Edit_TargetCH;
        TEdit *Edit_TargetID;
        TGroupBox *GroupBox1;
        TEdit *Edit_R;
        TEdit *Edit_G;
        TEdit *Edit_B;
        TButton *Button1;
private:	// User declarations
public:		// User declarations
        __fastcall TAnalyzerFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TAnalyzerFrame *AnalyzerFrame;
//---------------------------------------------------------------------------
#endif
