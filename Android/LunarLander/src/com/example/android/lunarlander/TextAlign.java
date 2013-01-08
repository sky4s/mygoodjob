package com.example.android.lunarlander;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;

import android.app.Activity;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.graphics.Picture;
import android.graphics.Rect;
import android.graphics.Typeface;
import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.util.AttributeSet;
import android.view.View;
import android.view.ViewGroup;
import android.view.ViewParent;

public class TextAlign extends GraphicsActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(new SampleView(this));
	}

	private static class SampleView extends View {
		private Paint mPaint;
		private float mX;
		private float[] mPos;

		private Path mPath;
		private Paint mPathPaint;

		private static final int DY = 30;
		private static final String TEXT_L = "Left";
		private static final String TEXT_C = "Center";
		private static final String TEXT_R = "Right";
		private static final String POSTEXT = "Positioned";
		private static final String TEXTONPATH = "Along a path";

		private static void makePath(Path p) {
			p.moveTo(10, 0);
			p.cubicTo(100, -50, 200, 50, 300, 0);
		}

		private float[] buildTextPositions(String text, float y, Paint paint) {
			float[] widths = new float[text.length()];
			// initially get the widths for each char
			int n = paint.getTextWidths(text, widths);
			// now popuplate the array, interleaving spaces for the Y values
			float[] pos = new float[n * 2];
			float accumulatedX = 0;
			for (int i = 0; i < n; i++) {
				pos[i * 2 + 0] = accumulatedX;
				pos[i * 2 + 1] = y;
				accumulatedX += widths[i];
			}
			return pos;
		}

		public SampleView(Context context) {
			super(context);
			setFocusable(true);

			mPaint = new Paint();
			mPaint.setAntiAlias(true);
			mPaint.setTextSize(30);
			mPaint.setTypeface(Typeface.SERIF);

			mPos = buildTextPositions(POSTEXT, 0, mPaint);

			mPath = new Path();
			makePath(mPath);

			mPathPaint = new Paint();
			mPathPaint.setAntiAlias(true);
			mPathPaint.setColor(0x800000FF);
			mPathPaint.setStyle(Paint.Style.STROKE);
		}

		@Override
		protected void onDraw(Canvas canvas) {
			canvas.drawColor(Color.WHITE);

			Paint p = mPaint;
			float x = mX;
			float y = 0;
			float[] pos = mPos;

			// draw the normal strings

			p.setColor(0x80FF0000);
			canvas.drawLine(x, y, x, y + DY * 3, p);
			p.setColor(Color.BLACK);
			p.setStrokeWidth(3);

			canvas.translate(0, DY);
			p.setTextAlign(Paint.Align.LEFT);

			canvas.drawText(TEXT_L, x, y, p);
			p.setColor(Color.YELLOW);
			canvas.drawPoint(x, y, p);
			p.setColor(Color.BLACK);

			canvas.translate(0, DY);
			p.setTextAlign(Paint.Align.CENTER);

			canvas.drawText(TEXT_C, x, y, p);
			p.setColor(Color.YELLOW);
			canvas.drawPoint(x, y, p);
			p.setColor(Color.BLACK);

			canvas.translate(0, DY);
			p.setTextAlign(Paint.Align.RIGHT);

			canvas.drawText(TEXT_R, x, y, p);
			p.setColor(Color.YELLOW);
			canvas.drawPoint(x, y, p);
			p.setColor(Color.BLACK);

			canvas.translate(100, DY * 2);

			// now draw the positioned strings

			p.setColor(0xBB00FF00);
			for (int i = 0; i < pos.length / 2; i++) {
				canvas.drawLine(pos[i * 2 + 0], pos[i * 2 + 1] - DY,
						pos[i * 2 + 0], pos[i * 2 + 1] + DY * 2, p);
			}
			p.setColor(Color.BLACK);
			
			p.setTextAlign(Paint.Align.LEFT);
			canvas.drawPosText(POSTEXT, pos, p);

			canvas.translate(0, DY);
			p.setTextAlign(Paint.Align.CENTER);
			canvas.drawPosText(POSTEXT, pos, p);

			canvas.translate(0, DY);
			p.setTextAlign(Paint.Align.RIGHT);
			canvas.drawPosText(POSTEXT, pos, p);

			// now draw the text on path

			canvas.translate(-100, DY * 2);

			canvas.drawPath(mPath, mPathPaint);
			p.setTextAlign(Paint.Align.LEFT);
			canvas.drawTextOnPath(TEXTONPATH, mPath, 0, 0, p);

			canvas.translate(0, DY * 1.5f);
			canvas.drawPath(mPath, mPathPaint);
			p.setTextAlign(Paint.Align.CENTER);
			canvas.drawTextOnPath(TEXTONPATH, mPath, 0, 0, p);

			canvas.translate(0, DY * 1.5f);
			canvas.drawPath(mPath, mPathPaint);
			p.setTextAlign(Paint.Align.RIGHT);
			canvas.drawTextOnPath(TEXTONPATH, mPath, 0, 0, p);
		}

		@Override
		protected void onSizeChanged(int w, int h, int ow, int oh) {
			super.onSizeChanged(w, h, ow, oh);
			mX = w * 0.5f; // remember the center of the screen
		}
	}
}

