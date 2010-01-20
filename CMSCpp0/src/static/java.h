#ifndef JAVAH
#define JAVAH
#include <string>
#include <vcl.h>

namespace java {
    using std::string;
    class Class;
    class Object :public TObject{
      public:
	bool equals(Object obj);
	Class getClass();
	int hashCode();
	string toString();
      protected:
	 Object clone();
	void finalize();
    };
    class Class {
      public:
	string getSimpleName();
    };
};
#endif

