#include "util.h"

namespace util {

    //==========================================================================
    // Util
    //==========================================================================
    using namespace std;
    using namespace boost;
     shared_ptr < string > Util::toString(wchar_t * wc) {
	size_t size = wcslen(wc);
	char *c = new char[size];
	for (size_t x = 0; x != size; x++) {
	    c[x] = wc[x];
	};
	shared_ptr < string > result(new string(c));
	return result;
    };
    shared_array < wchar_t > Util::towchar_t(string & str) {
	unsigned int size = str.size();

	//wchar_t *wc = new wchar_t[size + 1];
	shared_array < wchar_t > wc(new wchar_t[size + 1]);
	for (unsigned int x = 0; x != size; x++) {
	    wc[x] = str[x];
	}
	wc[size] = '\0';
	return wc;
    };

    wchar_t *Util::towchar_t2(std::string & str) {
	//char *cstr = str.c_str();
	const char *cstr = str.c_str();
	unsigned int size = str.size() + 1;
	wchar_t *wchar = new wchar_t[size];
	mbstowcs(wchar, cstr, size);
	return wchar;
	/*unsigned int size = str.size();
	   wchar_t *wc = new wchar_t[size + 1];
	   for (int x = 0; x != size; x++) {
	   wc[x] = str[x];
	   };
	   wc[size] = '\0';
	   return wc; */
    };
    //==========================================================================
};

