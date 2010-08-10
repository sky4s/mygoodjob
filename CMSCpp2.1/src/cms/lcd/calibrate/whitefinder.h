#ifndef WHITEFINDERH
#define WHITEFINDERH
//C�t�Τ��

//C++�t�Τ��


//��L�w�Y���

//�����ؤ��Y���

namespace cms {
    namespace lcd {
	namespace calibrate {
	    class WhitePointFinder:public cms::util::WindowListener {
	      private:

		RGB_ptr findMatchRGB0(xyY_ptr xyY, RGB_ptr initRGB);
		RGB_ptr findRGBAround(xyY_ptr xyY);
		RGB_ptr findMatchRGB(xyY_ptr xyY, RGB_ptr initRGB);
		RGB_ptr fixRGB2TouchMax(RGB_ptr rgb);

		 bptr < cms::lcd::calibrate::algo::ChromaticAroundAlgorithm > aroundAlgo;
		 bptr < cms::lcd::calibrate::algo::CIEuv1960NearestAlgorithm > nearAlgo;

		 bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth;

	      protected:
		 bool stop;
		 bptr < cms::measure::MeterMeasurement > mm;
		double maxcode;
	      public:
		 WhitePointFinder(bptr < cms::measure::MeterMeasurement >
				  mm,
				  bptr <
				  cms::lcd::calibrate::BitDepthProcessor >
				  bitDepth, double maxcode);
		virtual RGB_ptr findRGB(xyY_ptr xyY);
		void windowClosing();
	    };

	    class StocktonWhitePointFinder:public WhitePointFinder {
	      private:
		RGB_ptr initRGB;
		bool keepBlue;
	      public:
		 StocktonWhitePointFinder(bptr <
					  cms::measure::MeterMeasurement >
					  mm, bptr <
					  cms::lcd::calibrate::
					  BitDepthProcessor > bitDepth,
					  RGB_ptr initRGB, double maxcode, bool keepBlue);
		RGB_ptr findRGB(xyY_ptr targetxyY);
	    };
	};
    };
};
#endif
