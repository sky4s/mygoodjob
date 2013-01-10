/*      ClockWidget Tutorial (aedus.com)
       Author: Steve Patton
       Date: 28-May-2011  */

package com.aedus.android.ClockWidget;

import java.util.Calendar;
import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;

import android.appwidget.AppWidgetManager;
import android.appwidget.AppWidgetProvider;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.Bitmap.Config;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.graphics.RectF;
import android.widget.RemoteViews;
import android.widget.Toast;

public class ClockWidget extends AppWidgetProvider
 {
  int[] mAppWidgetIds;
  AppWidgetManager widgetManager;

  static Timer timer = null;

  public void update(Context context)
   {
    RemoteViews views = new RemoteViews(context.getPackageName(),
      R.layout.widget);
    Bitmap bitmap = Bitmap.createBitmap(294, 220, Config.ARGB_8888);
    Canvas canvas = new Canvas(bitmap);

    Paint p = new Paint();
    p.setAntiAlias(true);

    p.setStyle(Style.FILL);
    p.setStrokeWidth(1);
    p.setColor(0xC7000000);
//    canvas.drawArc(new RectF(38, 2, 254, 218), 0, 360, false, p);

    p.setStyle(Style.STROKE);
    p.setStrokeWidth(1);
    p.setColor(0xFFFFFFFF);
//    canvas.drawArc(new RectF(38, 2, 254, 218), 0, 360, false, p);

    Date dt = new Date();

    int mainAngle = dt.getSeconds() * 360 / 60;
    mainAngle -= 135;
    int offset = 10;
    p.setColor(0xFF00FF00);
    p.setStrokeWidth(16);
    RectF rect = new RectF(38+offset,2+offset,
                                     254-offset,218-offset);
    canvas.drawArc(rect, mainAngle, 90, false, p);

    p.setColor(0xFFFF7777);
    offset = 27;
    mainAngle = dt.getMinutes() * 360 / 60;
    mainAngle -= 125;
    rect = new RectF(38 + offset, 2 + offset,
                            254 - offset, 218 - offset);
    canvas.drawArc(rect , mainAngle, 70, false, p);

    p.setColor(0xFFFFFF33);
    offset = 44;
    mainAngle = dt.getHours();
    if ( mainAngle > 12 )
     mainAngle -= 12;
    mainAngle = mainAngle * 360 / 12;
    mainAngle -= 115;
    rect = new RectF(38 + offset, 2 + offset,
                            254 - offset, 218 - offset);
    canvas.drawArc(rect, mainAngle, 50, false, p);

    views.setImageViewBitmap(R.id.widget_imageview, bitmap);

    widgetManager.updateAppWidget(mAppWidgetIds, views);
   }

  public void onDeleted(Context context, int[] appWidgetIds)
   {
    CharSequence text = "SHUTDOWN ";
    int duration = Toast.LENGTH_LONG;
    Toast toast = Toast.makeText(context, text, duration);
    toast.show();
    timer.cancel();
   }

  public void onUpdate(Context context,
           AppWidgetManager appWidgetManager, int[] appWidgetIds)
   {
    // lets copy our stuff
    mAppWidgetIds = new int[appWidgetIds.length];
    for (int a = 0; a < appWidgetIds.length; a++)
     mAppWidgetIds[a] = appWidgetIds[a];
    widgetManager = appWidgetManager;

    update(context);

    if ( timer == null )
     {
      CharSequence text = "INSTALLING";
      int duration = Toast.LENGTH_SHORT;
      Toast toast = Toast.makeText(context, text, duration);
      toast.show();

      timer = new Timer();
      Calendar cal = Calendar.getInstance();
      cal.add(Calendar.SECOND, 1);
      cal.set(Calendar.MILLISECOND, 0);

      timer.scheduleAtFixedRate(new MyTime(context,this),
                                          cal.getTime(), 1000);
     }

   }

  private class MyTime extends TimerTask
   {
    AppWidgetManager appWidgetManager;
    ClockWidget parent;
    Context context;

    public MyTime(Context context, ClockWidget parent)
     {
      this.parent = parent;
      this.context = context;
     }

    @Override
    public void run()
     {
      try
       {
      parent.update(context);
       }
      catch (Exception e)
       {
        CharSequence text = "tim_excp : " + e.getMessage();
        int duration = Toast.LENGTH_SHORT;
        Toast toast = Toast.makeText(context, text, duration);
        toast.show();
       }
     }
   }

 }