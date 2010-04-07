#include <includeall.h>
#pragma hdrstop
#include "tconcontrol.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace i2c {
    using namespace cms::util;
     TCONControl::TCONControl(bptr < TCONParameter >
			      parameter,
			      bptr < i2cControl >
			      control):parameter(parameter),
	control(control), dualTCON(false) {

    };
  TCONControl::TCONControl(bptr < TCONParameter > parameter, bptr < i2cControl > control1, bptr < i2cControl > control2):parameter(parameter),
	control(control1), control2(control2),
	dualTCON(true) {

    };
    void TCONControl::setTestRGB(RGB_ptr rgb) {
	int r = _toInt(rgb->R);
	int g = _toInt(rgb->G);
	int b = _toInt(rgb->B);
	setTestRGB(r, g, b);
    };
    void TCONControl::setTestRGB(int r, int g, int b) {
	bptr < ByteBuffer > data;

	if (parameter->independentRGB) {
	    //如果test RGB各自獨立
	    //BBLL 00BH GGLL 00GH RRLL 00RH
            // 8 0 24 16 40 32
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
            // 0 8 16 12 24 32
	    data.reset(new ByteBuffer(5));
	    (*data)[0] = r & 255;
	    (*data)[1] = r >> 8 + g >> 8 & 15 << 4;
	    (*data)[2] = g & 255;
	    (*data)[3] = b & 255;
	    (*data)[4] = g >> 8 & 15;
	}
	int address = parameter->testRGBAddress;
	control->write(address, data);
	if (true == dualTCON) {
	    control2->write(address, data);
	}
    };
    void TCONControl::setGammaTest(bool enable) {
	int address = parameter->gammaTestAddress;
	unsigned char bit = parameter->gammaTestBit;
	unsigned char data = enable << (bit - 1);
	control->writeByte(address, data);
	if (true == dualTCON) {
	    control2->writeByte(address, data);
	}
    };

    unsigned char TCONControl::readByte(int dataAddress) {
	return control->readByte(dataAddress);
    };
    void TCONControl::writeByte(int dataAddress, unsigned char data) {
	control->writeByte(dataAddress, data);
	if (true == dualTCON) {
	    control2->writeByte(dataAddress, data);
	}
    };
    const Dep::MaxValue & TCONControl::getLUTBit() {
	return parameter->lutBit;
    };
};

