#include <includeall.h>
#pragma hdrstop
#include "RegisterFramework.h"

//C�t�Τ��
#include <cstdarg>
//C++�t�Τ��

//vcl�w�Y���

//��L�w�Y���

//�����ؤ��Y���

//�����ؤ�gui�Y���
#include <fpga/gui_class.h>

namespace gui {
    namespace framework {
	RegisterMap::RegisterMap(std::string filename) {
	    map = AbstractBase::getStringMap(filename);

	};

	void RegisterMap::reset() {
	    map = nil_StringMap_ptr;
	};

	bptr < RegisterType > RegisterMap::getRegister(std::string regname) {
	};
	//=====================================================================

	BitRegister::BitRegister(int n, ...) {
	    if (n % 3 != 0) {
		throw new java::lang::IllegalArgumentException();
	    }

	    va_list num_list;
	    va_start(num_list, n);
	    regData = int_array(new int[n]);
	    byteCount = n / 3;

	    for (int i = 0; i < n; i++) {
		const int d = va_arg(num_list, const int);
		regData[i] = d;
		/*const string & str = _toString(d);
		   result->push_back(str); */
	    } va_end(num_list);
	};


	int BitRegister::getAddress(int n) {
	    if (n > byteCount) {
		throw new java::lang::IllegalArgumentException();
	    }
	    return regData[n * 3];
	}
	int BitRegister::getBit(int n) {
	    if (n > byteCount) {
		throw new java::lang::IllegalArgumentException();
	    }
	    return regData[n * 3 + 1];
	}

	int BitRegister::getLength(int n) {
	    if (n > byteCount) {
		throw new java::lang::IllegalArgumentException();
	    }
	    return regData[n * 3 + 2];
	}
	//=====================================================================

	RegisterFramework::RegisterFramework() {
	    childmap = TControlVecMap_ptr(new TControlVecMap());
	    labelvector = TLabel_vector_ptr(new TLabel_vector());
	    statictextVector = TControl_vector_ptr(new TControl_vector());
	};

	/*
	   scanUI�n�����Ʊ�
	   1.�̷�parent����
	   2.ô��: Scroll��StaticText,
	   3.�k��: Label��ComboBox, Label��Scroll 
	 */
	void RegisterFramework::scanUI(TForm * form) {
	    childScan(form);
	    processLabel();
	    processStaticText();	//ô��
	};

	void RegisterFramework::childScan(TWinControl * ctrl) {
	    int count = ctrl->ControlCount;
	    for (int x = 0; x < count; x++) {
		TControl *child = ctrl->Controls[x];
		String name = child->Name;
		TWinControl *parent = child->Parent;

		TControl_vector_ptr ctrlvec = (*childmap)[parent];
		if (nil_TControlVecMap_ptr == ctrlvec) {
		    ctrlvec = TControl_vector_ptr(new TControl_vector());
		}
		ctrlvec->push_back(child);
		(*childmap)[parent] = ctrlvec;


		TStaticText *staticText =
		    dynamic_cast < TStaticText * >(child);
		if (null != staticText) {
		    statictextVector->push_back(staticText);
		    continue;
		}

		TLabel *label = dynamic_cast < TLabel * >(child);
		if (null != label) {
		    labelvector->push_back(label);
		    continue;
		}

		TWinControl *wctrl = dynamic_cast < TWinControl * >(child);
		if (null != wctrl) {
		    childScan(wctrl);
		    continue;
		}




	    }

	}

	void RegisterFramework::processLabel() {
	    foreach(TLabel * label, *labelvector) {
		TWinControl *parent = label->Parent;
		TControl_vector_ptr ctrlvec = (*childmap)[parent];
		TControl_vector_ptr sameTop = findSameTop(ctrlvec, label);

		foreach(TControl * ctrl, *sameTop) {
		    TScrollBar *scroll =
			dynamic_cast < TScrollBar * >(ctrl);
		    if (null != scroll) {

		    }

		    TComboBox *combobox =
			dynamic_cast < TComboBox * >(ctrl);
		    if (null != combobox) {

		    }
		}

	    }
	};


	void RegisterFramework::processStaticText() {
	    foreach(TControl * ctrl, *statictextVector) {
		TStaticText *text = dynamic_cast < TStaticText * >(ctrl);
		if (null != text) {
		    TWinControl *parent = text->Parent;
		    TControl_vector_ptr ctrlvec = (*childmap)[parent];
		    TControl_vector_ptr sameTop =
			findSameTop(ctrlvec, text);
		    foreach(TControl * ctrl, *sameTop) {
			TScrollBar *scroll =
			    dynamic_cast < TScrollBar * >(ctrl);
			if (null != scroll
			    && (scroll->Left + scroll->Width) <
			    text->Left) {
			    binder.bind(text, scroll);
			}
		    }
		}
	    }
	};

	TControl_vector_ptr RegisterFramework::
	    findSameTop(TControl_vector_ptr vector, TControl * find) {
	    TControl_vector_ptr result(new TControl_vector());
	    foreach(TControl * ctrl, *vector) {
		if (ctrl != find && find->Top == ctrl->Top) {
		    result->push_back(ctrl);
		}
	    }
	    return result;
	};
	void RegisterFramework::bindComboBox(const string & regname, ...) {
	};

	void RegisterFramework::bind(const string & regname,
				     TControl * control) {
	};

	void RegisterFramework::active(TObject * sender) {
	    binder.active(sender);
	};
    };

};

