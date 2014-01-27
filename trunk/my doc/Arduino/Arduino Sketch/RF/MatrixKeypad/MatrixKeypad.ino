int keypressed = 0;
int keyboardPin = 0;    // Analog input pin that the keypad is attached to
int keyboardValue = 0;   // value read from the keyboard
int RFPin = 2;
int LEDPin = 13;

void setup(){


  Serial.begin(9600);  //hardware serial to PC
  pinMode(RFPin,OUTPUT);	 //设置13脚为数据发送口
  pinMode(LEDPin,OUTPUT);
}


void loop(){
//  if(true) {
//    digitalWrite(RFPin,LOW);
//    digitalWrite(LEDPin,HIGH);
//    return;
//  }


  keyboardValue = analogRead(keyboardPin); // read the keyboard value (0 - 1023)
  while (keyboardValue < 25){
    //do nothing until a key is pressed
    keyboardValue = analogRead(keyboardPin); 
    delay(50);
    digitalWrite(RFPin,LOW);
    Serial.println("wait key pressed");   
  }//end of do nothing till a key is pressed


  readkeyboard(); //get the value of key being pressed "keypressed" i.e. 0-9
//  if(5==keypressed) {
//
//    digitalWrite(RFPin,HIGH);	 //发送信号为方波周期1s
//    digitalWrite(LEDPin,HIGH);
//    delay(500);
//    digitalWrite(RFPin,LOW);
//    digitalWrite(LEDPin,LOW);
//    delay(500);
//    Serial.println("5 pressed");   
//  }
//  else {
//    Serial.println("Not 5 pressed");       
//  }
}



//read the keyboard routine
void readkeyboard(){
  keyboardValue = analogRead(keyboardPin); // read the value (0-1023)
  if (keyboardValue <25){
    keypressed = 0;
  }
  if ((keyboardValue >25) && (keyboardValue < 67)){
    keypressed = 1;
  }
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
    keypressed = 0;
  }
  if ((keyboardValue >889) && (keyboardValue < 938)){
    keypressed = 0;
  }
  if (keyboardValue >938){
    keypressed = 0;
  }
  //NOTE: the values used above are all halfway between the value obtained with each keypress in previous test sketch 

  while (keyboardValue > 25) {
    delay (100);
    keyboardValue = analogRead(keyboardPin); // read the value (0-1023)
  }//wait until key no longer being pressed before continuing



  Serial.println(keypressed);      // print the value back to the Serial view window on your PC
  delay(200);                     // wait 1000 milliseconds before the next loop
}
//end of read the keyboard routine





