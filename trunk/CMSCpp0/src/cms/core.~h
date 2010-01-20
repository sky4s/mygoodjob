#ifndef COREH
#define COREH
#include <vcl.h>
#include "static/util.h"
#include "static/java.h"
#include "colorspace/independ.h"

//using namespace util;
//using namespace java;
//using namespace cms;
//using cms::colorspace::CIExyY;

namespace cms {
    using namespace util;
    using namespace java;
    //using namespace cms;
    using namespace cms::colorspace;

    class SpectraIF {
      public:
	virtual double *getData() = 0;
	virtual int getEnd() = 0;
	virtual int getInterval() = 0;
	virtual int getStart() = 0;
    };

    class ColorMatchingFunction:public Object, SpectraIF {
    };

    enum CCTMethod {
	McCamyInt, McCamyFloat, Exp, ExpCCTOver50k, Robertson
    };

    class CorrelatedColorTemperature:public Object {
      public:
	static CIExyY CCT2BlackbodyxyY(int tempK);
	static CIExyY CCT2DIlluminantxyY(int tempK);
    };
    class DeltaE:public Object {
    };
    class Illuminant:public Object, SpectraIF {
    };
    class Patch:public Object, NameIF {
    };
    class Spectra:public Object, SpectraIF, NameIF {
    };
    class Target:public Object {
    };
};
#endif

