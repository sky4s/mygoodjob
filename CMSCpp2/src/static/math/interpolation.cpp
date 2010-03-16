#include "interpolation.h"

//C系統文件

//C++系統文件


//其他庫頭文件
#include <math.hpp>

//本項目內頭文件
#include "searcher.h"
#include <math/doublearray.h>

namespace math {
    using namespace java::lang;
    using namespace boost;
    using namespace std;


    int Interpolation::getxnPartStartIndex(double_vector_ptr xn,
					   double x, int width) {
    /**
     * 測試看看getxnPartStartIndexForExtrapolation套用下去會不會出問題
     */
	return getxnPartStartIndexForExtrapolation(xn, x, width);
    };

    int Interpolation::
	getxnPartStartIndexForExtrapolation(double_vector_ptr xn,
					    double x, int width) {
	if (width < 2) {
	    throw IllegalArgumentException("width < 2");
	}
	int_vector_ptr xnIndexArray =
	    Searcher::leftNearSequentialSearchAll(xn, x);
	if ((*xnIndexArray)[1] >= 0) {
	    return -((*xnIndexArray)[1] + 1);
	}
	int xnIndex =
	    (*xnIndexArray)[0] !=
	    -1 ? (*xnIndexArray)[0] : -(*xnIndexArray)[1];
	int startIndex = xnIndex - (width / 2 - 1);
	startIndex = startIndex < 0 ? 0 : startIndex;
	startIndex =
	    startIndex >
	    (static_cast <
	     signed int >(xn->size()) - width) ? xn->size() -
	    width : startIndex;
	return startIndex;
    };


  Interpolation::Interpolation(double_vector_ptr xn, double_vector_ptr yn):_xn(xn),
	_yn(yn)
    {
	if (xn->size() < 4 || yn->size() < 4 || xn->size() != yn->size()) {
	    throw
		IllegalArgumentException
		("xn.length < 4 || yn.length < 4 || xn->size() != yn->size()");
	}

    };
    double Interpolation::linear(double x1, double x2, double y1,
				 double y2, double x) {
	double result = y1 + (y2 - y1) * ((x - x1) / (x2 - x1));
	return result;
    };
    double Interpolation::linear(double_vector_ptr xn,
				 double_vector_ptr yn, double x) {
	int index = getxnPartStartIndex(xn, x, 2);
	return linear((*xn)[index], (*xn)[index + 1], (*yn)[index],
		      (*yn)[index + 1], x);
    };
    double Interpolation::linear2(double_vector_ptr xn,
				  double_vector_ptr yn, double x) {
	if (xn->size() != 2 || xn->size() != 2) {
	    throw IllegalArgumentException();
	}
	double x0 = (*xn)[0];
	double x1 = (*xn)[1];
	return linear((*xn)[0], (*xn)[1], (*yn)[0], (*yn)[1], x);
    };
    double Interpolation::interpolate(double_vector_ptr xn,
				      double_vector_ptr yn, double x,
				      Algo interpolationType) {
	switch (interpolationType) {
	case Linear:
	    return linear2(xn, yn, x);
	default:
	    throw IllegalArgumentException();
	};
    };

    double Interpolation::interpolate(double x, Algo interpolationType) {
	double_vector_ptr xnpart(nil_double_vector);
	double_vector_ptr ynpart(nil_double_vector);

	int noInterpolateIndex = -1;
	switch (interpolationType) {
	case Linear:{
		int startIndex = getxnPartStartIndex(_xn, x, 2);
		if (startIndex < 0) {
		    noInterpolateIndex = (-startIndex) - 1;
		    break;
		}
		xnpart = getPart(_xn, startIndex, 2);
		ynpart = getPart(_yn, startIndex, 2);
		break;
	    }
	};

	if (noInterpolateIndex != -1) {
	    return (*_yn)[noInterpolateIndex];
	} else {
	    return interpolate(xnpart, ynpart, x, interpolationType);
	}
    };

    double_vector_ptr Interpolation::getPart(double_vector_ptr
					     array,
					     int startIndex, int width) {
	double_vector_ptr part(new double_vector);
	DoubleArray::vectorcopy(array, startIndex, part, 0, width);

	return part;
    };
    //======================================================================

