#ifndef INTERPOLATIONH
#define INTERPOLATIONH

//C系統文件

//C++系統文件


//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>

namespace math {
    enum Algo {
	CubicPolynomial, Lagrange, Lagrange4, Lagrange8, Linear,
	Spline2, QuadraticPolynomial, Gamma, Gamma2
    };
    class Searcher;

    class Interpolation {
      protected:
	double_vector_ptr _xn, _yn;
	static int getxnPartStartIndex(double_vector_ptr xn, double x,
				       int width);
	static int
	 getxnPartStartIndexForExtrapolation(double_vector_ptr xn,
					     double x, int width);
	static double_vector_ptr getPart(double_vector_ptr
					 array, int startIndex, int width);
      public:
	 Interpolation(double_vector_ptr xn, double_vector_ptr yn);
	static double linear(double x1, double x2, double y1,
			     double y2, double x);
	static double linear(double_vector_ptr xn,
			     double_vector_ptr yn, double x);
	static double linear2(double_vector_ptr xn,
			      double_vector_ptr yn, double x);
	static double interpolate(double_vector_ptr xn,
				  double_vector_ptr yn, double x,
				  Algo interpolationType);
	double interpolate(double x, Algo interpolationType);
    };

    class Interpolation1DLUT {
      private:
	bool _hasCorrectedInRange;
	double_vector_ptr valueArray;
	double_vector_ptr keyArray;
	int size;
      protected:
	static double interpolationValue(double key,
					 double_vector_ptr keys,
					 double_vector_ptr values,
					 Algo type);
	double correctInRange(double number,
			      double_vector_ptr numberArray);
      public:
	 Interpolation1DLUT(double_vector_ptr key,
			    double_vector_ptr value);
	double correctKeyInRange(double key);
	double correctValueInRange(double value);

	double getKey(double value);
	double getValue(double key);
	bool isKeyInRange(double key);
	bool isValueInRange(double value);
	bool hasCorrectedInRange();
    };
};
#endif

