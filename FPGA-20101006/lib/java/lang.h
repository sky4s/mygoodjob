#ifndef LANGH
#define LANGH
//==============================================================================
// include template
//==============================================================================
//C系統文件

//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件

//本項目內gui頭文件
//==============================================================================
//C系統文件

//C++系統文件
#ifdef __BORLANDC__
# pragma pack(push, 8)
#endif
#include <string>
#include <vector>
#include <exception>

//其他庫頭文件
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#define TNT_LIB

#ifdef TNT_LIB
#include <tnt/tnt_array1d.h>
#include <tnt/tnt_array2d.h>
#include <tnt/tnt_array3d.h>
#endif

#ifdef __BORLANDC__
# pragma pack(pop)
#endif


//本項目內頭文件


//==============================================================================
// change the byte alignment macro
//==============================================================================
#include <vcl.h>
#ifdef __BORLANDC__
# pragma pack(push, 8)
#endif

#ifdef __BORLANDC__
# pragma pack(pop)
#endif
//==============================================================================

//==============================================================================
// 預先宣告, 可以減少include .h的需要
//==============================================================================
namespace java {
    namespace lang {
	class Object;
    };
};

namespace math {
    class Interpolation1DLUT;
    class DoubleArray;
    class FloatArray;
};

namespace i2c {
    class TestRGBBit;
    class i2cControl;
    class TCONParameter;
    class TCONControl;
};


namespace gui {
    namespace util {
	class UIValueSetter;
	class MultiUIBinder;
    };
    namespace event {
	class EventListener;
	class WindowListener;
	class WindowAdapter;
	class ChangeListener;
	class ListSelectionListener;
    };
};

//==============================================================================
//==============================================================================
//簡化java.lang使用上的巨集
//==============================================================================
//#define jObject java::lang::Object
typedef java::lang::Object jObject;
#define null NULL
//==============================================================================

//==============================================================================
//簡化boost::smart_ptr使用上的巨集
//==============================================================================
#define bptr boost::shared_ptr
#define barray boost::shared_array
#define bwptr boost::weak_ptr
//scope內用smart_ptr
#define bptr_ boost::scoped_ptr

#define Object_ptr bptr < jObject >
typedef bptr < std::string > string_ptr;
typedef bptr < AnsiString > String_ptr;
#define nil_string_ptr string_ptr ((std::string*)NULL)

typedef std::vector < int >int_vector;
typedef bptr < int_vector > int_vector_ptr;

typedef std::vector < bool > bool_vector;
typedef bptr < bool_vector > bool_vector_ptr;

#define nil_double_vector_ptr double_vector_ptr ((double_vector*)NULL)
#define nil_double_vector nil_double_vector_ptr
typedef std::vector < double >double_vector;
typedef bptr < double_vector > double_vector_ptr;

typedef std::vector < std::string > string_vector;
typedef bptr < string_vector > string_vector_ptr;
typedef std::vector < string_ptr > stringp_vector;
typedef bptr < stringp_vector > stringp_vector_ptr;
typedef std::vector < string_vector_ptr > string_doublevector;
typedef bptr < string_doublevector > string_doublevector_ptr;

typedef bptr < gui::util::UIValueSetter > uiset_ptr;
typedef bptr < gui::util::MultiUIBinder > mbinder_ptr;

typedef barray < double >double_array;
#define nil_double_array double_array ((double*)NULL)
typedef barray < float >float_array;
#define nil_float_array float_array ((float*)NULL)
typedef barray < int >int_array;
#define nil_int_array int_array ((int*)NULL)

//boost提供的foreach, 若要對vector<int> ivec做foreach, 語法為: foreach(const int & i, ivec) { ... }
#define foreach BOOST_FOREACH
//==============================================================================

//==============================================================================
//簡化tnt使用上的巨集
//==============================================================================
#ifdef TNT_LIB
typedef TNT::Array1D < long double >longdouble1D;
typedef TNT::Array2D < long double >longdouble2D;
typedef bptr < longdouble2D > longdouble2D_ptr;

//#define _USE_LONG_DOUBLE_

#ifdef  _USE_LONG_DOUBLE_
typedef TNT::Array1D < long double >double1D;
typedef TNT::Array2D < long double >double2D;
typedef TNT::Array3D < long double >double3D;
#else
typedef TNT::Array1D < double >double1D;
typedef TNT::Array2D < double >double2D;
typedef TNT::Array3D < double >double3D;
#endif

typedef bptr < double1D > double1D_ptr;
typedef bptr < double2D > double2D_ptr;
typedef bptr < double3D > double3D_ptr;

typedef TNT::Array1D < float >float1D;
typedef TNT::Array2D < float >float2D;
typedef TNT::Array3D < float >float3D;
typedef bptr < float1D > float1D_ptr;
typedef bptr < float2D > float2D_ptr;
typedef bptr < float3D > float3D_ptr;
#endif
//==============================================================================

