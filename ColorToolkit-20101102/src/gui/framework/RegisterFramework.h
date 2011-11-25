#ifndef REGISTERFRAMEWORKH
#define REGISTERFRAMEWORKH

//C系統文件

//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件

//本項目內gui頭文件

namespace gui {
    namespace framework {
	using namespace std;
	class RegisterType {

	};

	class BitRegister:public RegisterType {
	  private:


	};
	class LUTRegister:public RegisterType {
	};


	class RegisterMap {
	  private:
	    StringMap_ptr map;
	    void initAliasNameMap();
	  public:
	     RegisterMap(std::string filename);
	    void reset();
	     bptr < RegisterType > getRegister(std::string regname);
	};



	class RegisterFramework {

	  private:
	    void bind(const string & regname, TControl * control);
	    void childScan(TWinControl * ctrl);
	  public:
	    void bind(const string & regname, ...);
	    void scanUI(TForm * form);
	};


    };
};

#endif

