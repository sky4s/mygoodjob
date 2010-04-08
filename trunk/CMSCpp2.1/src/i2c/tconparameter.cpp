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
		   IndependentInstance : TestRGBBit::DependentInstance) {

    };
    TCONParameter::TCONParameter(int gammaTestAddress,
				 unsigned char gammaTestBit,
				 int testRGBAddress,
				 const TestRGBBit & testRGBBit,
				 const Dep::
				 MaxValue &
				 lutBit):gammaTestAddress
	(gammaTestAddress), gammaTestBit(gammaTestBit),
	testRGBAddress(testRGBAddress), lutBit(lutBit),
	testRGBBit(testRGBBit) {

    };
    TestRGBBit::TestRGBBit(const int rLowBit, const int rHighBit,
			   const int gLowBit, const int gHighBit,
			   const int bLowBit, const int bHighBit,
			   const int totalByte)
    :rLowBit(rLowBit), rHighBit(rHighBit), gLowBit(gLowBit),
	gHighBit(gHighBit), bLowBit(bLowBit), bHighBit(bHighBit),
	totalByte(totalByte) {

    };
    const TestRGBBit TestRGBBit::IndependentInstance(8, 0, 24, 16, 40, 32,
						     6);
    const TestRGBBit TestRGBBit::DependentInstance(0, 8, 16, 12, 24, 32,
						   5);
    /*const TestRGBBit TestRGBBit::getIndependentInstance() {
       TestRGBBit rgbbit(8, 0, 24, 16, 40, 32);
       return rgbbit;
       };
       const TestRGBBit TestRGBBit::getDependentInstance() {
       TestRGBBit rgbbit(0, 8, 16, 12, 24, 32);
       return rgbbit;
       }; */
};

