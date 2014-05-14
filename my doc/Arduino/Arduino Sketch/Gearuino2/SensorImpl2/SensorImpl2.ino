#define USE_7SEG_LED

#ifdef USE_7SEG_LED
#include "GearLedControl.h"
LedControl lc = LedControl(12, 11, 10, 2);
#endif



void setup() {

  Serial.begin(9600);  //hardware serial to PC

#ifdef USE_7SEG_LED
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0, 15);
  /* and clear the display */
  lc.clearDisplay(0);
  lc.setScanLimit(0, 4);

  lc.shutdown(1, false);
  /* Set the brightness to a medium values */
  lc.setIntensity(1, 15);
  /* and clear the display */
  lc.clearDisplay(1);
  //  lc.setScanLimit(1,3);
  lc.setScanLimit(1, 4);
#endif
}

int keypressed = 0;
int keyboardPin = 0;    // Analog input pin that the keypad is attached to
int keyboardValue = 0;   // value read from the keyboard

int photocellPin = 2; // 光敏電阻 (photocell) 接在 anallog pin 2
int photocellVal = 0; // photocell variable
float f = 0;
int i=0;

unsigned long delaytime = 1;
void loop() {
  //=================================================================================
  // keypad proc
  //=================================================================================
  int key = readkeyboard(); //get the value of key being pressed "keypressed" i.e. 0-9
  if ( key != -1) {
    Serial.println(key);
#ifdef USE_7SEG_LED
    setGearDigit(key);
#endif
    //    Serial.println("*"+String(tmp));
  }
  setGearDigit(8);
  //=================================================================================


  //=================================================================================
  // photocell proc
  //=================================================================================
  //  photocellVal = analogRead(photocellPin);
  setSpeedDigit(255);
  //  for(int x=0;x<1000;x++) {
  //    setSpeedDigit(x);
  //    delay(10);
  //  }
  //=================================================================================

  delay(160);

  //=================================================================================
  // led test
  //=================================================================================
  //  for(int x=0;x<20;x++) {
  //  lc.clearDisplay(1);
  if (i >= 20)   {
    i = 0;
    clearBar();
  }
  if (f >= 20)   {
    f= 0;
    clearBar();
  }
  setBar(i);
  //  Serial.println(f);
  //    delay(delaytime);
  //  }
  //  lc.clearDisplay(1);
  f += 0.125;
  i++;
  //  for(float kpl=0;kpl<19;kpl+=0.1) {
  setKPLDigit(f);
  //  }

  //=================================================================================
}

//=================================================================================
//LED Setting
//=================================================================================

/*
HUD的組成:
 G       SPD
 KPL   BAR
 
 G:      Gear, 7segx1
 SPD: Speed, 7segx3
 KPL:  KPL, 7segx3
 BAR: Progress Bar, 10 ledx2
 
 兩顆7219分別的控制順序:
 C BA0
 DE1 234
 第一顆控制01234, 其中234是Progress Bar
 第二顆控制ABCDE, 其中A~E都是7-seg
 要讓兩顆7219同時控制SPD的原因在於, 若只讓SPD亮,
 可以透過scanlimit的方式讓SPD達到最亮
 至於共同控制KPL...只是為了讓兩顆7219可以控制相同數量的LED
 
 Progress Bar的順序為 01234567 76543210 0123
 
 */

void setGearDigit(byte gear)  {
  lc.setDigit(1, 2, gear, false);
}
void setSpeedDigit(short speed) {
  int num0 = speed % 10;
  int num10 = speed / 10 % 10;
  int num100 = speed / 100 % 10;

  lc.setDigit(0, 0, num0, false);
  lc.setDigit(1, 0, num10, false);
  lc.setDigit(1, 1, num100, false);
}

void setKPLDigit(float kpl) {
    //有小數而且<100
    int num0 = ((int)(kpl * 10)) % 10;
    int num10 = ((int)kpl) % 10;
    int num100 = ((int)kpl / 10) % 10;
    lc.setDigit(0, 1, num0, false);
    lc.setDigit(1, 4, num10, true);
    lc.setDigit(1, 3, num100, false);
}

void setKPLDigit(short kpl) {
    //只有整數
    int ikpl = (int)kpl;
    int num0 = ikpl % 10;
    int num10 = ikpl / 10 % 10;
    int num100 = ikpl / 100 % 10;
    lc.setDigit(0, 1, num0, false);
    lc.setDigit(1, 4, num10, false);
    lc.setDigit(1, 3, num100, false);
}
//byte barRowArray[3] = {
//  1, 0, 2
//};
//byte barColArray[20] = {
//  1, 6, 2 , 7, 4, 0, 5, 3,
//  3, 5, 0, 4, 7, 2, 6, 1,
//  1, 6, 2 , 7
//};
//void setBar(byte count) {
//  int row = barRowArray[count / 8];
//  //  int col = count%8;
//  int col =  barColArray[count];
//  lc.setLed(1, row, col, true);
//}

void setBar(byte count) {
  if ( count < 8) {
    lc.setLed(0, 2, count, true);
  } 
  else if (count >= 8 && count < 16) {
    if ( count >= 8 && count <= 9) {
      lc.setLed(0, 3, 9 - count + 6, true);
    } 
    else {
      lc.setLed(0, 3, 15 - count, true);
    }
  } 
  else if ( count >= 16 && count <= 19) {
    lc.setLed(0, 4, count - 16, true);
  }

}

void clearBar() {
  for (int x = 0; x < 8; x++) {
    lc.setLed(0, 2, x, false);
    lc.setLed(0, 3, x, false);
  }
  for (int x = 0; x < 4; x++) {
    lc.setLed(0, 4, x, false);
  }
}

//=================================================================================

//read the keyboard routine
int readkeyboard() {
  keyboardValue = analogRead(keyboardPin); // read the value (0-1023)
  if (keyboardValue < 67) {
    //    keypressed = -1;
    return -1;
  }
  //  if ((keyboardValue >35) && (keyboardValue < 67)){
  //    keypressed = 1;
  ////    Serial.println(keyboardValue);
  //  }
  if ((keyboardValue > 67) && (keyboardValue < 108)) {
    keypressed = 2;
  }
  if ((keyboardValue > 108) && (keyboardValue < 162)) {
    keypressed = 3;
  }
  if ((keyboardValue > 162) && (keyboardValue < 253)) {
    keypressed = 4;
  }
  if ((keyboardValue > 253) && (keyboardValue < 361)) {
    keypressed = 5;
  }
  if ((keyboardValue > 361) && (keyboardValue < 479)) {
    keypressed = 6;
  }
  if ((keyboardValue > 479) && (keyboardValue < 619)) {
    keypressed = 7;
  }
  if ((keyboardValue > 619) && (keyboardValue < 765)) {
    keypressed = 8;
  }
  if ((keyboardValue > 765) && (keyboardValue < 819)) {
    keypressed = 9;
  }
  if ((keyboardValue > 819) && (keyboardValue < 889)) {
    keypressed = 10;
  }
  if ((keyboardValue > 889) && (keyboardValue < 938)) {
    keypressed = 11;
  }
  if (keyboardValue > 938) {
    keypressed = 12;
  }
  //  tmp=keyboardValue;
  //NOTE: the values used above are all halfway between the value obtained with each keypress in previous test sketch

  //  while (keyboardValue > 25) {
  //    delay (100);
  //    keyboardValue = analogRead(keyboardPin); // read the value (0-1023)
  //  }//wait until key no longer being pressed before continuing


  //  delay(100);
  return keypressed;
}
//end of read the keyboard routine




