#include <includeall.h>
#pragma hdrstop
#include "CA210API.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace ca210api {
    using namespace boost;
    using namespace std;

    //==========================================================================
     CAMeasureResult::CAMeasureResult() {
    };
    CAMeasureResult::CAMeasureResult(float x, float y, float Lv, float X,
				     float Y, float Z, long cct,
				     float duv):x(x), y(y), Lv(Lv), X(X),
	Y(Y), Z(Z), cct(cct), duv(duv) {
    };
    CAMeasureResult::CAMeasureResult(float x, float y, float Lv, float X,
				     float Y, float Z, long cct,
				     float duv, float R, float G,
				     float B):x(x), y(y), Lv(Lv), X(X),
	Y(Y), Z(Z), cct(cct), duv(duv), R(R), G(G), B(B) {
    };

    float_array CAMeasureResult::getxyYValues() {
	float_array result(new float[3]);
	result[0] = x;
	result[1] = y;
	result[2] = Y;
	return result;
    };
    float_array CAMeasureResult::getXYZValues() {
	float_array result(new float[3]);
	result[0] = X;
	result[1] = Y;
	result[2] = Z;
	return result;
    };
    //==========================================================================


    CA210API::CA210API() {
	//try {
	enable = false;

	result = ca200.BindDefault();
	ca200.AutoConnect();
	ca = ca200.get_SingleCa();
	probe = ca.get_SingleProbe();
	memory = ca.get_Memory();
	enable = true;
	/*}
	   catch(EOleException & ex) {
	   enable = false;
	   } */
    };
    CA210API::~CA210API() {
	close();
    }
    void CA210API::calibrate() {
	ca.CalZero();
    };

    void CA210API::close() {
	ca.set_RemoteMode(Off);
    };
    float_array CA210API::triggerMeasurement() {
	ca.set_DisplayMode(Lvxy);
	ca.Measure(0);
	float_array measureValues(new float[3]);

	measureValues[0] = probe.get_X();
	measureValues[1] = probe.get_Y();
	measureValues[2] = probe.get_Z();
	return measureValues;
    };
    bptr < CAMeasureResult > CA210API::triggerMeasureResult() {
	//=====================================================================
	// XYZ
	//=====================================================================
	ca.set_DisplayMode(Lvxy);
	ca.Measure(0);

	float x = probe.get_sx();
	float y = probe.get_sy();
	float Lv = probe.get_Lv();
	float X = probe.get_X();
	float Y = probe.get_Y();
	float Z = probe.get_Z();
	long cct = probe.get_T();
	float duv = probe.get_duv();
	//=====================================================================

	//=====================================================================
	// Analyze
	//=====================================================================
	ca.set_DisplayMode(Analyzer_nodisplay);
	ca.Measure(0);
	float R = probe.get_R();
	float G = probe.get_G();
	float B = probe.get_B();
	//=====================================================================

	measureResult = bptr < CAMeasureResult >
	    (new CAMeasureResult(x, y, Lv, X, Y, Z, cct, duv, R, G, B));
	return measureResult;
    };

    float_array CA210API::triggerIntensityAnalyze() {
	ca.set_DisplayMode(Analyzer_nodisplay);
	ca.Measure(0);


	float_array measureValues(new float[3]);
	measureValues[0] = probe.get_R();
	measureValues[1] = probe.get_G();
	measureValues[2] = probe.get_B();
	return measureValues;
    };

    float CA210API::triggerFlickerJEITA() {
	ca.set_DisplayMode(JEITAflicker);
	ca.Measure(0);
	return probe.get_FlckrJEITA();
    };

    float CA210API::triggerFlickerFMA() {
	ca.set_DisplayMode(FMAflicker);
	ca.Measure(0);
	return probe.get_FlckrFMA();
    };

    bptr < CAMeasureResult > CA210API::getMeasureResult() {
	return measureResult;
    };

    // Options
    void CA210API::setSyncMode(SyncMode mode) {
	ca.set_SyncMode(mode);
    };
    void CA210API::setSyncHz(int hz) {
	ca.set_SyncMode(hz);
    };
    void CA210API::setAveragingMode(AveragingMode mode) {
	ca.set_AveragingMode(mode);
    };

    void CA210API::setBrightnessUnit(BrightnessUnit unit) {
	ca.set_BrightnessUnit(unit);
    };
    void CA210API::setDisplayMode(DisplayMode mode) {
	ca.set_DisplayMode(mode);
    };

    void CA210API::setDisplayDigits(DisplayDigits digits) {
	ca.set_DisplayDigits(digits);
    };
    void CA210API::setCalStandard(CalStandard standard) {
	ca.set_CalStandard(standard);
    };
    void CA210API::setRemoteMode(RemoteMode mode) {
	if (enable) {
	    ca.set_RemoteMode(mode);
	}
    };

    // Analyzer Mode
    void CA210API::setAnalyzerCalMode() {
	ca.SetAnalyzerCalMode();
    };
    void CA210API::resetAnalyzerCalMode() {
	ca.ResetAnalyzerCalMode();
    };

    void CA210API::setAnalyzerCalData(lClr lclr) {
	ca.SetAnalyzerCalData(lclr);
    };
    void CA210API::setLvxyCalMode() {
	ca.SetLvxyCalMode();
    };
    void CA210API::resetLvxyCalMode() {
	ca.ResetLvxyCalMode();
    };
    void CA210API::setLvxyCalData(lClr lclr, float xValue, float yValue, float YValue) {
	ca.SetLvxyCalData(lclr, xValue, yValue, YValue);
    };

    void CA210API::setLvxyCalData(lClr lclr, float_array xyYValue) {
	ca.SetLvxyCalData(lclr, xyYValue[0], xyYValue[1], xyYValue[2]);
    };

    void CA210API::setLvxyCalData(lClr lclr, double_array xyYValue) {
	ca.SetLvxyCalData(lclr, (float) xyYValue[0], (float) xyYValue[1], (float) xyYValue[2]);
    };

    long CA210API::enter() {
	return ca.Enter();
    };

    // Channel NO
    void CA210API::setChannelNO(int no) {
	memory.set_ChannelNO(no);
    };

    long CA210API::getChannelNO() {
	return memory.get_ChannelNO();
    };
    // channel ID
    void CA210API::setChannelID(wchar_t * id) {
	memory.SetChannelID(id);
    };

    void CA210API::setChannelID(const WideString & id) {
	memory.SetChannelID(id);
    };

    wchar_t *CA210API::getChannelID() {
	wchar_t *channelID = memory.get_ChannelID();
	return channelID;
    };

    void CA210API::copyToFile(const WideString & filename) {
	memory.CopyToFile(probe.Number, filename);
    };
    void CA210API::copyFromFile(const WideString & filename) {
	memory.CopyFromFile(probe.Number, filename);
    };
    xyY_ptr CA210API::getReferenceColor() {
	using namespace Indep;
	float x = 0, y = 0, Y = 0;
	memory.GetReferenceColor(memory.get_ChannelID(), &x, &y, &Y);
	xyY_ptr xyY(new CIExyY(x, y, Y));
	return xyY;
    };
};

