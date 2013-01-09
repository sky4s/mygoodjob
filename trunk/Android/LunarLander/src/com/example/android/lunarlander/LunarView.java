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

import android.content.Context;
import android.content.res.Resources;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.LinearGradient;
import android.graphics.Paint;
import android.graphics.Paint.FontMetrics;
import android.graphics.Paint.Style;
import android.graphics.PaintFlagsDrawFilter;
import android.graphics.PointF;
import android.graphics.RadialGradient;
import android.graphics.Rect;
import android.graphics.RectF;
import android.graphics.Shader;
import android.graphics.SweepGradient;
import android.os.Handler;
import android.os.Message;
import android.util.AttributeSet;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.widget.TextView;
import dashboard.util.Interpolation;

/**
 * View that draws, takes keystrokes, etc. for a simple LunarLander game.
 * 
 * Has a mode which RUNNING, PAUSED, etc. Has a x, y, dx, dy, ... capturing the
 * current ship physics. All x/y etc. are measured with (0,0) at the lower left.
 * updatePhysics() advances the physics based on realtime. draw() renders the
 * ship, and does an invalidate() to prompt another draw() as soon as possible
 * by the system.
 */
class LunarView extends SurfaceView implements SurfaceHolder.Callback {
	class LunarThread extends Thread {
		/*
		 * Difficulty setting constants
		 */
		// public static final int DIFFICULTY_EASY = 0;
		// public static final int DIFFICULTY_HARD = 1;
		// public static final int DIFFICULTY_MEDIUM = 2;
		/*
		 * Physics constants
		 */
		// public static final int PHYS_DOWN_ACCEL_SEC = 35;
		// public static final int PHYS_FIRE_ACCEL_SEC = 80;
		// public static final int PHYS_FUEL_INIT = 60;
		// public static final int PHYS_FUEL_MAX = 100;
		// public static final int PHYS_FUEL_SEC = 10;
		// public static final int PHYS_SLEW_SEC = 120; // degrees/second rotate
		// public static final int PHYS_SPEED_HYPERSPACE = 180;
		// public static final int PHYS_SPEED_INIT = 30;
		// public static final int PHYS_SPEED_MAX = 120;
		/*
		 * State-tracking constants
		 */
		// public static final int STATE_LOSE = 1;
		// public static final int STATE_PAUSE = 2;
		// public static final int STATE_READY = 3;
		// public static final int STATE_RUNNING = 4;
		// public static final int STATE_WIN = 5;

		/*
		 * Goal condition constants
		 */
		// public static final int TARGET_ANGLE = 18; // > this angle means
		// crash
		// public static final int TARGET_BOTTOM_PADDING = 17; // px below gear
		// public static final int TARGET_PAD_HEIGHT = 8; // how high above
		// ground
		// public static final int TARGET_SPEED = 28; // > this speed means
		// crash
		// public static final double TARGET_WIDTH = 1.6; // width of target
		/*
		 * UI constants (i.e. the speed & fuel bars)
		 */
		public static final int UI_BAR = 100; // width of the bar(s)
		public static final int UI_BAR_HEIGHT = 10; // height of the bar(s)
		// private static final String KEY_DIFFICULTY = "mDifficulty";
		// private static final String KEY_DX = "mDX";
		//
		// private static final String KEY_DY = "mDY";
		// private static final String KEY_FUEL = "mFuel";
		// private static final String KEY_GOAL_ANGLE = "mGoalAngle";
		// private static final String KEY_GOAL_SPEED = "mGoalSpeed";
		// private static final String KEY_GOAL_WIDTH = "mGoalWidth";
		//
		// private static final String KEY_GOAL_X = "mGoalX";
		// private static final String KEY_HEADING = "mHeading";
		// private static final String KEY_LANDER_HEIGHT = "mLanderHeight";
		// private static final String KEY_LANDER_WIDTH = "mLanderWidth";
		// private static final String KEY_WINS = "mWinsInARow";
		//
		// private static final String KEY_X = "mX";
		// private static final String KEY_Y = "mY";

		/*
		 * Member (state) fields
		 */
		/** The drawable to use as the background of the animation canvas */
		// private Bitmap mBackgroundImage;

		/**
		 * Current height of the surface/canvas.
		 * 
		 * @see #setSurfaceSize
		 */
		private int mCanvasHeight = 1;

		/**
		 * Current width of the surface/canvas.
		 * 
		 * @see #setSurfaceSize
		 */
		private int mCanvasWidth = 1;

		/** What to draw for the Lander when it has crashed */
		// private Drawable mCrashedImage;

		/**
		 * Current difficulty -- amount of fuel, allowed angle, etc. Default is
		 * MEDIUM.
		 */
		// private int mDifficulty;

		/** Velocity dx. */
		// private double mDX;

		/** Velocity dy. */
		// private double mDY;

		/** Is the engine burning? */
		// private boolean mEngineFiring;

		/** What to draw for the Lander when the engine is firing */
		// private Drawable mFiringImage;

