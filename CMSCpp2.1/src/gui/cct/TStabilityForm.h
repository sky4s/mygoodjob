//---------------------------------------------------------------------------

#ifndef TStabilityFormH
#define TStabilityFormH
//---------------------------------------------------------------------------

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//�����ؤ��Y���
#include <java/lang.h>
#include <cms/cms.h>

//---------------------------------------------------------------------------
class TStabilityForm:public TForm {
    __published:		// IDE-managed Components
    TButton * Button1;
    void __fastcall Button1Click(TObject * Sender);
  private:			// User declarations
     bptr < cms::measure::MeterMeasurement > mm;
  public:			// User declarations
     __fastcall TStabilityForm(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TStabilityForm *StabilityForm;
//---------------------------------------------------------------------------
#endif

