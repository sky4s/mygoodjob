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
#include <Grids.hpp>
//其他庫頭文件

//本項目內頭文件
#include <gui/util/binder.h>
#include <gui/event/listener.h>
//本項目內gui頭文件
//---------------------------------------------------------------------------

class HueSetter;
class SaturationSetter;

class THSVAdjustFrame:public TFrame {
    __published:		// IDE-managed Components
    TGroupBox * GroupBox40;
        TLabel *lb_Hue_gain;
    TLabel *Label197;
    TScrollBar *sb_Hue_gain;
    TEdit *Edit_c3d_Manual39_h_adj;
    TGroupBox *GroupBox41;
        TLabel *lb_Sat_gain;
    TLabel *Label207;
    TScrollBar *sb_Sat_gain;
    TEdit *edt_c3d_satC;
    TEdit *Edit_c3d_Manual39_s_adj;
    TGroupBox *GroupBox7;
        TLabel *lb_Val_gain;
    TLabel *Label25;
    TScrollBar *sb_Val_gain;
    TEdit *Edit_c3d_Manual39_v_adj;
    TEdit *edt_c3d_valC;
    void __fastcall sb_Hue_gainChange(TObject * Sender);
    void __fastcall sb_Sat_gainChange(TObject * Sender);
    void __fastcall sb_Val_gainChange(TObject * Sender);
  private:			// User declarations
    double h, s, v;
     std::vector < bwptr < gui::event::ChangeListener > >changeListenerVector;
    TStringGrid *stringGrid;
    double_array getHSVGain(double h, double s, double v, int row);
  public:			// User declarations
     __fastcall THSVAdjustFrame(TComponent * Owner);
    void setHSV(double h, double s, double v);
    void addChangeListener(bptr < gui::event::ChangeListener > listener);
    double_array getHSVGain();
    void setColorAdjustable(bool enable);
    void setTStringGrid(TStringGrid * stringGrid);
};

class SelectionListener:public gui::event::ListSelectionListener {
  private:
    THSVAdjustFrame * parent;
  public:
    SelectionListener(THSVAdjustFrame * parent):parent(parent) {
    };
    virtual void valueChanged(TObject * Sender, int ACol, int ARow, bool & CanSelect) {
    };
};

/*class HueSetter:public gui::util::Label2ScrollBarSetter {
  private:
    THSVAdjustFrame * parent;
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
}; */

extern PACKAGE THSVAdjustFrame *HSVAdjustFrame;
//---------------------------------------------------------------------------
#endif

