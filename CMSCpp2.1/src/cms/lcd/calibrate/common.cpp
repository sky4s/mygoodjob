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
		step(bitDepth->getMeasureStep()), type(Normal) {
		this->rgbMeasureCode =
		    getRGBMeasureCode(getMeasureCode(start, end, firstStep, step), Channel::W,
				      bitDepth->getMeasureMaxValue());
	    };
	     MeasureCondition::MeasureCondition(const int start, const int end, const int firstStep,
						const int step,
						const Dep::MaxValue & maxValue):start(start),
		end(end), firstStep(firstStep), step(step), type(Normal) {
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
		highStart(highStart), highEnd(highEnd), highStep(highStep), type(Extend) {
		this->rgbMeasureCode =
		    getRGBMeasureCode(getMeasureCode
				      (lowStart, lowEnd, lowStep,
				       highStart, highEnd, highStep), Channel::W, maxValue);
	    };

	  MeasureCondition::MeasureCondition(RGB_vector_ptr rgbMeasureCode):type(Normal)
	    {
		this->rgbMeasureCode = rgbMeasureCode;
	    };

	    RGB_vector_ptr MeasureCondition::getRGBMeasureCode() {
		return rgbMeasureCode;
	    };

	    int_vector_ptr MeasureCondition::
		getMeasureCode(const int start, const int end,
			       const int firstStep, const int step) {
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

	};
    };
};

