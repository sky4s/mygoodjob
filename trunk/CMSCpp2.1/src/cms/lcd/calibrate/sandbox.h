#ifndef SANDBOXH
#define SANDBOXH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "dimdg.h"


namespace cms {
    namespace lcd {
	namespace calibrate {

	    enum Domain {
		CIExy, CIEuv, CIEuvPrime
	    };

	    class AdvancedDGLutGenerator:private DimDGLutGenerator, WindowListener {
	      private:
		//採用用大值的B Intensity或者100?
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
		XYZ_vector_ptr targetXYZVector;
		bool autoParameter;
		int brightTurn;
	      public:
		 AdvancedDGLutGenerator(Component_vector_ptr componentVector,
					bptr < cms::measure::IntensityAnalyzerIF > analyzer1,
					bptr < cms::measure::IntensityAnalyzerIF > analyzer2,
					bptr < BitDepthProcessor > bitDepth);
		 AdvancedDGLutGenerator(Component_vector_ptr componentVector,
					bptr < cms::lcd::calibrate::ComponentFetcher > fetcher,
					bptr < BitDepthProcessor > bitDepth);
		RGB_vector_ptr produce(XYZ_ptr targetWhite, double_vector_ptr luminanceGammaCurve,
				       int dimTurn, int brightTurn, double dimGamma,
				       double brightGamma);
		RGB_vector_ptr produce(XYZ_ptr targetWhite, double_vector_ptr luminanceGammaCurve,
				       int dimTurn, int brightTurn, double dimGamma,
				       double brightGamma, int brightWidth);
		RGB_vector_ptr produce(XYZ_vector_ptr targetXYZVector);
		XYZ_vector_ptr getTarget0(XYZ_ptr startXYZ, XYZ_ptr targetXYZ, XYZ_ptr endXYZ,
					  double_vector_ptr luminanceGammaCurve, int dimTurn,
					  int brightTurn, double dimGamma, double brightGamma,
					  int brightWidth);

		void setUseMaxTargetBIntensity(bool useMaxTargetBIntensity);
		void setBTargetIntensity(double bTargetIntensity);
		void windowClosing();
		void setMultiGen(bool enable, int times);
		XYZ_vector_ptr getTargetXYZVector();
		XYZ_vector_ptr getTargetXYZVector(XYZ_ptr targetWhite,
						  double_vector_ptr luminanceGammaCurve,
						  int dimTurn, int brightTurn, double dimGamma,
						  double brightGamma, int brightWidth);
	      private:

		static XYZ_vector_ptr getDimGammaTarget(double_vector_ptr
							luminanceGammaCurve,
							XYZ_ptr startXYZ,
							XYZ_ptr endXYZ,
							double dimGamma, int dimTurn);

		static XYZ_vector_ptr
		    getBrightGammaTarget(double_vector_ptr luminanceGammaCurve,
					 XYZ_ptr startXYZ, XYZ_ptr endXYZ, double brightGamma,
					 int brightTurn, int brightWidth,
					 bptr < BitDepthProcessor > bitDepth);
		static XYZ_ptr getTargetXYZ(double v1, double v2, double v3, Domain domain);
		static XYZ_ptr getTargetXYZ(double v1, double v2, double v3);
		static bool isDuplicateBlue100(Component_vector_ptr componentVector);
		RGB_vector_ptr produceDGLutMulti(XYZ_vector_ptr
						 targetXYZVector,
						 Component_vector_ptr componentVector);
		RGB_vector_ptr produceDGLut0(XYZ_vector_ptr targetXYZVector,
					     Component_vector_ptr componentVector,
					     bptr < cms::measure::IntensityAnalyzerIF > analyzer);
		bool checkTargetXYZVector(XYZ_vector_ptr targetXYZVector, int start, int end,
					  double deltaabThreshold);
	      public:
		static RGB_vector_ptr smooth(RGB_vector_ptr result1,
					     RGB_vector_ptr result2,
					     bptr < BitDepthProcessor > bitDepth, int brightTurn);
		void setAutoParameter(bool auto);
		int getBrightTurn();
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

