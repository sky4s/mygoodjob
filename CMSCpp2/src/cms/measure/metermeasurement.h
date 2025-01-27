#ifndef METERMEASUREMENTH
#define METERMEASUREMENTH

//C系統文件

//C++系統文件
#include <vector>

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include <gui/TMeasureWindow.h>

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
	     bptr < cms::measure::meter::DGLutFileMeter > dgc;
	  protected:
	     bptr < cms::measure::meter::Meter > meter;
	    TMeasureWindow *measureWindow;
	  public:
	     MeterMeasurement(bptr < cms::measure::meter::Meter > meter,
			      bool calibration);

	    void calibrate();

	    void close();

	    void setMeasureWindowsVisible(bool visible);

	    Patch_ptr measure(RGB_ptr rgb, const string_ptr patchName);

	    Patch_ptr measure(int r, int g, int b,
			      const string_ptr patchName);
	    Patch_ptr measure(int r, int g, int b,
			      const std::string & patchName);

	    void setBlankTimes(int blankTimes);
	    void setWaitTimes(int waitTimes);
	    void setFakeMeasure(bool fake);
	    bool isFakeMeasure();

	     bptr < cms::measure::cp::MeasureInterface >
		getMeasureInterface();
	     bptr < cms::measure::meter::Meter > getMeter();


	  protected:
	    void meterClose();

	    Patch_ptr measure0(RGB_ptr
			       measureRGB,
			       const string_ptr patchName,
			       const string_ptr titleNote,
			       string_ptr timeNote);



	};
	using namespace std;
	class MeasureResult {
	  public:
	    Patch_vector_ptr result;
	    int practicalMeasureCount;
	     MeasureResult(Patch_vector_ptr result,
			   int practicalMeasureCount);
	};

    };
};
#endif

