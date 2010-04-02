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
	    mm->setWaitTimes(5000);
	    ca210api->setChannelNO(0);
	    ca210api->copyToFile(CalibrationDataFilename);
	};

	 CA210IntensityAnalyzer::CA210IntensityAnalyzer(bptr < CA210 >
							ca210,
							bptr <
							MeterMeasurement >
							mm):ca210(ca210),
	    ca210api(ca210->getCA210API()), mm(mm), dummyMode(false),
	    dgc(null) {
	    init();
	};

      CA210IntensityAnalyzer::CA210IntensityAnalyzer(bptr < MeterMeasurement > mm):mm(mm),
	    dummyMode(true), dgc(null)
	{
	};

	RGB_ptr CA210IntensityAnalyzer::getIntensity(RGB_ptr rgb) {
	    Patch_ptr patch = mm->measure(rgb, rgb->toString());
	    XYZ = patch->getXYZ();
	    float_array rgbComponent;
	    if (true == dummyMode) {
		//若為dummy mode, 代表從meter直接撈資料
		//而meter是假的, 其實是從檔案撈資料
		if (null == dgc) {
		    dgc = dynamic_cast
			< DGLutFileMeter * >(mm->getMeter().get());
		    /*dgc.reset(dynamic_cast
		       < DGLutFileMeter * >(mm->getMeter().get())); */
		}
		Component_ptr c = dgc->getComponent();
		RGB_ptr intensity = c->intensity;
		rgbComponent.reset(new float[3]);
		rgbComponent[0] = intensity->R;
		rgbComponent[1] = intensity->G;
		rgbComponent[2] = intensity->B;
	    } else {
		rgbComponent = ca210api->triggerComponentAnalyze();
	    }

	    float r = rgbComponent[0];
	    float g = rgbComponent[1];
	    float b = rgbComponent[2];
	    RGB_ptr intensity(new RGBColor(r, g, b));
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
		mm->setMeasureWindowsVisible(false);
	    }
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
	//======================================================================

      StocktonComponentAnayzer::StocktonComponentAnayzer(bptr < CA210 > ca210, bptr < MeterMeasurement > mm):CA210IntensityAnalyzer(ca210, mm)
	{
	    mm->setWaitTimes(5000);
	    ca210api->setLvxyCalMode();
	};

	void StocktonComponentAnayzer::setupComponent(const Dep::
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

	void StocktonComponentAnayzer::enter() {
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

	MaxMatrixComponentAnalyzer::
	    MaxMatrixComponentAnalyzer(const Dep::RGBColorSpace &
				       rgbColorSpace):rgbColorSpace
	    (rgbColorSpace) {
	};

	RGB_ptr MaxMatrixComponentAnalyzer::getIntensity(RGB_ptr rgb) {
	    //component: 0~100%
	};
	void MaxMatrixComponentAnalyzer::setupComponent(const Dep::
							Channel & ch,
							RGB_ptr rgb) {
	};
	void MaxMatrixComponentAnalyzer::enter() {
	};
	void MaxMatrixComponentAnalyzer::beginAnalyze() {
	};
	void MaxMatrixComponentAnalyzer::endAnalyze() {
	};
    };
};

