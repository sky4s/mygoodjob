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
#include <cms/measure/meter.h>
//---------------------------------------------------------------------------

class TMainForm:public TForm {
    __published:		// IDE-managed Components
    TMainMenu * MainMenu1;
    TMenuItem *MatrixCalibration1;
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
  private:			// User declarations
  public:			// User declarations
     __fastcall TMainForm(TComponent * Owner);
    //boost::shared_ptr < cms::measure::meter::CA210 > meter;
    //boost::shared_ptr < cms::measure::meter::Meter > meter;
    boost:: shared_ptr < cms::measure::meter::Meter > meter;
};
//---------------------------------------------------------------------------
extern PACKAGE TMainForm *MainForm;
//---------------------------------------------------------------------------
#endif

