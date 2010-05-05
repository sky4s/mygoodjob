#ifndef RGBGAMMAH
#define RGBGAMMAH
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include "rgbop.h"
#include "lcdcalibrator.h"
#include <cms/util/rgbarray.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms::util;
	    //using namespace cms::lcd::calibrate;
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
		int p1, p2;
		RGB_vector_ptr dglut;
	      protected:
		 RGBGamma_ptr getRendering(RGBGamma_ptr source);
		RGBGamma_ptr processP1(RGBGamma_ptr source);
		RGBGamma_ptr processP1P2(RGBGamma_ptr source);
	      public:
		 P1P2GammaOp(int p1, int p2, RGB_vector_ptr dglut);
		/*P1P2GammaOp(RGBGamma_ptr source, int p1, int p2,
		   RGB_vector_ptr dglut); */
	    };

	    class NewGammaOp:public RGBGammaOp {
	      private:
		int p1, p2;
		double gammaShift;
		RGB_vector_ptr dglut;
		int getNonZeroBlueIndex();
		double getNonZeroRIntensty();
		 bptr < ComponentLUT > componentLUT;
	      protected:
		 RGBGamma_ptr getRendering(RGBGamma_ptr source);
		double getBCode(double rRatio, double gRatio,
				double GCode);
		double getRCode(double rRatio, double GCode, double BCode);
                //double getRRatio(
	      public:
		 NewGammaOp(int p1, int p2, double gammaShift,
			    RGB_vector_ptr dglut,
			    bptr < ComponentLUT > componentLUT);
	    };
	};
    };
};
#endif

