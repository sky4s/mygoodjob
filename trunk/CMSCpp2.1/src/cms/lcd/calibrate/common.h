#ifndef COMMONH
#define COMMONH
namespace cms {
    namespace lcd {
	namespace calibrate {
	    Enumeration(KeepMaxLuminance)
	    None, TargetWhite, NativeWhite	//keep狾程獹&︹放
	    , NativeWhiteAdvanced	//keep狾程獹&︹放, smooth跑て
	    , EnumerationEnd()



	    Enumeration(Correct)
	    P1P2, RBInterpolation, None, DefinedDim, EnumerationEnd()

		/*
		   ノㄓ癘更秖代兵ン, よ獽暗把计肚患
		 */
	    class MeasureCondition {
		friend class cms::colorformat::DGLutProperty;
	      private:
		//int_vector_ptr measureCode;
		 RGB_vector_ptr rgbMeasureCode;
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

		//bool isRGBType();

	      private:
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

	};
    };
};
#endif

