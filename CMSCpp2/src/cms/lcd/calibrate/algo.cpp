#include "algo.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <cms/colorspace/rgb.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    namespace algo {
		using namespace std;
		using namespace Dep;

		//==============================================================
		// Algorithm
		//==============================================================
		bool Algorithm::isWhiteMode() {
		    return mode == White;
		};
		bool Algorithm::isGreenMode() {
		    return mode == Green;
		};

		void Algorithm::setMode(Mode mode) {
		    this->mode = mode;
		};
		//==============================================================

		//==============================================================
		// StepAroundAlgorithm
		//==============================================================
		 list < RGBColor >
		    StepAroundAlgorithm::
		    rgbAdjust(channel_vector_ptr channels,
			      Channel & maxChannel,
			      bptr < RGBColor > centerRGB, double
			      adjustStep, double_array delta) {

		    list < RGBColor > rgbList;
		    foreach(Dep::Channel ch, *channels) {
			if (checkAdjustable
			    (centerRGB, adjustStep, maxChannel, ch,
			     delta)) {
			    /*RGB rgb = (RGB) centerRGB.clone();
			       rgb.changeMaxValue(RGB.MaxValue.Double255);
			       rgb.addValue(ch, adjustStep);
			       rgbList.add(rgb); */
			}
		    };
		    return rgbList;

		};

		list < RGBColor > StepAroundAlgorithm::
		    whiteAdjust(Channel & maxChannel, bptr < RGBColor >
				centerRGB, double adjustStep) {
		};
		//==============================================================

	    };
	};
    };
};

