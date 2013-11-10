// Lab15 使用四位數七段顯示器當計數器 V2

// 定義七段顯示器各節段與 Arduino 的腳位對應關係
#define A 5
#define B 7
#define C 4
#define D 11
#define E 10
#define FF 3
#define G 6

// 定義共陽極與 Arduino 的腳位對應關係
#define CA1 13
#define CA2 12
#define CA3 9
//#define CA4 8

// 定義七個節段的腳位，將 A, B, C, D, E, F, G 依序放入陣列
byte segs[7] = { A, B, C, D, E, FF, G };

// 定義共陽極七段顯示器的字型(digit pattern)
// define the LED digit patterns, from 0 - 9
// 0 = LED on, 1 = LED off, in this order:
//                Mapping to       a,b,c,d,e,f,g of Seven-Segment LED
byte seven_seg_digits[13][7] = { { 0,0,0,0,0,0,1 },  // = 0
                                 { 1,0,0,1,1,1,1 },  // = 1
                                 { 0,0,1,0,0,1,0 },  // = 2
                                 { 0,0,0,0,1,1,0 },  // = 3
                                 { 1,0,0,1,1,0,0 },  // = 4
                                 { 0,1,0,0,1,0,0 },  // = 5
                                 { 0,1,0,0,0,0,0 },  // = 6
                                 { 0,0,0,1,1,1,1 },  // = 7
                                 { 0,0,0,0,0,0,0 },  // = 8
                                 { 0,0,0,1,1,0,0 },  // = 9
                                 { 0,0,0,1,0,0,0 },  //10 A
                                 { 0,0,0,0,0,0,0 },  //11 B
                                 { 0,1,1,0,0,0,1 } , //12 C
                                }; 

//A-D B-C E-F                                
byte reverse_seven_seg_digits[13][7] = { { 0,0,0,0,0,0,1 },  // = 0
                                 { 1,0,0,1,1,1,1 },  // = 1
                                 { 0,1,0,0,1,0,0 },  // = 2
                                 { 0,0,0,0,1,1,0 },  // = 3
                                 { 1,0,0,1,0,1,0 },  // = 4
                                 { 0,0,1,0,0,1,0 },  // = 5
                                 { 0,0,1,0,0,0,0 },  // = 6
                                 { 1,0,0,0,1,1,1 },  // = 7
                                 { 0,0,0,0,0,0,0 },  // = 8
                                 { 1,0,0,0,0,1,0 },  // = 9
                                 { 1,0,0,0,0,0,0 },  //10 A
                                 { 0,0,0,0,0,0,0 },  //11 B
                                 { 0,1,1,0,0,0,1 } , //12 C
                                };                                 

// 定義每個七段顯示器顯示的時間 (延遲時間), 預設 1ms 
int delay_time = 7;
                             
void setup() {
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(FF, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(CA1, OUTPUT);
  pinMode(CA2, OUTPUT);
  pinMode(CA3, OUTPUT);


  TCCR1A = 0x00;                // Normal mode, just as a Timer

  TCCR1B &= ~_BV(CS12);         // no prescaling
  TCCR1B &= ~_BV(CS11);       
  TCCR1B |= _BV(CS10);     
  
  TIMSK1 |= _BV(TOIE1);         // enable timer overflow interrupt
  
  TCNT1 = 0;
}

void displayDigit(int num1,int num2,int num3) {
  lightDigit1(num1);
  delay(delay_time);
  darkSegments();
  
  lightDigit2(num2);
  delay(delay_time);
  darkSegments();
  
  lightDigit3(num3);
  delay(delay_time);  
  darkSegments();
}

volatile unsigned int count = 0;
volatile unsigned int second = 0;

ISR (TIMER1_OVF_vect)
{  
  count++;
  
  if (count == 244) {             // overflow frequency = 16 MHz/65536 = 244Hz
//  if (count == 24) {             // overflow frequency = 16 MHz/65536 = 244Hz  
//    PORTB ^= _BV(5);              // Toggle LED, PB5 = Arduino pin 13
    second++;
    if(second>999) {
      second=0;
    }
 
    count = 0;
  }  
}
 
void loop() {
    int num2 = second/10%10;
    int num3 = second/100%10;
    displayDigit(second%10,num2,num3);
//  displayDigit(10,11,12);
//  lightDigit1(1);
//  delay(delay_time);
//  darkSegments();
//  lightDigit2(2);
//  delay(delay_time);
//  darkSegments();
//  lightDigit3(3);
//  delay(delay_time);
  
//  darkSegments();
  // 從 0000 計數到 9999
//  for (unsigned int number = 999; number >0; number--) {
//    // 每一秒鐘計數一次
//    unsigned long startTime = millis();
//    for (unsigned long elapsed=0; elapsed < 48; elapsed = millis() - startTime) {
//      // 多工掃瞄，輪流點亮個、十、百、以及千位數的七段顯示器
//      
//      // 顯示個位數
//      lightDigit1(number%10);
//      delay(delay_time);
//      darkSegments();
//
//      // 顯示十位數
//      lightDigit2((number/10)%10);
//      delay(delay_time);
//      darkSegments();
//
//      // 顯示百位數
//      lightDigit3((number/100)%10);            
//      delay(delay_time);
//      darkSegments();
//        
//    }    
//  }
}

// 選擇顯示的位數 (4:千、3:百、2:十、或 1:個位數)
void pickDigit(int x) {
  digitalWrite(CA1, HIGH);
  digitalWrite(CA2, HIGH);
  digitalWrite(CA3, HIGH);
 
  switch(x) {
    case 1:
    digitalWrite(CA1, LOW);
    break;
    
    case 2: 
    digitalWrite(CA2, LOW); 
    break;
    
    case 3: 
    digitalWrite(CA3, LOW); 
    break;
  }
}

// 點亮個位數
void lightDigit1(byte number) {
  pickDigit(1);   
  lightSegments(number);  
}

// 點亮十位數
void lightDigit2(byte number) {
  pickDigit(2);
  lightSegments(number);  
}

// 點亮百位數
void lightDigit3(byte number) {
  pickDigit(3);
  lightSegments(number);  
}

//// 點亮千位數
//void lightDigit4(byte number) {
//  pickDigit(4);
//  lightSegments(number);  
//}

// 點亮七段顯示器
void lightSegments(byte number) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segs[i], reverse_seven_seg_digits[number][i]);
  }
}

//byte dark[7] =  { 0,0,0,0,0,0,0 }; 
byte dark[7] =  { 1,1,1,1,1,1,1 }; 
void darkSegments() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segs[i], dark[i]);
  }
}
 

