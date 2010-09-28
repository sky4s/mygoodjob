//---------------------------------------------------------------------------

#ifndef TFormInTargetH
#define TFormInTargetH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TFormInTarget : public TForm
{
__published:	// IDE-managed Components
        TOpenDialog *OpenDialog1;
        TSaveDialog *SaveDialog1;
        TGroupBox *GroupBox1;
        TLabel *Label1;
        TLabel *Label3;
        TStringGrid *sg_rgb;
        TStringGrid *sg_hsv;
        TBitBtn *btn_rgb2hsv;
        TBitBtn *btn_hsv2rgb;
        TGroupBox *GroupBox2;
        TButton *btn_rgb2hsv_bach;
        TButton *btn_hsv2rgb_bach;
        TEdit *edt_num;
        TLabel *Label2;
        TButton *btn_sim_color;
        TScrollBox *ScrollBox1;
        TImage *img_in_target;
        void __fastcall btn_rgb2hsvClick(TObject *Sender);
        void __fastcall btn_hsv2rgbClick(TObject *Sender);
        void __fastcall btn_hsv2rgb_bachClick(TObject *Sender);
        void __fastcall btn_rgb2hsv_bachClick(TObject *Sender);
        void __fastcall btn_sim_colorClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormInTarget(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormInTarget *FormInTarget;
//---------------------------------------------------------------------------
#endif