class GraphicsActivity extends Activity {
	// set to true to test Picture
	private static final boolean TEST_PICTURE = false;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	}

	@Override
	public void setContentView(View view) {
		if (TEST_PICTURE) {
			ViewGroup vg = new PictureLayout(this);
			vg.addView(view);
			view = vg;
		}

		super.setContentView(view);
	}
}

class PictureLayout extends ViewGroup {
	private final Picture mPicture = new Picture();

	public PictureLayout(Context context) {
		super(context);
	}

	public PictureLayout(Context context, AttributeSet attrs) {
		super(context, attrs);
	}

	@Override
	public void addView(View child) {
		if (getChildCount() > 1) {
			throw new IllegalStateException(
					"PictureLayout can host only one direct child");
		}

		super.addView(child);
	}

	@Override
	public void addView(View child, int index) {
		if (getChildCount() > 1) {
			throw new IllegalStateException(
					"PictureLayout can host only one direct child");
		}

		super.addView(child, index);
	}

	@Override
	public void addView(View child, LayoutParams params) {
		if (getChildCount() > 1) {
			throw new IllegalStateException(
					"PictureLayout can host only one direct child");
		}

		super.addView(child, params);
	}

	@Override
	public void addView(View child, int index, LayoutParams params) {
		if (getChildCount() > 1) {
			throw new IllegalStateException(
					"PictureLayout can host only one direct child");
		}

		super.addView(child, index, params);
	}

	@Override
	protected LayoutParams generateDefaultLayoutParams() {
		return new LayoutParams(LayoutParams.MATCH_PARENT,
				LayoutParams.MATCH_PARENT);
	}

	@Override
	protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
		final int count = getChildCount();

		int maxHeight = 0;
		int maxWidth = 0;

		for (int i = 0; i < count; i++) {
			final View child = getChildAt(i);
			if (child.getVisibility() != GONE) {
				measureChild(child, widthMeasureSpec, heightMeasureSpec);
			}
		}

		maxWidth += getPaddingLeft() + getPaddingRight();
		maxHeight += getPaddingTop() + getPaddingBottom();

		Drawable drawable = getBackground();
		if (drawable != null) {
			maxHeight = Math.max(maxHeight, drawable.getMinimumHeight());
			maxWidth = Math.max(maxWidth, drawable.getMinimumWidth());
		}

		setMeasuredDimension(resolveSize(maxWidth, widthMeasureSpec),
				resolveSize(maxHeight, heightMeasureSpec));
	}

	private void drawPict(Canvas canvas, int x, int y, int w, int h, float sx,
			float sy) {
		canvas.save();
		canvas.translate(x, y);
		canvas.clipRect(0, 0, w, h);
		canvas.scale(0.5f, 0.5f);
		canvas.scale(sx, sy, w, h);
		canvas.drawPicture(mPicture);
		canvas.restore();
	}

	@Override
	protected void dispatchDraw(Canvas canvas) {
		super.dispatchDraw(mPicture.beginRecording(getWidth(), getHeight()));
		mPicture.endRecording();

		int x = getWidth() / 2;
		int y = getHeight() / 2;

		if (false) {
			canvas.drawPicture(mPicture);
		} else {
			drawPict(canvas, 0, 0, x, y, 1, 1);
			drawPict(canvas, x, 0, x, y, -1, 1);
			drawPict(canvas, 0, y, x, y, 1, -1);
			drawPict(canvas, x, y, x, y, -1, -1);
		}
	}

	@Override
	public ViewParent invalidateChildInParent(int[] location, Rect dirty) {
		location[0] = getLeft();
		location[1] = getTop();
		dirty.set(0, 0, getWidth(), getHeight());
		return getParent();
	}

	@Override
	protected void onLayout(boolean changed, int l, int t, int r, int b) {
		final int count = super.getChildCount();

		for (int i = 0; i < count; i++) {
			final View child = getChildAt(i);
			if (child.getVisibility() != GONE) {
				final int childLeft = getPaddingLeft();
				final int childTop = getPaddingTop();
				child.layout(childLeft, childTop,
						childLeft + child.getMeasuredWidth(),
						childTop + child.getMeasuredHeight());

			}
		}
	}
}
