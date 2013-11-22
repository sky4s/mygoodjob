package com.carl47.arduinousb.androiddisplay;

import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;

public class StartBitmap {
	
	private static Path aPath;
	private static Path dPath;
	private static float dx;
	private static float dy;//correction factors bitmap is 4000x2250


	public StartBitmap(float sw, float sh) {
		dx = sw;
		dy = sh;
		aPath = new Path();
		////construct an arrow
        aPath.moveTo(600*dx, 120*dy);
        aPath.lineTo(3200*dx, 120*dy);
        aPath.lineTo(3200*dx, 40*dy);
        aPath.lineTo(3400*dx, 160*dy);
        aPath.lineTo(3200*dx, 280*dy);
        aPath.lineTo(3200*dx, 200*dy);
        aPath.lineTo(600*dx, 200*dy);
        aPath.close();
        dPath = new Path();
		//construct an arrow
        dPath.moveTo(120*dx, 400*dy);
        dPath.lineTo(200*dx, 400*dy);
        dPath.lineTo(200*dx, 1720*dy);
        dPath.lineTo(280*dx, 1720*dy);
        dPath.lineTo(160*dx, 1920*dy);
        dPath.lineTo(40*dx, 1720*dy);
        dPath.lineTo(120*dx, 1720*dy);
        dPath.close();
		drawIntoBitmap();
	}//end of constructor
	
	 private static void drawIntoBitmap() {        
	        Canvas c = new Canvas(MainActivity.mBitmap);
	        Paint p = new Paint();
	        c.drawColor(Color.WHITE); //background	       
	        p.setColor(Color.BLACK);
	        p.setTextSize(200*dy);
	        c.drawText("(0,0)", 100*dx, 220*dy, p);
	        c.drawText("4000", 3500*dx, 220*dy, p);
	        c.drawText("2250", 40*dx, 2150*dy, p);//axis values
	        p.setTextSize(500*dy);
	        c.drawText("X", 1700*dx, 600*dy, p);
	        c.drawText("Y", 240*dx, 1300*dy, p); //show x and y
	        p.setColor(Color.BLUE);
	    	c.drawPath(aPath, p);
	    	c.drawPath(dPath, p);//draw arrows
	    	p.setColor(Color.LTGRAY);
	    	c.drawRect(2000*dx, 1050*dy, 4000*dx, 2250*dy, p); //information box
	    	p.setColor(Color.BLACK);
		    p.setTextSize(200*dy);   //show information
		    c.drawText("Screen Width = " + String.valueOf((int)(dx*4000)), 2100*dx, 1320*dy, p);
		    c.drawText("Screen height = " + String.valueOf((int)(dy*2250)), 2100*dx, 1720*dy, p);
	 }//end of draw into bitmap
	 
}//end of start bitmap
