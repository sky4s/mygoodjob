//---------------------------------------------------------------------------

#ifndef TMainFormH
#define TMainFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Menus.hpp>

#include <java/lang.h>
//#include <cms/measure/meter.h>
//#include <cms/measure/analyzer.h>
//---------------------------------------------------------------------------

class TMainForm:public TForm {
    __published:		// IDE-managed Components
    TMainMenu * MainMenu1;
    TMenuItem *TargetWhite1;
    TMenuItem *CCTLUT1;
    TMenuItem *GammaAdj1;
    TMenuItem *Measurement1;
    TMenuItem *config1;
    TMenuItem *About1;
    TMenuItem *Exit1;
    void __fastcall About1Click(TObject * Sender);
    void __fastcall Exit1Click(TObject * Sender);
    void __fastcall TargetWhite1Click(TObject * Sender);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall CCTLUT1Click(TObject * Sender);
  private:			// User declarations
    //==========================================================================
    // meter
    //==========================================================================
     bool linkCA210;
     bptr < cms::measure::meter::CA210 > ca210;
     bptr < cms::measure::meter::Meter > meter;
    //==========================================================================
  public:			// User declarations
    //==========================================================================
    // meter
    //==========================================================================
     bptr < cms::measure::MeterMeasurement > mm;
     bptr < cms::measure::meter::CA210 > getCA210();
     bptr < cms::measure::ComponentAnalyzerIF > analyzer;
    //==========================================================================
    __fastcall TMainForm(TComponent * Owner);


};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif

