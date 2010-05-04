#ifndef GAMMAH
#define GAMMAH

//C系統文件

//C++系統文件


//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>

namespace math {
    class GammaFinder {
      public:
	static double findingGamma(double_vector_ptr normalizeInput,
				   double_vector_ptr normalizeOutput);
	static double findingGamma(double_vector_ptr input,
				   double_vector_ptr output,
				   double inputMinValue,
				   double outputMinValue,
				   double inputMaxValue,
				   double outputMaxValue);
	static double_vector_ptr normalize(double_vector_ptr valueArray,
					   double minValue,
					   double maxValue);
	static double gamma(double input, double gamma);
	static double_vector_ptr gamma(double_vector_ptr input,
				       double gamma);
      protected:
	static barray < double_vector_ptr >
	    normalize(double_vector_ptr input, double_vector_ptr output,
		      double inputMinValue, double outputMinValue,
		      double inputMaxValue, double outputMaxValue);
    };
};
#endif

