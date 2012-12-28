package dashboard.util;

public class Interpolation {

	public static double interpolate(double[] xn, double[] yn, double x) {
		return linear2(xn, yn, x);
	}

	public static double linear2(double[] xn, double[] yn, double x) {
		if (xn.length != 2 || yn.length != 2) {
			throw new IllegalArgumentException();
		}
		return linear(xn[0], xn[1], yn[0], yn[1], x);
	}

	public static double linear(double x1, double x2, double y1, double y2,
			double x) {
		double ratio = (x - x1) / (x2 - x1);
		return y1 + (y2 - y1) * ratio;
	}
}
