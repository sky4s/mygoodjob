//---------------------------------------------------------------------------

#ifndef TC3D_SimualteFormH
#define TC3D_SimualteFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>

//---------------------------------------------------------------------------
class TC3DSimualteForm:public TForm {
    __published:		// IDE-managed Components
    TSaveDialog * SaveDialog1;
    TOpenDialog *OpenDialog1;
    TGroupBox *GroupBox2;
    TCheckBox *cb_record_u_want;
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TImage *Image2;
    TTabSheet *TabSheet2;
    TImage *Image3;
    TTabSheet *TabSheet3;
    TImage *Image4;
    TPageControl *pc_hsv_dif;
    TTabSheet *ts_h_diff;
    TImage *Image_h;
    TTabSheet *ts_S_diff;
    TImage *Image_s;
    TTabSheet *ts_V_diff;
    TImage *Image_v;
    TBitBtn *btn_saveHSV;
    TImage *Img_diff;
    TButton *btn_dif_save;
    TLabel *lb_hsv_dis_max;
    TPanel *Panel1;
    TGroupBox *GroupBox1;
    TLabel *Label1;
    TLabel *lb_hsv_adj_h;
    TLabel *Label2;
    TLabel *lb_hsv_adj_s;
    TLabel *Label3;
    TLabel *lb_hsv_adj_v;
    TLabel *Label4;
    TGroupBox *GroupBox9;
    TLabel *lb_c3d_showS;
    TLabel *lb_c3d_showH;
    TLabel *lb_c3d_showI;
    TLabel *lb_c3d_showV;
    TGroupBox *GroupBox4;
    TLabel *lb_c3d_showG;
    TLabel *lb_c3d_showB;
    TLabel *lb_c3d_showR;
    TGroupBox *GroupBox46;
    TLabel *lb_c3d_showY;
    TLabel *lb_c3d_showX;
    TButton *btn_img_save;
    TSaveDialog *SaveDialog_Img;
    TScrollBox *ScrollBox1;
    TImage *Image1;
    void __fastcall Image1MouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall btn_img_saveClick(TObject * Sender);
    void __fastcall Image1MouseDown(TObject * Sender,
				    TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall cb_record_u_wantClick(TObject * Sender);
    void __fastcall Image1DblClick(TObject * Sender);
    void __fastcall btn_dif_saveClick(TObject * Sender);
    void __fastcall btn_saveHSVClick(TObject * Sender);
    void __fastcall SaveDialog_ImgTypeChange(TObject * Sender);
  private:			// User declarations
  public:			// User declarations
     __fastcall TC3DSimualteForm(TComponent * Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TC3DSimualteForm *C3DSimualteForm;
//---------------------------------------------------------------------------
#endif

