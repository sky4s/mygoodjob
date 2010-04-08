#ifndef TCONPARAMETERH
#define TCONPARAMETERH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
//nclude <cms/colorformat/excelfile.h>

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
		    const int bLowBit, const int bHighBit,
		    const int totalByte);
	/*static const TestRGBBit & getIndependentInstance();
	   static const TestRGBBit & getDependentInstance(); */
	//private:
	static const TestRGBBit IndependentInstance;
	static const TestRGBBit DependentInstance;
    };

    class TCONParameter {
      public:
	const int gammaTestAddress;
	const int testRGBAddress;
	const unsigned char gammaTestBit;
	const Dep::MaxValue & lutBit;
	const TestRGBBit & testRGBBit;

      public:
	 TCONParameter(int gammaTestAddress,
		       unsigned char gammaTestBit, int testRGBAddress,
		       bool independentRGB, const Dep::MaxValue & lutBit);
	 TCONParameter(int gammaTestAddress,
		       unsigned char gammaTestBit, int testRGBAddress,
		       const TestRGBBit & testRGBBit,
		       const Dep::MaxValue & lutBit);
    };

};

#endif

