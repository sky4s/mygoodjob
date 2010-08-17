#ifndef LCDCALIBRATORH
#define LCDCALIBRATORH

//C╰参ゅン

//C++╰参ゅン

//ㄤ畐繷ゅン

//セ兜ヘず繷ゅン
#include <math/regression.h>
#include "rgbgamma.h"
#include "component.h"
#include "dg.h"
#include "common.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace math;

	    class LCDCalibrator {
		friend class cms::colorformat::DGLutProperty;
	      private:

		//==============================================================
		// タ把计
		//==============================================================
		 Correct correct;
		//dim
		int p1, p2;
		int under;
		double dimGamma;
		bool averageDimDG;

		double bIntensityGain;
		bool avoidFRCNoise;

		//bmax
		bool bMax;
		bool bMax2;
		int bMax2Begin;
		double bMax2Gamma;
		bool skipInverseB;
		int maxZDGCode;

		//gamma
		bool rgbIndepGamma;
		double gamma, rgamma, ggamma, bgamma;
		bool useGammaCurve;
		double_vector_ptr gammaCurve;
		double_vector_ptr rgammaCurve;
		double_vector_ptr ggammaCurve;
		double_vector_ptr bgammaCurve;
		bool gByPass;
		bool originalGamma;

		bool useNewMethod;

		 bptr < MeasureCondition > measureCondition;
		 bptr < BitDepthProcessor > bitDepth;

		// max lumi
		KeepMaxLuminance keepMaxLuminance;
		int keepMaxLumiOver;
		double keepMaxLumiGamma;
		bool autoKeepMaxLumiParameter;
		double bTargetIntensity;

		//multi
		bool multiGen;
		int multiGenTimes;
		//==============================================================
		 bptr < ComponentFetcher > fetcher;
		RGB_vector_ptr dglut;
		Component_vector_ptr componentVector;
		double_vector_ptr luminanceVector;
		RGBGamma_ptr finalRGBGamma;
		RGBGamma_ptr initialRGBGamma;
		XYZ_vector_ptr targetXYZVector;


		void setGammaCurve0(double_vector_ptr gammaCurve);
		void setGammaCurve0(double_vector_ptr rgammaCurve,
				    double_vector_ptr ggammaCurve, double_vector_ptr bgammaCurve);
		Component_vector_ptr fetchComponentVector(bptr <
							  MeasureCondition > measureCondition);
		double_vector_ptr fetchLuminanceVector(bptr < MeasureCondition > measureCondition);
		void initNativeWhiteAnalyzer();
	      public:
		static double_vector_ptr getGammaCurveVector(double gamma, int n, int
							     effectiven);

		void setP1P2(int p1, int p2);
		void setRBInterpolation(int under);
		void setNonDimCorrect();
		void setDefinedDim(int under, double gamma, bool averageDimDG);
		void setGamma(double gamma);
		void setGamma(double rgamma, double ggamma, double bgamma);
		void setGammaCurve(double_vector_ptr gammaCurve);
		void setGammaCurve(double_vector_ptr rgammaCurve,
				   double_vector_ptr ggammaCurve, double_vector_ptr bgammaCurve);
		void setOriginalGamma();
		void setGByPass(bool byPass);
		void setBIntensityGain(double gain);
		void setBMax(bool bMax);
		void setBMax2(bool bMax2, int begin, double gamma);
		void setAvoidFRCNoise(bool avoid);
		void setKeepMaxLuminance(KeepMaxLuminance keepMaxLuminance);
		void setKeepMaxLuminanceNativeWhiteAdvanced(int over, double gamma,
							    bool autoParameter);
		void setNewMethod(bool enable);
		void setSkipInverseB(bool skip);

		 LCDCalibrator(bptr <
			       cms::lcd::calibrate::ComponentFetcher >
			       fetcher, bptr < BitDepthProcessor > bitDepth);
		double_vector_ptr getGammaCurve(Component_vector_ptr componentVector);
		RGB_vector_ptr getCCTDGLut(bptr < MeasureCondition > measureCondition);
		RGB_vector_ptr getGammaDGLut(bptr < MeasureCondition > measureCondition);
		 bptr < cms::colorformat::DGLutFile >
		    storeDGLutFile(const std::string & filename, RGB_vector_ptr dglut);
		void storeDGLutFile(RGB_vector_ptr dglut,
				    bptr < cms::colorformat::DGLutFile > dglutFile);
		void setBTargetIntensity(double bTargetIntensity);
		void setMultiGen(bool enable, int times);
	      private:
		 RGB_vector_ptr getDGLutOpResult(RGB_vector_ptr dglut);
		 bptr < cms::measure::MaxMatrixIntensityAnayzer > nativeWhiteAnalyzer;
		RGB_vector_ptr oldMethod(DGLutGenerator & generator,
					 const Dep::MaxValue & quantizationBit);
		RGB_vector_ptr newMethod(DGLutGenerator & generator, int overParameter);
	      public:
		 bptr < cms::measure::MaxMatrixIntensityAnayzer > getNativeWhiteAnalyzer();
		void setNativeWhiteAnalyzer(bptr < cms::measure::MaxMatrixIntensityAnayzer >
					    analyzer);
	    };


	};
    };
};

#endif

