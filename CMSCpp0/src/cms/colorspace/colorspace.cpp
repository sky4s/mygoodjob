#include "colorspace.h"
#include "java/lang.h"
#include "java/Exception.h"

namespace cms {
    namespace colorspace {


  /**
   * �åd��y��=>���y��
   * @param cartesianValues double[]
   * @return double[]
   */
	shared_array <
	    double >ColorSpace::
	    cartesian2polarCoordinatesValues(shared_array <
					     double >cartesianValues) {
	    using java::lang::Math;
	    //using namespace std;
	    /*if (cartesianValues.length != 3) {
	       throw new
	       IllegalArgumentException
	       ("cartesianValues.length != 3");
	       } */
	    using namespace boost;
	     shared_array < double >polarValues(new double[3]);


	     polarValues[0] = cartesianValues[0];
	    double t1 = cartesianValues[1];
	    double t2 = cartesianValues[2];
	     polarValues[1] = Math::sqrt(Math::pow(cartesianValues[1], 2) +
					 Math::pow(cartesianValues[2], 2));
	    if (t1 == 0 && t2 == 0) {
		polarValues[2] = 0;
	    } else {
		polarValues[2] = Math::atan2(t2, t1);
	    } polarValues[2] *= (180.0 / Math::PI);
	    while (polarValues[2] >= 360.0) {	// Not necessary, but included as a check.
		polarValues[2] -= 360.0;
	    }
	    while (polarValues[2] < 0) {
		polarValues[2] += 360.0;
	    }
	    return polarValues;
	}

	shared_array < double >ColorSpace::
	    cartesian2polarCoordinatesValues(double x, double y) {
	    shared_array < double >polarValues(new double[2]);

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
	}

	string & ColorSpace::getName() {
	    return this->getClass().getSimpleName();
	}
      ColorSpace::ColorSpace():setValuesLocked(false) {
	}

	shared_array < double >ColorSpace::getValues() {
	    shared_array < double >values(new double[2]);
	    return getValues(values);
	}

	shared_array < double >ColorSpace::getValues(shared_array <
						     double >values) {
	    /*if (values.length != getNumberBands()) {
	       throw new IllegalArgumentException("values.length != getNumberBands()");
	       } */
	    return _getValues(values);
	}

	shared_array <
	    double >ColorSpace::
	    polar2cartesianCoordinatesValues(shared_array < double
					     >polarValues) {
	    double t = (polarValues[2] * Math::PI) / 180.0;

	    shared_array < double
	    >cartesianValues(new double[3]);

	    cartesianValues[0] = polarValues[0];
	    cartesianValues[1] = polarValues[1] * Math::cos(t);
	    cartesianValues[2] = polarValues[1] * Math::sin(t);

	    return cartesianValues;
	}
	shared_array < double >ColorSpace::polar2cartesianCoordinatesValues(double
									    distance, double
									    angle) {
	    double t = (angle * Math::PI) / 180.0;

	    shared_array < double
	    >cartesianValues(new double[2]);
	    cartesianValues[0] = distance * Math::cos(t);
	    cartesianValues[1] = distance * Math::sin(t);

	    return cartesianValues;

	}
	void ColorSpace::setValues(shared_array < double >values) {
	    if (setValuesLocked == true) {
		throw IllegalStateException("setValuesLocked == true");
	    }
	    /*if (values.length != getNumberBands()) {
	       throw new
	       IllegalArgumentException
	       ("values.length != getNumberBands()");
	       } */
	    _setValues(values);
	}
	void ColorSpace::setValues(double value1, double value2,
				   double value3) {
	    double values[3] = { value1, value2, value3 };
	    setValues(shared_array < double >(values));
	}
	void ColorSpace::setValuesLock(boolean lock) {
	    setValuesLocked = lock;
	}
    };


};

