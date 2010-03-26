//---------------------------------------------------------------------------

#ifndef TI2CTestFormH
#define TI2CTestFormH
//---------------------------------------------------------------------------

//C系統文件

//C++系統文件

//其他庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//本項目內頭文件
#include <java/lang.h>
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
    TCheckBox *CheckBox_Connecting;
    TGroupBox *GroupBox3;
    TCheckBox *CheckBox1;
    TEdit *Edit1;
    TEdit *Edit2;
    TEdit *Edit3;
    void __fastcall Button1Click(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall Edit1Change(TObject * Sender);
    void __fastcall Edit2Change(TObject * Sender);
    void __fastcall Edit3Change(TObject * Sender);
  private:			// User declarations
     bptr < cms::i2c::i2cControl > i2c;
  public:			// User declarations
     __fastcall TI2CTestForm(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TI2CTestForm *I2CTestForm;
//---------------------------------------------------------------------------
#endif

