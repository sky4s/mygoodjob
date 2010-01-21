#include "colorspace.h"
#include "java/lang.h"
//#include <boost/scoped_array.hpp>

namespace cms {
    namespace colorspace {
	using std::string;

  /**
   * 笛卡兒座標=>極座標
   * @param cartesianValues double[]
   * @return double[]
   */
	shared_array<double> ColorSpace::cartesian2polarCoordinatesValues(double
							     *cartesianValues) {
	    using java::lang::Math;
	    //using namespace std;
		/*if (cartesianValues.length != 3) {
		   throw new
		   IllegalArgumentException
		   ("cartesianValues.length != 3");
		   } */
		//double *polarValues = new double[3];
	     //auto_ptr < double *> polarValues(new double[3]);
             using namespace boost;
             shared_array<double> polarValues(new double[3]);


	     polarValues[0] = cartesianValues[0];
	    double t1 = cartesianValues[1];
	    double t2 = cartesianValues[2];
	     polarValues[1] = Math::sqrt(Math::pow(cartesianValues[1], 2) +
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
	}

	shared_array<double>  ColorSpace::
	    cartesian2polarCoordinatesValues(double x, double y) {
	    //double[] polarValues = new double[2];
            shared_array<double> polarValues(new double[2]);

	    double t1 = x;
	    double t2 = y;
	    polarValues[0] = Math::sqrt(Math::pow(t1, 2) + Math::pow(t2, 2));
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
    };


};

