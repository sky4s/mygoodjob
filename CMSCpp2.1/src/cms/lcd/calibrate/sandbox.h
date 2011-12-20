#ifndef SANDBOXH
#define SANDBOXH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include "dimdg.h"
#include <gui/event/listener.h>


namespace cms {
    namespace lcd {
	namespace calibrate {

	    enum Domain {
		CIExy, CIEuv, CIEuvPrime
	    };
	    static XYZ_ptr getTargetXYZ(double v1, double v2, double v3, Domain domain);
	    static XYZ_ptr getTargetXYZ(double x, double y, double Y);

	    class AdvancedDGLutGenerator:private DimDGLutGenerator, gui::event::WindowAdapter {
	      private:
		const LCDCalibrator & c;
		bool isAvoidHook(XYZ_ptr targetXYZ, double offsetK);
		XYZ_ptr getXYZ(XYZ_ptr XYZ, double offsetK);
		bool isDuplicateBlue100(XYZ_ptr targetXYZ);
		/*double rTargetIntensity;
		   double gTargetIntensity;
		   double bTargetIntensity;
		   bool autoIntensity; */
		RGB_ptr idealIntensity;
		/*bool smoothIntensity;
		   int smoothIntensityStart;
		   int smoothIntensityEnd; */

		bool stopMeasure;
		//bool multiGen;
		//int multiGenTimes, multiGenStart, multiGenEnd;
		//multigen���ɭԷ|�Ψ�fetcher(�]���n���_���s�q��)
		 bptr < cms::lcd::calibrate::ComponentFetcher > fetcher;
		 bptr < BitDepthProcessor > bitDepth;
		 bptr < cms::measure::IntensityAnalyzerIF > analyzer2nd;
		const bool smoothMode;
		XYZ_vector_ptr targetXYZVector;
		//bool autoParameter;
		int autoBrightTurn;
		int autoBrightWidth;
		int brightTurn;
		//double middleCCTRatio;

		Component_vector_ptr componentVector2;
		 bptr < PanelRegulator > panelRegulator1;
		 bptr < PanelRegulator > panelRegulator2;

		RGBGamma_ptr rgbGenerateResult;
		void init();
		XYZ_vector_ptr getTarget0(XYZ_ptr startXYZ, XYZ_ptr targetXYZ, XYZ_ptr endXYZ,
					  double_vector_ptr luminanceGammaCurve, int dimTurn,
					  int brightTurn, double dimGamma, double brightGamma,
					  int brightWidth);
		XYZ_vector_ptr getTarget0(XYZ_ptr startXYZ, XYZ_ptr targetXYZ, XYZ_ptr endXYZ,
					  double_vector_ptr luminanceGammaCurve, int dimTurn,
					  int brightTurn, double dimGamma, double brightGamma,
					  int brightWidth, double middleCCTRatio);

	      public:
		 AdvancedDGLutGenerator(Component_vector_ptr componentVector,
					bptr < cms::lcd::calibrate::ComponentFetcher > fetcher,
					bptr < cms::measure::IntensityAnalyzerIF > analyzer1,
					bptr < cms::measure::IntensityAnalyzerIF > analyzer2nd,
					bptr < BitDepthProcessor > bitDepth,
					const LCDCalibrator & calibrator);

		 AdvancedDGLutGenerator(Component_vector_ptr componentVector,
					bptr < cms::lcd::calibrate::ComponentFetcher > fetcher,
					bptr < BitDepthProcessor > bitDepth,
					const LCDCalibrator & calibrator);



		RGB_vector_ptr produce(XYZ_vector_ptr targetXYZVector);


		//void setTargetIntensity(double_array intensity);
		virtual void windowClosing(TObject * Sender, TCloseAction & Action);
		//void setMultiGen(bool enable, int times);
		XYZ_vector_ptr getTargetXYZVector();
		XYZ_vector_ptr getTargetXYZVector(XYZ_ptr targetWhite,
						  double_vector_ptr luminanceGammaCurve,
						  int dimTurn, int brightTurn, double dimGamma,
						  double brightGamma, int brightWidth);
		XYZ_vector_ptr getTargetXYZVector(XYZ_ptr targetWhite, XYZ_ptr nativeWhite,
						  double_vector_ptr luminanceGammaCurve,
						  int dimTurn, int brightTurn, double dimGamma,
						  double brightGamma, int brightWidth);
	      private:


		static XYZ_vector_ptr
		    getBrightGammaTarget(double_vector_ptr luminanceGammaCurve,
					 XYZ_ptr startXYZ, XYZ_ptr endXYZ, double brightGamma,
					 int brightTurn, int brightWidth,
					 bptr < BitDepthProcessor > bitDepth);

		static bool isDuplicateBlue100(Component_vector_ptr componentVector);
		RGB_vector_ptr produceDGLutMulti(XYZ_vector_ptr
						 targetXYZVector,
						 Component_vector_ptr componentVector);
		RGB_ptr getIdealIntensity(Component_vector_ptr componentVector,
					  bptr < cms::measure::MaxMatrixIntensityAnalyzer >
					  analyzer);
		RGB_vector_ptr produceDGLut(XYZ_vector_ptr targetXYZVector,
					    Component_vector_ptr componentVector,
					    bptr < cms::measure::IntensityAnalyzerIF > analyzer,
					    bptr < PanelRegulator > panelRegulator);

		Component_ptr getFRCAbilityComponent(int grayLevel, RGB_ptr rgb,
						     bptr < cms::measure::IntensityAnalyzerIF >
						     analyzer,
						     Component_vector_ptr componentVector);

		bool checkTargetXYZVector(XYZ_vector_ptr targetXYZVector, int start, int end,
					  double deltaabThreshold);
		XYZ_ptr getMiddleXYZ(int middleIndex, double middleCCTRatio, XYZ_ptr targetXYZ);

	      public:
		static RGB_vector_ptr smooth(RGB_vector_ptr result1,
					     RGB_vector_ptr result2,
					     bptr < BitDepthProcessor > bitDepth, int brightTurn);
		//void setAutoParameter(bool autoParameter);
		int getAutoBrightTurn();
		int getAutoBrightWidth();
		void setComponentVector2(Component_vector_ptr componentVector2,
					 bptr < PanelRegulator > panelRegulator2);
		void setPanelRegulator(bptr < PanelRegulator > panelRegulator);
		//void setMiddleCCTRatio(double ratio);
		__property RGBGamma_ptr RGBGenerateResult = { read = rgbGenerateResult };
		/*__property bool AutoIntensity = { write = autoIntensity };
		__property double RTargetIntensity = { write = rTargetIntensity };
		__property double GTargetIntensity = { write = gTargetIntensity };
		__property double BTargetIntensity = { write = bTargetIntensity };*/
		__property RGB_ptr IdealIntensity = { read = idealIntensity };
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

		static XYZ_vector_ptr getTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
						double_vector_ptr luminanceGammaCurve,
						Domain domain, double gamma);
		static XYZ_vector_ptr getTarget(XYZ_ptr startXYZ, XYZ_ptr endXYZ,
						double_vector_ptr luminanceGammaCurve,
						double gamma);
	    };
	};
    };
};

#endif

