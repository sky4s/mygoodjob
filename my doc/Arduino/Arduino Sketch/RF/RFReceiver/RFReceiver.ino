int dataPin = 2;
int LED = 13;
int data;

void setup()
{
  Serial.begin(9600);  //hardware serial to PC
  pinMode(dataPin,INPUT);	 //设置12脚为数据接收（datain）脚
  pinMode(LED,OUTPUT);   //设置13脚为LED显示管脚
}

void loop ()
{
  data=digitalRead(dataPin);
  digitalWrite(LED,dataPin);//用12脚接收到的无线电平信号	   //控制13脚上的LED
  Serial.println(data);  
}

