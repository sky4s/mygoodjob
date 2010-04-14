#ifndef WHITEFINDERH
#define WHITEFINDERH
//C系統文件

//C++系統文件


//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace lcd {
	namespace calibrate {
	    class WhitePointFinder {
	      private:

		RGB_ptr findMatchRGB0(xyY_ptr xyY, RGB_ptr initRGB);
		RGB_ptr findRGBAround(xyY_ptr xyY);
		RGB_ptr findMatchRGB(xyY_ptr xyY, RGB_ptr initRGB);
		RGB_ptr fixRGB2TouchMax(RGB_ptr rgb);

		 bptr < cms::lcd::calibrate::algo::
		    ChromaticAroundAlgorithm > aroundAlgo;
		 bptr < cms::lcd::calibrate::algo::
		    CIEuv1960NearestAlgorithm > nearAlgo;
	      protected:
		 bptr < cms::measure::MeterMeasurement > mm;
	      public:
		 WhitePointFinder(bptr < cms::measure::MeterMeasurement >
				  mm);
		RGB_ptr findRGB(xyY_ptr xyY);
	    };

	    class StocktonWhitePointFinder:public WhitePointFinder {
	      private:
		RGB_ptr initRGB;
	      public:
		StocktonWhitePointFinder(bptr <
					 cms::measure::MeterMeasurement >
					 mm, RGB_ptr initRGB);
		RGB_ptr findRGB(xyY_ptr targetxyY);
	    };
	};
    };
};
#endif

