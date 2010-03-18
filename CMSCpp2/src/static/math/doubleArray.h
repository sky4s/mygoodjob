#ifndef DOUBLEARRAYH
#define DOUBLEARRAYH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include <tnt/tnt_array1d.h>
#include <tnt/tnt_array2d.h>

namespace math {
    class DoubleArray {
      private:
	static const double e;
	static double getTolerance(int m, int n, double1D sv);
      public:
	static double_array plus(double_array v1, double v, int n);
	static double_array minus(double_array v1, double_array v2, int n);
	static double_array times(double_array v1, double v, int n);

	static string_ptr toString(double_array m, int n);
	static string_ptr toString(double_vector_ptr m);
	static string_ptr toString(double1D_ptr m);
	static string_ptr toString(double2D_ptr m);
	static string_ptr toString(const longdouble2D & m);
	static string_ptr toString(const longdouble1D & m);


	static double_vector_ptr getRangeCopy(double_vector_ptr M, int j1,
					      int j2);
	static double1D_ptr getRangeCopy(double1D_ptr M, int j1, int j2);

	static double2D_ptr transpose(double1D_ptr a);
	static double2D_ptr transpose(double2D_ptr M);

	static void setDouble1D(double2D_ptr array2d, double1D_ptr array1d,
				int n);
	static double1D_ptr getDouble1DCopy(double2D_ptr array2d, int n);
	static double1D_ptr getDouble1D(double2D_ptr array2d, int n);
	static double1D_ptr getDouble1D(double1D_ptr array1d, int n);

	static void vectorcopy(double_vector_ptr src, int srcPos,
			       double_vector_ptr dest, int destPos,
			       int length);
	static void arraycopy(double1D_ptr src, int srcPos,
			      double1D_ptr dest, int destPos, int length);

	static double2D_ptr diagonal(double1D_ptr m);
	static double2D_ptr times(double2D_ptr a, double2D_ptr b);
	static double2D_ptr identity(int n);
	static double2D_ptr identity(int m, int n);
	static double2D_ptr solve(double2D_ptr a, double2D_ptr b);
	static double2D_ptr inverse(double2D_ptr m);
	static double2D_ptr pseudoInverse(double2D_ptr m);

	static double_array toDoubleArray(double array[], int n);
	static double_array toDoubleArray(int n, ...);

	static void storeToExcel(const std::string & filename,
				 double_vector_ptr doubleVector);
    };
};
#endif

