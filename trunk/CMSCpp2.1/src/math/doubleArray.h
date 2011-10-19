#ifndef DOUBLEARRAYH
#define DOUBLEARRAYH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include <debug.h>

#ifdef __BORLANDC__
# pragma pack(push, 8)
#endif

#ifdef TNT_LIB
#include <tnt/tnt_array1d.h>
#include <tnt/tnt_array2d.h>
#endif

#ifdef __BORLANDC__
# pragma pack(pop)
#endif

namespace math {
#ifdef TNT_LIB
    class DoubleArray {
      private:
	static const double e;
	static double getTolerance(int m, int n, double1D sv);
	static double2D identity_(int m, int n);
      public:

	static string_ptr toString(double_array m, int n);
	static string_ptr toString(double_vector_ptr m);

	static string_ptr toString(double1D_ptr m);
	static string_ptr toString(double2D_ptr m);
	static std::string toString(double2D m);
	static string_ptr toString(const longdouble2D & m);
	static string_ptr toString(const longdouble1D & m);



	static void setDouble1D(double2D_ptr array2d, double1D_ptr array1d, int n);
	static double1D_ptr getDouble1DCopy(double2D_ptr array2d, int n);
	static double1D_ptr getDouble1D(double2D_ptr array2d, int n);
	static double1D_ptr getDouble1D(double1D_ptr array1d, int n);

	//=====================================================================
	// copy
	//=====================================================================
	static double_vector_ptr getRangeCopy(double_vector_ptr M, int j1, int j2);
	static double_vector_ptr copy(double_vector_ptr M);
	static double1D_ptr getRangeCopy(double1D_ptr M, int j1, int j2);

	static double2D_ptr transpose(double1D_ptr a);
	static double2D_ptr transpose(double2D_ptr M);

	static void vectorcopy(double_vector_ptr src, int srcPos,
			       double_vector_ptr dest, int destPos, int length);
	static void arraycopy(double1D_ptr src, int srcPos,
			      double1D_ptr dest, int destPos, int length);
	static void arraycopy(double *src, int srcPos, double *dest, int destPos, int length);
	static void arraycopy(double_array src, int srcPos,
			      double_array dest, int destPos, int length);
	static double_array arraycopy(double_array src, int length);
	//=====================================================================


	//=====================================================================
	// linear algebra
	//=====================================================================
	static double_array plus(double_array v1, double v, int n);
	static double_array minus(double_array v1, double_array v2, int n);
	static double_vector_ptr minus(double_vector_ptr v1, double v);
	static double_array times(double_array v1, double v, int n);


	static double2D_ptr diagonal(double1D_ptr m);
	static double2D_ptr times(double2D_ptr a, double2D_ptr b);
	static double2D times(double2D a, double2D b);
	static double2D_ptr identity(int n);
	static double2D_ptr identity(int m, int n);


	static double2D_ptr solve(double2D_ptr a, double2D_ptr b);
	static double2D solve(double2D a, double2D b);
	static double2D_ptr inverse(double2D_ptr m);
	static double2D inverse(double2D m);
	static double2D_ptr pseudoInverse(double2D_ptr m);
	//=====================================================================

	//=====================================================================
	// transform
	//=====================================================================
	static double2D_ptr toDouble2D(int width, int n, ...);
	static void toDouble2D_(int x, int n, ...);
	static double2D_ptr toDouble2D(double *array, int m, int n);
	static double2D_ptr toDouble2D(double_array array, int length);

	static double_array toDoubleArray(double array[], int n);
	static double_array toDoubleArray(int n, ...);
	static double_array toDoubleArray(float_array floatArray, int n);
	static double_array toDoubleArray(double2D_ptr array);
	static double_vector_ptr toDoubleVector(double array[], int n);
	static double *toCDoubleArray(double_vector_ptr doubleVector);
	static void toCDoubleArray(double_vector_ptr doubleVector, double *cDoubleArray);
	//=====================================================================

#ifdef EXCEL_ACCESSIBLE
	static void storeToExcel(const std::string & filename, double_vector_ptr doubleVector);
	static double_vector_ptr loadFromExcel(const std::string & filename);
#endif

	static double_vector_ptr getReverse(double_vector_ptr vec);
	static double sum(double_array array, int length);
    };

    class FloatArray {
      public:
	static float2D_ptr toFloat2D(int width, int n, ...);
	static float2D_ptr inverse(float2D_ptr m);
	static float2D_ptr solve(float2D_ptr a, float2D_ptr b);
	static float2D_ptr identity(int m, int n);
	static float2D_ptr times(float2D_ptr a, float2D_ptr b);
	static string_ptr toString(float2D_ptr m);
    };
#endif

    class IntArray {
      public:
	static int max(int_array array, int n);
	static double_array toDoubleArray(int_array array, int n);
	static void arraycopy(int_array src, int_array dest, int length);
	static int_array arraycopy(int_array src, int length);
    };


};
#endif

