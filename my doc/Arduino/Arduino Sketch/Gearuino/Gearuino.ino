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
#include <SoftwareSerial.h>
#include "OBD2.h"
#include <canvas.h>

//#define DEBUG
//#define GEARUINO_Vector
//#define ITERACTION
//#define BRIDGE

//#ifdef GEARUINO_Vector
//template<typename Data>
//class Vector {
//  size_t d_size; // Stores no. of actually stored objects
//  size_t d_capacity; // Stores allocated capacity
//  Data *d_data; // Stores data
//public:
//  Vector() : 
//  d_size(0), d_capacity(0), d_data(0) {
//
//  }; // Default constructor
//  Vector(int initcapacity) : 
//  d_size(0),   d_data(0) {
//    init(initcapacity);
//  }; 
//  Vector(Vector const &other) : 
//  d_size(other.d_size), d_capacity(other.d_capacity), d_data(0) { 
//    d_data = (Data *)malloc(d_capacity*sizeof(Data)); 
//    memcpy(d_data, other.d_data, d_size*sizeof(Data)); 
//  }; // Copy constuctor
//  ~Vector() { 
//    free(d_data); 
//  }; // Destructor
//  Vector &operator=(Vector const &other) { 
//    free(d_data); 
//    d_size = other.d_size; 
//    d_capacity = other.d_capacity; 
//    d_data = (Data *)malloc(d_capacity*sizeof(Data)); 
//    memcpy(d_data, other.d_data, d_size*sizeof(Data)); 
//    return *this; 
//  }; // Needed for memory management
//  void push_back(Data const &x) { 
//    if (d_capacity == d_size) resize(); 
//    d_data[d_size++] = x; 
//  }; // Adds new value. If needed, allocates more space
//  size_t size() const { 
//    return d_size; 
//  }; // Size getter
//  Data const &operator[](size_t idx) const { 
//    return d_data[idx]; 
//  }; // Const getter
//  Data &operator[](size_t idx) { 
//    return d_data[idx]; 
//  }; // Changeable getter
//private:
//  void init(int initcapacity) {
//    d_capacity=initcapacity;
//    d_data = (Data *)malloc(d_capacity*sizeof(Data)); 
//  };
//  void resize() { 
//    d_capacity = d_capacity ? d_capacity*2 : 1; 
//    Data *newdata = (Data *)malloc(d_capacity*sizeof(Data)); 
//    memcpy(newdata, d_data, d_size * sizeof(Data)); 
//    free(d_data); 
//    d_data = newdata; 
//  };// Allocates double the old space
//};
//#endif


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

class ATCommand {
private:
  char buf[MaxBufferSize];
  void init(String cmd) {
    cmd.toCharArray(buf,MaxBufferSize);
    command = strtok(buf,":+");
    char* p="";
    for(int x=0;x<3&&NULL!=p;x++) {
      p=strtok(NULL,",");
      //      Serial.println(p);
      switch(x) {
      case 0:
        param1=p;
        break;
      case 1:
        param2=p;
        break;
      case 2: 
        param3=p;
        break;
      }
    }

  }
public:
  char* command;
  char* param1;
  char* param2;
  char* param3;
  ATCommand(String cmd) {
    init(cmd);
  }
  ATCommand() {
  }
  void parse(String cmd) {
    init(cmd);
  }
  String toString() {
    return String(command)+","+String(param1) +( (param2!=NULL)?","+String(param2):"")+ ((param3!=NULL)?","+String(param3):""); 
  }

  String addressToParam(char* address) {
    char* p1 = strtok(address,":");
    char* p2 = strtok(NULL,":");
    char* p3 = strtok(NULL,":");
    return String(p1)+","+String(p2)+","+String(p3);
  }
};

enum State {
  INITIALIZED,
  READY,
  PAIRABLE,
  PAIRED,
  INQUIRING,
  CONNECTING,
  CONNECTED,
  DISCONNECTED,
  UNKNOW
};

static const String OK="OK";
static const String ERROR="ERROR";
static const String FAIL="FAIL";
static const int ResponseMaxSize = 10;
static const int MaxWaitTimes = 30;
static const int DelayTime = 500;
static const int A2IBufferSize=3;
class HC05Control {
private:
  SerialControl serialControl;
  boolean ok;
  String responses[ResponseMaxSize];
  int responseIndex;
  char atoiBuffer[A2IBufferSize];
public:

  HC05Control(SoftwareSerial & _serial):
  serialControl(SerialControl(_serial)),ok(false),touchMaxWaitTimes(false){
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

    return isResponseOk();
  }
  void sendCommand(String _command) {
    responseIndex=0;
    serialControl.sendString(_command);
#ifdef DEBUG
    Serial.println("HC05Control debug "+_command);
#endif
  }

