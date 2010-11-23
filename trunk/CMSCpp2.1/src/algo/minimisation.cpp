#include <includeall.h>
#pragma hdrstop
#include "minimisation.h"

//C系統文件

//C++系統文件

//vcl庫頭文件

//其他庫頭文件
#include "asa047.H"
//本項目內頭文件

//本項目內gui頭文件

namespace algo {
    using namespace java::lang;
    using namespace math;


    double minimisationFunction(double x[]) {
	double_vector_ptr params = DoubleArray::toDoubleVector(x, Minimisation::minimisation_n);
	 return Minimisation::mf_ptr->function(params);
    };
  Minimisation::Minimisation():konvge(3) {
    };
    void Minimisation::nelderMead(bptr < MinimisationFunction > mf, double_vector_ptr start,
				  double_vector_ptr step, double ftol, int nmax) {
	if (start->size() != step->size()) {
	    throw IllegalArgumentException("start->size() != step->size()");
	}
	mf_ptr = mf;
	minimisation_n = start->size();
	this->n = start->size();
	this->kcount = nmax;

	double *cstart = DoubleArray::toCDoubleArray(start);
	double *cstep = DoubleArray::toCDoubleArray(step);
	double *xmin = new double[n];

	nelmin(minimisationFunction, n, cstart, xmin, &ynewlo, ftol, cstep, konvge, kcount,
	       &icount, &numres, &ifault);

	paramValues = DoubleArray::toDoubleVector(xmin, n);
	step = DoubleArray::toDoubleVector(cstep, n);

	delete[]xmin;
	delete[]cstep;
	delete[]cstart;
    };
    int Minimisation::getNiter() {
	return icount;
    };
    int Minimisation::getNmax() {
	return numres;
    };
    double Minimisation::getMinimum() {
	return ynewlo;
    };
    void Minimisation::setNrestartsMax(int nrm) {
	this->konvge = nrm;
    };
    int Minimisation::getNrestartMax() {
	return konvge;
    };
    double_vector_ptr Minimisation::getParamValues() {
	return paramValues;
    };
    Error Minimisation::getError() {
	switch (ifault) {
	case 0:
	    return Error::NoErrors;
	case 1:
	    return Error::IllegalValue;
	case 2:
	    return Error::IterationTerminate;
	default:
	    return Error::Unknow;

	}
    };
};

