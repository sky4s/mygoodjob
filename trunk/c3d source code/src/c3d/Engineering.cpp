//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Engineering.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define PAC_SIZE 56

TEngineerForm *EngineerForm;
RW_Func RW;
bool connect = false;
//---------------------------------------------------------------------------
__fastcall TEngineerForm::TEngineerForm(TComponent* Owner)
        : TForm(Owner)
{

}
__fastcall TEngineerForm::~TEngineerForm()
{

}
//---------------------------------------------------------------------------
void __fastcall TEngineerForm::FormCreate(TObject *Sender)
{
        int val;
        AnsiString tmp = "7c";
        Hex2Dec(tmp, &val);
        //StringGrid of device address
        char str[5];
        for(int i = 0; i < 7 ; i++){
                sprintf(str, "%d", (int)((double)val/pow(2,7-i))%2);
                sg_device_addr->Cells[i][0] = (AnsiString)str;
        }
        sg_device_addr->Cells[7][0] = "RW";

        //StringGrid of sequence R/W data show
        for(int i = 0; i <= 15 ; i++){
                sprintf(str, "%02X",i);
                sg_seq_data->Cells[i+1][0] = (AnsiString)str;
        }

}
//---------------------------------------------------------------------------

void __fastcall TEngineerForm::FormClose(TObject *Sender, TCloseAction &Action)
{
        Action = caFree;
        RW.USB_disconnect();
        if(hLib!=NULL)
                LPT_disconnect();
}
//--------------------------------------------------------------------------

bool TEngineerForm::Get_byte_addr(unsigned char* data_addr, int* data_addr_cnt)
{
        AnsiString dataString = edt_byte_addr->Text;
        if(dataString.Length() > 4 || dataString.Length()==0 ){
                ShowMessage("Too many digits on device address.");
        }else{
                unsigned short dataVal;
                int val;
                if(Hex2Dec(dataString,&val)==0)
                        return 0;
                dataVal = val;
                data_addr[1] = dataVal/256;     //high bit
                data_addr[0] = dataVal%256;     //low bit
                int data_addr_len;
                if(cbo_mem_addr_size->ItemIndex <=3)
                        data_addr_len = 1;
                else if( cbo_mem_addr_size->ItemIndex <= 8)
                        data_addr_len = 2;
                *data_addr_cnt = data_addr_len-1;
        }

        return 1;
}
//---------------------------------------------------------------------------------
bool TEngineerForm::Get_seq_addr(unsigned char* data_addr, int* data_addr_cnt)
{
        AnsiString dataString = edt_seq_addr->Text;
        if(dataString.Length() > 4 || dataString.Length()==0 ){
                ShowMessage("Too many or few digits on device address.");
        }else{
                unsigned short dataVal;
                int val;
                if(Hex2Dec(dataString,&val)==0)
                        return 0;
                dataVal = val;
                data_addr[1] = dataVal/256;     //high bit
                data_addr[0] = dataVal%256;     //low bit
                int data_addr_len;
                if(cbo_mem_addr_size->ItemIndex <=3)
                        data_addr_len = 1;
                else if( cbo_mem_addr_size->ItemIndex <= 8)
                        data_addr_len = 2;
                *data_addr_cnt = data_addr_len-1;
        }
        return 1;
}

//--------------------------------------------------------------------------
bool TEngineerForm::Get_device_addr(unsigned char* dev, int *dev_addr_cnt)
{
        bool ok;
        int val;
        if(rg_device_addr_sel->ItemIndex==0){       //single TCON
                *dev_addr_cnt = 1;
                ok = Hex2Dec(edt_addr_tcon_s->Text,&val);
                dev[0] = (unsigned char)val;
        }else if(rg_device_addr_sel->ItemIndex==1){       //dual TCON
                *dev_addr_cnt = 2;
                ok = Hex2Dec(edt_addr_tcon_dm->Text,&val);
                dev[0] = (unsigned char)val;
                bool ok1 = Hex2Dec(edt_addr_tcon_ds->Text,&val);
                ok = ok & ok1;
                dev[1] = (unsigned char)val;
        }else if(rg_device_addr_sel->ItemIndex==2){       //single EEPROM
                *dev_addr_cnt = 1;
                ok = Hex2Dec(edt_addr_EEP->Text,&val);
                dev[0] = (unsigned char)val;
        }else if(rg_device_addr_sel->ItemIndex==3){
                *dev_addr_cnt = 1;
                ok = Hex2Dec(edt_addr_OTP->Text,&val);
                dev[0] = (unsigned char)val;
        }else //may add quad-TCON here
                return 0;

        return 1;
}
//--------------------------------------------------------------------------
bool TEngineerForm::B_write()
{
        int sel;
        unsigned char dev_addr[4];       int dev_addr_cnt;
        unsigned char data_addr[2];      int data_addr_cnt;
        unsigned char write_data;
        bool card_sel;

        if(Get_byte_addr(data_addr, &data_addr_cnt)==0){
                ShowMessage("Please enter a Byte address.");
                return 0;
        }

        if(Get_device_addr(dev_addr, &dev_addr_cnt)==0){
                ShowMessage("Please choose a device address.");
                return 0;
        }

        if(Get_write_data(&write_data)==0){
                ShowMessage("Please enter a byte to write.");
                return 0;
        }

        int ok = 1;
        unsigned char dev_addr_tmp;
        for(int i = 0; i < dev_addr_cnt; i++){
                SetDeviceAddr(dev_addr[i], &dev_addr_tmp, data_addr, data_addr_cnt);
                if(rg_i2c_card_sel->ItemIndex == 0)
                        RW.USB_write(dev_addr_tmp, data_addr, data_addr_cnt, &write_data, 1);
                else{
                        ok = RW.LPT_Write(dev_addr_tmp, data_addr, data_addr_cnt, &write_data, 1);
                        if(ok!=1){
                                if(ok==-1)
                                        ShowMessage("Device address Send fail!");
                                else if(ok==-2)
                                        ShowMessage("Data address Send fail!");
                                else if(ok==0)
                                        ShowMessage("Data Send fail!");
                                return 0;
                        }
                }
        }
        if(rg_device_addr_sel->ItemIndex==2)
                Sleep(11);
        return 1;
}

//--------------------------------------------------------------------------
unsigned char TEngineerForm::B_read()
{
        unsigned char dev_addr[4];
        //device read/write address, extend to 4 devices set at a time

        unsigned char data_addr[2];     //Word address, may be 1 or 2 Byte
        unsigned char data_read; //data read
        int data_addr_cnt;      //number of byte in data address
        int dev_addr_cnt;       //number of device

        if(Get_byte_addr(data_addr, &data_addr_cnt)==0){
                ShowMessage("Please enter a Byte address.");
                return NULL;
        }

        if(Get_device_addr(dev_addr, &dev_addr_cnt)==0){
                ShowMessage("Please choose a device address.");
                return NULL;
        }
        int ok=1;
        unsigned char dev_addr_tmp;
        for(int i = 0; i < dev_addr_cnt; i++){
                SetDeviceAddr(dev_addr[i], &dev_addr_tmp, data_addr, data_addr_cnt);
                if(rg_i2c_card_sel->ItemIndex == 0)
                        connect = RW.USB_read(dev_addr_tmp, data_addr, data_addr_cnt, &data_read, 1);
                else{
                        ok = RW.LPT_Read_Byte(dev_addr_tmp, data_addr, data_addr_cnt, &data_read);
                        if(ok!=1){
                                if(connect){
                                        if(ok==-1)
                                                ShowMessage("Device address Send fail!");
                                        else if(ok==-2)
                                                ShowMessage("Data address Send fail!");
                                        else if(ok==0)
                                                ShowMessage("Data Send fail!");
                                }
                                return 0;
                        }else
                                connect=1;
                }
        }
        return data_read;
}

//--------------------------------------------------------------------------
bool TEngineerForm::SetRead_Byte(TBit Addr_Bit, unsigned char* read_val)
{
        AnsiString str_addr;
        Dec2Hex(Addr_Bit.Addr(), &str_addr);
        edt_byte_addr->Text = str_addr;
        *read_val = B_read();
        *read_val = *read_val & ~(Addr_Bit.StbBit());
        *read_val = *read_val >> Addr_Bit.ShiftBit();
        return 1;
}

