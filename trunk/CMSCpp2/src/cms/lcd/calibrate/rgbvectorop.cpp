#include <includeall.h>
#pragma hdrstop
#include "rgbvectorop.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <cms/util/rgbarray.h>
#include <debug.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    //==================================================================
	    using namespace Dep;
	    using namespace cms::util;
	    RGB_vector_ptr LinearOp::getRendering(RGB_vector_ptr source) {

		int size = source->size();
		RGB_vector_ptr result(new RGB_vector());
		for (int x = 0; x < size; x++) {
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
	    RGB_vector_ptr P1P2DGOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result = RGBVector::deepClone(source);
		RGB_ptr rgbp1 = (*result)[p1];

		for (int x = 0; x != p1; x++) {
		    double v = x * rgbp1->G / p1;
		    double d = java::lang::Math::roundTo(v * 4);
		    RGB_ptr rgb = (*result)[x];
		    rgb->setValues(v, v, v);
		    rgb->quantization(maxValue);
		    double d2 = rgb->getValue(Channel::G);
		}

		//if (true == smooth) {
		RGB_ptr rgbp0 = (*result)[p1 - 1];
		//RGB_ptr rgbp1 = (*result)[p1];
		RGB_ptr rgbp2 = (*result)[p1 + 1];
		rgbp1->R = (rgbp0->R + rgbp2->R) / 2;
		rgbp1->G = (rgbp0->G + rgbp2->G) / 2;
		rgbp1->B = (rgbp0->B + rgbp2->B) / 2;
		rgbp1->quantization(maxValue);
		//};

		return result;
	    };
	  P1P2DGOp::P1P2DGOp(double p1, double p2, const MaxValue & maxValue):p1(p1), p2(p2), maxValue(maxValue)
	    {
	    };
	    //==================================================================

	    //==================================================================
	    // RBInterpolation
	    //==================================================================
	    RGB_vector_ptr RBInterpolationOp::
		getRendering(RGB_vector_ptr source) {
		//int size = source->size();

		double rInterval = (*source)[under]->R / under;
		double gInterval = (*source)[under]->G / under;
		double bInterval = (*source)[under]->B / under;
		RGB_vector_ptr result = RGBVector::deepClone(source);


		for (int x = 0; x != under; x++) {
		    //做RB interpolation
		    RGB_ptr rgb = (*result)[x];

		    rgb->R = rInterval * x;
		    rgb->G = gInterval * x;
		    rgb->B = bInterval * x;
		}
		return result;
	    };
	  RBInterpolationOp::RBInterpolationOp(double under):under(under)
	    {
	    };
	    //==================================================================

	    //==================================================================
	    /*BMaxOp::BMaxOp(const Dep::MaxValue & out):out(out) {

	       }; */
	  BMaxOp::BMaxOp(bptr < BitDepthProcessor > bitDepth):bitDepth(bitDepth)
	    {

	    };
	    RGB_vector_ptr BMaxOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result = RGBVector::deepClone(source);
		int size = result->size();
		for (int x = bitDepth->getLevel() - 1;
		     x >= (bitDepth->getEffectiveLevel() - 1); x--) {
		    RGB_ptr rgb = (*result)[x];
		    rgb->B = bitDepth->getMaxDigitalCount();
		    int y = x;
		}

		for (int x = size - 2; x != 1; x--) {
		    RGB_ptr rgb = (*result)[x];
		    RGB_ptr nextrgb = (*result)[x - 1];
		    double diff =
			x > 252 ? 10 / 4. : (x > 232 ? 8 / 4. : 6 / 4.);
		    double thisB = rgb->B;
		    double nextB = nextrgb->B;


		    if (thisB > nextB) {
			nextrgb->B = thisB - diff;
		    } else {
			double preB = (*result)[x + 1]->B;
			rgb->B = (preB + nextB) / 2.;
			break;
		    }
		}

		/*for (int x = bitDepth->getLevel() - 1;
		     x >= (bitDepth->getEffectiveLevel() - 1); x--) {
		    RGB_ptr rgb = (*result)[x];
		    rgb->B = bitDepth->getMaxDigitalCount();
		}*/

		return result;
	    };
	    //==================================================================
	    RGB_vector_ptr GByPassOp::getRendering(RGB_vector_ptr source) {
		RGB_vector_ptr result = RGBVector::deepClone(source);
		//8/6 0~244,245~250,251~255
		//6/6 0~251,252~255
		if (bitDepth->is8in6Out()) {
		    for (int x = 0; x != 245; x++) {
			(*result)[x]->G = x;
		    };
		    for (int x = 245; x != 251; x++) {
			(*result)[x]->G = (*result)[x - 1]->G + 0.5;
		    };
		    for (int x = 251; x != 256; x++) {
			(*result)[x]->G = (*result)[x - 1]->G + 1;
		    };
		} else if (bitDepth->is6in6Out()) {
		    for (int x = 0; x != 252; x++) {
			(*result)[x]->G = x;
		    };
		    for (int x = 252; x != 256; x++) {
			(*result)[x]->G = 252;
		    };
		}
		return result;
	    };

	  GByPassOp::GByPassOp(bptr < BitDepthProcessor > bitDepth):bitDepth(bitDepth)
	    {

	    };
	    //==================================================================
	    RGB_vector_ptr FrcNROp::getRendering(RGB_vector_ptr source) {
		int size = source->size();
		RGB_vector_ptr result = RGBVector::clone(source);

		RGB_ptr rgb255 = (*result)[255];

		foreach(const Channel & ch, *Channel::RGBChannel) {
		    if (rgb255->getValue(ch) >= 248.5) {
			(*source)[255]->setValue(ch, 252);
			(*source)[254]->setValue(ch, 250);
			(*source)[253]->setValue(ch, 248);

			for (int x = 252; x != -1; x--) {
			    RGB_ptr thisRGB = (*source)[x];
			    RGB_ptr nextRGB = (*source)[x + 1];
			    double thisv = thisRGB->getValue(ch);
			    double nextv = nextRGB->getValue(ch);
			    if (thisv >= nextv) {
				thisRGB->setValue(ch, nextv - 2);
			    } else {
				break;
			    }
			}
		    }
		}
		foreach(const Channel & ch, *Channel::RGBChannel) {
		    for (int x = 1; x != 31; x++) {
			RGB_ptr rgb = (*source)[x];
			double v = rgb->getValue(ch);
			if (v == 3 || v == 1) {
			    double setvalue = (v == 3) ? 2.5 : 0.5;
			    rgb->setValue(ch, setvalue);
			    RGB_ptr prergb = (*source)[x - 1];
			    double prev = prergb->getValue(ch);
			    if (prev == rgb->getValue(ch)) {
				prergb->setValue(ch, prev - 2);
			    }
			    if (prergb->getValue(ch) < 0) {
				prergb->setValue(ch, 0);
			    }
			}

		    }
		}
		return result;
	    };
	    //==================================================================

	    //==================================================================
	    RGB_vector_ptr KeepMaxLuminanceOp::
		getRendering(RGB_vector_ptr source) {
		int size = source->size();
		RGB_vector_ptr result = RGBVector::clone(source);
		return result;
	    };
	    //==================================================================
	};
    };
};

