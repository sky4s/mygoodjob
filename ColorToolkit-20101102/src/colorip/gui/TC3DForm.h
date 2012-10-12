//---------------------------------------------------------------------------
//
//   20100608 C3D table by lynne
//   can do table read/ write/ save / load/
//   in RGB or RGBW table, 10 bit or 12 bit
//   table讀寫使用 TEngineerForm::SetRead_DG 與 TEngineerForm::SetWrite_DG                                                             //
//---------------------------------------------------------------------------

#ifndef TC3DFormH
#define TC3DFormH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "TMainForm.h"
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>

#include <colorip/gui_class.h>
//---------------------------------------------------------------------------


class TC3DForm : public TForm
{
__published:	// IDE-managed Components
        TCheckBox *CheckBox1;
        TCheckBox *CheckBox2;
        TStringGrid *sg_C3D_table;
        TButton *btn_C3D_read;
        TButton *btn_C3D_wrt;
        TButton *btn_C3D_save;
        TButton *btn_C3D_load;
        TSaveDialog *SaveDialog1;
        TOpenDialog *OpenDialog1;
        TBitBtn *Btn_C3D_reload;
        TCheckBox *CheckBox3;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall CheckBox_Click(TObject *Sender);
        void __fastcall btn_C3D_readClick(TObject *Sender);
        void __fastcall btn_C3D_wrtClick(TObject *Sender);
        void __fastcall btn_C3D_saveClick(TObject *Sender);
        void __fastcall btn_C3D_loadClick(TObject *Sender);
        void __fastcall OnKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall Btn_C3D_reloadClick(TObject *Sender);

private:	// User declarations
public:		// User declarations

        __fastcall TC3DForm(TComponent* Owner);
        //TC3DForm1(int tbl_size);

        bool c3d_lutArrange();
        void Initial_C3D_table();   // initial C3D table

        //////////////////// 20100608 Record Enable Function //////////////////////////

        bool C3D_EN_State;          // 紀錄C3D table 的 Enable狀態
        int C3DEN_idx;              // 紀錄C3D Enable的CheckBox的index
        bool C3D_LUT_RW_start();    // 回復enable狀態
        void C3D_LUT_RW_over();     // 紀錄enable狀態
        void C3D_LUT_FuncEnable(bool en_flag);  // 設定C3D lut button是否作用, flag =0 不作用, 反之,作用
        //////////////////////////////////////////////////////////////////////////////

        TBit* cb;
        _CHKB** ChkB;
        TLUT* Addr_LUT;

        AbstC3D *OC3D;
        int** C3D_table;
        bool C3D_Chg;               // C3D_Chg = 0 為禁止寫入, C3D_Chg =1 為允許寫入
};
//---------------------------------------------------------------------------
extern PACKAGE TC3DForm *C3DForm;
//---------------------------------------------------------------------------
#endif
