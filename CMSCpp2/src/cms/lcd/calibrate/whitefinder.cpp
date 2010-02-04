#include "whitefinder.h"

//C系統文件

//C++系統文件


//其他庫頭文件

//本項目內頭文件
#include <cms/lcd/calibrate/aroundalgo.h>
#include <cms/lcd/calibrate/nearalgo.h>
#include <cms/colorspace/rgb.h>
#include <cms/colorspace/ciexyz.h>
#include <cms/measure/MeterMeasurement.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms::measure;
	    using namespace cms::lcd::calibrate::algo;
	    using namespace Dep;
	     WhitePointFinder::WhitePointFinder(bptr <
						cms::measure::
						MeterMeasurement >
						mm):mm(mm),
		aroundAlgo(ChromaticAroundAlgorithm())
	    , nearAlgo(CIEuv1960NearestAlgorithm
		       (XYZ_ptr((Indep::CIEXYZ *) NULL),
			mm->getMeasureInterface()
		       )) {
	    };

	    RGB_ptr WhitePointFinder::findRGBAround(xyY_ptr xyY) {
		RGB_vector_ptr aroundRGB =
		    aroundAlgo.getAroundRGB(RGBColor::White, 1);
		XYZ_ptr center = xyY->toXYZ();
		 bptr < AlgoResult > algoResult =
		    nearAlgo.getNearestRGB(center, aroundRGB);
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
	       3. 再以此修正後的值, 修正其餘非255的兩點, 使色度達到最接近值.
	     */
	    RGB_ptr WhitePointFinder::findRGB(xyY_ptr xyY) {
		RGB_ptr initRGB = findRGBAround(xyY);
		RGB_ptr fixRGB = fixRGB2TouchMax(initRGB);
		RGB_ptr finalRGB = findMatchRGB(xyY, fixRGB);
		return finalRGB;
	    };
	};

    };
};

