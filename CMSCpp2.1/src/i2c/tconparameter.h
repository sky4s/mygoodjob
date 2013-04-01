#ifndef TCONPARAMETERH
#define TCONPARAMETERH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include <cms/cms.h>

namespace i2c {

    class DirectGammaType {
      public:
	const int rLowBit;
	const int rHighBit;
	const int gLowBit;
	const int gHighBit;
	const int bLowBit;
	const int bHighBit;
	const int totalByte;
	const int patternBit;
	 DirectGammaType(const int rLowBit, const int rHighBit,
			 const int gLowBit, const int gHighBit,
			 const int bLowBit, const int bHighBit, const int totalByte,
			 const int patternBit);
	bool operator==(const DirectGammaType &) const;	// use member function

	static const DirectGammaType IndependentInstance;
	static const DirectGammaType DependentInstance;
	static const DirectGammaType TCON62301Instance;
	static const DirectGammaType TCON1H501Instance;
	static const DirectGammaType NotAssignInstance;
	static const DirectGammaType TCON12409AgingInstance;
    };

    class TCONParameter {
      public:
	//======================================================================
	// gamma test(direct gamma)
	//======================================================================
	const int gammaTestAddress;
	const int directGammaRGBAddress;
	const unsigned char gammaTestBit;
	const DirectGammaType & directGammaType;
	const bool gammaTest;
	//hide en
	const bool hideEn;
	const int hideENAddress;
	const unsigned char hideENBit;
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
		       unsigned char gammaTestBit, int directGammaRGBAddress,
		       bool independentRGB, const Dep::MaxValue & lutBit);
	 TCONParameter(const Dep::MaxValue & lutBit,
		       const int DGLutAddress, const int DGAddress, const unsigned char DGBit,
		       const int gammaTestAddress, const unsigned char gammaTestBit,
		       const int directGammaRGBAddress, const DirectGammaType & directGammaType,
		       const int FRCAddress, const unsigned char FRCBit);
	 TCONParameter(const Dep::MaxValue & lutBit,
		       const int DGLutAddress, const int DGAddress, const unsigned char DGBit,
		       const int gammaTestAddress, const unsigned char gammaTestBit,
		       const int directGammaRGBAddress, const DirectGammaType & directGammaType,
		       const int FRCAddress, const unsigned char FRCBit,
		       const int hideENAddress, const unsigned char hideENBit);
	 TCONParameter(const Dep::MaxValue & lutBit, const int DGLutAddress, const int DGAddress,
		       const unsigned char DGBit, const int FRCAddress, const unsigned char FRCBit);
	bool isGammaTestEnable();
	bool isHideEnable();
    };

};

#endif

