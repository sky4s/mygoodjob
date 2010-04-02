//---------------------------------------------------------------------------

#ifndef TGammaAdjustmentFormH
#define TGammaAdjustmentFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TOptionsFrame.h"
#include "TOutputFileFrame.h"
//---------------------------------------------------------------------------
class TGammaAdjustmentForm : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TGroupBox *GroupBox2;
        TEdit *Edit_Channel;
        TComboBox *ComboBox_LevelStep;
        TOptionsFrame *TOptionsFrame1;
        TOutputFileFrame *TOutputFileFrame1;
        TLabel *Label9;
        TGroupBox *GroupBox3;
        TGroupBox *GroupBox4;
        TGroupBox *GroupBox5;
        TLabel *Label1;
        TEdit *Edit_GammaW;
        TButton *Button1;
        TLabel *Label2;
        TLabel *Label3;
        TLabel *Label4;
        TEdit *Edit1;
        TEdit *Edit2;
        TEdit *Edit3;
        TButton *Button2;
        TButton *Button3;
private:	// User declarations
public:		// User declarations
        __fastcall TGammaAdjustmentForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TGammaAdjustmentForm *GammaAdjustmentForm;
//---------------------------------------------------------------------------
#endif
