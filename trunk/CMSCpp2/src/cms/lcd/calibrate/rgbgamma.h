#ifndef RGBGAMMAH
#define RGBGAMMAH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>

#define RGBGamma_ptr  bptr < RGBGamma >

namespace cms {
    namespace lcd {
	namespace calibrate {
	    class RGBGamma {
	      public:
		double_vector_ptr r, g, b;
		RGBGamma(double_vector_ptr r, double_vector_ptr g,
			 double_vector_ptr b);
	    };

	    class RGBGammaOp {
	      private:
		RGBGamma_ptr source;
		std::vector < bptr < RGBGammaOp > >opvector;
	      protected:
		RGBGamma_ptr createInstance(RGBGamma_ptr source);
		virtual RGBGamma_ptr getRendering(RGBGamma_ptr source)
		= 0;
	      public:
		 RGBGammaOp();
		 RGBGammaOp(RGBGamma_ptr source);
		RGBGamma_ptr createInstance();
		void addOp(bptr < RGBGammaOp > op);

	    };
	};
    };
};
#endif

