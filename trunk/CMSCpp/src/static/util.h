#ifndef UTILH
#define UTILH

//C系統文件

//C++系統文件
#include <string>
//其他庫頭文件
#include <boost/shared_ptr.hpp>
#include <boost/shared_array.hpp>
//本項目內頭文件

namespace util {
    using namespace std;
    using namespace boost;
    class Util {
      public:
	static shared_ptr < string > toString(wchar_t * wc);
	static shared_array < wchar_t > towchar_t(string & str);
    };
    class NameIF {
      public:
	virtual shared_ptr < string > getName() = 0;
    };

};
#endif