		/** Fuel remaining */
		// private double mFuel;

		/** Allowed angle. */
		// private int mGoalAngle;

		/** Allowed speed. */
		// private int mGoalSpeed;

		/** Width of the landing pad. */
		// private int mGoalWidth;

		/** X of the landing pad. */
		// private int mGoalX;

		/** Message handler used by thread to interact with TextView */
		private Handler mHandler;

		/**
		 * Lander heading in degrees, with 0 up, 90 right. Kept in the range
		 * 0..360.
		 */
		// private double mHeading;

		/** Pixel height of lander image. */
		// private int mLanderHeight;

		/** What to draw for the Lander in its normal state */
		// private Drawable mLanderImage;

		/** Pixel width of lander image. */
		// private int mLanderWidth;

		/** Used to figure out elapsed time between frames */
		// private long mLastTime;

		/** Paint to draw the lines on screen. */
		// private Paint mLinePaint;

		/** "Bad" speed-too-high variant of the line color. */
		// private Paint mLinePaintBad;

		/** The state of the game. One of READY, RUNNING, PAUSE, LOSE, or WIN */
		// private int mMode;

		/** Currently rotating, -1 left, 0 none, 1 right. */
		// private int mRotating;

		/** Indicate whether the surface has been created & is ready to draw */
		private boolean mRun = false;

		/** Scratch rect object. */
		// private RectF mScratchRect;

		/** Handle to the surface manager object we interact with */
		private SurfaceHolder mSurfaceHolder;

		/** Number of wins in a row. */
		// private int mWinsInARow;

		/** X of lander center. */
		// private double mX;

		/** Y of lander center. */
		// private double mY;

		public LunarThread(SurfaceHolder surfaceHolder, Context context,
				Handler handler) {
			// get handles to some important objects
			mSurfaceHolder = surfaceHolder;
			mHandler = handler;
			mContext = context;

			Resources res = context.getResources();
			// cache handles to our key sprites & other drawables
			// mLanderImage = context.getResources().getDrawable(
			// R.drawable.lander_plain);
			// mFiringImage = context.getResources().getDrawable(
			// R.drawable.lander_firing);
			// mCrashedImage = context.getResources().getDrawable(
			// R.drawable.lander_crashed);

			// load background image as a Bitmap instead of a Drawable b/c
			// we don't need to transform it and it's faster to draw this way
			// mBackgroundImage = BitmapFactory.decodeResource(res,
			// R.drawable.earthrise);

			// Use the regular lander image as the model size for all sprites
			// mLanderWidth = mLanderImage.getIntrinsicWidth();
			// mLanderHeight = mLanderImage.getIntrinsicHeight();

			// Initialize paints for speedometer
			// mLinePaint = new Paint();
			// mLinePaint.setAntiAlias(true);
			// mLinePaint.setARGB(255, 0, 255, 0);
			//
			// mLinePaintBad = new Paint();
			// mLinePaintBad.setAntiAlias(true);
			// mLinePaintBad.setARGB(255, 120, 180, 0);

			// mScratchRect = new RectF(0, 0, 0, 0);

			// mWinsInARow = 0;
			// mDifficulty = DIFFICULTY_MEDIUM;

			// initial show-up of lander (not yet playing)
			// mX = mLanderWidth;
			// mY = mLanderHeight * 2;
			// mFuel = PHYS_FUEL_INIT;
			// mDX = 0;
			// mDY = 0;
			// mHeading = 0;
			// mEngineFiring = true;
		}

		/**
		 * Starts the game, setting parameters for the current difficulty.
		 */
		public void doStart() {
			synchronized (mSurfaceHolder) {
				// First set the game for Medium difficulty
				// mFuel = PHYS_FUEL_INIT;
				// mEngineFiring = false;
				// mGoalWidth = (int) (mLanderWidth * TARGET_WIDTH);
				// mGoalSpeed = TARGET_SPEED;
				// mGoalAngle = TARGET_ANGLE;
				// int speedInit = PHYS_SPEED_INIT;

				// Adjust difficulty params for EASY/HARD
				// if (mDifficulty == DIFFICULTY_EASY) {
				// mFuel = mFuel * 3 / 2;
				// mGoalWidth = mGoalWidth * 4 / 3;
				// mGoalSpeed = mGoalSpeed * 3 / 2;
				// mGoalAngle = mGoalAngle * 4 / 3;
				// speedInit = speedInit * 3 / 4;
				// } else if (mDifficulty == DIFFICULTY_HARD) {
				// mFuel = mFuel * 7 / 8;
				// mGoalWidth = mGoalWidth * 3 / 4;
				// mGoalSpeed = mGoalSpeed * 7 / 8;
				// speedInit = speedInit * 4 / 3;
				// }

				// pick a convenient initial location for the lander sprite
				// mX = mCanvasWidth / 2;
				// mY = mCanvasHeight - mLanderHeight / 2;

				// start with a little random motion
				// mDY = Math.random() * -speedInit;
				// mDX = Math.random() * 2 * speedInit - speedInit;
				// mHeading = 0;

				// Figure initial spot for landing, not too near center
				// while (true) {
				// mGoalX = (int) (Math.random() * (mCanvasWidth - mGoalWidth));
				// if (Math.abs(mGoalX - (mX - mLanderWidth / 2)) >
				// mCanvasHeight / 6)
				// break;
				// }

				// mLastTime = System.currentTimeMillis() + 100;
				// setState(STATE_RUNNING);
			}
		}

