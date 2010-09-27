//---------------------------------------------------------------------------

#ifndef EngineeringH
#define EngineeringH
//---------------------------------------------------------------------------
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
#include "ReadWriteFunc.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <String.h>
#include <Dialogs.hpp>
#include <windows.h>
#include <time.h>
//#include "Unit1.h"
#include <gui\c3d\TMainForm.h>
//---------------------------------------------------------------------------
/*=========================================================================
//   DCR table reverse at 20090804 by lynnelin
//
/=========================================================================*/

class TEngineerForm : public TForm
{
__published:	// IDE-managed Components
        TPageControl *PageControl1;
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
        TStringGrid *sg_seq_data;
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
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall btn_byte_readClick(TObject *Sender);
        void __fastcall rg_i2c_card_selClick(TObject *Sender);
        void __fastcall btn_byte_writeClick(TObject *Sender);
        void __fastcall btn_connect_cardClick(TObject *Sender);
        void __fastcall btn_seq_writeClick(TObject *Sender);
        void __fastcall btn_seq_readClick(TObject *Sender);
        void __fastcall PageControl1Exit(TObject *Sender);
        void __fastcall btn_soft_resetClick(TObject *Sender);
        void __fastcall cbo_mem_addr_sizeChange(TObject *Sender);
        void __fastcall rg_device_addr_selClick(TObject *Sender);
        void __fastcall edt_addr_tcon_sChange(TObject *Sender);
        void __fastcall edt_addr_tcon_dmChange(TObject *Sender);
        void __fastcall edt_addr_tcon_dsChange(TObject *Sender);
        void __fastcall edt_addr_EEPChange(TObject *Sender);
        void __fastcall btn_seq_loadClick(TObject *Sender);
        void __fastcall btn_seq_saveClick(TObject *Sender);
        void __fastcall btn_en_ftmClick(TObject *Sender);
        void __fastcall btn_reloadClick(TObject *Sender);
        void __fastcall rg_powerClick(TObject *Sender);
        void __fastcall rg_speedClick(TObject *Sender);
        void __fastcall btn_page_writeClick(TObject *Sender);
        void __fastcall btn_page_readClick(TObject *Sender);
        void __fastcall btn_page_saveClick(TObject *Sender);
        void __fastcall btn_page_loadClick(TObject *Sender);
        void __fastcall btn_LPT_spdClick(TObject *Sender);
        void __fastcall cb_low_freqClick(TObject *Sender);
        void __fastcall edt_addr_OTPChange(TObject *Sender);
        void __fastcall btn_byte_read_no_ackClick(TObject *Sender);
        void __fastcall SaveDialog_txt_hexSelectionChange(TObject *Sender);

private:	// User declarations
public:		// User declarations
        __fastcall TEngineerForm(TComponent* Owner);
        __fastcall ~TEngineerForm(void);
        bool Get_byte_addr(unsigned char* data_addr, int* data_addr_cnt);
        bool Get_device_addr(unsigned char* dev, int *dev_addr_cnt);
        bool Get_device_addr(int* dev_ad);
        bool Get_write_data(unsigned char *write_data);
        bool Get_seq_addr(unsigned char* data_addr, int* data_addr_cnt);
        void Get_seq_write_data(unsigned char* data, int data_len);
        bool Set_seq_data(unsigned char* data_read, int data_len, int data_addr_val);
        bool SetDeviceAddr(unsigned char dev_ad, unsigned char* dev_ad_new, unsigned char* data_ad, int data_ad_c);
        void dev_addr_change(TObject *Sender);
        bool Get_read_data(unsigned char *read_data);
        bool USB_pg_write(unsigned char dev_ad, unsigned char* data_addr, int data_addr_cnt,
                unsigned char* data_write, int data_len, int pck_size, int wait_t);
        bool LPT_pg_write(unsigned char dev_ad, unsigned char* data_addr, int data_addr_cnt,
                unsigned char* data_write, int data_len, int pck_size, int wait_t);
        void wait(long milli);
        unsigned char B_read();
        bool B_write();
        bool pg_write();
        bool SetWrite_Byte(TBit Bit, int set_val);
        bool SetRead_Byte(TBit Addr_Bit, unsigned char* read_val);
        bool SetWrite_PG(TLUT Addr_LUT, int* lut, int length);
        bool SetRead_DG(TLUT Addr_LUT,int* DG_table, int length);
        bool pg_read(unsigned char* read, bool IsShow);
        bool SetRead_DCR(TLUT Addr_LUT,unsigned char* read_data, int length);
        bool SetRead_OD(TLUT Addr_LUT, int* OD_table, int length);
        String* Load_file(String Fpath, int Lut_no);
        bool SetRead_CM(TLUT Addr_LUT,int* CM, int length);
        bool SetRead_CMofs(TLUT Addr_LUT,float* ofs, int length);
        bool SetRead_SP(TLUT Addr_LUT,int* SP, int length);
        bool SetRead_PG(TLUT Addr_LUT,int* table, int length);
        void Clear_sg_seq_data();
};
//---------------------------------------------------------------------------
extern PACKAGE TEngineerForm *EngineerForm;

