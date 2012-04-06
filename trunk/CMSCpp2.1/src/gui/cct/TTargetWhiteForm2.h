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
#include <Buttons.hpp>
//本項目內頭文件
#include <gui/event/listener.h>


//---------------------------------------------------------------------------
class TTargetWhiteForm2:public TForm, gui::event::WindowListener {
    __published:		// IDE-managed Components
    TPageControl * PageControl1;
    TTabSheet *TabSheet1;
    TGroupBox *GroupBox2;
    TRadioButton *RadioButton_Targetxy;
    TRadioButton *RadioButton_RGBRatio;
    TButton *Button_Run;
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
    TCheckBox *CheckBox_MoreAccurate;
    TTabSheet *TabSheet2;
    TGroupBox *GroupBox6;
    TEdit *Edit_RZ;
    TEdit *Edit_GZ;
    TEdit *Edit_BZ;
    TEdit *Edit_WZ;
    TEdit *Edit_WY;
    TEdit *Edit_BY;
    TEdit *Edit_GY;
    TEdit *Edit_RY;
    TEdit *Edit_RX;
    TEdit *Edit_GX;
    TEdit *Edit_BX;
    TEdit *Edit_WX;
    TLabel *Label17;
    TLabel *Label20;
    TLabel *Label18;
    TLabel *Label19;
    TLabel *Label15;
    TLabel *Label9;
    TLabel *Label16;
    TButton *Button_setMaxMatrix;
    TButton *Button_Connect;
    TButton *Button_Disconnect;
    TCheckBox *CheckBox_Lock;
    TGroupBox *GroupBox7;
    TLabel *Label4;
    TEdit *Edit_refx;
    TLabel *Label7;
    TEdit *Edit_refy;
    TLabel *Label8;
    TEdit *Edit_refLuminance;
    TButton *Button_Measure;
    TProgressBar *ProgressBar1;
    TButton *Button_ConnectToggle;
    TEdit *Edit_InverseIntensityofB;
    TButton *Button_FindInverseIntensity;
    TStatusBar *StatusBar1;
    void __fastcall RadioButton_MaxRGBClick(TObject * Sender);
    void __fastcall ScrollBar_RChange(TObject * Sender);
    void __fastcall ScrollBar_GChange(TObject * Sender);
    void __fastcall ScrollBar_BChange(TObject * Sender);
    void __fastcall Edit_CTChange(TObject * Sender);
    void __fastcall Edit_targetxChange(TObject * Sender);
    void __fastcall Edit_targetyChange(TObject * Sender);
    void __fastcall Button_RunClick(TObject * Sender);
    void __fastcall Edit_RChange(TObject * Sender);
    void __fastcall Edit_GChange(TObject * Sender);
    void __fastcall Edit_BChange(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall Edit_BZChange(TObject * Sender);
    void __fastcall FormShow(TObject * Sender);
    void __fastcall Button_setMaxMatrixClick(TObject * Sender);
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
    void __fastcall Button_ConnectClick(TObject * Sender);
    void __fastcall Button_DisconnectClick(TObject * Sender);
    void __fastcall Button_MeasureClick(TObject * Sender);
    void __fastcall Button_ConnectToggleClick(TObject * Sender);
    void __fastcall Button_FindInverseIntensityClick(TObject * Sender);
    void __fastcall Edit_InverseIntensityofBKeyPress(TObject * Sender, char &Key);
    void __fastcall FormResize(TObject * Sender);
    void __fastcall PageControl1Resize(TObject * Sender);
  private:			// User declarations
    void setColorimetricValues(double x, double y, double up, double vp);
    void scrollBar_Change();
    int calculateCCT(double x, double y);
    bool colorimetricChanging;

    bptr < cms::lcd::BitDepthProcessor > bitDepth;
    void setRGBRatio(int r, int g, int b);
    //int maxBRawGrayLevel;
    //bool findInverseZ;
    mbinder_ptr binder;
    bool continueMeasure;
    bool measuring;
    bool connect;
  public:			// User declarations
    __fastcall TTargetWhiteForm2(TComponent * Owner);
    void windowClosing();
    void setBitDepthProcessor(bptr < cms::lcd::BitDepthProcessor > bitDepth);
    bool stopMeasure;
    //__property bool FindInverseZ = { read = findInverseZ };

};
//---------------------------------------------------------------------------
extern PACKAGE TTargetWhiteForm2 *TargetWhiteForm2;
//---------------------------------------------------------------------------
#endif

