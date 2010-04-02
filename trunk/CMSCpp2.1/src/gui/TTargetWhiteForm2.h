//---------------------------------------------------------------------------

#ifndef TTargetWhiteForm2H
#define TTargetWhiteForm2H
//---------------------------------------------------------------------------

//C系統文件

//C++系統文件

//其他庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Menus.hpp>
//本項目內頭文件

//---------------------------------------------------------------------------
class TTargetWhiteForm2:public TForm {
    __published:		// IDE-managed Components
    TPageControl * PageControl1;
    TTabSheet *TabSheet1;
    TGroupBox *GroupBox2;
    TRadioButton *RadioButton_Targetxy;
    TRadioButton *RadioButton_RGBRatio;
    TButton *Button2;
    TGroupBox *GroupBox4;
    TLabel *Label10;
    TLabel *Label11;
    TLabel *Label2;
    TLabel *Label1;
    TLabel *Label5;
    TLabel *Label6;
    TEdit *Edit_targetx;
    TEdit *Edit_targety;
    TEdit *Edit_CT;
    TEdit *Edit_up;
    TEdit *Edit_vp;
    TRadioButton *RadioButton_MaxRGB;
    TGroupBox *GroupBox1;
    TEdit *Edit_R;
    TEdit *Edit_G;
    TEdit *Edit_B;
    TGroupBox *GroupBox5;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label12;
    TScrollBar *ScrollBar_R;
    TScrollBar *ScrollBar_G;
    TScrollBar *ScrollBar_B;
    TPanel *Panel1;
    TEdit *Edit_ScrollR;
    TEdit *Edit_ScrollG;
    TEdit *Edit_ScrollB;
    TLabel *Label3;
    void __fastcall RadioButton_MaxRGBClick(TObject * Sender);
    void __fastcall ScrollBar_RChange(TObject * Sender);
    void __fastcall ScrollBar_GChange(TObject * Sender);
    void __fastcall ScrollBar_BChange(TObject * Sender);
    void __fastcall Edit_CTChange(TObject * Sender);
    void __fastcall Edit_targetxChange(TObject * Sender);
    void __fastcall Edit_targetyChange(TObject * Sender);
    void __fastcall Button2Click(TObject * Sender);
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

