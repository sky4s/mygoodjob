#include "patch.h"

namespace cms {
    using namespace boost;
    using namespace std;
    using namespace Indep;
    using namespace Dep;
     Patch::Patch(shared_ptr < string > name, shared_ptr < CIEXYZ > XYZ,
		  shared_ptr < CIEXYZ > normalizedXYZ,
		  shared_ptr < RGBColor > rgb):name(name), XYZ(XYZ),
	normalizedXYZ(normalizedXYZ), rgb(rgb) {
    };

    string_ptr Patch::getName() {
	return name;
    };

    shared_ptr < CIEXYZ > Patch::getXYZ() {
	return XYZ;
    };
    shared_ptr < CIEXYZ > Patch::getNormalizedXYZ() {
	return normalizedXYZ;
    };
    shared_ptr < RGBColor > Patch::getRGB() {
	return rgb;
    };
};

