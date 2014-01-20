#ifndef LED_H
#define LED_H

boolean ledReflect = false;
boolean commonAnodeLED=false;
/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn e
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
//LedControl lc=LedControl(12,11,10,1,commonAnodeLED,false,!ledReflect);
LedControl lc=LedControl(LED_DATA_PIN,LED_CLK_PIN,LED_LOAD_PIN,1,commonAnodeLED,false,!ledReflect);

void displayGear(byte gear) {
  lc.upsidedownMode=!ledReflect;
  lc.setDigit(0,2,gear,false);
  lc.setChar(0,1,' ',false);
  lc.setChar(0,0,' ',false);
}

void displayKPL(float kpl) {

}


void displayRPM(int rpm) {
  int digit = rpm/1000;
  int circle = (rpm-digit*1000)/111; //one piece is 111 rpm
  //  Serial.println(String(circle));
  if( 9==circle) {
    circle=0;
    digit++; 
  }
  lc.upsidedownMode=!ledReflect;
  if(digit>0) {
    lc.setDigit(0,2,digit,false);
  }
  else {
    lc.setChar(0,2,' ',false);
  }
  byte v0=0;
  byte v1=0;
  //pABCDEFG
  if( circle>=1) {
    v1=v1|B00000100;
  }
  if( circle>=2) {
    v1=v1|B00000010;
  }
  if( circle>=3) {
    v1=v1|B01000000;
  }
  if( circle>=4) {
    v0=v0|B01000000;
  }
  if( circle>=5) {
    v0=v0|B00100000;
  }
  if( circle>=6) {
    v0=v0|B00010000;
  }
  if( circle>=7) {
    v0=v0|B00001000;
  }
  if( circle>=8) {
    v1=v1|B00001000;
  }
  lc.setSegment(0,0,v0 );
  lc.setSegment(0,1,v1 );
}

void displayDigit(int value) {
  if(-1==value) {
    lc.setChar(0,0,' ',false);
    lc.setChar(0,1,' ',false);
    lc.setChar(0,2,' ',false);
    return;
  }

  int digit0=value%10;
  int digit1=(value/10)%10;
  int digit2=(value/100)%10;
  lc.upsidedownMode=!ledReflect;
  lc.setDigit(0,2,digit0,false );
  if(value>=10) {
    lc.setDigit(0,1,digit1,false );
    if( value>=100) {
      lc.setDigit(0,0,digit2,false );
    }
    else {
      lc.setChar(0,0,' ',false);
    }
  }
  else {
    lc.setChar(0,1,' ',false);
    lc.setChar(0,0,' ',false);
  }

}

void initLedControl() {
  /*
   The MAX72XX is in power-sav  ing mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,15);
  /* and clear the display */
  lc.clearDisplay(0);
  lc.setScanLimit(0,2);
}

#endif
