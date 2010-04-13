#ifndef CIEXYZH
#define CIEXYZH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
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
		string_vector_ptr getBandNames();
		double getCCT();

		NormalizeY getNormalizeY();
		double getSaturation(CIEXYZ white);
		double_array getuvPrimeValues();
		double_array getuvValues();
		double_array getValues(double_array values,
				       NormalizeY normalizeY);



		double_array getValues();
		double_array getValues(double_array values);

		 bptr < CIEXYZ > toXYZ();

		double_array getWhitenessIndex();
		double_array getxyValues() const;

		double_array getxyzValues();

		double getYellownessIndex();

		bool isBlack();

		bool isLegal();
		bool isLegal(XYZ_ptr white);
		static bptr < CIEXYZ >
		    minus(const XYZ_ptr XYZ1, const XYZ_ptr XYZ2);

		static XYZ_ptr
		    plus(const XYZ_ptr XYZ1, const XYZ_ptr XYZ2);

		void normalize(XYZ_ptr normal);

		void normalizeY();

		void normalize(NormalizeY normalizeY);
		void rationalize();
		void rationalize(XYZ_ptr white);

		void scaleY(XYZ_ptr scale);
		void scaleY(double scaleY);
		void times(double factor);

		 CIEXYZ();
		 CIEXYZ(double_array XYZValues, NormalizeY normalizeY);
		 CIEXYZ(double_array XYZValues);
		 CIEXYZ(double X, double Y, double Z,
			NormalizeY normalizeY);
		 CIEXYZ(double X, double Y, double Z);
	    };


	    class CIExyY:public DeviceIndependentSpace, NormalizeYOperator {
	      protected:
		NormalizeY normalizeY_;
		static CIExyY D65xyY;
	      public:
		double x, y, Y;
		 CIExyY();

		 CIExyY(const XYZ_ptr XYZ);
		 CIExyY(double_array xyValues, NormalizeY normalizeY);
		 CIExyY(double_array xyValues);
		 CIExyY(double x, double y, double Y,
			NormalizeY normalizeY);
		 CIExyY(double x, double y, double Y);
		 CIExyY(double x, double y);

		static bptr < CIExyY > fromCCT2Blackbody(int CCT);
		static bptr < CIExyY > fromCCT2DIlluminant(int CCT);
		static bptr < CIExyY > fromXYZ(const XYZ_ptr XYZ);

		 bptr < CIEXYZ > toXYZ();

		static bptr < CIEXYZ > toXYZ(const CIExyY & xyY);

		double_array _getValues(double_array values);
		void _setValues(double_array values);
		string_vector_ptr getBandNames();
		void normalize(NormalizeY normalizeY);
		void normalizeY();

		double_array getValues(double_array values,
				       NormalizeY normalizeY);
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
	    };
	};
    };
};

#endif

