#include "independ.h"

namespace cms {
    namespace colorspace {
	const double DeviceIndependentSpace::ACTUAL_EPSILON = 0.008856;
	const double DeviceIndependentSpace::ACTUAL_KAPPA = 903.3;

	const double DeviceIndependentSpace::INTENT_EPSILON =
	    216.0 / 24389.0;
	const double DeviceIndependentSpace::INTENT_KAPPA = 24389.0 / 27.0;

	double DeviceIndependentSpace::epsilon = INTENT_EPSILON;
	double DeviceIndependentSpace::kappa = INTENT_KAPPA;

	const double NormalizeYOperator::NormalFactor = 1;
	//CIEXYZ::normalizeY = Not;
    };
};

