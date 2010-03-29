#ifndef LCDCALIBRATORH
#define LCDCALIBRATORH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include <math/regression.h>
#include "rgbgamma.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    class Component:public jObject {
	      public:
		Component(RGB_ptr rgb, RGB_ptr intensity);
		Component(RGB_ptr rgb, RGB_ptr intensity, XYZ_ptr XYZ);
		Component(RGB_ptr rgb, RGB_ptr intensity, XYZ_ptr XYZ,
			  RGB_ptr gamma);
		RGB_ptr rgb;
		RGB_ptr intensity;
		XYZ_ptr XYZ;
		RGB_ptr gamma;
	    };
	    class ComponentFetcher {
	      private:
		bptr < cms::measure::IntensityAnalyzerIF > analyzer;
		//bptr < cms::measure::MeterMeasurement > mm;
		bool stop;
		bool tconInput;
		bool real10Bit;
	      public:
		 ComponentFetcher(bptr <
				  cms::measure::IntensityAnalyzerIF >
				  analyzer);
		Component_vector_ptr fetchComponent(int start, int end,
						    int firstStep,
						    int step);
		void setStop(bool stop);
		void setTCONInput(bool tconInput);
		void setReal10Bit(bool real10bit);
		static void storeToExcel(const std::string & filename,
					 Component_vector_ptr
					 componentVector);
	    };

	    /*
	       DGLutGenerator擔任產出DG Code的重責大任
	       1. 首先接手ComponentFetcher產出的rgb,對應的componet,亮度
	       2. 藉由regression找出componet與亮度的關係
	       1/2由init產出

	       3. 由目標gamma curve經步驟二找到對應的component
	       4. 由compomenet對應出DG Code, DG Code產出
	       3/4由produce產出

	     */
	    using namespace math;
	    class DGLutGenerator {
	      private:
		//const Dep::MaxValue & in, &out;
		bptr < PolynomialRegression > regression;
		Component_vector_ptr componentVector;
		//double2D_ptr coefs;
		double a0, a1, a2, a3, c, d;
		double minLuminance, maxLuminance;
		 bptr < math::Interpolation1DLUT > rLut;
		 bptr < math::Interpolation1DLUT > gLut;
		 bptr < math::Interpolation1DLUT > bLut;
		 bptr < BitDepthProcessor > bitDepth;
	      protected:
		void init();
		double getIntensity(double luminance);
		double getLuminance(double rIntensity, double gIntensity,
				    double bIntensity);
		double_vector_ptr getLuminanceGammaCurve(double_vector_ptr
							 normalGammaCurve);
		double_vector_ptr getReverse(double_vector_ptr vec);
		double getMaximumIntensity();
	      public:
		 DGLutGenerator(Component_vector_ptr componentVector,
				bptr < BitDepthProcessor > bitDepth);
		//RGB_vector_ptr produce(double_vector_ptr normalGammaCurve);
		RGB_vector_ptr produce(RGBGamma_ptr normalRGBGammaCurve);
		RGBGamma_ptr getRGBGamma(double_vector_ptr
					 normalGammaCurve);
	    };

	    class IntensityGenerator {

	    };


	    enum Correct {
		P1P2 = 1, RBInterpolation = 2, None = 3
	    };

	    class LCDCalibrator {
		friend class cms::colorformat::DGLutProperty;
	      private:

		 Correct correct;
		double p1, p2;
		//const Dep::MaxValue & in, &lut, &out;
		double rbInterpUnder;
		bool gByPass;
		double bIntensityGain;
		bool bMax;
		bool keepMaxLuminance;
		//bool gamma256;
		bool avoidFRCNoise;
		bool rgbgamma;
		double gamma, rgamma, ggamma, bgamma;
		double_vector_ptr gammaCurve;
		double_vector_ptr rgammaCurve;
		double_vector_ptr ggammaCurve;
		double_vector_ptr bgammaCurve;
		 bptr < DGLutGenerator > generator;
		 bptr < ComponentFetcher > fetcher;
		 bptr < cms::measure::IntensityAnalyzerIF > analyzer;

		RGB_vector_ptr dglut;
		Component_vector_ptr componentVector;
		RGBGamma_ptr finalRGBGamma;
		RGBGamma_ptr initialRGBGamma;

		int start, end, firstStep, step;
		void set(int start, int end, int firstStep, int step);
		 bptr < BitDepthProcessor > bitDepth;
	      public:
		static double_vector_ptr getGammaCurveVector
		    (double gamma, int n, int effectiven);

		void setP1P2(double p1, double p2);
		void setRBInterpolation(int under);
		void setNoneDimCorrect();
		void setGamma(double gamma);
		void setGamma(double rgamma, double ggamma, double bgamma);
		void setGammaCurve(double_vector_ptr gammaCurve);
		void setGammaCurve(double_vector_ptr rgammaCurve,
				   double_vector_ptr ggammaCurve,
				   double_vector_ptr bgammaCurve);
		void setGByPass(bool byPass);
		void setBIntensityGain(double gain);
		void setBMax(bool bMax);
		void setAvoidFRCNoise(bool avoid);
		void setKeepMaxLuminance(bool keepMaxLuminance);

		 LCDCalibrator(bptr < cms::measure::IntensityAnalyzerIF >
			       analyzer,
			       bptr < BitDepthProcessor > bitDepth);

		//RGB_vector_ptr getDGLut(int start, int end, int step);
		RGB_vector_ptr getDGLut(int start, int end, int firstStep,
					int step);
		RGB_vector_ptr getDGLut(int firstStep, int step);
		void storeDGLut(const std::string & filename,
				RGB_vector_ptr dglut);
	      private:
		 RGB_vector_ptr getDGLutOpResult(RGB_vector_ptr dglut);
	    };


	};
    };
};

#endif

