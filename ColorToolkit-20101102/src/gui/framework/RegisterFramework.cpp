#include <includeall.h>
#pragma hdrstop
#include "RegisterFramework.h"

//C系統文件
#include <cstdarg>
//C++系統文件

//vcl庫頭文件

//其他庫頭文件

//本項目內頭文件

//本項目內gui頭文件
#include <fpga/gui_class.h>

namespace gui {
    namespace framework {
	RegisterType::RegisterType(std::string regname):regname(regname) {

	};
	//=====================================================================
	 RegisterMap::RegisterMap(std::string filename) {
	    tconMap = AbstractBase::getStringMap(filename);
	    registerMap = RegisterTypeMap_ptr(new RegisterTypeMap());
	};

	int_vector_ptr RegisterMap::getIntVector(std::string text) {
	    if (text.length() == 0 || text == "_NULL") {
		return nil_int_vector_ptr;
	    }
	    using namespace cms::util;
	    string_vector_ptr tokens = StringVector::tokenize(text, ",");
	    int size = tokens->size();
	    int_vector_ptr values(new int_vector(size - 1));
	    for (int x = 1; x < size; x++) {
		string token = (*tokens)[x];
		(*values)[x - 1] = _toInt(token);
	    }
	    return values;
	};

	/*
	   ToDo
	 */
	RegisterType_ptr RegisterMap::getRegister(std::string regname,
						  int_vector_ptr intVector)
	{
	    if (true) {
		RegisterType_ptr result(new RegisterType(regname));
		return result;
	    }
	    int size = intVector->size();
	    switch (size) {
	    case 3:		//TBit1
		break;
	    case 4:		//TLUT
		break;
	    case 6:		//TBit2
		break;
	    case 9:		//TBit3
		break;
	    case 12:		//TBit4
		break;
	    };
	};

	RegisterType_ptr RegisterMap::getRegister(std::string regname) {

	    if (0 == regname.length() || "_NULL" == regname) {
		return nil_RegisterType_ptr;
	    }

	    RegisterType_ptr reg = (*registerMap)[regname];
	    if (null == reg) {
		//沒有=>代表沒有生成RegisterType, 即刻生成
		const std::string text = (*tconMap)[regname];
		if ("" != text) {
		    int_vector_ptr intVector = getIntVector(text);
		    reg = getRegister(regname, intVector);
		    (*registerMap)[regname] = reg;
		} else {
		    return nil_RegisterType_ptr;
		}
	    }
	    return reg;
	};
	//=====================================================================

      BitRegister::BitRegister(std::string regname, int n,...):RegisterType(regname)
	{
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
	    } va_end(num_list);
	};

