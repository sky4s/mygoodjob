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
	    int size;
	  public:
	    unsigned char *buffer;
	     ByteBuffer(int size);
	    ~ByteBuffer();
	    inline const int getSize() const {
		return size;
	    };
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
	    virtual void write0(unsigned char dev_addr,
				unsigned char *data_addr,
				int data_addr_cnt,
				unsigned char *data_write, int data_len) =
		0;
	  public:
	     i2cControl(const unsigned char deviceAddress);
	    virtual bool connect() = 0;
	    virtual void disconnect() = 0;
	    void write(int dataAddress, bptr < ByteBuffer > data);
	    /*unsigned char readByte();
	       bptr < ByteBuffer > readByteBuffer(); */
	    static bptr < i2cControl >
		getLPTInstance(const unsigned char deviceAddress);
	    static bptr < i2cControl >
		getUSBInstance(const unsigned char deviceAddress,
			       USBPower power, USBSpeed speed);
	};



	class i2cLPTControl:public i2cControl {
	  protected:
	    void write0(unsigned char dev_addr,
			unsigned char *data_addr,
			int data_addr_cnt,
			unsigned char *data_write, int data_len);
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
	    void write0(unsigned char dev_addr,
			unsigned char *data_addr,
			int data_addr_cnt,
			unsigned char *data_write, int data_len);
	  public:
	     i2cUSBControl(const unsigned char deviceAddress,
			   USBPower power, USBSpeed speed);
	    bool connect();
	    void disconnect();
	};
    };
};

#endif

