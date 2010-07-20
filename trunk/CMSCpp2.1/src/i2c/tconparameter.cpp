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
	DGLutAddress(-1), DGAddress(DGAddress), DGBit(DGBit) {

    };
    /*TCONParameter::TCONParameter(int gammaTestAddress,
       unsigned char gammaTestBit,
       int testRGBAddress, bool independentRGB,
       const Dep::MaxValue & lutBit,
       int DGLutAddress):gammaTestAddress
       (gammaTestAddress), gammaTestBit(gammaTestBit),
       testRGBAddress(testRGBAddress), lutBit(lutBit),
       testRGBBit(independentRGB ? TestRGBBit::
       IndependentInstance : TestRGBBit::DependentInstance),
       DGLutAddress(DGLutAddress) {

       }; */
    TCONParameter::TCONParameter(const int gammaTestAddress,
				 const unsigned char gammaTestBit,
				 const int testRGBAddress,
				 const TestRGBBit & testRGBBit,
				 const Dep::MaxValue & lutBit, const int
				 DGLutAddress, const int DGAddress, const unsigned char
				 DGBit):gammaTestAddress(gammaTestAddress),
	gammaTestBit(gammaTestBit), testRGBAddress(testRGBAddress),
	lutBit(lutBit), testRGBBit(testRGBBit), DGLutAddress(DGLutAddress),
	DGAddress(DGAddress), DGBit(DGBit) {

    };
    TestRGBBit::TestRGBBit(const int rLowBit, const int rHighBit,
			   const int gLowBit, const int gHighBit,
			   const int bLowBit, const int bHighBit,
			   const int totalByte)
    :rLowBit(rLowBit), rHighBit(rHighBit), gLowBit(gLowBit),
	gHighBit(gHighBit), bLowBit(bLowBit), bHighBit(bHighBit),
	totalByte(totalByte) {

    };
    //12401
    const TestRGBBit TestRGBBit::IndependentInstance(8, 0, 24, 16, 40,
						     32, 6);
    //12403
    const TestRGBBit TestRGBBit::DependentInstance(0, 8, 16, 12, 24,
						   32, 5);
};

