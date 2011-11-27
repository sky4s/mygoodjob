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



/*
  對應不同的TBit
  主項: bit數 + 附屬項
  check box: 1bit
  combo box: 1/2bit  + TLabel(for name)
  label edit : 1/2/3/4bit
  scroll bar: 1/2bit + TLabel(for name) + TStaticText

  附屬項中, TLabel會為定值, 僅顯示name; TStaticText則被動顯示ScrollBar的結果
  TStaticText透過UI繫結即可
  所以只要處理Checkbox/ComboBox/LabelEdit/ScrollBar這四個
  但其中ComboBox/ScrollBar需要透過Label得到Reg Name
  Checkbox和LabelEdit自帶Reg Name

  原本的想法是從ComboBox/ScrollBar從Label取得Reg Name後就直接繫結事件處理就好
  但是沒有address如何繫結...
  繫結的方法分為兩種 1.產生新類別把RegisterType跟UI綁再一起
  2.利用Map把兩者綁在一起~
  為了空間考量, 應該後者較好? 反正每次rw的時候都一定要再去問候一下RegisterType,
  那就直接去跟Map問候就好啦!

  目前的想法為:
  一個RegisterFramework的Class統整 RegisterType和UI的繫結
  RegisterType包括BitRegister和LUTRegister
  只要透過 RegisterFramework.bind("reg name",CheckBox) <=這個程式"大部分"可以自動做掉
  和RegisterFramework.bindComboBox("reg name","option1","option2"...)
  兩隻函式就可以繫結 register<=>UI

  事件處理:
  CheckBox: OnClick
  ComboBox: OnClick
  LabeledEdit: OnKeyPress
  ScrollBar: OnChange

*/
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
	    TControl_vector_ptr labelVector;
	    TControl_vector_ptr statictextVector;
	    TControl_vector_ptr checkVector;
	    TControl_vector_ptr editVector;
	     bptr < RegisterMap > registerMap;
	     gui::util::MultiUIBinder binder;

	    void childScan(TWinControl * ctrl);
	    void processLabel();
	    void processStaticText();
	    void processTControl(TControl_vector_ptr vector);
	    void init();
	    static TControl_vector_ptr findSameTop(TControl_vector_ptr
						   vector,
						   TControl * find);

	    void __fastcall onClick(TObject * Sender);
	    void __fastcall onKeyPress(TObject * Sender, char &Key);
	    void __fastcall onChange(TObject * Sender);
	  public:
	    void bindComboBox(const string & regname, ...);
	    void bind(const string & regname, TControl * control);
	    void scanUI(TForm * form);
	     RegisterFramework();
	     RegisterFramework(std::string filename);
	    void active(TObject * sender);
	    void resetRegisterMap();
	    void setRegisterFilename(std::string filename);
	};


    };
};

#endif

