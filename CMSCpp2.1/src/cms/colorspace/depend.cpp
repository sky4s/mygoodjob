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
	    double_array DeviceDependentSpace::
		XYZ2LinearRGBValues(double_array XYZValues, const RGBColorSpace & colorSpace) {
		double2D_ptr aM = colorSpace.toRGBMatrix;
		double2D_ptr rgbValues =
		    DoubleArray::times(DoubleArray::toDouble2D(XYZValues, 3), aM);

		 return DoubleArray::toDoubleArray(rgbValues);
	    };
	    RGB_ptr DeviceDependentSpace::XYZ2LinearRGB(XYZ_ptr XYZ,
							const RGBColorSpace & colorSpace) {
		double_array rgbValues = XYZ2LinearRGBValues(XYZ->getValues(), colorSpace);
		RGB_ptr rgb(new RGBColor(colorSpace, rgbValues, MaxValue::Double1));
		 return rgb;
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
		}
		va_end(num_list);
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

	    const RGBColorSpace RGBColorSpace::unknowRGB =
		RGBColorSpace(CSType::Unknow, Illuminant::D50, 2.2);
	    const RGBColorSpace RGBColorSpace::sRGB =
		RGBColorSpace(CSType::sRGB, Illuminant::D65, 2.2, 0.64, 0.33, 0.30, 0.60, 0.15,
			      0.06);
	    const RGBColorSpace RGBColorSpace::sRGB_gamma22 =
		RGBColorSpace(CSType::sRGB_gamma22, Illuminant::D65, 2.2,
			      0.64, 0.33, 0.30, 0.60, 0.15, 0.06);
	    /*const RGBColorSpace RGBColorSpace::getsRGBGamma22() {
	       const RGBColorSpace sRGB_gamma22(CSType::sRGB_gamma22, Illuminant::D65, 2.2,
	       0.64, 0.33, 0.30, 0.60, 0.15, 0.06);
	       return sRGB_gamma22;
	       }; */
	    RGBColorSpace::RGBColorSpace(const CSType & _type,
					 const cms::Illuminant & _referenceWhite,
					 const double _gamma):type(_type),
		referenceWhite(_referenceWhite), gamma(_gamma) {
	    };
	    RGBColorSpace::RGBColorSpace(const CSType & _type,
					 const cms::
					 Illuminant & _referenceWhite,
					 double _toXYZMatrix[9],
					 const double _gamma):type(_type),
		referenceWhite(_referenceWhite), gamma(_gamma) {

		toXYZMatrix = double2D_ptr(new double2D(3, 3, _toXYZMatrix));
		toRGBMatrix = DoubleArray::inverse(toXYZMatrix);
	    };
	    RGBColorSpace::RGBColorSpace(const CSType & _type,
					 const cms::
					 Illuminant & _referenceWhite,
					 double2D_ptr _toXYZMatrix,
					 const double _gamma):type(_type),
		referenceWhite(_referenceWhite), gamma(_gamma) {
		toXYZMatrix = _toXYZMatrix;
		toRGBMatrix = DoubleArray::inverse(toXYZMatrix);
	    };
	    RGBColorSpace::RGBColorSpace(const CSType & _type,
					 const cms::Illuminant & _referenceWhite,
					 const double _gamma, double m0, double m1, double m2,
					 double m3, double m4, double m5, double m6, double m7,
					 double m8):type(_type), referenceWhite(_referenceWhite),
		gamma(_gamma) {
		double array[9];
		array[0] = m0;
		array[1] = m1;
		array[2] = m2;
		array[3] = m3;
		array[4] = m4;
		array[5] = m5;
		array[6] = m6;
		array[7] = m7;
		array[8] = m8;

		this->toXYZMatrix = double2D_ptr(new double2D(3, 3, array));
		this->toRGBMatrix = DoubleArray::inverse(toXYZMatrix);
	    };
	    RGBColorSpace::RGBColorSpace(const CSType & _type,
					 const cms::Illuminant & _referenceWhite,
					 const double _gamma, double _rx, double _ry, double _gx,
					 double _gy, double _bx, double _by):rx(_rx), ry(_ry),
		gx(_gx), gy(_gy), bx(_bx), by(_by), type(_type), referenceWhite(_referenceWhite),
		gamma(_gamma) {
		this->referenceWhiteXYZ = referenceWhite.getXYZ();
		double_array whiteXYZValues = referenceWhiteXYZ->getValues();
		this->toXYZMatrix =
		    RGBBase::calculateRGBXYZMatrix(rx, ry, gx, gy, bx, by, whiteXYZValues);
		if (toXYZMatrix != null) {
		    this->toRGBMatrix = DoubleArray::inverse(toXYZMatrix);
		}
	    };
	    /*const RGBColorSpace & RGBColorSpace::NTSCRGB =
	       RGBColorSpace(CSType::NTSCRGB, 2.2, Illuminant::C,
	       0.606734, 0.298839, 0.000000,
	       0.173564, 0.586811, 0.0661196,
	       0.200112, 0.114350, 1.11491); */
	    XYZ_ptr RGBColorSpace::getReferenceWhiteXYZ() {
		return referenceWhiteXYZ;
	    };
	    //======================================================================
	    //======================================================================
	    // RGBBase
	    //======================================================================
	    double_array RGBBase::
		linearToRGBValues(double_array linearRGBValues, RGBColorSpace rgbColorSpace) {
		double_array rgbValues = DoubleArray::arraycopy(linearRGBValues,
								3);
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

			rgbValues[x] = Math::pow(rgbValues[x], 1. / rgbColorSpace.gamma);
			if (negative) {
			    rgbValues[x] = -rgbValues[x];
			}
		    }
		};
		return rgbValues;
	    };
	    double_array RGBBase::linearToRGBValues(double_array linearRGBValues, double gamma) {
		double_array rgbValues(new double[3]);
		boolean negative = false;
		for (int x = 0; x < 3; x++) {
		    negative = rgbValues[x] < 0;
		    if (negative) {
			rgbValues[x] = -rgbValues[x];
		    }

		    rgbValues[x] = Math::pow(rgbValues[x], 1. / gamma);
		    if (negative) {
			rgbValues[x] = -rgbValues[x];
		    }
		}


		return rgbValues;
	    };
	    double_array RGBBase::toLinearRGBValues(double_array rgbValues, double gamma) {
		double_array linearRGBValues = DoubleArray::arraycopy(rgbValues, 3);
		boolean negative = false;
		for (int x = 0; x < 3; x++) {
		    negative = linearRGBValues[x] < 0;
		    if (negative) {
			linearRGBValues[x] = -linearRGBValues[x];
		    }

		    linearRGBValues[x] = Math::pow(linearRGBValues[x], gamma);
		    if (negative) {
			linearRGBValues[x] = -linearRGBValues[x];
		    }
		}

		return linearRGBValues;
	    };
	    double2D_ptr RGBBase::
		calculateRGBXYZMatrix(xyY_ptr r, xyY_ptr g, xyY_ptr b, XYZ_ptr white) {
		return calculateRGBXYZMatrix(r->x, r->y,
					     g->x, g->y, b->x, b->y, white->getValues());
	    };
	    double2D_ptr RGBBase::
		calculateRGBXYZMatrix(double rx,
				      double ry,
				      double gx,
				      double gy,
				      double bx, double by, double_array whiteXYZValues) {
		double2D_ptr matrix(new double2D(3, 3));
		(*matrix)[0][0] = rx / ry;
		(*matrix)[0][1] = 1;
		(*matrix)[0][2] = (1 - rx - ry) / ry;
		(*matrix)[1][0] = gx / gy;
		(*matrix)[1][1] = 1;
		(*matrix)[1][2] = (1 - gx - gy) / gy;
		(*matrix)[2][0] = bx / by;
		(*matrix)[2][1] = 1;
		(*matrix)[2][2] = (1 - bx - by) / by;
		double2D_ptr inv = DoubleArray::inverse(matrix);
		double2D_ptr S = DoubleArray::times(DoubleArray::toDouble2D(whiteXYZValues, 3),
						    inv);
		for (int x = 0; x < 3; x++) {
		    double s = (*S)[0][x];
		    (*matrix)[x][0] *= s;
		    (*matrix)[x][1] *= s;
		    (*matrix)[x][2] *= s;
		}
		return matrix;
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
		}
		va_end(num_list);
		return result;
	    };
	    const MaxValue & MaxValue::Double1 = MaxValue(1.);	//正規化
	    const MaxValue & MaxValue::Double100 = MaxValue(100.);	//正規化
	    const MaxValue & MaxValue::Int5Bit = MaxValue(31., true, false, 5);	//5bit
	    const MaxValue & MaxValue::Int6Bit = MaxValue(63., true, false, 6);	//6bit
	    const MaxValue & MaxValue::Int7Bit = MaxValue(127., true, false, 7);	//7bit
	    const MaxValue & MaxValue::Int8Bit = MaxValue(255., true, true, 8);	//一般常用的RGB code
	    const MaxValue & MaxValue::Double255 = MaxValue(255.);	//各種bit數的RGB code通用
	    const MaxValue & MaxValue::Double256 = MaxValue(256.);	//各種bit數的RGB code通用
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
	    const bptr < MaxValue_vector >
		MaxValue::MaxValueVector = MaxValue::make(15, Int5Bit, Int6Bit,
							  Int7Bit, Int8Bit, Int9Bit,
							  Int10Bit, RealInt10Bit,
							  Int11Bit, Int12Bit,
							  Int13Bit, Int14Bit,
							  Int15Bit, Int16Bit,
							  Int20Bit, Int24Bit);
	    MaxValue MaxValue::getIntegerMaxValueByLevel(int level) {
		/* TODO : getIntegerMaxValueByLevel */
		return null;
	    };
	    MaxValue MaxValue::getIntegerMaxValueByMax(int max) {
		/* TODO : getIntegerMaxValueByMax */
		return null;
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

	    RGBBasis::RGBBasis(const RGBColorSpace & colorSpace):rgbColorSpace(&colorSpace) {

	    };
	  RGBBasis::RGBBasis(RGB_ptr rgb):rgbColorSpace(&rgb->getRGBColorSpace()) {
	    };
	    const RGBColorSpace & RGBBasis::getRGBColorSpace() {
		return *rgbColorSpace;
	    };
	    //======================================================================
	  ColorAppearanceBase::ColorAppearanceBase(const RGBColorSpace & colorSpace, int_array lshIndex):RGBBasis(colorSpace),
		lshIndex(lshIndex)
	    {
	    };
	  ColorAppearanceBase::ColorAppearanceBase(RGB_ptr rgb, int_array lshIndex):RGBBasis(rgb),
		lshIndex
		(lshIndex) {
	    };
	    double_array ColorAppearanceBase::getCartesianCoordinatesValues() {
		return polar2cartesianCoordinatesValues(getLSHValues());
	    };
	    double_array ColorAppearanceBase::getLSHValues() {
		double_array values = getValues();
		double_array result(new double[3]);
		result[0] = values[lshIndex[0]];
		result[1] = values[lshIndex[1]];
		result[2] = values[lshIndex[2]];
		return result;
	    };
	    void ColorAppearanceBase::setLSHValues(double_array LSHValues) {
		this->setValues(LSHValues[lshIndex[0]],
				LSHValues[lshIndex[1]], LSHValues[lshIndex[2]]);
	    };
	    //======================================================================
	    //======================================================================
	    // HSV
	    //======================================================================
	    HSV::HSV(const RGBColorSpace & colorSpace,
		     double_array hsvValues):ColorAppearanceBase(colorSpace, lshIndex) {
		this->setValues(hsvValues);
	    };
	    HSV::HSV(const RGBColorSpace & colorSpace, double h, double s, double
		     v):ColorAppearanceBase(colorSpace, lshIndex) {
		this->setValues(h, s, v);
	    };
	  HSV::HSV(RGB_ptr rgb):ColorAppearanceBase(rgb, lshIndex) {
		this->setValues(this->_fromRGB(rgb));
	    };
	    double_array HSV::fromRGBValues(double_array rgbValues) {
		double h, s, v;
		double r = rgbValues[0];
		double g = rgbValues[1];
		double b = rgbValues[2];
		//i = (r + g + b) / 3;
		double max = Math::max(r, g);
		max = Math::max(b, max);
		v = max;
		double min = Math::min(r, g);
		min = Math::min(b, min);
		double d = max - min;
		s = d;
		d = (d == 0 ? d + 256 : d);
		if (max == 0) {
		    s = 0;
		} else {
		    s = s / max;
		}

		if (s == 0) {
		    h = 0;
		} else {
		    if (max == r)
			h = 60 * (g - b) / d;
		    else if (max == g)
			h = 60 * (b - r) / d + 120;
		    else if (max == b)
			h = 60 * (r - g) / d + 240;
		    h = Math::fmod(h + 360, 360);
		}
		double_array hsvValues(new double[3]);
		hsvValues[0] = h;
		hsvValues[1] = s * 100;
		hsvValues[2] = v / 255. * 100;
		//hsviValues[3] = i;
		return hsvValues;
	    };
	    string_vector_ptr HSV::getBandNames() {
		string_vector_ptr names(new string_vector(3));
		(*names)[0] = "H";
		(*names)[1] = "S";
		(*names)[2] = "V";
		return names;
	    };
	    RGB_ptr HSV::toRGB() {
		double_array rgbValues = toRGBValues(getValues());
		RGB_ptr rgb(new RGBColor(*rgbColorSpace, rgbValues, MaxValue::Double255));
		return rgb;
	    };
	    /*
	       hue = hsvValues[0] = 0~360
	       saturation = hsvValues[1] = 0~100
	       value = hsvValues[2] = 0~100
	     */
	    double_array HSV::toRGBValues(double_array hsvValues) {
		//double s0 = hsvValues[1];
		//double v0 = hsvValues[2];

		double h = hsvValues[0];	//eat 0~360
		double s = hsvValues[1] / 100;	//eat 0~100 to 0~1
		double v = hsvValues[2] / 100 * 255;	//eat 0~100 to 0~255
		double r, g, b;
		s = (s < 0 ? 0 : s);
		s = (s > 1 ? 1 : s);
		v = (v < 0 ? 0 : v);
		v = (v > 255 ? 255 : v);
		h = (h > 360 ? 360 : h);
		h = (h < 0 ? h + 360 : h);
		int hi = (int) (Math::floor(h / 60)) % 6;
		double f = h / 60 - Math::floor(h / 60);
		double p = v * (1 - s);
		double q = v * (1 - f * s);
		double t = v * (1 - (1 - f) * s);
		if (hi == 0) {
		    r = v;
		    g = t;
		    b = p;
		} else if (hi == 1) {
		    r = q;
		    g = v;
		    b = p;
		} else if (hi == 2) {
		    r = p;
		    g = v;
		    b = t;
		} else if (hi == 3) {
		    r = p;
		    g = q;
		    b = v;
		} else if (hi == 4) {
		    r = t;
		    g = p;
		    b = v;
		} else if (hi == 5) {
		    r = v;
		    g = p;
		    b = q;
		}
		double_array rgbValues(new double[3]);
		rgbValues[0] = r;
		rgbValues[1] = g;
		rgbValues[2] = b;
		return rgbValues;
	    };
	    int_array HSV::lshIndex = initLSHIndex();
	    int_array HSV::initLSHIndex() {
		int_array index(new int[3]);
		index[0] = 2;
		index[1] = 1;
		index[2] = 0;
		return index;
	    };
	    double_array HSV::getHSVIValues() {
		double_array rgbValues = toRGBValues(getValues());
		double_array hsviValues = getHSVIValues(rgbValues);
		/*double_array hsviValues(new double[4]);
		   hsviValues[0] = this->H;
		   hsviValues[1] = S;
		   hsviValues[2] = V;
		   hsviValues[3] = (rgbValues[0] + rgbValues[1] + rgbValues[2]) / 3.; */
		return hsviValues;
	    };
	    double_array HSV::getHSVIValues(double_array rgbValues) {
		double_array hsvValues = fromRGBValues(rgbValues);
		double_array hsviValues(new double[4]);
		hsviValues[0] = hsvValues[0];
		hsviValues[1] = hsvValues[1];
		hsviValues[2] = hsvValues[2];
		hsviValues[3] = (rgbValues[0] + rgbValues[1] + rgbValues[2]) / 3.;
		return hsviValues;
	    };
	    double_array HSV::_fromRGB(RGB_ptr rgb) {
		double_array rgbValues(new double[3]);
		rgb->getValues(rgbValues, MaxValue::Double255);
		double_array hsvValues = fromRGBValues(rgbValues);
		return hsvValues;
	    };
	    double_array HSV::_getValues(double_array values) {
		values[0] = H;
		values[1] = S;
		values[2] = V;
		return values;
	    };
	    void HSV::_setValues(double_array values) {
		H = values[0];
		S = values[1];
		V = values[2];
	    };
	    //======================================================================
	};
    };
};

