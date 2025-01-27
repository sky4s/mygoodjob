#include "ciexyz.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <math/doublearray.h>

namespace cms {
    namespace colorspace {
	namespace independ {
	    using namespace std;
	    using namespace boost;
	    using namespace java::lang;
	    using namespace math;
	    //======================================================================
	    // CIEXYZ
	    //======================================================================
	    string_vector_ptr CIEXYZ::getBandNames() {
		string_vector_ptr names(new string_vector(3));
		 (*names)[0] = "X";
		 (*names)[1] = "Y";
		 (*names)[2] = "Z";
		 return names;
	    };

	    double CIEXYZ::getCCT() {
		//return CorrelatedColorTemperature.XYZ2CCTByRobertson(this);
	    };

	    NormalizeY CIEXYZ::getNormalizeY() {
		return _normalizeY;
	    };
	    double CIEXYZ::getSaturation(CIEXYZ white) {
		/*double[] uv = this.getuvPrimeValues();
		   double[] uvn = white.getuvPrimeValues();
		   return 13 * Math.sqrt(Maths.sqr(uv[0] - uvn[0]) +
		   Maths.sqr(uv[1] - uvn[1])); */
	    };
	    double_array CIEXYZ::getuvPrimeValues() {
		/*CIExyY xyY = CIExyY.fromXYZ(this);
		   return xyY.getuvPrimeValues(); */
	    };
	    double_array CIEXYZ::getuvValues() {
		/*CIExyY xyY = CIExyY.fromXYZ(this);
		   return xyY.getuvValues(); */
	    };
	    double_array CIEXYZ::getValues(double_array values,
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

	    double_array CIEXYZ::_getValues(double_array values) {
		// double_array values(new double[3]);
		values[0] = X;
		values[1] = Y;
		values[2] = Z;
		return values;
	    };
	    void CIEXYZ::_setValues(double_array values) {
		X = values[0];
		Y = values[1];
		Z = values[2];
	    };


	    //using ColorSpace::getValues;
	    double_array CIEXYZ::getValues() {
		return ColorSpace::getValues();
	    };
	    double_array CIEXYZ::getValues(double_array values) {
		return ColorSpace::getValues(values);
	    };

	    shared_ptr < CIEXYZ > CIEXYZ::toXYZ() {
		//return *this;
	    };

	    double_array CIEXYZ::getWhitenessIndex() {
		//return new CIExyY(this).getWhitenessIndex();
	    };

	    double_array CIEXYZ::getxyValues() const {
		if (Y == 0) {
		    //return new double[] {
		    //0, 0};
		    //double *result  = new double[2];
		    double_array values(new double[2]);
		     values[0] = 0;
		     values[1] = 0;
		     return values;
		} else {
		    double sum = (X + Y + Z);
		    double x = X / sum;
		    double y = Y / sum;
		    double_array values(new double[2]);
		    values[0] = x;
		    values[1] = y;
		    return values;
		}
	    };

	    double_array CIEXYZ::getxyzValues() {
		double sum = (X + Y + Z);
		double x = X / sum;
		double y = Y / sum;
		double z = 1 - x - y;
		double_array values(new double[3]);
		values[0] = x;
		values[1] = y;
		values[2] = z;
		return values;
	    };

	    double CIEXYZ::getYellownessIndex() {
		return 100 * (1.2985 * X - 1.1335 * Z) / Y;
	    };

	    bool CIEXYZ::isBlack() {
		return X == 0 && Y == 0 && Z == 0;
	    };

	    bool CIEXYZ::isLegal() {
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
	    bool CIEXYZ::isLegal(XYZ_ptr white) {
		return isLegal() && X <= white->X && Y <= white->Y &&
		    Z <= white->Z;
	    };
	    XYZ_ptr CIEXYZ::minus(const XYZ_ptr XYZ1, const XYZ_ptr XYZ2) {

		XYZ_ptr result(new CIEXYZ());
		result->X = XYZ1->X - XYZ2->X;
		result->Y = XYZ1->Y - XYZ2->Y;
		result->Z = XYZ1->Z - XYZ2->Z;
		return result;
	    };

	    XYZ_ptr CIEXYZ::plus(const XYZ_ptr XYZ1, const XYZ_ptr XYZ2) {
		XYZ_ptr result(new CIEXYZ());
		result->X = XYZ1->X + XYZ2->X;
		result->Y = XYZ1->Y + XYZ2->Y;
		result->Z = XYZ1->Z + XYZ2->Z;
		return result;
	    };

	    void CIEXYZ::normalize(XYZ_ptr normal) {
		double factor = (NormalFactor / normal->Y);
		X *= factor;
		Y *= factor;
		Z *= factor;
		_normalizeY = Normal1;
	    };

	    void CIEXYZ::normalizeY() {
		double factor = NormalFactor / Y;
		X *= factor;
		Z *= factor;
		Y = NormalFactor;
		_normalizeY = Normal1;
	    };

	    void CIEXYZ::normalize(NormalizeY normalizeY) {
		double_array values =
		    getValues(double_array(new double[3]),
			      normalizeY);
		setValues(values);
		_normalizeY = normalizeY;
	    };

	    void CIEXYZ::rationalize() {
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
	    void CIEXYZ::rationalize(XYZ_ptr white) {
		rationalize();

		X = (X > white->X) ? white->X : X;
		Y = (Y > white->Y) ? white->Y : Y;
		Z = (Z > white->Z) ? white->Z : Z;
	    };

	    void CIEXYZ::scaleY(XYZ_ptr scale) {
		scaleY(scale->Y);
	    };
	    void CIEXYZ::scaleY(double scaleY) {
		double factor = scaleY / Y;
		times(factor);
	    };
	    void CIEXYZ::times(double factor) {
		X *= factor;
		Y *= factor;
		Z *= factor;
	    };

	    CIEXYZ::CIEXYZ() {
	    };
	  CIEXYZ::CIEXYZ(double_array XYZValues, NormalizeY normalizeY):_normalizeY(normalizeY)
	    {
		setValues(XYZValues);
	    };
	    CIEXYZ::CIEXYZ(double_array XYZValues) {
		setValues(XYZValues);
	    };
	    CIEXYZ::CIEXYZ(double X, double Y, double Z,
			   NormalizeY normalizeY):_normalizeY(normalizeY) {
		setValues(X, Y, Z);
	    };
	    CIEXYZ::CIEXYZ(double X, double Y, double Z) {
		setValues(X, Y, Z);
	    };

	    //======================================================================


	    //======================================================================
	    // CIExyY
	    //======================================================================
	    CIExyY::CIExyY() {
	    };

	  CIExyY::CIExyY(XYZ_ptr XYZ):_normalizeY(XYZ->_normalizeY)
	    {
		double_array xyValues = XYZ->getxyValues();
		setValues(xyValues[0], xyValues[1], XYZ->Y);
	    };
	  CIExyY::CIExyY(double_array xyValues, NormalizeY normalizeY):_normalizeY(normalizeY)
	    {
		setValues(xyValues);
	    };
	    CIExyY::CIExyY(double_array xyValues) {
		setValues(xyValues);
	    };
	    CIExyY::CIExyY(double x, double y, double Y,
			   NormalizeY normalizeY):_normalizeY(normalizeY) {
		setValues(x, y, Y);
	    };
	    CIExyY::CIExyY(double x, double y, double Y) {
		setValues(x, y, Y);
	    };
	    CIExyY::CIExyY(double x, double y) {
		setValues(x, y, 1);
	    };

	    xyY_ptr CIExyY::fromCCT2Blackbody(int CCT) {
		//return CorrelatedColorTemperature.CCT2BlackbodyxyY(CCT);
	    };
	    xyY_ptr CIExyY::fromCCT2DIlluminant(int CCT) {
		//return CorrelatedColorTemperature.CCT2DIlluminantxyY(CCT);
	    };
	    xyY_ptr CIExyY::fromXYZ(const XYZ_ptr XYZ) {
		double_array xyValues = XYZ->getxyValues();
		xyY_ptr
		    xyY(new CIExyY(xyValues[0], xyValues[1], XYZ->Y,
				   XYZ->_normalizeY));
		return xyY;
	    }

	    XYZ_ptr CIExyY::toXYZ() {
		return toXYZ(*this);
	    };

	    XYZ_ptr CIExyY::toXYZ(const CIExyY & xyY) {
		shared_ptr < CIEXYZ > XYZ(new CIEXYZ());

		XYZ->X = (xyY.x / xyY.y) * xyY.Y;
		XYZ->Y = xyY.Y;
		XYZ->Z = ((1 - xyY.x - xyY.y) / xyY.y) * xyY.Y;
		XYZ->_normalizeY = xyY._normalizeY;
		XYZ->_degree = xyY._degree;
		return XYZ;
	    };

	    double_array CIExyY::_getValues(double_array values) {
		values[0] = x;
		values[1] = y;
		values[2] = Y;
		return values;
	    };
	    void CIExyY::_setValues(double_array values) {
		x = values[0];
		y = values[1];
		Y = values[2];
	    };
	    string_vector_ptr CIExyY::getBandNames() {
		string_vector_ptr names(new string_vector(3));
		(*names)[0] = "x";
		(*names)[1] = "y";
		(*names)[2] = "Y";
		return names;
	    };
	    void CIExyY::normalize(NormalizeY normalizeY) {
		Y = normalizeY;
		_normalizeY = normalizeY;
	    };
	    void CIExyY::normalizeY() {
		Y = NormalFactor;
		_normalizeY = Normal1;
	    };

	    double_array CIExyY::getValues(double_array values,
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
		/* TODO : getValues */
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
	    double_array CIExyY::getValues() {
		return ColorSpace::getValues();
	    };
	    double_array CIExyY::getValues(double_array values) {
		return ColorSpace::getValues(values);
	    };
	    double CIExyY::getCCT() {
		return toXYZ()->getCCT();
	    };

	    double_array CIExyY::getDeltauv(const xyY_ptr xyY) {
		double_array uvp1 = getuvValues();
		double_array uvp2 = xyY->getuvValues();
		return DoubleArray::minus(uvp1, uvp2, 2);
	    };

	    double_array CIExyY::getDeltauvPrime(const xyY_ptr xyY) {
		double_array uvp1 = getuvPrimeValues();
		double_array uvp2 = xyY->getuvPrimeValues();
		return DoubleArray::minus(uvp1, uvp2, 2);
	    };
	    double_array CIExyY::getDeltaxy(const xyY_ptr xyY) {
		double_array deltaxy(new double[2]);
		deltaxy[0] = x - xyY->x;
		deltaxy[1] = y - xyY->y;
		return deltaxy;
	    };

	    double_array CIExyY::getuvPrimeValues() {
		double denominator = (-2 * x + 12 * y + 3);
		double_array uvp(new double[2]);
		uvp[0] = 4 * x / denominator;
		uvp[1] = 9 * y / denominator;
		return uvp;
	    };

	    double_array CIExyY::getuvPrimeYValues() {
		double_array uvp = getuvPrimeValues();
		double_array uvpY(new double[3]);
		uvpY[0] = uvp[0];
		uvpY[1] = uvp[1];
		uvpY[2] = Y;
		return uvpY;
	    };
	    double_array CIExyY::getuvValues() {
		double denominator = (-2 * x + 12 * y + 3);
		double_array uv(new double[2]);
		uv[0] = 4 * x / denominator;
		uv[1] = 6 * y / denominator;
		return uv;
	    };

	    double_array CIExyY::getWhitenessIndex() {
		double_array dxy = D65xyY.getDeltaxy(xyY_ptr(this));
		double W = Y + 800 * dxy[0] + 1700 * dxy[1];
		double Tw = 1000 * dxy[0] - 650 * dxy[1];

		double_array index(new double[2]);
		index[0] = W;
		index[1] = Tw;
		return index;
	    };
	    double_array CIExyY::getxyValues() {
		double_array xy(new double[2]);
		xy[0] = x;
		xy[1] = y;
		return xy;
	    };
	    bool CIExyY::isLegal() {
		return Y >= 0 && (x + y) <= 1;
	    };

	    void CIExyY::rationalize() {
		/*x = Double.isNaN(x) ? 0 : x;
		   y = Double.isNaN(y) ? 0 : y; */
	    };
	    void CIExyY::setuvPrimeValues(double_array uvPrimeValues) {
		double u = uvPrimeValues[0];
		double v = uvPrimeValues[1];
		double denominator = 9 * u / 2 - 12 * v + 9;

		x = (27 * u / 4) / denominator;
		y = 3 * v / denominator;
	    };
	    void CIExyY::setuvPrimeYValues(double_array uvPrimeYValues) {
		double_array uv(new double[2]);
		uv[0] = uvPrimeYValues[0];
		uv[1] = uvPrimeYValues[1];
		setuvPrimeValues(uv);
		Y = uvPrimeYValues[2];
	    }
	    //======================================================================
	};
    };

};

