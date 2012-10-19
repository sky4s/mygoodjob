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
#include <colorip/gui_class.h>

namespace gui {
    namespace framework {
	RegisterType::RegisterType(std::string _regname, TypeID _typeID):regname(_regname),
	    typeID(_typeID) {
	};
	 RegisterType::RegisterType(std::string _regname):regname(_regname) {

	};
	//=====================================================================
	RegisterMap::RegisterMap(std::string filename) {
	    tconMap = AbstractIPBase::getStringMap(filename);
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
	RegisterType_ptr RegisterMap::getRegister(std::string regname, int_vector_ptr intVector) {
	    //if (true) {
	    RegisterType_ptr result(new RegisterType(regname));
	    return result;
	    /*}
	       int size = intVector->size();
	       RegisterType_ptr reg;
	       switch (size) {
	       case 3:          //TBit1
	       case 6:          //TBit2
	       case 9:          //TBit3
	       case 12:         //TBit4
	       reg = RegisterType_ptr(new BitRegister(regname, intVector));
	       break;
	       case 4:          //TLUT
	       break;
	       };
	       return reg; */
	};
	RegisterType_ptr RegisterMap::getRegister(std::string regname) {
	    //_NULL是原本的 tcon header定義不用顯示的關鍵字
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
      BitRegister::BitRegister(std::string regname, int n,...):RegisterType(regname, Bit) {
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
      BitRegister::BitRegister(std::string regname, int_vector_ptr intVector):RegisterType(regname, Bit)
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
	String RegisterFramework::NON_BIND = "Non-Bind";
	void RegisterFramework::init() {
	    //全部清乾淨
	    childmap.clear();
	    ctrl2nameMap.clear();
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
	   2.歸類: Label跟ComboBox, Label跟Scroll, 利用Label去取得reg
	   3.繫結: Scroll跟StaticText, 僅bind UI
	 */
	void RegisterFramework::scanUI(TForm * form) {
	    scanChild(form);
	    processLabel(labelVector);	//歸類
	    //以下才是繫結
	    processSingleTControl(checkVector);	//TCheckBox
	    processSingleTControl(editVector);	//TLabeledEdit
	    processStaticText(statictextVector);	//繫結 scroll 和 static text
	};
	void RegisterFramework::scanChild(TWinControl * ctrl) {
	    int count = ctrl->ControlCount;
	    for (int x = 0; x < count; x++) {
		TControl *child = ctrl->Controls[x];
		String name = child->Name;
		TWinControl *parent = child->Parent;
		TControl_vector_ptr ctrlvec = childmap[parent];
		if (nil_TControlVecMap_ptr == ctrlvec) {
		    ctrlvec = TControl_vector_ptr(new TControl_vector());
		}
		ctrlvec->push_back(child);
		childmap[parent] = ctrlvec;
		TStaticText *staticText = dynamic_cast < TStaticText * >(child);
		if (null != staticText) {
		    staticText->Caption = NON_BIND;
		    statictextVector->push_back(staticText);
		    continue;
		}

		TComboBox *comboBox = dynamic_cast < TComboBox * >(child);
		if (null != comboBox) {

//comboBox->Caption = NON_BIND;
		    comboBox->Text = NON_BIND;
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

		TLabeledEdit *edit = dynamic_cast < TLabeledEdit * >(child);
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

   將Label跟ScrollBar或者ComboBox結合


   ScrollBar跟TComboBox可能遇到沒有對到Label的情形, 這時候要顯示Non-Bind

 */
	void RegisterFramework::processLabel(TControl_vector_ptr labelVector) {
	    foreach(TControl * ctrl, *labelVector) {
		TWinControl *parent = ctrl->Parent;
		TControl_vector_ptr ctrlvec = childmap[parent];
		TControl_vector_ptr sameTop = findSameTop(ctrlvec, ctrl);
		TLabel *label = dynamic_cast < TLabel * >(ctrl);
		if (0 == sameTop->size()) {
		    label->Caption = NON_BIND;
		    continue;
		}

		String caption = label->Caption;
		char *cArrayCaption = caption.c_str();

		//reg找到對應的register
		RegisterType_ptr registerType = registerMap->getRegister(cArrayCaption);
		if (nil_RegisterType_ptr == registerType) {
		    label->Visible = false;
		}

		foreach(TControl * ctrl2, *sameTop) {
		    TScrollBar *scroll = dynamic_cast < TScrollBar * >(ctrl2);
		    TComboBox *combobox = dynamic_cast < TComboBox * >(ctrl2);
		    TStaticText *text = dynamic_cast < TStaticText * >(ctrl2);
		    if (null != text) {

			//StaticText不在這裡處理
			continue;
		    }

		    bool canBind = null != scroll || null != combobox;
		    if (nil_RegisterType_ptr != registerType && canBind) {
			registerType->control = ctrl2;
		    } else {
			if (canBind) {

			    //沒有對應的reg, 全hide
			    ctrl2->Visible = false;
			} else {

			    //除了沒對應的reg, 也沒可結合的UI, 表示格式錯誤
			    label->Caption = NON_BIND;
			}
		    }

		}


	    }
	};

/*

   繫結StaticText前面的ScrollBar

 */
	void RegisterFramework::processStaticText(TControl_vector_ptr statictextVector) {
	    foreach(TControl * ctrl, *statictextVector) {
		TStaticText *text = dynamic_cast < TStaticText * >(ctrl);
		if (null != text) {
		    TWinControl *parent = text->Parent;

//找到兄弟姊妹
		    TControl_vector_ptr ctrlvec = childmap[parent];

//找到top一樣高的
		    TControl_vector_ptr sameTop = findSameTop(ctrlvec, text);
		    foreach(TControl * ctrl, *sameTop) {
			TScrollBar *scroll = dynamic_cast < TScrollBar * >(ctrl);
			if (null != scroll && (scroll->Left + scroll->Width) < text->Left) {

//找到是Scroll且位置合理就進行下列判斷
			    if (true == scroll->Visible) {

//只要符合上述條件, 就bind在一起
				binder.bind(text, scroll);
			    } else {
				text->Visible = false;
			    }
			}
		    }
		}
	    }
	};

	/*
	   處理CheckBox LabeledEdit
	 */
	void RegisterFramework::processSingleTControl(TControl_vector_ptr vector) {
	    foreach(TControl * ctrl, *vector) {
		String caption = null;
		//check和labeled edit是唯二自帶reg name的
		TCheckBox *checkBox = dynamic_cast < TCheckBox * >(ctrl);
		if (null != checkBox) {
		    caption = checkBox->Caption;
		}
		TLabeledEdit *labeledEdit = dynamic_cast < TLabeledEdit * >(ctrl);
		if (null != labeledEdit) {
		    caption = labeledEdit->EditLabel->Caption;
		}
		if (caption != null) {
		    string caption_stl = caption.c_str();
		    ctrl2nameMap[ctrl] = caption_stl;
		    RegisterType_ptr reg = registerMap->getRegister(caption_stl);
		    if (null != reg) {
			reg->control = ctrl;
		    } else {
			ctrl->Visible = false;
		    }
		}

	    }

	};
	TControl_vector_ptr RegisterFramework::findSameTop(TControl_vector_ptr vector,
							   TControl * find) {
	    return findSameTop(vector, find, true);
	};

/*
   same top的從寬原則是:
   只要有重疊到一半就算same top
 */
	TControl_vector_ptr RegisterFramework::
	    findSameTop(TControl_vector_ptr vector, TControl * find, bool loose) {
	    TControl_vector_ptr result(new TControl_vector());
	    foreach(TControl * ctrl, *vector) {
		if (loose) {

		    /*
		       upper:

		       ctrl==
		       find==
		       mid --     == (ctrl's bottom must over middle)
		       ==

		       below:
		       find==
		       mid -- ctrl== (ctrl m top must less than middle)
		       ==
		       ==
		     */
		    int middle = (find->Top + find->Height / 2);
		    bool upper = (ctrl->Top + ctrl->Height) > middle;
		    bool below = ctrl->Top < middle;
		    if (ctrl != find && (upper || below)) {
			result->push_back(ctrl);
		    }
		} else {
		    if (ctrl != find && find->Top == ctrl->Top) {
			result->push_back(ctrl);
		    }
		}
	    }
	    return result;
	};

/*

 */
	void RegisterFramework::bindComboBox(const string & regname, int n, ...) {
	    RegisterType_ptr reg = registerMap->getRegister(regname);
	    if (null == reg) {
		return;
	    };
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
	void RegisterFramework::bind(const string & regname, TControl * control) {
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
	static const char &Space = ' ';
	void __fastcall RegisterFramework::onClick(TObject * Sender) {
	    TCheckBox *chechBox = dynamic_cast < TCheckBox * >(Sender);
	    if (null != chechBox) {
		string regname = ctrl2nameMap[chechBox];
		simpleEventHandler(regname, chechBox, Space);
		return;
	    }
	    TComboBox *comboBox = dynamic_cast < TComboBox * >(Sender);
	    if (null != comboBox) {
		string regname = ctrl2nameMap[comboBox];
		simpleEventHandler(regname, comboBox, Space);
	    }
	};
	void __fastcall RegisterFramework::onKeyPress(TObject * Sender, char &Key) {
	    TLabeledEdit *edit = dynamic_cast < TLabeledEdit * >(Sender);
	    if (null != edit) {
		string regname = ctrl2nameMap[edit];
		simpleEventHandler(regname, edit, Key);
	    }
	};
	void __fastcall RegisterFramework::onChange(TObject * Sender) {
	    TScrollBar *scroll = dynamic_cast < TScrollBar * >(Sender);
	    if (null != scroll) {
		string regname = ctrl2nameMap[scroll];
		simpleEventHandler(regname, scroll, Space);

	    }
	};
	void RegisterFramework::simpleEventHandler(std::string regname, TObject * sender,
						   const char &key) {
	    RegisterType_ptr regType = registerMap->getRegister(regname);
	    if (0 != regType->originalOnChangeFunc) {
		regType->originalOnChangeFunc(sender);
	    }
	    if (0 != regType->originalOnKeyPressFunc) {
		regType->originalOnKeyPressFunc(sender, key);
	    };
	};


	void RegisterFramework::processOnChange(TScrollBar * scrollBar, RegisterType_ptr reg) {
	    if (null != scrollBar->OnChange) {
		reg->originalOnChangeFunc = scrollBar->OnChange;
	    }
	    scrollBar->OnChange = onChange;
	};
	void RegisterFramework::processOnClick(TCheckBox * checkBox, RegisterType_ptr reg) {
	    if (null != checkBox->OnClick) {
		reg->originalOnChangeFunc = checkBox->OnClick;
	    }
	    checkBox->OnClick = onClick;
	};
	void RegisterFramework::processOnClick(TComboBox * comboBox, RegisterType_ptr reg) {
	    if (null != comboBox->OnClick) {
		reg->originalOnChangeFunc = comboBox->OnClick;
	    }
	    comboBox->OnClick = onClick;
	};
    };
};

