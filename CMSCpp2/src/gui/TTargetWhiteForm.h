//---------------------------------------------------------------------------

#ifndef TTargetWhiteFormH
#define TTargetWhiteFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <java/lang.h>
//---------------------------------------------------------------------------
class TTargetWhiteForm:public TForm {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox1;
    TLabel *Label1;
    TEdit *Edit_CT;
    TLabel *Label2;
    TLabel *Label3;
    TEdit *Edit_x;
    TLabel *Label4;
    TEdit *Edit_y;
    TLabel *Label5;
    TLabel *Label6;
    TEdit *Edit_up;
    TEdit *Edit_vp;
    TButton *Button_Calculate;
    TGroupBox *GroupBox2;
    TGroupBox *GroupBox3;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TEdit *Edit_SourceCH;
    TEdit *Edit_TargetCH;
    TEdit *Edit_TargetID;
    TGroupBox *GroupBox4;
    TLabel *Label10;
    TEdit *Edit_targetx;
    TLabel *Label11;
    TEdit *Edit_targety;
    TRadioGroup *RadioGroup1;
    TRadioButton *RadioButton1;
    TRadioButton *RadioButton2;
    TButton *Button2;
    TPanel *Panel1;
    TScrollBar *ScrollBar_R;
    TEdit *Edit_R;
    TEdit *Edit_G;
    TEdit *Edit_B;
    TLabel *Label12;
    TScrollBar *ScrollBar_G;
    TScrollBar *ScrollBar_B;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label15;
    void __fastcall ScrollBar_RChange(TObject * Sender);
    void __fastcall ScrollBar_GChange(TObject * Sender);
    void __fastcall ScrollBar_BChange(TObject * Sender);
    void __fastcall Edit_CTChange(TObject * Sender);
    void __fastcall Button2Click(TObject * Sender);

  private:			// User declarations
    void scrollBar_Change();
    void setColorimetricValues(double x, double y, double up, double vp);
  public:			// User declarations
     __fastcall TTargetWhiteForm(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TTargetWhiteForm *TargetWhiteForm;
//---------------------------------------------------------------------------
#endif

