#ifndef DEBUG_H
#define DEBUG_H

#ifdef ITERACTION
void interaction() {
  if(serialBuffer.listen()) {
    String line= serialBuffer.getLine();
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

#ifdef USE_HC05
boolean hc05KeyPin=false;
boolean hc05BaudRate=false;
#endif

void bridge() {
  if (Serial.available()){
    char in = Serial.read();
    Serial.write(in);


    if( in=='$') {
#ifdef USE_HC05
      hc05KeyPin=!hc05KeyPin;
      digitalWrite(HC05KeyPin, hc05KeyPin?LOW:HIGH);
#endif
    }
    else if( in=='%') {
#ifdef USE_HC05
      hc05BaudRate=!hc05BaudRate;
      if(hc05BaudRate) {
        softserial.begin(38400);
      }
      else {
        softserial.begin(9600);
      }
#endif
    }
    else {
      softserial.print(in);
    }
  }
  if (softserial.available()) {
    Serial.write(softserial.read());
  }
}
#endif

#endif
