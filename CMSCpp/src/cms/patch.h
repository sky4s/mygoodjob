#ifndef PATCHH
#define PATCHH

#include <java/lang.h>
#include <cms/core.h>
#include <cms/colorspace/depend.h>

namespace cms {
    using cms::colorspace::RGBColor;
    class Patch:public Object, NameIF {
      protected:
	shared_ptr < string > name;
	//CIELab _Lab = null;
	shared_ptr < CIEXYZ > XYZ;
	shared_ptr < CIEXYZ > normalizedXYZ;
	shared_ptr < RGBColor > rgb;
	//shared_ptr < RGBColor > originalRGB = null;
	shared_ptr < Spectra > spectra;
	shared_ptr < Spectra > reflectSpectra;
      public:
	Patch(shared_ptr < string > name, shared_ptr < CIEXYZ > XYZ,
	      shared_ptr < CIEXYZ > normalizedXYZ,
	      shared_ptr < RGBColor > rgb):name(name), XYZ(XYZ),
	    normalizedXYZ(normalizedXYZ), rgb(rgb) {
	};
    };


};
#endif

