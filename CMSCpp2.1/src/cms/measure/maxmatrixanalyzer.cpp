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
            if( null == XYZ ) {
            return nil_RGB_ptr;
            }
            else {
	    return getIntensity(XYZ);
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

	    intensityValues[0] = (*rgbValues)[0][0] / (*targetRatio)[0][0];
	    intensityValues[1] = (*rgbValues)[1][0] / (*targetRatio)[1][0];
	    intensityValues[2] = (*rgbValues)[2][0] / (*targetRatio)[2][0];

	    RGB_ptr intensity(new
			      RGBColor(intensityValues[0], intensityValues[1], intensityValues[2]));
	    return intensity;
	};

	XYZ_ptr MaxMatrixIntensityAnalyzer::getCIEXYZ() {
	    return XYZ;
	};

	XYZ_ptr MaxMatrixIntensityAnalyzer::getCIEXYZOnly(RGB_ptr rgb) {
	    if (null != mm) {
		Patch_ptr patch = mm->measure(rgb, rgb->toString());
                if( null ==patch) {
                XYZ  =  nil_XYZ_ptr;
                return nil_XYZ_ptr;
                }
                else {
		XYZ = patch->getXYZ();
		return XYZ;
                }
	    } else {
		throw IllegalStateException("mm = null");
	    }
	};

	void MaxMatrixIntensityAnalyzer::setupComponent(const Dep::Channel & ch, RGB_ptr rgb) {
	    XYZ_ptr measureXYZ = getCIEXYZOnly(rgb);
	    if (ch == Channel::W) {
		referenceRGB = rgb->clone();
	    }
	    setupComponent(ch, measureXYZ);

	    /*if (null != mm) {
	       Patch_ptr p = mm->measure(rgb, rgb->toString());
	       if (ch == Channel::W) {
	       referenceRGB = rgb->clone();
	       }
	       XYZ_ptr measureXYZ = p->getXYZ();
	       setupComponent(ch, measureXYZ);
	       } else {
	       throw IllegalStateException("mm = null");
	       } */
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
	    this->targetRatio = DoubleArray::times(inverseMatrix, targetWhite);

	};
	void MaxMatrixIntensityAnalyzer::beginAnalyze() {
	    if (null != mm) {
		mm->setMeasureWindowsVisible(true);
	    } else {
		throw IllegalStateException("mm = null");
	    }
	};
	void MaxMatrixIntensityAnalyzer::endAnalyze() {
	    if (null != mm) {
		mm->setMeasureWindowsVisible(false);
	    } else {
		throw IllegalStateException("mm = null");
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
	double2D_ptr MaxMatrixIntensityAnalyzer::getTargetRatio() {
	    return targetRatio;
	};

	//=====================================================================
	//=====================================================================
	// IntensityAnayzer
	//=====================================================================
      IntensityAnayzer::IntensityAnayzer(bptr < MaxMatrixIntensityAnalyzer > matrix, bptr < CA210IntensityAnalyzer > ca210):matrix(matrix), ca210(ca210),
	    no(0)
	{

	    fieldNames =
		StringVector::fromCString(13, "no", "CA_R", "CA_G", "CA_B",
					  "MA_R", "MA_G", "MA_B", "MA_Ro",
					  "MA_Go", "MA_Bo", "MA2_R", "MA2_G", "MA2_B");
	    Util::deleteExist(INTENSITY_FILE);
	    excel = bptr < SimpleExcelAccess > (new
						SimpleExcelAccess
						(INTENSITY_FILE,
						 cms::colorformat::Create, fieldNames));
	};

	RGB_ptr IntensityAnayzer::getIntensity(RGB_ptr rgb) {
	    RGB_ptr ca210Intensity = ca210->getIntensity(rgb);
	    XYZ_ptr XYZ = ca210->getCIEXYZ();
	    RGB_ptr matrixIntensity = matrix->getIntensity(XYZ);
	    double2D_ptr originalIntensity = matrix->rgbValues;
	    string_vector_ptr values;

	    values =
		StringVector::fromDouble(13,
					 static_cast < double >(no++),
					 ca210Intensity->R,
					 ca210Intensity->G,
					 ca210Intensity->B,
				 	 matrixIntensity->R,
					 matrixIntensity->G,
					 matrixIntensity->B,
					 (*originalIntensity)[0][0],
					 (*originalIntensity)[1][0],
					 (*originalIntensity)[2][0], 0., 0., 0.);
	    excel->insert(values);
	    return ca210Intensity;
	};
	XYZ_ptr IntensityAnayzer::getCIEXYZ() {
	    return ca210->getCIEXYZ();
	};

	XYZ_ptr IntensityAnayzer::getCIEXYZOnly(RGB_ptr rgb) {
	    throw UnsupportedOperationException();
	};

	void IntensityAnayzer::setupComponent(const Dep::Channel & ch, RGB_ptr rgb) {
	    ca210->setupComponent(ch, rgb);
	    XYZ_ptr XYZ = ca210->getCIEXYZ();
	    matrix->setupComponent(ch, XYZ);
	};
	void IntensityAnayzer::enter() {
	    ca210->enter();
	    matrix->enter();

	    double2D_ptr targetRatio = matrix->targetRatio;
	    string_vector_ptr values;

	    values =
		StringVector::fromDouble(13, 99., 0., 0., 0., 0., 0.,
					 0., (*targetRatio)[0][0],
					 (*targetRatio)[1][0], (*targetRatio)[2][0], 0., 0., 0.);
	    excel->insert(values);

	};
	void IntensityAnayzer::beginAnalyze() {
	    ca210->beginAnalyze();
	};
	void IntensityAnayzer::endAnalyze() {
	    ca210->endAnalyze();
	};
	void IntensityAnayzer::setWaitTimes(int waitTimes) {
	    ca210->setWaitTimes(waitTimes);
	};
	int IntensityAnayzer::getWaitTimes() {
	    return ca210->getWaitTimes();
	};
	xyY_ptr IntensityAnayzer::getReferenceColor() {
	    return ca210->getReferenceColor();
	};
	xyY_ptr IntensityAnayzer::getPrimaryColor(const Dep::Channel & ch) {
	    return ca210->getPrimaryColor(ch);
	};
	RGB_ptr IntensityAnayzer::getReferenceRGB() {
	    return ca210->getReferenceRGB();
	};
	bptr < MeterMeasurement > IntensityAnayzer::getMeterMeasurement() {
	    return bptr < MeterMeasurement > ((MeterMeasurement *) null);
	};
	//=====================================================================
#endif
    };
};

