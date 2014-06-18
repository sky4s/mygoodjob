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
        //11311  |RH|RL|GH|GL|BH|BL|    (10-bit)
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

    /*bptr < cms::util::ByteBuffer > TCONControl::getRGBByteBufferWith12411Aging(int gray,
									       const DirectGammaType
									       & directGammaType) {

    };*/

    bptr < cms::util::ByteBuffer > TCONControl::getRGBByteBufferWith12411(int r, int g, int b,
									       const DirectGammaType
									       & directGammaType) {
        //12411  |RH|RL|GH|GL|BH|BL|    (12-bit)
        //        8  4  8  4  8  4
	int rLow = (r & 15) << 4;
	int rHigh = r >> 4;
	int gLow = (g & 15) << 4;
	int gHigh = g >> 4;
	int bLow = (b & 15) << 4;
	int bHigh = b >> 4;

        int totalByte = directGammaType.totalByte;

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
        } else if (DirectGammaType::TCON11311Instance == directGammaType) {
            return getRGBByteBufferWith11311(r, g, b, directGammaType);
        } else if (DirectGammaType::TCON12411Instance == directGammaType) {
            return getRGBByteBufferWith12411(r, g, b, directGammaType);
        }
        /*else if (DirectGammaType::TCON12411AgingInstance == directGammaType) {
            return getRGBByteBufferWith12411Aging(r, directGammaType);  //取其一當作灰階
        }*/    //因為要讀byte 搬到TCONControl::setAgingModeRGB()裡面作...

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
        //int EnableAddress = parameter->gammaTestAddress;
        int RGBAddress = parameter->directGammaRGBAddress;
        //int totalByte = directGammaType.totalByte;

        /*if(EnableAddress >= RGBAddress && EnableAddress < RGBAddress+totalByte)
        {
            //--------------------For AUO11311-----------------------
            unsigned char bytedata = readByte(EnableAddress);
            (*data)[1] = (*data)[1] | bytedata;
            //-------------------------------------------------------

            ShowMessage("Waring : Direct gamma Enable address conflict");
            return 0;
        }*/  //造成62301 type 會出現警告....先註掉

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

        bool isSecondGamma = parameter->secondGamma;
        if(isSecondGamma) {      //當有兩張DG時 (DirectGamma也兩個)
            int RGBAddress2 = parameter->directGamma2RGBAddress;
            write(RGBAddress2, data);
            bptr < ByteBuffer > dataFrom0 = read(RGBAddress2, size, 0);
            if (!dualTCON) {
                //1 tcon
                return data->equals(dataFrom0);
            } else {
                //2 tcon
                bptr < ByteBuffer > dataFrom1 = read(RGBAddress2, size, 1);
                return data->equals(dataFrom0) && data->equals(dataFrom1);
            }
        }
    };

    bool TCONControl::setAgingModeRGB(int r, int g, int b) {

	const DirectGammaType & agingModeType = parameter->agingModeType;

        //Special case : 12411 因為要讀byte，在這作處理
        if(agingModeType == DirectGammaType::TCON12411AgingInstance)
        {
            //12411 Aging  只有10-bit 分開兩位子且都跟其他設定綁一起(須先讀在寫)
            //[9:4](bit:0~5)，[3:0](bit:0~3)

            //因為AUO-12411像是TCON的Special case 所以設定先寫死
            unsigned char bytedata = readByte(80);  //(Dec)
            int high = (bytedata & 192) | (r >> 4);      //取r當灰階值就好

            bytedata = readByte(81);
            int low = (bytedata & 240) | (r & 15);

            bptr < ByteBuffer > data(new ByteBuffer(2));
            //先清空buffer
            for (int x = 0; x < 2; x++) {
                (*data)[x] = 0;
            }

            (*data)[0] = high;
            (*data)[1] = low;

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
        } else {
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
        }
    };

    bool TCONControl::setPGModeRGB(int r, int g, int b) {  //byBS+ 20140506
        //Current support AUO-12802
        //Setting PG_PTN

        //Method 1: 寫完時讀出來比較還要寫..先不用
        /*
        setTwoByteData(parameter->pgPatternMSBAddress, parameter->pgPatternMSBStartBit, parameter->pgPatternMSBEndBit,
                       parameter->pgPatternLSBAddress, parameter->pgPatternLSBStartBit, parameter->pgPatternLSBEndBit,
                       r);  //利用一個 Channel 就可以了
        */

        //感覺PG Mode 只是過度，排列格式先固定寫法 (不然應該可以用Address map寫出彈性)
        unsigned char bytedata = readByte(parameter->pgPatternMSBAddress);  //(Dec)
        int high = (bytedata & 192) | (r >> 4);      //取r當灰階值就好

        bytedata = readByte(parameter->pgPatternLSBAddress);
        int low = (bytedata & 15) | (r & 15)<<4;

        bptr < ByteBuffer > data(new ByteBuffer(2));
        //先清空buffer
        for (int x = 0; x < 2; x++) {
            (*data)[x] = 0;
        }
        (*data)[0] = high;
        (*data)[1] = low;

        int address = parameter->pgPatternMSBAddress;
        write(address, data);
        int size = data->getSize();
        bptr < ByteBuffer > dataFrom0 = read(address, size, 0);

        if (!dualTCON) { //1 tcon
            return data->equals(dataFrom0);
        } else {          //2 tcon
            bptr < ByteBuffer > dataFrom1 = read(address, size, 1);
            return data->equals(dataFrom0) && data->equals(dataFrom1);
        }
    }

    void TCONControl::setGammaTest(bool enable) {
	if (enable && parameter->isHideEnable()) {
	    setSingleBitData(parameter->hideENAddress, parameter->hideENBit, enable);
	}
	setSingleBitData(parameter->gammaTestAddress, parameter->gammaTestBit, enable);

        if(parameter->secondGamma) {    //for two DG (DirectGamma也兩個)
            setSingleBitData(parameter->gammaTest2Address, parameter->gammaTest2Bit, enable);
        }

	if (!enable && parameter->isHideEnable()) {
	    setSingleBitData(parameter->hideENAddress, parameter->hideENBit, enable);
	}
    };

    void TCONControl::setTconAgingMode(bool enable) {
        //1. AG_PTN_SEL
        //2. AG_MODE_SEL
        //3. AG_MANU_SEL    (目前只有AUO-12411/2有,12409無)  201312 by BS+
        //4. AGBS_DEBUG
        setBitData(parameter->agingPatternSelectAddress, parameter->agingPatternSelectStartBit,
                   parameter->agingPatternSelectEndBit, parameter->agingPatternSelectValue);
        setSingleBitData(parameter->agingModeSelectAddress, parameter->agingModeSelectBit, enable);
        if(parameter->agingManuSelectAddress != -1) {
            setSingleBitData(parameter->agingManuSelectAddress, parameter->agingManuSelectBit, 0); //0: 選Type 1(AUO)
        }
        setSingleBitData(parameter->agingAGBSDebugAddress, parameter->agingAGBSDebugBit, enable);
    };

    //Current for 12411/2        201406011 byBS+
    void TCONControl::setTconAgingTiming(bool enable) {

        if(parameter->agingTimingControl){
            //1. AG_FRM_RATE[1:0]
            //2. AG_MPLL_MODE[1:0]
            //3. AG_MPLL_N[5:0]   4. AG_MPLL_F[15:0]   5. AG_MPLL_M[1:0]
            //7. AG_HBLK[10:0]   8. AG_VBLK1[10:0]   9. AG_VBLK2[10:0]

            setBitData(parameter->agingFrameRateAddress, parameter->agingFrameRateStartBit,
                       parameter->agingFrameRateEndBit, parameter->agingFrameRate);
            setBitData(parameter->agingMpllModeAddress, parameter->agingMpllModeStartBit,
                       parameter->agingMpllModeEndBit, parameter->agingMpllModeValue);
            /*setBitData(parameter->agingMpllNAddress, parameter->agingMpllNStartBit,
                       parameter->agingMpllNEndBit, parameter->agingMpllNValue); */
            setTwoByteData(parameter->agingMpllNMSBAddress, parameter->agingMpllNMSBStartBit, parameter->agingMpllNMSBEndBit,
                           parameter->agingMpllNLSBAddress, parameter->agingMpllNLSBStartBit, parameter->agingMpllNLSBEndBit,
                           parameter->agingMpllNValue);
            setTwoByteData(parameter->agingMpllFMSBAddress, parameter->agingMpllFMSBStartBit, parameter->agingMpllFMSBEndBit,
                           parameter->agingMpllFLSBAddress, parameter->agingMpllFLSBStartBit, parameter->agingMpllFLSBEndBit,
                           parameter->agingMpllFValue);
            setBitData(parameter->agingMpllMAddress, parameter->agingMpllMStartBit,
                       parameter->agingMpllMEndBit, parameter->agingMpllMValue);
            setTwoByteData(parameter->agingHblkMSBAddress, parameter->agingHblkMSBStartBit, parameter->agingHblkMSBEndBit,
                           parameter->agingHblkLSBAddress, parameter->agingHblkLSBStartBit, parameter->agingHblkLSBEndBit,
                           parameter->agingHblkValue);
            setTwoByteData(parameter->agingVblk1MSBAddress, parameter->agingVblk1MSBStartBit, parameter->agingVblk1MSBEndBit,
                           parameter->agingVblk1LSBAddress, parameter->agingVblk1LSBStartBit, parameter->agingVblk1LSBEndBit,
                           parameter->agingVblk1Value);
            setTwoByteData(parameter->agingVblk2MSBAddress, parameter->agingVblk2MSBStartBit, parameter->agingVblk2MSBEndBit,
                           parameter->agingVblk2LSBAddress, parameter->agingVblk2LSBStartBit, parameter->agingVblk2LSBEndBit,
                           parameter->agingVblk2Value);

        }

    };

    void TCONControl::setTconPGMode(bool enable) {
        //1. PG_HBLK
        //2. PG_VBLK
        //3. PG_MODE
        //4. PG_EN
        setTwoByteData(parameter->pgHblkMSBAddress, parameter->pgHblkMSBStartBit, parameter->pgHblkMSBEndBit,
                       parameter->pgHblkLSBAddress, parameter->pgHblkLSBStartBit, parameter->pgHblkLSBEndBit,
                       parameter->pgHblkValue);
        setTwoByteData(parameter->pgVblkMSBAddress, parameter->pgVblkMSBStartBit, parameter->pgVblkMSBEndBit,
                       parameter->pgVblkLSBAddress, parameter->pgVblkLSBStartBit, parameter->pgVblkLSBEndBit,
                       parameter->pgVblkValue);
        setBitData(parameter->pgModeAddress, parameter->pgModeStartBit, parameter->pgModeEndBit, 7); //最低位元3bit on
        setSingleBitData(parameter->pgEnableAddress, parameter->pgEnableBit, enable);

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
    bool TCONControl::isPGModeEnable() {
	return parameter->isPGModeEnable();
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
        if(parameter->secondGamma) {
            write(parameter->DG2LutAddress, data);
        }

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

        if(parameter->secondGamma)
            setSingleBitData(parameter->DG2Address, parameter->DG2Bit, enable);
    };
    bool TCONControl::isDG() {
	return getBitData(parameter->DGAddress, parameter->DGBit);
    };
    void TCONControl::setFRC(bool enable) {
	setSingleBitData(parameter->FRCAddress, parameter->FRCBit, enable);

        if(parameter->secondGamma)
            setSingleBitData(parameter->FRC2Address, parameter->FRC2Bit, enable);
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
	unsigned char mask = 255 &  ~ (((1<<bitlength)-1) << Startbit);
	//挖掉要填的位元
	bytedata = bytedata & mask;
	//產生要填的data
	bytedata = bytedata | data << Startbit;
	writeByte(dataAddress, bytedata);
    };

    //1.MSB位址  2.MSB開始bit  3.MSB結束bit  4.LSB位址  5.LSB開始bit  6.LSB結束bit  7.寫入Value    byBS+
    void TCONControl::setTwoByteData(int MSBAddress, unsigned char MSB_Startbit, unsigned char MSB_Endbit,
                                     int LSBAddress, unsigned char LSB_Startbit, unsigned char LSB_Endbit,
                                     int value) {
        unsigned char MSB_bytedata = readByte(MSBAddress);
        unsigned char LSB_bytedata = readByte(LSBAddress);
        unsigned char MSB_bitlength = (MSB_Endbit-MSB_Startbit+1);
        unsigned char LSB_bitlength = (LSB_Endbit-LSB_Startbit+1);

        //----------------- MSB Byte -----------------
	//製作遮罩
	unsigned char mask = 255 &  ~ (((1<<MSB_bitlength)-1) << MSB_Startbit);
	//挖掉要填的位元
	MSB_bytedata = MSB_bytedata & mask;
        //要填的data
        int temp_value = value >> (LSB_bitlength);
	//產生要填的data
	MSB_bytedata = MSB_bytedata | (temp_value << MSB_Startbit);
        writeByte(MSBAddress, MSB_bytedata);

        //----------------- LSB Byte -----------------
	mask = 255 &  ~ (((1<<LSB_bitlength)-1) << LSB_Startbit);
	LSB_bytedata = LSB_bytedata & mask;
        temp_value = value & ((1<<LSB_bitlength)-1);    //差異處
	LSB_bytedata = LSB_bytedata | (temp_value << LSB_Startbit);
        writeByte(LSBAddress, LSB_bytedata);
    };

    bool TCONControl::getBitData(int dataAddress, unsigned char bit) {
	unsigned char bytedata = readByte(dataAddress);
	bytedata = bytedata >> bit;
	bytedata = bytedata & 1;
	return (1 == bytedata);
    };
};