		/**
		 * Pauses the physics update & animation.
		 */
		// public void pause() {
		// synchronized (mSurfaceHolder) {
		// if (mMode == STATE_RUNNING) setState(STATE_PAUSE);
		// }
		// }

		/**
		 * Restores game state from the indicated Bundle. Typically called when
		 * the Activity is being restored after having been previously
		 * destroyed.
		 * 
		 * @param savedState
		 *            Bundle containing the game state
		 */
		// public synchronized void restoreState(Bundle savedState) {
		// synchronized (mSurfaceHolder) {
		// // setState(STATE_PAUSE);
		// // mRotating = 0;
		// // mEngineFiring = false;
		//
		// // mDifficulty = savedState.getInt(KEY_DIFFICULTY);
		// // mX = savedState.getDouble(KEY_X);
		// // mY = savedState.getDouble(KEY_Y);
		// // mDX = savedState.getDouble(KEY_DX);
		// // mDY = savedState.getDouble(KEY_DY);
		// // mHeading = savedState.getDouble(KEY_HEADING);
		// //
		// // mLanderWidth = savedState.getInt(KEY_LANDER_WIDTH);
		// // mLanderHeight = savedState.getInt(KEY_LANDER_HEIGHT);
		// // mGoalX = savedState.getInt(KEY_GOAL_X);
		// // mGoalSpeed = savedState.getInt(KEY_GOAL_SPEED);
		// // mGoalAngle = savedState.getInt(KEY_GOAL_ANGLE);
		// // mGoalWidth = savedState.getInt(KEY_GOAL_WIDTH);
		// // mWinsInARow = savedState.getInt(KEY_WINS);
		// // mFuel = savedState.getDouble(KEY_FUEL);
		// }
		// }

		@Override
		public void run() {
			while (mRun) {
				Canvas c = null;
				try {
					c = mSurfaceHolder.lockCanvas(null);
					synchronized (mSurfaceHolder) {
						// if (mMode == STATE_RUNNING) updatePhysics();
						doDraw(c);
					}
				} finally {
					// do this in a finally so that if an exception is thrown
					// during the above, we don't leave the Surface in an
					// inconsistent state
					if (c != null) {
						mSurfaceHolder.unlockCanvasAndPost(c);
					}
				}
			}
		}

		/**
		 * Dump game state to the provided Bundle. Typically called when the
		 * Activity is being suspended.
		 * 
		 * @return Bundle with this view's state
		 */
		// public Bundle saveState(Bundle map) {
		// synchronized (mSurfaceHolder) {
		// if (map != null) {
		// map.putInt(KEY_DIFFICULTY, Integer.valueOf(mDifficulty));
		// map.putDouble(KEY_X, Double.valueOf(mX));
		// map.putDouble(KEY_Y, Double.valueOf(mY));
		// map.putDouble(KEY_DX, Double.valueOf(mDX));
		// map.putDouble(KEY_DY, Double.valueOf(mDY));
		// map.putDouble(KEY_HEADING, Double.valueOf(mHeading));
		// map.putInt(KEY_LANDER_WIDTH, Integer.valueOf(mLanderWidth));
		// map.putInt(KEY_LANDER_HEIGHT, Integer
		// .valueOf(mLanderHeight));
		// map.putInt(KEY_GOAL_X, Integer.valueOf(mGoalX));
		// map.putInt(KEY_GOAL_SPEED, Integer.valueOf(mGoalSpeed));
		// map.putInt(KEY_GOAL_ANGLE, Integer.valueOf(mGoalAngle));
		// map.putInt(KEY_GOAL_WIDTH, Integer.valueOf(mGoalWidth));
		// map.putInt(KEY_WINS, Integer.valueOf(mWinsInARow));
		// map.putDouble(KEY_FUEL, Double.valueOf(mFuel));
		// }
		// }
		// return map;
		// }

		/**
		 * Sets the current difficulty.
		 * 
		 * @param difficulty
		 */
		// public void setDifficulty(int difficulty) {
		// synchronized (mSurfaceHolder) {
		// mDifficulty = difficulty;
		// }
		// }

		/**
		 * Sets the current difficulty.
		 * 
		 * @param difficulty
		 */
		// public void setDifficulty(int difficulty) {
		// synchronized (mSurfaceHolder) {
		// mDifficulty = difficulty;
		// }
		// }

