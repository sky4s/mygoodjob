#ifndef LCDCALIBRATORH
#define LCDCALIBRATORH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <math/regression.h>
#include "rgbgamma.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace math;
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
	    class ComponentFetcher:public cms::util::WindowListener {
	      private:
		bptr < cms::measure::IntensityAnalyzerIF > analyzer;
		bool stop;
		 bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth;
	      public:
		 ComponentFetcher(bptr <
				  cms::measure::IntensityAnalyzerIF >
				  analyzer,
				  bptr < BitDepthProcessor > bitDepth);
		Component_vector_ptr fetchComponent(int start, int end,
						    int firstStep,
						    int step);
		Component_vector_ptr fetchComponent(int_vector_ptr
						    measureCode);
		static int_vector_ptr getMeasureCode(int start, int end,
						     int firstStep,
						     int step);

		//void setStop(bool stop);
		static void storeToExcel(const std::string & filename,
					 Component_vector_ptr
					 componentVector);
		void windowClosing();
	    };

	    class ComponentRelationIF {
	      public:
		virtual double getIntensity(double luminance) = 0;
		virtual double getLuminance(double rIntensity,
					    double gIntensity,
					    double bIntensity) = 0;
	    };
	    class ComponentLinearRelation:public ComponentRelationIF {
	      private:
		bptr < PolynomialRegression > regression;
		double a0, a1, a2, a3, c, d;
		void init(double2D_ptr input, double2D_ptr output);
		void init(Component_vector_ptr componentVector);
		Component_vector_ptr componentVector;
	      public:
		 ComponentLinearRelation(double2D_ptr input,
					 double2D_ptr output);
		 ComponentLinearRelation(Component_vector_ptr
					 componentVector);
		double getIntensity(double luminance);
		double getLuminance(double rIntensity, double gIntensity,
				    double bIntensity);
	    };

	    class ComponentPLRelation:public ComponentRelationIF {
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

	    class ComponentLUT {
	      private:
		Component_vector_ptr componentVector;
		bptr < math::Interpolation1DLUT > rLut;
		bptr < math::Interpolation1DLUT > gLut;
		bptr < math::Interpolation1DLUT > bLut;
	      protected:
		init(Component_vector_ptr componentVector);
		double_vector_ptr getReverse(double_vector_ptr vec);
	      public:
		 ComponentLUT(Component_vector_ptr componentVector);
		double getIntensity(const Dep::Channel & ch, double code);
		double getCode(const Dep::Channel & ch, double intensity);
		double correctIntensityInRange(const Dep::Channel & ch,
					       double intensity);
	    };

	    class DGLutGenerator {
	      protected:
		Component_vector_ptr componentVector;
		double minLuminance, maxLuminance;
		 bptr < ComponentLUT > lut;
		 bptr < BitDepthProcessor > bitDepth;
		 bptr < ComponentRelationIF > componentRelation;
		void init();
		double_vector_ptr getLuminanceGammaCurve(double_vector_ptr
							 normalGammaCurve);

		double getMaximumIntensity();
	      public:
		 DGLutGenerator(Component_vector_ptr componentVector,
				bptr < BitDepthProcessor > bitDepth);
		RGB_ptr produce(double rIntensity, double gIntensity,
				double bIntensity);
		RGB_vector_ptr produce(RGBGamma_ptr normalRGBGammaCurve);
		RGBGamma_ptr getRGBGamma(double_vector_ptr
					 normalGammaCurve);
		 bptr < ComponentLUT > getComponentLUT();
	    };

	    enum Correct {
		P1P2 = 1, RBInterpolation = 2, None = 3, New = 4, New2 = 5
	    };

	    class MeasureCondition {
	      public:
		const int start;
		const int end;
		const int step;
		const int firstStep;

		const int lowStart;
		const int lowEnd;
		const int lowStep;
		const int highStart;
		const int highEnd;
		const int highStep;
		const bool normalCondition;
		 MeasureCondition(const int start, const int end,
				  const int firstStep, const int step);
		 MeasureCondition(const int lowStart, const int lowEnd,
				  const int lowStep, const int highStart,
				  const int highEnd, const int highStep);
		int_vector_ptr getMeasureCode();
	      private:
		 int_vector_ptr getMeasureCode(const int start,
					       const int end,
					       const int firstStep,
					       const int step);
		int_vector_ptr getMeasureCode(const int lowStart,
					      const int lowEnd,
					      const int lowStep,
					      const int highStart,
					      const int highEnd,
					      const int highStep);
		bool isNoRemainder(int start, int end, int step);
	    };

	    class LCDCalibrator {
		friend class cms::colorformat::DGLutProperty;
	      private:

		//==============================================================
		// 校正參數
		//==============================================================
		 Correct correct;
		int p1, p2;
		int under;
		double gammaShift;
		bool gByPass;
		double bIntensityGain;
		bool bMax;
		bool keepMaxLuminance;
		bool avoidFRCNoise;
		bool rgbgamma;
		double gamma, rgamma, ggamma, bgamma;
		bool useGammaCurve;
		double_vector_ptr gammaCurve;
		double_vector_ptr rgammaCurve;
		double_vector_ptr ggammaCurve;
		double_vector_ptr bgammaCurve;
		 bptr < MeasureCondition > measureCondition;
		 bptr < BitDepthProcessor > bitDepth;
		//==============================================================

		 bptr < DGLutGenerator > generator;
		 bptr < ComponentFetcher > fetcher;
		RGB_vector_ptr dglut;
		Component_vector_ptr componentVector;
		RGBGamma_ptr finalRGBGamma;
		RGBGamma_ptr initialRGBGamma;


		void setGammaCurve0(double_vector_ptr gammaCurve);
		void setGammaCurve0(double_vector_ptr rgammaCurve,
				    double_vector_ptr ggammaCurve,
				    double_vector_ptr bgammaCurve);
	      public:
		static double_vector_ptr getGammaCurveVector
		    (double gamma, int n, int effectiven);

		void setP1P2(int p1, int p2);
		void setRBInterpolation(int under);
		void setNoneDimCorrect();
		void setNew(int p1, int p2, double gammaShift);
		void setNew2(int under);
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

		 LCDCalibrator(bptr <
			       cms::lcd::calibrate::ComponentFetcher >
			       fetcher,
			       bptr < BitDepthProcessor > bitDepth);

		RGB_vector_ptr getCCTDGLut(bptr < MeasureCondition >
					   measureCondition);
		RGB_vector_ptr getGammaDGLut(int step);
		void storeDGLut(const std::string & filename,
				RGB_vector_ptr dglut);
	      private:
		 RGB_vector_ptr getDGLutOpResult(RGB_vector_ptr dglut);
	    };


	};
    };
};

#endif

