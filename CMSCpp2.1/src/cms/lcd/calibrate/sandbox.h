#ifndef SANDBOXH
#define SANDBOXH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件


namespace cms {
    namespace lcd {
	namespace calibrate {
	    class DimDGLutGenerator {
	      private:
		Component_vector_ptr componentVector;
		bptr < cms::measure::IntensityAnalyzerIF > analyzer;

		Component_vector_ptr fetchComponent(bptr <
						    cms::measure::
						    MaxMatrixIntensityAnayzer
						    > analyzer,
						    Component_vector_ptr
						    componentVector);
		static XYZ_vector_ptr getTarget(XYZ_ptr startXYZ,
						XYZ_ptr endXYZ,
						double_vector_ptr
						luminanceGammaCurve);

	      public:
		 DimDGLutGenerator(Component_vector_ptr componentVector,
				   bptr <
				   cms::measure::IntensityAnalyzerIF >
				   analyzer);
		RGB_vector_ptr produce(XYZ_ptr targetWhite,
				       double_vector_ptr
				       luminanceGammaCurve, int under);
	    };

	    class DimTargetGenerator {
	      public:
		static XYZ_vector_ptr getLinearTarget(XYZ_ptr startXYZ,
						      XYZ_ptr endXYZ,
						      double_vector_ptr
						      luminanceGammaCurve);
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

