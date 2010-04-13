#include <includeall.h>
#pragma hdrstop
#include "svd.h"

//C系統文件

//C++系統文件

//其他庫頭文件
#include <jama/jama_svd.h>
//本項目內頭文件

namespace math {

    using namespace JAMA;
    //======================================================================
    // SVDLib
    //======================================================================
    longdouble2D SVDLib::toLongDouobleArray(double2D_ptr array) {
	int m = array->dim1();
	int n = array->dim2();
	longdouble2D result(m, n);
	for (int x = 0; x < m; x++) {
	    for (int y = 0; y < n; y++) {
		result[x][y] = (*array)[x][y];
	    };
	};
	return result;
    };
    double2D_ptr SVDLib::toDoubleArray(const longdouble2D & array) {
	int m = array.dim1();
	int n = array.dim2();
	double2D_ptr result(new double2D(m, n));
	for (int x = 0; x < m; x++) {
	    for (int y = 0; y < n; y++) {
		(*result)[x][y] = array[x][y];
	    };
	};
	return result;
    };
    double1D_ptr SVDLib::toDoubleArray(const longdouble1D & array) {
	int size = array.dim();
	double1D_ptr result(new double1D(size));
	for (int x = 0; x < size; x++) {
	    (*result)[x] = array[x];
	};
	return result;
    };

  SVDLib::SVDLib(double2D_ptr array):sv(new double1D()), v(new double2D()),
	u(new double2D()) {
	svd(array);
    };
    double1D_ptr SVDLib::getCoefficients(double1D_ptr output) {
	double1D_ptr coef = svbksb(u, sv, v, output);
	return coef;
    };
    double1D_ptr SVDLib::getPredict(double2D_ptr input, double1D_ptr coefs) {
	double1D_ptr predict(new double1D(input->dim1()));

	for (int i = 0; i < input->dim1(); i++) {
	    for (int j = 0; j < input->dim2(); j++) {
		(*predict)[i] += (*input)[i][j] * (*coefs)[j];
	    }
	}
	return predict;
    };
    double1D_ptr SVDLib::getSingularValues() {
	return sv;
    };
    double2D_ptr SVDLib::getU() {
	return u;
    };
    double2D_ptr SVDLib::getV() {
	return v;
    };
    void SVDLib::svd(double2D_ptr input) {
#ifdef  _USE_LONG_DOUBLE_
	SVD < long double >svd(*input);
	svd.getU(*u);
	svd.getSingularValues(*sv);
	svd.getV(*v);
#else
	SVD < long double >svd(toLongDouobleArray(input));
	longdouble2D u_;
	longdouble1D sv_;
	longdouble2D v_;
	svd.getU(u_);
	svd.getSingularValues(sv_);
	svd.getV(v_);
	u = toDoubleArray(u_);
	sv = toDoubleArray(sv_);
	v = toDoubleArray(v_);
#endif

    };


    double1D_ptr SVDLib::svbksb(const double2D_ptr u,
				const double1D_ptr sv,
				const double2D_ptr v,
				const double1D_ptr output) {
	double s;
	int m = u->dim1(), n = u->dim2();
	double1D_ptr coef(new double1D(n));
	double1D tmp(n);

	for (int i = 0; i < n; i++) {
	    s = 0.0;
	    if ((*sv)[i] != 0) {
		for (int j = 0; j < m; j++) {
		    s += (*u)[j][i] * (*output)[j];
		};
		s /= (*sv)[i];
	    }
	    tmp[i] = s;
	}
	for (int i = 0; i < n; i++) {
	    s = 0.0;
	    for (int j = 0; j < n; j++) {
		s += (*v)[i][j] * tmp[j];
	    }
	    (*coef)[i] = s;
	}
	//cout<<*coef<<endl;
	return coef;
    };
    //======================================================================
};

