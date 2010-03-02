#ifndef LANGH
#define LANGH

//C系統文件

//C++系統文件
#include <string>
#include <vector>
//#pragma hdrstop

//其他庫頭文件
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
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
#define null NULL
//==============================================================================

//==============================================================================
//簡化boost::smart_ptr使用上的巨集
//==============================================================================
#define bptr boost::shared_ptr
#define barray boost::shared_array
#define bptr_ boost::scoped_ptr

#define string_ptr bptr < std::string >
#define nil_string_ptr string_ptr ((std::string*)NULL)
#define Object_ptr bptr < jObject >

#define double_vector std::vector < double >
#define double_vector_ptr bptr < double_vector >
#define nil_double_vector_ptr double_vector_ptr ((double_vector*)NULL)
#define nil_double_vector nil_double_vector_ptr

#define int_vector std::vector < double >
#define int_vector_ptr bptr < int_vector >

#define string_vector std::vector < std::string >
#define string_vector_ptr bptr < string_vector >
#define stringp_vector std::vector < string_ptr >
#define stringp_vector_ptr bptr < string_ptr_vector >


#define double_array barray <double>
#define nil_double_array double_array ((double*)NULL)
#define float_array barray <float>
#define nil_float_array float_array ((float*)NULL)



#define foreach BOOST_FOREACH
//==============================================================================

//==============================================================================
//簡化cms使用上的巨集
//==============================================================================
#define Dep cms::colorspace::depend
#define Indep cms::colorspace::independ

#define RGB_ptr bptr < Dep::RGBColor >
#define RGB_array barray < RGB_ptr >
#define RGB_list std::list < RGB_ptr >
#define RGB_list_ptr bptr < RGB_list >
#define RGB_vector std::vector < RGB_ptr >
#define RGB_vector_ptr bptr < RGB_vector >

#define xyY_ptr bptr < Indep::CIExyY >
#define xyY_vector std::vector < xyY_ptr >
#define xyY_vector_ptr bptr < xyY_vector >

#define XYZ_ptr bptr < Indep::CIEXYZ >
#define XYZ_vector std::vector < XYZ_ptr >
#define XYZ_vector_ptr bptr < XYZ_vector >


#define channel_vector std::vector < Dep::Channel >
#define channel_vector_ptr bptr < channel_vector >

#define Patch_ptr bptr < cms::Patch >
#define Patch_list std::list < Patch_ptr >
#define Patch_list_ptr bptr < Patch_list >
#define Patch_vector std::vector < Patch_ptr >
#define Patch_vector_ptr bptr < Patch_vector >
//==============================================================================

//==============================================================================
//簡化tnt使用上的巨集
//==============================================================================
#define longdouble1D TNT::Array1D< long double >
#define longdouble2D TNT::Array2D< long double >
#define longdouble2D_ptr bptr< longdouble2D >

//#define _USE_LONG_DOUBLE_

#ifdef  _USE_LONG_DOUBLE_
#define double1D TNT::Array1D< long double >
#define double2D TNT::Array2D< long double >
#define double3D TNT::Array3D< long double >
#else
#define double1D TNT::Array1D< double >
#define double2D TNT::Array2D< double >
#define double3D TNT::Array3D< double >
#endif

#define double1D_ptr bptr< double1D >
#define double2D_ptr bptr< double2D >
#define double3D_ptr bptr< double3D >

#define float1D TNT::Array1D< float >
#define float2D TNT::Array2D< float >
#define float3D TNT::Array3D< float >
//==============================================================================


namespace cms {
    class Patch;
    class Spectra;
    namespace colorformat {
	namespace logo {
	    class LogoFile;
	};
	class ExcelFileDB;
    };
    namespace colorspace {
	namespace depend {
	    class RGBColor;
	    class Channel;
	    class RGBColorSpace;
	};
	namespace independ {
	    class CIExyY;
	    class CIEXYZ;
	};
    };
    namespace lcd {
	namespace calibrate {
	    class LCDCalibrator;
	    namespace algo {
		class ChromaticAroundAlgorithm;
		class CIEuv1960NearestAlgorithm;
	    };
	};
    };
    namespace measure {
	class MeterMeasurement;
	class MeasureResult;
	class ComponentAnalyzerIF;
	namespace cp {
	    class MeasureInterface;
	};
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
 避免忘記delete的問題, 以smart_ptr替代指標.
 例外的是, string當作常數的狀況下, 可以const string &使用.

