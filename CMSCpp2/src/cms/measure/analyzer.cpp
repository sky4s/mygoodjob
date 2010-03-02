#include "analyzer.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <ca210api/CA210API.h>
#include <cms/measure/meter.h>
#include <cms/measure/MeterMeasurement.h>
#include <cms/colorspace/rgb.h>
#include <cms/colorspace/ciexyz.h>
#include <cms/colorspace/depend.h>
#include <cms/patch.h>

namespace cms {
    namespace measure {

	using namespace cms::measure::meter;
	using namespace Dep;
	using namespace Indep;
	using namespace ca210api;

	 CA210ComponentAnalyzer::
	    CA210ComponentAnalyzer(bptr < CA210 > ca210):ca210(ca210),
	    ca210api(ca210->getCA210API()), mm(bptr < MeterMeasurement >
					       (new
						MeterMeasurement(ca210,
								 false))) {
	    mm->setWaitTimes(5000);
	    ca210api->resetLvxyCalMode();
	    ca210api->setAnalyzerCalMode();
	};

	RGB_ptr CA210ComponentAnalyzer::getComponent(RGB_ptr rgb) {
	    Patch_ptr patch = mm->measure(rgb, rgb->toString());
	     XYZ = patch->getXYZ();
	     bptr < CAMeasureResult > measureResult =
		ca210api->getMeasureResult();
	     RGB_ptr
		component(new
			  RGBColor(measureResult->R, measureResult->G,
				   measureResult->B));
	     return component;

	};
	XYZ_ptr CA210ComponentAnalyzer::getCIEXYZ() {
	    return XYZ;
	};

	void CA210ComponentAnalyzer::setupComponent(const Dep::
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
	    ca210api->setAnalyzerCalData(lclr);
	};

	void CA210ComponentAnalyzer::enter() {
	    ca210api->enter();
	};

	void CA210ComponentAnalyzer::setChannel(int no, string_ptr id) {
	    ca210api->setChannelNO(no);
	    ca210api->setChannelID(*id);
	};

	//======================================================================

      StocktonComponentAnayzer::StocktonComponentAnayzer(bptr < CA210 > ca210):CA210ComponentAnalyzer(ca210)
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

	RGB_ptr MaxMatrixComponentAnalyzer::getComponent(RGB_ptr rgb) {
	};
	void MaxMatrixComponentAnalyzer::setupComponent(const Dep::
							Channel & ch,
							RGB_ptr rgb) {
	};
	void MaxMatrixComponentAnalyzer::enter() {
	};
    };
};

