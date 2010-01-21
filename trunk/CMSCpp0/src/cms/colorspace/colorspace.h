#ifndef COLORSPACEH
#define COLORSPACEH
#include "../../static/java/lang.h"
#include "../../static/util.h"
#include <boost/scoped_array.hpp>
#include <boost/shared_array.hpp>


namespace cms {
    namespace colorspace {
	using namespace util;
	using namespace java::lang;
	using std::string;
        using namespace boost;

	class ColorSpace:public Object, NameIF {
	  private:
	    boolean setValuesLocked;
	  protected:
	    virtual int getNumberBands() = 0;
	    virtual double *_getValues(double *values) = 0;
	    virtual double *_setValues(double *values) = 0;
	     ColorSpace();
	  public:

	    static shared_array<double> cartesian2polarCoordinatesValues(double
							    *cartesianValues);
	    static shared_array<double> cartesian2polarCoordinatesValues(double x,
							    double y);

	    boolean equalsValues(ColorSpace & colorSpace);
	    string *getBandNames();
	     string & getName();
	    double *getValues();
	    double *getValues(double *values);

	    static double *polar2cartesianCoordinatesValues(double
							    *polarValues);
	    static double *polar2cartesianCoordinatesValues(double
							    distance,
							    double angle);
	    void setValues(double *values);
	    void setValues(double value1, double value2, double value3);
	    void setValuesLock(boolean lock);
	};
    };
};
#endif