  State getState() {
    if(sendCommandAndWaitOk("AT+STATE")) {
      String response=responses[0];
      int index=response.indexOf(':');
      String statestr=response.substring(index+1);
#ifdef DEBUG
      Serial.println("HC05Control debug getState() "+statestr+"/"+response[0]);
#endif
      if(statestr=="INITIALIZED") {
        return INITIALIZED;
      }
      else  if(statestr.equals("READY")) {
        return READY;
      }
      else  if(statestr.equals("PAIRABLE")) {
        return PAIRABLE;
      } 
      else  if(statestr.equals("PAIRED")) {
        return PAIRED;
      } 
      else  if(statestr.equals("INQUIRING")) {
        return INQUIRING;
      } 
      else  if(statestr.equals("CONNECTING")) {
        return CONNECTING;
      } 
      else  if(statestr.equals("CONNECTED")) {
        return CONNECTED;
      } 
      else  if(statestr.equals("DISCONNECTED")) {
        return DISCONNECTED;
      }
      else {
        return UNKNOW;
      }
    }
    return UNKNOW;
  }

  boolean isResponse() {
    ok=false;
    if(serialControl.isResponse()) {
      String response=serialControl.getResponse();
#ifdef DEBUG
      Serial.println("HC05Control debug response "+response);
#endif

      if(response.startsWith(OK)) {
#ifdef DEBUG
        Serial.println("HC05Control debug ok");
#endif
        ok=true;
        return true;
      }
      else if(response.startsWith(ERROR)) {
#ifdef DEBUG
        Serial.println("HC05Control debug error");
#endif
        responses[0]=response;

        int first=response.indexOf('(');
        int second=response.indexOf(')');
        String errorString=response.substring(first+1,second);
        errorString.toCharArray(atoiBuffer,A2IBufferSize);
        errorcode=  atoi(atoiBuffer);
#ifdef DEBUG
        Serial.println("HC05Control debug errorcode "+String(errorcode)+" "+errorString);
#endif
        return true;
      }
      else if(response.startsWith(FAIL)) {
#ifdef DEBUG
        Serial.println("HC05Control debug fail");
#endif
        responses[0]=response;
        return true;
      }
      else {
#ifdef DEBUG
        Serial.println("HC05Control debug ["+response+"]");
#endif
        if((responseIndex+1) >ResponseMaxSize) {
#ifdef DEBUG
          Serial.println("HC05Control debug responseIndex+1 >=ResponseMaxSize");
#endif
          return false;
        }
        responses[responseIndex++]=response;
        return false;
      }
    }
    else {
#ifdef DEBUG
      //      Serial.println("HC05Control debug no response");
      Serial.print(".");
#endif
      return false;
    }

  }

  boolean isResponseOk() {
#ifdef DEBUG
    Serial.println("HC05Control debug isResponseOk() "+String(ok?"Yes":"No"));
#endif
    return ok;
  }

  String*  getResponses() {
    return responses;
  }
  int getResponseSize() {
    return responseIndex;
  }
  int errorcode;
  boolean touchMaxWaitTimes;

};


SoftwareSerial softserial(8, 9); // RX, TX
InputBuffer serialBuffer;
HC05Control hc05(softserial);
//#define GEARUINO_SLAVE "2013,9,110911"
#define GEARUINO_SLAVE "19,5D,253224"
boolean autoconnect=false;
ATCommand at;
COBD obd(softserial);

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for Leonardo only
  //  }
  softserial.begin(38400);

  if(autoconnect){
    State state=hc05.getState();
    if(true==hc05.touchMaxWaitTimes) {
      Serial.println("TouchMaxWaitTimes"); 
      return;
    }
    //    Serial.println(state);
    if(CONNECTED!=state) {
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

    Serial.println("Linked");

  }
  while (!obd.Init());  
  canvas.setPaint(1,0,0,0,1);
  canvas.drawRect(0,0,4000,2250); // set full screen to white
  canvas.setPaint(20,0,0,255,1);
  canvas.setText("ABCDEFGH");
  canvas.drawText(0,2250,950);//big blue text
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
  //  Serial.println(hc05.getState());
  //  delay(500);
#ifdef ITERACTION
  interaction();
#endif
#ifdef BRIDGE
  bridge();
#endif

  int value;
  if (obd.ReadSensor(PID_RPM, value)) {
    // RPM is read and stored in 'value'
    // light on LED when RPM exceeds 5000
    //    digitalWrite(13, value > 5000 ? HIGH : LOW);

  }
}

























































































































