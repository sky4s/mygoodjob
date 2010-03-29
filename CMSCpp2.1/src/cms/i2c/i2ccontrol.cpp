#include <includeall.h>
#pragma hdrstop
#include "i2ccontrol.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件


namespace cms {
    namespace i2c {
	using namespace java::lang;
	using namespace cms::util;

	//======================================================================
	// DeviceAddressSendFailException
	//======================================================================
	 DeviceAddressSendFailException::DeviceAddressSendFailException() {
	};
	 DeviceAddressSendFailException::
	    DeviceAddressSendFailException(std::
					   string
					   message):RuntimeException
	    (message) {
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
      DataSendFailException::DataSendFailException(std::string message):RuntimeException(message)
	{
	};
	//======================================================================

	//======================================================================
	// i2cControl
	//======================================================================
	RW_Func i2cControl::i2cio;
              int i2cControl::getDataAddressLength(const AddressingSize size) {
                switch(size) {
                 case _2k:
                 case _4k:
                 case _8k:
                 case _16k:
                 return 1;
                 default:
                 return 2;
                }
            };
                        const unsigned char  i2cControl::getRealDeviceAddress() {
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
    }*/
                          switch(size) {
                           case _4k: //1
                           return (deviceAddress & 0xFC) + (dataAddressByteArray[1] & 0x01);
                           case _8k: //2
                           return (deviceAddress & 0xF8) + (dataAddressByteArray[1] & 0x03);
                           case _16k: //3
                           return (deviceAddress & 0xF0) + (dataAddressByteArray[1] & 0x07);
                           default:
                                return deviceAddress;
                          }

                        };

	     i2cControl::i2cControl(const unsigned char deviceAddress,
		 const AddressingSize size):deviceAddress
	    (deviceAddress), dataAddressLength(getDataAddressLength(size)),size(size) {
               	    if (dataAddressLength != 1 && dataAddressLength != 2) {
		throw
		    IllegalArgumentException
		    ("dataAddressLength != 1 && dataAddressLength != 2");
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
	};*/
            unsigned char  * i2cControl::getDataAddressByteArray(int dataAddress) {
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
	unsigned char*  dataAddressByteArray=  getDataAddressByteArray(dataAddress);
             const unsigned char  realDeviceAddress= getRealDeviceAddress();
	    int dataLength = data->getSize();
	    write0(realDeviceAddress, dataAddressByteArray,
		   dataAddressLength - 1, data->buffer, dataLength);
	};
	void i2cControl::writeByte(int dataAddress, unsigned char data) {
	    	unsigned char*  dataAddressByteArray=  getDataAddressByteArray(dataAddress);
                         const unsigned char  realDeviceAddress= getRealDeviceAddress();
	    bptr < ByteBuffer > byteBuffer(new ByteBuffer(1));
	    (*byteBuffer)[0] = data;
	    write0(realDeviceAddress, dataAddressByteArray,
		   dataAddressLength - 1, byteBuffer->buffer, 1);
	};
	bptr < ByteBuffer > i2cControl::read(int dataAddress,
					     int dataLength) {
	    bptr < ByteBuffer > data(new ByteBuffer(dataLength));
	    	unsigned char*  dataAddressByteArray=  getDataAddressByteArray(dataAddress);
            const unsigned char  realDeviceAddress= getRealDeviceAddress();
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
				       const AddressingSize size) {
	    return bptr < i2cControl >
		(new i2cLPTControl(deviceAddress, size));
	};
	bptr < i2cControl >
	    i2cControl::getUSBInstance(const unsigned char deviceAddress,
				        const AddressingSize size,
				       USBPower power, USBSpeed speed) {
	    return bptr < i2cControl >
		(new
		 i2cUSBControl(deviceAddress, size, power,
			       speed));
	};
	//======================================================================

	//======================================================================
	// i2cLPTControl
	//======================================================================
	void i2cLPTControl::write0(unsigned char dev_addr,
				   unsigned char *data_addr,
				   int data_addr_cnt,
				   unsigned char *data_write,
				   int data_len) {
	    int result =
		i2cio.LPT_Write(dev_addr, data_addr, data_addr_cnt,
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
				  int data_addr_cnt,
				  unsigned char *data_read, int data_cnt) {
	    int result =
		i2cio.LPT_Read_seq(dev_addr, data_addr, data_addr_cnt,
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
				      const AddressingSize size):i2cControl
	    (deviceAddress, size) {
	    int result = i2cio.LPT_connect();
	    using namespace java::lang;
	    switch (result) {
	    case 0:
		throw IllegalStateException("No LPT Dll found.");
	    case -1:
		throw
		    IllegalStateException
		    ("GetProcAddress for Inp32 Failed.");
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
				   int data_addr_cnt,
				   unsigned char *data_write,
				   int data_len) {
	    i2cio.USB_write(dev_addr, data_addr, data_addr_cnt, data_write,
			    data_len);
	};
	void i2cUSBControl::read0(unsigned char dev_addr,
				  unsigned char *data_addr,
				  int data_addr_cnt,
				  unsigned char *data_read, int data_cnt) {
	    i2cio.USB_read(dev_addr, data_addr, data_addr_cnt, data_read,
			   data_cnt);
	};
	i2cUSBControl::i2cUSBControl(const unsigned char deviceAddress,
				      const AddressingSize size,
				     USBPower power,
				     USBSpeed
				     speed):i2cControl(deviceAddress,
						       size),
	    power(power), speed(speed) {

	};
	bool i2cUSBControl::connect() {
	    return i2cio.USB_connect(power, speed);
	};
	void i2cUSBControl::disconnect() {
	    i2cio.USB_disconnect();
	};
	i2cUSBControl::~i2cUSBControl() {
	    disconnect();
	};
	//======================================================================
    };
};

