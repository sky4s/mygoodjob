#include <includeall.h>
#pragma hdrstop
#include "feedback.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <gui/cct/TMainForm.h>

namespace cms {
    namespace lcd {
	namespace calibrate {
	    using namespace cms::measure;
	    using namespace Dep;
	    using namespace Indep;
	    using namespace java::lang;
	    using namespace cms::colorformat;
	    using namespace cms::util;
	    using namespace cms::lcd::calibrate;

	    xyY_ptr IntensityEstimator::getxyY(RGB_ptr intensity) {
		XYZ_ptr rXYZ2 = rXYZ->clone();
		XYZ_ptr gXYZ2 = gXYZ->clone();
		XYZ_ptr bXYZ2 = bXYZ->clone();
		 rXYZ2->times(intensity->R / 100.);
		 gXYZ2->times(intensity->G / 100.);
		 bXYZ2->times(intensity->B / 100.);
		XYZ_ptr rgXYZ = CIEXYZ::plus(rXYZ2, gXYZ2);
		XYZ_ptr XYZ = CIEXYZ::plus(rgXYZ, bXYZ2);
		xyY_ptr xyY(new CIExyY(XYZ));
		 return xyY;
	    };
	     IntensityEstimator::IntensityEstimator(Component_vector_ptr componentVector,
						    bptr < cms::measure::IntensityAnalyzerIF >
						    analyzer,
						    bptr < BitDepthProcessor >
						    bitDepth):componentVector(componentVector),
		analyzer(analyzer), bitDepth(bitDepth),
		dgLutGenerator(bptr < DGLutGenerator > (new DGLutGenerator(componentVector))) {
		xyY_ptr xyYR = analyzer->getPrimaryColor(Channel::R);
		xyY_ptr xyYG = analyzer->getPrimaryColor(Channel::G);
		xyY_ptr xyYB = analyzer->getPrimaryColor(Channel::B);
		 rXYZ = xyYR->toXYZ();
		 gXYZ = xyYG->toXYZ();
		 bXYZ = xyYB->toXYZ();
		//dgLutGenerator = DGLutGenerator(componentVector);
	    };
	    double_array IntensityEstimator::getdxdy(const Dep::Channel & ch, int grayLevel) {
		int size = componentVector->size();
		int index = size - grayLevel - 1;
		Component_ptr c = (*componentVector)[index];
		//RGB_ptr orgrgb = c->rgb;
		const Dep::MaxValue & lutMaxValue = bitDepth->getLutMaxValue();
		RGB_ptr rgb = c->rgb->clone();
		RGB_ptr intensity = dgLutGenerator->getIntensity(rgb);
		 rgb->changeMaxValue(lutMaxValue);
		 rgb->addValue(ch, 1);
		 rgb->changeMaxValue(MaxValue::Double255);
		RGB_ptr intensity2 = dgLutGenerator->getIntensity(rgb);
		xyY_ptr xyY = getxyY(intensity);
		xyY_ptr xyY2 = getxyY(intensity2);
		double_array dxdy = DoubleArray::minus(xyY->getxyValues(), xyY2->getxyValues(), 2);
		 return dxdy;
	    };
	    double_array IntensityEstimator::getRdxGdy(int componentIndex) {
		return nil_double_array;
	    }
	    //=================================================================
	    // MeasureEstimator
	    //=================================================================
	    void MeasureEstimator::init() {
		if (true == MainForm->linkCA210) {
		    storeComponentVector = Component_vector_ptr(new Component_vector());
		} else {
		    DGLutFile dglut(DEBUG_DIR + _s("MeasureEstimator.xls"), ReadOnly);
		    storeComponentVector = dglut.getComponentVector();
		    storeIndex = 0;
		}
	    };
	  MeasureEstimator::MeasureEstimator(Component_vector_ptr componentVector, bptr < cms::measure::MeterMeasurement > mm, bptr < BitDepthProcessor > bitDepth):componentVector(componentVector), mm(mm),
		bitDepth(bitDepth), size(componentVector->size()),
		useComponentVector(true), measureRdxGdy(true) {
		init();
	    };
	  MeasureEstimator::MeasureEstimator(Component_vector_ptr componentVector, bptr < cms::measure::IntensityAnalyzerIF > analyzer, bptr < BitDepthProcessor > bitDepth):componentVector(componentVector),
		mm(analyzer->getMeterMeasurement()), bitDepth(bitDepth),
		size(componentVector->size()), useComponentVector(true), measureRdxGdy(true) {
		init();
	    };
	  MeasureEstimator::MeasureEstimator(RGB_vector_ptr dglut, bptr < cms::measure::IntensityAnalyzerIF > analyzer, bptr < BitDepthProcessor > bitDepth):dglut(dglut), mm(analyzer->getMeterMeasurement()),
		bitDepth(bitDepth), size(dglut->size()),
		useComponentVector(false), measureRdxGdy(true) {
		init();
	    };
	    double_array MeasureEstimator::getdxdy(const Dep::Channel & ch, int componentIndex) {
		if (true == MainForm->linkCA210) {
		    RGB_ptr dg0 = getMeasureBaseRGB(componentIndex);
		    dg0->changeMaxValue(bitDepth->getFRCAbilityBit());
		    XYZ_ptr XYZ0 = measure(dg0);
		    RGB_ptr dg1 = dg0->clone();
		    dg1->addValue(ch, 1);
		    XYZ_ptr XYZ1 = measure(dg1);
		    double_array delta = getdxdy(XYZ0, XYZ1);
		    /*Component_ptr c0(new Component(dg0, nil_RGB_ptr, XYZ0));
		       Component_ptr c1(new Component(dg1, nil_RGB_ptr, XYZ1));
		       storeComponentVector->push_back(c0);
		       storeComponentVector->push_back(c1); */
		    return delta;
		} else {
		    Component_ptr c0 = (*storeComponentVector)[storeIndex++];
		    Component_ptr c1 = (*storeComponentVector)[storeIndex++];
		    XYZ_ptr XYZ0 = c0->XYZ;
		    XYZ_ptr XYZ1 = c1->XYZ;
		    double_array delta = getdxdy(XYZ0, XYZ1);
		    return delta;
		}
	    };
	    double_array MeasureEstimator::getRdxGdy(int componentIndex) {
		if (true == MainForm->linkCA210) {
		    RGB_ptr dg0 = getMeasureBaseRGB(componentIndex);
		    dg0->changeMaxValue(bitDepth->getFRCAbilityBit());
		    RGB_ptr dg1 = dg0->clone();
		    dg1->addValue(Channel::R, 1);
		    RGB_ptr dg2 = dg0->clone();
		    dg2->addValue(Channel::G, 1);

		    XYZ_ptr XYZ2 = measure(dg2);
		    XYZ_ptr XYZ1 = measure(dg1);
		    XYZ_ptr XYZ0 = measure(dg0);


		    baseXYZ = XYZ0;
		    double_array delta1 = getdxdy(XYZ0, XYZ1);
		    double_array delta2 = getdxdy(XYZ0, XYZ2);
		    double_array delta(new double[2]);
		    delta[0] = delta1[0];
		    delta[1] = delta2[1];
		    /*Component_ptr c0(new Component(dg0, nil_RGB_ptr, XYZ0));
		       Component_ptr c1(new Component(dg1, nil_RGB_ptr, XYZ1));
		       Component_ptr c2(new Component(dg2, nil_RGB_ptr, XYZ2));
		       storeComponentVector->push_back(c0);
		       storeComponentVector->push_back(c1);
		       storeComponentVector->push_back(c2); */
		    return delta;
		} else {
		    Component_ptr c0 = (*storeComponentVector)[storeIndex++];
		    Component_ptr c1 = (*storeComponentVector)[storeIndex++];
		    Component_ptr c2 = (*storeComponentVector)[storeIndex++];
		    XYZ_ptr XYZ0 = c0->XYZ;
		    XYZ_ptr XYZ1 = c1->XYZ;
		    XYZ_ptr XYZ2 = c2->XYZ;
		    double_array delta1 = getdxdy(XYZ0, XYZ1);
		    double_array delta2 = getdxdy(XYZ0, XYZ2);
		    double_array delta(new double[2]);
		    delta[0] = delta1[0];
		    delta[1] = delta2[1];
		    return delta;
		}
	    };
	    RGB_ptr MeasureEstimator::getMeasureBaseRGB(int index) {
		if (useComponentVector) {
		    Component_ptr c = (*componentVector)[index];
		    RGB_ptr dg = c->rgb->clone();
		    return dg;
		} else {
		    RGB_ptr dg = (*dglut)[index]->clone();
		    return dg;
		}
	    };
	    double_array MeasureEstimator::getdxdy(XYZ_ptr XYZ0, XYZ_ptr XYZ1) {
		double_array xy0Values = XYZ0->getxyValues();
		double_array xy1Values = XYZ1->getxyValues();
		double_array delta = DoubleArray::minus(xy1Values, xy0Values, 2);
		return delta;
	    };
	    MeasureEstimator::~MeasureEstimator() {
		STORE_COMPONENT("MeasureEstimator.xls", storeComponentVector);
		mm->close();
	    };

