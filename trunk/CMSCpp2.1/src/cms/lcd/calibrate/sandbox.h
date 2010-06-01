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
		CIEuv, CIEuvPrime
	    };

	    class AdvancedDGLutGenerator:private DimDGLutGenerator {
	      public:
		AdvancedDGLutGenerator(Component_vector_ptr
				       componentVector,
				       bptr <
				       cms::measure::IntensityAnalyzerIF >
				       analyzer);
		RGB_vector_ptr produce(XYZ_ptr targetWhite,
				       double_vector_ptr
				       luminanceGammaCurve, int turn);
		//private:
		static XYZ_vector_ptr getTarget(XYZ_ptr startXYZ,
						XYZ_ptr turnXYZ,
						XYZ_ptr endXYZ,
						double_vector_ptr
						luminanceGammaCurve,
						int dimTurn,
						int brightTurn,
						double dimGamma,
						double brightGamma,
						Domain domain);
		static XYZ_ptr getTargetXYZ(double u, double v, double Y,
					    Domain domain);
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

