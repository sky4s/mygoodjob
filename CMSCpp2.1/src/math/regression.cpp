#include <includeall.h>
#pragma hdrstop
#include "regression.h"

//C系統文件
#include <assert.h>
#include <math.h>

//C++系統文件
#include <typeinfo>

//其他庫頭文件
#include <jama/jama_svd.h>

//本項目內頭文件
#include <math/doublearray.h>

namespace math {

#ifdef TNT_LIB
    //======================================================================
    // Regression
    //======================================================================
    Regression::Regression(double2D_ptr input,
			   double2D_ptr output):inputCoefs(input), output(output) {
    };
  Regression::Regression(double1D_ptr input, double1D_ptr output):inputCoefs(DoubleArray::transpose(input)),
	output(DoubleArray::transpose(output))
    {
    };
    double2D_ptr Regression::getCoefs() {
	return coefs;
    };
    double2D_ptr Regression::getPredict() {
	return getPredict0(inputCoefs, coefs);
    };
    double2D_ptr Regression::getPredict(double2D_ptr input) {
	return getPredict0(input, coefs);
    };
    double2D_ptr Regression::getPredict0(double2D_ptr input, double2D_ptr coefs) {
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
	/* TODO : getRMSD */
        throw java::lang::UnsupportedOperationException();
    };
    double Regression::getrSquare() {
	/* TODO : getrSquare */
        throw java::lang::UnsupportedOperationException();
    };
    void Regression::regress() {
	SVDLib svdLib(inputCoefs);

	int items = output->dim1();
	int outSize = output->dim2();
	coefs = double2D_ptr(new double2D(outSize, inputCoefs->dim2()));

	for (int x = 0; x < outSize; x++) {
	    double1D_ptr singleOutput(new double1D(items));
	    for (int y = 0; y < items; y++) {
		(*singleOutput)[y] = (*output)[y][x];
	    }
	    double1D_ptr singleCoefs = svdLib.getCoefficients(singleOutput);
	    DoubleArray::setDouble1D(coefs, singleCoefs, x);

	}
    };
    void Regression::setCoefs(double2D_ptr coefs) {
	this->coefs = coefs;
    };
    //======================================================================

    //======================================================================
    // PolynomialRegression
    //======================================================================
    double2D_ptr PolynomialRegression::
	processPolynomialInput(double2D_ptr input, const Polynomial::COEF & polynomialCoef) {
	int size = input->dim1();
	double1D_ptr in = DoubleArray::getDouble1D(input, 0);
	double1D_ptr firstcoef = Polynomial::getCoef(in, polynomialCoef);
	int width = firstcoef->dim();
	double2D_ptr polynomialInput(new double2D(size, width));
	for (int x = 0; x < size; x++) {
	    double1D_ptr in = DoubleArray::getDouble1D(input, x);
	    double1D_ptr coef = Polynomial::getCoef(in, polynomialCoef);
	    DoubleArray::setDouble1D(polynomialInput, coef, x);
	};
	return polynomialInput;
    };
    double2D_ptr PolynomialRegression::
	processPolynomialInput(double1D_ptr input, const Polynomial::COEF_1 & polynomialCoef) {

	int size = input->dim();
	double1D_ptr first = Polynomial::getCoef((*input)[0], polynomialCoef);
	int width = first->dim();
	double2D_ptr polynomialInput(new double2D(size, width));

	for (int x = 0; x < size; x++) {
	    double1D_ptr coef = Polynomial::getCoef((*input)[x], polynomialCoef);
	    DoubleArray::setDouble1D(polynomialInput, coef, x);
	}
	return polynomialInput;
    };
    double2D_ptr PolynomialRegression::processRegressionOutput(double1D_ptr output) {
	double2D_ptr regressionOutput = DoubleArray::transpose(output);
	return regressionOutput;
    };
    double2D_ptr PolynomialRegression::getPredict0(double2D_ptr input,
						   double2D_ptr coefs,
						   const Polynomial::COEF_3 & polynomialCoef) {
	return Regression::getPredict0(processPolynomialInput(input, polynomialCoef), coefs);
    };

