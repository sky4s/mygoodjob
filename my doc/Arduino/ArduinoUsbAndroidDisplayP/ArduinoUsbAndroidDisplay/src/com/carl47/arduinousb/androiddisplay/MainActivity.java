/* Copyright 2011 Google Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301,
 * USA.
 *
 * Project home page: http://code.google.com/p/usb-serial-for-android/
 */

            /* carl47 modified.
	    	 *  
	    	 * Received data is lost - about 1 in 20 data sends are corrupted.
	    	 * The only problem seems to be that bytes are lost from a serial transmission.
	    	 * I suspect that the problem lies in passing data between threads.
	    	 * Everything seems to be synchronised but I could not find anyway
	    	 * to help in mike wakerly's code.
	    	 * 
	    	 * The problem is governed by  the ratio of length of serial transmission
	    	 * to time between transmissions.
	    	 * At 115200 we can send at 20 msec intervals, any faster and get gross errors.
	    	 * At 9600 can send at 200 msec but no faster.
	    	 * The best error rate is 1 in 20 which is unusable.
	    	 * 
	    	 * I tried:
	    	 * A check sum is used to detect when have lost data.
	    	 * A repeat is then requested from the arduino.
	    	 * This had a major effect but we still get 1 or 2 errors in 65535.
	    	 * 
	    	 * I then tried:
	    	 * The transmissions(at 1152000) are sent twice with 20 msec delay between.
	    	 * This gave nil errors in at least 10 million transmissions.
	    	 * I decided to go with this, its dirty but it works.
	    	 * We halve the data transfer rate by two.
	    	 * The repeats give a maximum average data transfer of about 250 bytes/sec. 
	    	 *
	    	 * We still use a check sum.
	    	 * Only those data with the correct bytes are passed on to the user.
	    	 * 
	    	 */
	    	


package com.carl47.arduinousb.androiddisplay;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import java.io.IOException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import com.hoho.android.usbserial.driver.UsbSerialDriver;
import com.hoho.android.usbserial.driver.UsbSerialProber;
import com.hoho.android.usbserial.util.HexDump;
import com.hoho.android.usbserial.util.SerialInputOutputManager;

import android.os.Bundle;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.hardware.usb.UsbManager;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.ScrollView;
import android.widget.TextView;

public class MainActivity extends Activity {

	private static UsbSerialDriver sDriver = null;
    private final ExecutorService mExecutor = Executors.newSingleThreadExecutor();
    private SerialInputOutputManager mSerialIoManager;
    
