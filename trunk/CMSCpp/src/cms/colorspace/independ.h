#ifndef INDEPENDH
#define INDEPENDH
#include "colorspace.h"
#include <cms/core.h>
//#include "ciexyz.h"
#include <java/lang.h>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>

namespace cms {
    namespace colorspace {

	enum CIEStandard {
	    //CIE提供的值
	    ActualStandard,
	    //修正CIE的值(會較準確)
	    IntentStandard
	};
	enum Degree {
	    Two = 2, Ten = 10
	};

	enum NormalizeY {
	    Normal100 = 100, Normal1 = 1, Not = -1
	};

	class CIEXYZ;
	class DeviceIndependentSpace:public ColorSpace {


	  protected:
	    Degree _degree;
	    static double epsilon;
	    static double kappa;

	     DeviceIndependentSpace():_degree(Two) {

	    };
	    /*DeviceIndependentSpace(shared_array < double >values) {
	       setValues(values);
	       };
	       DeviceIndependentSpace(double value1, double value2,
	       double value3) {
	       setValues(value1, value2, value3);
	       }; */

	    int getNumberBands() {
		return 3;
	  } public:
	     Degree getDegree() {
		return _degree;
	    };
	    void setDegree(Degree degree) {
		_degree = degree;
	    };
	    static void setCIEStandard(CIEStandard standard) {
		if (standard == ActualStandard) {
		    epsilon = ACTUAL_EPSILON;
		    kappa = ACTUAL_KAPPA;
		} else {
		    epsilon = INTENT_EPSILON;
		    kappa = INTENT_KAPPA;
		}
	    }
	    static const double ACTUAL_EPSILON;
	    static const double ACTUAL_KAPPA;

	    static const double INTENT_EPSILON;
	    static const double INTENT_KAPPA;
	    virtual CIEXYZ toXYZ() = 0;
	};




	class NormalizeYOperator {
	  protected:
	    NormalizeY _normalizeY;
	  public:
	    virtual void normalize(NormalizeY normalizeY) = 0;

	    virtual void normalizeY() = 0;

	    void normalizeY100() {
		normalizeY();
		normalize(Normal100);
	    };
	    void setNormalizeNot() {
		_normalizeY = Not;
	    };

	    const static double NormalFactor;
	};

	class CIEXYZ:public DeviceIndependentSpace, NormalizeYOperator {
	  protected:
	    friend class CIExyY;
	    NormalizeY _normalizeY;

	  public:
	    double X, Y, Z;
	    shared_vector_string getBandNames() {
		shared_vector_string names(new vector < string > (3));
		 (*names)[0] = "X";
		 (*names)[1] = "Y";
		 (*names)[2] = "Z";
		 return names;
	    };

	    double getCCT() {
		//return CorrelatedColorTemperature.XYZ2CCTByRobertson(this);
	    };

	    NormalizeY getNormalizeY() {
		return _normalizeY;
	    };
	    double getSaturation(CIEXYZ white) {
		/*double[] uv = this.getuvPrimeValues();
		   double[] uvn = white.getuvPrimeValues();
		   return 13 * Math.sqrt(Maths.sqr(uv[0] - uvn[0]) +
		   Maths.sqr(uv[1] - uvn[1])); */
	    };
	    shared_array < double >getuvPrimeValues() {
		/*CIExyY xyY = CIExyY.fromXYZ(this);
		   return xyY.getuvPrimeValues(); */
	    };
	    shared_array < double >getuvValues() {
		/*CIExyY xyY = CIExyY.fromXYZ(this);
		   return xyY.getuvValues(); */
	    };
	    shared_array < double >getValues(shared_array < double >values,
					     NormalizeY normalizeY) {
		if (_normalizeY == Not) {
		    throw
			IllegalStateException
			("this.normalizeY == NormalizeY.Not");
		}
		getValues(values);
		if (_normalizeY == normalizeY) {
		    return values;
		}
		switch (_normalizeY) {
		case Normal100:
		    //DoubleArray.copy(DoubleArray.times(values, 1. / 100),
		    //values);
		    break;
		case Normal1:
		    //DoubleArray.copy(DoubleArray.times(values, 100),
		    //values);
		    break;
		}
		return values;
	    };

