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
        static const DirectGammaType TCON12409Instance;
        static const DirectGammaType TCON11311Instance;
        static const DirectGammaType TCON12411AgingInstance;
        static const DirectGammaType TCON12411Instance;
        static const DirectGammaType HawkTypeInstance;
    };

    class TCONParameter {
      public:
        const AnsiString tconNumber;
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
	// aging
	//======================================================================
        const bool agingMode;
        const int agingAGBSDebugAddress;
        const unsigned char agingAGBSDebugBit;
        const int agingModeSelectAddress;
        const int agingModeSelectValue;
        const unsigned char agingModeSelectStartBit;
        const unsigned char agingModeSelectEndBit;
        const int agingPatternSelectAddress;
        const unsigned char agingPatternSelectValue;
        const unsigned char agingPatternSelectStartBit;
        const unsigned char agingPatternSelectEndBit;
        const int agingRasterGrayAddress;
        const DirectGammaType & agingModeType;
        const int agingManuSelectAddress;
        const unsigned char agingManuSelectBit;
        //aging timing
        const bool agingTimingControl;
        const int agingFrameRate;
        const int agingFrameRateAddress;
        const unsigned char agingFrameRateStartBit;
        const unsigned char agingFrameRateEndBit;
        const int agingMpllModeAddress;
        const unsigned char agingMpllModeStartBit;
        const unsigned char agingMpllModeEndBit;
        const int agingMpllModeValue;
        const int agingMpllNMSBAddress;
        const unsigned char agingMpllNMSBStartBit;
        const unsigned char agingMpllNMSBEndBit;
        const int agingMpllNLSBAddress;
        const unsigned char agingMpllNLSBStartBit;
        const unsigned char agingMpllNLSBEndBit;
        const int agingMpllNValue;
        const int agingMpllFMSBAddress;
        const unsigned char agingMpllFMSBStartBit;
        const unsigned char agingMpllFMSBEndBit;
        const int agingMpllFLSBAddress;
        const unsigned char agingMpllFLSBStartBit;
        const unsigned char agingMpllFLSBEndBit;
        const int agingMpllFValue;
        const int agingMpllMAddress;
        const unsigned char agingMpllMStartBit;
        const unsigned char agingMpllMEndBit;
        const int agingMpllMValue;
        const int agingHblkMSBAddress;
        const unsigned char agingHblkMSBStartBit;
        const unsigned char agingHblkMSBEndBit;
        const int agingHblkLSBAddress;
        const unsigned char agingHblkLSBStartBit;
        const unsigned char agingHblkLSBEndBit;
        const int agingHblkValue;
        const int agingVblk1MSBAddress;
        const unsigned char agingVblk1MSBStartBit;
        const unsigned char agingVblk1MSBEndBit;
        const int agingVblk1LSBAddress;
        const unsigned char agingVblk1LSBStartBit;
        const unsigned char agingVblk1LSBEndBit;
        const int agingVblk1Value;
        const int agingVblk2MSBAddress;
        const unsigned char agingVblk2MSBStartBit;
        const unsigned char agingVblk2MSBEndBit;
        const int agingVblk2LSBAddress;
        const unsigned char agingVblk2LSBStartBit;
        const unsigned char agingVblk2LSBEndBit;
        const int agingVblk2Value;

	//======================================================================
	// Second gamma
	//======================================================================
        const bool secondGamma;
        const int DG2Address;
        const unsigned char DG2Bit;
        const int DG2LutAddress;
        const int gammaTest2Address;
        const unsigned char gammaTest2Bit;
        const int directGamma2RGBAddress;
        const int FRC2Address;
        const unsigned char FRC2Bit;
	//======================================================================
	// PG Mode
	//======================================================================
        const bool pgMode;
        const int pgEnableAddress;
        const unsigned char pgEnableBit;
        const int pgModeAddress;
        const unsigned char pgModeStartBit;
        const unsigned char pgModeEndBit;
        const int pgPatternMSBAddress;
        const unsigned char pgPatternMSBStartBit;
        const unsigned char pgPatternMSBEndBit;
        const int pgPatternLSBAddress;
        const unsigned char pgPatternLSBStartBit;
        const unsigned char pgPatternLSBEndBit;
        const int pgHblkMSBAddress;
        const unsigned char pgHblkMSBStartBit;
        const unsigned char pgHblkMSBEndBit;
        const int pgHblkLSBAddress;
        const unsigned char pgHblkLSBStartBit;
        const unsigned char pgHblkLSBEndBit;
        const int pgHblkValue;
        const int pgVblkMSBAddress;
        const unsigned char pgVblkMSBStartBit;
        const unsigned char pgVblkMSBEndBit;
        const int pgVblkLSBAddress;
        const unsigned char pgVblkLSBStartBit;
        const unsigned char pgVblkLSBEndBit;
        const int pgVblkValue;
	//======================================================================
	// DG On/Off , Lut
	//======================================================================
	const int DGLutAddress;
	const int DGAddress;
	const unsigned char DGBit;
        const AnsiString dgLUTType;
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
	 TCONParameter(const AnsiString tconNumber, const Dep::MaxValue & lutBit,
		       const int DGLutAddress, const AnsiString dgLUTType, const int DGAddress,
                       const unsigned char DGBit,
		       const int gammaTestAddress, const unsigned char gammaTestBit,
		       const int directGammaRGBAddress, const DirectGammaType & directGammaType,
		       const int FRCAddress, const unsigned char FRCBit);
	 TCONParameter(const AnsiString tconNumber,const Dep::MaxValue & lutBit,
		       const int DGLutAddress, const AnsiString dgLUTType, const int DGAddress,
                       const unsigned char DGBit,
		       const int gammaTestAddress, const unsigned char gammaTestBit,
		       const int directGammaRGBAddress, const DirectGammaType & directGammaType,
		       const int FRCAddress, const unsigned char FRCBit,
		       const int hideENAddress, const unsigned char hideENBit);

                       //For AgingMode    byBS+
         TCONParameter(const AnsiString tconNumber, const Dep::MaxValue & lutBit,
		       const int DGLutAddress, const AnsiString dgLUTType,
                       const int DGAddress, const unsigned char DGBit,
		       const int gammaTestAddress, const unsigned char gammaTestBit,
		       const int directGammaRGBAddress, const DirectGammaType & directGammaType,
		       const int FRCAddress, const unsigned char FRCBit,
                       const int agingAGBSDebugAddress, const unsigned char agingAGBSDebugBit,
                       const int agingModeSelectAddress, const int agingModeSelectValue,
                       const unsigned char agingModeSelectStartBit, const unsigned char agingModeSelectEndBit,
                       const int agingPatternSelectAddress, const unsigned char agingPatternSelectValue,
                       const unsigned char agingPatternSelectStartBit,
                       const unsigned char agingPatternSelectEndBit,
                       const int agingRasterGrayAddress, const DirectGammaType & agingModeType,
                       const int agingManuSelectAddress, const unsigned char agingManuSelectBit,
                       const bool agingTimingControl,
                       const int agingFrameRate, const int agingFrameRateAddress, const unsigned char agingFrameRateStartBit, const unsigned char agingFrameRateEndBit,
                       const int agingMpllModeAddress, const unsigned char agingMpllModeStartBit, const unsigned char agingMpllModeEndBit, const int agingMpllModeValue,
                       const int agingMpllNMSBAddress, const unsigned char agingMpllNMSBStartBit, const unsigned char agingMpllNMSBEndBit, const int agingMpllNLSBAddress, const unsigned char agingMpllNLSBStartBit, const unsigned char agingMpllNLSBEndBit, const int agingMpllNValue,
                       const int agingMpllFMSBAddress, const unsigned char agingMpllFMSBStartBit, const unsigned char agingMpllFMSBEndBit, const int agingMpllFLSBAddress, const unsigned char agingMpllFLSBStartBit, const unsigned char agingMpllFLSBEndBit, const int agingMpllFValue,
                       const int agingMpllMAddress, const unsigned char agingMpllMStartBit, const unsigned char agingMpllMEndBit, const int agingMpllMValue,
                       const int agingHblkMSBAddress, const unsigned char agingHblkMSBStartBit, const unsigned char agingHblkMSBEndBit, const int agingHblkLSBAddress, const unsigned char agingHblkLSBStartBit, const unsigned char agingHblkLSBEndBit, const int agingHblkValue,
                       const int agingVblk1MSBAddress, const unsigned char agingVblk1MSBStartBit, const unsigned char agingVblk1MSBEndBit, const int agingVblk1LSBAddress, const unsigned char agingVblk1LSBStartBit, const unsigned char agingVblk1LSBEndBit, const int agingVblk1Value,
                       const int agingVblk2MSBAddress, const unsigned char agingVblk2MSBStartBit, const unsigned char agingVblk2MSBEndBit, const int agingVblk2LSBAddress, const unsigned char agingVblk2LSBStartBit, const unsigned char agingVblk2LSBEndBit, const int agingVblk2Value
                       );


                       //For AgingMode + SecondGamma    byBS+
         TCONParameter(const AnsiString tconNumber, const Dep::MaxValue & lutBit,
		       const int DGLutAddress, const AnsiString dgLUTType,
                       const int DGAddress, const unsigned char DGBit,
		       const int gammaTestAddress, const unsigned char gammaTestBit,
		       const int directGammaRGBAddress, const DirectGammaType & directGammaType,
		       const int FRCAddress, const unsigned char FRCBit,
                       const int agingAGBSDebugAddress, const unsigned char agingAGBSDebugBit,
                       const int agingModeSelectAddress, const int agingModeSelectValue,
                       const unsigned char agingModeSelectStartBit, const unsigned char agingModeSelectEndBit,
                       const int agingPatternSelectAddress, const unsigned char agingPatternSelectValue,
                       const unsigned char agingPatternSelectStartBit,
                       const unsigned char agingPatternSelectEndBit,
                       const int agingRasterGrayAddress, const DirectGammaType & agingModeType,
                       const int agingManuSelectAddress, const unsigned char agingManuSelectBit,
                       const int DG2Address, const unsigned char DG2Bit, const int DG2LutAddress,
                       const int gammaTest2Address, const unsigned char gammaTest2Bit, const int directGamma2RGBAddress,
                       const int FRC2Address, const unsigned char FRC2Bit,
                       const bool agingTimingControl,
                       const int agingFrameRate, const int agingFrameRateAddress, const unsigned char agingFrameRateStartBit, const unsigned char agingFrameRateEndBit,
                       const int agingMpllModeAddress, const unsigned char agingMpllModeStartBit, const unsigned char agingMpllModeEndBit, const int agingMpllModeValue,
                       const int agingMpllNMSBAddress, const unsigned char agingMpllNMSBStartBit, const unsigned char agingMpllNMSBEndBit, const int agingMpllNLSBAddress, const unsigned char agingMpllNLSBStartBit, const unsigned char agingMpllNLSBEndBit, const int agingMpllNValue,
                       const int agingMpllFMSBAddress, const unsigned char agingMpllFMSBStartBit, const unsigned char agingMpllFMSBEndBit, const int agingMpllFLSBAddress, const unsigned char agingMpllFLSBStartBit, const unsigned char agingMpllFLSBEndBit, const int agingMpllFValue,
                       const int agingMpllMAddress, const unsigned char agingMpllMStartBit, const unsigned char agingMpllMEndBit, const int agingMpllMValue,
                       const int agingHblkMSBAddress, const unsigned char agingHblkMSBStartBit, const unsigned char agingHblkMSBEndBit, const int agingHblkLSBAddress, const unsigned char agingHblkLSBStartBit, const unsigned char agingHblkLSBEndBit, const int agingHblkValue,
                       const int agingVblk1MSBAddress, const unsigned char agingVblk1MSBStartBit, const unsigned char agingVblk1MSBEndBit, const int agingVblk1LSBAddress, const unsigned char agingVblk1LSBStartBit, const unsigned char agingVblk1LSBEndBit, const int agingVblk1Value,
                       const int agingVblk2MSBAddress, const unsigned char agingVblk2MSBStartBit, const unsigned char agingVblk2MSBEndBit, const int agingVblk2LSBAddress, const unsigned char agingVblk2LSBStartBit, const unsigned char agingVblk2LSBEndBit, const int agingVblk2Value
                       );

                       //For PGMode    byBS+
         TCONParameter(const AnsiString tconNumber, const int FRCAddress, const unsigned char FRCBit,
                       const int pgEnableAddress, const unsigned char pgEnableBit,
                       const int pgModeAddress, const unsigned char pgModeStartBit, const unsigned char pgModeEndBit,
                       const int pgPatternMSBAddress, const unsigned char pgPatternMSBStartBit, const unsigned char pgPatternMSBEndBit,
                       const int pgPatternLSBAddress, const unsigned char pgPatternLSBStartBit, const unsigned char pgPatternLSBEndBit,
                       const int pgHblkMSBAddress, const unsigned char pgHblkMSBStartBit, const unsigned char pgHblkMSBEndBit,
                       const int pgHblkLSBAddress, const unsigned char pgHblkLSBStartBit, const unsigned char pgHblkLSBEndBit,
                       const int pgHblkValue,
                       const int pgVblkMSBAddress, const unsigned char pgVblkMSBStartBit, const unsigned char pgVblkMSBEndBit,
                       const int pgVblkLSBAddress, const unsigned char pgVblkLSBStartBit, const unsigned char pgVblkLSBEndBit,
                       const int pgVblkValue);
	 TCONParameter(const AnsiString tconNumber, const Dep::MaxValue & lutBit, const int DGLutAddress, const AnsiString dgLUTType,
                       const int DGAddress,
		       const unsigned char DGBit, const int FRCAddress, const unsigned char FRCBit);

	bool isGammaTestEnable();
        bool isAgingModeEnable();
        bool isPGModeEnable();
	bool isHideEnable();
    };

};

#endif

