#include <includeall.h>
#pragma hdrstop
#include "util.h"

//C系統文件
#include <cstdarg>
//C++系統文件

//其他庫頭文件
#include <boost/tokenizer.hpp>
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
	    //const char *cstr = filename.c_str();
	    /*if (FileExists(cstr)) {
	       DeleteFile(cstr);
	       } */
	    deleteExist(filename.c_str());
	};

	void Util::deleteExist(const char *filename) {
	    //const char *cstr = filename.c_str();
	    if (FileExists(filename)) {
		DeleteFile(filename);
	    }
	};

	void Util::deleteExist(const WideString & filename) {
	    //const char *cstr = filename.c_str();
	    if (FileExists(filename)) {
		DeleteFile(filename);
	    }
	};


	bool Util::isFileExist(const std::string & filename) {
	    return FileExists(filename.c_str());
	}

	bptr < WideString > Util::toWideString(const std::string & s) {
	    bptr < WideString > wstring(new WideString(s.c_str()));
	    return wstring;
	};

	void Util::shellExecute(const std::string & filename) {
	    ShellExecute(null, null, filename.c_str(), null, null,
			 SW_SHOW);
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
	string_vector_ptr StringVector::fromDouble(int count, ...) {
	    string_vector_ptr result(new string_vector());
	    va_list num_list;
	    va_start(num_list, count);

	    for (int i = 0; i < count; i++) {
		const double d = va_arg(num_list, const double);
		const string & str = _toString(d);
		result->push_back(str);
	    } va_end(num_list);
	    return result;
	};
	string_vector_ptr StringVector::
	    fromDoubleArray(double1D_ptr doubleArray) {

	    string_vector_ptr result(new string_vector());
	    int size = doubleArray->dim1();
	    for (int x = 0; x < size; x++) {
		result->push_back(_toString((*doubleArray)[x]));
	    }

	    return result;
	};
	string_vector_ptr StringVector::
	    fromDoubleArray(double2D_ptr doubleArray, int n) {

	    string_vector_ptr result(new string_vector());
	    int size = doubleArray->dim2();
	    for (int x = 0; x < size; x++) {
		result->push_back(_toString((*doubleArray)[n][x]));
	    }
	    return result;
	};
	void StringVector::setContent(string_vector_ptr vector,
				      const std::string & content,
				      int n, ...) {
	    //int_array result(new int[n]);
	    va_list num_list;
	    va_start(num_list, n);

	    for (int i = 0; i < n; i++) {
		const int d = va_arg(num_list, const int);
		//result[i] = d;
		(*vector)[d] = content;
	    } va_end(num_list);
	};
	string_vector_ptr StringVector::tokenize(const std::
						 string & content,
						 const std::
						 string & delim) {
	    string_vector_ptr result(new string_vector());
#define TOKENIZER boost::tokenizer < boost::char_separator < char > >
	    boost::char_separator < char >sep(delim.c_str());
	    TOKENIZER tokens(content, sep);
	    for (TOKENIZER::iterator tok_iter = tokens.begin();
		 tok_iter != tokens.end(); ++tok_iter) {
		result->push_back(*tok_iter);
	    }
	    return result;
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

