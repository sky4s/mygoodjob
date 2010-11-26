#ifndef COMMONH
#define COMMONH
namespace cms {
    namespace lcd {
	namespace calibrate {
	    Enumeration(KeepMaxLuminance)
	    None, TargetWhite, NativeWhite	//keep���O�̤j�G��&���
	    , NativeWhiteAdvanced	//keep���O�̤j�G��&���, smooth�ܤ�
	    , EnumerationEnd()



	    Enumeration(Correct)
	    P1P2, RBInterpolation, None, DefinedDim, EnumerationEnd()

	    class PanelRegulator;
	    /*
	       �ΨӰO���q��������, ��K���Ѽƶǻ�
	     */
	    class MeasureCondition {
		friend class cms::colorformat::DGLutProperty;
		friend class GammaTestPanelRegulator;
	      private:
		//int_vector_ptr measureCode;
		 bool remapping;
		RGB_vector_ptr rgbMeasureCode;
		RGB_vector_ptr remappingRGBMeasureCode;
		int start;
		int end;
		int step;
		int firstStep;

		int lowStart;
		int lowEnd;
		int lowStep;
		int highStart;
		int highEnd;
		int highStep;
		enum MeasureType {
		    Normal, Extend
		};
		const MeasureType type;
	      public:

		 MeasureCondition(bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth);
		 MeasureCondition(const int start, const int end,
				  const int firstStep, const int step,
				  const Dep::MaxValue & maxValue);
		 MeasureCondition(const int lowStart, const int lowEnd,
				  const int lowStep, const int highStart,
				  const int highEnd, const int highStep,
				  const Dep::MaxValue & maxValue);
		 MeasureCondition(RGB_vector_ptr rgbMeasureCode);
		RGB_vector_ptr getRGBMeasureCode();
	      private:
		void setRemappingRGBMeasureCode(RGB_vector_ptr rgbMeasureCode);
		void setRemappingMode(bool remap);
		static int_vector_ptr getMeasureCode(const int start,
						     const int end,
						     const int firstStep, const int step);
		static int_vector_ptr getMeasureCode(const int lowStart,
						     const int lowEnd,
						     const int lowStep,
						     const int highStart,
						     const int highEnd, const int highStep);
		static bool isNoRemainder(int start, int end, int step);
		RGB_vector_ptr getRGBMeasureCode(int_vector_ptr
						 measureCode, const Dep::Channel & channel);
		RGB_vector_ptr getRGBMeasureCode(int_vector_ptr
						 measureCode,
						 const Dep::
						 Channel & channel, const Dep::MaxValue & maxValue);
	    };

	    /*
	       PanelRegulator�i�Ψӧ��ܭ��O�S��
	       �D�n���ηN�b��A�⭱�O�����I�קאּ�ؼХ��I�A�~��ϲ��ͪ�DG Lut�����I��n���ؼХ��I

	       ���T�ϥάy�{��
	       1. constructor��ƥ��n����T
	       2. setEnable(true)���ܭ��O�S��
	       3. remapping�N�o�쪺DG Lut�����^���T��DG Code
	       4. ���ݭnsetEnable(false)��_���O�S��
	     */
	    class PanelRegulator {
	      protected:
		bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth;
		bptr < i2c::TCONControl > tconctrl;
		double rgain, ggain, bgain;
		RGB_vector_ptr mappingRGBVector;
	      public:
		 PanelRegulator(bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth,
				bptr < i2c::TCONControl > tconctrl, double rgain, double ggain,
				double bgain);
		 PanelRegulator(bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth,
				bptr < i2c::TCONControl > tconctrl, int maxR, int maxG, int maxB);
		void setEnable(bool enable);
		RGB_vector_ptr remapping(RGB_vector_ptr dglut);
		RGB_vector_ptr getMappingRGBVector();
	    };

	    class GammaTestPanelRegulator:public PanelRegulator {
	      private:
		bptr < MeasureCondition > measureCondition;
	      public:
		/*GammaTestPanelRegulator(bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth,
		   bptr < i2c::TCONControl > tconctrl, double rgain,
		   double ggain, double bgain); */
		GammaTestPanelRegulator(bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth,
					bptr < i2c::TCONControl > tconctrl, int maxR, int maxG,
					int maxB, bptr < MeasureCondition > measureCondition);
		void setEnable(bool enable);
		void setRemappingMode(bool remap);
	    };
	};
    };
};
#endif

