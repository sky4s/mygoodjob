#include "colorspace.h"
//#include <string>
namespace cms {

    namespace colorspace {
	using std::string;
	string ColorSpace::getName() {
	    return this->getClass().getSimpleName();
	}
    };
};

