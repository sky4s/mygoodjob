#include "tconparameter.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace i2c {
	TCONParameter::TCONParameter(int gammaTestAddress,
				     unsigned char gammaTestBit,
				     int testRGBAddress,
				     bool independentRGB):gammaTestAddress
	    (gammaTestAddress), gammaTestBit(gammaTestBit),
	    testRGBAddress(testRGBAddress),
	    independentRGB(independentRGB) {

	};
	int TCONParameter::getGammaTestAddress() {
	    return gammaTestAddress;
	};
	int TCONParameter::getTestRGBAddress() {
	    return testRGBAddress;
	};
	bool TCONParameter::isIndependentRGB() {
	    return independentRGB;
	};
	unsigned char TCONParameter::getGammaTestBit() {
	    return gammaTestBit;
	};
    };
};

