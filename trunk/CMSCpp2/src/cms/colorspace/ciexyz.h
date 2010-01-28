#ifndef CIEXYZH
#define CIEXYZH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include "independ.h"

namespace cms {
    namespace colorspace {
	class CIEXYZ:public DeviceIndependentSpace, NormalizeYOperator {
	  protected:
	    friend class CIExyY;
	    NormalizeY _normalizeY;

	  public:
	    double X, Y, Z;
	    vector_string_ptr getBandNames();
	    double getCCT();

	    NormalizeY getNormalizeY();
	    double getSaturation(CIEXYZ white);
	     boost::shared_array < double >getuvPrimeValues();
	     boost::shared_array < double >getuvValues();
	     boost::shared_array < double >getValues(boost::shared_array <
						     double >values,
						     NormalizeY
						     normalizeY);

	     boost::shared_array < double >_getValues(boost::shared_array <
						      double >values);
	    void _setValues(boost::shared_array < double >values);


	     boost::shared_array < double >getValues();
	     boost::shared_array < double >getValues(boost::shared_array <
						     double >values);

	     boost::shared_ptr < CIEXYZ > toXYZ();

	     boost::shared_array < double >getWhitenessIndex();
	     boost::shared_array < double >getxyValues() const;

	     boost::shared_array < double >getxyzValues();

	    double getYellownessIndex();

	    bool isBlack();

	    bool isLegal();
	    bool isLegal(CIEXYZ white);
	    static boost::shared_ptr < CIEXYZ > minus(const CIEXYZ & XYZ1,
						      const CIEXYZ & XYZ2);

	    static boost::shared_ptr < CIEXYZ > plus(const CIEXYZ & XYZ1,
						     const CIEXYZ & XYZ2);

	    void normalize(boost::shared_ptr < CIEXYZ > normal);

	    void normalizeY();

	    void normalize(NormalizeY normalizeY);
	    void rationalize();
	    void rationalize(boost::shared_ptr < CIEXYZ > white);

	    void scaleY(boost::shared_ptr < CIEXYZ > scale);
	    void scaleY(double scaleY);
	    void times(double factor);

	     CIEXYZ();
	     CIEXYZ(boost::shared_array < double >XYZValues,
		    NormalizeY normalizeY);
	     CIEXYZ(boost::shared_array < double >XYZValues);
	     CIEXYZ(double X, double Y, double Z, NormalizeY normalizeY);
	     CIEXYZ(double X, double Y, double Z);
	};





	class CIExyY:public DeviceIndependentSpace, NormalizeYOperator {
	  protected:
	    NormalizeY _normalizeY;
	    static CIExyY D65xyY;
	  public:
	    double x, y, Y;
	     CIExyY();

	     CIExyY(CIEXYZ & XYZ);
	     CIExyY(boost::shared_array < double >xyValues,
		    NormalizeY normalizeY);
	     CIExyY(boost::shared_array < double >xyValues);
	     CIExyY(double x, double y, double Y, NormalizeY normalizeY);
	     CIExyY(double x, double y, double Y);
	     CIExyY(double x, double y);

	    static boost::shared_ptr < CIExyY > fromCCT2Blackbody(int CCT);
	    static boost::shared_ptr < CIExyY >
		fromCCT2DIlluminant(int CCT);
	    static boost::shared_ptr < CIExyY >
		fromXYZ(const CIEXYZ & XYZ);

	     boost::shared_ptr < CIEXYZ > toXYZ();

	    static boost::shared_ptr < CIEXYZ > toXYZ(const CIExyY & xyY);

	     boost::shared_array < double >_getValues(boost::shared_array <
						      double >values);
	    void _setValues(boost::shared_array < double >values);
	    vector_string_ptr getBandNames();
	    void normalize(NormalizeY normalizeY);
	    void normalizeY();

	     boost::shared_array < double >getValues(boost::shared_array <
						     double >values,
						     NormalizeY
						     normalizeY);
	     boost::shared_array < double >getValues();
	     boost::shared_array < double >getValues(boost::shared_array <
						     double >values);
	    double getCCT();

	     boost::shared_array < double >getDeltauv(CIExyY & xyY);

	     boost::shared_array < double >getDeltauvPrime(CIExyY & xyY);
	     boost::shared_array < double >getDeltaxy(CIExyY & xyY);

	     boost::shared_array < double >getuvPrimeValues();

	     boost::shared_array < double >getuvPrimeYValues();
	     boost::shared_array < double >getuvValues();
	     boost::shared_array < double >getWhitenessIndex();
	     boost::shared_array < double >getxyValues();
	    bool isLegal();
	    void rationalize();
	    void setuvPrimeValues(boost::shared_array <
				  double >uvPrimeValues);
	    void setuvPrimeYValues(boost::shared_array <
				   double >uvPrimeYValues);
	};

    };
};


#endif