    double2D_ptr PolynomialRegression::getPredict() {
	return getPredict(inputCoefs);
    };
    double2D_ptr PolynomialRegression::getPredict(double2D_ptr input) {
	return Regression::getPredict0(processPolynomialInput(input, polynomialCoef), coefs);
    };

  PolynomialRegression::PolynomialRegression(double2D_ptr input, double2D_ptr output, const Polynomial::COEF_3 & polynomialCoef):Regression
	(processPolynomialInput(input, polynomialCoef), output),
	polynomialCoef(polynomialCoef) {
    };
    PolynomialRegression::PolynomialRegression(double2D_ptr input,
					       double2D_ptr output,
					       const Polynomial::
					       COEF &
					       polynomialCoef):Regression
	(processPolynomialInput(input, polynomialCoef), output), polynomialCoef(polynomialCoef) {
    };
    PolynomialRegression::PolynomialRegression(double1D_ptr input,
					       double1D_ptr output,
					       const Polynomial::
					       COEF_1 &
					       polynomialCoef):Regression
	(processPolynomialInput(input, polynomialCoef),
	 processRegressionOutput(output)), polynomialCoef(polynomialCoef) {
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
    double1D_ptr Polynomial::getCoef(double1D_ptr xyz, const COEF_3 & coefs) {
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
    double1D_ptr Polynomial::getCoef(double x, double y, double z, const COEF_3 & coefs) {

	double1D_ptr coef3;
	switch (coefs.coef3_) {
	case COEF3_::BY_3:
	case COEF3_::BY_3C:
	    coef3 = Coef3X::getCoef3By3(x, y, z);
	    break;
	case COEF3_::BY_6:
	case COEF3_::BY_6C:
	    coef3 = Coef3X::getCoef3By6(x, y, z);
	    break;
	case COEF3_::BY_7:
	case COEF3_::BY_7C:
	    coef3 = Coef3X::getCoef3By7(x, y, z);
	    break;
	case COEF3_::BY_9:
	case COEF3_::BY_9C:
	    coef3 = Coef3X::getCoef3By9(x, y, z);
	    break;
	case COEF3_::BY_10:
	case COEF3_::BY_10C:
	    coef3 = Coef3X::getCoef3By10(x, y, z);
	    break;
	};
	if (coefs.withConstant) {
	    return addCoef3WithConstant(coef3);
	} else {
	    return coef3;
	}
    };

    double1D_ptr Polynomial::getCoefWithConstant(double x, int coefs) {
	double1D_ptr coef(new double1D(coefs));
	(*coef)[0] = 1.0;
	for (int i = 1; i < coefs; i++) {
	    (*coef)[i] = x * (*coef)[i - 1];
	}
	return coef;
    };
    double1D_ptr Polynomial::getCoef(double1D_ptr variables, const COEF & coefs) {
	const std::type_info & info = typeid(coefs);
	if (info == typeid(COEF_1)) {
	    if (variables->dim() == 1) {
		return getCoef((*variables)[0], static_cast < const COEF_1 & >(coefs));
	    } else {
		return getCoef(variables, static_cast < const COEF_1 & >(coefs));
	    }
	} else if (info == typeid(COEF_3)) {
	    return getCoef(variables, static_cast < const COEF_3 & >(coefs));
	}
	throw java::lang::IllegalArgumentException();
    };
    Polynomial::COEF::COEF(int item,
			   bool withConstant):item(withConstant ? item +
						   1 : item), withConstant(withConstant) {

    };

    void Polynomial::COEF::dummy() {
    };

    string_ptr Polynomial::COEF::toString() {
	string_ptr str(new string(typeid(*this).name()));
	return str;
    };


  Polynomial::COEF_1::COEF_1(int item, bool withConstant):COEF(item, withConstant) {


    };
    const Polynomial::COEF_1 & Polynomial::COEF_1::BY_1 = COEF_1(1, false);
    const Polynomial::COEF_1 & Polynomial::COEF_1::BY_1C = COEF_1(1, true);
    const Polynomial::COEF_1 & Polynomial::COEF_1::BY_2 = COEF_1(2, false);
    const Polynomial::COEF_1 & Polynomial::COEF_1::BY_2C = COEF_1(2, true);
    const Polynomial::COEF_1 & Polynomial::COEF_1::BY_3 = COEF_1(3, false);
    const Polynomial::COEF_1 & Polynomial::COEF_1::BY_3C = COEF_1(3, true);
    Polynomial::COEF_3::COEF_3(int item,
			       bool withConstant,
			       COEF3_ coef3_):COEF(item, withConstant), coef3_(coef3_) {

    };
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_3 = COEF_3(3, false, COEF3_::BY_3);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_3C = COEF_3(3, true, COEF3_::BY_3C);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_6 = COEF_3(6, false, COEF3_::BY_6);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_6C = COEF_3(6, true, COEF3_::BY_6C);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_7 = COEF_3(7, false, COEF3_::BY_7);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_7C = COEF_3(7, true, COEF3_::BY_7C);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_9 = COEF_3(9, false, COEF3_::BY_9);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_9C = COEF_3(9, true, COEF3_::BY_9C);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_10 = COEF_3(10, false, COEF3_::BY_10);
    const Polynomial::COEF_3 & Polynomial::COEF_3::BY_10C = COEF_3(10, true, COEF3_::BY_10C);
    double1D_ptr Polynomial::Coef3X::getCoef3By3(double x, double y, double z) {
	double1D_ptr coef(new double1D(3));
	(*coef)[0] = x;
	(*coef)[1] = y;
	(*coef)[2] = z;
	return coef;
    };
    double1D_ptr Polynomial::Coef3X::getCoef3By6(double x, double y, double z) {
	double1D_ptr coef(new double1D(6));
	(*coef)[0] = x;
	(*coef)[1] = y;
	(*coef)[2] = z;
	(*coef)[3] = x * y;
	(*coef)[4] = y * z;
	(*coef)[5] = z * x;
	return coef;
    };
    double1D_ptr Polynomial::Coef3X::getCoef3By7(double x, double y, double z) {
	double1D_ptr coef(new double1D(7));
	(*coef)[0] = x;
	(*coef)[1] = y;
	(*coef)[2] = z;
	(*coef)[3] = x * y;
	(*coef)[4] = y * z;
	(*coef)[5] = z * x;
	(*coef)[6] = x * y * z;
	return coef;
    };
    double1D_ptr Polynomial::Coef3X::getCoef3By9(double x, double y, double z) {
	double1D_ptr coef(new double1D(9));
	(*coef)[0] = x;
	(*coef)[1] = y;
	(*coef)[2] = z;
	(*coef)[3] = x * y;
	(*coef)[4] = y * z;
	(*coef)[5] = z * x;
	(*coef)[6] = x * x;
	(*coef)[7] = y * y;
	(*coef)[8] = z * z;
	return coef;
    };
    double1D_ptr Polynomial::Coef3X::getCoef3By10(double x, double y, double z) {
	double1D_ptr coef(new double1D(10));
	(*coef)[0] = x;
	(*coef)[1] = y;
	(*coef)[2] = z;
	(*coef)[3] = x * y;
	(*coef)[4] = y * z;
	(*coef)[5] = z * x;
	(*coef)[6] = x * x;
	(*coef)[7] = y * y;
	(*coef)[8] = z * z;
	(*coef)[9] = x * y * z;
	return coef;
    };
    //======================================================================
#endif

    //======================================================================
    // LinearRegression
    //======================================================================
    LinearRegression::LinearRegression(double_vector_ptr x, double_vector_ptr y) {
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

