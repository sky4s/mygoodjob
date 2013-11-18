/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)
 
 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts, 
 so only the following can be used for RX: 
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69
 
 Not all pins on the Leonardo support change interrupts, 
 so only the following can be used for RX: 
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).
 
 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example
 
 This example code is in the public domain.
 
 */
//#define DEBUG
//#define ITERACTION
#define BRIDGE
//#define CANVAS_WRAPPER

#include <SoftwareSerial.h>
#include "OBD2.h"
#include <canvas.h>
#include "HC05.h"
#include "io.h"
#include <ELM327.h>

#ifdef CANVAS_WRAPPER
#include "canvas.h"
CanvasWrapper wrapper(canvas,20);
#endif


class ELM327 {
private:
  SerialControl serialControl;
  //  boolean ok;
  int responseIndex;
  char atoiBuffer[A2IBufferSize];
  String responses[ResponseMaxSize];
public:
  boolean touchMaxWaitTimes;

  ELM327(SoftwareSerial & _serial):
  serialControl(SerialControl(_serial))/*,ok(false),touchMaxWaitTimes(false)*/{
    responseIndex=0;
  }
  boolean sendCommandAndWaitOk(String command) {
    sendCommand(command);
    int x=0;
    touchMaxWaitTimes=false;
    for(;!isResponse()&&x<MaxWaitTimes;x++) {
      delay(DelayTime);
    };
    if(x==MaxWaitTimes) {
      touchMaxWaitTimes=true;
    }
    return false;
    //    return isResponseOk();
  }
  void sendCommand(String _command) {
    responseIndex=0;
    serialControl.sendString(_command);
  }

  boolean isResponse() {
    //    ok=false;

    if(serialControl.isResponse()) {
      String response=serialControl.getResponse();
#ifdef DEBUG
      Serial.println("ELM327 debug response "+response);
#endif

      //      if(response.startsWith(OK)) {
      //#ifdef DEBUG
      //        Serial.println("HC05Control debug ok");
      //#endif
      //        ok=true;
      //        return true;
      //      }
      //      else if(response.startsWith(ERROR)) {
      //#ifdef DEBUG
      //        Serial.println("HC05Control debug error");
      //#endif
      //        responses[0]=response;
      //
      //        int first=response.indexOf('(');
      //        int second=response.indexOf(')');
      //        String errorString=response.substring(first+1,second);
      //        errorString.toCharArray(atoiBuffer,A2IBufferSize);
      //        errorcode=  atoi(atoiBuffer);
      //#ifdef DEBUG
      //        Serial.println("HC05Control debug errorcode "+String(errorcode)+" "+errorString);
      //#endif
      //        return true;
      //      }
      //      else if(response.startsWith(FAIL)) {
      //#ifdef DEBUG
      //        Serial.println("HC05Control debug fail");
      //#endif
      //        responses[0]=response;
      //        return true;
      //      }
      //      else {
      //#ifdef DEBUG
      //        Serial.println("HC05Control debug ["+response+"]");
      //#endif
      //        if((responseIndex+1) >ResponseMaxSize) {
      //#ifdef DEBUG
      //          Serial.println("HC05Control debug responseIndex+1 >=ResponseMaxSize");
      //#endif
      //          return false;
      //        }
      //        responses[responseIndex++]=response;
      //        return false;
      //      }
    }
    else {
#ifdef DEBUG
      Serial.print(".");
#endif
      return false;
    }

  }
};




SoftwareSerial softserial(8, 9); // RX, TX
InputBuffer serialBuffer;
HC05Control hc05(softserial);
ELM327 elm(softserial);
//#define GEARUINO_SLAVE "2013,9,110911"
#define GEARUINO_SLAVE "19,5D,253224"
boolean autoconnect=true;
ATCommand at;
//COBD obd(softserial);

#define ELM_TIMEOUT 9000
#define ELM_BAUD_RATE 38400
#define ELM_PORT softserial

void printStatus(byte status){
  switch (status)
  {
  case ELM_TIMEOUT: 
    Serial.println("ELM_TIMEOUT");
    break;
  case ELM_SUCCESS:
    Serial.println("ELM_SUCCESS");
    break;
  case ELM_NO_RESPONSE:
    Serial.println("ELM_NO_RESPONSE");
    break;
  case ELM_BUFFER_OVERFLOW:
    Serial.println("ELM_BUFFER_OVERFLOW");
    break;
  case ELM_GARBAGE:
    Serial.println("ELM_GARBAGE");
    break;
  case ELM_UNABLE_TO_CONNECT:
    Serial.println("ELM_UNABLE_TO_CONNECT");
    break;
  case ELM_NO_DATA:
    Serial.println("ELM_NO_DATA");
    break;
  default:
    Serial.print("UNKNOWN: ");
    Serial.println(status);
  }
}

