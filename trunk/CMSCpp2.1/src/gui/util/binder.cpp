//#include <includeall.h>
#pragma hdrstop
#include "binder.h"

//C系統文件
//#include <cstdarg>
//C++系統文件

//其他庫頭文件
//#include <boost/tokenizer.hpp>
//本項目內頭文件
//#include <debug.h>

namespace gui {
    namespace util {
	double UIBinder::editToScrollBarValue(double value) {
	    return value;
	};
	double UIBinder::scrollBarToEditValue(double value) {
	    return value;
	};

      UIBinder::UIBinder(TEdit * edit, TScrollBar * scrollBar):edit(edit),
	    scrollBar(scrollBar),
	    type(Edit2ScrollBar) {

	};
      UIBinder::UIBinder(TEdit * edit1, TEdit * edit2):edit(edit1),
	    edit2(edit2), type(Edit2Edit) {

	};

	void UIBinder::edit2ScrollBar(TObject * sender) {
	    if (edit == sender) {
		int value = edit->Text.ToInt();
		scrollBar->Position = (int) editToScrollBarValue(value);
	    } else if (scrollBar == sender) {
		int value = scrollBar->Position;
		edit->Text = scrollBarToEditValue(value);
	    }
	};
	void UIBinder::edit2Edit(TObject * sender) {
	    if (edit == sender) {
		edit2->Text = edit->Text;
	    } else if (edit2 == sender) {
		edit->Text = edit2->Text;
	    }
	};
	void UIBinder::active(TObject * sender) {
	    switch (type) {
	    case Edit2ScrollBar:
		edit2ScrollBar(sender);
		break;
	    case Edit2Edit:
		edit2Edit(sender);
		break;
	    }
	};

	MultiUIBinder::MultiUIBinder() {
	};
	void MultiUIBinder::active(TObject * sender) {
	    TWinControl *ctrl = dynamic_cast < TWinControl * >(sender);
	    if (null != ctrl) {
		binder_ptr binder = bindebrMap[ctrl];
		if (null != binder) {
		    binder->active(ctrl);
		}
	    }
	};
	void MultiUIBinder::bind(TEdit * edit, TScrollBar * scrollBar) {
	    binder_ptr binder(new UIBinder(edit, scrollBar));
	    bindebrMap[edit] = binder;
	    bindebrMap[scrollBar] = binder;
	};
	void MultiUIBinder::bind(TEdit * edit1, TEdit * edit2) {
	    binder_ptr binder(new UIBinder(edit1, edit2));
	    bindebrMap[edit1] = binder;
	    bindebrMap[edit2] = binder;
	};

    };
};

