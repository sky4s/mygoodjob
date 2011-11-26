#include <includeall.h>
#pragma hdrstop
#include "RegisterFramework.h"
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

	RegisterFramework::RegisterFramework() {
	    childmap = TControlVecMap_ptr(new TControlVecMap());
	    labelvector = TLabel_vector_ptr(new TLabel_vector());
	    statictextVector = TControl_vector_ptr(new TControl_vector());
	};

	/*
	   scanUI要做的事情
	   1.依照parent分類
	   2.繫結: Scroll跟StaticText,
	   3.歸類: Label跟ComboBox, Label跟Scroll 
	 */
	void RegisterFramework::scanUI(TForm * form) {
	    childScan(form);

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

		TWinControl *wctrl = dynamic_cast < TWinControl * >(child);
		if (null != wctrl) {
		    childScan(wctrl);
		    continue;
		}

		TLabel *label = dynamic_cast < TLabel * >(child);
		if (null != label) {
		    labelvector->push_back(label);
		}

		TStaticText *staticText =
		    dynamic_cast < TStaticText * >(child);
		if (null != staticText) {
		    statictextVector->push_back(staticText);
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
    };

};