//--------------------------------------------------------------------------
bool TEngineerForm::SetWrite_Byte(TBit Addr_Bit, int set_val)
{
        AnsiString str_addr;
        Dec2Hex(Addr_Bit.Addr(), &str_addr);
        edt_byte_addr->Text = str_addr;
        unsigned char t_data = B_read();
        t_data = t_data & Addr_Bit.StbBit();
        set_val = set_val & (int)pow(2,Addr_Bit.BitNum())-1;
        t_data = t_data | (set_val<<Addr_Bit.ShiftBit());
        AnsiString str;
        Dec2Hex((int)t_data, &str);
        edt_byte_wdata->Text = str;
        if(B_write())
                return 1;
        else
                return 0;
}

//---------------------------------------------------------------------------
bool TEngineerForm::SetRead_OD(TLUT Addr_LUT, int* OD_table, int length)
{
        String Addr_str;
        Dec2Hex(Addr_LUT.Addr(), &Addr_str);
        edt_seq_addr->Text = Addr_str;
        length = Addr_LUT.LutNum();
        edt_seq_len->Text = IntToStr(length);

        int data_len = StrToInt(edt_seq_len->Text);
        unsigned char* read_data_tmp = new unsigned char [data_len];
        bool ok = pg_read(read_data_tmp,1);

        for(int i = 0; i <data_len; i++)
                OD_table[i] = (int)read_data_tmp[i];

        delete [] read_data_tmp;
        if(ok ==0 | OD_table == NULL)
                return 0;
        return 1;
}
//---------------------------------------------------------------------------
bool TEngineerForm::SetRead_CMofs(TLUT Addr_LUT,float* ofs, int length)
{
        String Addr_str;
        Dec2Hex(Addr_LUT.Addr(), &Addr_str);
        edt_seq_addr->Text = Addr_str;
        edt_seq_len->Text = IntToStr(length*2);

        int data_len = StrToInt(edt_seq_len->Text);
        unsigned char* read_data_tmp = new unsigned char [data_len];
        bool ok = pg_read(read_data_tmp,1);

        int* read_data = new int [data_len];
        for(int i = 0; i <data_len; i++)
                read_data[i] = (int)read_data_tmp[i];

        int type = Addr_LUT.Type();
        if(type == 1){     //CM 10 bit [9:2],[1:0]
                for(int i = 0; i < length; i++)
                        ofs[i] = read_data[2*i]+read_data[2*i+1]*4;
        }else if(type == 2 || type == 4){    //CM 10bit [9:8](at low bit)  [7:0]
                for(int i = 0; i < length; i++)
                        ofs[i] = read_data[2*i]*256+read_data[2*i+1];
        }
        delete [] read_data;
        delete [] read_data_tmp;
        if(ok ==0 | ofs == NULL)
                return 0;
        return 1;
}
//---------------------------------------------------------------------------
bool TEngineerForm::SetRead_CM(TLUT Addr_LUT,int* CM, int length)
{
        String Addr_str;
        Dec2Hex(Addr_LUT.Addr(), &Addr_str);
        edt_seq_addr->Text = Addr_str;
        edt_seq_len->Text = IntToStr(length*2);

        int data_len = StrToInt(edt_seq_len->Text);
        unsigned char* read_data_tmp = new unsigned char [data_len];
        bool ok = pg_read(read_data_tmp,1);

        int* read_data = new int [data_len];
        for(int i = 0; i <data_len; i++)
                read_data[i] = (int)read_data_tmp[i];

        int type = Addr_LUT.Type();
        if(type == 1){     //CM 10 bit [9:2],[1:0]
                for(int i = 0; i < length; i++)
                        CM[i] = read_data[2*i]+read_data[2*i+1]*4;
        }else if(type == 2 || type == 4){    //CM 10bit [9:8](at low bit)  [7:0]
                for(int i = 0; i < length; i++)
                        CM[i] = read_data[2*i]*256+read_data[2*i+1];
        }
        delete [] read_data;
        delete [] read_data_tmp;
        if(ok ==0 | CM == NULL)
                return 0;
        return 1;
}
//---------------------------------------------------------------------------
bool TEngineerForm::SetRead_SP(TLUT Addr_LUT,int* SP, int length)
{
        String Addr_str;
        Dec2Hex(Addr_LUT.Addr(), &Addr_str);
        edt_seq_addr->Text = Addr_str;
        edt_seq_len->Text = IntToStr(length);

        int data_len = StrToInt(edt_seq_len->Text);
        unsigned char* read_data_tmp = new unsigned char [data_len];
        bool ok = pg_read(read_data_tmp,1);

        int* read_data = new int [data_len];
        for(int i = 0; i <data_len; i++)
                read_data[i] = (int)read_data_tmp[i];

        for(int i = 0; i < length; i++)
                SP[i] = read_data[i]%64;

        delete [] read_data;
        delete [] read_data_tmp;
        if(ok ==0 | SP == NULL)
                return 0;
        return 1;
}
//---------------------------------------------------------------------------
bool TEngineerForm::SetRead_PG(TLUT Addr_LUT,int* table, int length)
{
        String Addr_str;
        Dec2Hex(Addr_LUT.Addr(), &Addr_str);
        edt_seq_addr->Text = Addr_str;
        edt_seq_len->Text = IntToStr(length);

        unsigned char* read_data_tmp = new unsigned char [length];
        bool ok = pg_read(read_data_tmp,1);

        for(int i = 0; i <length; i++)
                table[i] = (int)read_data_tmp[i];

        delete [] read_data_tmp;
        if(ok ==0 | table == NULL)
                return 0;
        return 1;
}
//---------------------------------------------------------------------------
bool TEngineerForm::SetRead_DG(TLUT Addr_LUT,int* DG_table, int length)
{
        String Addr_str;
        Dec2Hex(Addr_LUT.Addr(), &Addr_str);
        edt_seq_addr->Text = Addr_str;
        if(Addr_LUT.BitNum()==10)
                length = ceil((double)Addr_LUT.LutNum()*5/4);
        else if(Addr_LUT.BitNum()==12)
                length = ceil((double)Addr_LUT.LutNum()*3/2);
        else
                length = Addr_LUT.LutNum();
        edt_seq_len->Text = IntToStr(length);

        int data_len = StrToInt(edt_seq_len->Text);
        unsigned char* read_data_tmp = new unsigned char [data_len];
        bool ok = pg_read(read_data_tmp,1);

        int* read_data = new int [data_len];
        for(int i = 0; i <data_len; i++)
                read_data[i] = (int)read_data_tmp[i];

        for(int i = 0; i < Addr_LUT.LutNum(); i++)
                DG_table[i] = 0;
        int idx;
        int n_idx=0;
        if(Addr_LUT.BitNum() == 10){
                idx = ceil((double)Addr_LUT.LutNum()*5/4);
                for(int i = 0; i < idx; i+=5){
                        n_idx = floor((double)i/5*4);
                        DG_table[n_idx] = read_data[i]*4+read_data[i+1]/64;
                        DG_table[n_idx+1] = read_data[i+1]%64*16+read_data[i+2]/16;
                        DG_table[n_idx+2] = read_data[i+2]%16*64+read_data[i+3]/4;
                        DG_table[n_idx+3] = read_data[i+3]%4*256+read_data[i+4];
                }
        }else if(Addr_LUT.BitNum() == 12){
                idx = ceil((double)Addr_LUT.LutNum()*3/2);
                n_idx = 0;
                for(int i = 0; i < idx; i+=3,n_idx+=2){
                        DG_table[n_idx] = read_data[i]+read_data[i+1]%16*256;
                        if(n_idx+1<Addr_LUT.LutNum())
                                DG_table[n_idx+1] =read_data[i+1]/16;
                        if(i+2<idx){
                                DG_table[n_idx+1] += read_data[i+2]*16;
                        }
                }
        }else
                DG_table = NULL;

        delete [] read_data;
        delete [] read_data_tmp;
        if(ok ==0 | DG_table == NULL)
                return 0;
        return 1;
}

