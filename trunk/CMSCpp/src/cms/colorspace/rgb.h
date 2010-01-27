#ifndef RGBH
#define RGBH

#include "depend.h"

namespace cms {
    namespace colorspace {

	class RGBColor:public RGBBase {
	  public:
	    double R, G, B;

	     RGBColor();
	     RGBColor(RGBColorSpace & rgbColorSpace,
		      boost::shared_array < double >rgb,
		      MaxValue & maxValue);
	     RGBColor(int r, int g, int b);
	     RGBColor(RGBColorSpace rgbColorSpace, CIEXYZ XYZ);
	     boost::shared_array <
		double >_getValues(boost::shared_array < double >values);
	    void _setValues(boost::shared_array < double >values);
	    //int getNumberBands();
	    vector_string_ptr getBandNames();
	  protected:
	     MaxValue _maxValue;
	    RGBColorSpace _rgbColorSpace;
	};
    };
};

#endif