void elm327Setup() {
  float f;
  bool b;
  byte by;
  int i;
  unsigned int ui;

  byte status;
  String s;
  Elm327 Elm;

  //  Serial.begin(115200);
  Serial.print("ELM327 Begin: ");
  printStatus(Elm.begin());

  Serial.print("Elm Voltage: ");
  status=Elm.getVoltage(f);
  if (status == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(f);
  }
  else{
    printStatus(status);
  }

  Serial.print("Elm Ignition: ");
  status=Elm.getIgnMon(b);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(b);
  }
  else{
    printStatus(status);
  }

  Serial.print("Elm Version: ");
  status=Elm.getVersion(s) ;
  if (status == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(s);
  }
  else{
    printStatus(status);
  }

  Serial.print("OBD2 Engine Load: ");
  status=Elm.engineLoad(by);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  }
  else{
    printStatus(status);
  }

  Serial.print("OBD2 Coolant Temperature: ");
  status=Elm.coolantTemperature(i);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  }
  else{
    printStatus(status);
  }

  Serial.print("OBD2 Fuel Trim, Bank 1, Short Term: ");
  status=Elm.fuelTrimBank1ShortTerm(i);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  }
  else{
    printStatus(status);
  }


  Serial.print("OBD2 Fuel Trim, Bank 2, Short Term: ");
  status=Elm.fuelTrimBank2ShortTerm(i);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  }
  else{
    printStatus(status);
  }

  Serial.print("OBD2 Fuel Trim, Bank 1, Long Term: ");
  status=Elm.fuelTrimBank1LongTerm(i) ;
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  }
  else{
    printStatus(status);
  }

  Serial.print("OBD2 Fuel Trim, Bank 2, Long Term: ");
  status=Elm.fuelTrimBank2LongTerm(i);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  }
  else{
    printStatus(status);
  }

  Serial.print("OBD2 Fuel Pressure: ");
  status=Elm.fuelPressure(i) ;
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  }
  else{
    printStatus(status);
  }

  Serial.print("OBD2 Intake Manifold Absolute Pressure: ");
  status=Elm.intakeManifoldAbsolutePressure(by) ;
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  }
  else{
    printStatus(status);
  }

  Serial.print("OBD2 Engine RPM: ");
  status=Elm.engineRPM(i) ;
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  }
  else{
    printStatus(status);
  }

  Serial.print("OBD2 Vehicle Speed: ");
  status=Elm.vehicleSpeed(by);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(b);
  }
  else{
    printStatus(status);
  }

  Serial.print("OBD2 Timing Advance: ");
  status=Elm.timingAdvance(i);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  }
  else{
    printStatus(status);
  }

  Serial.print("OBD2 Intake Air Temperature: ");
  status=Elm.intakeAirTemperature(i);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  }
  else{
    printStatus(status);
  }

  Serial.print("OBD2 MAF Air Flow Rate: ");
  status=Elm.MAFAirFlowRate(ui);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(ui);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 Throttle Position: ");
  status=Elm.throttlePosition(by);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 O2 Sensor: Bank1 - Sensor 1: ");
  byte vo;
  byte trim;
  status=Elm.o2SensorBank1Sensor1(vo, trim);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Voltage: ");
    Serial.println(vo, DEC);
    Serial.print(" Trim: ");
    Serial.println(trim, DEC);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 O2 Sensor: Bank1 - Sensor 2: ");
  status=Elm.o2SensorBank1Sensor2(vo, trim);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Voltage: ");
    Serial.println(vo, DEC);
    Serial.print(" Trim: ");
    Serial.println(trim, DEC);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 O2 Sensor: Bank1 - Sensor 3: ");
  status=Elm.o2SensorBank1Sensor3(vo, trim);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Voltage: ");
    Serial.println(vo, DEC);
    Serial.print(" Trim: ");
    Serial.println(trim, DEC);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 O2 Sensor: Bank1 - Sensor 4: ");
  status=Elm.o2SensorBank1Sensor4(vo, trim);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Voltage: ");
    Serial.println(vo, DEC);
    Serial.print(" Trim: ");
    Serial.println(trim, DEC);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 O2 Sensor: Bank2 - Sensor 1: ");
  status=Elm.o2SensorBank2Sensor1(vo, trim);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Voltage: ");
    Serial.println(vo, DEC);
    Serial.print(" Trim: ");
    Serial.println(trim, DEC);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 O2 Sensor: Bank2 - Sensor 2: ");
  status=Elm.o2SensorBank2Sensor2(vo, trim);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Voltage: ");
    Serial.println(vo, DEC);
    Serial.print(" Trim: ");
    Serial.println(trim, DEC);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 O2 Sensor: Bank2 - Sensor 3: ");
  status=Elm.o2SensorBank2Sensor3(vo, trim);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Voltage: ");
    Serial.println(vo, DEC);
    Serial.print(" Trim: ");
    Serial.println(trim, DEC);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 O2 Sensor: Bank2 - Sensor 4: ");
  status=Elm.o2SensorBank2Sensor4(vo, trim);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Voltage: ");
    Serial.println(vo, DEC);
    Serial.print(" Trim: ");
    Serial.println(trim, DEC);
  }
  else{
    printStatus(status);
  }

  Serial.print("OBD2 Auxiliary Input Status: ");
  status=Elm.auxiliaryInputStatus(b);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(b);
  }
  else{
    printStatus(status);
  }

  Serial.print("OBD2 Engine Run Time: ");
  status=Elm.engineRunTime(ui);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(ui);
  }
  else{
    printStatus(status);
  }

  Serial.print("OBD2 Distance since MIL active: ");
  status=Elm.distanceMIL(ui);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(ui);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 Relative Fuel Rail Pressure: ");
  status=Elm.relativeFuelRailPressure(ui);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(ui);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 Absolute Fuel Rail Pressure: ");
  status=Elm.absoluteFuelRailPressure(ui);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(ui);
  }
  else{
    printStatus(status);
  }
  unsigned int equiv;
  unsigned int voltage;
  Serial.print("OBD2 O2 Sensor 1, Equivilance Ratio and Voltage: ");
  status=Elm.o2S1WRVoltage(equiv, voltage);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value Equiv: ");
    Serial.println(equiv);
    Serial.print(" Value Voltage: ");
    Serial.println(voltage);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 O2 Sensor 2, Equivilance Ratio and Voltage: ");
  status=Elm.o2S2WRVoltage(equiv, voltage);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value Equiv: ");
    Serial.println(equiv);
    Serial.print(" Value Voltage: ");
    Serial.println(voltage);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 O2 Sensor 3, Equivilance Ratio and Voltage: ");
  status=Elm.o2S3WRVoltage(equiv, voltage);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value Equiv: ");
    Serial.println(equiv);
    Serial.print(" Value Voltage: ");
    Serial.println(voltage);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 O2 Sensor 4, Equivilance Ratio and Voltage: ");
  status=Elm.o2S4WRVoltage(equiv, voltage);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value Equiv: ");
    Serial.println(equiv);
    Serial.print(" Value Voltage: ");
    Serial.println(voltage);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 O2 Sensor 5, Equivilance Ratio and Voltage: ");
  status=Elm.o2S5WRVoltage(equiv, voltage);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value Equiv: ");
    Serial.println(equiv);
    Serial.print(" Value Voltage: ");
    Serial.println(voltage);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 O2 Sensor 6, Equivilance Ratio and Voltage: ");
  status=Elm.o2S6WRVoltage(equiv, voltage);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value Equiv: ");
    Serial.println(equiv);
    Serial.print(" Value Voltage: ");
    Serial.println(voltage);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 O2 Sensor 7, Equivilance Ratio and Voltage: ");
  status=Elm.o2S7WRVoltage(equiv, voltage);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value Equiv: ");
    Serial.println(equiv);
    Serial.print(" Value Voltage: ");
    Serial.println(voltage);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 O2 Sensor 8, Equivilance Ratio and Voltage: ");
  status=Elm.o2S8WRVoltage(equiv, voltage);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value Equiv: ");
    Serial.println(equiv);
    Serial.print(" Value Voltage: ");
    Serial.println(voltage);
  }
  else{
    printStatus(status);
  }

  Serial.print("OBD2 Commanded EGR: ");
  status=Elm.commandedEGR(by);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 EGR Error: ");
  status=Elm.EGRError(i);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  }
  else{
    printStatus(status);
  }
  Serial.print("OBD2 Commanded Evaporative Purge: ");
  status=Elm.commandedEvaporativePurge(by);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  }
  else{
    printStatus(status);
  }
  Serial.print("Fuel Level: ");
  status=Elm.fuelLevel(by);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  }
  else{
    printStatus(status);
  }
  Serial.print("Warmups since MIL last cleared: ");
  status=Elm.warmUpsSinceLastCleared(by);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  }
  else{
    printStatus(status);
  }
  Serial.print("Distance since MIL last cleared: ");
  status=Elm.distanceSinceLastCleared(ui);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(ui);
  }
  else{
    printStatus(status);
  }
  Serial.print("Evap Pressure: ");
  status=Elm.evapPressure(i);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  }
  else{
    printStatus(status);
  }
  Serial.print("Barometric Pressure: ");
  status=Elm.barometricPressure(by);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  }
  else{
    printStatus(status);
  }
  int current;

  Serial.print("O2 Sensor 1 Current and Equiv Ratio: ");
  status=Elm.o2S1WRCurrent(equiv, current);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value Current: ");
    Serial.println(current);
    Serial.print(" Value Equiv: ");
    Serial.println(equiv);
  }
  else{
    printStatus(status);
  }
  Serial.print("O2 Sensor 2 Current and Equiv Ratio: ");
  status=Elm.o2S2WRCurrent(equiv, current);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value Current: ");
    Serial.println(current);
    Serial.print(" Value Equiv: ");
    Serial.println(equiv);
  }
  else{
    printStatus(status);
  }
  Serial.print("O2 Sensor 3 Current and Equiv Ratio: ");
  status=Elm.o2S3WRCurrent(equiv, current);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value Current: ");
    Serial.println(current);
    Serial.print(" Value Equiv: ");
    Serial.println(equiv);
  }
  else{
    printStatus(status);
  }
  Serial.print("O2 Sensor 4 Current and Equiv Ratio: ");
  status=Elm.o2S4WRCurrent(equiv, current);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value Current: ");
    Serial.println(current);
    Serial.print(" Value Equiv: ");
    Serial.println(equiv);
  }
  else{
    printStatus(status);
  }
  Serial.print("O2 Sensor 5 Current and Equiv Ratio: ");
  status=Elm.o2S5WRCurrent(equiv, current);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value Current: ");
    Serial.println(current);
    Serial.print(" Value Equiv: ");
    Serial.println(equiv);
  }
  else{
    printStatus(status);
  }
  Serial.print("O2 Sensor 6 Current and Equiv Ratio: ");
  status=Elm.o2S6WRCurrent(equiv, current);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value Current: ");
    Serial.println(current);
    Serial.print(" Value Equiv: ");
    Serial.println(equiv);
  }
  else{
    printStatus(status);
  }
  Serial.print("O2 Sensor 7 Current and Equiv Ratio: ");
  status=Elm.o2S7WRCurrent(equiv, current);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value Current: ");
    Serial.println(current);
    Serial.print(" Value Equiv: ");
    Serial.println(equiv);
  }
  else{
    printStatus(status);
  }
  Serial.print("O2 Sensor 8 Current and Equiv Ratio: ");
  status=Elm.o2S8WRCurrent(equiv, current);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value Current: ");
    Serial.println(current);
    Serial.print(" Value Equiv: ");
    Serial.println(equiv);
  }
  else{
    printStatus(status);
  }
  Serial.print("Catalyst Temperature Bank1 Sensor 1: ");
  status=Elm.catalystTemperatureBank1Sensor1(i);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  }
  else{
    printStatus(status);
  }
  Serial.print("Catalyst Temperature Bank2 Sensor 1: ");
  status=Elm.catalystTemperatureBank2Sensor1(i);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  }
  else{
    printStatus(status);
  }
  Serial.print("Catalyst Temperature Bank1 Sensor 2: ");
  status=Elm.catalystTemperatureBank1Sensor2(i);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  }
  else{
    printStatus(status);
  }
  Serial.print("Catalyst Temperature Bank2 Sensor 2: ");
  status=Elm.catalystTemperatureBank2Sensor2(i);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  }
  else{
    printStatus(status);
  }
  Serial.print("Control Module Voltage: ");
  status=Elm.controlModuleVoltage(ui);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(ui);
  }
  else{
    printStatus(status);
  }
  Serial.print("Absolute Load Value: ");
  status=Elm.absoluteLoadValue(ui);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(ui);
  }
  else{
    printStatus(status);
  }

  Serial.print("Command equivalence ratio: ");
  status=Elm.commandEquivalenceRatio(f );
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(f);
  }
  else{
    printStatus(status);
  }

  Serial.print("Relative throttle position: ");
  status=Elm.relativeThrottlePosition(by);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  }
  else{
    printStatus(status);
  }


  Serial.print("Ambient Air Temperature: ");
  status=Elm.ambientAirTemperature(i );
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(i);
  }
  else{
    printStatus(status);
  }

  Serial.print("Absolute throttle position B: ");
  status=Elm.absoluteThrottlePositionB(by);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  }
  else{
    printStatus(status);
  }
  Serial.print("Absolute throttle position C: ");
  status=Elm.absoluteThrottlePositionC(by);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  }
  else{
    printStatus(status);
  }

  Serial.print("Accelerator pedal position D: ");
  status=Elm.acceleratorPedalPositionD(by);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  }
  else{
    printStatus(status);
  }

  Serial.print("Accelerator pedal position E: ");
  status=Elm.acceleratorPedalPositionE(by);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  }
  else{
    printStatus(status);
  }

  Serial.print("Accelerator pedal position F: ");
  status=Elm.acceleratorPedalPositionF(by);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  }
  else{
    printStatus(status);
  }

  Serial.print("Commanded Throttle Actuator: ");
  status=Elm.commandedThrottleActuator(by);
  if (status  == ELM_SUCCESS)
  {
    Serial.println ("Pass");
    Serial.print(" Value: ");
    Serial.println(by);
  }
  else{
    printStatus(status);
  }

}

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for Leonardo only
  //  }
  softserial.begin(38400);
