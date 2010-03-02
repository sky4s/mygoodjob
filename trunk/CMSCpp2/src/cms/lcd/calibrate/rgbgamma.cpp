#include "rgbgamma.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace lcd {
	namespace calibrate {
	    //==================================================================
	    // BIntensityGainOp
	    //==================================================================
	    RGBGamma_ptr BIntensityGainOp::
		getRendering(RGBGamma_ptr source) {
	    };
	    //==================================================================
	    //==================================================================
	    // P1P2
	    //==================================================================
	    RGBGamma_ptr P1P2Op::getRendering(RGBGamma_ptr source) {
		//int size = source->size();
		/*RGBGamma_ptr result(new RGB_vector(size));

		   return result; */
	    };
	     P1P2Op::P1P2Op(double p1, double p2):p1(p1), p2(p2) {
	    };
	    //==================================================================
	};
    };
};

