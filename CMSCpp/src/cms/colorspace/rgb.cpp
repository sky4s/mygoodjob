#include "rgb.h"

namespace cms {
    namespace colorspace {
	//======================================================================
	// RGBColor
	//======================================================================
	using namespace std;
	using namespace boost;

	 RGBColor::RGBColor():_rgbColorSpace(RGBColorSpace::unknowRGB),
	    _maxValue(MaxValue::Double1) {
	};
	 RGBColor::RGBColor(RGBColorSpace & rgbColorSpace,
			    boost::shared_array < double >rgb,
			    MaxValue &
			    maxValue):_rgbColorSpace(rgbColorSpace),
	    _maxValue(maxValue) {

	    if (rgb != NULL) {
		setValues(rgb);
	    }
	};
	RGBColor::RGBColor(int r, int g,
			   int b):_rgbColorSpace(RGBColorSpace::unknowRGB),
	    _maxValue(MaxValue::Int8Bit) {
	    setValues(r, g, b);
	};
      RGBColor::RGBColor(RGBColorSpace rgbColorSpace, CIEXYZ XYZ):_rgbColorSpace(rgbColorSpace),
	    _maxValue(MaxValue::
		      Double1) {
	    //this(colorSpace, fromXYZValues(XYZ.getValues(), colorSpace),
	    //MaxValue.Double1);
	};


	shared_array < double >RGBColor::_getValues(shared_array <
						    double >values) {
	    values[0] = R;
	    values[1] = G;
	    values[2] = B;
	    return values;

	};

	void RGBColor::_setValues(shared_array < double >values) {
	    R = values[0];
	    G = values[1];
	    B = values[2];
	};

	vector_string_ptr RGBColor::getBandNames() {
	    vector_string_ptr vec(new vector < string > (3));

	    (*vec)[0] = "R";
	    (*vec)[1] = "G";
	    (*vec)[2] = "B";
	    return vec;
	};
	/*static shared_array<double> fromXYZValues(shared_array<double> XYZValues,
	   RGBBColorSpace rgbColorSpace) {
	   double[] linearRGBValues = XYZ2LinearRGBValues(XYZValues, colorSpace);
	   double[] rgbValues = linearToRGBValues(linearRGBValues, colorSpace);

	   return rgbValues;
	   } */
	//======================================================================
    };
};

