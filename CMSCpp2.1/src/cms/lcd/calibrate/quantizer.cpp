#include <includeall.h>
#pragma hdrstop
#include "quantizer.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
//#include "rgbvectorop.h";

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace Dep;
	    using namespace java::lang;
	    RGB_vector_ptr ColorimetricQuantizer::colorimetricQuantization(RGB_vector_ptr dglut,
									   int quadrant) {
		RGB_vector_ptr clone = RGBVector::deepClone(dglut);
		int bit = (*clone)[0]->getMaxValue().bit; //13
		const MaxValue & realMaxValue = MaxValue::getByIntegerBit(bit - 2);

		 foreach(RGB_ptr rgb, *clone) {
		    int r = (int) rgb->R;
		    int g = (int) rgb->G;
		    int b = (int) rgb->B;
		    int rm = r % 4;
		    int gm = g % 4;
		    int bm = b % 4;
		    int_array bestRGB = getBestRGB(rm, gm, bm, quadrant);
		    int rr = bestRGB[0];
		    int gg = bestRGB[1];
		    int bb = bestRGB[2];

		    //���^11bit�B�����h��, �~���i��B�z
		     rgb->changeMaxValue(realMaxValue, true);

		    //rr�T��|�b0~6..���N�q?
		     rgb->R += ((rr == 2 || rr == 4 || rr == 6) ? 1 : 0);	//2,4,6�N��i��
		     rgb->G += ((gg == 2 || gg == 4 || gg == 6) ? 1 : 0);
		     rgb->B += ((bb == 2 || bb == 4 || bb == 6) ? 1 : 0);
		};
		 return clone;
	    };

	    //=================================================================
	    // r: 13bit R���H4���l��(pos in 13bit)
	    // g: 13bit G���H4���l��
	    // b: 13bit B���H4���l��
	    // quadrant: �Ʊ��ͦV���H��
	    // return: 
	    //=================================================================
	    int_array ColorimetricQuantizer::getBestRGB(int r, int g, int b, int quadrant) {
		if (r == 0 && g == 0 && b == 0) {
		    int_array result(new int[3]);
		     return result;
		}

		if ((r != 0 && g == 0 && b == 0) || (r == 0 && g != 0 && b == 0)) {
		    quadrant = 0;
		}

		double mindist = LONG_MAX;
		double_array preminxy = nil_double_array;
		double_array minxy = nil_double_array;
		int_array bestRGB = nil_int_array;
		double_array averagexy(new double[2]);
		//�z�Q�ؼФ�������׮t�Z ��쬰 �U�����@=0.0001
		averagexy[0] = 5, averagexy[1] = 8;

		//r=0~3
		for (int rr = 0; rr < (r != 0 ? 2 : 1); rr++) {	//rr�u��0�M0,1���
		    for (int gg = 0; gg < (g != 0 ? 2 : 1); gg++) {
			for (int bb = 0; bb < (b != 0 ? 2 : 1); bb++) {
			    int rrr = r != 0 ? r * 2 - 1 + rr : 0;	//rrr = 0~6
			    int ggg = g != 0 ? g * 2 - 1 + gg : 0;
			    int bbb = b != 0 ? b * 2 - 1 + bb : 0;
			    //pos 1 2 3�S���i��α˥h�A�S�Ӥ���1,2,3,4,5,6

			    //���o��ת�����
			    double_array xy = getxyPrecise(rrr, ggg, bbb);
			    //���o��װ����᪺�H��
			    int nowQuadrant = getQuadrant(xy[0], xy[1]);
			    //�H�z�Q��׮t�Z�@���[�v
			    double dist = Math::sqrt(Math::sqr(averagexy[0] * xy[0]) +
						     Math::sqr(averagexy[1] * xy[1]));
			    if ((nowQuadrant == quadrant && 0 != nowQuadrant &&
				 -1 != nowQuadrant) || 0 == quadrant) {
				if (preminxy != null) {
				    if (dist < mindist) {
					mindist = dist;
					minxy = preminxy = xy;
					bestRGB[0] = rrr, bestRGB[1] = ggg, bestRGB[2] = bbb;
				    }
				} else {
				    //�Ĥ@���@�w�|�i�o��
				    mindist = dist;
				    minxy = preminxy = xy;
				    bestRGB = int_array(new int[3]);
				    bestRGB[0] = rrr, bestRGB[1] = ggg, bestRGB[2] = bbb;
				}
			    }
			}
		    }
		}
		return bestRGB;
	    };

	    double_array ColorimetricQuantizer::getxy(int r, int g, int b) {
		int_array rdist(new int[2]);
		rdist[0] = 4, rdist[1] = 0;
		int_array gdist(new int[2]);
		gdist[0] = 0, gdist[1] = 6;
		int_array bdist(new int[2]);
		bdist[0] = -4, bdist[1] = -8;

		double x = 0, y = 0;
		if (r == 1 || r == 3 || r == 5) {
		    int rr = (r + 1) / 2;
		    x -= (rdist[0] / 4.) * rr;
		} else if (r == 2 || r == 4 || r == 6) {
		    int rr = 4 - r / 2;
		    x += (rdist[0] / 4.) * rr;
		}

		if (g == 1 || g == 3 || g == 5) {
		    int rr = (g + 1) / 2;
		    y -= (gdist[1] / 4.) * rr;
		} else if (g == 2 || g == 4 || g == 6) {
		    int rr = 4 - g / 2;
		    y += (gdist[1] / 4.) * rr;
		}

		if (b == 1 || b == 3 || b == 5) {
		    int rr = (b + 1) / 2;
		    x -= (bdist[0] / 4.) * rr;
		    y -= (bdist[1] / 4.) * rr;
		} else if (b == 2 || b == 4 || b == 6) {
		    int rr = 4 - b / 2;
		    x += (bdist[0] / 4.) * rr;
		    y += (bdist[1] / 4.) * rr;
		}
		double_array result(new double[2]);
		result[0] = x, result[1] = y;
		return result;
	    };

	    int_array rdist, gdist, bdist, rdist_, gdist_, bdist_;
	    double_array ColorimetricQuantizer::getxyPrecise(int r, int g, int b) {
		if (null == rdist) {
		    rdist = int_array(new int[2]);
		    rdist[0] = 6, rdist[1] = 0;
		    gdist = int_array(new int[2]);
		    gdist[0] = 0, gdist[1] = 10;
		    bdist = int_array(new int[2]);
		    bdist[0] = -6, bdist[1] = -11;
		    rdist_ = int_array(new int[2]);
		    rdist_[0] = -6, rdist_[1] = 0;
		    gdist_ = int_array(new int[2]);
		    gdist_[0] = 0, gdist_[1] = -10;
		    bdist_ = int_array(new int[2]);
		    bdist_[0] = 7, bdist_[1] = 12;
		}
		/*int_array rdist(new int[2]);
		   rdist[0] = 6, rdist[1] = 0;
		   int_array gdist(new int[2]);
		   gdist[0] = 0, gdist[1] = 10;
		   int_array bdist(new int[2]);
		   bdist[0] = -6, bdist[1] = -11;

		   int_array rdist_(new int[2]);
		   rdist_[0] = -6, rdist_[1] = 0;
		   int_array gdist_(new int[2]);
		   gdist_[0] = 0, gdist_[1] = -10;
		   int_array bdist_(new int[2]);
		   bdist_[0] = 7, bdist_[1] = 12; */

		double x = 0, y = 0;
		if (r == 1 || r == 3 || r == 5) {
		    //�˥h
		    int rr = (r + 1) / 2;	//rr=1,2,3
		    x += (rdist_[0] / 4.) * rr;
		} else if (r == 2 || r == 4 || r == 6) {
		    //�i��
		    int rr = 4 - r / 2;	//rr=3,2,1
		    x += (rdist[0] / 4.) * rr;
		}

		if (g == 1 || g == 3 || g == 5) {
		    int rr = (g + 1) / 2;
		    y += (gdist_[1] / 4.) * rr;
		} else if (g == 2 || g == 4 || g == 6) {
		    int rr = 4 - g / 2;
		    y += (gdist[1] / 4.) * rr;
		}

		if (b == 1 || b == 3 || b == 5) {
		    int rr = (b + 1) / 2;
		    x += (bdist_[0] / 4.) * rr;
		    y += (bdist_[1] / 4.) * rr;
		} else if (b == 2 || b == 4 || b == 6) {
		    int rr = 4 - b / 2;
		    x += (bdist[0] / 4.) * rr;
		    y += (bdist[1] / 4.) * rr;
		}
		double_array result(new double[2]);
		result[0] = x, result[1] = y;
		return result;
	    };
	    //=================================================================
	    // �H��������, ���b�����N�O�H��0
	    // x,y(+,+) �H��1
	    // x,y(-,+) �H��2
	    // x,y(-,-) �H��3
	    // x,y(+,-) �H��4
	    //=================================================================
	    int ColorimetricQuantizer::getQuadrant(double x, double y) {
		if (x == 0 && y == 0) {
		    return 0;
		} else if (x > 0 && y > 0) {
		    return 1;
		} else if (x < 0 && y > 0) {
		    return 2;

		} else if (x < 0 && y < 0) {
		    return 3;
		} else if (x > 0 && y < 0) {
		    return 4;
		} else {
		    return -1;
		}
	    };

	};
    };
};

