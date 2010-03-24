//---------------------------------------------------------------------------

#ifndef TI2CTestFormH
#define TI2CTestFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TI2CTestForm:public TForm {
    __published:		// IDE-managed Components
    TButton * Button1;
    TGroupBox *GroupBox1;
    TRadioButton *RadioButton_Single;
    TEdit *Edit_Single;
    TRadioButton *RadioButton_Dual;
    TEdit *Edit_Master;
    TEdit *Edit_Slave;
    TGroupBox *GroupBox2;
    TRadioButton *RadioButton_USB;
    TRadioButton *RadioButton_LPT;
    TCheckBox *CheckBox2;
    void __fastcall Button1Click(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
  private:			// User declarations
  public:			// User declarations
     __fastcall TI2CTestForm(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TI2CTestForm *I2CTestForm;
//---------------------------------------------------------------------------
#endif

