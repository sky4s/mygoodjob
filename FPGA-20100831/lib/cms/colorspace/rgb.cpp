#include "rgb.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <math/doublearray.h>

namespace cms {
    namespace colorspace {
	namespace depend {
	    using namespace java::lang;
	    using namespace std;
	    using namespace boost;
	    using namespace math;
	    //======================================================================
	    // RGBColor
	    //======================================================================
	     RGBColor::RGBColor():rgbColorSpace(&RGBColorSpace::unknowRGB),
		maxValue(&MaxValue::Double1) {
		setValues(0, 0, 0);
	    };
	     RGBColor::RGBColor(const MaxValue &
				maxValue):rgbColorSpace(&RGBColorSpace::
							unknowRGB), maxValue(&maxValue) {
		setValues(0, 0, 0);
	    };
	     RGBColor::RGBColor(const RGBColorSpace & rgbColorSpace,
				double_array rgb,
				const MaxValue &
				maxValue):rgbColorSpace(&rgbColorSpace), maxValue(&maxValue) {

		if (rgb != null) {
		    setValues(rgb);
		}
	    };
	    RGBColor::RGBColor(int r, int g, int b):rgbColorSpace(&RGBColorSpace::
								  unknowRGB),
		maxValue(&MaxValue::Int8Bit) {
		setValues(r, g, b);
	    };
	    RGBColor::RGBColor(double r, double g, double b,
			       const MaxValue & maxValue):rgbColorSpace(&RGBColorSpace::unknowRGB),
		maxValue(&maxValue) {
		setValues(r, g, b);
	    };
	    RGBColor::RGBColor(double r, double g, double b):rgbColorSpace(&RGBColorSpace::
									   unknowRGB),
		maxValue(&MaxValue::Double255) {
		setValues(r, g, b);
	    };

	    /* TODO : RGBColor */
	    /*RGBColor::RGBColor(const RGBColorSpace & rgbColorSpace,
	       XYZ_ptr XYZ):rgbColorSpace(&rgbColorSpace),
	       maxValue(&MaxValue::Double1) {

	       //this(colorSpace, fromXYZValues(XYZ.getValues(), colorSpace),
	       //MaxValue.Double1);
	       }; */


	    double_array RGBColor::_getValues(double_array values) {
		values[0] = R;
		values[1] = G;
		values[2] = B;
		return values;

	    };

	    void RGBColor::_setValues(double_array values) {
		R = values[0];
		G = values[1];
		B = values[2];
	    };

	    string_vector_ptr RGBColor::getBandNames() {
		string_vector_ptr vec(new string_vector(3));

		(*vec)[0] = "R";
		(*vec)[1] = "G";
		(*vec)[2] = "B";
		return vec;
	    };
	    /*static shared_array<double> fromXYZValues(shared_array<double> XYZValues,
	       RGBBColorSpace rgbColorSpace) {
	       double[] linearRGBValues = XYZ2LinearRGBValues(XYZValues, colorSpace);
	       double[] rgbValues = linearToRGBValues(linearRGBValues, colorSpace);

	       return rgbValues;
	       } */
	    //======================================================================

	    void RGBColor::changeMaxValue(const MaxValue & type, bool integerRoundDown) {
		// 類型一樣不需要轉換 || 無限制類型無法進行轉換
		if (*this->maxValue == type ||
		    *this->maxValue == MaxValue::DoubleUnlimited ||
		    type == MaxValue::DoubleUnlimited) {
		    return;
		}

		double_array values = this->getValues();
		changeMaxValue(values, *this->maxValue, type, integerRoundDown);

		this->maxValue = &type;
		this->setValues(values);
	    };

	    void RGBColor::changeMaxValue(const MaxValue & type) {
		changeMaxValue(type, false);
	    };

	    void RGBColor::changeMaxValue(double_array values,
					  const MaxValue & srcType,
					  const MaxValue & destType, bool integerRoundDown) {
		if (srcType.integer == true || destType.integer == true) {
		    changeIntegerMaxValue(values, srcType, destType, integerRoundDown);
		} else {
		    values = normalizeTo100(values, srcType);
		    changeMaxValue(values, destType, integerRoundDown);
		}
	    };

