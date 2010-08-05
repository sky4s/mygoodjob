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
		friend class cms::colorformat::DGLutProperty;
	      private:
		//int_vector_ptr measureCode;
		 RGB_vector_ptr rgbMeasureCode;
		int start;
		int end;
		int step;
		int firstStep;

		int lowStart;
		int lowEnd;
		int lowStep;
		int highStart;
		int highEnd;
		int highStep;
		const Type type;
	      public:
		enum Type {
		    Normal, Extend
		};
		 MeasureCondition(bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth);
		 MeasureCondition(const int start, const int end,
				  const int firstStep, const int step,
				  const Dep::MaxValue & maxValue);
		 MeasureCondition(const int lowStart, const int lowEnd, const int lowStep,
				  const int highStart, const int highEnd, const int highStep,
				  const Dep::MaxValue & maxValue);
		 MeasureCondition(RGB_vector_ptr rgbMeasureCode);
		RGB_vector_ptr getRGBMeasureCode();

		//bool isRGBType();

	      private:
		static int_vector_ptr getMeasureCode(const int start,
						     const int end, const int firstStep,
						     const int step);
		static int_vector_ptr getMeasureCode(const int lowStart, const int lowEnd,
						     const int lowStep, const int highStart,
						     const int highEnd, const int highStep);
		static bool isNoRemainder(int start, int end, int step);
		RGB_vector_ptr getRGBMeasureCode(int_vector_ptr measureCode,
						 const Dep::Channel & channel);
		RGB_vector_ptr getRGBMeasureCode(int_vector_ptr measureCode,
						 const Dep::Channel & channel,
						 const Dep::MaxValue & maxValue);
	    };



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

		bool newMethod;

		 bptr < MeasureCondition > measureCondition;
		 bptr < BitDepthProcessor > bitDepth;

		// max lumi
		KeepMaxLuminance keepMaxLuminance;
		int keepMaxLumiOver;
		double keepMaxLumiGamma;
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


		void setGammaCurve0(double_vector_ptr gammaCurve);
		void setGammaCurve0(double_vector_ptr rgammaCurve,
				    double_vector_ptr ggammaCurve, double_vector_ptr bgammaCurve);
		Component_vector_ptr fetchComponentVector(bptr <
							  MeasureCondition > measureCondition);
		double_vector_ptr fetchLuminanceVector(bptr < MeasureCondition > measureCondition);
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
		void setKeepMaxLuminanceNativeWhiteAdvanced(int over, double gamma);
		void setNewMethod(bool enable);

		 LCDCalibrator(bptr <
			       cms::lcd::calibrate::ComponentFetcher >
			       fetcher, bptr < BitDepthProcessor > bitDepth);
		double_vector_ptr getGammaCurve(Component_vector_ptr componentVector);
		RGB_vector_ptr getCCTDGLut(bptr < MeasureCondition > measureCondition);
		RGB_vector_ptr getGammaDGLut(bptr < MeasureCondition > measureCondition);
		 bptr < cms::colorformat::DGLutFile >
		    storeDGLutFile(const std::string & filename, RGB_vector_ptr dglut);
		void storeDGLutFile(const std::string & filename, RGB_vector_ptr dglut,
				    bptr < cms::colorformat::DGLutFile > dglutFile);
		void setBTargetIntensity(double bTargetIntensity);
		void setMultiGen(bool enable, int times);
	      private:
		 RGB_vector_ptr getDGLutOpResult(RGB_vector_ptr dglut);
	    };


	};
    };
};

#endif

