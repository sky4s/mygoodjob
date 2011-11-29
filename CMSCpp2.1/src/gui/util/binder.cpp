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
	void UIValueSetter::setFilter(TextFilterIF_ptr filter) {
	    this->filter = filter;
	};
	void UIValueSetter::setFilterFunction(FilterFunction func) {
	    this->filterFunction = func;
	};
	String UIValueSetter::getString(int value) {
	    if (null != filterFunction) {
		return filterFunction(value);
	    } else if (null != filter) {
		return filter->filter(value);
	    } else {
		return value;
	    }

	};
	//=====================================================================
	// setter group
	//=====================================================================
      Edit2ScrollBarSetter::Edit2ScrollBarSetter(TEdit * edit, TScrollBar * scrollBar):edit(edit),
	    scrollBar(scrollBar)
	{
	};

	void Edit2ScrollBarSetter::set(TObject * sender) {
	    if (edit == sender) {
		int value = edit->Text.ToInt();
		scrollBar->Position = value;
	    } else if (scrollBar == sender) {
		int value = scrollBar->Position;
		edit->Text = getString(value);
	    }
	};

      Label2ScrollBarSetter::Label2ScrollBarSetter(TLabel * label, TScrollBar * scrollBar):label(label),
	    scrollBar(scrollBar)
	{
	};

	void Label2ScrollBarSetter::set(TObject * sender) {
	    /*if (label == sender) {
	       int value = label->Caption.ToInt();
	       scrollBar->Position = value;
	       } else */
	    if (scrollBar == sender) {
		int value = scrollBar->Position;
		label->Caption = getString(value);
	    }
	};


      StaticText2ScrollBarSetter::StaticText2ScrollBarSetter(TStaticText * text, TScrollBar * scrollBar):text(text),
	    scrollBar(scrollBar)
	{
	};

	void StaticText2ScrollBarSetter::set(TObject * sender) {
	    if (scrollBar == sender) {
		int value = scrollBar->Position;
		text->Caption = getString(value);
	    }
	};

      ScrollBar2ScrollBarSetter::ScrollBar2ScrollBarSetter(TScrollBar * scrollBar1, TScrollBar * scrollBar2):scrollBar1(scrollBar1), scrollBar2(scrollBar2)
	{
	};

	void ScrollBar2ScrollBarSetter::set(TObject * sender) {
	    if (scrollBar1 == sender) {
		scrollBar2->Position = scrollBar1->Position;
	    } else if (scrollBar2 == sender) {
		scrollBar1->Position = scrollBar2->Position;
	    }
	};

      Edit2EditSetter::Edit2EditSetter(TEdit * edit1, TEdit * edit2):edit1(edit1), edit2(edit2)
	{
	};

	void Edit2EditSetter::set(TObject * sender) {
	    if (edit1 == sender) {
		edit2->Text = edit1->Text;
	    } else if (edit2 == sender) {
		edit1->Text = edit2->Text;
	    }
	};

	//=====================================================================

	//=====================================================================
	// binder group
	//=====================================================================
	MultiUIBinder::MultiUIBinder() {
	};
	void __fastcall MultiUIBinder::active(TObject * sender) {
	    TControl *ctrl = dynamic_cast < TControl * >(sender);
	    if (null != ctrl) {
		Range range = setterMap.equal_range(ctrl);
		for (SetterIterator i = range.first; i != range.second; ++i) {
		    uiset_ptr setter = i->second;
		    setter->set(ctrl);
		}
	    }
	};
	void MultiUIBinder::bind(TEdit * edit, TScrollBar * scrollBar) {
	    uiset_ptr setter(new Edit2ScrollBarSetter(edit, scrollBar));
	    bind(edit, scrollBar, setter);
	};
	void MultiUIBinder::bind(TEdit * edit1, TEdit * edit2) {
	    using namespace std;
	    uiset_ptr setter(new Edit2EditSetter(edit1, edit2));
	    bind(edit1, edit2, setter);
	};
	void MultiUIBinder::bind(TScrollBar * scrollBar1, TScrollBar * scrollBar2) {
	    using namespace std;
	    uiset_ptr setter(new ScrollBar2ScrollBarSetter(scrollBar1, scrollBar2));
	    bind(scrollBar1, scrollBar2, setter);
	};
	void MultiUIBinder::bind(TLabel * label, TScrollBar * scrollBar) {
	    bind(nil_TextFilterIF_ptr, label, scrollBar);
	};
	void MultiUIBinder::bind(TextFilterIF_ptr filter, TLabel * label, TScrollBar * scrollBar) {
	    using namespace std;
	    uiset_ptr setter(new Label2ScrollBarSetter(label, scrollBar));
	    setter->setFilter(filter);
	    setter->set(scrollBar);
	    scrollBar->OnChange = active;
	    bind(label, scrollBar, setter);
	};

	void MultiUIBinder::bind(FilterFunction filterFunction, TLabel * label,
				 TScrollBar * scrollBar) {
	    using namespace std;
	    uiset_ptr setter(new Label2ScrollBarSetter(label, scrollBar));
	    setter->setFilterFunction(filterFunction);
	    setter->set(scrollBar);
	    scrollBar->OnChange = active;
	    bind(label, scrollBar, setter);
	};

	void MultiUIBinder::bind(TStaticText * text, TScrollBar * scrollBar) {
	    bind(nil_TextFilterIF_ptr, text, scrollBar);
	};
	void MultiUIBinder::bind(TextFilterIF_ptr filter, TStaticText * text,
				 TScrollBar * scrollBar) {
	    using namespace std;
	    uiset_ptr setter(new StaticText2ScrollBarSetter(text, scrollBar));
	    setter->setFilter(filter);
	    setter->set(scrollBar);
	    scrollBar->OnChange = active;
	    bind(text, scrollBar, setter);
	};

	void MultiUIBinder::bind(FilterFunction filterFunction, TStaticText * text,
				 TScrollBar * scrollBar) {
	    using namespace std;
	    uiset_ptr setter(new StaticText2ScrollBarSetter(text, scrollBar));
	    setter->setFilterFunction(filterFunction);
	    setter->set(scrollBar);
	    scrollBar->OnChange = active;
	    bind(text, scrollBar, setter);
	};

	void MultiUIBinder::bind(TControl * ctrl1, TControl * ctrl2, uiset_ptr setter) {
	    setterMap.insert(make_pair(ctrl1, setter));
	    setterMap.insert(make_pair(ctrl2, setter));
	};
	int MultiUIBinder::loose(TControl * ctrl) {
	    int eraseCount = -1;
	    if (null != ctrl) {
		eraseCount = setterMap.erase(ctrl);
	    }
	    return eraseCount;
	};

	//=====================================================================
    };
};

