#ifndef REGISTERFRAMEWORKH
#define REGISTERFRAMEWORKH

//C�t�Τ��

//C++�t�Τ��

//vcl�w�Y���

//��L�w�Y���

//�����ؤ��Y���
#include <java/lang.h>
#include <gui/util/binder.h>

//�����ؤ�gui�Y���

namespace gui {
    namespace framework {
	using namespace std;
	class RegisterType {

	};

	class BitRegister:public RegisterType {
	  private:
	    int byteCount;
	    int_array regData;
	  public:
	     BitRegister(n, ...);
	    int getAddress(int n);
	    int getBit(int n);
	    int getLength(int n);

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
	    TControlVecMap_ptr childmap;
	    TLabel_vector_ptr labelvector;
	    TControl_vector_ptr statictextVector;

	    void bind(const string & regname, TControl * control);
	    void childScan(TWinControl * ctrl);
	    void processLabel();
	    void processStaticText();
	    static TControl_vector_ptr findSameTop(TControl_vector_ptr
						   vector,
						   TControl * find);
	     gui::util::MultiUIBinder binder;
	  public:
	    void bindComboBox(const string & regname, ...);
	    //void bind(const string & regname, ...);
	    void scanUI(TForm * form);
	     RegisterFramework();
	    void active(TObject * sender);
	};


    };
};

#endif

