#define USE_7SEG_LED

#ifdef USE_7SEG_LED
#include "GearLedControl.h"
LedControl lc=LedControl(12,11,10,2);
#endif

void setup(){

  Serial.begin(9600);  //hardware serial to PC

#ifdef USE_7SEG_LED
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,15);
  /* and clear the display */
  lc.clearDisplay(0);
#endif
}

//int tmp=0;
void loop(){


  //  keyboardValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
  //  while (keyboardValue < 25){
  //    //do nothing until a key is pressed
  //    keyboardValue = analogRead(keyboardPin); 
  //    delay(50);
  //  }//end of do nothing till a key is pressed


  int key= readkeyboard(); //get the value of key being pressed "keypressed" i.e. 0-9
  if( key!=-1) {
    Serial.println(key);  
#ifdef USE_7SEG_LED
    lc.setDigit(0,3,key,false);
#endif
    //    Serial.println("*"+String(tmp));   
  }
  delay(100); 

}
int keypressed = 0;
int keyboardPin = 0;    // Analog input pin that the keypad is attached to
int keyboardValue = 0;   // value read from the keyboard



//read the keyboard routine
int readkeyboard(){
  keyboardValue = analogRead(keyboardPin); // read the value (0-1023)
  if (keyboardValue <67){
    //    keypressed = -1;
    return -1;
  }
  //  if ((keyboardValue >35) && (keyboardValue < 67)){
  //    keypressed = 1;
  ////    Serial.println(keyboardValue);   
  //  }
  if ((keyboardValue >67) && (keyboardValue < 108)){
    keypressed = 2;
  }
  if ((keyboardValue >108) && (keyboardValue < 162)){
    keypressed = 3;
  }
  if ((keyboardValue >162) && (keyboardValue < 253)){
    keypressed = 4;
  }
  if ((keyboardValue >253) && (keyboardValue < 361)){
    keypressed = 5;
  }
  if ((keyboardValue >361) && (keyboardValue < 479)){
    keypressed = 6;
  }
  if ((keyboardValue >479) && (keyboardValue < 619)){
    keypressed = 7;
  }
  if ((keyboardValue >619) && (keyboardValue < 765)){
    keypressed = 8;
  }
  if ((keyboardValue >765) && (keyboardValue < 819)){
    keypressed = 9;
  }
  if ((keyboardValue >819) && (keyboardValue < 889)){
    keypressed = 10;
  }
  if ((keyboardValue >889) && (keyboardValue < 938)){
    keypressed = 11;
  }
  if (keyboardValue >938){
    keypressed = 12;
  }
  //  tmp=keyboardValue;
  //NOTE: the values used above are all halfway between the value obtained with each keypress in previous test sketch 

  while (keyboardValue > 25) {
    delay (100);
    keyboardValue = analogRead(keyboardPin); // read the value (0-1023)
  }//wait until key no longer being pressed before continuing
  //  delay(100);  
  return keypressed;

  //  if(-1!=keypressed) {
  //    Serial.println(keypressed);      // print the value back to the Serial view window on your PC
  //  }
  //  delay(100);                     // wait 1000 milliseconds before the next loop
}
//end of read the keyboard routine









