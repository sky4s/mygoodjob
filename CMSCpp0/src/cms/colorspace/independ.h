#ifndef INDEPENDH
#define INDEPENDH
#include "colorspace.h"
//#include "ciexyz.h"

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
	    //CIEXYZ white;
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
		//shared_array < double >(new double[3]);
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
	  protected:NormalizeY _normalizeY;
	  public:
	    NormalizeYOperator(NormalizeY
			       normalizeY):_normalizeY(normalizeY) {
	    };
	  NormalizeYOperator():_normalizeY(Not) {
	    };
	    virtual void normalize(NormalizeY normalizeY) = 0;
	    virtual void normalizeY() = 0;
	    void normalizeY100() {
		normalizeY();
		normalize(Normal100);
	    };
	    virtual void setNormalizeNot() = 0;
	    const static double NormalFactor;
	};

    };
};
#endif

