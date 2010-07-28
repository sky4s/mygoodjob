#ifndef LCDCALIBRATORH
#define LCDCALIBRATORH

//C╰参ゅン

//C++╰参ゅン

//ㄤ畐繷ゅン

//セ兜ヘず繷ゅン
#include <math/regression.h>
#include "rgbgamma.h"
#include "component.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace math;

	     Enumeration(KeepMaxLuminance)
	     None, TargetWhite, NativeWhite	//keep狾程獹&︹放
	    , NativeWhiteAdvanced	//keep狾程獹&︹放, smooth跑て
	    , EnumerationEnd()

		/*
		   沮秖代挡狦, 玻ネ惠―DG Lut
		 */
	    class DGLutGenerator {
	      private:
		enum Mode {
		    Component, WLumi, RGBLumi,
		};
		KeepMaxLuminance keepMaxLuminance;
	      protected:
		 Mode mode;
		Component_vector_ptr componentVector;
		double_vector_ptr luminanceVector;
		double_vector_ptr rLuminanceVector, gLuminanceVector, bLuminanceVector;
		double minLuminance, maxLuminance;
		 bptr < ComponentLUT > lut;
		 bptr < ComponentRelationIF > componentRelation;
		 bptr < Interpolation1DLUT > wlut;
		double getMaximumIntensity();
		void initComponent(Component_vector_ptr componentVector,
				   bool keepTargetWhiteMaxLuminance);
	      public:
		 DGLutGenerator(Component_vector_ptr componentVector);
		 DGLutGenerator(Component_vector_ptr componentVector,
				KeepMaxLuminance keepMaxLuminance);
		 DGLutGenerator(double_vector_ptr luminanceVector);
		RGB_ptr getDGCode(double rIntensity, double gIntensity, double bIntensity);
		RGB_ptr getDGCode(double rIntensity, double gIntensity,
				  double bIntensity, bool correctInRange);
		RGB_vector_ptr getCCTDGLut(RGBGamma_ptr normalRGBGammaCurve);
		RGB_vector_ptr getGammaDGLut(double_vector_ptr normalGammaCurve);

		//パgamma curve锣rgb intensity
		RGBGamma_ptr getRGBGamma(double_vector_ptr normalGammaCurve);
		double_vector_ptr getLuminanceGammaCurve(double_vector_ptr normalGammaCurve);
		double getMaxBIntensity();
	    };

	     Enumeration(Correct)
	     P1P2, RBInterpolation, None, DefinedDim, EnumerationEnd()

		/*
		   ノㄓ癘更秖代兵ン, よ獽暗把计肚患
		 */
	    class MeasureCondition {
	      private:
		int_vector_ptr measureCode;
		RGB_vector_ptr rgbMeasureCode;
	      public:
		enum Type {
		    Normal, Extend, Plain, RGB
		};
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
		//const bool normalCondition;
		 MeasureCondition(const int start, const int end,
				  const int firstStep, const int step);
		 MeasureCondition(const int lowStart, const int lowEnd,
				  const int lowStep, const int highStart,
				  const int highEnd, const int highStep);
		 MeasureCondition(int_vector_ptr measureCode);
		 MeasureCondition(RGB_vector_ptr rgbMeasureCode);
		int_vector_ptr getMeasureCode();
		RGB_vector_ptr getRGBMeasureCode();
		const Type type;
		bool isRGBType();
	      private:
		 int_vector_ptr getMeasureCode(const int start,
					       const int end, const int firstStep, const int step);
		int_vector_ptr getMeasureCode(const int lowStart,
					      const int lowEnd,
					      const int lowStep,
					      const int highStart,
					      const int highEnd, const int highStep);
		bool isNoRemainder(int start, int end, int step);

	    };



	    class LCDCalibrator {
		friend class cms::colorformat::DGLutProperty;
	      private:

		//==============================================================
		// タ把计
		//==============================================================
		 Correct correct;
		int p1, p2;
		int under;
		double dimGamma;
		bool gByPass;
		double bIntensityGain;
		bool bMax;
		bool bMax2;
		int bMax2Begin;
		double bMax2Gamma;
		bool avoidFRCNoise;
		bool rgbIndepGamma;
		double gamma, rgamma, ggamma, bgamma;
		bool useGammaCurve;
		bool averageDimDG;
		bool newMethod;
		double_vector_ptr gammaCurve;
		double_vector_ptr rgammaCurve;
		double_vector_ptr ggammaCurve;
		double_vector_ptr bgammaCurve;
		 bptr < MeasureCondition > measureCondition;
		 bptr < BitDepthProcessor > bitDepth;
		KeepMaxLuminance keepMaxLuminance;
		int keepMaxLumiOver;
		double keepMaxLumiGamma;
		double bTargetIntensity;

		bool multiGen;
		int multiGenTimes;
		//==============================================================
		 bptr < ComponentFetcher > fetcher;
		RGB_vector_ptr dglut;
		Component_vector_ptr componentVector;
		double_vector_ptr luminanceVector;
		RGBGamma_ptr finalRGBGamma;
		RGBGamma_ptr initialRGBGamma;


		void setGammaCurve0(double_vector_ptr gammaCurve);
		void setGammaCurve0(double_vector_ptr rgammaCurve,
				    double_vector_ptr ggammaCurve, double_vector_ptr bgammaCurve);
		Component_vector_ptr fetchComponentVector(bptr <
							  MeasureCondition > measureCondition);
		double_vector_ptr fetchLuminanceVector(bptr < MeasureCondition > measureCondition);
	      public:
		static double_vector_ptr getGammaCurveVector(double gamma, int n, int effectiven);

		void setP1P2(int p1, int p2);
		void setRBInterpolation(int under);
		void setNonDimCorrect();
		void setDefinedDim(int under, double gamma, bool averageDimDG);
		void setGamma(double gamma);
		void setGamma(double rgamma, double ggamma, double bgamma);
		void setGammaCurve(double_vector_ptr gammaCurve);
		void setGammaCurve(double_vector_ptr rgammaCurve,
				   double_vector_ptr ggammaCurve, double_vector_ptr bgammaCurve);
		void setGByPass(bool byPass);
		void setBIntensityGain(double gain);
		void setBMax(bool bMax);
		void setBMax2(bool bMax2, int begin, double gamma);
		void setAvoidFRCNoise(bool avoid);
		void setKeepMaxLuminance(KeepMaxLuminance keepMaxLuminance);
		void setKeepMaxLuminanceNativeWhiteAdvanced(int over, double gamma);
		void setNewMethod(bool enable);

		 LCDCalibrator(bptr <
			       cms::lcd::calibrate::ComponentFetcher >
			       fetcher, bptr < BitDepthProcessor > bitDepth);

		RGB_vector_ptr getCCTDGLut(bptr < MeasureCondition > measureCondition);
		RGB_vector_ptr getGammaDGLut(bptr < MeasureCondition > measureCondition);
		 bptr < cms::colorformat::DGLutFile >
		    storeDGLutFile(const std::string & filename, RGB_vector_ptr dglut);
		void setBTargetIntensity(double bTargetIntensity);
		void setMultiGen(bool enable, int times);
	      private:
		 RGB_vector_ptr getDGLutOpResult(RGB_vector_ptr dglut);
	    };


	};
    };
};

#endif

