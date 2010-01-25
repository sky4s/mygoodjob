#ifndef DEPENDH
#define DEPENDH
#include <vcl.h>
#include "colorspace.h"
#include <cms/core.h>
#include <cstdarg>

namespace cms {
    namespace colorspace {


	class DeviceDependentSpace:public ColorSpace {
	};

	enum CSType {
	    AdobeRGB, CIERGB, sRGB, sRGB_gamma22, sRGB_gamma18,
	    ProPhotoRGB,
	    WideGamutRGB, BetaRGB, BruceRGB, ECIRGB, LStarRGB,
	    AppleRGB, BestRGB,
	    skyRGB, NTSCRGB, EktaSpacePS5RGB, Unknow, AdobeRGBD50,
	    AdobeRGB1998,
	    SMPTE_C
	};
	class RGBBase;
	class RGBColorSpace {
	    friend class RGBBase;
	  private:

	    const double _gamma;
	    const CSType _type;
	    const Illuminant referenceWhite;
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
	     RGBColorSpace() {
	    };
	    inline bool operator==(const RGBColorSpace & that) const {
		return _type == that._type;
	    };
	};


	class RGBBase:public DeviceDependentSpace {
	  public:
	    static shared_array <
		double >linearToRGBValues(shared_array <
					  double >linearRGBValues,
					  RGBColorSpace rgbColorSpace) {

		//double[] rgbValues = linearRGBValues.clone();
		shared_array < double >rgbValues;
		boolean negative = false;

		if (rgbColorSpace == RGBColorSpace::sRGB) {
		    for (int x = 0; x < 3; x++) {
			negative = rgbValues[x] < 0;
			if (negative) {
			    rgbValues[x] = -rgbValues[x];
			}

			if (rgbValues[x] <= 0.0031308) {
			    rgbValues[x] *= 12.92;
			} else {
			    rgbValues[x] =
				1.055 * Math::pow(rgbValues[x],
						  1. / 2.4) - 0.055;
			}
			if (negative) {
			    rgbValues[x] = -rgbValues[x];
			}
		    }
		} else {
		    for (int x = 0; x < 3; x++) {
			negative = rgbValues[x] < 0;
			if (negative) {
			    rgbValues[x] = -rgbValues[x];
			}

			rgbValues[x] =
			    Math::pow(rgbValues[x],
				      1. / rgbColorSpace._gamma);

			if (negative) {
			    rgbValues[x] = -rgbValues[x];
			}
		    }
		};

		return rgbValues;
	    };
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
	    string _fullname;

	     Channel(int index, TColor color,
		     string fullname):_index(index), _color(color),
		_fullname(fullname) {

	    };


	    static boolean isPrimaryColorChannel(const Channel & channel) {
		return channel == R || channel == G || channel == B;
	    };
	    static boolean isSecondaryColorChannel(const Channel & channel) {
		return channel == C || channel == M || channel == Y;
	    };
	    static vector < Channel > *getChannelVector(int count, ...) {
		vector < Channel > *result =
		    new vector < Channel > (count);

		va_list num_list;
		va_start(num_list, count);

		for (int i = 0; i < count; i++) {
		    Channel c = va_arg(num_list, Channel);
		    result->push_back(c);
		}

		va_end(num_list);
		return result;
	    };

	  public:
	    inline bool operator==(const Channel & that) const {
		return _index == that._index;
	    };
	    inline bool operator!=(const Channel & that) const {
		return !(_index == that._index);
	    };
	    Channel() {
	    };


	    int getArrayIndex() {
		return _index - 1;
	    };

	    static const Channel & getChannel(boolean R, boolean G,
					      boolean B) {
		int index = 0;
		index += R ? 1 : 0;
		index += G ? 2 : 0;
		index += B ? 3 : 0;
		return getChannel(index);
	    };

	    static const Channel & getChannel(int chIndex) {
		switch (chIndex) {
		case 1:
		    return R;
		case 2:
		    return G;
		case 3:
		    return B;
		case 4:
		    return Y;
		case 5:
		    return M;
		case 6:
		    return C;
		case 7:
		    return W;
		    /*default:
		       return NULL; */
		}
	    };
	    static const Channel & getChannelByArrayIndex(int
							  arrayIndex) {
		return getChannel(arrayIndex + 1);
	    };
	    boolean isPrimaryColorChannel() {
		return isPrimaryColorChannel(*this);
	    };

	    boolean isSecondaryColorChannel() {
		return isSecondaryColorChannel(*this);
	    };
	    static const vector < Channel > &RGBYMCChannel;
	    static const vector < Channel > &RGBYMCWChannel;
	    static const vector < Channel > &RGBChannel;
	    static const vector < Channel > &RGBWChannel;
	    static const vector < Channel > &WRGBChannel;
	    static const vector < Channel > &YMCChannel;
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


	class RGBColor:public RGBBase {
	  public:
	    double R, G, B;

	     RGBColor():_rgbColorSpace(RGBColorSpace::unknowRGB),
		_maxValue(MaxValue::Double1) {
	    };
	    RGBColor(RGBColorSpace & rgbColorSpace,
		     shared_array < double >rgb,
		     MaxValue &
		     maxValue):_rgbColorSpace(rgbColorSpace),
		_maxValue(maxValue) {

		if (rgb != NULL) {
		    setValues(rgb);
		}
	    };
	    RGBColor(int r, int g,
		     int b):_rgbColorSpace(RGBColorSpace::unknowRGB),
		_maxValue(MaxValue::Int8Bit) {
		setValues(r, g, b);
	    };
	  RGBColor(RGBColorSpace rgbColorSpace, CIEXYZ XYZ):_rgbColorSpace(rgbColorSpace),
		_maxValue(MaxValue::
			  Double1) {
		//this(colorSpace, fromXYZValues(XYZ.getValues(), colorSpace),
		//MaxValue.Double1);
	    }

	    /*static shared_array<double> fromXYZValues(shared_array<double> XYZValues,
	       RGBBColorSpace rgbColorSpace) {
	       double[] linearRGBValues = XYZ2LinearRGBValues(XYZValues, colorSpace);
	       double[] rgbValues = linearToRGBValues(linearRGBValues, colorSpace);

	       return rgbValues;
	       } */
	  protected:
	    MaxValue _maxValue;
	    RGBColorSpace _rgbColorSpace;
	};
    };
};
#endif

