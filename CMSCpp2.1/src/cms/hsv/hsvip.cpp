#include <includeall.h>
#pragma hdrstop
#include "hsvip.h"

namespace cms {
    namespace hsvip {
	using namespace math;
	using namespace java::lang;
	using namespace Dep;
	//======================================================================
	// SingleHueAdjustValue
	//======================================================================
	 SingleHueAdjustValue::SingleHueAdjustValue(short _hueAdjustValue,
						    short _saturationAdjustValue,
						    short _valueAdjustValue) {
	    hueAdjustValue = _hueAdjustValue;
	    saturationAdjustValue = _saturationAdjustValue;
	    valueAdjustValue = _valueAdjustValue;
	};
	double SingleHueAdjustValue::getDoubleHueAdjustValue() {
	    return hueAdjustValue / 768. * 360;
	};
	//======================================================================

	//======================================================================
	// TuneParameter
	//======================================================================
	TuneParameter::TuneParameter(barray < SingleHueAdjustValue > hsvAdjustValue) {
	};
	void TuneParameter::init(barray < SingleHueAdjustValue > hsvAdjustValue) {
	    hueAdjustValue = short_array(new short[24]);
	    saturationAdjustValue = short_array(new short[24]);
	    valueAdjustValue = short_array(new short[24]);
	    for (int x = 0; x < 24; x++) {
		SingleHueAdjustValue single = hsvAdjustValue[x];
		hueAdjustValue[x] = single.hueAdjustValue;
		saturationAdjustValue[x] = single.saturationAdjustValue;
		valueAdjustValue[x] = single.valueAdjustValue;
	    }
	};
	//======================================================================

	//======================================================================
	// HSVLUT
	//======================================================================
      HSVLUT::HSVLUT(TuneParameter & _tuneParameter):tuneParameter(_tuneParameter) {
	    init(tuneParameter.hueAdjustValue, tuneParameter.saturationAdjustValue,
		 tuneParameter.valueAdjustValue);
	};
	void HSVLUT::init(short_array hueAdjustValue,
			  short_array saturationAdjustValue, short_array valueAdjustValue) {

	};
	int HSVLUT::getDownAddrO(AUOHSV & auoHSV) {
	    int maxIdx = getMaxIdx(auoHSV);
	    short r = auoHSV.r;
	    short g = auoHSV.g;
	    short b = auoHSV.b;

	    int zone = auoHSV.zone >> 1;	//0~7 ==> 0~3 (4)
	    switch (maxIdx) {
	    case 0:
		return ((g - b) >= 0) ? zone : 20 + zone;	//0~3 : 20~23
	    case 1:
		return ((r - b) <= 0) ? 8 + zone : ((r == b) ? 8 : 4 + zone);	//8~11 : 4~7
	    case 2:
		return ((r - g) >= 0) ? 16 + zone : 12 + zone;	// 16~19 : 12~15
	    case 3:
		return 0;
	    }
	    return -1;
	};
	int HSVLUT::getMaxIdx(AUOHSV & auoHSV) {
	    short r = auoHSV.r;
	    short g = auoHSV.g;
	    short b = auoHSV.b;
	    if ((r - g) >= 0 && (r - b) >= 0) {
		return 0;
	    } else if ((r - g) < 0 && (g - b) >= 0) {
		return 1;
	    } else if ((r - b) < 0 && (g - b) < 0) {
		return 2;
	    } else {
		return 0;
	    }
	};
	short_array HSVLUT::getHSVIntpol(AUOHSV & auoHSV, SingleHueAdjustValue & v) {
	    short_array hsvIntpol(new short[4]);
	    hsvIntpol[0] = getHueIntpol(auoHSV, v.hueAdjustValue, v.hueAdjustValue);
	    hsvIntpol[1] = getSatIntpol(auoHSV, v.saturationAdjustValue, v.saturationAdjustValue);
	    hsvIntpol[2] = getLumIntpol(auoHSV, v.valueAdjustValue, v.valueAdjustValue);
	    return hsvIntpol;
	};
	short HSVLUT::getHueIntpol(AUOHSV & auoHSV, int down, int up) {
	    up = up < down ? up + 768 : up;

	    int down_3 = down << 3;
	    int up_down = up - down;
	    int up_down_index = up_down * auoHSV.hueIndex;
	    double up_down_index_double = ((double) up_down_index) / Math::pow(2, 5);
	    up_down_index = (int) Math::round(up_down_index_double);
	    int hueIntpol = up_down_index + down_3;
	    return (short) hueIntpol;
	};
	short HSVLUT::getSatIntpol(AUOHSV & auoHSV, int down, int up) {
	    int down_up = up - down;
	    int sat_intval = down_up * auoHSV.hueIndex;

	    int sat_intval_4 = sat_intval / 16;

	    int down_4 = down * 16;
	    int sat_intpol = sat_intval_4 + down_4;

	    return (short) sat_intpol;
	};
	short HSVLUT::getLumIntpol(AUOHSV & auoHSV, int down, int up) {
	    int down_up = up - down;
	    int lum_intval = down_up * auoHSV.hueIndex;

	    int down_256 = down * 256;
	    int lum_intpol = lum_intval + down_256;

	    return (short) lum_intpol;
	};
	//======================================================================

