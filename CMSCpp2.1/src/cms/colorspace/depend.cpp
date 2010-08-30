#include <includeall.h>
#pragma hdrstop
#include "depend.h"

//C系統文件
#include <cstdarg>
//C++系統文件
#include <limits>
#include <iostream>
//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace colorspace {
	namespace depend {
	    using namespace boost;
	    using namespace std;
	    using namespace java::lang;
	    using namespace math;

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
	    const Channel & Channel::R = Channel::Channel(1, clRed, "R", ChannelIndex::R);
	    const Channel & Channel::G = Channel::Channel(2, clGreen, "G", ChannelIndex::G);
	    const Channel & Channel::B = Channel::Channel(3, clBlue, "B", ChannelIndex::B);
	    const Channel & Channel::Y = Channel::Channel(4, clYellow, "Y", ChannelIndex::Y);
	    const Channel & Channel::M = Channel::Channel(5, (TColor) 0xff00ff, "M",
							  ChannelIndex::M);
	    const Channel & Channel::C = Channel::Channel(6, (TColor) 0xffff00, "C",
							  ChannelIndex::C);
	    const Channel & Channel::W = Channel::Channel(7, clWhite, "W", ChannelIndex::W);

	    const Channel_vector_ptr Channel::RGBYMCChannel = getChannelVector(6, R, G, B, Y, M, C);
	    const Channel_vector_ptr Channel::RGBYMCWChannel =
		getChannelVector(7, R, G, B, Y, M, C, W);
	    const Channel_vector_ptr Channel::RGBChannel = getChannelVector(3, R, G, B);
	    const Channel_vector_ptr Channel::RGBWChannel = getChannelVector(4, R, G, B, W);
	    const Channel_vector_ptr Channel::WRGBChannel = getChannelVector(4, W, R, G, B);
	    const Channel_vector_ptr Channel::YMCChannel = getChannelVector(3, Y, M, C);


	    /*Channel::Channel(int index, const TColor & color, string fullname):
	       color(color), fullname(fullname) {

	       }; */
	     Channel::Channel(int index, const TColor & color, string fullname, const ChannelIndex chindex):	/*index(index), */
	     color(color), fullname(fullname), chindex(chindex) {
		//std::cout << fullname << " " << chindex << std::endl;
	    };

	    bool Channel::isPrimaryColorChannel(const Channel & channel) {
		return channel == R || channel == G || channel == B;
	    };
	    bool Channel::isSecondaryColorChannel(const Channel & channel) {
		return channel == C || channel == M || channel == Y;
	    };
	    Channel_vector_ptr Channel::getChannelVector(int count, ...) {
		Channel_vector_ptr result(new Channel_vector());
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

	    const int Channel::getArrayIndex() const {
		return chindex - 1;
	    };

	    const Channel & Channel::getChannel(boolean R, boolean G, boolean B) {
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
		default:
		    throw IllegalArgumentException("Unsupported chIndex:" + chIndex);
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
	    Channel_vector_ptr Channel::getBesidePrimaryChannel(const Channel & primaryColorChannel) {
		switch (primaryColorChannel.chindex) {
		case ChannelIndex::R:
		    return getChannelVector(2, G, B);
		case ChannelIndex::G:
		    return getChannelVector(2, R, B);
		case ChannelIndex::B:
		    return getChannelVector(2, R, G);
		default:
		    throw IllegalArgumentException("Unsupported Channel: "
						   + *primaryColorChannel.toString());
		}
	    };
	    //======================================================================
	    //======================================================================
	    // RGBColorSpace
	    //======================================================================
	    RGBColorSpace::RGBColorSpace(const CSType & type,
					 const cms::
					 Illuminant & referenceWhite,
					 const double gamma):type_(type),
		referenceWhite(referenceWhite), gamma_(gamma) {
	    };
	    RGBColorSpace::RGBColorSpace(const CSType & type,
					 const cms::
					 Illuminant & referenceWhite,
					 double toXYZMatrix[9],
					 const double gamma):type_(type),
		referenceWhite(referenceWhite), gamma_(gamma) {

		toXYZMatrix_ = double2D_ptr(new double2D(3, 3, toXYZMatrix));
		toRGBMatrix_ = DoubleArray::inverse(toXYZMatrix_);
	    };
	    RGBColorSpace::RGBColorSpace(const CSType & type,
					 const double gamma,
					 const cms::
					 Illuminant & referenceWhite,
					 ...):type_(type),
		referenceWhite(referenceWhite), gamma_(gamma) {
		const int n = 9;
		double array[n];
		va_list num_list;
		va_start(num_list, n);

		for (int i = 0; i < n; i++) {
		    const double d = va_arg(num_list, const double);
		    array[i] = d;
		} va_end(num_list);
		toXYZMatrix_ = double2D_ptr(new double2D(3, 3, array));
		toRGBMatrix_ = DoubleArray::inverse(toXYZMatrix_);
	    };
	    const RGBColorSpace & RGBColorSpace::unknowRGB =
		RGBColorSpace(CSType::Unknow, Illuminant::D50, 2.2);
	    const RGBColorSpace & RGBColorSpace::sRGB =
		RGBColorSpace(CSType::sRGB, 2.2, Illuminant::D65,
			      0.412424, 0.212656, 0.0193324,
			      0.357579, 0.715158, 0.119193,
			      0.180464, 0.0721856, 0.950444);
	    const RGBColorSpace & RGBColorSpace::sRGB_gamma22 =
		RGBColorSpace(CSType::sRGB_gamma22, 2.2, Illuminant::D65,
			      0.412424, 0.212656, 0.0193324,
			      0.357579, 0.715158, 0.119193,
			      0.180464, 0.0721856, 0.950444);
	    /*const RGBColorSpace & RGBColorSpace::NTSCRGB =
	       RGBColorSpace(CSType::NTSCRGB, 2.2, Illuminant::C,
	       0.606734, 0.298839, 0.000000,
	       0.173564, 0.586811, 0.0661196,
	       0.200112, 0.114350, 1.11491); */
	    //======================================================================

	    //======================================================================
	    // RGBBase
	    //======================================================================
	    double_array RGBBase::
		linearToRGBValues(double_array linearRGBValues, RGBColorSpace rgbColorSpace) {
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
			    rgbValues[x] = 1.055 * Math::pow(rgbValues[x], 1. / 2.4) - 0.055;
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

			rgbValues[x] = Math::pow(rgbValues[x], 1. / rgbColorSpace.gamma_);

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

	    bptr < MaxValue_vector > MaxValue::make(int count,...) {
		bptr < MaxValue_vector > result(new MaxValue_vector());
		va_list num_list;
		va_start(num_list, count);

		for (int i = 0; i < count; i++) {
		    const MaxValue & m = va_arg(num_list, const MaxValue);
		    result->push_back(m);
		} va_end(num_list);
		return result;
	    };

	    const MaxValue & MaxValue::Double1 = MaxValue(1.);	//正規化
	    const MaxValue & MaxValue::Double100 = MaxValue(100.);	//正規化
	    const MaxValue & MaxValue::Int5Bit = MaxValue(31., true, false, 5);	//5bit
	    const MaxValue & MaxValue::Int6Bit = MaxValue(63., true, false, 6);	//6bit
	    const MaxValue & MaxValue::Int7Bit = MaxValue(127., true, false, 7);	//7bit
	    const MaxValue & MaxValue::Int8Bit = MaxValue(255., true, true, 8);	//一般常用的RGB code
	    const MaxValue & MaxValue::Double255 = MaxValue(255.);	//各種bit數的RGB code通用
	    const MaxValue & MaxValue::Int9Bit = MaxValue(510., true, true, 9);	//9bit
	    const MaxValue & MaxValue::Double1020 = MaxValue(1020, false, true, -1);	//10bit
	    const MaxValue & MaxValue::Int10Bit = MaxValue(1020, true, true, 10);	//10bit
	    const MaxValue & MaxValue::RealInt10Bit = MaxValue(1023, true, true, 10);	//real 10bit
	    const MaxValue & MaxValue::Int11Bit = MaxValue(2040, true, true, 11);	//11bit
	    const MaxValue & MaxValue::Double4080 = MaxValue(4080, false, true, -1);	//12bit
	    const MaxValue & MaxValue::Int12Bit = MaxValue(4080, true, true, 12);	//12bit
	    const MaxValue & MaxValue::Real12Bit = MaxValue(4095, true, true, 12);	//12bit            
	    const MaxValue & MaxValue::Int13Bit = MaxValue(8160, true, true, 13);	//13bit
	    const MaxValue & MaxValue::Int14Bit = MaxValue(16320, true, true, 14);	//14bit
	    const MaxValue & MaxValue::Int15Bit = MaxValue(32640, true, true, 15);	//15bit
	    const MaxValue & MaxValue::Int16Bit = MaxValue(65280, true, true, 16);	//16bit
	    const MaxValue & MaxValue::Int20Bit = MaxValue(1044480, true, true, 20);	//20bit
	    const MaxValue & MaxValue::Int24Bit = MaxValue(16711680, true, true, 24);	//24bit
	    const MaxValue & MaxValue::Int31Bit = MaxValue(2139095040, true, true, 31);	//31bit
	    const MaxValue & MaxValue::DoubleUnlimited = MaxValue(std::numeric_limits < double >::max());	//無限制

	    const bptr < MaxValue_vector > MaxValue::MaxValueVector =
		MaxValue::make(15, Int5Bit, Int6Bit, Int7Bit, Int8Bit,
			       Int9Bit, Int10Bit, RealInt10Bit, Int11Bit,
			       Int12Bit, Int13Bit, Int14Bit, Int15Bit,
			       Int16Bit, Int20Bit, Int24Bit);

	    MaxValue MaxValue::getIntegerMaxValueByLevel(int level) {
		/* TODO : getIntegerMaxValueByLevel */
	    };
	    MaxValue MaxValue::getIntegerMaxValueByMax(int max) {
		/* TODO : getIntegerMaxValueByMax */
	    };
	    double MaxValue::getStepIn255() {
		return 255. / max;
	    };

	    const MaxValue & MaxValue::getByIntegerBit(int bit) {
		foreach(const MaxValue & m, *MaxValueVector) {
		    if (true == m.integer && m.bit == bit) {
			return m;
		    }
		}
		throw IllegalStateException("");
	    };
	    const string_ptr MaxValue::toString() const {
		return string_ptr(new
				  string((integer ? "Int" : "Double") + _toString(bit) + "Bit"));
	    };
	    const MaxValue & MaxValue::valueOf(string_ptr stringValue) {
		if (*stringValue == "Int5Bit") {
		    return Int5Bit;
		} else if (*stringValue == "Int6Bit" || *stringValue == "6bit") {
		    return Int6Bit;
		} else if (*stringValue == "Int7Bit") {
		    return Int7Bit;
		} else if (*stringValue == "Int8Bit" || *stringValue == "8bit") {
		    return Int8Bit;
		} else if (*stringValue == "Int9Bit") {
		    return Int9Bit;
		} else if (*stringValue == "Int10Bit" || *stringValue == "10bit") {
		    return Int10Bit;
		} else if (*stringValue == "Int11Bit") {
		    return Int11Bit;
		} else if (*stringValue == "Int12Bit") {
		    return Int12Bit;
		} else {
		    throw IllegalArgumentException();
		}
	    }
	    //======================================================================
	};
    };
};

