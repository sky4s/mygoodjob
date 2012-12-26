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
#include "quantizer.h"
#include <cms/measure/include.h>	//20120302


namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace math;

	    extern bool debugMode;
	    extern bool linkCA210;
	    extern bool pcWithDirectGamma;

	    /*
	       只要DeHook有開, 基本上就是要PanelRegulator先改變面板特性, 再做量測
	       改變的基準就是把Target White改到避開Hook

	       第一代DeHook簡述:
	       把TargetWhite的B直接改成B intensity最大點, 因此255那一點就是對到B Intensity最大點,
	       因此可以避開Intensity反轉的問題

	       第二代DeHook簡述:
	       第一代的增強, 基本上概念與第一代無誤, 但是有兩種選項
	       1.B Gap優先: 讓BGap最小
	       2.Gamma優先: 讓Gamma最接近目標Gamma

	       兩個選項是互相牴觸, 有trade-off的, 所以才開放兩個選項供選擇.
	       1.B Gap優先
	       與第一代De-Hook相同的概念, 但是把B Intensity最大點落在254, 如此可以進一步縮小B Gap
	       由於是落在254, 因此採用的RGB將不會是255 255 250(假設B Intensity最大是250)的組合.
	       R&G會是比250更小的值, 但是卻保證與Panel White的dxy <0.003(Panel White為255/255/255)
	       且Gamma介於1.5~3(此為我們內定的SPEC, 非客戶要求)

	       甚至將B Intensity最大點落在253...252...更可以進一步縮小B Gap
	       (但還是要遵守Gamma 1.5~3的規則)

	       2.Gamma優先
	       基本規則等同於B Gap優先, 但是只會把B Intensity放在最接近目標Gamma(譬如2.2)的灰階,
	       確保整條Gamma都接近目標值


	     */
	    enum DeHook {
		None,
		KeepCCT,	//第一代的DeHook, 把TargetWhite的B直接改成B intensity最大點
		SecondWithBGap1st,	//第二代DeHook, 但是以降低B Gap為優先
		SecondWithGamma1st,	//第二代DeHook, 但是以Gamma優先(相對的B Gap就無法降低)
	    };

	    enum KeepL {
		ByGamma, ByLuminance
	    };


	     Enumeration(SecondWhite)
	     None, MaxRGB, DeHook, DeHook2, EnumerationEnd();

	    class LCDCalibrator {
		friend class cms::colorformat::DGLutProperty;
		friend class cms::lcd::calibrate::AdvancedDGLutGenerator;
		friend class cms::lcd::calibrate::DeHookProcessor;
	      private:

		//==============================================================
		// 校正參數
		//==============================================================
		 DimCorrect correct;
		//==============================================================
		//dim
		//==============================================================
		int p1, p2;
		int dimUnder;
		double dimStrength;
		int dimFixEnd;
		//bool dimFix;
		double dimFixThreshold;
		bool keepDarkLevel;
		bool fixInverseCIEZ;
		int dimRBFixUnder;
		bool dimRBFix;
		bool dimRBFixAutoUnder;
		//==============================================================

		//==============================================================
		//bmax
		//==============================================================
		bool bMax;
		bool bMax2;
		int bMax2Begin;
		double bMax2Gamma;
		//==============================================================

		//==============================================================
		//gamma
		//==============================================================
		bool rgbIndepGamma;
		double gamma, rgamma, ggamma, bgamma, dimGamma;
		int dimGammaEnd;
		bool useGammaCurve;
		double_vector_ptr gammaCurve;
		double_vector_ptr rgammaCurve;
		double_vector_ptr ggammaCurve;
		double_vector_ptr bgammaCurve;
		bool gByPass;
		bool originalGamma;
		bool absoluteGamma;
		int absoluteGammaStart;
		double absGammaStartGLAboveGamma;
		KeepL keepL;
		bool fineLuminanceCalibrate;
		//==============================================================

		//==============================================================
		// max lumi
		//==============================================================
		KeepMaxLuminance keepMaxLuminance;
		int keepMaxLumiOver;
		bool autoKeepMaxLumiParameter;
		bool forceAssignTargetWhite;
		//==============================================================

		//==============================================================
		//multi
		//==============================================================
		bool multiGen;
		int multiGenTimes;
		bool keepMaxYInMultiGen;
		bool luminanceCalibration;
		bool luminanceCalibrationOnly;
		//==============================================================

		//==============================================================
		//intensity
		//==============================================================
		double rTargetIntensity;
		double gTargetIntensity;
		double bTargetIntensity;
		//bool autoIntensity;
		bool autoIntensityInMultiGen;
		//RGB_ptr idealIntensity;
		bool smoothIntensity;
		int smoothIntensityStart;
		int smoothIntensityEnd;
		double bIntensityGain;
		//==============================================================

		//==============================================================
		// de-hook
		//==============================================================
		//用來註記是否有用了panel regulator
		bool remapped;
		DeHook dehook;
		int maxBRawGrayLevel;
		int maxBDGGrayLevel;
		double gammaDWLimit;
		double gammaUPLimit;
		 bptr < cms::devicemodel::LCDModel > lcdmodel4DeHook;
		int bGap1stGammaBoundGrayLevel;
		double bestGammaAtGammaBoundGrayLevel;
		double reasonableDeltaChromaticity;
		Patch_ptr bestGammaPatch1;
		Patch_ptr bestGammaPatch2;
		bool alterGammaCurveAtDeHook2;
		//==============================================================
		//==============================================================
		// feedback
		//==============================================================
		bool feedbackFix;
		int feedbackFixCount;
		int initDefectCount;
		double_array maxMeasureError;
		bool colorimetricQuanti;
		//QuantiType quantiType;
		 bptr < cms::lcd::calibrate::FeedbackFixer > feedbackFixer;
		//==============================================================
		//==============================================================
		// others
		//==============================================================
		bool avoidFRCNoise;
		//使用新的有多種target的方法去找到DG
		bool useNewMethod;

		string excuteStatus;
		//==============================================================

	      public:
		//==============================================================
		// options
		//==============================================================

		//==============================================================
		//dim
		//==============================================================
		void setP1P2(int p1, int p2);
		void setRGBInterpolation(int under);
		void setNonDimCorrect();
		void setDefinedDim(int under, double strength);
		void setDefinedDimRBFix(int under, bool enable, bool autoUnder);
		__property int DimFixEnd = { write = dimFixEnd };
		//__property bool DimFix = { write = dimFix };
		__property double DimFixThreshold = { write = dimFixThreshold
		};
		__property bool KeepDarkLevel = { read = keepDarkLevel, write = keepDarkLevel
		};
		__property bool FixInverseCIEZ = { read = fixInverseCIEZ, write = fixInverseCIEZ
		};
		//==============================================================

		//==============================================================
		//gamma
		//==============================================================
		void setGamma(double gamma);
		//2-gamma
		void setGamma(double dimGamma, int dimGammaEnd, double brightGamma);
		//3-gamma
		void setGamma(double dimGamma, int dimGammaEnd,
			      int middleGammaEnd, double brightGamma);
		void setGamma(double rgamma, double ggamma, double bgamma);
		void setGammaCurve(double_vector_ptr gammaCurve);
		void setGammaCurve(double_vector_ptr rgammaCurve,
				   double_vector_ptr ggammaCurve, double_vector_ptr bgammaCurve);
		void setOriginalGamma();
		void setAbsoluteGamma(bool absoluteGamma,
				      int startGrayLevel, double startGrayLevelAboveGamma,
				      KeepL keepL);
		//==============================================================

		//==============================================================
		// max luminance
		//==============================================================
		void setBMax2(bool bMax2, int begin, double gamma);
		__property double BIntensityGain = { write = bIntensityGain
		};
		__property bool BMax = { write = bMax };

		void setKeepMaxLuminance(KeepMaxLuminance keepMaxLuminance);
		void setKeepMaxLuminanceSmooth2NativeWhite(int over, bool autoParameter);
		__property DeHook DeHookMode = { read = dehook, write = dehook
		};
		__property bool ForceAssignTargetWhite = { write = forceAssignTargetWhite
		};

		//==============================================================

		//==============================================================
		//intensity
		//==============================================================
		__property double RTargetIntensity = { write = rTargetIntensity
		};
		__property double BTargetIntensity = { write = bTargetIntensity
		};
		void setSmoothIntensity(int start, int end);
		__property bool AutoIntensityInMultiGen = { write = autoIntensityInMultiGen
		};
		//==============================================================

		void setMultiGen(bool enable, int times);
		__property bool KeepMaxYInMultiGen = { write = keepMaxYInMultiGen
		};
		__property bool LuminanceCalibration = { write = luminanceCalibration
		};
		__property bool LuminanceCalibrationOnly = { write = luminanceCalibrationOnly
		};
		__property bool FineLuminanceCalibrate = { write = fineLuminanceCalibrate
		};
		//==============================================================
		// for NB Noise
		//==============================================================
		__property bool GByPass = { write = gByPass };
		__property bool AvoidFRCNoise = { write = avoidFRCNoise };
		//==============================================================

		__property bool NewMethod = { write = useNewMethod };
		__property bool FeedbackFix = { write = feedbackFix };
		__property string ExcuteStatus = { read = excuteStatus };
		bool componentVectorLuminanceCheckResult;
		bool increaseZOfTarget;
		//==============================================================

	      private:
		//==============================================================
		// store
		//==============================================================
		 RGB_vector_ptr dglut;
		Component_vector_ptr originalComponentVector;
		Component_vector_ptr luminanceVector;
		RGBGamma_ptr finalRGBGamma;
		RGBGamma_ptr initialRGBGamma;
		XYZ_vector_ptr targetXYZVector;
		XYZ_vector_ptr multiGenTargetXYZVector;

		 bptr < MeasureCondition > measureCondition;
		 bptr < BitDepthProcessor > bitDepth;
		FeedbackListener *feedbackListener;
		//==============================================================

		//==============================================================

		//==============================================================
		// 外部componenet
		//==============================================================
		 bptr < i2c::TCONControl > tconctrl;
		 bptr < ComponentFetcher > fetcher;
		 bptr < cms::measure::MaxMatrixIntensityAnalyzer > secondWhiteAnalyzer;
		//==============================================================

		//==============================================================
		// functions
		//==============================================================
		void setGammaCurve0(double_vector_ptr gammaCurve);
		void setGammaCurve0(double_vector_ptr rgammaCurve,
				    double_vector_ptr ggammaCurve, double_vector_ptr bgammaCurve);
		Component_vector_ptr fetchComponentVector();
		Component_vector_ptr fetchComponentVector(bptr < MeasureCondition >
							  measureCondition);
		Component_vector_ptr fetchLuminanceVector(bptr < MeasureCondition >
							  measureCondition);

		bool checkComponentVectorLuminance(Component_vector_ptr componentVector);
		RGB_vector_ptr getDGLutOpResult(RGB_vector_ptr dglut);
		RGB_vector_ptr oldMethod(DGLutGenerator & generator,
					 bptr < PanelRegulator >
					 panelRegulator, const Dep::MaxValue & quantizationBit);

		//==============================================================
		// white XYZ relative
		//==============================================================
		XYZ_ptr measureFirstAnalyzerReferenceRGB() const;
		XYZ_ptr maxWhiteXYZ;
		XYZ_ptr targetWhiteXYZ;
		void initWhiteXYZ(XYZ_ptr referenceXYZ);
		//==============================================================

		double_vector_ptr initLuminanceGammaCurve(XYZ_ptr referenceXYZ);
		 bptr < AdvancedDGLutGenerator > initAdvancedDGLutGenerator();
		RGB_vector_ptr newMethod(bptr < PanelRegulator > panelRegulato);

		void fixChromaticityReverseByFeedback(RGB_vector_ptr dglut);
		int_vector_ptr getReverseIndexVector(double_vector_ptr
						     deltaVector, int start, int end);
		 int_vector_ptr
		    getMustMeasureZoneIndexVector(double_vector_ptr
						  dxofBase,
						  double_vector_ptr dyofBase, int start, int end);
		void pushBackNumber(int_vector_ptr result, int number);
		double_vector_ptr selectDelta(double_vector_ptr dxofBase,
					      double_vector_ptr dyofBase, Dep::Channel & ch);

		Component_vector_ptr getDimComponentVector(RGB_vector_ptr dglut);
		bool isDoDeHook();
		 bptr < cms::measure::IntensityAnalyzerIF > getFirstAnalzyer() const;

		//==============================================================

		//==============================================================
		// 2nd white analyzer
		//==============================================================
		void init2ndWhiteAnalyzer(KeepMaxLuminance keepMaxLuminance, DeHook deHook);
		//==============================================================


		//==============================================================
		// smooth
		//==============================================================

		//==============================================================
		// gamma curve relative
		//==============================================================
		//一段式gamma
		static double_vector_ptr getGammaCurveVector(double gamma, int n, int
							     effectiven);
		static double_vector_ptr get10BitGammaCurveVector(double gamma, int n,
								  int effectiven);
		//兩段式gamma
		static double_vector_ptr getGammaCurveVector(double
							     dimGamma, int
							     dimGammaEnd, double
							     brightGamma, int n, int
							     effectiven);
		//三段式gamma
		static double_vector_ptr getGammaCurveVector(double
							     dimGamma, int
							     dimGammaEnd, int
							     middleGammaEnd, double
							     brightGamma, int n, int
							     effectiven);
		double_vector_ptr getOriginalGammaCurve(Component_vector_ptr componentVector);
		//==============================================================

		 bptr < PanelRegulator > getPanelRegulatorForDeHook();
		 bptr < PanelRegulator > getPanelRegulatorForTargetWhite();
	      public:

		static double_vector_ptr
		    getLuminanceGammaCurve(double_vector_ptr
					   normalGammaCurve,
					   double maxLuminance, double minLuminance);

		static double_vector_ptr
		    getLuminanceGammaCurve(double_vector_ptr
					   normalGammaCurve,
					   double maxLuminance,
					   double minLuminance,
					   bool absGamma,
					   int absGammaStartGL,
					   double startGLAboveGamma, KeepL keepL, int effectiven);
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

		RGB_vector_ptr getCCTDGLut(bptr < MeasureCondition >
					   measureCondition,
					   bptr < cms::colorformat::DGLutFile > dgLutFile);
		RGB_vector_ptr getGammaDGLut(bptr < MeasureCondition > measureCondition);
		 bptr < cms::colorformat::DGLutFile >
		    storeDGLutFile(const std::string & filename, RGB_vector_ptr dglut);
		void storeInfo2DGLutFile(bptr < cms::colorformat::DGLutFile > dglutFile);
		void storeDGLut2DGLutFile(bptr <
					  cms::colorformat::DGLutFile >
					  dglutFile, RGB_vector_ptr dglut);
		__property bptr <
		    cms::measure::MaxMatrixIntensityAnalyzer >
		    SecondWhiteAnalyzer = { read = secondWhiteAnalyzer, write = secondWhiteAnalyzer
		};
		__property bptr < i2c::TCONControl > TCONControl = { write = tconctrl };
		void setFeedbackListener(FeedbackListener * listener);
		 bptr < cms::measure::MeterMeasurement > getMeterMeasurement() const;
		__property bool AlterGammaCurveAtDeHook2 = { write = alterGammaCurveAtDeHook2
		};
		String dgLutOpErrorMessage;
		String errorMessage;
		//==============================================================



	    };


	};
    };
};

#endif

