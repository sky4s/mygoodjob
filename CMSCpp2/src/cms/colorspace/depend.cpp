#include "depend.h"

#include <limits>

namespace cms {
    namespace colorspace {
	namespace depend {
	    using namespace boost;
	    using namespace std;
	    using namespace java::lang;

	    //======================================================================
	    // DeviceDependentSpace
	    //======================================================================
	    int DeviceDependentSpace::getNumberBands() {
		return 3;
	    };
	    //======================================================================

	    //======================================================================
	    // Channel
	    //======================================================================
	    const Channel & Channel::R =
		Channel::Channel(1, clRed, "R", ChannelIndex::R);
	    const Channel & Channel::G =
		Channel::Channel(2, clGreen, "G", ChannelIndex::G);
	    const Channel & Channel::B =
		Channel::Channel(3, clBlue, "B", ChannelIndex::B);
	    const Channel & Channel::Y =
		Channel::Channel(4, clYellow, "Y", ChannelIndex::Y);
	    const Channel & Channel::M =
		Channel::Channel(5, (TColor) 0xff00ff, "M",
				 ChannelIndex::M);
	    const Channel & Channel::C =
		Channel::Channel(6, (TColor) 0xffff00, "C",
				 ChannelIndex::C);
	    const Channel & Channel::W =
		Channel::Channel(7, clWhite, "W", ChannelIndex::W);

	    const channel_vector_ptr Channel::RGBYMCChannel =
		getChannelVector(6, R, G, B, Y, M, C);
	    const channel_vector_ptr Channel::RGBYMCWChannel =
		getChannelVector(7, R, G, B, Y, M, C, W);
	    const channel_vector_ptr Channel::RGBChannel =
		getChannelVector(3, R, G, B);
	    const channel_vector_ptr Channel::RGBWChannel =
		getChannelVector(4, R, G, B, W);
	    const channel_vector_ptr Channel::WRGBChannel =
		getChannelVector(4, W, R, G, B);
	    const channel_vector_ptr Channel::YMCChannel =
		getChannelVector(3, Y, M, C);


	     Channel::Channel(int index, const TColor & color, string fullname):	/*index(index), */
	     color(color), fullname(fullname) {

	    };
	     Channel::Channel(int index, const TColor & color, string fullname, ChannelIndex chenum):	/*index(index), */
	     color(color), fullname(fullname), chindex(chindex) {

	    };

	    bool Channel::isPrimaryColorChannel(const Channel & channel) {
		return channel == R || channel == G || channel == B;
	    };
	    bool Channel::isSecondaryColorChannel(const Channel & channel) {
		return channel == C || channel == M || channel == Y;
	    };
	    channel_vector_ptr Channel::getChannelVector(int count, ...) {
		channel_vector_ptr result(new channel_vector());
		va_list num_list;
		va_start(num_list, count);

		for (int i = 0; i < count; i++) {
		    Channel & c = va_arg(num_list, Channel);
		    result->push_back(c);
		} va_end(num_list);
		return result;
	    };

	    const string_ptr Channel::toString() const {
		string_ptr str(new string(fullname));
		 return str;
	    };

	    int Channel::getArrayIndex() {
		return chindex - 1;
	    };

	    const Channel & Channel::getChannel(boolean R, boolean G,
						boolean B) {
		int index = 0;
		index += R ? 1 : 0;
		index += G ? 2 : 0;
		index += B ? 3 : 0;
		return getChannel(index);
	    };

	    const Channel & Channel::getChannel(int chIndex) {
		switch (chIndex) {
		case ChannelIndex::R:
		    return R;
		case ChannelIndex::G:
		    return G;
		case ChannelIndex::B:
		    return B;
		case ChannelIndex::Y:
		    return Y;
		case ChannelIndex::M:
		    return M;
		case ChannelIndex::C:
		    return C;
		case ChannelIndex::W:
		    return W;
		    /*default:
		       return NULL; */
		}
	    };
	    const Channel & Channel::getChannelByArrayIndex(int arrayIndex) {
		return getChannel(arrayIndex + 1);
	    };
	    bool Channel::isPrimaryColorChannel() const {
		return isPrimaryColorChannel(*this);
	    };

