//---------------------------------------------------------------------------


#ifndef TColorPickerFrameH
#define TColorPickerFrameH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TColorPickerFrame:public TFrame {
    __published:		// IDE-managed Components
    TPageControl * pc_img;
    TTabSheet *ts_image;
    TScrollBox *ScrollBox1;
    TImage *Img_3DLUT;
    TTabSheet *ts_color;
    TImage *img_color;
    TBitBtn *btn_img_next;
    TBitBtn *btn_img_prev;
    TTabSheet *TabSheet3;
    TImage *img_sim;
    TLabel *lb_c3d_showV;
    TLabel *lb_c3d_showS;
    TLabel *lb_c3d_showH;
    TLabel *lb_c3d_showB;
    TLabel *lb_c3d_showG;
    TLabel *lb_c3d_showR;
    TLabel *lb_c3d_showY;
    TLabel *lb_c3d_showX;
    TGroupBox *GroupBox44;
    TGroupBox *GroupBox34;
    TImage *Img_c3d_sel;
    TLabel *lb_c3d_selR;
    TLabel *lb_c3d_selH;
    TLabel *lb_c3d_selG;
    TLabel *lb_c3d_selB;
    TLabel *lb_c3d_selV;
    TLabel *lb_c3d_selS;
    TLabel *lb_c3d_selI;
    TLabel *Label190;
    TLabel *Label198;
    TLabel *Label202;
    TLabel *Label206;
    TLabel *Label208;
    TLabel *Label209;
    TLabel *Label213;
    TGroupBox *GroupBox45;
    TLabel *lb_c3d_simR;
    TLabel *lb_c3d_simH;
    TLabel *lb_c3d_simG;
    TLabel *lb_c3d_simB;
    TLabel *lb_c3d_simV;
    TLabel *lb_c3d_simS;
    TLabel *lb_c3d_simI;
    TLabel *Label246;
    TLabel *Label247;
    TLabel *Label248;
    TLabel *Label249;
    TLabel *Label250;
    TLabel *Label251;
    TLabel *Label252;
    TImage *Img_c3d_sim;
    void __fastcall Img_3DLUTMouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall Img_3DLUTMouseDown(TObject * Sender,
				       TMouseButton Button, TShiftState Shift, int X, int Y);
  private:			// User declarations
  public:			// User declarations
     __fastcall TColorPickerFrame(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TColorPickerFrame *ColorPickerFrame;
//---------------------------------------------------------------------------
#endif

