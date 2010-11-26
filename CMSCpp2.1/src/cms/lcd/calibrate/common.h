#ifndef COMMONH
#define COMMONH
namespace cms {
    namespace lcd {
	namespace calibrate {
	    Enumeration(KeepMaxLuminance)
	    None, TargetWhite, NativeWhite	//keep面板最大亮度&色溫
	    , NativeWhiteAdvanced	//keep面板最大亮度&色溫, smooth變化
	    , EnumerationEnd()



	    Enumeration(Correct)
	    P1P2, RBInterpolation, None, DefinedDim, EnumerationEnd()

	    class PanelRegulator;
	    /*
	       用來記載量測的條件, 方便做參數傳遞
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
	       PanelRegulator可用來改變面板特性
	       主要的用意在於，把面板的白點修改為目標白點，才能使產生的DG Lut的白點剛好為目標白點

	       正確使用流程為
	       1. constructor具備必要的資訊
	       2. setEnable(true)改變面板特性
	       3. remapping將得到的DG Lut對應回正確的DG Code
	       4. 視需要setEnable(false)恢復面板特性
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