	    shared_array < double >_getValues(shared_array <
					      double >values) {
		//shared_array < double >values(new double[3]);
		values[0] = X;
		values[1] = Y;
		values[2] = Z;
		return values;
	    };
	    virtual void _setValues(shared_array < double >values) {
		X = values[0];
		Y = values[1];
		Z = values[2];
	    };


	    //using ColorSpace::getValues;
	    shared_array < double >getValues() {
		return ColorSpace::getValues();
	    };
	    shared_array < double >getValues(shared_array < double >values) {
		return ColorSpace::getValues(values);
	    };


	    CIEXYZ toXYZ() {
		return *this;
	    };

	    shared_array < double >getWhitenessIndex() {
		//return new CIExyY(this).getWhitenessIndex();
	    };

	    shared_array < double >getxyValues() const {
		if (Y == 0) {
		    //return new double[] {
		    //0, 0};
		    //double *result  = new double[2];
		    shared_array < double >values(new double[2]);
		     values[0] = 0;
		     values[1] = 0;
		     return values;
		} else {
		    double sum = (X + Y + Z);
		    double x = X / sum;
		    double y = Y / sum;
		    shared_array < double >values(new double[2]);
		    values[0] = x;
		    values[1] = y;
		    return values;
		}
	    };

	    shared_array < double >getxyzValues() {
		double sum = (X + Y + Z);
		double x = X / sum;
		double y = Y / sum;
		double z = 1 - x - y;
		shared_array < double >values(new double[3]);
		values[0] = x;
		values[1] = y;
		values[2] = z;
		return values;
	    };

	    double getYellownessIndex() {
		return 100 * (1.2985 * X - 1.1335 * Z) / Y;
	    };

	    boolean isBlack() {
		return X == 0 && Y == 0 && Z == 0;
	    };

	    boolean isLegal() {
		if (Y == 0 && (X > 0 || Z > 0)) {
		    //如果Y=0,就應該為黑色,其他頻道不應該有值
		    return false;
		} else if (Y != 0 && X == 0) {
		    //如果Y有值(具有亮度),X頻道就也應該有值,Z則不一定
		    return false;
		} else if (X < 0 || Y < 0 || Z < 0) {
		    return false;
		}

		return true;
	    };
	    boolean isLegal(CIEXYZ white) {
		return isLegal() && X <= white.X && Y <= white.Y &&
		    Z <= white.Z;
	    };
	    static shared_ptr < CIEXYZ > minus(const CIEXYZ & XYZ1,
					       const CIEXYZ & XYZ2) {

		shared_ptr < CIEXYZ > result(new CIEXYZ());
		result->X = XYZ1.X - XYZ2.X;
		result->Y = XYZ1.Y - XYZ2.Y;
		result->Z = XYZ1.Z - XYZ2.Z;
		return result;
	    };

	    static shared_ptr < CIEXYZ > plus(const CIEXYZ & XYZ1,
					      const CIEXYZ & XYZ2) {
		shared_ptr < CIEXYZ > result(new CIEXYZ());
		result->X = XYZ1.X + XYZ2.X;
		result->Y = XYZ1.Y + XYZ2.Y;
		result->Z = XYZ1.Z + XYZ2.Z;
		return result;
	    };

	    void normalize(CIEXYZ normal) {
		double factor = (NormalFactor / normal.Y);
		X *= factor;
		Y *= factor;
		Z *= factor;
		_normalizeY = Normal1;
	    };

	    void normalizeY() {
		double factor = NormalFactor / Y;
		X *= factor;
		Z *= factor;
		Y = NormalFactor;
		_normalizeY = Normal1;
	    };

	    void normalize(NormalizeY normalizeY) {
		shared_array < double >values =
		    getValues(shared_array < double >(new double[3]),
			      normalizeY);
		setValues(values);
		_normalizeY = normalizeY;
	    };

	    void rationalize() {
		/*X = Double.isNaN(X) ? 0 : X;
		   Y = Double.isNaN(Y) ? 0 : Y;
		   Z = Double.isNaN(Z) ? 0 : Z; */

		X = (X < 0) ? 0 : X;
		Y = (Y < 0) ? 0 : Y;
		Z = (Z < 0) ? 0 : Z;

		if (Y == 0. && (X > 0. || Z > 0.)) {
		    X = 0;
		    Z = 0;
		}
		if (Y != 0. && X == 0.) {
		    X = 0;
		    Y = 0;
		    Z = 0;
		}
	    };
	    void rationalize(CIEXYZ white) {
		rationalize();

		X = (X > white.X) ? white.X : X;
		Y = (Y > white.Y) ? white.Y : Y;
		Z = (Z > white.Z) ? white.Z : Z;
	    };

