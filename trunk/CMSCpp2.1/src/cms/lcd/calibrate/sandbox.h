#ifndef SANDBOXH
#define SANDBOXH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "dimdg.h"
#include <gui/event/listener.h>


namespace cms {
    namespace lcd {
	namespace calibrate {

	    enum Domain {
		CIExy, CIEuv, CIEuvPrime
	    };
	    enum WhiteMode {
		Normal, WhiteSmooth, BIntensitySmooth
	    };
	    static XYZ_ptr getTargetXYZ(double v1, double v2, double v3, Domain domain);
	    static XYZ_ptr getTargetXYZ(double x, double y, double Y);

	    class MaxBIntensityInfo {
	      public:
		MaxBIntensityInfo(int maxBGrayLevel, double
				  maxBIntensity):maxBGrayLevel
		    (maxBGrayLevel), maxBIntensity(maxBIntensity) {
		};
		int maxBGrayLevel;
		double maxBIntensity;
	    };

	    class AdvancedDGLutGenerator:private DimDGLutGenerator, gui::event::WindowAdapter {
	      private:
		const LCDCalibrator & c;
		XYZ_ptr getXYZ(XYZ_ptr XYZ, double offsetK);
		RGB_ptr idealIntensity;


		bool stopMeasure;
		//multigen的時候會用到fetcher(因為要不斷重新量測)
		 bptr < cms::lcd::calibrate::ComponentFetcher > fetcher;
		 bptr < BitDepthProcessor > bitDepth;
		 bptr < cms::measure::IntensityAnalyzerIF > analyzer2nd;
		WhiteMode mode;
		XYZ_vector_ptr targetXYZVector;
		int brightTurn;
		int effectiveInputLevel;

		//=============================================================
		// Intensity Relative
		//=============================================================
		// Max B Intensity
		int useMaxBIntensityZone;

		MaxBIntensityInfo getMaxBIntensityInfo(XYZ_vector_ptr
						       targetXYZVector,
						       Component_vector_ptr
						       componentVector,
						       bptr <
						       cms::measure::
						       IntensityAnalyzerIF > analyzer);

		RGB_ptr getIdealIntensity(Component_vector_ptr
					  componentVector,
					  bptr <
					  cms::measure::MaxMatrixIntensityAnalyzer > analyzer);
		double_array getSmoothIntensity(double rTargetIntensity,
						double gTargetIntensity,
						double bTargetIntensity, int grayLevel);
		//=============================================================

		Component_vector_ptr componentVector2;
		 bptr < PanelRegulator > panelRegulator1;
		 bptr < PanelRegulator > panelRegulator2;
		RGBGamma_ptr rgbGenerateResult;
		void init();
		XYZ_vector_ptr getTarget0(XYZ_ptr startXYZ,
					  XYZ_ptr targetXYZ,
					  XYZ_ptr endXYZ,
					  double_vector_ptr
					  luminanceGammaCurve, int dimTurn,
					  int brightTurn, double dimGamma,
					  double brightGamma, int brightWidth);


	      public:
		 AdvancedDGLutGenerator(Component_vector_ptr
					componentVector,
					bptr <
					cms::lcd::calibrate::
					ComponentFetcher > fetcher,
					bptr <
					cms::measure::IntensityAnalyzerIF >
					analyzer1,
					bptr <
					cms::measure::IntensityAnalyzerIF >
					analyzer2nd,
					bptr < BitDepthProcessor >
					bitDepth, const LCDCalibrator & calibrator);

		 AdvancedDGLutGenerator(Component_vector_ptr
					componentVector,
					bptr <
					cms::lcd::calibrate::
					ComponentFetcher > fetcher,
					bptr < BitDepthProcessor >
					bitDepth, const LCDCalibrator & calibrator);

		RGB_vector_ptr produce();


		virtual void windowClosing(TObject * Sender, TCloseAction & Action);
		void setTarget(XYZ_ptr targetWhite, XYZ_ptr nativeWhite,
			       double_vector_ptr luminanceGammaCurve,
			       int dimTurn, int brightTurn,
			       double dimGamma, double brightGamma, int effectiveInputLevel);
	      private:
		static XYZ_vector_ptr
		    getBrightGammaTarget(double_vector_ptr
					 luminanceGammaCurve,
					 XYZ_ptr startXYZ, XYZ_ptr endXYZ,
					 double brightGamma,
					 int brightTurn, int brightWidth,
					 bptr < BitDepthProcessor > bitDepth);

