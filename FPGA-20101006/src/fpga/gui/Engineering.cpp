//---------------------------------------------------------------------------
#include <vcl.h>
#include <lib/includeall.h>
#pragma hdrstop
#include "Engineering.h"
#include <i2c/core/ReadWriteFunc.h>
#include <i2c/core/PrintPortI2C.h>
#include "table_type.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#define PAC_SIZE 56


TEngineerForm *EngineerForm;
RW_Func RW;
bool connect = false;
String Connect_Msg = "";

char *Err_Msg_Card = "Card Connect Fail!";
char *Err_Msg_BAddr = "Please enter Byte Address.";
char *Err_Msg_Dev = "Please choose a Device Address.";
char *Err_Msg_WByte = "Please enter DATA to write";
char *Err_Msg_R = "Read Fail!";
char *Err_Msg_W = "Write Fail!";

// 20100608 新增, 詳細內容寫在'table_type.h'
ReadWrite_LUT RW_LUT;
// decode / encode data in difference Table type, Defined in table_type.h
bool Read_LUT(TLUT Addr_LUT, IntTbl & Out, ByteTbl In)
{
    if (Addr_LUT.BitNum() == 8) {
	RW_LUT.Read_LUT8(Out, In, Addr_LUT.Type());
    } else if (Addr_LUT.BitNum() == 4) {
	RW_LUT.Read_LUT4(Out, In, Addr_LUT.Type());
    } else if (Addr_LUT.BitNum() == 5) {	// 201007
	RW_LUT.Read_LUT5(Out, In, Addr_LUT.Type());
    } else if (Addr_LUT.BitNum() == 6) {
	RW_LUT.Read_LUT6(Out, In, Addr_LUT.Type());
    } else if (Addr_LUT.BitNum() == 10) {
	RW_LUT.Read_LUT10(Out, In, Addr_LUT.Type());
    } else if (Addr_LUT.BitNum() == 12) {
	RW_LUT.Read_LUT12(Out, In, Addr_LUT.Type());
    } else if (Addr_LUT.BitNum() == 16) {
	RW_LUT.Read_LUT16(Out, In, Addr_LUT.Type());
    } else
	Out.Tbl = NULL;
    return 1;
}

bool Write_LUT(TLUT Addr_LUT, ByteTbl & Out, IntTbl In)
{
    if (Addr_LUT.BitNum() == 8) {
	RW_LUT.Write_LUT8(Out, In, Addr_LUT.Type());
    } else if (Addr_LUT.BitNum() == 4) {
	RW_LUT.Write_LUT4(Out, In, Addr_LUT.Type());
    } else if (Addr_LUT.BitNum() == 5) {	// 201007
	RW_LUT.Write_LUT5(Out, In, Addr_LUT.Type());
    } else if (Addr_LUT.BitNum() == 6) {
	RW_LUT.Write_LUT6(Out, In, Addr_LUT.Type());
    } else if (Addr_LUT.BitNum() == 10) {
	RW_LUT.Write_LUT10(Out, In, Addr_LUT.Type());
    } else if (Addr_LUT.BitNum() == 12) {
	RW_LUT.Write_LUT12(Out, In, Addr_LUT.Type());
    } else if (Addr_LUT.BitNum() == 16) {
	RW_LUT.Write_LUT16(Out, In, Addr_LUT.Type());
    } else
	Out.Tbl = NULL;
    return 1;
}

//---------------------------------------------------------------------------
__fastcall TEngineerForm::TEngineerForm(TComponent * Owner)
:TForm(Owner)
{

}
__fastcall TEngineerForm::~TEngineerForm()
{

}

//---------------------------------------------------------------------------
void __fastcall TEngineerForm::FormCreate(TObject * Sender)
{
    int val;
    AnsiString tmp = "7c";
    Hex2Dec(tmp, &val);
    //StringGrid of device address
    char str[5];
    for (int i = 0; i < 7; i++) {
	sprintf(str, "%d", (int) ((double) val / pow(2, 7 - i)) % 2);
	sg_device_addr->Cells[i][0] = (AnsiString) str;
    }
    sg_device_addr->Cells[7][0] = "RW";

    //StringGrid of sequence R/W data show
    for (int i = 0; i <= 15; i++) {
	sprintf(str, "%02X", i);
	sg_seq_data->Cells[i + 1][0] = (AnsiString) str;
    }

}

//---------------------------------------------------------------------------

void __fastcall TEngineerForm::FormClose(TObject * Sender, TCloseAction & Action)
{
    Action = caFree;
    RW.USB_disconnect();
    if (hLib != NULL)
	LPT_disconnect();
}

//--------------------------------------------------------------------------
// 取得介面中Byte Read/Write的Address空格的值
// 輸出型式為unsigned char* (1 or 2 Byte)
// data_addr_cnt為紀錄Address的長度, 1 or 2 byte
bool TEngineerForm::Get_byte_addr(unsigned char *data_addr, int *data_addr_cnt)
{
    AnsiString dataString = edt_byte_addr->Text;
    if (dataString.Length() > 4 || dataString.Length() == 0) {
	ShowMessage("Too many digits on device address.");
    } else {
	unsigned short dataVal;
	int val;
	if (Hex2Dec(dataString, &val) == 0)
	    return 0;
	dataVal = val;
	data_addr[1] = dataVal / 256;	//high bit
	data_addr[0] = dataVal % 256;	//low bit
	int data_addr_len;
	if (cbo_mem_addr_size->ItemIndex <= 3)
	    data_addr_len = 1;
	else if (cbo_mem_addr_size->ItemIndex <= 8)
	    data_addr_len = 2;
	*data_addr_cnt = data_addr_len - 1;
    }

    return 1;
}

//---------------------------------------------------------------------------------
// 取得介面中Sequential Read/Write的Address空格的值,
// 即data_addr輸出型式為unsigned char* (1 or 2 Byte)
// data_addr_cnt為紀錄Address的長度, 1 or 2 byte
bool TEngineerForm::Get_seq_addr(unsigned char *data_addr, int *data_addr_cnt)
{
    AnsiString dataString = edt_seq_addr->Text;
    if (dataString.Length() > 4 || dataString.Length() == 0) {
	ShowMessage("Too many or few digits on device address.");
    } else {
	unsigned short dataVal;
	int val;
	if (Hex2Dec(dataString, &val) == 0)
	    return 0;
	dataVal = val;
	data_addr[1] = dataVal / 256;	//high bit
	data_addr[0] = dataVal % 256;	//low bit
	int data_addr_len;
	if (cbo_mem_addr_size->ItemIndex <= 3)
	    data_addr_len = 1;
	else if (cbo_mem_addr_size->ItemIndex <= 8)
	    data_addr_len = 2;
	*data_addr_cnt = data_addr_len - 1;
    }
    return 1;
}

//--------------------------------------------------------------------------
// 取得介面中的Device Address的數值,
bool TEngineerForm::Get_device_addr(unsigned char *dev, int *dev_addr_cnt)
{
    bool ok;
    int val;
    if (rg_device_addr_sel->ItemIndex == 0) {	//single TCON
	*dev_addr_cnt = 1;
	ok = Hex2Dec(edt_addr_tcon_s->Text, &val);
	dev[0] = (unsigned char) val;
    } else if (rg_device_addr_sel->ItemIndex == 1) {	//dual TCON
	*dev_addr_cnt = 2;
	ok = Hex2Dec(edt_addr_tcon_dm->Text, &val);
	dev[0] = (unsigned char) val;
	bool ok1 = Hex2Dec(edt_addr_tcon_ds->Text, &val);
	ok = ok & ok1;
	dev[1] = (unsigned char) val;
    } else if (rg_device_addr_sel->ItemIndex == 2) {	//single EEPROM
	*dev_addr_cnt = 1;
	ok = Hex2Dec(edt_addr_EEP->Text, &val);
	dev[0] = (unsigned char) val;
    } else if (rg_device_addr_sel->ItemIndex == 3) {
	*dev_addr_cnt = 1;
	ok = Hex2Dec(edt_addr_OTP->Text, &val);
	dev[0] = (unsigned char) val;
    } else			//may add quad-TCON here
	return 0;

    return ok;
}

//--------------------------------------------------------------------------
bool TEngineerForm::B_write(unsigned char dev_addr)	//將介面上的Byte數值寫入
{
    int sel;
    unsigned char data_addr[2];
    int data_addr_cnt;
    unsigned char write_data;
    bool card_sel;

    if (Get_byte_addr(data_addr, &data_addr_cnt) == 0) {	//取得介面上byte address
	ShowMessage(Err_Msg_BAddr);
	return 0;
    }

    if (Get_write_data(&write_data) == 0) {	//取得介面上write byte
	ShowMessage(Err_Msg_WByte);
	return 0;
    }

    int ok;
    unsigned char dev_addr_tmp;
    SetDeviceAddr(dev_addr, &dev_addr_tmp, data_addr, data_addr_cnt);
    if (rg_i2c_card_sel->ItemIndex == 0) {	//USB
	int cnnct_ok = RW.USB_connect(rg_power->ItemIndex, rg_speed->ItemIndex);	//201007 for Vdd drop
	if (!cnnct_ok)
	    return 0;
	RW.USB_write(dev_addr_tmp, data_addr, data_addr_cnt, &write_data, 1);
    } else {			//LPT
	ok = RW.LPT_Write(dev_addr_tmp, data_addr, data_addr_cnt, &write_data, 1);
	if (ok != 1)		//傳送失敗, 再傳一次
	    ok = RW.LPT_Write(dev_addr_tmp, data_addr, data_addr_cnt, &write_data, 1);
	if (ok != 1) {
	    if (ok == -1)
		ShowMessage("Device address Send fail!");
	    else if (ok == -2)
		ShowMessage("Data address Send fail!");
	    return 0;
	}
    }

    //if(rg_device_addr_sel->ItemIndex==2)
    Sleep(11);
    return 1;
}

//--------------------------------------------------------------------------
bool TEngineerForm::B_read(unsigned char &data_read, unsigned char dev_addr)	//將欲讀出的Byte值讀出來
{
    unsigned char data_addr[2];	//Word address, may be 1 or 2 Byte
    int data_addr_cnt;		//number of byte in data address

    if (Get_byte_addr(data_addr, &data_addr_cnt) == 0) {	//取得介面上byte address
	ShowMessage(Err_Msg_BAddr);
	return NULL;
    }
    int ok;
    unsigned char dev_addr_tmp;

    SetDeviceAddr(dev_addr, &dev_addr_tmp, data_addr, data_addr_cnt);
    if (rg_i2c_card_sel->ItemIndex == 0) {	// USB
	int cnnct_ok = RW.USB_connect(rg_power->ItemIndex, rg_speed->ItemIndex);	//201007 for Vdd drop
	if (!cnnct_ok)
	    return 0;
	ok = RW.USB_seq_read_P1(dev_addr_tmp, data_addr, data_addr_cnt, &data_read, 1, 1);
	connect = ok;
    } else {			// LPT
	ok = RW.LPT_Read_Byte(dev_addr_tmp, data_addr, data_addr_cnt, &data_read);
	if (ok != 1)		//傳送失敗, 再傳一次
	    ok = RW.LPT_Read_Byte(dev_addr_tmp, data_addr, data_addr_cnt, &data_read);
	if (ok != 1) {
	    /*if(connect){
	       if(ok==-1)
	       ShowMessage("Device address Send fail!");
	       else if(ok==-2)
	       ShowMessage("Data address Send fail!");
	       else if(ok==0)
	       ShowMessage("Data Send fail!");
	       } */
	    return 0;
	} else
	    connect = 1;
    }
    return ok;
}

