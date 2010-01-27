#include "ciexyz.h"

namespace cms {
    namespace colorspace {
	using namespace std;
	using namespace boost;
	using namespace java::lang;
	//======================================================================
	// CIEXYZ
	//======================================================================
	vector_string_ptr CIEXYZ::getBandNames() {
	    vector_string_ptr names(new vector < string > (3));
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
	shared_array < double >CIEXYZ::getuvPrimeValues() {
	    /*CIExyY xyY = CIExyY.fromXYZ(this);
	       return xyY.getuvPrimeValues(); */
	};
	shared_array < double >CIEXYZ::getuvValues() {
	    /*CIExyY xyY = CIExyY.fromXYZ(this);
	       return xyY.getuvValues(); */
	};
	shared_array < double >CIEXYZ::getValues(shared_array <
						 double >values,
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

	shared_array < double >CIEXYZ::_getValues(shared_array <
						  double >values) {
	    //shared_array < double >values(new double[3]);
	    values[0] = X;
	    values[1] = Y;
	    values[2] = Z;
	    return values;
	};
	void CIEXYZ::_setValues(shared_array < double >values) {
	    X = values[0];
	    Y = values[1];
	    Z = values[2];
	};


	//using ColorSpace::getValues;
	shared_array < double >CIEXYZ::getValues() {
	    return ColorSpace::getValues();
	};
	shared_array < double >CIEXYZ::getValues(shared_array <
						 double >values) {
	    return ColorSpace::getValues(values);
	};

	shared_ptr < CIEXYZ > CIEXYZ::toXYZ() {
	    //return *this;
	};

	shared_array < double >CIEXYZ::getWhitenessIndex() {
	    //return new CIExyY(this).getWhitenessIndex();
	};

	shared_array < double >CIEXYZ::getxyValues() const {
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

	shared_array < double >CIEXYZ::getxyzValues() {
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
	bool CIEXYZ::isLegal(CIEXYZ white) {
	    return isLegal() && X <= white.X && Y <= white.Y &&
		Z <= white.Z;
	};
	shared_ptr < CIEXYZ > CIEXYZ::minus(const CIEXYZ & XYZ1,
					    const CIEXYZ & XYZ2) {

	    shared_ptr < CIEXYZ > result(new CIEXYZ());
	    result->X = XYZ1.X - XYZ2.X;
	    result->Y = XYZ1.Y - XYZ2.Y;
	    result->Z = XYZ1.Z - XYZ2.Z;
	    return result;
	};

	shared_ptr < CIEXYZ > CIEXYZ::plus(const CIEXYZ & XYZ1,
					   const CIEXYZ & XYZ2) {
	    shared_ptr < CIEXYZ > result(new CIEXYZ());
	    result->X = XYZ1.X + XYZ2.X;
	    result->Y = XYZ1.Y + XYZ2.Y;
	    result->Z = XYZ1.Z + XYZ2.Z;
	    return result;
	};

	void CIEXYZ::normalize(shared_ptr < CIEXYZ > normal) {
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
	    shared_array < double >values =
		getValues(shared_array < double >(new double[3]),
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
	void CIEXYZ::rationalize(shared_ptr < CIEXYZ > white) {
	    rationalize();

	    X = (X > white->X) ? white->X : X;
	    Y = (Y > white->Y) ? white->Y : Y;
	    Z = (Z > white->Z) ? white->Z : Z;
	};

	void CIEXYZ::scaleY(shared_ptr < CIEXYZ > scale) {
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
	CIEXYZ::CIEXYZ(shared_array < double >XYZValues,
		       NormalizeY normalizeY):_normalizeY(normalizeY) {
	    setValues(XYZValues);
	};
	CIEXYZ::CIEXYZ(shared_array < double >XYZValues) {
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

      CIExyY::CIExyY(CIEXYZ & XYZ):_normalizeY(XYZ._normalizeY) {
	    shared_array < double >xyValues = XYZ.getxyValues();
	    setValues(xyValues[0], xyValues[1], XYZ.Y);
	};
	CIExyY::CIExyY(shared_array < double >xyValues,
		       NormalizeY normalizeY):_normalizeY(normalizeY) {
	    setValues(xyValues);
	};
	CIExyY::CIExyY(shared_array < double >xyValues) {
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

	shared_ptr < CIExyY > CIExyY::fromCCT2Blackbody(int CCT) {
	    //return CorrelatedColorTemperature.CCT2BlackbodyxyY(CCT);
	};
	shared_ptr < CIExyY > CIExyY::fromCCT2DIlluminant(int CCT) {
	    //return CorrelatedColorTemperature.CCT2DIlluminantxyY(CCT);
	};
	shared_ptr < CIExyY > CIExyY::fromXYZ(const CIEXYZ & XYZ) {
	    shared_array < double >xyValues = XYZ.getxyValues();
	    shared_ptr < CIExyY >
		xyY(new CIExyY(xyValues[0], xyValues[1], XYZ.Y,
			       XYZ._normalizeY));
	    return xyY;
	}

	shared_ptr < CIEXYZ > CIExyY::toXYZ() {
	    //return toXYZ(this);
	};

	shared_ptr < CIEXYZ > CIExyY::toXYZ(const CIExyY & xyY) {
	    shared_ptr < CIEXYZ > XYZ(new CIEXYZ());

	    XYZ->X = (xyY.x / xyY.y) * xyY.Y;
	    XYZ->Y = xyY.Y;
	    XYZ->Z = ((1 - xyY.x - xyY.y) / xyY.y) * xyY.Y;
	    XYZ->_normalizeY = xyY._normalizeY;
	    XYZ->_degree = xyY._degree;
	    return XYZ;
	};

	shared_array < double >CIExyY::_getValues(shared_array <
						  double >values) {
	    values[0] = x;
	    values[1] = y;
	    values[2] = Y;
	    return values;
	};
	void CIExyY::_setValues(shared_array < double >values) {
	    x = values[0];
	    y = values[1];
	    Y = values[2];
	};
	vector_string_ptr CIExyY::getBandNames() {
	    vector_string_ptr names(new vector < string > (3));
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

	shared_array < double >CIExyY::getValues(shared_array <
						 double >values,
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
	shared_array < double >CIExyY::getValues() {
	    return ColorSpace::getValues();
	};
	shared_array < double >CIExyY::getValues(shared_array <
						 double >values) {
	    return ColorSpace::getValues(values);
	};
	double CIExyY::getCCT() {
	    return toXYZ()->getCCT();
	};

	shared_array < double >CIExyY::getDeltauv(CIExyY & xyY) {
	    shared_array < double >uvp1 = getuvValues();
	    shared_array < double >uvp2 = xyY.getuvValues();
	    //double[] duvp = DoubleArray.minus(uvp1, uvp2);
	    //return duvp;
	};

	shared_array < double >CIExyY::getDeltauvPrime(CIExyY & xyY) {
	    shared_array < double >uvp1 = getuvPrimeValues();
	    shared_array < double >uvp2 = xyY.getuvPrimeValues();
	    //double[] duvp = DoubleArray.minus(uvp1, uvp2);
	    //return duvp;
	};
	shared_array < double >CIExyY::getDeltaxy(CIExyY & xyY) {
	    shared_array < double >deltaxy(new double[2]);
	    deltaxy[0] = x - xyY.x;
	    deltaxy[1] = y - xyY.y;
	    return deltaxy;
	};

	shared_array < double >CIExyY::getuvPrimeValues() {
	    double denominator = (-2 * x + 12 * y + 3);
	    shared_array < double >uvp(new double[2]);
	    uvp[0] = 4 * x / denominator;
	    uvp[1] = 9 * y / denominator;
	    return uvp;
	};

	shared_array < double >CIExyY::getuvPrimeYValues() {
	    shared_array < double >uvp = getuvPrimeValues();
	    shared_array < double >uvpY(new double[3]);
	    uvpY[0] = uvp[0];
	    uvpY[1] = uvp[1];
	    uvpY[2] = Y;
	    return uvpY;
	};
	shared_array < double >CIExyY::getuvValues() {
	    double denominator = (-2 * x + 12 * y + 3);
	    shared_array < double >uv(new double[2]);
	    uv[0] = 4 * x / denominator;
	    uv[1] = 6 * y / denominator;
	    return uv;
	};

	shared_array < double >CIExyY::getWhitenessIndex() {
	    shared_array < double >dxy = D65xyY.getDeltaxy(*this);
	    double W = Y + 800 * dxy[0] + 1700 * dxy[1];
	    double Tw = 1000 * dxy[0] - 650 * dxy[1];

	    shared_array < double >index(new double[2]);
	    index[0] = W;
	    index[1] = Tw;
	    return index;
	};
	shared_array < double >CIExyY::getxyValues() {
	    shared_array < double >xy(new double[2]);
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
	void CIExyY::setuvPrimeValues(shared_array < double >uvPrimeValues) {
	    double u = uvPrimeValues[0];
	    double v = uvPrimeValues[1];
	    double denominator = 9 * u / 2 - 12 * v + 9;

	    x = (27 * u / 4) / denominator;
	    y = 3 * v / denominator;
	};
	void CIExyY::setuvPrimeYValues(shared_array <
				       double >uvPrimeYValues) {
	    shared_array < double >uv(new double[2]);
	    uv[0] = uvPrimeYValues[0];
	    uv[1] = uvPrimeYValues[1];
	    setuvPrimeValues(uv);
	    Y = uvPrimeYValues[2];
	}
	//======================================================================
    };
};

;

