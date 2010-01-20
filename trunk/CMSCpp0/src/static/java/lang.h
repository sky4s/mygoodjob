#ifndef LANGH
#define LANGH
#include <string>
#include <vcl.h>

namespace java {
    namespace lang {
	using std::string;
	class Class;

	class Object:public TObject {
	  public:
	    bool equals(Object & obj);
	    Class & getClass();
	    int hashCode();
	    void notify();
	    void notifyAll();
	     string & toString();
	    void wait();
	    void wait(long timeout, int nanos);
	    void wait(long timeout);
	    boolean isNull();
	  protected:
	     Object & clone();
	    void finalize();
	     Object(boolean null);
	     Object();
	  private:
	     boolean null;
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
	    static double PI;
	};
    };
};
#endif

