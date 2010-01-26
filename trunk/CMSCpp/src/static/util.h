#ifndef UTILH
#define UTILH

#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
#include <cwchar>

namespace util {
    using namespace std;
    using namespace boost;
    class Util {
      public:
	static shared_ptr < string > toString(wchar_t * wc) {
	    size_t size = wcslen(wc);
	    char *c = new char[size];
	    for (size_t x = 0; x != size; x++) {
		c[x] = wc[x];
	    };
	     shared_ptr < string > result(new string(c));
	     return result;
	};
	static shared_array < wchar_t > towchar_t(string & str) {
	    unsigned int size = str.size();

	    //wchar_t *wc = new wchar_t[size + 1];
	    shared_array < wchar_t > wc(new wchar_t[size + 1]);
	    for (unsigned int x = 0; x != size; x++) {
		wc[x] = str[x];
	    }
	    wc[size] = '\0';
	    return wc;
	};
    };
    class NameIF {
      public:
	virtual shared_ptr < string > getName() = 0;
    };

};
#endif

