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
	class RGBColor;
	class CIEXYZ;
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
	boost::shared_ptr < std::string > name;
	//CIELab _Lab = null;
	boost::shared_ptr < cms::colorspace::CIEXYZ > XYZ;
	boost::shared_ptr < cms::colorspace::CIEXYZ > normalizedXYZ;
	boost::shared_ptr < cms::colorspace::RGBColor > rgb;
	//shared_ptr < RGBColor > originalRGB = null;
	boost::shared_ptr < Spectra > spectra;
	boost::shared_ptr < Spectra > reflectSpectra;
      public:
	Patch(boost::shared_ptr < std::string > name,
	      boost::shared_ptr < cms::colorspace::CIEXYZ > XYZ,
	      boost::shared_ptr < cms::colorspace::CIEXYZ > normalizedXYZ,
	      boost::shared_ptr < cms::colorspace::RGBColor > rgb);
	boost::shared_ptr < std::string > getName();
	boost::shared_ptr < cms::colorspace::CIEXYZ > getXYZ();
	boost::shared_ptr < cms::colorspace::CIEXYZ > getNormalizedXYZ();
	boost::shared_ptr < cms::colorspace::RGBColor > getRGB();
    };

};
#endif

