//---------------------------------------------------------------------------

#ifndef HueSatValH
#define HueSatValH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Unit1.h"
#include "Engineering.h"
#include <Buttons.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
#include <Grids.hpp>

//---------------------------------------------------------------------------
class AbstHSV
{
        public:
                virtual TBit SetEn()=0;
                virtual TBit* SetChkBx()=0;
                virtual TLUT* SetLUT()=0;
                int HSVChkBox_Nbr;
};

class THSVForm1 : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TGroupBox *GroupBox1;
        TCheckBox *cb_en;
        TCheckBox *CheckBox1;
        TRadioGroup *rg_HSV_Mode;
        TButton *btn_HSV_load;
        TButton *btn_HSV_save;
        TGroupBox *GroupBox29;
        TLabel *Label111;
        TCheckBox *cb_Hue_Red;
        TStringGrid *sg_Hue_Sat_val;
        TCheckBox *cb_Hue_Green;
        TCheckBox *cb_Hue_Blue;
        TCheckBox *cb_Hue_Mag;
        TCheckBox *cb_Hue_Yellow;
        TCheckBox *cb_Hue_Cyan;
        TStaticText *StaticText31;
        TStaticText *StaticText32;
        TStaticText *StaticText33;
        TEdit *ed_Hue_Custom;
        TButton *btn_Hue_Img_load;
        TGroupBox *GroupBox28;
        TGroupBox *GroupBox30;
        TLabel *Label136;
        TLabel *lb_Hue_gain;
        TLabel *Label132;
        TLabel *lb_Hue_dif_n;
        TLabel *lb_Hue_dif_p;
        TLabel *Label192;
        TLabel *Label193;
        TScrollBar *sb_Hue_gain;
        TBitBtn *btn_set_hue;
        TScrollBar *sb_Hue_dif_n;
        TButton *btn_reset_hue;
        TScrollBar *sb_Hue_dif_p;
        TCheckBox *cb_Hue_rotation;
        TGroupBox *GroupBox27;
        TLabel *Label139;
        TLabel *lb_Sat_gain;
        TLabel *Label140;
        TLabel *lb_Sat_dif_n;
        TLabel *lb_Sat_dif_p;
        TLabel *Label191;
        TLabel *Label194;
        TLabel *Label195;
        TScrollBar *sb_Sat_gain;
        TBitBtn *btn_set_sat;
        TScrollBar *sb_Sat_dif_n;
        TScrollBar *sb_Sat_dif_p;
        TButton *btn_reset_sat;
        TCheckBox *cb_Sat_glb;
        TGroupBox *GB_HSV_Val;
        TLabel *Label189;
        TLabel *lb_Val_gain;
        TLabel *Label196;
        TLabel *lb_Val_dif_n;
        TLabel *lb_Val_dif_p;
        TLabel *Label199;
        TLabel *Label200;
        TLabel *Label201;
        TScrollBar *sb_Val_gain;
        TBitBtn *btn_set_val;
        TScrollBar *sb_Val_dif_n;
        TButton *btn_reset_val;
        TScrollBar *sb_Val_dif_p;
        TCheckBox *cb_Val_glb;
        TStringGrid *sg_HSV_table;
        TBitBtn *Btn_HSV_reload;
        TStaticText *Hue_Img_Infor;
        TImage *Hue_Img;
        TLabeledEdit *le_ChAangle;
        void __fastcall cb_Hue_RedClick(TObject *Sender);
        void __fastcall cb_Hue_YellowClick(TObject *Sender);
        void __fastcall cb_Hue_GreenClick(TObject *Sender);
        void __fastcall cb_Hue_BlueClick(TObject *Sender);
        void __fastcall cb_Hue_CyanClick(TObject *Sender);
        void __fastcall cb_Hue_MagClick(TObject *Sender);
        void __fastcall ed_Hue_CustomChange(TObject *Sender);
        void __fastcall btn_HSV_loadClick(TObject *Sender);
        void __fastcall btn_HSV_saveClick(TObject *Sender);
        void __fastcall btn_set_hueClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall CheckBox_Click(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall Hue_ImgMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall btn_reset_hueClick(TObject *Sender);
        void __fastcall btn_set_satClick(TObject *Sender);
        void __fastcall btn_reset_satClick(TObject *Sender);
        void __fastcall btn_set_valClick(TObject *Sender);
        void __fastcall btn_reset_valClick(TObject *Sender);
        void __fastcall sb_Hue_dif_nChange(TObject *Sender);
        void __fastcall sb_Hue_dif_pChange(TObject *Sender);
        void __fastcall sb_Sat_dif_nChange(TObject *Sender);
        void __fastcall sb_Sat_dif_pChange(TObject *Sender);
        void __fastcall sb_Val_dif_nChange(TObject *Sender);
        void __fastcall sb_Val_dif_pChange(TObject *Sender);
        void __fastcall sb_Hue_gainScroll(TObject *Sender,
          TScrollCode ScrollCode, int &ScrollPos);
        void __fastcall sb_Sat_gainScroll(TObject *Sender,
          TScrollCode ScrollCode, int &ScrollPos);
        void __fastcall sb_Val_gainChange(TObject *Sender);
        void __fastcall cb_enClick(TObject *Sender);
        void __fastcall btn_Hue_Img_loadClick(TObject *Sender);
        void __fastcall rg_HSV_ModeClick(TObject *Sender);
        void __fastcall Btn_HSV_reloadClick(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
private:	// User declarations
public:		// User declarations
        TBit* cb;
        _CHKB** ChkB;
        TLUT* lut_addr;
        _CHKB en;

        AbstHSV *OHSV;
        int Hue_table[96];
        int Sat_table[96];
        int Val_table[96];
        bool HSV_Chg;

        __fastcall THSVForm1(TComponent* Owner);
        void Reset_HSVshow();
        //bool Load_HSIini(String Fpath);
        void Hue_LUTWrite();
        void Initial_HSV_table();
        bool Load_HSV(String Fpath);
};

void rgb2hsv(double r, double g, double b, double *h, double *s, double *i, double *v)
{
        r = (int)r;
        g = (int)g;
        b = (int)b;
        *i = (r+g+b)/3;
        double max = (r>g?r:g);
        max = (b>max?b:max);
        *v = max;
        double min = (r<g?r:g);
        min = (min<b?min:b);
        double d = max-min;
        *s = d;
        d = (d==0?d+256:d);

        if(s==0)
                *h = 0;
        else if(max==r)
                *h = 60*(g-b)/d;
        else if(max==g)
                *h = 60*(b-r)/d+120;
        else if(max==b)
                *h = 60*(r-g)/d+240;
        *h = fmod(*h+360,360);
        if(max==0)
                *s = 0;
        else
                *s = *s/max;
}
//--------------------------------------------------------------------------

//---------------------------------------------------------------------------
extern PACKAGE THSVForm1 *HSVForm1;
//---------------------------------------------------------------------------
#endif