//--------------------------------------------------------------------------

// 讀取Byte
bool TEngineerForm::SetRead_Byte(TBit Addr_Bit, unsigned char *read_val)
{
    // 將要讀取的data Address顯示到介面上
    AnsiString str_addr;
    Dec2Hex(Addr_Bit.Addr(), &str_addr);
    edt_byte_addr->Text = str_addr;

    unsigned char dev_addr[4];
    //device read/write address, extend to 4 devices set at a time
    int dev_addr_cnt;		//number of device
    if (Get_device_addr(dev_addr, &dev_addr_cnt) == 0) {	//取得介面上device address
	ShowMessage(Err_Msg_Dev);
	return NULL;
    }
    unsigned char *data_read = new unsigned char[dev_addr_cnt];
    bool dif = 0;
    for (int i = 0; i < dev_addr_cnt; i++) {	//對每個device address動作
	bool ok = 0;
	int cnt = 0;
	while (ok == 0 && cnt < 3) {
	    ok = B_read(data_read[i], dev_addr[i]);	// 讀取Byte
	    cnt++;
	}
	//if(ok==0){ delete [] data_read; return 0;}

	// 將得到的Byte數值做修正, (根據參數排在那些bit做修正)
	data_read[i] = data_read[i] & ~(Addr_Bit.StbBit());
	data_read[i] = data_read[i] >> Addr_Bit.ShiftBit();

	if (i >= 1)
	    if (data_read[i] != data_read[i - 1])
		dif = 1;
    }
    *read_val = data_read[0];
    if (dif == 1)
	ShowMessage(Addr_Bit.Name() + "has difference value.");
    delete[]data_read;
    return 1;
}

//--------------------------------------------------------------------------

// 寫入Byte, Addr_Bit為Address資訊, set_val為寫入的資料
bool TEngineerForm::SetWrite_Byte(TBit Addr_Bit, int set_val)
{
    // 寫入data以Byte為單位, 由於可能寫入某幾個bit,
    // 因此需要先讀取Byte, 再加上寫入data合成可寫入的Byte

    // 將要寫入的data Address顯示到介面上
    AnsiString str_addr;
    Dec2Hex(Addr_Bit.Addr(), &str_addr);
    edt_byte_addr->Text = str_addr;

    unsigned char t_data;
    bool ok_w = 1, ok_t;
    unsigned char dev_addr[4];
    int dev_addr_cnt;
    if (Get_device_addr(dev_addr, &dev_addr_cnt) == 0) {	//取得介面上device address
	ShowMessage(Err_Msg_Dev);
	return 0;
    }
    for (int i = 0; i < dev_addr_cnt; i++) {	//對每個device address動作
	bool ok = 0;
	int cnt = 0;
	while (ok == 0 && cnt < 3) {
	    ok = B_read(t_data, dev_addr[i]);	//讀取Byte
	    cnt++;
	}
	if (ok == 0) {
	    ShowMessage("Fail to retrieve data in device, cannot write!");
	    return 0;
	}
	// 將得到的Byte數值做修正, (根據data排在那些bit做修正)
	t_data = t_data & Addr_Bit.StbBit();
	set_val = set_val & (int) pow(2, Addr_Bit.BitNum()) - 1;
	t_data = t_data | (set_val << Addr_Bit.ShiftBit());

	// 根據排列的bit位置,計算寫入的Byte
	AnsiString str;
	Dec2Hex((int) t_data, &str);
	edt_byte_wdata->Text = str;
	ok_t = B_write(dev_addr[i]);	//寫入Byte
	ok_w = ok_w || ok_t;
    }

    if (ok_w)
	return 1;
    else
	return 0;
}

//---------------------------------------------------------------------------

// 連續讀取data或讀取Table
// 20100608 revise, 以 Read_LUT 轉換 Byte 為 Data, 並且可以寫chksum Byte
bool TEngineerForm::SetRead_PG(TLUT Addr_LUT, int *Read_table, bool IsChkSum)
{				// IsChkSum: 1 要加checksum, 0 不用加checksum

    int chk_len;		// 預留的Checksum長度
    if (IsChkSum == true) {
	chk_len = 2;
    } else {
	chk_len = 0;
    }
    int data_len;
    // 計算table拆成Byte後的長度, Addr_LUT.LutNum()是table當中的數值個數
    if (Addr_LUT.BitNum() == 4 && Addr_LUT.Type() == 1)
	data_len = ceil(Addr_LUT.LutNum() / 2);
    else if (Addr_LUT.BitNum() == 4 && Addr_LUT.Type() == 2)
	data_len = Addr_LUT.LutNum();
    else if (Addr_LUT.BitNum() == 8 || Addr_LUT.BitNum() == 6 || Addr_LUT.BitNum() == 5)
	data_len = Addr_LUT.LutNum();	// 201007
    else if (Addr_LUT.BitNum() == 12)
	data_len = ceil((double) Addr_LUT.LutNum() * 3 / 2);
    else if (Addr_LUT.BitNum() == 10 && (Addr_LUT.Type() == 1 || Addr_LUT.Type() == 2))
	data_len = Addr_LUT.LutNum() * 2;
    else if (Addr_LUT.BitNum() == 10 && (Addr_LUT.Type() == 3 || Addr_LUT.Type() == 4))
	data_len = ceil((double) Addr_LUT.LutNum() * 5 / 4);
    else if (Addr_LUT.BitNum() == 16)
	data_len = Addr_LUT.LutNum() * 2;

    // Set Table Start Address & length (in Bytes)to Interface
    String Addr_str;
    Dec2Hex(Addr_LUT.Addr() - chk_len, &Addr_str);
    edt_seq_addr->Text = Addr_str;
    edt_seq_len->Text = IntToStr(data_len + chk_len);

    unsigned char *read_data = new unsigned char[data_len + chk_len];
    bool ok = pg_read(read_data, 1);	// Read Bytes of data
    // bool pg_read(unsigned char *data_read, bool IsShow),
    // return value = false means read fail, otherwise read success,
    // when IsShow is true, it means value will show in table of Engineer->Configuration

    for (int i = 0; i < Addr_LUT.LutNum(); i++)
	Read_table[i] = 0;
    if (chk_len > 0) {
	for (int i = 0; i < data_len; i++)
	    read_data[i] = read_data[i + chk_len];
    }
    IntTbl Out;
    Out.Tbl = Read_table;
    Out.Len = Addr_LUT.LutNum();

    ByteTbl In;
    In.Tbl = read_data;
    In.Len = data_len;

    // 由Byte排列成原本的數值範圍
    bool ok1 = Read_LUT(Addr_LUT, Out, In);
    ok = ok && ok1;

    delete[]read_data;
    if (ok == 0 | Read_table == NULL)
	return 0;
    return 1;
}

//---------------------------------------------------------------------------
// DG or C3d read
// 20100608 revise, 以 Read_LUT 轉換 byte 為 data, 並且可以寫chksum Byte
bool TEngineerForm::SetRead_DG(TLUT * Addr_LUT, int **DG_table, int LUT_Nbr, bool IsChkSum)
{				// IsChkSum: 1 要加checksum, 0 不用加checksum
    // Addr_LUT[0]: DG_R Address,  Addr_LUT[1]: DG_G Address,
    // Addr_LUT[2]: DG_B Address,  Addr_LUT[3]: DG_W Address,
    // DG_table: 4*257的矩陣 或是 3*256... ,
    // LUT_Nbr =3 RGB table,LUT_Nbr =4 RGBW table

    int chk_len;		// 預留的Checksum長度
    if (IsChkSum == true) {
	chk_len = 2;
    } else {
	chk_len = 0;
    }

    int read_len = chk_len;

    // 計算table拆成Byte後的長度, Addr_LUT.LutNum()是table當中的數值個數
    int *Byte_len = new int[LUT_Nbr];
    for (int i = 0; i < LUT_Nbr; i++) {	// 計算不同bit數的table, 所有的byte數
	if (Addr_LUT[i].BitNum() == 8)
	    Byte_len[i] = (int) ceil((double) Addr_LUT[i].LutNum());
	else if (Addr_LUT[i].BitNum() == 10 && (Addr_LUT[i].Type() == 3 || Addr_LUT[i].Type() == 4))
	    Byte_len[i] = (int) ceil((double) Addr_LUT[i].LutNum() * 5 / 4);
	else if (Addr_LUT[i].BitNum() == 12)
	    Byte_len[i] = (int) ceil((double) Addr_LUT[i].LutNum() * 3 / 2);
	else if (Addr_LUT[i].BitNum() == 16)
	    Byte_len[i] = (int) ceil((double) Addr_LUT[i].LutNum() * 2);
	else
	    ShowMessage("Table Bit Error");

	read_len += Byte_len[i];
    }

    int start_addr = Addr_LUT[0].Addr() - chk_len;

    unsigned char *read_data = new unsigned char[read_len];
    for (int i = 0; i < read_len; i++)
	read_data[i] = 0;

    unsigned char **read_data_C = new unsigned char *[LUT_Nbr];
    for (int i = 0; i < LUT_Nbr; i++)
	read_data_C[i] = new unsigned char[Byte_len[i]];

    // Set Table Start Address & length (in Bytes) to Interface
    String Addr_str;
    Dec2Hex(start_addr, &Addr_str);
    edt_seq_addr->Text = Addr_str;
    edt_seq_len->Text = IntToStr(read_len);
    bool ok = pg_read(read_data, 1);	// Read Bytes of data
    bool ok1 = true;
    int read_data_idx = chk_len;
    for (int i = 0; i < LUT_Nbr; i++) {	// DG 分R,G,B,W部份計算, C3D 分R,G,B,W 計算, DCR 分BL,DIM,Histo
	for (int j = 0; j < Addr_LUT[i].LutNum(); j++) {
	    DG_table[i][j] = -1;
	}

	for (int j = 0; j < Byte_len[i]; j++) {
	    read_data_C[i][j] = read_data[read_data_idx + j];
	}
	read_data_idx += Byte_len[i];

	// 轉換12 bit=>10 bit 開始
	IntTbl Out;
	Out.Tbl = DG_table[i];
	Out.Len = Addr_LUT[i].LutNum();

	ByteTbl In;
	In.Tbl = read_data_C[i];
	In.Len = Byte_len[i];

	// 由Byte排列成原本的數值範圍
	ok1 = Read_LUT(Addr_LUT[i], Out, In);
	ok = ok & ok1;
    }

    delete[]read_data;
    for (int i = 0; i < LUT_Nbr; i++) {
	delete[]read_data_C[i];
    }
    delete[]read_data_C;

    if (ok == 0)
	return 0;
    return 1;
}

//---------------------------------------------------------------------------

