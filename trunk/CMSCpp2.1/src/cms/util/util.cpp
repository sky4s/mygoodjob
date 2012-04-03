#include <includeall.h>
#pragma hdrstop
#include "util.h"

//C系統文件
#include <cstdarg>
#include <dir.h>
//C++系統文件

//其他庫頭文件
#include <boost/tokenizer.hpp>

//本項目內頭文件
//#include <debug.h>

namespace cms {
    namespace util {

	//==========================================================================
	// Util
	//==========================================================================
	using namespace std;
	using namespace boost;
	using namespace java::lang;
	using namespace cms::colorformat;
	string_ptr Util::toString(wchar_t * wc) {
	    size_t size = wcslen(wc);
	    char *c = new char[size];
	    for (size_t x = 0; x != size; x++) {
		c[x] = wc[x];
	    };
	    string str = c;
	    string_ptr result(new string(str));
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
	    deleteExist(filename.c_str());
	};

	void Util::deleteExist(const char *filename) {
	    if (FileExists(filename)) {
		DeleteFile(filename);
	    }
	};

	void Util::deleteExist(const WideString & filename) {
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
	    ShellExecute(null, null, filename.c_str(), null, null, SW_SHOW);
	};
#if defined(EXCEL_ACCESSIBLE) && defined(COLORSPACE)
	void Util::storeXYZxyVector(const std::string & filename, XYZ_vector_ptr XYZVector) {
	    storeXYZxyVector(filename, XYZVector, "Gray Level");
	};

	void Util::storeXYZxyVector(const std::string & filename,
				    XYZ_vector_ptr XYZVector, const std::string firstColumn) {
	    Util::deleteExist(filename);
	    SimpleExcelAccess excel(filename, Create,
				    StringVector::
				    fromCString(6, firstColumn.c_str(), "X", "Y", "Z", "_x", "_y"));
	    int size = XYZVector->size();
	    for (int x = 0; x != size; x++) {
		XYZ_ptr XYZ = (*XYZVector)[x];

		Indep::CIExyY xyY(XYZ);
		string_vector_ptr values = StringVector::fromDouble
		    (6, static_cast < double >(x), XYZ->X, XYZ->Y,
		     XYZ->Z, xyY.x, xyY.y);
		excel.insert(values);
	    }

	};
#endif

	void Util::sleep(int waitTimes) {
	    int count = waitTimes / 100;
	    for (int x = 0; x < count; x++) {
		Sleep(100);
		Application->ProcessMessages();
	    }
	};
#if defined(LCD_DEVICE)
	Component_vector_ptr Util::copy(Component_vector_ptr src) {
	    using namespace cms::lcd::calibrate;
	    int size = src->size();
	    Component_vector_ptr result(new Component_vector(size));
	    for (int x = 0; x < size; x++) {
		Component_ptr c = (*src)[x];
		Component_ptr newc(new Component(c));
		(*result)[x] = newc;
	    }

	    return result;
	};
#endif
	string Util::getCurrentDirectory() {
	    char curdir[MAXPATH];

	    strcpy(curdir, "X:\\");	/* fill string with form of response: X:\ */
	    curdir[0] = 'A' + getdisk();	/* replace X with current drive letter */
	    getcurdir(0, curdir + 3);	/* fill rest of string with current directory */
            string result = curdir;
	    return result;
	    /*string result(curdir);
	       return result; */

	};


	//=====================================================================
	// 擷取app的檔案資訊
	//=====================================================================
	int_array Util::fetchVersionInfo() {

	    DWORD dwVerInfoSize = GetFileVersionInfoSize(Application->ExeName.c_str(), null);
	    if (dwVerInfoSize > 0) {
		BYTE *bVerInfoBuf = new BYTE[dwVerInfoSize];
		if (GetFileVersionInfo(Application->ExeName.c_str(), 0, dwVerInfoSize, bVerInfoBuf)) {
		    VS_FIXEDFILEINFO *vsInfo;
		    UINT vsInfoSize;

		    if (VerQueryValue(bVerInfoBuf, "\\", (void **) &vsInfo, &vsInfoSize)) {
			int_array version(new int[4]);
			int iFileVerMajor = HIWORD(vsInfo->dwFileVersionMS);
			int iFileVerMinor = LOWORD(vsInfo->dwFileVersionMS);
			int iFileVerRelease = HIWORD(vsInfo->dwFileVersionLS);
			int iFileVerBuild = LOWORD(vsInfo->dwFileVersionLS);
			version[0] = iFileVerMajor;
			version[1] = iFileVerMinor;
			version[2] = iFileVerRelease;
			version[3] = iFileVerBuild;
			delete[]bVerInfoBuf;
			return version;
		    }
		    delete[]bVerInfoBuf;
		}
	    }
	    return nil_int_array;
	};
	//=====================================================================
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

