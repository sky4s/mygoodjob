#include <includeall.h>
#pragma hdrstop
#include "analyzer.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <ca210api/CA210API.h>

#define CA210DAT "ca210.dat"
#define INTENSITY_FILE "intensity.xls"

namespace cms {
    namespace measure {

	using namespace java::lang;
	using namespace cms::measure::meter;
	using namespace cms::colorformat;
	using namespace cms::lcd::calibrate;
	using namespace Dep;
	using namespace Indep;
	using namespace ca210api;

	//======================================================================
	// IntensityAnalyzerIF
	//======================================================================
	void IntensityAnalyzerIF::
	    setReferenceColorComment(const string & comment) {
	    this->comment = string_ptr(new string(comment));
	};
	string_ptr IntensityAnalyzerIF::getReferenceColorComment() {
	    return comment;
	};
	//======================================================================

	//======================================================================
	//
	//======================================================================
	void CA210IntensityAnalyzer::init() {
	    ca210api->setDisplayMode(Lvxy);
	    ca210api->setChannelNO(0);
	    Util::deleteExist(CA210DAT);
	    ca210api->copyToFile(CA210DAT);
	};

      CA210IntensityAnalyzer::CA210IntensityAnalyzer(bptr < CA210 > ca210, bptr < MeterMeasurement > mm):ca210(ca210), ca210api(ca210->getCA210API()), mm(mm),
	    dummyMode(false),
	    dgc(null) {
	    /*, defaultWaitTimes(-1) */
	    init();
	};

      CA210IntensityAnalyzer::CA210IntensityAnalyzer(bptr < MeterMeasurement > mm):mm(mm), dummyMode(true),
	    dgc
	    (null) {
	};

	RGB_ptr CA210IntensityAnalyzer::getIntensity(RGB_ptr rgb) {
	    if (false == dummyMode) {
		ca210api->setDisplayMode(Lvxy);
	    }
	    getCIEXYZOnly(rgb);
	    float_array rgbIntensity;
	    if (true == dummyMode) {
		//若為dummy mode, 代表從meter直接撈資料
		//而meter是假的, 其實是從檔案撈資料
		if (null == dgc) {
		    dgc = dynamic_cast
			< DGLutFileMeter * >(mm->getMeter().get());
		}
		Component_ptr c = dgc->getComponent();
		RGB_ptr intensity = c->intensity;
		rgbIntensity = float_array(new float[3]);
		rgbIntensity[0] = intensity->R;
		rgbIntensity[1] = intensity->G;
		rgbIntensity[2] = intensity->B;
	    } else {
		rgbIntensity = ca210api->triggerIntensityAnalyze();
	    }

	    RGB_ptr intensity(new
			      RGBColor(rgbIntensity[0], rgbIntensity[1],
				       rgbIntensity[2]));
	    return intensity;

	};
	XYZ_ptr CA210IntensityAnalyzer::getCIEXYZ() {
	    return XYZ;
	};
	XYZ_ptr CA210IntensityAnalyzer::getCIEXYZOnly(RGB_ptr rgb) {
	    Patch_ptr patch = mm->measure(rgb, rgb->toString());
	    XYZ = patch->getXYZ();
	    return XYZ;
	};

	void CA210IntensityAnalyzer::setupComponent(const Dep::
						    Channel & ch,
						    RGB_ptr rgb) {
	    Patch_ptr p = mm->measure(rgb, rgb->toString());
	    XYZ = p->getXYZ();

	    switch (ch.chindex) {
	    case ChannelIndex::R:
		rp = p;
		break;
	    case ChannelIndex::G:
		gp = p;
		break;
	    case ChannelIndex::B:
		bp = p;
		break;
	    case ChannelIndex::W:
		wp = p;
		break;
	    };
	};

	void CA210IntensityAnalyzer::enter() {
	    if (false == dummyMode) {
		ca210api->copyFromFile(CA210DAT);
		ca210api->setLvxyCalMode();

		RGB_ptr r = rp->getRGB();
		mm->measure(r, r->toString());
		ca210api->setLvxyCalData(Red,
					 (new CIExyY(rp->getXYZ()))->
					 getValues());

		RGB_ptr g = gp->getRGB();
		mm->measure(g, g->toString());
		ca210api->setLvxyCalData(Green,
					 (new CIExyY(gp->getXYZ()))->
					 getValues());

		RGB_ptr b = bp->getRGB();
		mm->measure(b, b->toString());
		ca210api->setLvxyCalData(Blue,
					 (new CIExyY(bp->getXYZ()))->
					 getValues());

		RGB_ptr w = wp->getRGB();
		mm->measure(w, w->toString());
		ca210api->setLvxyCalData(White,
					 (new CIExyY(wp->getXYZ()))->
					 getValues());

		ca210api->enter();
	    }
	    mm->setMeasureWindowsVisible(false);
	};

