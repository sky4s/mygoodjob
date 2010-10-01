//---------------------------------------------------------------------------

#ifndef TC3DFormH
#define TC3DFormH
//---------------------------------------------------------------------------

//C系統文件
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//C++系統文件

//C++系統文件

//vcl庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>
#include <Menus.hpp>
#include <ImgList.hpp>
#include <Menus.hpp>
#include "TColorPickerFrame.h"
#include "TColorFrame.h"
//其他庫頭文件

//本項目內頭文件
#include <c3d/Address_type.h>
#include <c3d/core.h>
#include <gui/event/listener.h>
//本項目內gui頭文件

#define  C3DChkBox_Nbr 2

//---------------------------------------------------------------------------


//---------------------------------------------------------------------------


class TC3DForm1:public TForm {
    __published:		// IDE-managed Components
    TCheckBox * cb_en;
    TCheckBox *cb_demo;
    TRadioGroup *rg_c3d_hsv_mode;
    TButton *btn_c3d_load;
    TButton *btn_c3d_save_h;
    TButton *btn_c3d_check;
    TGroupBox *GroupBox36;
    TRadioButton *rb_c3d_point;
    TRadioButton *rb_c3d_r;
    TRadioButton *rb_c3d_y;
    TRadioButton *rb_c3d_g;
    TRadioButton *rb_c3d_c;
    TRadioButton *rb_c3d_b;
    TRadioButton *rb_c3d_m;
    TStringGrid *sg_c3d_hsvi;
    TStaticText *StaticText34;
    TStaticText *StaticText35;
    TStaticText *StaticText36;
    TStaticText *StaticText37;
    TOpenDialog *OpenDialog1;
    TGroupBox *GroupBox38;
    TLabel *Label231;
    TLabel *lb_c3d_tbl_ir;
    TLabel *Label233;
    TLabel *lb_c3d_tbl_ig;
    TLabel *Label235;
    TLabel *lb_c3d_tbl_ib;
    TRadioGroup *rg_c3d_interpl;
    TSaveDialog *SaveDialog1;
    TButton *btn_tbl_search;
    TButton *btn_directly_sim;
    TLabeledEdit *LabeledEdit1;
    TBitBtn *BitBtn2;
    TEdit *edt_show_h;
    TRadioGroup *rg_c3d_TblSize;
    TComboBox *cb_sim_type;
    TPageControl *pc_img;
    TTabSheet *ts_image;
    TTabSheet *ts_color;
    TImage *img_color;
    TBitBtn *btn_img_next;
    TBitBtn *btn_img_prev;
    TTabSheet *TabSheet3;
    TImage *img_sim;
    TLabel *lb_c3d_showY;
    TLabel *lb_c3d_showX;
    TLabel *lb_c3d_showR;
    TLabel *lb_c3d_showG;
    TLabel *lb_c3d_showB;
    TLabel *lb_c3d_showH;
    TLabel *lb_c3d_showS;
    TLabel *lb_c3d_showV;
    TRadioGroup *rg_Sat_smooth;
    TRadioGroup *rg_v_smooth2gray;
    TPageControl *pc_Adjust;
    TTabSheet *TabSheet20;
    TTabSheet *TabSheet22;
    TTabSheet *TabSheet2;
    TStringGrid *sg_table_step;
    TBitBtn *BitBtn1;
    TButton *btn_sim_by_val;
    TButton *btn_dirSim_by_val;
    TPageControl *PageControl7;
    TTabSheet *TabSheet23;
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
    TTabSheet *TabSheet24;
    TGroupBox *GroupBox22;
    TGroupBox *GroupBox35;
    TImage *Img_c3d_tbl;
    TLabel *lb_c3d_tblR;
    TLabel *lb_c3d_tblG;
    TLabel *lb_c3d_tblB;
    TLabel *lb_c3d_tblH;
    TLabel *lb_c3d_tblS;
    TLabel *lb_c3d_tblI;
    TLabel *lb_c3d_tblV;
    TLabel *Label215;
    TLabel *Label216;
    TLabel *Label219;
    TLabel *Label220;
    TLabel *Label221;
    TLabel *Label222;
    TLabel *Label223;
    TGroupBox *GroupBox37;
    TImage *Img_c3d_cor;
    TLabel *lb_c3d_corG;
    TLabel *lb_c3d_corB;
    TLabel *lb_c3d_corH;
    TLabel *lb_c3d_corS;
    TLabel *lb_c3d_corI;
    TLabel *lb_c3d_corV;
    TLabel *lb_c3d_corR;
    TLabel *Label224;
    TLabel *Label225;
    TLabel *Label226;
    TLabel *Label227;
    TLabel *Label228;
    TLabel *Label229;
    TLabel *Label230;
    TGroupBox *GroupBox2;
    TButton *btn_c3d_reset;
    TButton *btn_c3d_load_rgb;
    TButton *btn_c3d_save_rgb;
    TGroupBox *GroupBox3;
    TButton *btn_c3d_sim;
    TBitBtn *BitBtn_c3d_undo;
    TButton *btn_c3d_write;
    TEdit *Edit1;
    TPageControl *pc_global_adj;
    TTabSheet *TabSheet7;
    TTabSheet *TabSheet8;
    TPageControl *pc_point_color_adj;
    TTabSheet *TabSheet9;
    TTabSheet *TabSheet10;
    TButton *btn_LoadRecord;
    TButton *btn_AddPoint;
    TButton *btn_SaveRecord;
    TButton *btn_DeletePoint;
    TListBox *ListBox_PointColor;
    TLabel *Label1;
    TGroupBox *gb_c3d_RGB_adj;
    TLabel *Label181;
    TLabel *lb_c3d_rgb_dis;
    TScrollBar *sb_c3d_rgb_dis;
    TStringGrid *sg_rgb_input;
    TBitBtn *btn_key_in_HSV;
    TPageControl *pc_HuePage_Grid;
    TTabSheet *ts_light12;
    TTabSheet *ts_middle12;
    TStringGrid *sg_12color2;
    TTabSheet *ts_dark6;
    TButton *btn_dark;
    TStringGrid *sg_Dark;
    TTabSheet *ts_gray9;
    TStringGrid *sg_Gray;
    TRadioGroup *rg_PCrgb_choose;
    TGroupBox *gb_PCrgb_hsv;
    TLabel *lb_c3d_hsv_v;
    TScrollBar *sb_c3d_hsv_v;
    TLabel *Label188;
    TScrollBar *sb_c3d_hsv_s;
    TLabel *lb_c3d_hsv_s;
    TLabel *lb_c3d_hsv_h;
    TScrollBar *sb_c3d_hsv_h;
    TLabel *Label186;
    TLabel *Label187;
    TGroupBox *gb_PCrgb_rgb;
    TLabel *Label182;
    TLabel *lb_c3d_rgb_r;
    TLabel *lb_c3d_rgb_g;
    TLabel *Label183;
    TLabel *Label184;
    TLabel *lb_c3d_rgb_b;
    TScrollBar *sb_c3d_rgb_r;
    TScrollBar *sb_c3d_rgb_g;
    TScrollBar *sb_c3d_rgb_b;
    TBitBtn *btn_key_in_RGB;
    TGroupBox *GroupBox1;
    TLabel *Label204;
    TLabel *Label203;
    TLabel *lb_c3d_Point_HSV_hdn;
    TLabel *Label185;
    TLabel *lb_c3d_Point_HSV_hdp;
    TLabel *Label2;
    TLabel *Label3;
    TLabel *lb_c3d_Point_HSV_svd;
    TScrollBar *sb_c3d_Point_HSV_hdn;
    TScrollBar *sb_c3d_Point_HSV_hdp;
    TScrollBar *sb_c3d_Point_HSV_svd;
    TGroupBox *gb_c3d_HSI_adj;
    TGroupBox *GroupBox40;
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
    TEdit *Edit_c3d_Manual39_v_adj;
    TScrollBar *sb_c3d_Manual39_v;
    TLabel *lb_c3d_Manual39_v;
    TLabel *Label25;
    TLabeledEdit *lbe_sat_sigma_light;
    TRadioGroup *rg_manual_39_choice;
    TGroupBox *GroupBox4;
    TLabel *lb_c3d_Point_HSV_v;
    TLabel *Label5;
    TGroupBox *GroupBox5;
    TLabel *lb_c3d_Point_HSV_h;
    TLabel *Label7;
    TScrollBar *sb_c3d_Point_HSV_h;
    TEdit *Edit_c3d_Point_HSV_h_adj;
    TGroupBox *GroupBox6;
    TLabel *lb_c3d_Point_HSV_s;
    TLabel *Label10;
    TScrollBar *sb_c3d_Point_HSV_s;
    TEdit *Edit_c3d_Point_HSV_s_adj;
    TEdit *Edit_c3d_Point_HSV_v_adj;
    TScrollBar *sb_c3d_Point_HSV_v;
    TCheckBox *cb_c3d_Point_HSV_h_g;
    TCheckBox *cb_c3d_Point_HSV_s_g;
    TCheckBox *cb_c3d_Point_HSV_v_g;
    TLabel *Label27;
    TLabel *Label28;
    TCheckBox *cb_show_ref_img;
    TPopupMenu *PopupMenu_HSV_ref_img;
    TMenuItem *c3d_Sim_Color_HSV_Step;
    TMenuItem *c3d_Sim_Image_HSV_Step;
    TStringGrid *sg_12color1;
    TEdit *edt_c3d_valC;
    TRadioGroup *rg_PointNum;
    TButton *btn_show_4_color;
    TGroupBox *GroupBox20;
    TGroupBox *GroupBox21;
    TEdit *edt_auto_rgb2xyz11;
    TEdit *edt_auto_rgb2xyz12;
    TEdit *edt_auto_rgb2xyz13;
    TEdit *edt_auto_rgb2xyz21;
    TEdit *edt_auto_rgb2xyz22;
    TEdit *edt_auto_rgb2xyz23;
    TEdit *edt_auto_rgb2xyz31;
    TEdit *edt_auto_rgb2xyz32;
    TEdit *edt_auto_rgb2xyz33;
    TGroupBox *GroupBox23;
    TLabeledEdit *lble_auto_Gm_R;
    TLabeledEdit *lble_auto_Gm_G;
    TLabeledEdit *lble_auto_Gm_B;
    TButton *btn_Auto_Src_Load;
    TButton *btn_Auto_Src_Calc;
    TGroupBox *GroupBox24;
    TButton *btn_Auto_Trg_Load;
    TGroupBox *GroupBox26;
    TLabeledEdit *LabeledEdit5;
    TButton *Button6;
    TButton *btn_Auto_Trg_BuildTbl;
    TOpenDialog *OpenDialog_xls;
    TSaveDialog *SaveDialog_xls;
    TOpenDialog *OpenDialog_img;
    TScrollBox *ScrollBox1;
    TImage *Img_3DLUT;
    TRadioGroup *rg_normal_target;
    TRadioGroup *rg_Color_Model;
    TCheckBox *CheckBox1;
    TButton *btn_c3d_load_img;
    TColorPickerFrame *TColorPickerFrame1;
        TPointColorFrame *PointColorFrame1;
    void __fastcall btn_c3d_load_imgClick(TObject * Sender);
    void __fastcall rg_c3d_interplClick(TObject * Sender);
    void __fastcall btn_c3d_simClick(TObject * Sender);
    void __fastcall rg_c3d_TblSizeClick(TObject * Sender);
    void __fastcall rb_c3d_pointClick(TObject * Sender);
    void __fastcall rb_c3d_colorClick(TObject * Sender);
    void __fastcall btn_c3d_resetClick(TObject * Sender);
    void __fastcall btn_c3d_loadClick(TObject * Sender);
    void __fastcall btn_c3d_save_hClick(TObject * Sender);
    void __fastcall btn_c3d_writeClick(TObject * Sender);
    void __fastcall sb_c3d_rgb_disChange(TObject * Sender);
    void __fastcall sb_c3d_rgb_rChange(TObject * Sender);
    void __fastcall sb_c3d_rgb_gChange(TObject * Sender);
    void __fastcall sb_c3d_rgb_bChange(TObject * Sender);
    void __fastcall sb_c3d_hsv_Change(TObject * Sender);
    void __fastcall sb_c3d_Manual39_hChange(TObject * Sender);
    void __fastcall sb_c3d_Point_HSV_hdnChange(TObject * Sender);
    void __fastcall sb_c3d_Point_HSV_hdpChange(TObject * Sender);
    void __fastcall sb_c3d_Manual39_sChange(TObject * Sender);
    void __fastcall sb_c3d_Manual39_vChange(TObject * Sender);
    void __fastcall Img_3DLUTMouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall Img_3DLUTMouseDown(TObject * Sender,
				       TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall BitBtn_c3d_undoClick(TObject * Sender);
    void __fastcall btn_c3d_checkClick(TObject * Sender);
    void __fastcall cb_enClick(TObject * Sender);
    void __fastcall CheckBox_Click(TObject * Sender);
    void __fastcall btn_c3d_load_rgbClick(TObject * Sender);
    void __fastcall btn_tbl_searchClick(TObject * Sender);
    void __fastcall btn_directly_simClick(TObject * Sender);
    void __fastcall sg_table_stepKeyDown(TObject * Sender, WORD & Key, TShiftState Shift);
    void __fastcall BitBtn1Click(TObject * Sender);
    void __fastcall BitBtn2Click(TObject * Sender);
    void __fastcall LabeledEdit1SubLabelClick(TObject * Sender);
    void __fastcall btn_sim_by_valClick(TObject * Sender);
    void __fastcall btn_dirSim_by_valClick(TObject * Sender);
    void __fastcall btn_key_in_RGBClick(TObject * Sender);
    void __fastcall btn_key_in_HSVClick(TObject * Sender);
    void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
    void __fastcall sg_12color1MouseDown(TObject * Sender,
					 TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall sg_12color2MouseDown(TObject * Sender,
					 TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall btn_c3d_save_rgbClick(TObject * Sender);
    void __fastcall sg_12color1DrawCell(TObject * Sender, int ACol,
					int ARow, TRect & Rect, TGridDrawState State);
    void __fastcall sg_12color2DrawCell(TObject * Sender, int ACol,
					int ARow, TRect & Rect, TGridDrawState State);
    void __fastcall img_colorMouseDown(TObject * Sender,
				       TMouseButton Button, TShiftState Shift, int X, int Y);
    void __fastcall img_colorMouseMove(TObject * Sender, TShiftState Shift, int X, int Y);
    void __fastcall rg_PointNumClick(TObject * Sender);
    void __fastcall btn_img_nextClick(TObject * Sender);
    void __fastcall btn_img_prevClick(TObject * Sender);
    //void __fastcall btn_ColorSetClick(TObject *Sender);
    void __fastcall btn_darkClick(TObject * Sender);
    void __fastcall lbe_sat_sigma_lightChange(TObject * Sender);
    void __fastcall sg_12color1SelectCell(TObject * Sender, int ACol, int ARow, bool & CanSelect);
    void __fastcall sg_12color2SelectCell(TObject * Sender, int ACol, int ARow, bool & CanSelect);
    void __fastcall sg_DarkDrawCell(TObject * Sender, int ACol,
				    int ARow, TRect & Rect, TGridDrawState State);
    void __fastcall sg_GrayDrawCell(TObject * Sender, int ACol,
				    int ARow, TRect & Rect, TGridDrawState State);
    void __fastcall sg_DarkSelectCell(TObject * Sender, int ACol, int ARow, bool & CanSelect);
    void __fastcall sg_GraySelectCell(TObject * Sender, int ACol, int ARow, bool & CanSelect);
    void __fastcall btn_AddPointClick(TObject * Sender);
    void __fastcall btn_DeletePointClick(TObject * Sender);
    void __fastcall btn_SaveRecordClick(TObject * Sender);
    void __fastcall btn_LoadRecordClick(TObject * Sender);
    void __fastcall ListBox_PointColorClick(TObject * Sender);
    void __fastcall sb_c3d_Point_HSV_svdChange(TObject * Sender);
    void __fastcall pc_AdjustChange(TObject * Sender);
    void __fastcall btn_show_4_colorClick(TObject * Sender);
    void __fastcall rg_PCrgb_chooseClick(TObject * Sender);
    void __fastcall rg_manual_39_choiceClick(TObject * Sender);
    void __fastcall pc_global_adjChange(TObject * Sender);
    void __fastcall c3d_Sim_Color_HSV_StepClick(TObject * Sender);
    void __fastcall c3d_Sim_Image_HSV_StepClick(TObject * Sender);
    void __fastcall sb_c3d_Point_HSV_hChange(TObject * Sender);
    void __fastcall sb_c3d_Point_HSV_sChange(TObject * Sender);
    void __fastcall sb_c3d_Point_HSV_vChange(TObject * Sender);
    void __fastcall cb_show_ref_imgClick(TObject * Sender);
    void __fastcall pc_imgChange(TObject * Sender);
    void __fastcall btn_Auto_Src_LoadClick(TObject * Sender);
    void __fastcall btn_Auto_Src_CalcClick(TObject * Sender);
    void __fastcall btn_Auto_Trg_LoadClick(TObject * Sender);
    void __fastcall btn_Auto_Trg_BuildTblClick(TObject * Sender);
    void __fastcall SaveDialog1TypeChange(TObject * Sender);
        void __fastcall TColorPickerFrame1cb_show_ref_imgClick(
          TObject *Sender);

  private:			// User declarations

     class ColorMouseListener:public gui::event::MouseListener {
	const TC3DForm1 *parent;
      public:
	 ColorMouseListener(TC3DForm1 * parent);
	virtual void mousePressed(TObject * Sender,
				  TMouseButton Button, TShiftState Shift, int X, int Y);
	virtual void mouseReleased(TObject * Sender,
				   TMouseButton Button, TShiftState Shift, int X, int Y);
    };
    bptr < ColorMouseListener > colorMouseListener;

  public:			// User declarations
    __fastcall TC3DForm1(TComponent * Owner);
    __fastcall ~ TC3DForm1();
    double ***c3d_lutR, ***c3d_lutG, ***c3d_lutB;
    double ***c3d_lutH, ***c3d_lutS, ***c3d_lutV, ***c3d_lutI;
    double ***tmp_c3d_lutR, ***tmp_c3d_lutG, ***tmp_c3d_lutB, ***tmp_c3d_lutH, ***tmp_c3d_lutS,
	***tmp_c3d_lutV;
    double **PointColor_array;
    int PointColor_array_nbr;
    bool interpol;		//true: techehedral, false: trilinear
    bool fl_ref_HSV_img_col;	// reference HSV adjust with image(0) or color(1)

    TBit *cb;
    _CHKB **ChkB;
    TLUT *lut;
    _CHKB en;
    bool C3D_Chg;
    void cal_c3d_rgb(bool flg_wri);
    void C3Dsim(double r, double g, double b, double *r_new, double *g_new, double *b_new);
    void C3Dsim_t(double r, double g, double b, double *r_new, double *g_new, double *b_new);
    void Show_c3d_CorImg(double cor_r, double cor_g, double cor_b);
    void Show_c3d_SimImg(double sim_r, double sim_g, double sim_b);
    void refresh_6axis_grid(double r, double g, double b);
    void refresh_6axis_grid_t(double r, double g, double b);
    void c3d_grid(int c, int r, int g, int b);
    void c3d_tmp_tbl_save();
    void c3d_scrollbar_reset();
    void C3Dini();
    void Show_c3d_TblImg(double tbl_r, double tbl_g, double tbl_b);
    void Show_c3d_SelImg(double sel_r, double sel_g, double sel_b);
    void Show_c3d_Img_sim();

    bool c3d_lutArrange();
    void new_array();
    void delete_array();

    double GetH_val();
    void SetH_caption(double H);

    void Adjust_H_diffusion(double H);
    int Get_Point_H_NegDif();
    int Get_Point_H_PosDif();
    double GetPointH_val();
    void SetPointH_caption(double H);

    int GetS_val();
    void SetS_Caption();
    int GetPointS_val();
    void SetPointS_Caption();

    void SetV_Caption();
    int GetV_val();
    void SetPointV_Caption();
    int GetPointV_val();

    //method 2
    /*  void c3d_6axisAdj_h(bool flag);
       void c3d_6axisAdj_s(bool flag);
       void c3d_6axisAdj_v(bool flag);
     */

    //method 1
    void c3d_hsvBase_adj(bool flg_wri);
    void c3d_HSVBase_h_adj();
    void c3d_HSVBase_s_adj();
    void c3d_HSVBase_v_adj();

    //methid 3
    void c3d_MixAdj_h(bool flag);
    void c3d_MixAdj_s(bool flag);
    void c3d_MixAdj_v(bool flag);
    void Direct_sim(double r, double g, double b, double *r_new, double *g_new, double *b_new);
    void c3d_MixAdj_r(int type, double dif_p, double dif_n, double gain);
    //method 4
    void c3d_hsv_FixGain_h(double tmp_c3d_lutH[9][9][9]);
    void c3d_hsv_FixGain(bool flg_wri);

    void calculate_HSV_disc();
    void calculate_disc();
    void calculate_NCTU_dif();
    void Caculate_dif_table(double ***c3d_dif_lutR, double ***c3d_dif_lutG, double ***c3d_dif_lutB,
			    double ***c3d_dif, int modif);
    void C3Dsim_dif(double r, double g, double b, double *r_new, double *g_new, double *b_new,
		    double ***c3d_dif);

    void Load_c3d_table(String Fpath);
    void Save_c3d_table(String Fpath);

    void Set_Adj_Color(double r, double g, double b);
    void PointAdjust_1(int idx_r, int idx_g, int idx_b);
    void PointAdjust_4();
    void Modif_Point(int color, double gain1, double gain2, double gain3, bool fl_ranh);
    void PointAdjust_m();

    void Manual39_color_adj(bool flg_wri);
    void Manual39_light(double h, double s, double v, double col[3]);
    void Manual39_dark(double h, double s, double v, double col[3]);
    void Manual39_mid(double h, double s, double v, double col[3]);

    void ShowSelectCell(int ARow, double r, double g, double b, TStringGrid * sg);
    void ShowImageColor(TImage * img, double r, double g, double b);
    void Set_HuePageStringGrid(TStringGrid * sg);
    void set_c3d_color_grid(int grid_num, int c, int r, int g, int b);

    void SmoothValue_2Gray(double s, double v, double *col);
    void SmoothSaturation(double s, double gain, double *col);
    void Record_Move(int i_r, int i_g, int i_b, double r, double g, double b);

    void ColorSet();
    void Point_HSV_Bar_Move();
    void Manual39_HSV_Bar_Move();

    void Reset_c3d_Point_RGB_Scroll();
    void Reset_c3d_Point_HSV_Scroll();
    void Ini_c3d_table();
    void Refresh_Manual39_Point();
    void Refresh_PointColor_rgb(double r, double g, double b);
    void refresh_c3d_color_grid();

    void c3d_lutAssign();


};

//---------------------------------------------------------------------------
extern PACKAGE TC3DForm1 *C3DForm1;
//---------------------------------------------------------------------------

void TC3DForm1::Reset_c3d_Point_HSV_Scroll()
{
    sb_c3d_Point_HSV_h->Position = sb_c3d_Point_HSV_h->Max / 2;
    sb_c3d_Point_HSV_s->Position = sb_c3d_Point_HSV_s->Max / 2;
    sb_c3d_Point_HSV_v->Position = sb_c3d_Point_HSV_v->Max / 2;
}

//----------------------------------------------------------------------------
// 將調整用的ScrollBar設為初始值
// 包括Point Color的R,G,B,H,S,V, 與 Hue Page的H,S,V
void TC3DForm1::c3d_scrollbar_reset()
{
    sb_c3d_rgb_dis->Position = 0;
    Reset_c3d_Point_RGB_Scroll();
    Reset_c3d_Point_HSV_Scroll();
}

void TC3DForm1::Reset_c3d_Point_RGB_Scroll()
{
    //sb_c3d_rgb_dis->Position = 0;
    sb_c3d_rgb_r->Position = sb_c3d_rgb_r->Max / 2;
    sb_c3d_rgb_g->Position = sb_c3d_rgb_g->Max / 2;
    sb_c3d_rgb_b->Position = sb_c3d_rgb_b->Max / 2;
    sb_c3d_hsv_h->Position = sb_c3d_hsv_h->Max / 2;
    sb_c3d_hsv_s->Position = sb_c3d_hsv_s->Max / 2;
    sb_c3d_hsv_v->Position = sb_c3d_hsv_v->Max / 2;
    // sb_c3d_hsv_i->Position = sb_c3d_hsv_i->Max/2;
}

void fix_val(double *value, double upbound)
{
    if (*value < 0)
	*value = 0;
    else if (*value > upbound)
	*value = upbound;
}
void c3d_Aratio(int i_r, int i_g, int i_b, double *rat, int d)
{
    double tmp;
    *rat = d;
    for (int i = i_r; i <= i_r + 1; i++)
	for (int j = i_g; j <= i_g + 1; j++)
	    for (int k = i_b; k <= i_b + 1; k++) {
		if (sqrt(double (i * i + j * j + k * k)) < d) {
		    tmp = sqrt(double (i * i + j * j + k * k));
		    *rat = (*rat > tmp ? tmp : *rat);
		}
	    }
}

char *Load_File(String Fpath)
{
    long lSize;
    char *buffer;
    FILE *fptr;
    if ((fptr = fopen(Fpath.c_str(), "r")) == NULL)
	return 0;

    // obtain file size:
    fseek(fptr, 0, SEEK_END);
    lSize = ftell(fptr);
    rewind(fptr);

    // allocate memory to contain the whole file:
    buffer = (char *) malloc(sizeof(char) * lSize);
    if (buffer == NULL)
	return 0;
    // copy the file into the buffer:
    fread(buffer, 1, lSize, fptr);
    fclose(fptr);
    return buffer;
}

#endif

