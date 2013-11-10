const int inPin =  11;
int val=0;
void setup() {
  Serial.begin(9600);
  pinMode(inPin, INPUT);      // sets the digital pin 11 as inpu
  
}

void loop() {
   val = digitalRead(inPin);   // read the input pin
  Serial.print(val+"\n");
  delay(100);
}