	    void MeasureEstimator::measure(int startIndex, int endIndex) {
		resetMeasure();
		//const Dep::MaxValue & frcBit = bitDepth->getFRCAbilityBit();
		XYZ_vector_ptr baseXYZVec(new XYZ_vector());

		XYZ_ptr XYZ;
		//先量base
		for (int x = endIndex; x >= startIndex; x--) {

		    if (null != constrained) {
			//如果有下constraind
			bool search = binary_search(constrained->begin(), constrained->end(), x);
			if (search) {
			    //如果是constraind裡面有的, 才量
			    RGB_ptr rgb = getMeasureBaseRGB(x);
			    XYZ = measure(rgb);
			} else {
			    //constraind沒有就給0
			    XYZ = XYZ_ptr(new CIEXYZ());
			}
		    } else {
			RGB_ptr rgb = getMeasureBaseRGB(x);
			XYZ = measure(rgb);
		    }
		    baseXYZVec->push_back(XYZ);
		}

		//量完再來做處裡
		int size = baseXYZVec->size();
		//為了讓base和r/g可以對齊, 所以多塞一個0
		dxofBase->push_back(0);
		dyofBase->push_back(0);
		for (int x = size - 2; x >= 0; x--) {
		    //因為是反過來量, 所以從後面開始算(最小的在後面)
		    XYZ_ptr XYZ0 = (*baseXYZVec)[x + 1];
		    XYZ_ptr XYZ1 = (*baseXYZVec)[x];
		    if (0 == XYZ0->Y || 0 == XYZ1->Y) {
			//若亮度是0, 代表遇到constained, 就要略過直接給delta為1
			dxofBase->push_back(1);
			dyofBase->push_back(1);
		    } else {
			double_array dxy = getdxdy(XYZ0, XYZ1);
			dxofBase->push_back(dxy[0]);
			dyofBase->push_back(dxy[1]);
		    }
		};

		if (measureRdxGdy) {
		    for (int x = endIndex; x >= startIndex; x--) {
			double_array RdxGdy = getRdxGdy(x);
			dxofRVector->push_back(RdxGdy[0]);
			dyofGVector->push_back(RdxGdy[1]);
		    }
		    dxofRVector = DoubleArray::getReverse(dxofRVector);
		    dyofGVector = DoubleArray::getReverse(dyofGVector);
		}

	    }

