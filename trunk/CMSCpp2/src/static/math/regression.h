#ifndef REGRESSIONH
#define REGRESSIONH

//C系統文件

//C++系統文件


//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>

    namespace math {
	class SVDLib {

	};
	class LinearRegression {
	  public:
	    LinearRegression(double_vector_ptr x, double_vector_ptr y);
	    double getValue(double x);
	    double getSlope();
	    double getIntercept();
	    double getCoefficient();
	  private:

	    double m_a, m_b, m_coeff;
	};
    };

#endif

