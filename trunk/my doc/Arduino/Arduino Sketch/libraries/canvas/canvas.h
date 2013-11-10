 //canvas.setPaint(int wide, byte red , byte green , byte blue, byte style)
 //wide - width of brush, style 0 = stroke 1 = fill
 //canvas.setText(String text)
 //text string up to 8 characters 
 //canvas.drawLine(int Xstart, int Ystart, int Xstop, int Ystop)
 //canvas.drawRect(int left, int top, int right, int bottom)
 //canvas.drawCircle(int Xcenter, int Ycenter, int radius)
 //canvas.drawText(int Xstart, int Ystart ,int TextSize


#ifndef canvas_h
#define canvas_h

#include "Arduino.h"

class canvasclass
{
public:

void setPaint(unsigned int w, byte r ,byte g ,byte b, byte s);
void setText(String t);
void drawText(unsigned int xs,unsigned int ys,unsigned int ts);
void drawLine(unsigned int xs,unsigned int ys,unsigned int xf,unsigned int yf);
void drawRect(unsigned int l,unsigned int t,unsigned int r,unsigned int b);
void drawCircle(unsigned int xs,unsigned int ys,unsigned int r);

private:

void usbSend(byte type, unsigned int xs,unsigned int ys,unsigned int xf,unsigned int yf);

};//end of class canvasclass

extern canvasclass canvas;
#endif
