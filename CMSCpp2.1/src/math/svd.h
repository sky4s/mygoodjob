#ifndef SVDH
#define SVDH
//C系統文件

//C++系統文件

//其他庫頭文件
//#include <jama/jama_svd.h>
//本項目內頭文件


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
};
#endif

