#ifndef SANDBOXH
#define SANDBOXH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include "dimdg.h"


namespace cms {
    namespace lcd {
	namespace calibrate {

	    enum Domain {
		CIExy, CIEuv, CIEuvPrime
	    };

	    class AdvancedDGLutGenerator:private DimDGLutGenerator, WindowListener {
	      private:
		//�ĥΥΤj�Ȫ�B Intensity�Ϊ�100?
		bool useMaxTargetBIntensity;
		bool isAvoidHook(XYZ_ptr targetXYZ, double offsetK);
		XYZ_ptr getXYZ(XYZ_ptr XYZ, double offsetK);
		bool isDuplicateBlue100(XYZ_ptr targetXYZ);
		double bTargetIntensity;
		bool stopMeasure;
		bool multiGen;
		int multiGenTimes, multiGenStart, multiGenEnd;
		 bptr < cms::lcd::calibrate::ComponentFetcher > fetcher;
		 bptr < BitDepthProcessor > bitDepth;
		 bptr < cms::measure::IntensityAnalyzerIF > analyzer2;
		const bool smoothMode;
	      public:
		 AdvancedDGLutGenerator(Component_vector_ptr
					componentVector,
					bptr <
					cms::measure::IntensityAnalyzerIF >
					analyzer1,
					bptr < cms::measure::IntensityAnalyzerIF > analyzer2,
					bptr < BitDepthProcessor > bitDepth);
		 AdvancedDGLutGenerator(Component_vector_ptr componentVector,
					bptr < cms::lcd::calibrate::ComponentFetcher > fetcher,
					bptr < BitDepthProcessor > bitDepth);
		RGB_vector_ptr produce(XYZ_ptr targetWhite, double_vector_ptr luminanceGammaCurve,
				       int dimTurn, int brightTurn, double dimGamma,
				       double brightGamma);

		XYZ_vector_ptr getAvoidHookTarget(XYZ_ptr startXYZ,
						  XYZ_ptr targetXYZ,
						  double_vector_ptr
						  luminanceGammaCurve,
						  int dimTurn, int brightTurn, double dimGamma);
		XYZ_vector_ptr getTarget(XYZ_ptr startXYZ,
					 XYZ_ptr targetXYZ, XYZ_ptr endXYZ,
					 double_vector_ptr
					 luminanceGammaCurve, int dimTurn,
					 int brightTurn, double dimGamma, double brightGamma);

		void setUseMaxTargetBIntensity(bool useMaxTargetBIntensity);
		void setBTargetIntensity(double bTargetIntensity);
		void windowClosing();
		void setMultiGen(bool enable, int times);
	      private:

		static XYZ_vector_ptr getDimGammaTarget(double_vector_ptr
							luminanceGammaCurve,
							XYZ_ptr startXYZ,
							XYZ_ptr endXYZ,
							double dimGamma, int dimTurn);
		static XYZ_vector_ptr
		    getBrightGammaTarget(double_vector_ptr
					 luminanceGammaCurve,
					 XYZ_ptr startXYZ, XYZ_ptr endXYZ,
					 double brightGamma,
					 int brightTurn, bptr < BitDepthProcessor > bitDepth);
		static XYZ_ptr getTargetXYZ(double v1, double v2, double v3, Domain domain);
		static XYZ_ptr getTargetXYZ(double v1, double v2, double v3);
		static bool isDuplicateBlue100(Component_vector_ptr componentVector);
		RGB_vector_ptr produceDGLut_(XYZ_vector_ptr
					     targetXYZVector, Component_vector_ptr componentVector);
		RGB_vector_ptr produceDGLut0(XYZ_vector_ptr
					     targetXYZVector,
					     Component_vector_ptr
					     componentVector,
					     bptr < cms::measure::IntensityAnalyzerIF > analyzer);
	      public:
		static RGB_vector_ptr smooth(RGB_vector_ptr result1,
					     RGB_vector_ptr result2,
					     bptr < BitDepthProcessor > bitDepth, int brightTurn);
	    };



	    class DimTargetGenerator {
	      public:

		static XYZ_vector_ptr getLinearTarget(XYZ_ptr startXYZ,
						      XYZ_ptr endXYZ,
						      double_vector_ptr luminanceGammaCurve);
		static XYZ_vector_ptr getLinearTarget(XYZ_ptr startXYZ,
						      XYZ_ptr endXYZ,
						      double_vector_ptr
						      luminanceGammaCurve, Domain domain);
		static XYZ_vector_ptr getGammaTarget(XYZ_ptr startXYZ,
						     XYZ_ptr endXYZ,
						     double_vector_ptr
						     luminanceGammaCurve, double gamma);
	    };
	};
    };
};

#endif
