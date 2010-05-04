#include <includeall.h>
#pragma hdrstop
#include "rgbgamma.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms::util;
	    using namespace cms::colorformat;
	    using namespace boost;
	    using namespace std;

	    //==================================================================
	    // BIntensityGainOp
	    //==================================================================
	    RGBGamma_ptr BIntensityGainOp::
		getRendering(RGBGamma_ptr source) {
		double_vector_ptr b(new double_vector(*source->b));
		//int size = b->size();
		int effectiveLevel = bitDepth->getEffectiveLevel();

		int realstart = effectiveLevel - (255 - start);

		for (int x = 0; x != realstart; x++) {
		    //0~start
		    double value = (*b)[x] * gain;
		     (*b)[x] = value;
		};


		double bstart = (*b)[realstart - 1];
		double bstartRemainder = 100 - bstart;
		int remainder = 255 - start;


		for (int x = realstart; x != effectiveLevel; x++) {

		    //start-size
		    //' 19thBP*gain+(100-19thBP*gain)/(255-236)*(19-i)
		    //19以下 0~19 , 對我們這邊是其實是236以上
		    //temp_diff = 255 - Val(Text4.Text)=255=236=19
		    //BP(i) = BP(temp_diff) * Val(Text3.Text) + (100 - BP(temp_diff) * Val(Text3.Text)) / (255 - Val(Text4.Text)) * (temp_diff - i)
		    //BP(i) = BP(19) * gain + (100 - BP(19) * gain) / (255 - 236) * (19 - i)
		    //bstart_1 = b19*gain =
		    /*int n = x - start;
		       (*b)[x] = bstart_1 + (1 - bstart_1)
		       * (static_cast < double >(n) / remainder); */
		    /*double c = bstartRemainder / remainder;
		       double ss = (effectiveLevel - x); */
		    (*b)[x] = bstart +
			bstartRemainder / remainder * (x - realstart + 1);
		};

		for (int x = effectiveLevel; x != bitDepth->getLevel();
		     x++) {
		    (*b)[x] = (*b)[effectiveLevel - 1];
		};
		RGBGamma_ptr result(new RGBGamma(source->r, source->g, b));
		return result;
	    };
	  BIntensityGainOp::BIntensityGainOp(double gain, int start, bptr < BitDepthProcessor > bitDepth):gain(gain), start(start),
		bitDepth(bitDepth)
	    {
	    };
	    //==================================================================
	    //==================================================================
	    // P1P2Op
	    //==================================================================
	    RGBGamma_ptr P1P2GammaOp::processP1(RGBGamma_ptr source) {
		//處理P1點
		int indexR = -1, indexB = -1;
		int size = dglut->size();
		//原本p1點的dg code
		RGB_ptr rgbp1 = (*dglut)[p1];
		for (int x = 0;
		     x != size && (indexR == -1 || indexB == -1); x++) {
		    RGB_ptr rgb = (*dglut)[x];
		    if (rgb->R > rgbp1->G && indexR == -1) {
			indexR = x;
		    };
		    if (rgb->B > rgbp1->G && indexB == -1) {
			indexB = x;
		    };
		}

		double_vector & r = (*source->r);
		double_vector & b = (*source->b);
		r[p1] =
		    r[indexR] + (r[indexR + 1] - r[indexR]) *
		    (rgbp1->G - (*dglut)[indexR]->R) /
		    ((*dglut)[indexR + 1]->R - (*dglut)[indexR]->R);
		b[p1] =
		    b[indexB] + (b[indexB + 1] - b[indexB]) *
		    (rgbp1->G - (*dglut)[indexB]->B) /
		    ((*dglut)[indexB + 1]->B - (*dglut)[indexB]->B);

		return source;
	    };
	    RGBGamma_ptr P1P2GammaOp::processP1P2(RGBGamma_ptr source) {
		double_vector & r = (*source->r);
		double_vector & g = (*source->g);
		double_vector & b = (*source->b);
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
	  P1P2GammaOp::P1P2GammaOp(int p1, int p2, RGB_vector_ptr dglut):p1(p1), p2(p2),
		dglut(dglut)
	    {
	    };
	    /*P1P2GammaOp::
	       P1P2GammaOp(RGBGamma_ptr source, int p1, int p2,
	       RGB_vector_ptr dglut):p1(p1), p2(p2),
	       dglut(dglut) {
	       this->source = source;
	       }; */
	    //==================================================================

	    //==================================================================
	    // NewGammaOp
	    //==================================================================
	    RGBGamma_ptr NewGammaOp::getRendering(RGBGamma_ptr source) {
		using namespace math;
		double_vector & b = (*source->b);
		int size = under + 1;

		double_vector_ptr input(new double_vector(size));
		double_vector_ptr output(new double_vector(size));
		for (int x = 0; x <= under; x++) {
		    (*input)[x] = x;
		    (*output)[x] = b[x];
		}
		double_vector_ptr normalinput =
		    GammaFinder::normalize(input, (*input)[0],
					   (*input)[under]);
		double_vector_ptr normaloutput =
		    GammaFinder::normalize(output, (*output)[0],
					   (*output)[under]);
		double gamma =
		    GammaFinder::findingGamma(normalinput, normaloutput);

		double_vector_ptr newNormalOutput =
		    GammaFinder::gamma(normalinput, gamma + gammaShift);

		for (int x = 1; x < under; x++) {
		    double normal = (*newNormalOutput)[x];
		    b[x] = b[0] + (b[under] - b[0]) * normal;
		}
		return source;
	    };
	  NewGammaOp::NewGammaOp(int under, double gammaShift, RGB_vector_ptr dglut):under(under), gammaShift(gammaShift),
		dglut(dglut)
	    {
	    };

	    //==================================================================
	};
    };
};

