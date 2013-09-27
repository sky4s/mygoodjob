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
    bptr < cms::util::ByteBuffer > TCONControl::getRGBByteBufferWith12409(int r, int g, int b,
								          const DirectGammaType
								          & directGammaType) {
        //12409   |RH |RLGH |GL|BH |BL|
        //         8    4,4  8   8  4
	int rLow = r & 15;
	int rHigh = (r >> 4) & 255;
	int gLow = g & 255;
	int gHigh = (g >> 8) & 15;
	int bLow = b & 15;
	int bHigh = (b >> 4) & 255;

	int totalByte = directGammaType.totalByte;
	bptr < ByteBuffer > data(new ByteBuffer(totalByte));
	//先清空buffer
	for (int x = 0; x < totalByte; x++) {
	    (*data)[x] = 0;
	}

	(*data)[0] = rHigh; //RH
	(*data)[1] = rLow << 4 | gHigh;
	(*data)[2] = gLow ;
	(*data)[3] = bHigh;
        (*data)[4] = bLow << 4;

	return data;

    };
    bptr < cms::util::ByteBuffer > TCONControl::getRGBByteBufferWith12409Aging(int r, int g, int b,
									       const DirectGammaType
									       & directGammaType) {
        //12409 Aging |RHRL1|RL2GHGL1|GL2BHBL1|BL2
        //              2,6   2,2,4    4,2,2    6
	int rLow = r & 3;
	int rHigh = (r >> 2) & 255;
	int gLow = g & 15;
	int gHigh = (g >> 4) & 63;
	int bLow = b & 63;
	int bHigh = (b >> 6) & 15;

	int totalByte = directGammaType.totalByte;
	bptr < ByteBuffer > data(new ByteBuffer(totalByte));
	//先清空buffer
	for (int x = 0; x < totalByte; x++) {
	    (*data)[x] = 0;
	}
	// rHigh
	// rLow(2)|gHigh(6)
	// gLow(4)|bHigh(4)
	// bLow(6)|(2)
	(*data)[0] = rHigh; //RH+RL1
	(*data)[1] = rLow << 6 | gHigh; //RL2 GH GL1
	(*data)[2] = gLow << 4 | bHigh;
	(*data)[3] = bLow << 2;

	return data;
    };
    bptr < cms::util::ByteBuffer > TCONControl::getRGBByteBufferWith11311(int r, int g, int b,
									       const DirectGammaType
									       & directGammaType) {
        //11311  |RH|RL|GH|GL|BH|BL|
        //        8  2  8  2  8  2
	int rLow = (r & 3) << 6;
	int rHigh = r >> 2;
	int gLow = (g & 3) << 6;
	int gHigh = g >> 2;
	int bLow = (b & 3) << 6;
	int bHigh = b >> 2;

        int totalByte = directGammaType.totalByte;

        //當Direct gamma 的Address中出現其他register時，需要做的處理。
        //但parameter在這不能直接使用，改在setDirectGammaRGB判斷?
        /*int EnableAddress = parameter->gammaTestAddress;
        int RGBAddress = parameter->directGammaRGBAddress;
        if(EnableAddress >= RGBAddress && EnableAddress < RGBAddress+totalByte)
        {
            unsigned char bytedata = readByte(EnableAddress);
            rLow = rLow | bytedata;  //For AUO11311
        }*/

	bptr < ByteBuffer > data(new ByteBuffer(totalByte));
	//先清空buffer
	for (int x = 0; x < totalByte; x++) {
	    (*data)[x] = 0;
	}

	(*data)[0] = rHigh;
	(*data)[1] = rLow;
	(*data)[2] = gHigh;
	(*data)[3] = gLow;
        (*data)[4] = bHigh;
        (*data)[5] = bLow;

	return data;

    };

    bptr < ByteBuffer > TCONControl::getRGBByteBuffer(int r, int g, int b,
						      const DirectGammaType & directGammaType) {
	if (DirectGammaType::TCON62301Instance == directGammaType) {
	    return getRGBByteBufferWith62301(r, g, b, directGammaType);
	} else if (DirectGammaType::TCON12409AgingInstance == directGammaType) {
	    return getRGBByteBufferWith12409Aging(r, g, b, directGammaType);
	} else if (DirectGammaType::TCON12409Instance == directGammaType) {
	    return getRGBByteBufferWith12409(r, g, b, directGammaType);
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
	//0, 1, 2,  1,  3,  4
	(*data)[directGammaType.rLowBit / 8] = rLow;	//0
	(*data)[directGammaType.gLowBit / 8] = gLow;	//16
	(*data)[directGammaType.bLowBit / 8] = bLow;	//24

	//Red
	if (directGammaType.rHighBit % 8 != 0) {
	    int index = directGammaType.rHighBit / 8;
	    byte d = (*data)[index];
	    (*data)[index] = d + (rHigh << 4);
	} else {
	    int index = directGammaType.rHighBit / 8;
	    byte d = (*data)[index];
	    (*data)[index] = d + rHigh;
	}

	//Green
	if (directGammaType.gHighBit % 8 != 0) {
	    int index = directGammaType.gHighBit / 8;
	    byte d = (*data)[index];
	    (*data)[index] = d + (gHigh << 4);
	} else {
	    int index = directGammaType.gHighBit / 8;
	    byte d = (*data)[index];
	    (*data)[index] = d + gHigh;
	}
	//Blue
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

        //當Direct gamma 的Address中出現其他register時，需要做的處理。
        int EnableAddress = parameter->gammaTestAddress;
        int RGBAddress = parameter->directGammaRGBAddress;
        int totalByte = directGammaType.totalByte;
        if(EnableAddress >= RGBAddress && EnableAddress < RGBAddress+totalByte)
        {
            //unsigned char bytedata = readByte(EnableAddress);
            //rLow = rLow | bytedata;  //For AUO11311
            ShowMessage("Waring : Direct gamma Enable address conflict");
            return 0;
        }

	write(RGBAddress, data);
	int size = data->getSize();
	bptr < ByteBuffer > dataFrom0 = read(RGBAddress, size, 0);
	if (!dualTCON) {
	    //1 tcon
	    return data->equals(dataFrom0);
	} else {
	    //2 tcon
	    bptr < ByteBuffer > dataFrom1 = read(RGBAddress, size, 1);
	    return data->equals(dataFrom0) && data->equals(dataFrom1);
	}
    };

    bool TCONControl::setAgingModeRGB(int r, int g, int b) {
	const DirectGammaType & agingModeType = parameter->agingModeType;
	bptr < ByteBuffer > data = getRGBByteBuffer(r, g, b, agingModeType);

	int address = parameter->agingRasterGrayAddress;
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
	    setSingleBitData(parameter->hideENAddress, parameter->hideENBit, enable);
	}
	setSingleBitData(parameter->gammaTestAddress, parameter->gammaTestBit, enable);
	if (!enable && parameter->isHideEnable()) {
	    setSingleBitData(parameter->hideENAddress, parameter->hideENBit, enable);
	}
    };

    void TCONControl::setTconAgingMode(bool enable) {
        //1. AG_PTN_SEL
        //2. AG_MODE_SEL
        //3. AGBS_DEBUG
        setBitData(parameter->agingPatternSelectAddress, parameter->agingPatternSelectStartBit,
                   parameter->agingPatternSelectEndBit, parameter->agingPatternSelectValue);
        setSingleBitData(parameter->agingModeSelectAddress, parameter->agingModeSelectBit, enable);
        setSingleBitData(parameter->agingAGBSDebugAddress, parameter->agingAGBSDebugBit, enable);
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
    bool TCONControl::isAgingModeEnable() {
	return parameter->isAgingModeEnable();
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
	    throw IllegalArgumentException("");
	}
    }
    const MaxValue & TCONControl::getLUTBit() {
	return parameter->lutBit;
    }
    AnsiString TCONControl::getLUTType() {
        return parameter->dgLUTType;
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

    bptr < ByteBuffer > TCONControl::getDGLut12BitByteBufferType1(RGB_vector_ptr rgbVector) {
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

    bptr < ByteBuffer > TCONControl::getDGLut12BitByteBufferType2(RGB_vector_ptr rgbVector) {
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

		int c0 = d0lmh[1] + (d0lmh[2] << 4);
		int c1 = d1lmh[2] + (d0lmh[0] << 4);
		int c2 = d1lmh[0] + (d1lmh[1] << 4);
		(*data)[index++] = c0;
		(*data)[index++] = c1;
		(*data)[index++] = c2;
	    } if (remainder) {
		int d0 =
		    static_cast <
		    int >((*rgbVector)[rgbVector->size() - 1]->getValue(ch, MaxValue::Int12Bit));
		//int_array dlmh = getLMHData(d0);
                //int c0 = dlmh[1] + (dlmh[2] << 4);
		//int c1 = dlmh[0] << 4;

                //第257筆Data，為13 bit，做另外處理
                int c0 = d0 >> 5;         //取前面msb : 8bit
                int c1 = (d0 & 31) << 3;  //取後面lsb : 5bit 置於msb

		(*data)[index++] = c0;
		(*data)[index++] = c1;
	    }
	}
	return data;
    };

    void TCONControl::setDGLut(RGB_vector_ptr rgbVector) {
	const MaxValue & lutBit = getLUTBit();
        AnsiString lutType = getLUTType();
	bptr < ByteBuffer > data;

	if (lutBit == MaxValue::Int12Bit) {
            if(lutType == "12bitType1")        //Type define rule in "tconcontrol.h"
	        data = getDGLut12BitByteBufferType1(rgbVector);
            else if(lutType == "12bitType2")
                data = getDGLut12BitByteBufferType2(rgbVector);
	} else if (lutBit == MaxValue::Int10Bit) {
	    data = getDGLut10BitByteBuffer(rgbVector);
	}
	write(parameter->DGLutAddress, data);
    }
    RGB_vector_ptr TCONControl::getDGLut() {
	throw UnsupportedOperationException("");
    };

    int_array TCONControl::getLMHData(int data) {
	int_array result(new int[3]);
	result[0] = data & 15;
	result[1] = data >> 4 & 15;
	result[2] = data >> 8 & 15;
	return result;
    }
    void TCONControl::setDG(bool enable) {
	setSingleBitData(parameter->DGAddress, parameter->DGBit, enable);
    };
    bool TCONControl::isDG() {
	return getBitData(parameter->DGAddress, parameter->DGBit);
    };
    void TCONControl::setFRC(bool enable) {
	setSingleBitData(parameter->FRCAddress, parameter->FRCBit, enable);
    };
    bool TCONControl::isFRC() {
	return getBitData(parameter->FRCAddress, parameter->FRCBit);
    };
    void TCONControl::setSingleBitData(int dataAddress, unsigned char bit, bool data) {
	unsigned char bytedata = readByte(dataAddress);
	//製作遮罩
	unsigned char mask = ~(1 << bit);
	//挖掉要填的那個位元
	bytedata = bytedata & mask;
	//產生要填的data
	bytedata = bytedata | data << bit;
	writeByte(dataAddress, bytedata);
    };
                                 //1.EEPROM位址  2.開始bit  3.結束bit  4. 寫入值    byBS+
    void TCONControl::setBitData(int dataAddress, unsigned char Startbit,
                                 unsigned char Endbit, unsigned char data) {
	unsigned char bytedata = readByte(dataAddress);
        unsigned char bitlength = (Endbit-Startbit+1);

	//製作遮罩
	unsigned char mask = 255 &  ~ (((1 << bitlength )-1)  << Startbit);
	//挖掉要填的位元
	bytedata = bytedata & mask;
	//產生要填的data
	bytedata = bytedata | data << Startbit;
	writeByte(dataAddress, bytedata);
    };

    bool TCONControl::getBitData(int dataAddress, unsigned char bit) {
	unsigned char bytedata = readByte(dataAddress);
	bytedata = bytedata >> bit;
	bytedata = bytedata & 1;
	return (1 == bytedata);
    };
};

