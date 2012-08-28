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

	    class RBInterpolationOp:public DGLutOp {
	      private:
		double under;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 RBInterpolationOp(double under);
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


	    /*
	       純粹將EffectiveLevel以後的值全部設成最大值
	       deprecated
	     */
	    /*class KeepNativeWhiteOp:public DGLutOp {
	       private:
	       bptr < BitDepthProcessor > bitDepth;
	       protected:
	       RGB_vector_ptr getRendering(RGB_vector_ptr source);
	       public:
	       KeepNativeWhiteOp(bptr < BitDepthProcessor > bitDepth);

	       }; */

	    class SetWhiteOp:public DGLutOp {
	      private:
		bptr < BitDepthProcessor > bitDepth;
		RGB_ptr setRGB;
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
	    // deprecated
	    //=================================================================
	    /*class DimDGLutFixOp:public DGLutOp {
	       protected:
	       bptr < BitDepthProcessor > bitDepth;
	       double dimFixThreshold;
	       //const double suitGapx, suitGapy;
	       //double targetGapx, targetGapy;
	       Component_vector_ptr componentVector;
	       bptr < ChromaticityAdjustEstimatorIF > adjustEstimator;

	       static int getDefectType(bool dxdefect, bool dydefect);
	       static int_array getDefectTypeArray(double2D_ptr deltaxyValues, double thresholdx,
	       double thresholdy);
	       static double2D_ptr getDeltaxyValues(Component_vector_ptr componentVector);
	       int getSuitAdjustGrayLevel(int middleGrayLevel, double delta,
	       double_array coordinatorArray);
	       double_array getCoordinatorArray(int grayLevel, bool getCoordinatorX);
	       bool isSuitGap(double_array coordinatorArray);

	       RGB_vector_ptr getRendering(RGB_vector_ptr source);
	       public:
	       DimDGLutFixOp(bptr < BitDepthProcessor > bitDepth, double dimFixThreshold,
	       Component_vector_ptr componentVector,
	       bptr < ChromaticityAdjustEstimatorIF > adjustEstimator);
	       enum DefectType {
	       None, Type0, Type1x, Type1y, Type2, Type12, Type21, Type3, Type4
	       };
	       }; */
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

