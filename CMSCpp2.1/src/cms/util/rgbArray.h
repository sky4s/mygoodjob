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
	    static void storeToExcel(const std::string & filename,
				     RGB_vector_ptr rgbVector);
	    static RGB_vector_ptr clone(RGB_vector_ptr vector);
	    static RGB_vector_ptr deepClone(RGB_vector_ptr vector);
	    static void changeMaxValue(RGB_vector_ptr vector,
				       const Dep::MaxValue & type);
	    static void quantization(RGB_vector_ptr vector,
				     const Dep::MaxValue & maxValue);
	};

	enum Type {
	    Intensity, Gamma
	};
	class RGBGamma:public jObject {
	  public:
	    const Type type;
	    const double max;
	    double_vector_ptr r, g, b, w;
	     RGBGamma(double_vector_ptr r, double_vector_ptr g,
		      double_vector_ptr b);
	     RGBGamma(double_vector_ptr r, double_vector_ptr g,
		      double_vector_ptr b, double_vector_ptr w);
	     RGBGamma(double_vector_ptr r, double_vector_ptr g,
		      double_vector_ptr b, const double max,
		      const Type type);
	     RGBGamma(double_vector_ptr r, double_vector_ptr g,
		      double_vector_ptr b, double_vector_ptr w,
		      const double max, const Type type);
	    static void storeToExcel(const std::string & filename,
				     RGBGamma_ptr rgbgamma);
	    static void storeToDesiredGamma(const std::
					    string & filename,
					    RGBGamma_ptr rgbgamma);
	    static RGBGamma_ptr loadFromDesiredGamma(const std::
						     string & filename);
	    RGBGamma_ptr clone();

	};
    };
}
#endif

