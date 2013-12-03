/*
 
 
 */
//============================================================================
// for debug setting
//============================================================================
//#define DEBUG
//#define ITERACTION
//#define BRIDGE
//#define CANVAS_WRAPPER
//#define SKIP_SETUP

//don't want to handle BT connection, because BT will not appear in final version.
#define SKIP_BT_CONNECT
//============================================================================

//============================================================================
// function setting
//============================================================================
#define USE_SERIAL_CONTROL
#ifndef SKIP_BT_CONNECT
#define USE_HC05
//#define USE_AT_COMMAND
#endif
#define USE_ELM
//#define USE_PROCESS_BUTTON

static const int MaxBTTry=10;
#define HC05_BAUD_RATE 38400

#define MASTER_BT_ADDR "2013,9,260146"
#define ELM327_BT_ADDR "2013,9,110911"
//#define ELM327_BT_ADDR "19,5D,253224"

const static unsigned long DebounceDelay = 200;    // the debounce time; increase if the output flickers
//============================================================================

//============================================================================
// pin define
//============================================================================
static const int HC05KeyPin=7;
static const int SwitchPin=2;
static const int ReflectPin=3;
static const int LEDPin =13;
static const int OBD2RXPin = 8;
static const int OBD2TXPin = 9;
//============================================================================
#include <Arduino.h>
#include <GearLedControl.h>
#include <SoftwareSerial.h>
#include <Bounce.h>

SoftwareSerial softserial(OBD2RXPin, OBD2TXPin); // RX, TX
Bounce switchBouncer = Bounce( SwitchPin,DebounceDelay ); 
Bounce reflectBouncer = Bounce( ReflectPin,DebounceDelay ); 

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

//============================================================================
// ELM327 API
//============================================================================
#ifdef USE_ELM

#include <GearELM327.h>
ELM327 elm(softserial);
#include "elm.h"

#else

#include <OBD.h>
COBD obd(softserial);

#endif
//============================================================================

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,1);
boolean autoconnect=true;
boolean reflect=true;

void displayDigit(int value);
void initLedControl();
void btConnect();


void setup()  
{
  pinMode(HC05KeyPin, OUTPUT);
  digitalWrite(HC05KeyPin, HIGH);
  Serial.begin(9600);
  Serial.println("setup()");
  softserial.begin(HC05_BAUD_RATE);

  initLedControl();
  displayDigit(168);

#ifdef SKIP_SETUP
  if(true) {
    return; 
  }
#endif

#ifndef SKIP_BT_CONNECT
  btConnect();
#endif

#ifdef USE_ELM
  while (elm.begin()!=ELM_SUCCESS);  
#else //USE_ELM
  while (!obd.init());  
#endif //USE_ELM
  Serial.println("OBD Linked");


  pinMode(SwitchPin, INPUT);
  pinMode(ReflectPin, INPUT);
  pinMode(LEDPin, OUTPUT);

  // set initial LED state
  digitalWrite(LEDPin, LOW);
  displayDigit(0);
  delay(1000);
}

#ifdef BRIDGE
void bridge();
#endif
void interaction();
void processButton(Bounce bouncer);
int funcselect=0;

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
#else
#ifdef USE_ELM
  elmLoop();
#else //USE_ELM
  obdLoop();
#endif //USE_ELM
#endif //BRIDGE

  processButton(switchBouncer);
  processButton(reflectBouncer);

}

#ifdef USE_ELM
int rpm;
byte speed;
float voltage;
byte status;
#define MAX_FUNC_COUNT 4

void elmLoop() {

  switch(funcselect) {
  case 0:
    {
      status=elm.vehicleSpeed(speed);
      if (  status== ELM_SUCCESS ) {
        displayDigit(speed);
      }
    }
    break;
  case 1:
    {
      status=elm.engineRPM(rpm);
      if ( status== ELM_SUCCESS ) {
        displayDigit(rpm/100*10);
      }
    }
    break;
  case 2:
    {
      status=elm.vehicleSpeed(speed);
      if ( status== ELM_SUCCESS ) {
        status=elm.engineRPM(rpm);
      }   
      if ( status== ELM_SUCCESS ) {
        byte gear = getGearPosition(rpm,speed);
        displayDigit(gear);
      }
    } 
    break;
  case 3:
    {
      status=elm.getVoltage(voltage);
      if (  status== ELM_SUCCESS ) {
        int intvoltage=(int)(voltage*10);
        displayDigit(intvoltage);
      }
    }
    break;
  }

}
#else
int value;
void obdLoop() {
  int value;
  //  if (obd.readSensor(PID_RPM, value)) {
  //    // RPM is read and stored in 'value'
  //    // light on LED when RPM exceeds 5000
  //    //    digitalWrite(13, value > 5000 ? HIGH : LOW);
  //    Serial.println("RPM: "+String(value));
  //  }
  if (obd.readSensor(PID_SPEED, value)) {
    // RPM is read and stored in 'value'
    // light on LED when RPM exceeds 5000
    //    digitalWrite(13, value > 5000 ? HIGH : LOW);
    Serial.println("Speed: "+String(value));
    displayDigit(value);
  }
}
#endif

