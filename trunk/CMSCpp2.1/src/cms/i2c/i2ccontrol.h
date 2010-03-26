#ifndef I2CCONTROLH
#define I2CCONTROLH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include <cms/i2c/core/ReadWritefunc.h>

namespace cms {
    namespace i2c {

	class ByteBuffer {
	  private:
	    const unsigned int size;
	  public:
	    unsigned char *buffer;
	     ByteBuffer(const unsigned int size);
	    ~ByteBuffer();
	    inline const int getSize() const {
		return size;
	    };
	    unsigned char &operator[] (const size_t index);
	    const unsigned char &operator[] (const size_t index) const;
	};


	class DeviceAddressSendFailException:public java::lang::
	    RuntimeException {
	  public:
	    DeviceAddressSendFailException();
	    DeviceAddressSendFailException(std::string message);
	};

	class DataAddressSendFailException:public java::lang::
	    RuntimeException {
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
	    External = 1, _5V = 2, _3_3V = 3
	};

	enum USBSpeed {
	    _50KHz = 1, _100KHz = 2, _400KHz = 3
	};

	class i2cControl {
	  private:
	    const unsigned char deviceAddress;
	  protected:
	    static RW_Func i2cio;
	    unsigned char dataAddressByteArray[2];
	    int dataAddressLength;
	    void initDataAddress(int dataAddress);
	    virtual void write0(unsigned char dev_addr,
				unsigned char *data_addr,
				int data_addr_cnt,
				unsigned char *data_write, int data_len) =
		0;
	    virtual void read0(unsigned char dev_addr,
			       unsigned char *data_addr, int data_addr_cnt,
			       unsigned char *data_read, int data_cnt) = 0;


	  public:
	     i2cControl(const unsigned char deviceAddress);
	    virtual bool connect() = 0;
	    virtual void disconnect() = 0;
	    void write(int dataAddress, bptr < ByteBuffer > data);
	    void writeByte(int dataAddress, unsigned char data);
	     bptr < ByteBuffer > read(int dataAddress, int dataLength);
	    unsigned char readByte(int dataAddress);
	    static bptr < i2cControl >
		getLPTInstance(const unsigned char deviceAddress);
	    static bptr < i2cControl >
		getUSBInstance(const unsigned char deviceAddress,
			       USBPower power, USBSpeed speed);
	};



	class i2cLPTControl:public i2cControl {
	  protected:
	    virtual void write0(unsigned char dev_addr,
				unsigned char *data_addr,
				int data_addr_cnt,
				unsigned char *data_write, int data_len);
	    virtual void read0(unsigned char dev_addr,
			       unsigned char *data_addr, int data_addr_cnt,
			       unsigned char *data_read, int data_cnt);
	  public:
	     bool connect();
	    void disconnect();
	     i2cLPTControl(const unsigned char deviceAddress);
	};

	class i2cUSBControl:public i2cControl {
	  private:
	    USBPower power;
	    USBSpeed speed;
	  protected:
	     virtual void write0(unsigned char dev_addr,
				 unsigned char *data_addr,
				 int data_addr_cnt,
				 unsigned char *data_write, int data_len);
	    virtual void read0(unsigned char dev_addr,
			       unsigned char *data_addr, int data_addr_cnt,
			       unsigned char *data_read, int data_cnt);
	  public:
	     i2cUSBControl(const unsigned char deviceAddress,
			   USBPower power, USBSpeed speed);
	    bool connect();
	    void disconnect();
	    ~i2cUSBControl();
	};
    };
};

#endif

