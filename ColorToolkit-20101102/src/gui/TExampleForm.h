//---------------------------------------------------------------------------

#ifndef TExampleFormH
#define TExampleFormH
//---------------------------------------------------------------------------


//C�t�Τ��

//C++�t�Τ��

//vcl�w�Y���
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//��L�w�Y���

//�����ؤ��Y���
#include <gui/framework/RegisterFramework.h>

//�����ؤ�gui�Y���
//---------------------------------------------------------------------------
class TExampleForm:public TForm {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox1;
    TCheckBox *CheckBox1;
    TLabel *Label1;
    TComboBox *ComboBox1;
    TLabel *Label2;
    TScrollBar *ScrollBar1;
    TStaticText *StaticText1;
        TLabeledEdit *LabeledEdit1;
    void __fastcall FormActivate(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
  private:			// User declarations
     gui::framework::RegisterFramework regframework;
  public:			// User declarations
     __fastcall TExampleForm(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TExampleForm *ExampleForm;
//---------------------------------------------------------------------------
#endif

