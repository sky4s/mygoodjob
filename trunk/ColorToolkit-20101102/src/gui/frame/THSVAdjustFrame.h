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

class CaptionIF {
  public:
    virtual String getSaturationCaption(int saturationPos) = 0;
};

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
    TButton *Button_HueReset;
    TButton *Button_SaturationReset;
    TButton *Button_BrightnessReset;
    TButton *Button_HueReturn;
    TButton *Button_SaturationReturn;
    TButton *Button_BrightnessReturn;

    void __fastcall sb_Hue_gainChange(TObject * Sender);
    void __fastcall Button_HueResetClick(TObject * Sender);
    void __fastcall Button_SaturationResetClick(TObject * Sender);
    void __fastcall Button_BrightnessResetClick(TObject * Sender);
    void __fastcall sb_Sat_gainChange(TObject * Sender);
    void __fastcall sb_Val_gainChange(TObject * Sender);

  private:			// User declarations
    //double h, s, v;
     std::vector < bwptr < gui::event::ChangeListener > >changeListenerVector;
    TStringGrid *stringGrid;
    double_array getHSVGain(double h, double s, double v, int row);
    bool settingHSVPosition;

    int defaultH, defaultS, defaultV;

    int maxHueValue;
     bptr < CaptionIF > captionIF;
  public:			// User declarations
    void updateHSVCaption();
    void sb_HSV_gainChange(TObject * Sender);
    __fastcall THSVAdjustFrame(TComponent * Owner);
    void setHSVEdit(double h, double s, double v);
    void addChangeListener(bptr < gui::event::ChangeListener > listener);
    double_array getHSVGain();
    int_array getHSVPosition();
    void setHSVPostition(int h, int s, int v);
    void setHSVPostition(int_array hsvPostition);
    void setColorAdjustable(bool enable);
    void setTStringGrid(TStringGrid * stringGrid);
    void setDefaultHSVPosition(int h, int s, int v);
    void setMaxHueValue(int maxHueValue);
    void setCaptionIF(bptr < CaptionIF > captionIF);
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

extern PACKAGE THSVAdjustFrame *HSVAdjustFrame;
//---------------------------------------------------------------------------
#endif