//---------------------------------------------------------------------------
bool Hex2Dec(AnsiString str, int* val)
{
        char* dataByte = str.c_str();    //take input string into char* array
        *val = 0;
        int len = str.Length();
        if( len == 0)
                return 0;
        for(int i = 0; i < len; i++){
                if(dataByte[i] >='0' && dataByte[i] <='9'){
                        *val = *val*16 + (unsigned int)(dataByte[i] - '0');
                }else{
                        if(dataByte[i] >='a' && dataByte[i] <='f')
                                *val = *val*16 + (unsigned int)(dataByte[i] - 'a' + 10);
                        else if(dataByte[i] >='A' && dataByte[i] <='F')
                                *val = *val*16 + (unsigned int)(dataByte[i] - 'A' + 10);
                        else if(dataByte[i] !=NULL && dataByte[i] !=' ')
                                return 0;
                }
        }

        //delete [] dataByte;
        return 1;
}

bool Dec2Hex(int val, AnsiString *str)
{
        char string[4];
        sprintf( string,"%02X", val );
        *str = (AnsiString)string;
        return 1;
}
//---------------------------------------------------------------------------

char* LoadFile(String Fpath, int* len)
{
        long lSize;
        char* buffer="";
        FILE* fptr;
        if((fptr = fopen(Fpath.c_str(),"r"))==NULL)
                return NULL;
       
         // obtain file size:
        fseek (fptr , 0 , SEEK_END);
        lSize = ftell (fptr);
        rewind (fptr);

        // allocate memory to contain the whole file:
        buffer = new char [lSize];
        int n = 0;
        if(buffer == "")
                return NULL;
        else{
                while (!feof(fptr)) {
                        buffer[n] = fgetc (fptr);
                        n++;
                }
        }
        fclose(fptr);
        *len = n;
        return buffer;
}

