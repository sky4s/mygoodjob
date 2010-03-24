#ifndef PATCHH
#define PATCHH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <cms/util/util.h>
#include <java/lang.h>

namespace cms {
    class Patch:public jObject, cms::util::NameIF {

      protected:
	bptr < std::string > name;
	//CIELab _Lab = null;
	XYZ_ptr XYZ;
	XYZ_ptr normalizedXYZ;
	RGB_ptr rgb;
	//shared_ptr < RGBColor > originalRGB = null;
	bptr < Spectra > spectra;
	bptr < Spectra > reflectSpectra;
      public:
	Patch(bptr < std::string > name,
	      XYZ_ptr XYZ,
	      XYZ_ptr normalizedXYZ,
	      RGB_ptr rgb);
	bptr < std::string > getName();
	XYZ_ptr getXYZ();
	XYZ_ptr getNormalizedXYZ();
	RGB_ptr getRGB();
    };

};
#endif