	    void scaleY(CIEXYZ scale) {
		scaleY(scale.Y);
	    };
	    void scaleY(double scaleY) {
		double factor = scaleY / Y;
		times(factor);
	    };
	    void times(double factor) {
		X *= factor;
		Y *= factor;
		Z *= factor;
	    };

	    CIEXYZ() {
	    };
	    CIEXYZ(shared_array < double >XYZValues,
		   NormalizeY normalizeY):_normalizeY(normalizeY) {
		setValues(XYZValues);
	    };
	    CIEXYZ(shared_array < double >XYZValues) {
		setValues(XYZValues);
	    };
	    CIEXYZ(double X, double Y, double Z,
		   NormalizeY normalizeY):_normalizeY(normalizeY) {
		setValues(X, Y, Z);
	    };
	    CIEXYZ(double X, double Y, double Z) {
		setValues(X, Y, Z);
	    };
	};

	class CIExyY:public DeviceIndependentSpace, NormalizeYOperator {
	  protected:
	    NormalizeY _normalizeY;
	    static CIExyY D65xyY;
	  public:
	    double x, y, Y;
	     CIExyY() {
	    };

	  CIExyY(CIEXYZ & XYZ):_normalizeY(XYZ._normalizeY) {
		shared_array < double >xyValues = XYZ.getxyValues();
		setValues(xyValues[0], xyValues[1], XYZ.Y);
	    };
	    CIExyY(shared_array < double >xyValues,
		   NormalizeY normalizeY):_normalizeY(normalizeY) {
		setValues(xyValues);
	    };
	    CIExyY(shared_array < double >xyValues) {
		setValues(xyValues);
	    };
	    CIExyY(double x, double y, double Y,
		   NormalizeY normalizeY):_normalizeY(normalizeY) {
		setValues(x, y, Y);
	    };
	    CIExyY(double x, double y, double Y) {
		setValues(x, y, Y);
	    };
	    CIExyY(double x, double y) {
		setValues(x, y, y);
	    };

	    static shared_ptr < CIExyY > fromCCT2Blackbody(int CCT) {
		//return CorrelatedColorTemperature.CCT2BlackbodyxyY(CCT);
	    };
	    static shared_ptr < CIExyY > fromCCT2DIlluminant(int CCT) {
		//return CorrelatedColorTemperature.CCT2DIlluminantxyY(CCT);
	    };
	    static shared_ptr < CIExyY > fromXYZ(const CIEXYZ & XYZ) {
		shared_array < double >xyValues = XYZ.getxyValues();
		//CIExyY xyY = new CIExyY(xyValues[0], xyValues[1], XYZ.Y,
		//                    XYZ.normalizeY);
		shared_ptr < CIExyY >
		    xyY(new CIExyY(xyValues[0], xyValues[1], XYZ.Y,
				   XYZ._normalizeY));
		return xyY;
	    }

	    CIEXYZ toXYZ() {
		//return toXYZ(this);
	    };

	    static shared_ptr < CIEXYZ > toXYZ(const CIExyY & xyY) {
		shared_ptr < CIEXYZ > XYZ(new CIEXYZ());

		XYZ->X = (xyY.x / xyY.y) * xyY.Y;
		XYZ->Y = xyY.Y;
		XYZ->Z = ((1 - xyY.x - xyY.y) / xyY.y) * xyY.Y;
		XYZ->_normalizeY = xyY._normalizeY;
		XYZ->_degree = xyY._degree;
		return XYZ;
	    };

	    shared_array < double >_getValues(shared_array <
					      double >values) {
		values[0] = x;
		values[1] = y;
		values[2] = Y;
		return values;
	    };
	    void _setValues(shared_array < double >values) {
		x = values[0];
		y = values[1];
		Y = values[2];
	    };
	    shared_vector_string getBandNames() {
		shared_vector_string names(new vector < string > (3));
		(*names)[0] = "x";
		(*names)[1] = "y";
		(*names)[2] = "Y";
		return names;
	    };
	    void normalize(NormalizeY normalizeY) {
		Y = normalizeY;
		_normalizeY = normalizeY;
	    };
	    void normalizeY() {
		Y = NormalFactor;
		_normalizeY = Normal1;
	    };