	short ValuePrecisionEvaluator::getV(short max, short min, short offset) {
	    boolean interpolateOffset = false;
	    short v = (short) getV(max, min, offset, (short) 1023, 1, 8, 10,
				   interpolateOffset);
	    return v;
	};
	int ValuePrecisionEvaluator::getV(short max, short min, short offset, short minusMax,
					  int bit1, int bit2, int bit3, boolean interpolateOffset) {
	    int offset10 = interpolateOffset ? offset : offset << 4;	//6+4=10
	    boolean negative = offset < 0;
	    offset10 = Math::abs(offset10);
	    int max_min10 = max - min;	//10bit
	    int max_bar10 = minusMax - max;	//10bit bar的取法會導致最後結果為10 or 11bit


	    long offsetXmax_min20 = (offset10 * max_min10) >> bit3;	// 20 - bit3 bit


	    long offsetXmax_min20Xmax_bar10 = offsetXmax_min20 * max_bar10;	//最大只到 20 - bit3 + 7 bit
	    //_offsetXmax_min20Xmax_bar10 = (offsetXmax_min20Xmax_bar10 > _offsetXmax_min20Xmax_bar10) ? offsetXmax_min20Xmax_bar10 : _offsetXmax_min20Xmax_bar10;      //以bit3=10來說, 為17bit


	    long offsetXmax_minXmax_bar30 = (offsetXmax_min20Xmax_bar10) >> bit2;	//28 - bit2 -bit3 bit
	    //_offsetXmax_minXmax_bar30 = offsetXmax_minXmax_bar30 > _offsetXmax_minXmax_bar30 ? offsetXmax_minXmax_bar30 : _offsetXmax_minXmax_bar30;  //以bit2 = 8, bit3 = 10來說, 為9bit


	    long theone = (long) Math::pow(2, 29 - bit2 - bit3);	//29 - bit2 - bit3

	    long originalGain = negative ? theone - offsetXmax_minXmax_bar30 :
		theone + offsetXmax_minXmax_bar30;

	    long gain32 = originalGain >> bit1;


	    long result = (max * gain32);	//10+11


	    int totalBit = 29 - bit1 - bit2 - bit3;

	    //最後輸出bit數, 受bit 1/2/3影響
	    //固定輸出為10bit 0~1023
	    int shiftResult = (int) (result >> (totalBit));

	    /*staticResult = (result > staticResult) ? result : staticResult;
	       if (shiftResult > staticShiftResult) {
	       staticShiftResult = shiftResult;
	       _max = max;
	       _min = min;
	       } */
	    return shiftResult;	//可以達11bit
	};