// 連續寫入data或寫入Table
// 20100608 revise, 以 Write_LUT 轉換 data 為 Byte, 並且可以寫chksum Byte
bool TEngineerForm::SetWrite_PG(TLUT Addr_LUT, int *write_table, bool IsChkSum)
{				// IsChkSum: 1 要加checksum, 0 不用加checksum
    int chk_len;
    if (IsChkSum) {		// 預留的Checksum長度
	chk_len = 2;
    } else {
	chk_len = 0;
    }

    int data_len;
    // 計算table拆成Byte後的長度, Addr_LUT.LutNum()是table當中的數值個數
    if (Addr_LUT.BitNum() == 4 && Addr_LUT.Type() == 1)
	data_len = ceil(Addr_LUT.LutNum() / 2);
    else if (Addr_LUT.BitNum() == 4 && Addr_LUT.Type() == 2)
	data_len = Addr_LUT.LutNum();
    else if (Addr_LUT.BitNum() == 8 || Addr_LUT.BitNum() == 6 || Addr_LUT.BitNum() == 5)
	data_len = Addr_LUT.LutNum();	// 201007
    else if (Addr_LUT.BitNum() == 12)
	data_len = ceil((double) Addr_LUT.LutNum() * 3 / 2);
    else if (Addr_LUT.BitNum() == 10 && (Addr_LUT.Type() == 1 || Addr_LUT.Type() == 2))
	data_len = Addr_LUT.LutNum() * 2;
    else if (Addr_LUT.BitNum() == 10 && (Addr_LUT.Type() == 3 || Addr_LUT.Type() == 4))
	data_len = ceil((double) Addr_LUT.LutNum() * 5 / 4);
    else if (Addr_LUT.BitNum() == 16)
	data_len = Addr_LUT.LutNum() * 2;

    unsigned char *write_data = new unsigned char[data_len];
    ByteTbl Out;
    Out.Tbl = write_data;
    Out.Len = data_len;

    IntTbl In;
    In.Tbl = write_table;
    In.Len = Addr_LUT.LutNum();

    Write_LUT(Addr_LUT, Out, In);
    ByteTbl Out_tmp;
    if (IsChkSum) {		// 需要計算checksum
	int chksum = 0;
	Out_tmp.Len = Out.Len + chk_len;
	Out_tmp.Tbl = new unsigned char[Out_tmp.Len];
	for (int i = Out.Len - 1; i >= 0; i--) {
	    Out_tmp.Tbl[i + 2] = Out.Tbl[i];
	    chksum += int (Out.Tbl[i]);
	}
	Out_tmp.Tbl[0] = (int) floor((double) chksum / 256) % 256;
	Out_tmp.Tbl[1] = chksum % 256;

	// 將寫入數值顯示到介面上
	Set_seq_data(Out_tmp.Tbl, Out_tmp.Len, Addr_LUT.Addr() - chk_len);
	delete[]Out_tmp.Tbl;
    } else
	// 將寫入數值顯示到介面上
	Set_seq_data(Out.Tbl, Out.Len, Addr_LUT.Addr());
    delete Out.Tbl;
    if (pg_write()) {		// 寫入table數值到device
	Sleep(10);		// write buffer time
	return 1;
    } else {
	Sleep(10);
	return 0;
    }
}

bool TEngineerForm::SetWrite_PG(TLUT Addr_LUT, int *write_table, bool IsChkSum, bool MSB_first)
{				// IsChkSum: 1 要加checksum, 0 不用加checksum
    int chk_len;
    if (IsChkSum) {		// 預留的Checksum長度
	chk_len = 2;
    } else {
	chk_len = 0;
    }

    int data_len;
    // 計算table拆成Byte後的長度, Addr_LUT.LutNum()是table當中的數值個數
    if (Addr_LUT.BitNum() == 4 && Addr_LUT.Type() == 1)
	data_len = ceil(Addr_LUT.LutNum() / 2);
    else if (Addr_LUT.BitNum() == 4 && Addr_LUT.Type() == 2)
	data_len = Addr_LUT.LutNum();
    else if (Addr_LUT.BitNum() == 8 || Addr_LUT.BitNum() == 6 || Addr_LUT.BitNum() == 5)
	data_len = Addr_LUT.LutNum();	// 201007
    else if (Addr_LUT.BitNum() == 12)
	data_len = ceil((double) Addr_LUT.LutNum() * 3 / 2);
    else if (Addr_LUT.BitNum() == 10 && (Addr_LUT.Type() == 1 || Addr_LUT.Type() == 2))
	data_len = Addr_LUT.LutNum() * 2;
    else if (Addr_LUT.BitNum() == 10 && (Addr_LUT.Type() == 3 || Addr_LUT.Type() == 4))
	data_len = ceil((double) Addr_LUT.LutNum() * 5 / 4);
    else if (Addr_LUT.BitNum() == 16)
	data_len = Addr_LUT.LutNum() * 2;

    unsigned char *write_data = new unsigned char[data_len];
    ByteTbl Out;
    Out.Tbl = write_data;
    Out.Len = data_len;

    IntTbl In;
    In.Tbl = write_table;
    In.Len = Addr_LUT.LutNum();

    Write_LUT(Addr_LUT, Out, In);
    ByteTbl Out_tmp;
    if (IsChkSum) {		// 需要計算checksum
	int chksum = 0;
	Out_tmp.Len = Out.Len + chk_len;
	Out_tmp.Tbl = new unsigned char[Out_tmp.Len];
	for (int i = Out.Len - 1; i >= 0; i--) {
	    Out_tmp.Tbl[i + 2] = Out.Tbl[i];
	    chksum += int (Out.Tbl[i]);
	}
	if (MSB_first) {
	    Out_tmp.Tbl[0] = (int) floor((double) chksum / 256) % 256;
	    Out_tmp.Tbl[1] = chksum % 256;
	} else {
	    Out_tmp.Tbl[0] = chksum % 256;
	    Out_tmp.Tbl[1] = (int) floor((double) chksum / 256) % 256;
	}
	// 將寫入數值顯示到介面上
	Set_seq_data(Out_tmp.Tbl, Out_tmp.Len, Addr_LUT.Addr() - chk_len);
	delete[]Out_tmp.Tbl;
    } else
	// 將寫入數值顯示到介面上
	Set_seq_data(Out.Tbl, Out.Len, Addr_LUT.Addr());
    delete Out.Tbl;
    if (pg_write()) {		// 寫入table數值到device
	Sleep(10);		// write buffer time
	return 1;
    } else {
	Sleep(10);
	return 0;
    }
}


// DG與C3D table 使用, 分RGB or RGBW連續寫入 (DG or C3D use)
// 20100608 revise, 以 Write_LUT 轉換 data 為 Byte, 並且可以寫chksum Byte
bool TEngineerForm::SetWrite_DG(TLUT * Addr_LUT, int **lut, int LUT_Nbr, bool IsChkSum)
{				// IsChkSum: 1 要加checksum, 0 不用加checksum
    int chk_len;
    if (IsChkSum) {		// 預留的Checksum長度
	chk_len = 2;
    } else {
	chk_len = 0;
    }

    // 計算table拆成Byte後的長度, Addr_LUT.LutNum()是table當中的數值個數
    int *data_len = new int[LUT_Nbr];
    for (int i = 0; i < LUT_Nbr; i++) {	// 計算不同bit數的table, 所有的byte數
	if (Addr_LUT[i].BitNum() == 8)
	    data_len[i] = (int) ceil((double) Addr_LUT[i].LutNum());
	else if (Addr_LUT[i].BitNum() == 10 && (Addr_LUT[i].Type() == 3 || Addr_LUT[i].Type() == 4))
	    data_len[i] = (int) ceil((double) Addr_LUT[i].LutNum() * 5 / 4);
	else if (Addr_LUT[i].BitNum() == 12)
	    data_len[i] = (int) ceil((double) Addr_LUT[i].LutNum() * 3 / 2);
	else if (Addr_LUT[i].BitNum() == 16)
	    data_len[i] = (int) ceil((double) Addr_LUT[i].LutNum() * 2);
	else
	    ShowMessage("Table Bit Error");
    }

    ByteTbl *Out = new ByteTbl[LUT_Nbr];	// in/ out package
    IntTbl *In = new IntTbl[LUT_Nbr];
    for (int i = 0; i < LUT_Nbr; i++) {
	In[i].Len = Addr_LUT[i].LutNum();
	In[i].Tbl = lut[i];
	Out[i].Len = data_len[i];
	Out[i].Tbl = new unsigned char[data_len[i]];
    }
    for (int i = 0; i < LUT_Nbr; i++) {	// // 將table的數值轉成Byte排列
	Write_LUT(Addr_LUT[i], Out[i], In[i]);
    }

    ByteTbl Out_tmp;
    Out_tmp.Len = chk_len;
    for (int i = 0; i < LUT_Nbr; i++)
	Out_tmp.Len += Out[i].Len;
    Out_tmp.Tbl = new unsigned char[Out_tmp.Len];

    // 計算checksum
    int chksum = 0;
    int ci = chk_len;		// combine index
    for (int lut_n = 0; lut_n < LUT_Nbr; lut_n++) {
	for (int i = 0; i < Out[lut_n].Len; i++, ci++) {
	    Out_tmp.Tbl[ci] = Out[lut_n].Tbl[i];
	    chksum += int (Out_tmp.Tbl[ci]);
	}
    }
    if (IsChkSum) {
	Out_tmp.Tbl[0] = (int) floor((double) chksum / 256) % 256;
	Out_tmp.Tbl[1] = chksum % 256;
    }
    // 將寫入數值顯示到介面上
    Set_seq_data(Out_tmp.Tbl, Out_tmp.Len, Addr_LUT[0].Addr() - chk_len);

    for (int i = 0; i < LUT_Nbr; i++)
	delete[]Out[i].Tbl;
    delete[]Out;
    delete[]In;
    delete[]Out_tmp.Tbl;

    if (pg_write()) {		// 寫入table數值到device
	Sleep(10);		// write buffer time
	return 1;
    } else {
	Sleep(10);
	return 0;
    }
}

