//---------------------------------------------------------------------------

#ifndef TMatrixCalibrationH
#define TMatrixCalibrationH
//---------------------------------------------------------------------------

//C系統文件

//C++系統文件

//其他庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//本項目內頭文件
#include "TCA210SettingFrame.h"
//---------------------------------------------------------------------------
class TMatrixCalibrationForm:public TForm {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox1;
    TLabel *Label1;
    TEdit *Edit_R;
    TEdit *Edit_G;
    TEdit *Edit_B;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *Label4;
    TLabel *Label5;
    TEdit *Edit_Rx;
    TEdit *Edit_Gx;
    TEdit *Edit_Wx;
    TEdit *Edit_Bx;
    TEdit *Edit_Ry;
    TEdit *Edit_Gy;
    TEdit *Edit_By;
    TEdit *Edit_Wy;
    TEdit *Edit_RLv;
    TEdit *Edit_GLv;
    TEdit *Edit_BLv;
    TEdit *Edit_WLv;
    TLabel *Label6;
    TLabel *Label7;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TEdit *Edit_MatrixChannel;
    TEdit *Edit_ID;
    TButton *Button_Load;
    TButton *Button_MatrixCalibrate;
    TGroupBox *GroupBox2;
    TLabel *Label11;
    TEdit *Edit_BackupStart;
    TLabel *Label12;
    TEdit *Edit_BackupEnd;
    TButton *Button_SaveToFile;
    TButton *Button_LoadFromFile;
    TCA210SettingFrame *TCA210SettingFrame1;
    TLabel *Label13;
    void __fastcall TCA210SettingFrame1Button_ConnectClick(TObject * Sender);
    void __fastcall TCA210SettingFrame1ComboBox_SyncModeChange(TObject * Sender);
    void __fastcall Button_MatrixCalibrateClick(TObject * Sender);
    void __fastcall FormKeyPress(TObject * Sender, char &Key);
  private:			// User declarations
    //bptr < cms::measure::meter::CA210 > ca210;
     bptr < ca210api::CA210API > ca210API;
     bptr < cms::measure::MeterMeasurement > mm;
  public:			// User declarations
     __fastcall TMatrixCalibrationForm(TComponent * Owner);
    bool setMeter(bptr < ca210api::CA210API > ca210API, bptr < cms::measure::MeterMeasurement > mm);
};
//---------------------------------------------------------------------------
extern PACKAGE TMatrixCalibrationForm *MatrixCalibrationForm;
//---------------------------------------------------------------------------
#endif

