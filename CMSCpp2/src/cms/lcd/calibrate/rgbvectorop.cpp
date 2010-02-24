#include "rgbvectorop.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <cms/colorspace/rgb.h>

namespace cms {
    namespace lcd {
	namespace calibrate {

	    RGB_vector_ptr RGBVectorOp::
		createInstance(RGB_vector_ptr source) {
		RGB_vector_ptr rendering = getRendering(source);
		 foreach(bptr < RGBVectorOp > op, opvector) {
		    rendering = op->createInstance(rendering);
		};
		 return rendering;
	    };
	     RGBVectorOp::RGBVectorOp() {
	    };
	  RGBVectorOp::RGBVectorOp(RGB_vector_ptr source):source(source)
	    {
	    };
	    RGB_vector_ptr RGBVectorOp::createInstance() {
		return createInstance(source);
	    };
	    void RGBVectorOp::setSource(RGB_vector_ptr source) {
		this->source = source;
	    };
	    void RGBVectorOp::addOp(bptr < RGBVectorOp > op) {
		opvector.push_back(op);
	    };
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
	};
    };
};

