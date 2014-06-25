#include <includeall.h>
#pragma hdrstop
#include "i2ccontrol.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <i2c/core/PrintPortI2C.h>
#define PAC_SIZE 56

namespace i2c {
    using namespace java::lang;
    using namespace cms::util;

    //======================================================================
    // DeviceAddressSendFailException
    //======================================================================
     DeviceAddressSendFailException::DeviceAddressSendFailException() {
    };
  DeviceAddressSendFailException::DeviceAddressSendFailException(std::string message):RuntimeException
	(message)
    {
    };
    //======================================================================
    DataAddressSendFailException::DataAddressSendFailException() {
    };
  DataAddressSendFailException::DataAddressSendFailException(std::string message):RuntimeException(message)
    {
    };
    //======================================================================
    DataSendFailException::DataSendFailException() {
    };
  DataSendFailException::DataSendFailException(std::string message):RuntimeException(message) {
    };
    //======================================================================

    //======================================================================
    // i2cControl
    //======================================================================
    RW_Func i2cControl::i2cio;
    int i2cControl::getDataAddressLength(const AddressingSize size) {
	switch (size) {
	case _2k:
	case _4k:
	case _8k:
	case _16k:
	    return 1;
	default:
	    return 2;
	}
    };
    const unsigned char i2cControl::getRealDeviceAddress() {
	/*int itemIndex = cbo_mem_addr_size->ItemIndex;
	   //從記憶體的大小決定dev_ad_new要怎麼設定, dev_ad => dev_ad_new
	   if (itemIndex == 1) {
	   *dev_ad_new = (dev_ad & 0xFC) + (data_ad[1] & 0x01);
	   } else if (itemIndex == 2) {
	   *dev_ad_new = (dev_ad & 0xF8) + (data_ad[1] & 0x03);
	   } else if (itemIndex == 3) {
	   *dev_ad_new = (dev_ad & 0xF0) + (data_ad[1] & 0x07);
	   } else {
	   *dev_ad_new = dev_ad;
	   } */
	switch (size) {
	case _4k:		//1
	    return (deviceAddress & 0xFC) + (dataAddressByteArray[1] & 0x01);
	case _8k:		//2
	    return (deviceAddress & 0xF8) + (dataAddressByteArray[1] & 0x03);
	case _16k:		//3
	    return (deviceAddress & 0xF0) + (dataAddressByteArray[1] & 0x07);
	default:
	    return deviceAddress;
	}

    };

  i2cControl::i2cControl(const unsigned char deviceAddress, const AddressingSize size, const int dataByteNum):deviceAddress
	(deviceAddress), dataAddressLength(getDataAddressLength(size)),
	size(size), dataByteNum(dataByteNum) {
	if (dataAddressLength != 1 && dataAddressLength != 2) {
	    throw IllegalArgumentException("dataAddressLength != 1 && dataAddressLength != 2");
	}
        if (dataByteNum != 1 && dataByteNum != 2) {
	    throw IllegalArgumentException("dataByteNum != 1 && dataByteNum != 2");
	}
    };
    /*void i2cControl::initDataAddress(int dataAddress) {
       dataAddressLength = dataAddress > 255 ? 2 : 1;
       dataAddressByteArray[0] = dataAddress & 255;
       if (dataAddressLength == 2) {
       dataAddressByteArray[1] = dataAddress >> 8 & 255;
       }
       }; */
    /*void i2cControl::setDataAddressByteArray(int dataAddress) {
       dataAddressByteArray[0] = dataAddress & 255;
       if (dataAddressLength == 2) {
       dataAddressByteArray[1] = dataAddress >> 8 & 255;
       }
       }; */
    unsigned char *i2cControl::getDataAddressByteArray(int dataAddress) {
	dataAddressByteArray[0] = dataAddress & 255;
	if (dataAddressLength == 2) {
	    dataAddressByteArray[1] = dataAddress >> 8 & 255;
	}
	return dataAddressByteArray;
    };
    /*
       int LPT_Write(unsigned char dev_addr, unsigned char *data_addr,
       int data_addr_cnt, unsigned char *data_write,
       int data_len);

       bool USB_write(unsigned char dev_addr, unsigned char *data_addr,
       int data_addr_cnt, unsigned char *data_write,
       int data_len);
     */
    void i2cControl::write(int dataAddress, bptr < ByteBuffer > data) {
	unsigned char *dataAddressByteArray = getDataAddressByteArray(dataAddress);
	const unsigned char realDeviceAddress = getRealDeviceAddress();
	int dataLength = data->getSize();
	write0(realDeviceAddress, dataAddressByteArray,
	       dataAddressLength - 1, data->buffer, dataLength);
    };

 
    void i2cControl::writeByte(int dataAddress, unsigned char data) {
	unsigned char *dataAddressByteArray = getDataAddressByteArray(dataAddress);
	const unsigned char realDeviceAddress = getRealDeviceAddress();
	bptr < ByteBuffer > byteBuffer(new ByteBuffer(1));
	(*byteBuffer)[0] = data;
	write0(realDeviceAddress, dataAddressByteArray,
	       dataAddressLength - 1, byteBuffer->buffer, 1);
    };
    bptr < ByteBuffer > i2cControl::read(int dataAddress, int dataLength) {
	bptr < ByteBuffer > data(new ByteBuffer(dataLength));
	unsigned char *dataAddressByteArray = getDataAddressByteArray(dataAddress);
	const unsigned char realDeviceAddress = getRealDeviceAddress();
	read0(realDeviceAddress, dataAddressByteArray,
	      dataAddressLength - 1, data->buffer, dataLength);
	return data;
    };
    unsigned char i2cControl::readByte(int dataAddress) {
	bptr < ByteBuffer > buffer = read(dataAddress, 1);
	return (*buffer)[0];
    };