		/**
		 * Sets if the engine is currently firing.
		 */
		// public void setFiring(boolean firing) {
		// synchronized (mSurfaceHolder) {
		// mEngineFiring = firing;
		// }
		// }

		/**
		 * Used to signal the thread whether it should be running or not.
		 * Passing true allows the thread to run; passing false will shut it
		 * down if it's already running. Calling start() after this was most
		 * recently called with false will result in an immediate shutdown.
		 * 
		 * @param b
		 *            true to run, false to shut down
		 */
		public void setRunning(boolean b) {
			mRun = b;
		}

		/**
		 * Sets the game mode. That is, whether we are running, paused, in the
		 * failure state, in the victory state, etc.
		 * 
		 * @see #setState(int, CharSequence)
		 * @param mode
		 *            one of the STATE_* constants
		 */
		// public void setState(int mode) {
		// synchronized (mSurfaceHolder) {
		// setState(mode, null);
		// }
		// }

		/**
		 * Sets the game mode. That is, whether we are running, paused, in the
		 * failure state, in the victory state, etc.
		 * 
		 * @param mode
		 *            one of the STATE_* constants
		 * @param message
		 *            string to add to screen or null
		 */
		// public void setState(int mode, CharSequence message) {
		// /*
		// * This method optionally can cause a text message to be displayed
		// * to the user when the mode changes. Since the View that actually
		// * renders that text is part of the main View hierarchy and not
		// * owned by this thread, we can't touch the state of that View.
		// * Instead we use a Message + Handler to relay commands to the main
		// * thread, which updates the user-text View.
		// */
		// synchronized (mSurfaceHolder) {
		// mMode = mode;
		//
		// if (mMode == STATE_RUNNING) {
		// Message msg = mHandler.obtainMessage();
		// Bundle b = new Bundle();
		// b.putString("text", "");
		// b.putInt("viz", View.INVISIBLE);
		// msg.setData(b);
		// mHandler.sendMessage(msg);
		// } else {
		// mRotating = 0;
		// mEngineFiring = false;
		// Resources res = mContext.getResources();
		// CharSequence str = "";
		// if (mMode == STATE_READY)
		// str = res.getText(R.string.mode_ready);
		// else if (mMode == STATE_PAUSE)
		// str = res.getText(R.string.mode_pause);
		// else if (mMode == STATE_LOSE)
		// str = res.getText(R.string.mode_lose);
		// else if (mMode == STATE_WIN)
		// str = res.getString(R.string.mode_win_prefix)
		// + mWinsInARow + " "
		// + res.getString(R.string.mode_win_suffix);
		//
		// if (message != null) {
		// str = message + "\n" + str;
		// }
		//
		// if (mMode == STATE_LOSE) mWinsInARow = 0;
		//
		// Message msg = mHandler.obtainMessage();
		// Bundle b = new Bundle();
		// b.putString("text", str.toString());
		// b.putInt("viz", View.VISIBLE);
		// msg.setData(b);
		// mHandler.sendMessage(msg);
		// }
		// }
		// }

		/* Callback invoked when the surface dimensions change. */
		public void setSurfaceSize(int width, int height) {
			// synchronized to make sure these all change atomically
			synchronized (mSurfaceHolder) {
				mCanvasWidth = width;
				mCanvasHeight = height;

				// don't forget to resize the background image
				// mBackgroundImage = Bitmap.createScaledBitmap(
				// mBackgroundImage, width, height, true);
			}
		}

		/**
		 * Resumes from a pause.
		 */
		// public void unpause() {
		// // Move the real time clock up to now
		// synchronized (mSurfaceHolder) {
		// mLastTime = System.currentTimeMillis() + 100;
		// }
		// setState(STATE_RUNNING);
		// }

		/**
		 * Handles a key-down event.
		 * 
		 * @param keyCode
		 *            the key that was pressed
		 * @param msg
		 *            the original event object
		 * @return true
		 */
		// boolean doKeyDown(int keyCode, KeyEvent msg) {
		// synchronized (mSurfaceHolder) {
		// boolean okStart = false;
		// if (keyCode == KeyEvent.KEYCODE_DPAD_UP) okStart = true;
		// if (keyCode == KeyEvent.KEYCODE_DPAD_DOWN) okStart = true;
		// if (keyCode == KeyEvent.KEYCODE_S) okStart = true;
		//
		// if (okStart
		// && (mMode == STATE_READY || mMode == STATE_LOSE || mMode ==
		// STATE_WIN)) {
		// // ready-to-start -> start
		// doStart();
		// return true;
		// } else if (mMode == STATE_PAUSE && okStart) {
		// // paused -> running
		// unpause();
		// return true;
		// } else if (mMode == STATE_RUNNING) {
		// // center/space -> fire
		// if (keyCode == KeyEvent.KEYCODE_DPAD_CENTER
		// || keyCode == KeyEvent.KEYCODE_SPACE) {
		// setFiring(true);
		// return true;
		// // left/q -> left
		// } else if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT
		// || keyCode == KeyEvent.KEYCODE_Q) {
		// mRotating = -1;
		// return true;
		// // right/w -> right
		// } else if (keyCode == KeyEvent.KEYCODE_DPAD_RIGHT
		// || keyCode == KeyEvent.KEYCODE_W) {
		// mRotating = 1;
		// return true;
		// // up -> pause
		// } else if (keyCode == KeyEvent.KEYCODE_DPAD_UP) {
		// pause();
		// return true;
		// }
		// }
		//
		// return false;
		// }
		// }

