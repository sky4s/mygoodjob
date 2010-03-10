#include <includeall.h>
#pragma hdrstop
#include "core.h"
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    using namespace boost;
    using namespace Indep;
    using namespace java::lang;
    //==========================================================================
    // CorrelatedColorTemperature
    //==========================================================================
     bptr < CIExyY >
	CorrelatedColorTemperature::CCT2DIlluminantxyY(int tempK) {
	//using namespace std;
	double x = 0.0, y;
	double T, T2, T3;
	// double M1, M2;

	// No optimization provided.
	 T = tempK;
	 T2 = T * T;		// Square
	 T3 = T2 * T;		// Cube

	// For correlated color temperature (T) between 4000K and 7000K:

	if (T >= 4000. && T <= 7000.) {
	    x = -4.6070 * (1E9 / T3) + 2.9678 * (1E6 / T2) +
		0.09911 * (1E3 / T) + 0.244063;
	} else
	    // or for correlated color temperature (T) between 7000K and 25000K:

	if (T > 7000.0 && T <= 25000.0) {
	    x = -2.0064 * (1E9 / T3) + 1.9018 * (1E6 / T2) +
		0.24748 * (1E3 / T) + 0.237040;
	} else {
	    //string msg = "invalid temp: " + tempK +
	    //    ", tempK must in 4000~25000K";
	    //throw IllegalArgumentException();
	    return bptr < CIExyY > (new CIExyY(0, 0, 1.0));
	}

	// Obtain y(x)
	y = -3.000 * (x * x) + 2.870 * x - 0.275;

	// wave factors (not used, but here for futures extensions)

	// M1 = (-1.3515 - 1.7703*x + 5.9114 *y)/(0.0241 + 0.2562*x - 0.7341*y);
	// M2 = (0.0300 - 31.4424*x + 30.0717*y)/(0.0241 + 0.2562*x - 0.7341*y);

	// Fill WhitePoint struct
	//CIExyY xyY(x, y, 1.0);
	bptr < CIExyY > xyY(new CIExyY(x, y, 1.0));

	return xyY;
    };

    double CorrelatedColorTemperature::xy2CCTByMcCamyFloat(bptr < CIExyY >
							   xyY) {
	double n = (xyY->x - 0.332) / (xyY->y - 0.1858);
	double sqr = Math::sqr(n);
	double cct = -449 * sqr * n + 3525 * sqr - 6823.3 * n + 5520.33;
	return cct;
    }
    //==========================================================================


    const Illuminant & Illuminant::D50 = Illuminant();
    const Illuminant & Illuminant::D65 = Illuminant();
    const Illuminant & Illuminant::C = Illuminant();
};

