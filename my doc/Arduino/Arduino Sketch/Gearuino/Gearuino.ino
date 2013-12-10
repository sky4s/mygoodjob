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
#endif

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

#include <Arduino.h>
#include <GearLedControl.h>
#include <SoftwareSerial.h>
#include <Bounce.h>
#include "car.h"

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
#include <GearELM327.h>
ELM327 elm(softserial);
#include "elm.h"
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

  while (elm.begin()!=ELM_SUCCESS);  
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
  elmLoop();
#endif //BRIDGE

  processButton(switchBouncer);
  processButton(reflectBouncer);
}


int rpm;
byte speed;
float voltage;
byte status;
unsigned int maf;
byte gear;
float kpl;
#define MAX_FUNC_COUNT 4

void elmLoop() {

  switch(funcselect) {
  case 0:
    {
      status=elm.vehicleSpeed(speed);
#ifdef DEBUG
      Serial.println("Speed: "+String(speed));
#endif
      if (  status== ELM_SUCCESS ) {
        displayDigit(speed);
      }
#ifdef DEBUG
      else {
        printStatus(status);
      }
#endif
    }
    break;
  case 1:
    {
      status=elm.engineRPM(rpm);
#ifdef DEBUG
      Serial.println("RPM: "+String(rpm));
#endif
      if ( status== ELM_SUCCESS ) {
        displayRPM(rpm);
      }
#ifdef DEBUG
      else {
        printStatus(status);
      }
#endif
    }
    break;
  case 2:
    {
      status=elm.vehicleSpeed(speed);
      if ( status== ELM_SUCCESS ) {
        status=elm.engineRPM(rpm);
      }   

      if ( status== ELM_SUCCESS ) {
        gear = getGearPosition(rpm,speed);
#ifdef DEBUG
        Serial.println("Gear: "+String(gear));
#endif
        displayGear(gear);
      }
#ifdef DEBUG
      else {
        printStatus(status);
      }
#endif
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
        kpl=   getKPL(speed,maf);
        displayKPL(kpl);
      }
#ifdef DEBUG
      else {
        printStatus(status);
      }
#endif
    }
    break;

  }

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


void displayGear(byte gear) {
  lc.upsidedownMode=!reflect;
  lc.setDigit(0,2,gear,false);
}

void displayKPL(float kpl) {

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

  if(ELM_SUCCESS==elm.begin()) {
    btAutoconnect=false;
    Serial.println("ELM connecting test OK."); 
  }
  else {
    //    softserial.begin(38400);
    btAutoconnect=true;
    Serial.println("ELM connecting test failed."); 
  }


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









































































