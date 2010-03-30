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

	 MeterMeasurement::MeterMeasurement(shared_ptr < Meter >
					    meter,
					    bool calibration):meter(meter),
	    waitTimes(meter->getSuggestedWaitTimes()),
	    measureWindowClosing(false), titleTouched(false),
	    fakeMeasure(false), tconinput(false) {
	    measureWindow = MeasureWindow;
	    if (true == calibration) {
		calibrate();
	    }
	};

      MeterMeasurement::MeterMeasurement(bptr < cms::measure::meter::Meter > meter, bptr < cms::i2c::TCONControl > tconcontrl, bool calibration):meter(meter),
	    tconcontrl(tconcontrl),
	    waitTimes(meter->getSuggestedWaitTimes()),
	    measureWindowClosing(false), titleTouched(false),
	    fakeMeasure(false), tconinput(true) {
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
		if (null == measureWindow) {
		    measureWindow = MeasureWindow;
		}
		measureWindow->Visible = visible;
		//measureWindow->ShowModal();
		measureWindowClosing = !visible;
	    }
	};

	Patch_ptr
	    MeterMeasurement::measure(RGB_ptr rgb,
				      const string_ptr patchName) {
	    return measure0(rgb, patchName, nil_string_ptr,
			    nil_string_ptr);
	};

	Patch_ptr MeterMeasurement::measure(int r, int g, int b,
					    const string_ptr patchName) {
	    RGB_ptr rgb(new RGBColor(r, g, b));
	    return measure(rgb, patchName);
	};

	Patch_ptr MeterMeasurement::measure(int r, int g, int b,
					    const string & patchName) {
	    string_ptr str(new string(patchName));
	    RGB_ptr rgb(new RGBColor(r, g, b));
	    return measure(rgb, str);
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

	bptr < MeasureInterface > MeterMeasurement::getMeasureInterface() {
	    class MI:public MeasureInterface {
	      public:
		bptr < MeasureResult >
		    measureResult(RGB_vector_ptr rgbVec, bool forceTrigger,
				  bool trigger) {
		    int size = rgbVec->size();

		};

		Patch_ptr measure(RGB_ptr rgb, bool forceTrigger,
				  bool trigger) {
		    this->measure(rgb);
		};
		Patch_ptr measure(RGB_ptr rgb) {
		    return mm->measure(rgb, rgb->toString());
		};
		void reset() {
		};

	      private:
		friend class MeterMeasurement;
		MeterMeasurement *mm;
	      MI(MeterMeasurement * mm):mm(mm) {
		};
	    };
	    return bptr < MeasureInterface > (dynamic_cast <
					      MeasureInterface *
					      >(new MI(this)));
	};

	bptr < cms::measure::meter::Meter > MeterMeasurement::getMeter() {
	    return meter;
	};

	void MeterMeasurement::meterClose() {
	    //meter->close();
	};

	Patch_ptr
	    MeterMeasurement::measure0(RGB_ptr measureRGB,
				       string_ptr patchName,
				       string_ptr titleNote,
				       string_ptr timeNote) {
	    setMeasureWindowsVisible(true);
	    //量測的顏色, 量測的顏色可能與導具的顏色不同, 所以特別獨立出此變數
	    //final RGB measureRGB = processInverseRGB(rgb);
	    //string_ptr name =
	    //  (patchName == NULL) ? measureRGB.toString() : patchName;

	    if (!titleTouched) {
		//如果title沒被設定過
		if (titleNote != NULL) {
		    //measureWindow.setTitle("Measure Window " + titleNote);
		    /*measureWindow->Caption =
		       AnsiString("Measure Window " + titleNote); */

		} else {
		    measureWindow->Caption = AnsiString("Measure Window");
		}
		/*measureWindow.setNorthLabel1(name + "   " +
		   rgb.toString() + "   " +
		   titleNote); */
	    }
	    //==========================================================================
	    // 變換完視窗顏色的短暫停留
	    //==========================================================================
	    if (!fakeMeasure) {
		if (tconinput) {
		    const MaxValue & maxValue = measureRGB->getMaxValue();
		    RGB_ptr testRGB = measureRGB->clone();
		    if (maxValue == MaxValue::Int10Bit
			|| maxValue == MaxValue::RealInt10Bit) {
			testRGB->R *= 4;
			testRGB->G *= 4;
			testRGB->B *= 4;
		    } else {
			testRGB->R *= 16;
			testRGB->G *= 16;
			testRGB->B *= 16;
		    }
		    tconcontrl->setTestRGB(testRGB);
		} else {
		    measureWindow->setRGB(measureRGB);
		}
		Sleep(waitTimes);
	    }
	    //==========================================================================

	    if (true == measureWindowClosing) {
		//如果視窗被關閉, 就結束量測
		return Patch_ptr((Patch *) NULL);
	    }
	    double_array result = meter->triggerMeasurementInXYZ();

	    XYZ_ptr XYZ(new Indep::CIEXYZ(result));
	    Patch_ptr patch(new Patch(patchName, XYZ, XYZ, measureRGB));
	    return patch;
	};
	void MeasureUtils::
	    meterCalibrate(MeterMeasurement & meterMeasurement) {
	    shared_ptr < Meter > meter = meterMeasurement.meter;
	    TMeasureWindow *measureWindow = meterMeasurement.measureWindow;
	    meterCalibrate( /*measureWindow, */ meter,
			   measureWindow);
	};
	void MeasureUtils::meterCalibrate(shared_ptr < Meter > meter,
					  TMeasureWindow * measureWindow) {
	    if (!meter->isConnected()) {
		throw IllegalStateException("!meter.isConnected()");
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
		if (measureWindow != null) {
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

	MeasureResult::MeasureResult(Patch_vector_ptr result,
				     int practicalMeasureCount):result
	    (result), practicalMeasureCount(practicalMeasureCount) {

	};
    };
};

