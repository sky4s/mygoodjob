#include <SoftwareSerial.h>
#define RxD 2
#define TxD 3
#define LED 13
SoftwareSerial blueToothSerial(RxD,TxD); 


const int LED_ON = 0x1;
const int LED_OFF = 0x2;


    

const int DELAY = 300;

unsigned char temp_val;
unsigned char Receive_val;
unsigned char len;
unsigned char Buffer_temp[4];
unsigned char i;

void UART_FUN()
{

  for(i=0;i<5;i++)
   Buffer_temp[i]=0x0;
    delay(100);
  while(blueToothSerial.available())            
  {                                                
     Receive_val=blueToothSerial.read();
      //Serial.print(Receive_val); 
     // Serial.print("\n"); 
     

     if(Receive_val==0xAA)
     {
     		len=0;
     		Buffer_temp[len++]=Receive_val;
     }
     else if(len < 5)
     {
     		Buffer_temp[len++]=Receive_val;
     }
     
  }   
 
  if(Buffer_temp[0]==0xAA && Buffer_temp[1]==0xBB && Buffer_temp[3]==0xF1)
  {
   Serial.print("LED_ON \n"); 
   temp_val=LED_ON;
   }
   else if(Buffer_temp[0]==0xAA && Buffer_temp[1]==0xBB && Buffer_temp[3]==0xF2)
  {
   Serial.print("LED_OFF \n"); 
   temp_val=LED_OFF ;
   }
 

 
  
 
}




void setup()  
{

  pinMode(LED, OUTPUT);   
  Serial.begin(9600);  
  blueToothSerial.begin(9600);
  temp_val=0;     
  len=0;
}

void loop()
{
  UART_FUN();
	
  if(temp_val==LED_ON)
  {
  		digitalWrite(LED, HIGH); 
  }
  else if(temp_val==LED_OFF)
  {
			digitalWrite(LED, LOW); 
  
  }


  
  
}



