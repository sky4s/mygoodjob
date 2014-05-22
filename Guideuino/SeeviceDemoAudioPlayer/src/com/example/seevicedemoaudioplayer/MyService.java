package com.example.seevicedemoaudioplayer;

import java.io.IOException;
import java.util.Timer;
import java.util.TimerTask;

import org.microbridge.server.AbstractServerListener;
import org.microbridge.server.Server;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;
import android.widget.Toast;

public class MyService extends Service {
	private static final String TAG = "My Service Demo";
	// MediaPlayer myPlayer;
	private Timer timer;
	private Server server = null;

	@Override
	public IBinder onBind(Intent intent) {
		return null;
	}

	@Override
	public void onCreate() {
		Toast.makeText(this, "My Service Created", Toast.LENGTH_LONG).show();
		Log.d(TAG, "onCreate");

		// myPlayer = MediaPlayer.create(this, R.raw.loveme);
		// myPlayer.setLooping(false); // Set looping
		try {
			server = new Server(4567);
			server.start();
		} catch (IOException e) {
			Log.e("microbridge", "Unable to start TCP server", e);
			System.exit(-1);
		}

		server.addListener(new AbstractServerListener() {

			@Override
			public void onReceive(org.microbridge.server.Client client,
					byte[] data) {

			};

		});
	}

	@Override
	public void onDestroy() {
		Toast.makeText(this, "My Service Stopped", Toast.LENGTH_LONG).show();
		Log.d(TAG, "onDestroy");
		// myPlayer.stop();
	}
	static byte index=0;
	@Override
	public void onStart(Intent intent, int startid) {
		Toast.makeText(this, "My Service Started", Toast.LENGTH_LONG).show();
		Log.d(TAG, "onStart");
		// myPlayer.start();
		/*
		 * �T�w�C�@��e�Xadb�T��, �n�D����screencap ���槹�����٭n��arduino�^������,
		 * ���ɴN�i�H�hŪ��screencap�᪺����
		 */
		timer = new Timer();
		timer.schedule(new TimerTask() {

			@Override
			public void run() {

				// �b�o�̷Q��k��adb��~��arduino���q
				try {
					server.send(new byte[] { index++, 2 });
				} catch (IOException e) {
					Log.e("microbridge", "problem sending TCP message", e);
				}

			}
		}, 0, 1 * 1000);

	}
}