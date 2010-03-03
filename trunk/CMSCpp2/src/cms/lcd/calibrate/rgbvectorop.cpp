#include "rgbvectorop.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <cms/colorspace/rgb.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    //==================================================================
	    using namespace Dep;
	    RGB_vector_ptr LinearOp::getRendering(RGB_vector_ptr source) {

		int size = source->size();
		RGB_vector_ptr result(new RGB_vector());
		for (int x = 0; x < size; x++) {
		    /*RGB_ptr rgb = (*source)[x];
		       rgb->R = rgb->G = rgb->B = x; */
		    RGB_ptr rgb2(new RGBColor());
		     rgb2->R = rgb2->G = rgb2->B = x;
		     result->push_back(rgb2);
		};
		 return result;
	    };
	    //==================================================================

	    //==================================================================
	    RGB_vector_ptr MinusOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result(new RGB_vector());
		 foreach(RGB_ptr rgb, *source) {
		    RGB_ptr rgb2(new RGBColor());
		     rgb2->R = rgb->R - minusValue;
		     rgb2->G = rgb->G - minusValue;
		     rgb2->B = rgb->B - minusValue;
		     result->push_back(rgb2);
		};
		return result;
	    };
	  MinusOp::MinusOp(double minusValue):minusValue(minusValue)
	    {
	    };
	    //==================================================================
	    // P1P2DGOp
	    //==================================================================
	    //bool P1P2DGOp::smooth = true;
	    RGB_vector_ptr P1P2DGOp::getRendering(RGB_vector_ptr source) {
		int size = source->size();
		RGB_vector_ptr result(new RGB_vector(size));
		RGB_ptr rgbp1 = (*source)[p1];

		for (int x = 0; x != p1; x++) {
		    double v = x * rgbp1->G / p1;
		    RGB_ptr rgb = (*source)[x];
		    rgb->setValues(v, v, v);
		}

		for (int x = p1; x != size; x++) {
		    (*result)[x] = (*source)[x];
		}

		if (true == smooth) {
		    RGB_ptr rgbp0 = (*result)[p1 - 1];
		    RGB_ptr rgbp1 = (*result)[p1];
		    RGB_ptr rgbp2 = (*result)[p1 + 1];
		    rgbp1->R = (rgbp0->R + rgbp2->R) / 2;
		    rgbp1->G = (rgbp0->G + rgbp2->G) / 2;
		    rgbp1->B = (rgbp0->B + rgbp2->B) / 2;
		};

		return result;
	    };
	  P1P2DGOp::P1P2DGOp(double p1, double p2):p1(p1),
		p2(p2), smooth(true)
	    {
	    };
	    P1P2DGOp::P1P2DGOp(double p1, double p2, bool smooth):p1(p1),
		p2(p2), smooth(smooth) {
	    };
	    //==================================================================

	    //==================================================================
	    // RBInterpolation
	    //==================================================================
	    RGB_vector_ptr RBInterpolationOp::
		getRendering(RGB_vector_ptr source) {
		int size = source->size();

		double rInterval = (*source)[under]->R / under;
		double gInterval = (*source)[under]->G / under;
		double bInterval = (*source)[under]->B / under;
		RGB_vector_ptr result(new RGB_vector(size));

		for (int x = 0; x != under; x++) {
		    //做RB interpolation
		    RGB_ptr rgb(new RGBColor(*(*source)[x]));
		    rgb->R = rInterval * x;
		    rgb->G = gInterval * x;
		    rgb->B = bInterval * x;
		    (*result)[x] = rgb;
		}
		for (int x = under; x != size; x++) {
		    //僅copy
		    RGB_ptr rgb(new RGBColor(*(*source)[x]));
		    (*result)[x] = rgb;
		}
		return result;
	    };
	  RBInterpolationOp::RBInterpolationOp(double under):under(under)
	    {
	    };
	    //==================================================================

	    RGB_vector_ptr BMaxOp::getRendering(RGB_vector_ptr source) {
	    };
	    BMaxOp::BMaxOp() {
	    };
	    RGB_vector_ptr GByPassOp::getRendering(RGB_vector_ptr source) {
	    };
	    GByPassOp::GByPassOp() {
	    };
	};
    };
};

