#ifndef RGBARRAYH
#define RGBARRAYH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件


namespace cms {
    namespace util {

	class RGBVector {
	  public:
	    static string_ptr toString(RGB_vector_ptr rgbVector);
	    static RGB_vector_ptr getLinearRGBVector(int n);
	    static RGB_vector_ptr getLinearRGBVector(bptr < cms::lcd::calibrate::BitDepthProcessor >
						     bitDepth, double bgain);
	    static RGB_vector_ptr getLinearRGBVector(bptr < cms::lcd::calibrate::BitDepthProcessor >
						     bitDepth, double rgain, double ggain,
						     double bgain);
	    static RGB_vector_ptr getLinearRGBVector(RGB_vector_ptr rgbVector, double rgain,
						     double ggain, double bgain);
	    static void storeToExcel(const std::string & filename, RGB_vector_ptr rgbVector);
	    static void storeToText(const std::string & filename, RGB_vector_ptr rgbVector);
	    static RGB_vector_ptr deepClone(RGB_vector_ptr vector);
	    static void changeMaxValue(RGB_vector_ptr vector, const Dep::MaxValue & type);
	    static void quantization(RGB_vector_ptr vector, const Dep::MaxValue & maxValue);
	    static void quantization(RGB_vector_ptr vector, const Dep::MaxValue & maxValue,
				     bool integerRoundDown);
	    static RGB_vector_ptr reverse(RGB_vector_ptr rgbVector);
	    static bool isAscend(RGB_vector_ptr rgbVector);
	    static bool isAscend(RGB_vector_ptr rgbVector, int start, int end);
	    static RGB_vector_ptr copyRange(RGB_vector_ptr rgbVector, int start, int end);
	};

	enum RGBType {
	    Intensity, Gamma
	};
	class RGBGamma:public jObject {
	  private:
	    static RGBGamma_ptr loadFromDesiredGamma(const std::
						     string & filename, bool isGammaValue);
	  public:

	    const RGBType type;
	    const double max;
	    double_vector_ptr r, g, b, w;
	     RGBGamma(double_vector_ptr r, double_vector_ptr g, double_vector_ptr b);
	     RGBGamma(double_vector_ptr r, double_vector_ptr g,
		      double_vector_ptr b, double_vector_ptr w);
	     RGBGamma(double_vector_ptr r, double_vector_ptr g,
		      double_vector_ptr b, const double max, const RGBType type);
	     RGBGamma(double_vector_ptr r, double_vector_ptr g,
		      double_vector_ptr b, double_vector_ptr w, const double max,
		      const RGBType type);
	    static void storeToExcel(const std::string & filename, RGBGamma_ptr rgbgamma);
	    static void storeToDesiredGamma(const std::string & filename, RGBGamma_ptr rgbgamma);
	    static RGBGamma_ptr loadFromDesiredGamma(const std::string & filename);
	    static RGBGamma_ptr loadFromDesiredGammaValue(const std::string & filename);
	    RGBGamma_ptr clone();

	};
    };
}
#endif

