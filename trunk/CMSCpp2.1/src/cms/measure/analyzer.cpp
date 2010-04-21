#include <includeall.h>
#pragma hdrstop
#include "analyzer.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <ca210api/CA210API.h>

#define CA210DAT "ca210.dat"

namespace cms {
    namespace measure {

	using namespace java::lang;
	using namespace cms::measure::meter;
	using namespace cms::colorformat;
	using namespace cms::lcd::calibrate;
	using namespace Dep;
	using namespace Indep;
	using namespace ca210api;

	/*const WideString & CA210IntensityAnalyzer::
	   CalibrationDataFilename = "ca210.dat"; */

	void CA210IntensityAnalyzer::init() {
	    ca210api->setDisplayMode(Lvxy);
	    ca210api->setChannelNO(0);
	    Util::deleteExist(CA210DAT);
	    ca210api->copyToFile(CA210DAT);
	};

	 CA210IntensityAnalyzer::CA210IntensityAnalyzer(bptr < CA210 >
							ca210,
							bptr <
							MeterMeasurement >
							mm):ca210(ca210),
	    ca210api(ca210->getCA210API()), mm(mm), dummyMode(false),
	    dgc(null), defaultWaitTimes(-1) {
	    init();
	};

      CA210IntensityAnalyzer::CA210IntensityAnalyzer(bptr < MeterMeasurement > mm):mm(mm),
	    dummyMode(true), dgc(null), defaultWaitTimes(-1)
	{
	};

