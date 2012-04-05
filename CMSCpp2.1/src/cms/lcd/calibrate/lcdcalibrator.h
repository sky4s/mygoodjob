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
//#include "feedback.h"
#include <cms/measure/include.h>	//20120302


namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace math;

	    extern bool debugMode;
	    extern bool linkCA210;
	    extern bool pcWithTCONInput;

	    enum DeHook {
		None,
		//Original,	//廢棄
		//Evolution,	//廢棄
		KeepCCT /*Original */ ,
		ReduceBGap	/*Evolution */
	    };

	    class LCDCalibrator {
		friend class cms::colorformat::DGLutProperty;
		friend class cms::lcd::calibrate::AdvancedDGLutGenerator;
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
		double dimStrength;
		int dimFixEnd;
		bool dimFix;
		double dimFixThreshold;
		bool keepDarkLevel;
		//==============================================================

		//==============================================================
		//bmax
		//==============================================================
		bool bMax;
		bool bMax2;
		int bMax2Begin;
		double bMax2Gamma;
		int maxBRawGrayLevel;
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
		bool highlightGammaFix;
		//==============================================================

		//==============================================================
		// max lumi
		//==============================================================
		KeepMaxLuminance keepMaxLuminance;
		int keepMaxLumiOver;
		bool autoKeepMaxLumiParameter;
		//==============================================================

		//==============================================================
		//multi
		//==============================================================
		bool multiGen;
		int multiGenTimes;
		//==============================================================

		//==============================================================
		//intensity
		//==============================================================
		double rTargetIntensity;
		double gTargetIntensity;
		double bTargetIntensity;
		bool autoIntensity;
		RGB_ptr idealIntensity;
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
		int deHookRBGZone;
		//==============================================================

		//==============================================================
		// feedback
		//==============================================================
		bool feedbackFix;
		int feedbackFixCount;
		int initDefectCount;
		double_array maxMeasureError;
		bool colorimetricQuanti;
		QuantiType quantiType;
		 bptr < cms::lcd::calibrate::FeedbackFixer > feedbackFixer;
		//==============================================================
		//==============================================================
		// others
		//==============================================================
		bool avoidFRCNoise;
		//使用新的有多種target的方法去找到DG
		bool useNewMethod;

		string excuteStatus;
		//bool debugMode;
		//==============================================================

	      public:
		//==============================================================
		// options
		//==============================================================

		//==============================================================
		//dim
		//==============================================================
		void setP1P2(int p1, int p2);
		void setRBInterpolation(int under);
		void setNonDimCorrect();
		void setDefinedDim(int under, double strength);
		__property int DimFixEnd = { write = dimFixEnd };
		__property bool DimFix = { write = dimFix };
		__property double DimFixThreshold = { write = dimFixThreshold
		};
                __property bool KeepDarkLevel = {read = keepDarkLevel, write = keepDarkLevel };
		//==============================================================

		//==============================================================
		//gamma
		//==============================================================
		void setGamma(double gamma);
		//2-gamma
		void setGamma(double dimGamma, int dimGammaEnd, double brightGamma);
		//3-gamma
		void setGamma(double dimGamma, int dimGammaEnd, int middleGammaEnd,
			      double brightGamma);
		void setGamma(double rgamma, double ggamma, double bgamma);
		void setGammaCurve(double_vector_ptr gammaCurve);
		void setGammaCurve(double_vector_ptr rgammaCurve,
				   double_vector_ptr ggammaCurve, double_vector_ptr bgammaCurve);
		void setOriginalGamma();
		void setAbsoluteGamma(bool absoluteGamma, int startGrayLevel,
				      double startGrayLevelAboveGamma);
		__property bool HighlightGammaFix = {read = highlightGammaFix, write = highlightGammaFix };
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
		__property DeHook DeHookMode = { read = dehook, write = dehook };
		//void setEvolutionDeHook(int zone);
		void setDeHookReduceBGap(int zone);
		//__property int EvolutionDeHookZone = { read = evoDeHookZone };
		__property int DeHookRBGZone = { read = deHookRBGZone };
		//==============================================================

		//==============================================================
		//intensity
		//==============================================================
		__property double RTargetIntensity = { write = rTargetIntensity
		};
		__property double BTargetIntensity = { write = bTargetIntensity
		};
		void setSmoothIntensity(int start, int end);
		//==============================================================

		void setMultiGen(bool enable, int times);


		//==============================================================
		// for NB Noise
		//==============================================================
		__property bool GByPass = { write = gByPass };
		__property bool AvoidFRCNoise = { write = avoidFRCNoise };
		//==============================================================

		__property bool NewMethod = { write = useNewMethod };
		__property bool FeedbackFix = { write = feedbackFix };
		__property string ExcuteStatus = { read = excuteStatus };
		//==============================================================

	      private:
		//==============================================================
		// store
		//==============================================================
		 RGB_vector_ptr dglut;
		Component_vector_ptr originalComponentVector;
		double_vector_ptr luminanceVector;
		RGBGamma_ptr finalRGBGamma;
		RGBGamma_ptr initialRGBGamma;
		XYZ_vector_ptr targetXYZVector;

		 bptr < MeasureCondition > measureCondition;
		 bptr < BitDepthProcessor > bitDepth;
		FeedbackListener *feedbackListener;
		XYZ_ptr targetWhiteXYZ;
		//==============================================================

		//==============================================================

		//==============================================================
		// 
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
		double_vector_ptr fetchLuminanceVector();
		void init2ndWhiteAnalyzer(bool useMaxBIntensity);
		RGB_vector_ptr getDGLutOpResult(RGB_vector_ptr dglut);
		RGB_vector_ptr oldMethod(DGLutGenerator & generator,
					 bptr < PanelRegulator >
					 panelRegulator, const Dep::MaxValue & quantizationBit);
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
		//bool isDoDeHookOrg();
		//bool isDoDeHookEvo();
		bool isDoDeHookKeepCCT();
		bool isDoDeHookReduceBGap();

		//==============================================================
		// 量化
		//==============================================================
		static RGB_vector_ptr colorimetricQuantization(RGB_vector_ptr dglut, int quadrant);
		//==============================================================
		//==============================================================
		// smooth
		//==============================================================
		void smoothComponentVector(Component_vector_ptr componentVector);
		void smoothComponentVector2(Component_vector_ptr componentVector);
		static void smooth(double_array curve, int size, int times);
		static double_array getSmoothCurve(double_array
						   originalCurve,
						   double_array deltaCurve, int size);
		//==============================================================

		static double_vector_ptr getGammaCurveVector(double gamma, int n, int
							     effectiven);

		static double_vector_ptr getGammaCurveVector(double
							     dimGamma, int
							     dimGammaEnd, double
							     brightGamma, int n, int
							     effectiven);
		static double_vector_ptr getGammaCurveVector(double dimGamma, int dimGammaEnd,
							     int middleGammaEnd, double brightGamma,
							     int n, int effectiven);
		double_vector_ptr getOriginalGammaCurve(Component_vector_ptr componentVector);
	      public:

		static double_vector_ptr
		    getLuminanceGammaCurve(double_vector_ptr
					   normalGammaCurve,
					   double maxLuminance, double minLuminance);

		static double_vector_ptr
		    getLuminanceGammaCurve(double_vector_ptr normalGammaCurve,
					   double maxLuminance, double minLuminance,
					   bool absGamma, int absGammaStartGL,
					   double startGLAboveGamma, int effectiven);
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

		RGB_vector_ptr getCCTDGLut(bptr < MeasureCondition > measureCondition,
					   bptr < cms::colorformat::DGLutFile > dgLutFile);
		RGB_vector_ptr getGammaDGLut(bptr < MeasureCondition > measureCondition);
		 bptr < cms::colorformat::DGLutFile >
		    storeDGLutFile(const std::string & filename, RGB_vector_ptr dglut);
		/*void storeDGLutFile(RGB_vector_ptr dglut,
		   bptr < cms::colorformat::DGLutFile > dglutFile); */
		//bptr < DGLutFile > storeInfo2DGLutFile(const std::string & filename);
		void storeInfo2DGLutFile(bptr < cms::colorformat::DGLutFile > dglutFile);
		void storeDGLut2DGLutFile(bptr < cms::colorformat::DGLutFile > dglutFile,
					  RGB_vector_ptr dglut);

		/*__property bptr <
		    cms::measure::MaxMatrixIntensityAnalyzer >
		    NativeWhiteAnalyzer = { read = nativeWhiteAnalyzer, write = nativeWhiteAnalyzer
		};*/
		__property bptr <
		    cms::measure::MaxMatrixIntensityAnalyzer >
		    SecondWhiteAnalyzer = { read = secondWhiteAnalyzer, write = secondWhiteAnalyzer
		};
		__property bptr < i2c::TCONControl > TCONControl = { write = tconctrl };
		void setFeedbackListener(FeedbackListener * listener);
		//==============================================================



	    };


	};
    };
};

#endif

