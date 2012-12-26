#ifndef RGBVECTOROPH
#define RGBVECTOROPH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "rgbop.h"
#include "lcdcalibrator.h"
#include "feedback.h"

namespace cms {
    namespace lcd {
	namespace calibrate {

	    class DGLutOp:public RGBOp < RGB_vector > {
	      public:
		//RGB_vector_ptr createInstance();
	    };

	    class LinearOp:public DGLutOp {
	      protected:
		RGB_vector_ptr getRendering(RGB_vector_ptr source);

	    };
	    class MinusOp:public DGLutOp {
	      private:double minusValue;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 MinusOp(double minusValue);
	    };

	    class P1P2DGOp:public DGLutOp {
	      private:
		double p1, p2;
		//const Dep::MaxValue & maxValue;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 P1P2DGOp(double p1, double p2);
	    };

	    class RGBInterpolationOp:public DGLutOp {
	      private:
		int under;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 RGBInterpolationOp(int under);
	    };

	    class RBInterpolationOp:public DGLutOp {
	      private:
		int under;
		bool autoUnder;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
		int calculateAutoUnder();
	      public:
		 RBInterpolationOp(int under);
		 RBInterpolationOp(int under, bool autoUnder);
	    };

	    class BMaxOp:public DGLutOp {
	      private:
		//const Dep::MaxValue & out;
		bptr < BitDepthProcessor > bitDepth;

	      public:
		BMaxOp(bptr < BitDepthProcessor > bitDepth);
	      protected:
		RGB_vector_ptr getRendering(RGB_vector_ptr source);
	    };

	    class BMax2Op:public DGLutOp {
	      private:
		bptr < BitDepthProcessor > bitDepth;
		int begin;
		double gamma;
	      public:
		 BMax2Op(bptr < BitDepthProcessor > bitDepth, int begin, double gamma);
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	    };

	    class GByPassOp:public DGLutOp {
	      private:
		//const Dep::MaxValue & in, &out;
		bptr < BitDepthProcessor > bitDepth;
	      protected:
		RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		GByPassOp(bptr < BitDepthProcessor > bitDepth);
	    };

	    class FrcNROp:public DGLutOp {
	      private:
		bptr < BitDepthProcessor > bitDepth;
	      protected:
		RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		FrcNROp(bptr < BitDepthProcessor > bitDepth);
	    };




	    class SetWhiteOp:public DGLutOp {
	      private:
		bptr < BitDepthProcessor > bitDepth;
		RGB_ptr setRGB;
		bool input10Bit;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 SetWhiteOp(bptr < BitDepthProcessor > bitDepth, RGB_ptr setRGB);
	    };




	    class KeepNativeWhiteSmoothOp:public DGLutOp {
	      private:
		bptr < BitDepthProcessor > bitDepth;
		int over;
		bool compensationR;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 KeepNativeWhiteSmoothOp(bptr < BitDepthProcessor > bitDepth, int over,
					 bool compensationR);
	    };



	    //=================================================================
	    class DimDGLutFixOp2 /*:public DimDGLutFixOp */  {
	      protected:
		bptr < BitDepthProcessor > bitDepth;
		double dimFixThreshold;
		Component_vector_ptr componentVector;
		 bptr < ChromaticityAdjustEstimatorIF > adjustEstimator;
		RGB_vector_ptr getRendering(RGB_vector_ptr source);
		bool_array getDefectArray(double2D_ptr deltaxyValues, double threshold, int index);

		static double2D_ptr getDeltaxyValues(Component_vector_ptr componentVector);
	      public:
		 DimDGLutFixOp2(bptr < BitDepthProcessor > bitDepth, double dimFixThreshold,
				Component_vector_ptr componentVector,
				bptr < ChromaticityAdjustEstimatorIF > adjustEstimator);
	    };
	    //=================================================================

	    class DeHook2Op:public DGLutOp {
	      private:
		bptr < BitDepthProcessor > bitDepth;
		int maxBDGGrayLevel;
		RGB_ptr maxBDG;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 DeHook2Op(bptr < BitDepthProcessor > bitDepth, RGB_ptr _maxBDG,
			   int _maxBDGGrayLevel);

	    };
	};
    };
}
#endif

