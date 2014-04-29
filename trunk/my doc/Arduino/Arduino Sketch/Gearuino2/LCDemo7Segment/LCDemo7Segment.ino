//We always have to include the library
#include "GearLedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,2);

/* we always wait a bit between updates of the display */
unsigned long delaytime=1000;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,15);
  /* and clear the display */
  lc.clearDisplay(0);

  lc.shutdown(1,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(1,15);
  /* and clear the display */
  lc.clearDisplay(1);
}


/*
 This method will display the characters for the
 word "Arduino" one after the other on digit 0. 
 */
void writeArduinoOn7Segment() {
  int x=0;
  //  for(int x=0;x<7;x++) {
  lc.setChar(0,x,'a',false);
  delay(delaytime);
  lc.setRow(0,x,0x05);
  delay(delaytime);
  lc.setChar(0,x,'d',false);
  delay(delaytime);
  lc.setRow(0,x,0x1c);
  delay(delaytime);
  lc.setRow(0,x,B00010000);
  delay(delaytime);
  lc.setRow(0,x,0x15);
  delay(delaytime);
  lc.setRow(0,x,0x1D);
  delay(delaytime);
  lc.clearDisplay(0);
  delay(delaytime);
  //  }
} 

/*
  This method will scroll all the hexa-decimal
 numbers and letters on the display. You will need at least
 four 7-Segment digits. otherwise it won't really look that good.
 */
void scrollDigits() {
  for(int i=0;i<13;i++) {
    lc.setDigit(0,1,i,false);
    lc.setDigit(0,5,i+1,false);
    lc.setDigit(0,7,i+2,false);
    lc.setDigit(0,2,i+3,false);
    //    lc.setDigit(0,3,i+4,false);
    lc.setDigit(0,6,i+4,false);
    lc.setDigit(0,4,i+5,false);
    lc.setDigit(0,0,i+6,false);
    delay(delaytime);
  }
  lc.clearDisplay(0);
  delay(delaytime);
}

//=======================================================================================
// 陰極: 11111111 00     000000 2222
//
int posarray[8] = {
  1,6,2 ,7,4,0,5,3
};

void loop() { 
  //  writeArduinoOn7Segment();
  //  scrollDigits();

  int addr=1;
  //  for(int x=0;x<=9;x++) {
  //    lc.setDigit(addr,1,x,false);
  //    lc.setDigit(addr,5,(x+1)%10,false);
  //    lc.setDigit(addr,7,(x+2)%10,false);
  //    //    lc.setIntensity(0,1);
  //    lc.setDigit(addr,2,(x+3)%10,false);
  //    //    lc.setIntensity(0,15);
  //    lc.setDigit(addr,6,(x+4)%10,false);
  //    lc.setDigit(addr,4,(x+5)%10,false);
  //    lc.setDigit(addr,0,(x+6)%10,false);
  //    delay(delaytime);
  //  }
  //  lc.clearDisplay(1);

  for(int x=0;x<8;x++) {
    int pos=posarray[x];
    lc.clearDisplay(1);
    lc.setLed(1,1,pos,true);
    delay(delaytime);
  }

  //  }
}



















