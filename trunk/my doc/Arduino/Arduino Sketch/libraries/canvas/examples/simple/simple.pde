 //canvas.setPaint(int wide, byte red , byte green , byte blue, byte style)
 //wide - width of brush, style 0 = stroke 1 = fill
 //canvas.setText(String text)
 //text string up to 8 characters 
 //canvas.drawLine(int Xstart, int Ystart, int Xstop, int Ystop)
 //canvas.drawRect(int left, int top, int right, int bottom)
 //canvas.drawCircle(int Xcenter, int Ycenter, int radius)
 //canvas.drawText(int Xstart, int Ystart ,int TextSize

#include <canvas.h>

void setup() {
 canvas.setPaint(1,255,255,255,1);
 canvas.drawRect(0,0,4000,2250); // set full screen to white
 
 canvas.setPaint(40,0,0,0,1);
 canvas.drawLine(0,0,4000,2250);  //black line across screen
 
 canvas.setPaint(100,255,0,0,0);
 canvas.drawCircle(1000,800,400); //big red circle
 
 canvas.setPaint(100,0,255,0,0);
 canvas.drawRect(2400,600,3400,1000); // big green rectangle
 
 canvas.setPaint(20,0,0,255,1);
 canvas.setText("ABCDEFG");
 canvas.drawText(0,2250,950);//big blue text
}

void loop() 
{}

