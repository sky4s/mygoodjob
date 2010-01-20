#ifndef JAVAH
#define JAVAH
#include <string>
#include <vcl.h>

namespace java {
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
};
#endif

