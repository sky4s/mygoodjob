#ifndef IO_H
#define IO_H


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
  InputBuffer(SoftwareSerial& serial):
  serial(&serial),hardware(false) {
    echo=false;
    bufferIndex=0;
  }

  InputBuffer():  
  hardware(true) {
    echo=false;
    bufferIndex=0;
  }

  void setEcho(boolean _echo) {
    echo=_echo;
  }

  String getLine() {
    return line;
  }

  boolean listen() {
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
  }
};

class SerialControl {
private:
  SoftwareSerial&  serial;
  InputBuffer buffer;
  String response;
public:
  SerialControl(SoftwareSerial & _serial):
  serial(_serial), buffer(InputBuffer(_serial)){

  }
  void sendString(String str) {
    serial.println(str);
  }
  boolean isResponse() {
    boolean listen= buffer.listen();
    if(listen) {
      response=buffer.getLine();
    }
    return listen;
  }
  String getResponse() {
    return response;
  }

};

#endif
