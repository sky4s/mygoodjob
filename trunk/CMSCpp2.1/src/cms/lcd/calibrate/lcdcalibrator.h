#ifndef LCDCALIBRATORH
#define LCDCALIBRATORH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <math/regression.h>
#include "rgbgammaop.h"
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
		// 校正參數
		//==============================================================
		 Correct correct;
		//==============================================================
		//dim
		//==============================================================
		int p1, p2;
		int under;
		double dimGamma;
		bool averageDimDG;
		//==============================================================

		//==============================================================
		//bmax
		//==============================================================
		bool bMax;
		bool bMax2;
		int bMax2Begin;
		double bMax2Gamma;
		bool skipInverseB;
		int maxZDGCode;
		//==============================================================

		//==============================================================
		//gamma
		//==============================================================
		bool rgbIndepGamma;
		double gamma, rgamma, ggamma, bgamma;
		bool useGammaCurve;
		double_vector_ptr gammaCurve;
		double_vector_ptr rgammaCurve;
		double_vector_ptr ggammaCurve;
		double_vector_ptr bgammaCurve;
		bool gByPass;
		bool originalGamma;
		//==============================================================

		//==============================================================
		// max lumi
		//==============================================================
		KeepMaxLuminance keepMaxLuminance;
		int keepMaxLumiOver;
		double keepMaxLumiGamma;
		bool autoKeepMaxLumiParameter;
		//==============================================================

		//==============================================================
		//multi
		//==============================================================
		bool multiGen;
		int multiGenTimes;
		//==============================================================

		//==============================================================
		// others
		//==============================================================
		double bTargetIntensity;
		double bIntensityGain;
		bool avoidFRCNoise;
		bool useNewMethod;
		//兩種狀況下 accurateMode會有作用, 當然都要搭配tcon才能用
		//所以一定是搭配PanelRegulator去修改面板特性的
		// 1. KeepMaxLuminance為NativeWhiteAdvanced的時候
		//   為了讓結果跟接近NativeWhite, 所以Target White的B改為反轉點
		// 2. 將面板白點修改為目標白點
		//   修改面板特性讓面板白點為目標白點, 使求出來的白點正好就是目標
		bool accurateMode;
		bool manualAccurateMode;
		bool remapped;
		double middleCCTRatio;
		//==============================================================

		//==============================================================
		// store
		//==============================================================
		RGB_vector_ptr dglut;
		Component_vector_ptr componentVector;
		double_vector_ptr luminanceVector;
		RGBGamma_ptr finalRGBGamma;
		RGBGamma_ptr initialRGBGamma;
		XYZ_vector_ptr targetXYZVector;

		 bptr < MeasureCondition > measureCondition;
		 bptr < BitDepthProcessor > bitDepth;
		//==============================================================

		//==============================================================

		//==============================================================
		// 
		//==============================================================
		 bptr < i2c::TCONControl > tconctrl;
		 bptr < ComponentFetcher > fetcher;
		 bptr < cms::measure::MaxMatrixIntensityAnayzer > nativeWhiteAnalyzer;
		//==============================================================

		//==============================================================
		// functions
		//==============================================================
		void setGammaCurve0(double_vector_ptr gammaCurve);
		void setGammaCurve0(double_vector_ptr rgammaCurve,
				    double_vector_ptr ggammaCurve, double_vector_ptr bgammaCurve);
		Component_vector_ptr fetchComponentVector();
		double_vector_ptr fetchLuminanceVector();
		void initNativeWhiteAnalyzer();
		RGB_vector_ptr getDGLutOpResult(RGB_vector_ptr dglut, DGLutGenerator & generator);
		RGB_vector_ptr oldMethod(DGLutGenerator & generator,
					 bptr < PanelRegulator > panelRegulator,
					 const Dep::MaxValue & quantizationBit);
		RGB_vector_ptr newMethod(DGLutGenerator & generator,
					 bptr < PanelRegulator > panelRegulato);
		//==============================================================
	      public:
		static double_vector_ptr getGammaCurveVector(double gamma, int n, int
							     effectiven);
		//==============================================================
		// options
		//==============================================================
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
		void setKeepMaxLuminanceNativeWhiteAdvanced(int over,
							    double gamma, bool autoParameter);
		void setNewMethod(bool enable);
		void setSkipInverseB(bool skip);
		void setBTargetIntensity(double bTargetIntensity);
		void setMultiGen(bool enable, int times);
		void setAccurateMode(bool enable);
		void setManualAccurateMode(bool enable);
		void setMiddleCCTRatio(double ratio);
		//==============================================================

		//==============================================================
		// constructor
		//==============================================================
		 LCDCalibrator(bptr <
			       cms::lcd::calibrate::ComponentFetcher >
			       fetcher, bptr < BitDepthProcessor > bitDepth);
		//==============================================================

		//==============================================================
		// functions call from outside
		//==============================================================
		double_vector_ptr getGammaCurve(Component_vector_ptr componentVector);
		RGB_vector_ptr getCCTDGLut(bptr < MeasureCondition > measureCondition);
		RGB_vector_ptr getGammaDGLut(bptr < MeasureCondition > measureCondition);
		 bptr < cms::colorformat::DGLutFile >
		    storeDGLutFile(const std::string & filename, RGB_vector_ptr dglut);
		void storeDGLutFile(RGB_vector_ptr dglut,
				    bptr < cms::colorformat::DGLutFile > dglutFile);
		 bptr < cms::measure::MaxMatrixIntensityAnayzer > getNativeWhiteAnalyzer();
		void setNativeWhiteAnalyzer(bptr <
					    cms::measure::MaxMatrixIntensityAnayzer > analyzer);
		void setTCONControl(bptr < i2c::TCONControl > tconctrl);
		//==============================================================



	    };
	};
    };
};

#endif

