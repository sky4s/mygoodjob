#ifndef CANVAS_H
#define CANVAS_H

class CanvasWrapper {
private:
  canvasclass canvas;
  int line;
  int lineheight;
  int currentline;
  int factor;
public:
  CanvasWrapper(canvasclass _canvas,int _line){
    canvas=_canvas;
    line=_line;
    lineheight = 2250/line;
    factor=500;
  }
  inline int getY() {
    return (currentline++%line)*lineheight;
  }

  void println(String s) {
    int length=s.length();
    int count = length/8;
    int mod = length%8;
    canvas.setPaint(2,255,255,255,1);
    int y=getY();
    for(int x=0;x<count;x++) {
      int start=8*x;
      String sub= s.substring(start,start+8); 
      canvas.setText(sub);
      canvas.drawText(factor*x,y,lineheight);//big blue text
      //      Serial.println(sub+" "+String(start));
    }
    if(0!=mod) {
      //      int start=factor*count;
      String sub= count!=0?s.substring(length-mod,length):s;
      //      Serial.println(sub+" "+String(start));
      canvas.setText(sub);
      canvas.drawText(factor*count,y,lineheight);//big blue text
    }
  }

  void clear() {
    canvas.setPaint(1,0,0,0,1);
    canvas.drawRect(0,0,4000,2250); // set full screen to white 
  }
};


#endif
