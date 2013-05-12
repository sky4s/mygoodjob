package sky4s.dashboard;

import java.text.NumberFormat;
import java.util.StringTokenizer;
import java.util.Timer;
import java.util.TimerTask;

import org.prowl.torque.remote.ITorqueService;

//import com.example.android.lunarlander.LunarView;
//import com.example.android.lunarlander.LunarView.LunarThread;

import sky4s.dashboard.util.SystemUiHider;

import sky4s.dashboard.R;
import sky4s.dashboard.R.id;
import sky4s.dashboard.R.layout;

import android.annotation.TargetApi;
import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.widget.TextView;

/**
 * An example full-screen activity that shows and hides the system UI (i.e.
 * status bar and navigation/system bar) with user interaction.
 * 
 * @see SystemUiHider
 */
public class PluginActivity extends Activity {
	/**
	 * Whether or not the system UI should be auto-hidden after
	 * {@link #AUTO_HIDE_DELAY_MILLIS} milliseconds.
	 */
	private static final boolean AUTO_HIDE = true;

	/**
	 * If {@link #AUTO_HIDE} is set, the number of milliseconds to wait after
	 * user interaction before hiding the system UI.
	 */
	private static final int AUTO_HIDE_DELAY_MILLIS = 3000;

	/**
	 * If set, will toggle the system UI visibility upon interaction. Otherwise,
	 * will show the system UI visibility upon interaction.
	 */
	private static final boolean TOGGLE_ON_CLICK = true;

	/**
	 * The flags to pass to {@link SystemUiHider#getInstance}.
	 */
	private static final int HIDER_FLAGS = SystemUiHider.FLAG_HIDE_NAVIGATION;

	/**
	 * The instance of the {@link SystemUiHider} for this activity.
	 */
	private SystemUiHider mSystemUiHider;

	// private TextView textView;
	private Handler handler;
	private Timer updateTimer;
	private NumberFormat nf;

	/** A handle to the thread that's actually running the animation. */
	private DashBoardView.DashBoardThread mDashBoardThread;