    bptr < i2cControl >
	i2cControl::getLPTInstance(const unsigned char deviceAddress,
				   const AddressingSize size,
                                   const LPTCard card) {
	return bptr < i2cControl > (new i2cLPTControl(deviceAddress, size, card));
    };
    bptr < i2cControl >
	i2cControl::getUSBInstance(const unsigned char deviceAddress,
				   const AddressingSize size, const int dataByteNum,
                                   USBPower power, USBSpeed speed) {
	return bptr < i2cControl > (new i2cUSBControl(deviceAddress, size, dataByteNum, power, speed));
    };
    bptr < i2cControl >
	i2cControl::getDoDoBirdInstance(const unsigned char deviceAddress,
				        const AddressingSize size, const int dataByteNum) {
	return bptr < i2cControl > (new i2cDoDoBirdControl(deviceAddress, size, dataByteNum));
    };

    //======================================================================

    //======================================================================
    // i2cLPTControl
    //======================================================================
    void i2cLPTControl::write0(unsigned char dev_addr,
			       unsigned char *data_addr,
			       int data_addr_cnt, unsigned char *data_write, int data_len) {
	int result = i2cio.LPT_Write(dev_addr, data_addr, data_addr_cnt,
				     data_write, data_len);
	switch (result) {
	case 0:
	    throw DataSendFailException();
	case -1:
	    throw DeviceAddressSendFailException();
	case -2:
	    throw DataAddressSendFailException();
	};
    };

    void i2cLPTControl::read0(unsigned char dev_addr,
			      unsigned char *data_addr,
			      int data_addr_cnt, unsigned char *data_read, int data_cnt) {
	int result = i2cio.LPT_Read_seq(dev_addr, data_addr, data_addr_cnt,
					data_read, data_cnt);
	switch (result) {
	case 0:
	    throw DataSendFailException();
	case -1:
	    throw DeviceAddressSendFailException();
	case -2:
	    throw DataAddressSendFailException();
	};
    };

    bool i2cLPTControl::connect() {
	read(0, 1);
	return true;
    };
    void i2cLPTControl::disconnect() {
    };
    i2cLPTControl::i2cLPTControl(const unsigned char
				 deviceAddress,
				 const AddressingSize size,
				 const LPTCard card):i2cControl(deviceAddress, size, 1) {
	switch (card) {
	case Large:
	    SetCardLarge();
	    break;
	case Small:
	    SetCardSmall();
	    break;
	}

	int result = i2cio.LPT_connect();
	using namespace java::lang;
	switch (result) {
	case 0:
	    throw IllegalStateException("No LPT Dll found.");
	case -1:
	    throw IllegalStateException("GetProcAddress for Inp32 Failed.");
	case -2:
	    throw IllegalStateException("ECR Byte Mode setting fail.");
	};
    };
    //======================================================================

