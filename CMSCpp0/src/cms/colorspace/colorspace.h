#ifndef COLORSPACEH
#define COLORSPACEH
#include <static/java/lang.h>
#include <static/util.h>
#include <boost/shared_array.hpp>
#include <vector>


namespace cms {
    namespace colorspace {
	using namespace java::lang;
	using namespace util;
	using namespace boost;
	using namespace std;
	class ColorSpace:public Object, NameIF {

	  private:
	    boolean setValuesLocked;
	  protected:
	    virtual int getNumberBands() = 0;
	    virtual shared_array < double >_getValues(shared_array <
						      double >values) = 0;
	    virtual void _setValues(shared_array < double >values) = 0;
	     ColorSpace();
	  public:

	    static shared_array <
		double >cartesian2polarCoordinatesValues(shared_array <
							 double
							 >cartesianValues);
	    static shared_array <
		double >cartesian2polarCoordinatesValues(double x,
							 double y);

	    boolean equalsValues(ColorSpace & colorSpace);
	    virtual vector < string > getBandNames() = 0;
	     string & getName();
	     shared_array < double >getValues();
	     shared_array < double >getValues(shared_array <
					      double >values);

	    static shared_array <
		double >polar2cartesianCoordinatesValues(shared_array <
							 double
							 >polarValues);
	    static shared_array < double >polar2cartesianCoordinatesValues(double
									   distance, double
									   angle);
	    void setValues(shared_array < double >values);
	    void setValues(double value1, double value2, double value3);
	    void setValuesLock(boolean lock);
	};
    };
};
#endif

