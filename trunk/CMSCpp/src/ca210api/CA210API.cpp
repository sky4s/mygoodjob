#include "CA210API.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <util.h>

namespace ca210api {
    using namespace boost;
    using namespace std;

    //==========================================================================
     MeasureResult::MeasureResult() {
    };
    MeasureResult::MeasureResult(float x, float y, float Lv, float X,
				 float Y, float Z, long cct,
				 float duv):x(x), y(y), Lv(Lv), X(X), Y(Y),
	Z(Z), cct(cct), duv(duv) {
    };
    float_array MeasureResult::getxyYValues() {
	float_array result(new float[3]);
	result[0] = x;
	result[1] = y;
	result[2] = Y;
	return result;
    };
    float_array MeasureResult::getXYZValues() {
	float_array result(new float[3]);
	result[0] = X;
	result[1] = Y;
	result[2] = Z;
	return result;
    };
    //==========================================================================


    CA210API::CA210API() {
	ca200.BindDefault();
	ca200.AutoConnect();
	ca = ca200.get_SingleCa();
	probe = ca.get_SingleProbe();
	memory = ca.get_Memory();
    };
    void CA210API::calibrate() {
	ca.CalZero();
    };

    void CA210API::close() {

    };
    shared_array < float >CA210API::triggerMeasurement() {
	shared_ptr < MeasureResult > result = this->triggerMeasureResult();
	shared_array < float >measureValues(new float[3]);
	measureValues[0] = result->X;
	measureValues[1] = result->Y;
	measureValues[2] = result->Z;
	return measureValues;
    };
    shared_ptr < MeasureResult > CA210API::triggerMeasureResult() {
	ca.Measure(0);
	float x = probe.get_sx();
	float y = probe.get_sy();
	float Lv = probe.get_Lv();
	float X = probe.get_X();
	float Y = probe.get_Y();
	float Z = probe.get_Z();
	long cct = probe.get_T();
	float duv = probe.get_duv();
	//MeasureResult result(x, y, Lv, X, Y, Z, cct, duv);
	shared_ptr < MeasureResult >
	    result(new MeasureResult(x, y, Lv, X, Y, Z, cct, duv));
	return result;
    };

    // Options
    void CA210API::setSyncMode(SyncMode mode) {
	ca.set_SyncMode(mode);
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
	ca.set_RemoteMode(mode);
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
    void CA210API::setLvxyCalData(lClr lclr, float xValue, float yValue,
				  float YValue) {
	ca.SetLvxyCalData(lclr, xValue, yValue, YValue);
    };

    void CA210API::setLvxyCalData(lClr lclr,
				  shared_array < float >xyYValue) {
	ca.SetLvxyCalData(lclr, xyYValue[0], xyYValue[1], xyYValue[2]);
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

    void CA210API::setChannelID(string & id) {
	memory.SetChannelID(util::Util::towchar_t(id).get());
	//memory.SetChannelID(id);
    };
    wchar_t *CA210API::getChannelID() {
	wchar_t *channelID = memory.get_ChannelID();
	return channelID;
    };
};

