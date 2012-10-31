#ifndef HSVIPH
#define HSVIPH

//C系統文件

//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件

//本項目內gui頭文件

typedef bptr < cms::hsvip::AUOHSV > AUOHSV_ptr;

namespace cms {
    namespace hsvip {

	class SingleHueAdjustValue {
	  public:
	    SingleHueAdjustValue(short hueAdjustValue,
				 short saturationAdjustValue, short valueAdjustValue);
	    short hueAdjustValue;
	    short saturationAdjustValue;
	    short valueAdjustValue;
	    double getDoubleHueAdjustValue() const;
	};

	class TuneParameter {
	  public:
	    TuneParameter(barray < SingleHueAdjustValue > hsvAdjustValue);
	    short_array hueAdjustValue;
	    short_array saturationAdjustValue;
	    short_array valueAdjustValue;
	  private:
	    void init(barray < SingleHueAdjustValue > hsvAdjustValue);
	};

	class HSVLUT {
	  public:
	    HSVLUT(TuneParameter & tuneParameter);
	    static int getDownAddrO(AUOHSV & auoHSV);
	    static short_array getHSVIntpol(const AUOHSV & auoHSV, const SingleHueAdjustValue & v);

	  private:
	    short_array hueAdjustValue;
	    short_array saturationAdjustValue;
	    short_array valueAdjustValue;
	    void init(short_array hueAdjustValue,
		      short_array saturationAdjustValue, short_array valueAdjustValue);
	    TuneParameter & tuneParameter;
	    static int getMaxIdx(AUOHSV & auoHSV);
	    static short getHueIntpol(const AUOHSV & auoHSV, int down, int up);
	    static short getSatIntpol(const AUOHSV & auoHSV, int down, int up);
	    static short getLumIntpol(const AUOHSV & auoHSV, int down, int up);
	};

	class ValuePrecisionEvaluator {
	  public:
	    static short getV(short max, short min, short offset);
	    static int getV(short max, short min, short offset, short minusMax,
			    int bit1, int bit2, int bit3, boolean interpolateOffset);
	};

	class SaturationPrecisionEvaluator {
	  public:
	    static short getShortSaturation(short saturation, short adjustValue,
					    byte turnPoint, boolean complement,
					    int bitG2,
					    int bitgain, int bitOutputSaturation, int turnPointBit);

	    static short getShortTurnPoint(byte turnPoint, int bit);
	};

	class IntegerSaturationFormula {
	  public:
	    IntegerSaturationFormula(byte turnPoint, int turnPointBit);
	    short getSaturation(short originalSaturation, short adjustValue) const;
	  private:
	    byte turnPoint;
	    int turnPointBit;
	};

	class IntegerHSVIP {
	  public:
	    static short_array getHSVValues(AUOHSV & hsv,
					    const SingleHueAdjustValue
					    & singleHueAdjustValue,
					    const IntegerSaturationFormula
					    & integerSaturationFormula, boolean hsvClip);
	    //protected:
	    static short_array getHSVValues(AUOHSV & hsv, short_array hsvIntpol,
					    const IntegerSaturationFormula
					    & integerSaturationFormula, boolean hsvClip);
	};

	class AUOHSV {
	  public:
	    AUOHSV(RGB_ptr rgb);
	    AUOHSV(HSV_ptr hsv);
	    const static int NUMBER_BAND = 9;

	    short zone;
	    short hueIndex;
	    short saturation;
	    short value;
	    short r;
	    short g;
	    short b;
	    short min;
	    short divH;
	    int getDownAddrress();
	    int getHue();
	    double getHueInDegree();
	    static AUOHSV_ptr fromHSVValues3(short_array hsvValues3);
	    static short_array getRGBValues(short_array hsvValues3);
	    RGB_ptr toRGB();
	  protected:
	    void init(short_array auoHSVValues);
	    void init(short zone, short hueIndex, short saturation, short value,
		      short min, short r, short g, short b, short divH);


	    static short_array fromRGBValues(short_array rgbValues);
	  private:
	    static boolean RGBClipping;
	    static double_array toDoubleArray(short_array shortArray, int size);
	};

	class ChromaEnhance {
	  private:
	    bptr < Dep::RGBColorSpace > colorspace;
	    const IntegerSaturationFormula & isf;
	    boolean hsvClip;
	  public:
	    void setHSVClip(boolean clip);
	    ChromaEnhance(bptr < Dep::RGBColorSpace > colorspace,
			  const IntegerSaturationFormula & isf);
	    double calculateDeltaL(const SingleHueAdjustValue & singleHueAdjustValue);
	    static double calculateDeltaL(const SingleHueAdjustValue & singleHueAdjustValue,
					  bptr < Dep::RGBColorSpace > colorspace,
					  const IntegerSaturationFormula & isf, boolean hsvClip);
	};
    };
};


#endif