		/**
		 * Handles a key-up event.
		 * 
		 * @param keyCode
		 *            the key that was pressed
		 * @param msg
		 *            the original event object
		 * @return true if the key was handled and consumed, or else false
		 */
		// boolean doKeyUp(int keyCode, KeyEvent msg) {
		// boolean handled = false;
		//
		// synchronized (mSurfaceHolder) {
		// if (mMode == STATE_RUNNING) {
		// if (keyCode == KeyEvent.KEYCODE_DPAD_CENTER
		// || keyCode == KeyEvent.KEYCODE_SPACE) {
		// setFiring(false);
		// handled = true;
		// } else if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT
		// || keyCode == KeyEvent.KEYCODE_Q
		// || keyCode == KeyEvent.KEYCODE_DPAD_RIGHT
		// || keyCode == KeyEvent.KEYCODE_W) {
		// mRotating = 0;
		// handled = true;
		// }
		// }
		// }
		//
		// return handled;
		// }

		int lightGray = Color.rgb(192, 192, 192);
		int lightRed = Color.rgb(192, 0, 0);
		int middleGray = Color.rgb(144, 144, 144);
		int middleRed = Color.rgb(144, 0, 0);
		int gray = Color.rgb(128, 128, 128);
		int dullGray = Color.rgb(64, 64, 64);
		int darkGray = Color.rgb(32, 32, 32);

