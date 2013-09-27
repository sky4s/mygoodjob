#ifndef INTERPOLATIONH
#define INTERPOLATIONH

//C╰参ゅン

//C++╰参ゅン


//ㄤ畐繷ゅン

//セ兜ヘず繷ゅン
#include <java/lang.h>

namespace math {
    enum Algo {
	CubicPolynomial, Lagrange, Lagrange4, Lagrange8, Linear,
	Spline2, QuadraticPolynomial, Gamma, Gamma2
    };
    class Searcher;

    class Interpolation {
      protected:
	double_vector_ptr xn_, yn_;
	static int getxnPartStartIndex(double_vector_ptr xn, double x, int width);
	static int
	 getxnPartStartIndexForExtrapolation(double_vector_ptr xn, double x, int width);
	static double_vector_ptr getPart(double_vector_ptr array, int startIndex, int width);
      public:
	 Interpolation(double_vector_ptr xn, double_vector_ptr yn);
	static double linear(double x1, double x2, double y1, double y2, double x);
	static double linear(double_vector_ptr xn, double_vector_ptr yn, double x);
	static double linear2(double_vector_ptr xn, double_vector_ptr yn, double x);
        static double parabola(double Ax, double Ay, double Bx, double By, double X);
        static double BezierCurve(double P0x, double P0y, double P1x, double P1y, double P2x, double P2y, double X);
	static double interpolate(double_vector_ptr xn,
				  double_vector_ptr yn, double x, Algo interpolationType);
	double interpolate(double x, Algo interpolationType);
    };
    /*
       紇臫arrayず程籔程﹚
       Progressive: 亥糤
       Ripple: Τ癬ヱ
    */
    enum LUTType {
	Progressive, Ripple
    };

    class Interpolation1DLUT {
      private:
	bool hasCorrectedInRange_;
	double_vector_ptr valueArray;
	double_vector_ptr keyArray;
	int size;
	LUTType lutType;
	double getMaxValue(double_vector_ptr array);
	double getMinValue(double_vector_ptr array);
	double maxKey, maxValue, minKey, minValue;
	bool inverseSearch;
      protected:
	double interpolationValue(double key,
				  double_vector_ptr keys, double_vector_ptr values, Algo type);
	double correctInRange(double number, double_vector_ptr numberArray);
      public:
	 Interpolation1DLUT(double_vector_ptr key, double_vector_ptr value);
	 Interpolation1DLUT(double_vector_ptr key, double_vector_ptr value, LUTType lutType);
	double correctKeyInRange(double key);
	double correctValueInRange(double value);

	double getKey(double value);
	double getValue(double key);
	bool isKeyInRange(double key);
	bool isValueInRange(double value);
	bool hasCorrectedInRange();
	double getMaxKey();
	double getMaxValue();
	__property bool InverseSearch = { write = inverseSearch };
    };
};
#endif