	short SaturationPrecisionEvaluator::getShortTurnPoint(byte turnPoint, int bit) {
	    short shotTurnPoint = -1;
	    int shiftBit = 10 - bit;

	    shotTurnPoint = (short) ((turnPoint << shiftBit) - 1);
	    return shotTurnPoint;
	};
	short SaturationPrecisionEvaluator::getShortSaturation(short saturation, short adjustValue,
							       byte turnPoint, boolean complement,
							       int bitG2,
							       int bitgain, int bitOutputSaturation,
							       int turnPointBit) {
	    int newEndSaturation = (1 << bitOutputSaturation) + (complement ? -1 : 0);

	    short result = -1;
	    int intg1 = adjustValue;	//9bit
	    double n = 1;
	    double n2 = 1. / (Math::pow(2, bitG2) - 1);

	    int intg1g2Shift = bitG2 - 3 + (12 - bitgain);
	    int offsetShift = 10 + (bitgain - 12) + (3 - turnPointBit);	//乘出來的offset做縮減


	    boolean select = false;
	    turnPoint++;	//turnPoint +1
	    short shotTurnPoint = getShortTurnPoint(turnPoint, turnPointBit);


	    select = saturation < shotTurnPoint;

	    int turnPointMax = (int) Math::pow(2, turnPointBit);

	    if (select) {
		//======================================================================
		// S' = S + LUT * (S/T)
		//    = S + (LUT/T) * S = S * ( 1+ (LUT/T) )
		//======================================================================
		double g2 = n / (turnPoint);	// 3bit
		double g2n2 = g2 / n2;
		int intg2_turnpoint = (int) g2n2;	//9bit register


		int originalIntg1g2 = intg1 * intg2_turnpoint;
		boolean negative = originalIntg1g2 < 0;
		originalIntg1g2 = Math::abs(originalIntg1g2);

		int intg1g2 = originalIntg1g2 >> intg1g2Shift;	//9+9=18 18-5=13
		int saturationOffset = saturation * intg1g2;	// 12 + 13 = 23 (22?)
		int saturationOffset2 = saturationOffset >> offsetShift;	//22 - 10 = 12
		int ints = negative ? saturation - saturationOffset2 : saturation + saturationOffset2;	//12 + 12

		result = (short) ints;


	    } else {
		//======================================================================
		// S' = S + LUT / (S-100%)/(100%-T)
		//    = S + LUT / (100%-T) * (S-100%)
		//    = S + (LUT/n) * (n/(100%-T) * (100%-S)
		//======================================================================
		double g2 = n / (turnPointMax - turnPoint);
		double g2n2 = g2 / n2;
		int intg2_turnpoint = (int) g2n2;	//9bit register

		int originalIntg1g2 = intg1 * intg2_turnpoint;
		boolean negative = originalIntg1g2 < 0;
		originalIntg1g2 = Math::abs(originalIntg1g2);

		int intg1g2 = originalIntg1g2 >> intg1g2Shift;
		int saturationOffset = (newEndSaturation - saturation) * intg1g2;
		int saturationOffset2 = saturationOffset >> offsetShift;
		int ints = negative ? saturation - saturationOffset2 : saturation + saturationOffset2;	//12 + 12


		result = (short) ints;

	    }
	    return result;

	};
      IntegerSaturationFormula::IntegerSaturationFormula(byte _turnPoint, int _turnPointBit):turnPoint(_turnPoint),
	    turnPointBit(_turnPointBit)
	{

	};
	short IntegerSaturationFormula::getSaturartion(short originalSaturation, short adjustValue) {
	    boolean runInComplement = true;
	    //boolean showMessage = false;
	    int bitg2 = 11;
	    int bitgain = 12;
	    int bitOutputSaturation = 10;
	    short result =
		SaturationPrecisionEvaluator::getShortSaturation(originalSaturation, adjustValue,
								 turnPoint, runInComplement, bitg2,
								 bitgain, bitOutputSaturation,
								 turnPointBit);
	    return result;
	};
	short_array IntegerHSVIP::getHSVValues(AUOHSV & hsv,
					       const SingleHueAdjustValue
					       & singleHueAdjustValue,
					       const IntegerSaturationFormula
					       & integerSaturationFormula, boolean hsvClip) {
	    short_array hsvIntpol = HSVLUT::getHSVIntpol(hsv, singleHueAdjustValue);
	    short_array result = getHSVValues(hsv, hsvIntpol, integerSaturationFormula,
					      hsvClip);
	    return result;
	};
	short_array IntegerHSVIP::getHSVValues(AUOHSV & hsv, short_array hsvIntpol,
					       const IntegerSaturationFormula
					       & integerSaturationFormula, boolean hsvClip) {
	    short_array hsvValues(new short[3]);
	    hsvValues[0] = hsvIntpol[0];
	    hsvValues[1] = integerSaturationFormula.getSaturartion(hsv.saturation, hsvIntpol[1]);

	    short offset = (short) (hsvIntpol[2] / Math::pow(2, 4));
	    hsvValues[2] = ValuePrecisionEvaluator::getV(hsv.value, hsv.min, offset);

	    if (hsvClip) {
		hsvValues[1] = hsvValues[1] > 1023 ? 1023 : hsvValues[1];
		hsvValues[1] = hsvValues[1] < 0 ? 0 : hsvValues[1];

		hsvValues[2] = hsvValues[2] > 1023 ? 1023 : hsvValues[2];
		hsvValues[2] = hsvValues[2] < 0 ? 0 : hsvValues[2];
	    }
	    return hsvValues;
	};