		/**
		 * Draws the ship, fuel/speed bars, and background to the provided
		 * Canvas.
		 */
		private void doDraw(Canvas canvas) {
			if (null == canvas) {
				return;
			}

			Paint paint = new Paint();
			paint.setStyle(Paint.Style.STROKE);
			paint.setAntiAlias(true);
			paint.setFilterBitmap(true);
			canvas.setDrawFilter(new PaintFlagsDrawFilter(0,
					Paint.ANTI_ALIAS_FLAG | Paint.FILTER_BITMAP_FLAG));

			int shortSideLength = Math.min(mCanvasWidth, mCanvasHeight);

			int baseRadius = shortSideLength / 2;
			int cx = mCanvasWidth / 2;
			int cy = mCanvasHeight / 2;

			// �~�� ���h
			int dkgrayWidth = 22;
			paint.setColor(darkGray);
			paint.setStrokeWidth(dkgrayWidth);
			canvas.drawCircle(cx, cy, baseRadius - dkgrayWidth / 2, paint);

			// �~�� ����
			int grayWidth = 16;
			int grayOffset = (dkgrayWidth - grayWidth) / 2;
			paint.setColor(middleGray);
			paint.setStrokeWidth(grayWidth);
			canvas.drawCircle(cx, cy, baseRadius - grayWidth / 2 - grayOffset,
					paint);

			// �~�� ����
			boolean showStairs = true;
			int outterStairsCount = 6;
			if (showStairs) {
				paint.setStrokeWidth(1);
				for (int x = 0; x < outterStairsCount; x++) {
					int color = (x % 2 == 0) ? gray : darkGray;
					paint.setColor(color);
					canvas.drawCircle(cx, cy, baseRadius - dkgrayWidth - 1 - x,
							paint);
				}
			}

			// �~�� ���
			float[] polarValues = new float[2];
			int midgrayWidth = 8;
			int whiteWidth = 5;
			Polar2cartesianIF polar2cartesian = new MathPolar2cartesian();
			int[] outterColors = new int[] { Color.RED, Color.BLACK,
					Color.BLACK, Color.BLACK, Color.BLACK, Color.WHITE,
					Color.WHITE, Color.WHITE, Color.WHITE, Color.WHITE,
					Color.WHITE, Color.WHITE };

			for (int x = 0; x < 12; x++) {

				polarValues[1] = x * 30;
				polarValues[0] = baseRadius;
				float[] coord0 = polar2cartesian
						.getCartesianCoordinatesValues(polarValues);
				polarValues[0] = baseRadius - dkgrayWidth;
				float[] coord1 = polar2cartesian
						.getCartesianCoordinatesValues(polarValues);

				paint.setColor(dullGray);
				paint.setStrokeWidth(midgrayWidth);
				canvas.drawLine(coord0[0] + cx, coord0[1] + cy, coord1[0] + cx,
						coord1[1] + cy, paint);

				coord0[0] = (float) Interpolation.linear(0, 1, coord0[0],
						coord1[0], .3);
				coord0[1] = (float) Interpolation.linear(0, 1, coord0[1],
						coord1[1], .3);

				paint.setColor(outterColors[x]);
				paint.setStrokeWidth(whiteWidth);
				canvas.drawLine(coord0[0] + cx, coord0[1] + cy, coord1[0] + cx,
						coord1[1] + cy, paint);
			}

			// ����
			int internalRadius = baseRadius - dkgrayWidth - 1
					- outterStairsCount;
			// RadialGradient lg = new RadialGradient(cx, cy, internalRadius,
			// new int[] { Color.BLACK, Color.BLACK, Color.BLUE },
			// new float[] { 0, 0.7f, 1 }, Shader.TileMode.CLAMP);
			// paint.setColor(Color.WHITE);
			// paint.setShader(lg);
			// paint.setStyle(Paint.Style.FILL);
			// canvas.drawCircle(cx, cy, internalRadius, paint);

			int degreePerkRPM = 30;
			int maxkRPM = 7;
			int startDegree = 150;
			int endDegree = degreePerkRPM * maxkRPM + startDegree;
			int redDegree = endDegree - degreePerkRPM;

			int ringWidth = 5;
			paint.setColor(Color.RED);
			paint.setStyle(Paint.Style.STROKE);
			paint.setStrokeWidth(ringWidth);
			RectF oval1 = new RectF(cx - internalRadius + 1, cy
					- internalRadius + 1, cx + internalRadius - 1, cy
					+ internalRadius - 1);
			canvas.drawArc(oval1, redDegree, degreePerkRPM, false, paint);

			// ��שw�q
			int graduationWidth = 6;

			int graduationLength = 14;
			int graduationRadius = internalRadius - ringWidth - 1;

			int middleGraduationWidth = (int) (graduationWidth * (2. / 3));
			int middleGraduationLength = graduationLength / 2;

			int smallGraduationWidth = middleGraduationWidth / 2;
			int smallGraduationLength = middleGraduationLength - 2;

			// ���h
			int innerGradientRadius = graduationRadius - middleGraduationLength;
			RadialGradient lg = new RadialGradient(cx, cy, innerGradientRadius,
					new int[] { Color.BLACK, Color.BLACK, dullGray },
					new float[] { 0, 0.83f, 1 }, Shader.TileMode.CLAMP);
			// paint.setColor(Color.BLACK);
			paint.setShader(lg);
			paint.setStyle(Paint.Style.FILL);
			canvas.drawCircle(cx, cy, innerGradientRadius, paint);

			// ���⺥�h
			int redGradientWidth = 100;
			int redGradientRadius = innerGradientRadius - redGradientWidth / 2;
			RadialGradient redlg = new RadialGradient(cx, cy,
					innerGradientRadius, new int[] { Color.BLACK, Color.BLACK,
							lightRed }, new float[] { 0, 0.7f, 1 },
					Shader.TileMode.CLAMP);
			paint.setShader(redlg);
			paint.setColor(Color.RED);
			paint.setStyle(Paint.Style.STROKE);
			paint.setStrokeWidth(redGradientWidth);
			RectF redoval = new RectF(cx - redGradientRadius, cy
					- redGradientRadius, cx + redGradientRadius, cy
					+ redGradientRadius);
			canvas.drawArc(redoval, redDegree, degreePerkRPM, false, paint);
			paint.setShader(null);

			int textSize = 45;
			int distanceOfFontToLine = 4;
			Paint fpaint = new Paint();
			fpaint.setStyle(Style.FILL);
			fpaint.setTextSize(textSize);
			fpaint.setTextAlign(Paint.Align.CENTER);

			float[] fontcoord = new float[2];
			Rect fontrect = new Rect();
			// ���
			for (int x = 0; x <= maxkRPM; x++) {
				int degree = startDegree + x * degreePerkRPM;
				int c = (x != 7) ? Color.WHITE : Color.RED;
				float[][] coord0 = drawRadiation(canvas, degree,
						graduationRadius, graduationLength, c, graduationWidth,
						polar2cartesian);

				// �~��
				fontcoord[0] = (float) Interpolation.linear(0, 1, coord0[0][0],
						coord0[1][0], distanceOfFontToLine);
				fontcoord[1] = (float) Interpolation.linear(0, 1, coord0[0][1],
						coord0[1][1], distanceOfFontToLine);

				// �e�I, �Ѧҥ�
				fpaint.setStrokeWidth(3);
				fpaint.setColor(Color.YELLOW);
				canvas.drawPoint(fontcoord[0] + cx, fontcoord[1] + cy, fpaint);

				String text = Integer.toString(x);
				// canvas.drawText(text, fontcoord[0] + cx, fontcoord[1] + cy,
				// fpaint);

				// paint.getTextBounds(text, 0, text.length(), fontrect);
				// fontcoord[0] -= fontrect.width() / 2;
				// FontMetrics fm = fpaint.getFontMetrics();
				// int textHeight = (int) (Math.ceil(fm.descent - fm.ascent) +
				// 2);
				// int textHeight = getFontHeight(fpaint);
				// int textHeight = fontrect.height();
				// fontcoord[1] += textHeight ;

				// ��r
				fpaint.setColor(Color.WHITE);
				// PointF p = getTextCenterToDraw(text, new PointF(fontcoord[0]
				// + cx, fontcoord[1] + cy), fpaint);
				int halfTextSize = textSize / 2;
				Rect textRect = new Rect(
						(int) fontcoord[0] + cx - halfTextSize,
						(int) fontcoord[1] + cy - halfTextSize,
						(int) fontcoord[0] + cx + halfTextSize,
						(int) fontcoord[1] + cy + halfTextSize);
				PointF p = getTextCenterInRect(text, textRect, fpaint);
				// + cx,)
				canvas.drawText(text, p.x, p.y, fpaint);

				// �e�I, �Ѧҥ�
				fpaint.setStrokeWidth(3);
				fpaint.setColor(Color.YELLOW);
				canvas.drawPoint(fontcoord[0] + cx, fontcoord[1] + cy, fpaint);

				if (x < maxkRPM) {
					// �����
					int degree2 = degree + 15;
					int c2 = (x < (maxkRPM - 1)) ? Color.WHITE : Color.RED;
					drawRadiation(canvas, degree2, graduationRadius,
							middleGraduationLength, c2, middleGraduationWidth,
							polar2cartesian);
				}
			}

			drawHelloRectangle(canvas, 10, 10, 150, 30);

			// �p���
			for (int degree = startDegree; degree < endDegree; degree += 3) {
				if (degree % 30 != 0 && degree % 15 != 0) {

					int c = (degree < (endDegree - degreePerkRPM)) ? Color.WHITE
							: Color.RED;
					drawRadiation(canvas, degree, graduationRadius,
							smallGraduationLength, c, smallGraduationWidth,
							polar2cartesian);
				}

			}

		}

