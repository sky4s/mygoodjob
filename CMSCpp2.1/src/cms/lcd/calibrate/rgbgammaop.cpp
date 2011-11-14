#include <includeall.h>
#pragma hdrstop
#include "rgbgammaop.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���

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
	    RGBGamma_ptr BIntensityGainOp::getRendering(RGBGamma_ptr source) {
		double_vector_ptr b(new double_vector(*source->b));
		int effectiveLevel = bitDepth->getEffectiveInputLevel();
		//�qeffectiveLevel����u�����_�l�I
		int realstart = effectiveLevel - (255 - start);

		for (int x = 0; x != realstart; x++) {
		    //0~start �@�߭��Wgain��
		    //BP(i) = BP(i) * Val(Text3.Text) '''' Gain
		    double value = (*b)[x] * gain;
		     (*b)[x] = value;
		};

		double bstart = (*b)[realstart - 1];
		double bstartRemainder = 100 - bstart;
		int remainder = 255 - start;
		//19thBP*gain+(100-19thBP*gain)/(255-236)*(19-i)

		for (int x = realstart; x != effectiveLevel; x++) {
		    (*b)[x] = bstart + bstartRemainder / remainder * (x - realstart + 1);
		};

		for (int x = effectiveLevel; x != bitDepth->getLevel(); x++) {
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
		//�B�zP1�I
		int indexR = -1, indexB = -1;
		int size = dglut->size();
		//�쥻p1�I��dg code
		RGB_ptr rgbp1 = (*dglut)[p1];
		//���Pp1�IDG code��G�ۦP��R�MB��DG code�ҦbDG count
		for (int x = 0; x != size && (indexR == -1 || indexB == -1); x++) {
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

		////�Y�۾F�O�ۦP��, �����N�|��0
		double rdenominator = (*dglut)[indexR + 1]->R - (*dglut)[indexR]->R;
		double bdenominator = (*dglut)[indexB + 1]->B - (*dglut)[indexB]->B;

		//��U�@��gamma���t��
		double rnumerator = r[indexR] + (r[indexR + 1] - r[indexR]) *
		    (rgbp1->G - (*dglut)[indexR]->R);
		double brnumerator = b[indexB] + (b[indexB + 1] - b[indexB]) *
		    (rgbp1->G - (*dglut)[indexB]->B);

		if (0 == rdenominator || 0 == bdenominator) {
		    //int x = 1;
		}
		//���B�������Y���s, �|�����s�����~
		r[p1] = rnumerator / rdenominator;
		b[p1] = brnumerator / bdenominator;

		return source;
	    };
	    RGBGamma_ptr P1P2GammaOp::processP1P2(RGBGamma_ptr source) {
		double_vector & r = (*source->r);
		double_vector & g = (*source->g);
		double_vector & b = (*source->b);
		double base = g[p2] - g[p1];
		for (int x = p1 + 1; x != p2 - 1; x++) {
		    //x�bp1p2�����Ҧ������
		    double ratio = (g[x] - g[p1]) / base;
		    //r&b�̷�g����Ұ��վ�
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
	    //==================================================================

	    //==================================================================
	    // NewGammaOp
	    //==================================================================
	    int NewGammaOp::getNonZeroBlueIndex() {
		for (int x = 1; x < p2; x++) {
		    //dglut->get_allocator()
		    double b = (*dglut)[x]->B;
		    if (b != 0) {
			return x;
		    }
		}
		return -1;
	    };
	    double NewGammaOp::getNonZeroRIntensty() {
		//�Ĥ@�ӫD�sG��
		double g = (*dglut)[1]->G;
		//���P�o�ӫD�sG�ȬۦP��R�Ȫ�intensity
		return componentLUT->getIntensity(Dep::Channel::R, g);
	    };
	    RGBGamma_ptr NewGammaOp::getRendering(RGBGamma_ptr source) {
		using namespace math;
		double_vector & r = (*source->r);
		double_vector & b = (*source->b);
		int size = p2 + 1;

		double rminIntensity = getNonZeroRIntensty();
		int nonZeroBlueIndex = getNonZeroBlueIndex();
		double bminIntensity = b[nonZeroBlueIndex];

		//����b��intensity curve
		double_vector_ptr input(new double_vector(size));
		double_vector_ptr rOutput(new double_vector(size));
		double_vector_ptr bOutput(new double_vector(size));
		for (int x = 0; x <= p2; x++) {
		    (*input)[x] = x;
		    (*rOutput)[x] = r[x];
		    (*bOutput)[x] = b[x];
		}

		//�����W��
		double_vector_ptr normalinput = GammaFinder::normalize(input, (*input)[0],
								       (*input)[p2]);
		double_vector_ptr rNormaloutput = GammaFinder::normalize(rOutput, (*rOutput)[0],
									 (*rOutput)[p2]);
		double_vector_ptr bNormaloutput = GammaFinder::normalize(bOutput, (*bOutput)[0],
									 (*bOutput)[p2]);
		//�p��Xgamma
		double rgamma = GammaFinder::findingGamma(normalinput, rNormaloutput);
		double bgamma = GammaFinder::findingGamma(normalinput, bNormaloutput);

		//���s����output
		double_vector_ptr newRNormalOutput = GammaFinder::gamma(normalinput, rgamma);
		double_vector_ptr newBNormalOutput =
		    GammaFinder::gamma(normalinput, bgamma + gammaShift);

		//�Noutput�ন��ڪ�intensity
		for (int x = 1; x < p2; x++) {
		    double bnormal = (*newBNormalOutput)[x];
		    b[x] = bminIntensity + (b[p2] - bminIntensity) * bnormal;
		    double rnormal = (*newRNormalOutput)[x];
		    r[x] = rminIntensity + (r[p2] - rminIntensity) * rnormal;
		}
		return source;
	    };
	    double NewGammaOp::getBCode(double rRatio, double gRatio, double GCode) {
		return (1 - rRatio - gRatio) * GCode / gRatio;
	    };
	    double NewGammaOp::getRCode(double rRatio, double GCode, double BCode) {
		return rRatio * (GCode + BCode) / (1 - rRatio);
	    };
	  NewGammaOp::NewGammaOp(int p1, int p2, double gammaShift, RGB_vector_ptr dglut, bptr < ComponentLUT > componentLUT):p1(p1), p2(p2),
		gammaShift(gammaShift), dglut(dglut),
		componentLUT(componentLUT) {
	    };

	    //==================================================================
	};
    };
};

