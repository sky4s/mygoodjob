#ifndef I2CCONTROLH
#define I2CCONTROLH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>

namespace cms {
    namespace i2c {
	class i2cControl {
	  public:
	    void connect();
	    void disconnect();
	};

	class i2cLPTControl:public i2cControl {

	};

	class i2cUSBControl:public i2cControl {

	};
    };
};

#endif