		private PointF getTextCenterInRect(String text, Rect rect, Paint paint) {
			int fontHeight = (int) (rect.height() / 0.7);
			paint.setTextSize(fontHeight);
			Rect bounds = new Rect();
			paint.getTextBounds(text, 0, text.length(), bounds);
			PointF p = new PointF(rect.left + rect.width() / 2, rect.top
					+ rect.height() / 2 + (bounds.bottom - bounds.top) / 2);
			return p;
		}

		void drawHelloRectangle(Canvas c, int topLeftX, int topLeftY,
				int width, int height) {
			Paint mPaint = new Paint();
			// height of 'Hello World'; height*0.7 looks good
			int fontHeight = (int) (height * 0.7);

			mPaint.setColor(Color.RED);
			mPaint.setStyle(Style.FILL);
			c.drawRect(topLeftX, topLeftY, topLeftX + width, topLeftY + height,
					mPaint);

			mPaint.setTextSize(fontHeight);
			mPaint.setColor(Color.BLACK);
			mPaint.setTextAlign(Paint.Align.CENTER);
			String textToDraw = new String("Hello World");
			Rect bounds = new Rect();
			mPaint.getTextBounds(textToDraw, 0, textToDraw.length(), bounds);
			c.drawText(textToDraw, topLeftX + width / 2, topLeftY + height / 2
					+ (bounds.bottom - bounds.top) / 2, mPaint);
		}

		private int getFontHeight(Paint paint) {
			FontMetrics fm = paint.getFontMetrics();
			return (int) Math.ceil(fm.descent - fm.top) + 2;

		}

		private PointF getTextCenterToDraw(String text, PointF center,
				Paint paint) {
			Rect textBounds = new Rect();
			paint.getTextBounds(text, 0, text.length(), textBounds);
			float x = center.x - textBounds.width() * 0.4f;
			float y = center.y + textBounds.height() * 0.4f;
			return new PointF(x, y);
		}

		private float[][] drawRadiation(Canvas canvas, int degree, int radius,
				int length, int color, int width,
				Polar2cartesianIF polar2cartesian) {
			float[] polarValues = new float[2];
			polarValues[1] = degree;
			polarValues[0] = radius;
			float[] coord0 = polar2cartesian
					.getCartesianCoordinatesValues(polarValues);

			polarValues[0] = radius - length;
			float[] coord1 = polar2cartesian
					.getCartesianCoordinatesValues(polarValues);

			Paint paint = new Paint();
			paint.setStyle(Paint.Style.STROKE);
			paint.setAntiAlias(true);
			paint.setFilterBitmap(true);
			paint.setStrokeWidth(width);
			paint.setColor(color);

			int cx = mCanvasWidth / 2;
			int cy = mCanvasHeight / 2;
			canvas.drawLine(coord0[0] + cx, coord0[1] + cy, coord1[0] + cx,
					coord1[1] + cy, paint);

			float[][] coordinators = new float[][] { coord0, coord1 };
			return coordinators;
		}
	}

	/** Handle to the application context, used to e.g. fetch Drawables. */
	private Context mContext;

