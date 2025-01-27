#ifndef COMMONH
#define COMMONH
namespace cms {
    namespace lcd {
	namespace calibrate {
	    Enumeration(KeepMaxLuminance)
	    None,		//無處理
	    TargetLuminance,	//keep目標亮度(不一定有用
	    TargetWhite,	//keep 目標白點: 可搭配de-hook
	    NativeWhite,	//keep面板最大亮度&色溫
		//NativeWhiteAdvanced,      //keep面板最大亮度&色溫, smooth變化 (廢棄不用)
	    Smooth2NativeWhite,	//keep面板最大亮度&色溫, smooth變化
	    EnumerationEnd()



	    Enumeration(DimCorrect)
	    P1P2, RGBInterpolation, None, DefinedDim, EnumerationEnd()

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
                 bool Enable10BitInMeasurement;
                 bool NullDgCodeTable;
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
                int AgingMeasureStep;
		enum MeasureType {
		    Normal, Extend
		};
		const MeasureType type;
		 bptr < cms::lcd::BitDepthProcessor > bitDepth;
	      public:

		 MeasureCondition(bptr < cms::lcd::BitDepthProcessor > bitDepth);
		 MeasureCondition(const int start, const int end,
				  const int firstStep, const int step,
				  const Dep::MaxValue & maxValue);
		 MeasureCondition(const int lowStart, const int lowEnd,
				  const int lowStep, const int highStart,
				  const int highEnd, const int highStep,
				  const Dep::MaxValue & maxValue);
		 MeasureCondition(RGB_vector_ptr rgbMeasureCode);
		 MeasureCondition(RGB_vector_ptr rgbMeasureCode,
				  bptr < cms::lcd::BitDepthProcessor > bitDepth);
		 MeasureCondition(RGB_vector_ptr rgbMeasureCode,
				  bptr < cms::lcd::BitDepthProcessor > bitDepth,
                                  const bool Enable10BitInMeasurement,
                                  const int AgingMeasureStep);
		 MeasureCondition(RGB_vector_ptr rgbMeasureCode, const int start, const int end);
                 MeasureCondition(const bool Enable10BitInMeasurement, const int AgingMeasureStep,
                                  const bool NullDgCodeTable);
		RGB_vector_ptr getRGBMeasureCode();
                bool get10BitInMeasurement();
                bool getNullDgCodeTable();
                int getAgingMeasureStep();
	      private:
		//void setRemappingRGBMeasureCode(RGB_vector_ptr rgbMeasureCode);
		//virtual void setRemappingMode(bool remap);
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
		__property RGB_vector_ptr RemappingRGBMeasureCode =
		    { write = remappingRGBMeasureCode
		};
		__property bool RemappingMode = { write = remapping };
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
		bptr < cms::lcd::BitDepthProcessor > bitDepth;
		bptr < i2c::TCONControl > tconctrl;
		double rgain, ggain, bgain;
		//RGB_vector_ptr mappingRGBVector;
	      public:
		/*PanelRegulator(double rgain, double ggain, double bgain,
		   bptr < cms::lcd::BitDepthProcessor > bitDepth,
		   bptr < i2c::TCONControl > tconctrl); */

		 PanelRegulator(bptr < cms::lcd::BitDepthProcessor > bitDepth,
				bptr < i2c::TCONControl > tconctrl, double maxR, double maxG,
				double maxB);
		virtual void setEnable(bool enable) = 0;
		virtual RGB_vector_ptr remapping(RGB_vector_ptr dglut) = 0;
		//RGB_vector_ptr getMappingRGBVector();
	    };

	    class DGLutPanelRegulator:public PanelRegulator {
	      protected:
		//bptr < cms::lcd::BitDepthProcessor > bitDepth;
		//bptr < i2c::TCONControl > tconctrl;
		//double rgain, ggain, bgain;
		RGB_vector_ptr mappingRGBVector;
	      public:
		/*PanelRegulator(double rgain, double ggain, double bgain,
		   bptr < cms::lcd::BitDepthProcessor > bitDepth,
		   bptr < i2c::TCONControl > tconctrl); */

		DGLutPanelRegulator(bptr < cms::lcd::BitDepthProcessor > bitDepth,
				    bptr < i2c::TCONControl > tconctrl, double maxR, double maxG,
				    double maxB);
		virtual void setEnable(bool enable);
		virtual RGB_vector_ptr remapping(RGB_vector_ptr dglut);
		//RGB_vector_ptr getMappingRGBVector();
	    };

	    class GammaTestPanelRegulator:public PanelRegulator {
	      private:
		bptr < MeasureCondition > measureCondition;
		void setRemappingMode(bool remap);
	      public:
		 GammaTestPanelRegulator(bptr < cms::lcd::BitDepthProcessor > bitDepth,
					 bptr < i2c::TCONControl > tconctrl,
					 double maxR, double maxG, double maxB,
					 bptr < MeasureCondition > measureCondition);
		virtual void setEnable(bool enable);
		virtual RGB_vector_ptr remapping(RGB_vector_ptr dglut);
	    };
	};
    };
};
#endif

