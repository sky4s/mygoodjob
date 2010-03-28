#include <includeall.h>
#pragma hdrstop
#include "tconcontrol.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace i2c {
	TCONControl::TCONControl(bptr < TCONParameter >
				 parameter,
				 bptr < i2cControl >
				 control):parameter(parameter),
	    control(control), dualTCON(false) {

	};
	 TCONControl::TCONControl(bptr < TCONParameter > parameter,
				  bptr < i2cControl > control1,
				  bptr < i2cControl >
				  control2):parameter(parameter),
	    control(control1), control2(control2), dualTCON(true) {

	};
	void TCONControl::setTestRGB(RGB_ptr rgb) {
	    int address = parameter->getTestRGBAddress();
	    double_array rgbValues(new double[3]);
	    rgb->getValues(rgbValues, Dep::MaxValue::Int12Bit);
	    int r = _toInt(rgbValues[0]);
	    int g = _toInt(rgbValues[1]);
	    int b = _toInt(rgbValues[2]);
	    bptr < ByteBuffer > data;

	    if (parameter->isIndependentRGB()) {
		//如果test RGB各自獨立
		//BBLL 00BH GGLL 00GH RRLL 00RH
		data.reset(new ByteBuffer(6));
		(*data)[0] = r >> 8;
		(*data)[1] = r & 255;
		(*data)[2] = g >> 8;
		(*data)[3] = g & 255;
		(*data)[4] = b >> 8;
		(*data)[5] = b & 255;

	    } else {
		//如果test RGB沒有獨立
		//00BH BBLL GGLL GHRH RRLL
		data.reset(new ByteBuffer(5));
		(*data)[0] = r & 255;
		(*data)[1] = r >> 8 + g >> 8 & 15 << 4;
		(*data)[2] = g & 255;
		(*data)[3] = b & 255;
		(*data)[4] = g >> 8 & 15;
	    }
	    control->write(address, data);
	    if (true == dualTCON) {
		control2->write(address, data);
	    }
	};
	void TCONControl::setGammaTest(bool enable) {
	    int address = parameter->getGammaTestAddress();
	    unsigned char bit = parameter->getGammaTestBit();
	    unsigned char data = enable << (bit - 1);
	    control->writeByte(address, data);
	    if (true == dualTCON) {
		control2->writeByte(address, data);
	    }
	};
    };
};

