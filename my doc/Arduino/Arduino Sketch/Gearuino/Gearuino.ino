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
#define DEBUG_MODE
#define BT_BAUD_RATE 38400


#define USE_ELM
#define USE_HC05
#define USE_SERIAL_CONTROL
//#define USE_OBDSIM

#include <Arduino.h>
#include "LedControl.h"
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

#define MASTER_BT_ADDR "2013,9,260146"
#define ELM327_BT_ADDR "2013,9,110911"
//#define ELM327_BT_ADDR "19,5D,253224"

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
  lc.setScanLimit(0,3);
}


boolean autoconnect=true;
void displayDigit(int value);
void setup()  
{
  Serial.begin(9600);
  Serial.println("setup()");
  initLedControl();
  displayDigit(168);
  // Open serial communications and wait for port to open:

  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for Leonardo only
  //  }

  softserial.begin(BT_BAUD_RATE);
#ifdef DEBUG_MODE
  if(true) {
    return; 
  }
#endif

#ifdef USE_OBDSIM
  //  softserial.begin(9600);
#else //USE_OBDSIM
#ifdef USE_ELM
  //  softserial.begin(38400);
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
    Serial.println("OBD connecting test OK."); 
  }
#endif //USE_ELM

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
      while(!hc05.sendCommandAndWaitOk("AT+LINK="+String(ELM327_BT_ADDR))) {
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
#endif //USE_HC05
#endif //USE_OBDSIM

  //  softserial.begin(9600);
#ifdef USE_ELM
  printStatus(elm.begin());
#else //USE_ELM
  while (!obd.init());  
#endif //USE_ELM
  Serial.println("OBD Linked");
  displayDigit(0);
  delay(1000);
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
  byte value;
  float voltage;
  byte status=elm.getVoltage(voltage);
  if (status== ELM_SUCCESS ) {
    int intvoltage=(int)(voltage*10);
    Serial.println("Voltage: "+String(intvoltage));
    displayDigit(intvoltage);
  }
  else {
    printStatus(status);
  }

#else
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
#endif
#endif
}























































































































































































