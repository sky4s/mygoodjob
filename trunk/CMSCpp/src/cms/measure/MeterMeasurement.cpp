#include "MeterMeasurement.h"

#include <vcl.h>
#include <cms/measure/meter.h>
#include <cms/patch.h>
#include <cms/colorspace/ciexyz.h>
#include <cms/colorspace/rgb.h>

namespace cms {
    namespace measure {
	using namespace boost;
	using namespace cms;
	using namespace cms::colorspace;
	using namespace cms::measure::meter;
	using namespace std;
	 MeterMeasurement::MeterMeasurement(shared_ptr <
					    cms::measure::meter::Meter >
					    meter,
					    bool calibration):meter(meter),
	    waitTimes(1 /*meter->getSuggestedWaitTimes() */ ),
	 measureWindowClosing(false), titleTouched(false),
	    fakeMeasure(false) {
	    measureWindow = MeasureWindow;
	    if (true == calibration) {
		calibrate();
	    }
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
		measureWindow->Visible = visible;
		measureWindowClosing = !visible;
	    }
	};

	shared_ptr < Patch >
	    MeterMeasurement::measure(shared_ptr < RGBColor > rgb,
				      shared_ptr < string > patchName) {
	    return measure0(rgb, patchName, nil_string_ptr,
			    nil_string_ptr);
	};

	shared_ptr < Patch > MeterMeasurement::measure(int r, int g, int b,
						       string patchName) {
	    shared_ptr < RGBColor > rgb(new RGBColor(r, g, b));
	    return measure(rgb, string_ptr(&patchName));
	};

	void MeterMeasurement::setBlankTimes(int blankTimes) {
	    this->blankTimes = blankTimes;
	};
	void MeterMeasurement::setWaitTimes(int waitTimes) {
	    this->waitTimes = waitTimes;
	};
	void MeterMeasurement::setFakeMeasure(bool fake) {
	    this->fakeMeasure = fake;
	};
	bool MeterMeasurement::isFakeMeasure() {
	    return fakeMeasure;
	};

	void MeterMeasurement::meterClose() {
	    meter->close();
	};

	shared_ptr < Patch >
	    MeterMeasurement::measure0(shared_ptr < RGBColor > measureRGB,
				       shared_ptr < string > patchName,
				       shared_ptr < string > titleNote,
				       shared_ptr < string > timeNote) {
	    setMeasureWindowsVisible(true);
	    //量測的顏色, 量測的顏色可能與導具的顏色不同, 所以特別獨立出此變數
	    //final RGB measureRGB = processInverseRGB(rgb);
	    //shared_ptr < string > name =
	    //  (patchName == NULL) ? measureRGB.toString() : patchName;

	    if (!titleTouched) {
		//如果title沒被設定過
		if (titleNote != NULL) {
		    //measureWindow.setTitle("Measure Window " + titleNote);
		    /*measureWindow->Caption =
		       AnsiString("Measure Window " + titleNote); */

		} else {
		    //measureWindow.setTitle("Measure Window");
		    measureWindow->Caption = AnsiString("Measure Window");
		}
		/*measureWindow.setNorthLabel1(name + "   " +
		   rgb.toString() + "   " +
		   titleNote); */
	    }
	    //設定好顏色
	    /*Color c =
	       this.isCPCodeLoading()? this.cpBackground : background;
	       measureWindow.setBackground(c); */
	    //measureWindow.setColor(measureRGB.getColor());
	    measureWindow->setRGB(measureRGB);

	    //==========================================================================
	    // 變換完視窗顏色的短暫停留
	    //==========================================================================
	    if (!fakeMeasure) {
		Sleep(waitTimes);
	    }
	    //==========================================================================

	    /*if (meter instanceof DummyMeter) {
	       //如果是dummy, 就直接指定RGB, 由dummy轉換成XYZ
	       ((DummyMeter) meter).setRGB(measureRGB);
	       } */

	    if (true == measureWindowClosing) {
		//如果視窗被關閉, 就結束量測
		//return shared_ptr < Patch > ((Patch *) NULL);
	    }
	    shared_array < double >result =
		meter->triggerMeasurementInXYZ();

	    /*String measureString = getMeasureString(result);
	       measureWindow.setNorthLabel3(measureString +
	       (softCalibrate ?
	       (" (" +
	       DoubleArray.
	       toString(unSoftCalXYZValues)
	       + " )") : ""));
	       if (informationProvider != null) {
	       String info = informationProvider.getInformation();
	       measureWindow.setSouthLabel(info);
	       }
	       if (timeNote != null) {
	       measureWindow.setNorthLabel2(timeNote);
	       } */
	    shared_ptr < cms::colorspace::CIEXYZ >
		XYZ(new cms::colorspace::CIEXYZ(result));
	    shared_ptr < Patch >
		patch(new Patch(patchName, XYZ, XYZ, measureRGB));
	    return patch;
	};
	void MeasureUtils::
	    meterCalibrate(MeterMeasurement & meterMeasurement) {
	    shared_ptr < Meter > meter = meterMeasurement.meter;
	    TMeasureWindow *measureWindow = meterMeasurement.measureWindow;
	    meterCalibrate( /*measureWindow, */ meter,
			   measureWindow);
	};
	void MeasureUtils::meterCalibrate(	/*Component parentComponent, */
					     shared_ptr
					     <
					     Meter
					     >
					     meter,
					     TMeasureWindow
					     * measureWindow) {
	    if (!meter->isConnected()) {
		throw java::lang::
		    IllegalStateException("!meter.isConnected()");
	    } else {
		if (measureWindow != NULL) {
		    //show出黑幕, 避免影響校正
		    //measureWindow.setColor(Color.black);
		    measureWindow->setRGB(0, 0, 0);
		    measureWindow->Visible = true;
		}
		//string s = meter->getCalibrationDescription();
		AnsiString(meter->getCalibrationDescription()->c_str());
		/*ShowMessage(AnsiString
		   ((*meter.getCalibrationDescription()).
		   c_str())); */
		meter->calibrate();
		if (measureWindow != NULL) {
		    //關閉黑幕
		    //measureWindow.setVisible(false);
		    measureWindow->Visible = false;
		}
		ShowMessage(AnsiString("End of calibration"));
		/*JOptionPane.showMessageDialog(parentComponent,
		   "End of calibration",
		   "End of calibration",
		   JOptionPane.
		   INFORMATION_MESSAGE); */
	    };
	};
    };
};

