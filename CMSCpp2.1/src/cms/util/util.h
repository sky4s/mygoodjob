#ifndef UTILH
#define UTILH

//C�t�Τ��

//C++�t�Τ��

//��L�w�Y���


//�����ؤ��Y���
#include <debug.h>

namespace cms {
    namespace util {
	using namespace std;
	using namespace boost;
	class Util {
	  public:
	    static string_ptr toString(wchar_t * wc);
	    static template < typename T > const string Util::toString(const T t) {
		return _toString(t);
	    };
	    static boost::shared_array < wchar_t > towchar_t(std::string & str);
	    static wchar_t *towchar_t2(std::string & str);
	    static void deleteExist(const std::string & filename);
	    static void deleteExist(const char *filename);
	    static void deleteExist(const WideString & filename);
	    static bool isFileExist(const std::string & filename);
	    static bptr < WideString > toWideString(const std::string & s);
	    static void shellExecute(const std::string & filename);
#if defined(EXCEL_ACCESSIBLE) && defined(COLORSPACE)
	    static void storeXYZxyVector(const std::string & filename, XYZ_vector_ptr XYZVector);
	    static void storeXYZxyVector(const std::string & filename,
					 XYZ_vector_ptr XYZVector, const std::string firstColumn);
#endif

	    static void sleep(int waitTimes);
#if defined(LCD_DEVICE)
	    static Component_vector_ptr copy(Component_vector_ptr src);
#endif
	    static string getCurrentDirectory();
	    static int_array fetchVersionInfo();
	};

	class StringVector {
	  public:
	    static string_vector_ptr fromCString(int count, ...);
	    static string_vector_ptr fromString(int count, ...);
	    static string_vector_ptr fromString(int n, const std::string * strings);
	    static string_vector_ptr fromDouble(int count, ...);
#ifdef TNT_LIB
	    static string_vector_ptr fromDoubleArray(double1D_ptr doubleArray);
	    static string_vector_ptr fromDoubleArray(double2D_ptr doubleArray, int n);
#endif
	    static void setContent(string_vector_ptr vector,
				   const std::string & content, int n, ...);
	    static string_vector_ptr tokenize(const std::string & content,
					      const std::string & delim);
	    static string_vector_ptr fromTextFile(const std::string & filename);
	    static bptr < TStringList > getTStringListFromTextFile(const std::string & filename);

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
	    bool equals(bptr < ByteBuffer > compare);
	};


	class DoubleBufferedCanvas {
	  private:
	    TCanvas * canvas;
	    int width, height;
	     bptr < Graphics::TBitmap > bitmap;
	    const bool doubleBuffered;
	  public:
	    static void copy(TCanvas * source, TCanvas * dest, int width, int height);
	    static bptr < Graphics::TBitmap > getTBitmap(TCanvas * canvas, int width, int height);
	     DoubleBufferedCanvas(TCanvas * canvas, int width, int height);
	    TCanvas *getDoubleBufferedCanvas();
	    void excute();
	    void clear();
	    void setSize(int width, int height);
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

	class CallBackIF {
	  public:virtual void callback() = 0;
	};

    };
};
#endif

