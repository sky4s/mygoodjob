#ifndef LANGH
#define LANGH

#include <string>
#include <vcl.h>
//#include "jobject.h"

namespace java {
    namespace lang {
	using std::string;
	class Class;

	class Object {
	  public:
	    boolean equals(Object & obj);
	    Class & getClass();
	    int hashCode();
	    void notify();
	    void notifyAll();
	     string & toString();
	    void wait();
	    void wait(long timeout, int nanos);
	    void wait(long timeout);
	    bool isNull();
	     Object(bool null);
	     Object();
	  protected:
	     Object & clone();
	    void finalize();

	  private:
	     bool null;
	};

	class Class {
	  public:
	    string & getSimpleName();
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
    };
};
#endif

