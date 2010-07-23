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
    //rgb->getValues()
	int r = _toInt(rgb->R);
	int g = _toInt(rgb->G);
	int b = _toInt(rgb->B);
	setTestRGB(r, g, b);
    };
    bptr < ByteBuffer > TCONControl::getRGBByteBuffer(int r, int g, int b,
						      const TestRGBBit &
						      testRGBBit) {
	int rLow = r & 255;
	int rHigh = (r >> 8) & 15;
	int gLow = g & 255;
	int gHigh = (g >> 8) & 15;
	int bLow = b & 255;
	int bHigh = (b >> 8) & 15;

	int totalByte = testRGBBit.totalByte;
	bptr < ByteBuffer > data(new ByteBuffer(totalByte));
	for (int x = 0; x < totalByte; x++) {
	    (*data)[x] = 0;
	}
	//0, 8, 16, 12, 24, 32
	//0,1,2,1,3,4
	(*data)[testRGBBit.rLowBit / 8] = rLow;	//0
	(*data)[testRGBBit.gLowBit / 8] = gLow;	//16
	(*data)[testRGBBit.bLowBit / 8] = bLow;	//24

	if (testRGBBit.rHighBit % 8 != 0) {
	    int index = testRGBBit.rHighBit / 8;
	    byte d = (*data)[index];
	    (*data)[index] = d + (rHigh << 4);
	} else {
	    int index = testRGBBit.rHighBit / 8;
	    byte d = (*data)[index];
	    (*data)[index] = d + rHigh;
	}
	if (testRGBBit.gHighBit % 8 != 0) {
	    int index = testRGBBit.gHighBit / 8;
	    byte d = (*data)[index];
	    (*data)[index] = d + (gHigh << 4);
	} else {
	    int index = testRGBBit.gHighBit / 8;
	    byte d = (*data)[index];
	    (*data)[index] = d + gHigh;
	}
	if (testRGBBit.bHighBit % 8 != 0) {
	    int index = testRGBBit.bHighBit / 8;
	    byte d = (*data)[index];
	    (*data)[index] = d + (bHigh << 4);
	} else {
	    int index = testRGBBit.bHighBit / 8;
	    byte d = (*data)[index];
	    (*data)[index] = d + bHigh;
	}

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
    void TCONControl::setDGLut(RGB_vector_ptr rgbVector) {
	/* TODO : setDGLut */
    };
};

