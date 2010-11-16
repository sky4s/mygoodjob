#include <includeall.h>
#pragma hdrstop
#include "patch.h"
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    using namespace boost;
    using namespace std;
    using namespace Indep;
    using namespace Dep;
     Patch::Patch(string_ptr name, XYZ_ptr XYZ,
		  XYZ_ptr normalizedXYZ,
		  RGB_ptr rgb):name(name), XYZ(XYZ), normalizedXYZ(normalizedXYZ), rgb(rgb) {
    };
  Patch::Patch(string_ptr name, XYZ_ptr XYZ, XYZ_ptr normalizedXYZ, RGB_ptr rgb, RGB_ptr intensity):name(name), XYZ(XYZ),
	normalizedXYZ(normalizedXYZ), rgb(rgb),
	intensity(intensity) {
    };
    string_ptr Patch::getName() {
	return name;
    };

    XYZ_ptr Patch::getXYZ() {
	return XYZ;
    };
    XYZ_ptr Patch::getNormalizedXYZ() {
	return normalizedXYZ;
    };
    RGB_ptr Patch::getRGB() {
	return rgb;
    };

    RGB_ptr Patch::getIntensity() {
	return intensity;
    };
    Lab_ptr Patch::getLab() {
	return _Lab;
    };
    Patch_vector_ptr Patch::Produce::LabPatches(Patch_vector_ptr XYZPatchList, XYZ_ptr white) {
	Patch_ptr firstPatch = (*XYZPatchList)[0];

	foreach(Patch_ptr p, *XYZPatchList) {
	    XYZ_ptr XYZ = p->getXYZ();
	    Lab_ptr Lab = CIELab::fromXYZ(XYZ, white);
	    p->_Lab = Lab;
	}
	return XYZPatchList;
    };
};