struct WRITE_PG{
        int addr;
        unsigned char* Wrt_data;
        int lut_num;
};
//---------------------------------------------------------------------------
bool Write_LUT(int* LUT, int Lut_num, TLUT Addr_LUT, WRITE_PG *write_pg)
{
        write_pg->addr = -1;
        write_pg->Wrt_data = NULL;
        write_pg->lut_num = -1;

        write_pg->addr = Addr_LUT.Addr();
        int b_num = Addr_LUT.BitNum();
        int type = Addr_LUT.Type();
        unsigned char *LUT_W;
        if(b_num == 10){
                if(type == 1){     //CM 10 bit [9:2],[1:0]
                        LUT_W = new unsigned char[Lut_num*2];
                        for(int i = 0; i < Lut_num; i++){
                                LUT_W[i*2] = LUT[i]/4;
                                LUT_W[i*2+1] = LUT[i]%4*64;
                        }
                        write_pg->Wrt_data = LUT_W;
                        write_pg->lut_num = Lut_num*2;
                }else if(type == 2){    //CM 10bit [9:8](at low bit)  [7:0]
                        LUT_W = new unsigned char [Lut_num*2];
                        for(int i = 0; i < Lut_num; i++){
                                LUT_W[i*2] = LUT[i]/256;
                                LUT_W[i*2+1] = LUT[i]%256;
                        }
                        write_pg->Wrt_data = LUT_W;
                        write_pg->lut_num = Lut_num*2;
                }else if(type == 3){       //DG 10 bit
                        int remain = Lut_num % 4;
                        int Byte_num = ceil((double)Lut_num*5/4);
                        LUT_W = new unsigned char [Byte_num];
                        int lut_num = Lut_num-remain;
                        int idx;
                        for(int i = 0; i < lut_num; i+=4){
                                idx = (int)floor((double)i/4)*5;
                                LUT_W[idx] = LUT[i]/4;
                                LUT_W[idx+1] = LUT[i]%4*64+LUT[i+1]/16;
                                LUT_W[idx+2] = LUT[i+1]%16*16+LUT[i+2]/64;
                                LUT_W[idx+3] = LUT[i+2]%64*4+LUT[i+3]/256;
                                LUT_W[idx+4] = LUT[i+3]%256;
                        }
                        if(remain==1){
                                idx = (int)floor((double)lut_num/4)*5;
                                LUT_W[idx] = LUT[lut_num]/4;
                                LUT_W[idx+1] = LUT[lut_num]%4*64;
                        }else if(remain==2){
                                idx = (int)floor((double)lut_num/4)*5;
                                LUT_W[idx] = LUT[lut_num]/4;
                                LUT_W[idx+1] = LUT[lut_num]%4*64+LUT[lut_num+1]/16;
                                LUT_W[idx+2] = LUT[lut_num+1]%16*16;
                        }else if(remain==3){
                                idx = (int)floor((double)lut_num/4)*5;
                                LUT_W[idx] = LUT[lut_num]/4;
                                LUT_W[idx+1] = LUT[lut_num]%4*64+LUT[lut_num+1]/16;
                                LUT_W[idx+2] = LUT[lut_num+1]%16*16+LUT[lut_num+2]/64;
                                LUT_W[idx+3] = LUT[lut_num+2]%64*4;
                        }
                        write_pg->Wrt_data = LUT_W;
                        write_pg->lut_num = Byte_num;
                }
        }else if(b_num==12){
                if(type == 1){      //DG 12 bit //3D LUT
                        int remain = Lut_num % 2;
                        int Byte_num = ceil((double)Lut_num*3/2);
                        LUT_W = new unsigned char [Byte_num];
                        int idx = 0;
                        if(remain>0)
                                Lut_num -= 1;
                        for(int i = 0; i < Lut_num; i=i+2){
                                LUT_W[idx] = LUT[i]%256;
                                LUT_W[idx+1] = LUT[i+1]%16*16+LUT[i]/256;
                                LUT_W[idx+2] = LUT[i+1]/16;
                                idx += 3;
                        }
                        if(remain==1){
                                LUT_W[Byte_num-2] = LUT[Lut_num]%256;
                                LUT_W[Byte_num-1] = LUT[Lut_num]/256;
                        }
                        write_pg->Wrt_data = LUT_W;
                        write_pg->lut_num = Byte_num;
                }else if(type == 2){      //DCR DIM LUT (因為BL table為8 bit, 實際使用的code在dcr1.cpp)
                        int remain = Lut_num % 2;
                        int Byte_num = ceil((double)Lut_num*3/2);
                        LUT_W = new unsigned char [Byte_num];
                        int idx = 0;
                        if(remain>0)
                                Lut_num -= 1;
                        for(int i = 0; i < Lut_num; i=i+2){
                                LUT_W[idx] = LUT[i]/16;
                                LUT_W[idx+1] = LUT[i]%16*16+LUT[i+1]/256;
                                LUT_W[idx+2] = LUT[i+1]%256;
                                idx += 3;
                        }
                        if(remain==1){
                                LUT_W[Byte_num-2] = LUT[Lut_num]/16;
                                LUT_W[Byte_num-1] = LUT[Lut_num]%16*16;
                        }
                        write_pg->Wrt_data = LUT_W;
                        write_pg->lut_num = Byte_num;
                }
        }else if(b_num==8){        //
                write_pg->Wrt_data = new unsigned char [Addr_LUT.LutNum()];
                for(int i = 0; i < Addr_LUT.LutNum();i++)
                        write_pg->Wrt_data[i] = (unsigned char)LUT[i];
                write_pg->lut_num = Lut_num;
        }else if(b_num==4 && type == 1){        //SP_LUT
                int Byte_num = Lut_num/2;
                LUT_W = new unsigned char [Byte_num];
                for (int i = 0; i < Byte_num; i++){
                        LUT_W[i] = LUT[i*2]+ LUT[i*2+1]*16;
                }
                write_pg->Wrt_data = LUT_W;
                write_pg->lut_num = Byte_num;
        }else if(b_num==4 && type == 2){        //SP_LUT
                LUT_W = new unsigned char [Lut_num];
                for (int i = 0; i < Lut_num; i++){
                        LUT_W[i] = LUT[i]%16;
                }
                write_pg->Wrt_data = LUT_W;
                write_pg->lut_num = Lut_num;
        }else if(b_num==6 && type == 1){        //SP_LUT
                LUT_W = new unsigned char [Lut_num];
                for (int i = 0; i < Lut_num; i++){
                        LUT_W[i] = LUT[i]%64;
                }
                write_pg->Wrt_data = LUT_W;
                write_pg->lut_num = Lut_num;
        }else{
                return 0;
        }
        return 1;
}

//--------------------------------------------------------------------------


#endif
