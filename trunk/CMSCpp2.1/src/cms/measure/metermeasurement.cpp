#include <includeall.h>
#pragma hdrstop
#include "MeterMeasurement.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace measure {
	using namespace boost;
	using namespace cms;
	using namespace Dep;
	using namespace cms::measure::meter;
	using namespace cms::measure::cp;
	using namespace std;
	using namespace java::lang;
	using namespace cms::lcd::calibrate;

	void MeterMeasurement::init(bool calibration) {
	    measureWindow = MeasureWindow;
	    if (true == calibration) {
		calibrate();
	    }
	};
      MeterMeasurement::MeterMeasurement(shared_ptr < Meter > meter, bool calibration):meter(meter), waitTimes(meter->getSuggestedWaitTimes()),
	    measureWindowClosing(false), titleTouched(false),
	    fakeMeasure(false) {
	    init(calibration);
	};

	void MeterMeasurement::calibrate() {
	    MeasureUtils::meterCalibrate(*this);
	};

	void MeterMeasurement::close() {
	    setMeasureWindowsVisible(false);
	    measureWindow->Close();
	    meterClose();
	};

	void MeterMeasurement::setMeasureWindowsVisible(bool visible) {
	    if (!fakeMeasure) {
		if (null == measureWindow) {
		    measureWindow = MeasureWindow;
		}
		measureWindow->setVisible(visible);
		measureWindowClosing = !visible;
	    }
	};

	Patch_ptr MeterMeasurement::measure(RGB_ptr rgb, const string_ptr patchName) {
	    return measure0(rgb, patchName, nil_string_ptr, nil_string_ptr, false);
	};

	Patch_ptr MeterMeasurement::measure(int r, int g, int b, const string_ptr patchName) {
	    RGB_ptr rgb(new RGBColor(r, g, b));
	    return measure(rgb, patchName);
	};

	Patch_ptr MeterMeasurement::measure(int r, int g, int b, const string & patchName) {
	    string_ptr str(new string(patchName));
	    RGB_ptr rgb(new RGBColor(r, g, b));
	    return measure(rgb, str);
	};

	void MeterMeasurement::setBlankTimes(int blankTimes) {
	    this->blankTimes = blankTimes;
	};
	void MeterMeasurement::setWaitTimes(int waitTimes) {
	    this->waitTimes = waitTimes;
	    /*if (waitTimes == 0) {
	       int x = 1;
	       } */
	};
	int MeterMeasurement::getWaitTimes() {
	    return waitTimes;
	};
	void MeterMeasurement::setFakeMeasure(bool fake) {
	    this->fakeMeasure = fake;
	};
	bool MeterMeasurement::isFakeMeasure() {
	    return fakeMeasure;
	};

	bptr < cms::measure::meter::Meter > MeterMeasurement::getMeter() {
	    return meter;
	};

	void MeterMeasurement::meterClose() {

	};
	Patch_ptr MeterMeasurement::measureFlicker(RGB_ptr rgb, const string_ptr patchName) {
	    return measure0(rgb, patchName, nil_string_ptr, nil_string_ptr, true);
	};
	Patch_ptr
	    MeterMeasurement::measure0(RGB_ptr measureRGB,
				       string_ptr patchName,
				       string_ptr titleNote, string_ptr timeNote, bool flickerMeasure) {
	    setMeasureWindowsVisible(true);
	    //量測的顏色, 量測的顏色可能與導具的顏色不同, 所以特別獨立出此變數

	    if (!titleTouched) {
		//如果title沒被設定過
		if (titleNote != NULL) {
		    //measureWindow.setTitle("Measure Window " + titleNote);
		    /*measureWindow->Caption =
		       AnsiString("Measure Window " + titleNote); */

		} else {
		    measureWindow->Caption = AnsiString("Measure Window");
		}
	    }
	    //==========================================================================
	    // 變換完視窗顏色的短暫停留
	    //==========================================================================
	    if (!fakeMeasure) {
		Application->ProcessMessages();
		measureWindow->setRGB(measureRGB);
		Application->ProcessMessages();
		Sleep(waitTimes);
	    }
	    //==========================================================================

	    if (true == measureWindowClosing) {
		//如果視窗被關閉, 就結束量測
		return Patch_ptr((Patch *) NULL);
	    }
	    double_array result;
	    if (flickerMeasure) {
		float flickerValue = -1;
		CA210 *ca210 = dynamic_cast < CA210 * >(meter.get());
		if (null != ca210) {
		    bptr < ca210api::CA210API > ca210api = ca210->getCA210API();
		    flickerValue = ca210api->triggerFlickerFMA();
		}
		result = double_array(new double[3]);
		result[0] = 0;
		result[1] = flickerValue;
		result[2] = 0;
	    } else {
		result = meter->triggerMeasurementInXYZ();
	    }

	    XYZ_ptr XYZ(new Indep::CIEXYZ(result));
	    Patch_ptr patch(new Patch(patchName, XYZ, XYZ, measureRGB));
	    return patch;
	};
	//======================================================================

	//======================================================================
	// MeasureResult
	//======================================================================
	void MeasureUtils::meterCalibrate(MeterMeasurement & meterMeasurement) {
	    shared_ptr < Meter > meter = meterMeasurement.meter;
	    TMeasureWindow *measureWindow = meterMeasurement.measureWindow;
	    meterCalibrate(meter, measureWindow);
	};
	void MeasureUtils::meterCalibrate(shared_ptr < Meter > meter,
					  TMeasureWindow * measureWindow) {
	    if (!meter->isConnected()) {
		throw IllegalStateException("!meter.isConnected()");
	    } else {
		if (measureWindow != NULL) {
		    //show出黑幕, 避免影響校正
		    measureWindow->setRGB(0, 0, 0);
		    Application->ProcessMessages();
		    measureWindow->setVisible(true);
		}
		ShowMessage(meter->getCalibrationDescription()->c_str());
		meter->calibrate();
		if (measureWindow != null) {
		    //關閉黑幕
		    measureWindow->setVisible(false);
		}
		ShowMessage("End of calibration");
	    };
	};

	MeasureResult::MeasureResult(Patch_vector_ptr result,
				     int practicalMeasureCount):result
	    (result), practicalMeasureCount(practicalMeasureCount) {

	};
	//======================================================================

	//======================================================================
	// MeasureTool
	//======================================================================
      MeasureTool::MeasureTool(bptr < cms::measure::MeterMeasurement > mm):mm(mm),
	    stop(false)
	{

	};
	Patch_vector_ptr MeasureTool::rampMeasure(const Dep::
						  Channel & channel,
						  bptr <
						  cms::lcd::calibrate::
						  MeasureCondition > measureCondition) {

	    RGB_vector_ptr trueMeasureCode(new RGB_vector());
	    foreach(RGB_ptr & c, *measureCondition->getRGBMeasureCode()) {
		RGB_ptr rgb;
		if (channel == Channel::W) {
		    rgb = c;
		} else {
		    rgb = RGB_ptr(new RGBColor(c->getMaxValue()));
		    rgb->setValue(channel, c->getValue(channel));
		}
		trueMeasureCode->push_back(rgb);
	    };
	    bptr < MeasureCondition > newMeasureCondition(new MeasureCondition(trueMeasureCode));
	    return rampMeasure(newMeasureCondition);
	};
	Patch_vector_ptr MeasureTool::rampMeasure(bptr < cms::lcd::calibrate::MeasureCondition >
						  measureCondition) {
	    RGB_vector_ptr rgbMeasureCode = measureCondition->getRGBMeasureCode();
	    Patch_vector_ptr vector(new Patch_vector());
	    foreach(RGB_ptr rgb, *rgbMeasureCode) {
		Patch_ptr patch = mm->measure(rgb, rgb->toString());
		vector->push_back(patch);
		if (true == stop) {
		    stop = false;
		    mm->setMeasureWindowsVisible(false);
		    return nil_Patch_vector_ptr;
		}
	    };
	    mm->setMeasureWindowsVisible(false);
	    return vector;
	};
	Component_vector_ptr MeasureTool::flickerMeasure(bptr < MeasureCondition > measureCondition) {
	    RGB_vector_ptr rgbMeasureCode = measureCondition->getRGBMeasureCode();
	    Component_vector_ptr vector(new Component_vector());
	    foreach(RGB_ptr rgb, *rgbMeasureCode) {
		Patch_ptr patch = mm->measureFlicker(rgb, rgb->toString());

		Component_ptr component(new Component(rgb, nil_RGB_ptr, patch->getXYZ()));
		vector->push_back(component);
		if (true == stop) {
		    stop = false;
		    mm->setMeasureWindowsVisible(false);
		    return nil_Component_vector_ptr;
		}
	    };
	    mm->setMeasureWindowsVisible(false);
	    return vector;
	};
	void MeasureTool::windowClosing(TObject * Sender, TCloseAction & Action) {
	    stop = true;
	}
	int MeasureTool::getMaxZDGCode(bptr < cms::lcd::calibrate::MeasureCondition >
				       measureCondition) {
	    RGB_vector_ptr rgbMeasureCode = measureCondition->getRGBMeasureCode();
	    Patch_ptr prePatch;
	    XYZ_ptr maxZ;
	    RGB_ptr maxZRGB;
	    //int maxZDG = -1;
	    mm->setMeasureWindowsVisible(true);

	    foreach(RGB_ptr rgb, *rgbMeasureCode) {
		Patch_ptr patch = mm->measure(rgb, rgb->toString());
		if (true == stop) {
		    stop = false;
		    mm->setMeasureWindowsVisible(false);
		    return -1;
		}
		XYZ_ptr XYZ = patch->getXYZ();
		if (null == maxZ) {
		    maxZ = XYZ;
		    maxZRGB = rgb;
		    continue;
		}
		if (XYZ->Z > maxZ->Z) {
		    maxZ = XYZ;
		    maxZRGB = rgb;
		} else {
		    mm->setMeasureWindowsVisible(false);
		    //return (int) rgb->getValue(Channel::W);
		    return (int) maxZRGB->getValue(Channel::W);
		}
	    };
	    mm->setMeasureWindowsVisible(false);
	    return -1;
	}

	int MeasureTool::getMaxZDGCode(bptr < MeterMeasurement > mm,
				       bptr < BitDepthProcessor > bitDepth) {
	    if (mm->isFakeMeasure()) {
		throw IllegalStateException("mm->isFakeMeasure(), cannot do real measure.");
	    }
	    bptr < MeasureTool > mt(new MeasureTool(mm));
	    MeasureWindow->addWindowListener(mt);
	    bptr < MeasureCondition > measureCondition(new MeasureCondition(bitDepth));
	    int maxZDGCode = mt->getMaxZDGCode(measureCondition);
	    return maxZDGCode;
	};
	//======================================================================
    };
};

