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

#include <SoftwareSerial.h>
//#include "OBD2.h"
//#include <canvas.h>
#include "io.h"
#include "HC05.h"
#include <ELM327.h>
#include "elm.h"

#ifdef CANVAS_WRAPPER
#include "canvas.h"
CanvasWrapper wrapper(canvas,20);
#endif


class ELM327 {
private:
  SerialControl serialControl;
  //  boolean ok;
  int responseIndex;
  char atoiBuffer[A2IBufferSize];
  String responses[ResponseMaxSize];
public:
  boolean touchMaxWaitTimes;

  ELM327(SoftwareSerial & _serial):
  serialControl(SerialControl(_serial))/*,ok(false),touchMaxWaitTimes(false)*/{
    responseIndex=0;
  }
  boolean sendCommandAndWaitOk(String command) {
    sendCommand(command);
    int x=0;
    touchMaxWaitTimes=false;
    for(;!isResponse()&&x<MaxWaitTimes;x++) {
      delay(DelayTime);
    };
    if(x==MaxWaitTimes) {
      touchMaxWaitTimes=true;
    }
    return false;
    //    return isResponseOk();
  }
  void sendCommand(String _command) {
    responseIndex=0;
    serialControl.sendString(_command);
  }

  boolean isResponse() {
    //    ok=false;

    if(serialControl.isResponse()) {
      String response=serialControl.getResponse();
#ifdef DEBUG
      Serial.println("ELM327 debug response "+response);
#endif

      //      if(response.startsWith(OK)) {
      //#ifdef DEBUG
      //        Serial.println("HC05Control debug ok");
      //#endif
      //        ok=true;
      //        return true;
      //      }
      //      else if(response.startsWith(ERROR)) {
      //#ifdef DEBUG
      //        Serial.println("HC05Control debug error");
      //#endif
      //        responses[0]=response;
      //
      //        int first=response.indexOf('(');
      //        int second=response.indexOf(')');
      //        String errorString=response.substring(first+1,second);
      //        errorString.toCharArray(atoiBuffer,A2IBufferSize);
      //        errorcode=  atoi(atoiBuffer);
      //#ifdef DEBUG
      //        Serial.println("HC05Control debug errorcode "+String(errorcode)+" "+errorString);
      //#endif
      //        return true;
      //      }
      //      else if(response.startsWith(FAIL)) {
      //#ifdef DEBUG
      //        Serial.println("HC05Control debug fail");
      //#endif
      //        responses[0]=response;
      //        return true;
      //      }
      //      else {
      //#ifdef DEBUG
      //        Serial.println("HC05Control debug ["+response+"]");
      //#endif
      //        if((responseIndex+1) >ResponseMaxSize) {
      //#ifdef DEBUG
      //          Serial.println("HC05Control debug responseIndex+1 >=ResponseMaxSize");
      //#endif
      //          return false;
      //        }
      //        responses[responseIndex++]=response;
      //        return false;
      //      }
    }
    else {
#ifdef DEBUG
      Serial.print(".");
#endif
      return false;
    }

  }
};


#define ELM_TIMEOUT 9000
#define ELM_BAUD_RATE 38400
#define ELM_PORT softserial

SoftwareSerial softserial(8, 9); // RX, TX
InputBuffer serialBuffer;
HC05Control hc05(softserial);
ELM327 elm(softserial);
//#define GEARUINO_SLAVE "2013,9,110911"
#define GEARUINO_SLAVE "19,5D,253224"
boolean autoconnect=true;
ATCommand at;
//COBD obd(softserial);



void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for Leonardo only
  //  }
  softserial.begin(38400);
#ifdef CANVAS_WRAPPER
  wrapper.clear();
#endif
  // elm.sendCommandAndWaitOk("AT");
  //  elm.sendCommandAndWaitOk("ATZ");
  //  
  //  if(true) return;

  //  if(hc05.sendCommandAndWaitOk("ATZ")) {
  //    Serial.println("ELM327 Linked"); 
  //    autoconnect=false;
  //  }

  if(autoconnect){
    Serial.println("Begin connect..."); 
    State state=hc05.getState();
    if(true==hc05.touchMaxWaitTimes) {
      Serial.println("TouchMaxWaitTimes"); 
      //      return;
    }
    else if(CONNECTED!=state) {
      Serial.println("Try connect");
      //    hc05.sendCommandAndWaitOk("AT+DISC");

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
    }

    Serial.println("BT Linked");

  }
    elm327Setup();
  //  canvas.setPaint(2,255,255,255,1);
  //  canvas.setText("BTLink");
  //  canvas.drawText(0,90,90);//big blue text
  //  while (!obd.init());  
  Serial.println("OBD Linked");
  //  canvas.setText("OBDLink");
  //  canvas.drawText(0,90,90);//big blue text


}


#ifdef ITERACTION
void interaction() {
  if(serialBuffer.listen()) {
    String line= serialBuffer.getLine();
    //    Serial.println("Send: "+line);
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
    //    if(in=='c') {
    //      Serial.println(hc05.getState());
    //    }
    //    else {
    softserial.print(in);
    //    }
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
#endif
  // elm.sendCommand("ATZ");
  //delay(1000);
  // elm.sendCommand("AT");
  //  Serial.println("loop");
  //  hc05.sendCommand("AT Z");
  //  int value;
  //  if (obd.ReadSensor(PID_RPM, value)) {
  //    // RPM is read and stored in 'value'
  //    // light on LED when RPM exceeds 5000
  //    digitalWrite(13, value > 5000 ? HIGH : LOW);
  //    //    canvas.setText(String(value));
  //    //    canvas.drawText(0,90,90);//big blue text
  //    Serial.println(value);
  //  }
}













































































































































