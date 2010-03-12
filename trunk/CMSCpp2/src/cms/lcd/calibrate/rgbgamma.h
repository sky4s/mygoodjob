#ifndef RGBGAMMAH
#define RGBGAMMAH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include "rgbop.h"

namespace cms {
    namespace lcd {
	namespace calibrate {
	    class RGBGamma {
	      public:
		double_vector_ptr r, g, b;
		RGBGamma(double_vector_ptr r, double_vector_ptr g,
			 double_vector_ptr b);
		static void storeToExcel(const std::string & filename,
					 RGBGamma_ptr rgbgamma);
	    };

	    class RGBGammaOp:public RGBOp < RGBGamma > {
	      public:
		static RGBGamma_ptr getRGBGamma(double_vector_ptr
						gammaCurve);
	    };

	    class BIntensityGainOp:public RGBGammaOp {
	      private:
		double gain;
		int start;
	      protected:
		 RGBGamma_ptr getRendering(RGBGamma_ptr source);
	      public:
		 BIntensityGainOp(double gain);
		 BIntensityGainOp(double gain, int start);
	    };
	    class P1P2GammaOp:public RGBGammaOp {
	      private:
		double p1, p2;
		RGB_vector_ptr dglut;
	      protected:
		 RGBGamma_ptr getRendering(RGBGamma_ptr source);
		RGBGamma_ptr processP1(RGBGamma_ptr source);
		RGBGamma_ptr processP1P2(RGBGamma_ptr source);
	      public:
		 P1P2GammaOp(double p1, double p2, RGB_vector_ptr dglut);
		 P1P2GammaOp(RGBGamma_ptr source, double p1, double p2,
			     RGB_vector_ptr dglut);
	    };
	};
    };
};
#endif

