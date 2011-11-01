#include <includeall.h>
#pragma hdrstop
#include "common.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件


namespace cms {
    namespace lcd {
	namespace calibrate {

	    using namespace cms::measure;
	    using namespace Dep;
	    using namespace java::lang;
	    using namespace cms::colorformat;
	    using namespace cms::util;
	    using namespace cms::lcd::calibrate;



	    //==================================================================
	     MeasureCondition::MeasureCondition(bptr < cms::lcd::calibrate::BitDepthProcessor >
						bitDepth):start(bitDepth->getMeasureStart()),
		end(bitDepth->getMeasureEnd()), firstStep(bitDepth->getMeasureFirstStep()),
		step(bitDepth->getMeasureStep()), type(Normal), remapping(false) {
		this->rgbMeasureCode =
		    getRGBMeasureCode(getMeasureCode(start, end, firstStep, step), Channel::W,
				      bitDepth->getMeasureMaxValue());
	    };
	     MeasureCondition::MeasureCondition(const int start, const int end, const int firstStep,
						const int step,
						const Dep::MaxValue & maxValue):start(start),
		end(end), firstStep(firstStep), step(step), type(Normal), remapping(false) {
		this->rgbMeasureCode =
		    getRGBMeasureCode(getMeasureCode(start, end, firstStep, step), Channel::W,
				      maxValue);
	    };
	     MeasureCondition::MeasureCondition(const int lowStart,
						const int lowEnd,
						const int lowStep,
						const int highStart, const int highEnd, const int
						highStep,
						const Dep::
						MaxValue &
						maxValue):lowStart
		(lowStart), lowEnd(lowEnd), lowStep(lowStep),
		highStart(highStart), highEnd(highEnd), highStep(highStep), type(Extend),
		remapping(false) {
		this->rgbMeasureCode =
		    getRGBMeasureCode(getMeasureCode
				      (lowStart, lowEnd, lowStep, highStart, highEnd, highStep),
				      Channel::W, maxValue);
	    };

	  MeasureCondition::MeasureCondition(RGB_vector_ptr rgbMeasureCode):type(Normal), remapping(false)
	    {
		this->rgbMeasureCode = rgbMeasureCode;
	    };

	    MeasureCondition::MeasureCondition(RGB_vector_ptr rgbMeasureCode, const int start,
					       const int end):type(Normal) {
		RGB_vector_ptr result(new RGB_vector());
		for (int x = start; x <= end; x++) {
		    result->push_back((*rgbMeasureCode)[x]);
		}
		this->rgbMeasureCode = result;
	    };

	    RGB_vector_ptr MeasureCondition::getRGBMeasureCode() {
		if (remapping) {
		    return remappingRGBMeasureCode;
		} else {
		    return rgbMeasureCode;
		}
	    }

	    void MeasureCondition::setRemappingRGBMeasureCode(RGB_vector_ptr rgbMeasureCode) {
		this->remappingRGBMeasureCode = rgbMeasureCode;
	    };
	    void MeasureCondition::setRemappingMode(bool remap) {
		this->remapping = remap;
	    };
	    int_vector_ptr MeasureCondition::
		getMeasureCode(const int start, const int end, const int firstStep,
			       const int step) {
		int_vector_ptr measureCode(new int_vector());
		int measureStep = firstStep;
		bool first = true;

		for (int x = start; x >= end; x -= measureStep) {
		    if (x != start && true == first) {
			first = false;
			measureStep = step;
		    }
		    measureCode->push_back(x);
		}
		if ((*measureCode)[measureCode->size() - 1] != end) {
		    measureCode->push_back(end);
		}

		return measureCode;
	    };
	    int_vector_ptr MeasureCondition::
		getMeasureCode(const int lowStart, const int lowEnd,
			       const int lowStep, const int highStart,
			       const int highEnd, const int highStep) {
		int_vector_ptr measureCode(new int_vector());

		int start = isNoRemainder(highStart, highEnd,
					  highStep) ? highStart : highStart + 1;

		for (int x = start; x >= highEnd; x -= highStep) {
		    int code = x > 255 ? 255 : x;
		    measureCode->push_back(code);
		}
		start = (lowStart == highEnd) ? (lowStart - lowStep) : highEnd;
		for (int x = start; x >= lowEnd; x -= lowStep) {
		    measureCode->push_back(x);
		}

		return measureCode;
	    };

