#ifndef UTILH
#define UTILH

//C系統文件

//C++系統文件

//其他庫頭文件


//本項目內頭文件
#include <debug.h>

namespace cms {
    namespace util {
	using namespace std;
	using namespace boost;
	class Util {
	  public:
	    static string_ptr toString(wchar_t * wc);
	    static template < typename T >
		const string Util::toString(const T t) {
		return _toString(t);
	    };
	    static boost::shared_array < wchar_t >
		towchar_t(std::string & str);
	    static wchar_t *towchar_t2(std::string & str);
	    static void deleteExist(const std::string & filename);
	    static void deleteExist(const char *filename);
	    static void deleteExist(const WideString & filename);
	    static bool isFileExist(const std::string & filename);
	    static bptr < WideString > toWideString(const std::string & s);
	    static void shellExecute(const std::string & filename);
#ifdef EXCEL_ACCESSIBLE
	    static void storeXYZxyVector(const std::string & filename,
					 XYZ_vector_ptr XYZVector);
	    static void storeXYZxyVector(const std::string & filename,
					 XYZ_vector_ptr XYZVector,
					 const std::string firstColumn);
#endif
	};

	class StringVector {
	  public:
	    static string_vector_ptr fromCString(int count, ...);
	    static string_vector_ptr fromString(int count, ...);
	    static string_vector_ptr fromString(int n,
						const std::string *
						strings);
	    static string_vector_ptr fromDouble(int count, ...);
	    static string_vector_ptr fromDoubleArray(double1D_ptr
						     doubleArray);
	    static string_vector_ptr fromDoubleArray(double2D_ptr
						     doubleArray, int n);
	    static void setContent(string_vector_ptr vector,
				   const std::string & content, int n,
				   ...);
	    static string_vector_ptr tokenize(const std::string & content,
					      const std::string & delim);
	};
	class NameIF {
	  public:
	    virtual string_ptr getName() = 0;
	};
	class ByteBuffer {
	  private:
	    const unsigned int size;
	  public:
	    unsigned char *buffer;
	     ByteBuffer(const unsigned int size);
	    ~ByteBuffer();
	    inline const int getSize() const {
		return size;
	    };
	    unsigned char &operator[] (const size_t index);
	    const unsigned char &operator[] (const size_t index) const;
	};
	class WindowListener {
	  public:
	    virtual void windowClosing() = 0;
	};

	class DoubleBufferedCanvas {
	  private:
	    TCanvas * canvas;
	    const int width, height;
	     bptr < Graphics::TBitmap > bitmap;
	    const bool doubleBuffered;
	  public:
	     DoubleBufferedCanvas(TCanvas * canvas, int width, int height);
	    TCanvas *getDoubleBufferedCanvas();
	    void excute();
	    void clear();
	};
	class SCurve {
	  private:
	    double start, end;
	    double startValue, endValue;
	    double getAbsoluteInput(double normalizeInput);
	    double sigmoidFunction(double t);
	  public:
	     SCurve(double start, double end);
	    double getValue(double normalizeInput);
	};
	class UIBinder {
	};
    };
};
#endif

