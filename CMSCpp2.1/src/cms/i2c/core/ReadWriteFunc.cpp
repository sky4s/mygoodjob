//---------------------------------------------------------------------------


//#pragma hdrstop

#include "ReadWriteFunc.h"

//---------------------------------------------------------------------------

//#pragma package(smart_init)

RW_Func::RW_Func()
{
}


//--------------------------------------------------------------------------
int RW_Func::LPT_Read_Byte_Skip_Ack(unsigned char dev_addr,
				    unsigned char *data_addr,
				    int data_addr_cnt,
				    unsigned char *data_read)
{
    bool ok = true;
    i2c_start();
    Ack_Stop_remove();
    ok = i2c_send_byte(dev_addr & 0xFE);	//write
    while (data_addr_cnt > 0) {	//2 byte data address
	Ack_Stop_remove();
	ok = i2c_send_byte(data_addr[data_addr_cnt]);	//send high byte first
	data_addr_cnt--;
    }
    Ack_Stop_remove();
    ok = i2c_send_byte(data_addr[0]);
    Ack_Stop_remove();
    i2c_read_byte(dev_addr, data_read);
    return 1;
}

//---------------------------------------------------------------------------

int RW_Func::LPT_Read_Byte(unsigned char dev_addr,
			   unsigned char *data_addr, int data_addr_cnt,
			   unsigned char *data_read)
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
			  int data_addr_cnt, unsigned char *data_read,
			  int data_cnt)
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
		       int data_addr_cnt, unsigned char *data_read,
		       int data_len)
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
			int data_addr_cnt, unsigned char *data_write,
			int data_len)
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
			       unsigned char *data_write, int data_len,
			       int flag)
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
		       int data_addr_cnt, unsigned char *data_write,
		       int data_len)
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

