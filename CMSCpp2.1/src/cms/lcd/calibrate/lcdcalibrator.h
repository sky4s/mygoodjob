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

/*
 UI與內部Object聯結的思維

 UI上的選項設定後, 必定需要傳送到內部Object, 設定為Object內的property(特徵)
 因此UI必定會呼叫Object的setXXX(), 把這些參數傳送到Object
 所以每多一項參數, UI就要呼叫Object, Object也得開相對映的setXXX() method, 才可以完成這項工作.
 老實講很瑣碎=.=

 有沒有辦法可以自動化甚至半自動化完成這件事情呢?
 或許只能透過setProperty(propertyName, propertyValue); 這樣的函式吧!

 __property這關鍵字還算不錯的東西! 只要在header宣告就好! 免去.cpp定義setXXX的麻煩!
 也好!
*/


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
		double dimStrength;
		int dimFixEnd;
		bool dimFix;
		double dimFixThreshold;
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
		double gamma, rgamma, ggamma, bgamma, dimGamma;
		int dimGammaEnd;
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
		bool feedbackFix;
		bool smoothComponent;
		//==============================================================

	      public:
		//==============================================================
		// options
		//==============================================================
		void setP1P2(int p1, int p2);
		void setRBInterpolation(int under);
		void setNonDimCorrect();
		void setDefinedDim(int under, double strength);

		void setGamma(double gamma);
		void setGamma(double dimGamma, int dimGammaEnd, double brightGamma);
		void setGamma(double rgamma, double ggamma, double bgamma);
		void setGammaCurve(double_vector_ptr gammaCurve);
		void setGammaCurve(double_vector_ptr rgammaCurve,
				   double_vector_ptr ggammaCurve, double_vector_ptr bgammaCurve);
		void setOriginalGamma();

		void setBMax2(bool bMax2, int begin, double gamma);

		void setKeepMaxLuminance(KeepMaxLuminance keepMaxLuminance);
		void setKeepMaxLuminanceNativeWhiteAdvanced(int over,
							    double gamma, bool autoParameter);

		void setMultiGen(bool enable, int times);
		__property int DimFixEnd = { write = dimFixEnd };
		__property bool DimFix = { write = dimFix };
		__property double DimFixThreshold = { write = dimFixThreshold };
		__property bool GByPass = { write = gByPass };
		__property double BIntensityGain = { write = bIntensityGain };
		__property bool BMax = { write = bMax };
		__property bool AvoidFRCNoise = { write = avoidFRCNoise };
		__property bool NewMethod = { write = useNewMethod };
		__property bool SkipInverseB = { write = skipInverseB };
		__property double BTargetIntensity = { write = bTargetIntensity };
		__property bool AccurateMode = { write = accurateMode };
		__property bool ManualAccurateMode = { write = manualAccurateMode };
		__property double MiddleCCTRatio = { write = middleCCTRatio };
		__property bool FeedbackFix = { write = feedbackFix };
		__property bool SmoothComponent = { read = smoothComponent, write = smoothComponent
		};
		//==============================================================


	      private:
		//==============================================================
		// store
		//==============================================================
		 RGB_vector_ptr dglut;
		Component_vector_ptr originalComponentVector;
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
		 bptr < cms::measure::MaxMatrixIntensityAnalyzer > nativeWhiteAnalyzer;
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

		void fixReverseByFeedback(RGB_vector_ptr dglut);
		int checkReverse(double_vector_ptr deltaVector);
		int checkReverse(double_vector_ptr deltaVector, int start, int end);
		int_vector_ptr getReverseIndexVector(double_vector_ptr deltaVector,
						     int start, int end);
		int_vector_ptr getMustMeasureZoneIndexVector(double_vector_ptr dxofBase,
							     double_vector_ptr dyofBase, int start,
							     int end);
		void pushBackNumber(int_vector_ptr result, int number);
		double_vector_ptr selectDelta(double_vector_ptr dxofBase,
					      double_vector_ptr dyofBase, Dep::Channel & ch);

		Component_vector_ptr getDimComponentVector(RGB_vector_ptr dglut);

		//==============================================================

		//==============================================================
		// smooth
		//==============================================================
		void smoothComponentVector(Component_vector_ptr componentVector);
		void smoothComponentVector2(Component_vector_ptr componentVector);
		static void smooth(double_array curve, int size, int times);
		static double_array getSmoothCurve(double_array originalCurve,
						   double_array deltaCurve, int size);
		//==============================================================
	      public:
		static double_vector_ptr getGammaCurveVector(double gamma, int n, int
							     effectiven);
		static double_vector_ptr getGammaCurveVector(double dimGamma, int dimGammaEnd,
							     double brightGamma, int n,
							     int effectiven);


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
		double_vector_ptr getOriginalGammaCurve(Component_vector_ptr componentVector);
		RGB_vector_ptr getCCTDGLut(bptr < MeasureCondition > measureCondition);
		RGB_vector_ptr getGammaDGLut(bptr < MeasureCondition > measureCondition);
		 bptr < cms::colorformat::DGLutFile >
		    storeDGLutFile(const std::string & filename, RGB_vector_ptr dglut);
		void storeDGLutFile(RGB_vector_ptr dglut,
				    bptr < cms::colorformat::DGLutFile > dglutFile);
		//bptr < cms::measure::MaxMatrixIntensityAnalyzer > getNativeWhiteAnalyzer();
		/*void setNativeWhiteAnalyzer(bptr <
		   cms::measure::MaxMatrixIntensityAnalyzer > analyzer); */
		__property bptr < cms::measure::MaxMatrixIntensityAnalyzer >
		    NativeWhiteAnalyzer = { read = nativeWhiteAnalyzer, write = nativeWhiteAnalyzer
		};
		//void setTCONControl(bptr < i2c::TCONControl > tconctrl);
		__property bptr < i2c::TCONControl > TCONControl = { write = tconctrl };
		//==============================================================



	    };

	    class ChromaticityAdjustEstimatorIF {
	      public:
		virtual double_array getdxdy(const Dep::Channel & ch, int grayLevel) = 0;
		virtual double_array getRdxGdy(int componentIndex) = 0;
	    };

	    /*
	       色度調整幅度的預測, 透過intensity
	     */
	    class IntensityEstimator:public ChromaticityAdjustEstimatorIF {
	      private:
		Component_vector_ptr componentVector;
		bptr < DGLutGenerator > dgLutGenerator;
		bptr < cms::measure::IntensityAnalyzerIF > analyzer;
		XYZ_ptr rXYZ, gXYZ, bXYZ;
		xyY_ptr getxyY(RGB_ptr intensity);
		 bptr < BitDepthProcessor > bitDepth;
	      public:
		 IntensityEstimator(Component_vector_ptr componentVector,
				    bptr < cms::measure::IntensityAnalyzerIF > analyzer,
				    bptr < BitDepthProcessor > bitDepth);
		virtual double_array getdxdy(const Dep::Channel & ch, int grayLevel);
		virtual double_array getRdxGdy(int componentIndex);
	    };

	    /*
	       色度調整幅度的預測, 透過量測
	     */
	    class MeasureEstimator:public ChromaticityAdjustEstimatorIF {
	      private:
		bptr < cms::measure::MeterMeasurement > mm;
		Component_vector_ptr componentVector;
		Component_vector_ptr storeComponentVector;
		RGB_vector_ptr dglut;
		 bptr < BitDepthProcessor > bitDepth;
		void init();
		int storeIndex;
		double_array getdxdy(XYZ_ptr XYZ0, XYZ_ptr XYZ1);
		const int size;
		RGB_ptr getMeasureBaseRGB(int index);
		bool useComponentVector;
		XYZ_ptr baseXYZ;
		XYZ_ptr measure(RGB_ptr rgb);
		bool measureRdxGdy;
		int_vector_ptr constrained;
	      public:
		 MeasureEstimator(Component_vector_ptr componentVector,
				  bptr < cms::measure::MeterMeasurement > mm,
				  bptr < BitDepthProcessor > bitDepth);
		 MeasureEstimator(Component_vector_ptr componentVector,
				  bptr < cms::measure::IntensityAnalyzerIF > analyzer,
				  bptr < BitDepthProcessor > bitDepth);
		 MeasureEstimator(RGB_vector_ptr dglut,
				  bptr < cms::measure::IntensityAnalyzerIF > analyzer,
				  bptr < BitDepthProcessor > bitDepth);
		virtual double_array getdxdy(const Dep::Channel & ch, int componentIndex);
		virtual double_array getRdxGdy(int componentIndex);
		~MeasureEstimator();
		void measure(int startIndex, int endIndex);

		void resetMeasure();

		double_vector_ptr dxofRVector;
		double_vector_ptr dyofGVector;
		double_vector_ptr dxofBase;
		double_vector_ptr dyofBase;
		__property bool MeasureRdxGdy = { write = measureRdxGdy };
		__property int_vector_ptr Constrained = { write = constrained };
	    };
	};
    };
};

#endif

