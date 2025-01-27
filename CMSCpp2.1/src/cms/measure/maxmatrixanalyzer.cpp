#include <includeall.h>
#pragma hdrstop
#include "maxmatrixanalyzer.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件



namespace cms {
    namespace measure {

	using namespace java::lang;
	using namespace cms::measure::meter;
	using namespace cms::colorformat;
	using namespace cms::lcd::calibrate;
	using namespace Dep;
	using namespace Indep;
	using namespace ca210api;

#ifdef TNT_LIB
	//======================================================================
	// MaxMatrixIntensityAnayzer
	//======================================================================
	 MaxMatrixIntensityAnalyzer::MaxMatrixIntensityAnalyzer(bptr < MeterMeasurement > mm):mm(mm) {

	};
	 MaxMatrixIntensityAnalyzer::MaxMatrixIntensityAnalyzer() {

	};

	RGB_ptr MaxMatrixIntensityAnalyzer::getIntensity(RGB_ptr rgb) {
	    //component: 0~100%
	    getCIEXYZOnly(rgb);
	    if (null == XYZ) {
		return nil_RGB_ptr;
	    } else {
		RGB_ptr intensity = getIntensity(XYZ);
		Patch::Operator::setIntensity(measurePatch, intensity);
		return intensity;
	    }
	};

	RGB_ptr MaxMatrixIntensityAnalyzer::getIntensity(XYZ_ptr XYZ) {
	    if (null == inverseMatrix) {
		throw IllegalStateException("NULL == inverseMatrix");
	    }
	    double2D_ptr color = DoubleArray::toDouble2D(1, 3, XYZ->X, XYZ->Y, XYZ->Z);
	    rgbValues = DoubleArray::times(inverseMatrix, color);
	    (*rgbValues)[0][0] *= 100;
	    (*rgbValues)[1][0] *= 100;
	    (*rgbValues)[2][0] *= 100;
	    double_array intensityValues(new double[3]);

	    intensityValues[0] = (*rgbValues)[0][0] / (*whiteRatio)[0][0];
	    intensityValues[1] = (*rgbValues)[1][0] / (*whiteRatio)[1][0];
	    intensityValues[2] = (*rgbValues)[2][0] / (*whiteRatio)[2][0];

	    RGB_ptr intensity(new
			      RGBColor(intensityValues[0], intensityValues[1], intensityValues[2]));
	    return intensity;
	};

	XYZ_ptr MaxMatrixIntensityAnalyzer::getCIEXYZ() {
	    return XYZ;
	};

	XYZ_ptr MaxMatrixIntensityAnalyzer::getCIEXYZOnly(RGB_ptr rgb) {
	    if (null != mm) {
		measurePatch = mm->measure(rgb, rgb->toString());
		if (null == measurePatch) {
		    XYZ = nil_XYZ_ptr;
		    return nil_XYZ_ptr;
		} else {
		    XYZ = measurePatch->getXYZ();
		    return XYZ;
		}
	    } else {
		//throw IllegalStateException("mm = null");
		return nil_XYZ_ptr;
	    }
	};

	void MaxMatrixIntensityAnalyzer::setupComponent(const Dep::Channel & ch, RGB_ptr rgb) {
	    XYZ_ptr measureXYZ = getCIEXYZOnly(rgb);
	    if (ch == Channel::W) {
		referenceRGB = rgb->clone();
	    }
	    setupComponent(ch, measureXYZ);

	};

	void MaxMatrixIntensityAnalyzer::setupComponent(const Dep::Channel & ch, XYZ_ptr measureXYZ) {
	    switch (ch.chindex) {
	    case ChannelIndex::R:
		rXYZ = measureXYZ;
		break;
	    case ChannelIndex::G:
		gXYZ = measureXYZ;
		break;
	    case ChannelIndex::B:
		bXYZ = measureXYZ;
		break;
	    case ChannelIndex::W:
		wXYZ = measureXYZ;
		break;
	    };
	};
	void MaxMatrixIntensityAnalyzer::enter() {
	    if (null != mm) {
		mm->setMeasureWindowsVisible(false);
	    }
	    if (rXYZ == null || gXYZ == null || bXYZ == null || wXYZ == null) {
		throw IllegalStateException("Excute setupComponent() with RGBW first.");
	    }
	    double2D_ptr m = DoubleArray::toDouble2D(3, 9, rXYZ->X, gXYZ->X, bXYZ->X,
						     rXYZ->Y, gXYZ->Y, bXYZ->Y,
						     rXYZ->Z, gXYZ->Z, bXYZ->Z);

	    this->inverseMatrix = DoubleArray::inverse(m);

	    double2D_ptr targetWhite = DoubleArray::toDouble2D(1, 3, wXYZ->X, wXYZ->Y, wXYZ->Z);
	    this->whiteRatio = DoubleArray::times(inverseMatrix, targetWhite);

	};
	void MaxMatrixIntensityAnalyzer::beginAnalyze() {
	    if (null != mm) {
		mm->setMeasureWindowsVisible(true);
	    } else {
		//throw IllegalStateException("mm = null");
	    }
	};
	void MaxMatrixIntensityAnalyzer::endAnalyze() {
	    if (null != mm) {
		mm->setMeasureWindowsVisible(false);
	    } else {
		//throw IllegalStateException("mm = null");
	    }
	};
	void MaxMatrixIntensityAnalyzer::setWaitTimes(int waitTimes) {
	    if (null != mm) {
		mm->WaitTimes = waitTimes;
	    }
	};

