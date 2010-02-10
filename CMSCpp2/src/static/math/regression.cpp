#include "regression.h"

//C系統文件
#include <assert.h>
#include <math.h>

//C++系統文件

//其他庫頭文件
#include <jama/jama_svd.h>

//本項目內頭文件
#include <math/doublearray.h>

namespace math {
    using namespace JAMA;
    //======================================================================
    // SVDLib
    //======================================================================
     SVDLib::SVDLib():sv(new double1D()), v(new double2D()),
	u(new double2D()) {
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
	SVD < double >svd(*input);
	svd.getU(*u);
	svd.getSingularValues(*sv);
	svd.getV(*v);

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
		}
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

	return coef;


    };
    //======================================================================

    //======================================================================
    // Regression
    //======================================================================
  Regression::Regression(double2D_ptr input, double2D_ptr output):inputCoefs(input),
	output(output)
    {
    };
  Regression::Regression(double1D_ptr input, double1D_ptr output):inputCoefs(DoubleArray::transpose(input)),
	output(DoubleArray::transpose(output))
    {
    };
    double2D_ptr Regression::getCoefs() {
	return coefs;
    };
    double2D_ptr Regression::getPredict() {
	return getPredict(inputCoefs, coefs);
    };
    double2D_ptr Regression::getPredict(double2D_ptr input,
					double2D_ptr coefs) {
	int m = coefs->dim1();
	int n = input->dim1();
	double2D_ptr predict(new double2D(m, n));

	for (int x = 0; x < m; x++) {
	    double1D_ptr coef = DoubleArray::getDouble1D(coefs, x);
	    double1D_ptr v = SVDLib::getPredict(input, coef);
	    DoubleArray::setDouble1D(predict, v, x);
	}
	return DoubleArray::transpose(predict);
    };
    double Regression::getRMSD() {
    };
    double Regression::getrSquare() {
    };
    void Regression::regress() {
	SVDLib svdLib;
	svdLib.svd(inputCoefs);

	int items = output->dim1();
	int outSize = output->dim2();
	//coefs = new double[outSize][];
	coefs.reset(new double2D(outSize, items));

	for (int x = 0; x < outSize; x++) {
	    double1D_ptr singleOutput(new double1D(items));
	    for (int y = 0; y < items; y++) {
		(*singleOutput)[y] = (*output)[y][x];
	    }
	    double1D_ptr singleCoefs =
		svdLib.getCoefficients(singleOutput);
	    DoubleArray::setDouble1D(coefs, singleCoefs, x);
	}
    };
    void Regression::setCoefs(double2D_ptr coefs) {
	this->coefs = coefs;
    };
    //======================================================================

    //======================================================================
    // Polynomial
    //======================================================================
    double1D_ptr Polynomial::addCoef3WithConstant(double1D_ptr coef3) {
	int size = coef3->dim();
	double1D_ptr newcoef(new double1D(size + 1));

	DoubleArray::arraycopy(coef3, 0, newcoef, 1, size);
	(*newcoef)[0] = 1.;
	return newcoef;
    };
    double1D_ptr Polynomial::getCoef(double1D_ptr xyz,
				     const COEF_3 & coefs) {
	if (xyz->dim() != 3) {
	    throw java::lang::IllegalArgumentException("xyz->dim() != 3");
	}
	return getCoef((*xyz)[0], (*xyz)[1], (*xyz)[2], coefs);
    };
    double1D_ptr Polynomial::getCoef(double x, const COEF_1 & coefs) {
	double1D_ptr coef = getCoefWithConstant(x, coefs.item);
	if (!coefs.withConstant) {
	    coef = DoubleArray::getRangeCopy(coef, 1, coef->dim() - 1);
	}
	return coef;
    };
    double1D_ptr Polynomial::getCoef(double x, double y, double z,
				     const COEF_3 & coefs) {
    };
    double1D_ptr Polynomial::getCoefWithConstant(double x, int coefs) {
	double1D_ptr coef(new double1D(coefs));
	(*coef)[0] = 1.0;
	for (int i = 1; i < coefs; i++) {
	    (*coef)[i] = x * (*coef)[i - 1];
	}
	return coef;
    };

  Polynomial::COEF::COEF(int item, bool withConstant):item(withConstant ? item +
	 1 : item),
	withConstant(withConstant) {

    };
    Polynomial::COEF_1::COEF_1(int item, bool withConstant):COEF(item,
								 withConstant)
    {

    };

    const Polynomial::COEF_1 & Polynomial::COEF_1::BY_1 = COEF_1(1, false);
    const Polynomial::COEF_1 & Polynomial::COEF_1::BY_1C = COEF_1(1, true);
    const Polynomial::COEF_1 & Polynomial::COEF_1::BY_2 = COEF_1(2, false);
    const Polynomial::COEF_1 & Polynomial::COEF_1::BY_2C = COEF_1(2, true);
    const Polynomial::COEF_1 & Polynomial::COEF_1::BY_3 = COEF_1(3, false);
    const Polynomial::COEF_1 & Polynomial::COEF_1::BY_3C = COEF_1(3, true);

    Polynomial::COEF_3::COEF_3(int item, bool withConstant):COEF(item,
								 withConstant)
    {

    };
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_3 = COEF_3(3, false);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_3C = COEF_3(3, true);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_6 = COEF_3(6, false);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_6C = COEF_3(6, true);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_7 = COEF_3(7, false);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_7C = COEF_3(7, true);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_9 = COEF_3(9, false);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_9C = COEF_3(9, true);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_10 =
	COEF_3(10, false);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_10C =
	COEF_3(10, true);
    //======================================================================

    //======================================================================
    // LinearRegression
    //======================================================================
    LinearRegression::LinearRegression(double_vector_ptr x,
				       double_vector_ptr y) {
	int n = x->size();
	// calculate the averages of arrays x and y
	double xa = 0, ya = 0;
	for (int i = 0; i < n; i++) {
	    xa += (*x)[i];
	    ya += (*y)[i];
	};
	xa /= n;
	ya /= n;
	// calculate auxiliary sums
	double xx = 0, yy = 0, xy = 0;
	for (int i = 0; i < n; i++) {
	    double tmpx = (*x)[i] - xa, tmpy = (*y)[i] - ya;
	    xx += tmpx * tmpx;
	    yy += tmpy * tmpy;
	    xy += tmpx * tmpy;
	}
	// calculate regression line parameters// make sure slope is not infinite
	assert(fabs(xx) != 0);
	m_b = xy / xx;
	m_a = ya - m_b * xa;
	m_coeff = (fabs(yy) == 0) ? 1 : xy / sqrt(xx * yy);
    };
    double LinearRegression::getValue(double x) {
	return m_a + m_b * x;
    };
    double LinearRegression::getSlope() {
	return m_b;
    };
    double LinearRegression::getIntercept() {
	return m_a;
    };
    double LinearRegression::getCoefficient() {
	return m_coeff;
    };
    //======================================================================
};

