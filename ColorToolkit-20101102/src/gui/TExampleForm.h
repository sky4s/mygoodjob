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
#include <Grids.hpp>
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
    TCheckBox *CheckBox2;
    TLabel *Label3;
    TComboBox *ComboBox2;
    TLabel *Label4;
    TComboBox *ComboBox3;
    TStringGrid *StringGrid1;
    TLabel *Label5;
    void __fastcall FormActivate(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall StringGrid1SelectCell(TObject * Sender, int ACol, int ARow, bool & CanSelect);
  private:			// User declarations
     gui::framework::RegisterFramework regframework;
  public:			// User declarations
     __fastcall TExampleForm(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TExampleForm *ExampleForm;
//---------------------------------------------------------------------------
#endif

