#include "CA210API.h"
using namespace ca210api;

CA210API::CA210API()
{
    ca200.BindDefault();
    ca200.AutoConnect();
    ca = ca200.get_SingleCa();
    probe = ca.get_SingleProbe();
    memory = ca.get_Memory();
}

void CA210API::calibrate()
{
    ca.CalZero();
}

void CA210API::close()
{

}

float *CA210API::triggerMeasurement()
{
    MeasureResult result = this->getMeasureResult();
    measureValues[0] = result.X;
    measureValues[1] = result.Y;
    measureValues[2] = result.Z;
    return measureValues;
}

void CA210API::setSyncMode(SyncMode mode)
{
    ca.set_SyncMode(mode);
}

void CA210API::setAveragingMode(AveragingMode mode)
{
    ca.set_AveragingMode(mode);
}

void CA210API::setBrightnessUnit(BrightnessUnit unit)
{
    ca.set_BrightnessUnit(unit);
}

void CA210API::setDisplayDigits(DisplayDigits digits)
{
    ca.set_DisplayDigits(digits);
}

void CA210API::setCalStandard(CalStandard standard)
{
    ca.set_CalStandard(standard);
}

void CA210API::setRemoteMode(RemoteMode mode)
{
    ca.set_RemoteMode(mode);
}

void CA210API::setDisplayMode(DisplayMode mode)
{
    ca.set_DisplayMode(mode);
}

MeasureResult ca210api::CA210API::getMeasureResult()
{
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
}

MeasureResult::MeasureResult()
{

}

MeasureResult::MeasureResult(float x, float y, float Lv, float X, float Y, float Z, long cct, float duv):x(x),
y(y), Lv(Lv), X(X), Y(Y), Z(Z), cct(cct),
duv(duv)
{

}


void CA210API::setChannelNO(int no)
{
    memory.set_ChannelNO(no);
}


long CA210API::enter()
{
    return ca.Enter();
}

long CA210API::getChannelNO()
{

    return memory.get_ChannelNO();
}

void CA210API::setChannelID(string id)
{
    //wstringstream s;
    //s << id;
    //memory.set_ChannelID(s.str().c_str());
}

string CA210API::getChannelID()
{
    wchar_t *channelID = memory.get_ChannelID();
    stringstream s;
    s << channelID;
    return s.str();
}