	//======================================================================
	// AUOHSV
	//======================================================================
	AUOHSV::AUOHSV(RGB_ptr rgb) {
	    init(fromRGBValues(rgb->get10BitValues()));
	};
	AUOHSV::AUOHSV(HSV_ptr hsv) {
	    RGB_ptr rgb = hsv->toRGB();
	    short_array rgbValues = rgb->get10BitValues();
	    init(fromRGBValues(rgbValues));
	};
	int AUOHSV::getDownAddrress() {
	    return HSVLUT::getDownAddrO(*this);
	};

	int AUOHSV::getHue() {
	    int downAddress = getDownAddrress();
	    int hue = downAddress * 255 + hueIndex;
	    return hue;
	}
	double AUOHSV::getHueInDegree() {
	    double normal = getHue() / (24. * 255);
	    return normal * 360;
	};
	void AUOHSV::init(short_array v) {
	    init(v[3], v[0], v[1], v[2], v[4], v[5], v[6], v[7], v[8]);
	};
	void AUOHSV::init(short _zone, short _hueIndex, short _saturation, short _value,
			  short _min, short _r, short _g, short _b, short _divH) {
	    zone = _zone;
	    hueIndex = _hueIndex;
	    saturation = _saturation;
	    value = _value;
	    min = _min;
	    r = _r;
	    g = _g;
	    b = _b;
	    divH = _divH;
	};
	static short getDiv(short a, short b) {
	    short div = (short) (((double) a) / b * (Math::pow(2, 10)));
	    return div;
	}

	static short getHDividend(short_array rgbValues) {
	    short r = rgbValues[0];
	    short g = rgbValues[1];
	    short b = rgbValues[2];
	    if (r >= g && r >= b) {	// bmax == r
		return (short) (g >= b ? Math::abs(g - b) : Math::abs(r - g) - Math::abs(g - b));
	    } else if (r < g && g >= b) {	//bmax == g
		return (short) ((r == b || b > r) ? Math::abs(r - b) :
				Math::abs(g - b) - Math::abs(r - b));
	    } else if (b > r && b > g) {	//bmax == b
		return (short) (r >= g ? Math::abs(r - g) : Math::abs(r - b) - Math::abs(r - g));
	    } else {
		return 0;
	    }
	}