	int MaxMatrixIntensityAnalyzer::getWaitTimes() {
	    if (null != mm) {
		return mm->WaitTimes;
	    } else {
		return -1;
	    };
	};
	xyY_ptr MaxMatrixIntensityAnalyzer::getReferenceColor() {
	    if (null != wXYZ) {
		xyY_ptr xyY(new CIExyY(wXYZ));
		return xyY;
	    } else {
		xyY_ptr xyY((CIExyY *) null);
		return xyY;
	    }
	};
	xyY_ptr MaxMatrixIntensityAnalyzer::getPrimaryColor(const Dep::Channel & ch) {
	    switch (ch.chindex) {
	    case ChannelIndex::R:
		return xyY_ptr(new CIExyY(rXYZ));
	    case ChannelIndex::G:
		return xyY_ptr(new CIExyY(gXYZ));
	    case ChannelIndex::B:
		return xyY_ptr(new CIExyY(bXYZ));
	    default:
		throw IllegalArgumentException("Unsupported Channel: " + *ch.toString());
	    };
	};
	RGB_ptr MaxMatrixIntensityAnalyzer::getReferenceRGB() {
	    return referenceRGB;
	};
	void MaxMatrixIntensityAnalyzer::setReferenceRGB(RGB_ptr rgb) {
	    this->referenceRGB = rgb;
	};
	bool MaxMatrixIntensityAnalyzer::isInverseMatrixNull() {
	    return null == inverseMatrix;
	}
	bptr < MeterMeasurement > MaxMatrixIntensityAnalyzer::getMeterMeasurement() {
	    return mm;
	};
	double2D_ptr MaxMatrixIntensityAnalyzer::getWhiteRatio() {
	    return whiteRatio;
	};

	bptr < MaxMatrixIntensityAnalyzer >
	    MaxMatrixIntensityAnalyzer::getReadyAnalyzer(bptr < MeterMeasurement > mm,
							 double rMax, double gMax, double bMax) {
	    bptr < MaxMatrixIntensityAnalyzer >
		nativeWhiteAnalyzer(new MaxMatrixIntensityAnalyzer(mm));
	    //已知rgb
	    RGB_ptr rgb(new RGBColor(rMax, gMax, bMax, MaxValue::Double255));
	    RGB_ptr r(new RGBColor(rMax, 0, 0, MaxValue::Double255));
	    RGB_ptr g(new RGBColor(0, gMax, 0, MaxValue::Double255));
	    RGB_ptr b(new RGBColor(0, 0, bMax, MaxValue::Double255));

	    int defaultWaitTimes = nativeWhiteAnalyzer->getWaitTimes();
	    nativeWhiteAnalyzer->setWaitTimes(5000);
	    nativeWhiteAnalyzer->beginAnalyze();
	    nativeWhiteAnalyzer->setupComponent(Channel::R, r);
	    nativeWhiteAnalyzer->setupComponent(Channel::G, g);
	    nativeWhiteAnalyzer->setupComponent(Channel::B, b);
	    nativeWhiteAnalyzer->setupComponent(Channel::W, rgb);
	    nativeWhiteAnalyzer->enter();
	    nativeWhiteAnalyzer->setWaitTimes(defaultWaitTimes);
	    return nativeWhiteAnalyzer;
	};
	bptr < MaxMatrixIntensityAnalyzer >
	    MaxMatrixIntensityAnalyzer::getReadyAnalyzer(XYZ_ptr rXYZ,
							 XYZ_ptr gXYZ, XYZ_ptr bXYZ, XYZ_ptr wXYZ) {

	    return getReadyAnalyzer(bptr < MeterMeasurement > ((MeterMeasurement *) null), rXYZ,
				    gXYZ, bXYZ, wXYZ);
	};
	bptr < MaxMatrixIntensityAnalyzer >
	    MaxMatrixIntensityAnalyzer::getReadyAnalyzer(bptr < MeterMeasurement > mm, XYZ_ptr rXYZ,
							 XYZ_ptr gXYZ, XYZ_ptr bXYZ, XYZ_ptr wXYZ) {
	    bptr < MaxMatrixIntensityAnalyzer > ma(new MaxMatrixIntensityAnalyzer(mm));
	    ma->setupComponent(Channel::R, rXYZ);
	    ma->setupComponent(Channel::G, gXYZ);
	    ma->setupComponent(Channel::B, bXYZ);
	    ma->setupComponent(Channel::W, wXYZ);
	    ma->enter();
	    return ma;
	};
	bptr < MaxMatrixIntensityAnalyzer > MaxMatrixIntensityAnalyzer::getReadyAnalyzer
	    (bptr < cms::measure::IntensityAnalyzerIF > originalAnalyzer, XYZ_ptr wXYZ) {
	    XYZ_ptr rXYZ = originalAnalyzer->getPrimaryColor(Channel::R)->toXYZ();
	    XYZ_ptr gXYZ = originalAnalyzer->getPrimaryColor(Channel::G)->toXYZ();
	    XYZ_ptr bXYZ = originalAnalyzer->getPrimaryColor(Channel::B)->toXYZ();
	    return getReadyAnalyzer(bptr < MeterMeasurement > ((MeterMeasurement *) null), rXYZ,
				    gXYZ, bXYZ, wXYZ);
	};
	//=====================================================================
 
	//=====================================================================
#endif
    };
};

