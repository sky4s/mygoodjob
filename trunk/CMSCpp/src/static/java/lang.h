#ifndef LANGH
#define LANGH

//C系統文件

//C++系統文件
#include <string>
//其他庫頭文件
#include <boost/shared_ptr.hpp>
//本項目內頭文件



#define shared_vector_double  shared_ptr < vector < double > >
#define shared_vector_string  shared_ptr < vector < string > >
#define null_string shared_ptr < string > (NULL)

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
 幾經測試之下, 本來決定用define的方式以  shared_vector_double 代替 shared_ptr < vector < double > >,
 就可以避掉indent的問題!

 但是畢竟是指標...要一直不斷的用(*)[]去取值 (不能用->[] 這種怪語法..), 太麻煩了,
  所以回頭用shared_array

*/


namespace java {
    namespace lang {
	using namespace boost;
	using namespace std;
	class Object;

	class Class {
	  private:
	    friend class Object;
	    const type_info & info;
	     Object & object;
	     Class(Object & object);
	  public:
	     shared_ptr < string > getSimpleName();
	     shared_ptr < string > getName();
	};

	class Object {
	  private:
	    bool null;
	    Class c;
	  public:
	     bool equals(shared_ptr < Object > obj);
	     Class & getClass();
	    int hashCode();
	     shared_ptr < string > toString();
	    bool isNull();
	     Object(bool null);
	     Object();

	  protected:
	     shared_ptr < Object > clone();
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
	};


	class Exception:public Object {
	  public:
	    Exception();
	    Exception(string message);
	    string & toString();
	  private:
	    string message;
	};
	class RuntimeException:public Exception {
	  public:
	    RuntimeException();
	    RuntimeException(string message);
	};
	class IllegalStateException:public RuntimeException {
	  public:
	    IllegalStateException();
	    IllegalStateException(string message);
	};

	class IllegalArgumentException:public RuntimeException {
	  public:
	    IllegalArgumentException();
	    IllegalArgumentException(string message);
	};
    };
};
#endif

