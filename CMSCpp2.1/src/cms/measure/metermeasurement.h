#ifndef METERMEASUREMENTH
#define METERMEASUREMENTH

//C系統文件

//C++系統文件
#include <vector>

//其他庫頭文件

//本項目內頭文件
#include <gui/TMeasureWindow.h>
#include <gui/event/listener.h>

namespace cms {
    namespace measure {
	class MeterMeasurement;
	class MeasureUtils {
	  public:
	    static void meterCalibrate(MeterMeasurement & meterMeasurement);

	    static void meterCalibrate(boost::shared_ptr < cms::measure::meter::Meter > meter,
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
	    int averageTimes;
	    Patch_vector_ptr measurePatchVector;
	  protected:
	     bptr < cms::measure::meter::Meter > meter;
	    TMeasureWindow *measureWindow;
	    void init(bool calibration);
	  public:
	    void resetMeasurePatchVector();
	     MeterMeasurement(bptr < cms::measure::meter::Meter > meter, bool calibration);
	    void calibrate();
	    void close();
	    void setMeasureWindowsVisible(bool visible);

	    Patch_ptr measure(RGB_ptr rgb, const string_ptr patchName);
	    Patch_ptr measure(int r, int g, int b, const string_ptr patchName);
	    Patch_ptr measure(int r, int g, int b, const std::string & patchName);
	    Patch_ptr measureFlicker(RGB_ptr rgb, const string_ptr patchName);

	    __property int WaitTimes = { read = waitTimes, write = waitTimes };
	    __property int BlankTimes = { write = blankTimes };
	    __property bool FakeMeasure = { read = fakeMeasure, write = fakeMeasure };
	    __property int AverageTimes = { read = averageTimes, write = averageTimes };
	    __property Patch_vector_ptr MeasurePatchVector = { read = measurePatchVector };
	     bptr < cms::measure::meter::Meter > getMeter();
	    void setMeasurePatchVector(Patch_vector_ptr measurePatchVector);
	  protected:
	    void meterClose();

	    Patch_ptr measure0(RGB_ptr
			       measureRGB,
			       const string_ptr patchName,
			       const string_ptr titleNote, string_ptr timeNote, bool flicker);



	};
	class MeasureResult {
	  public:
	    Patch_vector_ptr result;
	    int practicalMeasureCount;
	     MeasureResult(Patch_vector_ptr result, int practicalMeasureCount);
	};

	class MeasureTool:public gui::event::WindowAdapter {
	  private:
	    bool stop;
	    bptr < cms::measure::MeterMeasurement > mm;
	  public:
	    MeasureTool(bptr < cms::measure::MeterMeasurement > mm);
	    Patch_vector_ptr rampMeasure(const Dep::Channel & channel,
					 bptr <
					 cms::lcd::calibrate::MeasureCondition > measureCondition);
	    Patch_vector_ptr rampMeasure(bptr < cms::lcd::calibrate::MeasureCondition >
					 measureCondition);
	    Component_vector_ptr flickerMeasure(bptr <
						cms::lcd::calibrate::
						MeasureCondition > measureCondition);
	    virtual void windowClosing(TObject * Sender, TCloseAction & Action);
	    int getMaxZDGCode(bptr < cms::lcd::calibrate::MeasureCondition > measureCondition);
	    static int getMaxZDGCode(bptr < cms::measure::MeterMeasurement > mm,
				     bptr < cms::lcd::BitDepthProcessor > bitDepth);
	    static int getMaxBIntensityRawGrayLevel(bptr < cms::measure::MeterMeasurement > mm,
						    bptr < cms::lcd::BitDepthProcessor > bitDepth);
	    static int getMaxBIntensityRawGrayLevel(bptr < cms::measure::MeterMeasurement > mm,
						    bptr < cms::lcd::BitDepthProcessor > bitDepth,
						    bptr < IntensityAnalyzerIF > analyzer);
	};



    };
};
#endif

