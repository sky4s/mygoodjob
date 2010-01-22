#ifndef LANGH
#define LANGH

#include <string>
#include <vcl.h>
#include <math>

namespace java {
    namespace lang {
	using std::string;
	class Class;

	class Object {
	  private:
	    bool null;
	  public:
	    boolean equals(Object & obj) {
		//return this->Equals(&obj);
		return false;
	    };
	     Class & getClass();
	    int hashCode() {
		//return this->Hash();
		return -1;
	    };
	    void notify() {
	    };
	    void notifyAll() {
	    };
	    string & toString() {
		return *new string();
	    };
	    void wait() {
	    };
	    void wait(long timeout, int nanos) {
	    };
	    void wait(long timeout) {
	    };
	    bool isNull() {
		return null;
	    };
	  Object(bool null = false):null(null) {

	    };


	  protected:
	    Object & clone() {
		return *new Object();
	    };
	    void finalize();


	};

	class Class {
	  public:
	    string & getSimpleName() {
		return *new string("");
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
    };
};
#endif

