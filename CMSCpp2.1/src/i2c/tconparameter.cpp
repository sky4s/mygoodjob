#include "tconparameter.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace i2c {
    using namespace Dep;
     TCONParameter::TCONParameter(int gammaTestAddress,
				  unsigned char gammaTestBit,
				  int testRGBAddress,
				  bool independentRGB,
				  const MaxValue &
				  lutBit):gammaTestAddress
	(gammaTestAddress), gammaTestBit(gammaTestBit),
	testRGBAddress(testRGBAddress), lutBit(lutBit),
	testRGBBit(independentRGB ? TestRGBBit::
		   IndependentInstance : TestRGBBit::DependentInstance),
	DGLutAddress(-1), DGAddress(-1), DGBit(0), gammaTest(true), FRCAddress(-1), FRCBit(0),
	hideENAddress(-1), hideENBit(-1), hideEn(false) {

    };
    TCONParameter::TCONParameter(const Dep::MaxValue & lutBit, const int
				 DGLutAddress, const int DGAddress, const unsigned char
				 DGBit, const int gammaTestAddress,
				 const unsigned char gammaTestBit,
				 const int testRGBAddress,
				 const TestRGBBit & testRGBBit, const int FRCAddress,
				 const unsigned char FRCBit):gammaTestAddress(gammaTestAddress),
	gammaTestBit(gammaTestBit), testRGBAddress(testRGBAddress), lutBit(lutBit),
	testRGBBit(testRGBBit), DGLutAddress(DGLutAddress), DGAddress(DGAddress), DGBit(DGBit),
	gammaTest(true), FRCAddress(FRCAddress), FRCBit(FRCBit), hideENAddress(-1),
	hideENBit(-1), hideEn(false) {

    };
    TCONParameter::TCONParameter(const Dep::MaxValue & lutBit, const int
				 DGLutAddress, const int DGAddress, const unsigned char
				 DGBit, const int gammaTestAddress,
				 const unsigned char gammaTestBit,
				 const int testRGBAddress,
				 const TestRGBBit & testRGBBit, const int FRCAddress,
				 const unsigned char FRCBit, const int hideENAddress,
				 const unsigned char hideENBit):gammaTestAddress(gammaTestAddress),
	gammaTestBit(gammaTestBit), testRGBAddress(testRGBAddress), lutBit(lutBit),
	testRGBBit(testRGBBit), DGLutAddress(DGLutAddress), DGAddress(DGAddress), DGBit(DGBit),
	gammaTest(true), FRCAddress(FRCAddress), FRCBit(FRCBit), hideENAddress(hideENAddress),
	hideENBit(hideENBit), hideEn(true) {

    };
    TCONParameter::TCONParameter(const Dep::MaxValue & lutBit, const int DGLutAddress,
				 const int DGAddress,
				 const unsigned char DGBit, const int FRCAddress,
				 const unsigned char FRCBit):gammaTestAddress(-1), gammaTestBit(-1),
	testRGBAddress(-1), lutBit(lutBit), testRGBBit(testRGBBit), DGLutAddress(DGLutAddress),
	DGAddress(DGAddress), DGBit(DGBit), gammaTest(false), FRCAddress(FRCAddress),
	FRCBit(FRCBit), hideENAddress(-1), hideENBit(-1), hideEn(false) {
    };
    TestRGBBit::TestRGBBit(const int rLowBit, const int rHighBit,
			   const int gLowBit, const int gHighBit,
			   const int bLowBit, const int bHighBit, const int totalByte,
			   const int patternBit)
    :rLowBit(rLowBit), rHighBit(rHighBit), gLowBit(gLowBit), gHighBit(gHighBit), bLowBit(bLowBit),
	bHighBit(bHighBit), totalByte(totalByte), patternBit(patternBit) {

    };
    bool TCONParameter::isGammaTestEnable() {
	return gammaTest;
    };
    bool TCONParameter::isHideEnable() {
	return hideEn;
    };

    bool TestRGBBit::operator==(const TestRGBBit & t) const {
	return this->rLowBit == t.rLowBit && this->rHighBit == t.rHighBit &&
	    this->gLowBit == t.gLowBit && this->gHighBit == t.gHighBit &&
	    this->bLowBit == t.bLowBit && this->bHighBit == t.bHighBit &&
	    this->totalByte == t.totalByte && this->patternBit == t.patternBit;

    };

    //12401  RL RH GL GH BL BG
    //
    const TestRGBBit TestRGBBit::IndependentInstance(8, 0, 24, 16, 40, 32, 6, 12);
    //12403
    const TestRGBBit TestRGBBit::DependentInstance(0, 8, 16, 12, 24, 32, 5, 12);
    //62301 |BHGHRH|RL|GL|BL|
    const TestRGBBit TestRGBBit::TCON62301Instance(8, 4, 16, 2, 24, 0, 4, 10);
    //1H501
    const TestRGBBit TestRGBBit::TCON1H501Instance(0, 8, 16, 24, 32, 40, 6, 10);
    const TestRGBBit TestRGBBit::NotAssignInstance(0, 0, 0, 0, 0, 0, 0, 12);
};

