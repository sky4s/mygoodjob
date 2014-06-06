#include "ReadWriteFunc.h"

//C系統文件    

//C++系統文件

//其他庫頭文件
#include <LPT_lib/HWINTERFACELib_TLB.h>
#include <LPT_lib/HWINTERFACELib_OCX.h>
#include <USB_i2c_lib/USB_I2C.h>

#include "FTD2XX_lib/ftd2xx.h"    //20140603 byBS+

//本項目內頭文件
#include "PrintPortI2C.h"

//---------------------------------------------------------------------------

//#pragma package(smart_init)

//for DoDoBird I2C Card
FT_HANDLE ftHandle;
//I2C Timing
#define TIME_DATA_WRITE 50
#define TIME_DATA_READ 50
#define TIME_8TH_9TH 50

RW_Func::RW_Func()
{
}

//--------------------------------------------------------------------------
int RW_Func::LPT_Read_Byte_Skip_Ack(unsigned char dev_addr,
				    unsigned char *data_addr,
				    int data_addr_cnt, unsigned char *data_read)
{
    //bool ok = true;                                             
    i2c_start();
    Ack_Stop_remove();
    i2c_send_byte(dev_addr & 0xFE);	//write
    while (data_addr_cnt > 0) {	//2 byte data address
	Ack_Stop_remove();
	i2c_send_byte(data_addr[data_addr_cnt]);	//send high byte first
	data_addr_cnt--;
    }
    Ack_Stop_remove();
    i2c_send_byte(data_addr[0]);
    Ack_Stop_remove();
    i2c_read_byte(dev_addr, data_read);
    return 1;
}

//---------------------------------------------------------------------------

int RW_Func::LPT_Read_Byte(unsigned char dev_addr,
			   unsigned char *data_addr, int data_addr_cnt, unsigned char *data_read)
{
    bool ok = true;
    i2c_start();
    ok = i2c_send_byte(dev_addr & 0xFE);	//write
    if (ok == 0)
	return -1;		//device address send fail
    while (data_addr_cnt > 0) {	//2 byte data address
	ok = i2c_send_byte(data_addr[data_addr_cnt]);	//send high byte first
	data_addr_cnt--;
	if (ok == 0)
	    return -2;		//word address send fail
    }
    ok = i2c_send_byte(data_addr[0]);
    if (ok == 0)
	return -2;		//word address send fail

    ok = i2c_read_byte(dev_addr, data_read);
    if (ok != 1)
	return 0;		//data read fail
    return 1;
}

//---------------------------------------------------------------------------

int RW_Func::LPT_Read_seq(unsigned char dev_addr, unsigned char *data_addr,
			  int data_addr_cnt, unsigned char *data_read, int data_cnt)
{
    bool ok = true;
    i2c_start();
    ok = i2c_send_byte(dev_addr & 0xFE);	//write
    if (ok == 0)
	return -1;		//device address send fail

    while (data_addr_cnt > 0) {
	ok = ok & i2c_send_byte(data_addr[data_addr_cnt]);
	data_addr_cnt--;
	if (ok == 0)
	    return -2;		//word address send fail
    }
    ok = i2c_send_byte(data_addr[0]);
    if (ok == 0)
	return -2;		//word address send fail

    ok = i2c_read_byte_seq(dev_addr, data_read, data_cnt);
    if (ok != 1)
	return 0;		//data read fail
    return 1;
}

//---------------------------------------------------------------------------
int RW_Func::LPT_connect()
{
    int cnnct_ok = Link_LPT();
    /*read data to check if connect ok */

    return cnnct_ok;
}

//--------------------------------------------------------------------------
bool RW_Func::USB_disconnect(void)
{
    unsigned char *WriteBuffer = new unsigned char[65];
    unsigned char *ReadBuffer = new unsigned char[65];
    WriteBuffer[0] = I2C_START | I2C_DEV_WRITE | I2C_STOP;
    WriteBuffer[1] = 1;
    WriteBuffer[2] = POWER_CTRL;	//0x80 means [power control]
    WriteBuffer[3] = POWER_EXTERNAL;
    USB.WriteReport(WriteBuffer, 4);
    USB.ReadReportEx(ReadBuffer);
    delete[]WriteBuffer;
    delete[]ReadBuffer;
    return 1;
}

int RW_Func::USB_connect(int pwr_i, int clck_i)
{
    unsigned char *WriteBuffer = new unsigned char[65];
    unsigned char *ReadBuffer = new unsigned char[65];
    int cnnct_ok = 0;
    VendorID = 0x04b4;
    ProductID = 0xf232;

    unsigned char ucPowerItem = 0;
    unsigned char ucSpeedItem = 0;

    //Power mode selection by RadioGroup Component
    switch (pwr_i) {
    case 0:
	ucPowerItem = POWER_EXTERNAL;
	break;
    case 1:
	ucPowerItem = POWER_INTERNAL_5V;
	break;
    case 2:
	ucPowerItem = POWER_INTERNAL_3P3V;
	break;
    default:
	ucPowerItem = POWER_INTERNAL_3P3V;
	break;
    }

    WriteBuffer[0] = I2C_START | I2C_DEV_WRITE | I2C_STOP;
    WriteBuffer[1] = 1;
    WriteBuffer[2] = POWER_CTRL;	//0x80 means [power control]
    WriteBuffer[3] = ucPowerItem;
    USB.WriteReport(WriteBuffer, 4);
    USB.ReadReportEx(ReadBuffer);

    //Clock Rate selection by RadioGroup Component
    switch (clck_i) {
    case 0:
	ucSpeedItem = CLOCK_RATE_50KHZ;
	break;
    case 1:
	ucSpeedItem = CLOCK_RATE_100KHZ;
	break;
    case 2:
	ucSpeedItem = CLOCK_RATE_400KHZ;
	break;
    default:
	ucSpeedItem = CLOCK_RATE_400KHZ;
	break;
    }

    WriteBuffer[0] = ucSpeedItem;
    USB.WriteReport(WriteBuffer, 1);
    USB.ReadReportEx(ReadBuffer);

    if (USB.FindTheHID())
	cnnct_ok = 1;
    delete[]WriteBuffer;
    delete[]ReadBuffer;
    return cnnct_ok;
}

