#include "whitefinder.h"

//C系統文件

//C++系統文件


//其他庫頭文件

//本項目內頭文件
#include <cms/lcd/calibrate/aroundalgo.h>
#include <cms/lcd/calibrate/nearalgo.h>
#include <cms/colorspace/rgb.h>
#include <cms/colorspace/ciexyz.h>
#include <cms/patch.h>
#include <cms/measure/MeterMeasurement.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms;
	    using namespace cms::measure;
	    using namespace cms::lcd::calibrate::algo;
	    using namespace Dep;
	    using namespace Indep;
	     WhitePointFinder::WhitePointFinder(bptr <
						MeterMeasurement >
						mm):mm(mm),
		aroundAlgo(ChromaticAroundAlgorithm())
	    , nearAlgo(CIEuv1960NearestAlgorithm
		       (XYZ_ptr((CIEXYZ *) NULL), mm->getMeasureInterface()
		       )) {
	    };

	    RGB_ptr WhitePointFinder::findRGBAround(xyY_ptr xyY) {
		RGB_ptr nearestRGB = RGBColor::White;
		bool findNearest = false;

		do {
		    RGB_vector_ptr aroundRGB =
			aroundAlgo.getAroundRGB(RGBColor::White, 1);
		    XYZ_ptr center = xyY->toXYZ();
		     bptr < AlgoResult > algoResult =
			nearAlgo.getNearestRGB(center, aroundRGB);
		    XYZ_vector_ptr aroundXYZ = algoResult->aroundXYZ;
		    RGB_ptr nearestRGB = algoResult->nearestRGB;
		     findNearest =
			MeasuredUtils::isFirstNearestXYZInuvPrime(center,
								  aroundXYZ);
		} while (!findNearest);
		 return nearestRGB;
	    };

            /*
              1. 找到最大值頻道
              2. 計算目前xyY與目標值之delta
              3.
            */
	    RGB_ptr WhitePointFinder::findMatchRGB(xyY_ptr xyY,
						   RGB_ptr initRGB) {
		const Channel & maxChannel = initRGB->getMaxChannel();
		channel_vector_ptr matchChannels =
		    Channel::getBesidePrimaryChannel(maxChannel);
		Patch_ptr patch =
		    mm->measure(initRGB, initRGB->toString());
		double_array delta =
		    nearAlgo.getDelta(xyY->toXYZ(), patch->getXYZ());
	    };
	    RGB_ptr WhitePointFinder::fixRGB2TouchMax(RGB_ptr rgb) {
		const Channel & maxChannel = rgb->getMaxChannel();
		double maxChannelValue = rgb->getValue(maxChannel);
		double diff = 255 - maxChannelValue;
		rgb->addValue(diff);
		return rgb;
	    };

	    /*
	       白點尋找流程

	       由於缺乏model可以預測適當的白點,
	       1. 因此先以RGB為cube尋找正確白點
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

