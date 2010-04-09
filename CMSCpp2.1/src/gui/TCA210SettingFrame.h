//---------------------------------------------------------------------------


#ifndef TCA210SettingFrameH
#define TCA210SettingFrameH
//---------------------------------------------------------------------------

//C系統文件

//C++系統文件

//其他庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//本項目內頭文件
//---------------------------------------------------------------------------
class TCA210SettingFrame:public TFrame {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox1;
    TLabel *Label1;
    TLabel *Label2;
    TLabel *Label3;
    TComboBox *ComboBox_SyncMode;
    TComboBox *ComboBox_Speed;
    TComboBox *ComboBox_CalStandard;
    TEdit *Edit1_Hz;
    TLabel *Label4;
    TLabel *Label5;
    TComboBox *ComboBox_DisplayMode;
    TButton *Button_Connect;
    TButton *Button_Disconnect;
    void __fastcall Button_ConnectClick(TObject * Sender);
    void __fastcall Button_DisconnectClick(TObject * Sender);
    void __fastcall ComboBox_SyncModeChange(TObject * Sender);
    void __fastcall ComboBox_CalStandardChange(TObject * Sender);
  private:			// User declarations
    //bptr < cms::measure::meter::CA210 > ca210;
     bptr < ca210api::CA210API > ca210API;
  public:			// User declarations
     __fastcall TCA210SettingFrame(TComponent * Owner);
    //void setCA210(bptr < cms::measure::meter::CA210 > ca210);
    void setCA210API(bptr < ca210api::CA210API > ca210API);
};
//---------------------------------------------------------------------------
extern PACKAGE TCA210SettingFrame *CA210SettingFrame;
//---------------------------------------------------------------------------
#endif