	    double_array RGBColor::
		changeIntegerMaxValue(double_array integerValues,
				      const MaxValue & srcType,
				      const MaxValue & destType, bool roundDown) {
		if (false == srcType.integer && false == destType.integer) {
		    //既然是處理整數的轉換, 當然至少要有一個是整數啦~
		    throw IllegalArgumentException
			("false == srcType.integer && false == destType.integer");
		}
		double rate = -1;

		if (true == srcType.integer && false == srcType.divisible && destType.max == 255) {
		    //處理小於8bit, 也就是沒辦法整除的部份
		    rate = (destType.max + 1) / srcType.max;
		} else if (true == destType.integer
			   && false == destType.divisible && srcType.max == 255) {
		    //處理小於8bit, 也就是沒辦法整除的部份
		    rate = destType.max / (srcType.max + 1);
		} else {
		    rate = destType.max / srcType.max;
		}
		//int size = integerValues.length;
		int size = RGBNumberBands;

		for (int x = 0; x < size; x++) {
		    integerValues[x] *= rate;
		    integerValues[x] = destType.integer ?
			(roundDown ? (int) integerValues[x] : Math::
			 roundTo(integerValues[x])) : integerValues[x];
		    //小於8bit的轉換, 會有超過max的狀況, 所以要作clip
		    integerValues[x] =
			(integerValues[x] > destType.max) ? destType.max : integerValues[x];
		}

		return integerValues;
	    };

	    double_array RGBColor::changeMaxValue(double_array normal100,
						  const MaxValue & type, bool integerRoundDown) {
		int size = RGBNumberBands;

		if (type.integer == true) {
		    for (int x = 0; x < size; x++) {
			normal100[x] /= (100. / type.max);
			normal100[x] =
			    integerRoundDown ? (int) normal100[x] : Math::roundTo(normal100[x]);
		    }
		} else {
		    for (int x = 0; x < size; x++) {
			normal100[x] /= (100. / type.max);
		    }

		}
		return normal100;
	    };


	    double_array RGBColor::normalizeTo100(double_array values, const MaxValue & maxValue) {
		double max = maxValue.max;
		//int size = values.length;
		int size = RGBNumberBands;
		for (int x = 0; x < size; x++) {
		    values[x] = values[x] / max * 100;
		};
		return values;
	    };

	    void RGBColor::addValue(const Channel & channel, double addvalue) {
		if (channel.isPrimaryColorChannel()) {
		    double nowvalue = this->getValue(channel);
		    this->setValue(channel, nowvalue + addvalue);
		}
	    };

	    void RGBColor::addValue(double addvalue) {
		double_array nowvalues = this->getValues();
		double_array newvalues = DoubleArray::plus(nowvalues, addvalue,
							   getNumberBands());
		this->setValues(newvalues);
	    }

	    double RGBColor::getValue(const Channel & channel) {

		switch (channel.chindex) {
		case ChannelIndex::R:
		    return R;
		case ChannelIndex::G:
		    return G;
		case ChannelIndex::B:
		    return B;
		case ChannelIndex::Y:
		    return Math::min(R, G);
		case ChannelIndex::M:
		    return Math::min(R, B);
		case ChannelIndex::C:
		    return Math::min(G, B);
		case ChannelIndex::W:
		    Channel minCh = getMinChannel();
		    return getValue(minCh);
		}
		throw IllegalArgumentException("");
	    };

	    double RGBColor::getValue(const Channel & channel, const MaxValue & type) {
		double_array values(new double[3]);
		values = getValues(values, type);

		switch (channel.chindex) {
		case ChannelIndex::R:
		    return values[0];
		case ChannelIndex::G:
		    return values[1];
		case ChannelIndex::B:
		    return values[2];
		case ChannelIndex::Y:
		    return Math::min(values[0], values[1]);
		case ChannelIndex::M:
		    return Math::min(values[0], values[2]);
		case ChannelIndex::C:
		    return Math::min(values[1], values[2]);
		case ChannelIndex::W:
		    Channel minCh = getMinChannel();
		    return values[minCh.getArrayIndex()];
		    //return getValue(minCh);
		}
		throw IllegalArgumentException("");
	    };

	    double_array RGBColor::getValues(double_array values, const MaxValue & type) {
		getValues(values);
		if (type != *maxValue) {
		    changeMaxValue(values, *maxValue, type, false);
		}
		return values;
	    };

	    double_array RGBColor::getValues() {
		return ColorSpace::getValues();
	    };
	    double_array RGBColor::getValues(double_array values) {
		return ColorSpace::getValues(values);
	    };

