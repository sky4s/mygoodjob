#include "lang.h"

//C系統文件
#include <cmath>
//C++系統文件

//其他庫頭文件

//本項目內頭文件

namespace java {
    namespace lang {
	using namespace std;
	using namespace boost;
	//======================================================================
	// Class
	//======================================================================
	 Class::Class(Object & object):object(object), info(typeid(object)) {

	};
	string_ptr Class::getSimpleName() {
	    return string_ptr(new string(info.name()));
	};

	string_ptr Class::getName() {
	    return string_ptr(new string(info.name()));
	};
	//======================================================================

	//======================================================================
	// Object
	//======================================================================
	int Object::globalID = 0;
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

	string_ptr Object::toString() {
	    return getClass().getName();
	};
	bool Object::isNull() {
	    return null;
	};
      Object::Object(bool null):null(null), c(*this),
	    objectID(globalID++) {

	};
      Object::Object():null(false), c(*this), objectID(globalID++) {

	};
      /*Object::Object(Object & o):null(false), c(*this),
	    objectID(globalID++) {

	};*/
	const int Object::getObjectID() {
	    return objectID;
	};
	object_ptr Object::clone() {
	    return object_ptr(new Object(this));
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
	double Math::sqr(double v) {
	    return v * v;
	}
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