	void CA210IntensityAnalyzer::setChannel(int no, string_ptr id) {
	    if (false == dummyMode) {
		//設定no
		ca210api->setChannelNO(no);
		//設定id
		ca210api->setChannelID(WideString(id->c_str()));
	    }
	};
	void CA210IntensityAnalyzer::beginAnalyze() {
	    mm->setMeasureWindowsVisible(true);
	};
	void CA210IntensityAnalyzer::endAnalyze() {
	    mm->setMeasureWindowsVisible(false);
	};
	void CA210IntensityAnalyzer::setWaitTimes(int waitTimes) {
	    mm->setWaitTimes(waitTimes);
	};

	int CA210IntensityAnalyzer::getWaitTimes() {
	    return mm->getWaitTimes();
	};
	xyY_ptr CA210IntensityAnalyzer::getReferenceColor() {
	    if (null != wp) {
		return xyY_ptr(new CIExyY(wp->getXYZ()));
	    } else {
		return xyY_ptr((CIExyY *) null);
	    }

	};
	xyY_ptr CA210IntensityAnalyzer::getPrimaryColor(const Dep::
							Channel & ch) {
	    switch (ch.chindex) {
	    case ChannelIndex::R:
		if (null != rp) {
		    return xyY_ptr(new CIExyY(rp->getXYZ()));
		}
		break;
	    case ChannelIndex::G:
		if (null != gp) {
		    return xyY_ptr(new CIExyY(gp->getXYZ()));
		}
		break;
	    case ChannelIndex::B:
		if (null != bp) {
		    return xyY_ptr(new CIExyY(bp->getXYZ()));
		}
		break;
	    default:
		throw IllegalArgumentException("Unsupported Channel:" +
					       *ch.toString());
	    };
	    return xyY_ptr((CIExyY *) null);
	};
	RGB_ptr CA210IntensityAnalyzer::getReferenceRGB() {
	    if (null != wp) {
		return wp->getRGB();
	    } else {
		return RGB_ptr((RGBColor *) null);
	    }
	};
	bptr < MeterMeasurement >
	    CA210IntensityAnalyzer::getMeterMeasurement() {
	    return mm;
	};
	//======================================================================

	//======================================================================
	// MaxMatrixIntensityAnayzer
	//======================================================================
      MaxMatrixIntensityAnayzer::MaxMatrixIntensityAnayzer(bptr < MeterMeasurement > mm):mm(mm)
	{

	};
	MaxMatrixIntensityAnayzer::MaxMatrixIntensityAnayzer() {

	};

	RGB_ptr MaxMatrixIntensityAnayzer::getIntensity(RGB_ptr rgb) {
	    //component: 0~100%
	    getCIEXYZOnly(rgb);

	    return getIntensity(XYZ);
	};

	RGB_ptr MaxMatrixIntensityAnayzer::getIntensity(XYZ_ptr XYZ) {
	    if (null == inverseMatrix) {
		throw IllegalStateException("NULL == inverseMatrix");
	    }
	    double2D_ptr color =
		DoubleArray::toDouble2D(1, 3, XYZ->X, XYZ->Y, XYZ->Z);
	    rgbValues = DoubleArray::times(inverseMatrix, color);
	    (*rgbValues)[0][0] *= 100;
	    (*rgbValues)[1][0] *= 100;
	    (*rgbValues)[2][0] *= 100;
	    double_array intensityValues(new double[3]);

	    intensityValues[0] = (*rgbValues)[0][0] / (*targetRatio)[0][0];
	    intensityValues[1] = (*rgbValues)[1][0] / (*targetRatio)[1][0];
	    intensityValues[2] = (*rgbValues)[2][0] / (*targetRatio)[2][0];

	    RGB_ptr intensity(new
			      RGBColor(intensityValues[0],
				       intensityValues[1],
				       intensityValues[2]));
	    return intensity;
	};

