#ifndef COLORSPACEH
#define COLORSPACEH
#include <java/lang.h>
#include <util.h>
#include <cms/core.h>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <vector>


namespace cms {
    namespace colorspace {
	using namespace java::lang;
	using namespace util;
	using namespace boost;
	using namespace std;
	class ColorSpace:public Object, public NameIF,
	    public virtual ValuePropertyIF {

	  private:
	    boolean setValuesLocked;
	  protected:
	    virtual int getNumberBands() = 0;
	    virtual shared_array < double >_getValues(shared_array <
						      double >values) = 0;
	    virtual void _setValues(shared_array < double >values) = 0;
	     ColorSpace():setValuesLocked(false) {
	    };
	  public:
	    static shared_array < double >
		cartesian2polarCoordinatesValues(shared_array <
						 double >cartesianValues) {
		using java::lang::Math;
		 shared_array < double >polarValues(new double[3]);


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
		} polarValues[2] *= (180.0 / Math::PI);
		while (polarValues[2] >= 360.0) {	// Not necessary, but included as a check.
		    polarValues[2] -= 360.0;
		}
		while (polarValues[2] < 0) {
		    polarValues[2] += 360.0;
		}
		return polarValues;
	    };
	    static shared_array < double >
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
	    };

	    boolean equalsValues(ColorSpace & colorSpace) {
	    }
	    virtual vector < string > getBandNames() = 0;
	    shared_ptr < string > getName() {
		return this->getClass().getSimpleName();
	    };
	    shared_array < double >getValues() {
		shared_array < double >values(new double[3]);
		return getValues(values);
	    };
	    shared_array < double >getValues(shared_array < double >values) {
		return _getValues(values);
	    };

	    static shared_array <
		double >polar2cartesianCoordinatesValues(shared_array <
							 double
							 >polarValues) {
		double t = (polarValues[2] * Math::PI) / 180.0;

		shared_array < double >cartesianValues(new double[3]);

		cartesianValues[0] = polarValues[0];
		cartesianValues[1] = polarValues[1] * Math::cos(t);
		cartesianValues[2] = polarValues[1] * Math::sin(t);

		return cartesianValues;
	    };
	    static shared_array < double >polar2cartesianCoordinatesValues(double
									   distance, double
									   angle) {
		double t = (angle * Math::PI) / 180.0;

		shared_array < double
		>cartesianValues(new double[2]);
		cartesianValues[0] = distance * Math::cos(t);
		cartesianValues[1] = distance * Math::sin(t);

		return cartesianValues;

	    };

	    void setValues(shared_array < double >values) {
		if (setValuesLocked == true) {
		    throw IllegalStateException("setValuesLocked == true");
		}
		_setValues(values);
	    };
	    void setValues(double value1, double value2, double value3) {
		double values[3] = { value1, value2, value3 };
		setValues(shared_array < double >(values));
	    };

	    void setValuesLock(boolean lock) {
		setValuesLocked = lock;
	    };


	};
    };
};
#endif

