#ifndef COLORSPACEH
#define COLORSPACEH
#include "../../static/java.h"
#include "../../static/util.h"

namespace cms {
    namespace colorspace {
	using namespace util;
	using namespace java;
	using std::string;
	class ColorSpace:public Object, NameIF {
	  public:
	    string getName();
	    static double *cartesian2polarCoordinatesValues(double
							    *cartesianValues);
	    static double *cartesian2polarCoordinatesValues(double x,
							    double y);

	};
    };
#endif