	    bool Channel::isSecondaryColorChannel() const {
		return isSecondaryColorChannel(*this);
	    };
	    channel_vector_ptr Channel::getBesidePrimaryChannel(const
								Channel &
								primaryColorChannel)
	    {
		switch (primaryColorChannel.chindex) {
		case ChannelIndex::R:
		    return getChannelVector(2, G, B);
		case ChannelIndex::G:
		    return getChannelVector(2, R, B);
		case ChannelIndex::B:
		    return getChannelVector(2, R, G);
		}
	    };
	    //======================================================================
	    //======================================================================
	    // RGBColorSpace
	    //======================================================================
	  RGBColorSpace::RGBColorSpace(const CSType & cstype, const cms::Illuminant & referenceWhite, const double _gamma):_type(cstype), referenceWhite(referenceWhite),
		_gamma(_gamma)
	    {
	    };
	    const RGBColorSpace & RGBColorSpace::unknowRGB =
		RGBColorSpace(CSType::Unknow, Illuminant::D50, 2.2);
	    const RGBColorSpace & RGBColorSpace::sRGB =
		RGBColorSpace(CSType::sRGB, Illuminant::D65, 2.2);
	    //======================================================================

	    //======================================================================
	    // RGBBase
	    //======================================================================
	    double_array RGBBase::
		linearToRGBValues(double_array linearRGBValues,
				  RGBColorSpace rgbColorSpace) {
		double_array rgbValues;
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
	    //======================================================================

	    //======================================================================
	    // MaxValue
	    //======================================================================
	    const MaxValue & MaxValue::Double1 = MaxValue(1.);	//正規化
	    const MaxValue & MaxValue::Double100 = MaxValue(100.);	//正規化
	    const MaxValue & MaxValue::Int5Bit = MaxValue(31., true, false);	//5bit
	    const MaxValue & MaxValue::Int6Bit = MaxValue(63., true, false);	//6bit
	    const MaxValue & MaxValue::Int7Bit = MaxValue(127., true, false);	//7bit
	    const MaxValue & MaxValue::Int8Bit = MaxValue(255., true, true);	//一般常用的RGB code
	    const MaxValue & MaxValue::Double255 = MaxValue(255.);	//各種bit數的RGB code通用
	    const MaxValue & MaxValue::Int9Bit = MaxValue(510., true, true);	//9bit
	    const MaxValue & MaxValue::Double1020 = MaxValue(1020, false, true);	//10bit
	    const MaxValue & MaxValue::Int10Bit = MaxValue(1020, true, true);	//10bit
	    const MaxValue & MaxValue::Int11Bit = MaxValue(2040, true, true);	//11bit
	    const MaxValue & MaxValue::Double4080 = MaxValue(4080, false, true);	//12bit
	    const MaxValue & MaxValue::Int12Bit = MaxValue(4080, true, true);	//12bit
	    const MaxValue & MaxValue::Int13Bit = MaxValue(8160, true, true);	//13bit
	    const MaxValue & MaxValue::Int14Bit = MaxValue(16320, true, true);	//14bit
	    const MaxValue & MaxValue::Int15Bit = MaxValue(32640, true, true);	//15bit
	    const MaxValue & MaxValue::Int16Bit = MaxValue(65280, true, true);	//16bit
	    const MaxValue & MaxValue::Int20Bit = MaxValue(1044480, true, true);	//20bit
	    const MaxValue & MaxValue::Int24Bit = MaxValue(16711680, true, true);	//24bit
	    const MaxValue & MaxValue::Int31Bit = MaxValue(2139095040, true, true);	//31bit
	    const MaxValue & MaxValue::DoubleUnlimited = MaxValue(std::numeric_limits < double >::max());	//無限制

	    MaxValue MaxValue::getIntegerMaxValueByLevel(int level) {
	    };
	    MaxValue MaxValue::getIntegerMaxValueByMax(int max) {
	    };
	    double MaxValue::getStepIn255() {
		return 255. / max;
	    };

	    //======================================================================
	};
    };
};

