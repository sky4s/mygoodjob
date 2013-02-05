package org.prowl.torquescan;

import java.text.NumberFormat;
import java.util.Timer;
import java.util.TimerTask;

import org.prowl.torque.remote.ITorqueService;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.TextView;

/**
 * This is a very rough, sample plugin that displays a list of all the currently available
 * sensors in Torque (that your ECU supports).
 * 
 * Use the "Display Test Mode" in the main Torque app settings to simulate values.
 * 
 * The plugin name and icon used in Torque are that of the apk icon and name.
 * 
 * Note the intent-filter entries in the manifest - one for this code (an actual activity based plugin)
 * and one for allowing exensions of PID lists for manufacturer specific ECUs. The PID lists are a simple
 * file based resource you can throw together in a normal text-editor. 
 * 
 * Have fun!
 * 
 * @author Ian Hawkins http://torque-bhp.com/
 */
public class PluginActivity extends Activity {


   private ITorqueService torqueService;

   private TextView textView;
   private Handler handler;
   private NumberFormat nf;

   private Timer updateTimer;

   @Override
   public void onCreate(Bundle savedInstanceState) {
      super.onCreate(savedInstanceState);
      setContentView(R.layout.main);
      LayoutInflater inflater = LayoutInflater.from(this);
      View view = inflater.inflate(R.layout.main, null);
      textView = (TextView)view.findViewById(R.id.textview);

      // Max of 2 digits for readings.
      nf = NumberFormat.getInstance();
      nf.setMaximumFractionDigits(2);

      handler = new Handler();

      setContentView(view);
   }


   @Override
   protected void onResume() {
      super.onResume();

      // Bind to the torque service
      Intent intent = new Intent();
      intent.setClassName("org.prowl.torque", "org.prowl.torque.remote.TorqueService");
      boolean successfulBind = bindService(intent, connection, 0);

      if (successfulBind) {
         updateTimer = new Timer();
         updateTimer.schedule(new TimerTask() { public void run() {
            update();
         }}, 1000, 200);
      }
   }



   @Override
   protected void onPause() {
      // TODO Auto-generated method stub
      super.onPause();
      updateTimer.cancel();
      unbindService(connection);
   }

   /**
    * Do an update
    */
   public void update() {
      // String used for code readability.
      String text = ""; 

      try {
         text = text + "API Version: "+torqueService.getVersion() + "\n";

         long[] pids = torqueService.getListOfActivePids();
         for (long pid: pids) {

            String description = torqueService.getDescriptionForPid(pid);
            // If no description, display as hex.
            if (description == null)
               description = Long.toString(pid, 16);
            
            float value = torqueService.getValueForPid(pid, true);
            String unit = torqueService.getUnitForPid(pid);

            text = text + description+": "+nf.format(value);
            
            if (unit != null)
               text +=" "+unit;
            
            text+="\n";

         }

      } catch(RemoteException e) {
         Log.e(getClass().getCanonicalName(),e.getMessage(),e);
      }

      // Update the widget.
      final String myText = text;
      handler.post(new Runnable() { public void run() {
         textView.setText(myText);
      }});

   }



   /**
    * Bits of service code. You usually won't need to change this.
    */
   private ServiceConnection connection = new ServiceConnection() {
      public void onServiceConnected(ComponentName arg0, IBinder service) {
         torqueService = ITorqueService.Stub.asInterface(service);
      };
      public void onServiceDisconnected(ComponentName name) {
         torqueService = null;
      };
   };
}