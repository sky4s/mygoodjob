#ifndef REGISTERFRAMEWORKH
#define REGISTERFRAMEWORKH

//C系統文件

//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件
#include <java/lang.h>
#include <gui/util/binder.h>

//本項目內gui頭文件

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