//---------------------------------------------------------------------------
// 201007 revise, checksum MSB,LSB 2 kinds arrange
bool TEngineerForm::SetWrite_DG(TLUT * Addr_LUT, int **lut, int LUT_Nbr, bool IsChkSum,
				bool MSB_first)
{				// IsChkSum: 1 要加checksum, 0 不用加checksum
    int chk_len;
    if (IsChkSum) {		// 預留的Checksum長度
	chk_len = 2;
    } else {
	chk_len = 0;
    }

    // 計算table拆成Byte後的長度, Addr_LUT.LutNum()是table當中的數值個數
    int *data_len = new int[LUT_Nbr];
    for (int i = 0; i < LUT_Nbr; i++) {	// 計算不同bit數的table, 所有的byte數
	if (Addr_LUT[i].BitNum() == 8)
	    data_len[i] = (int) ceil((double) Addr_LUT[i].LutNum());
	else if (Addr_LUT[i].BitNum() == 10 && (Addr_LUT[i].Type() == 3 || Addr_LUT[i].Type() == 4))
	    data_len[i] = (int) ceil((double) Addr_LUT[i].LutNum() * 5 / 4);
	else if (Addr_LUT[i].BitNum() == 12)
	    data_len[i] = (int) ceil((double) Addr_LUT[i].LutNum() * 3 / 2);
	else if (Addr_LUT[i].BitNum() == 16)
	    data_len[i] = (int) ceil((double) Addr_LUT[i].LutNum() * 2);
	else
	    ShowMessage("Table Bit Error");
    }

    ByteTbl *Out = new ByteTbl[LUT_Nbr];	// in/ out package
    IntTbl *In = new IntTbl[LUT_Nbr];
    for (int i = 0; i < LUT_Nbr; i++) {
	In[i].Len = Addr_LUT[i].LutNum();
	In[i].Tbl = lut[i];
	Out[i].Len = data_len[i];
	Out[i].Tbl = new unsigned char[data_len[i]];
    }
    for (int i = 0; i < LUT_Nbr; i++) {	// // 將table的數值轉成Byte排列
	Write_LUT(Addr_LUT[i], Out[i], In[i]);
    }

    ByteTbl Out_tmp;
    Out_tmp.Len = chk_len;
    for (int i = 0; i < LUT_Nbr; i++)
	Out_tmp.Len += Out[i].Len;
    Out_tmp.Tbl = new unsigned char[Out_tmp.Len];

    // 計算checksum
    int chksum = 0;
    int ci = chk_len;		// combine index
    for (int lut_n = 0; lut_n < LUT_Nbr; lut_n++) {
	for (int i = 0; i < Out[lut_n].Len; i++, ci++) {
	    Out_tmp.Tbl[ci] = Out[lut_n].Tbl[i];
	    chksum += int (Out_tmp.Tbl[ci]);
	}
    }

    if (IsChkSum) {
	if (MSB_first) {
	    Out_tmp.Tbl[0] = (int) floor((double) chksum / 256) % 256;
	    Out_tmp.Tbl[1] = chksum % 256;
	} else {
	    Out_tmp.Tbl[0] = chksum % 256;
	    Out_tmp.Tbl[1] = (int) floor((double) chksum / 256) % 256;
	}
    }
    // 將寫入數值顯示到介面上
    Set_seq_data(Out_tmp.Tbl, Out_tmp.Len, Addr_LUT[0].Addr() - chk_len);

    for (int i = 0; i < LUT_Nbr; i++)
	delete[]Out[i].Tbl;
    delete[]Out;
    delete[]In;
    delete[]Out_tmp.Tbl;

    if (pg_write()) {		// 寫入table數值到device
	Sleep(10);		// write buffer time
	return 1;
    } else {
	Sleep(10);
	return 0;
    }
}

//---------------------------------------------------------------------------
bool TEngineerForm::btn_byte_readClick()
{
    unsigned char dev_addr[4];
    //device read/write address, extend to 4 devices set at a time
    int dev_addr_cnt;		//number of device
    if (Get_device_addr(dev_addr, &dev_addr_cnt) == 0) {	//取得介面上device address
	ShowMessage(Err_Msg_Dev);
	return NULL;
    }
    unsigned char *data_read = new unsigned char[dev_addr_cnt];

    bool dif = 0;
    char str[10] = "";
    for (int i = 0; i < dev_addr_cnt; i++) {	//對每個device address動作
	bool ok = 0;
	int cnt = 0;
	while (ok == 0 && cnt < 3) {
	    ok = B_read(data_read[i], dev_addr[i]);
	    cnt++;
	}
	char str_t[2];
	if (ok == 0) {
	    sprintf(str_t, "%02X", dev_addr[i]);
	    strncat(str, str_t, 2);
	}
	if (i >= 1)
	    if (data_read[i] != data_read[i - 1])
		dif = 1;
    }
    if (str[0] != '\0') {
	Connect_Msg = (String) str + " Fail!";
	MainForm->StatusBar1->Panels->Items[0]->Text = "Connection: " + Connect_Msg;
	return 0;
    }
    char R_string[15];
    if (dif) {
	if (dev_addr_cnt == 2)
	    sprintf(R_string, "%X,%X", data_read[0], data_read[1]);
	else if (dev_addr_cnt == 3)
	    sprintf(R_string, "%X,%X,%X", data_read[0], data_read[1], data_read[2]);
	else if (dev_addr_cnt == 4)
	    sprintf(R_string, "%X,%X,%X,%X", data_read[0], data_read[1], data_read[2],
		    data_read[3]);
    } else {
	sprintf(R_string, "%X", data_read[0]);
    }
    AnsiString Rstr = (AnsiString) R_string;
    edt_byte_rdata->Text = Rstr;
    delete[]data_read;
    return 1;
}

void __fastcall TEngineerForm::btn_byte_readClick(TObject * Sender)
{
    //Check card connection
    if (btn_connect_card->Enabled == true) {
	ShowMessage(Err_Msg_Card);
	return;
    }

    btn_byte_read->Enabled = false;
    if (!btn_byte_readClick()) {
	ShowMessage(Err_Msg_R);
	edt_byte_rdata->Text = "";
    }
    btn_byte_read->Enabled = true;
}

//---------------------------------------------------------------------------
// 計算下次使用的data address
void Add_val2_data_ad(unsigned char *data_addr, int data_addr_cnt, int add_num)
{
    int addr_val = 0;

    for (int i = 1; i >= 0; i--) {
	addr_val *= 256;
	addr_val += data_addr[i];
    }
    addr_val += add_num;
    for (int i = 0; i <= 1; i++) {
	data_addr[i] = addr_val % 256;
	addr_val = addr_val / 256;
    }
}

//---------------------------------------------------------------------------
// Compose part of read data
void Set2data_read(unsigned char *data_read, unsigned char *data_read_tmp, int pck_cnt, int num)
{
    for (int i = 0; i < num; i++)
	data_read[pck_cnt * PAC_SIZE + i] = data_read_tmp[i];
}

//---------------------------------------------------------------------------
// set write buffer
void Set_write_buf(unsigned char *data_write, unsigned char *data_write_tmp, int drop, int num)
{
    for (int i = 0; i < num; i++)
	data_write_tmp[i] = data_write[drop + i];
}

//---------------------------------------------------------------------------
void TEngineerForm::Clear_sg_seq_data()
{
    for (int i = 1; i < (sg_seq_data->ColCount); i++)
	for (int j = 1; j < (sg_seq_data->RowCount); j++)
	    sg_seq_data->Cells[i][j] = "";
}

//---------------------------------------------------------------------------


// page read,  retrieve Device address, Data address and Data from interface
bool TEngineerForm::pg_read(unsigned char *data_read, bool IsShow)
{
    Clear_sg_seq_data();
    int sel;
    unsigned char dev_addr[4];
    int dev_addr_cnt;		//device address以byte儲存
    unsigned char data_addr[2];
    int data_addr_cnt;		//memory address以byte儲存
    unsigned char *data_read_tmp = new unsigned char[PAC_SIZE];
    int data_len;
    bool card_sel;

    // 從介面取sequential Read/ Write 的Data Address
    if (Get_seq_addr(data_addr, &data_addr_cnt) == 0) {
	ShowMessage(Err_Msg_BAddr);
	return 0;
    }
    // 從介面取device Address
    if (Get_device_addr(dev_addr, &dev_addr_cnt) == 0) {
	ShowMessage(Err_Msg_Dev);
	return 0;
    }
    // 從介面取Data Length
    data_len = StrToInt(edt_seq_len->Text);
    int tmp_len;

    unsigned char dev_addr_tmp;

    int ok;			//read ok or not
    int pck_cnt;		//record the number of package transmit
    unsigned char data_addr_tmp[2];

    for (int i = 0; i < dev_addr_cnt; i++) {	// 對所有的Device Address
	tmp_len = data_len;
	pck_cnt = 0;
	for (int i = 0; i <= data_addr_cnt; i++)
	    data_addr_tmp[i] = data_addr[i];
	// 將Device Address與Data Address合成Device Address Byte
	SetDeviceAddr(dev_addr[i], &dev_addr_tmp, data_addr_tmp, data_addr_cnt);
	if (rg_i2c_card_sel->ItemIndex == 0) {	//USB
	    int cnnct_ok = RW.USB_connect(rg_power->ItemIndex, rg_speed->ItemIndex);	//201007 for Vdd drop
	    if (!cnnct_ok)
		return 0;
	    if (tmp_len < PAC_SIZE) {	// 一個封包可讀完
		ok = RW.USB_seq_read_P1(dev_addr_tmp, data_addr_tmp,
					data_addr_cnt, data_read, tmp_len, 1);
		// 1st package, defined in ReadWriteFunc.cpp
		if (ok == 0) {
		    ShowMessage(Err_Msg_R);
		    delete[]data_read_tmp;
		    return 0;
		}

	    } else {		// 分成多個封包讀取
		// 1st package 'USB_seq_read_P1', defined in ReadWriteFunc.cpp
		ok = RW.USB_seq_read_P1(dev_addr_tmp, data_addr_tmp,
					data_addr_cnt, data_read_tmp, PAC_SIZE, 0);

		if (ok == 0) {
		    ShowMessage(Err_Msg_R);
		    delete[]data_read_tmp;
		    return 0;
		}
		// 將讀取的data放到'data_read'
		Set2data_read(data_read, data_read_tmp, pck_cnt, PAC_SIZE);
		pck_cnt++;
		tmp_len -= PAC_SIZE;

		while (tmp_len > PAC_SIZE) {	// 需要純data封包
		    // data 封包'USB_r_Data_Package'
		    ok = RW.USB_r_Data_Package(data_read_tmp, PAC_SIZE, 0);

		    // 將讀取的data放到'data_read'
		    Set2data_read(data_read, data_read_tmp, pck_cnt, PAC_SIZE);
		    tmp_len -= PAC_SIZE;
		    pck_cnt++;
		    /*if(ok==0){
		       ShowMessage(Err_Msg_R);
		       delete [] data_read_tmp;
		       return 0;
		       } */

		}
		// 最後一個data封包
		ok = RW.USB_r_Data_Package(data_read_tmp, tmp_len, 1);
		/* if(ok==0){ //最後一個package收不到正確的status
		   ShowMessage(Err_Msg_R);
		   delete [] data_read_tmp;
		   return 0;
		   } */

		// 將讀取的data放到'data_read'
		Set2data_read(data_read, data_read_tmp, pck_cnt, tmp_len);
	    }
	} else {
	    //LPT
	    ok = RW.LPT_Read_seq(dev_addr_tmp, data_addr, data_addr_cnt, data_read, data_len);
	    if (ok != 1) {
		if (ok == -1)
		    ShowMessage("Device address Send fail!");
		else if (ok == -2)
		    ShowMessage("Data address Send fail!");
		else if (ok == 0)
		    ShowMessage("Data Send fail!");
		delete[]data_read_tmp;
		return 0;
	    }
	}
    }

    // 在Engineering 介面上顯示checksum
    int readChksum = 0;
    for (int i = 0; i < data_len; i++)
	readChksum += (int) data_read[i];
    char string[10];
    sprintf(string, "%X", readChksum);
    AnsiString str = (AnsiString) string;
    stb_page_operat->Panels->Items[1]->Text = "Read Checksum: " + str;

    if (IsShow == true) {	// 顯示讀取的數值到Engineering 介面
	int data_addr_val;
	data_addr_val = data_addr[0] + data_addr[1] * 256;
	Set_seq_data(data_read, data_len, data_addr_val);
    }
    if (data_read_tmp != NULL)
	delete[]data_read_tmp;
    return 1;
}

