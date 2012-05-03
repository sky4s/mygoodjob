#ifndef LCDCALIBRATORH
#define LCDCALIBRATORH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
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
	    extern bool pcWithTCONInput;

	    /*
	       �u�nDeHook���}, �򥻤W�N�O�nPanelRegulator�����ܭ��O�S��, �A���q��
	       ���ܪ���ǴN�O��Target White����׶}Hook

	       �Ĥ@�NDeHook²�z:
	       ��TargetWhite��B�����令B intensity�̤j�I, �]��255���@�I�N�O���B Intensity�̤j�I,
	       �]���i�H�׶}Intensity���઺���D

	       �ĤG�NDeHook²�z:
	       �Ĥ@�N���W�j, �򥻤W�����P�Ĥ@�N�L�~, ���O����ؿﶵ
	       1.B Gap�u��: ��BGap�̤p
	       2.Gamma�u��: ��Gamma�̱���ؼ�Gamma

	       ��ӿﶵ�O���۬�Ĳ, ��trade-off��, �ҥH�~�}���ӿﶵ�ѿ��.
	       1.B Gap�u��
	       �P�Ĥ@�NDe-Hook�ۦP������, ���O��B Intensity�̤j�I���b254, �p���i�H�i�@�B�Y�pB Gap
	       �ѩ�O���b254, �]���ĥΪ�RGB�N���|�O255 255 250(���]B Intensity�̤j�O250)���զX.
	       R&G�|�O��250��p����, ���O�o�O�һPPanel White��dxy <0.003(Panel White��255/255/255)
	       �BGamma����1.5~3(�����ڭ̤��w��SPEC, �D�Ȥ�n�D)

	       �ƦܱNB Intensity�̤j�I���b253...252...��i�H�i�@�B�Y�pB Gap
	       (���٬O�n��uGamma 1.5~3���W�h)

	       2.Gamma�u��
	       �򥻳W�h���P��B Gap�u��, ���O�u�|��B Intensity��b�̱���ؼ�Gamma(Ĵ�p2.2)���Ƕ�,
	       �T�O���Gamma������ؼЭ�


	     */
	    enum DeHook {
		None,
		KeepCCT,	//�Ĥ@�N��DeHook, ��TargetWhite��B�����令B intensity�̤j�I
		SecondWithBGap1st,	//�ĤG�NDeHook, ���O�H���CB Gap���u��
		SecondWithGamma1st,	//�ĤG�NDeHook, ���O�HGamma�u��(�۹諸B Gap�N�L�k���C)
	    };


	     Enumeration(SecondWhite)
	     None, MaxRGB, DeHook, DeHook2, EnumerationEnd();

	    class LCDCalibrator {
		friend class cms::colorformat::DGLutProperty;
		friend class cms::lcd::calibrate::AdvancedDGLutGenerator;
		friend class cms::lcd::calibrate::DeHookProcessor;
	      private:

		//==============================================================
		// �ե��Ѽ�
		//==============================================================
		 DimCorrect correct;
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
		bool keepMaxYInMultiGen;
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
		//�Ψӵ��O�O�_���ΤFpanel regulator
		bool remapped;
		DeHook dehook;
		int maxBRawGrayLevel;
		int maxBDGGrayLevel;
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
		//�ϥηs�����h��target����k�h���DG
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
		void setRBInterpolation(int under);
		void setNonDimCorrect();
		void setDefinedDim(int under, double strength);
		__property int DimFixEnd = { write = dimFixEnd };
		__property bool DimFix = { write = dimFix };
		__property double DimFixThreshold = { write = dimFixThreshold
		};
		__property bool KeepDarkLevel = { read = keepDarkLevel, write = keepDarkLevel
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
				      int startGrayLevel, double startGrayLevelAboveGamma);
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
		__property bool KeepMaxYInMultiGen = { write = keepMaxYInMultiGen };


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
		// �~��componenet
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
		RGB_vector_ptr getDGLutOpResult(RGB_vector_ptr dglut);
		RGB_vector_ptr oldMethod(DGLutGenerator & generator,
					 bptr < PanelRegulator >
					 panelRegulator, const Dep::MaxValue & quantizationBit);
		RGB_vector_ptr newMethod(bptr < PanelRegulator > panelRegulato);

		void fixChromaticityReverseByFeedback(RGB_vector_ptr dglut);
		int_vector_ptr getReverseIndexVector(double_vector_ptr deltaVector, int start,
						     int end);
		int_vector_ptr getMustMeasureZoneIndexVector(double_vector_ptr dxofBase,
							     double_vector_ptr dyofBase, int start,
							     int end);
		void pushBackNumber(int_vector_ptr result, int number);
		double_vector_ptr selectDelta(double_vector_ptr dxofBase,
					      double_vector_ptr dyofBase, Dep::Channel & ch);

		Component_vector_ptr getDimComponentVector(RGB_vector_ptr dglut);
		bool isDoDeHook();
		//==============================================================

		//==============================================================
		// 2nd white analyzer
		//==============================================================
		void init2ndWhiteAnalyzer(KeepMaxLuminance keepMaxLuminance, DeHook deHook);
		//static SecondWhite getSecondWhite(KeepMaxLuminance keepMaxLuminance, DeHook deHook);
		//int getMaxBIntensityRawGrayLevel();
		//bptr < cms::devicemodel::LCDModel > getLCDModelForDeHook(int blueMaxGrayLevel);
		//==============================================================


		//==============================================================
		// �q��
		//==============================================================
		static RGB_vector_ptr colorimetricQuantization(RGB_vector_ptr dglut, int quadrant);
		//==============================================================
		//==============================================================
		// smooth
		//==============================================================

		//==============================================================

		static double_vector_ptr getGammaCurveVector(double gamma, int n, int
							     effectiven);

		static double_vector_ptr getGammaCurveVector(double
							     dimGamma, int
							     dimGammaEnd, double
							     brightGamma, int n, int
							     effectiven);
		static double_vector_ptr getGammaCurveVector(double
							     dimGamma, int
							     dimGammaEnd, int
							     middleGammaEnd, double
							     brightGamma, int n, int
							     effectiven);
		double_vector_ptr getOriginalGammaCurve(Component_vector_ptr componentVector);
	      public:

		static double_vector_ptr
		    getLuminanceGammaCurve(double_vector_ptr
					   normalGammaCurve, double maxLuminance,
					   double minLuminance);

		static double_vector_ptr
		    getLuminanceGammaCurve(double_vector_ptr
					   normalGammaCurve,
					   double maxLuminance,
					   double minLuminance,
					   bool absGamma,
					   int absGammaStartGL,
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
		//==============================================================



	    };


	};
    };
};

#endif

