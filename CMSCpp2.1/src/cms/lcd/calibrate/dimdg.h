#ifndef dimdgH
#define dimdgH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���


namespace cms {
    namespace lcd {
	namespace calibrate {


	    class DimDGLutGenerator {
	      private:

		static XYZ_vector_ptr getTarget(XYZ_ptr startXYZ,
						XYZ_ptr endXYZ,
						double_vector_ptr luminanceGammaCurve);
		static XYZ_vector_ptr getTarget(XYZ_ptr startXYZ,
						XYZ_ptr endXYZ,
						double_vector_ptr
						luminanceGammaCurve, double gamma);
	      protected:
		 Component_vector_ptr componentVector;
		 bptr < cms::measure::IntensityAnalyzerIF > analyzer;
	      public:
		 Component_vector_ptr fetchNewComponent(bptr <
							cms::measure::
							MaxMatrixIntensityAnalyzer
							> analyzer,
							Component_vector_ptr componentVector);
		 DimDGLutGenerator(Component_vector_ptr componentVector,
				   bptr < cms::measure::IntensityAnalyzerIF > analyzer);
		RGB_vector_ptr produce(XYZ_ptr targetWhite,
				       double_vector_ptr luminanceGammaCurve, int under);
		RGB_vector_ptr produce(XYZ_ptr targetWhite,
				       double_vector_ptr
				       luminanceGammaCurve, int under, double gamma);
	    };
	};
    };
};

#endif

