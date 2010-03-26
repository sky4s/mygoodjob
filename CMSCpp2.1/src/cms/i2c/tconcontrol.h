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
	    bptr < TConParameter > parameter;
	    bptr < i2cControl > control;
	  public:
	    TCONControl(bptr < TConParameter > parameter,
			bptr < i2cControl > control);
	    void setTestRGB(RGB_ptr rgb);
	    void setGammaTest(bool enable);

	};
    };
};

#endif

