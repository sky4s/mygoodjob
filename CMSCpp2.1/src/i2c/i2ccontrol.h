#ifndef I2CCONTROLH
#define I2CCONTROLH
//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>
#include <cms/util/util.h>
#include <i2c/core/ReadWritefunc.h>

namespace i2c {

    class DeviceAddressSendFailException:public java::lang::RuntimeException {
      public:
	DeviceAddressSendFailException();
	DeviceAddressSendFailException(std::string message);
    };

    class DataAddressSendFailException:public java::lang::RuntimeException {
      public:
	DataAddressSendFailException();
	DataAddressSendFailException(std::string message);
    };

    class DataSendFailException:public java::lang::RuntimeException {
      public:
	DataSendFailException();
	DataSendFailException(std::string message);
    };

    enum USBPower {
	External = 0, _5V = 1, _3_3V = 2
    };

    enum USBSpeed {
	_50KHz = 0, _100KHz = 1, _400KHz = 2
    };

    enum AddressingSize {
	_2k, _4k, _8k, _16k, _32k, _64k, _128k, _256k, _512k
    };


    enum LPTCard {
	Small, Large
    };

    class i2cControl {
      private:
	const unsigned char deviceAddress;
	const int dataAddressLength;
	const AddressingSize size;
	static int getDataAddressLength(const AddressingSize size);
	const unsigned char getRealDeviceAddress();
	unsigned char dataAddressByteArray[2];
      protected:
	static RW_Func i2cio;

	unsigned char *getDataAddressByteArray(int dataAddress);
	virtual void write0(unsigned char dev_addr,
			    unsigned char *data_addr,
			    int data_addr_cnt, unsigned char *data_write, int data_len) = 0;
	virtual void read0(unsigned char dev_addr,
			   unsigned char *data_addr, int data_addr_cnt,
			   unsigned char *data_read, int data_cnt) = 0;


      public:
        const int dataByteNum;     //20140619 byBS+
	 i2cControl(const unsigned char deviceAddress, const AddressingSize size, const int dataByteNum);
	virtual bool connect() = 0;
	virtual void disconnect() = 0;
	void write(int dataAddress, bptr < cms::util::ByteBuffer > data);
	void writeByte(int dataAddress, unsigned char data);
	 bptr < cms::util::ByteBuffer > read(int dataAddress, int dataLength);
	unsigned char readByte(int dataAddress);
	static bptr < i2cControl >
	    getLPTInstance(const unsigned char deviceAddress, 
			   const AddressingSize size, const LPTCard card);

	static bptr < i2cControl >
	    getUSBInstance(const unsigned char deviceAddress,
			   const AddressingSize size, const int dataByteNum,
                           USBPower power, USBSpeed speed);

	static bptr < i2cControl >
	    getDoDoBirdInstance(const unsigned char deviceAddress,
			        const AddressingSize size, const int dataByteNum);
    };


    class i2cLPTControl:public i2cControl {
      protected:
	virtual void write0(unsigned char dev_addr,
			    unsigned char *data_addr,
			    int data_addr_cnt, unsigned char *data_write, int data_len);
	virtual void read0(unsigned char dev_addr,
			   unsigned char *data_addr, int data_addr_cnt,
			   unsigned char *data_read, int data_cnt);
      public:
	 bool connect();
	void disconnect();
	 i2cLPTControl(const unsigned char deviceAddress,
		       const AddressingSize size, const LPTCard card);
    };

    class i2cUSBControl:public i2cControl {
      private:
	USBPower power;
	USBSpeed speed;
      protected:
	 virtual void write0(unsigned char dev_addr,
			     unsigned char *data_addr,
			     int data_addr_cnt, unsigned char *data_write, int data_len);
	virtual void read0(unsigned char dev_addr,
			   unsigned char *data_addr,
			   int data_addr_cnt, unsigned char *data_read, int data_cnt);
      public:
	 i2cUSBControl(const unsigned char deviceAddress,
		       const AddressingSize size, const int dataByteNum, USBPower power, USBSpeed speed);
	bool connect();
	void disconnect();
	~i2cUSBControl();
    };

    class i2cDoDoBirdControl:public i2cControl {    //20140604 byBS+
      private:
      protected:
	 virtual void write0(unsigned char dev_addr,
			     unsigned char *data_addr,
			     int data_addr_cnt, unsigned char *data_write, int data_len);
         virtual void read0(unsigned char dev_addr,
			   unsigned char *data_addr,
			   int data_addr_cnt, unsigned char *data_read, int data_cnt);
      public:
         i2cDoDoBirdControl(const unsigned char deviceAddress, const AddressingSize size, const int dataByteNum);
	 bool connect();
	 void disconnect();
	 ~i2cDoDoBirdControl();
    };
};

#endif

