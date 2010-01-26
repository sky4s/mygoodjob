#ifndef LANGH
#define LANGH

#include <string>
#include <vcl.h>
#include <math>
#include <boost/shared_ptr.hpp>
#include <typeinfo>
#include <iostream>
//#include "exception.h"

#define  shared_vector_double shared_ptr < vector < double > >
#define  shared_vector_string shared_ptr < vector < string > >

/*
 java->C++轉換原則

 *override+overload問題
 c++缺乏java的interface, 雖然可以pure virtual func代替,
 但是會遇到override+overload以及hide的問題. 且使用了多重繼承, 會引入虛擬繼承的問題.
 所以在不同類別有overload需求時盡量避免, 以更名解決; 不過要是有大量更名的需要,
 乾脆直接在子類別把被hide的func呼叫回來.

 *禁止使用指標及參考
 避免忘記delete的問題

 *物件完全採用smart_ptr
 參考會有無法有null的狀況, 因此全採用smart_ptr, 作到類似gc的效果.
 smart_ptr的產生方法為 shared_array < double >p(NULL);

 *原生型別陣列採用smart_ptr(shared_array)
 純粹採用vector的話, 雖然可以達到類似java array的特性, 但是作為local vector不能當作ref or ptr被傳出去,
 否則可能會指向一個未知的空間.
 所以一般是建議採用shared_ptr<vector<>>, 但是這種作法會讓indent(程式碼格式化器) 出錯!
 因為現在用的indent是c專屬的, 他看不懂template的<< >>...會當作shift運算子.

 幾經測試之下, 本來決定用define的方式以  shared_vector_double 代替 shared_ptr < vector < double > >,
 就可以避掉indent的問題!
 但是畢竟是指標...要一直不斷的用(*)[]去取值, 太麻煩了, 所以回頭用shared_array

*/


namespace java {
    namespace lang {
	using namespace boost;
	//using std::string;
	using namespace std;
	class Object;

	class Class {
	  private:
	    friend class Object;
	    const type_info & info;
	     Object & object;
	     Class(Object & object):object(object), info(typeid(object)) {

	    };
	  public:

	     shared_ptr < string > getSimpleName() {
		return shared_ptr < string > (new string(info.name()));
	    };

	     shared_ptr < string > getName() {
		return shared_ptr < string > (new string(info.name()));
	    };
	};

	class Object {
	  private:
	    bool null;
	    Class c;
	  public:
	     boolean equals(shared_ptr < Object > obj) {
		//return this->Equals(&obj);
		return false;
	    };

	    Class & getClass() {
		return c;
	    };
	    int hashCode() {
		//return this->Hash();
		return -1;
	    };

	    shared_ptr < string > toString() {
		return shared_ptr < string > (new string());
	    };
	    bool isNull() {
		return null;
	    };
	  Object(bool null = false):null(null), c(*this) {

	    };

	  protected:
	    shared_ptr < Object > clone() {
		return shared_ptr < Object > (new Object());
	    };
	    void finalize() {
	    };


	};



	class Math {
	  public:
	    static double sqrt(double a) {
		return std::sqrt(a);
	    };
	    static double pow(double a, double b) {
		return std::pow(a, b);
	    };
	    static double atan2(double y, double x) {
		return std::atan2(y, x);
	    };
	    static const double PI;
	    static double cos(double x) {
		return std::cos(x);
	    };
	    static double sin(double x) {
		return std::sin(x);
	    };
	};

	class Exception:public Object {
	  public:
	    Exception() {
	    };
	    Exception(string message) {
		this->message = message;
	    };
	    string & toString() {
		return message;
	    };
	  private:
	    string message;
	};
	class RuntimeException:public Exception {
	  public:
	    RuntimeException() {
	    };
	  RuntimeException(string message):Exception(message) {

	    };
	};
	class IllegalStateException:public RuntimeException {
	  public:
	    IllegalStateException() {
	    };
	  IllegalStateException(string message):RuntimeException(message)
	    {

	    };
	};

	class IllegalArgumentException:public RuntimeException {
	  public:
	    IllegalArgumentException() {
	    };
	  IllegalArgumentException(string message):RuntimeException(message)
	    {

	    };
	};


    };
};
#endif