	/** Pointer to the text view to display "Paused.." etc. */
	private TextView mStatusText;

	/** The thread that actually draws the animation */
	private LunarThread thread;

	public LunarView(Context context, AttributeSet attrs) {
		super(context, attrs);

		// register our interest in hearing about changes to our surface
		SurfaceHolder holder = getHolder();
		holder.addCallback(this);

		// create thread only; it's started in surfaceCreated()
		thread = new LunarThread(holder, context, new Handler() {
			@Override
			public void handleMessage(Message m) {
				mStatusText.setVisibility(m.getData().getInt("viz"));
				mStatusText.setText(m.getData().getString("text"));
			}
		});
		setFocusable(true); // make sure we get key events
	}

	/**
	 * Fetches the animation thread corresponding to this LunarView.
	 * 
	 * @return the animation thread
	 */
	public LunarThread getThread() {
		return thread;
	}

	/**
	 * Standard override to get key-press events.
	 */
	// @Override
	// public boolean onKeyDown(int keyCode, KeyEvent msg) {
	// return thread.doKeyDown(keyCode, msg);
	// }

	/**
	 * Standard override for key-up. We actually care about these, so we can
	 * turn off the engine or stop rotating.
	 */
	// @Override
	// public boolean onKeyUp(int keyCode, KeyEvent msg) {
	// return thread.doKeyUp(keyCode, msg);
	// }

	/**
	 * Standard window-focus override. Notice focus lost so we can pause on
	 * focus lost. e.g. user switches to take a call.
	 */
	@Override
	public void onWindowFocusChanged(boolean hasWindowFocus) {
		// if (!hasWindowFocus) thread.pause();
	}

	/**
	 * Installs a pointer to the text view used for messages.
	 */
	public void setTextView(TextView textView) {
		mStatusText = textView;
	}

	/* Callback invoked when the surface dimensions change. */
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		thread.setSurfaceSize(width, height);
	}

	/*
	 * Callback invoked when the Surface has been created and is ready to be
	 * used.
	 */
	public void surfaceCreated(SurfaceHolder holder) {
		// start the thread here so that we don't busy-wait in run()
		// waiting for the surface to be created
		thread.setRunning(true);
		thread.start();
	}

	/*
	 * Callback invoked when the Surface has been destroyed and must no longer
	 * be touched. WARNING: after this method returns, the Surface/Canvas must
	 * never be touched again!
	 */
	public void surfaceDestroyed(SurfaceHolder holder) {
		// we have to tell thread to shut down & wait for it to finish, or else
		// it might touch the Surface after we return and explode
		boolean retry = true;
		thread.setRunning(false);
		while (retry) {
			try {
				thread.join();
				retry = false;
			} catch (InterruptedException e) {
			}
		}
	}

}

interface Polar2cartesianIF {
	float[] getCartesianCoordinatesValues(final float[] polarValues);
}

class MathPolar2cartesian implements Polar2cartesianIF {
	public static final float[] cartesian2polarCoordinatesValues(
			final float[] cartesianValues) {
		float[] polarValues = new float[2];

		// polarValues[0] = cartesianValues[0];
		float t1 = cartesianValues[0];
		float t2 = cartesianValues[1];
		polarValues[0] = (float) (Math.sqrt(Math.pow(cartesianValues[0], 2)
				+ Math.pow(cartesianValues[1], 2)));
		if (t1 == 0 && t2 == 0) {
			polarValues[1] = 0;
		} else {
			polarValues[1] = (float) Math.atan2(t2, t1);
		}
		polarValues[1] *= (180.0 / Math.PI);
		while (polarValues[1] >= 360.0) { // Not necessary, but included as a
											// check.
			polarValues[1] -= 360.0;
		}
		while (polarValues[1] < 0) {
			polarValues[1] += 360.0;
		}
		return polarValues;
	}

	/**
	 * ���y��=>�åd��y��
	 * 
	 * @param polarValues
	 *            double[]
	 * @return double[]
	 */
	public static final float[] polar2cartesianCoordinatesValues(
			final float[] polarValues) {
		float t = (float) ((polarValues[1] * Math.PI) / 180.0);

		float[] cartesianValues = new float[2];
		cartesianValues[0] = (float) (polarValues[0] * Math.cos(t));
		cartesianValues[1] = (float) (polarValues[0] * Math.sin(t));

		return cartesianValues;
	}

	public float[] getCartesianCoordinatesValues(final float[] polarValues) {
		return polar2cartesianCoordinatesValues(polarValues);
	}
}

class LutPolar2cartesian implements Polar2cartesianIF {
	public float[] getCartesianCoordinatesValues(final float[] polarValues) {
		float t = (float) ((polarValues[1] * Math.PI) / 180.0);

		float[] cartesianValues = new float[2];
		cartesianValues[0] = (float) (polarValues[0] * Math.cos(t));
		cartesianValues[1] = (float) (polarValues[0] * Math.sin(t));

		return cartesianValues;
	}
}