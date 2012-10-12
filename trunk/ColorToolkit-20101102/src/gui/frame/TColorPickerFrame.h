//---------------------------------------------------------------------------


#ifndef TColorPickerFrameH
#define TColorPickerFrameH
#include <Buttons.hpp>
#include <Classes.hpp>
#include <ComCtrls.hpp>
#include <Controls.hpp>
#include <ExtCtrls.hpp>
#include <Forms.hpp>
#include <Graphics.hpp>
#include <StdCtrls.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------

//C系統文件

//C++系統文件
#include <vector>
//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件
#include <gui/event/listener.h>
#include <java/lang.h>
//本項目內gui頭文件
#include <gui/util/TInTargetForm.h>
//---------------------------------------------------------------------------
class TColorPickerFrame:public TFrame {
    __published:		// IDE-managed Components
    TPageControl * pc_img;
    TTabSheet *ts_image;
    TScrollBox *ScrollBox1;
    TImage *image;
    TTabSheet *ts_color;
    TImage *originalColor;
    TBitBtn *btn_img_next;
    TBitBtn *btn_img_prev;
    TTabSheet *TabSheet3;
    TImage *simulatedColor;
    TLabel *lb_c3d_showV;
    TLabel *lb_c3d_showS;
    TLabel *lb_c3d_showH;
    TLabel *lb_c3d_showB;
    TLabel *lb_c3d_showG;
    TLabel *lb_c3d_showR;
    TLabel *lb_c3d_showY;
    TLabel *lb_c3d_showX;
    TButton *btn_c3d_load_img;
    TCheckBox *cb_show_ref_img;
    TOpenDialog *OpenDialog_img;
    void __fastcall imageMouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall imageMouseDown(TObject * Sender,
				   TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall imageMouseUp(TObject * Sender,
				 TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall btn_c3d_load_imgClick(TObject * Sender);
    void __fastcall cb_show_ref_imgClick(TObject * Sender);
  private:			// User declarations
     std::vector < bwptr < gui::event::MouseMotionListener > >mouseMotionListenerVector;
     std::vector < bwptr < gui::event::MouseListener > >mouseListenerVector;
    TInTargetForm *inTargetForm;
    void setColor(TImage * image, int r, int g, int b);
    void setColor(TImage * image, TColor color);
  public:			// User declarations
     __fastcall TColorPickerFrame(TComponent * Owner);
    void addMouseMotionListener(bptr < gui::event::MouseMotionListener > listener);
    void addMouseListener(bptr < gui::event::MouseListener > listener);
    void setTInTargetForm(TInTargetForm * inTargetForm);
    void setOriginalColor(int r, int g, int b);
    void setSimulatedColor(int r, int g, int b);
};
//---------------------------------------------------------------------------
extern PACKAGE TColorPickerFrame *ColorPickerFrame;
//---------------------------------------------------------------------------
#endif