	    void RGBColor::setValue(const Channel & channel, double value) {

		switch (channel.chindex) {
		case ChannelIndex::R:
		    R = value;
		    break;
		case ChannelIndex::G:
		    G = value;
		    break;
		case ChannelIndex::B:
		    B = value;
		    break;
		case ChannelIndex::Y:
		    R = G = value;
		    break;
		case ChannelIndex::M:
		    R = B = value;
		    break;
		case ChannelIndex::C:
		    B = G = value;
		    break;
		case ChannelIndex::W:
		    R = G = B = value;
		    break;
		}
	    };

	    const Channel & RGBColor::getMinChannel() {
		double_array rgbValues = getValues();
		int minIndex = Math::minIndex(rgbValues, getNumberBands());
		return Channel::getChannelByArrayIndex(minIndex);
	    };

	    const Channel & RGBColor::getMaxChannel() {
		double_array rgbValues = getValues();
		int maxIndex = Math::maxIndex(rgbValues, getNumberBands());
		return Channel::getChannelByArrayIndex(maxIndex);
	    };
	    RGB_ptr RGBColor::clone() {
		return RGB_ptr(new RGBColor(*this));
	    };

	    const RGB_ptr RGBColor::White(new RGBColor(255, 255, 255));
	    const RGB_ptr RGBColor::Black(new RGBColor(0, 0, 0));

	    void RGBColor::quantization(const MaxValue & maxValue) {
		quantization(maxValue, false);
	    };
	    void RGBColor::quantization(const MaxValue & maxValue, bool integerRoundDown) {
		const MaxValue & origin = *this->maxValue;
		//先轉到目標domain
		changeMaxValue(maxValue, integerRoundDown);
		//再轉回原本的domain
		changeMaxValue(origin, integerRoundDown);
	    };
	    const MaxValue & RGBColor::getMaxValue() {
		return *maxValue;
	    };
	    double_array RGBColor::getRGBRatio() {
		double_array result(new double[3]);
		double total = R + G + B;
		if (total == 0) {
		    result[0] = result[1] = result[2] = 0;
		} else {
		    result[0] = R / total;
		    result[1] = G / total;
		    result[2] = B / total;
		}
		return result;
	    };
	    int RGBColor::getNumberBands() {
		return RGBNumberBands;
	    };

	    double RGBColor::getHue() {
		double r = getValue(Channel::R, MaxValue::Double1);
		double g = getValue(Channel::G, MaxValue::Double1);
		double b = getValue(Channel::B, MaxValue::Double1);
		double div = Math::pow(Math::pow(r - g, 2) + (r - b) * (g - b), 0.5);
		div = (div <= 0 ? 0.00001 : div);

		double tmp = 0.5 * ((r - g) + (r - b)) / div;
		if (tmp > 1) {
		    tmp = 1;
		} else if (tmp < -1) {
		    tmp = -1;
		}

		double h = Math::acos(tmp) * 180 / 3.14159265;
		if (b > g) {
		    h = 360 - h;
		}
		return h;
	    };
	    double_array RGBColor::getHSVIValues() {
		double h, s, v, i;
		double r = getValue(Channel::R, MaxValue::Double1);
		double g = getValue(Channel::G, MaxValue::Double1);
		double b = getValue(Channel::B, MaxValue::Double1);
		i = (r + g + b) / 3;
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
		double_array hsviValues(new double[4]);
		hsviValues[0] = h;
		hsviValues[1] = s;
		hsviValues[2] = v;
		hsviValues[3] = i;
		return hsviValues;
	    };
	    RGB_ptr RGBColor::fromHSVValues(double h, double s, double v) {
		double_array rgbValues = HSV2RGBValues(h, s, v);
		RGB_ptr rgb(new RGBColor(RGBColorSpace::unknowRGB, rgbValues, MaxValue::Double1));
		return rgb;
	    };
	    double_array RGBColor::HSV2RGBValues(double h, double s, double v) {
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

	    TColor RGBColor::getColor() {
		int r = (int) this->getValue(Channel::R, MaxValue::Int8Bit);
		int g = (int) this->getValue(Channel::G, MaxValue::Int8Bit);
		int b = (int) this->getValue(Channel::B, MaxValue::Int8Bit);
		TColor color = (TColor) b * 65536 + g * 256 + r;
		return color;
	    };

	};
    };
};

