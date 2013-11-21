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
//#define BRIDGE
//#define CANVAS_WRAPPER


#define USE_ELM
#define USE_HC05
#define USE_SERIAL_CONTROL
#define USE_SOFT_SERIAL
#define USE_OBDSIM

#include <Arduino.h>

#ifdef USE_SOFT_SERIAL
#include <SoftwareSerial.h>
#ifdef USE_OBDSIM
SoftwareSerial softserial(6, 7); // RX, TX
#else
SoftwareSerial softserial(8, 9); // RX, TX
#endif
#endif

#ifdef USE_SERIAL_CONTROL
#include <SerialControl.h>
InputBuffer serialBuffer;
#endif


//#define GEARUINO_SLAVE "2013,9,110911"
#define GEARUINO_SLAVE "19,5D,253224"
boolean autoconnect=true;


#ifdef USE_HC05
#include "HC05.h"
HC05Control hc05(softserial);
//ATCommand at;
#endif


#ifdef USE_ELM
#include <GearELM327.h>
ELM327 elm(softserial);
//#include <ELM327.h>
//Elm327 elm(softserial);
#include "elm.h"
#else
#include <OBD.h>
COBD obd(softserial);
#endif


void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for Leonardo only
  //  }

#ifdef USE_OBDSIM
  softserial.begin(9600);
#else
  softserial.begin(38400);
#endif


#ifdef USE_ELM
//  printStatus(elm.begin());
  autoconnect=(ELM_SUCCESS!=elm.begin());
#else
  autoconnect=!obd.init();  
#endif

#ifdef USE_HC05
  if(autoconnect){
    Serial.println("Begin connect..."); 
    State state=hc05.getState();
    if(true==hc05.touchMaxWaitTimes) {
      Serial.println("TouchMaxWaitTimes"); 
      //      return;
    }
    else if(CONNECTED!=state) {
      Serial.println("Try connect");
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
      Serial.println("BT Linked");
    }

  }
#endif

#ifdef USE_ELM
  printStatus(elm.begin());
#else
  while (!obd.init());  
#endif
  Serial.println("OBD Linked");
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
void bridge() {
  if (Serial.available()){
    char in = Serial.read();
    Serial.write(in);
    softserial.print(in);
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
#else
#ifdef USE_ELM
  int value;
  byte status=elm.engineRPM(value);
  if (status== ELM_SUCCESS ) {
    Serial.println("RPM: "+String(value));
  }
  else {
    printStatus(status);
  }

#else
  int value;
  if (obd.readSensor(PID_RPM, value)) {
    // RPM is read and stored in 'value'
    // light on LED when RPM exceeds 5000
    //    digitalWrite(13, value > 5000 ? HIGH : LOW);
    Serial.println("RPM: "+String(value));
  }
  if (obd.readSensor(PID_SPEED, value)) {
    // RPM is read and stored in 'value'
    // light on LED when RPM exceeds 5000
    //    digitalWrite(13, value > 5000 ? HIGH : LOW);
    Serial.println("Speed: "+String(value));
  }
#endif
#endif
}






























































































































































