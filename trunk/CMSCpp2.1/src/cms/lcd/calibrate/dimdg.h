#ifndef dimdgH
#define dimdgH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件


namespace cms {
    namespace lcd {
	namespace calibrate {


	    class DimDGLutGenerator {
	      private:

		static XYZ_vector_ptr getTarget(XYZ_ptr startXYZ,
						XYZ_ptr endXYZ,
						double_vector_ptr
						luminanceGammaCurve);
	      protected:
		 Component_vector_ptr componentVector;
		 bptr < cms::measure::IntensityAnalyzerIF > analyzer;

		static void storeXYZVector(XYZ_vector_ptr XYZVector);
	      public:
		 Component_vector_ptr fetchComponent(bptr <
						     cms::measure::
						     MaxMatrixIntensityAnayzer
						     > analyzer,
						     Component_vector_ptr
						     componentVector);
		 DimDGLutGenerator(Component_vector_ptr componentVector,
				   bptr <
				   cms::measure::IntensityAnalyzerIF >
				   analyzer);
		RGB_vector_ptr produce(XYZ_ptr targetWhite,
				       double_vector_ptr
				       luminanceGammaCurve, int under);
	    };
	};
    };
};

#endif

