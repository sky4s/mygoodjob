#include "rgbgamma.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件


namespace cms {
    namespace lcd {
	namespace calibrate {
	    //==================================================================
	    // RGBGamma
	    //==================================================================
	    RGBGamma::RGBGamma(double_vector_ptr r, double_vector_ptr g,
			       double_vector_ptr b):r(r), g(g), b(b) {
	    };
	    //==================================================================

	    //==================================================================
	    // RGBGammaOp
	    //==================================================================
	    RGBGamma_ptr RGBGammaOp::createInstance(RGBGamma_ptr source) {
		RGBGamma_ptr rendering = getRendering(source);
		 foreach(bptr < RGBGammaOp > op, opvector) {
		    rendering = op->createInstance(rendering);
		};
		 return rendering;
	    };
	    //==================================================================
	};
    };
};

