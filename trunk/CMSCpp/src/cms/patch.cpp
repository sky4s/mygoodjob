#include "patch.h"

namespace cms {
    Patch::Patch(shared_ptr < string > name, shared_ptr < CIEXYZ > XYZ,
		 shared_ptr < CIEXYZ > normalizedXYZ,
		 shared_ptr < RGBColor > rgb):name(name), XYZ(XYZ),
	normalizedXYZ(normalizedXYZ), rgb(rgb) {
    };
};

