#include "whitefinder.h"

//C系統文件

//C++系統文件


//其他庫頭文件

//本項目內頭文件
//#include <cms/colorspace/rgb.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms::measure;
	     WhitePointFinder::
		WhitePointFinder(MeterMeasurement & mm):mm(mm) {
	    };

	    RGB_ptr WhitePointFinder::findRB(xyY_ptr xyY) {

	    };
	    RGB_ptr WhitePointFinder::findMatchRGB(xyY_ptr xyY,
						   RGB_ptr initRGB) {

	    };
	    RGB_ptr WhitePointFinder::fixRGB2TouchMax(RGB_ptr rgb) {

	    };

	    /*
	       白點尋找流程

	       由於缺乏model可以預測適當的白點,
	       1. 因此先基於G以R&B尋找正確白點
	       2. 然後再調整White使RGB其中一點為255.
	       再以此修正後的值, 修正其餘非255的兩點, 使色度達到最接近值.
	     */
	    RGB_ptr WhitePointFinder::findRGB(xyY_ptr xyY) {
		RGB_ptr initRGB = findRB(xyY);
		RGB_ptr fixRGB = fixRGB2TouchMax(initRGB);
		RGB_ptr finalRGB = findMatchRGB(xyY, fixRGB);
		return finalRGB;
	    };
	};

    };
};

