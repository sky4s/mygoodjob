#include "regression.h"

//C系統文件
#include <assert.h>
#include <math.h>

//C++系統文件

//其他庫頭文件

//本項目內頭文件

    namespace math {
	LinearRegression::LinearRegression(double_vector_ptr x,
					   double_vector_ptr y) {
	    int n = x->size();
	    // calculate the averages of arrays x and y
	    double xa = 0, ya = 0;
	    for (int i = 0; i < n; i++) {
		xa += (*x)[i];
		ya += (*y)[i];
	    };
	     xa /= n;
	     ya /= n;

	    // calculate auxiliary sums
	    double xx = 0, yy = 0, xy = 0;
	    for (int i = 0; i < n; i++) {
		double tmpx = (*x)[i] - xa, tmpy = (*y)[i] - ya;
		 xx += tmpx * tmpx;
		 yy += tmpy * tmpy;
		 xy += tmpx * tmpy;
	    }
	    // calculate regression line parameters// make sure slope is not infinite
		assert(fabs(xx) != 0);

	    m_b = xy / xx;
	    m_a = ya - m_b * xa;
	    m_coeff = (fabs(yy) == 0) ? 1 : xy / sqrt(xx * yy);
	};
	double LinearRegression::getValue(double x) {
	    return m_a + m_b * x;
	};
	double LinearRegression::getSlope() {
	    return m_b;
	};
	double LinearRegression::getIntercept() {
	    return m_a;
	};
	double LinearRegression::getCoefficient() {
	    return m_coeff;
	};
    };

