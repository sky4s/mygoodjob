#ifndef ANALYZERH
#define ANALYZERH

//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>

namespace ca210api {
    class CA210API;
};
namespace cms {
    namespace colorspace {
	namespace depend {
	    class Channel;
	    class RGBColor;
	};
	namespace independ {
	    class CIEXYZ;
	};

    };
    namespace measure {
	namespace meter {
	    class Meter;
	    class CA210;
	};
    };
};

namespace cms {

    namespace measure {

	class MeterMeasurement;
	class ComponentAnalyzerIF {
	  public:
	    bptr < Dep::RGBColor >
		getComponent(bptr < Dep::RGBColor > rgb);
	    void setupComponent(Dep::Channel & ch,
				bptr < Indep::CIEXYZ > XYZ);

	    void setupComponent(Dep::Channel & ch,
				bptr < Dep::RGBColor > rgb);
	};

	class CA210ComponentAnayzer:public jObject, ComponentAnalyzerIF {
	  private:
	    bptr < MeterMeasurement > mm;
	    bptr < cms::measure::meter::CA210 > ca210;
	    bptr < ca210api::CA210API > ca210api;
	  public:
	    CA210ComponentAnayzer(bptr < cms::measure::meter::CA210 >
				  ca210);

	    bptr < Dep::RGBColor >
		getComponent(bptr < Dep::RGBColor > rgb);
	    void setupComponent(Dep::Channel & ch,
				bptr < Dep::RGBColor > rgb);

	};
    };
};
#endif

