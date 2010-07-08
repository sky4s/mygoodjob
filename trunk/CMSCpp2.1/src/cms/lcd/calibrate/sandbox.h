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

	    class AdvancedDGLutGenerator:private DimDGLutGenerator {
	      private:
		//採用用大值的B Intensity或者100?
		bool useMaxTargetBIntensity;
		bool isAvoidHook(XYZ_ptr targetXYZ, double offsetK);
		XYZ_ptr getXYZ(XYZ_ptr XYZ, double offsetK);
		bool isDuplicateBlue100(XYZ_ptr targetXYZ);
		double bTargetIntensity;
	      public:
		 AdvancedDGLutGenerator(Component_vector_ptr
					componentVector,
					bptr <
					cms::measure::IntensityAnalyzerIF >
					analyzer);
		RGB_vector_ptr produce(XYZ_ptr targetWhite,
				       double_vector_ptr
				       luminanceGammaCurve, int dimTurn,
				       int brightTurn, double dimGamma,
				       double brightGamma);
		RGB_vector_ptr produce(XYZ_ptr targetWhite,
				       double_vector_ptr
				       luminanceGammaCurve, int dimTurn,
				       int brightTurn, double dimGamma,
				       double brightGamma, bool avoidHook);

		XYZ_vector_ptr getAvoidHookTarget(XYZ_ptr startXYZ,
						  XYZ_ptr targetXYZ,
						  double_vector_ptr
						  luminanceGammaCurve,
						  int dimTurn,
						  int brightTurn,
						  double dimGamma);
		static XYZ_vector_ptr getTarget(XYZ_ptr startXYZ,
						XYZ_ptr targetXYZ,
						XYZ_ptr endXYZ,
						double_vector_ptr
						luminanceGammaCurve,
						int dimTurn,
						int brightTurn,
						double dimGamma,
						double brightGamma);

		void setUseMaxTargetBIntensity(bool
					       useMaxTargetBIntensity);
		void setBTargetIntensity(double bTargetIntensity);
	      private:

		static XYZ_vector_ptr getDimGammaTarget(double_vector_ptr
							luminanceGammaCurve,
							XYZ_ptr startXYZ,
							XYZ_ptr endXYZ,
							double dimGamma,
							int dimTurn);
		static XYZ_vector_ptr
		    getBrightGammaTarget(double_vector_ptr
					 luminanceGammaCurve,
					 XYZ_ptr startXYZ, XYZ_ptr endXYZ,
					 double brightGamma,
					 int brightTurn);
		static XYZ_ptr getTargetXYZ(double v1, double v2,
					    double v3, Domain domain);
		static XYZ_ptr getTargetXYZ(double v1, double v2,
					    double v3);
		static bool isDuplicateBlue100(Component_vector_ptr
					       componentVector);


	    };



	    class DimTargetGenerator {
	      public:

		static XYZ_vector_ptr getLinearTarget(XYZ_ptr startXYZ,
						      XYZ_ptr endXYZ,
						      double_vector_ptr
						      luminanceGammaCurve);
		static XYZ_vector_ptr getLinearTarget(XYZ_ptr startXYZ,
						      XYZ_ptr endXYZ,
						      double_vector_ptr
						      luminanceGammaCurve,
						      Domain domain);
		static XYZ_vector_ptr getGammaTarget(XYZ_ptr startXYZ,
						     XYZ_ptr endXYZ,
						     double_vector_ptr
						     luminanceGammaCurve,
						     double gamma);
	    };
	};
    };
};

#endif