	    shared_array < double >getValues(shared_array < double >values,
					     NormalizeY normalizeY) {
		if (_normalizeY == Not) {
		    throw
			IllegalStateException
			("this.normalizeY == NormalizeY.Not");
		}
		getValues(values);
		if (_normalizeY == normalizeY) {
		    return values;
		}
		switch (_normalizeY) {
		case Normal100:
		    //DoubleArray.copy(DoubleArray.times(values, 1. / 100),
		    //values);
		    break;
		case Normal1:
		    //DoubleArray.copy(DoubleArray.times(values, 100),
		    //values);
		    break;
		}
		return values;
	    };
	    //using ColorSpace::getValues;
	    shared_array < double >getValues() {
		return ColorSpace::getValues();
	    };
	    shared_array < double >getValues(shared_array < double >values) {
		return ColorSpace::getValues(values);
	    };
	    double getCCT() {
		return toXYZ().getCCT();
	    };

	    shared_array < double >getDeltauv(CIExyY & xyY) {
		shared_array < double >uvp1 = getuvValues();
		shared_array < double >uvp2 = xyY.getuvValues();
		//double[] duvp = DoubleArray.minus(uvp1, uvp2);
		//return duvp;
	    };

	    shared_array < double >getDeltauvPrime(CIExyY & xyY) {
		shared_array < double >uvp1 = getuvPrimeValues();
		shared_array < double >uvp2 = xyY.getuvPrimeValues();
		//double[] duvp = DoubleArray.minus(uvp1, uvp2);
		//return duvp;
	    };
	    shared_array < double >getDeltaxy(CIExyY & xyY) {
		shared_array < double >deltaxy(new double[2]);
		deltaxy[0] = x - xyY.x;
		deltaxy[1] = y - xyY.y;
		return deltaxy;
	    };

	    shared_array < double >getuvPrimeValues() {
		double denominator = (-2 * x + 12 * y + 3);
		shared_array < double >uvp(new double[2]);
		uvp[0] = 4 * x / denominator;
		uvp[1] = 9 * y / denominator;
		return uvp;
	    };

	    shared_array < double >getuvPrimeYValues() {
		shared_array < double >uvp = getuvPrimeValues();
		shared_array < double >uvpY(new double[3]);
		uvpY[0] = uvp[0];
		uvpY[1] = uvp[1];
		uvpY[2] = Y;
		return uvpY;
	    };
	    shared_array < double >getuvValues() {
		double denominator = (-2 * x + 12 * y + 3);
		shared_array < double >uv(new double[2]);
		uv[0] = 4 * x / denominator;
		uv[1] = 6 * y / denominator;
		return uv;
	    };

	    shared_array < double >getWhitenessIndex() {
		shared_array < double >dxy = D65xyY.getDeltaxy(*this);
		double W = Y + 800 * dxy[0] + 1700 * dxy[1];
		double Tw = 1000 * dxy[0] - 650 * dxy[1];

		shared_array < double >index(new double[2]);
		index[0] = W;
		index[1] = Tw;
		return index;
	    };
	    shared_array < double >getxyValues() {
		shared_array < double >xy(new double[2]);
		xy[0] = x;
		xy[1] = y;
		return xy;
	    };
	    boolean isLegal() {
		return Y >= 0 && (x + y) <= 1;
	    };

	    void rationalize() {
		/*x = Double.isNaN(x) ? 0 : x;
		   y = Double.isNaN(y) ? 0 : y; */
	    };
	    void setuvPrimeValues(shared_array < double >uvPrimeValues) {
		double u = uvPrimeValues[0];
		double v = uvPrimeValues[1];
		double denominator = 9 * u / 2 - 12 * v + 9;

		x = (27 * u / 4) / denominator;
		y = 3 * v / denominator;
	    };
	    void setuvPrimeYValues(shared_array < double >uvPrimeYValues) {
		shared_array < double >uv(new double[2]);
		uv[0] = uvPrimeYValues[0];
		uv[1] = uvPrimeYValues[1];
		setuvPrimeValues(uv);
		Y = uvPrimeYValues[2];
	    }
	};
    };
};
#endif

