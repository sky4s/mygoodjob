// transmitter.pde
//
// Simple example of how to use VirtualWire to transmit messages
// Implements a simplex (one-way) transmitter with an TX-C1 module
//
// See VirtualWire.h for detailed API docs
// Author: Mike McCauley (mikem@airspayce.com)
// Copyright (C) 2008 Mike McCauley
// $Id: transmitter.pde,v 1.3 2009/03/30 00:07:24 mikem Exp $

#include <VirtualWire.h>

char keypressed = 0;
int keyboardPin = 0;    // Analog input pin that the keypad is attached to
int keyboardValue = 0;   // value read from the keyboard
char *msg = " ";
int ledPin=1;

void setup()
{
  //    Serial.begin(9600);	  // Debugging only
  //    Serial.println("setup");

  pinMode(5, INPUT);
  analogReference(EXTERNAL);
  vw_set_tx_pin(1);
  pinMode(ledPin, OUTPUT);
  // Initialise the IO and ISR
  //    vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(2000);	 // Bits per sec
}

void loop()
{
  //  keyboardValue = analogRead(keyboardPin); //Read P5
  //  while (keyboardValue < 25) {
  //    //do nothing until a key is pressed
  //    keyboardValue = analogRead(keyboardPin);
  //    delay(50);//if no input, just wait 50ms, and keep in loop
  //  }//end of do nothing till a key is pressed
  //
  //  readkeyboard(); //get the value of key being pressed "keypressed" i.e. 0-9    
  //  msg[0]=keypressed;


  //  digitalWrite(ledPin, true); // Flash a light to show transmitting

  vw_send((uint8_t *)msg, strlen(msg));
  vw_wait_tx(); // Wait until the whole message is gone

  delay(500);  
  //  digitalWrite(ledPin, false);
  //  delay(500);  
}

//read the keyboard routine
void readkeyboard() {
  keyboardValue = analogRead(keyboardPin); // read the value (0-1023)
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
    keyboardValue = analogRead(keyboardPin); // read the value (0-1023)
  }//wait until key no longer being pressed before continuing
  //for de-bounce usage

  //maybe can pass delay?
  delay(50);                     // wait 1000 milliseconds before the next loop
}
//end of read the keyboard routine





