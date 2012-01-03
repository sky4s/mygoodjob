#include <includeall.h>
#pragma hdrstop
#include "doublearray.h"

//C系統文件
#include <cstdarg>
//C++系統文件

//其他庫頭文件
#include <tnt/tnt_array2d_utils.h>
#include <jama/jama_lu.h>
#include <jama/jama_qr.h>
#include <jama/jama_svd.h>

//本項目內頭文件

namespace math {
    using namespace boost;
    using namespace java::lang;
    using namespace std;
    using namespace JAMA;
    using namespace cms::colorformat;
    using namespace cms::util;
#ifdef TNT_LIB
    string_ptr DoubleArray::toString(double_array m, int n) {
	string_ptr str(new string("["));
	for (int x = 0; x != n - 1; x++) {
	    double v = m[x];
	     (*str) += _toString(v);
	     (*str) += ", ";
	};
	(*str) += _toString(m[n - 1]);
	(*str) += "]";
	return str;
    };

    string_ptr DoubleArray::toString(double_vector_ptr m) {
	string_ptr str(new string("["));
	int n = m->size();
	for (int x = 0; x != n - 1; x++) {
	    double v = (*m)[x];
	    (*str) += _toString(v);
	    (*str) += ", ";
	};
	(*str) += _toString((*m)[n - 1]);
	(*str) += "]";
	return str;
    };

    string_ptr DoubleArray::toString(double1D_ptr m) {
	string_ptr str(new string());

	for (int i = 0; i < m->dim1() - 1; i++) {
	    (*str) += _toString((*m)[i]) + " ";
	}
	(*str) += _toString((*m)[m->dim1() - 1]) + "\n";

	return str;
    };

    string_ptr DoubleArray::toString(double2D_ptr m) {

	string_ptr str(new string());

	for (int i = 0; i < m->dim1(); i++) {
	    for (int j = 0; j < m->dim2() - 1; j++) {
		(*str) += _toString((*m)[i][j]) + " ";
	    }
	    (*str) += _toString((*m)[i][m->dim2() - 1]);
	    if (i < m->dim1() - 1) {
		(*str) += "\n";
	    }
	}
	return str;
    };

    string DoubleArray::toString(double2D m) {
	using namespace std;
	string str;

	for (int i = 0; i < m.dim1(); i++) {
	    for (int j = 0; j < m.dim2() - 1; j++) {
		str += _toString(m[i][j]) + " ";
	    }
	    str += _toString(m[i][m.dim2() - 1]);
	    if (i < m.dim1() - 1) {
		str += "\n";
	    }
	}
	return str;
    };

    string_ptr DoubleArray::toString(const longdouble2D & m) {
	string_ptr str(new string());

	for (int i = 0; i < m.dim1(); i++) {
	    for (int j = 0; j < m.dim2() - 1; j++) {
		(*str) += _toString(m[i][j]) + " ";
	    }
	    (*str) += _toString(m[i][m.dim2() - 1]);
	    if (i < m.dim1() - 1) {
		(*str) += "\n";
	    }
	}
	return str;
    };

    string_ptr DoubleArray::toString(const longdouble1D & m) {
	string_ptr str(new string());

	for (int i = 0; i < m.dim1() - 1; i++) {
	    (*str) += _toString(m[i]) + " ";
	}
	(*str) += _toString(m[m.dim1() - 1]) + "\n";

	return str;
    };

    double_array DoubleArray::plus(double_array v1, double v, int n) {
	double_array array(new double[n]);
	for (int i = 0; i < n; i++) {
	    array[i] = v1[i] + v;
	}
	return array;
    };

    double_array DoubleArray::minus(double_array v1, double_array v2, int n) {
	double_array array(new double[n]);
	for (int i = 0; i < n; i++) {
	    array[i] = v1[i] - v2[i];
	}
	return array;
    };

