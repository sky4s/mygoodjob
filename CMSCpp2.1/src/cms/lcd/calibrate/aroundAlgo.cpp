#include <includeall.h>
#pragma hdrstop
#include "aroundAlgo.h"

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���

namespace cms {
    namespace lcd {
	namespace calibrate {
	    namespace algo {
		using namespace std;
		using namespace Dep;
		//==============================================================
		// StepAroundAlgorithm
		//==============================================================
		 RGB_vector_ptr
		    StepAroundAlgorithm::
		    rgbAdjust(Channel_vector_ptr channels,
			      const Channel & maxChannel,
			      bptr < RGBColor > centerRGB, double
			      adjustStep, double_array delta) {

		    RGB_vector_ptr rgbVec(new RGB_vector());;
		     foreach(const Dep::Channel & ch, *channels) {
			if (checkAdjustable
			    (centerRGB, adjustStep, maxChannel, ch,
			     delta)) {
			    RGB_ptr rgb = centerRGB->clone();
			     rgb->changeMaxValue(MaxValue::Double255);
			     rgb->addValue(ch, adjustStep);
			     rgbVec->push_back(rgb);
			}
		    };
		     return rgbVec;

		};

		RGB_vector_ptr StepAroundAlgorithm::
		    whiteAdjust(const Channel & maxChannel,
				bptr < RGBColor > centerRGB,
				double adjustStep) {
		    RGB_vector_ptr rgbVec(new RGB_vector());;
		    if (whiteCheckAdjustable
			(centerRGB, adjustStep, maxChannel)) {
			RGB_ptr rgb = centerRGB->clone();
			 rgb->changeMaxValue(MaxValue::Double255);
			 rgb->addValue(adjustStep);
			 rgbVec->push_back(rgb);
		    }
		    return rgbVec;
		};

		bool StepAroundAlgorithm::checkAdjustable(RGB_ptr rgb,
							  double step,
							  const Dep::
							  Channel &
							  maxChannel,
							  const Dep::
							  Channel &
							  adjustChannel,
							  double_array
							  delta) {
		    /* TODO : checkAdjustable */
                    return false;
		};
		bool StepAroundAlgorithm::ChromaticSkipByDelta = true;
	      StepAroundAlgorithm::StepAroundAlgorithm():maxCode(255)
		{
		};
		StepAroundAlgorithm::
		    StepAroundAlgorithm(double maxcode):maxCode(maxcode) {
		};
		//==============================================================

		//==============================================================
		// ChromaticAroundAlgorithm
		//==============================================================
		bool ChromaticAroundAlgorithm::
		    checkAdjustable(RGB_ptr rgb, double step,
				    const Dep::Channel & maxChannel,
				    const Dep::Channel & adjustChannel,
				    double_array delta) {
		    if (isWhiteMode()) {
			//�p�G�O�b���I�Ҧ�
			if (adjustChannel == maxChannel) {
			    //�u�n�ʨ�̤j�W�D�N�O����!
			    return false;
			}
		    } else if (isGreenMode()) {
			//�p�G���O�b���I�Ҧ�
			//�u�n�ʨ�G�N�O����!
			if (adjustChannel == Channel::G) {
			    return false;
			}
		    }

		    if (ChromaticSkipByDelta == true && delta != null) {
			if (adjustChannel == Channel::R
			    && delta[0] * step > 0) {
	/**
         * �P���N�O����
         * du>0����, R�@�w�n���t��. �ҥH�ۭ��@�w<0
         * �p�Gdu*step >0����, �N��:
         * 1.du>0�BR�����վ� 2.du<0�BR���t�վ�
         * �H�W���O�h�l���վ�
         */
			    return false;
			}
			if (adjustChannel == Channel::B
			    && delta[1] * step < 0) {
	/**
         * �����N�O����
         * dv>0����, B�@�w�n������. �ҥH�ۭ��@�w>0
         * �p�Gdv*step <0����, �N��:
         * 1.dv>0�BB���t�վ� 2.dv<0�BB�����վ�
         * �H�W���O�h�l���վ�
         */
			    return false;
			}
		    }
		    //�վ�᪺�I�n 1.>=0 2.<=maxcode
		    double afterValue =
			rgb->getValue(adjustChannel) + step;
		    return afterValue <= maxCode && afterValue >= 0;

		};
		RGB_vector_ptr ChromaticAroundAlgorithm::
		    getAroundRGB(RGB_ptr centerRGB, double_array delta,
				 double step) {
		    RGB_vector_ptr rgbVec(new RGB_vector());
		    rgbVec->push_back(centerRGB);
		    //rgbList.add(centerRGB);
		    const Channel & maxChannel =
			centerRGB->getMaxChannel();

		    /*if (this.chromaticExpandMode) {
		       // RB�P���ܰ�
		       rgbList.addAll(this.
		       getChromaticExpandAround(centerRGB,
		       delta,
		       step));
		       } else { */
		    // R/G/B�U���ܰ�
		    //========================================================================
		    // �o2�h�j�骺�ܰʦ�
		    // 1. ���t��: +step �� -step���t�O
		    // 2. RGB�W�D: RGB�W�D�U�۰��@��step���վ�
		    //========================================================================
		    double adjustStep = step;
		    for (int x = 0; x < 2; x++) {
			foreach(const Channel & ch, *(Channel::RGBChannel)) {
			    //�ܴ����P��channel
			    if (checkAdjustable
				(centerRGB, adjustStep, maxChannel, ch,
				 delta)) {
				RGB_ptr rgb = centerRGB->clone();
				rgb->changeMaxValue(MaxValue::Double255);
				rgb->addValue(ch, adjustStep);
				rgbVec->push_back(rgb);
			    }
			}
			//�����t
			adjustStep = -adjustStep;
		    };
		    //========================================================================
		    return rgbVec;
		};
		RGB_vector_ptr ChromaticAroundAlgorithm::
		    getAroundRGB(RGB_ptr centerRGB, double step) {
		    return getAroundRGB(centerRGB, nil_double_array, step);
		};
		ChromaticAroundAlgorithm::ChromaticAroundAlgorithm() {
		    setMode(Normal);
		};
	      ChromaticAroundAlgorithm::ChromaticAroundAlgorithm(double maxcode):StepAroundAlgorithm(maxcode)
		{
		    setMode(Normal);
		};
		//==============================================================
	    };
	};
    };
};