	short_array AUOHSV::fromRGBValues(short_array rgbValues) {
	    short r = rgbValues[0];
	    short g = rgbValues[1];
	    short b = rgbValues[2];

	    short max = Math::max(rgbValues, 3);
	    short min = Math::min(rgbValues, 3);
	    short max_min = (short) (max - min);
	    short sDivq = getDiv(max_min, max);
	    sDivq = (sDivq == 1024) ? 1023 : sDivq;
	    short hDividend = getHDividend(rgbValues);
	    short divH = getDiv(hDividend, max_min);
	    divH = (divH == 1024) ? 1023 : divH;
	    short hPre3Divq = (short) (divH >> 7);
	    short hDivq = (short) (divH & 255);
	    short_array auoHSVValues(new short[NUMBER_BAND]);
	    auoHSVValues[0] = hDivq;
	    auoHSVValues[1] = sDivq;
	    auoHSVValues[2] = max;
	    auoHSVValues[3] = hPre3Divq;
	    auoHSVValues[4] = min;
	    auoHSVValues[5] = rgbValues[0];
	    auoHSVValues[6] = rgbValues[1];
	    auoHSVValues[7] = rgbValues[2];
	    auoHSVValues[8] = divH;
	    return auoHSVValues;
	};

	short_array AUOHSV::getRGBValues(short_array hsvValues3) {
	    short gen_hi = (short) (hsvValues3[0] >> 10);
	    short gen_f = (short) (hsvValues3[0] & 1023);
	    short gen_s = hsvValues3[1];
	    short gen_fs = (short) Math::round(gen_f * gen_s / Math::pow(2, 8));
	    short gen_vfs = (short) Math::round(gen_fs * hsvValues3[2] / Math::pow(2, 12));
	    short gen_vs = (short) Math::round(gen_s * hsvValues3[2] / Math::pow(2, 10));
	    short v = hsvValues3[2];

	    short gen_p = (short) (v - gen_vs);
	    gen_p = gen_p < 0 ? 0 : gen_p;

	    short gen_q = (short) (v - gen_vfs);
	    gen_q = gen_q < 0 ? 0 : gen_q;

	    short gen_t = (short) (gen_vfs + v - gen_vs);
	    gen_t = gen_t > 8191 ? 8191 : gen_t;
	    short_array rgbValues(new short[3]);
	    gen_hi = (short) (gen_hi % 6);

	    switch (gen_hi) {
	    case 0:
		rgbValues[0] = v;
		rgbValues[1] = gen_t;
		rgbValues[2] = gen_p;
		break;
	    case 1:
		rgbValues[0] = gen_q;
		rgbValues[1] = v;
		rgbValues[2] = gen_p;
		break;
	    case 2:
		rgbValues[0] = gen_p;
		rgbValues[1] = v;
		rgbValues[2] = gen_t;
		break;
	    case 3:
		rgbValues[0] = gen_p;
		rgbValues[1] = gen_q;
		rgbValues[2] = v;
		break;
	    case 4:
		rgbValues[0] = gen_t;
		rgbValues[1] = gen_p;
		rgbValues[2] = v;
		break;
	    case 5:
		rgbValues[0] = v;
		rgbValues[1] = gen_p;
		rgbValues[2] = gen_q;
		break;
	    }
	    if (RGBClipping) {
		rgbValues[0] = (rgbValues[0] > 1023) ? 1023 : rgbValues[0];
		rgbValues[1] = (rgbValues[1] > 1023) ? 1023 : rgbValues[1];
		rgbValues[2] = (rgbValues[2] > 1023) ? 1023 : rgbValues[2];

		rgbValues[0] = (rgbValues[0] < 0) ? 0 : rgbValues[0];
		rgbValues[1] = (rgbValues[1] < 0) ? 0 : rgbValues[1];
		rgbValues[2] = (rgbValues[2] < 0) ? 0 : rgbValues[2];
	    }
	    return rgbValues;
	};

