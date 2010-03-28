#include <includeall.h>
#pragma hdrstop
#include "util.h"

//C系統文件
#include <cstdarg>
//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace cms {
    namespace util {

	//==========================================================================
	// Util
	//==========================================================================
	using namespace std;
	using namespace boost;
	using namespace java::lang;
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

	    shared_array < wchar_t > wc(new wchar_t[size + 1]);
	    for (unsigned int x = 0; x != size; x++) {
		wc[x] = str[x];
	    }
	    wc[size] = '\0';
	    return wc;
	};

	wchar_t *Util::towchar_t2(std::string & str) {
	    const char *cstr = str.c_str();
	    unsigned int size = str.size() + 1;
	    wchar_t *wchar = new wchar_t[size];
	    mbstowcs(wchar, cstr, size);
	    return wchar;
	};



	void Util::deleteExist(const std::string & filename) {
	    const char *cstr = filename.c_str();
	    if (FileExists(cstr)) {
		DeleteFile(cstr);
	    }
	};

	bptr < WideString > Util::toWideString(const std::string & s) {
	    bptr < WideString > wstring(new WideString(s.c_str()));
	    return wstring;
	};


	//==========================================================================

	string_vector_ptr StringVector::fromCString(int count, ...) {
	    string_vector_ptr result(new string_vector());
	    va_list num_list;
	    va_start(num_list, count);

	    for (int i = 0; i < count; i++) {
		const char *c = va_arg(num_list, const char *);
		string str(c);
		result->push_back(str);
	    } va_end(num_list);
	    return result;
	};

	string_vector_ptr StringVector::fromString(int count, ...) {
	    string_vector_ptr result(new string_vector());
	    va_list num_list;
	    va_start(num_list, count);

	    for (int i = 0; i < count; i++) {
		const string str = va_arg(num_list, const string);
		result->push_back(str);
	    } va_end(num_list);
	    return result;
	};

	string_vector_ptr StringVector::fromString(int n,
						   const std::string *
						   strings) {
	    string_vector_ptr result(new string_vector(n));
	    for (int x = 0; x < n; x++) {
		(*result)[x] = strings[x];
	    } return result;
	};
	//======================================================================

	//======================================================================
	// ByteBuffer
	//======================================================================
      ByteBuffer::ByteBuffer(const unsigned int size):size(size) {
	    buffer = new unsigned char[size];
	};
	ByteBuffer::~ByteBuffer() {
	    delete[]buffer;
	};
	unsigned char &ByteBuffer::operator[] (const size_t index) {
	    if (index >= size) {
		throw IndexOutOfBoundsException();
	    }
	    return buffer[index];
	};
	const unsigned char &ByteBuffer::operator[] (const size_t index) const {
	    if (index >= size) {
		throw IndexOutOfBoundsException();
	    }
	    return buffer[index];
	};
	//======================================================================
    };
};