//---------------------------------------------------------------------

bool RW_Func::USB_read(unsigned char dev_addr, unsigned char *data_addr,
		       int data_addr_cnt, unsigned char *data_read, int data_len)
{
    unsigned char *WriteBuffer = new unsigned char[65];
    unsigned char *ReadBuffer = new unsigned char[65];
    for (int i = 0; i < 65; i++) {
	WriteBuffer[i] = 0;
	ReadBuffer[i] = 0;
    }
    int buf_idx = 0;
    //Read
    WriteBuffer[buf_idx++] = I2C_START | I2C_DEV_WRITE;	//Control Byte
    WriteBuffer[buf_idx++] = 1 + data_addr_cnt;	//Output Data length
    WriteBuffer[buf_idx++] = (dev_addr >> 1);	//DEVICE_ADDR
    int addr_cnt1 = data_addr_cnt;
    while (addr_cnt1 > 0) {
	WriteBuffer[buf_idx++] = data_addr[addr_cnt1];	//DATA_ADDR
	addr_cnt1--;
    }
    WriteBuffer[buf_idx++] = data_addr[0];
    USB.WriteReport(WriteBuffer, 4 + data_addr_cnt);	//USB Output Packet
    USB.ReadReportEx(ReadBuffer);	//USB Iutput Packet

    buf_idx = 0;
    WriteBuffer[buf_idx++] = I2C_START | I2C_DEV_READ | I2C_STOP;	//Control Byte
    WriteBuffer[buf_idx++] = data_len;	//Output Data length
    WriteBuffer[buf_idx++] = (dev_addr >> 1);	//DEVICE_ADDR;
    USB.WriteReport(WriteBuffer, 3 + data_len);	//USB Output Packet
    USB.ReadReportEx(ReadBuffer);	//USB Iutput Packet
    for (int i = 0; i < data_len; i++) {	//1st byte is status byte
	data_read[i] = ReadBuffer[i + 1];
    }
    int r_ok = ReadBuffer[0];	//status byte
    delete[]WriteBuffer;
    delete[]ReadBuffer;
    return r_ok;
}

//---------------------------------------------------------------------------

bool RW_Func::USB_write(unsigned char dev_addr, unsigned char *data_addr,
			int data_addr_cnt, unsigned char *data_write, int data_len)
{
    //Write
    int buf_idx = 0;
    unsigned char *WriteBuffer = new unsigned char[65];
    unsigned char *ReadBuffer = new unsigned char[65];

    WriteBuffer[buf_idx++] = I2C_START | I2C_DEV_WRITE | I2C_STOP;	//Control Byte
    WriteBuffer[buf_idx++] = data_len + 1 + data_addr_cnt;	//Output Data length
    WriteBuffer[buf_idx++] = (dev_addr >> 1);	//DEVICE_ADDR
    int addr_cnt1 = data_addr_cnt;
    while (addr_cnt1 > 0) {
	WriteBuffer[buf_idx++] = data_addr[addr_cnt1];	//DATA_ADDR
	addr_cnt1--;
    }
    WriteBuffer[buf_idx++] = data_addr[0];	//DATA_ADDR

    for (int i = 0; i < data_len; i++) {
	WriteBuffer[4 + data_addr_cnt + i] = data_write[i];	//Data Byte
    }
    USB.WriteReport(WriteBuffer, 4 + data_addr_cnt + data_len);	//USB Output Packet
    USB.ReadReportEx(ReadBuffer);	//USB Iutput Packet

    int r_ok = ReadBuffer[0];	//status byte
    delete[]WriteBuffer;
    delete[]ReadBuffer;
    return r_ok;
}