 // Set up listener for serial data received from the arduino using USB	    
    private final SerialInputOutputManager.Listener mListener =
            new SerialInputOutputManager.Listener() {

        @Override
        public void onRunError(Exception e) {
           //ignore
        }//end of run error

        @Override
        public void onNewData(final byte[] data) {
            MainActivity.this.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    MainActivity.this.updateReceivedData(data);
                }// end of run the update data subroutine
            });
        }//end of we have received data
    };//end of serial in out listener
    
    private static float xs = 0;
    private static float ys = 0;
    private static float xf = 0;
    private static float yf = 0;
    private static byte type = 0;
    private void updateReceivedData(byte[] data) {
    	byte sentcheck = 0;
    	
    	if(data.length == 10){
    		xs = deltaX * axis(data[0],data[1]);
    		ys = deltaY * axis(data[2],data[3]);
    		xf = deltaX * axis(data[4],data[5]);
    		yf = deltaY * axis(data[6],data[7]);
    		type = data[8];
    		sentcheck = data[9]; //value is unsigned
    	}//end of we have got 10 bytes
    	
    	int tsum = 0; //the check sum on received bytes
    	for(byte i = 0; i < data.length - 1; i++){
    		int s = data[i];
    		if(s < 0)   s  = s + 256;   ///convert to unsigned byte
    		tsum += s; 
    	}//end of get check sum on received
    	 byte rxcheck = (byte) tsum;  //received check sum
    	
    	if((rxcheck == sentcheck)&&(data.length == 10)){	    		
    		if(type == 'T'){
    		char t[] = new char[8]; //temp
    		for(int i = 0; i < 8; i++) t[i] = (char) data[i];
    		text = String.copyValueOf(t);
    		}// end of we have set text
    		else if(type == 'P'){
    		width = xs; //the stroke width
    		int t = 0; // temp
    		t = data[2];
    		if(t < 0) t += 256;  //convert to unsigned byte
    		red = t; //set the color
    		t = data[3];
    		if(t < 0) t += 256;  //convert to unsigned byte
    		green = t; //set the color
    		t = data[4];
    		if(t < 0) t += 256;  //convert to unsigned byte
    		blue = t; //set the color
    		style = false;
    		if(data[5] > 0)  style = true; //we use FILL		
    		}//end of we have set paint
    		else
    		drawIntoBitmap(mBitmap);
 	        mView.invalidate();  //must have a draw
    		
    	}//check sum is ok
    		    			       
    }//end of update data

    private float axis (byte d1, byte d2){
	    int i1 = d1;
        if(d1 < 0) i1 = d1 + 256;  //convert to unsigned byte
        int i2 = d2;
        if(d2 < 0) i2 = d2 + 256;
        float e = i1*256 + i2;	
	    return e;
}//end of convert two byes to a float
    
     private static int red;
     private static int green;
     private static int blue;//black on start
     private static float width;
     private static String text;
     private static boolean style;  //true is FILL
	 private static void drawIntoBitmap(Bitmap bm) {        
       Canvas c = new Canvas(bm);
       Paint p = new Paint();        
       p.setColor(Color.rgb(red, green, blue));
       p.setStrokeWidth(width);     
       p.setStyle(Style.STROKE);
       if(style)  p.setStyle(Style.FILL);
       if(type == 'C')
       c.drawCircle(xs, ys, xf, p);
       else if(type == 'R')
       c.drawRect(xs, ys, xf,yf , p);
       else if(type == 'L')
       c.drawLine(xs, ys, xf,yf , p);
       else if(type == 'W'){
       p.setTextSize(yf);
       c.drawText(text, xs, ys, p);
       }//end of decide on draw type
   }//end of draw into bitmap
      
    public static Bitmap  mBitmap;  //the image for display
	private static View mView;  //the view that is displayed
	private static float deltaX;
	private static float deltaY;  //correction factors for screen size
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		DisplayMetrics metrics = new DisplayMetrics();  ///////
        getWindowManager().getDefaultDisplay().getMetrics(metrics);
        deltaX = (float) (metrics.widthPixels/4000.0); //correction for x - length
        deltaY = (float) (metrics.heightPixels/2250.0); //correction for y - height
        //max screen size screen - locked in landscape
		mBitmap = Bitmap.createBitmap(2000, 1125, Bitmap.Config.ARGB_8888);
		new StartBitmap(deltaX,deltaY);
		mView = new MyView(this);
		setContentView(mView);
		 // Get UsbManager from Android.
        UsbManager manager = (UsbManager) getSystemService(Context.USB_SERVICE);
        // Find the first available driver.
        sDriver = UsbSerialProber.acquire(manager);  
	}//end of oncreate

	private Paint   mBitmapPaint;
    public class MyView extends View {                       
        public MyView(Context c) {
            super(c);
            mBitmapPaint = new Paint();
        }//end of constructor
        
        @Override
    	protected void onDraw(Canvas canvas) { 
            canvas.drawBitmap(mBitmap, 0, 0, mBitmapPaint);
        }//end of ondraw
}//end of view
    
    @Override
    protected void onPause() {
        super.onPause();
        stopIoManager();
        if (sDriver != null) {
            try {
                sDriver.close();
            } catch (IOException e) {
                // Ignore.
            }
            sDriver = null;
        }
        finish();
    }//end of on pause

	 @Override
	    protected void onResume() {
	        super.onResume();
	        if (sDriver == null) {
	        	StatusIntoBitmap("No serial device.",mBitmap);
	 	        mView.invalidate();
	        } else {
	            try {
	                sDriver.open();
	                sDriver.setBaudRate(115200);
	            } catch (IOException e) {
	               // Ignore
	                try {
	                    sDriver.close();
	                } catch (IOException e2) {
	                    // Ignore.
	                }
	                sDriver = null;
	                return;
	            }
	            String text = sDriver.getClass().getSimpleName();
	            StatusIntoBitmap(text,mBitmap);
	 	        mView.invalidate(); //display the driver
	        }
	        onDeviceStateChange();
	    }//end of on resume
	 
	 private static void StatusIntoBitmap(String text,Bitmap bm) {        
	       Canvas c = new Canvas(bm);
	       Paint p = new Paint();
	       p.setColor(Color.BLACK);
	       p.setTextSize(200*deltaY); //write to screen the status of USB
	       c.drawText(text, 2100*deltaX, 2120*deltaY, p);
	       
	 }//end of update the status on screen

	 private void onDeviceStateChange() {
	        stopIoManager();
	        startIoManager();
	    }//end of state changed
	 
	 private void stopIoManager() {
	        if (mSerialIoManager != null) {
	            mSerialIoManager.stop();
	            mSerialIoManager = null;
	        }
	    }//end of stop manager

	 private void startIoManager() {
	        if (sDriver != null) {
	            mSerialIoManager = new SerialInputOutputManager(sDriver, mListener);
	            mExecutor.submit(mSerialIoManager);
	        }//end of no driver
	    }//end of start manager

}//end of main activity