	string_vector_ptr StringVector::fromString(int n, const std::string * strings) {
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
#ifdef TNT_LIB
	string_vector_ptr StringVector::fromDoubleArray(double1D_ptr doubleArray) {

	    string_vector_ptr result(new string_vector());
	    int size = doubleArray->dim1();
	    for (int x = 0; x < size; x++) {
		result->push_back(_toString((*doubleArray)[x]));
	    }

	    return result;
	};
	string_vector_ptr StringVector::fromDoubleArray(double2D_ptr doubleArray, int n) {

	    string_vector_ptr result(new string_vector());
	    int size = doubleArray->dim2();
	    for (int x = 0; x < size; x++) {
		result->push_back(_toString((*doubleArray)[n][x]));
	    }
	    return result;
	};
#endif
	void StringVector::setContent(string_vector_ptr vector,
				      const std::string & content, int n, ...) {
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
						 string & content, const std::string & delim) {
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

	string_vector_ptr StringVector::fromTextFile(const std::string & filename) {
	    string_vector_ptr result(new string_vector());
	    bptr < TStringList > list = getTStringListFromTextFile(filename);
	    for (int i = 0; i < list->Count; i++) {
		String str = list->Strings[i];
		result->push_back(str.c_str());
	    }
	    return result;
	};

	bptr < TStringList > StringVector::getTStringListFromTextFile(const std::string & filename) {
	    bptr < TStringList > list(new TStringList());
	    list->LoadFromFile(filename.c_str());
	    return list;
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
	bool ByteBuffer::equals(bptr < ByteBuffer > compare) {
	    if (size != compare->size) {
		throw IllegalStateException("size is not match");
	    }
	    for (unsigned int x = 0; x < size; x++) {
		if ((*this)[x] != (*compare)[x]) {
		    return false;
		}
	    }
	    return true;
	};
	//======================================================================

	//======================================================================
	//
	//======================================================================
      DoubleBufferedCanvas::DoubleBufferedCanvas(TCanvas * canvas, int width, int height):canvas(canvas), width(width),
	    height(height),
	    doubleBuffered(true) {
	    if (doubleBuffered) {
		bitmap = getTBitmap(canvas, width, height);
		/*bitmap = bptr < Graphics::TBitmap > (new Graphics::TBitmap());
		   bitmap->Canvas->Handle = CreateCompatibleDC(canvas->Handle);
		   bitmap->Width = width;
		   bitmap->Height = height; */
	    }
	};

	bptr < Graphics::TBitmap > DoubleBufferedCanvas::getTBitmap(TCanvas * canvas, int width,
								    int height) {
	    bptr < Graphics::TBitmap > bitmap(new Graphics::TBitmap());
	    bitmap->Canvas->Handle = CreateCompatibleDC(canvas->Handle);
	    bitmap->Width = width;
	    bitmap->Height = height;
	    return bitmap;
	};
	TCanvas *DoubleBufferedCanvas::getDoubleBufferedCanvas() {
	    if (doubleBuffered) {
		return bitmap->Canvas;
	    } else {
		return canvas;
	    }
	};
	void DoubleBufferedCanvas::copy(TCanvas * source, TCanvas * dest, int width, int height) {
	    BitBlt(dest->Handle, 0, 0, width, height, source->Handle, 0, 0, SRCCOPY);
	}
	void DoubleBufferedCanvas::excute() {
	    if (doubleBuffered) {
		copy(bitmap->Canvas, canvas, width, height);
		//BitBlt(canvas->Handle, 0, 0, width, height, bitmap->Canvas->Handle, 0, 0, SRCCOPY);
	    }
	};
	void DoubleBufferedCanvas::clear() {
	    if (doubleBuffered) {
		TCanvas *canvas = bitmap->Canvas;
		canvas->Brush->Color = clBlack;
		canvas->FillRect(TRect(0, 0, width, height));
	    }
	};
	void DoubleBufferedCanvas::setSize(int width, int height) {
	    this->width = width;
	    this->height = height;
	    bitmap->Width = width;
	    bitmap->Height = height;
	};
	//======================================================================

	double SCurve::getAbsoluteInput(double normalizeInput) {
	    return (end - start) * normalizeInput + start;
	};
	double SCurve::sigmoidFunction(double t) {
	    return 1. / (1 + Math::exp(-t));
	};
      SCurve::SCurve(double start, double end):start(start), end(end) {
	    startValue = sigmoidFunction(start);
	    endValue = sigmoidFunction(end);
	};
	double SCurve::getValue(double normalizeInput) {
	    double abs = getAbsoluteInput(normalizeInput);
	    double value = sigmoidFunction(abs);
	    return (value - startValue) / (endValue - startValue);
	};
    };
};