//==================================================================//
//      New serial write method for OPT
//
//==================================================================//
bool RW_Func::USB_write_serial(unsigned char dev_addr,
			       unsigned char *data_addr, int data_addr_cnt,
			       unsigned char *data_write, int data_len, int flag)
{
    //Write
    int buf_idx = 0;
    unsigned char *WriteBuffer = new unsigned char[65];
    unsigned char *ReadBuffer = new unsigned char[65];

    if (flag == 1) {		//with start & end
	WriteBuffer[buf_idx++] = I2C_START | I2C_DEV_WRITE | I2C_STOP;	//Control Byte !!
    } else if (flag == 2) {	//with start
	WriteBuffer[buf_idx++] = I2C_START | I2C_DEV_WRITE;	//Control Byte !!
    } else if (flag == 3) {	//with end
	WriteBuffer[buf_idx++] = I2C_DEV_WRITE | I2C_STOP;	//Control Byte !!
	//修改 I2C_DEV_WRITE 與 device address & address
    } else if (flag == 4) {	//no start or end
	WriteBuffer[buf_idx++] = I2C_DEV_WRITE;	//Control Byte !!
	//修改 I2C_DEV_WRITE 與 device address & address
    }

    WriteBuffer[buf_idx++] = data_len + 1 + data_addr_cnt;	//Output Data length
    WriteBuffer[buf_idx++] = (dev_addr >> 1);	//DEVICE_ADDR
    int addr_cnt1 = data_addr_cnt;
    while (addr_cnt1 > 0) {
	WriteBuffer[buf_idx++] = data_addr[addr_cnt1];	//DATA_ADDR
	addr_cnt1--;
    }
    WriteBuffer[buf_idx++] = data_addr[0];	//DATA_ADDR

    for (int i = 0; i < data_len; i++) {
	WriteBuffer[4 + data_addr_cnt + i] = data_write[i];	//Data Byte
    }
    USB.WriteReport(WriteBuffer, 4 + data_addr_cnt + data_len);	//USB Output Packet
    USB.ReadReportEx(ReadBuffer);	//USB Iutput Packet

    int r_ok = ReadBuffer[0];	//status byte
    delete[]WriteBuffer;
    delete[]ReadBuffer;
    return r_ok;
}

//---------------------------------------------------------------------------
int RW_Func::LPT_Write(unsigned char dev_addr, unsigned char *data_addr,
		       int data_addr_cnt, unsigned char *data_write, int data_len)
{
    bool ok = true;

    i2c_start();
    ok = i2c_send_byte(dev_addr & 0xFE);
    if (ok == 0) {
	i2c_end();
	return -1;		//device address send fail
    }
    while (data_addr_cnt > 0) {	//2 byte data address
	ok = i2c_send_byte(data_addr[data_addr_cnt]);	//send high byte first
	data_addr_cnt--;
	if (ok == 0) {
	    i2c_end();
	    return -2;		//word address send fail
	}
    }
    ok = i2c_send_byte(data_addr[0]);
    if (ok == 0) {
	i2c_end();
	return -2;		//word address send fail
    }
    for (int i = 0; i < data_len; i++) {
	ok = i2c_send_byte(data_write[i]);
	if (ok == 0) {
	    i2c_end();
	    return 0;		//data send fail
	}
    }
    i2c_end();

    i2c_set_sda();		//to produce sda/scl rising without causing end signal
    i2c_set_scl();
    return 1;
}

//---------------------------------------------------------------------------
bool RW_Func::USB_start()
{
    //Write
    int buf_idx = 0;
    unsigned char *WriteBuffer = new unsigned char[65];
    unsigned char *ReadBuffer = new unsigned char[65];

    WriteBuffer[buf_idx++] = I2C_START;	//Control Byte
    WriteBuffer[buf_idx++] = 0;	//Output Data length
    WriteBuffer[buf_idx++] = 0;	//DEVICE_ADDR
    USB.WriteReport(WriteBuffer, 3);	//USB Output Packet
    USB.ReadReportEx(ReadBuffer);	//USB Iutput Packet

    int r_ok = ReadBuffer[0];	//status byte
    delete[]WriteBuffer;
    delete[]ReadBuffer;
    return r_ok;
}

bool RW_Func::USB_stop()
{
    //Write
    int buf_idx = 0;
    unsigned char *WriteBuffer = new unsigned char[65];
    unsigned char *ReadBuffer = new unsigned char[65];

    WriteBuffer[buf_idx++] = I2C_STOP;	//Control Byte
    WriteBuffer[buf_idx++] = 0;	//Output Data length
    WriteBuffer[buf_idx++] = 0;	//DEVICE_ADDR
    USB.WriteReport(WriteBuffer, 2);	//USB Output Packet
    USB.ReadReportEx(ReadBuffer);	//USB Iutput Packet

    int r_ok = ReadBuffer[0];	//status byte
    delete[]WriteBuffer;
    delete[]ReadBuffer;
    return r_ok;
}

//--------------------------------------------------------------------------
// 20100608 有I2C_START與Device Address, 以Overflag決定是否有I2C_STOP的i2c package
bool RW_Func::USB_seq_write_P1(unsigned char dev_addr, unsigned char *data_addr, int data_addr_cnt,
			       unsigned char *data_write, int data_len, bool overflag)
{
    //Write
    int buf_idx = 0;
    unsigned char *WriteBuffer = new unsigned char[65];
    unsigned char *ReadBuffer = new unsigned char[65];

    if (overflag == 1)
	WriteBuffer[buf_idx++] = I2C_START | I2C_DEV_WRITE | I2C_STOP;	//Control Byte
    else
	WriteBuffer[buf_idx++] = I2C_START | I2C_DEV_WRITE;	//Control Byte

    WriteBuffer[buf_idx++] = data_len + (1 + data_addr_cnt);	//Output Data length
    WriteBuffer[buf_idx++] = (dev_addr >> 1);	//DEVICE_ADDR
    int addr_cnt1 = data_addr_cnt;
    while (addr_cnt1 > 0) {
	WriteBuffer[buf_idx++] = data_addr[addr_cnt1];	//DATA_ADDR
	addr_cnt1--;
    }
    WriteBuffer[buf_idx++] = data_addr[0];	//DATA_ADDR

    for (int i = 0; i < data_len; i++) {
	WriteBuffer[4 + data_addr_cnt + i] = data_write[i];	//Data Byte
    }
    USB.WriteReport(WriteBuffer, 3 + (1 + data_addr_cnt) + data_len);	//USB Output Packet
    USB.ReadReportEx(ReadBuffer);	//USB Iutput Packet

    int r_ok = ReadBuffer[0];	//status byte
    delete[]WriteBuffer;
    delete[]ReadBuffer;
    return r_ok;
}