//---------------------------------------------------------------------------
bool TEngineerForm::SetWrite_PG(TLUT Addr_LUT, int* lut, int length)
{
        String Addr_str;
        Dec2Hex(Addr_LUT.Addr(), &Addr_str);
        edt_seq_addr->Text = Addr_str;
        WRITE_PG write_pg;
        Write_LUT(lut, length, Addr_LUT,&write_pg);      //type...
        edt_seq_len->Text = IntToStr(write_pg.lut_num);
        //將write data在"Write_LUT裡面 轉成unsigned char*"
        Set_seq_data(write_pg.Wrt_data, write_pg.lut_num, write_pg.addr);
        delete write_pg.Wrt_data;
        if(pg_write()){
                Sleep(10);
                return 1;
        }else{
                Sleep(10);        
                return 0;
        }
}
//---------------------------------------------------------------------------

bool TEngineerForm::SetRead_DCR(TLUT Addr_LUT,unsigned char* read_data, int length)
{
        String Addr_str;
        Dec2Hex(Addr_LUT.Addr(), &Addr_str);
        edt_seq_addr->Text = Addr_str;
        edt_seq_len->Text = IntToStr(length);
        bool ok = pg_read(read_data,1);
        if(ok == 0)
                return 0;
        return 1;
}

//---------------------------------------------------------------------------
void __fastcall TEngineerForm::btn_byte_readClick(TObject *Sender)
{
        btn_byte_read->Enabled = false;
        unsigned char data_read = B_read();
        btn_byte_read->Enabled = true;

        char string[4];
        sprintf( string,"%X", data_read);
        AnsiString str = (AnsiString)string;
        edt_byte_rdata->Text = str;
}

//---------------------------------------------------------------------------
void Add_val2_data_ad(unsigned char* data_addr, int data_addr_cnt,int add_num)
{
        int addr_val = 0;

        for(int i = 1; i >= 0; i--){
                addr_val *= 256;
                addr_val += data_addr[i];
        }
        addr_val += add_num;
        for(int i = 0; i <= 1; i++){
                data_addr[i] = addr_val % 256;
                addr_val = addr_val/256;
        }
}
//---------------------------------------------------------------------------
void Set2data_read(unsigned char* data_read, unsigned char* data_read_tmp, int pck_cnt, int num)
{
        for(int i = 0; i < num; i++)
                data_read[pck_cnt*PAC_SIZE+i] = data_read_tmp[i];
}
//---------------------------------------------------------------------------

void Set_write_buf(unsigned char* data_write, unsigned char* data_write_tmp, int drop, int num)
{
        for(int i = 0; i < num; i++)
                data_write_tmp[i] = data_write[drop+i];
}

//---------------------------------------------------------------------------
void TEngineerForm::Clear_sg_seq_data()
{
       for(int i = 1; i < (sg_seq_data->ColCount); i++)
                for(int j=1; j < (sg_seq_data->RowCount); j++)
                        sg_seq_data->Cells[i][j]="";
}

//---------------------------------------------------------------------------
bool TEngineerForm::pg_read(unsigned char *data_read, bool IsShow)
{
        Clear_sg_seq_data();
        int sel;
        unsigned char dev_addr[4];     int dev_addr_cnt;       //device address以byte儲存
        unsigned char data_addr[2];    int data_addr_cnt;      //memory address以byte儲存
        unsigned char *data_read_tmp;  int data_len;
        bool card_sel;

        if(Get_seq_addr(data_addr, &data_addr_cnt)==0){
                ShowMessage("Please enter a Byte address.");
                return 0;
        }

        if(Get_device_addr(dev_addr, &dev_addr_cnt)==0){
                ShowMessage("Please choose a device address.");
                return 0;
        }
        data_len = StrToInt(edt_seq_len->Text);
        data_read_tmp = new unsigned char [data_len];
        for(int i = 0; i < data_len; i++)
                data_read_tmp[i] = 0;
        unsigned char dev_addr_tmp;

        int ok=0;       //read ok or not
        int rd_cnt = 0;  //fail read count
        int pck_cnt = 0;    //record the number of package transmit
        unsigned char data_addr_tmp[2];
        for(int i = 0; i < dev_addr_cnt; i++){
                pck_cnt = 0;
                if(rg_i2c_card_sel->ItemIndex == 0){    //USB
                        int tmp_len = data_len; //data length remain after data transmit
                        if(tmp_len>PAC_SIZE){
                                for(int i = 0; i <= data_addr_cnt; i++)
                                        data_addr_tmp[i] = data_addr[i];
                                while(tmp_len>PAC_SIZE){
                                        SetDeviceAddr(dev_addr[i], &dev_addr_tmp, data_addr_tmp, data_addr_cnt);
                                        rd_cnt = 0;
                                        ok = 0;
                                        while(ok==0 && rd_cnt<3){     //if fail read exceed 3, give up rework
                                                ok = RW.USB_read(dev_addr_tmp, data_addr_tmp, data_addr_cnt, data_read_tmp, PAC_SIZE);
                                                rd_cnt++;
                                        }
                                        if(rd_cnt >= 3){
                                                char str[30];
                                                sprintf(str,"Package %d send fail.",pck_cnt+1);
                                                ShowMessage(str);
                                                return 0;
                                        }
                                        Add_val2_data_ad(data_addr_tmp, data_addr_cnt, PAC_SIZE);
                                        Set2data_read(data_read, data_read_tmp, pck_cnt, PAC_SIZE);
                                        pck_cnt++;
                                        tmp_len -= PAC_SIZE;
                                }
                                SetDeviceAddr(dev_addr[i], &dev_addr_tmp, data_addr_tmp, data_addr_cnt);
                                rd_cnt = 0;
                                ok = 0;
                                while(ok==0 && rd_cnt<3){     //if fail read exceed 3, give up rework
                                        ok = RW.USB_read(dev_addr_tmp, data_addr_tmp, data_addr_cnt, data_read_tmp, tmp_len);
                                        rd_cnt++;
                                }
                                if(rd_cnt >= 3){
                                        char str[30];
                                        sprintf(str,"Package %d send fail.",pck_cnt+1);
                                        ShowMessage(str);
                                        return 0;
                                }
                                Set2data_read(data_read, data_read_tmp, pck_cnt, tmp_len);

                        }else{
                                SetDeviceAddr(dev_addr[i], &dev_addr_tmp, data_addr, data_addr_cnt);
                                rd_cnt = 0;
                                ok = 0;
                                while(ok==0 && rd_cnt<3){     //if fail read exceed 3, give up rework
                                        ok = ok | RW.USB_read(dev_addr_tmp, data_addr, data_addr_cnt, data_read, data_len);
                                        rd_cnt++;
                                }
                                if(rd_cnt >= 3){
                                        char str[30];
                                        sprintf(str,"Package %d send fail.",pck_cnt+1);
                                        ShowMessage(str);
                                        return 0;
                                }
                        }
                }else{
                //LPT
                        SetDeviceAddr(dev_addr[i], &dev_addr_tmp, data_addr, data_addr_cnt);
                        ok = RW.LPT_Read_seq(dev_addr_tmp, data_addr, data_addr_cnt, data_read, data_len);
                        if(ok!=1){
                                if(ok==-1)
                                        ShowMessage("Device address Send fail!");
                                else if(ok==-2)
                                        ShowMessage("Data address Send fail!");
                                else if(ok==0)
                                        ShowMessage("Data Send fail!");
                                return 0;
                        }
                }
                Sleep(50);
        }

        if(rd_cnt>=3)
                MessageBox(NULL,"Read package fail for 3 times.","Error",MB_OK);

        int readChksum = 0;
        for(int i = 0; i < data_len; i++)
                readChksum += (int)data_read[i];
        char string[10];
        sprintf( string,"%X", readChksum );
        AnsiString str = (AnsiString)string;
        stb_page_operat->Panels->Items[1]->Text = "Read Checksum: "+ str;

        if(IsShow == true){
                int data_addr_val;
                data_addr_val = data_addr[0]+data_addr[1]*256;
                Set_seq_data(data_read, data_len, data_addr_val);
        }
        if(data_read_tmp!=NULL)
                delete [] data_read_tmp;
        return 1;
}

//---------------------------------------------------------------------------
void __fastcall TEngineerForm::btn_seq_readClick(TObject *Sender)
{
        btn_seq_read->Enabled = false;
        int len = StrToInt(edt_seq_len->Text);
        unsigned char * data_read = new unsigned char [len];
        for(int i = 0; i < len; i++)
                data_read[i] = 0;
        pg_read(data_read,1);
        btn_seq_read->Enabled = true;
        if(data_read!=NULL)
                delete [] data_read;
}
//---------------------------------------------------------------------------