    double_vector_ptr DoubleArray::minus(double_vector_ptr v1, double v) {
	double_vector_ptr array(new double_vector(v1->size()));
	for (unsigned int i = 0; i < v1->size(); i++) {
	    (*array)[i] = (*v1)[i] - v;
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

    double_vector_ptr DoubleArray::getRangeCopy(double_vector_ptr M, int j1, int j2) {
	double_vector_ptr copy(new double_vector);
	vectorcopy(M, j1, copy, 0, j2 - j1 + 1);
	return copy;
    };
    double_vector_ptr DoubleArray::copy(double_vector_ptr M) {
	return getRangeCopy(M, 0, M->size() - 1);
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
    void DoubleArray::setDouble1D(double2D_ptr array2d, double1D_ptr array1d, int n) {
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
				 double_vector_ptr dest, int destPos, int length) {
	dest->insert(dest->begin() + destPos, src->begin() + srcPos,
		     src->begin() + srcPos + length);

    };

    void DoubleArray::arraycopy(double1D_ptr src, int srcPos,
				double1D_ptr dest, int destPos, int length) {
	for (int x = 0; x != length; x++) {
	    (*dest)[x + destPos] = (*src)[x + srcPos];
	};
    };
    void DoubleArray::arraycopy(double *src, int srcPos, double *dest, int destPos, int length) {
	for (int x = 0; x != length; x++) {
	    dest[x + destPos] = src[x + srcPos];
	};
    }
    void DoubleArray::arraycopy(double_array src, int srcPos,
				double_array dest, int destPos, int length) {
	for (int x = 0; x != length; x++) {
	    dest[x + destPos] = src[x + srcPos];
	};
    };

    double_array DoubleArray::arraycopy(double_array src, int length) {
	double_array dest(new double[length]);
	arraycopy(src, 0, dest, 0, length);
	return dest;
    }

    double2D_ptr DoubleArray::diagonal(double1D_ptr m) {
	int size = m->dim();
	double2D_ptr I(new double2D(size, size));
	for (int i = 0; i < size; i++) {
	    (*I)[i][i] = (*m)[i];
	}
	return I;
    };

    double2D_ptr DoubleArray::times(double2D_ptr a, double2D_ptr b) {
	int m = a->dim1();
	int n = a->dim2();
	int bn = b->dim2();

	double2D_ptr result(new double2D(m, bn));
	double1D Bcolj(n);
	for (int j = 0; j < bn; j++) {
	    for (int k = 0; k < n; k++) {
		Bcolj[k] = (*b)[k][j];
	    }
	    for (int i = 0; i < m; i++) {
		long double s = 0;
		for (int k = 0; k < n; k++) {
		    s += (*a)[i][k] * Bcolj[k];
		}
		(*result)[i][j] = s;
	    }
	}
	return result;
    };

    double2D DoubleArray::times(double2D a, double2D b) {
	int m = a.dim1();
	int n = a.dim2();
	int bn = b.dim2();

	double2D result(m, bn);
	double1D Bcolj(n);
	for (int j = 0; j < bn; j++) {
	    for (int k = 0; k < n; k++) {
		Bcolj[k] = b[k][j];
	    }
	    for (int i = 0; i < m; i++) {
		long double s = 0;
		for (int k = 0; k < n; k++) {
		    s += a[i][k] * Bcolj[k];
		}
		result[i][j] = s;
	    }
	}
	return result;
    };

    double2D_ptr DoubleArray::identity(int n) {
	double2D_ptr m(new double2D(n, n));
	for (int x = 0; x < n; x++) {
	    (*m)[x][x] = 1;
	}
	return m;
    };
    double2D_ptr DoubleArray::identity(int m, int n) {
	double2D_ptr result(new double2D(m, n));
	//int size = Math::min(m, n);
	for (int x = 0; x < m; x++) {
	    for (int y = 0; y < n; y++) {
		(*result)[x][y] = (x == y) ? 1 : 0;
		//(*result)[x][y] = (x == y) ? 1 : (*result)[x][y];
	    }
	}

	return result;
    };
    double2D DoubleArray::identity_(int m, int n) {
	double2D result(m, n);
	//int size = Math::min(m, n);
	for (int x = 0; x < m; x++) {
	    for (int y = 0; y < n; y++) {
		result[x][y] = (x == y) ? 1 : 0;
	    }
	}
	return result;
    };
    double2D_ptr DoubleArray::solve(double2D_ptr a, double2D_ptr b) {

	int m = a->dim1();
	int n = a->dim2();
	double2D_ptr result;
	if (m == n) {
	    LU < double >lu(*a);
	    result = double2D_ptr(new double2D(lu.solve(*b)));
	} else {
	    QR < double >qr(*a);
	    result = double2D_ptr(new double2D(qr.solve(*b)));
	}
	return result;
    };
    double2D DoubleArray::solve(double2D a, double2D b) {

	int m = a.dim1();
	int n = a.dim2();
	if (m == n) {
	    LU < double >lu(a);
	    return lu.solve(b);
	} else {
	    QR < double >qr(a);
	    return qr.solve(b);
	}
    };

    double2D_ptr DoubleArray::inverse(double2D_ptr matrix) {
	int m = matrix->dim1();
	return solve(matrix, identity(m, m));
    };
    double2D DoubleArray::inverse(double2D matrix) {
	int m = matrix.dim1();
	return solve(matrix, identity_(m, m));
    };

    double2D_ptr DoubleArray::pseudoInverse(double2D_ptr m) {
	/* TODO : pseudoInverse */
	double1D sv;
	double2D v, u;

	SVD < double >svd(*m);
	svd.getU(u);
	svd.getSingularValues(sv);
	svd.getV(v);
	/* TODO : pseudoInverse */
	return double2D_ptr((double2D *) null);
    };



    double2D_ptr DoubleArray::toDouble2D(int width, int n, ...) {
	double *array = new double[n];
	va_list num_list;
	va_start(num_list, n);

	for (int i = 0; i < n; i++) {
	    const double d = va_arg(num_list, const double);
	    array[i] = d;
	} va_end(num_list);

	int height = n / width;
	double2D_ptr result(new double2D(height, width, array));
	return result;
    };

    void DoubleArray::toDouble2D_(int m, int n, ...) {
	//int count = m * n;
	va_list num_list;
	va_start(num_list, n);

	for (int i = 0; i < n; i++) {
	    const double d = va_arg(num_list, const double);
	    //result[i] = d;
	    cout << "v:" << d << endl;
	} va_end(num_list);
	//return result;
    };

    double2D_ptr DoubleArray::toDouble2D(double *array, int m, int n) {
	int count = m * n;
	double *newarray = new double[count];
	arraycopy(array, 0, newarray, 0, count);
	double2D_ptr result(new double2D(m, n, newarray));
	//double2D_ptr result(new double2D(m, n, array));
	return result;
    };

    double2D_ptr DoubleArray::toDouble2D(double_array array, int length) {
	double2D_ptr result(new double2D(1, length, array.get()));
	return result;
    };

    const double DoubleArray::e = Math::pow(2, -53);
    double DoubleArray::getTolerance(int m, int n, double1D sv) {
	/* TODO : getTolerance */
	return -1;
    };

    double_array DoubleArray::toDoubleArray(double array[], int n) {
	double_array result(new double[n]);
	for (int x = 0; x != n; x++) {
	    result[x] = array[x];
	}
	return result;
    };

    double_array DoubleArray::toDoubleArray(int n, ...) {
	double_array result(new double[n]);
	va_list num_list;
	va_start(num_list, n);

	for (int i = 0; i < n; i++) {
	    const double d = va_arg(num_list, const double);
	    result[i] = d;
	} va_end(num_list);
	return result;
    };

    double_array DoubleArray::toDoubleArray(float_array floatArray, int n) {
	double_array result(new double[n]);
	for (int x = 0; x != n; x++) {
	    result[x] = floatArray[x];
	}
	return result;
    };
    double_array DoubleArray::toDoubleArray(double2D_ptr array) {
	int height = array->dim1();
	int width = array->dim2();
	double_array result(new double[height * width]);
	for (int y = 0; y < height; y++) {
	    for (int x = 0; x < width; x++) {
		result[y * width + x] = (*array)[y][x];
	    }
	}
	return result;
    };
    double_vector_ptr DoubleArray::toDoubleVector(double array[], int n) {
	double_vector_ptr result(new double_vector(n));
	for (int x = 0; x < n; x++) {
	    (*result)[x] = array[x];
	};
	return result;
    };
    double *DoubleArray::toCDoubleArray(double_vector_ptr doubleVector) {
	int size = doubleVector->size();
	double *result = new double[size];
	for (int x = 0; x < size; x++) {
	    result[x] = (*doubleVector)[x];
	}
	return result;
    };
    void DoubleArray::toCDoubleArray(double_vector_ptr doubleVector, double *cDoubleArray) {
	int size = doubleVector->size();
	for (int x = 0; x < size; x++) {
	    cDoubleArray[x] = (*doubleVector)[x];
	}
    };

    double_array DoubleArray::fromString(std::string str) {
	string_vector_ptr stringVec = StringVector::tokenize(str, ",\n");
	int size = stringVec->size();
	double_array result(new double[size]);
	for (int x = 0; x < size; x++) {
	    result[x] = _toDouble((*stringVec)[x]);
	}
	return result;
    };

#ifdef EXCEL_ACCESSIBLE
    void DoubleArray::storeToExcel(const string & filename, double_vector_ptr doubleVector) {
	Util::deleteExist(filename);
	bptr < SimpleExcelAccess > excel = SimpleExcelAccess::getValueStoreInstance(filename);
	int size = doubleVector->size();

	for (int x = 0; x != size; x++) {
	    string v = _toString((*doubleVector)[x]);
	    string_vector_ptr values = StringVector::fromString(1, v);
	    excel->insert(values);
	}
    };

    double_vector_ptr DoubleArray::loadFromExcel(const std::string & filename) {
	SimpleExcelAccess xls(filename);
	bptr < DBQuery > query = xls.retrieve();
	double_vector_ptr result(new double_vector());

	while (query->hasNext()) {
	    string_vector_ptr strresult = query->nextResult();
	    double_vector_ptr values = DBQuery::toDoubleVector(strresult);
	    double v = (*values)[0];
	    result->push_back(v);
	}
	return result;

    };
#endif

    double_vector_ptr DoubleArray::getReverse(double_vector_ptr vec) {
	int size = vec->size();
	double_vector_ptr result(new double_vector(size));
	for (int x = 0; x != size; x++) {
	    (*result)[x] = (*vec)[size - 1 - x];
	}
	return result;
    };
    double DoubleArray::sum(double_array array, int length) {
	double sum = 0;
	for (int x = 0; x != length; x++) {
	    sum += array[x];
	}
	return sum;
    };
    void DoubleArray::inspect(double_array array, int size) {
	double v = 0;
	for (int x = 0; x < size; x++) {
	    v = array[x];
            double stopHere = v;
	}
    };
    void DoubleArray::inspect(double_vector_ptr vector) {
	int size = vector->size();
	double v = 0;
	for (int x = 0; x < size; x++) {
	    v = (*vector)[x];
            double stopHere = v;
	}
    };
    //==========================================================================
    float2D_ptr FloatArray::toFloat2D(int width, int n, ...) {
	float *array = new float[n];
	va_list num_list;
	va_start(num_list, n);

	for (int i = 0; i < n; i++) {
	    const double d = va_arg(num_list, const double);
	    array[i] = static_cast < float >(d);
	} va_end(num_list);

	int height = n / width;
	float2D_ptr result(new float2D(height, width, array));
	return result;
    }

    float2D_ptr FloatArray::inverse(float2D_ptr matrix) {
	int m = matrix->dim1();
	int n = matrix->dim2();
	return solve(matrix, identity(m, n));
    };

    float2D_ptr FloatArray::solve(float2D_ptr a, float2D_ptr b) {

	int m = a->dim1();
	int n = a->dim2();
	float2D_ptr result;
	if (m == n) {
	    LU < float >lu(*a);
	    result = float2D_ptr(new float2D(lu.solve(*b)));
	} else {
	    QR < float >qr(*a);
	    result = float2D_ptr(new float2D(qr.solve(*b)));
	}
	return result;
    };

    float2D_ptr FloatArray::identity(int m, int n) {
	float2D_ptr result(new float2D(m, n));
	int size = Math::min(m, n);
	for (int x = 0; x < size; x++) {
	    (*result)[x][x] = 1;
	}
	return result;
    };

    float2D_ptr FloatArray::times(float2D_ptr a, float2D_ptr b) {
	int m = a->dim1();
	int n = a->dim2();
	int bn = b->dim2();

	float2D_ptr X(new float2D(m, bn));
	float1D Bcolj(n);
	for (int j = 0; j < bn; j++) {
	    for (int k = 0; k < n; k++) {
		Bcolj[k] = (*b)[k][j];
	    }
	    for (int i = 0; i < m; i++) {
		long double s = 0;
		for (int k = 0; k < n; k++) {
		    s += (*a)[i][k] * Bcolj[k];
		}
		(*X)[i][j] = s;
	    }
	}
	return X;
    };

    string_ptr FloatArray::toString(float2D_ptr m) {

	string_ptr str(new string());

	for (int i = 0; i < m->dim1(); i++) {
	    for (int j = 0; j < m->dim2() - 1; j++) {
		(*str) += _toString((*m)[i][j]) + " ";
	    }
	    (*str) += _toString((*m)[i][m->dim2() - 1]);
	    if (i < m->dim1() - 1) {
		(*str) += "\n";
	    }
	}
	return str;
    };
    //==========================================================================
#endif

    int IntArray::max(int_array array, int n) {
	int max = std::numeric_limits < double >::min();
	for (int x = 0; x != n; x++) {
	    const int &v = array[x];
	    max = v > max ? v : max;
	} return max;
    };

    double_array IntArray::toDoubleArray(int_array array, int n) {
	double_array result(new double[n]);
	for (int x = 0; x < n; x++) {
	    result[x] = array[x];
	}
	return result;
    };

    void IntArray::arraycopy(int_array src, int_array dest, int length) {
	for (int x = 0; x < length; x++) {
	    dest[x] = src[x];
    }};
    int_array IntArray::arraycopy(int_array src, int length) {
	int_array dest(new int[length]);
	arraycopy(src, dest, length);
	return dest;
    };
    std::string IntArray::toString(int *array, int n) {
	std::string result;
	for (int x = 0; x < n; x++) {
	    result += _toString(array[x]) + ",";
	}
	return result;
    };
    int_array IntArray::fromString(std::string str) {
	string_vector_ptr stringVec = StringVector::tokenize(str, ",");
	int size = stringVec->size();
	int_array result(new int[size]);
	for (int x = 0; x < size; x++) {
	    result[x] = _toInt((*stringVec)[x]);
	}
	return result;
    };
    void IntArray::arraycopy(int_array src, int *dest, int length) {
	for (int x = 0; x < length; x++) {
	    dest[x] = src[x];
	}
    };
    //==========================================================================
};