bool RW_Func::USB_Data_Package(unsigned char *data, int data_len, bool overflag)
{
    //Write
    int buf_idx = 0;
    unsigned char *WriteBuffer = new unsigned char[65];
    unsigned char *ReadBuffer = new unsigned char[65];
    if (overflag > 0)
	WriteBuffer[buf_idx++] = I2C_STOP;	//Control Byte
    else
	WriteBuffer[buf_idx++] = 0;	//Control Byte
    WriteBuffer[buf_idx++] = data_len;	//Output Data length
    WriteBuffer[buf_idx++] = (data[0]);	//DEVICE_ADDR
    for (int i = 1; i < data_len; i++) {
	WriteBuffer[buf_idx++] = data[i];	//Data Byte
    }
    USB.WriteReport(WriteBuffer, 2 + data_len);	//USB Output Packet
    USB.ReadReportEx(ReadBuffer);	//USB Iutput Packet

    int r_ok = ReadBuffer[0];	//status byte
    delete[]WriteBuffer;
    delete[]ReadBuffer;
    return r_ok;
}


//---------------------------------------------------------------------------
// 20100608 有I2C_START與Device Address, 以Overflag決定是否有I2C_STOP的i2c package
bool RW_Func::USB_seq_read_P1(unsigned char dev_addr, unsigned char *data_addr, int data_addr_cnt,
			      unsigned char *data_read, int data_len, bool overflag)
{
    unsigned char *WriteBuffer = new unsigned char[65];
    unsigned char *ReadBuffer = new unsigned char[65];
    for (int i = 0; i < 65; i++) {
	WriteBuffer[i] = 0;
	ReadBuffer[i] = 0;
    }
    int buf_idx = 0;
    //Read
    WriteBuffer[buf_idx++] = I2C_START | I2C_DEV_WRITE;	//Control Byte
    WriteBuffer[buf_idx++] = 1 + data_addr_cnt;	//Output Data length
    WriteBuffer[buf_idx++] = (dev_addr >> 1);	//DEVICE_ADDR
    int addr_cnt1 = data_addr_cnt;
    while (addr_cnt1 > 0) {
	WriteBuffer[buf_idx++] = data_addr[addr_cnt1];	//DATA_ADDR
	addr_cnt1--;
    }
    WriteBuffer[buf_idx++] = data_addr[0];
    USB.WriteReport(WriteBuffer, 3 + (1 + data_addr_cnt));	//USB Output Packet
    USB.ReadReportEx(ReadBuffer);	//USB Iutput Packet

    buf_idx = 0;
    for (int i = 0; i < 65; i++) {
	WriteBuffer[i] = 0;
	ReadBuffer[i] = 0;
    }
    if (overflag == 0)
	WriteBuffer[buf_idx++] = I2C_RESTART | I2C_DEV_READ;	//Control Byte
    else
	WriteBuffer[buf_idx++] = I2C_RESTART | I2C_DEV_READ | I2C_STOP;	//Control Byte

    WriteBuffer[buf_idx++] = data_len;	//Output Data length
    WriteBuffer[buf_idx++] = (dev_addr >> 1);	//DEVICE_ADDR;
    USB.WriteReport(WriteBuffer, 3 + data_len);	//USB Output Packet
    USB.ReadReportEx(ReadBuffer);	//USB Iutput Packet
    for (int i = 0; i < data_len; i++) {	//1st byte is status byte
	data_read[i] = ReadBuffer[i + 1];
    }
    int r_ok = ReadBuffer[0];	//status byte
    delete[]WriteBuffer;
    delete[]ReadBuffer;
    return r_ok;
}

