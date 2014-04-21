/*

 
 */
//============================================================================
// for debug setting
//============================================================================
//#define DEBUG
//#define ITERACTION //(deprecated)
//#define BRIDGE
//#define TEST_IN_BRIDGE
//#define CANVAS_WRAPPER
//============================================================================

//============================================================================
// reserve setting
//============================================================================
#ifdef BRIDGE
#define SKIP_SETUP
#endif
#ifdef ITERACTION
#define USE_SERIAL_CONTROL
#endif
//don't want to handle BT connection, because BT will not appear in final version.
#define SKIP_BT_CONNECT
//============================================================================

//============================================================================
// function setting
//============================================================================
//#define USE_BUTTON
//#define MULTI_ELM_FUNC
const static unsigned long DebounceDelay = 200;    // the debounce time; increase if the output flickers
#define OBD_BAUD_RATE 38400
//#define OBD_BAUD_RATE2 9600
#define MAX_OBD_RETRY 10
//============================================================================

//============================================================================
// BlueTooth Setting (deprecated)
//============================================================================
#ifndef SKIP_BT_CONNECT
#define USE_HC05
#endif

static const int MaxBTTry=10;
#define MASTER_BT_ADDR "2013,9,260146"
#define ELM327_BT_ADDR "2013,9,110911"
//#define ELM327_BT_ADDR "19,5D,253224"
//============================================================================

//============================================================================
// pin define
//============================================================================
#ifdef USE_HC05
static const int HC05KeyPin=7;
#endif
static const int SwitchPin=4;
static const int ReflectPin=5;
static const int LEDPin =13;
static const int OBD2RXPin = 2;
static const int OBD2TXPin = 3;

static const int LED_DATA_PIN = 12;
static const int LED_CLK_PIN = 11;
static const int LED_LOAD_PIN = 10;
//============================================================================


//============================================================================
// include
//============================================================================
#include <Arduino.h>
#include <GearLedControl.h>
#include <SoftwareSerial.h>
#include <Bounce.h>
#include "car.h"
#include "led.h"

// RX, TX, debug　需要用到, 　所以要擺在debug　之前
SoftwareSerial softserial(OBD2RXPin, OBD2TXPin); 
#include "debug.h"
//============================================================================

//============================================================================
// global variable declare
//============================================================================

#ifdef USE_BUTTON
Bounce switchBouncer = Bounce( SwitchPin,DebounceDelay ); 
Bounce reflectBouncer = Bounce( ReflectPin,DebounceDelay ); 
#endif

#ifdef USE_SERIAL_CONTROL
#include <SerialControl.h>
InputBuffer serialBuffer;
#endif

#ifdef USE_HC05
#include "HC05.h"
HC05Control hc05(softserial);
#ifdef USE_AT_COMMAND
ATCommand at;
#endif
#endif

extern boolean ledReflect;
boolean autoconnect=true;
//============================================================================

//============================================================================
// ELM327 API
//============================================================================
#include <GearELM327.h>
ELM327 elm(softserial);
#include "elm.h"
//============================================================================

void setup()  
{
#ifdef USE_HC05
  pinMode(HC05KeyPin, OUTPUT);
  digitalWrite(HC05KeyPin, HIGH);
#endif
  Serial.begin(9600);
  Serial.println("setup()");
  softserial.begin(OBD_BAUD_RATE);

  initLedControl();

#ifndef DEBUG
  for(int x=0;x<3;x++) {
    displayDigit(168);
    delay(800);
    displayDigit(-1);
    delay(800);
  }
#endif

#ifdef SKIP_SETUP
  if(true) {
    return; 
  }
#endif

#ifndef SKIP_BT_CONNECT
  btConnect();
#endif

  //=====================================
  // OBD linking
  //=====================================
  //  byte status=ELM_UNABLE_TO_CONNECT;
  //  for(int x=0; status!=ELM_SUCCESS;x++) {
  //    status=elm.begin();
  //#ifdef DEBUG
  //    printStatus(status);
  //#endif
  //    if( MAX_OBD_RETRY == x) {
  //      softserial.begin(OBD_BAUD_RATE2);
  //    }
  //  }
  while(ELM_SUCCESS!=elm.begin());
  Serial.println("OBD Linked");
  //=====================================

#ifdef USE_BUTTON
  pinMode(SwitchPin, INPUT);
  pinMode(ReflectPin, INPUT);
  pinMode(LEDPin, OUTPUT);

  // set initial LED state
  digitalWrite(LEDPin, LOW);
#endif


#ifndef DEBUG
  for(int x=0;x<2;x++) {
    displayDigit(0);
    delay(1000);
    displayDigit(-1);
    delay(1000);
  }
#endif
}


