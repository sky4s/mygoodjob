//---------------------------------------------------------------------------

#ifndef TMainFormH
#define TMainFormH
//---------------------------------------------------------------------------
//C系統文件

//C++系統文件

//其他庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>
//本項目內頭文件
#include <java/lang.h>
//---------------------------------------------------------------------------

class TMainForm:public TForm {
    __published:		// IDE-managed Components
    TMainMenu * MainMenu1;
    TMenuItem *TargetWhite1;
    TMenuItem *CCTLUT1;
    TMenuItem *Measurement1;
    TMenuItem *About1;
    TMenuItem *Exit1;
    TGroupBox *Resolution;
    TLabel *Width;
    TLabel *Height;
    TGroupBox *GroupBox1;
    TEdit *Edit_Interval;
    TLabel *Label1;
    TGroupBox *GroupBox2;
    TRadioButton *RadioButton_PC;
    TRadioButton *RadioButton_TCON;
    TEdit *Edit_Width;
    TEdit *Edit_Height;
    TGroupBox *GroupBox_DeviceAddress;
    TRadioButton *RadioButton_SingleTCON;
    TRadioButton *RadioButton_DualTCON;
    TEdit *Edit_DeviceAddress;
    TEdit *Edit_MasterDeviceAddress;
    TEdit *Edit_SlaveDeviceAddress;
    TButton *Button_Connect;
    TGroupBox *GroupBox_GammaTestAddress;
    TGroupBox *GroupBox5;
    TLabel *Label2;
    TEdit *Edit_EnableAddress;
    TLabel *Label3;
    TEdit *Edit_EnableBit;
    TLabel *Label4;
    TEdit *Edit_LUTAddress;
    TGroupBox *GroupBox_Card;
    TRadioButton *RadioButton_USB;
    TRadioButton *RadioButton_LPTLarge;
    TRadioButton *RadioButton_LPTSmall;
    TCheckBox *CheckBox_Connecting;
    TLabel *Label5;
    TComboBox *ComboBox_AddressingSize;
    TCheckBox *CheckBox_IndepRGB;
    void __fastcall About1Click(TObject * Sender);
    void __fastcall Exit1Click(TObject * Sender);
    void __fastcall TargetWhite1Click(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall CCTLUT1Click(TObject * Sender);
    void __fastcall GammaAdj1Click(TObject * Sender);
    void __fastcall RadioButton_TCONClick(TObject * Sender);
    void __fastcall RadioButton_PCClick(TObject * Sender);
    void __fastcall Button_ConnectClick(TObject * Sender);
    void __fastcall CheckBox_ConnectingClick(TObject * Sender);
        void __fastcall Measurement1Click(TObject *Sender);
  private:			// User declarations
    //==========================================================================
    // meter
    //==========================================================================
     bptr < cms::measure::meter::CA210 > ca210;
     bptr < cms::measure::meter::Meter > meter;
     bptr < cms::measure::meter::CA210 > getCA210();
    //==========================================================================
    const cms::i2c::AddressingSize getAddressingSize();
     bptr < cms::i2c::TCONParameter > parameter;
     bptr < cms::i2c::TCONControl > control;
  public:			// User declarations
    //==========================================================================
    // meter
    //==========================================================================
     bool linkCA210;
     bptr < cms::measure::MeterMeasurement > mm;
     bptr < cms::measure::IntensityAnalyzerIF > analyzer;
    int getInterval();
    void setDummyMeterFilename(const std::string & filename);
    void resetDummyMeter();
    //==========================================================================
    __fastcall TMainForm(TComponent * Owner);


};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif

