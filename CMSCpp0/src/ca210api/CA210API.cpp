#include "CA210API.h"

ca210api::CA210API::CA210API()
{
    ca200.BindDefault();
    ca200.AutoConnect();
    ca = ca200.get_SingleCa();
    probe = ca.get_SingleProbe();
}

void ca210api::CA210API::calibrate()
{
    ca.CalZero();
}

void ca210api::CA210API::close()
{

}

float *ca210api::CA210API::triggerMeasurement()
{
    ca.Measure(0);
    float X = probe.get_X();
    float Y = probe.get_Y();
    float Z = probe.get_Z();
    measureValues[0] = X;
    measureValues[1] = Y;
    measureValues[2] = Z;
    //float result[3];
    return measureValues;
}