	/** A handle to the View in which the game is running. */
	private DashBoardView mDashBoardView;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);

		setContentView(R.layout.activity_dash_board);

		mDashBoardView = (DashBoardView) findViewById(R.id.dashboard);
		mDashBoardThread = mDashBoardView.getThread();

		final View controlsView = findViewById(R.id.fullscreen_content_controls);
		// final View contentView = findViewById(R.id.fullscreen_content);

		// LayoutInflater inflater = LayoutInflater.from(this);
		// View view = inflater.inflate(R.layout.activity_dash_board, null);
		// textView = (TextView) view.findViewById(R.id.fullscreen_content);
		// textView = (TextView) findViewById(R.id.fullscreen_content);
		// Max of 2 digits for readings.
		nf = NumberFormat.getInstance();
		nf.setMaximumFractionDigits(2);
		handler = new Handler();
		// setContentView(view);
		// setContentView(R.layout.activity_dash_board);

		// Set up an instance of SystemUiHider to control the system UI for
		// this activity.
		mSystemUiHider = SystemUiHider.getInstance(this, mDashBoardView,
				HIDER_FLAGS);
		mSystemUiHider.setup();
		mSystemUiHider
				.setOnVisibilityChangeListener(new SystemUiHider.OnVisibilityChangeListener() {
					// Cached values.
					int mControlsHeight;
					int mShortAnimTime;

					@Override
					@TargetApi(Build.VERSION_CODES.HONEYCOMB_MR2)
					public void onVisibilityChange(boolean visible) {
						if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2) {
							// If the ViewPropertyAnimator API is available
							// (Honeycomb MR2 and later), use it to animate
							// the
							// in-layout UI controls at the bottom of the
							// screen.
							if (mControlsHeight == 0) {
								mControlsHeight = controlsView.getHeight();
							}
							if (mShortAnimTime == 0) {
								mShortAnimTime = getResources().getInteger(
										android.R.integer.config_shortAnimTime);
							}
							controlsView
									.animate()
									.translationY(visible ? 0 : mControlsHeight)
									.setDuration(mShortAnimTime);
						} else {
							// If the ViewPropertyAnimator APIs aren't
							// available, simply show or hide the in-layout
							// UI
							// controls.
							controlsView.setVisibility(visible ? View.VISIBLE
									: View.GONE);
						}

						if (visible && AUTO_HIDE) {
							// Schedule a hide().
							delayedHide(AUTO_HIDE_DELAY_MILLIS);
						}
					}
				});

		// Set up the user interaction to manually show or hide the system
		// UI.
		mDashBoardView.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View view) {
				if (TOGGLE_ON_CLICK) {
					mSystemUiHider.toggle();
				} else {
					mSystemUiHider.show();
				}
			}
		});

		// Upon interacting with UI controls, delay any scheduled hide()
		// operations to prevent the jarring behavior of controls going away
		// while interacting with the UI.
		findViewById(R.id.dummy_button).setOnTouchListener(
				mDelayHideTouchListener);
	}

	@Override
	protected void onPostCreate(Bundle savedInstanceState) {
		super.onPostCreate(savedInstanceState);

		// Trigger the initial hide() shortly after the activity has been
		// created, to briefly hint to the user that UI controls
		// are available.
		delayedHide(100);
	}

	/**
	 * Touch listener to use for in-layout UI controls to delay hiding the
	 * system UI. This is to prevent the jarring behavior of controls going away
	 * while interacting with activity UI.
	 */
	View.OnTouchListener mDelayHideTouchListener = new View.OnTouchListener() {
		@Override
		public boolean onTouch(View view, MotionEvent motionEvent) {
			if (AUTO_HIDE) {
				delayedHide(AUTO_HIDE_DELAY_MILLIS);
			}
			return false;
		}
	};

	Handler mHideHandler = new Handler();
	Runnable mHideRunnable = new Runnable() {
		@Override
		public void run() {
			mSystemUiHider.hide();
		}
	};

	/**
	 * Schedules a call to hide() in [delay] milliseconds, canceling any
	 * previously scheduled calls.
	 */
	private void delayedHide(int delayMillis) {
		mHideHandler.removeCallbacks(mHideRunnable);
		mHideHandler.postDelayed(mHideRunnable, delayMillis);
	}

	public void onExitButtonClick(View view) {
		super.finish();
	}

	private ITorqueService torqueService;
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

	@Override
	protected void onResume() {
		super.onResume();

		// Bind to the torque service
		Intent intent = new Intent();
		intent.setClassName("org.prowl.torque",
				"org.prowl.torque.remote.TorqueService");
		boolean successfulBind = bindService(intent, connection, 0);

		if (successfulBind) {
			updateTimer = new Timer();
			updateTimer.schedule(new TimerTask() {
				public void run() {
					update();
				}
			}, 1000, 16);
		}

		this.mDashBoardView.start();
	}

	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
		updateTimer.cancel();
		unbindService(connection);

		this.mDashBoardView.stop();
	}

	/**
	 * Do an update
	 */
	public void update() {
		// String used for code readability.
		String text = "";
		if (null == torqueService) {
			return;
		}
		try {
			text = text + "API Version: " + torqueService.getVersion() + "\n";

			torqueService.setDebugTestMode(true);

			// long[] pids = torqueService.getListOfActivePids();
			String[] pids = torqueService.listActivePIDs();
			String[] infos = torqueService.getPIDInformation(pids);
			float[] values = torqueService.getPIDValues(pids);

			int size = pids.length;
			for (int x = 0; x < size; x++) {
				String pid = pids[x];

				// StringTokenizer tokenzier = new StringTokenizer(infos[x],
				// ",");
				// String description = tokenzier.nextToken();
				// tokenzier.nextToken();
				// String unit = tokenzier.nextToken();
				float value = values[x];
				//
				// text = text + description + ": " + nf.format(value);
				// // text = text + description;
				// if (unit != null)
				// text += " " + unit;
				// text += " (" + pid + ")";
				// text += "\n";

				if (pid.equals("0d,0")) {
					// speed obd
					mDashBoardThread.speed = (int) value;
				} else if (pid.equals("0c,0")) {
					// rpm
					mDashBoardThread.rpm = (int) value;
				} else if (pid.equals("211b3")) {
					// rpm
					// mDashBoardThread.rpm = (int) value;
				}
			}

		} catch (RemoteException e) {
			Log.e(getClass().getCanonicalName(), e.getMessage(), e);
		}

		// Update the widget.
		final String myText = text;
		handler.post(new Runnable() {
			public void run() {
				// textView.setText(myText);
			}
		});

	}
}
