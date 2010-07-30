#include <includeall.h>
#pragma hdrstop
#include "tconcontrol.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace i2c {
    using namespace cms::util;
    using namespace Dep;
     TCONControl::TCONControl(bptr < TCONParameter >
			      parameter,
			      bptr < i2cControl >
			      control):parameter(parameter), control(control), dualTCON(false) {

    };
  TCONControl::TCONControl(bptr < TCONParameter > parameter, bptr < i2cControl > control1, bptr < i2cControl > control2):parameter(parameter),
	control(control1), control2(control2),
	dualTCON(true) {

    };
    void TCONControl::setGammaTestRGB(RGB_ptr rgb) {
	//rgb->getValues()
	int r = _toInt(rgb->R);
	int g = _toInt(rgb->G);
	int b = _toInt(rgb->B);
	setGammaTestRGB(r, g, b);
    };
    bptr < ByteBuffer > TCONControl::getRGBByteBuffer(int r, int g, int b,
						      const TestRGBBit & testRGBBit) {
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

    void TCONControl::setGammaTestRGB(int r, int g, int b) {
	const TestRGBBit & testRGBBit = parameter->testRGBBit;
	bptr < ByteBuffer > data = getRGBByteBuffer(r, g, b, testRGBBit);

	int address = parameter->testRGBAddress;
	write(address, data);
    };
    void TCONControl::setGammaTest(bool enable) {
	setBitData(parameter->gammaTestAddress, parameter->gammaTestBit, enable);
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
    bool TCONControl::isGammaTestEnable() {
	return parameter->isGammaTestEnable();
    };

    void TCONControl::write(int dataAddress, bptr < ByteBuffer > data) {
	control->write(dataAddress, data);
	if (true == dualTCON) {
	    control2->write(dataAddress, data);
	}
    }
    const MaxValue & TCONControl::getLUTBit() {
	return parameter->lutBit;
    };

    bptr < ByteBuffer > TCONControl::getDGLut10BitByteBuffer(RGB_vector_ptr rgbVector) {
	/* TODO : getDGLut10BitByteBuffer */
    };
    bptr < ByteBuffer > TCONControl::getDGLut12BitByteBuffer(RGB_vector_ptr rgbVector) {
	int size = rgbVector->size();
	int halfSize = size / 2;
	int remainder = size % 2;
	int singleChannelDataSize = halfSize * 3 + remainder ? 2 : 0;
	int totalDataSize = singleChannelDataSize * 3;
	bptr < ByteBuffer > data(new ByteBuffer(totalDataSize));
	int index = 0;

	foreach(const Channel & ch, *Channel::RGBChannel) {
	    for (int x = 0; x < halfSize; x++) {
		int d0 = static_cast < int >((*rgbVector)[x]->getValue(ch));
		int d1 = static_cast < int >((*rgbVector)[x + 1]->getValue(ch));
		int_array d0lmh = getLMHData(d0);
		int_array d1lmh = getLMHData(d1);
		(*data)[index++] = d0lmh[0] + (d0lmh[1] << 4);
		(*data)[index++] = d0lmh[2] + (d1lmh[1] << 4);
		(*data)[index++] = d1lmh[1] + (d1lmh[2] << 4);
	    }
	}
	return data;
    };
    void TCONControl::setDGLut(RGB_vector_ptr rgbVector) {
	const MaxValue & lutBit = getLUTBit();
	bptr < ByteBuffer > data;

	if (lutBit == MaxValue::Int12Bit) {
	    data = getDGLut12BitByteBuffer(rgbVector);
	} else if (lutBit == MaxValue::Int10Bit) {
	    data = getDGLut10BitByteBuffer(rgbVector);
	}
	write(parameter->DGLutAddress, data);
    }

    int_array TCONControl::getLMHData(int data) {
	int_array result(new int[3]);
	result[0] = data & 15;
	result[1] = data >> 4 & 15;
	result[2] = data >> 8 & 15;
	return result;
    }

    void TCONControl::setDG(bool enable) {
	setBitData(parameter->DGAddress, parameter->DGBit, enable);
    };
    void TCONControl::setBitData(int dataAddress, unsigned char bit, bool data) {
	unsigned char bytedata = readByte(dataAddress);
	//製作遮罩
	unsigned char mask = ~(1 << bit);
	//挖掉要填的那個位元
	bytedata = bytedata & mask;
	//產生要填的data
	bytedata = bytedata | data << bit;
	writeByte(dataAddress, bytedata);
    };
};

