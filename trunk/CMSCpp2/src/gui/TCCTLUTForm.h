//---------------------------------------------------------------------------

#ifndef TCCTLUTFormH
#define TCCTLUTFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TCCTLUTForm:public TForm {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox1;
    TLabel *Label1;
    TEdit *Edit1;
    TLabel *Label2;
    TLabel *Label3;
    TComboBox *ComboBox1;
    TEdit *Edit2;
    TGroupBox *GroupBox2;
    TRadioButton *RadioButton2;
    TButton *Button1;
    TCheckBox *CheckBox1;
    TRadioButton *RadioButton1;
    TComboBox *ComboBox2;
    TGroupBox *GroupBox3;
    TRadioButton *RadioButton3;
    TRadioButton *RadioButton4;
    TLabel *Label4;
    TEdit *Edit3;
    TGroupBox *GroupBox4;
    TCheckBox *CheckBox2;
    TEdit *Edit4;
    TCheckBox *CheckBox3;
    TGroupBox *GroupBox5;
    TRadioGroup *RadioGroup_in;
    TRadioGroup *RadioGroup_lut;
    TRadioGroup *RadioGroup_out;
    TCheckBox *CheckBox5;
    TCheckBox *CheckBox6;
    TGroupBox *GroupBox6;
    TEdit *Edit_available;
    TGroupBox *GroupBox7;
    TLabel *Label5;
    TEdit *Edit5;
    TLabel *Label6;
    TEdit *Edit6;
    TButton *Button2;
    TOpenDialog *OpenDialog1;
        TButton *Button3;
    void __fastcall RadioGroup_inClick(TObject * Sender);
    void __fastcall RadioGroup_outClick(TObject * Sender);
    void __fastcall RadioGroup_lutClick(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall Button2Click(TObject * Sender);
  private:			// User declarations
     bool checkAvailable(int in, int lut, int out);
    void checkAvailable();
  public:			// User declarations
     __fastcall TCCTLUTForm(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TCCTLUTForm *CCTLUTForm;
//---------------------------------------------------------------------------
#endif