#ifdef USE_BUTTON
void processButton(Bounce &bouncer);
#endif
int funcselect=0;

#ifdef TEST_IN_BRIDGE
int count=0;
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

#ifdef TEST_IN_BRIDGE
  delay(100);
  displayDigit(count++);
  ledReflect=false;
#else
  bridge();
#endif

#else
  elmLoop();
#endif //BRIDGE

#ifdef USE_BUTTON
  processButton(switchBouncer);
  processButton(reflectBouncer);
#endif


}

int rpm;
byte speed;
float voltage;
byte status;
unsigned int maf;
byte gear;
float kpl;
byte rThrottlePos;
#define MAX_FUNC_COUNT 5
boolean idleWhenStop = false;

void elmLoop() {

  status=elm.engineRPM(rpm);
  if(idleWhenStop) {
    if ( status== ELM_SUCCESS &&( 0 == rpm)) {
      displayDigit(-1);
      delay(1000);
      return;
    }
#ifdef DEBUG
    else {
      Serial.print("engineRPM: ");
      printStatus(status);
    }
#endif     
  }

#ifdef MULTI_ELM_FUNC
  multiElmFuncLoop(funcselect);
#else
  multiElmFuncLoop(0);
#endif
}


void multiElmFuncLoop(int func) {
  switch(func) {
  case 0:
    {
      status=elm.vehicleSpeed(speed);
#ifdef DEBUG
      Serial.println("Speed: "+String(speed));
#endif
      if (  status== ELM_SUCCESS ) {
        displayDigit(speed);
      }
    }
    break;

  case 1:
    {
#ifdef DEBUG
      Serial.println("RPM: "+String(rpm));
#endif
      if ( status== ELM_SUCCESS ) {
        displayRPM(rpm);
      }
    }
    break;

  case 2:
    {
      status=elm.vehicleSpeed(speed);
      if ( status== ELM_SUCCESS ) {
        gear = getGearPosition(rpm,speed);
#ifdef DEBUG
        Serial.println("Gear: "+String(gear));
#endif
        displayGear(gear);
      }
    } 
    break;
  case 3:
    {
      status=elm.vehicleSpeed(speed);
#ifdef DEBUG
      Serial.println("Speed: "+String(speed));
#endif
      if (  status== ELM_SUCCESS ) {
        status=elm.MAFAirFlowRate(maf);
      }
      if ( status== ELM_SUCCESS ) {
        kpl= getKPL(speed,maf);
        displayKPL(kpl);
      }
    }
    break;
  case 4:
    {
      status=elm.throttlePosition(rThrottlePos);
#ifdef DEBUG
      Serial.println("ThrottlePosition: "+String(rThrottlePos));
#endif
      if (status== ELM_SUCCESS ) {
        displayDigit(rThrottlePos);
      }
    }
    break;

  }

#ifdef DEBUG
  if (  status!= ELM_SUCCESS ) {
    printStatus(status);
  }
#endif

}

#ifdef USE_BUTTON
void processButton(Bounce &bouncer) {
  if(bouncer.update() == true && bouncer.read() == HIGH) {
    switch(bouncer.pin) {
    case SwitchPin:
      funcselect++;
      funcselect=(MAX_FUNC_COUNT==funcselect)?0:funcselect;
      break;
    case ReflectPin:
      ledReflect=!ledReflect;
      break;
    }
    digitalWrite(LEDPin, HIGH);
    delay(32);
    digitalWrite(LEDPin, LOW);
  }
}
#endif


















































































































