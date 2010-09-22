#ifndef BINDERH
#define BINDERH

//C系統文件

//C++系統文件
#include <map>
//其他庫頭文件
#include <vcl.h>
#include <Controls.hpp>
//本項目內頭文件
#include <java/lang.h>

typedef std::multimap < TWinControl *,
    binder_ptr >::const_iterator BinderItrator;
typedef std::pair < BinderItrator, BinderItrator > Range;

namespace gui {
    namespace util {
	class UIBinder {
	    enum Type { Edit2ScrollBar, Edit2Edit };
	  private:
	    TEdit * edit;
	    TEdit *edit2;
	    TScrollBar *scrollBar;
	    Type type;
	  protected:
	    virtual double editToScrollBarValue(double value);
	    virtual double scrollBarToEditValue(double value);
	    void edit2ScrollBar(TObject * sender);
	    void edit2Edit(TObject * sender);
	  public:
	    UIBinder(TEdit * edit, TScrollBar * scrollBar);
	    UIBinder(TEdit * edit1, TEdit * edit2);
	    void active(TObject * sender);
	};

	class MultiUIBinder {
	  private:
	    //std::map < TWinControl *, binder_ptr > binderMap;
	    std::multimap < TWinControl *, binder_ptr > binderMap2;
	  public:
	    MultiUIBinder();
	    void active(TObject * sender);
	    void bind(TEdit * edit, TScrollBar * scrollBar);
	    void bind(TEdit * edit1, TEdit * edit2);
	};
    };
};

#endif

