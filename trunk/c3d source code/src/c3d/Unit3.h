//---------------------------------------------------------------------------

#ifndef Unit3H
#define Unit3H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm3 : public TForm
{
__published:	// IDE-managed Components
        TPageControl *pc_c3d_hsv_step_show;
        TTabSheet *TabSheet1;
        TImage *Image1;
        TTabSheet *TabSheet2;
        TImage *Image2;
        TLabel *Label3;
        TTabSheet *TabSheet3;
        TImage *Image3;
        TEdit *EditH;
        TEdit *EditS;
        TLabel *Label6;
        TEdit *EditV;
        TLabel *Label7;
        TLabel *Label1;
        TLabel *Label2;
        TLabel *Label4;
        TLabel *Label5;
        TLabel *Label10;
        TLabel *Label11;
        TLabel *Label12;
        TLabel *Label13;
        TLabel *Label14;
        TLabel *Label15;
        TLabel *Label8;
        TLabel *Label9;
        TLabel *Label16;
        TGroupBox *GroupBox1;
        TLabel *Label17;
        TLabel *lb_c3d_sim_H_step;
        TLabel *Label19;
        TLabel *lb_c3d_sim_S_step;
        TLabel *Label21;
        TLabel *lb_c3d_sim_V_step;
        TScrollBar *sb_c3d_sim_H_step;
        TScrollBar *sb_c3d_sim_S_step;
        TScrollBar *sb_c3d_sim_V_step;
        TLabel *Label18;
        TLabel *Label20;
        TLabel *Label22;
        TStaticText *Text_H_move;
        TStaticText *Text_S_move;
        TStaticText *Text_V_move;
        void __fastcall Image1MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image2MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall Image3MouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall sb_c3d_sim_H_stepChange(TObject *Sender);
        void __fastcall sb_c3d_sim_S_stepChange(TObject *Sender);
        void __fastcall sb_c3d_sim_V_stepChange(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm3(TComponent* Owner);
        void ResetClickAdj();        
};
//---------------------------------------------------------------------------
extern PACKAGE TForm3 *Form3;
//---------------------------------------------------------------------------
#endif
