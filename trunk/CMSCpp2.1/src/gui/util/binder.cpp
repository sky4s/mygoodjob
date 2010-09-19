#include <includeall.h>
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
	double UIBinder::editToScrollBar(double value) {
	    return value;
	};
	double UIBinder::scrollBarToEdit(double value) {
	    return value;
	};

      UIBinder::UIBinder(TEdit * edit, TScrollBar * scrollBar):edit(edit),
	    scrollBar(scrollBar)
	{

	};
    };
};

