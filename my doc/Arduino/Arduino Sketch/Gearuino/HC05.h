#ifndef HC05_H
#define HC05_H
#include <SerialControl.h>

//#ifdef USE_AT_COMMAND
class ATCommand {
private:
  char buf[MaxBufferSize];
  void init(String cmd) {
    cmd.toCharArray(buf,MaxBufferSize);
    command = String(strtok(buf,":+"));
    char* p=NULL;
    for(int x=0;x<3;x++) {
      p=strtok(NULL,",");

      //#ifdef DEBUG
      //      Serial.println(String(x)+" "+String(p));
      //#endif

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
      if(NULL==p) {
        break;
      }
    }

  }
public:
  String command;
  String param1;
  String param2;
  String param3;
  ATCommand(String cmd) {
    param1=NULL;
    param2=NULL;
    param3=NULL;
    init(cmd);
  }
  ATCommand() {
  }
  void parse(String cmd) {
    init(cmd);
  }
  String toString() {
    return command
      +((NULL==param1?"":","+param1)
      +(NULL==param2?"":","+param2
      +(NULL==param3?"":","+param3 ) )  );

  }

  String addressToParam(char* address) {
    char* p1 = strtok(address,":");
    char* p2 = strtok(NULL,":");
    char* p3 = strtok(NULL,":");
    return String(p1)+","+String(p2)+","+String(p3);
  }
};
//#endif

enum RSSIDesc {
  Poor,Weak,Good
};

class RSSI {
private:
  int rssi;
public:
  RSSI(String _rssi){
    char buf[5];
    _rssi.toCharArray(buf,5);
    int rssi=strtol(buf,NULL,16);
  }
  RSSIDesc getRSSIDesc() {
    if(rssi<-95) {
      return Poor;
    }
    else if(-95<=rssi && rssi <-90) {
      return Weak;
    }
    else  if(-90<= rssi) {
      return Good;
    }
  }

  String toString() {
    RSSIDesc desc=  getRSSIDesc();
    switch(desc) {
      case Poor:
      return "Poor";
    case Weak:
      return"Weak";
    case Good:
      return "Good";
    }
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
static const String INQ="+INQ";
static const int ResponseMaxSize = 10;

static const int MaxWaitTimes = 30;
static const int DelayTime = 500;
static const int A2IBufferSize=3;


class HC05Control {
private:
  SerialControl serialControl;
  boolean ok;
  int responseIndex;
  char atoiBuffer[A2IBufferSize];
  String responses[ResponseMaxSize];
  boolean inq;
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
    inq=false;
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
      else if(response.startsWith(INQ)) {
        inquiry=response;
        inq=true;
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
      //      Serial.print(".");
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
  String inquiry;
  boolean isInquiry() {
    return inq;
  } 
};

#endif

