	    XYZ_ptr MeasureEstimator::measure(RGB_ptr rgb) {
		Patch_ptr p = mm->measure(rgb, nil_string_ptr);
		XYZ_ptr XYZ = p->getXYZ();
		Component_ptr c(new Component(rgb, nil_RGB_ptr, XYZ));
		storeComponentVector->push_back(c);
		return XYZ;
	    };
	    void MeasureEstimator::resetMeasure() {
		dxofRVector = double_vector_ptr(new double_vector());
		dyofGVector = double_vector_ptr(new double_vector());
		dxofBase = double_vector_ptr(new double_vector());
		dyofBase = double_vector_ptr(new double_vector());
	    };
	    int MeasureEstimator::getMeasureCount() {
		return storeComponentVector->size();
	    };
	    double_array MeasureEstimator::getMaxMeasureError() {
		int size = storeComponentVector->size();
		double_array maxError(new double[2]);
		maxError[0] = 0;
		maxError[1] = 0;

		for (int x = 0; x < size - 1; x++) {
		    Component_ptr c = (*storeComponentVector)[x];
		    RGB_ptr rgb = c->rgb;
		    Component_vector_ptr tmp(new Component_vector());

		    for (int y = x + 1; y < size; y++) {
			Component_ptr c2 = (*storeComponentVector)[y];
			RGB_ptr rgb2 = c2->rgb;
			if (rgb->equals(rgb2)) {
			    tmp->push_back(c2);
			}
		    }
		    int sameRGBCount = tmp->size();
		    if (0 != sameRGBCount) {
			double_array meanxy(new double[2]);
			foreach(Component_ptr c2, *tmp) {
			    XYZ_ptr XYZ = c2->XYZ;
			    xyY_ptr xyY(new CIExyY(XYZ));
			    meanxy[0] += xyY->x;
			    meanxy[1] += xyY->y;
			}
			meanxy[0] /= sameRGBCount;
			meanxy[1] /= sameRGBCount;

			foreach(Component_ptr c2, *tmp) {
			    XYZ_ptr XYZ = c2->XYZ;
			    xyY_ptr xyY(new CIExyY(XYZ));
			    double dx = Math::abs(xyY->x - meanxy[0]);
			    double dy = Math::abs(xyY->y - meanxy[1]);
			    maxError[0] = (dx > maxError[0]) ? dx : maxError[0];
			    maxError[1] = (dy > maxError[1]) ? dy : maxError[1];
			}
		    }
		};
		return maxError;
	    };
	};
    };
};

