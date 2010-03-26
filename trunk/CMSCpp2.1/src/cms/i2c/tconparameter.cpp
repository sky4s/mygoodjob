#include "tconparameter.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace i2c {
	TConParameter::TConParameter(int gammaTestAddress,
				     unsigned char gammaTestBit,
				     int testRGBAddress,
				     bool
				     independentRGB):gammaTestAddress
	    (gammaTestAddress), gammaTestBit(gammaTestBit),
	    testRGBAddress(testRGBAddress),
	    independentRGB(independentRGB) {

	};
	int TConParameter::getGammaTestAddress() {
	    return gammaTestAddress;
	};
	int TConParameter::getTestRGBAddress() {
	    return testRGBAddress;
	};
	bool TConParameter::isIndependentRGB() {
	    return independentRGB;
	};
	unsigned char TConParameter::getGammaTestBit() {
	    return gammaTestBit;
	};

    };
};

