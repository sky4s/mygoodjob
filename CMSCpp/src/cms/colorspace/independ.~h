#ifndef INDEPENDH
#define INDEPENDH
#include "colorspace.h"
#include <cms/core.h>
//#include "ciexyz.h"
#include <boost/shared_ptr.hpp>

namespace cms {
    namespace colorspace {

	enum Degree {
	    Two = 2, Ten = 10
	};
	enum CIEStandard {
	    //CIE提供的值
	    ActualStandard,
	    //修正CIE的值(會較準確)
	    IntentStandard
	};

	class DeviceIndependentSpace:public ColorSpace {
	  protected:
	    Degree degree;
	    CIEXYZ white;
	    //CIEXYZ originalWhite;
	    //bool adaptedToD65;

	    int getNumberBands() {
		return 3;
	    };
	    static double epsilon;
	    static double kappa;

	     DeviceIndependentSpace() {
	    };

	     DeviceIndependentSpace(shared_array < double >values) {
		setValues(values);
	    };


	    DeviceIndependentSpace(double value1, double value2,
				   double value3) {
		double values[3] = { value1, value2, value3 };
		setValues(shared_array < double >(values));
	    };




	  public:
	    Degree getDegree() {
		return degree;
	    };


	    void setDegree(Degree degree) {
		this->degree = degree;
	    }

	    static const double ACTUAL_EPSILON;
	    static const double ACTUAL_KAPPA;

	    static const double INTENT_EPSILON;
	    static const double INTENT_KAPPA;
	    //virtual CIEXYZ toXYZ() = 0;

	};


	enum NormalizeY {
	    Normal100 = 100, Normal1 = 1, Not = -1
	};

	class NormalizeYOperator {
	  public:
	    virtual void normalize(NormalizeY normalizeY) = 0;

	    virtual void normalizeY() = 0;

	    virtual void normalizeY100() = 0;

	    virtual void setNormalizeNot() = 0;
	    const static double NormalFactor;
	};

	class CIEXYZ:public DeviceIndependentSpace, NormalizeYOperator {
	  protected:
	    //friend class CIExyY;
	    NormalizeY _normalizeY;


	    shared_array < double >_getValues(shared_array <
					      double >values) {
		values[0] = X;
		values[1] = Y;
		values[2] = Z;
		return values;
	    };
	    void _setValues(shared_array < double >values) {
		X = values[0];
		Y = values[1];
		Z = values[2];
	    };
	  public:
	    double X, Y, Z;
	    CIEXYZ() {
	    };

	    CIEXYZ(shared_array < double >XYZValues, NormalizeY
		   normalizeY):DeviceIndependentSpace(XYZValues) {
	    };
	    CIEXYZ(shared_array <
		   double >XYZValues):DeviceIndependentSpace(XYZValues) {

	    };

	    CIEXYZ(double X, double Y,
		   double Z):DeviceIndependentSpace(X, Y, Z) {

	    };
	    CIEXYZ(double X, double Y, double Z,
		   NormalizeY normalizeY):DeviceIndependentSpace(X, Y, Z) {


	    };
	    vector < string > getBandNames() {
		vector < string > result(3);
		result[0] = "X";
		result[1] = "Y";
		result[2] = "Z";
		return result;
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

	    virtual shared_array < double >getValues(shared_array <
						     double >values,
						     NormalizeY normalizeY)
	    {
		if (_normalizeY == Not) {
		    throw
			IllegalStateException
			("this.normalizeY == NormalizeY.Not");
		}
		ColorSpace::getValues(values);
		if (_normalizeY == normalizeY) {
		    return values;
		}
		switch (_normalizeY) {
		case Normal100:
		    DoubleArray.copy(DoubleArray.times(values, 1. / 100),
				     values);
		    break;
		case Normal1:
		    DoubleArray.copy(DoubleArray.times(values, 100),
				     values);
		    break;
		}
		return values;
	    };

	    shared_array < double >getWhitenessIndex() {
		//return new CIExyY(this).getWhitenessIndex();
	    };

	    shared_array < double >getxyValues() {
		/*if (Y == 0) {
		   return new double[] {
		   0, 0};
		   } else {
		   double sum = (X + Y + Z);
		   double x = X / sum;
		   double y = Y / sum;
		   return new double[] {
		   x, y};
		   } */
	    };

	    shared_array < double >getxyzValues() {
		/*double sum = (X + Y + Z);
		   double x = X / sum;
		   double y = Y / sum;
		   double z = 1 - x - y;
		   return new double[] {
		   x, y, z}; */
	    }

  /**
   * Yellowness Index per ASTM MEthod E313.
   * Yellowness Index may only  be calculated  for D65 at two degree view angle.
   * @return double
   */
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

	    bool isLegal(CIEXYZ & white) {
		return isLegal() && X <= white.X && Y <= white.Y &&
		    Z <= white.Z;
	    };

	    static shared_ptr < CIEXYZ > minus(CIEXYZ & XYZ1,
					       CIEXYZ & XYZ2) {
		//CIEXYZ result = new CIEXYZ();
		shared_ptr < CIEXYZ > result =
		    shared_ptr < CIEXYZ > (new CIEXYZ());

		result->X = XYZ1.X - XYZ2.X;
		result->Y = XYZ1.Y - XYZ2.Y;
		result->Z = XYZ1.Z - XYZ2.Z;
		return result;
	    };

	    void normalize(CIEXYZ & normal) {
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



	    static shared_ptr < CIEXYZ > plus(CIEXYZ & XYZ1, CIEXYZ & XYZ2) {
		//CIEXYZ result = new CIEXYZ();
		shared_ptr < CIEXYZ > result =
		    shared_ptr < CIEXYZ > (new CIEXYZ());
		result->X = XYZ1.X + XYZ2.X;
		result->Y = XYZ1.Y + XYZ2.Y;
		result->Z = XYZ1.Z + XYZ2.Z;
		return result;
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

	    void normalize(NormalizeY normalizeY) {
	    };



	    void normalizeY100() {
	    };

	    void setNormalizeNot() {
	    };
	};
    };
};
#endif

