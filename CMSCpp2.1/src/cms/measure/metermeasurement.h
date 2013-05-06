#ifndef METERMEASUREMENTH
#define METERMEASUREMENTH

//C�t�Τ��

//C++�t�Τ��
#include <vector>

//��L�w�Y���

//�����ؤ��Y���
#include <gui/TMeasureWindow.h>
#include <gui/event/listener.h>
#include "meter.h"

namespace cms {
    namespace measure {
	class MeterMeasurement;
	class MeasureUtils {
	  public:
	    static void meterCalibrate(MeterMeasurement & meterMeasurement);

	    static void meterCalibrate(boost::shared_ptr < cms::measure::meter::Meter > meter,
				       TMeasureWindow * measureWindow);
	};
	//Enumeration(FakeMode)
	//None, Component, Patch EnumerationEnd()

	 Enumeration(FlickerMode)
	 FMA, JEITA EnumerationEnd()

	class MeterMeasurement {
	    friend class MeasureUtils;
	  public:
	    static const int DefaultWaitTimes = 400;
	    static const int DefaultBlankTimes = 0;
	  private:
	    int waitTimes;
	    int blankTimes;
	    RGB_ptr blankRGB;
	    bool measureWindowClosing;
	    bool titleTouched;
	    int averageTimes;
	    Patch_vector_ptr measurePatchVector;
	    FakeMode fakeMode;
	    FlickerMode flicker;
	    RGB_vector_ptr measureRequest;
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

	    //measure�Ѷq��bit�ƨM�w�OAG0/AG2
	    Patch_ptr measure(const string_ptr patchName);
	    Patch_ptr measure(RGB_ptr rgb, const string_ptr patchName);
	    Patch_ptr measure(int r, int g, int b, const string_ptr patchName);
	    Patch_ptr measure(int r, int g, int b, const std::string & patchName);
	    Patch_ptr measureFlicker(RGB_ptr rgb, const string_ptr patchName);
	    Patch_ptr measureFlicker(const string_ptr patchName);


	    void pushMeasureRequest(RGB_ptr rgb);
	    void pushMeasureRequest(RGB_vector_ptr measureVector);
	    void clearMeasureRequest();
	    //pullMeasureResult�@�v�HAG1�B��
	    Patch_vector_ptr pullMeasureResult();



	    __property int WaitTimes = { read = waitTimes, write = waitTimes };
	    __property int BlankTimes = { write = blankTimes };
	    __property RGB_ptr BlankRGB = { write = blankRGB };
	    /*
	       fake�����,..Orz
	       �u��Component��->�u��q��Component
	       ��MeasurePatchVector->����������

	       �p��Ϥ����fake measure?
	     */
	    __property FakeMode FakeMeasureMode = { read = fakeMode };
	    __property FlickerMode Flicker = { write = flicker };
	    __property int AverageTimes = { read = averageTimes, write = averageTimes };
	    __property Patch_vector_ptr MeasurePatchVector = { read = measurePatchVector };
	     bptr < cms::measure::meter::Meter > getMeter();
	    bool doExtraMeasure();
	  protected:
	    void meterClose();

	    //measure0�p�G�baging mode, �Ѷq��bit�ƨM�w�OAG0/AG2
	    Patch_ptr measure0(RGB_ptr
			       measureRGB,
			       const string_ptr patchName,
			       const string_ptr titleNote, string_ptr timeNote, bool flicker,
			       bool noPattern);



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
	    bool inverseMeasure;
	    bool isAgingMode();
	  public:
	     MeasureTool(bptr < cms::measure::MeterMeasurement > mm);
	    Patch_vector_ptr rampMeasure(const Dep::Channel & channel,
					 bptr <
					 cms::lcd::calibrate::MeasureCondition > measureCondition);
	    Patch_vector_ptr rampMeasure(const Dep::Channel & channel, int_vector_ptr background,
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
	    __property bool InverseMeasure = { write = inverseMeasure
	    };
	};



    };
};
#endif

