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
  SoftwareSerial& serial;
  boolean echo;// = true;
  char buffer[40];
  int bufferIndex;
  String input;
public:
  InputBuffer(SoftwareSerial& serial):
  serial(serial) {
    echo=true;
    bufferIndex=0;
  }
  
  String getInput() {
    return input;
  }

  boolean listen() {
    if (serial.available()) {
      char read=serial.read();

      if('\n'==read || '\r'==read) {
        if(0!=bufferIndex) {
          buffer[bufferIndex++]='\0';
          input=String(buffer);
          if(echo) {
            Serial.println(input);
          }
          bufferIndex=0;
          return true;
        }
      }
      else {
        buffer[bufferIndex++]=read;
      }

      //      mySerial_m.write(read);
      return false;
    }
  }
};


//SoftwareSerial mySerial_s(10, 11); // RX, TX
SoftwareSerial softserial(8, 9); // RX, TX
 
InputBuffer input(softserial);
void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  //  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  //  mySerial_s.begin(38400);
  softserial.begin(38400);
  //  mySerial.println("Hello, world?");
}
//boolean echo = true;
//char buffer[40];
//int bufferIndex=0;
//String input;
void loop() // run over and over
{
  if (Serial.available()) {
    char read=Serial.read();
    //
    //    if('\n'==read || '\r'==read) {
    //      if(0!=bufferIndex) {
    //        buffer[bufferIndex++]='\0';
    //        input=String(buffer);
    //        if(echo) {
    //          Serial.println(input);
    //        }
    //        bufferIndex=0;
    //      }
    //    }
    //    else {
    //      buffer[bufferIndex++]=read;
    //    }
    //
    softserial.write(read);
  }
  if(input.listen()) {
    Serial.println(input.getInput());
  }
//  if (softserial.available()){
//    Serial.write(softserial.read());
//  }
}

















