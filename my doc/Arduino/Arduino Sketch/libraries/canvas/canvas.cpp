//canvas.setPaint(int wide, byte red , byte green , byte blue, byte style)
 //wide - width of brush, style 0 = stroke 1 = fill
 //canvas.setText(String text)
 //text string up to 8 characters 
 //canvas.drawLine(int Xstart, int Ystart, int Xstop, int Ystop)
 //canvas.drawRect(int left, int top, int right, int bottom)
 //canvas.drawCircle(int Xcenter, int Ycenter, int radius)
 //canvas.drawText(int Xstart, int Ystart ,int TextSize

#include "Arduino.h"
#include "canvas.h"

void canvasclass::setPaint(unsigned int wide, byte r ,byte g ,byte b, byte stroke){ 
 unsigned int t1 =0;
 t1 |= r;
 t1 <<= 8; //move into top 8
 t1 |= g;  //next into bottom 8
 unsigned int t2 =0;
 t2 |= b;
 t2 <<= 8; //move into top 8
 t2 |= stroke;  //next into bottom 8
 usbSend('P',wide,t1,t2,0);   
}

void canvasclass::setText(String t){
 unsigned int t1 =0;
 t1 |= t[0];
 t1 <<= 8; //move into top 8
 t1 |= t[1];  //next into bottom 8
 unsigned int t2 =0;
 t2 |= t[2];
 t2 <<= 8; //move into top 8
 t2 |= t[3];  //next into bottom 8
 unsigned int t3 =0;
 t3 |= t[4];
 t3 <<= 8; //move into top 8
 t3 |= t[5];  //next into bottom 8
 unsigned int t4 =0;
 t4 |= t[6];
 t4 <<= 8; //move into top 8
 t4 |= t[7];  //next into bottom 8
 usbSend('T',t1,t2,t3,t4); 
}

void canvasclass::drawText(unsigned int xs,unsigned int ys,unsigned int ts){
usbSend('W',xs,ys,0,ts);    
}

void canvasclass::drawLine(unsigned int xs,unsigned int ys,unsigned int xf,unsigned int yf){
usbSend('L',xs,ys,xf,yf);  
}

void canvasclass::drawRect(unsigned int l,unsigned int t,unsigned int r,unsigned int b){
usbSend('R',l,t,r,b);  
}

void canvasclass::drawCircle(unsigned int xs,unsigned int ys,unsigned int r){
usbSend('C',xs,ys,r,0);  
}

void canvasclass::usbSend(byte type, unsigned int xs,unsigned int ys,unsigned int xf,unsigned int yf)
{
 Serial.begin(115200); // ensure up to speed
 byte buf[10];
 buf[1] = xs;
 buf[0] = xs >> 8;  //get most significant byte
 buf[3] = ys;
 buf[2] = ys >> 8;
 buf[5] = xf;
 buf[4] = xf >> 8;
 buf[7] = yf;
 buf[6] = yf >> 8;
 buf[8] = type;

 unsigned int tsum = 0;
 for(byte i = 0; i < 9; i++) tsum += buf[i];
 buf[9] = tsum;       //check sum for transmission
 
 Serial.write(buf, 10);
 delay(20);
 Serial.write(buf, 10);
 delay(20); 
}//end of send 10 bytes

canvasclass canvas;
