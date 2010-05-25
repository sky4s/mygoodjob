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
    bptr < ByteBuffer > TCONControl::getRGBByteBuffer(int r, int g, int b,
						      const TestRGBBit &
						      testRGBBit) {
	/* TODO : getRGBByteBuffer */
	bptr < ByteBuffer > data(new ByteBuffer(testRGBBit.totalByte));
	int rLow = r & 255;
	int rHigh = (r >> 8) & 15;
	int gLow = g & 255;
	int gHigh = (g >> 8) & 15;
	int bLow = b & 255;
	int bHigh = (b >> 8) & 15;

	(*data)[testRGBBit.rLowBit / 8] = rLow;
	(*data)[testRGBBit.gLowBit / 8] = gLow;
	(*data)[testRGBBit.bLowBit / 8] = bLow;

	rHigh;
	gHigh;
	bHigh;

	return data;
    };

    void TCONControl::setTestRGB(int r, int g, int b) {
	const TestRGBBit & testRGBBit = parameter->testRGBBit;
	bptr < ByteBuffer > data = getRGBByteBuffer(r, g, b, testRGBBit);

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

