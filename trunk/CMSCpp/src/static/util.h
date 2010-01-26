#ifndef UTILH
#define UTILH
#include <string>
#include <boost/shared_ptr.hpp>

namespace util {
 
    using namespace std;
    using namespace boost;
    class NameIF {
      public:
	virtual shared_ptr < string > getName() = 0;
    };
};
#endif

