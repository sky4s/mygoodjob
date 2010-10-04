//---------------------------------------------------------------------------


#ifndef THSVAdjustFrameH
#define THSVAdjustFrameH
//---------------------------------------------------------------------------


//C系統文件

//C++系統文件

//vcl庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//其他庫頭文件

//本項目內頭文件
#include <gui/util/binder.h>

//本項目內gui頭文件
//---------------------------------------------------------------------------

class HueSetter;
class SaturationSetter;

class THSVAdjustFrame:public TFrame {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox40;
    TLabel *lb_c3d_Manual39_h;
    TLabel *Label197;
    TScrollBar *sb_c3d_Manual39_h;
    TEdit *Edit_c3d_Manual39_h_adj;
    TGroupBox *GroupBox41;
    TLabel *lb_c3d_Manual39_s;
    TLabel *Label207;
    TScrollBar *sb_c3d_Manual39_s;
    TEdit *edt_c3d_satC;
    TEdit *Edit_c3d_Manual39_s_adj;
    TGroupBox *GroupBox7;
    TLabel *lb_c3d_Manual39_v;
    TLabel *Label25;
    TScrollBar *sb_c3d_Manual39_v;
    TEdit *Edit_c3d_Manual39_v_adj;
    TEdit *edt_c3d_valC;
    void __fastcall sb_c3d_Manual39_hChange(TObject * Sender);
  private:			// User declarations
     gui::util::MultiUIBinder binder;
    double h, s, v;
     bptr < HueSetter > hueSetter;
     bptr < SaturationSetter > saturationSetter;
  public:			// User declarations
     __fastcall THSVAdjustFrame(TComponent * Owner);
    void setHSV(double h, double s, double v);
};

class HueSetter:public gui::util::Label2ScrollBarSetter {
  public:
    HueSetter(TLabel * label, TScrollBar * scrollBar)
    :gui::util::Label2ScrollBarSetter(label, scrollBar) {
    };
    virtual void set(TObject * sender) {
	if (sender == scrollBar) {
	    double h = scrollBar->Position - scrollBar->Max / 2;
	    label->Caption = FloatToStr(h) + "°";
	}
    };
};

class SaturationSetter:public gui::util::Label2ScrollBarSetter {
  private:
    double factor, base;
  public:
    SaturationSetter(TLabel * label, TScrollBar * scrollBar, double factor, double base)
    :gui::util::Label2ScrollBarSetter(label, scrollBar), factor(factor), base(base) {
    };
    virtual void set(TObject * sender) {
	using namespace java::lang;
	if (sender == scrollBar) {
	    int pos = scrollBar->Position - scrollBar->Max / 2;
	    double gain = (double) pos / 100. / factor;
	    double result = Math::floor(base * gain * 1000) / 1000;
	    label->Caption = FloatToStr(result);
	}
    };
    void setBase(double base) {
	this->base = base;
    }
};

//---------------------------------------------------------------------------
extern PACKAGE THSVAdjustFrame *HSVAdjustFrame;
//---------------------------------------------------------------------------
#endif