	    bool MeasureCondition::isNoRemainder(int start, int end, int step) {
		double dividend = ((double) start - end) / step;
		bool noremainder = dividend == static_cast < int >(dividend);
		return noremainder;
	    }
	    RGB_vector_ptr MeasureCondition::
		getRGBMeasureCode(int_vector_ptr measureCode, const Dep::Channel & channel) {
		return getRGBMeasureCode(measureCode, channel, MaxValue::Int8Bit);
	    }
	    RGB_vector_ptr MeasureCondition::
		getRGBMeasureCode(int_vector_ptr measureCode,
				  const Dep::Channel & channel, const MaxValue & maxValue) {
		RGB_vector_ptr rgbMeasureCode(new RGB_vector());
		foreach(int c, *measureCode) {
		    RGB_ptr rgb(new RGBColor(maxValue));
		    rgb->setValue(channel, c);
		    rgbMeasureCode->push_back(rgb);
		}
		return rgbMeasureCode;
	    };
	    //==================================================================

	    //==================================================================
	    // PanelRegulator
	    //==================================================================
	  PanelRegulator::PanelRegulator(bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth, bptr < i2c::TCONControl > tconctrl, double rgain, double ggain, double bgain):
	    bitDepth(bitDepth), tconctrl(tconctrl), rgain(rgain), ggain(ggain), bgain(bgain) {

	    };
	    PanelRegulator::PanelRegulator(bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth,
					   bptr < i2c::TCONControl > tconctrl, int maxR, int maxG,
					   int maxB):bitDepth(bitDepth), tconctrl(tconctrl) {
		int max = bitDepth->getOutputMaxDigitalCount();
		rgain = ((double) maxR) / max;
		ggain = ((double) maxG) / max;
		bgain = ((double) maxB) / max;
	    };
	    void PanelRegulator::setEnable(bool enable) {
		if (true == enable) {
		    mappingRGBVector = RGBVector::getLinearRGBVector(bitDepth, rgain, ggain, bgain);
		    tconctrl->setDG(false);
		    tconctrl->setDGLut(mappingRGBVector);
		    tconctrl->setDG(true);
		} else {
		    tconctrl->setDG(false);
		}
	    };
	    RGB_vector_ptr PanelRegulator::remapping(RGB_vector_ptr dglut) {
		RGB_vector_ptr result = RGBVector::deepClone(dglut);
		foreach(RGB_ptr rgb, *result) {
		    rgb->R *= rgain;
		    //rgb->R = (int) rgb->R;
		    rgb->G *= ggain;
		    //rgb->G = (int) rgb->G;
		    rgb->B *= bgain;
		    //rgb->B = (int) rgb->B;
		}
		return result;
	    };
	    RGB_vector_ptr PanelRegulator::getMappingRGBVector() {
		return mappingRGBVector;
	    };
	    //==================================================================

	    /*GammaTestPanelRegulator::GammaTestPanelRegulator(bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth, bptr < i2c::TCONControl > tconctrl, double rgain, double ggain, double bgain):PanelRegulator(bitDepth, tconctrl, rgain, ggain,
	       bgain)
	       {
	       }; */
	  GammaTestPanelRegulator::GammaTestPanelRegulator(bptr < cms::lcd::calibrate::BitDepthProcessor > bitDepth, bptr < i2c::TCONControl > tconctrl, int maxR, int maxG, int maxB, bptr < MeasureCondition > measureCondition):PanelRegulator(bitDepth,
			   tconctrl, maxR, maxG,
			   maxB), measureCondition(measureCondition) {
	    };
	    void GammaTestPanelRegulator::setEnable(bool enable) {
		setRemappingMode(enable);
	    };

	    void GammaTestPanelRegulator::setRemappingMode(bool remap) {
		if (null == measureCondition->remappingRGBMeasureCode) {
		    RGB_vector_ptr remapping =
			RGBVector::getLinearRGBVector(measureCondition->rgbMeasureCode, rgain,
						      ggain, bgain);
		    measureCondition->remappingRGBMeasureCode = remapping;
		}

		measureCondition->setRemappingMode(remap);
	    };
	};
    };
};

