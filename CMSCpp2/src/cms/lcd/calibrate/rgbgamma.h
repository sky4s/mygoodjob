#ifndef RGBGAMMAH
#define RGBGAMMAH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include "rgbop.h"

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

	    class RGBGammaOp:public RGBOp < RGBGamma > {
	    };

	    class BIntensityGainOp:public RGBGammaOp {
	      protected:
		RGBGamma_ptr getRendering(RGBGamma_ptr source);
	    };
	    class P1P2Op:public RGBGammaOp {

	      private:
		double p1, p2;
	      protected:
		 RGBGamma_ptr getRendering(RGBGamma_ptr source);
	      public:
		 P1P2Op(double p1, double p2);
	    };
	};
    };
};
#endif

