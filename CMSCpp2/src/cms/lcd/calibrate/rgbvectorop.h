#ifndef RGBVECTOROPH
#define RGBVECTOROPH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include "rgbop.h"
#include "lcdcalibrator.h"

namespace cms {
    namespace lcd {
	namespace calibrate {

	    class DGCodeOp:public RGBOp < RGB_vector > {
	    };

	    class LinearOp:public DGCodeOp {
	      protected:
		RGB_vector_ptr getRendering(RGB_vector_ptr source);

	    };
	    class MinusOp:public DGCodeOp {
	      private:double minusValue;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 MinusOp(double minusValue);
	    };

	    class P1P2DGOp:public DGCodeOp {
	      private:
		double p1, p2;
		bool smooth;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 P1P2DGOp(double p1, double p2);
		 P1P2DGOp(double p1, double p2, bool smooth);

	    };

	    class RBInterpolationOp:public DGCodeOp {
	      private:
		double under;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 RBInterpolationOp(double under);
	    };

	    class BMaxOp:public DGCodeOp {
	      private:
		const BitDepth & out;
	      public:
		 BMaxOp(const BitDepth & out);
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	    };

	    class GByPassOp:public DGCodeOp {
	      private:
		const BitDepth & in, &out;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 GByPassOp(const BitDepth & in, const BitDepth & out);
	    };

	    class AvoidFRCNoiseOp:public DGCodeOp {
	      protected:
		RGB_vector_ptr getRendering(RGB_vector_ptr source);
	    };
	};
    };
}
#endif

