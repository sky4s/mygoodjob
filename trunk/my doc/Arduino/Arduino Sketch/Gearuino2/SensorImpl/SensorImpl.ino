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
  lc.setScanLimit(0,6);

  lc.shutdown(1,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(1,15);
  /* and clear the display */
  lc.clearDisplay(1);
  lc.setScanLimit(1,3);
#endif
}

int keypressed = 0;
int keyboardPin = 0;    // Analog input pin that the keypad is attached to
int keyboardValue = 0;   // value read from the keyboard

int photocellPin = 2; // 光敏電阻 (photocell) 接在 anallog pin 2
int photocellVal = 0; // photocell variable


unsigned long delaytime=1;
void loop(){


  //  keyboardValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
  //  while (keyboardValue < 25){
  //    //do nothing until a key is pressed
  //    keyboardValue = analogRead(keyboardPin); 
  //    delay(50);
  //  }//end of do nothing till a key is pressed

  //=================================================================================
  // keypad proc
  //=================================================================================
  int key= readkeyboard(); //get the value of key being pressed "keypressed" i.e. 0-9
  if( key!=-1) {
    Serial.println(key);  
#ifdef USE_7SEG_LED
    setGearDigit(key);
#endif
    //    Serial.println("*"+String(tmp));   
  }
  //=================================================================================


  //=================================================================================
  // photocell proc
  //=================================================================================
  photocellVal = analogRead(photocellPin);
  setKPLDigit(photocellVal);
  //=================================================================================

  delay(100); 

  //  for(int x=0;x<8;x++) {
  //    int pos=posarray[x];
  //    lc.clearDisplay(1);
  //    lc.setLed(1,1,pos,true);
  //    delay(delaytime);
  //  }
  //  for(int x=0;x<8;x++) {
  //    int pos=posarray2[x];
  //    lc.clearDisplay(1);
  //    lc.setLed(1,0,pos,true);
  //    delay(delaytime);
  //  }
  //  for(int x=0;x<4;x++) {
  //    int pos=posarray[x];
  //    lc.clearDisplay(1);
  //    lc.setLed(1,2,pos,true);
  //    delay(delaytime);
  //  }
  for(int x=0;x<20;x++) {
    lc.clearDisplay(1);
    setBar(x);
    delay(delaytime);
  }
  lc.clearDisplay(1);
}
int posarray[8] = {
  1,6,2 ,7,4,0,5,3
};
int posarray2[8] = {
  3,5,0,4,7,2,6,1
};
byte barRowArray[3]={
  1,0,2};
byte barColArray[20]={ 
  1,6,2 ,7,4,0,5,3,3,5,0,4,7,2,6,1,1,6,2 ,7};
void setBar(byte count) {  
  int row = barRowArray[count/8];
  //  int col = count%8;
  int col=  barColArray[count];
  lc.setLed(1,row,col,true);
}


void setGearDigit(byte gear)  {
  lc.setDigit(0,2,gear,false);
}
void setSpeedDigit(byte speed) {
  int num0=speed%10;
  int num10=speed/10%10;
  int num100=speed/100%10;
  lc.setDigit(0,1,num0,false);
  lc.setDigit(0,5,num10,false);
  lc.setDigit(0,3,num100,false);
}

void setKPLDigit(float kpl) {
  if( kpl == (int)kpl){
    //只有整數
    int ikpl = (int)kpl;
    int num0=ikpl%10;
    int num10=ikpl/10%10;
    int num100=ikpl/100%10;
    lc.setDigit(0,6,num0,false);
    lc.setDigit(0,4,num10,false);
    lc.setDigit(0,0,num100,false);
  }
  else {
    //有小數
  }
}




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



























