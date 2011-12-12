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



/*
  �������P��TBit
  �D��: bit�� + ���ݶ�
  check box: 1bit
  combo box: 1/2bit  + TLabel(for name)
  label edit : 1/2/3/4bit
  scroll bar: 1/2bit + TLabel(for name) + TStaticText

  ���ݶ���, TLabel�|���w��, �����name; TStaticText�h�Q�����ScrollBar�����G
  TStaticText�z�LUIô���Y�i
  �ҥH�u�n�B�zCheckbox/ComboBox/LabelEdit/ScrollBar�o�|��
  ���䤤ComboBox/ScrollBar�ݭn�z�LLabel�o��Reg Name
  Checkbox�MLabelEdit�۱aReg Name

  �쥻���Q�k:
  �qComboBox/ScrollBar�qLabel���oReg Name��N����ô���ƥ�B�z�N�n
  ���O�S��address�p��ô��...
  ô������k������� 1.���ͷs���O��RegisterType��UI�j�A�@�_
  2.�Q��Map���̸j�b�@�_~
  ���F�Ŷ��Ҷq, ���ӫ�̸��n? �ϥ��C��rw���ɭԳ��@�w�n�A�h�ݭԤ@�URegisterType,
  ���N�����h��Map�ݭԴN�n��!

  �ثe���Q�k��:
  �@��RegisterFramework��Class�ξ�
  1.UI�MRegname��ô��
  2.Regname�MRegisterType��ô��
  3.�ƥ󪺳B�z
  RegisterType�]�ABitRegister�MLUTRegister
  ���ô���z�L RegisterFramework.bind("reg name",CheckBox) <=���z�LRegisterFramework"�j����"�i�H�۰ʰ���
  �M RegisterFramework.bindComboBox("reg name","option1","option2"...) <=��ĳ�bUI Designer�W�B�z�����
  �Ⱖ�禡�N�i�Hô�� register<=>UI.
  ���O���F��֪��B�z, RegisterFramework.scanUI(TForm * form)�O�̦n��

  1212�Q�k��s:
  UI->Register Name
  Rigister Name->Register Type

  �ƥ�B�z:
  CheckBox: OnClick
  ComboBox: OnClick
  LabeledEdit: OnKeyPress
  ScrollBar: OnChange


*/
namespace gui {
    namespace framework {
	class RegisterType;
	class BitRegister;
	class LUTRegister;
	class RegisterType;
    };
};

	//=====================================================================
	// ���F��K�ϥΪ�������typedef
	//=====================================================================
typedef bptr < gui::framework::RegisterType > RegisterType_ptr;
#define nil_RegisterType_ptr RegisterType_ptr((RegisterType *) NULL)
typedef bptr < gui::framework::BitRegister > BitRegister_ptr;
typedef bptr < gui::framework::LUTRegister > LUTRegister_ptr;

typedef std::map < const std::string, RegisterType_ptr > RegisterTypeMap;
typedef bptr < RegisterTypeMap > RegisterTypeMap_ptr;
#define nil_RegisterTypeMap_ptr RegisterTypeMap_ptr((RegisterTypeMap *) NULL)
	//=====================================================================

namespace gui {
    namespace framework {
	using namespace std;

	enum TypeID {
	    Bit, Lut
	};

	/*
	   �Ҧ�Register Type���ѯR
	 */
	class RegisterType {
	    friend class RegisterFramework;
	  private:
	    RegisterType();
	    OnChangeFunction originalOnChangeFunc;
	    OnKeyPressFunction originalOnKeyPressFunc;
	  protected:
	    std::string regname;
	    TControl *control;
	    TypeID typeID;
	    RegisterType(std::string regname, TypeID typeID);
	  public:
	    RegisterType(std::string regname);
	    //__property OnChangeFunction OriginalOnChangeFunc = { write = originalOnChangeFunc };
	    //__property OnKeyPressFunction OriginalOnKeyPressFunc = { write = originalOnKeyPressFunc
	    //};
	};



	class BitRegister:public RegisterType {
	  private:
	    int byteCount;
	    int_array regData;
	  public:
	    BitRegister(std::string regname, int n, ...);
	    BitRegister(std::string regname, int_vector_ptr intVector);
	    int getAddress(int n);
	    int getBit(int n);
	    int getLength(int n);

	};


	class LUTRegister:public RegisterType {
	  public:
	    LUTRegister(std::string regname, int_vector_ptr intVector);
	};



	/*
	   regname->Register
	   ������إ�Register Type�Mtcon.ini�����Y
	 */
	class RegisterMap {
	  private:
	    StringMap_ptr tconMap;
	    RegisterTypeMap_ptr registerMap;
	    void initAliasNameMap();
	    int_vector_ptr getIntVector(std::string text);
	    RegisterType_ptr getRegister(std::string regname, int_vector_ptr intVector);
	  public:
	    RegisterMap(std::string filename);
	    RegisterType_ptr getRegister(std::string regname);
	};

	typedef bptr < RegisterMap > RegisterMap_ptr;
	typedef std::map < TControl *, std::string > TControl2RegNameMap;
#define   TCtrl2RegNameMap_ptr bptr<TControl2RegNameMap>

	class RegisterFramework {
	  private:
	    TControlVecMap childmap;	//parent->child
	    TControl2RegNameMap ctrl2nameMap;	//TControl->Register Name
	    RegisterMap_ptr registerMap;

	    TControl_vector_ptr labelVector;
	    TControl_vector_ptr statictextVector;
	    TControl_vector_ptr checkVector;
	    TControl_vector_ptr editVector;

	    gui::util::MultiUIBinder binder;

	    void scanChild(TWinControl * ctrl);
	    //=================================================================
	    // process TControl(s)
	    //=================================================================
	    void processLabel(TControl_vector_ptr labelVector);
	    void processStaticText(TControl_vector_ptr statictextVector);
	    void processSingleTControl(TControl_vector_ptr vector);
	    //=================================================================
	    void init();
	    static TControl_vector_ptr findSameTop(TControl_vector_ptr vector, TControl * find);
	    static TControl_vector_ptr findSameTop(TControl_vector_ptr vector, TControl * find,
						   bool loose);
	    //=================================================================
	    //event handler
	    //=================================================================
	    void __fastcall onClick(TObject * Sender);	//check/combo
	    void __fastcall onKeyPress(TObject * Sender, char &Key);	//edit label
	    void __fastcall onChange(TObject * Sender);	//scroll bar
	    void processOnChange(TScrollBar * scrollBar, RegisterType_ptr reg);
	    void processOnClick(TCheckBox * checkBox, RegisterType_ptr reg);
	    void processOnClick(TComboBox * comboBox, RegisterType_ptr reg);
	    void simpleEventHandler(std::string regname, TObject * sender, char &ke);
	    //=================================================================
	  public:
	    void bindComboBox(const string & regname, int n, ...);
	    void bind(const string & regname, TControl * control);
	    void scanUI(TForm * form);
	    RegisterFramework();
	    RegisterFramework(std::string filename);
	    void active(TObject * sender);
	    void setRegisterFilename(std::string filename);
	    static String NON_BIND;
	};

	class IOInterface {

	};
    };
};



#endif

