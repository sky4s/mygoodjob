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

#ifndef TFunctionFormH
#define TFunctionFormH
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
#include <colorip/gui_class.h>
#include <addresstype/Address_type.h>
//�����ؤ�gui�Y���
//---------------------------------------------------------------------------



class TFunctionForm:public TForm {
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
    TCheckBox *CheckBox14;
    TLabel *Label3;
    TComboBox *ComboBox3;
    TCheckBox *CheckBox_FuncOn;
    TGroupBox *GroupBox_ManualAdjust;
    TEdit *Edit_R;
    TEdit *Edit_G;
    TEdit *Edit_B;
    TButton *Button_RAdd;
    TButton *Button_GAdd;
    TButton *Button_BAdd;
    TButton *Button_RMinus;
    TButton *Button_GMinus;
    TButton *Button_BMinus;
    TCheckBox *CheckBox_ManualEnable;
    TCheckBox *CheckBox_OrderFix;
    void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall btn_dg_wrtClick(TObject * Sender);
    void __fastcall btn_dg_readClick(TObject * Sender);
    void __fastcall btn_dg_loadClick(TObject * Sender);
    void __fastcall btn_dg_saveClick(TObject * Sender);



    void __fastcall FrcDg_CheckBox_Click(TObject * Sender);
    void __fastcall FrcDg_ComboBox_Click(TObject * Sender);
    void __fastcall FrcDg_LblEdit_KeyPress(TObject * Sender, char &Key);
    void __fastcall Btn_FRC_DG_reloadClick(TObject * Sender);

    void __fastcall FormKeyDown(TObject * Sender, WORD & Key, TShiftState Shift);
    void __fastcall CheckBox_ManualEnableClick(TObject * Sender);
    void __fastcall Button_RAddClick(TObject * Sender);
    void __fastcall Button_RMinusClick(TObject * Sender);
    void __fastcall Button_GAddClick(TObject * Sender);
    void __fastcall Button_GMinusClick(TObject * Sender);
    void __fastcall Button_BAddClick(TObject * Sender);
    void __fastcall Button_BMinusClick(TObject * Sender);


  private:			// User declarations
    static bool DG_IsChkSum;
    void adjustNumberOfEdit(TEdit * edit, bool add);
    int **generateGainDGLUT(int maxR, int maxG, int maxB);
    int **getDGLUTFromUI();
    int **getEmptyDGLUT();
    void setDGLUTToUI(int **dgLUT);
    void deleteDGLUT(int **dgLUT);

    int **manualBasedDGLUT;
    int **gainDGLUT;
  public:			// User declarations
     __fastcall TFunctionForm(TComponent * Owner);

    AbstFunc *OFunc;

    // FRC DG
    TBit *FrcDg_cb;
    _CHKB **FrcDgChkB;

    TBit *FrcDg_cbo;
    _CBOB **FrcDgCboB;

    TBit *FrcDg_lble;
    _LBLE **FrcDgLblE;



    TLUT *Addr_DgLUT;

    bool Func_Chg;		// Func_Chg = 0 ���T��g�J, Func_Chg =1 �����\�g�J, �H�קK�ʧ@�Q���_

    //================================= 20100608 ==========================
    bool DG_EN_State;		// ����DG table �� Enable���A
    int DGEN_idx;		// ����DG Enable��CheckBox��index
    bool DG_LUT_RW_start();	// ����enable���A
    void DG_LUT_RW_over();	// �^�_enable���A
    void DG_LUT_FuncEnable(bool flag);	// �]�wDG lut button�O�_�@��, flag =0 ���@��, �Ϥ�,�@��

    void Initial_DG_table();
    //=====================================================================
};
//---------------------------------------------------------------------------
extern PACKAGE TFunctionForm *FunctionForm;

//---------------------------------------------------------------------------





#endif

