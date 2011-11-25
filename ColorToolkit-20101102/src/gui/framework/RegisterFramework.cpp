#include <includeall.h>
#pragma hdrstop
#include "RegisterFramework.h"

namespace gui {
    namespace framework {
	using namespace std;
	class RegisterFramework {

	  private:
	    void bind(const string & regname, TControl * control);
	  public:
	    void bind(const string & regname, ...);
	    void scanUI(TForm * form);
	};

	class RegisterType {

	};

	class BitRegister:public RegisterType {
	};
	class LUTRegister:public RegisterType {
	};
    };

};

