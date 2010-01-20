#ifndef UTILH
#define UTILH
#include <string>


namespace util {

    class Utils {

    };
    using std::string;
    class NameIF {
      public:
	virtual string& getName() = 0;
    };
};
#endif

