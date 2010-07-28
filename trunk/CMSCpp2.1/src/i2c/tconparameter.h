#ifndef TCONPARAMETERH
#define TCONPARAMETERH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>

namespace i2c {

    class TestRGBBit {
      public:
	const int rLowBit;
	const int rHighBit;
	const int gLowBit;
	const int gHighBit;
	const int bLowBit;
	const int bHighBit;
	const int totalByte;
	 TestRGBBit(const int rLowBit, const int rHighBit,
		    const int gLowBit, const int gHighBit,
		    const int bLowBit, const int bHighBit, const int totalByte);

	static const TestRGBBit IndependentInstance;
	static const TestRGBBit DependentInstance;
    };

    class TCONParameter {
      public:
	//======================================================================
	// gamma test(direct gamma)
	//======================================================================
	const int gammaTestAddress;
	const int testRGBAddress;
	const unsigned char gammaTestBit;
	const TestRGBBit & testRGBBit;
	const bool gammaTest;
	//======================================================================
	// DG On/Off , Lut
	//======================================================================
	const int DGLutAddress;
	const int DGAddress;
	const unsigned char DGBit;
	//======================================================================

	const Dep::MaxValue & lutBit;

      public:
	 TCONParameter(int gammaTestAddress,
		       unsigned char gammaTestBit, int testRGBAddress,
		       bool independentRGB, const Dep::MaxValue & lutBit);
	 TCONParameter(const Dep::MaxValue & lutBit,
		       const int DGLutAddress, const int DGAddress, const unsigned char DGBit,
		       const int gammaTestAddress, const unsigned char gammaTestBit,
		       const int testRGBAddress, const TestRGBBit & testRGBBit);
	 TCONParameter(const Dep::MaxValue & lutBit, const int DGLutAddress, const int DGAddress,
		       const unsigned char DGBit);
	bool isGammaTestEnable();
    };

};

#endif

