#ifndef TCONPARAMETERH
#define TCONPARAMETERH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
//nclude <cms/colorformat/excelfile.h>

namespace cms {
    namespace i2c {
	class TConParameter {
	  private:
	    const int gammaTestAddress;
	    const int testRGBAddress;
	    const bool independentRGB;
	    const unsigned char gammaTestBit;
	  public:
	     TConParameter(int gammaTestAddress,
			   unsigned char gammaTestBit, int testRGBAddress,
			   bool independentRGB);
	    int getGammaTestAddress();
	    int getTestRGBAddress();
	    bool isIndependentRGB();
	    unsigned char getGammaTestBit();
	};
    };
};

#endif

