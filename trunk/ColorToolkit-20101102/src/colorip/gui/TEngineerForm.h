//---------------------------------------------------------------------------
//   20100608
//   1. 修正USB Sequential read/ write
//   2. 連續的讀寫動作, 由SetRead_PG, SetWrite_PG, SetRead_DG, SetWrite_DG完成,
//      後兩者為DG與C3D使用,(for RGB or RGBW table)
//   3. 連續的讀寫動作, 可以參數IsChkSum決定是否讀寫Checksum,
//      1為讀寫checksum, 0不讀寫
//   4. Table type 的轉換由class RW_Func完成, 定義在"table_type.h"
//---------------------------------------------------------------------------

#ifndef TEngineerFormH
#define TEngineerFormH
//---------------------------------------------------------------------------




#include "TMainForm.h"

//C系統文件
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//C++系統文件

//vcl庫頭文件
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include <jpeg.hpp>
#include <Graphics.hpp>
#include <Dialogs.hpp>
#include <String.h>
#include <Dialogs.hpp>
#include <windows.h>
//其他庫頭文件

//本項目內頭文件

//本項目內gui頭文件
#include <gui/framework/RegisterFramework.h>
#include <colorip/gui_class.h>
#include "table_type.h"
//---------------------------------------------------------------------------
/*=========================================================================
//   DCR table reverse at 20090804 by lynnelin
//
/=========================================================================*/


class TEngineerForm:public TForm {
    __published:		// IDE-managed Components
    TPageControl * PageControl1;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TGroupBox *GroupBox1;
    TImage *Img_LPT_04T;
    TImage *Img_LPT_06T;
    TImage *Img_usb;
    TGroupBox *gb_USB_set;
    TRadioGroup *rg_speed;
    TRadioGroup *rg_power;
    TRadioGroup *rg_i2c_card_sel;
    TGroupBox *GroupBox2;
    TLabel *Label1;
    TLabel *Label3;
    TRadioGroup *rg_device_addr_sel;
    TEdit *edt_addr_tcon_s;
    TComboBox *cbo_mem_addr_size;
    TEdit *edt_addr_tcon_dm;
    TEdit *edt_addr_tcon_ds;
    TEdit *edt_addr_EEP;
    TBitBtn *btn_en_ftm;
    TGroupBox *gb_byte_write;
    TLabeledEdit *edt_byte_rdata;
    TLabeledEdit *edt_byte_addr;
    TLabeledEdit *edt_byte_wdata;
    TBitBtn *btn_byte_read;
    TBitBtn *btn_byte_write;
    TGroupBox *GroupBox3;
    TBitBtn *btn_seq_write;
    TBitBtn *btn_seq_read;
    TLabeledEdit *edt_seq_addr;
    TLabeledEdit *edt_seq_len;
    TBitBtn *btn_seq_load;
    TBitBtn *btn_seq_save;
    TStringGrid *sg_device_addr;
    TOpenDialog *OpenDialog_txt_hex;
    TSaveDialog *SaveDialog_txt_hex;
    TBitBtn *btn_connect_card;
    TGroupBox *GroupBox4;
    TRadioGroup *rg_w_page;
    TBitBtn *btn_soft_reset;
    TRadioGroup *rg_w_cycl_t;
    TMemo *Memo3;
    TGroupBox *GroupBox5;
    TButton *btn_page_read;
    TButton *btn_page_write;
    TButton *btn_page_save;
    TButton *btn_page_load;
    TStatusBar *stb_page_operat;
    TBitBtn *btn_reload;
    TGroupBox *GroupBox6;
    TButton *btn_LPT_spd;
    TStaticText *st_lpt_speed;
    TCheckBox *cb_low_freq;
    TEdit *edt_addr_OTP;
    TButton *btn_byte_read_no_ack;
    TLabel *Label2;
    TStringGrid *sg_seq_data;
    void __fastcall FormCreate(TObject * Sender);
    void __fastcall FormClose(TObject * Sender, TCloseAction & Action);
    void __fastcall btn_byte_readClick(TObject * Sender);
    void __fastcall rg_i2c_card_selClick(TObject * Sender);
    void __fastcall btn_byte_writeClick(TObject * Sender);
    void __fastcall btn_connect_cardClick(TObject * Sender);
    void __fastcall btn_seq_writeClick(TObject * Sender);
    void __fastcall btn_seq_readClick(TObject * Sender);
    void __fastcall PageControl1Exit(TObject * Sender);
    void __fastcall btn_soft_resetClick(TObject * Sender);
    void __fastcall cbo_mem_addr_sizeChange(TObject * Sender);
    void __fastcall rg_device_addr_selClick(TObject * Sender);
    void __fastcall edt_addr_tcon_sChange(TObject * Sender);
    void __fastcall edt_addr_tcon_dmChange(TObject * Sender);
    void __fastcall edt_addr_tcon_dsChange(TObject * Sender);
    void __fastcall edt_addr_EEPChange(TObject * Sender);
    void __fastcall btn_seq_loadClick(TObject * Sender);
    void __fastcall btn_seq_saveClick(TObject * Sender);
    void __fastcall btn_en_ftmClick(TObject * Sender);
    void __fastcall btn_reloadClick(TObject * Sender);
    void __fastcall rg_powerClick(TObject * Sender);
    void __fastcall rg_speedClick(TObject * Sender);
    void __fastcall btn_page_writeClick(TObject * Sender);
    void __fastcall btn_page_readClick(TObject * Sender);
    void __fastcall btn_page_saveClick(TObject * Sender);
    void __fastcall btn_page_loadClick(TObject * Sender);
    void __fastcall btn_LPT_spdClick(TObject * Sender);
    void __fastcall cb_low_freqClick(TObject * Sender);
    void __fastcall edt_addr_OTPChange(TObject * Sender);
    void __fastcall btn_byte_read_no_ackClick(TObject * Sender);
    void __fastcall SaveDialog_txt_hexSelectionChange(TObject * Sender);

