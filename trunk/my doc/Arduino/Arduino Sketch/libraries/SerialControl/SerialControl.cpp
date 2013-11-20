#include <Arduino.h>
#include "SerialControl.h"


InputBuffer:: InputBuffer(SoftwareSerial& serial):
serial(&serial),hardware(false) {
  echo=false;
  bufferIndex=0;
}

InputBuffer:: InputBuffer():  
hardware(true) {
  echo=false;
  bufferIndex=0;
}

void InputBuffer:: setEcho(boolean _echo) {
  echo=_echo;
}

String InputBuffer:: getLine() {
  return line;
}

boolean InputBuffer:: listen() {
#ifdef DEBUG
  //    Serial.println("InputBuffer debug listen()"); 
#endif
  if (hardware?Serial.available(): serial->available()) {
    read=hardware?Serial.read():serial->read();
#ifdef DEBUG
    //      Serial.print("InputBuffer debug "+read); 
#endif

    if('\n'==read || '\r'==read) {
      if(0!=bufferIndex) {
        buffer[bufferIndex++]='\0';
        line=String(buffer);
        if(echo) {
          Serial.println(line);
        }
        bufferIndex=0;
        return true;
      }
    }
    else {
      if(bufferIndex+1 >= MaxBufferSize){
#ifdef DEBUG
        Serial.println("InputBuffer debug bufferIndex+1 >= MaxBufferSize");
        return false;
#endif
      }
      buffer[bufferIndex++]=read;
    }

    return false;
  }
  return false;
}



SerialControl:: SerialControl(SoftwareSerial & _serial):
serial(_serial), buffer(InputBuffer(_serial)){

}
void  SerialControl:: sendString(String str) {
  serial.println(str);
}
boolean  SerialControl:: isResponse() {
  boolean listen= buffer.listen();
  if(listen) {
    response=buffer.getLine();
  }
  return listen;
}
String SerialControl::  getResponse() {
  return response;
}




