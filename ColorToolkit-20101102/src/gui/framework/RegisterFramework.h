#ifndef REGISTERFRAMEWORKH
#define REGISTERFRAMEWORKH

//C�t�Τ��

//C++�t�Τ��

//vcl�w�Y���

//��L�w�Y���

//�����ؤ��Y���

//�����ؤ�gui�Y���

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

