#ifndef SERIAL_CONTROL_H
#define SERIAL_CONTROL_H
#include <Arduino.h>
#include <SoftwareSerial.h>

static const int MaxBufferSize = 40;
class InputBuffer {
private:
  SoftwareSerial* serial;
  boolean echo;
  char buffer[MaxBufferSize];
  int bufferIndex;
  String line;
  boolean hardware;
  char read;
public:
  InputBuffer(SoftwareSerial& serial);

  InputBuffer();

  void setEcho(boolean _echo) ;

  String getLine();

  boolean listen() ;
};

class SerialControl {
private:
  SoftwareSerial&  serial;
  InputBuffer buffer;
  String response;
public:
  SerialControl(SoftwareSerial & _serial);
  void sendString(String str) ;
  boolean isResponse() ;
  String getResponse();

};

#endif
