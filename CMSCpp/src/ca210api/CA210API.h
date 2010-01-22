//---------------------------------------------------------------------------
#ifndef CA210APIH
#define CA210APIH
//---------------------------------------------------------------------------
#include "CA200SRVRLib/CA200SRVRLib_TLB.h"

//---------------------------------------------------------------------------

namespace ca210api {
    class MeasureResult {
      public:

	float x, y, Lv;
	float X, Y, Z;
	long cct;
	float duv;
	 MeasureResult() {
	};
	 MeasureResult(float x, float y, float Lv, float X, float Y,
		       float Z, long cct, float duv):x(x), y(y), Lv(Lv),
	    X(X), Y(Y), Z(Z), cct(cct), duv(duv) {

	};

	enum SyncMode { NTSC = 0, PAL, EXT, UNIV
	};
	enum AveragingMode { Slow = 0, Fast, Auto
	};
	enum BrightnessUnit { fL = 0, nits
	};
	enum DisplayMode { Lvxy =
		0, Tdudv, Analyzer_nodisplay, AnalyzerG, AnalyzerR, uv,
	    FMAflicker, XYZ, JEITAflicker
	};
	enum DisplayDigits { Display3digit = 0, Display4digit
	};
	enum CalStandard { D6500k = 0, D9300k
	};
	enum RemoteMode { Off = 0, On, Locked
	};
	enum lClr { Red = 0, Green, Blue, White
	};

	class CA210API {
	  private:
	    ICa200Disp ca200;
	    ICaDisp ca;
	    IProbeDisp probe;
	    IMemoryDisp memory;
	    float measureValues[3];

	  public:
	     CA210API() {
		ca200.BindDefault();
		ca200.AutoConnect();
		ca = ca200.get_SingleCa();
		probe = ca.get_SingleProbe();
		memory = ca.get_Memory();
	    };
	    void calibrate() {
		ca.CalZero();
	    };

	    void close() {

	    };
	    float *triggerMeasurement() {
		MeasureResult result = this->getMeasureResult();
		measureValues[0] = result.X;
		measureValues[1] = result.Y;
		measureValues[2] = result.Z;
		return measureValues;
	    };
	    MeasureResult getMeasureResult() {
		ca.Measure(0);
		float x = probe.get_sx();
		float y = probe.get_sy();
		float Lv = probe.get_Lv();
		float X = probe.get_X();
		float Y = probe.get_Y();
		float Z = probe.get_Z();
		long cct = probe.get_T();
		float duv = probe.get_duv();
		MeasureResult result(x, y, Lv, X, Y, Z, cct, duv);
		return result;
	    };

	    // Options
	    void setSyncMode(SyncMode mode) {
		ca.set_SyncMode(mode);
	    };
	    void setAveragingMode(AveragingMode mode) {
		ca.set_AveragingMode(mode);
	    };

	    void setBrightnessUnit(BrightnessUnit unit) {
		ca.set_BrightnessUnit(unit);
	    };
	    void setDisplayMode(DisplayMode mode) {
		ca.set_DisplayMode(mode);
	    };

	    void setDisplayDigits(DisplayDigits digits) {
		ca.set_DisplayDigits(digits);
	    };
	    void setCalStandard(CalStandard standard) {
		ca.set_CalStandard(standard);
	    };
	    void setRemoteMode(RemoteMode mode) {
		ca.set_RemoteMode(mode);
	    };

	    // Analyzer Mode
	    void CA210API::setAnalyzerCalMode() {
		ca.SetAnalyzerCalMode();
	    };
	    void resetAnalyzerCalMode() {
		ca.ResetAnalyzerCalMode();
	    };

	    void setAnalyzerCalData(lClr lclr) {
		ca.SetAnalyzerCalData(lclr);
	    };
	    void setLvxyCalMode() {
		ca.SetLvxyCalMode();
	    };
	    void resetLvxyCalMode() {
		ca.ResetLvxyCalMode();
	    };
	    void setLvxyCalData(lClr lclr, float xValue, float yValue,
				float YValue) {
		ca.SetLvxyCalData(lclr, xValue, yValue, YValue);
	    };

	    long enter() {
		return ca.Enter();
	    };

	    // Channel NO
	    void setChannelNO(int no) {
		memory.set_ChannelNO(no);
	    };

	    long getChannelNO() {
		return memory.get_ChannelNO();
	    };
	    // channel ID
	    void setChannelID(wchar_t * id) {
		memory.SetChannelID(id);
	    };
	    wchar_t *getChannelID() {
		wchar_t *channelID = memory.get_ChannelID();
		return channelID;
	    };




	};
    };
};
#endif

