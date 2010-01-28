#ifndef PATCHH
#define PATCHH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include <util.h>

namespace cms {

    class Spectra;
    namespace colorspace {
	namespace depend {
	    class RGBColor;
	};
	namespace independ {
	    class CIEXYZ;
	};
    };
};

namespace cms {

    /*using std::string;
       using namespace boost;
       using java::lang::Object;
       using util::NameIF;
       using cms::colorspace::RGBColor;
       using cms::colorspace::CIEXYZ; */

    class Patch:public java::lang::Object, util::NameIF {

      protected:
	bptr < std::string > name;
	//CIELab _Lab = null;
	bptr < Indep::CIEXYZ > XYZ;
	bptr < Indep::CIEXYZ > normalizedXYZ;
	bptr < Dep::RGBColor > rgb;
	//shared_ptr < RGBColor > originalRGB = null;
	bptr < Spectra > spectra;
	bptr < Spectra > reflectSpectra;
      public:
	Patch(bptr < std::string > name,
	      bptr < Indep::CIEXYZ > XYZ,
	      bptr < Indep::CIEXYZ > normalizedXYZ,
	      bptr < Dep::RGBColor > rgb);
	bptr < std::string > getName();
	bptr < Indep::CIEXYZ > getXYZ();
	bptr < Indep::CIEXYZ > getNormalizedXYZ();
	bptr < Dep::RGBColor > getRGB();
    };

};
#endif

