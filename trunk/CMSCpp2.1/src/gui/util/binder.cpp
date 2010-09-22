//#include <includeall.h>
#pragma hdrstop
#include "binder.h"

//C系統文件
//#include <cstdarg>
//C++系統文件
#include <utility>
//其他庫頭文件
//#include <boost/tokenizer.hpp>
//本項目內頭文件
//#include <debug.h>

namespace gui {
    namespace util {
	using namespace std;
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
	    edit2(edit2),
	    type(Edit2Edit) {

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
	    //using namespace std;
	    TWinControl *ctrl = dynamic_cast < TWinControl * >(sender);
	    if (null != ctrl) {
		Range range = binderMap2.equal_range(ctrl);
		for (BinderItrator i = range.first; i != range.second; ++i) {
		    binder_ptr binder = i->second;
		    binder->active(ctrl);
		}

		/*binder_ptr binder = binderMap[ctrl];
		if (null != binder) {
		    binder->active(ctrl);
		}*/
	    }
	};
	void MultiUIBinder::bind(TEdit * edit, TScrollBar * scrollBar) {
	    binder_ptr binder(new UIBinder(edit, scrollBar));
	    //binderMap[edit] = binder;
	    //binderMap[scrollBar] = binder;
	    binderMap2.insert(make_pair(edit, binder));
	    binderMap2.insert(make_pair(scrollBar, binder));
	};
	void MultiUIBinder::bind(TEdit * edit1, TEdit * edit2) {
	    using namespace std;
	    binder_ptr binder(new UIBinder(edit1, edit2));
	    //binderMap[edit1] = binder;
	    //binderMap[edit2] = binder;
	    binderMap2.insert(make_pair(edit1, binder));
	    binderMap2.insert(make_pair(edit2, binder));
	};

    };
};