static const float TireRound = 1889.353822;
static const float GearRatio[] ={
  15.256715,
  9.460955,
  6.250908,
  4.444413,
  3.376965,
  2.73429
};
static const int MaxGear = 6;
static float gearrpm[MaxGear];

byte getGearPosition(int rpm,byte speed) {
  for(int x=0;x<MaxGear;x++) {
    gearrpm[x] = speed*GearRatio[x]/TireRound/60;
  }
  float minDelta = 3.4028235E+38;
  int minIndex=0;
  byte x=0;
  for(;x<MaxGear;x++) {
    //    gearrpm[x] = abs( gearrpm[x] -rpm);
    //  if( 
    float delta = abs( gearrpm[x] -rpm);
    if(delta<minDelta) {
      minDelta = delta;
      minIndex = x;
    }
  }
  return x+1;
}

void processButton(Bounce bouncer) {
  if(bouncer.update() == true && bouncer.read() == HIGH) {
    switch(bouncer.pin) {
    case SwitchPin:
      funcselect++;
      funcselect=(MAX_FUNC_COUNT==funcselect)?0:funcselect;
      break;
    case ReflectPin:
      reflect=!reflect;
      break;
    }
    digitalWrite(LEDPin, HIGH);
    delay(32);
    digitalWrite(LEDPin, LOW);
  }
}



#ifdef ITERACTION
void interaction() {
  if(serialBuffer.listen()) {
    String line= serialBuffer.getLine();
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
boolean hc05KeyPin=false;
boolean hc05BaudRate=false;
void bridge() {
  if (Serial.available()){
    char in = Serial.read();
    Serial.write(in);

    if( in=='$') {
      hc05KeyPin=!hc05KeyPin;
      digitalWrite(HC05KeyPin, hc05KeyPin?LOW:HIGH);
    }
    else if( in=='%') {
      hc05BaudRate=!hc05BaudRate;
      if(hc05BaudRate) {
        softserial.begin(38400);
      }
      else {
        softserial.begin(9600);
      }
    }
    else {
      softserial.print(in);
    }
  }
  if (softserial.available()) {
    Serial.write(softserial.read());
  }
}
#endif

void displayDigit(int value) {
  //  Serial.println(value);
  int digit0=value%10;
  int digit1=(value/10)%10;
  int digit2=(value/100)%10;
  lc.setDigit(0,0,digit0,false,reflect);
  if(value>=10) {
    lc.setDigit(0,1,digit1,false,reflect);
    if( value>=100) {
      lc.setDigit(0,2,digit2,false,reflect);
    }
    else {
      lc.setChar(0,2,' ',false);
    }
  }
  else {
    lc.setChar(0,1,' ',false);
    lc.setChar(0,2,' ',false);
  }

}

void initLedControl() {
  /*
   The MAX72XX is in power-sav  ing mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,15);
  /* and clear the display */
  lc.clearDisplay(0);
  lc.setScanLimit(0,2);
}

#ifndef SKIP_BT_CONNECT
void btConnect() {

#ifdef USE_ELM
  if(ELM_SUCCESS==elm.begin()) {
    autoconnect=false;
    Serial.println("ELM connecting test OK."); 
  }
  else {
    //    softserial.begin(38400);
    autoconnect=true;
    Serial.println("ELM connecting test failed."); 
  }
#else //USE_ELM
  if(!obd.init()) {
    autoconnect=true;
    Serial.println("OBD connecting test failed."); 
  }
  else {
    autoconnect=false;
    Serial.println("OBD connecting test OK."); 
  }
#endif //USE_ELM

#ifdef USE_HC05
  if(autoconnect){
    Serial.println("Begin connect..."); 
    digitalWrite(HC05KeyPin, LOW);
    State state=hc05.getState();
    if(true==hc05.touchMaxWaitTimes) {
      Serial.println("TouchMaxWaitTimes"); 
    }
    else if(CONNECTED!=state) {
      Serial.println("Try connect");
      int x=0;
      for(;x<MaxBTTry&&!hc05.sendCommandAndWaitOk("AT+LINK="+String(ELM327_BT_ADDR));x++) {
        if(16==hc05.errorcode) {
          if(hc05.sendCommandAndWaitOk("AT+INIT")) {
            Serial.println("SPP init.");
          }
          else {
            Serial.println("SPP init failed: "+hc05.getResponses()[0]);
          }
        }
      }

      if(MaxBTTry==x) {
        Serial.println("Touch max bt try.");
      }
      else {
        Serial.println("BT Linked");
      }
      digitalWrite(HC05KeyPin, HIGH);
    }

  }
#endif //USE_HC05
}
#endif //SKIP_BT_CONNECT







































