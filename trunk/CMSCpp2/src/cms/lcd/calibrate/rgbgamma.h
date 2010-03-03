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
	      private:
		double gain;
	      protected:
		 RGBGamma_ptr getRendering(RGBGamma_ptr source);
	      public:
		 BIntensityGainOp(double gain);
	    };
	    class P1P2GammaOp:public RGBGammaOp {
	      private:
		double p1, p2;
		RGB_vector_ptr dgcode;
	      protected:
		 RGBGamma_ptr getRendering(RGBGamma_ptr source);
		RGBGamma_ptr processP1(RGBGamma_ptr source);
		RGBGamma_ptr processP1P2(RGBGamma_ptr source);
	      public:
		 P1P2GammaOp(double p1, double p2, RGB_vector_ptr dgcode);
		 P1P2GammaOp(RGBGamma_ptr source, double p1, double p2,
			     RGB_vector_ptr dgcode);
	    };
	};
    };
};
#endif

