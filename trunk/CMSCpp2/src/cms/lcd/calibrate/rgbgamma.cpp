#include "rgbgamma.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <cms/colorspace/rgb.h>


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
	    // BIntensityGainOp
	    //==================================================================
	    RGBGamma_ptr BIntensityGainOp::
		getRendering(RGBGamma_ptr source) {
		/* TODO : getRendering */
	    };
	     BIntensityGainOp::BIntensityGainOp(double gain):gain(gain) {
	    };
	    //==================================================================

	    //==================================================================
	    // P1P2Op
	    //==================================================================
	    RGBGamma_ptr P1P2GammaOp::processP1(RGBGamma_ptr source) {
		int indexR = -1, indexB = -1;
		int size = dgcode->size();
		RGB_ptr rgbp1 = (*dgcode)[p1];

		for (int x = 0;
		     x != size && (indexR == -1 || indexB == -1); x++) {
		    RGB_ptr rgb = (*dgcode)[x];
		    if (rgb->R > rgbp1->G && indexR == -1) {
			indexR = x;
		    };
		    if (rgb->B > rgbp1->G && indexB == -1) {
			indexB = x;
		    };
		}
		//'P1點的處理
		//RP2(P1) = RP2(index_r) + (RP2(index_r + 1) - RP2(index_r)) * (temp_g - RL2(index_r)) / (RL2(index_r + 1) - RL2(index_r))
		//BP2(P1) = BP2(index_b) + (BP2(index_b + 1) - BP2(index_b)) * (temp_g - BL2(index_b)) / (BL2(index_b + 1) - BL2(index_b))
		double_vector r = (*source->r);
		double_vector b = (*source->b);
		double rdiff = r[indexR + 1] - r[indexR];
		double bdiff = b[indexB + 1] - b[indexB];
		r[p1] = r[indexR] + rdiff * (rgbp1->G -
					     (*dgcode)[indexR]->R) / rdiff;
		b[p1] = b[indexR] + bdiff * (rgbp1->G -
					     (*dgcode)[indexB]->B) / bdiff;
		return source;
	    };
	    RGBGamma_ptr P1P2GammaOp::processP1P2(RGBGamma_ptr source) {
		double_vector r = (*source->r);
		double_vector g = (*source->g);
		double_vector b = (*source->b);
		for (int x = p1 + 1; x != p2 - 1; x++) {
		    //x在p1p2之間所佔的比例
		    double ratio = (g[x] - g[p1]) / (g[p2] - g[p1]);
		    //r&b依照g的比例做調整
		    r[x] = r[p1] + (r[p2] - r[p1]) * ratio;
		    b[x] = b[p1] + (b[p2] - b[p1]) * ratio;
		};
		return source;
	    };
	    RGBGamma_ptr P1P2GammaOp::getRendering(RGBGamma_ptr source) {
		source = processP1(source);
		source = processP1P2(source);
		return source;
	    };
	  P1P2GammaOp::P1P2GammaOp(double p1, double p2, RGB_vector_ptr dgcode):p1(p1), p2(p2),
		dgcode(dgcode)
	    {
	    };
	    P1P2GammaOp::P1P2GammaOp(RGBGamma_ptr source, double p1,
				     double p2,
				     RGB_vector_ptr dgcode):p1(p1),
		p2(p2), dgcode(dgcode) {
		this->source = source;
	    };
	    //==================================================================
	};
    };
};