bool TEngineerForm::Set_seq_data(unsigned char* data_read, int data_len, int data_addr_val)
{
        char string[5];
        int row = floor((double)data_len/16);
        int remain = data_len - row*16;

        for(int i = 0; i < row; i++){
                for(int j = 0; j < 16; j++){
                        sprintf( string,"%02X", data_read[i*16+j]);
                        sg_seq_data->Cells[j+1][i+1] = (AnsiString)string;
                }
                sprintf( string,"%02X", data_addr_val+i*16);
                sg_seq_data->Cells[0][i+1] = (AnsiString)string;
        }
        sprintf( string,"%02X",data_addr_val+row*16);
        sg_seq_data->Cells[0][row+1] = (AnsiString)string;
        for(int j = 0; j < remain; j++){
                sprintf( string,"%02X", data_read[row*16+j]);
                sg_seq_data->Cells[j+1][row+1] = (AnsiString)string;
        }
        return 1;
}
//--------------------------------------------------------------------------
bool TEngineerForm::Get_write_data(unsigned char *write_data){
        AnsiString str = edt_byte_wdata->Text;
        int val;
        if(Hex2Dec(str,&val)==0)
                return 0;
        *write_data = (unsigned char)val;
        return 1;
}
//---------------------------------------------------------------------------
bool TEngineerForm::Get_read_data(unsigned char *read_data){
        AnsiString str = edt_byte_rdata->Text;
        int val;
        if(Hex2Dec(str,&val)==0)
                return 0;
        *read_data = (unsigned char)val;
        return 1;
}

//-----------------------------------------------------------------------------
bool TEngineerForm::SetDeviceAddr(unsigned char dev_ad, unsigned char* dev_ad_new, unsigned char* data_ad, int data_ad_c)
{
        if(cbo_mem_addr_size->ItemIndex==1){
                *dev_ad_new = (dev_ad & 0xFC) + (data_ad[1] & 0x01);
        }else if(cbo_mem_addr_size->ItemIndex==2){
                *dev_ad_new = (dev_ad & 0xF8) + (data_ad[1] & 0x03);
        }else if(cbo_mem_addr_size->ItemIndex==3){
                *dev_ad_new = (dev_ad & 0xF0) + (data_ad[1] & 0x07);
        }else{
                *dev_ad_new = dev_ad;
        }

        return 1;
}