		RGB_vector_ptr produceDGLutMulti(XYZ_vector_ptr
						 targetXYZVector,
						 Component_vector_ptr componentVector);

		RGB_vector_ptr produceDGLut(XYZ_vector_ptr targetXYZVector,
					    Component_vector_ptr
					    componentVector,
					    bptr <
					    cms::measure::
					    IntensityAnalyzerIF > analyzer,
					    bptr < PanelRegulator > panelRegulator);

		Component_ptr getFRCAbilityComponent(int grayLevel,
						     RGB_ptr rgb,
						     bptr <
						     cms::measure::
						     IntensityAnalyzerIF >
						     analyzer,
						     Component_vector_ptr componentVector);

		bool checkTargetXYZVector(XYZ_vector_ptr targetXYZVector,
					  int start, int end, double deltaabThreshold);
		static RGB_vector_ptr smooth(RGB_vector_ptr result1,
					     RGB_vector_ptr result2,
					     bptr < BitDepthProcessor > bitDepth, int brightTurn);

	      public:
		void setComponentVector2(Component_vector_ptr
					 componentVector2, bptr < PanelRegulator > panelRegulator2);
		void setPanelRegulator(bptr < PanelRegulator > panelRegulator);
		__property RGBGamma_ptr RGBGenerateResult = { read = rgbGenerateResult
		};
		__property RGB_ptr IdealIntensity = { read = idealIntensity
		};
		void setUseMaxBIntensityZone(int zone);
		__property XYZ_vector_ptr TargetXYZVector = { read = targetXYZVector
		};
	    };



	    class DimTargetGenerator {
	      public:
		const static Domain UsageColorSpace;
		static XYZ_vector_ptr getLinearTarget(XYZ_ptr startXYZ,
						      XYZ_ptr endXYZ,
						      double_vector_ptr luminanceGammaCurve);
		static XYZ_vector_ptr getLinearTarget(XYZ_ptr startXYZ,
						      XYZ_ptr endXYZ,
						      double_vector_ptr
						      luminanceGammaCurve, Domain domain);

		static XYZ_vector_ptr getTarget(XYZ_ptr startXYZ,
						XYZ_ptr endXYZ,
						double_vector_ptr
						luminanceGammaCurve, Domain domain, double gamma);
		static XYZ_vector_ptr getTarget(XYZ_ptr startXYZ,
						XYZ_ptr endXYZ,
						double_vector_ptr
						luminanceGammaCurve, double gamma);
	    };

	    class DeHookProcessor {
	      private:
		const LCDCalibrator & c;
		RGB_vector_ptr getAroudRGBVector(RGB_ptr center, double step);
		Patch_ptr measure(RGB_ptr rgb);
		RGBPatchMap_ptr rgbPatchMap;
		double getNormalInput(int targetGrayLevel);
		Patch_ptr getBestGammaPatchByMeasureLoop(Patch_ptr basePatch, double targetGamma,
							 int targetGrayLevel, double deltaxySpec);
		double getGammaExponentialFromMeasure(Patch_ptr patch, int targetGrayLevel);
	      public:
		 DeHookProcessor(const LCDCalibrator & calibrator);
		int getMaxBIntensityRawGrayLevel();
		static SecondWhite getSecondWhite(KeepMaxLuminance keepMaxLuminance, DeHook deHook);
		 bptr < cms::devicemodel::LCDModel > getLCDModelForDeHook(int blueMaxGrayLevel);
		Patch_vector_ptr getReasonableChromaticityPatchVector(bptr <
								      cms::devicemodel::LCDModel >
								      model, int blueMaxGrayLevel,
								      double deltaxySpec);
		int getReasonableGammaGrayLevel(Patch_vector_ptr patchVector, double gammaDWLimit,
						double gammaUPLimit);
		int getBestGrayLevel(Patch_vector_ptr patchVector, double targetGamma);
		Patch_ptr getBestGammaPatch(Patch_vector_ptr patchVector, double targetGamma,
					    int targetGrayLevel);
		Patch_ptr getBestGammaPatchByMeasure(Patch_ptr basePatch, double targetGamma,
						     int targetGrayLevel, double deltaxySpec);
		double bestGamma;
		double_vector_ptr alterGammaCurve(double_vector_ptr gammaCurve, int alterStart,
						  int alterEnd, int maxDigitalCount,
						  double alterEndTargetGamma);
	    };
	};
    };
};



#endif

