//---------------------------------------------------------------------------
//
//   20100608 C3D table by lynne
//   can do table read/ write/ save / load/
//   in RGB or RGBW table, 10 bit or 12 bit
//   tableŪ�g�ϥ� TEngineerForm::SetRead_DG �P TEngineerForm::SetWrite_DG                                                             //
//---------------------------------------------------------------------------

#ifndef C3D1H
#define C3D1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "Unit1.h"
#include <Grids.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
#include <colorip/gui_class.h>
//---------------------------------------------------------------------------
class AbstC3D
{
        public:
                virtual TBit* SetChkBx()=0;
                virtual TLUT* SetLUT()=0;
                virtual String C3D_EN_Name()=0;  // 20100608 return the name of C3D enable register
                int C3DChkBox_Nbr;
                int C3DLUT_Nbr;
};


class TC3D999Form1 : public TForm
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

        __fastcall TC3D999Form1(TComponent* Owner);

        bool c3d_lutArrange();
        void Initial_C3D_table();   // initial C3D table

        //////////////////// 20100608 Record Enable Function //////////////////////////

        bool C3D_EN_State;          // ����C3D table �� Enable���A
        int C3DEN_idx;              // ����C3D Enable��CheckBox��index
        bool C3D_LUT_RW_start();    // �^�_enable���A
        void C3D_LUT_RW_over();     // ����enable���A
        void C3D_LUT_FuncEnable(bool en_flag);  // �]�wC3D lut button�O�_�@��, flag =0 ���@��, �Ϥ�,�@��
        //////////////////////////////////////////////////////////////////////////////

        TBit* cb;
        _CHKB** ChkB;
        TLUT* Addr_LUT;

        AbstC3D *OC3D;
        int** C3D_table;
        bool C3D_Chg;               // C3D_Chg = 0 ���T��g�J, C3D_Chg =1 �����\�g�J
        int **c3d_r, **c3d_g, **c3d_b;
        bool C3D_IsChkSum = 1;
        int TBL_SIZE;
        //double Ratio;
        int tbl_s;
        int tbl_val[4][33]
};
//---------------------------------------------------------------------------
extern PACKAGE TC3D999Form1 *C3D999Form1;
//---------------------------------------------------------------------------
#endif