      BitRegister::BitRegister(std::string regname, int_vector_ptr intVector):RegisterType(regname)
	{
	    int size = intVector->size();
	    regData = int_array(new int[size]);
	    for (int x = 0; x < size; x++) {
		regData[x] = (*intVector)[x];
	    }
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
	void RegisterFramework::init() {
	    childmap = TControlVecMap_ptr(new TControlVecMap());
	    labelVector = TControl_vector_ptr(new TControl_vector());
	    statictextVector = TControl_vector_ptr(new TControl_vector());
	    checkVector = TControl_vector_ptr(new TControl_vector());
	    editVector = TControl_vector_ptr(new TControl_vector());
	};
	RegisterFramework::RegisterFramework() {
	    setRegisterFilename("tcon.txt");
	    init();

	};

	RegisterFramework::RegisterFramework(std::string filename) {
	    setRegisterFilename(filename);
	    init();
	};

	/*
	   scanUI要做的事情
	   1.依照parent分類
	   2.繫結: Scroll跟StaticText, 僅bind UI
	   3.歸類: Label跟ComboBox, Label跟Scroll, 利用Label去取得reg 
	 */
	void RegisterFramework::scanUI(TForm * form) {
	    scanChild(form);
	    processStaticText(statictextVector);	//繫結 scroll 和 static text
	    processLabel(labelVector);	//歸類
	    processSingleTControl(checkVector);	//TCheckBox
	    processSingleTControl(editVector);	//TLabeledEdit
	};

	void RegisterFramework::scanChild(TWinControl * ctrl) {
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
		    labelVector->push_back(label);
		    continue;
		}

		TCheckBox *check = dynamic_cast < TCheckBox * >(child);
		if (null != check) {
		    checkVector->push_back(check);
		    continue;
		}

		TLabeledEdit *edit =
		    dynamic_cast < TLabeledEdit * >(child);
		if (null != edit) {
		    editVector->push_back(edit);
		    continue;
		}

		TWinControl *wctrl = dynamic_cast < TWinControl * >(child);
		if (null != wctrl) {
		    scanChild(wctrl);
		    continue;
		}
	    }

	}

	/*
	   將Label跟ScrollBar或者TComboBox結合
	 */
	void RegisterFramework::
	    processLabel(TControl_vector_ptr labelVector) {
	    foreach(TControl * ctrl, *labelVector) {
		TWinControl *parent = ctrl->Parent;
		TControl_vector_ptr ctrlvec = (*childmap)[parent];
		TControl_vector_ptr sameTop = findSameTop(ctrlvec, ctrl);
		TLabel *label = dynamic_cast < TLabel * >(ctrl);
		String caption = label->Caption;
		char *cArrayCaption = caption.c_str();

		foreach(TControl * ctrl, *sameTop) {
		    RegisterType_ptr registerType =
			registerMap->getRegister(cArrayCaption);

		    TScrollBar *scroll =
			dynamic_cast < TScrollBar * >(ctrl);
		    TComboBox *combobox =
			dynamic_cast < TComboBox * >(ctrl);
		    if (nil_RegisterType_ptr != registerType
			&& (null != scroll || null != combobox)) {
			registerType->control = ctrl;
		    }

		}

	    }
	};


	/*
	   繫結StaticText前面的ScrollBar
	 */
	void RegisterFramework::
	    processStaticText(TControl_vector_ptr statictextVector) {
	    foreach(TControl * ctrl, *statictextVector) {
		TStaticText *text = dynamic_cast < TStaticText * >(ctrl);
		if (null != text) {
		    TWinControl *parent = text->Parent;
		    //找到兄弟姊妹
		    TControl_vector_ptr ctrlvec = (*childmap)[parent];
		    //找到top一樣高的
		    TControl_vector_ptr sameTop =
			findSameTop(ctrlvec, text);
		    foreach(TControl * ctrl, *sameTop) {
			TScrollBar *scroll =
			    dynamic_cast < TScrollBar * >(ctrl);
			if (null != scroll
			    && (scroll->Left + scroll->Width) <
			    text->Left) {
			    //只要符合上述條件, 就bind在一起
			    binder.bind(text, scroll);
			}
		    }
		}
	    }
	};

	void RegisterFramework::
	    processSingleTControl(TControl_vector_ptr vector) {
	    foreach(TControl * ctrl, *vector) {
		String caption = null;
		TCheckBox *checkBox = dynamic_cast < TCheckBox * >(ctrl);
		if (null != checkBox) {
		    caption = checkBox->Caption;
		}
		TLabeledEdit *labeledEdit =
		    dynamic_cast < TLabeledEdit * >(ctrl);
		if (null != labeledEdit) {
		    caption = labeledEdit->EditLabel->Caption;
		}
		if (caption != null) {
		    RegisterType_ptr reg =
			registerMap->getRegister(caption.c_str());
		    if (null != reg) {
			reg->control = checkBox;
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
	/*
	 */
	void RegisterFramework::bindComboBox(const string & regname, int n,
					     ...) {
	    RegisterType_ptr reg = registerMap->getRegister(regname);
	    TControl *ctrl = reg->control;
	    if (null == ctrl) {
		return;
	    }
	    TComboBox *comboxBox = dynamic_cast < TComboBox * >(ctrl);
	    if (null != comboxBox) {
		va_list num_list;
		va_start(num_list, n);

		for (int i = 0; i < n; i++) {
		    char *str = va_arg(num_list, char *);
		    comboxBox->Items->Add(str);
		} va_end(num_list);
		comboxBox->ItemIndex = 0;
	    }
	};

	/*
	 */
	void RegisterFramework::bind(const string & regname,
				     TControl * control) {
	    RegisterType_ptr reg = registerMap->getRegister(regname);
	    if (null != reg) {
		reg->control = control;
	    }
	};

	void RegisterFramework::active(TObject * sender) {
	    binder.active(sender);
	};

	void RegisterFramework::setRegisterFilename(std::string filename) {
	    registerMap = RegisterMap_ptr(new RegisterMap(filename));
	};

    };

};

