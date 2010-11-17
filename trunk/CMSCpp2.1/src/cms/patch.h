#ifndef PATCHH
#define PATCHH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <cms/util/util.h>

namespace cms {
    class Patch:public jObject, cms::util::NameIF {

      protected:
	string_ptr name;
	XYZ_ptr XYZ;
	Lab_ptr _Lab;
	XYZ_ptr normalizedXYZ;
	RGB_ptr rgb;
	RGB_ptr intensity;
	 bptr < Spectra > spectra;
	 bptr < Spectra > reflectSpectra;
      public:
	 Patch(string_ptr name, XYZ_ptr XYZ, XYZ_ptr normalizedXYZ, RGB_ptr rgb);
	 Patch(string_ptr name, XYZ_ptr XYZ, XYZ_ptr normalizedXYZ, RGB_ptr rgb, RGB_ptr intensity);
	 bptr < std::string > getName();
	XYZ_ptr getXYZ();
	XYZ_ptr getNormalizedXYZ();
	RGB_ptr getRGB();
	RGB_ptr getIntensity();
	Lab_ptr getLab();
	const string_ptr toString() const;
	class Produce {
	  public:
	    static Patch_vector_ptr LabPatches(Patch_vector_ptr XYZPatchList, XYZ_ptr white);
	};
	friend class Produce;
    };

};
#endif