 *物件完全採用smart_ptr
 參考會有無法有NULL的狀況, 因此全採用smart_ptr, 作到類似gc的效果.
 NULL的smart_ptr產生方法為 shared_array < double >p(NULL);

 *原生型別陣列採用 長度固定: shared_ptr(shared_array)
                   長度不定: shared_ptr< vector<> >
 純粹採用vector的話, 雖然可以達到類似java array的特性, 但是作為local vector不能
 當作ref or ptr被傳出去, 否則可能會指向一個未知的空間.

 所以一般是建議採用shared_ptr< vector<> >, 但是這種作法會讓indent(程式碼格式化器) 出錯!
 因為現在用的indent是c專屬的, 他看不懂template的<< >>...會當作shift運算子.
 幾經測試之下, 本來決定用define就可以避掉indent的問題!

 但是畢竟是指標...要一直不斷的用(*)[]去取值 (不能用->[] 這種怪語法..), 太麻煩了,
 所以回頭用shared_array.

 糟糕的是, shared_array沒辦法知道自己的長度!
 因此java中的double[]盡量以shared_ptr< vector<> >替代.
 而List<>也已vector<>替代, 因為java中用的List<>是以ArrayList實作,
 其特性其實比較接近STL的vector.

 *是否還要使用陣列?(嚴格來說是指向複數元素的指標)
 採用share_array後可以不用管理陣列的釋放(其實不是陣列, 嚴格來說是指標).
 但是share_array缺乏長度資訊, 需要自己維護長度, share_array佔掉8byte.
 採用vector+bptr後, 不用管理資源且知道長度, 但是vector本身佔掉24byte.
 double指標佔掉4byte最少, 但是功能最貧乏.
 
 要是元素少但是會有大量實體產生, 選用share_array.
 要是實體不多, 則選用vector+bptr.
 若不知道實體多寡, 選用保險的vector+bptr.

 何時選用share_array: 長度不變動, 長度已知, 會有大量實體, 元素少
 何時選用vector+bptr: 長度會變動, 長度未知, 不會有大量實體

 *enum 與 Enumeration
 enum是c++內建, 功能很弱, 基本上只是一個常數代換而已.
 但如果不需複雜的功能, 其實enum夠了.
 要是enum需要跨class使用的時候, 建議採用擴充型的Enumeration().
 定義方法為: Enumeration(enum_name)
              item1=value, item2=value, ...
             EnumerationEnd();
 可以 Enumeration::item1使用, 較好辨識.
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
	    const string_ptr getSimpleName();
	    const string_ptr getName();
	};

	class Object {
	  private:
	    static int globalID;
	    const int objectID;
	    bool _null;
	    Class c;
	  public:
	    const bool equals(Object_ptr obj);
	     Class & getClass();
	    const int hashCode();
	    const string_ptr toString();
	    const bool isNull();
	     Object(bool _null);
	     Object();
	    const int getObjectID();

	  protected:
	     Object_ptr clone();
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
	    static double round(double v);

	    static double min(double a, double b);
	    static double max(double a, double b);

	    static int maxIndex(double_array values, int n);
	    static int minIndex(double_array values, int n);
	    static int maxIndex(double_vector_ptr values);
	    static int minIndex(double_vector_ptr values);
	};

        /*
          *例外體系
           完全仿製java例外體系, Exception為最上層類別, 其底下有RuntimeException.
           而RuntimeException下又有最常用的幾種例外.
        */
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
	class UnsupportedOperationException:public RuntimeException {
	  public:
	    UnsupportedOperationException();
	    UnsupportedOperationException(std::string message);
	};
	class IndexOutOfBoundsException:public RuntimeException {
	  public:
	    IndexOutOfBoundsException();
	    IndexOutOfBoundsException(std::string message);
	};

    };
};


#define Enumeration(E) \
struct E \
{ \
public: \
     E(int value = 0) : _value((__Enum)value) { \
     } \
     E& operator=(int value) { \
         this->_value = (__Enum)value; \
         return *this; \
     } \
     operator int() const { \
         return this->_value; \
     } \
\
     enum __Enum {

#define EnumerationEnd() \
     }; \
\
private: \
     __Enum _value; \
};

#endif

