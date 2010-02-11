#ifndef REGRESSIONH
#define REGRESSIONH

//C系統文件

//C++系統文件


//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include <tnt/tnt_array1d.h>
#include <tnt/tnt_array2d.h>

namespace math {
    class SVDLib {
      protected:
	double1D_ptr sv;
	double2D_ptr v, u;
	static longdouble2D toLongDouobleArray(double2D_ptr array);
	static double2D_ptr toDoubleArray(const longdouble2D & array);
	static double1D_ptr toDoubleArray(const longdouble1D & array);
      public:
	 SVDLib(double2D_ptr array);
	double1D_ptr getCoefficients(double1D_ptr output);
	static double1D_ptr getPredict(double2D_ptr input,
				       double1D_ptr coefs);
	double1D_ptr getSingularValues();
	double2D_ptr getU();
	double2D_ptr getV();
	void svd(double2D_ptr input);
	static double1D_ptr svbksb(const double2D_ptr u,
				   const double1D_ptr sv,
				   const double2D_ptr v,
				   const double1D_ptr output);
    };

    class Polynomial {
      private:
	class Coef3X {
	  public:
	    static double1D_ptr getCoef3By3(double x, double y, double z);
	    static double1D_ptr getCoef3By6(double x, double y, double z);
	    static double1D_ptr getCoef3By7(double x, double y, double z);
	    static double1D_ptr getCoef3By9(double x, double y, double z);
	    static double1D_ptr getCoef3By10(double x, double y, double z);
	};
	/*Enumeration(COEF1_)
	   BY_1 = 1, BY_1C = 2, BY_2 = 3, BY_2C = 4, BY_3 = 5, BY_3C =
	   6, EnumerationEnd() */
	 Enumeration(COEF3_)
	 BY_3 = 1, BY_3C = 2, BY_6 = 3, BY_6C = 4, BY_7 = 5, BY_7C =
	    6, BY_9 = 7, BY_9C = 8, BY_10 = 9, BY_10C =
	    10, EnumerationEnd()
      public:
	 class COEF {
	  protected:
	    COEF(int item, bool withConstant);
	    virtual void dummy();
	  public:
	    const int item;
	    const bool withConstant;

	};

	class COEF_1:public COEF {
	  private:
	    friend class Polynomial;
	    //COEF1_ coef1_;
	  public:
	    COEF_1(int item, bool withConstant);
	    static const COEF_1 & BY_1;
	    static const COEF_1 & BY_1C;
	    static const COEF_1 & BY_2;
	    static const COEF_1 & BY_2C;
	    static const COEF_1 & BY_3;
	    static const COEF_1 & BY_3C;
	};



	class COEF_3:public COEF {
	  private:
	    friend class Polynomial;
	    COEF3_ coef3_;
	  public:
	     COEF_3(int item, bool withConstant, COEF3_ coef3_);
	    static const COEF_3 & BY_3;
	    static const COEF_3 & BY_3C;
	    static const COEF_3 & BY_6;
	    static const COEF_3 & BY_6C;
	    static const COEF_3 & BY_7;
	    static const COEF_3 & BY_7C;
	    static const COEF_3 & BY_9;
	    static const COEF_3 & BY_9C;
	    static const COEF_3 & BY_10;
	    static const COEF_3 & BY_10C;
	};

	static double1D_ptr addCoef3WithConstant(double1D_ptr coef3);
	static double1D_ptr getCoef(double1D_ptr xyz,
				    const COEF_3 & coefs);
	static double1D_ptr getCoef(double x, const COEF_1 & coefs);
	static double1D_ptr getCoef(double x, double y, double z,
				    const COEF_3 & coefs);
	static double1D_ptr getCoefWithConstant(double x, int coefs);
	static double1D_ptr getCoef(double1D_ptr variables,
				    const COEF & coefs);

    };

    class Regression {
      protected:
	double2D_ptr inputCoefs;
	double2D_ptr output;
	double2D_ptr coefs;
      public:
	 Regression(double2D_ptr input, double2D_ptr output);
	 Regression(double1D_ptr input, double1D_ptr output);
	double2D_ptr getCoefs();
	double2D_ptr getPredict();
	static double2D_ptr getPredict(double2D_ptr input,
				       double2D_ptr coefs);
	double getRMSD();
	double getrSquare();
	void regress();
	void setCoefs(double2D_ptr coefs);
    };

    class PolynomialRegression:public Regression {
      protected:
	Polynomial::COEF polynomialCoef;
	static double2D_ptr processPolynomialInput(double2D_ptr input,
						   const Polynomial::
						   COEF & polynomialCoef);
	static double2D_ptr processPolynomialInput(double1D_ptr input,
						   const Polynomial::
						   COEF_1 &
						   polynomialCoef);
	static double2D_ptr processRegressionOutput(double1D_ptr output);
      public:
	 PolynomialRegression(double2D_ptr input, double2D_ptr output,
			      const Polynomial::COEF_3 & polynomialCoef);
	 PolynomialRegression(double2D_ptr input, double2D_ptr output,
			      const Polynomial::COEF & polynomialCoef);
	 PolynomialRegression(double1D_ptr input, double1D_ptr output,
			      const Polynomial::COEF_1 & polynomialCoef);

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

