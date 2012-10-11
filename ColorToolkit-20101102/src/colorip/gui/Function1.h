//---------------------------------------------------------------------------
//     20100608
//   1. DG table�i�]�w��RGB��RGBW,��AbstFunc::SetDGLUT()���^�ǭȨM�w,(in Func_12401.cpp)
//   2. DG table �POD table Ū�g���e�|�NGAM_EN�POD_EN Disable, �æbŪ�g�����^�_
//   3. OD table ����خ榡, ��AbstFunc::ODLUT_IP_Type()���^�ǭȨM�w,(in Func_12401.cpp)
//   4. OD table read/ write��� TEngineerForm::SetRead_PG(TLUT, int*, bool),
//      TEngineerForm::SetWrite_PG(TLUT, int*, bool)
//   5. DG table read/ write���TEngineerForm::SetRead_DG(TLUT*, int**, int ,bool),
//      TEngineerForm::SetWrite_PG(TLUT*, int**, int, bool)
//---------------------------------------------------------------------------

#ifndef Function1H
#define Function1H
//---------------------------------------------------------------------------

//C�t�Τ��

//C++�t�Τ��

//vcl�w�Y���
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

#include <Grids.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
//��L�w�Y���

//�����ؤ��Y���
#include <fpga/gui_class.h>
#include <addresstype/Address_type.h>
//�����ؤ�gui�Y���
//---------------------------------------------------------------------------



class TFunctionForm1:public TForm {
    __published:		// IDE-managed Components
    TOpenDialog * LoadDialog;
    TSaveDialog *SaveDialog;
    TPageControl *pc_Function;
    TTabSheet *ts_frc_gamma;
    TGroupBox *GroupBox1;
    TCheckBox *CheckBox5;
    TCheckBox *CheckBox6;
    TCheckBox *CheckBox7;
    TGroupBox *GroupBox2;
    TStringGrid *sg_dg;
    TButton *btn_dg_read;
    TButton *btn_dg_wrt;
    TButton *btn_dg_save;
    TButton *btn_dg_load;
    TCheckBox *CheckBox8;
    TCheckBox *CheckBox9;
    TBitBtn *Btn_FRC_DG_reload;
    TTabSheet *ts_p_state;
    TLabel *Label1;
    TCheckBox *CheckBox1;
    TCheckBox *CheckBox2;
    TComboBox *ComboBox1;
    TLabeledEdit *LabeledEdit1;
    TLabeledEdit *LabeledEdit2;
    TLabeledEdit *LabeledEdit3;
    TLabeledEdit *LabeledEdit4;
    TBitBtn *Btn_Pstate_reload;
    TTabSheet *ts_agbs;
    TCheckBox *CheckBox3;
    TCheckBox *CheckBox4;
    TLabeledEdit *LabeledEdit5;
    TLabeledEdit *LabeledEdit6;
    TLabeledEdit *LabeledEdit7;
    TBitBtn *Btn_AGBS_reload;
    TTabSheet *TabSheet1;
    TPageControl *PageControl2;
    TTabSheet *TabSheet6;
    TTabSheet *TabSheet7;
    TCheckBox *CheckBox10;
    TCheckBox *CheckBox11;
    TCheckBox *CheckBox12;
    TLabel *Label4;
    TLabel *Label5;
    TLabel *Label6;
    TLabel *Label7;
    TComboBox *ComboBox4;
    TComboBox *ComboBox5;
    TComboBox *ComboBox6;
    TComboBox *ComboBox7;
    TLabel *Label8;
    TLabel *Label9;
    TLabel *Label10;
    TScrollBar *ScrollBar3;
    TScrollBar *ScrollBar2;
    TScrollBar *ScrollBar1;
    TStaticText *StaticText1;
    TStaticText *StaticText2;
    TStaticText *StaticText3;
    TBitBtn *Btn_OD_reload;
    TPageControl *OD;
    TTabSheet *TabSheet4;
    TStringGrid *sg_od_1;
    TTabSheet *TabSheet5;
    TStringGrid *sg_od_2;
    TButton *btn_od_read;
    TButton *btn_od_write;
    TButton *btn_od_load;
    TButton *btn_od_save;
    TLabel *Label13;
    TLabel *Label14;
    TLabel *Label15;
    TLabel *Label16;
    TRadioGroup *rg_od_table_type;
    TCheckBox *CheckBox13;
    TCheckBox *CheckBox14;
    TLabel *Label3;
    TComboBox *ComboBox3;
    TCheckBox *CheckBox_FuncOn;
    void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall btn_dg_wrtClick(TObject * Sender);
    void __fastcall btn_dg_readClick(TObject * Sender);
    void __fastcall btn_dg_loadClick(TObject * Sender);
    void __fastcall btn_dg_saveClick(TObject * Sender);

