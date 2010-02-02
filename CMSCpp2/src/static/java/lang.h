#ifndef LANGH
#define LANGH

//C系統文件

//C++系統文件
#include <string>
//其他庫頭文件
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>
//本項目內頭文件

//==============================================================================
// include template
//==============================================================================
//C系統文件

//C++系統文件

//其他庫頭文件

//本項目內頭文件
//==============================================================================

//==============================================================================
//簡化java.lang使用上的巨集
//==============================================================================
#define jObject java::lang::Object
//==============================================================================

//==============================================================================
//簡化boost::smart_ptr使用上的巨集
//==============================================================================
#define bptr boost::shared_ptr
#define barray boost::shared_array

#define double_vector std::vector < double >
#define string_vector std::vector < std::string >


#define double_vector_ptr bptr < double_vector >
#define nil_double_vector_ptr double_vector_ptr ((double_vector*)NULL)
#define nil_double_vector nil_double_vector_ptr
#define string_vector_ptr bptr < string_vector >


#define double_array barray <double>
#define nil_double_array double_array ((double*)NULL)
#define float_array barray <float>
#define nil_float_array float_array ((float*)NULL)

#define string_ptr bptr < std::string >
#define nil_string_ptr string_ptr ((std::string*)NULL)
#define object_ptr bptr < jObject >

#define foreach BOOST_FOREACH
//==============================================================================

//==============================================================================
//簡化cms使用上的巨集
//===============================================================================
#define Dep cms::colorspace::depend
#define Indep cms::colorspace::independ
#define RGB_ptr bptr < Dep::RGBColor >
#define xyY_ptr bptr < Indep::CIExyY >
#define XYZ_ptr bptr < Indep::CIEXYZ >

#define RGB_vector std::vector < Dep::RGBColor >
#define RGB_vector_ptr bptr < RGB_vector >

#define channel_vector std::vector < Dep::Channel >
#define channel_vector_ptr bptr < channel_vector >
//==============================================================================

namespace cms {
    class Patch;
    class Spectra;
    namespace colorformat {
	namespace logo {
	    class LogoFile;
	};
    };
    namespace colorspace {
	namespace depend {
	    class RGBColor;
	    class Channel;
	};
	namespace independ {
	    class CIExyY;
	    class CIEXYZ;
	};
    };
    namespace measure {
	class MeterMeasurement;
	namespace meter {
	    class Meter;
	    class CA210;
	};
    };
};

//==============================================================================


/*
 java->C++轉換原則

 *override+overload問題
 c++缺乏java的interface, 雖然可以pure virtual func代替,
 但是會遇到override+overload以及hide的問題. 且使用了多重繼承, 會引入虛擬繼承的問題.
 所以在不同類別有overload需求時盡量避免, 以更名解決; 不過要是有大量更名的需要,
 乾脆直接在子類別把被hide的func呼叫回來.

 *禁止使用指標及參考
 避免忘記delete的問題, 以smart_ptr替代指標

 *物件完全採用smart_ptr
 參考會有無法有NULL的狀況, 因此全採用smart_ptr, 作到類似gc的效果.
 NULL的smart_ptr產生方法為 shared_array < double >p(NULL);

 *原生型別陣列採用smart_ptr(shared_array)
 純粹採用vector的話, 雖然可以達到類似java array的特性, 但是作為local vector不能
 當作ref or ptr被傳出去, 否則可能會指向一個未知的空間.

 所以一般是建議採用shared_ptr<vector<>>, 但是這種作法會讓indent(程式碼格式化器) 出錯!
 因為現在用的indent是c專屬的, 他看不懂template的<< >>...會當作shift運算子.
 幾經測試之下, 本來決定用define就可以避掉indent的問題!

 但是畢竟是指標...要一直不斷的用(*)[]去取值 (不能用->[] 這種怪語法..), 太麻煩了,
  所以回頭用shared_array

*/


namespace java {
    namespace lang {
	class Object;

	class Class {
	  private:

	    friend class Object;
	    const std::type_info & info;
	     Object & object;
	     Class(Object & object);
	  public:
	     string_ptr getSimpleName();
	    string_ptr getName();
	};

	class Object {
	  private:
	    static int globalID;
	    const int objectID;
	    bool null;
	    Class c;
	  public:
	     bool equals(object_ptr obj);
	     Class & getClass();
	    int hashCode();
	    string_ptr toString();
	    bool isNull();
	     Object(bool null);
	     Object();
	     //Object(Object & o);
	    const int getObjectID();

	  protected:
	     object_ptr clone();
	    void finalize();
	};

	class Math {
	  public:
	    static double sqrt(double a);
	    static double pow(double a, double b);
	    static double atan2(double y, double x);
	    static const double PI;
	    static double cos(double x);
	    static double sin(double x);
	    static double sqr(double v);
	};


	class Exception:public Object {
	  public:
	    Exception();
	    Exception(std::string message);
	    std::string & toString();
	  private:
	    std::string message;
	};
	class RuntimeException:public Exception {
	  public:
	    RuntimeException();
	    RuntimeException(std::string message);
	};
	class IllegalStateException:public RuntimeException {
	  public:
	    IllegalStateException();
	    IllegalStateException(std::string message);
	};

	class IllegalArgumentException:public RuntimeException {
	  public:
	    IllegalArgumentException();
	    IllegalArgumentException(std::string message);
	};
    };
};
#endif

