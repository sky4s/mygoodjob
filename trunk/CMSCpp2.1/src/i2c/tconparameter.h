#ifndef TCONPARAMETERH
#define TCONPARAMETERH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include <cms/cms.h>

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
	const int patternBit;
	 TestRGBBit(const int rLowBit, const int rHighBit,
		    const int gLowBit, const int gHighBit,
		    const int bLowBit, const int bHighBit, const int totalByte,
		    const int patternBit);
	bool operator==(const TestRGBBit &) const;	// use member function

	static const TestRGBBit IndependentInstance;
	static const TestRGBBit DependentInstance;
	static const TestRGBBit TCON62301Instance;
	static const TestRGBBit NotAssignInstance;

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
	// FRC On/Off
	//======================================================================
	const int FRCAddress;
	const unsigned char FRCBit;
	//======================================================================
	const Dep::MaxValue & lutBit;

      public:
	 TCONParameter(int gammaTestAddress,
		       unsigned char gammaTestBit, int testRGBAddress,
		       bool independentRGB, const Dep::MaxValue & lutBit);
	 TCONParameter(const Dep::MaxValue & lutBit,
		       const int DGLutAddress, const int DGAddress, const unsigned char DGBit,
		       const int gammaTestAddress, const unsigned char gammaTestBit,
		       const int testRGBAddress, const TestRGBBit & testRGBBit,
		       const int FRCAddress, const unsigned char FRCBit);
	 TCONParameter(const Dep::MaxValue & lutBit, const int DGLutAddress, const int DGAddress,
		       const unsigned char DGBit, const int FRCAddress, const unsigned char FRCBit);
	bool isGammaTestEnable();
    };

};

#endif

