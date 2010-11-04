//---------------------------------------------------------------------------

#ifndef TGamutFormH
#define TGamutFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include <java/lang.h>
//#include <cms/cms.h>
#include <cms/util/util.h>
//---------------------------------------------------------------------------
class TGamutSetupForm:public TForm {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox1;
    TLabel *Label1;
    TEdit *Edit_SourceRx;
    TEdit *Edit_SourceRy;
    TEdit *Edit_SourceRLv;
    TLabel *Label2;
    TEdit *Edit_SourceGx;
    TEdit *Edit_SourceGy;
    TEdit *Edit_SourceGLv;
    TLabel *Label3;
    TEdit *Edit_SourceBx;
    TEdit *Edit_SourceBy;
    TEdit *Edit_SourceBLv;
    TLabel *Label4;
    TEdit *Edit_SourceGamma;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TGroupBox *GroupBox2;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label12;
    TLabel *Label13;
    TLabel *Label14;
    TEdit *Edit_TargetRx;
    TEdit *Edit_TargetRy;
    TEdit *Edit_TargetRLv;
    TEdit *Edit_TargetGx;
    TEdit *Edit_TargetGy;
    TEdit *Edit_TargetGLv;
    TEdit *Edit_TargetBx;
    TEdit *Edit_TargetBy;
    TEdit *Edit_TargetBLv;
    TEdit *Edit_TargetGamma;
    TCheckBox *CheckBox_sRGB;
    TButton *Button_Setup;
    TButton *Button1;
    void __fastcall CheckBox_sRGBClick(TObject * Sender);
    void __fastcall Button_SetupClick(TObject * Sender);
    void __fastcall Button1Click(TObject * Sender);
  private:			// User declarations

  public:			// User declarations
     __fastcall TGamutSetupForm(TComponent * Owner);
    //bool dataCollectOk;
     cms::util::CallBackIF * callbackIF;
    double_array getSourceRGBxyY();
    double_array getTargetRGBxyY();
};
//---------------------------------------------------------------------------
extern PACKAGE TGamutSetupForm *GamutSetupForm;
//---------------------------------------------------------------------------
#endif

