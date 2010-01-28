#ifndef METERMEASUREMENTH
#define METERMEASUREMENTH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include "TMeasureWindow.h"

namespace cms {
    class Patch;
    namespace measure {

	namespace meter {
	    class Meter;
	};
    };
};

namespace cms {
    namespace measure {
	class MeterMeasurement;
	class MeasureUtils {
	  public:
	    static void meterCalibrate(MeterMeasurement &
				       meterMeasurement);

	    static void meterCalibrate(	/*Component parentComponent, */
					  boost::shared_ptr <
					  cms::measure::
					  meter::Meter > meter,
					  TMeasureWindow * measureWindow);
	};


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
	     boost::shared_ptr < cms::measure::meter::Meter > meter;
	    TMeasureWindow *measureWindow;
	  public:
	     MeterMeasurement(boost::shared_ptr <
			      cms::measure::meter::Meter > meter,
			      bool calibration);

	    void calibrate();

	    void close();

	    void setMeasureWindowsVisible(bool visible);

	     boost::shared_ptr < cms::Patch >
		measure(boost::shared_ptr < cms::colorspace::RGBColor >
			rgb, boost::shared_ptr < std::string > patchName);

	     boost::shared_ptr < cms::Patch >
		measure(int r, int g, int b, std::string patchName);

	    void setBlankTimes(int blankTimes);
	    void setWaitTimes(int waitTimes);
	    void setFakeMeasure(bool fake);
	    bool isFakeMeasure();

	  protected:
	    void meterClose();

	     boost::shared_ptr < cms::Patch >
		measure0(boost::shared_ptr < cms::colorspace::RGBColor >
			 measureRGB,
			 boost::shared_ptr < std::string > patchName,
			 boost::shared_ptr < std::string > titleNote,
			 boost::shared_ptr < std::string > timeNote);



	};


    };
};
#endif

