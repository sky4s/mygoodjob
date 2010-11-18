#ifndef CIEXYZH
#define CIEXYZH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���

//�����ؤ��Y���
#include "independ.h"

namespace cms {
    namespace colorspace {
	namespace independ {
	    class CIEXYZ:public DeviceIndependentSpace, NormalizeYOperator {
	      protected:
		friend class CIExyY;
		NormalizeY normalizeY_;
		double_array _getValues(double_array values);
		void _setValues(double_array values);

	      public:
		double X, Y, Z;
		//===============================================================
		// constructor
		//===============================================================
		 CIEXYZ();
		 CIEXYZ(double_array XYZValues, NormalizeY normalizeY);
		 CIEXYZ(double_array XYZValues);
		 CIEXYZ(double X, double Y, double Z, NormalizeY normalizeY);
		 CIEXYZ(double X, double Y, double Z);
		//===============================================================

		//===============================================================
		// ColorSpace
		//===============================================================
		string_vector_ptr getBandNames();
		//===============================================================
		//===============================================================
		// DeviceIndependentSpace
		//===============================================================
		XYZ_ptr toXYZ();
		//===============================================================
		double getCCT();

		const NormalizeY & getNormalizeY();
		double getSaturation(CIEXYZ white);
		double_array getuvPrimeValues();
		double_array getuvValues();
		double_array getValues(double_array values, NormalizeY normalizeY);

		double_array getValues();
		double_array getValues(double_array values);

		double_array getWhitenessIndex();
		double_array getxyValues() const;
		double_array getxyzValues();

		double getYellownessIndex();

		bool isBlack();
		bool isLegal();
		bool isLegal(XYZ_ptr white);

		static XYZ_ptr minus(const XYZ_ptr XYZ1, const XYZ_ptr XYZ2);
		static XYZ_ptr plus(const XYZ_ptr XYZ1, const XYZ_ptr XYZ2);

		void normalize(XYZ_ptr normal);
		void normalizeY();
		void normalize(NormalizeY normalizeY);
		void rationalize();
		void rationalize(XYZ_ptr white);

		void scaleY(XYZ_ptr scale);
		void scaleY(double scaleY);
		void times(double factor);


	    };


	    class CIExyY:public DeviceIndependentSpace, NormalizeYOperator {
	      protected:
		NormalizeY normalizeY_;
		static CIExyY D65xyY;
		double_array _getValues(double_array values);
		void _setValues(double_array values);
	      public:
		double x, y, Y;
		//===============================================================
		// constructor
		//===============================================================
		 CIExyY();
		 CIExyY(const XYZ_ptr XYZ);
		 CIExyY(double_array xyValues, NormalizeY normalizeY);
		 CIExyY(double_array xyValues);
		 CIExyY(double x, double y, double Y, NormalizeY normalizeY);
		 CIExyY(double x, double y, double Y);
		 CIExyY(double x, double y);
		//===============================================================
		//===============================================================
		// ColorSpace
		//===============================================================
		string_vector_ptr getBandNames();
		//===============================================================
		//===============================================================
		// DeviceIndependentSpace
		//===============================================================
		XYZ_ptr toXYZ();
		//===============================================================

		//===============================================================
		// static
		//===============================================================
		static xyY_ptr fromCCT2Blackbody(int CCT);
		static xyY_ptr fromCCT2DIlluminant(int CCT);
		static XYZ_ptr toXYZ(const CIExyY & xyY);

		//===============================================================
		// NormalizeYOperator
		//===============================================================
		void normalize(NormalizeY normalizeY);
		void normalizeY();
		//===============================================================

		//===============================================================
		// 
		//===============================================================
		double_array getValues(double_array values, NormalizeY normalizeY);
		double_array getValues();
		double_array getValues(double_array values);
		double getCCT();
		double_array getDeltauv(const xyY_ptr xyY);
		double_array getDeltauvPrime(const xyY_ptr xyY);
		double_array getDeltaxy(const xyY_ptr xyY);
		double_array getuvPrimeValues();
		double_array getuvPrimeYValues();
		double_array getuvValues();
		double_array getWhitenessIndex();
		double_array getxyValues();
		bool isLegal();
		void rationalize();
		void setuvPrimeValues(double_array uvPrimeValues);
		void setuvPrimeYValues(double_array uvPrimeYValues);
		void setuvValues(double_array uvValues);
		void setuvYValues(double_array uvYValues);
		//===============================================================
	    };

	    class CIELab:public DeviceIndependentSpace {
	      protected:
		double_array _getValues(double_array values);
		void _setValues(double_array values);
		XYZ_ptr white;
		static const double epsilon;
		static const double kappa;
	      public:

		double L, a, b;
		//===============================================================
		// constructor
		//===============================================================
		 CIELab();
		 CIELab(XYZ_ptr XYZ, XYZ_ptr white);
		 CIELab(double_array LabValues, XYZ_ptr white);
		 CIELab(double L, double a, double b);
		//===============================================================
		//===============================================================
		// ColorSpace
		//===============================================================
		string_vector_ptr getBandNames();
		//===============================================================
		//===============================================================
		// DeviceIndependentSpace
		//===============================================================
		XYZ_ptr toXYZ();
		//===============================================================
		//Lab_ptr CIELab::fromXYZ(const XYZ_ptr XYZ, const XYZ_ptr whitePoint);
		Lab_ptr getLabAdaptedToD65();
		static double_array fromXYZValues(double_array XYZValues, double_array whitePoint);
		static Lab_ptr fromXYZ(XYZ_ptr XYZ, XYZ_ptr whitePoint);
	    };
	};
    };
};

#endif

