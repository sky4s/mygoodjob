#include <includeall.h>
#pragma hdrstop
#include "colorspace.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
//#include <math/doublearray.h>

namespace cms {
    namespace colorspace {
	using namespace boost;
	using namespace std;
	using namespace java::lang;
	 ColorSpace::ColorSpace():setValuesLocked(false) {
	};

	 double_array
	    ColorSpace::
	    cartesian2polarCoordinatesValues(double_array cartesianValues)
	{

	    double_array polarValues(new double[3]);


	     polarValues[0] = cartesianValues[0];
	    double t1 = cartesianValues[1];
	    double t2 = cartesianValues[2];
	     polarValues[1] =
		Math::sqrt(Math::pow(cartesianValues[1], 2) +
			   Math::pow(cartesianValues[2], 2));
	    if (t1 == 0 && t2 == 0) {
		polarValues[2] = 0;
	    } else {
		polarValues[2] = Math::atan2(t2, t1);
	    }
	    polarValues[2] *= (180.0 / Math::PI);
	    while (polarValues[2] >= 360.0) {	// Not necessary, but included as a check.
		polarValues[2] -= 360.0;
	    }
	    while (polarValues[2] < 0) {
		polarValues[2] += 360.0;
	    }
	    return polarValues;
	};
	double_array
	    ColorSpace::cartesian2polarCoordinatesValues(double x,
							 double y) {
	    double_array polarValues(new double[2]);

	    double t1 = x;
	    double t2 = y;
	    polarValues[0] =
		Math::sqrt(Math::pow(t1, 2) + Math::pow(t2, 2));
	    if (t1 == 0 && t2 == 0) {
		polarValues[1] = 0;
	    } else {
		polarValues[1] = Math::atan2(t2, t1);
	    }
	    polarValues[1] *= (180.0 / Math::PI);
	    while (polarValues[1] >= 360.0) {	// Not necessary, but included as a check.
		polarValues[1] -= 360.0;
	    }
	    while (polarValues[1] < 0) {
		polarValues[1] += 360.0;
	    }
	    return polarValues;
	};

	bool ColorSpace::equalsValues(ColorSpace & colorSpace) {
	    double_array thisValues = this->getValues();
	    /* TODO : equalsValues */
	}
	string_ptr ColorSpace::getName() {
	    return this->getClass().getSimpleName();
	};
	double_array ColorSpace::getValues() {
	    double_array values(new double[3]);
	    return getValues(values);
	};
	double_array ColorSpace::getValues(double_array values) {
	    return _getValues(values);
	};

	double_array ColorSpace::
	    polar2cartesianCoordinatesValues(double_array polarValues) {
	    double t = (polarValues[2] * Math::PI) / 180.0;

	    double_array cartesianValues(new double[3]);

	    cartesianValues[0] = polarValues[0];
	    cartesianValues[1] = polarValues[1] * Math::cos(t);
	    cartesianValues[2] = polarValues[1] * Math::sin(t);

	    return cartesianValues;
	};
	double_array ColorSpace::polar2cartesianCoordinatesValues(double
								  distance,
								  double
								  angle) {
	    double t = (angle * Math::PI) / 180.0;

	    double_array cartesianValues(new double[2]);
	    cartesianValues[0] = distance * Math::cos(t);
	    cartesianValues[1] = distance * Math::sin(t);

	    return cartesianValues;

	};

	void ColorSpace::setValues(double_array values) {
	    if (setValuesLocked == true) {
		throw IllegalStateException("setValuesLocked == true");
	    }
	    _setValues(values);
	};
	void ColorSpace::setValues(double value1, double value2,
				   double value3) {
	    double_array values(new double[3]);
	    values[0] = value1;
	    values[1] = value2;
	    values[2] = value3;
	    setValues(values);
	};

	void ColorSpace::setValuesLock(bool lock) {
	    setValuesLocked = lock;
	};

	const string_ptr ColorSpace::toString() {
	    double_array values = this->getValues();
	    return math::DoubleArray::toString(values, getNumberBands());
	};
	double_array ColorSpace::
	    getValuesFromString(const string_ptr string) {
	    using namespace cms::util;
	    string_vector_ptr stringvector =
		StringVector::tokenize(*string, "[], '");
	    if (stringvector->size() != 3) {
		throw IllegalArgumentException("stringvector->size() != 3");
	    }
	    double_array result(new double[3]);
	    result[0] = _toDouble((*stringvector)[0]);
	    result[1] = _toDouble((*stringvector)[1]);
	    result[2] = _toDouble((*stringvector)[2]);
	    return result;
	};
    };
};

