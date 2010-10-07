//---------------------------------------------------------------------------
//     20100608
//   1. DG table可設定為RGB或RGBW,由AbstFunc::SetDGLUT()的回傳值決定,(in Func_12401.cpp)
//   2. DG table 與OD table 讀寫之前會將GAM_EN與OD_EN Disable, 並在讀寫完畢回復
//   3. OD table 有兩種格式, 由AbstFunc::ODLUT_IP_Type()的回傳值決定,(in Func_12401.cpp)
//   4. OD table read/ write改用 TEngineerForm::SetRead_PG(TLUT, int*, bool),
//      TEngineerForm::SetWrite_PG(TLUT, int*, bool)
//   5. DG table read/ write改用TEngineerForm::SetRead_DG(TLUT*, int**, int ,bool),
//      TEngineerForm::SetWrite_PG(TLUT*, int**, int, bool)
//---------------------------------------------------------------------------

#ifndef Function1H
#define Function1H
//---------------------------------------------------------------------------

//C系統文件

//C++系統文件

//vcl庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>

#include <Grids.hpp>
#include <Dialogs.hpp>
#include <Buttons.hpp>
//其他庫頭文件

//本項目內頭文件
#include <fpga/gui_class.h>
#include <addresstype/Address_type.h>
//本項目內gui頭文件
//#include "Unit1.h"
//---------------------------------------------------------------------------

//Abstract class of FunctionForm
class AbstFunc {
  public:
    //frc_dg
    virtual TBit * SetFrcDgChkBx() = 0;
    virtual TBit *SetFrcDgCboBx() = 0;
    virtual TBit *SetFrcDgLblE() = 0;
    virtual TLUT *SetDGLUT() = 0;
    virtual String DG_EN_Name() = 0;

    //P-state
    virtual TBit *SetPstateChkBx() = 0;
    virtual TBit *SetPstateCboBx() = 0;
    virtual TBit2 *SetPstateLblE2() = 0;

    //AGBS
    virtual TBit *SetAGBSChkBx() = 0;
    virtual TBit *SetAGBSCboBx() = 0;
    virtual TBit2 *SetAGBSLblE2() = 0;

    //OD
    virtual TBit *SetODChkBx() = 0;
    virtual TBit *SetODCboBx() = 0;
    virtual TBit2 *SetODCboBx2() = 0;
    virtual TBit *SetODScrollBar() = 0;
    virtual TLUT *SetODLUT() = 0;
    virtual String OD_EN_Name() = 0;
    virtual int ODLUT_IP_Type() = 0;

    // OD table Address Arrange
    // ODLUT_IP_Type 1: AUO IP ,
    // ODLUT_IP_Type 2: Vender IP

    int PstateChkBox_Nbr;	//Number of CheckBox in Pstate page
    int PstateCboBox_Nbr;	//Number of ComboBox in Pstate page
    int PstateLblE2_Nbr;	//Number of LabeledEdit2 in Pstate page

    int AGBSChkBox_Nbr;		//Number of CheckBox in AGBS page
    int AGBSCboBox_Nbr;		//Number of ComboBox in AGBS page
    int AGBSLblE2_Nbr;		//Number of LabeledEdit2 in AGBS page

    int FrcDgChkBox_Nbr;	//Number of CheckBox in FrcDg page
    int FrcDgCboBox_Nbr;	//Number of ComboBox in FrcDg page
    int FrcDgLblE_Nbr;		//Number of LabeledEdit in FrcDg page
    int DGLUT_Nbr;

    int ODChkBox_Nbr;		//Number of CheckBox in OD page
    int ODCboBox_Nbr;		//Number of ComboBox in OD page
    int ODCboBox2_Nbr;		//Number of ComboBox2 in OD page
    int ODScrollBar_Nbr;	//Number of ScrollBar in OD page

};

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

    bool Func_Chg;		// Func_Chg = 0 為禁止寫入, Func_Chg =1 為允許寫入, 以避免動作被中斷

    //================================= 20100608 ==========================
    bool DG_EN_State;		// 紀錄DG table 的 Enable狀態
    int DGEN_idx;		// 紀錄DG Enable的CheckBox的index
    bool DG_LUT_RW_start();	// 紀錄enable狀態
    void DG_LUT_RW_over();	// 回復enable狀態
    void DG_LUT_FuncEnable(bool flag);	// 設定DG lut button是否作用, flag =0 不作用, 反之,作用

    bool OD_EN_State;		// 紀錄OD table 的 Enable狀態
    int ODEN_idx;		// 紀錄OD Enable的CheckBox的index
    bool OD_LUT_RW_start();	// 紀錄enable狀態
    void OD_LUT_RW_over();	// 回復enable狀態
    void OD_LUT_FuncEnable(bool);	// 設定OD lut button是否作用, flag =0 不作用, 反之,作用
    int ODLUT_ip_type;		// 1: AUO IP(18x18 table) , 2: Vender IP (17x17 table)
    void Initial_DG_table();
    void Initial_OD_table();
    //=====================================================================
};
//---------------------------------------------------------------------------
extern PACKAGE TFunctionForm1 *FunctionForm1;

//---------------------------------------------------------------------------





#endif