	XYZ_ptr MaxMatrixIntensityAnayzer::getCIEXYZ() {
	    return XYZ;
	};

	XYZ_ptr MaxMatrixIntensityAnayzer::getCIEXYZOnly(RGB_ptr rgb) {
	    if (null != mm) {
		Patch_ptr patch = mm->measure(rgb, rgb->toString());
		XYZ = patch->getXYZ();
		return XYZ;
	    } else {
		throw IllegalStateException("mm = null");
	    }
	};

	void MaxMatrixIntensityAnayzer::setupComponent(const Dep::
						       Channel & ch,
						       RGB_ptr rgb) {
	    if (null != mm) {
		Patch_ptr p = mm->measure(rgb, rgb->toString());
		if (ch == Channel::W) {
		    referenceRGB = rgb->clone();
		}
		XYZ_ptr measureXYZ = p->getXYZ();
		setupComponent(ch, measureXYZ);
	    } else {
		throw IllegalStateException("mm = null");
	    }
	};

	void MaxMatrixIntensityAnayzer::setupComponent(const Dep::
						       Channel & ch,
						       XYZ_ptr measureXYZ)
	{
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
	void MaxMatrixIntensityAnayzer::enter() {
	    if (null != mm) {
		mm->setMeasureWindowsVisible(false);
	    }
	    if (rXYZ == null || gXYZ == null || bXYZ == null
		|| wXYZ == null) {
		throw IllegalStateException
		    ("Excute setupComponent() with RGBW first.");
	    }
	    double2D_ptr m =
		DoubleArray::toDouble2D(3, 9, rXYZ->X, gXYZ->X, bXYZ->X,
					rXYZ->Y, gXYZ->Y, bXYZ->Y,
					rXYZ->Z, gXYZ->Z, bXYZ->Z);

	    this->inverseMatrix = DoubleArray::inverse(m);

	    double2D_ptr targetWhite =
		DoubleArray::toDouble2D(1, 3, wXYZ->X, wXYZ->Y, wXYZ->Z);
	    this->targetRatio =
		DoubleArray::times(inverseMatrix, targetWhite);

	};
	void MaxMatrixIntensityAnayzer::beginAnalyze() {
	    if (null != mm) {
		mm->setMeasureWindowsVisible(true);
	    } else {
		throw IllegalStateException("mm = null");
	    }
	};
	void MaxMatrixIntensityAnayzer::endAnalyze() {
	    if (null != mm) {
		mm->setMeasureWindowsVisible(false);
	    } else {
		throw IllegalStateException("mm = null");
	    }
	};
	void MaxMatrixIntensityAnayzer::setWaitTimes(int waitTimes) {
	    if (null != mm) {
		mm->setWaitTimes(waitTimes);
	    }
	};

	int MaxMatrixIntensityAnayzer::getWaitTimes() {
	    if (null != mm) {
		return mm->getWaitTimes();
	    } else {
		return -1;
	    };
	};
	xyY_ptr MaxMatrixIntensityAnayzer::getReferenceColor() {
	    xyY_ptr xyY(new CIExyY(wXYZ));
	    return xyY;
	};
	xyY_ptr MaxMatrixIntensityAnayzer::getPrimaryColor(const Dep::
							   Channel & ch) {
	    switch (ch.chindex) {
	    case ChannelIndex::R:
		return xyY_ptr(new CIExyY(rXYZ));
	    case ChannelIndex::G:
		return xyY_ptr(new CIExyY(gXYZ));
	    case ChannelIndex::B:
		return xyY_ptr(new CIExyY(bXYZ));
	    default:
		throw IllegalArgumentException("Unsupported Channel: " +
					       *ch.toString());
	    };
	};
	RGB_ptr MaxMatrixIntensityAnayzer::getReferenceRGB() {
	    return referenceRGB;
	};
	bool MaxMatrixIntensityAnayzer::isInverseMatrixNull() {
	    return null == inverseMatrix;
	}
	bptr < MeterMeasurement >
	    MaxMatrixIntensityAnayzer::getMeterMeasurement() {
	    return mm;
	};

	//=====================================================================

	//=====================================================================
	// AdvancedMaxMatrixIntensityAnayzer
	//=====================================================================
	/*AdvancedMaxMatrixIntensityAnayzer::
	    AdvancedMaxMatrixIntensityAnayzer() {
	}

	void AdvancedMaxMatrixIntensityAnayzer::
	    setupTarget(XYZ_ptr targetXYZ) {
	    this->targetWhite = targetXYZ;
	};
	RGB_ptr AdvancedMaxMatrixIntensityAnayzer::
	    getIntensity(XYZ_ptr XYZ) {
	    if (null == inverseMatrix) {
		throw IllegalStateException("null == inverseMatrix");
	    }
	    double2D_ptr color =
		DoubleArray::toDouble2D(1, 3, XYZ->X, XYZ->Y, XYZ->Z);
	    rgbValues = DoubleArray::times(inverseMatrix, color);
	    (*rgbValues)[0][0] *= 100;
	    (*rgbValues)[1][0] *= 100;
	    (*rgbValues)[2][0] *= 100;
	    double_array intensityValues(new double[3]);

	    intensityValues[0] =
		(*rgbValues)[0][0] / (*xtalkRatio)[0][0] /
		(*targetRatio)[0][0];
	    intensityValues[1] =
		(*rgbValues)[1][0] / (*xtalkRatio)[1][0] /
		(*targetRatio)[1][0];
	    intensityValues[2] =
		(*rgbValues)[2][0] / (*xtalkRatio)[2][0] /
		(*targetRatio)[2][0];

	    RGB_ptr intensity(new
			      RGBColor(intensityValues[0],
				       intensityValues[1],
				       intensityValues[2]));
	    return intensity;
	};
	void AdvancedMaxMatrixIntensityAnayzer::enter() {
	    if (null != mm) {
		mm->setMeasureWindowsVisible(false);
	    }
	    if (rXYZ == null || gXYZ == null || bXYZ == null
		|| wXYZ == null || targetWhite == null) {
		throw IllegalStateException
		    ("Excute setupComponent() with RGBW and TargetWhite first.");
	    }
	    double2D_ptr m =
		DoubleArray::toDouble2D(3, 9, rXYZ->X, gXYZ->X, bXYZ->X,
					rXYZ->Y, gXYZ->Y, bXYZ->Y,
					rXYZ->Z, gXYZ->Z, bXYZ->Z);
	    //計算反矩陣
	    this->inverseMatrix = DoubleArray::inverse(m);

	    double2D_ptr whiteValues =
		DoubleArray::toDouble2D(1, 3, wXYZ->X, wXYZ->Y, wXYZ->Z);
	    double2D_ptr targetWhiteValues =
		DoubleArray::toDouble2D(1, 3, targetWhite->X,
					targetWhite->Y, targetWhite->Z);
	    //>1.
	    this->xtalkRatio =
		DoubleArray::times(inverseMatrix, whiteValues);

	    this->targetRatio =
		DoubleArray::times(inverseMatrix, targetWhiteValues);

	};*/
	//=====================================================================

	//=====================================================================
	// IntensityAnayzer
	//=====================================================================
      IntensityAnayzer::IntensityAnayzer(bptr < MaxMatrixIntensityAnayzer > matrix, bptr < CA210IntensityAnalyzer > ca210):matrix(matrix), ca210(ca210),
	    no(0)
	{

	    fieldNames =
		StringVector::fromCString(13, "no", "CA_R", "CA_G", "CA_B",
					  "MA_R", "MA_G", "MA_B", "MA_Ro",
					  "MA_Go", "MA_Bo", "MA2_R",
					  "MA2_G", "MA2_B");
	    Util::deleteExist(INTENSITY_FILE);
	    excel = bptr < SimpleExcelAccess > (new
						SimpleExcelAccess
						(INTENSITY_FILE,
						 cms::colorformat::Create,
						 fieldNames));
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
					 (*originalIntensity)[2][0],
					 0., 0., 0.);
	    excel->insert(values);
	    return ca210Intensity;
	};
	XYZ_ptr IntensityAnayzer::getCIEXYZ() {
	    return ca210->getCIEXYZ();
	};

	XYZ_ptr IntensityAnayzer::getCIEXYZOnly(RGB_ptr rgb) {
	    throw UnsupportedOperationException();
	};

	void IntensityAnayzer::
	    setupComponent(const Dep::Channel & ch, RGB_ptr rgb) {
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
					 (*targetRatio)[1][0],
					 (*targetRatio)[2][0], 0., 0., 0.);
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

    };
};

