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
	//const int MeterMeasurement::DefaultWaitTimes = 300;
	//const int MeterMeasurement::DefaultBlankTimes = 17;

	void MeterMeasurement::init(bool calibration) {
	    /*if (MeasureWindow == null) {
	       Application->CreateForm(__classid(TMeasureWindow),
	       &MeasureWindow);
	       } */
	    measureWindow = MeasureWindow;
	    if (true == calibration) {
		calibrate();
	    }
	};
      MeterMeasurement::MeterMeasurement(shared_ptr < Meter > meter, bool calibration):meter(meter), waitTimes(meter->getSuggestedWaitTimes()),
	    measureWindowClosing(false), titleTouched(false),
	    fakeMeasure(false) {
	    /*, tconinput(false) */

	    init(calibration);
	};

	/*MeterMeasurement::MeterMeasurement(bptr < cms::measure::meter::Meter > meter, bptr < cms::i2c::TCONControl > tconcontrol, bool calibration):meter(meter),
	   tconcontrol(tconcontrol),
	   waitTimes(meter->getSuggestedWaitTimes()),
	   measureWindowClosing(false), titleTouched(false),
	   fakeMeasure(false), tconinput(true) {

	   init(calibration);
	   }; */

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
		/*if (tconinput) {
		   this->tconcontrol->setGammaTest(visible);
		   } else { */
		if (null == measureWindow) {
		    measureWindow = MeasureWindow;
		}
		measureWindow->setVisible(visible);
		measureWindowClosing = !visible;
		//}

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
	int MeterMeasurement::getWaitTimes() {
	    return waitTimes;
	};
	void MeterMeasurement::setFakeMeasure(bool fake) {
	    this->fakeMeasure = fake;
	};
	bool MeterMeasurement::isFakeMeasure() {
	    return fakeMeasure;
	};

	/*bptr < MeasureInterface > MeterMeasurement::getMeasureInterface() {
	   class MI:public MeasureInterface {
	   public:
	   virtual      bptr < MeasureResult >
	   measureResult(RGB_vector_ptr rgbVec, bool forceTrigger,
	   bool trigger) {
	   using namespace cms::measure;

	   int size = rgbVec->size();
	   Patch_vector_ptr result(new Patch_vector());

	   foreach(RGB_ptr rgb, *rgbVec) {
	   Patch_ptr p = measure(rgb);
	   result->push_back(p);
	   };

	   bptr < MeasureResult >
	   measureResult(new MeasureResult(result, size));
	   return measureResult;
	   };

	   virtual      Patch_ptr measure(RGB_ptr rgb, bool forceTrigger,
	   bool trigger) {
	   this->measure(rgb);
	   };
	   virtual      Patch_ptr measure(RGB_ptr rgb) {
	   return mm->measure(rgb, rgb->toString());
	   };
	   virtual      void reset() {
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
	   }; */

	bptr < cms::measure::meter::Meter > MeterMeasurement::getMeter() {
	    return meter;
	};

	/*void MeterMeasurement::setTCONControl(bptr <
	   cms::i2c::TCONControl >
	   tconcontrol) {
	   //this->tconcontrol = tconcontrol;
	   //tconinput = true;
	   measureWindow->setTCONControl(tconcontrol);;
	   };

	   void MeterMeasurement::setTCONControlOff() {
	   //tconinput = false;
	   measureWindow->setTCONControlOff();
	   }; */

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
		measureWindow->setRGB(measureRGB);
		Application->ProcessMessages();
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
    };
};