//---------------------------------------------------------------------------
// 20100608 沒有I2C_START, 並以"overflag"選擇加上或不加上I2C_STOP的i2c package
bool RW_Func::USB_r_Data_Package(unsigned char *data_read, int data_len, bool overflag)
{
    unsigned char *WriteBuffer = new unsigned char[65];
    unsigned char *ReadBuffer = new unsigned char[65];
    for (int i = 0; i < 65; i++) {
	WriteBuffer[i] = 0;
	ReadBuffer[i] = 0;
    }
    int buf_idx = 0;
    if (overflag == 0) {
	WriteBuffer[buf_idx++] = I2C_DEV_READ;	//Control Byte
	WriteBuffer[buf_idx++] = data_len;	//Output Data length
	WriteBuffer[buf_idx++] = (0x7d >> 1);	//DEVICE_ADDR;
	USB.WriteReport(WriteBuffer, 3 + data_len - 1);	//USB Output Packet
	//USB.WriteReport(WriteBuffer,3+data_len);      //USB Output Packet
	USB.ReadReportEx(ReadBuffer);	//USB Iutput Packet

	for (int i = 0; i < data_len; i++) {	//1st byte is status byte
	    data_read[i] = ReadBuffer[i + 1];
	}
    } else {
	if (data_len == 0)
	    data_len = 1;
	WriteBuffer[buf_idx++] = I2C_DEV_READ | I2C_STOP;	//Control Byte
	//WriteBuffer[buf_idx++] = data_len+1;       //Output Data length
	WriteBuffer[buf_idx++] = data_len;	//Output Data length
	WriteBuffer[buf_idx++] = (0x7d >> 1);	//DEVICE_ADDR;
	//USB.WriteReport(WriteBuffer,3+data_len+1);    //USB Output Packet
	USB.WriteReport(WriteBuffer, 3 + data_len);	//USB Output Packet
	USB.ReadReportEx(ReadBuffer);	//USB Iutput Packet

	for (int i = 0; i < data_len; i++) {	//1st byte is status byte
	    //data_read[i]=ReadBuffer[i+2];
	    data_read[i] = ReadBuffer[i + 1];
	}
    }

    int r_ok = ReadBuffer[0];	//status byte
    delete[]WriteBuffer;
    delete[]ReadBuffer;
    return r_ok;
}
//---------------------------------------------------------------------------
//----------------- 豆豆鳥I2C Control   20160603 byBS+ ----------------------
//---------------------------------------------------------------------------
bool RW_Func::DoDoBird_connect(void)
{
    FT_STATUS ftStatus;
    bool initial_flag = 0;

    ftStatus = FT_Open(1,&ftHandle);    //不能為0 (官方文件給0的例子)
    if (ftStatus == FT_OK)    // FT_Open OK, use ftHandle to access device
        return 1;
    else    // FT_Open failed
        return 0;

}
//---------------------------------------------------------------------------
void RW_Func::DoDoBird_disconnect(void)
{
        FT_Close(ftHandle);
        ftHandle = 0;
}
//---------------------------------------------------------------------------
//(1) Initialize FT2232H/FT232H as I2C Mode
//(2) Also set desire I2C Speed (step 2 you set before) in this function
bool RW_Func::DoDoBird_initialize(void)
{
        FT_STATUS ftStatus;

        DWORD EventDWord;
        DWORD TxBytes;      //DWORD : 32-bit
        DWORD RxBytes;
        DWORD BytesReceived;
        DWORD BytesWritten;
        char RxBuffer[256];
        char TxBuffer[256]; // Contains data to write to device


        //******************** Initializate FT2232H as I2C Mode **************************************************************
        //Reset USB device
        ftStatus = FT_ResetDevice(ftHandle);
        if(ftStatus!=FT_OK)
                return 0;

        //Purge USB receive buffer by reading out all old data from FT2232H's receive buffer
        ftStatus = FT_GetQueueStatus(ftHandle, &RxBytes);
        if(RxBytes > 0)
           ftStatus = FT_Read(ftHandle, RxBuffer, RxBytes, &BytesReceived);
        if(ftStatus!=FT_OK)                                //Pointer to a variable of type DWORD which receives the number of bytes in the receive queue.
                return 0;

        //Set USB request transfer size    (default transfer size of 4096 bytes)
        ftStatus = FT_SetUSBParameters(ftHandle, 65536, 65535);
        if(ftStatus!=FT_OK)
                return 0;

        //Disable event and error characters   (disable?)
        ftStatus = FT_SetChars(ftHandle, 0, 0, 0, 0);
        if(ftStatus!=FT_OK)
                return 0;

        //Sets the read and write timeouts in ms for the FT2232H
        ftStatus = FT_SetTimeouts(ftHandle, 500, 500);  //TCON 應該不用wite
        if(ftStatus!=FT_OK)
                return 0;

        //Set the latency timer  (?)
        ftStatus = FT_SetLatencyTimer(ftHandle, 10);
        if(ftStatus!=FT_OK)
                return 0;

        //Reset MPSSE controller   (Enables different chip modes)
        ftStatus = FT_SetBitMode(ftHandle, 0, 0);
        if(ftStatus!=FT_OK)
                return 0;

        //Enable MPSSE controller
        //ftStatus = FT_SetBitMode(FT2232H_B_Handle, 0, &H2);
        ftStatus = FT_SetBitMode(ftHandle, 0, 0x2);
        if(ftStatus!=FT_OK)
                return 0;

        //Wait for all the USB stuff to complete and work
        Sleep(50);

        //Disable clock divide by 5 for FT2232H's 60 MHz master clock
        TxBuffer[0] = 0x8A;
        ftStatus = FT_Write(ftHandle, TxBuffer, 1, &BytesWritten);
        if(ftStatus!=FT_OK)
                return 0;


        //Turn off adaptive clocking
        TxBuffer[0] = 0x97;
        ftStatus = FT_Write(ftHandle, TxBuffer, 1, &BytesWritten);
        if(ftStatus!=FT_OK)
                return 0;

        //Disable 3 phase data clocking
        TxBuffer[0] = 0x8D;
        ftStatus = FT_Write(ftHandle, TxBuffer, 1, &BytesWritten);
        if(ftStatus!=FT_OK)
                return 0;

        //Set I2C clock frequency here !
        //Out_Buf(1) = Value_L
        //Out_Buf(2) = Value_H
        TxBuffer[0]=0x86;
        TxBuffer[1]=0x4a;  //fixed 400Mhz setting
        TxBuffer[2]=0x0;   //fixed 400Mhzv
        ftStatus = FT_Write(ftHandle, TxBuffer, 3, &BytesWritten);
        if(ftStatus!=FT_OK)
                return 0;

        //Delay
        Sleep(20);

        //Turn off loop back of TDI/TDO connection
        TxBuffer[0]=0x85;
        ftStatus = FT_Write(ftHandle, TxBuffer, 1, &BytesWritten);
        if(ftStatus!=FT_OK)
                return 0;

        //Delay
        Sleep(30);
        return 1;

}
//---------------------------------------------------------------------------
/********************************************************************************************************************************
'  Subject:    IIC_MultiByte_Write
'  Function:   IIC_MultiByte_Write
'  Parameter:  device, address, *pdata, length
'  Return:     -1 mean I2C fail, 1 mean I2C success
'  Remark:     (a) S --> device/W --> address --> data(0) --> data(1) --> data(2) --> ... --> data(length - 1) --> P --> delay
'              (b) The delay time is fixed to 500us (0.5ms)
'********************************************************************************************************************************/
bool RW_Func::DoDoBird_write(unsigned char dev_addr, unsigned char *data_addr,
		    int data_addr_cnt, unsigned char *data_write, int data_len)
{
        int i;
        int index = 0;

        //unsigned char TxBuffer[2048];
        //unsigned char RxBuffer[256];
        unsigned char *TxBuffer = new unsigned char[2048+(313*data_len)];
        unsigned char *RxBuffer = new unsigned char[128+data_len];

        DWORD lpdwBytesWritten;
        DWORD lpdwBytesReturned;

        bool write_flag = -1;

        FT_STATUS ftStatus = FT_Purge(ftHandle, 0x3);
        if(ftStatus!=FT_OK)
                return 0;


        //******************** Start *********************************************************************
        //ISDA=1 (AD_1, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x2;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //ISCL=1 (AD_0, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x3;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //ISDA=0 (AD_1, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x1;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //ISCL=0 (AD_0, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x0;      index++;
            TxBuffer[index] = 0x3;      index++;
        }

        //******************** Device Address/W ******************************************************
        //FT2232H Send 8 bits data automatically
        TxBuffer[index]  = 0x11;         index++;
        TxBuffer[index]  = 0x0;          index++;
        TxBuffer[index]  = 0x0;          index++;
        //TxBuffer[index]  = *device;      index++;
        TxBuffer[index]  = dev_addr;      index++;
        //Let AD_1 (DO) ouput high for receiving data from AD_2 (DI)
        //Modify loop number to increase time delay
        for(i = 0; i<=TIME_8TH_9TH; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x2;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //FT2232H scan ack bit automatically
        TxBuffer[index] = 0x22;         index++;
        TxBuffer[index] = 0x0;          index++;
        TxBuffer[index] = 0x87;         index++;
        //Keep Remaining AD_1 (DO) ouput high
        //Modify loop number to increase time delay
        for(i = 0; i<=TIME_DATA_WRITE; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x2;      index++;
            TxBuffer[index] = 0x3;      index++;
        }

        //******************** Register Address 1******************************************************
        int addr_index = data_addr_cnt;
        while (addr_index>=0) {
                //FT2232H Send 8 bits data automatically
                TxBuffer[index] = 0x11;         index++;
                TxBuffer[index] = 0x0;          index++;
                TxBuffer[index] = 0x0;          index++;
                TxBuffer[index] = data_addr[addr_index]; index++;
                //TxBuffer[index] = data_addr[0]; index++;
                //Let AD_1 (DO) ouput high for receiving data from AD_2 (DI)
                //Modify loop number to increase time delay
                for(i = 0; i<=TIME_8TH_9TH; i++) {
                    TxBuffer[index] = 0x80;     index++;
                    TxBuffer[index] = 0x2;      index++;
                    TxBuffer[index] = 0x3;      index++;
                }
                //FT2232H scan ack bit automatically
                TxBuffer[index] = 0x22;         index++;
                TxBuffer[index] = 0x0;          index++;
                TxBuffer[index] = 0x87;         index++;
                //Keep Remaining AD_1 (DO) ouput high
                //Modify loop number to increase time delay
                for(i = 0; i<=TIME_DATA_WRITE; i++) {
                    TxBuffer[index] = 0x80;     index++;
                    TxBuffer[index] = 0x2;      index++;
                    TxBuffer[index] = 0x3;      index++;
                }
                addr_index--;
        }

        //******************** Register Address 2******************************************************
        //FT2232H Send 8 bits data automatically
        /*TxBuffer[index] = 0x11;         index++;
        TxBuffer[index] = 0x0;          index++;
        TxBuffer[index] = 0x0;          index++;
        TxBuffer[index] = data_addr[1]; index++;       //先試1-byte的address
        //Let AD_1 (DO) ouput high for receiving data from AD_2 (DI)
        //Modify loop number to increase time delay
        for(i = 0; i<=TIME_8TH_9TH; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x2;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //FT2232H scan ack bit automatically
        TxBuffer[index] = 0x22;         index++;
        TxBuffer[index] = 0x0;          index++;
        TxBuffer[index] = 0x87;         index++;
        //Keep Remaining AD_1 (DO) ouput high
        //Modify loop number to increase time delay
        for(i = 0; i<=TIME_DATA_WRITE; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x2;      index++;
            TxBuffer[index] = 0x3;      index++;
        }*/

        //********************* Data ******************************************************************
        for(int j=0; j<data_len; j++) {
                //FT2232H Send 8 bits data automatically
                TxBuffer[index] = 0x11;           index++;
                TxBuffer[index] = 0x0;            index++;
                TxBuffer[index] = 0x0;            index++;
                TxBuffer[index] = data_write[j];  index++;
                //Let AD_1 (DO) ouput high for receiving data from AD_2 (DI)
                //Modify loop number to increase time delay
                for(i = 0; i<=TIME_8TH_9TH; i++) {
                    TxBuffer[index] = 0x80;     index++;
                    TxBuffer[index] = 0x2;      index++;
                    TxBuffer[index] = 0x3;      index++;
                }
                //FT2232H scan ack bit automatically
                TxBuffer[index] = 0x22;         index++;
                TxBuffer[index] = 0x0;          index++;
                TxBuffer[index] = 0x87;         index++;
                //Keep Remaining AD_1 (DO) ouput high
                //Modify loop number to increase time delay
                for(i = 0; i<=TIME_DATA_WRITE; i++) {
                    TxBuffer[index] = 0x80;     index++;
                    TxBuffer[index] = 0x2;      index++;
                    TxBuffer[index] = 0x3;      index++;
                }
        }

        //******************** Stop *********************************************************************
        //ISDA=0 (AD_1, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x0;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //ISCL=1 (AD_0, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x1;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //ISDA=1 (AD_1, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x3;      index++;
            TxBuffer[index] = 0x3;      index++;
        }

        //******************** Delay 500us ***********************************************************
        //ISDA=1 and ISCL=1
        for(i = 0; i<=5; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x3;      index++;
            TxBuffer[index] = 0x3;      index++;
        }

        //******************** Send OP-Code here *****************************************************
        ftStatus = FT_Write(ftHandle, TxBuffer, index, &lpdwBytesWritten);
        if(ftStatus!=FT_OK || index!=lpdwBytesWritten)
                return 0;
        ftStatus = FT_Read(ftHandle, RxBuffer, (data_len+data_addr_cnt+2), &lpdwBytesReturned);
        if(ftStatus!=FT_OK || (data_len+data_addr_cnt+2)!=lpdwBytesReturned)
                return 0;

        //******************** Check every Ack *******************************************************
        for(i = 0; i<(data_len+data_addr_cnt+2); i++) {
            if(((~RxBuffer[i]) & 1)!=0) {
                //ShowMessage("I2C transmission failure");
                return 0;
            }
        }

        write_flag = 1;
        delete[]TxBuffer;
        delete[]RxBuffer;
        return write_flag;

}
//---------------------------------------------------------------------------
/*********************************************************************************************************************************************************
'  Subject:    IIC_MultiByte_Read
'  Function:   IIC_MultiByte_Read
'  Parameter:  device, address, *pdata, length
'  Return:     -1 mean I2C fail, 1 mean I2C success
'  Remark:     S --> device/W --> address --> S --> device/R --> data_out(0) --> A --> data_out(1) --> A --> .... --> data_out(length - 1) --> NA --> P
'*********************************************************************************************************************************************************/
bool RW_Func::DoDoBird_read(unsigned char dev_addr, unsigned char *data_addr,
                   int data_addr_cnt, unsigned char *data_read, int data_len)
{
        int i;
        int index = 0;
        unsigned char *TxBuffer = new unsigned char[4096];
        unsigned char *RxBuffer = new unsigned char[128+data_len];
        //unsigned char data;
        DWORD lpdwBytesWritten;
        DWORD lpdwBytesReturned;

        int read_flag = -1;

        FT_STATUS ftStatus = FT_Purge(ftHandle, 0x3);
        if(ftStatus!=FT_OK)
                return 0;


        //******************** Start *********************************************************************
        //ISDA=1 (AD_1, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x2;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //ISCL=1 (AD_0, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x3;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //ISDA=0 (AD_1, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x1;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //ISCL=0 (AD_0, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x0;      index++;
            TxBuffer[index] = 0x3;      index++;
        }

        //******************** Device Address/W ******************************************************
        //FT2232H Send 8 bits data automatically
        TxBuffer[index]  = 0x11;         index++;
        TxBuffer[index]  = 0x0;          index++;
        TxBuffer[index]  = 0x0;          index++;
        TxBuffer[index]  = dev_addr;      index++;
        //Let AD_1 (DO) ouput high for receiving data from AD_2 (DI)
        //Modify loop number to increase time delay
        for(i = 0; i<=TIME_8TH_9TH; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x2;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //FT2232H scan ack bit automatically
        TxBuffer[index] = 0x22;         index++;
        TxBuffer[index] = 0x0;          index++;
        TxBuffer[index] = 0x87;         index++;
        //Keep Remaining AD_1 (DO) ouput high
        //Modify loop number to increase time delay
        for(i = 0; i<=TIME_DATA_WRITE; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x2;      index++;
            TxBuffer[index] = 0x3;      index++;
        }

        //******************** Register Address 1******************************************************
        int addr_index = data_addr_cnt;
        while (addr_index>=0) {
                //FT2232H Send 8 bits data automatically
                TxBuffer[index] = 0x11;         index++;
                TxBuffer[index] = 0x0;          index++;
                TxBuffer[index] = 0x0;          index++;
                TxBuffer[index] = data_addr[addr_index]; index++;
                //TxBuffer[index] = data_addr[0]; index++;
                //Let AD_1 (DO) ouput high for receiving data from AD_2 (DI)
                //Modify loop number to increase time delay
                for(i = 0; i<=TIME_8TH_9TH; i++) {
                    TxBuffer[index] = 0x80;     index++;
                    TxBuffer[index] = 0x2;      index++;
                    TxBuffer[index] = 0x3;      index++;
                }
                //FT2232H scan ack bit automatically
                TxBuffer[index] = 0x22;         index++;
                TxBuffer[index] = 0x0;          index++;
                TxBuffer[index] = 0x87;         index++;
                //Keep Remaining AD_1 (DO) ouput high
                //Modify loop number to increase time delay
                for(i = 0; i<=TIME_DATA_WRITE; i++) {
                    TxBuffer[index] = 0x80;     index++;
                    TxBuffer[index] = 0x2;      index++;
                    TxBuffer[index] = 0x3;      index++;
                }
                addr_index--;
        }

        //******************** Register Address 2******************************************************
        //FT2232H Send 8 bits data automatically
        /*TxBuffer[index] = 0x11;         index++;
        TxBuffer[index] = 0x0;          index++;
        TxBuffer[index] = 0x0;          index++;
        TxBuffer[index] = data_addrrss[0]; index++;       //先試1-byte的address
        //Let AD_1 (DO) ouput high for receiving data from AD_2 (DI)
        //Modify loop number to increase time delay
        for(i = 0; i<=TIME_8TH_9TH; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x2;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //FT2232H scan ack bit automatically
        TxBuffer[index] = 0x22;         index++;
        TxBuffer[index] = 0x0;          index++;
        TxBuffer[index] = 0x87;         index++;
        //Keep Remaining AD_1 (DO) ouput high
        //Modify loop number to increase time delay
        for(i = 0; i<=TIME_DATA_WRITE; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x2;      index++;
            TxBuffer[index] = 0x3;      index++;
        }*/

        //******************** Start *********************************************************************
        //ISDA=1 (AD_1, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x2;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //ISCL=1 (AD_0, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x3;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //ISDA=0 (AD_1, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x1;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //ISCL=0 (AD_0, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x0;      index++;
            TxBuffer[index] = 0x3;      index++;
        }


        //******************** Device Address/R ******************************************************
        //FT2232H Send 8 bits data automatically
        TxBuffer[index]  = 0x11;         index++;
        TxBuffer[index]  = 0x0;          index++;
        TxBuffer[index]  = 0x0;          index++;
        TxBuffer[index]  = dev_addr+1;      index++;     //+1 for read
        //Let AD_1 (DO) ouput high for receiving data from AD_2 (DI)
        //Modify loop number to increase time delay
        for(i = 0; i<=TIME_8TH_9TH; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x2;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //FT2232H scan ack bit automatically
        TxBuffer[index] = 0x22;         index++;
        TxBuffer[index] = 0x0;          index++;
        TxBuffer[index] = 0x87;         index++;
        //Keep Remaining AD_1 (DO) ouput high
        //Modify loop number to increase time delay
        for(i = 0; i<=TIME_DATA_WRITE; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x2;      index++;
            TxBuffer[index] = 0x3;      index++;
        }

        //******************** Read Data *************************************************************
        for(int j=0; j<data_len-1; j++) {
            //Let AD_1 (DO) ouput high for receiving data from AD_2 (DI)
            //Modify loop number to increase time delay
            for(i = 0; i<=TIME_DATA_READ; i++) {
                TxBuffer[index] = 0x80;     index++;
                TxBuffer[index] = 0x2;      index++;
                TxBuffer[index] = 0x3;      index++;
            }
            //FT2232H receive 8 bits data automatically
            TxBuffer[index] = 0x20;         index++;
            TxBuffer[index] = 0x0;          index++;
            TxBuffer[index] = 0x0;          index++;
            TxBuffer[index] = 0x87;         index++;
            //Send Ack automatically !
            TxBuffer[index] = 0x13;         index++;
            TxBuffer[index] = 0x0;          index++;
            TxBuffer[index] = 0x0;         index++; //bit7 is ack
        }

        //******************** Read last data ***************************************************************************************************************
        //Let AD_1 (DO) ouput high for receiving data from AD_2 (DI)
        //Modify loop number to increase time delay
        for(i = 0; i<=TIME_DATA_READ; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x2;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //FT2232H receive 8 bits data automatically
        TxBuffer[index] = 0x20;         index++;
        TxBuffer[index] = 0x0;          index++;
        TxBuffer[index] = 0x0;          index++;
        TxBuffer[index] = 0x87;         index++;
        //Send N_Ack automatically !
        TxBuffer[index] = 0x13;         index++;
        TxBuffer[index] = 0x0;          index++;
        TxBuffer[index] = 0x80;         index++; //bit7 is ack

        //******************** Stop *********************************************************************
        //ISDA=0 (AD_1, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x0;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //ISCL=1 (AD_0, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x1;      index++;
            TxBuffer[index] = 0x3;      index++;
        }
        //ISDA=1 (AD_1, Repeat commands to ensure the minimum period is achieced)
        for(i = 0; i<30; i++) {
            TxBuffer[index] = 0x80;     index++;
            TxBuffer[index] = 0x3;      index++;
            TxBuffer[index] = 0x3;      index++;
        }

        //******************** Send OP-Code here *****************************************************
        ftStatus = FT_Write(ftHandle, TxBuffer, index, &lpdwBytesWritten);
        if(ftStatus!=FT_OK || index!=lpdwBytesWritten)
                return 0;
        ftStatus = FT_Read(ftHandle, RxBuffer, (data_len+data_addr_cnt+3), &lpdwBytesReturned);
        if(ftStatus!=FT_OK || (data_len+data_addr_cnt+3)!=lpdwBytesReturned)
                return 0;

        //******************** Check every Ack *******************************************************
        for(i = 0; i< (data_addr_cnt+3); i++) {
            if(((~RxBuffer[i]) & 1)!=0) {
                return 0;
            }
        }

        //******************** Get Data **************************************************************
        for(int j=0; j<data_len; j++) {

                data_read[j] = ~RxBuffer[j+data_addr_cnt+3];
        }

        read_flag = 1;
        delete[]TxBuffer;
        delete[]RxBuffer;
        return read_flag;

}