//==============================================================================
// 簡化lexical使用上的巨集
//==============================================================================
#define _toString boost::lexical_cast < std::string >
#define _toInt boost::lexical_cast < int >
#define _toDouble boost::lexical_cast < double >
#define _toAnsiString(s)\
        AnsiString(s.c_str())
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
	    const string_ptr getSimpleName() const;
	    const string_ptr getName() const;
	};

	class Object /*:public TObject */  {
	  private:
	    //用來計量產生的物件數
	    static int globalID;
	    //用來記錄目前物件的ID
	    const int objectID;
	    bool null_;
	    const Class c;
	  public:
	    const bool equals(Object_ptr obj);
	    const Class & getClass() const;
	    const int hashCode();
	    const string_ptr toString() const;
	    const bool isNull();
	    Object(bool null_);
	    Object();
	    const int getObjectID();

	  protected:
	    Object_ptr clone();
	    void finalize();
	};

	class Math {
	  public:
	    static double abs(double a);
	    static double sqrt(double a);
	    static double pow(double a, double b);
	    static double atan2(double y, double x);
	    static const double PI;
	    static const double E;
	    static double cos(double x);
	    static double acos(double x);
	    static double sin(double x);
	    static double sqr(double v);
	    static double round(double v);
	    static double floor(double v);
	    static double roundTo(double v);
	    static double log(double v);
	    static double fmod(double x, double y);

	    static double min(double a, double b);
	    static double max(double a, double b);
#ifdef TNT_LIB
	    static double max(double1D_ptr values);
#endif

	    static int maxIndex(double_array values, int n);
	    static int minIndex(double_array values, int n);
	    static int maxIndex(double_vector_ptr values);
	    static int minIndex(double_vector_ptr values);
	    static double max(double_vector_ptr values);
	    static double min(double_vector_ptr values);

	    static double_vector_ptr normalize(double_vector_ptr original, double normal);
	    static double cubeRoot(double x);
	    static double exp(double x);
	    static double atan2deg(double b, double a);
	};

	/*
	 *例外體系
	 完全仿製java例外體系, Exception為最上層類別, 其底下有RuntimeException.
	 而RuntimeException下又有最常用的幾種例外.
	 */
	class Exception:public Object, std::exception {
	  public:
	    Exception();
	    Exception(std::string message);
	    std::string & toString();
	  private:
	    std::string message;
	};


	class RuntimeException:public Exception /*, std::runtime_error */  {
	  public:
	    RuntimeException();
	    RuntimeException(std::string message);
	};
	class IllegalStateException:public RuntimeException {
	  public:
	    IllegalStateException();
	    IllegalStateException(std::string message);
	};

	class IllegalArgumentException:public RuntimeException	/*,
								   std::invalid_argument */  {
	  public:
	    IllegalArgumentException();
	    IllegalArgumentException(std::string message);
	};
	class UnsupportedOperationException:public RuntimeException {
	  public:
	    UnsupportedOperationException();
	    UnsupportedOperationException(std::string message);
	};
	class IndexOutOfBoundsException:public RuntimeException	/*,
								   std::range_error */  {
	  public:
	    IndexOutOfBoundsException();
	    IndexOutOfBoundsException(std::string message);
	};
    };
};

//==============================================================================
// 擴充型enum
//==============================================================================
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
//==============================================================================

//==============================================================================
// Property類別
// http://www.codeguru.com/cpp/cpp/cpp_mfc/article.php/c4031/
//==============================================================================
#define READ_ONLY 1
#define WRITE_ONLY 2
#define READ_WRITE 3

template < typename Container, typename ValueType, int nPropType > class Property {
  public:
    Property() {
	m_cObject = NULL;
	Set = NULL;
	Get = NULL;
    }
//-- This to set a pointer to the class that contain the//   property --
	void setContainer(Container * cObject) {
	m_cObject = cObject;
    }
//-- Set the set member function that will change the value --
    void setter(void (Container::*pSet) (ValueType value)) {
	if ((nPropType == WRITE_ONLY) || (nPropType == READ_WRITE))
	    Set = pSet;
	else
	    Set = NULL;
    }
//-- Set the get member function that will retrieve the value --
    void getter(ValueType(Container::*pGet) ()) {
	if ((nPropType == READ_ONLY) || (nPropType == READ_WRITE))
	    Get = pGet;
	else
	    Get = NULL;
    }
//-- Overload the '=' sign to set the value using the set
//   member --
    ValueType operator =(const ValueType & value) {
	assert(m_cObject != NULL);
	assert(Set != NULL);
	(m_cObject->*Set) (value);
	return value;
    }
//-- To make possible to cast the property class to the
//   internal type --
    operator                                         ValueType() {
	assert(m_cObject != NULL);
	assert(Get != NULL);
	return (m_cObject->*Get) ();
    }
  private:
    Container * m_cObject;	//-- Pointer to the module that
    //   contains the property --
    void (Container::*Set) (ValueType value);
    //-- Pointer to set member function --
    ValueType(Container::*Get) ();
    //-- Pointer to get member function --
};

//==============================================================================

#endif

