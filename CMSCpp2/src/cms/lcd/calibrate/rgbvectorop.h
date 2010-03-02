#ifndef RGBVECTOROPH
#define RGBVECTOROPH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include "rgbop.h"

namespace cms {
    namespace lcd {
	namespace calibrate {

	    /*class RGBVectorOp {
	      private:
		RGB_vector_ptr source;
		std::vector < bptr < RGBVectorOp > >opvector;
	      protected:
		RGB_vector_ptr createInstance(RGB_vector_ptr source);
		virtual RGB_vector_ptr getRendering(RGB_vector_ptr source)
		= 0;

	      public:
		 RGBVectorOp();
		 RGBVectorOp(RGB_vector_ptr source);
		RGB_vector_ptr createInstance();
		void setSource(RGB_vector_ptr source);
		void addOp(bptr < RGBVectorOp > op);
	    };*/

	    //class DGCodeOp:public RGBVectorOp {
	    //};
	    class DGCodeOp:public RGBOp < RGB_vector > {
	    };

	    //class DGCodeOp_:public RGBOp < RGB_vector > {
	    //};

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

	    /*class P1P2Op:public DGCodeOp {
	      private:
		double p1, p2;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 P1P2Op(double p1, double p2);
	    };*/

	    class RBInterpolationOp:public DGCodeOp {
	      private:
		double under;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 RBInterpolationOp(double under);
	    };

	    class BMaxOp:public DGCodeOp {
	      protected:
		RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		BMaxOp();
	    };

	    class GByPassOp:public DGCodeOp {
	      protected:
		RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		GByPassOp();
	    };
	};
    };
}
#endif