//---------------------------------------------------------------------------
void __fastcall TEngineerForm::btn_seq_readClick(TObject * Sender)
{
    //Check card connection
    if (btn_connect_card->Enabled == true) {
	ShowMessage(Err_Msg_Card);
	return;
    }

    btn_seq_read->Enabled = false;
    int len = StrToInt(edt_seq_len->Text);
    unsigned char *data_read = new unsigned char[len];
    for (int i = 0; i < len; i++)
	data_read[i] = 0;
    pg_read(data_read, 1);
    if (data_read != NULL)
	delete[]data_read;

    btn_seq_read->Enabled = true;
}

//---------------------------------------------------------------------------

bool TEngineerForm::Set_seq_data(unsigned char *data_read, int data_len, int data_addr_val)
{
    String Addr_str;
    Dec2Hex(data_addr_val, &Addr_str);
    edt_seq_addr->Text = Addr_str;
    edt_seq_len->Text = IntToStr(data_len);

    char string[5];
    int row = floor((double) data_len / 16);
    int remain = data_len - row * 16;

    for (int i = 0; i < row; i++) {
	for (int j = 0; j < 16; j++) {
	    sprintf(string, "%02X", data_read[i * 16 + j]);
	    sg_seq_data->Cells[j + 1][i + 1] = (AnsiString) string;
	}
	sprintf(string, "%02X", data_addr_val + i * 16);
	sg_seq_data->Cells[0][i + 1] = (AnsiString) string;
    }
    sprintf(string, "%02X", data_addr_val + row * 16);
    sg_seq_data->Cells[0][row + 1] = (AnsiString) string;
    for (int j = 0; j < remain; j++) {
	sprintf(string, "%02X", data_read[row * 16 + j]);
	sg_seq_data->Cells[j + 1][row + 1] = (AnsiString) string;
    }
    return 1;
}

//--------------------------------------------------------------------------
bool TEngineerForm::Get_write_data(unsigned char *write_data)
{
    AnsiString str = edt_byte_wdata->Text;
    int val;
    if (Hex2Dec(str, &val) == 0)
	return 0;
    *write_data = (unsigned char) val;
    return 1;
}

//---------------------------------------------------------------------------
bool TEngineerForm::Get_read_data(unsigned char *read_data)
{
    AnsiString str = edt_byte_rdata->Text;
    int val;
    if (Hex2Dec(str, &val) == 0)
	return 0;
    *read_data = (unsigned char) val;
    return 1;
}

//-----------------------------------------------------------------------------
bool TEngineerForm::SetDeviceAddr(unsigned char dev_ad, unsigned char *dev_ad_new,
				  unsigned char *data_ad, int data_ad_c)
{
    if (cbo_mem_addr_size->ItemIndex == 1) {
	*dev_ad_new = (dev_ad & 0xFC) + (data_ad[1] & 0x01);
    } else if (cbo_mem_addr_size->ItemIndex == 2) {
	*dev_ad_new = (dev_ad & 0xF8) + (data_ad[1] & 0x03);
    } else if (cbo_mem_addr_size->ItemIndex == 3) {
	*dev_ad_new = (dev_ad & 0xF0) + (data_ad[1] & 0x07);
    } else {
	*dev_ad_new = dev_ad;
    }

    return 1;
}

