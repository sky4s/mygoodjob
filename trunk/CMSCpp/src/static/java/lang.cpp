#include "lang.h"

//C系統文件
#include <cmath>
//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace java {
    namespace lang {

	//======================================================================
	// Class
	//======================================================================
	Class::Class(Object & object):object(object), info(typeid(object)) {

	};
	 shared_ptr < string > Class::getSimpleName() {
	    return shared_ptr < string > (new string(info.name()));
	};

	shared_ptr < string > Class::getName() {
	    return shared_ptr < string > (new string(info.name()));
	};
	//======================================================================

	//======================================================================
	// Object
	//======================================================================
	bool Object::equals(shared_ptr < Object > obj) {
	    //return this->Equals(&obj);
	    return false;
	};

	Class & Object::getClass() {
	    return c;
	};
	int Object::hashCode() {
	    //return this->Hash();
	    return -1;
	};

	shared_ptr < string > Object::toString() {
	    return shared_ptr < string > (new string());
	};
	bool Object::isNull() {
	    return null;
	};
      Object::Object(bool null):null(null), c(*this) {

	};
      Object::Object():null(false), c(*this) {

	};
	shared_ptr < Object > Object::clone() {
	    return shared_ptr < Object > (new Object());
	};
	void Object::finalize() {
	};
	//======================================================================

	//======================================================================
	// Math
	//======================================================================
	double Math::sqrt(double a) {
	    return std::sqrt(a);
	};
	double Math::pow(double a, double b) {
	    return std::pow(a, b);
	};
	double Math::atan2(double y, double x) {
	    return std::atan2(y, x);
	};
	const double Math::PI = 3.1415926;
	double Math::cos(double x) {
	    return std::cos(x);
	};
	double Math::sin(double x) {
	    return std::sin(x);
	};
	//======================================================================

	//======================================================================
	// Exception
	//======================================================================
	Exception::Exception() {
	};
      Exception::Exception(string message):message(message) {
	};
	string & Exception::toString() {
	    return message;
	};


	RuntimeException::RuntimeException() {
	};
      RuntimeException::RuntimeException(string message):Exception(message)
	{

	};

	IllegalStateException::IllegalStateException() {
	};
      IllegalStateException::IllegalStateException(string message):RuntimeException(message)
	{

	};

	IllegalArgumentException::IllegalArgumentException() {
	};
      IllegalArgumentException::IllegalArgumentException(string message):RuntimeException(message)
	{

	};
	//======================================================================
    };
};

