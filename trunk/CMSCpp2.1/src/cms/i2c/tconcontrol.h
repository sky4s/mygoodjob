#ifndef TCONCONTROLH
#define TCONCONTROLH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
//nclude <cms/colorformat/excelfile.h>

namespace cms {
    namespace i2c {
	class TCONControl {
	  private:
	    bptr < TCONParameter > parameter;
	    bptr < i2cControl > control;
	    bptr < i2cControl > control2;
	    const bool dualTCON;

	  public:
	     TCONControl(bptr < TCONParameter > parameter,
			 bptr < i2cControl > control);
	     TCONControl(bptr < TCONParameter > parameter,
			 bptr < i2cControl > control1,
			 bptr < i2cControl > control2);
	    void setTestRGB(RGB_ptr rgb);
	    void setGammaTest(bool enable);
	    unsigned char readByte(int dataAddress);
	    void writeByte(int dataAddress, unsigned char data);
	};
    };
};

#endif

