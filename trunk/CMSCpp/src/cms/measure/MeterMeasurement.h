#ifndef METERMEASUREMENTH
#define METERMEASUREMENTH
#include "meter.h"
#include "TMeasureWindow.h"
#include <java/lang.h>
#include <string>
#include <cms/colorspace/depend.h>
#include <cms/core.h>
#include <cms/patch.h>

namespace cms {
    namespace measure {
	using cms::measure::meter::Meter;
	using namespace cms::colorspace;
	using cms::Patch;

	class MeterMeasurement {
	    friend class MeasureUtils;
	  public:
	    static const int DefaultWaitTimes = 300;
	    static const int DefaultBlankTimes = 17;
	  private:
	    int waitTimes;
	    int blankTimes;
	    bool measureWindowClosing;
	    bool titleTouched;
	    bool fakeMeasure;
	  protected:
	     Meter & meter;
	    TMeasureWindow *measureWindow;
	  public:
	     MeterMeasurement(Meter & meter,
			      bool calibration):meter(meter),
		waitTimes(meter.getSuggestedWaitTimes()),
		measureWindowClosing(false), titleTouched(false),
		fakeMeasure(false) {
		//this(meter, null, 0, calibration);
		measureWindow = MeasureWindow;
		if (true == calibration) {
		    calibrate();
		}
	    };

	    void calibrate() {
		meterCalibrate(*this);
	    };

	    void close() {
		setMeasureWindowsVisible(false);
		measureWindow->Close();
		meterClose();
	    };

	    void setMeasureWindowsVisible(boolean visible) {
		if (!fakeMeasure) {
		    measureWindow->Visible = visible;
		    measureWindowClosing = !visible;
		}
	    };

	    shared_ptr < Patch > measure(RGBColor & rgb,
					 string & patchName) {
		//return measure0(rgb, patchName, null, null);
	    };

	    void setBlankTimes(int blankTimes) {
		this->blankTimes = blankTimes;
	    };
	    void setWaitTimes(int waitTimes) {
		this->waitTimes = waitTimes;
	    };
	    void setFakeMeasure(bool fake) {
		this->fakeMeasure = fake;
	    };
	    bool isFakeMeasure() {
		return fakeMeasure;
	    };

	    static void meterCalibrate(MeterMeasurement & meterMeasurement) {
		Meter & meter = meterMeasurement.meter;
		TMeasureWindow *measureWindow =
		    meterMeasurement.measureWindow;
		meterCalibrate( /*measureWindow, */ meter, measureWindow);
	    };

	    static void meterCalibrate(	/*Component parentComponent, */
					  Meter & meter,
					  TMeasureWindow * measureWindow) {
		if (!meter.isConnected()) {
		    throw java::lang::
			IllegalStateException("!meter.isConnected()");
		} else {
		    if (measureWindow != NULL) {
			//show出黑幕, 避免影響校正
			//measureWindow.setColor(Color.black);
			measureWindow->setRGB(0, 0, 0);
			measureWindow->Visible = true;
		    }
		    std::string s = *meter.getCalibrationDescription();

		    ShowMessage(AnsiString
				((*meter.getCalibrationDescription()).
				 c_str()));
		    /*JOptionPane.showMessageDialog(parentComponent,
		       meter.
		       getCalibrationDescription
		       (), "Calibration",
		       JOptionPane.
		       INFORMATION_MESSAGE); */
		    meter.calibrate();

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

	  protected:
	    void meterClose() {
		meter.close();
	    };

	    shared_ptr < Patch > measure0(RGBColor & measureRGB,
					  shared_ptr < string > patchName,
					  shared_ptr < string > titleNote,
					  shared_ptr < string > timeNote) {
		setMeasureWindowsVisible(true);
		//量測的顏色, 量測的顏色可能與導具的顏色不同, 所以特別獨立出此變數
		//final RGB measureRGB = processInverseRGB(rgb);

		shared_ptr < string > name =
		    (patchName ==
		     NULL) ? measureRGB.toString() : patchName;
		if (!titleTouched) {
		    //如果title沒被設定過
		    if (titleNote != NULL) {
			//measureWindow.setTitle("Measure Window " + titleNote);
			/*measureWindow->Caption =
			   AnsiString("Measure Window " + titleNote); */

		    } else {
			//measureWindow.setTitle("Measure Window");
			measureWindow->Caption =
			    AnsiString("Measure Window");
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
		    return shared_ptr < Patch > (NULL);
		}
		shared_array < double >result =
		    meter.triggerMeasurementInXYZ();

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
		shared_ptr < CIEXYZ > XYZ(new CIEXYZ(result));
		/*shared_ptr < Patch >
		   patch(new Patch(name, XYZ, null, rgb));
		   return patch; */
		return shared_ptr < Patch > (NULL);
	    };
	};



    };
};

#endif

