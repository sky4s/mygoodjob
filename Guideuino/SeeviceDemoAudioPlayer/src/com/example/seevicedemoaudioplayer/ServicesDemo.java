package com.example.seevicedemoaudioplayer;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class ServicesDemo extends Activity implements OnClickListener {
	private static final String TAG = "ServicesDemo";
	Button buttonStart, buttonStop,buttonNext;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);

		buttonStart = (Button) findViewById(R.id.buttonStart);
		buttonStop = (Button) findViewById(R.id.buttonStop);
		buttonNext = (Button) findViewById(R.id.buttonNext);

		buttonStart.setOnClickListener(this);
		buttonStop.setOnClickListener(this);
		buttonNext.setOnClickListener(this);
	}

	public void onClick(View src) {
		switch (src.getId()) {
		case R.id.buttonStart:
			Log.d(TAG, "onClick: starting srvice");
			startService(new Intent(this, MyService.class));
			break;
		case R.id.buttonStop:
			Log.d(TAG, "onClick: stopping srvice");
			stopService(new Intent(this, MyService.class));
			break;
		case R.id.buttonNext:
			Log.d(TAG, "onClick: next Page");
			Intent intent=new Intent(this,NextPage.class);
			startActivity(intent);
			break;
		}
	}
}