#include "doublearray.h"

//C系統文件

//C++系統文件

//其他庫頭文件
#include <boost/lexical_cast.hpp>


//本項目內頭文件

namespace math {
    using namespace boost;
    using namespace java::lang;
    string_ptr DoubleArray::toString(double_array m, int n) {
	using namespace std;
	string_ptr str(new string("["));
	for (int x = 0; x != n - 1; x++) {
	    double v = m[x];
	     (*str) += lexical_cast < string > (v);
	     (*str) += ", ";
	};
	(*str) += lexical_cast < string > (m[n - 1]);
	(*str) += "]";
	return str;
    };

    double_array DoubleArray::plus(double_array v1, double v, int n) {
	double_array array(new double[n]);
	for (int i = 0; i < n; i++) {
	    array[i] = v1[i] + v;
	}
	return array;
    };

    double_array DoubleArray::minus(double_array v1, double_array v2,
				    int n) {
	double_array array(new double[n]);
	for (int i = 0; i < n; i++) {
	    array[i] = v1[i] - v2[i];
	}
	return array;
    };

    double_array DoubleArray::times(double_array v1, double v, int n) {
	double_array array(new double[n]);
	for (int i = 0; i < n; i++) {
	    array[i] = v1[i] * v;
	}
	return array;
    }

    double_vector_ptr DoubleArray::getRangeCopy(double_vector_ptr M,
						int j1, int j2) {
	double_vector_ptr copy(new double_vector);
	vectorcopy(M, j1, copy, 0, j2 - j1 + 1);
	return copy;
    };

    double1D_ptr DoubleArray::getRangeCopy(double1D_ptr M, int j1, int j2) {

	double1D_ptr array(new double1D(j2 - j1 + 1));
	arraycopy(M, j1, array, 0, j2 - j1 + 1);
	return array;
    };

    double2D_ptr DoubleArray::transpose(double1D_ptr a) {
	int an = a->dim1();
	double2D_ptr result(new double2D(an, 1));
	for (int j = 0; j < an; j++) {
	    (*result)[j][0] = (*a)[j];

	}
	return result;
    };

    double2D_ptr DoubleArray::transpose(double2D_ptr M) {
	int m = M->dim2();
	int n = M->dim1();
	double2D_ptr tM(new double2D(m, n));
	for (int i = 0; i < m; i++) {
	    for (int j = 0; j < n; j++) {
		(*tM)[i][j] = (*M)[j][i];
	    }
	}
	return tM;

    };
    void DoubleArray::setDouble1D(double2D_ptr array2d,
				  double1D_ptr array1d, int n) {
	int size = array1d->dim1();
	for (int x = 0; x != size; x++) {
	    (*array2d)[n][x] = (*array1d)[x];
	};
    };
    double1D_ptr DoubleArray::getDouble1DCopy(double2D_ptr array2d, int n) {
	int width = array2d->dim2();
	double1D_ptr result(new double1D(width));
	for (int x = 0; x != width; x++) {
	    (*result)[x] = (*array2d)[n][x];
	};
	return result;
    };
    double1D_ptr DoubleArray::getDouble1D(double2D_ptr array2d, int n) {
	int width = array2d->dim2();
	double1D_ptr result(new double1D(width, (*array2d)[n]));
	return result;
    };

    double1D_ptr DoubleArray::getDouble1D(double1D_ptr array1d, int n) {
	double1D_ptr result(new double1D(1, (*array1d)[0]));
	return result;
    };

    void DoubleArray::vectorcopy(double_vector_ptr src, int srcPos,
				 double_vector_ptr dest, int destPos,
				 int length) {
	dest->insert(dest->begin() + destPos, src->begin() + srcPos,
		     src->begin() + srcPos + length);

    };

    void DoubleArray::arraycopy(double1D_ptr src, int srcPos,
				double1D_ptr dest, int destPos,
				int length) {
	for (int x = 0; x != length; x++) {
	    (*dest)[x + destPos] = (*src)[x + srcPos];
	}
    };
};

