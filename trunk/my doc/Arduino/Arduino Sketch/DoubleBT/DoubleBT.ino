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

#define DEBUG
//#define GEARUINO_Vector

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
    if (hardware?Serial.available(): serial->available()) {
      read=hardware?Serial.read():serial->read();
#ifdef DEBUG
      Serial.print(read); 
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
          Serial.println("bufferIndex+1 >= MaxBufferSize");
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


static const String OK="OK";
static const String ERROR="ERROR";
static const int ResponseMaxSize = 10;
class HC05Control {
private:
  SerialControl serialControl;
  boolean error;
  String responses[ResponseMaxSize];
  int responseIndex;
public:

  HC05Control(SoftwareSerial & _serial):
  serialControl(SerialControl(_serial)),error(false){
    responseIndex=0;
  }
  boolean sendCommandAndWaitOk(String command) {
    sendCommand(command);
    while (isResponse()) ;
    //    Serial.println(command);
    //        Serial.println("is"+isResponseOk());
    //        Serial.println(responses[0]);
    return isResponseOk();
  }
  void sendCommand(String _command) {
    //    command=_command;
    responseIndex=0;
    serialControl.sendString(_command);
#ifdef DEBUG
    Serial.println("HC05Control debug "+_command);
#endif
  }
  boolean isResponse() {
    if(serialControl.isResponse()) {
      String response=serialControl.getResponse();
#ifdef DEBUG
      Serial.println("HC05Control debug "+response);
#endif
      if(response.startsWith(OK)) {
#ifdef DEBUG
        Serial.println("HC05Control debug ok");
#endif
        error=false;
        return true;
      }
      else if(response.startsWith(ERROR)) {
#ifdef DEBUG
        Serial.println("HC05Control debug error");
#endif
        error=true;
        responses[0]=response;
        return true;
      }
      else {
#ifdef DEBUG
        Serial.println("HC05Control debug ["+response+"]");
#endif
        if((responseIndex+1) >ResponseMaxSize) {
#ifdef DEBUG
          Serial.println("responseIndex+1 >=ResponseMaxSize");
#endif
          return false;
        }
        responses[responseIndex++]=response;
        return false;
      }
    }
    return false;
  }

  boolean isResponseOk() {
#ifdef DEBUG
    Serial.println("HC05Control debug isResponseOk() "+String(error?"err":"ok"));
#endif
    return !error;
  }

  String*  getResponses() {
    return responses;
  }
  int getResponseSize() {
    return responseIndex;
  }
  //  String command;

};


SoftwareSerial softserial(8, 9); // RX, TX
InputBuffer serialBuffer;
HC05Control hc05(softserial);
#define GEARUINI_SLAVE "2013,9,110911"
void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  //  while (!Serial) {
  //    ; // wait for serial port to connect. Needed for Leonardo only
  //  }
  softserial.begin(38400);


  //  hc05.sendCommandAndWaitOk("AT+INQM=1,"+String(ResponseMaxSize)+",24");
  //  if(hc05.sendCommandAndWaitOk("AT+BIND="+String(GEARUINI_SLAVE))){
  //    Serial.println("Bind to "+String(GEARUINI_SLAVE));
  //  }


  //  if(hc05.sendCommandAndWaitOk("AT+DISC")) {
  //    Serial.println(hc05.getResponses()[0]);
  //  }
  //if(true) {
  //  return;
  //}
  if(hc05.sendCommandAndWaitOk("AT+LINK="+String(GEARUINI_SLAVE))){
    Serial.println("XXX??");    
    Serial.println("Link to "+String(GEARUINI_SLAVE));
  }
  else /*if( hc05.getResponses()[0].equals( "ERROR:(16)"))*/ {
    Serial.println("XXX");    
    if(hc05.sendCommandAndWaitOk("AT+INIT")) {
      Serial.println("SPP init.");
    }
    else {
      Serial.println("SPP init failed: "+hc05.getResponses()[0]);
    }
    if(hc05.sendCommandAndWaitOk("AT+LINK="+String(GEARUINI_SLAVE))){
      Serial.println("Link to "+String(GEARUINI_SLAVE));
    }
  }
}
ATCommand at;
//#define ITERACTION
#define BRIDGE
void loop() // run over and over
{
  //  if(hc05.sendCommandAndWaitOk("a")) {
  //    Serial.println("AT ok");
  //    delay(500);
  //  }else {
  //    Serial.println("err");
  //  }
#ifdef ITERACTION
  //  String line;
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
      Serial.println("? "+hc05.command+" "+hc05.getResponses()[0]);
    }
  }
#endif
#ifdef BRIDGE
  if (Serial.available()){
    char in = Serial.read();
    Serial.write(in);
    softserial.print(in);
  }
  if (softserial.available()) {
    Serial.write(softserial.read());
  }
#endif
}

















































































