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
      public:
	static double_array plus(double_array v1, double v, int n);
	static double_array minus(double_array v1, double_array v2, int n);
	static string_ptr toString(double_array m, int n);
	static double_array times(double_array v1, double v, int n);
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

    };
};
#endif