//---------------------------------------------------------------------------
void __fastcall TEngineerForm::btn_byte_writeClick(TObject *Sender)
{
        if(btn_connect_card->Enabled == true){
                ShowMessage("No connection to card.");
                return;
        }
        btn_byte_write->Enabled = false;
        B_write();
        btn_byte_write->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TEngineerForm::rg_i2c_card_selClick(TObject *Sender)
{
        if(rg_i2c_card_sel->ItemIndex == 2){     //LPT 06T11-SA
                Img_LPT_06T->Visible = true;
                Img_LPT_04T->Visible = false;
                Img_usb->Visible = false;
                SetCardLarge();
                rg_device_addr_sel->Items->Strings[3] ="OTP";
        }else if(rg_i2c_card_sel->ItemIndex == 1){     //LPT 04T25-SA
                Img_LPT_06T->Visible = false;
                Img_LPT_04T->Visible = true;
                Img_usb->Visible = false;
                SetCardSmall();
                rg_device_addr_sel->Items->Strings[3]="OTP";
        }else if(rg_i2c_card_sel->ItemIndex == 0){     //USB
                Img_LPT_06T->Visible = false;
                Img_LPT_04T->Visible = false;
                Img_usb->Visible = true;
                rg_device_addr_sel->Items->Strings[3]="===";

        }
        btn_connect_card->Enabled = true;
        connect = false;
        //MainForm->StatusBar1->Panels->Items[0]->Text = "Connection: Fail!";
	btn_en_ftm->Enabled = true;
        btn_connect_cardClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TEngineerForm::btn_connect_cardClick(TObject *Sender)
{
        int cnnct_ok = 0;
        connect = false;
        //USB connect
        if(rg_i2c_card_sel->ItemIndex == 0){
                if(rg_device_addr_sel->ItemIndex==3){
                        rg_i2c_card_sel->ItemIndex = -1;
                        ShowMessage("USB signal will be transmitted in package, Please choose one of LPT");
                        return;
                }
                cnnct_ok = RW.USB_connect(rg_power->ItemIndex,rg_speed->ItemIndex);
                if(cnnct_ok == true)
                        btn_byte_readClick(Sender);
        //LPT connect
        }else if(rg_i2c_card_sel->ItemIndex == 1 || rg_i2c_card_sel->ItemIndex == 2){
                RW.USB_disconnect();
                cnnct_ok = RW.LPT_connect();
                if(cnnct_ok == 0){
                        MessageBox(NULL,"No LPT Dll found.","Error",MB_OK);
                        return;
                }else if(cnnct_ok == -1){
                        MessageBox(NULL,"GetProcAddress for Inp32 Failed.","Error",MB_OK);
                        return;
                }else if(cnnct_ok == -2){
                        MessageBox(NULL,"ECR Byte Mode setting fail.","Error",MB_OK);
                        return;
                }else
                        btn_byte_readClick(Sender);
        }
        if(connect == true){
                btn_connect_card->Enabled = false;
                //MainForm->StatusBar1->Panels->Items[0]->Text = "Connection: OK!";
        }else{
                btn_connect_card->Enabled = true;
                //MainForm->StatusBar1->Panels->Items[0]->Text = "Connection: fail!";
        }
}
//---------------------------------------------------------------------------

void TEngineerForm::Get_seq_write_data(unsigned char* write_data, int data_len)
{
        int row = floor((double)data_len/16);
        int remain = data_len - row*16;
        int val;

        for(int i = 0; i < data_len; i++)
                write_data[i] = 0;

        for(int i = 0; i < row; i++){
                for(int j = 0; j < 16; j++){
                        if(Hex2Dec(sg_seq_data->Cells[j+1][i+1], &val))
                                write_data[i*16+j] = (unsigned char)val;       //型態不合 (hex2Dec?!)
                }
        }
        for(int j = 0; j < remain; j++){
                if(Hex2Dec(sg_seq_data->Cells[j+1][row+1], &val))
                        write_data[row*16+j] = LOBYTE(val);       //型態不合 (hex2Dec?!)
        }
}
//---------------------------------------------------------------------------

bool TEngineerForm::USB_pg_write(unsigned char dev_ad, unsigned char* data_addr, int data_addr_cnt,
unsigned char* data_write, int data_len, int pck_size, int wait_t)
{
        int tmp_len = data_len; //data length remain after data transmit
        unsigned char data_addr_tmp[2];
        for(int i = 0; i <= data_addr_cnt; i++)
                data_addr_tmp[i] = data_addr[i];
        unsigned char* data_w_tmp = new unsigned char [PAC_SIZE];
        for(int i = 0; i < PAC_SIZE; i++){
                data_w_tmp[i]=0;
        }
        if(data_w_tmp==NULL)
                return 0;       //memory allocate fail
        unsigned char dev_ad_tmp;
        int pck_cnt = 0;

        //if address start != 8 multiplier
        int data_ad = (int)data_addr_tmp[0]+(int)data_addr_tmp[1]*256;

        int ok=0;       //read ok or not
        int rd_cnt = 0;  //fail read count
        int front = 0;

        if(rg_device_addr_sel->ItemIndex==2 && data_ad%8!=0){
                front = 8-data_ad%8;
                Set_write_buf(data_write, data_w_tmp, 0, front);
                SetDeviceAddr(dev_ad, &dev_ad_tmp, data_addr_tmp, data_addr_cnt);
                ok=0;       //read ok or not
                rd_cnt = 0;  //fail read count
                while(ok==0 && rd_cnt<3){     //if fail read exceed 3, give up rework
                        ok = RW.USB_write(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, front);
                        rd_cnt++;
                }
                if(rd_cnt >= 3){
                        char str[30];
                        sprintf(str,"Package %d send fail.",pck_cnt+1);
                        ShowMessage(str);
                        return 0;
                }
                Add_val2_data_ad(data_addr_tmp, data_addr_cnt, front);
                tmp_len -= front;
                Sleep(wait_t);
        }
        /////////////////////////////////////////////////

        while(tmp_len>pck_size){   //need to send more packages
                Set_write_buf(data_write, data_w_tmp, front+pck_cnt*pck_size, pck_size);
                                  //Get Write data from interface
                SetDeviceAddr(dev_ad, &dev_ad_tmp, data_addr_tmp, data_addr_cnt);
                                  //Set the 1st Byte of device address
                ok=0;       //read ok or not
                rd_cnt = 0;  //fail read count
                while(ok==0 && rd_cnt<3){     //if fail read exceed 3, give up rework
                        ok = RW.USB_write(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, pck_size);
                        rd_cnt++;
                }
                if(rd_cnt >= 3){
                char str[30];
                        sprintf(str,"Package %d send fail.",pck_cnt+1);
                        ShowMessage(str);
                        return 0;
                }
                Add_val2_data_ad(data_addr_tmp, data_addr_cnt, pck_size);
                pck_cnt++;
                tmp_len -= pck_size;
                Sleep(wait_t);
       }
       Set_write_buf(data_write, data_w_tmp, front+pck_cnt*pck_size, tmp_len);
       SetDeviceAddr(dev_ad, &dev_ad_tmp, data_addr_tmp, data_addr_cnt);
       ok=0;       //read ok or not
       rd_cnt = 0;  //fail read count
       while(ok==0 && rd_cnt<3){     //if fail read exceed 3, give up rework
               ok = RW.USB_write(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, tmp_len);
               rd_cnt++;
       }
        if(rd_cnt >= 3){
                char str[30];
                sprintf(str,"Package %d send fail.",pck_cnt+1);
                ShowMessage(str);
                return 0; 
        }
       if(data_w_tmp!= NULL)
               delete [] data_w_tmp;

       return ok;
}
//---------------------------------------------------------------------------
/*
bool TEngineerForm::USB_pg_write_s(unsigned char dev_ad, unsigned char* data_addr, int data_addr_cnt,
unsigned char* data_write, int data_len, int pck_size, int wait_t)
{
        int tmp_len = data_len; //data length remain after data transmit
        unsigned char data_addr_tmp[2];
        for(int i = 0; i <= data_addr_cnt; i++)
                data_addr_tmp[i] = data_addr[i];
        unsigned char* data_w_tmp = new unsigned char [PAC_SIZE];
        for(int i = 0; i < 60; i++){
                data_w_tmp[i]=0;
        }
        if(data_w_tmp==NULL)
                return 0;       //memory allocate fail
        unsigned char dev_ad_tmp;
        int pck_cnt = 0;

        //if address start != 8 multiplier
        int data_ad = (int)data_addr_tmp[0]+(int)data_addr_tmp[1]*256;

        int ok=0;       //read ok or not
        int rd_cnt = 0;  //fail read count
        int front = 0;

        int flg_start_end = 0;
        //if start & end, flag = 1
        //if start, flag = 2
        //if end, flag = 3
        //if no start or end, flag = 4

        if(rg_device_addr_sel->ItemIndex==2 && data_ad%8!=0){
                front = 8-data_ad%8;
                Set_write_buf(data_write, data_w_tmp, 0, front);
                SetDeviceAddr(dev_ad, &dev_ad_tmp, data_addr_tmp, data_addr_cnt);
                ok=0;       //read ok or not
                rd_cnt = 0;  //fail read count
                while(ok==0 && rd_cnt<3){     //if fail read exceed 3, give up rework
                        // status with start
                        if(data_len < 8){
                                flg_start_end = 1;
                        }else
                                flg_start_end = 2;
                        ok = RW.USB_write_serial(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, front,flg_start_end);
                        // Original
                        //ok = RW.USB_write(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, front);
                        rd_cnt++;
                }
                if(rd_cnt >= 3){
                        char str[30];
                        sprintf(str,"Package %d send fail.",pck_cnt+1);
                        ShowMessage(str);
                        return 0;
                }
                Add_val2_data_ad(data_addr_tmp, data_addr_cnt, front);
                tmp_len -= front;
                Sleep(wait_t);
        }
        /////////////////////////////////////////////////

        while(tmp_len>pck_size){   //need to send more packages
                Set_write_buf(data_write, data_w_tmp, front+pck_cnt*pck_size, pck_size);
                                  //Get Write data from interface
                SetDeviceAddr(dev_ad, &dev_ad_tmp, data_addr_tmp, data_addr_cnt);
                                  //Set the 1st Byte of device address
                ok=0;       //read ok or not
                rd_cnt = 0;  //fail read count
                while(ok==0 && rd_cnt<3){     //if fail read exceed 3, give up rework
                        flg_start_end = 4;
                        ok = RW.USB_write_serial(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, pck_size,flg_start_end);
                        //Original
                        //ok = RW.USB_write(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, pck_size);
                        rd_cnt++;
                }
                if(rd_cnt >= 3){
                char str[30];
                        sprintf(str,"Package %d send fail.",pck_cnt+1);
                        ShowMessage(str);
                        return 0;
                }
                Add_val2_data_ad(data_addr_tmp, data_addr_cnt, pck_size);
                pck_cnt++;
                tmp_len -= pck_size;
                Sleep(wait_t);
       }
       Set_write_buf(data_write, data_w_tmp, front+pck_cnt*pck_size, tmp_len);
       SetDeviceAddr(dev_ad, &dev_ad_tmp, data_addr_tmp, data_addr_cnt);
       ok=0;       //read ok or not
       rd_cnt = 0;  //fail read count
       while(ok==0 && rd_cnt<3){     //if fail read exceed 3, give up rework
               flg_start_end = 3;
               ok = RW.USB_write_serial(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, tmp_len,flg_start_end);
               //Original
               //ok = RW.USB_write(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, tmp_len);               
               rd_cnt++;
       }
        if(rd_cnt >= 3){
                char str[30];
                sprintf(str,"Package %d send fail.",pck_cnt+1);
                ShowMessage(str);
                return 0; 
        }
       if(data_w_tmp!= NULL)
               delete [] data_w_tmp;

       return ok;
}              */
//---------------------------------------------------------------------------
bool TEngineerForm::LPT_pg_write(unsigned char dev_ad, unsigned char* data_addr, int data_addr_cnt,
unsigned char* data_write, int data_len, int pck_size, int wait_t)
{
        int tmp_len = data_len; //data length remain after data transmit
        unsigned char data_addr_tmp[2];
        for(int i = 0; i <= data_addr_cnt; i++)
                data_addr_tmp[i] = data_addr[i];
        unsigned char* data_w_tmp = new unsigned char [tmp_len];
        if(data_w_tmp==NULL)
                return NULL;
        unsigned char dev_ad_tmp;
        int pck_cnt = 0;
        //EEPROM internal counter can only address for 1 page size
        //計算data address 若小於page size的倍數者的前幾byte先送出,
        //並更新address為page size的倍數與更新送出的長度
        int address_val;

        int data_ad = (int)data_addr_tmp[0]+(int)data_addr_tmp[1]*256;

        int front = 0;
        if(rg_device_addr_sel->ItemIndex == 2){
                if(data_ad%8!=0){
                        front = 8-data_ad%8;
                        Set_write_buf(data_write, data_w_tmp, 0, front);
                        SetDeviceAddr(dev_ad, &dev_ad_tmp, data_addr_tmp, data_addr_cnt);
                        RW.LPT_Write(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, front);
                        Add_val2_data_ad(data_addr_tmp, data_addr_cnt, front);
                        tmp_len -= front;
                        Sleep(wait_t);
                }
                while(tmp_len>pck_size){   //need to send more packages
                        Set_write_buf(data_write, data_w_tmp, front+pck_cnt*pck_size, pck_size);//Get Write data from interface
                        SetDeviceAddr(dev_ad, &dev_ad_tmp, data_addr_tmp, data_addr_cnt);//Set the 1st Byte of device address
                        RW.LPT_Write(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, pck_size);
                        Add_val2_data_ad(data_addr_tmp, data_addr_cnt, pck_size);
                        pck_cnt++;
                        tmp_len -= pck_size;
                        Sleep(wait_t);
               }
       }
       Set_write_buf(data_write, data_w_tmp, front+pck_cnt*pck_size, tmp_len);
       SetDeviceAddr(dev_ad, &dev_ad_tmp, data_addr_tmp, data_addr_cnt);
       RW.LPT_Write(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, tmp_len);
       Sleep(wait_t);
       if(data_w_tmp!=NULL)
               delete [] data_w_tmp;
       return 1;
}

//---------------------------------------------------------------------------
bool TEngineerForm::pg_write()
{
        unsigned char dev_addr[4];      int dev_addr_cnt;
        unsigned char data_addr[2];     int data_addr_cnt;
        unsigned char* data_write;      int data_len;

        if(Get_seq_addr(data_addr, &data_addr_cnt)==0){
                ShowMessage("Please enter a Byte address.");
                return 0;
        }

        if(Get_device_addr(dev_addr, &dev_addr_cnt)==0){
                ShowMessage("Please choose a device address.");
                return 0;
        }
        data_len = StrToInt(edt_seq_len->Text);
        data_write = new unsigned char [data_len];
        if(data_write==NULL){
                ShowMessage("Memory is not enough!");
                return 0;
        }
        Get_seq_write_data(data_write, data_len);
        if(data_write==NULL){
                ShowMessage("Please enter a byte to write.");
                return 0;
        }

        int pck_size = data_len;
        if(rg_i2c_card_sel->ItemIndex == 0){    //USB package size
                pck_size = PAC_SIZE;
        }
        
        if(rg_device_addr_sel->ItemIndex == 2){ //EEPROM package size
                pck_size = 8;
                rg_w_cycl_t->ItemIndex = 1;     //Write EEPROM, EEPROM internal write cycle time: 5us
        }else
                rg_w_cycl_t->ItemIndex = 2;     //no need cycle time

        /*
        if(rg_w_page->ItemIndex == 0){
                pck_size = 2;
        }else if(rg_w_page->ItemIndex == 1){
                pck_size = 8;
        }else if(rg_w_page->ItemIndex == 2){
                pck_size = 16;
        }else if(rg_w_page->ItemIndex == 3){
                pck_size = 32;
        }
        */

        int wait_t = 0;
        if(rg_w_cycl_t->ItemIndex == 0)
                wait_t = 6;
        else if(rg_w_cycl_t->ItemIndex == 1)
                wait_t = 11;
        else if(rg_w_cycl_t->ItemIndex == 2)
                wait_t = 0;
        
        int ok = 0;
        for(int i = 0; i < dev_addr_cnt; i++){
                if(rg_i2c_card_sel->ItemIndex == 0){    //Use USB to transfer
                        // original PAC_SIZE byte per package
                        ok = USB_pg_write(dev_addr[i], data_addr, data_addr_cnt, data_write, data_len, pck_size, wait_t);
                        // no seperate
                        //ok = USB_pg_write_s(dev_addr[i], data_addr, data_addr_cnt, data_write, data_len, pck_size, wait_t);
                }else{
                        ok = LPT_pg_write(dev_addr[i], data_addr, data_addr_cnt, data_write, data_len, pck_size, wait_t);
                        if(ok!=1){
                                if(ok==-1)
                                        ShowMessage("Device address Send fail!");
                                else if(ok==-2)
                                        ShowMessage("Data address Send fail!");
                                else if(ok==0)
                                        ShowMessage("Data Send fail!");
                                return 0;
                        }
                }
                Sleep(50);
        }

        int write_chk = 0;
        for(int i = 0; i < data_len; i++)
                write_chk += int(data_write[i]);

        char string[10];
        sprintf( string,"%X", write_chk );
        AnsiString str = (AnsiString)string;
        stb_page_operat->Panels->Items[0]->Text = "Write Checksum: "+str;
        stb_page_operat->Panels->Items[1]->Text = "Read Checksum: ";

        if(data_write!=NULL)
                delete [] data_write;

        return 1;
}

//---------------------------------------------------------------------------
void __fastcall TEngineerForm::btn_seq_writeClick(TObject *Sender)
{

          //Check card connection
        if(btn_connect_card->Enabled == true){
                ShowMessage("No connection to card.");
        }

        btn_seq_write->Enabled = false;

        //clock_t startwait=clock();
        pg_write();
        //clock_t endwait=clock();

        //ShowMessage("  Time(ms):"+FloatToStr(endwait-startwait));
        btn_seq_write->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TEngineerForm::PageControl1Exit(TObject *Sender)
{
        RW.USB_disconnect();
}
//---------------------------------------------------------------------------

void __fastcall TEngineerForm::btn_soft_resetClick(TObject *Sender)
{
        if(rg_device_addr_sel->ItemIndex==2){
                rg_device_addr_sel->ItemIndex = 0;
                btn_connect_cardClick(Sender);
                if(!connect)
                        return;
        }
        if(!connect){
                btn_connect_cardClick(Sender);
                if(!connect)
                        return;
        }
        edt_byte_addr->Text = 4;
        edt_byte_wdata->Text = 1;
        btn_byte_writeClick(Sender);
}
//---------------------------------------------------------------------------
bool TEngineerForm::Get_device_addr(int* dev_ad)
{
        bool ok;
        int val;
        if(rg_device_addr_sel->ItemIndex==0){       //single TCON
                ok = Hex2Dec(edt_addr_tcon_s->Text,&val);
                *dev_ad = (unsigned char)val;
        }else if(rg_device_addr_sel->ItemIndex==1){       //dual TCON
                ok = Hex2Dec(edt_addr_tcon_dm->Text,&val);
                *dev_ad = (unsigned char)val;
        }else if(rg_device_addr_sel->ItemIndex==2){       //single EEPROM
                ok = Hex2Dec(edt_addr_EEP->Text,&val);
                *dev_ad = (unsigned char)val;
        }else   //may add quad-TCON here
                return 0;

        return 1;
}

//---------------------------------------------------------------------------
void TEngineerForm::dev_addr_change(TObject *Sender)
{
        int dev;
        Get_device_addr(&dev);
        //StringGrid of device address
        char str[5];
        for(int i = 0; i < 7 ; i++){
                sprintf(str, "%d", (int)((double)dev/pow(2,7-i))%2);
                sg_device_addr->Cells[i][0] = (AnsiString)str;
        }
        sg_device_addr->Cells[7][0] = "RW";
        //rg_device_addr_selClick(Sender);
}


void __fastcall TEngineerForm::cbo_mem_addr_sizeChange(TObject *Sender)
{
        //sg_device_addr是介面上的一列數值,用來表示實際上用來定址的位元
        dev_addr_change(Sender);
        int idx = cbo_mem_addr_size->ItemIndex;

        //2k, dev|word|R/W bit
        //     7 | 0  | 1
        if(idx==0){
        }
        //4k, dev|word|R/W bit
        //     6 | 1  | 1
        else if(idx==1){
                sg_device_addr->Cells[6][0] = "--";
        }
        //8k, dev|word|R/W bit
        //     5 | 2  | 1
        else if(idx==2){
                for(int i = 0; i <= 1; i++)
                        sg_device_addr->Cells[6-i][0] = "--";
        }
        //16k, dev|word|R/W bit
        //     4 | 3  | 1
        else if(idx==3){
                for(int i = 0; i <= 2; i++)
                        sg_device_addr->Cells[6-i][0] = "--";
        }
        //32k, dev|word|R/W bit
        //     7 | 0  | 1
        else if(idx>=4){
        }
         btn_en_ftm->Enabled = true;
}
//---------------------------------------------------------------------------


void __fastcall TEngineerForm::rg_device_addr_selClick(TObject *Sender)
{
        dev_addr_change(Sender);
        btn_en_ftm->Enabled = true;

        if(rg_device_addr_sel->ItemIndex==2){     //EEPROM
                //MainForm->StatusBar1->Panels->Items[1]->Text = "Device Address: "+edt_addr_EEP->Text;
                if(cbo_mem_addr_size->ItemIndex==0)      //2k
                        rg_w_page->ItemIndex = 1;
                else if(cbo_mem_addr_size->ItemIndex==1 || cbo_mem_addr_size->ItemIndex==2 || cbo_mem_addr_size->ItemIndex==3)
                        //4k, 8k, 16k
                        rg_w_page->ItemIndex = 2;
                else    //32k or more
                        rg_w_page->ItemIndex = 3;
                rg_w_cycl_t->ItemIndex = 1;
        }else{    //TCON or OTP
                rg_w_cycl_t->ItemIndex = 2;
                rg_w_page->ItemIndex = 4;
                if(rg_device_addr_sel->ItemIndex==0){
                       // MainForm->StatusBar1->Panels->Items[1]->Text = "Device Address: "+edt_addr_tcon_s->Text;
                }else if(rg_device_addr_sel->ItemIndex==1){
                        //MainForm->StatusBar1->Panels->Items[1]->Text = "Device Address: "+edt_addr_tcon_dm->Text+edt_addr_tcon_ds->Text;
                }else if(rg_device_addr_sel->ItemIndex==3){
                        //MainForm->StatusBar1->Panels->Items[1]->Text = "Device Address: "+edt_addr_OTP->Text;
                        if(rg_i2c_card_sel->ItemIndex == 0){
                                rg_i2c_card_sel->ItemIndex = -1;
                                ShowMessage("USB signal will be transmitted in package, Please choose one of LPT");
                                return;
                        }
                }
        }
        btn_connect_card->Enabled = true;
        connect = false;
        //MainForm->StatusBar1->Panels->Items[0]->Text = "Connection: Fail";
        btn_connect_cardClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TEngineerForm::edt_addr_tcon_sChange(TObject *Sender)
{
        rg_device_addr_sel->ItemIndex=0;
        rg_device_addr_selClick(Sender);
        dev_addr_change(Sender);
        btn_en_ftm->Enabled = true;
        btn_connect_cardClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TEngineerForm::edt_addr_tcon_dmChange(TObject *Sender)
{
        rg_device_addr_sel->ItemIndex=1;
        rg_device_addr_selClick(Sender);
        dev_addr_change(Sender);
        btn_en_ftm->Enabled = true;
        btn_connect_cardClick(Sender);        
}
//---------------------------------------------------------------------------

void __fastcall TEngineerForm::edt_addr_tcon_dsChange(TObject *Sender)
{
        rg_device_addr_sel->ItemIndex=1;
        rg_device_addr_selClick(Sender);
        dev_addr_change(Sender);
        btn_en_ftm->Enabled = true;
        btn_connect_cardClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TEngineerForm::edt_addr_EEPChange(TObject *Sender)
{
        rg_device_addr_sel->ItemIndex=2;
        rg_device_addr_selClick(Sender);
        dev_addr_change(Sender);
        btn_en_ftm->Enabled = true;
        btn_connect_cardClick(Sender);
}
//---------------------------------------------------------------------------


void __fastcall TEngineerForm::btn_seq_loadClick(TObject *Sender)
{
        if(!OpenDialog_txt_hex->Execute())
                return;
        String Fpath = OpenDialog_txt_hex->FileName;

        int Size;
        char *buffer = LoadFile(Fpath, &Size);
        if(buffer == NULL){
                ShowMessage("File is empty.");
                return;
        }

        if(OpenDialog_txt_hex->FilterIndex==1){ //Text File
                char *pch, *data;
                int idx = 0;
                pch = strtok (buffer,"\n\t");
                data = new char [Size];
                int val;
                int fileChksum = 0;
                while (pch!=NULL){
                        if(isdigit(pch[0]) || (pch[0]>='a' && pch[0]<='f') || (pch[0]>='A' && pch[0]<='F')){
                                Hex2Dec((AnsiString)pch, &val);
                                data[idx] = (unsigned char)val;
                                idx++;
                                fileChksum += val;
                        }
                        pch = strtok (NULL,"\n\t");
                }
                Set_seq_data(data, idx, 0);

                char string[10];
                sprintf( string,"%X", fileChksum );
                AnsiString str = (AnsiString)string;
                stb_page_operat->Panels->Items[2]->Text = "Load Checksum: "+str;
                delete [] pch;
                delete [] data;
        }else{  //hex file
                char *pch, *data;
                int idx = 0;
                pch = strtok (buffer,"\n\t");
                data = new char [Size];
                int val;
                int fileChksum = 0;
                int i = 0;
                int intel_address;
                while (pch!=NULL){
                         String str = (AnsiString)pch;
                         if(str.Length()<43)
                                break;
                         String addr = str.SubString(3,4);    //address
                               //if(isdigit(pch[0]) || (pch[0]>='a' && pch[0]<='f') || (pch[0]>='A' && pch[0]<='F')){
                               //         Hex2Dec((AnsiString)pch, &val);
                         //ShowMessage("Intel Addr: "+(AnsiString)addr);

                         int checksum;  //每一行的checksum
                         Hex2Dec((AnsiString)(str.SubString(10+16*2,2)), &checksum);

                         for(int i = 0; i <=15; i++){   //切出data數值
                                Hex2Dec((AnsiString)str.SubString(10+i*2,2), &val);
                                data[idx] = (unsigned char)val;
                                idx++;
                                fileChksum += val;
                         }
                         pch = strtok (NULL,"\n\t");
                }
                Set_seq_data(data, idx, 0);

                char string[10];
                sprintf( string,"%X", fileChksum );
                AnsiString str = (AnsiString)string;
                stb_page_operat->Panels->Items[2]->Text = "Load Checksum: "+str;
                delete [] pch;
                delete [] data;
        }
        delete [] buffer;
}
//---------------------------------------------------------------------------

void __fastcall TEngineerForm::btn_seq_saveClick(TObject *Sender)
{

        if(!SaveDialog_txt_hex->Execute())
                return;
        String Fpath = SaveDialog_txt_hex->FileName;
        FILE* fptr = fopen (Fpath.c_str(),"w");
        if(fptr == NULL){
                ShowMessage("Can't Open file.");
                return;
        }
        int data_len = StrToInt(edt_seq_len->Text);
        unsigned char* data = new unsigned char [data_len];
        Get_seq_write_data(data, data_len);
        if(SaveDialog_txt_hex->FilterIndex==1){ //Text File
                for(int i = 0; i < data_len; i++){
                        /*fprintf(fptr,"%02X", data[i]);
                        if(i%16!=15)
                                fprintf(fptr,"\t");
                        else
                                fprintf(fptr,"\n");
                        */
                        fprintf(fptr,"%02X\n", data[i]);
                }
        }else if(SaveDialog_txt_hex->FilterIndex==2){ //Intel Hex File
                int addr = 0;
                int checksum;
                int sum = 0;
                for(int i = 0; i < data_len;){
                        sum = 0;
                        for(int j = 0; j < 16; j++){
                                if(j==0){        //寫address ":10000000"
                                        addr = i;
                                        fprintf(fptr, ":1%05X00", addr);
                                }
                                fprintf(fptr,"%02X", data[i]);  //寫data, 一行16筆
                                sum += data[i];  //把同一行的data值sum起來
                                if(j==15){       //寫入checksum
                                        checksum = floor(addr/256)+(addr)%256+sum+16;
                                        fprintf(fptr, "%02X\n", (256-checksum%256)%256);
                                }
                                i++;
                        }
                }
				fprintf(fptr, ":00000001FF\n");
        }
        
        fprintf(fptr,"\0");
        fclose(fptr);
        delete [] data;
}
//---------------------------------------------------------------------------
void __fastcall TEngineerForm::btn_en_ftmClick(TObject *Sender)
{
        btn_en_ftm->Enabled = false;
        edt_byte_addr->Text = 2;

        if(rg_device_addr_sel->ItemIndex==2 || rg_device_addr_sel->ItemIndex==1){
                rg_device_addr_sel->ItemIndex = 0;
                btn_connect_cardClick(Sender);
                if(!connect)
                        return;
        }
        if(!connect){
                btn_connect_cardClick(Sender);
                if(!connect)
                        return;
        }

        btn_byte_readClick(Sender);
        unsigned char read_data;
        Get_read_data(&read_data);
        unsigned char write_data = read_data | 80;
        edt_byte_wdata->Text = (AnsiString)write_data;
        btn_byte_writeClick(Sender);

        rg_device_addr_sel->ItemIndex = 2;

        btn_connect_cardClick(Sender);
}
//---------------------------------------------------------------------------

String* TEngineerForm::Load_file(String Fpath, int Lut_no)
{
        long lSize;
        char* buffer;
        FILE* fptr;
        if((fptr = fopen(Fpath.c_str(),"r"))==NULL){
                //ShowMessage("Can't Open File.");
                return NULL;
        }
         // obtain file size:
        fseek (fptr , 0 , SEEK_END);
        lSize = ftell (fptr);
        rewind (fptr);

        // allocate memory to contain the whole file:
        buffer = (char*) malloc (sizeof(char)*lSize+1);
        if(buffer == NULL){
                //ShowMessage("Can't Allocate Memory.");
                return NULL;
        }
        // copy the file into the buffer:
        fread (buffer,1,lSize,fptr);
        buffer[lSize]='\0';
        fclose(fptr);

        String* LUT = new String [Lut_no];
        char * pch;
        pch = strtok (buffer,"\n\t");
        String tmp;
        int i = 0;

        while (pch != NULL){
                LUT[i] = (AnsiString)pch;
                pch = strtok (NULL,"\n\t");
                i++;
                if(i>=Lut_no)
                        break;
        }
        if(i<Lut_no){
                return NULL;
        }
        return LUT;
}

void __fastcall TEngineerForm::btn_reloadClick(TObject *Sender)
{
        btn_reload->Enabled = false;
        //MainForm->reload_all(Sender);
        btn_reload->Enabled = true;        
}
//---------------------------------------------------------------------------


void __fastcall TEngineerForm::rg_powerClick(TObject *Sender)
{
        RW.USB_disconnect();
        bool cnnct_ok = RW.USB_connect(rg_power->ItemIndex,rg_speed->ItemIndex);
        if(cnnct_ok == false){
                MessageBox(NULL,"USB connect fail.","Error",MB_OK);
                rg_power->ItemIndex = -1;
        }else{
                btn_byte_readClick(Sender);
        }
        if(cnnct_ok == 1 && connect == true){
                btn_connect_card->Enabled = false;
        }
}
//---------------------------------------------------------------------------

void __fastcall TEngineerForm::rg_speedClick(TObject *Sender)
{
        RW.USB_disconnect();
        bool cnnct_ok = RW.USB_connect(rg_power->ItemIndex,rg_speed->ItemIndex);
        if(cnnct_ok == false){
                MessageBox(NULL,"USB connect fail.","Error",MB_OK);
                rg_speed->ItemIndex = -1;
        }else{
                btn_byte_readClick(Sender);
        }
        if(cnnct_ok == 1 && connect == true){
                btn_connect_card->Enabled = false;
        }
}
//---------------------------------------------------------------------------



void __fastcall TEngineerForm::btn_page_writeClick(TObject *Sender)
{
        btn_page_write->Enabled = false;
        edt_seq_addr->Text = 0;
        int size_idx = pow(2,StrToFloat(cbo_mem_addr_size->ItemIndex)+1);
        edt_seq_len->Text = IntToStr(size_idx*1024/8);
        btn_seq_writeClick(Sender);
        btn_page_write->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TEngineerForm::btn_page_readClick(TObject *Sender)
{
        btn_page_read->Enabled = false;
        edt_seq_addr->Text = 0;
        int size_idx = pow(2,StrToFloat(cbo_mem_addr_size->ItemIndex)+1);
        edt_seq_len->Text = IntToStr(size_idx*1024/8);
        btn_seq_readClick(Sender);
        btn_page_read->Enabled = true;        
}
//---------------------------------------------------------------------------

void __fastcall TEngineerForm::btn_page_saveClick(TObject *Sender)
{
        btn_page_save->Enabled = false;
        edt_seq_addr->Text = 0;
        int size_idx = pow(2,StrToFloat(cbo_mem_addr_size->ItemIndex)+1);
        edt_seq_len->Text = IntToStr(size_idx*1024/8);
        btn_seq_saveClick(Sender);
        btn_page_save->Enabled = true;        
}
//---------------------------------------------------------------------------

void __fastcall TEngineerForm::btn_page_loadClick(TObject *Sender)
{
        btn_page_load->Enabled = false;
        edt_seq_addr->Text = 0;
        int size_idx = pow(2,StrToFloat(cbo_mem_addr_size->ItemIndex)+1);
        edt_seq_len->Text = IntToStr(size_idx*1024/8);
        btn_seq_loadClick(Sender);
        btn_page_load->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TEngineerForm::btn_LPT_spdClick(TObject *Sender)
{
        edt_seq_addr->Text = 0;
        edt_seq_len->Text = 256;

        clock_t start_t=clock();
        btn_seq_readClick(Sender);
        clock_t end_t=clock();
        if(end_t-start_t<=0){
                st_lpt_speed->Caption = "0";
                return;
        }
        double freq = 1.0/((double)(end_t-start_t)/300.0/9.0);
        char str[10];
        sprintf(str, "%3.2f kHz", freq);
        st_lpt_speed->Caption = str;
        int ID_OK;
        if(freq>70)
                ID_OK = MessageBox(NULL, "Lower LPT frequency?!","Confirm",MB_OKCANCEL);
        if(ID_OK == 1){
                cb_low_freq->Checked = true;
                SetHalfFreq();
        }
}
//---------------------------------------------------------------------------

void __fastcall TEngineerForm::cb_low_freqClick(TObject *Sender)
{
        if(cb_low_freq->Checked)
                SetHalfFreq();
        else
                SetOrigFreq();
}
//---------------------------------------------------------------------------


void __fastcall TEngineerForm::edt_addr_OTPChange(TObject *Sender)
{
        rg_device_addr_sel->ItemIndex=3;
        rg_device_addr_selClick(Sender);
        dev_addr_change(Sender);
        //btn_en_ftm->Enabled = true;
        btn_connect_cardClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TEngineerForm::btn_byte_read_no_ackClick(TObject *Sender)
{       //if slave no send ack, don't stop sending data.
        unsigned char dev_addr[4];
        //device read/write address, extend to 4 devices set at a time

        unsigned char data_addr[2];     //Word address, may be 1 or 2 Byte
        unsigned char data_read; //data read
        int data_addr_cnt;      //number of byte in data address
        int dev_addr_cnt;       //number of device

        if(Get_byte_addr(data_addr, &data_addr_cnt)==0){
                ShowMessage("Please enter a Byte address.");
        }

        if(Get_device_addr(dev_addr, &dev_addr_cnt)==0){
                ShowMessage("Please choose a device address.");
        }
        int ok=1;
        unsigned char dev_addr_tmp;
        for(int i = 0; i < dev_addr_cnt; i++){
                SetDeviceAddr(dev_addr[i], &dev_addr_tmp, data_addr, data_addr_cnt);
                //if(rg_i2c_card_sel->ItemIndex == 0)
                //        connect = RW.USB_read(dev_addr_tmp, data_addr, data_addr_cnt, &data_read, 1);
                //else{
                        ok = RW.LPT_Read_Byte_Skip_Ack(dev_addr_tmp, data_addr, data_addr_cnt, &data_read);
                //}
        }
        char string[20];
        sprintf( string,"Read Data: %X", data_read);
        AnsiString str = (AnsiString)string;
        ShowMessage(str);
}
//---------------------------------------------------------------------------




void __fastcall TEngineerForm::SaveDialog_txt_hexSelectionChange(
      TObject *Sender)
{
        if(OpenDialog_txt_hex->FilterIndex==1){ //Text File
                OpenDialog_txt_hex->DefaultExt = String(".txt");
                OpenDialog_txt_hex->FileName="*.txt";
                //if (OpenDialog_txt_hex->FileName.AnsiPos(".")<1)　　
                //        OpenDialog_txt_hex->FileName=OpenDialog_txt_hex->FileName+".txt";
        }else if(OpenDialog_txt_hex->FilterIndex==2){ //Intel Hex File
                OpenDialog_txt_hex->DefaultExt = String(".hex");
                OpenDialog_txt_hex->FileName="*.hex";
                ///if (OpenDialog_txt_hex->FileName.AnsiPos(".")<1)　　
                //        OpenDialog_txt_hex->FileName=OpenDialog_txt_hex->FileName+".hex;
        }
}
//---------------------------------------------------------------------------

