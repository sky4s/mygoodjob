#include "tconparameter.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace i2c {
    using namespace Dep;
     TCONParameter::TCONParameter(int gammaTestAddress,
				  unsigned char gammaTestBit,
				  int directGammaRGBAddress,
				  bool independentRGB,
				  const MaxValue &
				  lutBit):gammaTestAddress
	(gammaTestAddress), gammaTestBit(gammaTestBit),
	directGammaRGBAddress(directGammaRGBAddress), lutBit(lutBit),
	directGammaType(independentRGB ? DirectGammaType::
			IndependentInstance : DirectGammaType::DependentInstance),
	DGLutAddress(-1), DGAddress(-1), DGBit(0), gammaTest(true), FRCAddress(-1), FRCBit(0),
	hideENAddress(-1), hideENBit(-1), hideEn(false), agingModeSelectAddress(-1),
        agingModeSelectBit(-1), agingPatternSelectAddress(-1), agingPatternSelectValue(-1),
        agingPatternSelectStartBit(-1), agingPatternSelectEndBit(-1), agingRasterGrayAddress(-1),
        agingModeType(agingModeType), agingMode(false) {
    };
    TCONParameter::TCONParameter(const Dep::MaxValue & lutBit, const int
				 DGLutAddress, const int DGAddress, const unsigned char
				 DGBit, const int gammaTestAddress,
				 const unsigned char gammaTestBit,
				 const int directGammaRGBAddress,
				 const DirectGammaType & directGammaType, const int FRCAddress,
				 const unsigned char FRCBit):gammaTestAddress(gammaTestAddress),
	gammaTestBit(gammaTestBit), directGammaRGBAddress(directGammaRGBAddress), lutBit(lutBit),
	directGammaType(directGammaType), DGLutAddress(DGLutAddress), DGAddress(DGAddress),
	DGBit(DGBit), gammaTest(true), FRCAddress(FRCAddress), FRCBit(FRCBit), hideENAddress(-1),
	hideENBit(-1), hideEn(false), agingModeSelectAddress(-1),
        agingModeSelectBit(-1), agingPatternSelectAddress(-1), agingPatternSelectValue(-1),
        agingPatternSelectStartBit(-1), agingPatternSelectEndBit(-1), agingRasterGrayAddress(-1),
        agingModeType(agingModeType), agingMode(false) {
    };
    TCONParameter::TCONParameter(const Dep::MaxValue & lutBit, const int
				 DGLutAddress, const int DGAddress, const unsigned char
				 DGBit, const int gammaTestAddress,
				 const unsigned char gammaTestBit,
				 const int directGammaRGBAddress,
				 const DirectGammaType & directGammaType, const int FRCAddress,
				 const unsigned char FRCBit, const int hideENAddress,
				 const unsigned char hideENBit):gammaTestAddress(gammaTestAddress),
	gammaTestBit(gammaTestBit), directGammaRGBAddress(directGammaRGBAddress), lutBit(lutBit),
	directGammaType(directGammaType), DGLutAddress(DGLutAddress), DGAddress(DGAddress),
	DGBit(DGBit), gammaTest(true), FRCAddress(FRCAddress), FRCBit(FRCBit),
	hideENAddress(hideENAddress), hideENBit(hideENBit), hideEn(true), agingModeSelectAddress(-1),
        agingModeSelectBit(-1), agingPatternSelectAddress(-1), agingPatternSelectValue(-1),
        agingPatternSelectStartBit(-1), agingPatternSelectEndBit(-1), agingRasterGrayAddress(-1),
        agingModeType(agingModeType), agingMode(false) {
    };

    //for aging mode. byBS++
    TCONParameter::TCONParameter(const Dep::MaxValue & lutBit, const int
                                 DGLutAddress, const int DGAddress, const unsigned char
                                 DGBit, const int gammaTestAddress,
                                 const unsigned char gammaTestBit,
                                 const int directGammaRGBAddress,
                                 const DirectGammaType & directGammaType, const int FRCAddress,
                                 const unsigned char FRCBit, const int agingModeSelectAddress,
                                 const unsigned char agingModeSelectBit,
                                 const int agingPatternSelectAddress,
                                 const unsigned char agingPatternSelectValue,
                                 const unsigned char agingPatternSelectStartBit,
                                 const unsigned char agingPatternSelectEndBit,
                                 const int agingRasterGrayAddress,
                                 const DirectGammaType & agingModeType):gammaTestAddress(gammaTestAddress),
	gammaTestBit(gammaTestBit), directGammaRGBAddress(directGammaRGBAddress), lutBit(lutBit),
	directGammaType(directGammaType), DGLutAddress(DGLutAddress), DGAddress(DGAddress),
	DGBit(DGBit), gammaTest(true), FRCAddress(FRCAddress), FRCBit(FRCBit), hideENAddress(-1),
	hideENBit(-1), hideEn(false), agingModeSelectAddress(agingModeSelectAddress),
        agingModeSelectBit(agingModeSelectBit), agingPatternSelectAddress(agingPatternSelectAddress),
        agingPatternSelectValue(agingPatternSelectValue),
        agingPatternSelectStartBit(agingPatternSelectStartBit),
        agingPatternSelectEndBit(agingPatternSelectEndBit), agingRasterGrayAddress(agingRasterGrayAddress),
        agingModeType(agingModeType), agingMode(true) {
    };

    TCONParameter::TCONParameter(const Dep::MaxValue & lutBit, const int DGLutAddress,
				 const int DGAddress,
				 const unsigned char DGBit, const int FRCAddress,
				 const unsigned char FRCBit):gammaTestAddress(-1), gammaTestBit(-1),
	directGammaRGBAddress(-1), lutBit(lutBit), directGammaType(directGammaType),
	DGLutAddress(DGLutAddress), DGAddress(DGAddress), DGBit(DGBit), gammaTest(false),
	FRCAddress(FRCAddress), FRCBit(FRCBit), hideENAddress(-1), hideENBit(-1), hideEn(false),
        agingModeSelectAddress(-1), agingModeSelectBit(-1), agingPatternSelectAddress(-1),
        agingPatternSelectValue(-1), agingPatternSelectStartBit(-1), agingPatternSelectEndBit(-1),
        agingRasterGrayAddress(-1), agingModeType(agingModeType), agingMode(false) {
    };
    DirectGammaType::DirectGammaType(const int rLowBit, const int rHighBit,
				     const int gLowBit, const int gHighBit,
				     const int bLowBit, const int bHighBit, const int totalByte,
				     const int patternBit)
    :rLowBit(rLowBit), rHighBit(rHighBit), gLowBit(gLowBit), gHighBit(gHighBit), bLowBit(bLowBit),
	bHighBit(bHighBit), totalByte(totalByte), patternBit(patternBit) {

    };
    bool TCONParameter::isGammaTestEnable() {
	return gammaTest;
    };
    //Aging Mode byBS+
    bool TCONParameter::isAgingModeEnable() {
	return agingMode;
    };
    bool TCONParameter::isHideEnable() {
	return hideEn;
    };

    bool DirectGammaType::operator==(const DirectGammaType & t) const {
	return this->rLowBit == t.rLowBit && this->rHighBit == t.rHighBit &&
	    this->gLowBit == t.gLowBit && this->gHighBit == t.gHighBit &&
	    this->bLowBit == t.bLowBit && this->bHighBit == t.bHighBit &&
	    this->totalByte == t.totalByte && this->patternBit == t.patternBit;

    };



    //format: RL RH GL GH BL BH TOTALBYTE BIT

    //12401 |RH |RL|GH |GL|BH |BL|
    const DirectGammaType DirectGammaType::IndependentInstance(8, 0, 24, 16, 40, 32, 6, 12);
    //12403 |RL|RHGH|GL|BL|BH  |
    const DirectGammaType DirectGammaType::DependentInstance(0, 8, 16, 12, 24, 32, 5, 12);
    //62301 |BHGHRH |RL|GL|BL|
    const DirectGammaType DirectGammaType::TCON62301Instance(8, 4, 16, 2, 24, 0, 4, 10);
    //1H501 |RL|RH |GL|GH |BL|BH |
    const DirectGammaType DirectGammaType::TCON1H501Instance(0, 8, 16, 24, 32, 40, 6, 10);
    //12409 Aging |RHRL1|RL2GHGL1|GL2BHBL1|BL2
    const DirectGammaType DirectGammaType::TCON12409AgingInstance(2, 0, 12, 10, 22, 20, 4, 10);
    //12409 |RH |RLGH|GL|BH |BL|
    const DirectGammaType DirectGammaType::TCON12409Instance(12, 0, 16, 8, 36, 24, 5, 12);
    const DirectGammaType DirectGammaType::NotAssignInstance(0, 0, 0, 0, 0, 0, 0, 12);
};

