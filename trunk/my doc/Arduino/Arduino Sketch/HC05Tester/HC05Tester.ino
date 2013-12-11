/*
  AnalogReadSerial
 Reads an analog input on pin 0, prints the result to the serial monitor.
 Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.
 
 This example code is in the public domain.
 */
//#define USE_AT_COMMAND
//#define DEBUG

#include <SoftwareSerial.h>
#include <SerialControl.h>
#include "HC05.h"
#include <SerialControl.h>

InputBuffer serialBuffer;
static const int OBD2RXPin = 8;
static const int OBD2TXPin = 9;
SoftwareSerial softserial(OBD2RXPin, OBD2TXPin); // RX, TX
HC05Control hc05(softserial);
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  softserial.begin(9600);
}
void interaction() {
  if(serialBuffer.listen()) {
    String line= serialBuffer.getLine();
    hc05.sendCommand(line);
  }
  if(hc05.isResponse()) {
    if(hc05.isResponseOk()) {
      String *vec=hc05.getResponses();
      int size=hc05.getResponseSize();
      //if(size==0) {


      //}
      for(int x=0;x<size;x++) {
        String s = vec[x];
        Serial.println(s);
      }
      Serial.println("Ok");
    }
    else if(hc05.isInquiry()) {
      ATCommand cmd(hc05.inquiry);
      RSSI rssi(cmd.param3);
//      char buf[5];
//      cmd.param3.toCharArray(buf,5);
//      int rssi=strtol(buf,NULL,16);
      Serial.println( cmd.command+" (addr)"+cmd.param1+" (class)"+cmd.param2 +" (rssi)"+rssi.toString());
    }    
    else {
      Serial.println("? " +hc05.getResponses()[0]);
    }
  }
}

void bridge() {
  if (Serial.available()){
    char in = Serial.read();
    Serial.write(in);

    //    if( in=='$') {
    //      hc05KeyPin=!hc05KeyPin;
    //      digitalWrite(HC05KeyPin, hc05KeyPin?LOW:HIGH);
    //    }
    //    else if( in=='%') {
    //      hc05BaudRate=!hc05BaudRate;
    //      if(hc05BaudRate) {
    //        softserial.begin(38400);
    //      }
    //      else {
    //        softserial.begin(9600);
    //      }
    //    }
    //    else {
    softserial.print(in);
    //    }
  }
  if (softserial.available()) {
    Serial.write(softserial.read());
  }
}

// the loop routine runs over and over again forever:
void loop() {
  interaction();
  //  bridge();
}