    void __fastcall Pstate_CheckBox_Click(TObject * Sender);
    void __fastcall Pstate_ComboBox_Click(TObject * Sender);
    void __fastcall Pstate_LblEdit2_KeyPress(TObject * Sender, char &Key);

    void __fastcall AGBS_CheckBox_Click(TObject * Sender);
    void __fastcall AGBS_ComboBox_Click(TObject * Sender);
    void __fastcall AGBS_LblEdit2_KeyPress(TObject * Sender, char &Key);

    void __fastcall OD_CheckBox_Click(TObject * Sender);
    void __fastcall OD_ComboBox_Click(TObject * Sender);
    void __fastcall OD_ComboBox2_Click(TObject * Sender);
    void __fastcall OD_ScrollBar_Scroll(TObject * Sender, TScrollCode ScrollCode, int &ScrollPos);

    void __fastcall FrcDg_CheckBox_Click(TObject * Sender);
    void __fastcall FrcDg_ComboBox_Click(TObject * Sender);
    void __fastcall FrcDg_LblEdit_KeyPress(TObject * Sender, char &Key);
    void __fastcall Btn_FRC_DG_reloadClick(TObject * Sender);
    void __fastcall Btn_Pstate_reloadClick(TObject * Sender);
    void __fastcall Btn_AGBS_reloadClick(TObject * Sender);
    void __fastcall Btn_OD_reloadClick(TObject * Sender);
    void __fastcall FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift);
    void __fastcall btn_od_readClick(TObject * Sender);
    void __fastcall btn_od_writeClick(TObject * Sender);
    void __fastcall btn_od_loadClick(TObject * Sender);
    void __fastcall btn_od_saveClick(TObject * Sender);
    void __fastcall rg_od_table_typeClick(TObject * Sender);

  private:			// User declarations
    static bool DG_IsChkSum;
    static bool OD_IsChkSum;
  public:			// User declarations
     __fastcall TFunctionForm1(TComponent * Owner);

    AbstFunc *OFunc;

    //P-state parameter declare
    TBit *Pstate_cb;
    _CHKB **PstateChkB;

    TBit *Pstate_cbo;
    _CBOB **PstateCboB;

    TBit2 *Pstate_lble2;
    _LBLE2 **PstateLblE2;

    //Aging Bist parameter declare
    TBit *AGBS_cb;
    _CHKB **AGBSChkB;

    TBit *AGBS_cbo;
    _CBOB **AGBSCboB;

    TBit2 *AGBS_lble2;
    _LBLE2 **AGBSLblE2;

    // FRC DG
    TBit *FrcDg_cb;
    _CHKB **FrcDgChkB;

    TBit *FrcDg_cbo;
    _CBOB **FrcDgCboB;

    TBit *FrcDg_lble;
    _LBLE **FrcDgLblE;

    //OD
    TBit *OD_cb;
    _CHKB **ODChkB;

    TBit *OD_cbo;
    _CBOB **ODCboB;

    TBit2 *OD_cbo2;
    _CBOB2 **ODCboB2;

    TBit *OD_ScrlB;
    _ScrollBar **ODScrlB;

    TLUT *Addr_DgLUT;

    TLUT *Addr_ODLUT;
    TLUT *Addr_ODLUT1;
    TLUT *Addr_ODLUT2;

    bool Func_Chg;		// Func_Chg = 0 ���T��g�J, Func_Chg =1 �����\�g�J, �H�קK�ʧ@�Q���_

    //================================= 20100608 ==========================
    bool DG_EN_State;		// ����DG table �� Enable���A
    int DGEN_idx;		// ����DG Enable��CheckBox��index
    bool DG_LUT_RW_start();	// ����enable���A
    void DG_LUT_RW_over();	// �^�_enable���A
    void DG_LUT_FuncEnable(bool flag);	// �]�wDG lut button�O�_�@��, flag =0 ���@��, �Ϥ�,�@��

    bool OD_EN_State;		// ����OD table �� Enable���A
    int ODEN_idx;		// ����OD Enable��CheckBox��index
    bool OD_LUT_RW_start();	// ����enable���A
    void OD_LUT_RW_over();	// �^�_enable���A
    void OD_LUT_FuncEnable(bool);	// �]�wOD lut button�O�_�@��, flag =0 ���@��, �Ϥ�,�@��
    int ODLUT_ip_type;		// 1: AUO IP(18x18 table) , 2: Vender IP (17x17 table)
    void Initial_DG_table();
    void Initial_OD_table();
    //=====================================================================
};
//---------------------------------------------------------------------------
extern PACKAGE TFunctionForm1 *FunctionForm1;

//---------------------------------------------------------------------------





#endif

