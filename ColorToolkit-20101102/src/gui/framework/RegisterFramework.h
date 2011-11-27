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

  �쥻���Q�k�O�qComboBox/ScrollBar�qLabel���oReg Name��N����ô���ƥ�B�z�N�n
  ���O�S��address�p��ô��...
  ô������k������� 1.���ͷs���O��RegisterType��UI�j�A�@�_
  2.�Q��Map���̸j�b�@�_~
  ���F�Ŷ��Ҷq, ���ӫ�̸��n? �ϥ��C��rw���ɭԳ��@�w�n�A�h�ݭԤ@�URegisterType,
  ���N�����h��Map�ݭԴN�n��!

  �ثe���Q�k��:
  �@��RegisterFramework��Class�ξ� RegisterType�MUI��ô��
  RegisterType�]�ABitRegister�MLUTRegister
  �u�n�z�L RegisterFramework.bind("reg name",CheckBox) <=�o�ӵ{��"�j����"�i�H�۰ʰ���
  �MRegisterFramework.bindComboBox("reg name","option1","option2"...)
  �Ⱖ�禡�N�i�Hô�� register<=>UI

  �ƥ�B�z:
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

