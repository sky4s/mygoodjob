#ifndef WHITEFINDERH
#define WHITEFINDERH
//C系統文件

//C++系統文件


//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    class WhitePointFinder {
	      private:
		cms::measure::MeterMeasurement & mm;
		RGB_ptr findRB(xyY_ptr xyY);
		RGB_ptr findMatchRGB(xyY_ptr xyY, RGB_ptr initRGB);
		RGB_ptr fixRGB2TouchMax(RGB_ptr rgb);
	      public:
		 WhitePointFinder(cms::measure::MeterMeasurement & mm);
		RGB_ptr findRGB(xyY_ptr xyY);
	    };
	};
    };
};
#endif