    //======================================================================
    // Interpolation1DLUT
    //======================================================================
    double Interpolation1DLUT::interpolationValue(double key,
						  double_vector_ptr
						  keys,
						  double_vector_ptr
						  values, Algo type) {
	if (key == -key) {
	    key = 0;
	}
	int index = Searcher::leftNearSequentialSearch(keys, key);
	int interpoStart = 0;
	bool head = false;
	bool tail = false;

	//==========================================================================
	// 內插位置點的判斷
	//==========================================================================
	if (index == 0) {
	    interpoStart = index;
	    head = true;
	} else if (index == (keys->size() - 1)) {
	    interpoStart = index - 3;
	    tail = true;
	} else if (index == (keys->size() - 2)) {
	    interpoStart = index - 2;
	    tail = true;
	} else if (index == -1) {
	    throw IndexOutOfBoundsException("key[" + lexical_cast <
					    string >
					    (key) + "] out of keys[" +
					    lexical_cast < string >
					    ((*keys)[0]) + "~" +
					    lexical_cast < string >
					    ((*keys)[keys->size() - 1])
					    + "]");
	} else {
	    interpoStart = index - 1;
	}
	//==========================================================================

	double_vector_ptr xn(new double_vector);
	double_vector_ptr yn(new double_vector);

	DoubleArray::vectorcopy(keys, interpoStart, xn, 0, 4);
	DoubleArray::vectorcopy(values, interpoStart, yn, 0, 4);
	double result = NaN;

	switch (type) {
	case Linear:
	    if (tail) {
		xn = DoubleArray::getRangeCopy(xn, 2, 3);
		yn = DoubleArray::getRangeCopy(yn, 2, 3);
	    } else if (head) {
		xn = DoubleArray::getRangeCopy(xn, 0, 1);
		yn = DoubleArray::getRangeCopy(yn, 0, 1);
	    } else {
		xn = DoubleArray::getRangeCopy(xn, 1, 2);
		yn = DoubleArray::getRangeCopy(yn, 1, 2);
	    }

	    if ((*xn)[0] == (*xn)[1]) {
                //遇到同值的狀況, 只好例外處理, 否則無法內插
		result = ((*yn)[0] + (*yn)[1]) / 2;
	    } else {
		result = Interpolation::interpolate(xn, yn, key, Linear);
	    }
	    break;
	}
	return result;
    };

    Interpolation1DLUT::Interpolation1DLUT(double_vector_ptr key,
					   double_vector_ptr value) {
	this->keyArray = key;
	this->valueArray = value;
	size = keyArray->size();
	/*double k0 = (*keyArray)[0];
	   double k1 = (*keyArray)[1];
	   double v0 = (*valueArray)[0];
	   double v1 = (*valueArray)[1];
	   double a = 1; */

    };
    double Interpolation1DLUT::correctKeyInRange(double key) {
	return correctInRange(key, keyArray);
    };
    double Interpolation1DLUT::correctValueInRange(double value) {
	return correctInRange(value, valueArray);
    };

    double Interpolation1DLUT::correctInRange(double number,
					      double_vector_ptr
					      numberArray) {
	int arraySize = numberArray->size();
	_hasCorrectedInRange = false;
	if (number < (*numberArray)[0]) {
	    _hasCorrectedInRange = true;
	    return (*numberArray)[0];
	} else if (number > (*numberArray)[arraySize - 1]
	    ) {
	    _hasCorrectedInRange = true;
	    return (*numberArray)[arraySize - 1];
	}
	return number;

    };

    double Interpolation1DLUT::getKey(double value) {
	return interpolationValue(value, valueArray, keyArray, Linear);
    };
    double Interpolation1DLUT::getValue(double key) {
	return interpolationValue(key, keyArray, valueArray, Linear);
    };
    bool Interpolation1DLUT::isKeyInRange(double key) {
	return key >= (*keyArray)[0] && key <= (*keyArray)[size - 1];
    };
    bool Interpolation1DLUT::isValueInRange(double value) {
	return value >= (*valueArray)[0]
	    && value <= (*valueArray)[size - 1];
    };
    bool Interpolation1DLUT::hasCorrectedInRange() {
	return _hasCorrectedInRange;
    }
};

