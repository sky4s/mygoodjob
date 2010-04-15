#include <includeall.h>
#pragma hdrstop
#include "analyzer.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <ca210api/CA210API.h>

namespace cms {
    namespace measure {

	using namespace cms::measure::meter;
	using namespace cms::lcd::calibrate;
	using namespace Dep;
	using namespace Indep;
	using namespace ca210api;

	const WideString & CA210IntensityAnalyzer::
	    CalibrationDataFilename = "ca210.dat";

	void CA210IntensityAnalyzer::init() {
	    //mm->setWaitTimes(5000);
	    ca210api->setChannelNO(0);
	    ca210api->copyToFile(CalibrationDataFilename);
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
	    Patch_ptr p = mm->measure(rgb, rgb->toString());

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
	};

	void CA210IntensityAnalyzer::enter() {
	    if (false == dummyMode) {
		ca210api->enter();
	    }
	    mm->setMeasureWindowsVisible(false);
	};

	void CA210IntensityAnalyzer::setChannel(int no, string_ptr id) {
	    if (false == dummyMode) {
		ca210api->setChannelNO(no);
		ca210api->setChannelID(WideString(id->c_str()));

		ca210api->resetLvxyCalMode();
		ca210api->copyFromFile(CalibrationDataFilename);
		ca210api->setAnalyzerCalMode();
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
	    mm->setWaitTimes(defaultWaitTimes);
	    defaultWaitTimes = -1;
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
      MaxMatrixIntensityAnayzer::MaxMatrixIntensityAnayzer(bptr < MeterMeasurement > mm):mm(mm)
	{

	};

	RGB_ptr MaxMatrixIntensityAnayzer::getIntensity(RGB_ptr rgb) {
	    //component: 0~100%
	    Patch_ptr patch = mm->measure(rgb, rgb->toString());
	    XYZ = patch->getXYZ();

	    return getIntensity(XYZ);
	    /*double2D_ptr color =
	       DoubleArray::toDouble2D(3, 1, XYZ->X, XYZ->Y, XYZ->Z);
	       double2D_ptr ratio = DoubleArray::times(inverseMatrix, color);
	       double_array rgbIntensity(new double[3]);
	       rgbIntensity[0] = (*ratio)[0][0] / (*targetRatio)[0][0];
	       rgbIntensity[1] = (*ratio)[1][0] / (*targetRatio)[1][0];
	       rgbIntensity[2] = (*ratio)[2][0] / (*targetRatio)[2][0];

	       RGB_ptr intensity(new
	       RGBColor(rgbIntensity[0], rgbIntensity[1],
	       rgbIntensity[2]));
	       return intensity; */
	};

	RGB_ptr MaxMatrixIntensityAnayzer::getIntensity(XYZ_ptr XYZ) {
	    double2D_ptr color =
		DoubleArray::toDouble2D(3, 1, XYZ->X, XYZ->Y, XYZ->Z);
	    double2D_ptr ratio = DoubleArray::times(inverseMatrix, color);
	    double_array rgbIntensity(new double[3]);
	    rgbIntensity[0] = (*ratio)[0][0] / (*targetRatio)[0][0];
	    rgbIntensity[1] = (*ratio)[1][0] / (*targetRatio)[1][0];
	    rgbIntensity[2] = (*ratio)[2][0] / (*targetRatio)[2][0];

	    RGB_ptr intensity(new
			      RGBColor(rgbIntensity[0], rgbIntensity[1],
				       rgbIntensity[2]));
	    return intensity;
	};

	XYZ_ptr MaxMatrixIntensityAnayzer::getCIEXYZ() {
	    return XYZ;
	};
	void MaxMatrixIntensityAnayzer::setupComponent(const Dep::
						       Channel & ch,
						       RGB_ptr rgb) {
	    Patch_ptr p = mm->measure(rgb, rgb->toString());

	    switch (ch.chindex) {
	    case ChannelIndex::R:
		rPatch = p;
		break;
	    case ChannelIndex::G:
		gPatch = p;
		break;
	    case ChannelIndex::B:
		bPatch = p;
		break;
	    case ChannelIndex::W:
		wPatch = p;
		break;
	    };

	};
	void MaxMatrixIntensityAnayzer::enter() {
	    mm->setMeasureWindowsVisible(false);
	    XYZ_ptr rXYZ = rPatch->getXYZ();
	    XYZ_ptr gXYZ = gPatch->getXYZ();
	    XYZ_ptr bXYZ = bPatch->getXYZ();
	    XYZ_ptr wXYZ = wPatch->getXYZ();

	    double2D_ptr m =
		DoubleArray::toDouble2D(3, 3, rXYZ->X, gXYZ->X, bXYZ->X,
					rXYZ->Y, gXYZ->Y, bXYZ->Y,
					rXYZ->Z, gXYZ->Z, bXYZ->Z);
	    this->inverseMatrix = DoubleArray::inverse(m);
	    double2D_ptr targetWhite =
		DoubleArray::toDouble2D(3, 1, wXYZ->X, wXYZ->Y, wXYZ->Z);
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
	    mm->setWaitTimes(defaultWaitTimes);
	    defaultWaitTimes = -1;
	};
	//=====================================================================

	//=====================================================================
	// IntensityAnayzer
	//=====================================================================
      IntensityAnayzer::IntensityAnayzer(bptr < MaxMatrixIntensityAnayzer > matrix, bptr < CA210IntensityAnalyzer > ca210):matrix(matrix),
	    ca210(ca210), excel("intensity.xls", cms::colorformat::Create),
	    no(0) {

	    fieldNames =
		StringVector::fromCString(7, "no", "CA_R", "CA_G", "CA_B",
					  "MA_R", "MA_G", "MA_B");
	    excel.createTable("Sheet1", fieldNames);
	};
	RGB_ptr IntensityAnayzer::getIntensity(RGB_ptr rgb) {
	    RGB_ptr ca210Intensity = ca210->getIntensity(rgb);
	    XYZ_ptr XYZ = ca210->getCIEXYZ();
	    RGB_ptr matrixIntensity = matrix->getIntensity(XYZ);
	    string caR = _toString(ca210Intensity->R);
	    string caG = _toString(ca210Intensity->G);
	    string caB = _toString(ca210Intensity->B);
	    string maR = _toString(matrixIntensity->R);
	    string maG = _toString(matrixIntensity->G);
	    string maB = _toString(matrixIntensity->B);
	    string_vector_ptr values =
		StringVector::fromString(7, _toString(no++), caR, caG, caB,
					 maR, maG, maB);
	    excel.insert(fieldNames, values);
	    return ca210Intensity;
	};
	XYZ_ptr IntensityAnayzer::getCIEXYZ() {
	    return ca210->getCIEXYZ();
	};
	void IntensityAnayzer::
	    setupComponent(const Dep::Channel & ch, RGB_ptr rgb) {
	    ca210->setupComponent(ch, rgb);
	    matrix->setupComponent(ch, rgb);
	};
	void IntensityAnayzer::enter() {
	    ca210->enter();
	    matrix->enter();
	};
	void IntensityAnayzer::beginAnalyze() {
	    ca210->beginAnalyze();
	    matrix->beginAnalyze();
	};
	void IntensityAnayzer::endAnalyze() {
	    ca210->endAnalyze();
	    matrix->endAnalyze();
	};
	void IntensityAnayzer::setWaitTimes(int waitTimes) {
	    ca210->setWaitTimes(waitTimes);
	    matrix->setWaitTimes(waitTimes);
	};
	void IntensityAnayzer::setDefaultWaitTimes() {
	    ca210->setDefaultWaitTimes();
	    matrix->setDefaultWaitTimes();
	};
	//=====================================================================
    };
};

