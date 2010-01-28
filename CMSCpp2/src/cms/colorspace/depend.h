#ifndef DEPENDH
#define DEPENDH

//C系統文件
#include <cstdarg>
//C++系統文件
#include <string>
#include <vector>
//其他庫頭文件
#include <vcl.h>
//本項目內頭文件
#include <cms/core.h>
#include "colorspace.h"

namespace cms {
    namespace colorspace {

	namespace depend {

	    class DeviceDependentSpace:public ColorSpace {
		int getNumberBands();
	    };

	    enum CSType {
		AdobeRGB, CIERGB, sRGB, sRGB_gamma22, sRGB_gamma18,
		ProPhotoRGB, WideGamutRGB, BetaRGB, BruceRGB, ECIRGB,
		LStarRGB,
		AppleRGB, BestRGB, skyRGB, NTSCRGB, EktaSpacePS5RGB,
		Unknow,
		AdobeRGBD50, AdobeRGB1998, SMPTE_C
	    };
	    class RGBBase;
	    //using cms::Illuminant;
	    class RGBColorSpace {
		friend class RGBBase;
	      private:

		const double _gamma;
		const CSType _type;
		const cms::Illuminant referenceWhite;
		/*RGBColorSpace(CSType csType, Illuminant referenceWhite,
		   double[][]toXYZMatrix,
		   double gamma):_type(csType), _gamma(gamma),
		   referenceWhite(referenceWhite) {
		   this.toXYZMatrix = toXYZMatrix;
		   //this.toRGBMatrix = toXYZMatrix !=;
		   //null ? DoubleArray.inverse(toXYZMatrix) : null;
		   }; */
	      public:
		static const RGBColorSpace unknowRGB;
		static const RGBColorSpace sRGB;
		 RGBColorSpace();
		inline bool operator==(const RGBColorSpace & that) const {
		    return _type == that._type;
		};
	    };


	    class RGBBase:public DeviceDependentSpace {
	      public:
		static boost::shared_array <
		    double >linearToRGBValues(boost::shared_array <
					      double >linearRGBValues,
					      RGBColorSpace rgbColorSpace);
	    };



	    enum Round {
		//尚未執行
		NotYet,
		//四捨五入
		RoundOff,
		//無條件捨去
		RoundDown
	    };

	    class Channel {
	      public:
		static const Channel R;
		static const Channel G;
		static const Channel B;
		static const Channel Y;
		static const Channel M;
		static const Channel C;
		static const Channel W;
	      private:
		int _index;
		TColor _color;
		 std::string _fullname;

		 Channel(int index, TColor color, std::string fullname);

		static bool isPrimaryColorChannel(const Channel & channel);
		static bool isSecondaryColorChannel(const Channel &
						    channel);
		static std::vector < Channel > *getChannelVector(int count,
								 ...);

	      public:
		 inline bool operator==(const Channel & that) const {
		    return _index == that._index;
		};
		inline bool operator!=(const Channel & that) const {
		    return !(_index == that._index);
		};
		 Channel();


		int getArrayIndex();
		static const Channel & getChannel(boolean R, boolean G,
						  boolean B);

		static const Channel & getChannel(int chIndex);
		static const Channel & getChannelByArrayIndex(int
							      arrayIndex);
		boolean isPrimaryColorChannel();
		boolean isSecondaryColorChannel();
		static const std::vector < Channel > &RGBYMCChannel;
		static const std::vector < Channel > &RGBYMCWChannel;
		static const std::vector < Channel > &RGBChannel;
		static const std::vector < Channel > &RGBWChannel;
		static const std::vector < Channel > &WRGBChannel;
		static const std::vector < Channel > &YMCChannel;
	    };


	    class MaxValue {
	      public:
		const double max;
		const bool integer;
		const bool divisible;
	      private:
		 MaxValue(double max):max(max), integer(false),
		    divisible(false) {
		};
		 MaxValue(double max, bool integer,
			  bool divisible):max(max), integer(integer),
		    divisible(divisible) {
		};
	      public:
		static const MaxValue Double1;
		static const MaxValue Double100;
		static const MaxValue Int5Bit;
		static const MaxValue Int6Bit;
		static const MaxValue Int7Bit;
		static const MaxValue Int8Bit;
		static const MaxValue Double255;
		static const MaxValue Int9Bit;
		static const MaxValue Double1020;
		static const MaxValue Int10Bit;
		static const MaxValue Int11Bit;
		static const MaxValue Double4080;
		static const MaxValue Int12Bit;
		static const MaxValue Int13Bit;
		static const MaxValue Int14Bit;
		static const MaxValue Int15Bit;
		static const MaxValue Int16Bit;
		static const MaxValue Int20Bit;
		static const MaxValue Int24Bit;
		static const MaxValue Int31Bit;
		static const MaxValue DoubleUnlimited;

		static MaxValue getIntegerMaxValueByLevel(int level) {
		};
		static MaxValue getIntegerMaxValueByMax(int max) {
		};
		double getStepIn255() {
		    return 255. / max;
		};
	    };
	};


    };
};

#endif

