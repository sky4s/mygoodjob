#ifndef LCDCALIBRATORH
#define LCDCALIBRATORH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>

#define Composition_ptr  bptr < Composition >
#define Composition_vector std::vector < Composition_ptr >
#define Composition_vector_ptr bptr < Composition_vector >

namespace cms {
    namespace lcd {
	namespace calibrate {
	    class Composition:public jObject {
	      public:
		Composition(RGB_ptr rgb, RGB_ptr component);
		RGB_ptr rgb;
		RGB_ptr component;

	    };
	    class ComponentFetcher {
	      private:
		bptr < cms::measure::ComponentAnalyzerIF > analyzer;
		bptr < cms::measure::MeterMeasurement > mm;
	      public:
		ComponentFetcher(bptr < cms::measure::MeterMeasurement >
				 mm,
				 bptr < cms::measure::ComponentAnalyzerIF >
				 analyzer);
		ComponentFetcher(bptr < cms::measure::ComponentAnalyzerIF >
				 analyzer);
		//RGB_vector_ptr fetch(int start, int end, int step);
		Composition_vector_ptr fetchComposition(int start,
							int end, int step);
	    };

	    class DGCodeProducer {
	      protected:
		void init();
	      public:
		 DGCodeProducer(RGB_vector_ptr rgbComponent);
		RGB_vector_ptr produce(double_array gammaCurve);
		//RGB_vector_ptr produce(double gamma);

	    };

	    enum BitDepth {
		Bit6 = 6, Bit8 = 8, Bit10 = 10, Bit12 = 12
	    };
	    class LCDCalibrator {
	      private:
		bool p1p2;
		BitDepth in, lut, out;
		double_array gammaCurve;
		double rbInterpUnder;
		bool gByPass;
		double bIntensityGain;
		bool bMax;
		bool gamma256;
		bool avoidFRCNoise;
	      public:
		//LCDCalibrator();
		void setP1P2();
		void setRBInterpolation(int under);
		void setGamma(double gamma);
		void setGammaCurve(double_array gammaCurve);
		void setGByPass(bool byPass);
		void setBIntensityGain(double gain);
		void setBMax(bool bMax);
		void setGamma256(bool gamma256);
		void setAvoidFRCNoise(bool avoid);
		void setBitDepth(const BitDepth & in, const BitDepth & lut,
				 const BitDepth & out);
	    };


	};
    };
};

#endif

