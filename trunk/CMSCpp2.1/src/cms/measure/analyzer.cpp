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
	void IntensityAnalyzerIF::setReferenceColorComment(const string & comment) {
	    this->comment = string_ptr(new string(comment));
	};
	string_ptr IntensityAnalyzerIF::getReferenceColorComment() {
	    return comment;
	};
	xyY_ptr IntensityAnalyzerIF::measureReferenceRGB() {
	    bptr < MeterMeasurement > mm = getMeterMeasurement();
	    RGB_ptr rgb = getReferenceRGB();
	    Patch_ptr result = mm->measure(rgb, nil_string_ptr);
            mm->setMeasureWindowsVisible(false);
	    XYZ_ptr XYZ = result->getXYZ();
	    xyY_ptr xyY(new CIExyY(XYZ));
	    return xyY;
	};
	//======================================================================

	//======================================================================
	//
	//======================================================================
	void CA210IntensityAnalyzer::init() {
	    ca210api->setDisplayMode(Lvxy);
	    //ca210api->setChannelNO(0);
	    //Util::deleteExist(CA210DAT);
	    //ca210api->copyToFile(CA210DAT);
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
		//而meter是假的, 其實是從檔案撈資料
		if (null == dgc) {
		    dgc = dynamic_cast < DGLutFileMeter * >(mm->getMeter().get());
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

	    RGB_ptr intensity(new RGBColor(rgbIntensity[0], rgbIntensity[1], rgbIntensity[2]));
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

	void CA210IntensityAnalyzer::setupComponent(const Dep::Channel & ch, RGB_ptr rgb) {
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
		ca210api->setLvxyCalData(Red, (new CIExyY(rp->getXYZ()))->getValues());

		RGB_ptr g = gp->getRGB();
		mm->measure(g, g->toString());
		ca210api->setLvxyCalData(Green, (new CIExyY(gp->getXYZ()))->getValues());

		RGB_ptr b = bp->getRGB();
		mm->measure(b, b->toString());
		ca210api->setLvxyCalData(Blue, (new CIExyY(bp->getXYZ()))->getValues());

		RGB_ptr w = wp->getRGB();
		mm->measure(w, w->toString());
		ca210api->setLvxyCalData(White, (new CIExyY(wp->getXYZ()))->getValues());

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
	void CA210IntensityAnalyzer::setChannel(int no) {
	    if (false == dummyMode) {
		//設定no
		ca210api->setChannelNO(no);

	    }
	};
	int CA210IntensityAnalyzer::getChannelNO() {
	    if (false == dummyMode) {
		return (int) ca210api->getChannelNO();
	    } else {
		return -1;
	    }
	};
	void CA210IntensityAnalyzer::beginAnalyze() {
	    mm->setMeasureWindowsVisible(true);
	};
	void CA210IntensityAnalyzer::endAnalyze() {
	    mm->setMeasureWindowsVisible(false);
	};
	void CA210IntensityAnalyzer::setWaitTimes(int waitTimes) {
	    mm->WaitTimes = waitTimes;
	};

	int CA210IntensityAnalyzer::getWaitTimes() {
	    return mm->WaitTimes;
	};
	xyY_ptr CA210IntensityAnalyzer::getReferenceColor() {
	    if (null != wp) {
		return xyY_ptr(new CIExyY(wp->getXYZ()));
	    } else {
		return xyY_ptr((CIExyY *) null);
	    }

	};
	xyY_ptr CA210IntensityAnalyzer::getPrimaryColor(const Dep::Channel & ch) {
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
		throw IllegalArgumentException("Unsupported Channel:" + *ch.toString());
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
	bptr < MeterMeasurement > CA210IntensityAnalyzer::getMeterMeasurement() {
	    return mm;
	};
	//======================================================================


    };
};

