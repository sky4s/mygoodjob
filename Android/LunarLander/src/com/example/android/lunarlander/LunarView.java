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
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.graphics.PaintFlagsDrawFilter;
import android.graphics.PointF;
import android.graphics.RadialGradient;
import android.graphics.Rect;
import android.graphics.RectF;
import android.graphics.Shader;
import android.graphics.Typeface;
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
		 * UI constants (i.e. the speed & fuel bars)
		 */

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

		/** Message handler used by thread to interact with TextView */
		private Handler mHandler;

		/** Indicate whether the surface has been created & is ready to draw */
		private boolean mRun = false;

		/** Handle to the surface manager object we interact with */
		private SurfaceHolder mSurfaceHolder;

		public LunarThread(SurfaceHolder surfaceHolder, Context context,
				Handler handler) {
			// get handles to some important objects
			mSurfaceHolder = surfaceHolder;
			mHandler = handler;
			mContext = context;

			Resources res = context.getResources();

		}

		/**
		 * Starts the game, setting parameters for the current difficulty.
		 */
		public void doStart() {
			synchronized (mSurfaceHolder) {
				startTime = System.currentTimeMillis();
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

		@Override
		public void run() {
			while (mRun) {
				Canvas c = null;
				try {
					c = mSurfaceHolder.lockCanvas(null);
					synchronized (mSurfaceHolder) {
						// if (mMode == STATE_RUNNING) updatePhysics();
						updateDashboard();
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

		private long startTime;
		private String gear = "N";
		private int speed = 0;
		private int rpm = 0;

		private void updateDashboard() {

		}

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

		int lightGray = Color.rgb(192, 192, 192);
		int lightRed = Color.rgb(192, 0, 0);
		int middleGray = Color.rgb(144, 144, 144);
		int middleRed = Color.rgb(144, 0, 0);
		int gray = Color.rgb(128, 128, 128);
		int dullGray = Color.rgb(64, 64, 64);

		/**
		 * Draws the ship, fuel/speed bars, and background to the provided
		 * Canvas.
		 */
		private void doDraw(Canvas canvas) {
			if (null == canvas) {
				return;
			}

			// =================================================================
			// 初期設定
			// =================================================================
			Paint paint = new Paint();
			paint.setStyle(Paint.Style.STROKE);
			paint.setAntiAlias(true);
			paint.setFilterBitmap(true);
			canvas.setDrawFilter(new PaintFlagsDrawFilter(0,
					Paint.ANTI_ALIAS_FLAG | Paint.FILTER_BITMAP_FLAG));

			// 找到短邊, 好確定圓要怎麼畫
			int shortSideLength = Math.min(mCanvasWidth, mCanvasHeight);
			// 找到基礎半徑(最長半徑)
			int baseRadius = shortSideLength / 2;
			int cx = mCanvasWidth / 2;
			int cy = mCanvasHeight / 2;
			// =================================================================

			// =================================================================
			// 外圈
			// =================================================================
			// 外圈 底層(深色)
			int dkgrayWidth = 22;
			paint.setColor(darkGray);
			paint.setStrokeWidth(dkgrayWidth);
			canvas.drawCircle(cx, cy, baseRadius - dkgrayWidth / 2, paint);

			// 外圈 中間(稍淺)
			int grayWidth = 16;
			int grayOffset = (dkgrayWidth - grayWidth) / 2;
			paint.setColor(middleGray);
			paint.setStrokeWidth(grayWidth);
			canvas.drawCircle(cx, cy, baseRadius - grayWidth / 2 - grayOffset,
					paint);

			// 外圈 階梯
			int outterStairsCount = 0;
			paint.setStrokeWidth(1);
			for (int x = 0; x < outterStairsCount; x++) {
				int color = (x % 2 == 0) ? gray : darkGray;
				paint.setColor(color);
				canvas.drawCircle(cx, cy, baseRadius - dkgrayWidth - 1 - x,
						paint);
			}

			// 外圈 刻度
			float[] polarValues = new float[2];
			int midgrayWidth = 8; // 刻度的洞
			int whiteWidth = 5;// 刻度
			Polar2cartesianIF polar2cartesian = new MathPolar2cartesian();
			int[] outterColors = new int[] { Color.RED, Color.BLACK,
					Color.BLACK, Color.BLACK, Color.BLACK,
					Color.WHITE,// 0
					Color.WHITE, Color.WHITE, Color.WHITE, Color.WHITE,
					Color.WHITE, Color.WHITE };

			for (int x = 0; x < 12; x++) {
				// =================================================================
				// 刻度的洞
				// =================================================================
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
				// =================================================================

				// =================================================================
				// 刻度
				// =================================================================
				coord0[0] = (float) Interpolation.linear(0, 1, coord0[0],
						coord1[0], .3);
				coord0[1] = (float) Interpolation.linear(0, 1, coord0[1],
						coord1[1], .3);

				paint.setColor(outterColors[x]);
				paint.setStrokeWidth(whiteWidth);
				canvas.drawLine(coord0[0] + cx, coord0[1] + cy, coord1[0] + cx,
						coord1[1] + cy, paint);
				// =================================================================
			}
			// =================================================================

			// =================================================================
			// 內圈
			// =================================================================
			int internalRadius = baseRadius - dkgrayWidth - 1
					- outterStairsCount;
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

			// 刻度定義
			int graduatorWidth = 6;
			int graduatorLength = 14;
			int graduatorRadius = internalRadius - ringWidth - 1;

			int middleGraduatorWidth = (int) (graduatorWidth * (2. / 3));
			int middleGraduatorLength = graduatorLength / 2;

			int smallGraduatorWidth = middleGraduatorWidth / 2;
			int smallGraduatorLength = middleGraduatorLength - 2;

			// 漸層
			int innerGradientRadius = graduatorRadius - middleGraduatorLength;
			RadialGradient lg = new RadialGradient(cx, cy, innerGradientRadius,
					new int[] { Color.BLACK, Color.BLACK, dullGray },
					new float[] { 0, 0.83f, 1 }, Shader.TileMode.CLAMP);
			paint.setShader(lg);
			paint.setStyle(Paint.Style.FILL);
			canvas.drawCircle(cx, cy, innerGradientRadius, paint);

			// 紅色漸層
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

			// 字
			int textSize = 45;
			int distanceOfFontToLine = 4;
			Paint fpaint = new Paint();
			fpaint.setTypeface(Typeface.DEFAULT_BOLD);
			fpaint.setStyle(Style.FILL);
			fpaint.setTextSize(textSize);
			fpaint.setTextAlign(Paint.Align.CENTER);

			float[] fontcoord = new float[2];
			// 刻度
			for (int x = 0; x <= maxkRPM; x++) {
				int degree = startDegree + x * degreePerkRPM;

				int c = (x != 7) ? Color.WHITE : Color.RED;
				// 大刻度
				float[][] coord0 = drawRadiation(canvas, degree,
						graduatorRadius, graduatorLength, c, graduatorWidth,
						polar2cartesian);

				// 外插
				fontcoord[0] = (float) Interpolation.linear(0, 1, coord0[0][0],
						coord0[1][0], distanceOfFontToLine);
				fontcoord[1] = (float) Interpolation.linear(0, 1, coord0[0][1],
						coord0[1][1], distanceOfFontToLine);

				// 畫點, 參考用
				// fpaint.setStrokeWidth(3);
				// fpaint.setColor(Color.YELLOW);
				// canvas.drawPoint(fontcoord[0] + cx, fontcoord[1] + cy,
				// fpaint);

				// 刻字
		
				String text = Integer.toString(x);
				// PointF p = getTextCenterInRect(text, textRect, fpaint);
				PointF p = getStringCoordinator(text, textSize, fontcoord[0]
						+ cx, fontcoord[1] + cy, fpaint);
				
				fpaint.setColor(Color.BLACK);
				fpaint.setStyle(Paint.Style.FILL);
				canvas.drawText(text, p.x, p.y, fpaint);
				
				fpaint.setColor(Color.WHITE);
				fpaint.setStyle(Paint.Style.STROKE);
				fpaint.setStrokeWidth(3);
				canvas.drawText(text, p.x, p.y, fpaint);
				

				// 畫點, 參考用
				// fpaint.setStrokeWidth(3);
				// fpaint.setColor(Color.YELLOW);
				// canvas.drawPoint(fontcoord[0] + cx, fontcoord[1] + cy,
				// fpaint);

				if (x < maxkRPM) { // 為了省掉最後一個不用畫
					// 中刻度
					int degree2 = degree + 15;
					int c2 = (x < (maxkRPM - 1)) ? Color.WHITE : Color.RED;
					drawRadiation(canvas, degree2, graduatorRadius,
							middleGraduatorLength, c2, middleGraduatorWidth,
							polar2cartesian);
				}
				// =================================================================
			}
			fpaint.setStyle(Paint.Style.FILL);

			// 小刻度
			for (int degree = startDegree; degree < endDegree; degree += 3) {
				if (degree % 30 != 0 && degree % 15 != 0) {

					int c = (degree < (endDegree - degreePerkRPM)) ? Color.WHITE
							: Color.RED;
					drawRadiation(canvas, degree, graduatorRadius,
							smallGraduatorLength, c, smallGraduatorWidth,
							polar2cartesian);
				}

			}
			// 轉速指示
			// ================================================================
			int indicatorLength = graduatorRadius - graduatorLength / 2;
			RadialGradient ig = new RadialGradient(cx, cy, indicatorLength,
					new int[] { Color.BLACK, Color.RED }, new float[] { 0.10f,
							1 }, Shader.TileMode.CLAMP);
			int indicatorWidth = 8;
			float degree = rpm2Degree(rpm);

			Paint ipaint = new Paint();
			ipaint.setColor(Color.RED);
			ipaint.setStrokeWidth(indicatorWidth);
			ipaint.setShader(ig);

			float[][] indicatorCoord = getCoordinator(degree, indicatorLength,
					indicatorLength, polar2cartesian);
			canvas.drawLine(indicatorCoord[0][0] + cx, indicatorCoord[0][1]
					+ cy, indicatorCoord[1][0] + cx, indicatorCoord[1][1] + cy,
					ipaint);
			// ================================================================

			// ================================================================
			// 檔位顯示
			// ================================================================
			int gearFontText = 75;
			// String gear = "N";
			PointF gearCoord = getStringCoordinator(gear, gearFontText, cx, cy,
					fpaint);

			canvas.drawText(gear, gearCoord.x, gearCoord.y, fpaint);
			// ================================================================

			// ================================================================
			// 時速顯示
			// ================================================================
			int speedFontText = 75;
			// int speed=0;
			String speedText = String.valueOf(speed);
			int speedY = (int) (cy - speedFontText * 1.75);
			PointF speedCoord = getStringCoordinator(speedText, speedFontText,
					cx, speedY, fpaint);
			canvas.drawText(speedText, speedCoord.x, speedCoord.y, fpaint);

			int kphFontText = 20;
			String kph = "km/h";
			int kphY = speedY + speedFontText / 2 + kphFontText;
			PointF kphCoord = getStringCoordinator(kph, kphFontText, cx, kphY,
					fpaint);
			canvas.drawText(kph, kphCoord.x, kphCoord.y, fpaint);
			// ================================================================
			// ================================================================
			// 橫線
			// ================================================================
			int kphBottomY = kphY + kphFontText / 2;
			int gearTopY = cy - gearFontText / 2;
			int lineY = (kphBottomY + gearTopY) / 2;
			canvas.drawLine(cx - 100, lineY, cx + 100, lineY, fpaint);

			// ================================================================
			// ================================================================

		}

		private PointF getStringCoordinator(String text, int textSize,
				float centerX, float centerY, Paint paint) {
			paint.setTextSize(textSize);
			int halfTextSize = textSize / 2;
			Rect textRect = new Rect((int) centerX - halfTextSize,
					(int) centerY - halfTextSize, (int) centerX + halfTextSize,
					(int) centerY + halfTextSize);
			PointF p = getTextCenterInRect(text, textRect, paint);
			return p;
		}

		private float rpm2Degree(float rpm) {
			return (150 + rpm / 7000 * 210);

		}

		int darkGray = Color.rgb(32, 32, 32);

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

		private float[][] getCoordinator(float degree, int radius, int length,
				Polar2cartesianIF polar2cartesian) {
			float[] polarValues = new float[2];
			polarValues[1] = degree;
			polarValues[0] = radius;
			float[] coord0 = polar2cartesian
					.getCartesianCoordinatesValues(polarValues);

			polarValues[0] = radius - length;
			float[] coord1 = polar2cartesian
					.getCartesianCoordinatesValues(polarValues);

			float[][] coordinators = new float[][] { coord0, coord1 };
			return coordinators;
		}

		/**
		 * 畫出放射線的函式
		 * 
		 * @param canvas
		 * @param degree
		 *            角度
		 * @param radius
		 *            外緣的半徑
		 * @param length
		 *            從外圈往圓心畫的長度
		 * @param color
		 *            顏色
		 * @param width
		 *            寬度
		 * @param polar2cartesian
		 *            使用的座標轉換工具
		 * @return
		 */
		private float[][] drawRadiation(Canvas canvas, int degree, int radius,
				int length, int color, int width,
				Polar2cartesianIF polar2cartesian) {
			float[][] coordinators = getCoordinator(degree, radius, length,
					polar2cartesian);
			float[] coord0 = coordinators[0];
			float[] coord1 = coordinators[1];

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

			// float[][] coordinators = new float[][] { coord0, coord1 };
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
	 * 極座標=>笛卡兒座標
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