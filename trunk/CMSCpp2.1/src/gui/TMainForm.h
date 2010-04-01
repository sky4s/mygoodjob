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
#include <ExtCtrls.hpp>
#include <jpeg.hpp>
#include <ComCtrls.hpp>
//本項目內頭文件
#include <java/lang.h>
#include <cms/i2c/i2ccontrol.h>
//---------------------------------------------------------------------------

class TMainForm:public TForm {
    __published:		// IDE-managed Components
    TMainMenu * MainMenu1;
    TMenuItem *TargetWhite1;
    TMenuItem *CCTLUT1;
    TMenuItem *Measurement1;
    TMenuItem *About1;
    TMenuItem *Exit1;
    TLabel *Label6;
    TImage *Image1;
    TMenuItem *Config1;
    TMenuItem *MatrixCalibration1;
    TMenuItem *GammaAdj1;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TPanel *Panel_TCON;
        TGroupBox *GroupBox_Card;
        TRadioButton *RadioButton_USB;
        TRadioButton *RadioButton_LPTLarge;
        TRadioButton *RadioButton_LPTSmall;
        TGroupBox *GroupBox_DeviceAddress;
        TLabel *Label5;
        TRadioButton *RadioButton_SingleTCON;
        TRadioButton *RadioButton_DualTCON;
        TEdit *Edit_DeviceAddress;
        TEdit *Edit_MasterDeviceAddress;
        TEdit *Edit_SlaveDeviceAddress;
        TButton *Button_Connect;
        TCheckBox *CheckBox_Connecting;
        TComboBox *ComboBox_AddressingSize;
        TGroupBox *GroupBox_GammaTestAddress;
        TLabel *Label4;
        TGroupBox *GroupBox5;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *Edit_EnableAddress;
        TEdit *Edit_EnableBit;
        TEdit *Edit_LUTAddress;
        TCheckBox *CheckBox_IndepRGB;
        TGroupBox *GroupBox2;
        TRadioButton *RadioButton_PC;
        TRadioButton *RadioButton_TCON;
        TGroupBox *Resolution;
        TLabel *Width;
        TLabel *Height;
        TEdit *Edit_Width;
        TEdit *Edit_Height;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TEdit *Edit_Interval;
        TGroupBox *GroupBox3;
        TLabel *Label7;
        TLabel *Label8;
        TLabel *Label9;
        TEdit *Edit_SourceCH;
        TEdit *Edit_TargetCH;
        TEdit *Edit_TargetID;
        TGroupBox *GroupBox6;
        TGroupBox *GroupBox8;
        TRadioButton *RadioButton_In6;
        TRadioButton *RadioButton_In8;
        TRadioButton *RadioButton_In10;
        TGroupBox *GroupBox9;
        TRadioButton *RadioButton_Lut10;
        TRadioButton *RadioButton_Lut12;
        TGroupBox *GroupBox10;
        TRadioButton *RadioButton_Out6;
        TRadioButton *RadioButton_Out8;
        TRadioButton *RadioButton_Out10;
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
    void __fastcall Measurement1Click(TObject * Sender);
    void __fastcall MatrixCalibration1Click(TObject * Sender);
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
    void setChannel(int channel);
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

