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
//#include "feedback.h"
/*
 UI�P����Object�p�������

 UI�W���ﶵ�]�w��, ���w�ݭn�ǰe�줺��Object, �]�w��Object����property(�S�x)
 �]��UI���w�|�I�sObject��setXXX(), ��o�ǰѼƶǰe��Object
 �ҥH�C�h�@���Ѽ�, UI�N�n�I�sObject, Object�]�o�}�۹�M��setXXX() method, �~�i�H�����o���u�@.
 �ѹ����ܺ��H=.=

 ���S����k�i�H�۰ʤƬƦܥb�۰ʤƧ����o��Ʊ��O?
 �γ\�u��z�LsetProperty(propertyName, propertyValue); �o�˪��禡�a!

 __property�o����r�ٺ⤣�����F��! �u�n�bheader�ŧi�N�n! �K�h.cpp�w�qsetXXX���·�!
 �]�n!
*/


namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace math;

	    class LCDCalibrator {
		friend class cms::colorformat::DGLutProperty;
		friend class cms::lcd::calibrate::AdvancedDGLutGenerator;
	      private:

		//==============================================================
		// �ե��Ѽ�
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
		bool absoluteGamma;
		int absoluteGammaStart;
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
		//==============================================================

		//==============================================================
		// others
		//==============================================================
		double bIntensityGain;
		bool avoidFRCNoise;
		bool useNewMethod;
		//��ت��p�U accurateMode�|���@��, ��M���n�f�ttcon�~���
		//�ҥH�@�w�O�f�tPanelRegulator�h�קﭱ�O�S�ʪ�
		// 1. KeepMaxLuminance��NativeWhiteAdvanced���ɭ�
		//   ���F�����G�򱵪�NativeWhite, �ҥHTarget White��B�אּ�����I
		// 2. �N���O���I�קאּ�ؼХ��I
		//   �קﭱ�O�S�������O���I���ؼХ��I, �ϨD�X�Ӫ����I���n�N�O�ؼ�
		bool accurateMode;
		//�p�G��ʥh�ק�DG, ��B�������I�ױ�, �N�ݭn�ϳo��flag��true
		bool manualAccurateMode;
		//�Ψӵ��O�O�_���ΤFpanel regulator
		bool remapped;
		//dprecated
		double middleCCTRatio;

		//for feedback
		bool feedbackFix;
		int feedbackFixCount;
		int initDefectCount;
		double_array maxMeasureError;
		bool colorimetricQuanti;
		QuantiType quantiType;
		 bptr < cms::lcd::calibrate::FeedbackFixer > feedbackFixer;

		//dprecated
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
		void setAbsoluteGamma(bool absoluteGamma, int start);

		void setBMax2(bool bMax2, int begin, double gamma);

		void setKeepMaxLuminance(KeepMaxLuminance keepMaxLuminance);
		void setKeepMaxLuminanceNativeWhiteAdvanced(int over,
							    double gamma, bool autoParameter);

		void setMultiGen(bool enable, int times);
		void setSmoothIntensity(int start, int end);
		__property int DimFixEnd = { write = dimFixEnd };
		__property bool DimFix = { write = dimFix };
		__property double DimFixThreshold = { write = dimFixThreshold
		};
		__property bool GByPass = { write = gByPass };
		__property double BIntensityGain = { write = bIntensityGain
		};
		__property bool BMax = { write = bMax };
		__property bool AvoidFRCNoise = { write = avoidFRCNoise };
		__property bool NewMethod = { write = useNewMethod };
		__property bool SkipInverseB = { write = skipInverseB };
		__property double RTargetIntensity = { write = rTargetIntensity
		};
		__property double BTargetIntensity = { write = bTargetIntensity
		};
		__property bool AccurateMode = { write = accurateMode };
		__property bool ManualAccurateMode = { write = manualAccurateMode
		};
		__property double MiddleCCTRatio = { write = middleCCTRatio
		};
		__property bool FeedbackFix = { write = feedbackFix };
		__property bool SmoothComponent = { read = smoothComponent,
		    write = smoothComponent
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
		//bptr < FeedbackListener > feedbackListener;
		FeedbackListener *feedbackListener;
		XYZ_ptr targetWhiteXYZ;
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
		RGB_vector_ptr getDGLutOpResult(RGB_vector_ptr dglut);
		RGB_vector_ptr oldMethod(DGLutGenerator & generator,
					 bptr < PanelRegulator >
					 panelRegulator, const Dep::MaxValue & quantizationBit);
		RGB_vector_ptr newMethod(bptr < PanelRegulator > panelRegulato);

		void fixReverseByFeedback(RGB_vector_ptr dglut);
		int checkReverse(double_vector_ptr deltaVector);
		int checkReverse(double_vector_ptr deltaVector, int start, int end);
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

		//==============================================================
		// �q��
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
		static double_vector_ptr getAbsoluteGammaCurveVector(double
								     gamma, int n, int
								     effectiven,
								     Component_vector_ptr
								     componentVector);
		static double_vector_ptr getGammaCurveVector(double
							     dimGamma, int
							     dimGammaEnd, double
							     brightGamma, int n, int
							     effectiven);


	      public:

		static double_vector_ptr
		    getLuminanceGammaCurve(double_vector_ptr
					   normalGammaCurve,
					   double maxLuminance, double minLuminance);
		static double_vector_ptr
		    getLuminanceGammaCurve(double_vector_ptr normalGammaCurve,
					   double maxLuminance, double minLuminance,
					   bool absoluteGamma, int absoluteGammaStart);
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

		__property bptr <
		    cms::measure::MaxMatrixIntensityAnalyzer >
		    NativeWhiteAnalyzer = { read = nativeWhiteAnalyzer, write = nativeWhiteAnalyzer
		};
		__property bptr < i2c::TCONControl > TCONControl = { write = tconctrl };
		void setFeedbackListener(FeedbackListener * listener);
		//==============================================================



	    };


	};
    };
};

#endif

