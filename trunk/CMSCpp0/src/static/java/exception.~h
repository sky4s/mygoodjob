#ifndef EXCEPTIONH
#define EXCEPTIONH
#include <exception>
#include <stdexcept>
#include <string>
#include "lang.h"


namespace java {
    namespace lang {
	class Exception:public std::exception, java::lang::Object {
	  public:
	    Exception();
	    Exception(std::string message) {
		this->message = message;
	    }
	  private: string message;
	};
	class RuntimeException:public Exception {
	  public:
	    RuntimeException();
	    RuntimeException(std::string message):Exception(message) {

	    }
	};
	class IllegalStateException:public RuntimeException {
	  public:
	    IllegalStateException();
	    IllegalStateException(std::
				  string message):RuntimeException(message)
	    {

	    }
	};
    };
};

#endif