#ifdef CANVAS_WRAPPER
  wrapper.clear();
#endif
  // elm.sendCommandAndWaitOk("AT");
  //  elm.sendCommandAndWaitOk("ATZ");
  //  
  //  if(true) return;

  //  if(hc05.sendCommandAndWaitOk("ATZ")) {
  //    Serial.println("ELM327 Linked"); 
  //    autoconnect=false;
  //  }

  if(autoconnect){
    Serial.println("Begin connect..."); 
    State state=hc05.getState();
    if(true==hc05.touchMaxWaitTimes) {
      Serial.println("TouchMaxWaitTimes"); 
      //      return;
    }
    else if(CONNECTED!=state) {
      Serial.println("Try connect");
      //    hc05.sendCommandAndWaitOk("AT+DISC");

      while(!hc05.sendCommandAndWaitOk("AT+LINK="+String(GEARUINO_SLAVE))) {
        if(16==hc05.errorcode) {
          if(hc05.sendCommandAndWaitOk("AT+INIT")) {
            Serial.println("SPP init.");
          }
          else {
            Serial.println("SPP init failed: "+hc05.getResponses()[0]);
          }
        }
      }
    }

    Serial.println("BT Linked");
    elm327Setup();
  }

  //  canvas.setPaint(2,255,255,255,1);
  //  canvas.setText("BTLink");
  //  canvas.drawText(0,90,90);//big blue text
  //  while (!obd.init());  
  Serial.println("OBD Linked");
  //  canvas.setText("OBDLink");
  //  canvas.drawText(0,90,90);//big blue text


}