	AUOHSV_ptr AUOHSV::fromHSVValues3(short_array hsvValues3) {
	    using namespace Dep;
	    short_array rgbValues = getRGBValues(hsvValues3);
	    double_array doubleRGBValues = toDoubleArray(rgbValues, 3);
	    RGB_ptr rgb(new RGBColor(RGBColorSpace::unknowRGB, doubleRGBValues,
				     MaxValue::Int10Bit));
	    AUOHSV_ptr auohsv(new AUOHSV(rgb));
	    return auohsv;
	};
	boolean AUOHSV::RGBClipping = true;
	double_array AUOHSV::toDoubleArray(short_array shortArray, int size) {
	    double_array doubleArray(new double[size]);
	    for (int x = 0; x < size; x++) {
		doubleArray[x] = shortArray[x];
	    }
	    return doubleArray;
	};
	RGB_ptr AUOHSV::toRGB() {
	    using namespace Dep;
	    double_array rgbValues(new double[3]);
	    rgbValues[0] = r;
	    rgbValues[1] = g;
	    rgbValues[2] = b;
	    RGB_ptr rgb(new RGBColor(RGBColorSpace::unknowRGB, rgbValues, MaxValue::Int10Bit));
	    return rgb;
	};
	//======================================================================
	//
	//======================================================================
	//IntegerSaturationFormula ChromaEnhance::isf = IntegerSaturationFormula(7, 3);
      ChromaEnhance::ChromaEnhance(const RGBColorSpace & _colorspace, const IntegerSaturationFormula & _isf):colorspace(_colorspace), isf(_isf), hsvClip(false)
	{
	};
	double ChromaEnhance::calculateDeltaL(SingleHueAdjustValue & adjustValue) {
	    return calculateDeltaL(adjustValue, colorspace, isf, hsvClip);
	};
	void ChromaEnhance::setHSVClip(boolean clip) {
	    hsvClip = clip;
	};
	double ChromaEnhance::
	    calculateDeltaL(const SingleHueAdjustValue & adjustValue,
			    const RGBColorSpace & colorspace,
			    const IntegerSaturationFormula & isf, boolean hsvClip) {
	    using namespace Dep;
	    using namespace Indep;
	    double h = adjustValue.getDoubleHueAdjustValue();
	    double totalDeltaL = 0;
	    XYZ_ptr white = colorspace.referenceWhite.getXYZ();
	    int index = 0;

	    for (int s = 10; s <= 90; s += 10) {
		for (int v = 30; v <= 90; v += 10) {
		    HSV_ptr hsv(new HSV(colorspace, h, s, v));
		    AUOHSV auohsv(hsv);
		    short_array auohsvValues =
			IntegerHSVIP::getHSVValues(auohsv, adjustValue, isf, hsvClip);
		    AUOHSV_ptr hsv2 = AUOHSV::fromHSVValues3(auohsvValues);
		    RGB_ptr rgb = hsv2->toRGB();
		    XYZ_ptr XYZ = RGBColor::toXYZ(rgb, colorspace);
		    CIELab Lab(XYZ, white);
		    RGB_ptr rgb0 = hsv->toRGB();
		    XYZ_ptr XYZ0 = rgb0->toXYZ();
		    CIELab Lab0(XYZ0, white);
		    double deltaL = Math::abs(Lab.L - Lab0.L);
		    totalDeltaL += deltaL;
		    index++;
		};
	    };
	    double averageDeltaL = totalDeltaL / index;
	    return Math::abs(averageDeltaL);
	};
	//======================================================================
    };
    //======================================================================
};

