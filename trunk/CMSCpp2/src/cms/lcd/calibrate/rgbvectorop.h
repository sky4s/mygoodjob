#ifndef RGBVECTOROPH
#define RGBVECTOROPH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>

namespace cms {
    namespace lcd {
	namespace calibrate {

	    class RGBVectorOp {
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
	    };

	    class LinearOp:public RGBVectorOp {
	      protected:
		RGB_vector_ptr getRendering(RGB_vector_ptr source);

	    };
	    class MinusOp:public RGBVectorOp {
	      private:double minusValue;
	      protected:
		 RGB_vector_ptr getRendering(RGB_vector_ptr source);
	      public:
		 MinusOp(double minusValue);
	    };
	};
    };
}
#endif

