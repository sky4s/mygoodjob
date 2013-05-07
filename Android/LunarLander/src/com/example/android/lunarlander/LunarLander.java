/*
 * Copyright (C) 2007 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.example.android.lunarlander;

import android.app.Activity;
import android.hardware.SensorManager;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.Window;
import android.view.WindowManager;
import android.widget.TextView;

//import com.example.android.lunarlander.R;
import com.example.android.lunarlander.LunarView.LunarThread;

/**
 * This is a simple LunarLander activity that houses a single LunarView. It
 * demonstrates...
 * <ul>
 * <li>animating by calling invalidate() from draw()
 * <li>loading and drawing resources
 * <li>handling onPause() in an animation
 * </ul>
 */
public class LunarLander extends Activity {

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch (item.getItemId()) {
		case Menu.FIRST:

			break;
		case Menu.FIRST + 1:
			finish();
			break;
		}

		return super.onOptionsItemSelected(item);
	}

	/** A handle to the thread that's actually running the animation. */
	private LunarThread mLunarThread;

	/** A handle to the View in which the game is running. */
	private LunarView mLunarView;

	/**
	 * Invoked during init to give the Activity a chance to set up its Menu.
	 * 
	 * @param menu
	 *            the Menu to which entries may be added
	 * @return true
	 */
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		super.onCreateOptionsMenu(menu);
		// menu.add(0, Menu.FIRST, 0, "1");
		MenuItem actionItem = menu.add(0, Menu.FIRST + 1, 0, "Exit");
//		actionItem.setShowAsAction(MenuItem.SHOW_AS_ACTION_ALWAYS);
		// menu.add(0, MENU_START, 0, R.string.menu_start);
		// menu.add(0, MENU_STOP, 0, R.string.menu_stop);
		// menu.add(0, MENU_PAUSE, 0, R.string.menu_pause);
		// menu.add(0, MENU_RESUME, 0, R.string.menu_resume);
		// menu.add(0, MENU_EASY, 0, R.string.menu_easy);
		// menu.add(0, MENU_MEDIUM, 0, R.string.menu_medium);
		// menu.add(0, MENU_HARD, 0, R.string.menu_hard);

		return true;
	}

	/**
	 * Invoked when the user selects an item from the Menu.
	 * 
	 * @param item
	 *            the Menu entry which was selected
	 * @return true if the Menu item was legit (and we consumed it), false
	 *         otherwise
	 */
	private SensorManager mSensorManager;

	/**
	 * Invoked when the Activity is created.
	 * 
	 * @param savedInstanceState
	 *            a Bundle containing state saved from a previous execution, or
	 *            null if this is a new execution
	 */
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		// Get an instance of the SensorManager
		mSensorManager = (SensorManager) getSystemService(SENSOR_SERVICE);

		requestWindowFeature(Window.FEATURE_NO_TITLE);
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);

		// tell system to use the layout defined in our XML file
		setContentView(R.layout.lunar_layout);

		// get handles to the LunarView from XML, and its LunarThread
		mLunarView = (LunarView) findViewById(R.id.lunar);
		mLunarView.setmSensorManager(mSensorManager);
		mLunarThread = mLunarView.getThread();

		// give the LunarView a handle to the TextView used for messages
		mLunarView.setTextView((TextView) findViewById(R.id.text));

		if (savedInstanceState == null) {
			// we were just launched: set up a new game
			// mLunarThread.setState(LunarThread.STATE_READY);
			Log.w(this.getClass().getName(), "SIS is null");
		} else {
			// we are being restored: resume a previous game
			// mLunarThread.restoreState(savedInstanceState);
			Log.w(this.getClass().getName(), "SIS is nonnull");
		}
	}

	/**
	 * Invoked when the Activity loses user focus.
	 */
	@Override
	protected void onPause() {
		super.onPause();
//		 mLunarView.getThread().pause(); // pause game when Activity pauses
		mLunarView.stop();
	}
	protected void onResume() {
		super.onResume();
		mLunarView.start();
	}

	/**
	 * Notification that something is about to happen, to give the Activity a
	 * chance to save state.
	 * 
	 * @param outState
	 *            a Bundle into which this Activity should save its state
	 */
	@Override
	protected void onSaveInstanceState(Bundle outState) {
		// just have the View's thread save its state into our Bundle
		super.onSaveInstanceState(outState);
		// mLunarThread.saveState(outState);
		Log.w(this.getClass().getName(), "SIS called");
	}
}