  private:			// User declarations
    char *LoadFile(String Fpath, int *len);
    bool Dec2Hex(int val, AnsiString * str);
    bool Hex2Dec(AnsiString str, int *val);
    bool connect;
    String Connect_Msg;
    RW_Func RW;
// 20100608 新增, 詳細內容寫在'table_type.h'
    ReadWrite_LUT RW_LUT;
// decode / encode data in difference Table type, Defined in table_type.h
    //bool Read_LUT(TLUT Addr_LUT, IntTbl & Out, ByteTbl In);
    //bool Write_LUT(TLUT Addr_LUT, ByteTbl & Out, IntTbl In);

    //=========================================================================
    // basic io function
    //=========================================================================
    bool Get_byte_addr(unsigned char *data_addr, int *data_addr_cnt);
    bool Get_device_addr(unsigned char *dev, int *dev_addr_cnt);
    bool Get_device_addr(int *dev_ad);
    bool Get_write_data(unsigned char *write_data);
    bool Get_seq_addr(unsigned char *data_addr, int *data_addr_cnt);
    void Get_seq_write_data(unsigned char *data, int data_len);
    bool Set_seq_data(unsigned char *data_read, int data_len, int data_addr_val);

    bool SetDeviceAddr(unsigned char dev_ad, unsigned char *dev_ad_new,
		       unsigned char *data_ad, int data_ad_c);
    void dev_addr_change(TObject * Sender);
    bool Get_read_data(unsigned char *read_data);
    bool B_read(unsigned char &data_read, unsigned char dev_addr);
    bool B_write(unsigned char dev_addr);
    //=========================================================================

    //=========================================================================
    // pg write function
    //=========================================================================
    bool USB_pg_write(unsigned char dev_ad, unsigned char *data_addr,
		      int data_addr_cnt, unsigned char *data_write,
		      int data_len, int pck_size, int wait_t);
    //USB Page Write, Split to package (for EEPROM)
    bool USB_seq_pg_write(unsigned char dev_ad, unsigned char *data_addr,
			  int data_addr_cnt, unsigned char *data_write,
			  int data_len, int pck_size, int wait_t);
    //USB Sequential, no split to packages
    bool LPT_pg_write(unsigned char dev_ad, unsigned char *data_addr,
		      int data_addr_cnt, unsigned char *data_write,
		      int data_len, int pck_size, int wait_t);
    bool pg_read(unsigned char *read, bool IsShow);
    bool pg_write();
    //=========================================================================

    void Clear_sg_seq_data();
    bool btn_byte_readClick();




  public:			// User declarations
     __fastcall TEngineerForm(TComponent * Owner);
     __fastcall ~ TEngineerForm(void);

    //=========================================================================
    // public io function
    //=========================================================================
    //for byte, 只有TBit, 其他type需要手動拆回TBit才能進行rw
    bool SetWrite_Byte(TBit & Addr_Bit, int set_val);
    bool SetRead_Byte(TBit & Addr_Bit, unsigned char *read_val);
    //modified by skyforce
    unsigned char readByte(TBit & Addr_Bit);

    //for lut
    //write只有用到TLUT撈meta, 實際寫入的資料是write table
    bool SetWrite_PG(TLUT Addr_LUT, int *write_table, bool IsChkSum);
    bool SetWrite_PG(TLUT Addr_LUT, int *write_table, bool IsChkSum, bool MSB_first);
    //read到table去
    bool SetRead_PG(TLUT Addr_LUT, int *table, bool IsChkSum);

    //
    bool SetRead_DG(TLUT * Addr_LUT, int **DG_table, int LUT_Nbr, bool IsChkSum);
    bool SetWrite_DG(TLUT * Addr_LUT, int **lut, int LUT_Nbr, bool IsChkSum, bool MSB_first);
    bool SetWrite_DG(TLUT * Addr_LUT, int **lut, int LUT_Nbr, bool IsChkSum);

    //new io
    int_array readRegister(BitRegister_ptr reg);
    //void writeRegister(BitRegister_ptr reg);
    int_array readLUT();
    void writeLUT();
    //=========================================================================]

    static String *Load_file(String Fpath, int Lut_no);


};
//---------------------------------------------------------------------------
extern PACKAGE TEngineerForm *EngineerForm;

//---------------------------------------------------------------------------

//--------------------------------------------------------------------------


#endif

