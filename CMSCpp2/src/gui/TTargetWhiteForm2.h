//---------------------------------------------------------------------------

#ifndef TTargetWhiteForm2H
#define TTargetWhiteForm2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TTargetWhiteForm2:public TForm {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox3;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TEdit *Edit_SourceCH;
    TEdit *Edit_TargetCH;
    TEdit *Edit_TargetID;
    TGroupBox *GroupBox2;
    TGroupBox *GroupBox4;
    TLabel *Label10;
    TLabel *Label11;
    TEdit *Edit_targetx;
    TEdit *Edit_targety;
    TRadioGroup *RadioGroup1;
    TRadioButton *RadioButton1;
    TRadioButton *RadioButton2;
    TButton *Button2;
    TRadioButton *RadioButton3;
    TEdit *Edit_B;
    TEdit *Edit_R;
    TEdit *Edit_G;
    TGroupBox *GroupBox1;
    TLabel *Label2;
    TEdit *Edit_CT;
    TLabel *Label1;
    TLabel *Label5;
    TEdit *Edit_up;
    TLabel *Label6;
    TEdit *Edit_vp;
    TPanel *Panel1;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TScrollBar *ScrollBar_R;
    TEdit *Edit_ScrollR;
    TEdit *Edit_ScrollG;
    TEdit *Edit_ScrollB;
    TScrollBar *ScrollBar_G;
    TScrollBar *ScrollBar_B;
    TGroupBox *GroupBox5;
    void __fastcall RadioButton3Click(TObject * Sender);
    void __fastcall ScrollBar_RChange(TObject * Sender);
    void __fastcall ScrollBar_GChange(TObject * Sender);
    void __fastcall ScrollBar_BChange(TObject * Sender);
    void __fastcall Edit_CTChange(TObject * Sender);
    void __fastcall Edit_targetxChange(TObject * Sender);
    void __fastcall Edit_targetyChange(TObject * Sender);
  private:			// User declarations
    void setColorimetricValues(double x, double y, double up, double vp);
    void scrollBar_Change();
    int calculateCCT(double x, double y);
    bool changing;
  public:			// User declarations
     __fastcall TTargetWhiteForm2(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTargetWhiteForm2 *TargetWhiteForm2;
//---------------------------------------------------------------------------
#endif

