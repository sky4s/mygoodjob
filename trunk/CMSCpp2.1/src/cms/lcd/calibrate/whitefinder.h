#ifndef WHITEFINDERH
#define WHITEFINDERH
//C系統文件

//C++系統文件


//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace lcd {
	namespace calibrate {
	    class WhitePointFinder:public gui::event::WindowAdapter {
	      private:

		RGB_ptr findMatchRGB0(xyY_ptr xyY, RGB_ptr initRGB);
		RGB_ptr findRGBAround(xyY_ptr xyY);
		RGB_ptr findMatchRGB(xyY_ptr xyY, RGB_ptr initRGB);
		RGB_ptr fixRGB2TouchMax(RGB_ptr rgb);

		 bptr < cms::lcd::calibrate::algo::ChromaticAroundAlgorithm > aroundAlgo;
		 bptr < cms::lcd::calibrate::algo::CIEuv1960NearestAlgorithm > nearAlgo;

	      protected:
		 bptr < cms::lcd::BitDepthProcessor > bitDepth;
		bool stop;
		 bptr < cms::measure::MeterMeasurement > mm;
		double maxcode;
	      public:
		 WhitePointFinder(bptr < cms::measure::MeterMeasurement >
				  mm,
				  bptr < cms::lcd::BitDepthProcessor > bitDepth, double maxcode);
		virtual RGB_ptr findRGB(xyY_ptr xyY);
		virtual void windowClosing(TObject * Sender, TCloseAction & Action);
	    };

	    class StocktonWhitePointFinder:public WhitePointFinder {
	      private:
		RGB_ptr initRGB;
		bool keepBlue;
	      public:
		 StocktonWhitePointFinder(bptr <
					  cms::measure::MeterMeasurement >
					  mm, bptr < cms::lcd::BitDepthProcessor > bitDepth,
					  RGB_ptr initRGB, double maxcode, bool keepBlue);
		RGB_ptr findRGB(xyY_ptr targetxyY);
	    };
	};
    };
};
#endif

