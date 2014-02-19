//#define USE_SERIAL
//#define BYPASS_READ
#include <GearRCSwitch.h>
RCSwitch mySwitch = RCSwitch();

char keypressed = 0;
int keyboardPin = 0;    // Analog input pin that the keypad is attached to
int keyboardValue = 0;   // value read from the keyboard
//int RFPin = 2;
//int LEDPin = 13;

void setup() {

#ifdef USE_SERIAL
  Serial.begin(9600);  //hardware serial to PC
#endif
  //  pinMode(RFPin,OUTPUT);	 //设置13脚为数据发送口
  //  pinMode(LEDPin, OUTPUT);
  mySwitch.enableTransmit(10);
}


void loop() {
#ifndef BYPASS_READ
  keyboardValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
#endif
  //  while (keyboardValue < 25) {
  //    //do nothing until a key is pressed
  //#ifndef BYPASS_READ
  //    keyboardValue = analogRead(keyboardPin);
  //#endif
  //    delay(50);
  //    //    digitalWrite(RFPin,LOW);
  //  }//end of do nothing till a key is pressed
  if( keyboardValue <25) {
    delay(50);
    return;
  }
  //  readkeyboard(); //get the value of key being pressed "keypressed" i.e. 0-9

  /* Same switch as above, but using decimal code */
  mySwitch.send(5393, 24);
  delay(1000);  
  mySwitch.send(5396, 24);
  delay(1000);  
}



//read the keyboard routine
void readkeyboard() {
#ifndef BYPASS_READ
  keyboardValue = analogRead(keyboardPin); // read the value (0-1023)
#endif
  if ((keyboardValue > 25) && (keyboardValue < 67)) {
    keypressed = '+';
  }
  if ((keyboardValue > 67) && (keyboardValue < 108)) {
    keypressed = 'P';
  }
  if ((keyboardValue > 162) && (keyboardValue < 253)) {
    keypressed = 'U';
  }
  if ((keyboardValue > 253) && (keyboardValue < 361)) {
    keypressed = 'L';
  }
  if ((keyboardValue > 361) && (keyboardValue < 479)) {
    keypressed = '-';
  }
  if ((keyboardValue > 479) && (keyboardValue < 619)) {
    keypressed = 'R';
  }
  if ((keyboardValue > 619) && (keyboardValue < 765)) {
    keypressed = 'D';
  }
  if ((keyboardValue > 819) && (keyboardValue < 889)) {
    keypressed = 'M';
  }
  if (keyboardValue > 938) {
    keypressed = 'S';
  }
  //NOTE: the values used above are all halfway between the value obtained with each keypress in previous test sketch

  while (keyboardValue > 25) {
    delay (100);
#ifndef BYPASS_READ
    keyboardValue = analogRead(keyboardPin); // read the value (0-1023)
#endif
  }//wait until key no longer being pressed before continuing


#ifdef USE_SERIAL
  Serial.println(keypressed);      // print the value back to the Serial view window on your PC
#endif
  delay(200);                     // wait 1000 milliseconds before the next loop
}
//end of read the keyboard routine








