

/*
 
 
 */
//#define DEBUG
//#define ITERACTION
//#define BRIDGE
//#define CANVAS_WRAPPER
//#define SKIP_SETUP
#define SKIP_CONNECT


#define MAX_BT_TRY 10
#define BT_BAUD_RATE 38400
#define MASTER_BT_ADDR "2013,9,260146"
#define ELM327_BT_ADDR "2013,9,110911"
//#define ELM327_BT_ADDR "19,5D,253224"

#define USE_ELM
#define USE_HC05
#define USE_SERIAL_CONTROL

#include <Arduino.h>
#include "LedControl.h"
//#include <GearLedControl.h>
#include <SoftwareSerial.h>

#ifdef USE_OBDSIM

#define OBD2_RX_PIN 6
#define OBD2_TX_PIN 7
SoftwareSerial softserial(OBD2_RX_PIN,OBD2_TX_PIN); // RX, TX

#else

#define OBD2_RX_PIN 8
#define OBD2_TX_PIN 9
SoftwareSerial softserial(OBD2_RX_PIN, OBD2_TX_PIN); // RX, TX

#endif

#ifdef USE_SERIAL_CONTROL
#include <SerialControl.h>
InputBuffer serialBuffer;
#endif



#ifdef USE_HC05
#include "HC05.h"
HC05Control hc05(softserial);
//ATCommand at;
#endif

#ifdef USE_ELM

#include <GearELM327.h>
ELM327 elm(softserial);
#include "elm.h"

#else

#include <OBD.h>
COBD obd(softserial);

#endif

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,1);
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


boolean autoconnect=true;
void displayDigit(int value);
#define HC05_KEY_PIN 2
const int buttonPin = 3;    // the number of the pushbutton pin
const int ledPin = 13;      // the number of the LED pin
//int ledState = HIGH;         // the current state of the output pin
void setup()  
{
  pinMode(HC05_KEY_PIN, OUTPUT);
  digitalWrite(HC05_KEY_PIN, HIGH);
  Serial.begin(9600);
  Serial.println("setup()");
  softserial.begin(BT_BAUD_RATE);
  initLedControl();
  displayDigit(168);

  // Open serial communications and wait for port to open:
  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for Leonardo only
  //  }


#ifdef SKIP_SETUP
  if(true) {
    return; 
  }
#endif


#ifndef SKIP_CONNECT
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
    digitalWrite(HC05_KEY_PIN, LOW);
    State state=hc05.getState();
    if(true==hc05.touchMaxWaitTimes) {
      Serial.println("TouchMaxWaitTimes"); 
    }
    else if(CONNECTED!=state) {
      Serial.println("Try connect");
      int x=0;
      for(;x<MAX_BT_TRY&&!hc05.sendCommandAndWaitOk("AT+LINK="+String(ELM327_BT_ADDR));x++) {
        if(16==hc05.errorcode) {
          if(hc05.sendCommandAndWaitOk("AT+INIT")) {
            Serial.println("SPP init.");
          }
          else {
            Serial.println("SPP init failed: "+hc05.getResponses()[0]);
          }
        }
      }

      if(MAX_BT_TRY==x) {
        Serial.println("Touch max bt try.");
      }
      else {
        Serial.println("BT Linked");
      }
      digitalWrite(HC05_KEY_PIN, HIGH);
    }

  }
#endif //USE_HC05
#endif //SKIP_CONNECT

  //  softserial.begin(9600);
#ifdef USE_ELM
  while (elm.begin()!=ELM_SUCCESS);  
#else //USE_ELM
  while (!obd.init());  
#endif //USE_ELM
  Serial.println("OBD Linked");
  displayDigit(0);

  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // set initial LED state
  digitalWrite(ledPin, LOW);
  delay(1000);
}

void bridge();
void interaction();
void processButton();

//boolean doLoop=true;
int rpm;
byte speed;
float voltage;
byte status;
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
        displayDigit(rpm/10);
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


#else //USE_ELM
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
#endif //USE_ELM
#endif //BRIDGE
  processButton();

}

// Variables will change:
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin
// the following variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long lastDebounceTime = 0;  // the last time the output pin was toggled
long debounceDelay = 50;    // the debounce time; increase if the output flickers

void processButton() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);

  // check to see if you just pressed the button 
  // (i.e. the input went from LOW to HIGH),  and you've waited 
  // long enough since the last press to ignore any noise:  

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  } 

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer
    // than the debounce delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      // set the LED:
      if (reading == HIGH) {
        digitalWrite(ledPin, HIGH);
        delay(32);
        digitalWrite(ledPin, LOW);
        funcselect++;
        funcselect=(3==funcselect)?0:funcselect;
      }
      // only toggle the LED if the new button state is HIGH
      //      if (buttonState == HIGH) {
      //        ledState = !ledState;
      //      }
    }
  }



  // save the reading.  Next time through the loop,
  // it'll be the lastButtonState:
  lastButtonState = reading; 
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

boolean pin2=false;
//#ifdef BRIDGE
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
//#endif

void displayDigit(int value) {
  //  Serial.println(value);
  int digit0=value%10;
  int digit1=(value/10)%10;
  int digit2=(value/100)%10;
  lc.setDigit(0,0,digit0,false);
  if(value>=10) {
    lc.setDigit(0,1,digit1,false);
    if( value>=100) {
      lc.setDigit(0,2,digit2,false);
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












































































































































































































