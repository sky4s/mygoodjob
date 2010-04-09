#include <includeall.h>
#pragma hdrstop
#include "whitefinder.h"

//C系統文件

//C++系統文件


//其他庫頭文件

//本項目內頭文件

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
	    , nearAlgo(CIEuv1960NearestAlgorithm_
		       (XYZ_ptr((CIEXYZ *) null), mm)) {
	    };

	    RGB_ptr WhitePointFinder::findMatchRGB0(xyY_ptr xyY,
						    RGB_ptr initRGB) {
		RGB_ptr nearestRGB = initRGB;
		bool findNearest = false;

		do {
		    RGB_vector_ptr aroundRGB =
			aroundAlgo.getAroundRGB(nearestRGB, 1);
		    XYZ_ptr center = xyY->toXYZ();
		     bptr < AlgoResult > algoResult =
			nearAlgo.getNearestRGB(center, aroundRGB);
		    XYZ_vector_ptr aroundXYZ = algoResult->aroundXYZ;
		     nearestRGB = algoResult->nearestRGB;
		     findNearest =
			MeasuredUtils::isFirstNearestXYZInuvPrime(center,
								  aroundXYZ);
		} while (!findNearest);
		 return nearestRGB;
	    };

	    RGB_ptr WhitePointFinder::findRGBAround(xyY_ptr xyY) {
		aroundAlgo.setMode(Normal);
		RGB_ptr result = findMatchRGB0(xyY, RGBColor::White);
		return result;
	    };

	    /*
	       以此修正後的值, 修正其餘非255的兩點, 使色度達到最接近值.
	       1. 找到最大值頻道
	       2. 計算目前xyY與目標值之delta
	       3.
	     */
	    RGB_ptr WhitePointFinder::findMatchRGB(xyY_ptr xyY,
						   RGB_ptr initRGB) {
		aroundAlgo.setMode(White);
		RGB_ptr result = findMatchRGB0(xyY, initRGB);
		return result;
	    };

	    RGB_ptr WhitePointFinder::fixRGB2TouchMax(RGB_ptr rgb) {
		/*if (true)
		   return rgb; */
		RGB_ptr clone = rgb->clone();
		//然後再調整White使RGB其中一點為255.
		const Channel & maxChannel = clone->getMaxChannel();
		double maxChannelValue = clone->getValue(maxChannel);
		double diff = 255 - maxChannelValue;
		clone->addValue(diff);
		return clone;
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
		return initRGB;
	    };
	};

    };
};

