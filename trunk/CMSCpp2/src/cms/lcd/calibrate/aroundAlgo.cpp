#include <includeall.h>
#pragma hdrstop
#include "aroundAlgo.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

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
		    rgbAdjust(channel_vector_ptr channels,
			      Channel & maxChannel,
			      bptr < RGBColor > centerRGB, double
			      adjustStep, double_array delta) {

		    RGB_vector_ptr rgbVec(new RGB_vector());;
		     foreach(Dep::Channel ch, *channels) {
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
		    whiteAdjust(Channel & maxChannel, bptr < RGBColor >
				centerRGB, double adjustStep) {
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

		};
		bool StepAroundAlgorithm::ChromaticSkipByDelta = true;
	      StepAroundAlgorithm::StepAroundAlgorithm():maxCode(255)
		{
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
			//如果是在白點模式
			if (adjustChannel == maxChannel) {
			    //只要動到最大頻道就是不行!
			    return false;
			}
		    } else if (isGreenMode()) {
			//如果不是在白點模式
			//只要動到G就是不行!
			if (adjustChannel == Channel::G) {
			    return false;
			}
		    }

		    if (ChromaticSkipByDelta == true && delta != null) {
			if (adjustChannel == Channel::R
			    && delta[0] * step > 0) {
	/**
         * 同號就是不行
         * du>0的話, R一定要往負號. 所以相乘一定<0
         * 如果du*step >0的話, 代表:
         * 1.du>0且R往正調整 2.du<0且R往負調整
         * 以上都是多餘的調整
         */
			    return false;
			}
			if (adjustChannel == Channel::B
			    && delta[1] * step < 0) {
	/**
         * 異號就是不行
         * dv>0的話, B一定要往正號. 所以相乘一定>0
         * 如果dv*step <0的話, 代表:
         * 1.dv>0且B往負調整 2.dv<0且B往正調整
         * 以上都是多餘的調整
         */
			    return false;
			}
		    }
		    //調整後的點要 1.>=0 2.<=maxcode
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
		       // RB同時變動
		       rgbList.addAll(this.
		       getChromaticExpandAround(centerRGB,
		       delta,
		       step));
		       } else { */
		    // R/G/B各自變動
		    //========================================================================
		    // 這2層迴圈的變動有
		    // 1. 正負號: +step 跟 -step的差別
		    // 2. RGB頻道: RGB頻道各自做一次step的調整
		    //========================================================================
		    double adjustStep = step;
		    for (int x = 0; x < 2; x++) {
			foreach(const Channel & ch, *(Channel::RGBChannel)) {
			    //變換不同的channel
			    if (checkAdjustable
				(centerRGB, adjustStep, maxChannel, ch,
				 delta)) {
				RGB_ptr rgb = centerRGB->clone();
				rgb->changeMaxValue(MaxValue::Double255);
				rgb->addValue(ch, adjustStep);
				rgbVec->push_back(rgb);
			    }
			}
			//換正負
			adjustStep = -adjustStep;
		    };
		    //========================================================================
		    return rgbVec;
		};
		RGB_vector_ptr ChromaticAroundAlgorithm::
		    getAroundRGB(RGB_ptr centerRGB, double step) {
		    return getAroundRGB(centerRGB, nil_double_array, step);
		};
		//==============================================================
	    };
	};
    };
};