    //======================================================================
    // i2cUSBControl
    //======================================================================
    void i2cUSBControl::write0(unsigned char dev_addr,
			       unsigned char *data_addr,
			       int data_addr_cnt, unsigned char *data_write, int data_len) {
        if(data_len <= PAC_SIZE)
	    i2cio.USB_write(dev_addr, data_addr, data_addr_cnt, data_write, data_len);
        else {   // for LUT write from TCON Toolkit    201310 byBS+

            int pck_size = PAC_SIZE;
            int tmp_len = data_len; //data length remain after data transmit

            unsigned char* data_write_packet = new unsigned char [PAC_SIZE];
            for(int i = 0; i < PAC_SIZE; i++)
                data_write_packet[i] = data_write[i];         

            bool overflag = 0;
            // package1 (Send START + DEVICE)
            i2cio.USB_seq_write_P1(dev_addr, data_addr, data_addr_cnt, data_write_packet, pck_size, overflag);

            tmp_len -= pck_size;
            int start_data = pck_size;

            //package 2,3,...
            while(tmp_len > 0) {
                for(int i = 0; i < PAC_SIZE; i++)
                    data_write_packet[i] = data_write[start_data+i];

                if(tmp_len <= pck_size){  //End package (Send STOP)
                    overflag = 1;
                    i2cio.USB_Data_Package(data_write_packet, tmp_len, overflag);
                    tmp_len = 0;
                } else{                   //(Send DATA)
                    overflag = 0;
                    i2cio.USB_Data_Package(data_write_packet, pck_size, overflag);
                    tmp_len-=pck_size;
                    start_data+= pck_size;
                }
           }
           if(data_write_packet!= NULL)
                    delete [] data_write_packet;
        }
    };
    void i2cUSBControl::read0(unsigned char dev_addr,
			      unsigned char *data_addr,
			      int data_addr_cnt, unsigned char *data_read, int data_cnt) {
	i2cio.USB_read(dev_addr, data_addr, data_addr_cnt, data_read, data_cnt);
    };
    i2cUSBControl::i2cUSBControl(const unsigned char deviceAddress,
				 const AddressingSize size,
                                 const int dataByteNum,
				 USBPower power,
				 USBSpeed  speed):
                                 i2cControl(deviceAddress, size, dataByteNum), power(power), speed(speed) {


    };
    bool i2cUSBControl::connect() {
	return i2cio.USB_connect(power, speed);
    };
    void i2cUSBControl::disconnect() {
	i2cio.USB_disconnect();
    };
    i2cUSBControl::~i2cUSBControl() {
	//disconnect();
    };
    //======================================================================

    //======================================================================
    // i2cDoDoBirdControl
    //======================================================================
    void i2cDoDoBirdControl::write0(unsigned char dev_addr,
			       unsigned char *data_addr,
			       int data_addr_cnt, unsigned char *data_write, int data_len) {
        bool write_ok;
        write_ok = i2cio.DoDoBird_write(dev_addr, data_addr, data_addr_cnt, data_write, data_len);

        if(write_ok==0)
            throw DataSendFailException();

    };
    void i2cDoDoBirdControl::read0(unsigned char dev_addr,
			      unsigned char *data_addr,
			      int data_addr_cnt, unsigned char *data_read, int data_cnt) {
        bool read_ok;
	read_ok = i2cio.DoDoBird_read(dev_addr, data_addr, data_addr_cnt, data_read, data_cnt);

        if(read_ok==0)
            throw DataSendFailException();
    };

    bool i2cDoDoBirdControl::connect() {

	 if (i2cio.DoDoBird_connect()) {         //連接卡
             if(i2cio.DoDoBird_initialize()) {   //卡片初始化
                return 1;
             } else {
                ShowMessage("I2C Card Initial failed");
                return 0;
             }
         } else {
             return 0;
         }
    };
    void i2cDoDoBirdControl::disconnect() {
	i2cio.DoDoBird_disconnect();
    };
    i2cDoDoBirdControl::~i2cDoDoBirdControl() {
	//disconnect();
    };
    i2cDoDoBirdControl::i2cDoDoBirdControl(const unsigned char deviceAddress,
                                           const AddressingSize size, const int dataByteNum) :
                                           i2cControl(deviceAddress, size, dataByteNum){


    };

    //======================================================================
};