	RGB_ptr CA210IntensityAnalyzer::getIntensity(RGB_ptr rgb) {
	    //mm->measure(rgb, rgb->toString());
	    ca210api->setDisplayMode(Lvxy);
	    Patch_ptr patch = mm->measure(rgb, rgb->toString());
	    XYZ = patch->getXYZ();
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
		rgbIntensity.reset(new float[3]);
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

	void CA210IntensityAnalyzer::setupComponent(const Dep::
						    Channel & ch,
						    RGB_ptr rgb) {

	    mm->measure(rgb, rgb->toString());

	    lClr lclr;
	    switch (ch.chindex) {
	    case ChannelIndex::R:
		lclr = Red;
		break;
	    case ChannelIndex::G:
		lclr = Green;
		break;
	    case ChannelIndex::B:
		lclr = Blue;
		break;
	    case ChannelIndex::W:
		lclr = White;
		break;
	    };
	    if (false == dummyMode) {
		ca210api->setAnalyzerCalData(lclr);
	    }
	    float_array XYZValues = ca210api->triggerMeasurement();
	    XYZ.reset(new
		      CIEXYZ(XYZValues[0], XYZValues[1], XYZValues[2]));
	};

	void CA210IntensityAnalyzer::enter() {
	    if (false == dummyMode) {
		ca210api->enter();
	    }
	    mm->setMeasureWindowsVisible(false);
	};

	/*
	   設定channel的no和id
	 */
	void CA210IntensityAnalyzer::setChannel(int no, string_ptr id,
						bool reset) {
	    if (false == dummyMode) {
		//設定no
		ca210api->setChannelNO(no);
		//設定id
		ca210api->setChannelID(WideString(id->c_str()));
		//重新設定CalMode
		//ca210api->resetLvxyCalMode();
		if (true == reset) {
		    ca210api->copyFromFile(CA210DAT);
                    ca210api->setAnalyzerCalMode();
		}

	    }
	};
	void CA210IntensityAnalyzer::beginAnalyze() {
	    mm->setMeasureWindowsVisible(true);
	};
	void CA210IntensityAnalyzer::endAnalyze() {
	    mm->setMeasureWindowsVisible(false);
	};
	void CA210IntensityAnalyzer::setWaitTimes(int waitTimes) {
	    if (-1 == defaultWaitTimes) {
		defaultWaitTimes = mm->getWaitTimes();
	    }
	    mm->setWaitTimes(waitTimes);
	};
	void CA210IntensityAnalyzer::setDefaultWaitTimes() {
	    if (defaultWaitTimes != -1) {
		mm->setWaitTimes(defaultWaitTimes);
		defaultWaitTimes = -1;
	    }

	};
	//======================================================================

      StocktonIntensityAnayzer::StocktonIntensityAnayzer(bptr < CA210 > ca210, bptr < MeterMeasurement > mm):CA210IntensityAnalyzer(ca210, mm)
	{
	    mm->setWaitTimes(5000);
	    ca210api->setLvxyCalMode();
	};

	void StocktonIntensityAnayzer::setupComponent(const Dep::
						      Channel & ch,
						      RGB_ptr rgb) {
	    Patch_ptr p = mm->measure(rgb, rgb->toString());
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

	void StocktonIntensityAnayzer::enter() {
	    //==================================================================
	    Patch_ptr p = rp;
	    mm->measure(p->getRGB(), p->getRGB()->toString());
	    ca210api->setLvxyCalData(Red,
				     (new CIExyY(p->getXYZ()))->
				     getxyValues());
	    //==================================================================
	    p = gp;
	    mm->measure(p->getRGB(), p->getRGB()->toString());
	    ca210api->setLvxyCalData(Green,
				     (new CIExyY(p->getXYZ()))->
				     getxyValues());
	    //==================================================================
	    p = bp;
	    mm->measure(p->getRGB(), p->getRGB()->toString());
	    ca210api->setLvxyCalData(Blue,
				     (new CIExyY(p->getXYZ()))->
				     getxyValues());
	    //==================================================================
	    p = wp;
	    mm->measure(p->getRGB(), p->getRGB()->toString());
	    ca210api->setLvxyCalData(White,
				     (new CIExyY(p->getXYZ()))->
				     getxyValues());
	    //==================================================================

	    ca210api->enter();
	};
	//======================================================================
	// MaxMatrixIntensityAnayzer
	//======================================================================
      MaxMatrixIntensityAnayzer::MaxMatrixIntensityAnayzer(bptr < MeterMeasurement > mm):mm(mm), defaultWaitTimes(-1)
	{

	};

	RGB_ptr MaxMatrixIntensityAnayzer::getIntensity(RGB_ptr rgb) {
	    //component: 0~100%
	    Patch_ptr patch = mm->measure(rgb, rgb->toString());
	    XYZ = patch->getXYZ();

	    return getIntensity(XYZ);
	};

	RGB_ptr MaxMatrixIntensityAnayzer::getIntensity(XYZ_ptr XYZ) {
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

	void MaxMatrixIntensityAnayzer::setupComponent(const Dep::
						       Channel & ch,
						       RGB_ptr rgb) {
	    Patch_ptr p = mm->measure(rgb, rgb->toString());
	    XYZ_ptr measureXYZ = p->getXYZ();
	    setupComponent(ch, measureXYZ);
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
	    mm->setMeasureWindowsVisible(false);
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
	    mm->setMeasureWindowsVisible(true);
	};
	void MaxMatrixIntensityAnayzer::endAnalyze() {
	    mm->setMeasureWindowsVisible(false);
	};
	void MaxMatrixIntensityAnayzer::setWaitTimes(int waitTimes) {
	    if (-1 == defaultWaitTimes) {
		defaultWaitTimes = mm->getWaitTimes();
	    }
	    mm->setWaitTimes(waitTimes);
	};
	void MaxMatrixIntensityAnayzer::setDefaultWaitTimes() {
	    if (defaultWaitTimes != -1) {
		mm->setWaitTimes(defaultWaitTimes);
		defaultWaitTimes = -1;
	    }

	};
	/*const std::string & MaxMatrixIntensityAnayzer::
	   CoefficientFilename = "analyzer.xls"; */
	//=====================================================================

	//=====================================================================
	// IntensityAnayzer
	//=====================================================================
      IntensityAnayzer::IntensityAnayzer(bptr < MaxMatrixIntensityAnayzer > matrix, bptr < MaxMatrixIntensityAnayzer2 > matrix2, bptr < CA210IntensityAnalyzer > ca210):matrix(matrix), matrix2(matrix2),
	    ca210(ca210),
	    no(0) {

	    fieldNames =
		StringVector::fromCString(13, "no", "CA_R", "CA_G", "CA_B",
					  "MA_R", "MA_G", "MA_B", "MA_Ro",
					  "MA_Go", "MA_Bo", "MA2_R",
					  "MA2_G", "MA2_B");
	    excel.
		reset(new
		      SimpleExcelAccess("intensity.xls",
					cms::colorformat::Create,
					fieldNames));
	};
	RGB_ptr IntensityAnayzer::getIntensity(RGB_ptr rgb) {
	    RGB_ptr ca210Intensity = ca210->getIntensity(rgb);
	    XYZ_ptr XYZ = ca210->getCIEXYZ();
	    RGB_ptr matrixIntensity = matrix->getIntensity(XYZ);
	    double2D_ptr originalIntensity = matrix->rgbValues;
	    RGB_ptr matrix2Intensity = matrix2->getIntensity(XYZ);

	    string_vector_ptr values =
		StringVector::fromDouble(13, static_cast < double >(no++),
					 ca210Intensity->R,
					 ca210Intensity->G,
					 ca210Intensity->B,
					 matrixIntensity->R,
					 matrixIntensity->G,
					 matrixIntensity->B,
					 (*originalIntensity)[0][0],
					 (*originalIntensity)[1][0],
					 (*originalIntensity)[2][0],
					 matrix2Intensity->R,
					 matrix2Intensity->G,
					 matrix2Intensity->B);
	    excel->insert(values);
	    return ca210Intensity;
	};
	XYZ_ptr IntensityAnayzer::getCIEXYZ() {
	    return ca210->getCIEXYZ();
	};
	void IntensityAnayzer::
	    setupComponent(const Dep::Channel & ch, RGB_ptr rgb) {
	    ca210->setupComponent(ch, rgb);
	    XYZ_ptr XYZ = ca210->getCIEXYZ();
	    matrix->setupComponent(ch, XYZ);
	    matrix2->setupComponent(ch, XYZ);
	};
	void IntensityAnayzer::enter() {
	    ca210->enter();
	    matrix->enter();
	    matrix2->enter();

	    double2D_ptr targetRatio = matrix->targetRatio;
	    float2D_ptr targetRatio2 = matrix2->targetRatio;

	    string_vector_ptr values =
		StringVector::fromDouble(13, 99., 0., 0., 0., 0., 0., 0.,
					 (*targetRatio)[0][0],
					 (*targetRatio)[1][0],
					 (*targetRatio)[2][0],
					 (*targetRatio2)[0][0],
					 (*targetRatio2)[1][0],
					 (*targetRatio2)[2][0]);
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
	void IntensityAnayzer::setDefaultWaitTimes() {
	    ca210->setDefaultWaitTimes();
	};
	//=====================================================================

      MaxMatrixIntensityAnayzer2::MaxMatrixIntensityAnayzer2(bptr < MeterMeasurement > mm):MaxMatrixIntensityAnayzer(mm)
	{

	};

	void MaxMatrixIntensityAnayzer2::enter() {
	    mm->setMeasureWindowsVisible(false);
	    if (rXYZ == null || gXYZ == null || bXYZ == null
		|| wXYZ == null) {
		throw IllegalStateException
		    ("Excute setupComponent() with RGBW first.");
	    }

	    float2D_ptr m =
		FloatArray::toFloat2D(3, 9, rXYZ->X, rXYZ->Y, rXYZ->Z,
				      gXYZ->X, gXYZ->Y, gXYZ->Z,
				      bXYZ->X, bXYZ->Y, bXYZ->Z);
	    this->inverseMatrix = FloatArray::inverse(m);
	    float2D_ptr targetWhite =
		FloatArray::toFloat2D(1, 3, wXYZ->X, wXYZ->Y, wXYZ->Z);
	    this->targetRatio =
		FloatArray::times(inverseMatrix, targetWhite);

	};

	RGB_ptr MaxMatrixIntensityAnayzer2::getIntensity(XYZ_ptr XYZ) {
	    float2D_ptr color =
		FloatArray::toFloat2D(1, 3, XYZ->X, XYZ->Y, XYZ->Z);
	    rgbValues = FloatArray::times(inverseMatrix, color);
	    (*rgbValues)[0][0] *= 100;
	    (*rgbValues)[1][0] *= 100;
	    (*rgbValues)[2][0] *= 100;
	    float_array intensityValues(new float[3]);
	    intensityValues[0] = (*rgbValues)[0][0] / (*targetRatio)[0][0];
	    intensityValues[1] = (*rgbValues)[1][0] / (*targetRatio)[1][0];
	    intensityValues[2] = (*rgbValues)[2][0] / (*targetRatio)[2][0];

	    RGB_ptr intensity(new
			      RGBColor(static_cast <
				       double >(intensityValues[0]),
				       static_cast <
				       double >(intensityValues[1]),
				       static_cast <
				       double >(intensityValues[2])));
	    return intensity;
	};
    };
};

