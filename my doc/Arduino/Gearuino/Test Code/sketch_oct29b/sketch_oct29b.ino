#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=50;

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
  lc.setScanLimit(0,2);
}


/*
 This method will display the characters for the
 word "Arduino" one after the other on digit 0. 
 */
void writeArduinoOn7Segment() { 
//  for(int x=0;x<=299;x++) {
//
//     int d0=x%10;
//     int d1=(x-d0)/10%10;
//     int d3=x/100;
//
//     lc.setChar(0,0,'0'+d0,false);
//     if( x>10) {
//       lc.setChar(0,1,'0'+d1,false);
//     }
//     else {
//       lc.setChar(0,1,' ',false);
//     }
//     if( d3 ==0) {
//       lc.setChar(0,2,' ',false); 
//     }else {
//       lc.setChar(0,2,'0'+d3,false);
//     }
//     
//     
//     delay(delaytime);
//  }
   
    for(int x=0;x<=9;x++) {
      lc.setChar(0,0,'0'+x,false); 
      lc.setChar(0,1,'0'+x,false); 
      lc.setChar(0,2,'0'+x,false);       
      delay(delaytime*5);
    }
//  lc.setChar(0,0,'0',false);
//  delay(delaytime);
//  lc.setChar(0,0,'1',false);
//  delay(delaytime);
//  lc.setChar(0,0,'2',false);
//  delay(delaytime);
//  lc.setChar(0,0,'3',false);
//  delay(delaytime);
//  lc.setChar(0,0,'4',false);
//  delay(delaytime);
//  lc.setChar(0,0,'5',false);
//  delay(delaytime);
//  lc.setChar(0,0,'6',false);
//  delay(delaytime);
//  lc.setChar(0,0,'7',false);
//  delay(delaytime);
//  lc.setChar(0,0,'8',false);
//  delay(delaytime);
//  lc.setChar(0,0,'9',false);
//  delay(delaytime);  
  
//  lc.setChar(0,0,'a',false);
//  delay(delaytime);
//  lc.setRow(0,0,0x05);
//  delay(delaytime);
//  lc.setChar(0,0,'d',false);
//  delay(delaytime);
//  lc.setRow(0,0,0x1c);
//  delay(delaytime);
//  lc.setRow(0,0,B00010000);
//  delay(delaytime);
//  lc.setRow(0,0,0x15);
//  delay(delaytime);
//  lc.setRow(0,0,0x1D);
//  delay(delaytime);
//  lc.clearDisplay(0);
//  delay(delaytime);
} 

/*
  This method will scroll all the hexa-decimal
 numbers and letters on the display. You will need at least
 four 7-Segment digits. otherwise it won't really look that good.
 */
void scrollDigits() {
  for(int i=0;i<13;i++) {
    lc.setDigit(0,3,i,false);
    lc.setDigit(0,2,i+1,false);
    lc.setDigit(0,1,i+2,false);
    lc.setDigit(0,0,i+3,false);
    delay(delaytime);
  }
  lc.clearDisplay(0);
  delay(delaytime);
}

void loop() { 
  writeArduinoOn7Segment();
//  scrollDigits();
}
