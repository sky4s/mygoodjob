/*
  Software serial multple serial test
 
 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.
 
 The circuit: 
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
#include <SoftwareSerial.h>

class InputBuffer {
private:
  SoftwareSerial* serial;
  boolean echo;
  char buffer[40];
  int bufferIndex;
  String line;
  boolean hardware;
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
    if (hardware?Serial.available(): serial->available()) {
      char read=hardware?Serial.read():serial->read();

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
public:
  SerialControl(SoftwareSerial & _serial):
  serial(_serial), buffer(InputBuffer(_serial)){

  }
  void sendString(String str) {
//    Serial.println(str);
//    serial.print(str+21+"\r");
//    serial.print(str);
    serial.println(str);
  }
  boolean isResponse() {
    return buffer.listen();
  }
  String getResponse() {
    return buffer.getLine();
  }

};

SoftwareSerial softserial(8, 9); // RX, TX
SerialControl serialControl(softserial);
InputBuffer serialBuffer;
void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  softserial.begin(38400);
  //  serialBuffer.setEcho(true);
}

void loop() // run over and over
{
  if(serialBuffer.listen()) {
    String line= serialBuffer.getLine();
    serialControl.sendString(line);
  }
    if(serialControl.isResponse()) {
      Serial.println(serialControl.getResponse());
    }

}




























