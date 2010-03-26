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
	//======================================================================
	// ByteBuffer
	//======================================================================
	 ByteBuffer::ByteBuffer(const unsigned int size):size(size) {
	    buffer = new unsigned char[size];
	};
	 ByteBuffer::~ByteBuffer() {
	    delete[]buffer;
	};
	unsigned char &ByteBuffer::operator[] (const size_t index) {
	    if (index >= size) {
		throw IndexOutOfBoundsException();
	    }
	    return buffer[index];
	};
	const unsigned char &ByteBuffer::operator[] (const size_t index) const {
	    if (index >= size) {
		throw IndexOutOfBoundsException();
	    }
	    return buffer[index];
	};
	//======================================================================

	//======================================================================
	// DeviceAddressSendFailException
	//======================================================================
	DeviceAddressSendFailException::DeviceAddressSendFailException() {
	};
      DeviceAddressSendFailException::DeviceAddressSendFailException(std::string message):RuntimeException(message)
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
      DataSendFailException::DataSendFailException(std::string message):RuntimeException(message)
	{
	};
	//======================================================================

	//======================================================================
	// i2cControl
	//======================================================================
	RW_Func i2cControl::i2cio;
      i2cControl::i2cControl(const unsigned char deviceAddress):deviceAddress(deviceAddress)
	{

	};
	void i2cControl::initDataAddress(int dataAddress) {
	    dataAddressLength = dataAddress > 255 ? 2 : 1;
	    dataAddressByteArray[0] = dataAddress & 255;
	    if (dataAddressLength == 2) {
		dataAddressByteArray[1] = dataAddress >> 8 & 255;
	    }
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
	    initDataAddress(dataAddress);
	    int dataLength = data->getSize();
	    write0(deviceAddress, dataAddressByteArray,
		   dataAddressLength - 1, data->buffer, dataLength);
	};
	void i2cControl::writeByte(int dataAddress, unsigned char data) {
	    initDataAddress(dataAddress);
	    bptr < ByteBuffer > byteBuffer(new ByteBuffer(1));
	    (*byteBuffer)[0] = data;
	    write0(deviceAddress, dataAddressByteArray,
		   dataAddressLength - 1, byteBuffer->buffer, 1);
	};
	bptr < ByteBuffer > i2cControl::read(int dataAddress,
					     int dataLength) {
	    bptr < ByteBuffer > data(new ByteBuffer(dataLength));
	    initDataAddress(dataAddress);
	    read0(deviceAddress, dataAddressByteArray,
		  dataAddressLength - 1, data->buffer, dataLength);
	    return data;
	};
	unsigned char i2cControl::readByte(int dataAddress) {
	 bptr < ByteBuffer > buffer= read(dataAddress, 1);
         return (*buffer)[0];
	};

	bptr < i2cControl >
	    i2cControl::getLPTInstance(const unsigned char deviceAddress) {
	    return bptr < i2cControl > (new i2cLPTControl(deviceAddress));
	};
	bptr < i2cControl >
	    i2cControl::getUSBInstance(const unsigned char deviceAddress,
				       USBPower power, USBSpeed speed) {
	    return bptr < i2cControl >
		(new i2cUSBControl(deviceAddress, power, speed));
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
				     deviceAddress):i2cControl
	    (deviceAddress) {
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
				     USBPower power,
				     USBSpeed
				     speed):i2cControl(deviceAddress),
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

