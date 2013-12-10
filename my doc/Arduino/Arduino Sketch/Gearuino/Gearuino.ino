/*
 
 
 */
//============================================================================
// for debug setting
//============================================================================
//#define DEBUG
//#define ITERACTION
//#define BRIDGE
//#define CANVAS_WRAPPER
#ifdef BRIDGE
#define SKIP_SETUP
#endif

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
static const int HC05KeyPin = 7;
static const int SwitchPin = 2;
static const int ReflectPin = 3;
static const int LEDPin = 13;
static const int OBD2RXPin = 8;
static const int OBD2TXPin = 9;
//============================================================================

//============================================================================
// Car define
//============================================================================
#define LANCER_FORTIS
#ifdef LANCER_FORTIS
static const float TireRound = 2.049575047;
static const float GearRatio[] ={
  10.71,
  14.37588,
  8.54964,
  6.57288,
  5.09184,
  3.86172,
  3.17016,
};
static const int MaxGear = 7;
#else
static const float TireRound = 1.8893538219;
static const float GearRatio[] ={
  15.265971,
  15.256715,
  9.460955,
  6.250908,
  4.444413,
  3.376965,
  2.73429
};
static const int MaxGear = 7;
#endif
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
boolean reflect=true;
boolean commonAnodeLED=false;
LedControl lc=LedControl(12,11,10,1,commonAnodeLED,true,!reflect);
boolean btAutoconnect=true;


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
void processButton(Bounce &bouncer);
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
  //  delay(1000);
}

#ifdef USE_ELM
int rpm;
byte speed;
float voltage;
byte status;
byte kpl1;
int kpl2;
#define MAX_FUNC_COUNT 3

void elmLoop() {

  switch(funcselect) {
  case 0:
    {
      status=elm.vehicleSpeed(speed);
      Serial.println("Speed: "+String(speed));
      if (  status== ELM_SUCCESS ) {
        displayDigit(speed);
      }
    }
    break;
  case 1:
    {
      status=elm.engineRPM(rpm);
      Serial.println("RPM: "+String(rpm));
      if ( status== ELM_SUCCESS ) {
        //displayDigit(rpm/100*10);
        displayRPM(rpm);
      }
    }
    break;
  case 2:
    {
      status=elm.vehicleSpeed(speed);
      if ( status== ELM_SUCCESS ) {
        //        delay(1);
        status=elm.engineRPM(rpm);
      }   

      if ( status== ELM_SUCCESS ) {
        byte gear = getGearPosition(rpm,speed);
        Serial.println("Gear: "+String(gear));
        displayGear(gear);
      }
      else {
#ifdef DEBUG
        printStatus(status);
#endif
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


static float gearrpm[MaxGear];
byte getGearPosition(int rpm,byte speed) {
  for(int x=0;x<MaxGear;x++) {
    gearrpm[x] = speed*GearRatio[x]/TireRound*1000/60;
  }
  float minDelta = 3.4028235E+38;
  byte minIndex=0;
  for(byte x=1;x<MaxGear;x++) {
    float delta = abs( gearrpm[x] -rpm);
    if(delta<minDelta) {
      minDelta = delta;
      minIndex = x;
    }
  }
  //  Serial.println(String(rpm)+" "+String(speed));
  return minIndex;
}

void processButton(Bounce &bouncer) {
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

void displayGear(byte gear) {
  lc.upsidedownMode=!reflect;
  lc.setDigit(0,2,gear,false);
}

void displayRPM(int rpm) {
  int digit = rpm/1000;
  int circle = (rpm-digit*1000)/111; //one piece is 111 rpm
  //  Serial.println(String(circle));
  if( 9==circle) {
    circle=0;
    digit++; 
  }
  lc.upsidedownMode=!reflect;
  if(digit>0) {
    lc.setDigit(0,2,digit,false);
  }
  else {
    lc.setChar(0,2,' ',false);
  }
  byte v0=0;
  byte v1=0;
  //pABCDEFG
  if( circle>=1) {
    v1=v1|B00000100;
  }
  if( circle>=2) {
    v1=v1|B00000010;
  }
  if( circle>=3) {
    v1=v1|B01000000;
  }
  if( circle>=4) {
    v0=v0|B01000000;
  }
  if( circle>=5) {
    v0=v0|B00100000;
  }
  if( circle>=6) {
    v0=v0|B00010000;
  }
  if( circle>=7) {
    v0=v0|B00001000;
  }
  if( circle>=8) {
    v1=v1|B00001000;
  }
  lc.setSegment(0,0,v0 );
  lc.setSegment(0,1,v1 );
}

void displayDigit(int value) {
  int digit0=value%10;
  int digit1=(value/10)%10;
  int digit2=(value/100)%10;
  lc.upsidedownMode=!reflect;
  lc.setDigit(0,0,digit0,false );
  if(value>=10) {
    lc.setDigit(0,1,digit1,false );
    if( value>=100) {
      lc.setDigit(0,2,digit2,false );
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
    btAutoconnect=false;
    Serial.println("ELM connecting test OK."); 
  }
  else {
    //    softserial.begin(38400);
    btAutoconnect=true;
    Serial.println("ELM connecting test failed."); 
  }
#else //USE_ELM
  if(!obd.init()) {
    btAutoconnect=true;
    Serial.println("OBD connecting test failed."); 
  }
  else {
    btAutoconnect=false;
    Serial.println("OBD connecting test OK."); 
  }
#endif //USE_ELM

#ifdef USE_HC05
  if(btAutoconnect){
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

































