#ifdef ITERACTION
void interaction() {
  if(serialBuffer.listen()) {
    String line= serialBuffer.getLine();
    //    Serial.println("Send: "+line);
    hc05.sendCommand(line);
  }
  if(hc05.isResponse()) {
    if(hc05.isResponseOk()) {
      String*vec=hc05.getResponses();
      int size=hc05.getResponseSize();
      if(size==0) {
        Serial.println("Ok");
      }
      for(int x=0;x<size;x++) {
        String s = vec[x];
        Serial.println(s);
      }
    }
    else {
      Serial.println("? " +hc05.getResponses()[0]);
    }
  }
}
#endif

#ifdef BRIDGE
void bridge() {
  if (Serial.available()){
    char in = Serial.read();
    Serial.write(in);
    //    if(in=='c') {
    //      Serial.println(hc05.getState());
    //    }
    //    else {
    softserial.print(in);
    //    }
  }
  if (softserial.available()) {
    Serial.write(softserial.read());
  }
}
#endif


void loop() // run over and over
{

#ifdef CANVAS_WRAPPER
  wrapper.println("12345678#ABCDEFGH");
#endif

#ifdef ITERACTION
  interaction();
#endif
#ifdef BRIDGE
  bridge();
#endif
  // elm.sendCommand("ATZ");
  //delay(1000);
  // elm.sendCommand("AT");
  //  Serial.println("loop");
  //  hc05.sendCommand("AT Z");
  //  int value;
  //  if (obd.ReadSensor(PID_RPM, value)) {
  //    // RPM is read and stored in 'value'
  //    // light on LED when RPM exceeds 5000
  //    digitalWrite(13, value > 5000 ? HIGH : LOW);
  //    //    canvas.setText(String(value));
  //    //    canvas.drawText(0,90,90);//big blue text
  //    Serial.println(value);
  //  }
}













































































































































