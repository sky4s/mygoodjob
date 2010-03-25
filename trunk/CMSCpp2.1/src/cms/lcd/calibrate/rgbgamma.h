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
	    enum Type {
		Intensity, Gamma
	    };
	    class RGBGamma:public jObject {
	      public:
		const Type type;
		const double max;
		double_vector_ptr r, g, b, w;
		 RGBGamma(double_vector_ptr r, double_vector_ptr g,
			  double_vector_ptr b);
		 RGBGamma(double_vector_ptr r, double_vector_ptr g,
			  double_vector_ptr b, double_vector_ptr w);
		 RGBGamma(double_vector_ptr r, double_vector_ptr g,
			  double_vector_ptr b, const double max,
			  const Type type);
		 RGBGamma(double_vector_ptr r, double_vector_ptr g,
			  double_vector_ptr b, double_vector_ptr w,
			  const double max, const Type type);
		static void storeToExcel(const std::string & filename,
					 RGBGamma_ptr rgbgamma);
		static void storeToDesiredGamma(const std::
						string & filename,
						RGBGamma_ptr rgbgamma);
		static RGBGamma_ptr loadFromDesiredGamma(const std::
							 string &
							 filename);
		RGBGamma_ptr clone();

	    };

	    class RGBGammaOp:public RGBOp < RGBGamma > {

	    };

	    class BIntensityGainOp:public RGBGammaOp {
	      private:
		double gain;
		int start;
		 bptr < BitDepthProcessor > bitDepth;
	      protected:
		 RGBGamma_ptr getRendering(RGBGamma_ptr source);
	      public:
		 BIntensityGainOp(double gain, int start,
				  bptr < BitDepthProcessor > bitDepth);
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