//---------------------------------------------------------------------------
void __fastcall TEngineerForm::btn_byte_writeClick(TObject * Sender)
{
    if (btn_connect_card->Enabled == true) {
	ShowMessage(Err_Msg_Card);
	return;
    }
    btn_byte_write->Enabled = false;
    unsigned char dev_addr[4];
    int dev_addr_cnt;
    if (Get_device_addr(dev_addr, &dev_addr_cnt) == 0) {	//取得介面上device address
	ShowMessage(Err_Msg_Dev);
    }
    bool ok = 0;
    char str[10] = "";
    for (int i = 0; i < dev_addr_cnt; i++) {	//對每個device address動作
	ok = B_write(dev_addr[i]);
	char str_t[2];
	if (ok == 0) {
	    sprintf(str_t, "%02X", dev_addr[i]);
	    strncat(str, str_t, 2);
	}
    }
    if (str[0] != '\0') {
	Connect_Msg = (String) str + " Fail!";
	ShowMessage(Err_Msg_W);
    }
    btn_byte_write->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TEngineerForm::rg_i2c_card_selClick(TObject * Sender)
{
    if (rg_i2c_card_sel->ItemIndex == 2) {	//LPT 06T11-SA
	Img_LPT_06T->Visible = true;
	Img_LPT_04T->Visible = false;
	Img_usb->Visible = false;
	SetCardLarge();
	//rg_device_addr_sel->Items->Strings[3] ="OTP";
    } else if (rg_i2c_card_sel->ItemIndex == 1) {	//LPT 04T25-SA
	Img_LPT_06T->Visible = false;
	Img_LPT_04T->Visible = true;
	Img_usb->Visible = false;
	SetCardSmall();
	//rg_device_addr_sel->Items->Strings[3]="OTP";
    } else if (rg_i2c_card_sel->ItemIndex == 0) {	//USB
	Img_LPT_06T->Visible = false;
	Img_LPT_04T->Visible = false;
	Img_usb->Visible = true;
	//rg_device_addr_sel->Items->Strings[3]="===";

    }
    btn_connect_card->Enabled = true;
    connect = false;
    MainForm->StatusBar1->Panels->Items[0]->Text = "Connection: Fail!";
    btn_en_ftm->Enabled = true;
    btn_connect_cardClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TEngineerForm::btn_connect_cardClick(TObject * Sender)
{
    int cnnct_ok;
    connect = false;
    //USB connect
    if (rg_i2c_card_sel->ItemIndex == 0) {
	cnnct_ok = RW.USB_connect(rg_power->ItemIndex, rg_speed->ItemIndex);
	if (cnnct_ok == true)
	    btn_byte_readClick();	// read a byte to check if connect
	else
	    Connect_Msg = "USB Connect Fail!";
	//LPT connect
    } else if (rg_i2c_card_sel->ItemIndex == 1 || rg_i2c_card_sel->ItemIndex == 2) {
	RW.USB_disconnect();
	cnnct_ok = RW.LPT_connect();
	if (cnnct_ok == 0) {
	    Connect_Msg = "No LPT Dll found.";
	} else if (cnnct_ok == -1) {
	    Connect_Msg = "GetProcAddress for Inp32 Failed.";
	} else if (cnnct_ok == -2) {
	    Connect_Msg = "ECR Byte Mode setting fail.";
	} else {
	    btn_byte_readClick();	// read a byte to check if connect
	}
    }
    if (connect == true) {
	btn_connect_card->Enabled = false;
	MainForm->StatusBar1->Panels->Items[0]->Text = "Connection: OK!";
    } else {
	btn_connect_card->Enabled = true;
	MainForm->StatusBar1->Panels->Items[0]->Text = "Connection: " + Connect_Msg;
    }
}

//---------------------------------------------------------------------------
// Get sequential write data from interfae
void TEngineerForm::Get_seq_write_data(unsigned char *write_data, int data_len)
{
    int row = floor((double) data_len / 16);
    int remain = data_len - row * 16;
    int val;

    for (int i = 0; i < data_len; i++)
	write_data[i] = 0;

    for (int i = 0; i < row; i++) {
	for (int j = 0; j < 16; j++) {
	    if (Hex2Dec(sg_seq_data->Cells[j + 1][i + 1], &val))
		write_data[i * 16 + j] = (unsigned char) val;	//型態不合 (hex2Dec?!)
	}
    }
    for (int j = 0; j < remain; j++) {
	if (Hex2Dec(sg_seq_data->Cells[j + 1][row + 1], &val))
	    write_data[row * 16 + j] = LOBYTE(val);	//型態不合 (hex2Dec?!)
    }
}


//---------------------------------------------------------------------------

// 20100608 USB Sequential Write, used in TCON write & OTP write, 1 start 1 stop
bool TEngineerForm::USB_seq_pg_write(unsigned char dev_ad, unsigned char *data_addr,
				     int data_addr_cnt, unsigned char *data_write, int data_len,
				     int pck_size, int wait_t)
{
    int tmp_len = data_len;	//data length remain after data transmit
    unsigned char data_addr_tmp[2] = { 0 };
    for (int i = 0; i <= data_addr_cnt; i++)
	data_addr_tmp[i] = data_addr[i];

    unsigned char *data_w_tmp = new unsigned char[PAC_SIZE];
    for (int i = 0; i < PAC_SIZE; i++) {
	data_w_tmp[i] = 0;
    }
    if (data_w_tmp == NULL)
	return 0;		//memory allocate fail

    unsigned char dev_ad_tmp;	//device address byte (device addr(4bit)+data addr(3 bit))
    int data_ad = (int) data_addr_tmp[0] + (int) data_addr_tmp[1] * 256;
    int ok = 0, front = 0, pck_cnt = 0;
    //read ok or not  //fail read count

    SetDeviceAddr(dev_ad, &dev_ad_tmp, data_addr_tmp, data_addr_cnt);
    //Set the 1st Byte of device address
    bool overflag;

    // package1
    if (tmp_len <= pck_size) {
	overflag = 1;
	Set_write_buf(data_write, data_w_tmp, 0, tmp_len);
	//Get Write data from interface
	ok = RW.USB_seq_write_P1(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, tmp_len,
				 overflag);
    } else {
	overflag = 0;
	Set_write_buf(data_write, data_w_tmp, 0, pck_size);
	//Get Write data from interface
	ok = RW.USB_seq_write_P1(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, pck_size,
				 overflag);
    }

    pck_cnt++;
    tmp_len -= pck_size;
    int start_data = front + pck_cnt * pck_size;

    //package2
    while (tmp_len > 0) {
	if (tmp_len <= pck_size) {
	    overflag = 1;
	    Set_write_buf(data_write, data_w_tmp, start_data, tmp_len);
	    ok = RW.USB_Data_Package(data_w_tmp, tmp_len, overflag);
	    tmp_len = 0;
	} else {
	    overflag = 0;
	    Set_write_buf(data_write, data_w_tmp, start_data, pck_size);
	    ok = RW.USB_Data_Package(data_w_tmp, pck_size, overflag);
	    tmp_len -= pck_size;
	    start_data += pck_size;
	    pck_cnt++;
	}
    }
    if (data_w_tmp != NULL)
	delete[]data_w_tmp;
    return ok;
}

// 20100608 USB Package Write, used in EEPROM write, each package has 1 start 1 stop
bool TEngineerForm::USB_pg_write(unsigned char dev_ad, unsigned char *data_addr, int data_addr_cnt,
				 unsigned char *data_write, int data_len, int pck_size, int wait_t)
{				// EEPROM write package size = 8, and start counting address is 8 multiplier

    int tmp_len = data_len;	//data length remain after data transmit
    unsigned char data_addr_tmp[2] = { 0 };
    for (int i = 0; i <= data_addr_cnt; i++)
	data_addr_tmp[i] = data_addr[i];

    unsigned char *data_w_tmp = new unsigned char[PAC_SIZE];
    for (int i = 0; i < PAC_SIZE; i++) {
	data_w_tmp[i] = 0;
    }
    if (data_w_tmp == NULL)
	return 0;		//memory allocate fail

    unsigned char dev_ad_tmp;	//device address byte (device addr(4bit)+data addr(3 bit))
    int data_ad = (int) data_addr_tmp[0] + (int) data_addr_tmp[1] * 256;
    int ok = 0, rd_cnt = 0, front = 0, pck_cnt = 0;
    //read ok or not  //fail read count

    if (rg_device_addr_sel->ItemIndex == 2 && data_ad % 8 != 0) {	//if address start != 8 multiplier
	front = 8 - data_ad % 8;
	Set_write_buf(data_write, data_w_tmp, 0, front);
	//將參數2的值(從參數3開始,長度為參數4)放入參數1,
	SetDeviceAddr(dev_ad, &dev_ad_tmp, data_addr_tmp, data_addr_cnt);

	ok = 0;
	rd_cnt = 0;		//fail read count
	while (ok == 0 && rd_cnt < 2) {	//if fail read exceed 3, give up rework
	    ok = RW.USB_write(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, front);
	    rd_cnt++;
	    Sleep(wait_t);
	}
	if (ok == 0)
	    return 0;
	Add_val2_data_ad(data_addr_tmp, data_addr_cnt, front);
	tmp_len -= front;
    }
    /////////////////////////////////////////////////
    while (tmp_len > pck_size) {	//need to send more packages
	Set_write_buf(data_write, data_w_tmp, front + pck_cnt * pck_size, pck_size);
	//Get Write data from interface
	SetDeviceAddr(dev_ad, &dev_ad_tmp, data_addr_tmp, data_addr_cnt);
	//Set the 1st Byte of device address
	ok = 0;
	rd_cnt = 0;
	while (ok == 0 && rd_cnt < 2) {	//if fail read exceed 3, give up rework
	    ok = RW.USB_write(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, pck_size);
	    rd_cnt++;
	    Sleep(wait_t);
	}
	if (ok == 0)
	    return 0;
	Add_val2_data_ad(data_addr_tmp, data_addr_cnt, pck_size);
	pck_cnt++;
	tmp_len -= pck_size;
    }
    Set_write_buf(data_write, data_w_tmp, front + pck_cnt * pck_size, tmp_len);
    SetDeviceAddr(dev_ad, &dev_ad_tmp, data_addr_tmp, data_addr_cnt);
    ok = 0;
    rd_cnt = 0;
    while (ok == 0 && rd_cnt < 2) {	//if fail read exceed 3, give up rework
	ok = RW.USB_write(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, tmp_len);
	rd_cnt++;
    }
    if (ok == 0)
	return 0;
    if (data_w_tmp != NULL)
	delete[]data_w_tmp;
    return ok;
}

//---------------------------------------------------------------------------
// PrintPort package write, for EEPROM using package size (pck_size) set to 8
bool TEngineerForm::LPT_pg_write(unsigned char dev_ad, unsigned char *data_addr, int data_addr_cnt,
				 unsigned char *data_write, int data_len, int pck_size, int wait_t)
{				// EEPROM write package size = 8, and start counting address is 8 multiplier

    int tmp_len = data_len;	//data length remain after data transmit
    unsigned char data_addr_tmp[2];
    for (int i = 0; i <= data_addr_cnt; i++)
	data_addr_tmp[i] = data_addr[i];
    unsigned char *data_w_tmp = new unsigned char[tmp_len];
    if (data_w_tmp == NULL)
	return NULL;
    unsigned char dev_ad_tmp;
    int pck_cnt = 0;
    //EEPROM internal counter can only address for 1 page size
    //計算data address 若小於page size的倍數者的前幾byte先送出,
    //並更新address為page size的倍數與更新送出的長度
    int address_val;

    int data_ad = (int) data_addr_tmp[0] + (int) data_addr_tmp[1] * 256;

    int front = 0;
    if (rg_device_addr_sel->ItemIndex == 2) {	// EEPROM
	if (data_ad % 8 != 0) {
	    front = 8 - data_ad % 8;	// 1st package data length
	    Set_write_buf(data_write, data_w_tmp, 0, front);
	    // temperary record writing char to "data_w_tmp"
	    SetDeviceAddr(dev_ad, &dev_ad_tmp, data_addr_tmp, data_addr_cnt);
	    // composite Dvice Address and Data Address as Device Byte
	    RW.LPT_Write(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, front);
	    // write "data_w_tmp" to device
	    Add_val2_data_ad(data_addr_tmp, data_addr_cnt, front);
	    // Set address for next write
	    tmp_len -= front;
	    Sleep(wait_t);
	}
	while (tmp_len > pck_size) {	//need to send more packages
	    Set_write_buf(data_write, data_w_tmp, front + pck_cnt * pck_size, pck_size);	//Get Write data from interface
	    SetDeviceAddr(dev_ad, &dev_ad_tmp, data_addr_tmp, data_addr_cnt);	//Set the 1st Byte of device address
	    RW.LPT_Write(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, pck_size);
	    Add_val2_data_ad(data_addr_tmp, data_addr_cnt, pck_size);
	    pck_cnt++;
	    tmp_len -= pck_size;
	    Sleep(wait_t);
	}
    }
    // last package for EEPROM write, but 1st and only package in TCON
    Set_write_buf(data_write, data_w_tmp, front + pck_cnt * pck_size, tmp_len);
    SetDeviceAddr(dev_ad, &dev_ad_tmp, data_addr_tmp, data_addr_cnt);
    RW.LPT_Write(dev_ad_tmp, data_addr_tmp, data_addr_cnt, data_w_tmp, tmp_len);
    Sleep(wait_t);		// write cycle time for EEPROM
    if (data_w_tmp != NULL)
	delete[]data_w_tmp;
    return 1;
}

//---------------------------------------------------------------------------
// package write, retrieve Device address, Data address and Data from interface
bool TEngineerForm::pg_write()
{
    unsigned char dev_addr[4];
    int dev_addr_cnt;
    unsigned char data_addr[2];
    int data_addr_cnt;
    unsigned char *data_write;
    int data_len;

    if (Get_seq_addr(data_addr, &data_addr_cnt) == 0) {
	ShowMessage(Err_Msg_BAddr);
	return 0;
    }

    if (Get_device_addr(dev_addr, &dev_addr_cnt) == 0) {
	ShowMessage(Err_Msg_Dev);
	return 0;
    }
    data_len = StrToInt(edt_seq_len->Text);
    data_write = new unsigned char[data_len];
    if (data_write == NULL) {
	ShowMessage("Memory is not enough!");
	return 0;
    }
    Get_seq_write_data(data_write, data_len);
    if (data_write == NULL) {
	ShowMessage(Err_Msg_WByte);
	return 0;
    }

    int pck_size = data_len;
    if (rg_i2c_card_sel->ItemIndex == 0) {	//USB package size
	pck_size = PAC_SIZE;
    }

    if (rg_device_addr_sel->ItemIndex == 2) {	//EEPROM package size
	pck_size = 8;
	rg_w_cycl_t->ItemIndex = 1;	//Write EEPROM, EEPROM internal write cycle time: 5us
    } else
	rg_w_cycl_t->ItemIndex = 2;	//no need cycle time

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
    if (rg_w_cycl_t->ItemIndex == 0)
	wait_t = 6;
    else if (rg_w_cycl_t->ItemIndex == 1)
	wait_t = 11;
    else if (rg_w_cycl_t->ItemIndex == 2)
	wait_t = 0;

    int ok = 0;
    for (int i = 0; i < dev_addr_cnt; i++) {
	if (rg_i2c_card_sel->ItemIndex == 0) {	//Use USB to transfer
	    int cnnct_ok = RW.USB_connect(rg_power->ItemIndex, rg_speed->ItemIndex);	//201007 for Vdd drop
	    if (!cnnct_ok)
		return 0;
	    // original PAC_SIZE byte per package
	    if (rg_device_addr_sel->ItemIndex == 2) {
		ok = USB_pg_write(dev_addr[i], data_addr, data_addr_cnt, data_write, data_len,
				  pck_size, wait_t);
		if (ok == 0)
		    ShowMessage(Err_Msg_W);
	    } else {
		// no seperate
		ok = USB_seq_pg_write(dev_addr[i], data_addr, data_addr_cnt, data_write, data_len,
				      pck_size, wait_t);
		if (ok == 0)
		    ShowMessage(Err_Msg_W);
	    }
	} else {		// Use Printport to transfer
	    ok = LPT_pg_write(dev_addr[i], data_addr, data_addr_cnt, data_write, data_len, pck_size,
			      wait_t);
	    if (ok != 1) {
		if (ok == -1)
		    ShowMessage("Device address Send fail!");
		else if (ok == -2)
		    ShowMessage("Data address Send fail!");
		else if (ok == 0)
		    ShowMessage("Data Send fail!");
		return 0;
	    }
	}
	Sleep(10);
    }

    int write_chk = 0;
    for (int i = 0; i < data_len; i++)
	write_chk += int (data_write[i]);

    // show read/ write checksum in the bottom of windows
    char string[10];
    sprintf(string, "%X", write_chk);
    AnsiString str = (AnsiString) string;
    stb_page_operat->Panels->Items[0]->Text = "Write Checksum: " + str;
    stb_page_operat->Panels->Items[1]->Text = "Read Checksum: ";

    if (data_write != NULL)
	delete[]data_write;

    return 1;
}

//---------------------------------------------------------------------------
// Sequential Operation Write Buttom Click
void __fastcall TEngineerForm::btn_seq_writeClick(TObject * Sender)
{
    //Check card connection
    if (btn_connect_card->Enabled == true) {
	ShowMessage(Err_Msg_Card);
	return;
    }

    btn_seq_write->Enabled = false;

    //clock_t startwait=clock();
    pg_write();
    //clock_t endwait=clock();

    //ShowMessage("  Time(ms):"+FloatToStr(endwait-startwait));
    btn_seq_write->Enabled = true;
}

//---------------------------------------------------------------------------

// When Engineer Page Object is exit, send USE disconnect.
void __fastcall TEngineerForm::PageControl1Exit(TObject * Sender)
{
    RW.USB_disconnect();
}

//---------------------------------------------------------------------------
// TCON Software reset, send Address 4 as value 1
void __fastcall TEngineerForm::btn_soft_resetClick(TObject * Sender)
{
    if (rg_device_addr_sel->ItemIndex == 2) {
	rg_device_addr_sel->ItemIndex = 0;
	btn_connect_cardClick(Sender);
	if (!connect)
	    return;
    }
    if (!connect) {
	btn_connect_cardClick(Sender);
	if (!connect)
	    return;
    }
    edt_byte_addr->Text = 4;
    edt_byte_wdata->Text = 1;
    btn_byte_writeClick(Sender);
}

//---------------------------------------------------------------------------
// Function for getting device address from UI
bool TEngineerForm::Get_device_addr(int *dev_ad)
{
    bool ok;
    int val;
    if (rg_device_addr_sel->ItemIndex == 0) {	//single TCON
	ok = Hex2Dec(edt_addr_tcon_s->Text, &val);
	*dev_ad = (unsigned char) val;
    } else if (rg_device_addr_sel->ItemIndex == 1) {	//dual TCON
	ok = Hex2Dec(edt_addr_tcon_dm->Text, &val);
	*dev_ad = (unsigned char) val;
    } else if (rg_device_addr_sel->ItemIndex == 2) {	//single EEPROM
	ok = Hex2Dec(edt_addr_EEP->Text, &val);
	*dev_ad = (unsigned char) val;
    } else			//may add quad-TCON here
	return 0;

    return 1;
}

//---------------------------------------------------------------------------
void TEngineerForm::dev_addr_change(TObject * Sender)
{
    int dev;
    Get_device_addr(&dev);
    //StringGrid of device address
    char str[5];
    for (int i = 0; i < 7; i++) {
	sprintf(str, "%d", (int) ((double) dev / pow(2, 7 - i)) % 2);
	sg_device_addr->Cells[i][0] = (AnsiString) str;
    }
    sg_device_addr->Cells[7][0] = "RW";
    //rg_device_addr_selClick(Sender);
}


void __fastcall TEngineerForm::cbo_mem_addr_sizeChange(TObject * Sender)
{
    //sg_device_addr是介面上的一列數值,用來表示實際上用來定址的位元
    dev_addr_change(Sender);
    int idx = cbo_mem_addr_size->ItemIndex;

    //2k, dev|word|R/W bit
    //     7 | 0  | 1
    if (idx == 0) {
    }
    //4k, dev|word|R/W bit
    //     6 | 1  | 1
    else if (idx == 1) {
	sg_device_addr->Cells[6][0] = "--";
    }
    //8k, dev|word|R/W bit
    //     5 | 2  | 1
    else if (idx == 2) {
	for (int i = 0; i <= 1; i++)
	    sg_device_addr->Cells[6 - i][0] = "--";
    }
    //16k, dev|word|R/W bit
    //     4 | 3  | 1
    else if (idx == 3) {
	for (int i = 0; i <= 2; i++)
	    sg_device_addr->Cells[6 - i][0] = "--";
    }
    //32k, dev|word|R/W bit
    //     7 | 0  | 1
    else if (idx >= 4) {
    }
    btn_en_ftm->Enabled = true;
}

//---------------------------------------------------------------------------


void __fastcall TEngineerForm::rg_device_addr_selClick(TObject * Sender)
{
    dev_addr_change(Sender);
    btn_en_ftm->Enabled = true;

    if (rg_device_addr_sel->ItemIndex == 2) {	//EEPROM
	MainForm->StatusBar1->Panels->Items[1]->Text = "Device Address: " + edt_addr_EEP->Text;
	if (cbo_mem_addr_size->ItemIndex == 0)	//2k
	    rg_w_page->ItemIndex = 1;
	else if (cbo_mem_addr_size->ItemIndex == 1 || cbo_mem_addr_size->ItemIndex == 2
		 || cbo_mem_addr_size->ItemIndex == 3)
	    //4k, 8k, 16k
	    rg_w_page->ItemIndex = 2;
	else			//32k or more
	    rg_w_page->ItemIndex = 3;
	rg_w_cycl_t->ItemIndex = 1;
    } else {			//TCON or OTP
	rg_w_cycl_t->ItemIndex = 2;
	rg_w_page->ItemIndex = 4;
	if (rg_device_addr_sel->ItemIndex == 0) {
	    MainForm->StatusBar1->Panels->Items[1]->Text =
		"Device Address: " + edt_addr_tcon_s->Text;
	} else if (rg_device_addr_sel->ItemIndex == 1) {
	    MainForm->StatusBar1->Panels->Items[1]->Text =
		"Device Address: " + edt_addr_tcon_dm->Text + edt_addr_tcon_ds->Text;
	} else if (rg_device_addr_sel->ItemIndex == 3) {
	    MainForm->StatusBar1->Panels->Items[1]->Text = "Device Address: " + edt_addr_OTP->Text;
	    /*if(rg_i2c_card_sel->ItemIndex == 0){
	       rg_i2c_card_sel->ItemIndex = -1;
	       ShowMessage("USB signal will be transmitted in package, Please choose one of LPT");
	       return;
	       } */
	}
    }
    btn_connect_card->Enabled = true;
    connect = false;
    MainForm->StatusBar1->Panels->Items[0]->Text = "Connection: Fail";
    btn_connect_cardClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TEngineerForm::edt_addr_tcon_sChange(TObject * Sender)
{
    rg_device_addr_sel->ItemIndex = 0;
    rg_device_addr_selClick(Sender);
    dev_addr_change(Sender);
    btn_en_ftm->Enabled = true;
    btn_connect_cardClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TEngineerForm::edt_addr_tcon_dmChange(TObject * Sender)
{
    rg_device_addr_sel->ItemIndex = 1;
    rg_device_addr_selClick(Sender);
    dev_addr_change(Sender);
    btn_en_ftm->Enabled = true;
    btn_connect_cardClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TEngineerForm::edt_addr_tcon_dsChange(TObject * Sender)
{
    rg_device_addr_sel->ItemIndex = 1;
    rg_device_addr_selClick(Sender);
    dev_addr_change(Sender);
    btn_en_ftm->Enabled = true;
    btn_connect_cardClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TEngineerForm::edt_addr_EEPChange(TObject * Sender)
{
    rg_device_addr_sel->ItemIndex = 2;
    rg_device_addr_selClick(Sender);
    dev_addr_change(Sender);
    btn_en_ftm->Enabled = true;
    btn_connect_cardClick(Sender);
}

//---------------------------------------------------------------------------

void __fastcall TEngineerForm::edt_addr_OTPChange(TObject * Sender)
{
    rg_device_addr_sel->ItemIndex = 3;
    rg_device_addr_selClick(Sender);
    dev_addr_change(Sender);
    //btn_en_ftm->Enabled = true;
    btn_connect_cardClick(Sender);
}

//---------------------------------------------------------------------------

// Load sequential read/ write data from file
void __fastcall TEngineerForm::btn_seq_loadClick(TObject * Sender)
{
    if (!OpenDialog_txt_hex->Execute())
	return;
    String Fpath = OpenDialog_txt_hex->FileName;

    int Size;
    char *buffer = LoadFile(Fpath, &Size);
    if (buffer == NULL) {
	ShowMessage("File is empty.");
	return;
    }
    int fileChksum = 0;
    int idx = 0;
    char *pch, *data;
    pch = strtok(buffer, "\n\t");
    data = new char[Size];

    if (OpenDialog_txt_hex->FilterIndex == 1) {	//Text File
	int val;
	while (pch != NULL) {
	    if (isdigit(pch[0]) || (pch[0] >= 'a' && pch[0] <= 'f')
		|| (pch[0] >= 'A' && pch[0] <= 'F')) {
		Hex2Dec((AnsiString) pch, &val);
		data[idx] = (unsigned char) val;
		idx++;
		fileChksum += val;
	    }
	    pch = strtok(NULL, "\n\t");
	}

    } else {			//hex file
	int val;
	int i = 0;
	int intel_address;
	int Chksum_line = 0;
	int checksum;		//每一行的checksum

	if (pch[1] == '0' && pch[2] == '8') {	// 2k
	    while (pch != NULL) {
		String str = (AnsiString) pch;
		if (str.Length() < 10 + 8 * 2 + 1)
		    break;
		int addr;	//address
		Hex2Dec((AnsiString) (str.SubString(4, 4)), &addr);
		//if(isdigit(pch[0]) || (pch[0]>='a' && pch[0]<='f') || (pch[0]>='A' && pch[0]<='F')){
		//         Hex2Dec((AnsiString)pch, &val);
		//ShowMessage("Intel Addr: "+(AnsiString)addr);

		Hex2Dec((AnsiString) (str.SubString(10 + 8 * 2, 2)), &checksum);
		Chksum_line = 0;
		for (int i = 0; i <= 7; i++) {	//切出data數值
		    Hex2Dec((AnsiString) str.SubString(10 + i * 2, 2), &val);
		    data[idx] = (unsigned char) val;
		    idx++;
		    Chksum_line += val;
		}
		if ((Chksum_line + checksum + addr / 256 + addr % 256 + 8) % 256 != 0)
		    ShowMessage("Line fail.");
		fileChksum += Chksum_line;
		pch = strtok(NULL, "\n\t");
	    }
	} else if (pch[1] == '1' && pch[2] == '0') {	// 32k or 64k
	    while (pch != NULL) {
		String str = (AnsiString) pch;
		if (str.Length() < 10 + 16 * 2 + 1)
		    break;

		int addr;	//address
		Hex2Dec((AnsiString) (str.SubString(4, 4)), &addr);

		//if(isdigit(pch[0]) || (pch[0]>='a' && pch[0]<='f') || (pch[0]>='A' && pch[0]<='F')){
		//         Hex2Dec((AnsiString)pch, &val);
		//ShowMessage("Intel Addr: "+(AnsiString)addr);

		//int checksum;  //每一行的checksum
		Hex2Dec((AnsiString) (str.SubString(10 + 16 * 2, 2)), &checksum);
		Chksum_line = 0;
		for (int i = 0; i <= 15; i++) {	//切出data數值
		    Hex2Dec((AnsiString) str.SubString(10 + i * 2, 2), &val);
		    data[idx] = (unsigned char) val;
		    idx++;
		    Chksum_line += val;
		}
		if ((Chksum_line + checksum + (addr / 256) + addr % 256 + 16) % 256 != 0)
		    ShowMessage("Line fail.");
		fileChksum += Chksum_line;

		pch = strtok(NULL, "\n\t");
	    }
	} else {
	    ShowMessage("Can't Open!!");
	    //delete [] pch;
	    delete[]data;
	    delete[]buffer;
	    return;
	}

	if (idx == 256)
	    cbo_mem_addr_size->ItemIndex = 0;
	else if (idx == 4096)
	    cbo_mem_addr_size->ItemIndex = 4;
	else if (idx == 8192)
	    cbo_mem_addr_size->ItemIndex = 5;
    }
    Set_seq_data(data, idx, 0);
    //delete [] pch;
    delete[]data;

    char string[10];
    sprintf(string, "%X", fileChksum);
    AnsiString str = (AnsiString) string;
    stb_page_operat->Panels->Items[2]->Text = "Load Checksum: " + str;

    delete[]buffer;
}

//---------------------------------------------------------------------------
// Save sequential read/ write data from file
void __fastcall TEngineerForm::btn_seq_saveClick(TObject * Sender)
{

    if (!SaveDialog_txt_hex->Execute())
	return;
    String Fpath = SaveDialog_txt_hex->FileName;
    FILE *fptr = fopen(Fpath.c_str(), "w");
    if (fptr == NULL) {
	ShowMessage("Can't Open file.");
	return;
    }
    int data_len = StrToInt(edt_seq_len->Text);
    unsigned char *data = new unsigned char[data_len];
    Get_seq_write_data(data, data_len);
    if (SaveDialog_txt_hex->FilterIndex == 1) {	//Text File
	for (int i = 0; i < data_len; i++) {
	    /*fprintf(fptr,"%02X", data[i]);
	       if(i%16!=15)
	       fprintf(fptr,"\t");
	       else
	       fprintf(fptr,"\n");
	     */
	    fprintf(fptr, "%02X\n", data[i]);
	}
    } else if (SaveDialog_txt_hex->FilterIndex == 2) {	//Intel Hex File
	int addr = 0;
	int checksum;
	int sum = 0;
	if (cbo_mem_addr_size->ItemIndex == 0) {	// 2k Hex file
	    //EDID
	    for (int i = 0; i < data_len / 8; i++) {	// 一列8個數
		fprintf(fptr, ":08%04X00", addr);
		sum = 0;
		for (int j = 0; j < 8; j++) {
		    fprintf(fptr, "%02X", data[i * 8 + j]);	//寫data, 一行16筆
		    sum += data[i * 8 + j];	//把同一行的data值sum起來
		    if (j == 7) {	//寫入checksum
			checksum = floor(addr / 256) + (addr) % 256 + sum + 8;
			fprintf(fptr, "%02X\n", (256 - checksum % 256) % 256);
		    }
		}
		addr += 8;
	    }
	} else {
	    for (int i = 0; i < data_len / 16; i++) {	// 一列16個數
		sum = 0;
		addr = i * 16;
		fprintf(fptr, ":10%04X00", addr);
		for (int j = 0; j < 16; j++) {
		    fprintf(fptr, "%02X", data[i * 16 + j]);	//寫data, 一行16筆
		    sum += data[i * 16 + j];	//把同一行的data值sum起來
		    if (j == 15) {	//寫入checksum
			checksum = floor(addr / 256) + (addr) % 256 + sum + 16;
			fprintf(fptr, "%02X\n", (256 - checksum % 256) % 256);
		    }

		}
	    }
	}
	fprintf(fptr, ":00000001FF\n");
    }

    fprintf(fptr, "\0");
    fclose(fptr);
    delete[]data;
}

//---------------------------------------------------------------------------
// FTM buttom Click, (FTM mode on, set bit 1 of address 2 to high )
void __fastcall TEngineerForm::btn_en_ftmClick(TObject * Sender)
{
    btn_en_ftm->Enabled = false;
    edt_byte_addr->Text = 2;

    if (rg_device_addr_sel->ItemIndex == 2 || rg_device_addr_sel->ItemIndex == 1) {
	rg_device_addr_sel->ItemIndex = 0;
	btn_connect_cardClick(Sender);
	if (!connect)
	    return;
    }
    if (!connect) {
	btn_connect_cardClick(Sender);
	if (!connect)
	    return;
    }

    btn_byte_readClick(Sender);
    unsigned char read_data;
    Get_read_data(&read_data);
    unsigned char write_data = read_data | 80;
    edt_byte_wdata->Text = (AnsiString) write_data;
    btn_byte_writeClick(Sender);

    rg_device_addr_sel->ItemIndex = 2;

    btn_connect_cardClick(Sender);
}

//---------------------------------------------------------------------------

String *TEngineerForm::Load_file(String Fpath, int Lut_no)
{
    long lSize;
    char *buffer;
    FILE *fptr;
    if ((fptr = fopen(Fpath.c_str(), "r")) == NULL) {
	//ShowMessage("Can't Open File.");
	return NULL;
    }
    // obtain file size:
    fseek(fptr, 0, SEEK_END);
    lSize = ftell(fptr);
    rewind(fptr);

    // allocate memory to contain the whole file:
    buffer = (char *) malloc(sizeof(char) * lSize + 1);
    if (buffer == NULL) {
	//ShowMessage("Can't Allocate Memory.");
	return NULL;
    }
    // copy the file into the buffer:
    fread(buffer, 1, lSize, fptr);
    buffer[lSize] = '\0';
    fclose(fptr);

    String *LUT = new String[Lut_no];
    char *pch;
    pch = strtok(buffer, "\n\t");
    String tmp;
    int i = 0;

    while (pch != NULL) {
	LUT[i] = (AnsiString) pch;
	pch = strtok(NULL, "\n\t");
	i++;
	if (i >= Lut_no)
	    break;
    }
    if (i < Lut_no) {
	return NULL;
    }
    return LUT;
}

// reload whole TCON Address
void __fastcall TEngineerForm::btn_reloadClick(TObject * Sender)
{
    btn_reload->Enabled = false;
    MainForm->reload_all(Sender);
    btn_reload->Enabled = true;
}

//---------------------------------------------------------------------------

// USB power setting
void __fastcall TEngineerForm::rg_powerClick(TObject * Sender)
{
    RW.USB_disconnect();
    bool cnnct_ok = RW.USB_connect(rg_power->ItemIndex, rg_speed->ItemIndex);
    if (cnnct_ok == false) {
	MessageBox(NULL, "USB connect fail.", "Error", MB_OK);
	rg_power->ItemIndex = -1;
    } else {
	btn_byte_readClick(Sender);
    }
    if (cnnct_ok == 1 && connect == true) {
	btn_connect_card->Enabled = false;
    }
}

//---------------------------------------------------------------------------
// USB speed setting
void __fastcall TEngineerForm::rg_speedClick(TObject * Sender)
{
    RW.USB_disconnect();
    bool cnnct_ok = RW.USB_connect(rg_power->ItemIndex, rg_speed->ItemIndex);
    if (cnnct_ok == false) {
	MessageBox(NULL, "USB connect fail.", "Error", MB_OK);
	rg_speed->ItemIndex = -1;
    } else {
	btn_byte_readClick(Sender);
    }
    if (cnnct_ok == 1 && connect == true) {
	btn_connect_card->Enabled = false;
    }
}

//---------------------------------------------------------------------------

/////////////////Configuration package "page operation"///////////////////////

void __fastcall TEngineerForm::btn_page_writeClick(TObject * Sender)
{
    btn_page_write->Enabled = false;
    edt_seq_addr->Text = 0;
    int size_idx = pow(2, StrToFloat(cbo_mem_addr_size->ItemIndex) + 1);
    edt_seq_len->Text = IntToStr(size_idx * 1024 / 8);
    btn_seq_writeClick(Sender);
    btn_page_write->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TEngineerForm::btn_page_readClick(TObject * Sender)
{
    btn_page_read->Enabled = false;
    edt_seq_addr->Text = 0;
    int size_idx = pow(2, StrToFloat(cbo_mem_addr_size->ItemIndex) + 1);
    edt_seq_len->Text = IntToStr(size_idx * 1024 / 8);
    btn_seq_readClick(Sender);
    btn_page_read->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TEngineerForm::btn_page_saveClick(TObject * Sender)
{
    btn_page_save->Enabled = false;
    edt_seq_addr->Text = 0;
    int size_idx = pow(2, StrToFloat(cbo_mem_addr_size->ItemIndex) + 1);
    edt_seq_len->Text = IntToStr(size_idx * 1024 / 8);
    btn_seq_saveClick(Sender);
    btn_page_save->Enabled = true;
}

//---------------------------------------------------------------------------

void __fastcall TEngineerForm::btn_page_loadClick(TObject * Sender)
{
    btn_page_load->Enabled = false;
    edt_seq_addr->Text = 0;
    int size_idx = pow(2, StrToFloat(cbo_mem_addr_size->ItemIndex) + 1);
    edt_seq_len->Text = IntToStr(size_idx * 1024 / 8);
    btn_seq_loadClick(Sender);
    btn_page_load->Enabled = true;
}

//////////////////////////////////////////////////////////////////////////////

//---------------------------------------------------------------------------

// check PrintPort Speed
void __fastcall TEngineerForm::btn_LPT_spdClick(TObject * Sender)
{
    edt_seq_addr->Text = 0;
    edt_seq_len->Text = 256;

    clock_t start_t = clock();
    btn_seq_readClick(Sender);
    clock_t end_t = clock();
    if (end_t - start_t <= 0) {
	st_lpt_speed->Caption = "0";
	return;
    }
    double freq = 1.0 / ((double) (end_t - start_t) / 300.0 / 9.0);
    char str[10];
    sprintf(str, "%3.2f kHz", freq);
    st_lpt_speed->Caption = str;
    int ID_OK;
    if (freq > 70)
	ID_OK = MessageBox(NULL, "Lower LPT frequency?!", "Confirm", MB_OKCANCEL);
    if (ID_OK == 1) {
	cb_low_freq->Checked = true;
	SetHalfFreq();
    }
}

//---------------------------------------------------------------------------
// if "Half Frequency" Checked, Set PrintPort signal to half frequency
void __fastcall TEngineerForm::cb_low_freqClick(TObject * Sender)
{
    if (cb_low_freq->Checked)
	SetHalfFreq();
    else
	SetOrigFreq();
}

//---------------------------------------------------------------------------
// Always Sending data till stop, wherether recieve Ack or not (for debug use)
void __fastcall TEngineerForm::btn_byte_read_no_ackClick(TObject * Sender)
{
    unsigned char dev_addr[4];
    //device read/write address, extend to 4 devices set at a time

    unsigned char data_addr[2];	//Word address, may be 1 or 2 Byte
    unsigned char data_read;	//data read
    int data_addr_cnt;		//number of byte in data address
    int dev_addr_cnt;		//number of device

    if (Get_byte_addr(data_addr, &data_addr_cnt) == 0) {
	ShowMessage(Err_Msg_BAddr);
    }

    if (Get_device_addr(dev_addr, &dev_addr_cnt) == 0) {
	ShowMessage(Err_Msg_Dev);
    }
    int ok = 1;
    unsigned char dev_addr_tmp;
    for (int i = 0; i < dev_addr_cnt; i++) {
	SetDeviceAddr(dev_addr[i], &dev_addr_tmp, data_addr, data_addr_cnt);
	//if(rg_i2c_card_sel->ItemIndex == 0)
	//        connect = RW.USB_read(dev_addr_tmp, data_addr, data_addr_cnt, &data_read, 1);
	//else{
	ok = RW.LPT_Read_Byte_Skip_Ack(dev_addr_tmp, data_addr, data_addr_cnt, &data_read);
	//}
    }
    char string[20];
    sprintf(string, "Read Data: %X", data_read);
    AnsiString str = (AnsiString) string;
    ShowMessage(str);
}

//---------------------------------------------------------------------------



// Save Dialog
void __fastcall TEngineerForm::SaveDialog_txt_hexSelectionChange(TObject * Sender)
{
    if (OpenDialog_txt_hex->FilterIndex == 1) {	//Text File
	OpenDialog_txt_hex->DefaultExt = String(".txt");
	OpenDialog_txt_hex->FileName = "*.txt";
	//if (OpenDialog_txt_hex->FileName.AnsiPos(".")<1)　　
	//        OpenDialog_txt_hex->FileName=OpenDialog_txt_hex->FileName+".txt";
    } else if (OpenDialog_txt_hex->FilterIndex == 2) {	//Intel Hex File
	OpenDialog_txt_hex->DefaultExt = String(".hex");
	OpenDialog_txt_hex->FileName = "*.hex";
	///if (OpenDialog_txt_hex->FileName.AnsiPos(".")<1)　　
	//        OpenDialog_txt_hex->FileName=OpenDialog_txt_hex->FileName+".hex;
    }
}

//---------------------------------------------------------------------------

