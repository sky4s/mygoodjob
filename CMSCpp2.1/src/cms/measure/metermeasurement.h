#ifndef METERMEASUREMENTH
#define METERMEASUREMENTH

//C系統文件

//C++系統文件
#include <vector>

//其他庫頭文件

//本項目內頭文件
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
	    void init(bool calibration);
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
	    int getWaitTimes();
	    void setFakeMeasure(bool fake);
	    bool isFakeMeasure();

	     bptr < cms::measure::meter::Meter > getMeter();

	  protected:
	    void meterClose();

	    Patch_ptr measure0(RGB_ptr
			       measureRGB,
			       const string_ptr patchName,
			       const string_ptr titleNote,
			       string_ptr timeNote);



	};
	//using namespace std;
	class MeasureResult {
	  public:
	    Patch_vector_ptr result;
	    int practicalMeasureCount;
	     MeasureResult(Patch_vector_ptr result,
			   int practicalMeasureCount);
	};

	class MeasureTool:public cms::util::WindowListener {
	  private:
	    bool stop;
	    bptr < cms::measure::MeterMeasurement > mm;
	  public:
	    MeasureTool(bptr < cms::measure::MeterMeasurement > mm);
	    Patch_vector_ptr rampMeasure(const Dep::Channel & channel,
					 int start, int end, int step);
	    Patch_vector_ptr rampMeasure(const Dep::Channel & channel,
					 bptr <
					 cms::lcd::calibrate::
					 MeasureCondition >
					 measureCondition);
	    Patch_vector_ptr rampMeasure(const Dep::
					 Channel & channel,
					 RGB_vector_ptr rgbMeasureCode);
	    Patch_vector_ptr rampMeasure(RGB_vector_ptr rgbMeasureCode);
	    void windowClosing();
	};



    };
};
#endif

