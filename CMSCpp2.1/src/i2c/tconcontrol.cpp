#include <includeall.h>
#pragma hdrstop
#include "tconcontrol.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace i2c {
    using namespace cms::util;
    using namespace java::lang;
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
    bool TCONControl::setDirectGammaRGB(RGB_ptr rgb) {
	//rgb->getValues()
	int r = _toInt(rgb->R);
	int g = _toInt(rgb->G);
	int b = _toInt(rgb->B);
	return setDirectGammaRGB(r, g, b);
    };
    bptr < cms::util::ByteBuffer > TCONControl::getRGBByteBufferWith62301(int r, int g, int b,
									  const DirectGammaType &
									  directGammaType) {
	int highMask = 3;
	int rLow = r & 255;
	int rHigh = (r >> 8) & highMask;
	int gLow = g & 255;
	int gHigh = (g >> 8) & highMask;
	int bLow = b & 255;
	int bHigh = (b >> 8) & highMask;

	int totalByte = directGammaType.totalByte;
	bptr < ByteBuffer > data(new ByteBuffer(totalByte));
	//先清空buffer
	for (int x = 0; x < totalByte; x++) {
	    (*data)[x] = 0;
	}
	(*data)[0] = 64 | rHigh << 4 | gHigh << 2 | bHigh;

	(*data)[directGammaType.rLowBit / 8] = rLow;	//0
	(*data)[directGammaType.gLowBit / 8] = gLow;	//16
	(*data)[directGammaType.bLowBit / 8] = bLow;	//24

	return data;
    };
    bptr < ByteBuffer > TCONControl::getRGBByteBuffer(int r, int g, int b,
						      const DirectGammaType & directGammaType) {
 	if (DirectGammaType::TCON62301Instance == directGammaType) {
	    return getRGBByteBufferWith62301(r, g, b, directGammaType);
	}

	int patternBit = directGammaType.patternBit;
	int highMask = (12 == patternBit) ? 15 : 3;
	// C B A 9 8 7 6 5 4 3 2 1
	// ^^^^^^^H^^^^^^^^^^^^^^^L
	int rLow = r & 255;
	int rHigh = (r >> 8) & highMask;
	int gLow = g & 255;
	int gHigh = (g >> 8) & highMask;
	int bLow = b & 255;
	int bHigh = (b >> 8) & highMask;

	int totalByte = directGammaType.totalByte;
	bptr < ByteBuffer > data(new ByteBuffer(totalByte));
	//先清空buffer
	for (int x = 0; x < totalByte; x++) {
	    (*data)[x] = 0;
	}
	//0, 8, 16, 12, 24, 32
	//0,1,2,1,3,4
	(*data)[directGammaType.rLowBit / 8] = rLow;	//0
	(*data)[directGammaType.gLowBit / 8] = gLow;	//16
	(*data)[directGammaType.bLowBit / 8] = bLow;	//24

	if (directGammaType.rHighBit % 8 != 0) {
	    int index = directGammaType.rHighBit / 8;
	    byte d = (*data)[index];
	    (*data)[index] = d + (rHigh << 4);
	} else {
	    int index = directGammaType.rHighBit / 8;
	    byte d = (*data)[index];
	    (*data)[index] = d + rHigh;
	}
	if (directGammaType.gHighBit % 8 != 0) {
	    int index = directGammaType.gHighBit / 8;
	    byte d = (*data)[index];
	    (*data)[index] = d + (gHigh << 4);
	} else {
	    int index = directGammaType.gHighBit / 8;
	    byte d = (*data)[index];
	    (*data)[index] = d + gHigh;
	}
	if (directGammaType.bHighBit % 8 != 0) {
	    int index = directGammaType.bHighBit / 8;
	    byte d = (*data)[index];
	    (*data)[index] = d + (bHigh << 4);
	} else {
	    int index = directGammaType.bHighBit / 8;
	    byte d = (*data)[index];
	    (*data)[index] = d + bHigh;
	}

	return data;
    };

    bool TCONControl::setDirectGammaRGB(int r, int g, int b) {
	const DirectGammaType & directGammaType = parameter->directGammaType;
	bptr < ByteBuffer > data = getRGBByteBuffer(r, g, b, directGammaType);

	int address = parameter->directGammaRGBAddress;
	write(address, data);
	int size = data->getSize();
	bptr < ByteBuffer > dataFrom0 = read(address, size, 0);
	if (!dualTCON) {
	    //1 tcon
	    return data->equals(dataFrom0);
	} else {
	    //2 tcon
	    bptr < ByteBuffer > dataFrom1 = read(address, size, 1);
	    return data->equals(dataFrom0) && data->equals(dataFrom1);
	}
    };

    void TCONControl::setGammaTest(bool enable) {
	if (enable && parameter->isHideEnable()) {
	    setBitData(parameter->hideENAddress, parameter->hideENBit, enable);
	}
	setBitData(parameter->gammaTestAddress, parameter->gammaTestBit, enable);
	if (!enable && parameter->isHideEnable()) {
	    setBitData(parameter->hideENAddress, parameter->hideENBit, enable);
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
    bool TCONControl::isGammaTestEnable() {
	return parameter->isGammaTestEnable();
    };

    void TCONControl::write(int dataAddress, bptr < ByteBuffer > data) {
	control->write(dataAddress, data);
	if (true == dualTCON) {
	    control2->write(dataAddress, data);
	}
    }

    bptr < ByteBuffer > TCONControl::read(int dataAddress, int size) {
	return read(dataAddress, size, 0);
    }
    bptr < ByteBuffer > TCONControl::read(int dataAddress, int size, int tconIndex) {
	if (0 == tconIndex) {
	    return control->read(dataAddress, size);
	} else if (1 == tconIndex && true == dualTCON) {
	    return control2->read(dataAddress, size);
	} else {
	    throw new IllegalArgumentException("");
	}
    }
    const MaxValue & TCONControl::getLUTBit() {
	return parameter->lutBit;
    }

    bptr < ByteBuffer > TCONControl::getDGLut10BitByteBuffer(RGB_vector_ptr rgbVector) {
	//if (true) {
	return getDGLut10BitByteBufferType2(rgbVector);
	/*}
	   int processSize = 256;
	   int quarterSize = processSize / 4;
	   int singleChannelDataSize = quarterSize * 5;
	   int totalDataSize = singleChannelDataSize * 3;
	   bptr < ByteBuffer > data(new ByteBuffer(totalDataSize));
	   int index = 0;

	   foreach(const Channel & ch, *Channel::RGBChannel) {
	   for (int x = 0; x < quarterSize; x++) {
	   int d0 = static_cast < int >((*rgbVector)[x * 4]->getValue(ch, MaxValue::Int10Bit));
	   int d1 =
	   static_cast < int >((*rgbVector)[x * 4 + 1]->getValue(ch, MaxValue::Int10Bit));
	   int d2 =
	   static_cast < int >((*rgbVector)[x * 4 + 2]->getValue(ch, MaxValue::Int10Bit));
	   int d3 =
	   static_cast < int >((*rgbVector)[x * 4 + 3]->getValue(ch, MaxValue::Int10Bit));

	   int b0 = d0 >> 2;
	   int b1 = ((d0 & 3) << 8) + d1 >> 4;
	   int b2 = (*data)[index++] = ((d1 & 15) << 4) + d2 >> 6;
	   int b3 = (*data)[index++] = ((d2 & 63) << 2) + d3 >> 8;
	   int b4 = (*data)[index++] = d3 & 255;

	   (*data)[index++] = d0 >> 2;
	   (*data)[index++] = ((d0 & 3) << 8) + d1 >> 4;
	   (*data)[index++] = ((d1 & 15) << 4) + d2 >> 6;
	   (*data)[index++] = ((d2 & 63) << 2) + d3 >> 8;
	   (*data)[index++] = d3 & 255;
	   }} return data; */
    };

    bptr < ByteBuffer > TCONControl::getDGLut10BitByteBufferType2(RGB_vector_ptr rgbVector) {
	//int size = rgbVector->size();
	int processSize = 256;
	int quarterSize = processSize / 4;
	int singleChannelDataSize = quarterSize * 5;
	int totalDataSize = singleChannelDataSize * 3;
	bptr < ByteBuffer > data(new ByteBuffer(totalDataSize));
	int index = 0;

	foreach(const Channel & ch, *Channel::RGBChannel) {
	    for (int x = 0; x < quarterSize; x++) {
		int d0 = static_cast < int >((*rgbVector)[x * 4]->getValue(ch, MaxValue::Int10Bit));
		int d1 =
		    static_cast < int >((*rgbVector)[x * 4 + 1]->getValue(ch, MaxValue::Int10Bit));
		int d2 =
		    static_cast < int >((*rgbVector)[x * 4 + 2]->getValue(ch, MaxValue::Int10Bit));
		int d3 =
		    static_cast < int >((*rgbVector)[x * 4 + 3]->getValue(ch, MaxValue::Int10Bit));

		(*data)[index++] = d0 >> 2;
		(*data)[index++] = ((d0 & 3) << 8) + (d1 >> 4);
		(*data)[index++] = ((d1 & 15) << 4) + (d2 >> 6);
		(*data)[index++] = ((d2 & 63) << 2) + (d3 >> 8);
		(*data)[index++] = d3 & 255;
	}} return data;
    };

    bptr < ByteBuffer > TCONControl::getDGLut12BitByteBuffer(RGB_vector_ptr rgbVector) {
	int size = rgbVector->size();
	if (257 != size) {
	    if (size == 256) {
		rgbVector->push_back((*rgbVector)[size - 1]);
		size = rgbVector->size();
	    } else {
		throw IllegalArgumentException("rgbVector->size() != 257");
	    }
	}
	int halfSize = size / 2;
	int remainder = size % 2;
	int singleChannelDataSize = halfSize * 3 + (remainder ? 2 : 0);
	int totalDataSize = singleChannelDataSize * 3;
	bptr < ByteBuffer > data(new ByteBuffer(totalDataSize));
	int index = 0;

	foreach(const Channel & ch, *Channel::RGBChannel) {
	    for (int x = 0; x < halfSize; x++) {
		int d0 = static_cast < int >((*rgbVector)[x * 2]->getValue(ch, MaxValue::Int12Bit));
		int d1 =
		    static_cast < int >((*rgbVector)[x * 2 + 1]->getValue(ch, MaxValue::Int12Bit));
		int_array d0lmh = getLMHData(d0);
		int_array d1lmh = getLMHData(d1);

		int c0 = d0lmh[0] + (d0lmh[1] << 4);
		int c1 = d0lmh[2] + (d1lmh[0] << 4);
		int c2 = d1lmh[1] + (d1lmh[2] << 4);
		(*data)[index++] = c0;
		(*data)[index++] = c1;
		(*data)[index++] = c2;
	    } if (remainder) {
		int d0 =
		    static_cast <
		    int >((*rgbVector)[rgbVector->size() - 1]->getValue(ch, MaxValue::Int12Bit));
		int_array dlmh = getLMHData(d0);
		int c0 = dlmh[0] + (dlmh[1] << 4);
		int c1 = dlmh[2];
		(*data)[index++] = c0;
		(*data)[index++] = c1;
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
    RGB_vector_ptr TCONControl::getDGLut() {
	throw new UnsupportedOperationException("");
    };

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
    bool TCONControl::isDG() {
	return getBitData(parameter->DGAddress, parameter->DGBit);
    };
    void TCONControl::setFRC(bool enable) {
	setBitData(parameter->FRCAddress, parameter->FRCBit, enable);
    };
    bool TCONControl::isFRC() {
	return getBitData(parameter->FRCAddress, parameter->FRCBit);
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

    bool TCONControl::getBitData(int dataAddress, unsigned char bit) {
	unsigned char bytedata = readByte(dataAddress);
	bytedata = bytedata >> bit;
	bytedata = bytedata & 1;
	return (1 == bytedata);
    };
};

