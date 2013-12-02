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
static const int BTBaudRate=38400;

#define MASTER_BT_ADDR "2013,9,260146"
#define ELM327_BT_ADDR "2013,9,110911"
//#define ELM327_BT_ADDR "19,5D,253224"

const static unsigned long DebounceDelay = 50;    // the debounce time; increase if the output flickers
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
//const int interruptNumber = 0;  

void displayDigit(int value);
void initLedControl();
void btConnect();
void buttonStateChanged();

void setup()  
{
  pinMode(HC05KeyPin, OUTPUT);
  digitalWrite(HC05KeyPin, HIGH);
  Serial.begin(9600);
  Serial.println("setup()");
  softserial.begin(BTBaudRate);
  initLedControl();
  displayDigit(168);

#ifdef SKIP_SETUP
  if(true) {
    return; 
  }
#endif

  btConnect();

#ifdef USE_ELM
  while (elm.begin()!=ELM_SUCCESS);  
#else //USE_ELM
  while (!obd.init());  
#endif //USE_ELM
  Serial.println("OBD Linked");


  pinMode(SwitchPin, INPUT);
  pinMode(ReflectPin, INPUT);
  pinMode(LEDPin, OUTPUT);
#ifndef USE_PROCESS_BUTTON
  attachInterrupt(0, switchButtonStateChanged, RISING);
  attachInterrupt(1, reflectButtonStateChanged, RISING);
#endif


  // set initial LED state
  digitalWrite(LEDPin, LOW);
  displayDigit(0);
  delay(1000);
}

#ifdef BRIDGE
void bridge();
#endif
void interaction();
//void processButton(int);
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
#ifdef USE_ELM
  elmLoop();
#else //USE_ELM
  obdLoop();
#endif //USE_ELM

#endif //BRIDGE

#ifdef USE_PROCESS_BUTTON
  processButton(SwitchPin);
  processButton(ReflectPin);
#endif

  //  delay(100);
}

#ifdef USE_ELM
int rpm;
byte speed;
float voltage;
byte status;
#define MAX_FUNC_COUNT 3

void elmLoop() {

  switch(funcselect) {
  case 0:
    {
      status=elm.vehicleSpeed(speed);
      if (  status== ELM_SUCCESS ) {
        Serial.println("Speed: "+String(speed));
        displayDigit(speed);
      }
    }
    break;
  case 1:
    {
      status=elm.engineRPM(rpm);
      if ( status== ELM_SUCCESS ) {
        Serial.println("RPM: "+String(rpm));
        displayDigit(rpm/100*10);
      }
    }
    break;
  case 2:
    {
      status=elm.getVoltage(voltage);
      if (  status== ELM_SUCCESS ) {
        int intvoltage=(int)(voltage*10);
        Serial.println("Voltage: "+String(intvoltage));
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
  float minDelta = 
  for(int x=0;x<MaxGear;x++) {
    gearrpm[x] = abs( gearrpm[x] -rpm);
  }
}



#ifndef USE_PROCESS_BUTTON
Bounce siwtchBouncer = Bounce( SwitchPin,DebounceDelay ); 
Bounce reflectBouncer = Bounce( ReflectPin,DebounceDelay ); 

void switchButtonStateChanged() {
  if(siwtchBouncer.update() == true && siwtchBouncer.read() == HIGH) {
    funcselect++;
    funcselect=(MAX_FUNC_COUNT==funcselect)?0:funcselect;
  }
}

void reflectButtonStateChanged() {
  if(reflectBouncer.update() == true && reflectBouncer.read() == HIGH) {
    reflect=!reflect;
  }
}
#else

// Variables will change:
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled

void processButton(int pin) {
  // read the state of the switch into a local variable:
  int reading = digitalRead( pin);


  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 

  if ((millis() - lastDebounceTime) > DebounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      //      Serial.println(pin);
      buttonState = reading;
      // set the LED:
      if (reading == HIGH) {
        digitalWrite(LEDPin, HIGH);
        delay(32);
        digitalWrite(LEDPin, LOW);

        switch(pin) {
        case  SwitchPin: 
          {
            funcselect++;
            funcselect=(MAX_FUNC_COUNT==funcselect)?0:funcselect;
          }
          break;
        case ReflectPin: 
          {
            reflect=!reflect;
          }
          break;

        }
      }
    }
  }

  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading; 
}

#endif


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
boolean pin2=false;
void bridge() {
  if (Serial.available()){
    char in = Serial.read();
    Serial.write(in);
    softserial.print(in);
    if( in=='$') {
      pin2=!pin2;
      digitalWrite(HC05_KEY_PIN, pin2?LOW:HIGH);
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


void btConnect() {
#ifndef SKIP_BT_CONNECT
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
#endif //SKIP_BT_CONNECT
}






















