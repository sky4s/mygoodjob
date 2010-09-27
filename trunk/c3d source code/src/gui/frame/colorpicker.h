//---------------------------------------------------------------------------


#ifndef colorpickerH
#define colorpickerH
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
class TColorPickerFrame : public TFrame
{
__published:	// IDE-managed Components
        TPageControl *pc_img;
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
private:	// User declarations
public:		// User declarations
        __fastcall TColorPickerFrame(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TColorPickerFrame *ColorPickerFrame;
//---------------------------------------------------------------------------
#endif
