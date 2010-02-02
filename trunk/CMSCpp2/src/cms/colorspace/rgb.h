#ifndef RGBH
#define RGBH

#include "depend.h"

namespace cms {
    namespace colorspace {
	namespace depend {
	    class RGBColor:public RGBBase {
	      public:
		double R, G, B;

		 RGBColor();
		 RGBColor(RGBColorSpace & rgbColorSpace,
			  double_array rgb, MaxValue & maxValue);
		 RGBColor(int r, int g, int b);
		 RGBColor(double r, double g, double b);
		 RGBColor(RGBColorSpace rgbColorSpace, CIEXYZ XYZ);
		double_array _getValues(double_array values);
		void _setValues(double_array values);
		//int getNumberBands();
		string_vector_ptr getBandNames();

	      protected:
		 MaxValue _maxValue;
		RGBColorSpace _rgbColorSpace;
	    };
	};
    };
};

#endif

