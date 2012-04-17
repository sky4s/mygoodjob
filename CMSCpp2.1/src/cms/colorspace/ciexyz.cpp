#include <includeall.h>
#pragma hdrstop
#include "ciexyz.h"

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
//#include <math/doublearray.h>

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
		return CorrelatedColorTemperature::
		    xy2CCTByMcCamyFloat(xyY_ptr
					(new CIExyY(XYZ_ptr(this))));
	    };

	    const NormalizeY & CIEXYZ::getNormalizeY() {
		return normalizeY_;
	    };
	    double CIEXYZ::getSaturation(XYZ_ptr white) {
		/*double[] uv = this.getuvPrimeValues();
		   double[] uvn = white.getuvPrimeValues();
		   return 13 * Math.sqrt(Maths.sqr(uv[0] - uvn[0]) +
		   Maths.sqr(uv[1] - uvn[1])); */
		/* TODO : getSaturation */
		return -1;
	    };
	    double_array CIEXYZ::getuvPrimeValues() {
		CIExyY xyY(XYZ_ptr(new CIEXYZ(*this)));
		return xyY.getuvPrimeValues();
	    };
	    double_array CIEXYZ::getuvValues() {
		CIExyY xyY(XYZ_ptr(new CIEXYZ(*this)));
		return xyY.getuvValues();
	    };
	    double_array CIEXYZ::getValues(double_array values,
					   NormalizeY normalizeY) {
		if (normalizeY_ == Not) {
		    throw
			IllegalStateException
			("this.normalizeY == NormalizeY.Not");
		}
		getValues(values);
		if (normalizeY_ == normalizeY) {
		    return values;
		}
		switch (normalizeY_) {
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


	    double_array CIEXYZ::getValues() {
		return ColorSpace::getValues();
	    };
	    double_array CIEXYZ::getValues(double_array values) {
		return ColorSpace::getValues(values);
	    };

	    XYZ_ptr CIEXYZ::toXYZ() {
		return XYZ_ptr(this);
	    };

	    double_array CIEXYZ::getWhitenessIndex() {
		return CIExyY(toXYZ()).getWhitenessIndex();
	    };

	    double_array CIEXYZ::getxyValues() const {
		if (Y == 0) {
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
		return isLegal() && X <= white->X && Y <= white->Y
		    && Z <= white->Z;
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
		normalizeY_ = Normal1;
	    };

	    void CIEXYZ::normalizeY() {
		double factor = NormalFactor / Y;
		X *= factor;
		Z *= factor;
		Y = NormalFactor;
		normalizeY_ = Normal1;
	    };

	    void CIEXYZ::normalize(NormalizeY normalizeY) {
		double_array values =
		    getValues(double_array(new double[3]),
			      normalizeY);
		setValues(values);
		normalizeY_ = normalizeY;
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

	  CIEXYZ::CIEXYZ():X(0), Y(0), Z(0) {
	    };
	  CIEXYZ::CIEXYZ(double_array XYZValues, NormalizeY normalizeY):normalizeY_(normalizeY)
	    {
		setValues(XYZValues);
	    };
	    CIEXYZ::CIEXYZ(double_array XYZValues) {
		setValues(XYZValues);
	    };
	    CIEXYZ::CIEXYZ(double X, double Y, double Z,
			   NormalizeY normalizeY):normalizeY_(normalizeY) {
		setValues(X, Y, Z);
	    };
	    CIEXYZ::CIEXYZ(double X, double Y, double Z) {
		setValues(X, Y, Z);
	    };
	    XYZ_ptr CIEXYZ::clone() {
		return XYZ_ptr(new CIEXYZ(*this));
	    };
	    //======================================================================


	    //======================================================================
	    // CIExyY
	    //======================================================================
	  CIExyY::CIExyY():x(0), y(0), Y(0) {
	    };

	  CIExyY::CIExyY(XYZ_ptr XYZ):normalizeY_(XYZ->
			normalizeY_)
	    {
		double_array xyValues = XYZ->getxyValues();
		setValues(xyValues[0], xyValues[1], XYZ->Y);
	    };
	  CIExyY::CIExyY(double_array xyValues, NormalizeY normalizeY):normalizeY_(normalizeY)
	    {
		setValues(xyValues);
	    };
	    CIExyY::CIExyY(double_array xyValues) {
		setValues(xyValues);
	    };
	  CIExyY::CIExyY(double x, double y, double Y, NormalizeY normalizeY):normalizeY_(normalizeY)
	    {
		setValues(x, y, Y);
	    };
	    CIExyY::CIExyY(double x, double y, double Y) {
		setValues(x, y, Y);
	    };
	    CIExyY::CIExyY(double x, double y) {
		setValues(x, y, 1);
	    };

	    xyY_ptr CIExyY::fromCCT2Blackbody(int CCT) {
		return CorrelatedColorTemperature::CCT2BlackbodyxyY(CCT);
	    };
	    xyY_ptr CIExyY::fromCCT2DIlluminant(int CCT) {
		return CorrelatedColorTemperature::CCT2DIlluminantxyY(CCT);
	    };

	    XYZ_ptr CIExyY::toXYZ() {
		XYZ_ptr result = toXYZ(*this);
		return result;
	    };

	    XYZ_ptr CIExyY::toXYZ(const CIExyY & xyY) {
		XYZ_ptr XYZ(new CIEXYZ());

		if (xyY.x != 0 || xyY.y != 0 || xyY.Y != 0) {
		    XYZ->X = (xyY.x / xyY.y) * xyY.Y;
		    XYZ->Y = xyY.Y;
		    XYZ->Z = ((1 - xyY.x - xyY.y) / xyY.y) * xyY.Y;
		}
		XYZ->normalizeY_ = xyY.normalizeY_;
		XYZ->degree_ = xyY.degree_;
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
		normalizeY_ = normalizeY;
	    };
	    void CIExyY::normalizeY() {
		Y = NormalFactor;
		normalizeY_ = Normal1;
	    };

	    double_array CIExyY::getValues(double_array values,
					   NormalizeY normalizeY) {
		if (normalizeY_ == Not) {
		    throw
			IllegalStateException
			("this.normalizeY == NormalizeY.Not");
		}
		getValues(values);
		if (normalizeY_ == normalizeY) {
		    return values;
		}
		/* TODO : getValues */
		switch (normalizeY_) {
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
		setuvPrimeValues(uvPrimeYValues);
		Y = uvPrimeYValues[2];
	    }
	    void CIExyY::setuvValues(double_array uvValues) {
		double u = uvValues[0];
		double v = uvValues[1];
		double denominator = 2 * u - 8 * v + 4;

		x = 3 * u / denominator;
		y = 2 * u / denominator;
	    }
	    void CIExyY::setuvYValues(double_array uvYValues) {
		setuvValues(uvYValues);
		Y = uvYValues[2];
	    }
	    xyY_ptr CIExyY::clone() {
            	return xyY_ptr(new CIExyY(*this));
	    };
	    //======================================================================

	    //======================================================================
	    // CIELab
	    //===================================================================
	    //const double CIELab::epsilon = 216.0 / 24389.0;
	    //const double CIELab::kappa = 24389.0 / 27.0;

	    double_array CIELab::_getValues(double_array values) {
		values[0] = L;
		values[1] = a;
		values[2] = b;
		return values;
	    };
	    void CIELab::_setValues(double_array values) {
		L = values[0];
		a = values[1];
		b = values[2];
	    };
	  CIELab::CIELab():L(0), a(0), b(0) {
	    };

	  CIELab::CIELab(XYZ_ptr XYZ, XYZ_ptr white):DeviceIndependentSpace(white)
	    {
		double_array r(new double[3]);
		r[0] = XYZ->X / white->X;
		r[1] = XYZ->Y / white->Y;
		r[2] = XYZ->Z / white->Z;

		double_array f(new double[3]);

		for (int i = 0; i < 3; i++) {
		    if (r[i] > epsilon) {
			f[i] = Math::cubeRoot(r[i]);	// more precisse than return pow(t, 1.0/3.0);
		    } else {
			f[i] = (kappa * r[i] + 16) / 116;
		    }
		}

		double_array LabValues(new double[3]);
		LabValues[0] = 116.0 * f[1] - 16;
		LabValues[1] = 500.0 * (f[0] - f[1]);
		LabValues[2] = 200.0 * (f[1] - f[2]);

		setValues(LabValues);
	    };

	    CIELab::CIELab(double_array LabValues, XYZ_ptr white) {
		setValues(LabValues);
		this->white = white;
	    }
	    CIELab::CIELab(double L, double a, double b) {
		this->L = L;
		this->a = a;
		this->b = b;
	    }
	    string_vector_ptr CIELab::getBandNames() {
		string_vector_ptr names(new string_vector(3));
		(*names)[0] = "L";
		(*names)[1] = "a";
		(*names)[2] = "b";
		return names;
	    };
	    XYZ_ptr CIELab::toXYZ() {
		return XYZ_ptr((CIEXYZ *) null);
	    };
	    Lab_ptr CIELab::getLabAdaptedToD65() {
		return Lab_ptr(this);
	    };

	    double_array CIELab::fromXYZValues(double_array XYZValues,
					       double_array whitePoint) {
		double_array r(new double[3]);
		r[0] = XYZValues[0] / whitePoint[0];
		r[1] = XYZValues[1] / whitePoint[1];
		r[2] = XYZValues[2] / whitePoint[2];

		double_array f(new double[3]);

		for (int i = 0; i < 3; i++) {
		    if (r[i] > epsilon) {
			f[i] = Math::cubeRoot(r[i]);	// more precisse than return pow(t, 1.0/3.0);
		    } else {
			f[i] = (kappa * r[i] + 16) / 116;
		    }
		}

		double_array LabValues(new double[3]);
		LabValues[0] = 116.0 * f[1] - 16;
		LabValues[1] = 500.0 * (f[0] - f[1]);
		LabValues[2] = 200.0 * (f[1] - f[2]);
		return LabValues;
	    }
	    Lab_ptr CIELab::fromXYZ(XYZ_ptr XYZ, XYZ_ptr whitePoint) {
		double_array XYZValues = XYZ->getValues();
		double_array whiteXYZValues = whitePoint->getValues();
		double_array LabValues =
		    fromXYZValues(XYZValues, whiteXYZValues);
		Lab_ptr Lab(new CIELab(LabValues, whitePoint));
		return Lab;
	    };
	    //======================================================================
	    // CIELCh
	    //===================================================================
	  CIELCh::CIELCh(Lab_ptr Lab):DeviceIndependentSpace(Lab->
				   getWhite())
	    {
		this->setValues(fromLabValues(Lab->getValues()));
		this->style = Style::Lab;
	    };
	    double_array CIELCh::fromLabValues(double_array labValues) {
		return cartesian2polarCoordinatesValues(labValues);
	    };
	    string_vector_ptr CIELCh::getBandNames() {
		string_vector_ptr names(new string_vector(3));
		(*names)[0] = "L";
		(*names)[1] = "C";
		(*names)[2] = "h";
		return names;
	    };
	    XYZ_ptr CIELCh::toXYZ() {
		return XYZ_ptr((CIEXYZ *) null);
	    };
	    double_array CIELCh::_getValues(double_array values) {
		values[0] = L;
		values[1] = C;
		values[2] = h;
		return values;
	    };
	    void CIELCh::_setValues(double_array values) {
		L = values[0];
		C = values[1];
		h = values[2];
	    };
	};

    };
};

