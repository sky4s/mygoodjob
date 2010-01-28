#include "independ.h"

namespace cms {
    namespace colorspace {
	//======================================================================
	// DeviceIndependentSpace
	//======================================================================
	const double DeviceIndependentSpace::ACTUAL_EPSILON = 0.008856;
	const double DeviceIndependentSpace::ACTUAL_KAPPA = 903.3;

	const double DeviceIndependentSpace::INTENT_EPSILON =
	    216.0 / 24389.0;
	const double DeviceIndependentSpace::INTENT_KAPPA = 24389.0 / 27.0;

	double DeviceIndependentSpace::epsilon = INTENT_EPSILON;
	double DeviceIndependentSpace::kappa = INTENT_KAPPA;

	 DeviceIndependentSpace::DeviceIndependentSpace():_degree(Two) {

	};


	int DeviceIndependentSpace::getNumberBands() {
	    return 3;
	};

	Degree DeviceIndependentSpace::getDegree() {
	    return _degree;
	};
	void DeviceIndependentSpace::setDegree(Degree degree) {
	    _degree = degree;
	};
	void DeviceIndependentSpace::setCIEStandard(CIEStandard standard) {
	    if (standard == ActualStandard) {
		epsilon = ACTUAL_EPSILON;
		kappa = ACTUAL_KAPPA;
	    } else {
		epsilon = INTENT_EPSILON;
		kappa = INTENT_KAPPA;
	    }
	}
	//======================================================================

	//======================================================================
	// NormalizeYOperator
	//======================================================================
	const double NormalizeYOperator::NormalFactor = 1;
	//const CIExyY CIExyY::D65xyY = NULL;
	void NormalizeYOperator::normalizeY100() {
	    normalizeY();
	    normalize(Normal100);
	};
	void NormalizeYOperator::setNormalizeNot() {
	    _normalizeY = Not;
	};
	//======================================================================


    };
};

