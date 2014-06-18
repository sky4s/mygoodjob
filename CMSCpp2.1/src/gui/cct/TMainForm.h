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
#include <Buttons.hpp>
//本項目內頭文件
#include <i2c/i2ccontrol.h>
#include <cms/measure/meter.h>	//20120302
#include <cms/lcd/calibrate/include.h>	//20120302
#include "TGammaMeasurementForm.h"

extern bool g_bIsRunAgain;	//?明用于重?判?的?量g_bIsfRunAgain
//---------------------------------------------------------------------------
class ProgressThread;
class TMainForm:public TForm {
    __published:		// IDE-managed Components
    TMainMenu * MainMenu1;
    TMenuItem *TargetWhite1;
    TMenuItem *CCTLUT1;
    TMenuItem *Measurement1;
    TMenuItem *Exit1;
    TLabel *Label6;
    TImage *Image1;
    TMenuItem *MatrixCalibration1;
    TMenuItem *GammaAdj1;
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TPanel *Panel_TCON;
    TGroupBox *GroupBox_Card;
        TRadioButton *RadioButton_AUO_USB;
    TRadioButton *RadioButton_LPTLarge;
    TRadioButton *RadioButton_LPTSmall;
    TGroupBox *GroupBox_DeviceAddress;
    TLabel *Label5;
    TRadioButton *RadioButton_SingleTCON;
    TRadioButton *RadioButton_DualTCON;
    TEdit *Edit_DeviceAddress;
    TEdit *Edit_MasterDeviceAddress;
    TEdit *Edit_SlaveDeviceAddress;
    TComboBox *ComboBox_AddressingSize;
    TGroupBox *GroupBox2;
    TRadioButton *RadioButton_PC;
        TRadioButton *RadioButton_TCON_directGamma;
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TEdit *Edit_Interval;
    TButton *Button_I2CTest;
    TButton *Button_Connect;
    TGroupBox *GroupBox7;
    TComboBox *ComboBox_TCONType;
    TGroupBox *GroupBox_Pattern;
    TRadioButton *RadioButton_Normal;
    TRadioButton *RadioButton_HStripe;
    TRadioButton *RadioButton_Indep;
    TRadioButton *RadioButton_HSD;
    TRadioButton *RadioButton_FlickrPixel;
    TRadioButton *RadioButton_FlickrSubPixel;
    TRadioButton *RadioButton_PCTCON_NB;
    TRadioButton *RadioButton_Ninth;
    TCheckBox *CheckBox_LineAdjoin;
    TGroupBox *GroupBox_BitDepth;
    TLabel *Label10;
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
    TEdit *Edit_FRCAbility;
    TProgressBar *ProgressBar1;
    TStatusBar *StatusBar1;
    TLabel *Label21;
    TEdit *Edit_AverageTimes;
    TRadioButton *RadioButton_PCTCON_TV;
    TGroupBox *GroupBox_USBSetting;
    TRadioGroup *RadioGroup_USBPower;
    TRadioGroup *RadioGroup_Speed;
    TMenuItem *Help1;
    TMenuItem *ChangeLog1;
    TMenuItem *About2;
    TGroupBox *GroupBox_CHSetting;
    TLabel *Label7;
    TEdit *Edit_SourceCH;
    TMenuItem *GammaMeasure1;
    TMenuItem *StabilityMeasure1;
    TGroupBox *GroupBox3;
    TCheckBox *CheckBox_InverseMeasure;
    TRadioButton *RadioButton_HStripe2;
    TGroupBox *GroupBox4;
    TButton *Button_PatternTest;
        TRadioButton *RadioButton_TCON_aging;
        TLabel *Label29;
        TRadioButton *RadioButton_DoDoBird_USB;
        TPageControl *PageControl_RegisterSetting;
        TTabSheet *TabSheet3;
        TTabSheet *TabSheet_AGTiming;
        TGroupBox *GroupBox_AgingMode;
        TGroupBox *GroupBox_AgingModeSel;
        TLabel *Label18;
        TLabel *Label19;
        TEdit *Edit_AgingModeSelectAddress;
        TEdit *Edit_AgingModeSelectBit;
        TGroupBox *GroupBox_AgingPatternSel;
        TLabel *Label20;
        TLabel *Label23;
        TLabel *Label25;
        TLabel *Label26;
        TEdit *Edit_AgingPatternSelectAddress;
        TEdit *Edit_AgingPatternSelectStartBit;
        TEdit *Edit_AgingPatternSelectEndBit;
        TEdit *Edit_AgingPatternSelectValue;
        TGroupBox *GroupBox_AgingRasterGray;
        TLabel *Label22;
        TLabel *Label24;
        TComboBox *ComboBox_AgingType;
        TEdit *Edit_AgingRasterGrayAddress;
        TGroupBox *GroupBox_AgingAGBSDebug;
        TLabel *Label27;
        TLabel *Label28;
        TEdit *Edit_AgingAGBSDebugAddress;
        TEdit *Edit_AgingAGBSDebugBit;
        TGroupBox *GroupBox_MANU_SEL;
        TLabel *Label36;
        TLabel *Label37;
        TEdit *Edit_AgingManuSelectAddress;
        TEdit *Edit_AgingManuSelectBit;
        TGroupBox *GroupBox_FRC;
        TGroupBox *GroupBox_FRC_EN;
        TLabel *Label9;
        TLabel *Label16;
        TEdit *Edit_FRCEnableAddress;
        TEdit *Edit_FRCEnableBit;
        TGroupBox *GroupBox_SecondGamma;
        TGroupBox *GroupBox_GroupBox_GAM2_EN;
        TLabel *Label30;
        TLabel *Label31;
        TLabel *Label40;
        TEdit *Edit_DG2EnableAddress;
        TEdit *Edit_DG2EnableBit;
        TEdit *Edit_DG2LUTAddress;
        TGroupBox *GroupBox_GAM2_TEST;
        TLabel *Label32;
        TLabel *Label33;
        TLabel *Label41;
        TEdit *Edit_GammaTest2EnableAddress;
        TEdit *Edit_GammaTest2EnableBit;
        TEdit *Edit_DirectGamma2Address;
        TCheckBox *CheckBox_SecondGamma;
        TGroupBox *GroupBox_FRC2_EN;
        TLabel *Label38;
        TLabel *Label39;
        TEdit *Edit_FRC2EnableAddress;
        TEdit *Edit_FRC2EnableBit;
        TGroupBox *GroupBox_DirectGamma;
        TGroupBox *GroupBox_GAM_TEST;
        TLabel *Label2;
        TLabel *Label3;
        TEdit *Edit_GammaTestEnableAddress;
        TEdit *Edit_GammaTestEnableBit;
        TGroupBox *GroupBox_GAMDIRECT;
        TLabel *Label4;
        TLabel *Label11;
        TEdit *Edit_DirectGammaAddress;
        TComboBox *ComboBox_DirectGammaType;
        TGroupBox *GroupBox_HideEN;
        TLabel *Label8;
        TLabel *Label17;
        TEdit *Edit_HideEnableAddress;
        TEdit *Edit_HideEnableBit;
        TCheckBox *CheckBox_HideEN;
        TGroupBox *GroupBox_DigitalGamma;
        TGroupBox *GroupBox_GAM_EN;
        TLabel *Label13;
        TLabel *Label14;
        TEdit *Edit_DGEnableAddress;
        TEdit *Edit_DGEnableBit;
        TGroupBox *GroupBox_LUT;
        TLabel *Label12;
        TLabel *Label15;
        TComboBox *ComboBox_DGLUTType;
        TEdit *Edit_DGLUTAddress;
        TCheckBox *CheckBox_AgingMode;
        TCheckBox *CheckBox_DirectGamma;
        TGroupBox *GroupBox_PGmode;
        TLabel *Label53;
        TCheckBox *CheckBox_PGMode;
        TGroupBox *GroupBox5;
        TLabel *Label34;
        TLabel *Label35;
        TEdit *Edit_PGEnableAddress;
        TEdit *Edit_PGEnableBit;
        TGroupBox *GroupBox6;
        TLabel *Label42;
        TLabel *Label43;
        TLabel *Label65;
        TEdit *Edit_PGModeAddress;
        TEdit *Edit_PGModeStartBit;
        TEdit *Edit_PGModeEndBit;
        TGroupBox *GroupBox11;
        TLabel *Label44;
        TLabel *Label45;
        TLabel *Label46;
        TLabel *Label47;
        TLabel *Label59;
        TLabel *Label60;
        TEdit *Edit_PGPatternMSBStartBit;
        TEdit *Edit_PGPatternMSBEndBit;
        TEdit *Edit_PGPatternLSBStartBit;
        TEdit *Edit_PGPatternLSBEndBit;
        TEdit *Edit_PGPatternMSBAddress;
        TEdit *Edit_PGPatternLSBAddress;
        TGroupBox *GroupBox12;
        TLabel *Label48;
        TLabel *Label49;
        TLabel *Label50;
        TLabel *Label51;
        TLabel *Label52;
        TLabel *Label61;
        TLabel *Label62;
        TEdit *Edit_PGHblkMSBStartBit;
        TEdit *Edit_PGHblkMSBEndBit;
        TEdit *Edit_PGHblkLSBStartBit;
        TEdit *Edit_PGHblkLSBEndBit;
        TEdit *Edit_PGHblkMSBAddress;
        TEdit *Edit_PGHblkLSBAddress;
        TEdit *Edit_PGHblkValue;
        TGroupBox *GroupBox13;
        TLabel *Label54;
        TLabel *Label55;
        TLabel *Label56;
        TLabel *Label57;
        TLabel *Label58;
        TLabel *Label63;
        TLabel *Label64;
        TEdit *Edit_PGVblkMSBStartBit;
        TEdit *Edit_PGVblkMSBEndBit;
        TEdit *Edit_PGVblkLSBStartBit;
        TEdit *Edit_PGVblkLSBEndBit;
        TEdit *Edit_PGVblkMSBAddress;
        TEdit *Edit_PGVblkLSBAddress;
        TEdit *Edit_PGVblkValue;
        TGroupBox *GroupBox14;
        TComboBox *ComboBox_AGFrameRate;
        TLabel *Label66;
        TLabel *Label67;
        TEdit *Edit_AGFrameRateAddress;
        TEdit *Edit_AGFrameRateStartBit;
        TLabel *Label68;
        TEdit *Edit_AGFrameRateEndBit;
        TGroupBox *GroupBox22;
        TGroupBox *GroupBox18;
        TLabel *Label69;
        TLabel *Label70;
        TLabel *Label71;
        TLabel *Label79;
        TEdit *Edit_mpllModeAddress;
        TEdit *Edit_mpllModeEndBit;
        TEdit *Edit_mpllModeStartBit;
        TEdit *Edit_mpllModeValue;
        TGroupBox *GroupBox20;
        TLabel *Label72;
        TLabel *Label73;
        TLabel *Label74;
        TLabel *Label75;
        TLabel *Label76;
        TLabel *Label77;
        TLabel *Label78;
        TEdit *Edit_mpllFMSBAddress;
        TEdit *Edit_mpllFMSBEndBit;
        TEdit *Edit_mpllFMSBStartBit;
        TEdit *Edit_mpllFLSBAddress;
        TEdit *Edit_mpllFLSBEndBit;
        TEdit *Edit_mpllFLSBStartBit;
        TEdit *Edit_mpllFValue;
        TGroupBox *GroupBox21;
        TLabel *Label80;
        TLabel *Label81;
        TLabel *Label82;
        TEdit *Edit_mpllMAddress;
        TEdit *Edit_mpllMEndBit;
        TEdit *Edit_mpllMStartBit;
        TEdit *Edit_mpllMValue;
        TGroupBox *GroupBox19;
        TLabel *Label83;
        TLabel *Label85;
        TEdit *Edit_mpllNMSBAddress;
        TEdit *Edit_mpllNMSBEndBit;
        TEdit *Edit_mpllNMSBStartBit;
        TEdit *Edit_mpllNValue;
        TGroupBox *GroupBox23;
        TGroupBox *GroupBox15;
        TLabel *Label100;
        TLabel *Label101;
        TLabel *Label102;
        TLabel *Label103;
        TLabel *Label104;
        TLabel *Label105;
        TLabel *Label106;
        TEdit *Edit_AGHblkMSBAddress;
        TEdit *Edit_AGHblkMSBStartBit;
        TEdit *Edit_AGHblkMSBEndBit;
        TEdit *Edit_AGHblkLSBAddress;
        TEdit *Edit_AGHblkLSBStartBit;
        TEdit *Edit_AGHblkLSBEndBit;
        TEdit *Edit_AGHblkValue;
        TGroupBox *GroupBox16;
        TLabel *Label86;
        TLabel *Label87;
        TLabel *Label88;
        TLabel *Label89;
        TLabel *Label90;
        TLabel *Label91;
        TLabel *Label92;
        TEdit *Edit_AGVblk1MSBAddress;
        TEdit *Edit_AGVblk1MSBStartBit;
        TEdit *Edit_AGVblk1MSBEndBit;
        TEdit *Edit_AGVblk1LSBAddress;
        TEdit *Edit_AGVblk1LSBStartBit;
        TEdit *Edit_AGVblk1LSBEndBit;
        TEdit *Edit_AGVblk1Value;
        TGroupBox *GroupBox17;
        TLabel *Label93;
        TLabel *Label94;
        TLabel *Label95;
        TLabel *Label96;
        TLabel *Label97;
        TLabel *Label98;
        TLabel *Label99;
        TEdit *Edit_AGVblk2MSBAddress;
        TEdit *Edit_AGVblk2MSBStartBit;
        TEdit *Edit_AGVblk2MSBEndBit;
        TEdit *Edit_AGVblk2LSBAddress;
        TEdit *Edit_AGVblk2LSBStartBit;
        TEdit *Edit_AGVblk2LSBEndBit;
        TEdit *Edit_AGVblk2Value;
        TCheckBox *CheckBox_AGtiming;
        TLabel *Label84;
        TLabel *Label107;
        TLabel *Label108;
        TLabel *Label109;
        TLabel *Label110;
        TEdit *Edit_mpllNLSBAddress;
        TEdit *Edit_mpllNLSBEndBit;
        TEdit *Edit_mpllNLSBStartBit;
    void __fastcall About1Click(TObject * Sender);
    void __fastcall Exit1Click(TObject * Sender);
    void __fastcall TargetWhite1Click(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall CCTLUT1Click(TObject * Sender);
    void __fastcall GammaAdj1Click(TObject * Sender);
    void __fastcall RadioButton_TCON_directGammaClick(TObject * Sender);
    void __fastcall RadioButton_PCClick(TObject * Sender);
    void __fastcall Button_ConnectClick(TObject * Sender);
    void __fastcall MatrixCalibration1Click(TObject * Sender);
    void __fastcall RadioButton_In6Click(TObject * Sender);
    void __fastcall RadioButton_In8Click(TObject * Sender);
    void __fastcall RadioButton_In10Click(TObject * Sender);
    void __fastcall RadioButton_Lut10Click(TObject * Sender);
    void __fastcall RadioButton_Lut12Click(TObject * Sender);
    void __fastcall RadioButton_Out6Click(TObject * Sender);
    void __fastcall RadioButton_Out8Click(TObject * Sender);
    void __fastcall RadioButton_Out10Click(TObject * Sender);
    void __fastcall Button1Click(TObject * Sender);
    void __fastcall Edit_IntervalChange(TObject * Sender);
    void __fastcall Button_I2CTestClick(TObject * Sender);
    void __fastcall RadioButton_NormalClick(TObject * Sender);
    void __fastcall RadioButton_HStripeClick(TObject * Sender);
    void __fastcall RadioButton_IndepClick(TObject * Sender);
    void __fastcall RadioButton_HSDClick(TObject * Sender);
    void __fastcall RadioButton_FlickrPixelClick(TObject * Sender);
    void __fastcall RadioButton_FlickrSubPixelClick(TObject * Sender);
    void __fastcall FormDestroy(TObject * Sender);
    void __fastcall RadioButton_AUO_USBClick(TObject * Sender);
    void __fastcall RadioButton_LPTLargeClick(TObject * Sender);
    void __fastcall RadioButton_LPTSmallClick(TObject * Sender);
    void __fastcall ComboBox_TCONTypeChange(TObject * Sender);
    void __fastcall CheckBox_DirectGammaClick(TObject * Sender);
    void __fastcall RadioButton_PCTCON_NBClick(TObject * Sender);
    void __fastcall RadioButton_NinthClick(TObject * Sender);
    void __fastcall ComboBox_DGLUTTypeChange(TObject * Sender);
    void __fastcall TabSheet2Exit(TObject * Sender);
    void __fastcall Edit_AverageTimesChange(TObject * Sender);
    void __fastcall RadioButton_PCTCON_TVClick(TObject * Sender);
    void __fastcall Edit_SourceCHKeyPress(TObject * Sender, char &Key);
    void __fastcall TabSheet2Enter(TObject * Sender);
    void __fastcall About2Click(TObject * Sender);
    void __fastcall ChangeLog1Click(TObject * Sender);
    void __fastcall GammaMeasure1Click(TObject * Sender);
    void __fastcall StabilityMeasure1Click(TObject * Sender);
    void __fastcall RadioButton_HStripe2Click(TObject * Sender);
    void __fastcall CheckBox_HideENClick(TObject * Sender);
    void __fastcall Button_PatternTestClick(TObject * Sender);
    void __fastcall RadioButton_NinthMouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall GroupBox4MouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall TabSheet1MouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall RadioButton_IndepMouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall RadioButton_HSDMouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall RadioButton_FlickrPixelMouseMove(TObject * Sender,
						     TShiftState Shift, int X, int Y);
    void __fastcall RadioButton_FlickrSubPixelMouseMove(TObject * Sender, TShiftState Shift, int X,
							int Y);
    void __fastcall RadioButton_HStripeMouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall RadioButton_HStripe2MouseMove(TObject * Sender,
						  TShiftState Shift, int X, int Y);
    void __fastcall RadioButton_NormalMouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall FormActivate(TObject * Sender);
        void __fastcall RadioButton_TCON_agingClick(TObject *Sender);
        void __fastcall CheckBox_AgingModeClick(TObject *Sender);
        void __fastcall CheckBox_SecondGammaClick(TObject *Sender);
        void __fastcall CheckBox_PGModeClick(TObject *Sender);
        void __fastcall RadioButton_DoDoBird_USBClick(TObject *Sender);
        void __fastcall ComboBox_AGFrameRateChange(TObject *Sender);
  private:			// User declarations
    //==========================================================================
    // meter
    //==========================================================================
     bptr < cms::measure::meter::CA210 > ca210;
     bptr < cms::measure::meter::Meter > meter;
     bptr < cms::measure::meter::CA210 > getCA210();
     bptr < cms::lcd::calibrate::ComponentFetcher > fetcher;
    int getInterval();
     bptr < cms::measure::CA210IntensityAnalyzer > ca210Analyzer;
     bptr < cms::measure::IntensityAnalyzerIF > analyzer;
     bptr < cms::measure::MaxMatrixIntensityAnalyzer > secondWhiteAnalyzer;
    //==========================================================================
    //==========================================================================
    // T-CON ctrl
    //==========================================================================
    const i2c::AddressingSize getAddressingSize();
     bptr < i2c::TCONParameter > parameter;
     bptr < i2c::TCONControl > control;
    void setBitDepthEnable(bool lut10, bool lut12, bool out6, bool out8, bool out10);
    void setBitDepthChecked(int lutSelect, int outSelect);
    void setFRCAbility();
     bptr < cms::lcd::BitDepthProcessor > bitDepth;
    //==========================================================================
    // T-CON setup
    //==========================================================================
    void readTCONSetup(String filename, String section);
    void writeTCONCustomSetup();
    void readSetup();
    void writeSetup();
    void readTCONSections();
    String tconFilename;
    void initTCONFile();
    void setComboBoxTCONType();   //用來控制選Aging mode時，出現哪些tcon選項。
    void initialFactoryIF();      //用來工廠模式簡化頁面
    const static char *CUSTOM;
    //==========================================================================

    ProgressThread *progressThread;
    TThread *ca210Thread;
    bool connectCA210ByThread;

  public:			// User declarations
    //==========================================================================
    // meter
    //==========================================================================
     bptr < cms::measure::MeterMeasurement > mm;

    void setAnalyzerToTargetChannel();
    void setAnalyzerToSourceChannel();

    //analyzer
    bool isCA210Analyzer();
     bptr < cms::measure::IntensityAnalyzerIF > initAnalyzer();
     bptr < cms::measure::MaxMatrixIntensityAnalyzer > getSecondAnalyzerFromProperty();
    void setAnalyzerNull();

    //meter
    void setMeterMeasurementWaitTimes();
    void setDummyMeterFilename(const std::string & filename);
    void setDummyMeterFile(bptr < cms::colorformat::DGLutFile > dglutFile);
    void resetDummyMeter();
    void disconnectMeter();
    void connectMeter();
    void initCA210Meter();
    int getAverageTimes();

     bptr < cms::lcd::calibrate::ComponentFetcher > getComponentFetcher();
    //==========================================================================

    //==========================================================================
    // T-CON/Panel
    //==========================================================================
     bptr < i2c::TCONControl > getTCONControl();
    bool isPCwithDirectGamma();
    bool isInTCONSetup();
    //==========================================================================

    //==========================================================================
    // info flag
    //==========================================================================
    const bool linkEyeOne;
    const bool linkCA210;
    const bool newFunction;
    const bool debugMode;
    const bool factoryMode;
    //==========================================================================
    __fastcall TMainForm(TComponent * Owner);
    void showProgress(TProgressBar * progress);
    void stopProgress(TProgressBar * progress);
    void setAllFunctionOn(bool on);
    TGammaMeasurementForm *getGammaMeasurementForm() {
	if (GammaMeasurementForm == null) {
	    Application->CreateForm(__classid(TGammaMeasurementForm), &GammaMeasurementForm);

	}
	return GammaMeasurementForm;
    };

};

class ProgressThread:public TThread {
  private:
    TProgressBar * progress;
  protected:
    void __fastcall Execute();
  public:
     __fastcall ProgressThread(bool CreateSuspended, TProgressBar * progress);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif

