#include "java.h"
namespace java {
    bool Object::equals(Object & obj) {
	return false;
    } Class & Object::getClass() {
	//Class *c = new Class();
	return *new Class();
    }
    int Object::hashCode() {
	return -1;
    }

    void Object::notify() {
    }
    void Object::notifyAll() {
    }

    string & Object::toString() {
	return *new string();
    }

    void Object::wait() {
    }
    void Object::wait(long timeout, int nanos) {
    }
    void Object::wait(long timeout) {
    }
    boolean Object::isNull() {
	return null;
    }


    Object & Object::clone() {
	return *new Object();
    }

    void Object::finalize() {
    }

  Object::Object(boolean null = false):null(null) {

    }

    string & Class::getSimpleName() {
	return *new string("");
    }
};

