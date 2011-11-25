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


	typedef std::vector < TControl * >TControl_vector;
	typedef bptr < TControl_vector > TControl_vector_ptr;
	typedef std::map < TWinControl *,
	    TControl_vector_ptr > TControlVecMap;
	typedef bptr < TControlVecMap > TControlVecMap_ptr;
#define nil_TControlVecMap_ptr TControlVecMap_ptr((TControlVecMap *) NULL)

	class RegisterFramework {
	  private:
	    TControlVecMap_ptr childmap;
	    void bind(const string & regname, TControl * control);
	    void childScan(TWinControl * ctrl);
	  public:
	    void bind(const string & regname, ...);
	    void scanUI(TForm * form);
	     RegisterFramework();
	};


    };
};

#endif

